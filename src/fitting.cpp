#include <chrono>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <vector>

#include <cmath>

#include "TFile.h"
#include "RooRealVar.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"

#include "func.hpp"

using namespace std;
using namespace RooFit;

void fitting(void);
vector<double> parse(const string &file);

double CalcVelocity(const double tof) {
    double distance = 50.5; //in cm
    return(1.0);
    //return(distance/tof); // cm/ns
}

int main(int argc, char* argv[]) {
    string fileName="data/tofs.dat";
    //parse(fileName);
    fitting();
}

void fitting(void) {
    //Read in the data and set the variable to fit.
    RooRealVar tof("tof","tof",0,220);
    RooDataSet *data = RooDataSet::read("data/tofs.dat",RooArgList(tof));

    // RooDataSet data("data","data",RooArgSet(tof));
    // for(unsigned int i = 0; i < input.size(); i++) {
    //     tof=input[i];
    //     data.add(RooArgSet(tof));
    // }

    double peaks[]={17.333, 21.333, 27.111, 31.111, 34.222, 40.444, 45.778, 
                    49.778, 56, 60.444, 66.222, 70.667, 77.333, 84.889,
                    92.889, 102.222, 111.111, 120, 127};
    double wiggle=7.;
    double areaStart = 500.;
    double width=3.5;
    //double sigma = 3.5;
    double sigma = width/(2*sqrt(2*log(2)));
    double tau=-0.0253;
    
    // PDFs parameters for peak 0
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-wiggle, peaks[0]+wiggle);
    RooRealVar sigma0("sigma0","", sigma);
    RooRealVar alpha0("alpha0","number of events in peak 0", areaStart, 0, 5000);
    RooGaussian peak0("peak0","peak distribution", tof, mu0, sigma0);
    RooRealVar tau0("tau0", "", CalcVelocity(peaks[0])*tau, -5., 0.);
    RooExponential decay0("decay0", "decay part 0", tof, tau0);
    RooProdPdf vandle0 ("vandle0", "vandle dist 0", RooArgList(decay0,peak0));
    // PDFs parameters for peak 1
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-wiggle, peaks[1]+wiggle);
    RooRealVar sigma1("sigma1","", sigma);
    RooRealVar alpha1("alpha1","number of events in peak 1", areaStart, 0, 5000);
    RooGaussian peak1("peak1","peak distribution",tof,mu1,sigma1);
    RooRealVar tau1("tau1", "", CalcVelocity(peaks[1])*tau, -5., 0.);
    RooExponential decay1("decay1", "decay part 0", tof, tau1);
    RooProdPdf vandle1 ("vandle1", "vandle dist 0", RooArgList(decay1,peak1));
    // PDFs parameters for peak 2
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-wiggle, peaks[2]+wiggle);
    RooRealVar sigma2("sigma2","", sigma);
    RooRealVar alpha2("alpha2","number of events in peak 2", areaStart, 0, 5000.);
    RooGaussian peak2("peak2","peak distribution",tof,mu2,sigma2);
    RooRealVar tau2("tau2", "", CalcVelocity(peaks[2])*tau, -5., 0.);
    RooExponential decay2("decay2", "decay part 2", tof, tau2);
    RooProdPdf vandle2("vandle2", "vandle dist 2", RooArgList(decay2,peak2));
    // PDFs parameters for peak 3
    RooRealVar mu3("mu3","", peaks[3], peaks[3]-wiggle, peaks[3]+wiggle);
    RooRealVar sigma3("sigma3","", sigma);
    RooRealVar alpha3("alpha3","number of events in peak 3",areaStart,0, 5000.);
    RooGaussian peak3("peak3","peak distribution",tof,mu3,sigma3);
    RooRealVar tau3("tau3", "", CalcVelocity(peaks[3])*tau, -5., 0.);
    RooExponential decay3("decay3", "decay part 3", tof, tau3);
    RooProdPdf vandle3 ("vandle3", "vandle dist 3", RooArgList(decay3,peak3));
    // PDFs parameters for peak 4
    RooRealVar mu4("mu4","", peaks[4], peaks[4]-wiggle, peaks[4]+wiggle);
    RooRealVar sigma4("sigma4","", sigma);
    RooRealVar alpha4("alpha4","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak4("peak4","peak distribution",tof,mu4,sigma4);
    RooRealVar tau4("tau4", "", CalcVelocity(peaks[4])*tau, -5., 0.);
    RooExponential decay4("decay4", "decay part 4", tof, tau4);
    RooProdPdf vandle4 ("vandle4", "vandle dist 4", RooArgList(decay4,peak4));
    // PDFs parameters for peak 5
    RooRealVar mu5("mu5","", peaks[5], peaks[5]-wiggle, peaks[5]+wiggle);
    RooRealVar sigma5("sigma5","", sigma);
    RooRealVar alpha5("alpha5","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak5("peak5","peak distribution",tof,mu5,sigma5);
    RooRealVar tau5("tau5", "", CalcVelocity(peaks[5])*tau, -5., 0.);
    RooExponential decay5("decay5", "decay part 5", tof, tau5);
    RooProdPdf vandle5 ("vandle5", "vandle dist 5", RooArgList(decay5,peak5));
    // PDFs parameters for peak 6
    RooRealVar mu6("mu6","", peaks[6], peaks[6]-wiggle, peaks[6]+wiggle);
    RooRealVar sigma6("sigma6","", sigma);
    RooRealVar alpha6("alpha6","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak6("peak6","peak distribution",tof,mu6,sigma6);
    RooRealVar tau6("tau6", "", CalcVelocity(peaks[6])*tau, -5., 0.);
    RooExponential decay6("decay6", "decay part 6", tof, tau6);
    RooProdPdf vandle6 ("vandle6", "vandle dist 6", RooArgList(decay6,peak6));
    // PDFs parameters for peak 7
    RooRealVar mu7("mu7","", peaks[7], peaks[7]-wiggle, peaks[7]+wiggle);
    RooRealVar sigma7("sigma7","", sigma);
    RooRealVar alpha7("alpha7","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak7("peak7","peak distribution",tof,mu7,sigma7);
    RooRealVar tau7("tau7", "", CalcVelocity(peaks[7])*tau, -5., 0.);
    RooExponential decay7("decay7", "decay part 7", tof, tau7);
    RooProdPdf vandle7 ("vandle7", "vandle dist 7", RooArgList(decay7,peak7));
    // PDFs parameters for peak 8
    RooRealVar mu8("mu8","", peaks[8], peaks[8]-wiggle, peaks[8]+wiggle);
    RooRealVar sigma8("sigma8","", sigma);
    RooRealVar alpha8("alpha8","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak8("peak8","peak distribution",tof,mu8,sigma8);
    RooRealVar tau8("tau8", "", CalcVelocity(peaks[8])*tau, -5., 0.);
    RooExponential decay8("decay8", "decay part 8", tof, tau8);
    RooProdPdf vandle8 ("vandle8", "vandle dist 8", RooArgList(decay8,peak8));
    // PDFs parameters for peak 9
    RooRealVar mu9("mu9","", peaks[9], peaks[9]-wiggle, peaks[9]+wiggle);
    RooRealVar sigma9("sigma9","", sigma);
    RooRealVar alpha9("alpha9","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak9("peak9","peak distribution",tof,mu9,sigma9);
    RooRealVar tau9("tau9", "", CalcVelocity(peaks[9])*tau, -5., 0.);
    RooExponential decay9("decay9", "decay part 9", tof, tau9);
    RooProdPdf vandle9 ("vandle9", "vandle dist 9", RooArgList(decay9,peak9));
    // PDFs parameters for peak 10
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-wiggle, peaks[10]+wiggle);
    RooRealVar sigma10("sigma105","", sigma);
    RooRealVar alpha10("alpha10","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak10("peak10","peak distribution",tof,mu10,sigma10);
    RooRealVar tau10("tau10", "", CalcVelocity(peaks[10])*tau, -5., 0.);
    RooExponential decay10("decay10", "decay part 10", tof, tau10);
    RooProdPdf vandle10 ("vandle10", "vandle dist 10", RooArgList(decay10,peak10));
    // PDFs parameters for peak 11
    RooRealVar mu11("mu11","", peaks[11], peaks[11]-wiggle, peaks[11]+wiggle);
    RooRealVar sigma11("sigma11","", sigma);
    RooRealVar alpha11("alpha11","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak11("peak11","peak distribution",tof,mu11,sigma11);
    RooRealVar tau11("tau11", "", CalcVelocity(peaks[11])*tau, -5., 0.);
    RooExponential decay11("decay11", "decay part 11", tof, tau11);
    RooProdPdf vandle11 ("vandle11", "vandle dist 11", RooArgList(decay11,peak11));
    // PDFs parameters for peak 12
    RooRealVar mu12("mu12","", peaks[12], peaks[12]-wiggle, peaks[12]+wiggle);
    RooRealVar sigma12("sigma12","", sigma);
    RooRealVar alpha12("alpha12","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak12("peak12","peak distribution",tof,mu12,sigma12);
    RooRealVar tau12("tau12", "", CalcVelocity(peaks[12])*tau, -5., 0.);
    RooExponential decay12("decay12", "decay part 12", tof, tau12);
    RooProdPdf vandle12("vandle12", "vandle dist 12", RooArgList(decay12,peak12));
    // PDFs parameters for peak 13
    RooRealVar mu13("mu13","", peaks[13], peaks[13]-wiggle, peaks[13]+wiggle);
    RooRealVar sigma13("sigma13","", sigma);
    RooRealVar alpha13("alpha13","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak13("peak13","peak distribution",tof,mu13,sigma13);
    RooRealVar tau13("tau13", "", CalcVelocity(peaks[13])*tau, -5., 0.);
    RooExponential decay13("decay13", "decay part 13", tof, tau13);
    RooProdPdf vandle13("vandle13", "vandle dist 13", RooArgList(decay13,peak13));
    // PDFs parameters for peak 14
    RooRealVar mu14("mu14","", peaks[14], peaks[14]-wiggle, peaks[14]+wiggle);
    RooRealVar sigma14("sigma14","", sigma);
    RooRealVar alpha14("alpha14","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak14("peak14","peak distribution",tof,mu14,sigma14);
    RooRealVar tau14("tau14", "", CalcVelocity(peaks[14])*tau, -5., 0.);
    RooExponential decay14("decay14", "decay part 14", tof, tau14);
    RooProdPdf vandle14("vandle14", "vandle dist 14", RooArgList(decay14,peak14));
    // PDFs parameters for peak 15
    RooRealVar mu15("mu15","", peaks[15], peaks[15]-wiggle, peaks[15]+wiggle);
    RooRealVar sigma15("sigma15","", sigma);
    RooRealVar alpha15("alpha15","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak15("peak15","peak distribution",tof,mu15,sigma15);
    RooRealVar tau15("tau15", "", CalcVelocity(peaks[15])*tau, -5., 0.);
    RooExponential decay15("decay15", "decay part 15", tof, tau15);
    RooProdPdf vandle15("vandle15", "vandle dist 15", RooArgList(decay15,peak15));
    // PDFs parameters for peak 16
    RooRealVar mu16("mu16","", peaks[16], peaks[16]-wiggle, peaks[16]+wiggle);
    RooRealVar sigma16("sigma16","", sigma);
    RooRealVar alpha16("alpha16","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak16("peak16","peak distribution",tof,mu16,sigma16);
    RooRealVar tau16("tau16", "", CalcVelocity(peaks[16])*tau, -5., 0.);
    RooExponential decay16("decay16", "decay part 16", tof, tau16);
    RooProdPdf vandle16("vandle16", "vandle dist 16", RooArgList(decay16,peak16));
    // PDFs parameters for peak 17
    RooRealVar mu17("mu17","", peaks[17], peaks[17]-wiggle, peaks[17]+wiggle);
    RooRealVar sigma17("sigma17","", sigma);
    RooRealVar alpha17("alpha17","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak17("peak17","peak distribution",tof,mu17,sigma17);
    RooRealVar tau17("tau17","tau17",CalcVelocity(peaks[17])*tau,-5., 0.);
    RooExponential decay17("decay17", "decay part 17", tof, tau17);
    RooProdPdf vandle17("vandle17", "vandle dist 17", RooArgList(decay17,peak17));
    // PDFs parameters for peak 18
    RooRealVar mu18("mu18","", peaks[18], peaks[18]-wiggle, peaks[18]+wiggle);
    RooRealVar sigma18("sigma18","", sigma);
    RooRealVar alpha18("alpha18","number of events in peak 3",areaStart, 0, 5000.);
    RooGaussian peak18("peak18","peak distribution",tof,mu18,sigma18);
    RooRealVar tau18("tau18", "", CalcVelocity(peaks[18])*tau, -5., 0.);
    RooExponential decay18("decay18", "decay part 18", tof, tau18);
    RooProdPdf vandle18("vandle18", "vandle dist 18", RooArgList(decay18,peak18));

    // PDFs parameters for VANDLE
    //RooProdPdf npeak0("nPeak0", "vandleDist", RooArgList(peak_1,bkg));

    RooArgList prodList(vandle0,vandle1,vandle2,vandle3,vandle4,vandle5,vandle6,vandle7, 
                        vandle8);
    prodList.add(RooArgList(vandle9,vandle10,vandle11,vandle12,vandle13,vandle14,vandle15,
                            vandle16));
    prodList.add(RooArgList(vandle17,vandle18));
    RooArgList areaList(alpha0,alpha1,alpha2,alpha3,alpha4,alpha5,alpha6,
                        alpha7,alpha8);
    areaList.add(RooArgList(alpha9,alpha10,alpha11,alpha12,alpha13,alpha14,alpha15,
                         alpha16));
    areaList.add(RooArgList(alpha17,alpha18));

    /////////////////////////////////
    RooAddPdf model("model","model", prodList, areaList);
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save(), Range(0.,140.));

    //Do the plots
    RooPlot* frame = tof.frame();
    frame = tof.frame(200);
    frame->SetTitle("Time-of-Flight Spectrum");
    frame->SetXTitle("Time-of-Flight (ns)");
    frame->SetYTitle("Events/(ns)");
    frame->GetYaxis()->SetTitleOffset(1.2);
    data->plotOn(frame,Name("data1"));
    
    model.plotOn(frame,Name("model"));
    model.plotOn(frame,RooFit::Components("peak0"),RooFit::LineColor(kGreen), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("peak1"),RooFit::LineColor(kRed), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("peak2"),RooFit::LineColor(kYellow), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("peak3"),RooFit::LineColor(kViolet), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("peak4"),RooFit::LineColor(kOrange), 
                 RooFit::LineStyle(kDashed));
    model.plotOn(frame,RooFit::Components("peak5"),RooFit::LineColor(kPink), 
                 RooFit::LineStyle(kDashed));
    TCanvas* c = new TCanvas("c","",0,0,700,500);
    c->cd();
    c->SetFillColor(kWhite);
    frame->Draw();
    c->SaveAs("pics/image.eps");
}

vector<double> parse(const string &file) {
    vector<double> tof,counts, results;
    double temp1, temp2;
    string line;
    //read in the datafile
    ifstream data(file.c_str());
    if(data.is_open()) {
        while(data) {
            if(isdigit(data.peek())) {
                data >> temp1 >> temp2;
                tof.push_back((temp1-200)*0.5);
                counts.push_back(temp2);
            } else
                data.ignore(1000,'\n');
            
        }
    }else
        cout << "Cannot open the goddmaned file!!!" << endl;
    data.close();
    
    for(unsigned int i = 0; i < tof.size(); i++) {
        while(counts[i] > 0) {
            unsigned seed1 = 
                std::chrono::system_clock::now().time_since_epoch().count();
            uniform_real_distribution<double> dist(tof[i]-0.25,tof[i]+0.25);
            mt19937_64 rnd1(seed1);
            results.push_back(dist(rnd1));
            counts[i]--;
        }        
    }
    return(results);
}
