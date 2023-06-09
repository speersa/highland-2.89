void numuBkgMultiPiPrintEffPurVSCut(){
  //==============================================================================================================================================================
  //=== Initialize DrawingTools
  //                            
  DrawingTools* draw = new DrawingTools("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_run5cmc_500toys_fgd1.root",4);

  //=== Magnet MC samples
  DataSample mc("/lustrehome/riccioc/hl2_output/numuBkgMultiPi/FGD1/MC/numubkgmultipi_run5cmc_500toys_fgd1.root",4);

  //==============================================================================================================================================================
    
  //==============================================================================================================================================================
  //====== Draw Efficiency

  //==== CC-Inclusive sample
  cout<< " ================================================================================================= " <<endl;
  cout<< " CC-Inclusive " <<endl;
  draw.DrawEffPurVSCut(mc,0,"(topology==0 || topology==1 || topology==2)","",0,6);
  cout<< " ================================================================================================= " <<endl;

  cout<< " ================================================================================================= " <<endl;
  cout<< " CC-0Pion " <<endl;
  draw.DrawEffPurVSCut(mc,0,"topology==0","",0,8);
  cout<< " ================================================================================================= " <<endl;

  cout<< " ================================================================================================= " <<endl;
  cout<< " CC-1PositivePion " <<endl;
  draw.DrawEffPurVSCut(mc,1,"topology==1","",0,8);
  cout<< " ================================================================================================= " <<endl;

  cout<< " ================================================================================================= " <<endl;
  cout<< " CC-Other " <<endl;
  draw.DrawEffPurVSCut(mc,2,"topology==2","",0,8);
  cout<< " ================================================================================================= " <<endl;

  cout<< " ================================================================================================= " <<endl;
  //==============================================================================================================================================================
  
  //==============================================================================================================================================================

}
