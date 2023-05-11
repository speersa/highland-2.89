#include "FGDPIDSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "EventBoxTracker.hxx"
#include "VersioningUtils.hxx"
#include "SystematicUtils.hxx"

//#define DEBUG

//********************************************************************
FGDPIDSystematics::FGDPIDSystematics():FGDPIDVariation(), EventVariationBase(){
  //********************************************************************


  // Read the systematic source parameters from the data files
  Int_t npar=0;
  _fgd1mean  = new BinnedParams("FGD1PIDMean",    BinnedParams::k2D_EFF_SYMMETRIC, versionUtils::ExtensionSyst());
  _fgd1sigma = new BinnedParams("FGD1PIDSigRatio",BinnedParams::k2D_SYMMETRIC,     versionUtils::ExtensionSyst());
  npar=_fgd1mean->GetNBins()+_fgd1sigma->GetNBins();
  
  _fgd2mean  =  new BinnedParams("FGD2PIDMean",    BinnedParams::k2D_EFF_SYMMETRIC, versionUtils::ExtensionSyst());
  _fgd2sigma =  new BinnedParams("FGD2PIDSigRatio",BinnedParams::k2D_SYMMETRIC,     versionUtils::ExtensionSyst());
  npar +=_fgd2mean->GetNBins()+_fgd2sigma->GetNBins();

  //set the total number of parameters
  SetNParameters(npar);
}
//******************************************************************** 
void FGDPIDSystematics::Print(Option_t *option) const{
  //******************************************************************** 
  (void)option;

  std::cout << " ***** Bins for the FGDPIDSystematics **** " << std::endl;

  unsigned int offset = 0;

  std::cout << " Bins for _fgd1mean " << std::endl;
  _fgd1mean ->Print(offset); 

  offset += _fgd1mean->GetNBins();

  std::cout << " Bins for _fgd1sigma " << std::endl;
  _fgd1sigma ->Print(offset); 

  offset += _fgd1sigma->GetNBins();

  std::cout << " Bins for _fgd2mean " << std::endl;
  _fgd2mean ->Print(offset); 

  offset += _fgd2mean->GetNBins();

  std::cout << " Bins for _fgd2sigma " << std::endl;
  _fgd2sigma ->Print(offset); 


  std::cout << " ********* " << std::endl;

}  


//********************************************************************
void FGDPIDSystematics::Initialize(){
  //********************************************************************

  // Register the BinnedParams to have proper offsets for each of them
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd1mean,  _fgd1mean->GetNBins());
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd1sigma, _fgd1sigma->GetNBins());
   
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd2mean,  _fgd2mean->GetNBins());
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd2sigma, _fgd2sigma->GetNBins());
  

}
//********************************************************************
void FGDPIDSystematics::Apply(const ToyExperiment& toy, AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

#ifdef DEBUG
  std::cout << "FGDPIDSystematics::Apply(): tracks size " << box->nRelevantRecObjects << std::endl;  
#endif

  // Loop over relevant tracks for this systematic
  for (Int_t itrk = 0; itrk < box->nRelevantRecObjects; itrk++){
    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);
    ApplyVariation(track, toy);
  }
}

//********************************************************************
bool FGDPIDSystematics::UndoSystematic(AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

  for (int itrk=0;itrk<box->nRelevantRecObjects;itrk++){
    for (int k = 0; k < static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk])->nFGDSegments; k++) {
      // The new FGD track
      AnaFGDParticleB* fgdTrack = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk])->FGDSegments[k];
      // The original (corrected) fgd track
      const AnaFGDParticleB* original = static_cast<const AnaFGDParticleB*>(fgdTrack->Original);

      // revert to initial pulls
      fgdTrack->Pullpi = original->Pullpi;
      fgdTrack->Pullmu = original->Pullmu;
      fgdTrack->Pullp  = original->Pullp;
      fgdTrack->Pulle  = original->Pulle;
    }
  }

  // Don't reset the spill to corrected
  return false;
}

