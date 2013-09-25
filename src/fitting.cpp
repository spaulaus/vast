#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>
#include <cstdio>

#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"

using namespace std;
using namespace RooFit;

void fitting(void);

string dirName = "077cu-ban4-lower/";
string fileName = "077cu-ban4-lower";

string dataName="../data/roofit/"+dirName+fileName+".dat";
//string epsName = "../pics/roofit/"+dirName+fileName+"-noConv.eps";
//string resultsFile = "results/"+dirName+fileName+"-noConv.fit";

string epsName = "../pics/roofit/working.eps";
string resultsFile = "results/working.dat";

int main(int argc, char* argv[]) {
    ifstream test(dataName.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the data file to read in the sexy data!!" << endl << endl;
        exit(1);
    }
    fitting();
}

void fitting(void) {
    //Read in the data and set the variable to fit.
    double low = 0.;
    double high = 200.;
    RooRealVar tof("tof","tof", 0.0, low, high);

    double binning = 0.5;

    //Set the information for the peaks
    double peaks[]={23.855, 30.1971, 38.128, 44.917, 
                    50.181, 56.835, 65.151, 70.826,
                    79.253, 87.198, 94.690, 104.69, 
                    112.73, 135.93};
    double wiggle = 100.;
    
    double yStart = 3.e3, yLow = 0., yHigh = 1.e8;
    
    //Parameterization Parameters for Sigma -> sM*mu + sB
    RooConstVar sA("sA","", 2.55056292412568);
    RooConstVar sB("sB","", -0.0192702755935177);
    RooConstVar sC("sC","", 0.000620834380435262);
    RooConstVar sD("sD","", -4.02706921636101e-6);
    RooConstVar sE("sE","", 1.01415462736843e-8);

    //Parameterization Parameters for Alpha -> aM/mu + aB
    RooConstVar aI("aI","", 2.97314684100351e-7);
    RooConstVar aH("aH","", -0.000105412912022653);
    RooConstVar aG("aG","", 0.0135441451470589 );
    RooConstVar aF("aF","", -1.18042124700263);

    //Parameterization Parameters for N -> nM/mu + nB
    RooConstVar nJ("nJ","", -4.38376875421603);
    RooConstVar nK("nK","", -0.000234978549811854);
    RooConstVar nL("nL","", 1.32334100981145);

    vector<string> components;
    RooArgList cbs, ylds;

    for(int i = 0; i < 14; i++) {
        stringstream nameMu, nameYld, nameSig, nameAlph, nameN, nameCb;
        stringstream fAlph, fN, fSig;
        if(i < 10) {
            nameMu << "mu0" << i;
            nameYld << "yield0" << i;
            nameSig << "sigma0" << i;
            nameAlph << "alpha0" << i;
            nameN << "n0" << i;
            nameCb << "cb0" << i;
        }else {
            nameMu << "mu" << i;
            nameYld << "yield" << i;
            nameSig << "sigma" << i;
            nameAlph << "alpha" << i;
            nameN << "n" << i;
            nameCb << "cb" << i;
        }                         
        components.push_back(nameCb.str());

        RooRealVar *yield = new RooRealVar(nameYld.str().c_str(), "", yStart, 
                                     yLow, yHigh);
        RooRealVar *mu = new RooRealVar(nameMu.str().c_str(),"",peaks[i], 
                      peaks[i]-wiggle, peaks[i]+wiggle);
        
        fSig << "sE*pow(" << nameMu.str() << ",4)+sD*pow(" << nameMu.str() 
             << ",3)+sC*pow(" << nameMu.str() << ",2)+sB*" << nameMu.str()
             << "+sA";
        RooFormulaVar *sigma = new RooFormulaVar(nameSig.str().c_str(), fSig.str().c_str(), RooArgList(sA,sB,sC,sD,sE,*mu));
        
        fAlph << "aI*pow(" << nameMu.str() << ",3)+aH*pow(" << nameMu.str() 
              << ",2)+aG*" << nameMu.str() << "+aF";
        RooFormulaVar *alpha = new RooFormulaVar(nameAlph.str().c_str(), fAlph.str().c_str(), RooArgList(aI,aH,aG,aF,*mu));

        fN << "nJ/" << nameMu.str() << "+nK*" << nameMu.str() << "+nL";
        RooFormulaVar *n = new RooFormulaVar(nameN.str().c_str(), fN.str().c_str(), 
                         RooArgList(nJ,nK,nL,*mu));

        RooCBShape *cb = new RooCBShape(nameCb.str().c_str(), "", tof, *mu, 
                                    *sigma, *alpha, *n);
        
        cbs.add(*cb);
        ylds.add(*yield);
    }
    
    RooAddPdf model("model", "", cbs, ylds);
    RooDataSet *data = RooDataSet::read(dataName.c_str(), RooArgList(tof));
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(low, high));

    ofstream resultsParam(resultsFile.c_str());
    fitResult->printMultiline(resultsParam, 0, true, "");
    resultsParam.close();
    
    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(high*binning);
    frame->SetTitle("");
    frame->SetAxisRange(0.,500.,"Y");
    frame->SetAxisRange(0.,200.,"X");
    frame->SetXTitle("Time-of-Flight (2 ns)");
    frame->SetYTitle("Events / 2 ns");
    frame->GetYaxis()->SetTitleOffset(1.2);
    
    data->plotOn(frame,Name("data"));
    model.plotOn(frame,Name("model"));
    
    int lineColor = 36;
    for(unsigned int i = 0; i < components.size(); i++, lineColor++) {
        model.plotOn(frame,Components(components.at(i).c_str()),
                     LineColor(lineColor), LineStyle(2));
    }
   
    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    frame->Draw();
    c->SaveAs(epsName.c_str());

    if(fitResult->statusCodeHistory(0) != 0)
        cout << endl << endl << "Oh, Jesus, the fit did not converge." << endl;
    else
        cout << endl << endl << "The fit converged successfully." << endl;

    if(fitResult->statusCodeHistory(1) != 0)
        cout << "Hesse FAILED to calculate things properly." << endl << endl;
    else
        cout << "HESSE successfully calculated things." << endl << endl;
}
