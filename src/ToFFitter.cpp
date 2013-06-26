#include <fstream>
#include <iostream>

#include <cstdio>

#include "ModelBuilder.hpp"
#include "ToFFitter.hpp"

using namespace std;

ToFFitter::ToFFitter(const double &low, const double &high)  {
    low_ = low;
    high_ = high;
}

void ToFFitter::LoadData(const std::string &dir, const std::string &file) {
    dataFile_ ="../data/roofit/"+dir+file+".dat";
    eps_ = "../pics/roofit/"+dir+file+".eps";
    output_ = "results/"+dir+file+".fit";
    
    ifstream test(dataFile_.c_str());
    if(test.fail()) {
        cout << "Holy fuck!!! We couldn't open the data file to read in the sexy data!!" << endl << endl;
        exit(1);
    }

    RooDataSet *data_ = RooDataSet::read(dataFile_.c_str(), RooArgList(tof_));
}

void ToFFitter::FitData(const RooArgList &peaks,
                        const RooArgList &yields) {
    // ModelBuilder builder(tof_, "peaks.in", wiggle_, detRes_);
    // RooAddPdf model = builder.BuildModel();
    
    // RooFitResult* fitResult = model.fitTo(*data_, NumCPU(3), Save(), 
    //                                       Range(low_, high_));

    // ofstream resultsParam(output_.c_str());
    // fitResult->printMultiline(resultsParam, 0, false, "");
    // resultsParam.close();
}