//**************************************************
bool FGDPIDSystematics::GetVariation(
    const Int_t& pdg_ref, 
    const AnaParticleB& track, 
    Int_t pdg_hypo, 
    Float_t& pull_mean, 
    Float_t& mean_var, 
    Float_t& sigma_var, 
    const ToyExperiment& toy){
  //**************************************************
  
  Int_t pdg = pdg_ref;
  
#ifdef DEBUG
    std::cout << " FGDPIDSystematics::GetVariation(): pdg_ref " << pdg_ref << std::endl;  	     
#endif
    
  // Retrieve the PDG
  if (track.GetTrueParticle()){ 
    pdg = GetPDG(*track.GetTrueParticle());
  }
  
#ifdef DEBUG
    std::cout << " FGDPIDSystematics::GetVariation(): pdg base " << pdg << std::endl; 
    std::cout << " FGDPIDSystematics::GetVariation(): pdg hypo " << pdg_hypo << std::endl;  
    
#endif
  // Get the systematic source values
  Float_t sigR_value;
  Float_t sigR_error;
  Int_t mean_index;
  Int_t sigR_index;
  BinnedParamsParams params;
 
  
  bool inFGD1 = SubDetId::GetDetectorUsed(track.Detector, SubDetId::kFGD1);
  bool inFGD2 = SubDetId::GetDetectorUsed(track.Detector, SubDetId::kFGD2);

  // If both are present, issue a warning and do nothing
  if (inFGD1 && inFGD2){
    std::cout << "WARNING FGDPIDSystematics::GetVariation(): track has both FGDs. Cannot get the variation." << std::endl;
    return false;
  }

  if (inFGD1){    
#ifdef DEBUG
    std::cout << "FGDPIDSystematics::GetVariation(): FGD1 " << std::endl;  	     
#endif
    if (!_fgd1mean->GetBinValues((Float_t)pdg, (Float_t)pdg_hypo,  params,  mean_index))  return false;

    mean_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_fgd1mean);


    if (!_fgd1sigma->GetBinValues((Float_t)pdg, (Float_t)pdg_hypo, sigR_value, sigR_error, sigR_index)) return false;
    sigR_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_fgd1sigma);
  }
  else if (inFGD2){

#ifdef DEBUG
  std::cout << "FGDPIDSystematics::GetVariation(): FGD2 " << std::endl;  	     
#endif
    if (!_fgd2mean->GetBinValues((Float_t)pdg, (Float_t)pdg_hypo, params,  mean_index))  return false;

    mean_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_fgd2mean);

    if (!_fgd2sigma->GetBinValues((Float_t)pdg, (Float_t)pdg_hypo, sigR_value, sigR_error, sigR_index)) return false;
    sigR_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_fgd2sigma);  
  }
  else{
#ifdef DEBUG
    std::cout << "FGDPIDSystematics::GetVariation(): not FGD " << std::endl;  	     
#endif
    return false;
  }
  

#ifdef DEBUG
  std::cout << "FGDPIDSystematics::GetVariation(): meanmc,  meandata, mean_index  = " << params.meanMC  << " " <<  params.meanDATA  << " " << mean_index << std::endl;  	     
  std::cout << "FGDPIDSystematics::GetVariation(): meanmcErr,  meandataErr, mean_index  = " << params.sigmaMCl  << " " <<  params.sigmaDATAl  << " " << mean_index << std::endl;  	     
  std::cout << "FGDPIDSystematics::GetVariation(): sigR_value, sigR_error, sigR_index = " << sigR_value << " " <<  sigR_error  << " " << sigR_index <<std::endl;  
#endif
  // Apply the variation

  Float_t diffdataMC = params.meanDATA - params.meanMC;
  Float_t error_diff = fabs(diffdataMC); //100% error on data-mc difference -> to check why the individual errors are not considered

  Float_t error_int = sqrt(params.sigmaMCl * params.sigmaMCl + params.sigmaDATAl * params.sigmaDATAl);

  Float_t error = std::max(error_diff, error_int);
  
#ifdef DEBUG
  std::cout << "FGDPIDSystematics::GetVariation(): mean diff err  = " << error_diff << std::endl; 
  std::cout << "FGDPIDSystematics::GetVariation(): inter err  = " << error_int << std::endl;
  std::cout << "FGDPIDSystematics::GetVariation(): to be used max  = " << error << std::endl; 
#endif

  
  
  pull_mean = params.meanMC;
  
  mean_var  = error      * toy.GetToyVariations(_index)->Variations[mean_index];
  sigma_var = sigR_error * toy.GetToyVariations(_index)->Variations[sigR_index];
  
  sigma_var *= (sigR_value != 0) ? 1. / sigR_value : 0.;
  
  sigma_var += 1.;
   
  return true;
}

//**************************************************
bool FGDPIDSystematics::IsRelevantRecObject(const AnaEventC& event, const AnaRecObjectC& recObj) const{
  //**************************************************

  (void)event;

  // True track should always exist
  if (!recObj.TrueObject) return false;

  const AnaTrueParticleB* truePart = static_cast<const AnaTrueParticleB*>(recObj.TrueObject);

  bool ok = false;
  // Only consider true protons, pions, muons and electrons
  if      (abs(truePart->PDG) == ParticleId::kMuonPDG)      ok = true;      
  else if (abs(truePart->PDG) == ParticleId::kProtonPDG)    ok = true;
  else if (abs(truePart->PDG) == ParticleId::kPionPosPDG)   ok = true;
  else if (abs(truePart->PDG) == ParticleId::kElectronPDG)  ok = true;

  return ok;
}
