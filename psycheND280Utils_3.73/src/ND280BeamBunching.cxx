#include "ND280BeamBunching.hxx"
#include "VersioningUtils.hxx"
#include "Parameters.hxx"

//*****************************************************************************
ND280BeamBunching::ND280BeamBunching(): BeamBunching(){
//*****************************************************************************                 
  
  char filename[256];

  sprintf(filename,"%s/data/BunchPosition.dat",getenv("PSYCHEND280UTILSROOT"));

  ReadBeamBunchStructure(filename);
  
 
  if (ND::params().HasParameter("psycheND280Utils.TimeBunching.RCut") &&
      ND::params().HasParameter("psycheND280Utils.TimeBunching.LCut")){ 
    
    SetRCut(ND::params().GetParameterD("psycheND280Utils.TimeBunching.RCut"));
    SetLCut(ND::params().GetParameterD("psycheND280Utils.TimeBunching.LCut"));
  }
  else if (ND::params().HasParameter("psycheND280Utils.TimeBunching.Sigma") && 
      ND::params().HasParameter("psycheND280Utils.TimeBunching.NSigmas")){
  
    Float_t nsigmas = ND::params().GetParameterD("psycheND280Utils.TimeBunching.NSigmas");
    Float_t sigma   = ND::params().GetParameterD("psycheND280Utils.TimeBunching.Sigma");
    
    SetRCut(sigma * nsigmas);
    SetLCut(sigma * nsigmas);
  
  }
  
  
}

