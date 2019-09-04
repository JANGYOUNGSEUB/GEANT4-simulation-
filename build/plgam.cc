#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include <stdio.h>
#include <iostream>

void plgam(){


	TFile *file = new TFile("data.root","read");
	TTree *data = (TTree *)file -> Get("data");

	int entn = data->GetEntries();
	int eventID;
	int volumeID;
	int particleID;
	double edep;
	
	data->SetBranchAddress("eventID",&eventID);
	data->SetBranchAddress("volumeID",&volumeID);
	data->SetBranchAddress("edep",&edep);
	data->SetBranchAddress("particleID",&particleID);

	TH1D *hist_edep_pl = new TH1D("hist_edep_pl","energy deposit",3000,0,3000);
	
	double b,a,c1,s1;
	for(int i=0;i<entn;i++)
	{
		data->GetEntry(i);
		if(i==0) a=eventID;
		
		if(volumeID==400)
		{
			if(eventID==a)
			{	
				b=b+edep;
			}
			else
			{
				if(b>30)
				{
					hist_edep_pl->Fill(b);
					//cout << b << " " << particleID <<endl;
					b=edep;
				}
			}
		};	
		a=eventID;
	}


hist_edep_pl->Draw();








}
