/** \file LimitFinder.cpp
 *  \brief A class to find the sensitivity limit of the analysis
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#include <string>

#include <RooAddPdf.h>
#include <RooCBShape.h>
#include <RooConstVar.h>
#include <RooDataSet.h>
#include <RooFitResult.h>
#include <RooRealVar.h>


#include "LimitFinder.hpp"
#include "PhysicalConstants.hpp"

using namespace std;
using namespace RooFit;
using namespace PhysicalConstants;

///This method performs the fit needed to calculates the sensitivity limit of the detectors
Neutron LimitFinder::PerformFit(const double &edge, const double &yield, const CrystalBallParameters &cbpars) {
    double mass = Masses::Neutron.GetValue(); //MeV/c^2
    double c = General::SpeedOfLight.GetValue() * (100 / 1e9); //cm/ns
    ///@TODO Another hard coded distance.
    double edg = (50.5 / c) * sqrt(mass / (2 * edge));

    RooRealVar tof("tof", "tof", 0.0, 0.0, 200.);

    ///@TODO Could we make this a little cleaner like we do below? Make a loop that way we don't have to worry about
    /// setting all these by hand?
    vector<Variable> alphaCoefficients = cbpars.GetAlphaCoefficients();
    RooConstVar a3("a3", "", alphaCoefficients[3].GetValue());
    RooConstVar a2("a2", "", alphaCoefficients[2].GetValue());
    RooConstVar a1("a1", "", alphaCoefficients[1].GetValue());
    RooConstVar a0("a0", "", alphaCoefficients[0].GetValue());

    vector<Variable> nCoefficients = cbpars.GetNCoefficients();
    RooConstVar n2("n2", "", nCoefficients[2].GetValue());
    RooConstVar n1("n1", "", nCoefficients[1].GetValue());
    RooConstVar n0("n0", "", nCoefficients[0].GetValue());

    vector<Variable> sigmaCoefficients = cbpars.GetSigmaCoefficients();
    RooConstVar s4("s4", "", sigmaCoefficients[4].GetValue());
    RooConstVar s3("s3", "", sigmaCoefficients[3].GetValue());
    RooConstVar s2("s2", "", sigmaCoefficients[2].GetValue());
    RooConstVar s1("s1", "", sigmaCoefficients[1].GetValue());
    RooConstVar s0("s0", "", sigmaCoefficients[0].GetValue());


    //---------- The Variables for the cb to generate the peak
    RooConstVar mu("mu", "", edg);
    string fAlph = cbpars.GetAlphaFunction("mu");
    RooFormulaVar alpha("alpha", "", fAlph.c_str(), RooArgList(a3, a2, a1, a0, mu));
    string fN = cbpars.GetNFunction("mu");
    RooFormulaVar n("n", fN.c_str(), RooArgList(n2, n1, n0, mu));
    string fSig = cbpars.GetSigmaFunction("mu");
    RooFormulaVar sigma("sigma", "", fSig.c_str(), RooArgList(s4, s3, s2, s1, s0, mu));
    RooCBShape cb("cb", "", tof, mu, sigma, alpha, n);

    //---------- Generate the data set from the above peak
    RooDataSet *mcData = cb.generate(tof, yield);

    //---------- The Variables for the cb to fit the peak
    RooRealVar yld("yld", "", yield, 0.0, yield * 2);
    RooRealVar mu1("mu1", "", edg, 0., 200.);
    fAlph = cbpars.GetAlphaFunction("mu1");
    RooFormulaVar alpha1("alpha1", "", fAlph.c_str(), RooArgList(a3,a2,a1,a0, mu1));
    fN = cbpars.GetNFunction("mu1");
    RooFormulaVar nalt("nalt", fN.c_str(), RooArgList(n2,n1,n0,mu1));
    fSig = cbpars.GetSigmaFunction("mu1");
    RooFormulaVar sigma1("sigma1", "", fSig.c_str(), RooArgList(s4,s3,s2,s1,s0, mu1));
    RooCBShape cb1("cb1", "", tof, mu1, sigma1, alpha1, nalt);

    RooAddPdf model("model", "", RooArgList(cb1), RooArgList(yld));

    //---------- Fit the new CB to the generated data set
    RooFitResult *fitResult = model.fitTo(*mcData, NumCPU(3), Save(), Range(0., 200.));

    bool hasConvergence = fitResult->statusCodeHistory(0) == 0;
    bool hasHesseCalc = fitResult->statusCodeHistory(1) == 0;

    if (hasConvergence && hasHesseCalc) {
        cout << "The Fit converged, and HESSE had no issues" << endl;

        Neutron pk;
        Variable mew, yield;
        RooArgList finals = fitResult->floatParsFinal();

        for (int i = 0; i < finals.getSize(); i++) {
            RooRealVar tmp = *((RooRealVar *) finals.at(i));
            if (i == 0)
                mew = Variable(tmp.getValV(), tmp.getError(), "ns");
            if (i == 1)
                yield = Variable(tmp.getValV(), tmp.getError(), "counts");
        }
        pk.SetMu(mew);
        pk.SetYld(yield);
        pk.SetSigma(Variable(cbpars.CalcSigma(mew.GetValue()), 0.0, "ns"));
        pk.SetAlpha(Variable(cbpars.CalcAlpha(mew.GetValue()), 0.0, ""));
        pk.SetN(Variable(cbpars.CalcN(mew.GetValue()), 0.0, ""));

        delete (fitResult);
        return (pk);
    } else {
        delete fitResult;

        if (!hasConvergence)
            throw TofFitterException("TofFitter::PerformFit - The fit didn't converge. Cannot proceed with analysis!");
        if (!hasHesseCalc)
            throw TofFitterException("TofFitter::PerformFit - Hesse failed, the error bars cannot be used! Cannot "
                                             "proceed with analysis.");
    }
}
