#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include <cmath>
#include "time.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<double> tof,counts, results;
    double temp1, temp2;
    //read in the datafile
    ifstream data(argv[1]);
    if(data.is_open()) {
        while(data.good()) {
            data >> temp1 >> temp2;
            tof.push_back(temp1);
            counts.push_back(temp2);
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

    for(unsigned int i = 0; i < results.size(); i++)
        cout << results[i] << endl;
}
