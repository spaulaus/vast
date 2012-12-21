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
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"

#include "func.hpp"

using namespace std;
using namespace RooFit;

void fitting(void);
vector<double> parse(const string &file);

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
                    92.889, 102.222, 111.111, 120, 130};
    double width=5.5;
    double areaStart = 25;

    // PDFs parameters for peak 0
    RooRealVar mu0("mu0","", peaks[0], peaks[0]-width, peaks[0]+width);
    RooRealVar sigma0("sigma0","", 3.5);
    RooRealVar alpha0("alpha0","number of events in peak 0", areaStart, 0, 50);
    RooGaussian peak0("peak0","peak distribution", tof, mu0, sigma0);
    // PDFs parameters for peak 1
    RooRealVar mu1("mu1","", peaks[1], peaks[1]-width, peaks[1]+width);
    RooRealVar sigma1("sigma1","", 3.5);
    RooRealVar alpha1("alpha1","number of events in peak 1", areaStart, 0, 100);
    RooGaussian peak1("peak1","peak distribution",tof,mu1,sigma1);
    // PDFs parameters for peak 2
    RooRealVar mu2("mu2","", peaks[2], peaks[2]-width, peaks[2]+width);
    RooRealVar sigma2("sigma2","", 3.5);
    RooRealVar alpha2("alpha2","number of events in peak 2", areaStart, 0, 200);
    RooGaussian peak2("peak2","peak distribution",tof,mu2,sigma2);
    // PDFs parameters for peak 3
    RooRealVar mu3("mu3","", peaks[3], peaks[3]-width, peaks[3]+width);
    RooRealVar sigma3("sigma3","", 3.5);
    RooRealVar alpha3("alpha3","number of events in peak 3",areaStart,0, 150);
    RooGaussian peak3("peak3","peak distribution",tof,mu3,sigma3);
    // PDFs parameters for peak 4
    RooRealVar mu4("mu4","", peaks[4], peaks[4]-width, peaks[4]+width);
    RooRealVar sigma4("sigma4","", 3.5);
    RooRealVar alpha4("alpha4","number of events in peak 3",areaStart, 0, 75);
    RooGaussian peak4("peak4","peak distribution",tof,mu4,sigma4);
    // PDFs parameters for peak 5
    RooRealVar mu5("mu5","", peaks[5], peaks[5]-width, peaks[5]+width);
    RooRealVar sigma5("sigma5","", 3.5);
    RooRealVar alpha5("alpha5","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak5("peak5","peak distribution",tof,mu5,sigma5);
    // PDFs parameters for peak 6
    RooRealVar mu6("mu6","", peaks[6], peaks[6]-width, peaks[6]+width);
    RooRealVar sigma6("sigma6","", 3.5);
    RooRealVar alpha6("alpha6","number of events in peak 3",areaStart, 0, 300);
    RooGaussian peak6("peak6","peak distribution",tof,mu6,sigma6);
    // PDFs parameters for peak 7
    RooRealVar mu7("mu7","", peaks[7], peaks[7]-width, peaks[7]+width);
    RooRealVar sigma7("sigma7","", 3.5);
    RooRealVar alpha7("alpha7","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak7("peak7","peak distribution",tof,mu7,sigma7);
    // PDFs parameters for peak 8
    RooRealVar mu8("mu8","", peaks[8], peaks[8]-width, peaks[8]+width);
    RooRealVar sigma8("sigma8","", 3.5);
    RooRealVar alpha8("alpha8","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak8("peak8","peak distribution",tof,mu8,sigma8);
    // PDFs parameters for peak 9
    RooRealVar mu9("mu9","", peaks[9], peaks[9]-width, peaks[9]+width);
    RooRealVar sigma9("sigma9","", 3.5);
    RooRealVar alpha9("alpha9","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak9("peak9","peak distribution",tof,mu9,sigma9);
    // PDFs parameters for peak 10
    RooRealVar mu10("mu10","", peaks[10], peaks[10]-width, peaks[10]+width);
    RooRealVar sigma10("sigma105","", 3.5);
    RooRealVar alpha10("alpha10","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak10("peak10","peak distribution",tof,mu10,sigma10);
    // PDFs parameters for peak 11
    RooRealVar mu11("mu11","", peaks[11], peaks[11]-width, peaks[11]+width);
    RooRealVar sigma11("sigma11","", 3.5);
    RooRealVar alpha11("alpha11","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak11("peak11","peak distribution",tof,mu11,sigma11);
    // PDFs parameters for peak 12
    RooRealVar mu12("mu12","", peaks[12], peaks[12]-width, peaks[12]+width);
    RooRealVar sigma12("sigma12","", 3.5);
    RooRealVar alpha12("alpha12","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak12("peak12","peak distribution",tof,mu12,sigma12);
    // PDFs parameters for peak 13
    RooRealVar mu13("mu13","", peaks[13], peaks[13]-width, peaks[13]+width);
    RooRealVar sigma13("sigma13","", 3.5);
    RooRealVar alpha13("alpha13","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak13("peak13","peak distribution",tof,mu13,sigma13);
    // PDFs parameters for peak 14
    RooRealVar mu14("mu14","", peaks[14], peaks[14]-width, peaks[14]+width);
    RooRealVar sigma14("sigma14","", 3.5);
    RooRealVar alpha14("alpha14","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak14("peak14","peak distribution",tof,mu14,sigma14);
    // PDFs parameters for peak 15
    RooRealVar mu15("mu15","", peaks[15], peaks[15]-width, peaks[15]+width);
    RooRealVar sigma15("sigma15","", 3.5);
    RooRealVar alpha15("alpha15","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak15("peak15","peak distribution",tof,mu15,sigma15);
    // PDFs parameters for peak 16
    RooRealVar mu16("mu16","", peaks[16], peaks[16]-width, peaks[16]+width);
    RooRealVar sigma16("sigma16","", 3.5);
    RooRealVar alpha16("alpha16","number of events in peak 3",areaStart, 0, 100);
    RooGaussian peak16("peak16","peak distribution",tof,mu16,sigma16);
    // PDFs parameters for peak 17
    RooRealVar mu17("mu17","", peaks[17], peaks[17]-width, peaks[17]+width);
    RooRealVar sigma17("sigma17","", 3.5);
    RooRealVar alpha17("alpha17","number of events in peak 3",areaStart, 0, 50);
    RooGaussian peak17("peak17","peak distribution",tof,mu17,sigma17);
    // PDFs parameters for peak 18
    RooRealVar mu18("mu18","", peaks[18], peaks[18]-width, peaks[18]+width);
    RooRealVar sigma18("sigma18","", 3.5);
    RooRealVar alpha18("alpha18","number of events in peak 3",areaStart, 0, 50);
    RooGaussian peak18("peak18","peak distribution",tof,mu18,sigma18);

    // PDFs parameters for VANDLE
    //RooProdPdf npeak0("nPeak0", "vandleDist",tof, RooArgList(peak_1,bkg));
    
    RooArgList peakList(peak0,peak1,peak2,peak3,peak4,peak5,peak6,peak7, 
                        peak8);
    peakList.add(RooArgList(peak9,peak10,peak11,peak12,peak13,peak14,peak15,
                            peak16));
    peakList.add(RooArgList(peak17,peak18));
    RooArgList areaList(alpha0,alpha1,alpha2,alpha3,alpha4,alpha5,alpha6,
                     alpha7,alpha8);
    areaList.add(RooArgList(alpha9,alpha10,alpha11,alpha12,alpha13,alpha14,alpha15,
                         alpha16));
    areaList.add(RooArgList(alpha17,alpha18));

    /////////////////////////////////
    RooAddPdf model("model","model", peakList, areaList);
    RooFitResult* fitResult = model.fitTo(*data, NumCPU(3), Save());

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
