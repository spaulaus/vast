#ifndef __CLING__
#incluce <iostream>
#include <fstream>

#include <TApplication.h>
#include <TFile.h>
#include <TStyle.h>
#include <TH1.h>
#include <TROOT.h>
#include <TPad.h>
#include <TLine.h>
#endif

void bgt(void){
#ifndef __CLING__
    TApplication app("app",0,0);
#endif

    gROOT->Reset();
    //show integral in stats box
    //gStyle->SetOptStat("i");
    //do not show stats box
    gStyle->SetOptStat(0);

    double qvalue = 10.49;
    double sn = 4.5575;

    TFile f("results/vast/working/bgt.root");

    TH1D *bgtHigh = (TH1D*)f.Get("bgtHigh");
    bgtHigh->SetFillColor(2022);
    bgtHigh->SetLineColor(2022);
    bgtHigh->SetAxisRange(4,11,"X");
    bgtHigh->DrawCopy("HIST");

    TH1D *bgt = (TH1D*)f.Get("bgt");
    bgt->SetLineWidth(2);
    bgt->SetLineColor(2002);
    bgt->DrawCopy("HIST same");

    // ofstream bgtout("077cu-bgt.dat");
    // if(bgtout.is_open()) {
    //     Int_t n = bgt->GetNbinsX();
    //     for (Int_t i = 1; i <= n; i++) {
    //         bgtout << bgt->GetBinLowEdge(i)+bgt->GetBinWidth(i)/2 << " " 
    //                << bgt->GetBinContent(i) << endl;
    //     }
    // }
    // bgtout.close();

    TH1D *bgtLow = (TH1D*)f.Get("bgtLow");
    bgtLow->SetFillColor(10);
    bgtLow->SetLineColor(10);
    bgtLow->DrawCopy("HIST same");

    double maxRng = bgtHigh->GetMaximum();
    double minRng = bgtHigh->GetMinimum();
    TLine *q = new TLine(qvalue, minRng, qvalue, maxRng);
    q->Draw("same");
    TLine *s = new TLine(sn, minRng, sn, maxRng);
    s->Draw("same");

    gPad->RedrawAxis();

    //c1->SaveAs("077cu-bgt.eps");

#ifndef __CLING__
    app.Run(kTRUE);
#endif
}

#ifndef __CLING__
int main(int argc, char**argv) {
    bgt();
    return 0;
}
#endif
