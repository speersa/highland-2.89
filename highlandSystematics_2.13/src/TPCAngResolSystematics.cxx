#include "TPCAngResolSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "EventBoxTracker.hxx"
#include "VersioningUtils.hxx"
#include "SystematicUtils.hxx"

//#define DEBUG

//********************************************************************
TPCAngResolSystematics::TPCAngResolSystematics(): EventVariationBase(){
  //********************************************************************

  const std::string folder = std::string(getenv("HIGHLANDSYSTEMATICSROOT")) + "/data";

  // Read the systematic source parameters from the data files
  _tpcmean  = new BinnedParams(folder, "TPCAngResolution",         BinnedParams::k1D_EFF_SYMMETRIC, versionUtils::ExtensionSyst());
  _tpcsigma = new BinnedParams(folder, "TPCAngResolutionSigRatio", BinnedParams::k1D_SYMMETRIC, versionUtils::ExtensionSyst());
  Int_t npar = _tpcmean->GetNBins()+_tpcsigma->GetNBins();

  // Set the total number of parameters
  SetNParameters(npar);

}

//******************************************************************** 
void TPCAngResolSystematics::Print(Option_t *option) const{
  //******************************************************************** 

  (void)option;

  std::cout << " ***** Bins for the TPCAngResolSystematics **** " << std::endl;

  unsigned int offset = 0;

  std::cout << " Bins for _tpcmean " << std::endl;
  _tpcmean ->Print(offset); 

  offset += _tpcmean->GetNBins();

  std::cout << " Bins for _tpcsigma " << std::endl;
  _tpcsigma ->Print(offset); 

  offset += _tpcsigma->GetNBins();

  std::cout << " ********* " << std::endl;

}  

//********************************************************************
void TPCAngResolSystematics::Initialize(){
  //********************************************************************

  // Register the BinnedParams to have proper offsets for each of them
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_tpcmean,  _tpcmean->GetNBins());
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_tpcsigma, _tpcsigma->GetNBins());

}

//********************************************************************
void TPCAngResolSystematics::Apply(const ToyExperiment& toy, AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

#ifdef DEBUG
  std::cout << "TPCAngResolSystematics::Apply(): tracks size " << box->nRelevantRecObjects << std::endl;  
#endif

  // Loop over relevant tracks for this systematic
  for (Int_t itrk = 0; itrk < box->nRelevantRecObjects; itrk++){
    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);

    // Check track validity
    if (!track) continue;

    // Do not do anything if a track does not use a TPC
    if (track->nTPCSegments == 0) continue;

    AnaParticleB* TpcSegment = anaUtils::GetSegmentWithMostNodesInClosestTpc(*track);
    if(!TpcSegment) continue;

    Float_t mean, mean_var, sigma_var;
    if(!GetVariation(*TpcSegment, mean, mean_var, sigma_var, toy)) continue;

    Float_t track_angle = acos(track->DirectionStart[2]);
#ifdef DEBUG
    std::cout << "Default track angle in rad = " << track_angle << std::endl;
#endif

    track_angle = track_angle + mean_var;
    track_angle = mean + (track_angle - mean)*sigma_var;

#ifdef DEBUG
    std::cout << "Varied track angle in rad = " << track_angle << std::endl;
#endif

    track->DirectionStart[2] = cos(track_angle);

  }

}

//********************************************************************
bool TPCAngResolSystematics::UndoSystematic(AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

  for (int itrk=0;itrk<box->nRelevantRecObjects;itrk++){
    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);

    // Check track validity
    if (!track) continue;
    track->DirectionStart[2] = track->GetOriginalTrack()->DirectionStart[2];
  }

  // Don't reset the spill to corrected
  return false;

}

//**************************************************
bool TPCAngResolSystematics::GetVariation(const AnaParticleB& track, Float_t& mean, Float_t& mean_var, Float_t& sigma_var, const ToyExperiment& toy){
  //**************************************************

  // Get the systematic source values
  Float_t sigR_value;
  Float_t sigR_error;
  Int_t mean_index;
  Int_t sigR_index;
  BinnedParamsParams params;

  bool inTPC1 = SubDetId::GetDetectorUsed(track.Detector, SubDetId::kTPC1);
  bool inTPC2 = SubDetId::GetDetectorUsed(track.Detector, SubDetId::kTPC2);
  bool inTPC3 = SubDetId::GetDetectorUsed(track.Detector, SubDetId::kTPC3);

  if (inTPC1){
    if (!_tpcmean->GetBinValues(1.0, params,  mean_index))  return false;
    mean_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_tpcmean);

    if (!_tpcsigma->GetBinValues(1.0, sigR_value, sigR_error, sigR_index)) return false;
    sigR_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_tpcsigma);
  }
  else if (inTPC2){
    if (!_tpcmean->GetBinValues(2.0, params,  mean_index))  return false;
    mean_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_tpcmean);

    if (!_tpcsigma->GetBinValues(2.0, sigR_value, sigR_error, sigR_index)) return false;
    sigR_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_tpcsigma);
  }
  else if (inTPC3){
    if (!_tpcmean->GetBinValues(3.0, params,  mean_index))  return false;
    mean_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_tpcmean);

    if (!_tpcsigma->GetBinValues(3.0, sigR_value, sigR_error, sigR_index)) return false;
    sigR_index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_tpcsigma);
  }
  else
    return false;
  
#ifdef DEBUG
  std::cout << "TPCAngResolSystematics::GetVariation(): meanmc,  menadata, mean_index  = " << params.meanMC  << " " <<  params.meanDATA  << " " << mean_index << std::endl;  	     
  std::cout << "TPCAngResolSystematics::GetVariation(): sigR_value, sigR_error, sigR_index = " << sigR_value << " " <<  sigR_error  << " " << sigR_index <<std::endl;  
#endif

  // Apply the variation
  Float_t diffdataMC = params.meanDATA - params.meanMC;
  mean = params.meanMC;
  mean_var  = fabs(diffdataMC) * toy.GetToyVariations(_index)->Variations[mean_index];

  sigma_var = sigR_error * toy.GetToyVariations(_index)->Variations[sigR_index];  
  sigma_var *= (sigR_value != 0) ? 1. / sigR_value : 0.;
  sigma_var += 1.;
   
  return true;

}

//**************************************************
bool TPCAngResolSystematics::IsRelevantRecObject(const AnaEventC& event, const AnaRecObjectC& recObj) const{
  //**************************************************

  (void)event;
  (void)recObj; 

  return true;

}

