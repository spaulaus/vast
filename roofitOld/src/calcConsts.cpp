#include <fstream>
#include <iostream>

#include <cmath>
#include <cstdlib>

using namespace std;

double CalcSigma(const double &val) {
    double m = 0.0288026438611703;
    double b = -0.0413372812483731;
    return(m*val+b);
}

double CalcConvSigma(const double &val){
    double betaRes = 4.04/(2*sqrt(2*log(2)));
    double simRes = CalcSigma(val);
    return(sqrt(pow(simRes,2)+pow(betaRes,2)));
}

double CalcAlpha(const double &val) {
    double m = -5.66309545261006;
    double b = -0.408753253930762;
    return(m/val+b);
}

double CalcN(const double &val) {
    double m = -4.53373119793572;
    double b = 1.3468761986679;
    return(m/val+b);
}


int main(int argc, char* argv[]){
    double peaks[]={23.855, 30.196, 38.128, 44.917, 
                    50.181, 56.835, 65.151, 70.826,
                    79.253, 87.198, 94.690, 104.69, 
                    112.73, 135.93};
    
    cout << "#ToF(ns) Sigma  ConvSigma   Alpha   N" << endl;
    for(int i = 0; i < 14; i++)
        cout << peaks [i] << " " 
             << CalcSigma(peaks[i]) << " " 
             << CalcConvSigma(peaks[i]) << " " 
             << CalcAlpha(peaks[i]) << " " 
             << CalcN(peaks[i]) << endl;
}
