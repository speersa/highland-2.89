#include "TPCPIDSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "EventBoxTracker.hxx"
#include <cassert>
#include "Parameters.hxx"

//#define DEBUG

//********************************************************************
TPCPIDSystematics::TPCPIDSystematics(): TPCPIDVariation(), EventVariationBase(){
  //********************************************************************
#ifdef DEBUG
  std::cout << "TPCPIDSystematics::TPCPIDSystematics() " << std::endl;  
#endif
  // Read the systematic source parameters from the data files
  _sigma[TPCPIDVariation::kMuon]     = new BinnedParams("TPCPIDMuonSigRatio",   BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _sigma[TPCPIDVariation::kElectron] = new BinnedParams("TPCPIDEleSigRatio",    BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _sigma[TPCPIDVariation::kProton]   = new BinnedParams("TPCPIDProtonSigRatio", BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());

  _mean[TPCPIDVariation::kMuon]      = new BinnedParams("TPCPIDMuonMeanDiff",   BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _mean[TPCPIDVariation::kElectron]  = new BinnedParams("TPCPIDEleMeanDiff",    BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _mean[TPCPIDVariation::kProton]    = new BinnedParams("TPCPIDProtonMeanDiff", BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());

  // Offset for mean_err vars
  _offset = 0;

  UInt_t nbins = 0;

  for (UInt_t i = 0; i < TPCPIDVariation::kNPULLS; i++){
    if (!_mean[i] && !_sigma[i]) continue;

    // For the moment want both to exist
    HASSERT(_mean[i]);
    HASSERT(_sigma[i]);

    nbins += _mean[i]->GetNBins();

    _offset += _sigma[i]->GetNBins();
    nbins   += _sigma[i]->GetNBins();
  }

  SetNParameters(nbins);

  _full_correlations = ND::params().GetParameterI("psycheSystematics.Tracker.FullCorrelations");
}

//******************************************************************** 
void TPCPIDSystematics::Print(Option_t *option) const{
  //******************************************************************** 
  (void)option;
  std::cout << " ***** Bins for the TPCPIDSystematics **** " << std::endl;
  std::cout << "Total bins consist of the ones for sigma vatiation then coming the ones for mean " << std::endl;
  
  unsigned int offset = 0;
  
  std::cout << " Bins for _sigma[TPCPIDVariation::kMuon]  " << std::endl;
  _sigma[TPCPIDVariation::kMuon]->Print(offset); 
  
  offset += _sigma[TPCPIDVariation::kMuon]->GetNBins();
  
  std::cout << " Bins for _sigma[TPCPIDVariation::kElectron]  " << std::endl;
  _sigma[TPCPIDVariation::kElectron]->Print(offset); 
  
  offset += _sigma[TPCPIDVariation::kElectron]->GetNBins();
  
  std::cout << " Bins for _sigma[TPCPIDVariation::kProton]  " << std::endl;
  _sigma[TPCPIDVariation::kProton]->Print(offset);
  
  offset += _sigma[TPCPIDVariation::kProton]->GetNBins();
  
  std::cout << " Bins for _mean[TPCPIDVariation::kMuon]  " << std::endl;
  _mean[TPCPIDVariation::kMuon]->Print(offset); 
  
  offset += _mean[TPCPIDVariation::kMuon]->GetNBins();
  
  std::cout << " Bins for _mean[TPCPIDVariation::kElectron]  " << std::endl;
  _mean[TPCPIDVariation::kElectron]->Print(offset); 
  
  offset += _mean[TPCPIDVariation::kElectron]->GetNBins();
  
  std::cout << " Bins for _mean[TPCPIDVariation::kProton]  " << std::endl;
  _mean[TPCPIDVariation::kProton]->Print(offset);
  std::cout << " ********* " << std::endl;

}  
  
//********************************************************************
void TPCPIDSystematics::Apply(const ToyExperiment& toy, AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

#ifdef DEBUG
  std::cout << "TPCPIDSystematics::ApplyVariation(): tracks size " << box->nRelevantRecObjects << std::endl;  
#endif

  // Loop over tracks and save the relevent ones for this systematic (all for the moment)
  for (Int_t itrk = 0; itrk < box->nRelevantRecObjects; itrk++){

    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);

    ApplyVariation(track, toy);  
  }
}

//********************************************************************
bool TPCPIDSystematics::UndoSystematic(AnaEventC& event){
  //********************************************************************
#ifdef DEBUG
  std::cout << "TPCPIDSystematics::UndoSystematic() " << std::endl;  
#endif
  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

  for (Int_t itrk=0;itrk<box->nRelevantRecObjects;itrk++){
    for (Int_t k = 0; k < static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk])->nTPCSegments; k++) {
      // The new TPC track
      AnaTPCParticleB* tpcTrack = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk])->TPCSegments[k];
      // The corrected TPC track
      const AnaTPCParticleB* original = static_cast<const AnaTPCParticleB*>(tpcTrack->Original);
      if (!original)   continue;
      if (original->dEdxMeas == -99999) continue;

      tpcTrack->dEdxMeas = original->dEdxMeas;
    }
  }

  // Don't reset the spill to corrected
  return false;
}


  
//********************************************************************
bool TPCPIDSystematics::GetVariation(const AnaTPCParticleB& tpcTrack, 
    Float_t& mean_var, Float_t& sigma_var, 
    const AnaTrackB& track, const ToyExperiment& toy){
  //******************************************************************** 
#ifdef DEBUG
  std::cout << "TPCPIDSystematics::GetVariation() " << std::endl;  
#endif
  // Get the TPC 
  int tpc = SubDetId::GetTPC(tpcTrack.Detector);

  // Need true particle
  if (!track.GetTrueParticle()) return false; 

  // Get the expected dEdx and error on the dEdx depending on the true particle of the 
  // (global) track

  Int_t mean_index;
  Int_t sigma_index;

  TPCPIDVariation::HypEnum part = GetPIDHypo(track.GetTrueParticle()->PDG);
  
  // Pions are treated as muons in terms of errors
  if (part == TPCPIDVariation::kPion){
    part = TPCPIDVariation::kMuon;
  }

  // Non-valid hypothesis
  if (part == TPCPIDVariation::kNPULLS){
    return false;
  }
   
  
  if (!_mean[part] || !_sigma[part]) return false;

  // We need the errors part of the data file but as well the relative uncertainty for sigma
  Float_t mean_corr, sigma_corr;

  // Note that the momentum changes if the mom resoltion, scale and bfield are also anabled.
  if (!_mean[part]->GetBinValues(track.Momentum,  (Float_t)tpc, mean_corr,  mean_var,  mean_index))  return false;
  if (!_sigma[part]->GetBinValues(track.Momentum, (Float_t)tpc, sigma_corr, sigma_var, sigma_index)) return false;

  // Offset for the mean variations
  mean_index += _offset;

  for (Int_t i = 0; i < part; i++){
    if (_mean[i])
      mean_index += _mean[i]->GetNBins();
    if (_sigma[i])
      sigma_index  += _sigma[i]->GetNBins();
  }

  // override to ensure same variations for all params (see bugzilla 1271)
  // except for particles bin (as of TN 212)
  if (_full_correlations) {
    mean_index = part;
    sigma_index = part;
  }

  mean_var  *= toy.GetToyVariations(_index)->Variations[mean_index];
  sigma_var *= toy.GetToyVariations(_index)->Variations[sigma_index];
  sigma_var *= (sigma_corr != 0) ? 1. / sigma_corr : 0.;

  //TMP
  //mean_var  += -1. * mean_corr * sigma_var;

  sigma_var += 1.;

  return true;
}



//**************************************************
bool TPCPIDSystematics::IsRelevantRecObject(const AnaEventC& event, const AnaRecObjectC& track) const{
  //**************************************************
#ifdef DEBUG
  std::cout << "TPCPIDSystematics::IsRelevantRecObject() " << std::endl;  
#endif
  (void)event;

  // True track should always exist
  if (!track.TrueObject) return false;

  AnaTrueParticleB* truePart = static_cast<AnaTrueParticleB*>(track.TrueObject);
  
  HypEnum hypo = GetPIDHypo(truePart->PDG);

  if (hypo != TPCPIDVariation::kNPULLS){
    return true;
  }
  
  return false;
}
