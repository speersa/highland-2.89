#include <TColor.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <utility> 
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "THStack.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TTree.h"
#include "TSystem.h"
#include "TString.h"
#include "TChain.h"
#include "TStyle.h"
#include "TROOT.h"
#include "CommonStyle.h"

void psychev1v3comparison(bool single=true, bool all=false, bool now=false,int isyst=0){
    
  CommonStyle();
  gStyle->SetOptTitle(0);
  gStyle->SetPadTopMargin(0.12);
  gStyle->SetPadBottomMargin(0.40);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.08);       

  TString syst_name;

  if(single){
    if(isyst==0)       syst_name = "ChargeIDEff";
    else if(isyst==1)  syst_name = "TpcClusterEff";
    else if(isyst==2)  syst_name = "TpcTrackEff";
    else if(isyst==3)  syst_name = "TpcFgdMatchEff";
    else if(isyst==4)  syst_name = "FgdHybridTrackEff";
    else if(isyst==5)  syst_name = "MichelEleEff";
    else if(isyst==6)  syst_name = "PileUp";
    else if(isyst==7)  syst_name = "FgdMass";
    else if(isyst==8)  syst_name = "OOFV";
    else if(isyst==9)  syst_name = "SIPion";
    else if(isyst==10) syst_name = "FluxWeight";
  }
  else if (all) syst_name = "All";
  else if (now) syst_name = "noWeights-onlyVar";

  //TFile *infilev1 = new TFile("/lustrehome/riccioc/hl2_output/numuCCMultiPi/FGD1/MC/numumultipi_run4airmc_fgd1_psyche-v1.root");
  TFile *infilev1 = new TFile("/lustrehome/riccioc/hl2_output/numuCCMultiPi/FGD1/MC/numumultipi_run4airmc_fgd1_psyche-v1_flattree.root");
  TTree* input_treev1 = (TTree*)infilev1->Get("all_syst");

  Float_t selmu_momv1[1], selmu_thetav1[1], selmu_momv3, selmu_costhetav3, weight_syst_totalv1[1], weight_systv1[1][14], weightv1[2], weight_corr_totalv3, weight_corrv3[11];
  Int_t accum_levelv1[1][3], accum_levelv3[1][3];
  
  input_treev1->SetBranchAddress( "selmu_mom",         selmu_momv1         );
  input_treev1->SetBranchAddress( "selmu_costheta",    selmu_thetav1       );
  input_treev1->SetBranchAddress( "accum_level",       accum_levelv1       );
  input_treev1->SetBranchAddress( "weight_syst_total", weight_syst_totalv1 );
  input_treev1->SetBranchAddress( "weight_syst",       weight_systv1       );
  input_treev1->SetBranchAddress( "weight",            weightv1            );
         
  const Int_t Nsample = 3;
  TString sample_name[Nsample] = {"CC-0Pi", "CC-1piPlus", "CC-Other"};
  
  TH1D* hselmu_momv1[Nsample];
  TH1D* hselmu_cosv1[Nsample];

  TH1D* hselmu_momv1_30GeV[Nsample];

  for (Int_t is=0; is<Nsample; is++){
    hselmu_momv1[is] = new TH1D(Form("hselmu_momv1-%s",sample_name[is].Data()),Form("hselmu_momv1-%s",sample_name[is].Data()),20,0,5);
    hselmu_cosv1[is] = new TH1D(Form("hselmu_cosv1-%s",sample_name[is].Data()),Form("hselmu_cosv1-%s",sample_name[is].Data()),20,-1,1);

    hselmu_momv1_30GeV[is] = new TH1D(Form("hselmu_momv1_30GeV-%s",sample_name[is].Data()),Form("hselmu_momv1_30GeV-%s",sample_name[is].Data()),120,0,30);
  }
  
  Int_t neventv1 = input_treev1->GetEntries();
  for(Int_t i=0; i<neventv1; i++){
    input_treev1->GetEvent(i);
    for(Int_t is=0; is<Nsample; is++){
      if(accum_levelv1[0][is]>6) { 
        if(single && (isyst!=6  && isyst!=10)) {
          hselmu_momv1[is]->Fill(selmu_momv1[0]/1000,weight_systv1[0][isyst]);
          hselmu_cosv1[is]->Fill(selmu_thetav1[0],weight_systv1[0][isyst]);
          
          hselmu_momv1_30GeV[is]->Fill(selmu_momv1[0]/1000,weight_systv1[0][isyst]);
        }
        else if(single && isyst==6){
          hselmu_momv1[is]->Fill(selmu_momv1[0]/1000,weight_systv1[0][6]*weightv1[1]);
          hselmu_cosv1[is]->Fill(selmu_thetav1[0],weight_systv1[0][6]*weightv1[1]);

          hselmu_momv1_30GeV[is]->Fill(selmu_momv1[0]/1000,weight_systv1[0][6]*weightv1[1]);
        }
        else if(single && isyst==10){
          hselmu_momv1[is]->Fill(selmu_momv1[0]/1000,weight_systv1[0][10]*weightv1[0]);
          hselmu_cosv1[is]->Fill(selmu_thetav1[0],weight_systv1[0][10]*weightv1[0]);
        
          hselmu_momv1_30GeV[is]->Fill(selmu_momv1[0]/1000,weight_systv1[0][10]*weightv1[0]);
        }
        else if(all){
          hselmu_momv1[is]->Fill(selmu_momv1[0]/1000,weight_syst_totalv1[0]*weightv1[0]*weightv1[1]);
          hselmu_cosv1[is]->Fill(selmu_thetav1[0],weight_syst_totalv1[0]*weightv1[0]*weightv1[1]);
       
          hselmu_momv1_30GeV[is]->Fill(selmu_momv1[0]/1000,weight_syst_totalv1[0]*weightv1[0]*weightv1[1]);
        }
        else if(now){
          hselmu_momv1[is]->Fill(selmu_momv1[0]/1000);
          hselmu_cosv1[is]->Fill(selmu_thetav1[0]);

          hselmu_momv1_30GeV[is]->Fill(selmu_momv1[0]/1000);
        }
      }
    } 
  }

  //TFile *infilev3 = new TFile("/lustrehome/riccioc/hl2_output/numuCCMultiPi/FGD1/MC/numumultipi_run4airmc_fgd1_psyche-v3.root");
  TFile *infilev3 = new TFile("/lustrehome/riccioc/hl2_output/numuCCMultiPi/FGD1/MC/numumultipi_run4airmc_fgd1_psyche-v3_flattree_hl2head.root");
  TTree* input_treev3 = (TTree*)infilev3->Get("default");
  
  input_treev3->SetBranchAddress( "selmu_mom",         &selmu_momv3         );
  input_treev3->SetBranchAddress( "selmu_costheta",    &selmu_costhetav3    );
  input_treev3->SetBranchAddress( "accum_level",        accum_levelv3       );
  input_treev3->SetBranchAddress( "weight_corr_total", &weight_corr_totalv3 );
  input_treev3->SetBranchAddress( "weight_corr",        weight_corrv3       );
        
  TH1D* hselmu_momv3[Nsample];
  TH1D* hselmu_cosv3[Nsample];

  TH1D* hselmu_momv3_30GeV[Nsample];

  for(Int_t is=0; is<Nsample; is++){
    hselmu_momv3[is] = new TH1D(Form("hselmu_momv3-%s",sample_name[is].Data()),Form("hselmu_momv3-%s",sample_name[is].Data()),20,0,5);
    hselmu_cosv3[is] = new TH1D(Form("hselmu_cosv3-%s",sample_name[is].Data()),Form("hselmu_cosv3-%s",sample_name[is].Data()),20,-1,1);

    hselmu_momv3_30GeV[is] = new TH1D(Form("hselmu_momv3_30GeV-%s",sample_name[is].Data()),Form("hselmu_momv3_30GeV-%s",sample_name[is].Data()),120,0,30);
  }
  
  Int_t neventv3 = input_treev3->GetEntries();
  for(Int_t i=0; i<neventv3; i++){
    input_treev3->GetEvent(i);
    for(Int_t is=0; is<Nsample; is++){
      if(accum_levelv3[0][is]>6) {
        if(single) {
          hselmu_momv3[is]->Fill(selmu_momv3/1000,weight_corrv3[isyst]);
          hselmu_cosv3[is]->Fill(selmu_costhetav3,weight_corrv3[isyst]);

          hselmu_momv3_30GeV[is]->Fill(selmu_momv3/1000,weight_corrv3[isyst]);
        }
        else if(all) {
          hselmu_momv3[is]->Fill(selmu_momv3/1000,weight_corr_totalv3);
          hselmu_cosv3[is]->Fill(selmu_costhetav3,weight_corr_totalv3);

          hselmu_momv3_30GeV[is]->Fill(selmu_momv3/1000,weight_corr_totalv3);          
        }
        else if(now) {
          hselmu_momv3[is]->Fill(selmu_momv3/1000);
          hselmu_cosv3[is]->Fill(selmu_costhetav3);

          hselmu_momv3_30GeV[is]->Fill(selmu_momv3/1000);
        } 
      }
    }
  }

  TH1D* hdivmom[Nsample];
  TH1D* hdivcos[Nsample];
  for(Int_t is=0; is<Nsample; is++){
    hdivmom[is] = (TH1D*)hselmu_momv1[is]->Clone();
    hdivcos[is] = (TH1D*)hselmu_cosv1[is]->Clone();      
    hselmu_momv1[is]->Sumw2();
    hselmu_cosv1[is]->Sumw2();
    hselmu_momv3[is]->Sumw2();
    hselmu_cosv3[is]->Sumw2();
    hdivmom[is]->Divide(hselmu_momv1[is],hselmu_momv3[is]);
    hdivcos[is]->Divide(hselmu_cosv1[is],hselmu_cosv3[is]);
    hdivmom[is]->GetYaxis()->SetRangeUser(0.5,1.42);
    hdivcos[is]->GetYaxis()->SetRangeUser(0.5,1.42);
  }
  
  TCanvas* cmom[Nsample];
  TPad* upperPadmom[Nsample]; 
  TPad* lowerPadmom[Nsample];
  TLegend *leg[Nsample];

  cout <<" ********************************************************* "<<endl;
  cout << "      "  << syst_name.Data() <<endl;
  cout << " \n " <<endl;

  for (Int_t is=0; is<Nsample; is++){
    cmom[is] = new TCanvas(Form("cmom-%s",sample_name[is].Data()),Form("cmom-%s",sample_name[is].Data()),1);
    upperPadmom[is] = new TPad(Form("upperPadmom-%s",sample_name[is].Data()), Form("upperPadmom-%s",sample_name[is].Data()), 0, 0.3, 1, 1.0);
    lowerPadmom[is] = new TPad(Form("lowerPadmom-%s",sample_name[is].Data()), Form("lowerPadmom-%s",sample_name[is].Data()), 0, 0.05, 1, 0.3);
    
    leg[is] = new TLegend(0.35,0.90,0.86,0.98);
    leg[is]->SetFillStyle(0);
    leg[is]->SetBorderSize(0);
    leg[is]->SetFillColor(0);
    leg[is]->SetLineColor(1);
    leg[is]->SetNColumns(2);
    leg[is]->AddEntry(hselmu_momv1[is],"psyche v1","lep");
    leg[is]->AddEntry(hselmu_momv3[is],"psyche v3","lep");

    float vmax0  = TMath::Max(-999.,hselmu_momv1[is]->GetMaximum());
    float vmax1  = TMath::Max(vmax0,hselmu_momv3[is]->GetMaximum());
    float vmax02 = TMath::Max(vmax0,vmax1);

    upperPadmom[is]->Draw();                           
    upperPadmom[is]->cd();  

    hselmu_momv1[is]->GetYaxis()->SetRangeUser(0.001,vmax02*1.2);
    hselmu_momv1[is]->GetYaxis()->SetTitleOffset(0.8);
    hselmu_momv1[is]->GetYaxis()->SetTitle("#Events");          
    hselmu_momv1[is]->Draw("e1");
    hselmu_momv3[is]->SetLineColor(kGreen);
    hselmu_momv3[is]->SetMarkerColor(kGreen);

    hselmu_momv3[is]->Draw("sames e1");
    leg[is]->Draw("same");

    gPad->SetBottomMargin(0.01); 
    cmom[is]->cd();
    lowerPadmom[is]->Draw(); 
    lowerPadmom[is]->cd(); 
    
    gPad->Update();
    gStyle->SetOptStat(0);

    gPad->SetTopMargin(0.01);
    hdivmom[is]->GetYaxis()->SetTitleOffset(0.4);
    hdivmom[is]->GetYaxis()->SetTitleSize(0.09); 
    hdivmom[is]->GetYaxis()->SetLabelSize(0.09);
    hdivmom[is]->GetYaxis()->SetNdivisions(505);            
    hdivmom[is]->GetYaxis()->SetTitle("v1/v3");  
    hdivmom[is]->GetXaxis()->SetTitleSize(0.18);
    hdivmom[is]->GetXaxis()->SetLabelSize(0.13);                
    hdivmom[is]->GetXaxis()->SetTitle("Reconstructed muon momentum [GeV/c]");                           
    hdivmom[is]->Draw("e1");    
    cmom[is]->Print(Form("plots/%s/momdistr-%s_fgd1.pdf",syst_name.Data(),sample_name[is].Data()));
    
    cout << " \n " <<endl;
    cout << "v1 total number of events: sample " << sample_name[is].Data() << "   " << hselmu_momv1[is]->Integral() <<endl;
    cout << "v3 total number of events: sample " << sample_name[is].Data() << "   " << hselmu_momv3[is]->Integral() <<endl;
    cout << " \n " <<endl;


    cout << " \n " <<endl;
    cout << "v1 total number of events [0-30 GeV]: sample " << sample_name[is].Data() << "   " << hselmu_momv1_30GeV[is]->Integral() <<endl;
    cout << "v3 total number of events [0-30 GeV]: sample " << sample_name[is].Data() << "   " << hselmu_momv3_30GeV[is]->Integral() <<endl;
    cout << " \n " <<endl;


  }

  cout <<" ********************************************************* "<<endl;

  TCanvas* ccos[Nsample];
  TPad* upperPadcos[Nsample]; 
  TPad* lowerPadcos[Nsample];

  for (Int_t is=0; is<Nsample; is++){
    ccos[is] = new TCanvas(Form("ccos-%s",sample_name[is].Data()),Form("ccos-%s",sample_name[is].Data()),1);
    upperPadcos[is] = new TPad(Form("upperPadcos-%s",sample_name[is].Data()), Form("upperPadcos-%s",sample_name[is].Data()), 0, 0.3, 1, 1.0);
    lowerPadcos[is] = new TPad(Form("lowerPadcos-%s",sample_name[is].Data()), Form("lowerPadcos-%s",sample_name[is].Data()), 0, 0.05, 1, 0.3);
    
    float vmax0  = TMath::Max(-999.,hselmu_cosv1[is]->GetMaximum());
    float vmax1  = TMath::Max(vmax0,hselmu_cosv3[is]->GetMaximum());
    float vmax02 = TMath::Max(vmax0,vmax1);
   
    upperPadcos[is]->Draw();                               
    upperPadcos[is]->cd();                         
    hselmu_cosv1[is]->GetYaxis()->SetRangeUser(0.001,vmax02*1.2);
    hselmu_cosv1[is]->GetYaxis()->SetTitleOffset(0.8);
    hselmu_cosv1[is]->GetYaxis()->SetTitle("#Events");              
    hselmu_cosv1[is]->Draw("e1");
    hselmu_cosv3[is]->SetLineColor(kGreen);
    hselmu_cosv3[is]->SetMarkerColor(kGreen);
    hselmu_cosv3[is]->Draw("same e1");
    leg[is]->Draw("same");  
    
    gPad->SetBottomMargin(0.01); 
    ccos[is]->cd();
    lowerPadcos[is]->Draw(); 
    lowerPadcos[is]->cd(); 
    gPad->SetTopMargin(0.01);
    hdivcos[is]->GetYaxis()->SetTitleOffset(0.4);
    hdivcos[is]->GetYaxis()->SetTitleSize(0.09); 
    hdivcos[is]->GetYaxis()->SetLabelSize(0.09);
    hdivcos[is]->GetYaxis()->SetNdivisions(505);            
    hdivcos[is]->GetYaxis()->SetTitle("v1/v3");  
    hdivcos[is]->GetXaxis()->SetTitleSize(0.18);
    hdivcos[is]->GetXaxis()->SetLabelSize(0.13);            
    hdivcos[is]->GetXaxis()->SetTitle("Reconstructed muon cos#theta");                               
    hdivcos[is]->Draw("e1");  
    ccos[is]->Print(Form("plots/%s/cosdistr-%s_fgd1.pdf",syst_name.Data(),sample_name[is].Data()));

  }

}
