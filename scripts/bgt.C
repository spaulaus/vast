{
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
    bgtHigh->Draw("HIST");

    TH1D *bgt = (TH1D*)f.Get("bgt");
    bgt->SetLineWidth(2);
    bgt->SetLineColor(2002);
    bgt->Draw("HIST same");

    TH1D *bgtLow = (TH1D*)f.Get("bgtLow");
    bgtLow->SetFillColor(10);
    bgtLow->SetLineColor(10);
    bgtLow->Draw("HIST same");

    double maxRng = bgtHigh->GetMaximum();
    double minRng = bgtHigh->GetMinimum();
    TLine q(qvalue, minRng, qvalue, maxRng);
    q.Draw("same");
    TLine s(sn, minRng, sn, maxRng);
    s.Draw("same");

    gPad->RedrawAxis();
}
