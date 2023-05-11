#include <stdio.h>
#include "TPCPIDPullMCCorrection.hxx"
#include "HighlandAnalysisUtils.hxx"
#include "VersioningUtils.hxx"

#include "HEPConstants.hxx"


//#define DEBUG


//********************************************************************
TPCPIDPullMCCorrection::TPCPIDPullMCCorrection(){
  //********************************************************************


  // Read the systematic source parameters from the data files: a special case of sharing the data file with systematics
  _sigma[TPCPIDVariation::kMuon]     = 
    new BinnedParams("TPCPIDMuonSigRatio",   BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _sigma[TPCPIDVariation::kElectron] = 
    new BinnedParams("TPCPIDEleSigRatio",    BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _sigma[TPCPIDVariation::kProton]   = 
    new BinnedParams("TPCPIDProtonSigRatio", BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _mean[TPCPIDVariation::kMuon]      = 
    new BinnedParams("TPCPIDMuonMeanDiff",   BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _mean[TPCPIDVariation::kElectron]  = 
    new BinnedParams("TPCPIDEleMeanDiff",    BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
  _mean[TPCPIDVariation::kProton]    = 
    new BinnedParams("TPCPIDProtonMeanDiff", BinnedParams::k2D_SYMMETRIC, versionUtils::ExtensionSyst());
}

//********************************************************************
void TPCPIDPullMCCorrection::Apply(AnaSpillC& spillBB){
  //********************************************************************

  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);

#ifdef DEBUG 
  std::cout << " TPCPIDPullMCCorrection::Apply(): IsMC " << spill.GetIsMC() << std::endl;  
#endif


  // No correction for data
  if (!spill.GetIsMC())
    return;

  // Loop over all bunches
  for (unsigned int i = 0; i < spill.Bunches.size(); i++) {

    AnaBunch* bunch = static_cast<AnaBunch*>(spill.Bunches[i]);
    AnaTrackB* allTpcTracks[NMAXPARTICLES];

    // Get all the tracks in the TPC
    int nTPC = anaUtils::GetAllTracksUsingDet(*bunch, SubDetId::kTPC, allTpcTracks);
    for (Int_t j = 0; j < nTPC; j++)
      ApplyVariation(allTpcTracks[j], _exp);
  }


#ifdef DEBUG 
  std::cout << "TPCPIDPullMCCorrection::Apply() end " << std::endl;  
#endif

}
  
//**************************************************
TPCPIDVariation::HypEnum TPCPIDPullMCCorrection::GetPIDHypo(Int_t PDG) const{
  //**************************************************
  
  Int_t PDG_abs = abs(PDG);
  
  switch (PDG_abs){
    case 13: // Muon
      return TPCPIDVariation::kMuon;
      break;
    case 211: // Pion
      return TPCPIDVariation::kPion;      
      break;
    case 11: // Electron
      return TPCPIDVariation::kElectron;
      break;
    case 2212: // Proton
      return TPCPIDVariation::kProton;
      break;
    case 321: 
      return TPCPIDVariation::kKaon;
      break;
    default:
      return TPCPIDVariation::kNPULLS;
      break;
  }

  return TPCPIDVariation::kNPULLS;
}

//********************************************************************
bool TPCPIDPullMCCorrection::GetPIDParams(const AnaTPCParticleB& tpcTrackB, 
      Float_t& dEdxExp, Float_t& dEdxSigma, 
      const AnaTrackB& track){
//********************************************************************
// Need true particle
  if (!track.GetTrueParticle()) return false; 

  // Get the expected dEdx and error on the dEdx depending on the true particle of the 
  // (global) track
 
  
  const AnaTPCParticle& tpcTrack = static_cast<const AnaTPCParticle&>(tpcTrackB);
  
  Int_t PDG = abs(track.GetTrueParticle()->PDG);
  
  TPCPIDVariation::HypEnum pidhypo = GetPIDHypo(PDG);
  
  switch (pidhypo){
    case TPCPIDVariation::kMuon: // Muon
      dEdxExp = (Float_t)tpcTrack.dEdxexpMuon;
      dEdxSigma = (Float_t)tpcTrack.dEdxSigmaMuon;
      break;    
    case TPCPIDVariation::kPion: // Pion
      dEdxExp = (Float_t)tpcTrack.dEdxexpPion;
      dEdxSigma = (Float_t)tpcTrack.dEdxSigmaPion;
      break;
    case TPCPIDVariation::kElectron: // Electron
      dEdxExp = (Float_t)tpcTrack.dEdxexpEle;
      dEdxSigma = (Float_t)tpcTrack.dEdxSigmaEle;
      break;
    case TPCPIDVariation::kProton: // Proton
      dEdxExp = (Float_t)tpcTrack.dEdxexpProton;
      dEdxSigma = (Float_t)tpcTrack.dEdxSigmaProton;
      break;
    case TPCPIDVariation::kKaon: // Kaon
      dEdxExp = (Float_t)tpcTrack.dEdxexpKaon;
      dEdxSigma = (Float_t)tpcTrack.dEdxSigmaKaon;
      break;
    default:
      return false;
      break;
  }
  
  // Is it needed?
  if (dEdxSigma == -99999    || dEdxExp ==-99999)    return false;
  if (dEdxSigma == -0xABCDEF || dEdxExp ==-0xABCDEF) return false;

  return true; 
}


//********************************************************************
bool TPCPIDPullMCCorrection::GetVariation(const AnaTPCParticleB& tpcTrack, 
      Float_t& mean_var, Float_t& sigma_var, 
      const AnaTrackB& track, const ToyExperiment& exp){
  //******************************************************************** 

  // Get the TPC 
  int tpc = SubDetId::GetTPC(tpcTrack.Detector);
  
  // Need true particle
  if (!track.GetTrueParticle()) return false; 

  // Get the expected dEdx and error on the dEdx depending on the true particle of the 
  // (global) track
  
  TPCPIDVariation::HypEnum part = GetPIDHypo(track.GetTrueParticle()->PDG);
   
 
  // Pions are treated as muons in terms of errors
  if (part == TPCPIDVariation::kPion){
    part = TPCPIDVariation::kMuon;
  }
 
  // Non-valid hypothesis
  if (part == TPCPIDVariation::kNPULLS){
    return false;
  } 
  
  // Need the correction part from the systematics
  Float_t mean_err, sigma_err;

  // if dealing with kaons and want to use protons numbers` for kaons should
  // account for the scaling 
  Float_t Factor = 1.;
  
  if (part == TPCPIDVariation::kKaon){
    part = TPCPIDVariation::kProton;
    Factor *= (Float_t)units::GetPDGBase()->GetParticle(ParticleId::kProtonPDG)->Mass()/ 
      (Float_t)units::GetPDGBase()->GetParticle(ParticleId::kKPosPDG)->Mass();
  
  
  }

  if (!_mean[part] || !_sigma[part]) return false;
  
  // Note that the momentum changes if the mom resoltion, scale and bfield are also anabled.
	if (!_mean[part]->GetBinValues(track.Momentum * Factor, (Float_t) tpc, mean_var, mean_err))  return false;
	if (!_sigma[part]->GetBinValues(track.Momentum * Factor,(Float_t) tpc, sigma_var, sigma_err)) return false;

  return true;
}


