#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <cstdio>

#include <RooAddPdf.h>
#include <RooCBShape.h>
#include <RooConstVar.h>
#include <RooDataSet.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include <RooMCStudy.h>
#include <RooPlot.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>

#include "TofFitter.hpp"

using namespace std;
using namespace RooFit;



TofFitter::TofFitter(const vector<double> &peaks, const string &dir, 
                     const string &file, const bool &isTest = false)  {
    peaks_ = peaks;
    dataFile_ ="../data/tof/"+dir+file+".dat";
    if(isTest) {
        eps_ = "../pics/tof/working.eps";
        output_ = "../results/tof/working.fit";
    }else {
        eps_ = "../pics/tof/"+dir+file+".eps";
        output_ = "../results/tof"+dir+file+".fit";
    }
    CheckFileExistance();
    PerformFit();
}

TofFitter::TofFitter(const vector<double> &peaks, const string &dir, 
                     const string &file, const string &mod, 
                     const bool &isTest = false)  {
    peaks_ = peaks;
    dataFile_ ="../data/tof/"+dir+file+".dat";
    if(isTest) {
        eps_ = "../pics/tof/working.eps";
        output_ = "../results/tof/working.fit";
    }else {
        eps_ = "../pics/tof/"+dir+file+mod+".eps";
        output_ = "../results/tof"+dir+file+mod+".fit";
    }
    CheckFileExistance();
}

double TofFitter::CalcSigma(const double &tof){
    double sM = -0.000121210451962825;
    double sN = 0.0416568757021418;
    double sO = 0.550158923590531;
    return(sM*tof*tof+sN*tof+sO);
}

double TofFitter::CalcAlpha(const double &tof) {
//Parameterization Parameters for Alpha 
    double aI = 0.0130289072593045;
    double aH = 0.641803483244778;
    return(aI/tof/tof+aH);
}

double TofFitter::CalcN(const double &tof) {
//Parameterization Parameters for N 
    double nJ = 2.21591018795502e-06;
    double nK = 0.00189178692442985;
    double nL = 1.33190840921066;
    return(nJ*tof*tof+nK*tof+nL);
}


void TofFitter::CheckFileExistance(void) {
    ifstream test(dataFile_.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the data file to read" 
             << "in the sexy data!!" << endl << "What I got was " 
             << dataFile_ << endl << endl;
        exit(1);
    }
}

void TofFitter::PerformFit() {
     //Read in the data and set the variable to fit.
    double low = 0.;
    double high = 200.;
    RooRealVar tof("tof","tof", 0.0, low, high);

    double binning = 0.5;
    double wiggle = 200.;
    double yStart = 3.e3, yLow = 0., yHigh = 1.e8;
    
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

    vector<string> components, yields, mus, alphas, sigmas, ns;
    RooArgList cbs, ylds;
    
    for(unsigned int i = 0; i < peaks_.size(); i++) {
        stringstream nameMu, nameYld, nameSig, nameAlph, nameN, nameCb;
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
        yields.push_back(nameYld.str());
        mus.push_back(nameMu.str());
        alphas.push_back(nameAlph.str());
        sigmas.push_back(nameSig.str());
        ns.push_back(nameN.str());
    }

    for(unsigned int i = 0; i < yields.size(); i++) {
        stringstream fSig, fAlph, fN;
        RooRealVar *yield = new RooRealVar(yields[i].c_str(), "", yStart, 
                                     yLow, yHigh);
        RooRealVar *mu = new RooRealVar(mus[i].c_str(),"",peaks_[i], 
                      peaks_[i]-wiggle, peaks_[i]+wiggle);
        
        fSig << "sM*pow(" << mus[i] << ",2)+sN*" << mus[i] 
             << "+sO";
        RooFormulaVar *sigma = new RooFormulaVar(sigmas[i].c_str(), 
                                                 fSig.str().c_str(), 
                                                 RooArgList(sM,sN,sO,*mu));
        
        fAlph << "aI/pow(" << mus[i] << ",2)+aH";
        RooFormulaVar *alpha = new RooFormulaVar(alphas[i].c_str(), 
                                                 fAlph.str().c_str(), 
                                                 RooArgList(aI,aH,*mu));

        fN << "nJ*pow(" << mus[i] << ",2)+nK*" << mus[i] 
           << "+nL";
        RooFormulaVar *n = new RooFormulaVar(ns[i].c_str(), 
                                             fN.str().c_str(), 
                                             RooArgList(nJ,nK,nL,*mu));

        RooCBShape *cb = new RooCBShape(components[i].c_str(), "", tof, *mu, 
                                        *sigma, *alpha, *n);
        cbs.add(*cb);
        ylds.add(*yield);
    }

    RooAddPdf model("model", "", cbs, ylds);
    RooDataSet *data = RooDataSet::read(dataFile_.c_str(), RooArgList(tof));
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), 
                                          Range(low, high));
    
    map<string,pair<double,double> > fit;
    RooArgList finals = fitResult->floatParsFinal();
    for(unsigned int i = 0; i < yields.size()*2; i++) {
        RooRealVar tmp = *((RooRealVar*)finals.at(i));
        fit.insert(make_pair(tmp.GetName(), 
                             make_pair(tmp.getValV(), tmp.getError())));
    }

    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(high*binning);
    frame->SetTitle("");
    //frame->SetAxisRange(0.,450.,"Y");
    frame->SetAxisRange(0.,200.,"X");
    frame->SetXTitle("Time-of-Flight (ns)");
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
    c->SaveAs(eps_.c_str());

    hasConvergence_ = fitResult->statusCodeHistory(0) == 0;
    hasHesseCalc_   = fitResult->statusCodeHistory(1) == 0;

    if(hasConvergence_ && hasHesseCalc_) {
        cout << "The Fit converged, and HESSE had no issues" << endl;
        
        ofstream results(output_.c_str());
        results << "#Num Mu(ns) MuErr(ns) Yld YldErr Sigma Alpha N" << endl;
        for(unsigned int i = 0; i < yields.size(); i++) {
            pair<double,double> mew=fit.find(mus[i])->second;
            pair<double,double> y = fit.find(yields[i])->second;
            
            results << i << " " << mew.first << " " << mew.second << " " 
                    << y.first << " " << y.second << " " 
                    << CalcSigma(mew.first) << " " << CalcAlpha(mew.first) 
                    << " " << CalcN(mew.first) << endl;
        }
        results.close();
    }else {
        if(!hasConvergence_) 
            cout << endl << endl << "Oh, Jesus, the fit did not converge." 
                 << endl;
        if(!hasHesseCalc_)
            cout << "Hesse FAILED to calculate things properly." 
                 << endl << endl;
        exit(1);
    }
}

