void hist_test(){
	

	double count_qdc;
	double count_erg;

	TFile *file = new TFile("hist_qdc.root","read");
	TTree *tree = (TTree *)file ->Get("tree1");
	tree->SetBranchAddress("count_qdc",&count_qdc);
	
	TH1D *hist_qdc = new TH1D("",";Energy(keV);counts",3000,0,3000);
	
	Long64_t entrynum=tree->GetEntries();
	
	for(int i=0; i< entrynum;i++)
        {
                tree->GetEntry(i);
                hist_qdc->Fill(count_qdc*0.0415113-1.54326);
        }
	
	TFile *file1 = new TFile("g4.root","read");
        TTree *tree1 = (TTree *)file1 ->Get("tree1");

	tree1->SetBranchAddress("count_erg",&count_erg);
	
	Long64_t entrynum1=tree1->GetEntries();

	
	
	TH1D *hist_g4 = new TH1D("g4",";Energy(keV);Counts",3000,0,3000);

	for(int i=0; i<	entrynum1;i++)
	{
		tree1->GetEntry(i);
		hist_g4->Fill(count_erg);
	}
	
	TLegend *legend1 = new TLegend(0.7,0.8,0.9,1.0);
	legend1-> AddEntry(hist_g4,"Simulation data","l");
	legend1-> AddEntry(hist_qdc,"Experimental data","l");
	
	gStyle ->SetOptStat(0); 
	TCanvas *cvs= new TCanvas("cvs","cvs",600,450);
	cvs->Divide(1,1);
	cvs->cd(1);
	hist_g4->Draw();
	hist_g4->SetLineColor(2);
	hist_qdc->Draw("same");
	legend1 -> Draw("same");




}
