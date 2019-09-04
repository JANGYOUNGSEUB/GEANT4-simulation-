#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include <stdio.h>
#include <iostream>

using namespace std;


void gamma(){

	TFile *file = new TFile("data.root","read");
	TTree *data = (TTree *)file -> Get("data");
	//TFile *file1 = new TFile("hist_g4.root","recreate");
        //TTree *tree1 = new TTree("tree1","tree1");	

	int nent = data->GetEntries();
	int eventID;
	int volumeID;
	int particleID;
	Double_t edep;

	Double_t count_g4;
        //tree1 -> Branch("count_g4",&count_g4);


	data->SetBranchAddress("eventID",&eventID);
	data->SetBranchAddress("volumeID",&volumeID);
	data->SetBranchAddress("edep",&edep);
	data->SetBranchAddress("particleID",&particleID);

	TH1D *hist_edep = new TH1D("hist_edep","deposited energy;keV;counts",3000,0,3000);
	TH1D *hist_edep1 = new TH1D("hist_edep1","deposited energy;keV;counts",3000,0,3000);
	TH2D *hist_coin = new TH2D("hist_coin","",3000,0,3000,3000,0,3000);
	int a=0;
	float b=0;
	float b1=0;
	Double_t c;
	Double_t d=0;
	Double_t s;
	Double_t c1;
	Double_t d1;
	Double_t s1;
	
	for(int i =0; i< nent; i++)
	{
		data->GetEntry(i);
		if (i == 0)	a = eventID;

		
		
		else if (volumeID==100)
		{
			 if(eventID==a)
                        {
                                //s1=d1*(exp(2.23296-0.00737*d1)-0.00144274*d1+4.35266)/234.582;
                                //c1=gRandom -> Gaus(d1,s1);
                                //hist_edep1->Fill(c1);
				b=b+edep;
			}
                        else
                        {
                                if(b>80)
				{
						s=b*(exp(2.28852-0.00800046*b)-0.00171403*b+4.7685)/234.582;
                                                c=gRandom -> Gaus(b,s);
						//cout << particleID <<" " << endl;
						hist_edep->Fill(c);
						b=edep;
				}
			}
		}
		/*else if (volumeID==200)
		{
			if(eventID==a)
			{
				//if(((d1>1173)&&(d1<1174))||((d1>1132)&&(d1<1133)))
				{
					//s=d*(exp(2.28852-0.00800046*d)-0.00171403*d+4.7685)/234.582;
					//c=gRandom -> Gaus(d,s);
					//hist_edep->Fill(c);
					b1=b1+edep;
				}
			}
                        else
                        {
                                if(b1!=0&&b1>80)
                                {
                                                s1=b1*(exp(2.23296-0.00737*b1)-0.00144274*b1+4.35266)/234.582;
                                                c1=gRandom -> Gaus(b1,s1);
						hist_edep1->Fill(c1);
                                                //cout << d1 <<" " << volumeID <<" "<< eventID <<" "<<particleID << endl;        
                                                //if(((b1>1173)&&(b1<1174))||((b1>1132)&&(b1<1133)))
						d1=b1;
						b1=edep;
				}
			}
		}*/
		else continue;
		a=eventID;
	}

	for(int i =0; i< nent; i++)
        {
                data->GetEntry(i);
                if (i == 0)     a = eventID;



                else if (volumeID==200)
                {
                         if(eventID==a)
                        {
			       b=b+edep;
                        }
                        else
                        {
                                if(b>80)
                                {
                                                s=b*(exp(2.23296-0.00737*b)-0.00144274*b+4.35266)/234.582;
                                                c=gRandom -> Gaus(b,s);
						d=b;
                                                hist_edep1->Fill(c);
                                                b=edep;
                                }
                        }
                }
		else continue;
		a=eventID;
		hist_coin->Fill(c,c1);
        }


	//Int_t colors[] = {0, 1, 2, 3, 4, 5, 6};
	//gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);
	//Double_t levels[] = {-1.79e308, 1.17e-38, 0.90, 0.95, 1.00, 1.05, 1.10, 1.79e308};
	//hist_coin->SetContour((sizeof(levels)/sizeof(Double_t)), levels);	
	
	TCanvas *cvs=new TCanvas("cvs","",1200,600);
	cvs->Divide(2,1);	
	cvs->cd(1);
	hist_edep->Draw();        
	cvs->cd(2);
	hist_edep1->Draw();        
	
	//TCanvas *cvs1=new TCanvas("cvs","",1000,600);
	//hist_coin->Draw("colz");
	//tree1->Write();
        //file1->Close();		
}