void TofFitter::PerformMcStudy(void) {
   // cout << endl << endl << "Starting to do the MC Study" << endl << endl;
   //  RooArgList newcb, newyld;
   //  for(unsigned int i = 0; i < yields.size(); i++) {
   //      stringstream fAlph, fN, fSig;
        
   //      RooRealVar *yield = new RooRealVar(yields[i].c_str(), "", 
   //                                         fit.find(yields[i])->second.first, 
   //                                         yLow, yHigh);
   //      RooConstVar *mu = new RooConstVar(mus[i].c_str(),"",
   //                                        fit.find(mus[i])->second.first);
        
   //      fSig << "sM*pow(" << mus[i] << ",2)+sN*" << mus[i] << "+sO";
   //      RooFormulaVar *sigma = new RooFormulaVar(sigmas[i].c_str(), 
   //                                               fSig.str().c_str(), 
   //                                               RooArgList(sM,sN,sO,*mu));
        
   //      fAlph << "aI/pow(" << mus[i] << ",2)+aH";
   //      RooFormulaVar *alpha = new RooFormulaVar(alphas[i].c_str(), 
   //                                               fAlph.str().c_str(), 
   //                                               RooArgList(aI,aH,*mu));
        
   //      fN << "nJ*pow(" << mus[i] << ",2)+nK*" << mus[i] << "+nL";
   //      RooFormulaVar *n = new RooFormulaVar(ns[i].c_str(), 
   //                                           fN.str().c_str(), 
   //                                           RooArgList(nJ,nK,nL,*mu));
        
   //      RooCBShape *cb = new RooCBShape(components[i].c_str(), "", tof, *mu, 
   //                                      *sigma, *alpha, *n);
   //      newcb.add(*cb);
   //      newyld.add(*yield);
   //  }

   //  RooAddPdf model1("model1", "", newcb, newyld);
    
   //  RooMCStudy mcstudy(model1,tof,Binned(kTRUE),Silence(), 
   //                     Extended(), 
   //                     FitOptions(Save(kTRUE),Range(0.,200.),
   //                                PrintEvalErrors(0)));
   //  mcstudy.generateAndFit(200);
   //  for(unsigned int i = 0; i < yields.size(); i++) {
   //      // Plot distribution of minimized likelihood
   //      RooPlot* frame1 = mcstudy.plotNLL(Bins(40));
        
   //      // Make plots of the distributions of the yield, 
   //      // the error on yield and the pull of yield
   //      RooRealVar subject = *((RooRealVar*)newyld.at(i));
   //      RooPlot* frame2 = mcstudy.plotParam(subject,Bins(40));
   //      RooPlot* frame3 = mcstudy.plotError(subject,Bins(40));
   //      RooPlot* frame4 = mcstudy.plotPull(subject,Bins(40),FitGauss(kTRUE));
        
   //      TCanvas* cc = new TCanvas("cc","",500,500);
   //      cc->Divide(2,2);
   //      cc->cd(1); frame1->GetYaxis()->SetTitleOffset(1.4); frame1->Draw();
   //      cc->cd(2); frame2->GetYaxis()->SetTitleOffset(1.4); frame2->Draw();
   //      cc->cd(3); frame3->GetYaxis()->SetTitleOffset(1.4); frame3->Draw();
   //      cc->cd(4); frame4->GetYaxis()->SetTitleOffset(1.4); frame4->Draw();
        
   //      stringstream name;
   //      name << "../pics/roofit/"+dirName+"/mcStudy-8keVee-b/" 
   //           << yields.at(i) <<".jpg";
   //      cc->SaveAs(name.str().c_str());
   //  }
}
