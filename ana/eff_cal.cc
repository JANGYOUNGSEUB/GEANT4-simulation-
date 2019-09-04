void eff_cal()
{
	gStyle -> SetPadLeftMargin(0.14);
	gStyle -> SetPadRightMargin(0.02);
	gStyle -> SetPadTopMargin(0.02);
	gStyle -> SetPadBottomMargin(0.15);
	gStyle -> SetTitleOffset(0.92, "x");
	gStyle -> SetTitleOffset(0.8, "y");
	gStyle -> SetTitleOffset(1.05, "z");
	gStyle -> SetTextFont(132);
	gStyle -> SetTextSize(0.070);
	gStyle -> SetTitleSize(0.07, "x");
	gStyle -> SetTitleSize(0.07, "y");
	gStyle -> SetTitleSize(0.08, "z");
	gStyle -> SetLabelSize(0.07, "x");
	gStyle -> SetLabelSize(0.07, "y");
	gStyle -> SetLabelSize(0.08, "z");
	gStyle -> SetTitleFont(132, "x");
	gStyle -> SetTitleFont(132, "y");
	gStyle -> SetTitleFont(132, "z");
	gStyle -> SetLabelFont(132, "x");
	gStyle -> SetLabelFont(132, "y");
	gStyle -> SetLabelFont(132, "z");
	gStyle -> SetLegendFont(132);
	gStyle -> SetLegendTextSize(0.06);
	gStyle -> SetOptStat(0);
	gStyle -> SetOptTitle(0);

	TFile* file = new TFile("100keV_iterate_spec.root","read");

	Double_t energy[20];
	Double_t ratio[20];
	for (Int_t i = 0; i < 20; i++)
	{
		energy[i] = 100*(i+1);
		ratio[i] = 0.05;
	}
	Int_t nEven = 100000000;
	Double_t eff[20];

	TH1D* hist = (TH1D*) file->Get("hist");

	TF1* ftn = new TF1("ftn", "gaus(0) + [3]*x + [4]", 0, 2000);

	TCanvas* cvs = new TCanvas("cvs", "", 1000, 600);

	hist->Draw();
	for (Int_t i = 0; i < 20; i++)
	{
		hist->GetXaxis()->SetRangeUser(energy[i] - 80, energy[i] + 80);
		ftn->SetParameters(hist->GetBinContent(int(energy[i])), energy[i], 10, -1, 1);
		if (i < 6)	hist->Fit(ftn, "M", "", energy[i]-25, energy[i]+30);
		else if (i >=6 && i < 18)	hist->Fit(ftn, "M", "", energy[i]-45, energy[i]+40);
		else	hist->Fit(ftn, "M", "", energy[i]-50, energy[i]+45);
		eff[i] = 100*(sqrt(2.*TMath::Pi())*ftn->GetParameter(0)*ftn->GetParameter(2))/(nEven*ratio[i]);
		cout << "Efficiency @ " << energy[i] << " keV: " << eff[i] << endl;
/*
		cvs->Update();
		cvs->Modified();
		sleep(1);
*/
	}



	TGraph* graph = new TGraph(20, energy, eff);
	TH2D* dum = new TH2D("dum", "; Energy (keV); Absolute Efficiency (%);", 150, 0, 2100, 10, 1, 27);
	TCanvas* cvs2 = new TCanvas("cvs2", "", 1000, 600);
	dum->Draw();
	dum->GetXaxis()->CenterTitle();
	dum->GetYaxis()->CenterTitle();
	dum->GetXaxis()->SetNdivisions(509);
	graph->Draw("P");
	graph->SetMarkerStyle(20);


	cvs2->SaveAs("LaBr_eff_simul.pdf");






}
