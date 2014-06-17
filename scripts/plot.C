{
    gROOT->Reset();

    TFile f("sims.root","read");
    TCanvas *c0 = (TCanvas*)f.Get("sim3000");
    TCanvas *c1 = (TCanvas*)f.Get("sim1200");
    TCanvas *c3 = new TCanvas("c3","",0,0,500,700);
    TCanvas *c4 = new TCanvas("c4","",0,0,500,700);
    c3 = c0; c4 = c1;
    c3->Draw();
    c4->Draw();
}
