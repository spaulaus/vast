{
    gROOT->Reset();
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);

    double qvalue = 10.49;
    double sn = 4.5575;
    
    TFile f("results/vast/working/bgt.root");
    TGraphAsymmErrors *g = (TGraphAsymmErrors*)f.Get("Graph");
    g->Draw("AL");
    // TH1D *bgt = (TH1D*)f.Get("bgt");
    // bgt->Draw();
    // TH1D *bgtLow = (TH1D*)f.Get("bgtLow");
    // TH1D *bgtHigh = (TH1D*)f.Get("bgtHigh");
    
    
    // bgtLow->Draw("HIST same");
    // bgtHigh->Draw("HIST same");

    double maxRng = bgt->GetYaxis()->GetXmax();
    double minRng = bgt->GetYaxis()->GetXmin();
    TLine q(qvalue, minRng, qvalue, maxRng);
    q.Draw("same");
    TLine s(sn, minRng, sn, maxRng);
    s.Draw("same");
}
