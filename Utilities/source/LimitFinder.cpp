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
#include <RooFormulaVar.h>
#include <RooRealVar.h>

#include <PhysConstants.hpp>
#include <Variable.hpp>

#include "LimitFinder.hpp"
#include "ParamCalculator.hpp"

using namespace std;
using namespace RooFit;

Neutron LimitFinder::PerformFit(const double &edge, const double &yield){
    PhysConstants consts;
    double mass = consts.GetConstant("neutronMass").GetValue(); //MeV/c^2
    double c = consts.GetConstant("c").GetValue()*(100/1e9); //cm/ns
    double edg = (50.5/c)*sqrt(mass/(2*edge));

    RooRealVar tof("tof","tof", 0.0, 0.0, 200.);
    
    //Parameterization Parameters for Sigma 
    RooConstVar sM("sM","", -0.000121210451962825);
    RooConstVar sN("sN","", 0.0416568757021418);
    RooConstVar sO("sO","", 0.550158923590531);

    //Parameterization Parameters for Alpha 
    RooConstVar aI("aI","", 0.0130289072593045);
    RooConstVar aH("aH","", -0.641803483244778);

    //Parameterization Parameters for N 
    RooConstVar nJ("nJ","", 2.21591018795502e-06);
    RooConstVar nK("nK","", 0.00189178692442985);
    RooConstVar nL("nL","", 1.33190840921066);

    //---------- The Variables for the cb to generate the peak
    RooConstVar mu("mu","",edg);
    string fSig = "sM*pow(mu,2)+sN*mu+sO";
    RooFormulaVar sigma("sigma", "", fSig.c_str(), RooArgList(sM,sN,sO,mu));
    string fAlph = "aI/pow(mu,2)+aH";
    RooFormulaVar alpha("alpha","",fAlph.c_str(),RooArgList(aI,aH,mu));
    string fN = "nJ*pow(mu,2)+nK*mu+nL";
    RooFormulaVar n("n", fN.c_str(), RooArgList(nJ,nK,nL,mu));
    RooCBShape cb("cb", "", tof, mu, sigma, alpha, n);

    //---------- Generate the data set from the above peak
    RooDataSet *mcData = cb.generate(tof,yield);

    //---------- The Variables for the cb to fit the peak
    RooRealVar yld("yld","",yield,0.0,yield*2);
    RooRealVar mu1("mu1","",edg, 0., 200.);
    fSig = "sM*pow(mu1,2)+sN*mu1+sO";
    RooFormulaVar sigma1("sigma1", "", fSig.c_str(), RooArgList(sM,sN,sO,mu1));
    fAlph = "aI/pow(mu1,2)+aH";
    RooFormulaVar alpha1("alpha1","",fAlph.c_str(),RooArgList(aI,aH,mu1));
    fN = "nJ*pow(mu1,2)+nK*mu1+nL";
    RooFormulaVar n1("n1", fN.c_str(), RooArgList(nJ,nK,nL,mu1));
    RooCBShape cb1("cb1", "", tof, mu1, sigma1, alpha1, n1);

    RooAddPdf model("model","",RooArgList(cb1),RooArgList(yld));
    
    //---------- Fit the new CB to the generated data set
    RooFitResult* fitResult = model.fitTo(*mcData, NumCPU(3), Save(), 
                                          Range(0.,200.));
    
    bool hasConvergence = fitResult->statusCodeHistory(0) == 0;
    bool hasHesseCalc   = fitResult->statusCodeHistory(1) == 0;

    if(hasConvergence && hasHesseCalc) {
        cout << "The Fit converged, and HESSE had no issues" << endl;
        
        Neutron pk;
        Variable mew, yield;
        RooArgList finals = fitResult->floatParsFinal();

        for(int i = 0; i < finals.getSize(); i++) {
            RooRealVar tmp = *((RooRealVar*)finals.at(i));
            if(i == 0)
                mew = Variable(tmp.getValV(), tmp.getError(), "ns");
            if(i == 1)
                yield = Variable(tmp.getValV(), tmp.getError(), "counts");
        }
        ParamCalculator par;
        pk.SetMu(mew);
        pk.SetYld(yield);
        pk.SetSigma(Variable(par.CalcSigma(mew.GetValue()), 0.0, "ns"));
        pk.SetAlpha(Variable(par.CalcAlpha(mew.GetValue()), 0.0, ""));
        pk.SetN(Variable(par.CalcN(mew.GetValue()), 0.0, ""));
        
        delete(fitResult);
        return(pk);
    }else {
        if(!hasConvergence) 
            cerr << endl << endl << "Oh, Jesus, the fit did not converge." 
                 << endl;
        if(!hasHesseCalc)
            cerr << "Hesse FAILED to calculate things properly." 
                 << endl << endl;
        
        delete(fitResult);
        exit(1);
    }
}
