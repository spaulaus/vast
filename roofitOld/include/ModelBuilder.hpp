#ifndef __MODELBUILDER_HPP__
#define __MODELBUILDER_HPP__

#include <vector>

#include <RooAddPdf.h>
#include <RooArgList.h>

#include "ToFFitter.hpp"

class ModelBuilder {
public:
    ModelBuilder(const RooRealVar &tof, const std::string &file, 
                 const int &wiggle, const int &detRes);
    ~ModelBuilder(){};

    RooAddPdf BuildModel(void);
private:
    RooRealVar tof_;
    double wiggle_, detRes_;
    RooArgList peaks_, yields_;
    unsigned int numPeaks_;
    std::vector<double> pks_;
};

#endif //#ifndef __MODELBUILDER_HPP__
