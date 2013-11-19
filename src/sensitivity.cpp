#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "BGTCalculator.hpp"
#include "Decay.hpp"
#include "Integrator.hpp"
#include "LimitFinder.hpp"
#include "Neutron.hpp"
#include "NeutronDensity.hpp"

using namespace std;

int main() {
//---------- SET SOME DETAILS ABOUT THE EXP HERE ----------
//---------- HANDLE THIS BETTER LATER ----------
    double numBars = 9;
    Variable omega = Variable(numBars*0.0061,0.0,""); 
    
    //---------- For the 84Ga decay ---------
    // Variable betaEff = Variable(0.13, 0.03, "/100"); // 84ga
    // Variable q(13.690,0.500,"MeV"), sn(5.243,0.004,"MeV"),
    //     qbn(8.60,0.004,"MeV");
    // Decay decay(Variable(31,0.0,""),q,sn,qbn, Variable(0.085,0.01, "s")); 
    // //RawNumGammas, eff_gamma, absBr
    // decay.SetGammaInfo(Variable(7208,0.0,"counts"),
    //                    Variable(0.122882,0.00,"/100"),
    //                    Variable(0.086, 0.0, "/100"));
    
    //---------- For the 78cu Decay ---------
    // Variable betaEff = Variable(0.43, 0.03, "/100"); // 78cu
    // Variable q(12.990,0.500,"MeV"), sn(6.765,0.003,"MeV"),
    //     qbn(6.22,0.5,"MeV");
    // //ParentZ, Q(MeV), Sn(MeV), Qbetan(MeV), T1/2(s)
    // Decay decay(Variable(29,0.0,""),q,sn,qbn, Variable(0.335,0.011, "s")); 
    // //RawNumGammas, eff_gamma, absBr
    // //this info is taken from the 115 keV line associated with the 77Zn->77Ga decay
    // decay.SetGammaInfo(Variable(13394,0.0,"counts"),
    //                    Variable(0.214579,0.0122841,"/100"),
    //                    Variable(0.281, 0.00, "/100")); 
    
    //---------- For the 77cu Decay ----------
    Variable betaEff = Variable(0.23, 0.03, "/100"); // 77cu
    //ParentZ, Q(MeV), Sn(MeV), Qbetan(MeV), T1/2(s)
    Variable q(10.490,0.500,"MeV"), sn(4.5575,0.00025,"MeV"),
        qbn(5.720,0.015,"MeV");
    Decay decay(Variable(29,0.0,""),q,sn,qbn,Variable(0.4679,0.00021, "s")); 
    //RawNumGammas, eff_gamma, absBr
    decay.SetGammaInfo(Variable(351222,14751.324,"counts"),
                       Variable(0.0668422,0.003,"/100"),
                       Variable(0.191, 0.006, "/100")); 

    ofstream out("results/vast/working/working.sens");
    out << setw(7) << "#Ex(MeV) BR BRerr B(GT) B(GT)err" << endl;
    for(double i = 0.1; i < q.GetValue()-sn.GetValue(); i += 0.1) {
        LimitFinder lim;
        Neutron n = lim.PerformFit(i, 10.);
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
