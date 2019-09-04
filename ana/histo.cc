Double_t calresol(Double_t &E, TF1* ftn)
{
	Double_t resol = ftn->Eval(E);
	return resol;
}

Double_t realE(Double_t &preE, Double_t &resol)
{
	Double_t res = (preE*resol*0.01)/2.35;
	Double_t calE = gRandom->Gaus(preE, res);
	//Double_t calE = gRandom->Gaus(preE, 8.5);


	return calE;
}


void histo()
{
//	cout << "Input the type of source (Cs137, Co60, Ba133, Eu152): " << endl;
//	char source[100];
//	cin >> source;
//	cout << source << " source used." << endl;
//	TFile* file = new TFile(Form("../data/data_%s.root",source), "read");
	TFile* file = new TFile("../data/data.root", "read");
	TTree* tree = (TTree*) file->Get("data");
	Int_t eventID, volumeID;
	Double_t edep;

	tree->SetBranchAddress("eventID",&eventID);
	tree->SetBranchAddress("volumeID",&volumeID);
	tree->SetBranchAddress("edep",&edep);

	TFile* cal = new TFile("labr_eresol.root","read");
	TF1* ftn = (TF1*) cal->Get("exp");

	Int_t nEnt = tree->GetEntries();
	Int_t pre_id = 0;
	Double_t dep_E = 0;
	Double_t fE, resol;

	TH1D* hist = new TH1D("hist","",2500,0,2500);
	TH1D* hist_raw = new TH1D("hist_raw","",2500,0,2500);

	for (Int_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
		if (eventID == pre_id)
		{
			if (volumeID >= 100 && volumeID < 200)	dep_E = dep_E + edep;
			//dep_E = dep_E + edep;
		}
		else
		{
			
			if (dep_E != 0)
			{
				resol = calresol(dep_E, ftn);
				fE = realE(dep_E, resol);
				if (fE > gRandom->Gaus(50,5)) hist->Fill(fE);
				hist_raw->Fill(dep_E);
			}
			dep_E = 0;
			fE = 0;
		}

		pre_id = eventID;
	}

	TCanvas* cvs = new TCanvas("cvs","",1000,500);
	hist->Draw();
	TCanvas* cvs2 = new TCanvas("cvs2","",1000,500);
	hist_raw->Draw();

//	TFile* out = new TFile(Form("%s_spec.root",source),"RECREATE");
	TFile* out = new TFile("100keV_iterate_spec.root","RECREATE");
	out->cd();
	hist->Write();
	out->Close();
}
