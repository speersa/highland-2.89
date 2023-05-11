#include <stdio.h>
#include "FGDPIDPullMCCorrection.hxx"
#include "HighlandAnalysisUtils.hxx"
#include "VersioningUtils.hxx"
#include "Parameters.hxx" 

//#define DEBUG


//********************************************************************
FGDPIDPullMCCorrection::FGDPIDPullMCCorrection(){
  //********************************************************************


  // Read the systematic source parameters from the data files: a special case of sharing the data file with systematics
  _fgd1mean  = 
    new BinnedParams("FGD1PIDMean",     BinnedParams::k2D_EFF_SYMMETRIC, versionUtils::ExtensionSyst());
 
  _fgd1sigma = 
    new BinnedParams("FGD1PIDSigRatio", BinnedParams::k2D_SYMMETRIC,     versionUtils::ExtensionSyst());
  
  _fgd2mean  =  
    new BinnedParams("FGD2PIDMean",     BinnedParams::k2D_EFF_SYMMETRIC, versionUtils::ExtensionSyst());
  
  _fgd2sigma =  
      new BinnedParams("FGD2PIDSigRatio", BinnedParams::k2D_SYMMETRIC,     versionUtils::ExtensionSyst());
  
 
}

//********************************************************************
void FGDPIDPullMCCorrection::Apply(AnaSpillC& spillBB){
  //********************************************************************
  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);

#ifdef DEBUG  
  std::cout << " FGDPIDPullMCCorrection::Apply(): IsMC " << spill.GetIsMC() << std::endl; 
  std::cout << " FGDPIDPullMCCorrection::Apply(): Event " << spill.EventInfo->Event << std::endl;  
#endif


  // No correction for data
  if (!spill.GetIsMC())
    return;

  // Loop over all bunches
  for (unsigned int i = 0; i < spill.Bunches.size(); i++) {

    AnaBunch* bunch = static_cast<AnaBunch*>(spill.Bunches[i]);
    AnaTrackB* allFgdTracks[NMAXPARTICLES];

    // Get all the tracks in the FGD
    int nFGD = anaUtils::GetAllTracksUsingDet(*bunch, SubDetId::kFGD, allFgdTracks);
    for (Int_t j = 0; j < nFGD; j++)
      ApplyVariation(allFgdTracks[j], _exp);
  }


#ifdef DEBUG 
  std::cout << "FGDPIDPullMCCorrection::Apply() end " << std::endl;  
#endif

}

//**************************************************
bool FGDPIDPullMCCorrection::GetVariation(
    const Int_t& pdg_ref, 
    const AnaParticleB& track, 
    Int_t pdg_hypo,  
    Float_t& pull_mean, 
    Float_t& mean_var, 
    Float_t& sigma_var, 
    const ToyExperiment& toy){
  //**************************************************

  (void)toy;

#ifdef DEBUG
    std::cout << " FGDPIDPullMCCorrection::GetVariation(): pdg_ref " << pdg_ref << std::endl;  	     
#endif
    
  Int_t pdg = pdg_ref;
  
  // Retrieve the PDG
  if (track.GetTrueParticle()){ 
    pdg = GetPDG(*track.GetTrueParticle());
  }
  
#ifdef DEBUG
    std::cout << " FGDPIDPullMCCorrection::GetVariation(): pdg base " << pdg << std::endl; 
    std::cout << " FGDPIDPullMCCorrection::GetVariation(): pdg hypo " << pdg_hypo << std::endl;  	     
#endif
  
  // Get the systematic source values
  Float_t sigR_value;
  Float_t sigR_error;
  Int_t mean_index;
  Int_t sigR_index;
  BinnedParamsParams params;
 
  // One has to make sure a sub-detector segment is provided
  bool inFGD1 = SubDetId::GetDetectorUsed(track.Detector, SubDetId::kFGD1);
  bool inFGD2 = SubDetId::GetDetectorUsed(track.Detector, SubDetId::kFGD2);

  // If both are present, issue a warning and do nothing
  if (inFGD1 && inFGD2){
    std::cout << " WARNING FGDPIDPullMCCorrection::GetVariation(): track has both FGDs. Cannot get the variation." << std::endl;
    return false;
  }
  
  if (inFGD1){
#ifdef DEBUG
    std::cout << " FGDPIDPullMCCorrection::GetVariation(): FGD1 " << std::endl;  	     
#endif
    
    if (!_fgd1mean->GetBinValues((Float_t)pdg,  (Float_t)pdg_hypo,  params,     mean_index))  return false;
    if (!_fgd1sigma->GetBinValues((Float_t)pdg, (Float_t)pdg_hypo,  sigR_value, sigR_error, sigR_index)) return false;
  }
  else if (inFGD2){    
#ifdef DEBUG
    std::cout << " FGDPIDPullMCCorrection::GetVariation(): FGD2 " << std::endl;  	     
#endif
 
    if (!_fgd2mean->GetBinValues((Float_t)pdg,  (Float_t)pdg_hypo, params,      mean_index))  return false;
    if (!_fgd2sigma->GetBinValues((Float_t)pdg, (Float_t)pdg_hypo, sigR_value,  sigR_error, sigR_index)) return false;
  }
  else{
#ifdef DEBUG
    std::cout << " FGDPIDPullMCCorrection::GetVariation(): no FGD " << std::endl;  	     
#endif
 
    return false;
  }
  

#ifdef DEBUG
  std::cout << " FGDPIDPullMCCorrection::GetVariation(): meanmc,  menadata, mean_index  = " << params.meanMC  << " " <<  params.meanDATA  << " " << mean_index << std::endl;  	     
  std::cout << " FGDPIDPullMCCorrection::GetVariation(): sigR_value, sigR_error, sigR_index = " << sigR_value << " " <<  sigR_error  << " " << sigR_index <<std::endl;  
#endif
  // Apply the variation

  Float_t diffdataMC = params.meanDATA - params.meanMC;

  pull_mean = params.meanMC;
  
  mean_var  = diffdataMC;
  sigma_var = sigR_value;
  
  return true;
}

