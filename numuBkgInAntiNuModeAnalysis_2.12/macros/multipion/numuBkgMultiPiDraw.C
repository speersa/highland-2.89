void numuBkgMultiPiDraw(){

  //==============================================================================================================================================================
  //=== Initialize DrawingTools
  //                                                                                                                                 T2K style index      
  //                                                                                                                                      / 
  DrawingTools* draw = new DrawingTools("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_run5cmc_500toys_fgd1.root",4);
  draw->SetStackFillStyle(3254);

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

  exp.AddSampleGroup( "run5c"  , run5c  );
  exp.AddSampleGroup( "run6"   , run6   );
  exp.AddSampleGroup( "run7b"  , run7b  );
  exp.SetCurrentTree("default");

  //==============================================================================================================================================================
  
  
  //==============================================================================================================================================================
  //=== Cuts for different sample, i.e. CC-Inclusive, CC-0pi etc 
  const Int_t   Nsamples = 3;
  
  TString cut_sample[Nsamples]  = { "accum_level[][0]>8" , "accum_level[][1]>8" , "accum_level[][2]>7" };
  TString sample_name[Nsamples] = {      "CC-0Pion"      ,      "CC-1PiPlus"    ,       "CC-Other"     };  

  //==============================================================================================================================================================
  

  //==============================================================================================================================================================
  //====== Draw muon momentum, cosine and angle distributions
  
  TString reco_variable[] = { "selmu_mom/1000" ,"selmu_costheta"};
  Int_t   Nvar = sizeof(reco_variable)/sizeof(TString);

  TString variable_name[] = { "mom" , "costheta" };

  TString category[] = { "topology" , "particle" ,  "reaction" };
  Int_t   Ncateg = sizeof(category)/sizeof(TString);

  TCanvas *c1[Nsamples];
  TString mom_plot_TitleY[Nsamples] = {"Events/(0.2 GeV/c)","Events/(0.25 GeV/c)","Events/(0.25 GeV/c)"};
  
  for(int is=0; is<Nsamples; is++){
    for(int iv=0; iv<Nvar; iv++){
      for(int ic=0; ic<Ncateg; ic++){
	c1[is]=new TCanvas(Form("c1_%s_%s_%s",sample_name[is].Data(),reco_variable[iv].Data(),category[ic].Data()),Form("c1_%s_%s_%s",sample_name[is].Data(),reco_variable[iv].Data(),category[ic].Data()),1);
	draw->SetOptStat("");
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
	if(iv==0){
	  if(is<1) draw->Draw(exp,Form("%s",reco_variable[iv].Data()),25,0,5,Form("%s",category[ic].Data()),Form("%s",cut_sample[is].Data()),"","OVER NOAUTOLABELS");
	  else draw->Draw(exp,Form("%s",reco_variable[iv].Data()),20,0,5,Form("%s",category[ic].Data()),Form("%s",cut_sample[is].Data()),"","OVER NOAUTOLABELS");
	}
	if(iv==1){
	  draw->Draw(exp,Form("%s",reco_variable[iv].Data()),30,-1,1,Form("%s",category[ic].Data()),Form("%s",cut_sample[is].Data()),"","NOAUTOLABELS");
	}
	c1[is]->Print(Form("plots/%s_%s_%s_fgd1.pdf",sample_name[is].Data(),variable_name[iv].Data(),category[ic].Data()));
      }
    }
  }

  //==============================================================================================================================================================
  //====== Print Purities 

  std::cout<< "---------------------------------------------------------------------"<<std::endl;
  std::cout<< "---------------------------------------------------------------------"<<std::endl;
  std::cout<< "-------------------------- Print Purities ---------------------------"<<std::endl;
  std::cout<< "---------------------------------------------------------------------"<<std::endl;
  std::cout<< "---------------------------------------------------------------------"<<std::endl;

  for(int ic=0; ic<Ncateg; ic++){
    for(int is=0; is<Nsamples; is++){
      std::cout<< "-------------------------------------------------------------------------------------------------"<<std::endl;
      std::cout<< "---------------------------"<< Form(" %s ", sample_name[is].Data()) <<"--------------------------"<<std::endl;
      std::cout<< "-------------------------------------------------------------------------------------------------"<<std::endl;
      draw->PrintPurities(exp,Form("%s",category[ic].Data()),Form("%s",cut_sample[is].Data()));
    }
  }

  std::cout<< "---------------------------------------------------------------------"<<std::endl;
  std::cout<< "---------------------------------------------------------------------"<<std::endl;
  std::cout<< "---------------------------- The end --------------------------------"<<std::endl;
  std::cout<< "---------------------------------------------------------------------"<<std::endl;
  std::cout<< "---------------------------------------------------------------------"<<std::endl;

  //==============================================================================================================================================================
  
  //==============================================================================================================================================================
}
