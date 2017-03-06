{
    gROOT->Reset();

    TFile f("results/sim/working/sims.root","read");

    RooRealVar *tof = (RooRealVar*)f.Get("tof");
    RooDataSet *data = (RooDataSet*)f.Get("sim-data-1800");
    RooAddPdf *model = (RooAddPdf*)f.Get("sim-model-1800");
    RooAddPdf *conv = (RooAddPdf*)f.Get("conv-1800");
    RooPlot *frame = (RooPlot*)f.Get("frame");
    
    data->plotOn(frame);
    model->plotOn(frame);
    conv->plotOn(frame);

    frame->SetAxisRange(0,120,"X");
    frame->Draw();
}
