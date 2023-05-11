#include "FGDPIDMIPLikeSystematicsBase.hxx"
#include "SystematicUtils.hxx"
#include "ConstituentsUtils.hxx"

//#define DEBUG



//********************************************************************
void FGDPIDMIPLikeSystematicsBase::Apply(const ToyExperiment& toy, AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

#ifdef DEBUG
  std::cout << "FGDPIDMIPLikeSystematics::Apply(): tracks size " << box->nRelevantRecObjects << std::endl;  
#endif

  // Loop over relevant tracks for this systematic
  for (Int_t itrk = 0; itrk < box->nRelevantRecObjects; itrk++){
    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);
    ApplyVariation(track, toy);
  }
}

//********************************************************************
bool FGDPIDMIPLikeSystematicsBase::UndoSystematic(AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

  for (int itrk=0;itrk<box->nRelevantRecObjects;itrk++){
    for (int k = 0; k < static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk])->nFGDSegments; k++){
      
      // The new FGD track
      AnaFGDParticleB* fgdTrack0 = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk])->FGDSegments[k];
      
      AnaFGDParticle* fgdTrack = static_cast<AnaFGDParticle*>(fgdTrack0);
      
      // The original (corrected) fgd track
      const AnaFGDParticle* original = static_cast<const AnaFGDParticle*>(fgdTrack->Original);

      // revert to initial pulls
      fgdTrack->PIDMIPLike = original->PIDMIPLike;
    }
  }

  // Don't reset the spill to corrected
  return false;
}


//**************************************************
void FGDPIDMIPLikeSystematicsBase::ApplyVariation(AnaTrackB* track, const ToyExperiment& exp){
  //**************************************************


#ifdef DEBUG
  std::cout << " FGDPIDMIPLikeSystematics::ApplyVariation(): start " << std::endl;  
#endif

  // Check track validity
  if (!track) return;

  // Do not do anything if a track does not use an FGD
  if (track->nFGDSegments == 0) return;
  
  // Loop over FGD segments
  for (int k = 0; k < track->nFGDSegments; k++) {

    if (!track->FGDSegments[k]) continue;

    // The segment to be modified
    AnaFGDParticle* fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[k]);
    
    if (!fgdTrack)
      continue;

    // The un-corrected FGD track  
    const AnaFGDParticleB* original = static_cast<const AnaFGDParticleB*>(fgdTrack->Original);

    if (!original) continue; 
    
    // Apply the actual variation

#ifdef DEBUG
    // Get the FGD PID MIP Like prior to variation
    Float_t PIDMIPLike0 = fgdTrack->PIDMIPLike;
#endif

    
    Float_t pid_mean, mean_var, sigma_var;
    
    if (!GetVariation(*track, *fgdTrack, pid_mean, mean_var, sigma_var, exp)){
      
      continue; // for the moment depends on true info of the global track, not the TPC segment
    }

#ifdef DEBUG
    std::cout << " FGDPIDMIPLikeSystematics::ApplyVariation(): variation params" << std::endl; 
    std::cout << " pid_mean "  << pid_mean << std::endl;
    std::cout << " mean_var "  << mean_var  << std::endl;
    std::cout << " sigma_var " << sigma_var << std::endl;
#endif
    
  
    
    SetVariedPIDMIPLike(fgdTrack, pid_mean, mean_var, sigma_var);

#ifdef DEBUG
    std::cout << " FGDPIDMIPLikeSystematics::ApplyVariation(): Results: " << std::endl;  
    std::cout << " PIDMIPLike\t"  << PIDMIPLike0 << " -->\t " <<  fgdTrack->PIDMIPLike  << std::endl; 
#endif
  
  
  }

#ifdef DEBUG
  std::cout << " FGDPIDMIPLikeSystematics::ApplyVariation(): end \n " << std::endl;  
#endif


}


//**************************************************
void  FGDPIDMIPLikeSystematicsBase::SetVariedPIDMIPLike(AnaFGDParticle* fgdTrack, const Float_t& pid_mean, 
    const Float_t& mean_var, 
    const Float_t& sigma_var){
  //**************************************************

  if(!fgdTrack){
    return;  
  }

      
  // Vary based on mean
  fgdTrack->PIDMIPLike =  fgdTrack->PIDMIPLike + mean_var; 

  // Vary based on sigma ratio
  fgdTrack->PIDMIPLike =  pid_mean + (fgdTrack->PIDMIPLike - pid_mean) * sigma_var; 

  return;


}

