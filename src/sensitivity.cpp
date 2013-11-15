#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

#include "BGTCalculator.hpp"
#include "Decay.hpp"
#include "Integrator.hpp"
#include "LimitFinder.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"

using namespace std;

//---------- SET SOME DETAILS ABOUT THE EXP HERE ----------
//---------- HANDLE THIS BETTER LATER ----------
double numBars = 9;
Variable omega = Variable(numBars*0.0061,0.0,""); //solid angle from Sergey's sim
Variable betaEff = Variable(0.23, 0.03, "/100"); // the error needs recalculated.
pair<Variable,Variable> effs = make_pair(betaEff,omega);

int main() {
    //---------- SET THE DECAY INFORMATION HERE ---------
    //ParentZ, Q(MeV), Sn(MeV), Qbetan(MeV), T1/2(s)
    Variable q(10.490,0.500,"MeV"), sn(4.5575,0.00025,"MeV"),
        qbn(5.720,0.015,"MeV");
    Decay decay(Variable(29,0.0,""), q, sn, qbn,
                Variable(0.4679,0.00021, "s")); 
    //RawNumGammas, eff_gamma, absBr
    decay.SetGammaInfo(Variable(351222,14751.324,"counts"),
                       Variable(0.0668422,0.003,"/100"),
                       Variable(0.191, 0.006, "/100")); 


    ofstream out("results/vast/working/working.sens");
    out << setw(7) << "#Ex(MeV) BR BRerr B(GT) B(GT)err" << endl;
    for(double i = 0.1; i < q.GetValue()-sn.GetValue(); i += 0.1) {
        LimitFinder lim;
        Neutron n = lim.PerformFit(i, 10.);
        cout << n.GetRawYield().GetValue() << " " << endl;
        Integrator integrate(n,make_pair(0.,200.));
        BGTCalculator bgt(n,decay,betaEff,omega);
        
        out << n.GetExcitationEnergy().GetValue() << " " 
            << n.GetBranchingRatio().GetValue() << " " 
            << n.GetBranchingRatio().GetError() << " " 
            << n.GetBgt().GetValue() << " " 
            << n.GetBgt().GetError() << endl;
    }
    out.close();
}
