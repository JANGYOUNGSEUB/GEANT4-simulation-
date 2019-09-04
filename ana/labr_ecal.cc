void labr_ecal()
{
	Double_t energy[5] = {121.77, 344.28, 661.7, 1117, 1330};
	Double_t resol[5] = {9.3, 5.1, 3.5, 2.7, 2.65};
	TGraph* graph = new TGraph(5, energy, resol);

	TCanvas* cvs = new TCanvas("cvs","", 1000,700);
	graph->Draw();
	graph->SetMarkerStyle(20);
	graph->SetLineWidth(0);

	TF1* exp = new TF1("exp", "[0]*exp(-x/[1])+[2]",0, 2000);
	exp->SetParameters(100, 500, 1);
	graph->Fit(exp, "M", "", 100, 1500);

	TFile* out = new TFile("labr_eresol.root", "RECREATE");
	out->cd();
	exp->Write();
	out->Close();


}
