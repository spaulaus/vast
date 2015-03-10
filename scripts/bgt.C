{
    gROOT->Reset();

    //show integral in stats box
    //gStyle->SetOptStat("i");
    //do not show stats box
    gStyle->SetOptStat(0);
    
    gStyle->SetErrorX(0);

    double qvalue = 10.49;
    double sn = 4.5575;
    
    TFile f("results/vast/working/bgt.root");
    //TGraphAsymmErrors *g = (TGraphAsymmErrors*)f.Get("Graph");
    //g->Draw("AL");

    TH1D *bgtHigh = (TH1D*)f.Get("bgtHigh");
    bgtHigh->SetFillColor(2022);
    bgtHigh->SetLineColor(2022);
    //bgtHigh->SetAxisRange(6.8,8.8,"X");
    bgtHigh->Draw("HIST");

    TH1D *bgt = (TH1D*)f.Get("bgt");
    //bgt->SetLineWidth(3);
    //bgt->SetLineColor(2002);
    bgt->Draw("HIST same");

    TH1D *bgtLow = (TH1D*)f.Get("bgtLow");
    bgtLow->SetFillColor(10);
    bgtLow->SetLineColor(10);
    bgtLow->Draw("HIST same");

    gPad->RedrawAxis();

    double maxRng = bgt->GetYaxis()->GetXmax();
    double minRng = bgt->GetYaxis()->GetXmin();
    TLine q(qvalue, minRng, qvalue, maxRng);
    q.Draw("same");
    TLine s(sn, minRng, sn, maxRng);
    s.Draw("same");
}
