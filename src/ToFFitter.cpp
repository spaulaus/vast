#include <fstream>
#include <iostream>

#include <cstdio>

#include "ModelBuilder.hpp"
#include "ToFFitter.hpp"

using namespace std;
using namespace RooFit;

ToFFitting::ToFFitting(const double &low, const double &high)  {
    low_ = low;
    high_ = high;
    tof_.setRange(low,high);
}

void ToFFitting::LoadData(const std::string &dir, const std::string &file) {
    dataFile_ ="../data/roofit/"+dirName+fileName+".dat";
    eps_ = "../pics/roofit/"+dirName+fileName+".eps";
    output_ = "results/"+dirName+fileName+".fit";
    
    ifstream test(dataName_.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the data file to read in the sexy data!!" << endl << endl;
        exit(1);
    }

    data_ = RooDataSet::read(dataName_.c_str(), RooArgList(tof));
}

void ToFFitter::FitData(const RooArgList &peaks,
                        const RooArgList &yields) {
    LoadData();
    
    ModelBuilder builder(tof_, "peaks.in", wiggle_, detRes_);
    RooAddPdf model = builder.BuildModel();
    
    RooFitResult* fitResult = model.fitTo(*data_, NumCPU(3), Save(), 
                                          Range(low_, high_));

    ofstream resultsParam(resultsFile_.c_str());
    fitResult->printMultiline(resultsParam, 0, false, "");
    resultsParam.close();
}
