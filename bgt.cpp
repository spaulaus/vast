#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include <cmath>

#include <PhysConstants.hpp>

using namespace std;

vector<double> mu, area, muErr;

//********** MAGIC NUMBERS **********
double sn = 4558, q = 10490, z = 30, betaEff = 0.22;
double numBeta = 350311/0.0655391/0.191; //taken from logbook
double t = 0.4679; // in units of seconds
double numBars = 10;
double omega = numBars * 4.727e-3;
double coeff = 3812.413; //this is D/(ga/gv)**2 in units of seconds

double CalcErrEnergy(const unsigned int &i, const double &en) {
    double thk = 3, dist = 50.5;

    double timeComp = pow(2*muErr[i]/mu[i], 2);
    double physComp = pow(2*thk/dist,2);

    return( en * sqrt(timeComp+physComp) );
}

void ReadData(const string &file) {
    mu.clear(); area.clear();
    ifstream data(file.c_str());
    if(data.is_open()) {
        while(data.good()) {
            if(isdigit(data.peek())) {
                double junk, temp, temp1, temp2;
                data >> junk >> temp >> temp2 >> temp1 >> junk >> junk;
                mu.push_back(temp);
                area.push_back(temp1);
                muErr.push_back(temp2);
            }else {
                data.ignore(1000,'\n');
            }
        }
    }
    data.close();
}

double CalcEff(const double &energy) {
    //Taken from cf1200VLG/000.fit - uses keV
    // double a,b,c,d,e,f,g,E1,E2;
    // a = 8.07991379590916;
    // b = -2.76506346801857;
    // c = 0.659153868962284;
    // d = 5.90882582548888;
    // e = -0.64468269369943;
    // f = -0.395030757008049;
    // g = 1.73807042912493;
    // E1= 150.0;
    // E2 = 1000.0;
    // double x = log(energy/E1);
    // double y = log(energy/E2);                     
    
    // return((exp(pow(pow(a+b*x+c*x*x,-g) + 
    //                 pow(d+e*y+f*y*y,-g), -1/g)))/100);

    //From Sergey's eff_var_thresh
    return((52349.3/(energy+572.064)+5.17822)/100.);
}

double CalcBr(const double &area, const double &energy) { 
    return(area / CalcEff(energy) / numBeta / omega / betaEff);
}

double CalcEnergy(const double &time) {
    PhysConstants consts;
    double c  = consts.GetConstant("c").GetValue()*(100/1e9); // cm / ns
    double mn = consts.GetConstant("neutronMass").GetValue()/c/c; // MeV
    return(0.5*mn*pow(50.5/time,2.)*1000); // keV
}

double CalcF(const double &energy) {
    double betaEp = q - (energy + sn);

    double coeff[4][4] = { {-17.2, 7.9015, -2.54, 0.28482,}, 
                           {3.31368, -2.06273, 0.703822, -0.075039,}, 
                           {-0.364018, 0.387961, -0.142528, 0.016,},
                           {0.0278071, -0.026519, 0.0098854, -0.00113772} };
    
    double evalCoeff[4];
    for(int i = 0; i < 4; i++) {
        evalCoeff[i] = coeff[i][0] + log(z) * coeff[i][1] + 
            coeff[i][2]*pow(log(z),2.) + coeff[i][3]*pow(log(z),3.);
    }
    
    double logf = evalCoeff[0] + evalCoeff[1]*log(betaEp) + 
        evalCoeff[2]*pow(log(betaEp),2.) + evalCoeff[3]*pow(log(betaEp),3.);

    return(pow(10,logf));
}

int main() {
    vector<string> inFiles;
    inFiles.push_back("data/077cu-ban4-lower/077cu-ban4-lower-tof.out");
    inFiles.push_back("data/077cu-ban4-lower/077cu-ban4-lower-tof-02Plus.out");
    inFiles.push_back("data/077cu-ban4-lower/077cu-ban4-lower-tof-04Plus.out");

    vector<string> outFiles;
    outFiles.push_back("results/077cu-ban4-lower.dat");
    outFiles.push_back("results/077cu-ban4-lower-02Plus.dat");
    outFiles.push_back("results/077cu-ban4-lower-04Plus.dat");

    for(unsigned int i = 0; i < inFiles.size(); i++) {
        ReadData(inFiles.at(i));
        ofstream output(outFiles.at(i).c_str());
        
        double totN = 0, rawTotN = 0;
        output << "#En+Sn(MeV) errEn(MeV)   B(GT)(1/MeV)   log(ft)    "
               << "yield/gamma-eff/n-eff" << endl;

        for(unsigned int j = 0; j < mu.size(); j++) {
            double en = CalcEnergy(mu[j]); //in keV
            double br = CalcBr(area[j],en);
            double f = CalcF(en);
            double bgt = coeff/f/(t/br);
            double logft = log10(f*(t/br));
            double eff = CalcEff(en);
            totN += area[j]/eff;
            rawTotN += area[j];
            double eOut = (en+sn)/1000.;
            
            if(i==0)
                output << eOut <<  "     ";
            else if(i==1)
                output << eOut+0.59856 <<  "     ";
            else if(i==2)
                output << eOut+0.59856+0.69772 <<   "     ";
            output << CalcErrEnergy(j,en)/1000. << "    " << bgt << "    " 
                   << logft  << "     ";
            if(i == 0)
                output << area[j]/eff << endl;
            else if(i == 1)
                output << area[j]/0.0566419/eff << endl;
            else if(i == 2)
                output << area[j]/0.0497657/eff << endl;
        }
        output << "#Pn is " << totN / numBeta / betaEff / omega 
               << "  Ntot = " << totN << "   Raw Ntot = " << rawTotN << endl;
    }
}
