#include <fstream>
#include <iostream>
#include <string>

#include "RooCBShape.h"
#include "RooFFTConvPdf.h"
#include "RooFormulaVar.h"
#include "RooGaussModel.h"
#include "RooRealVar.h"

#include "ModelBuilder.hpp"

using namespace std;

ModelBuilder::ModelBuilder(const RooRealVar &tof, const string &file, 
                           const int &wiggle, const int &detRes) {
    wiggle_ = wiggle;
    detRes_ = detRes;

    ifstream input(file.c_str());
    if(!input) {
        cout << "We could not open the file containing the peak list, correct this."
             << endl << endl;
        exit(2);
    }else {
        cout << "Reading in the peaks to do the fitting on." << endl;
        while(input) {
            double temp;
            input >> temp;
            if(pks_.size() > 0 && pks_.back() == temp)
                continue;
            pks_.push_back(temp);
        }
    }
    numPeaks_ = pks_.size();
    while(pks_.size() != 20)
        pks_.push_back(0.0);
}

RooAddPdf ModelBuilder::BuildModel(void) {
    double yStart = 3.e3, yLow = 0., yHigh = 1.e8;
    
    //Set the information for the resolution model
    RooRealVar res("res", "res for gauss model", detRes_ / (2*sqrt(2*log(2))));
    RooRealVar x("x", "mean for gauss model", 0.0);

    //Parameterization Parameters for Sigma -> sM*mu + sB
    RooRealVar sM("sM","Slope for sigma para.", 0.0264412131874119);
    RooRealVar sB("sB","Intercept for sigma para.", 0.0432494943386515);

    //Parameterization Parameters for Alpha -> aM/mu + aB
    RooRealVar aM("aM","Scale for alpha para.", -9.53022215447638);
    RooRealVar aB("aB","Intercept for alpha para.", -0.357060159281673);

    //Parameterization Parameters for N -> nM/mu + nB
    RooRealVar nM("nM","Scale for n para.", -5.99204241877324);
    RooRealVar nB("nB","Intercept for n para.", 1.25859614260662);

    //---------- Peak Number 0 ----------
    RooRealVar yield00("yield00", "", yStart, yLow, yHigh);
    RooRealVar mu00("mu00","", pks_[0], pks_[0]-wiggle_, pks_[0]+wiggle_);
    RooFormulaVar sigma00("sigma00", "sM*mu00+sB", RooArgList(sM,mu00,sB));
    RooFormulaVar alpha00("alpha00", "aM/mu00+aB", RooArgList(aM,mu00,sB));
    RooFormulaVar n00("n00", "nM/mu00+nB", RooArgList(nM,mu00,nB));
    RooCBShape cb00("cb00", "", tof_, mu00, sigma00, alpha00, n00);
    
    RooGaussModel res00("res00", "", tof_, x, res);
    RooFFTConvPdf pk00("pk00","",tof_,cb00,res00);
    
    //---------- Peak Number 1 ----------
    RooRealVar yield01("yield01", "", yStart, yLow, yHigh);
    RooRealVar mu01("mu01","", pks_[1], pks_[1]-wiggle_, pks_[1]+wiggle_);
    RooFormulaVar sigma01("sigma01", "sM*mu01+sB", RooArgList(sM,mu01,sB));
    RooFormulaVar alpha01("alpha01", "aM/mu01+aB", RooArgList(aM,mu01,sB));
    RooFormulaVar n01("n01", "nM/mu01+nB", RooArgList(nM,mu01,nB));
    RooCBShape cb01("cb01", "", tof_, mu01, sigma01, alpha01, n01);
    
    RooGaussModel res01("res01", "", tof_, x, res);
    RooFFTConvPdf pk01("pk01","",tof_,cb01,res01);
    
    //---------- Peak Number 2 ----------
    RooRealVar yield02("yield02", "", yStart, yLow, yHigh);
    RooRealVar mu02("mu02","", pks_[2], pks_[2]-wiggle_,pks_[2]+wiggle_);
    RooFormulaVar sigma02("sigma02", "sM*mu02+sB", RooArgList(sM,mu02,sB));
    RooFormulaVar alpha02("alpha02", "aM/mu02+aB", RooArgList(aM,mu02,sB));
    RooFormulaVar n02("n02", "nM/mu02+nB", RooArgList(nM,mu02,nB));
    RooCBShape cb02("cb02", "", tof_, mu02, sigma02, alpha02, n02);
    
    RooGaussModel res02("res02", "", tof_, x, res);
    RooFFTConvPdf pk02("pk02","",tof_,cb02,res02);
    
    //---------- Peak Number 3 ----------
    RooRealVar yield03("yield03", "", yStart, yLow, yHigh);
    RooRealVar mu03("mu03","", pks_[3], pks_[3]-wiggle_, pks_[3]+wiggle_);
    RooFormulaVar sigma03("sigma03", "sM*mu03+sB", RooArgList(sM,mu03,sB));
    RooFormulaVar alpha03("alpha03", "aM/mu03+aB", RooArgList(aM,mu03,sB));
    RooFormulaVar n03("n03", "nM/mu03+nB", RooArgList(nM,mu03,nB));
    RooCBShape cb03("cb03", "", tof_, mu03, sigma03, alpha03, n03);
    
    RooGaussModel res03("res03", "", tof_, x, res);
    RooFFTConvPdf pk03("pk03","",tof_,cb03,res03);
    
    //---------- Peak Number 4 ----------
    RooRealVar yield04("yield04", "", yStart, yLow, yHigh);
    RooRealVar mu04("mu04","", pks_[4], pks_[4]-wiggle_, pks_[4]+wiggle_);
    RooFormulaVar sigma04("sigma04", "sM*mu04+sB", RooArgList(sM,mu04,sB));
    RooFormulaVar alpha04("alpha04", "aM/mu04+aB", RooArgList(aM,mu04,sB));
    RooFormulaVar n04("n04", "nM/mu04+nB", RooArgList(nM,mu04,nB));
    RooCBShape cb04("cb04", "", tof_, mu04, sigma04, alpha04, n04);
    
    RooGaussModel res04("res04", "", tof_, x, res);
    RooFFTConvPdf pk04("pk04","",tof_,cb04,res04);
    
    //---------- Peak Number 5 ----------
    RooRealVar yield05("yield05", "", yStart, yLow, yHigh);
    RooRealVar mu05("mu05","", pks_[5], pks_[5]-wiggle_, pks_[5]+wiggle_);
    RooFormulaVar sigma05("sigma05", "sM*mu05+sB", RooArgList(sM,mu05,sB));
    RooFormulaVar alpha05("alpha05", "aM/mu05+aB", RooArgList(aM,mu05,sB));
    RooFormulaVar n05("n05", "nM/mu05+nB", RooArgList(nM,mu05,nB));
    RooCBShape cb05("cb05", "", tof_, mu05, sigma05, alpha05, n05);
    
    RooGaussModel res05("res05", "", tof_, x, res);
    RooFFTConvPdf pk05("pk05","",tof_,cb05,res05);
    
    //---------- Peak Number 6 ----------
    RooRealVar yield06("yield06", "", yStart, yLow, yHigh);
    RooRealVar mu06("mu06","", pks_[6], pks_[6]-wiggle_, pks_[6]+wiggle_);
    RooFormulaVar sigma06("sigma06", "sM*mu06+sB", RooArgList(sM,mu06,sB));
    RooFormulaVar alpha06("alpha06", "aM/mu06+aB", RooArgList(aM,mu06,sB));
    RooFormulaVar n06("n06", "nM/mu06+nB", RooArgList(nM,mu06,nB));
    RooCBShape cb06("cb06", "", tof_, mu06, sigma06, alpha06, n06);
    
    RooGaussModel res06("res06", "", tof_, x, res);
    RooFFTConvPdf pk06("pk06","",tof_,cb06,res06);
    
    //---------- Peak Number 7 ----------
    RooRealVar yield07("yield07", "", yStart, yLow, yHigh);
    RooRealVar mu07("mu07","", pks_[7], pks_[7]-wiggle_, pks_[7]+wiggle_);
    RooFormulaVar sigma07("sigma07", "sM*mu07+sB", RooArgList(sM,mu07,sB));
    RooFormulaVar alpha07("alpha07", "aM/mu07+aB", RooArgList(aM,mu07,sB));
    RooFormulaVar n07("n07", "nM/mu07+nB", RooArgList(nM,mu07,nB));
    RooCBShape cb07("cb07", "", tof_, mu07, sigma07, alpha07, n07);
    
    RooGaussModel res07("res07", "", tof_, x, res);
    RooFFTConvPdf pk07("pk07","",tof_,cb07,res07);
    
    //---------- Peak Number 8 ----------
    RooRealVar yield08("yield08", "", yStart, yLow, yHigh);
    RooRealVar mu08("mu08","", pks_[8], pks_[8]-wiggle_, pks_[8]+wiggle_);
    RooFormulaVar sigma08("sigma08", "sM*mu08+sB", RooArgList(sM,mu08,sB));
    RooFormulaVar alpha08("alpha08", "aM/mu08+aB", RooArgList(aM,mu08,sB));
    RooFormulaVar n08("n08", "nM/mu08+nB", RooArgList(nM,mu08,nB));
    RooCBShape cb08("cb08", "", tof_, mu08, sigma08, alpha08, n08);
    
    RooGaussModel res08("res08", "", tof_, x, res);
    RooFFTConvPdf pk08("pk08","",tof_,cb08,res08);
    
    //---------- Peak Number 9 ----------
    RooRealVar yield09("yield09", "", yStart, yLow, yHigh);
    RooRealVar mu09("mu09","", pks_[9], pks_[9]-wiggle_, pks_[9]+wiggle_);
    RooFormulaVar sigma09("sigma09", "sM*mu09+sB", RooArgList(sM,mu09,sB));
    RooFormulaVar alpha09("alpha09", "aM/mu09+aB", RooArgList(aM,mu09,sB));
    RooFormulaVar n09("n09", "nM/mu09+nB", RooArgList(nM,mu09,nB));
    RooCBShape cb09("cb09", "", tof_, mu09, sigma09, alpha09, n09);
    
    RooGaussModel res09("res09", "", tof_, x, res);
    RooFFTConvPdf pk09("pk09","",tof_,cb09,res09);
    
    //---------- Peak Number 10 ----------
    RooRealVar yield10("yield10", "", yStart, yLow, yHigh);
    RooRealVar mu10("mu10","", pks_[10], pks_[10]-wiggle_, pks_[10]+wiggle_);
    RooFormulaVar sigma10("sigma10", "sM*mu10+sB", RooArgList(sM,mu10,sB));
    RooFormulaVar alpha10("alpha10", "aM/mu10+aB", RooArgList(aM,mu10,sB));
    RooFormulaVar n10("n10", "nM/mu10+nB", RooArgList(nM,mu10,nB));
    RooCBShape cb10("cb10", "", tof_, mu10, sigma10, alpha10, n10);
    
    RooGaussModel res10("res10", "", tof_, x, res);
    RooFFTConvPdf pk10("pk10","",tof_,cb10,res10);
    
    //---------- Peak Number 11 ----------
    RooRealVar yield11("yield11", "", yStart, yLow, yHigh);
    RooRealVar mu11("mu11","", pks_[11], pks_[11]-wiggle_, pks_[11]+wiggle_);
    RooFormulaVar sigma11("sigma11", "sM*mu11+sB", RooArgList(sM,mu11,sB));
    RooFormulaVar alpha11("alpha11", "aM/mu11+aB", RooArgList(aM,mu11,sB));
    RooFormulaVar n11("n11", "nM/mu11+nB", RooArgList(nM,mu11,nB));
    RooCBShape cb11("cb11", "", tof_, mu11, sigma11, alpha11, n11);
    
    RooGaussModel res11("res11", "", tof_, x, res);
    RooFFTConvPdf pk11("pk11","",tof_,cb11,res11);
    
    //---------- Peak Number 12 ----------
    RooRealVar yield12("yield12", "", yStart, yLow, yHigh);
    RooRealVar mu12("mu12","", pks_[12], pks_[12]-wiggle_, pks_[12]+wiggle_);
    RooFormulaVar sigma12("sigma12", "sM*mu12+sB", RooArgList(sM,mu12,sB));
    RooFormulaVar alpha12("alpha12", "aM/mu12+aB", RooArgList(aM,mu12,sB));
    RooFormulaVar n12("n12", "nM/mu12+nB", RooArgList(nM,mu12,nB));
    RooCBShape cb12("cb12", "", tof_, mu12, sigma12, alpha12, n12);
    
    RooGaussModel res12("res12", "", tof_, x, res);
    RooFFTConvPdf pk12("pk12","",tof_,cb12,res12);
    
    //---------- Peak Number 13 ----------
    RooRealVar yield13("yield13", "", yStart, yLow, yHigh);
    RooRealVar mu13("mu13","", pks_[13], pks_[13]-wiggle_, pks_[13]+wiggle_);
    RooFormulaVar sigma13("sigma13", "sM*mu13+sB", RooArgList(sM,mu13,sB));
    RooFormulaVar alpha13("alpha13", "aM/mu13+aB", RooArgList(aM,mu13,sB));
    RooFormulaVar n13("n13", "nM/mu13+nB", RooArgList(nM,mu13,nB));
    RooCBShape cb13("cb13", "", tof_, mu13, sigma13, alpha13, n13);
    
    RooGaussModel res13("res13", "", tof_, x, res);
    RooFFTConvPdf pk13("pk13","",tof_,cb13,res13);
    
    //---------- Peak Number 14 ----------
    RooRealVar yield14("yield14", "", yStart, yLow, yHigh);
    RooRealVar mu14("mu14","", pks_[14], pks_[14]-wiggle_, pks_[14]+wiggle_);
    RooFormulaVar sigma14("sigma14", "sM*mu14+sB", RooArgList(sM,mu14,sB));
    RooFormulaVar alpha14("alpha14", "aM/mu14+aB", RooArgList(aM,mu14,sB));
    RooFormulaVar n14("n14", "nM/mu14+nB", RooArgList(nM,mu14,nB));
    RooCBShape cb14("cb14", "", tof_, mu14, sigma14, alpha14, n14);
    
    RooGaussModel res14("res14", "", tof_, x, res);
    RooFFTConvPdf pk14("pk14","",tof_,cb14,res14);
    
    //---------- Peak Number 15 ----------
    RooRealVar yield15("yield15", "", yStart, yLow, yHigh);
    RooRealVar mu15("mu15","", pks_[15], pks_[15]-wiggle_, pks_[15]+wiggle_);
    RooFormulaVar sigma15("sigma15", "sM*mu15+sB", RooArgList(sM,mu15,sB));
    RooFormulaVar alpha15("alpha15", "aM/mu15+aB", RooArgList(aM,mu15,sB));
    RooFormulaVar n15("n15", "nM/mu15+nB", RooArgList(nM,mu15,nB));
    RooCBShape cb15("cb15", "", tof_, mu15, sigma15, alpha15, n15);
    
    RooGaussModel res15("res15", "", tof_, x, res);
    RooFFTConvPdf pk15("pk15","",tof_,cb15,res15);
    
    //---------- Peak Number 16 ----------
    RooRealVar yield16("yield16", "", yStart, yLow, yHigh);
    RooRealVar mu16("mu16","", pks_[16], pks_[16]-wiggle_, pks_[16]+wiggle_);
    RooFormulaVar sigma16("sigma16", "sM*mu16+sB", RooArgList(sM,mu16,sB));
    RooFormulaVar alpha16("alpha16", "aM/mu16+aB", RooArgList(aM,mu16,sB));
    RooFormulaVar n16("n16", "nM/mu16+nB", RooArgList(nM,mu16,nB));
    RooCBShape cb16("cb16", "", tof_, mu16, sigma16, alpha16, n16);
    
    RooGaussModel res16("res16", "", tof_, x, res);
    RooFFTConvPdf pk16("pk16","",tof_,cb16,res16);
    
    //---------- Peak Number 17 ----------
    RooRealVar yield17("yield17", "", yStart, yLow, yHigh);
    RooRealVar mu17("mu17","", pks_[17], pks_[17]-wiggle_, pks_[17]+wiggle_);
    RooFormulaVar sigma17("sigma17", "sM*mu17+sB", RooArgList(sM,mu17,sB));
    RooFormulaVar alpha17("alpha17", "aM/mu17+aB", RooArgList(aM,mu17,sB));
    RooFormulaVar n17("n17", "nM/mu17+nB", RooArgList(nM,mu17,nB));
    RooCBShape cb17("cb17", "", tof_, mu17, sigma17, alpha17, n17);
    
    RooGaussModel res17("res17", "", tof_, x, res);
    RooFFTConvPdf pk17("pk17","",tof_,cb17,res17);
    
    //---------- Peak Number 18 ----------
    RooRealVar yield18("yield18", "", yStart, yLow, yHigh);
    RooRealVar mu18("mu18","", pks_[18], pks_[18]-wiggle_, pks_[18]+wiggle_);
    RooFormulaVar sigma18("sigma18", "sM*mu18+sB", RooArgList(sM,mu18,sB));
    RooFormulaVar alpha18("alpha18", "aM/mu18+aB", RooArgList(aM,mu18,sB));
    RooFormulaVar n18("n18", "nM/mu18+nB", RooArgList(nM,mu18,nB));
    RooCBShape cb18("cb18", "", tof_, mu18, sigma18, alpha18, n18);
    
    RooGaussModel res18("res18", "", tof_, x, res);
    RooFFTConvPdf pk18("pk18","",tof_,cb18,res18);

    //---------- Peak Number 19 ----------
    RooRealVar yield19("yield19", "", yStart, yLow, yHigh);
    RooRealVar mu19("mu19","", pks_[19], pks_[19]-wiggle_, pks_[19]+wiggle_);
    RooFormulaVar sigma19("sigma19", "sM*mu19+sB", RooArgList(sM,mu19,sB));
    RooFormulaVar alpha19("alpha19", "aM/mu19+aB", RooArgList(aM,mu19,sB));
    RooFormulaVar n19("n19", "nM/mu19+nB", RooArgList(nM,mu19,nB));
    RooCBShape cb19("cb19", "", tof_, mu19, sigma19, alpha19, n19);
    
    RooGaussModel res19("res19", "", tof_, x, res);
    RooFFTConvPdf pk19("pk19","",tof_,cb19,res19);

    //Container for all of the peaks
    RooArgList pkHolder(pk00,pk01,pk02,pk03,pk04,pk05,pk06,pk07,pk08);
    pkHolder.add(RooArgList(pk09,pk10,pk11,pk12,pk13,pk14,pk15,pk16,pk17));
    pkHolder.add(RooArgList(pk18,pk19));

    //Container for all of the yields
    RooArgList yieldHolder(yield00,yield01,yield02,yield03,yield04,
                           yield05,yield06,yield07,yield08);
    yieldHolder.add(RooArgList(yield09,yield10,yield11,yield12,yield13,
                               yield14,yield15,yield16,yield17));
    yieldHolder.add(RooArgList(yield18,yield19));

    //Pick out just the ones we want
    for(unsigned int i = 0; i < numPeaks_; i++) {
        peaks_.add(pkHolder[i]);
        yields_.add(yieldHolder[i]);
    }

    RooAddPdf model("model", "", peaks_, yields_);
    return(model);
}
