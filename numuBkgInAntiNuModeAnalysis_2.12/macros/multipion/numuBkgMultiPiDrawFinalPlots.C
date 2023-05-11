void numuBkgMultiPiDrawFinalPlots(){

  //==============================================================================================================================================================
  //=== Initialize DrawingTools
  //                                                                                                                                 T2K style index      
  //                                                                                                                                      / 
  DrawingTools* draw = new DrawingTools("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_run5cmc_500toys_fgd1.root",4);
  //  draw->SetStackFillStyle(3254);

  //=== Initialize Experiment class 
  Experiment exp("nd280");
  
  //=== Data samples
  DataSample* data_run5c  = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/data/numubkgmultipi_run5cdata_fgd1.root");
  DataSample* data_run6   = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/data/numubkgmultipi_run6data_fgd1.root");
  DataSample* data_run7b  = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/data/numubkgmultipi_run7bdata_fgd1.root");

  //=== Magnet MC samples
  DataSample* magnet_mc_run5c  = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_run5cmc_500toys_fgd1.root");
  DataSample* magnet_mc_run6   = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_run6mc_500toys_fgd1.root");
  DataSample* magnet_mc_run7b  = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_run7bmc_500toys_fgd1.root");
  
  //=== Sand MC samples
  DataSample* sand_mc_run5  = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_sandmuon_500toys_fgd1.root");
  DataSample* sand_mc_run6  = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_sandmuon_500toys_fgd1.root");
  DataSample* sand_mc_run7b = new DataSample("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_sandmuon_500toys_fgd1.root");
  
  //=== Run5c sample
  SampleGroup run5c("run5c");
  run5c.AddDataSample(data_run5c);
  run5c.AddMCSample("magnet",magnet_mc_run5c);
  run5c.AddMCSample("sand",sand_mc_run5);
  
  //=== Run6 sample
  SampleGroup run6("run6");
  run6.AddDataSample(data_run6);
  run6.AddMCSample("magnet",magnet_mc_run6);
  run6.AddMCSample("sand",sand_mc_run6);
 
  //=== Run7b sample
  SampleGroup run7b("run7b");
  run7b.AddDataSample(data_run7b);
  run7b.AddMCSample("magnet",magnet_mc_run7b);
  run7b.AddMCSample("sand",sand_mc_run7b);

  exp.AddSampleGroup( "run5c" , run5c );
  exp.AddSampleGroup( "run6"  , run6  );
  exp.AddSampleGroup( "run7b" , run7b );

  exp.GetMCSample("run5c" ,  "magnet")->SetCurrentTree("all_syst");
  exp.GetMCSample("run6"  ,  "magnet")->SetCurrentTree("all_syst");
  exp.GetMCSample("run7b" ,  "magnet")->SetCurrentTree("all_syst");
  exp.GetMCSample("run5c" ,  "sand")->SetCurrentTree("sandmu_syst");
  exp.GetMCSample("run6"  ,  "sand")->SetCurrentTree("sandmu_syst");
  exp.GetMCSample("run7b" ,  "sand")->SetCurrentTree("sandmu_syst");
 
  //==============================================================================================================================================================
  
  
  //==============================================================================================================================================================
  //=== Cuts for different sample, i.e. CC-Inclusive, CC-0pi etc 
  const Int_t   Nsamples = 3;

  TString cut_sample[Nsamples]  = { "accum_level[][0]>8 && (weight_syst_total>0 && weight_syst_total<10)" , "accum_level[][1]>8 && (weight_syst_total>0 && weight_syst_total<10)" , "accum_level[][2]>7 && (weight_syst_total>0 && weight_syst_total<10)" };
  TString sample_name[Nsamples] = {      "CC-0Pion"      ,      "CC-1PiPlus"    ,       "CC-Other"     };  

  //==============================================================================================================================================================
  
  //==============================================================================================================================================================
  //====== Draw muon momentum, cosine and angle distributions
  TString reco_variable[] = { "selmu_mom/1000" ,"selmu_costheta"};
  Int_t   Nvar = sizeof(reco_variable)/sizeof(TString);

  TString variable_name[] = { "mom" , "costheta" };
  
  TCanvas *c1[Nsamples];
  TString mom_plot_TitleY[Nsamples] = {"Events/(0.2 GeV/c)","Events/(0.25 GeV/c)","Events/(0.25 GeV/c)"};

  for(int is=0; is<Nsamples; is++){
    for(int iv=0; iv<Nvar; iv++){
      c1[is]=new TCanvas(Form("c1_%s_%s",sample_name[is].Data(),reco_variable[iv].Data()),Form("c1_%s_%s",sample_name[is].Data(),reco_variable[iv].Data()),1);
      if(iv==0){
	draw->SetLegendPos("tr");
	draw->SetTitleY(Form("%s",mom_plot_TitleY[is].Data()));
	draw->SetTitleX("Reconstructed p_{#mu} [GeV/c]");
      }
      if(iv==1){
	draw->SetLegendPos("tl");
	draw->SetTitleY("Events");
	draw->SetTitleX("Reconstructed cos#theta_{#mu}");
      }
      draw->SetOptStat("");
      draw->SetAllMCStatLabel("MC stat. error");
      draw->SetAllMCLabel("MC stat. + det. syst. error");
      draw->SetMCErrorColor(kAzure);
      if(iv==0){
	if(is<1) draw->Draw(exp,Form("%s",reco_variable[iv].Data()),25,0,5,"all",Form("%s",cut_sample[is].Data()),"","OVER NOAUTOLABELS SYS NWS11 WC11 E2");
	else draw->Draw(exp,Form("%s",reco_variable[iv].Data()),20,0,5,"all",Form("%s",cut_sample[is].Data()),"","OVER NOAUTOLABELS SYS NWS11 WC11 E2");
      }
      if(iv==1){
	draw->Draw(exp,Form("%s",reco_variable[iv].Data()),30,-1,1,"all",Form("%s",cut_sample[is].Data()),"","NOAUTOLABELS SYS NWS11 WC11 E2");
      }
      c1[is]->Print(Form("plots/Final_%s_%s_fgd1.pdf",sample_name[is].Data(),variable_name[iv].Data()));
    }
  }
}
