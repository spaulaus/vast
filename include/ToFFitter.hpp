/** \file ToFFitter.hpp
 *
 *  A class to handle fitting the ToF spectra from VANDLE data
 *
 *  \author S. V. Paulauskas
 *  \date 24 June 2013
 *
 */
#ifndef __TOFFITTER_HPP__
#define __TOFFITTER_HPP__

#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGaussModel.h"
#include "RooMCStudy.h"
#include "RooNumConvPdf.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"

class ToFFitter {
public:
    ToFFitter();
    ToFFitter(const double &low, const double &high);
    ~ToFFitter();

    void FitData(const RooArgList &peaks,
                          const RooArgList &yields);

    void SetEpsName(const std::string &name) {eps_ = name;};
    void SetNumPeaks(const int &num) {numPeaks_ = num;};
    void SetResultsFile(const std::string &name) {output_ = name;};
private:
    void LoadData(const std::string &dir, const std::string &file);
        
    double low_, high_, wiggle_, detRes_;
    int numPeaks_;
    std::string eps_, output_, dataFile_;

    RooFitResult* result_;
    RooDataSet *data_;
    RooRealVar tof_;
}; //class ToFFitter
#endif //ifndef __TOFFITTER_HPP__
