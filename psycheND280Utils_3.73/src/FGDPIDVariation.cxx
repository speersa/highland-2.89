#include "FGDPIDVariation.hxx"

//#define DEBUG

//**************************************************
void FGDPIDVariation::ApplyVariation(AnaTrackB* track, const ToyExperiment& exp){
  //**************************************************


#ifdef DEBUG
  std::cout << " FGDPIDVariation::ApplyVariation(): start " << std::endl;  
#endif

  // Check track validity
  if (!track) return;

  // Do not do anything if a track does not use an FGD
  if (track->nFGDSegments == 0) return;


  // Loop over FGD segments
  for (int k = 0; k < track->nFGDSegments; k++) {

    if (!track->FGDSegments[k]) continue;

    // The segment to be modified
    AnaFGDParticleB* fgdTrack = track->FGDSegments[k];
 
    Int_t pdg = ParticleId::kInvalidPDG;

    // Retrieve the PDG
    if (fgdTrack->GetTrueParticle()) {
      
      pdg = GetPDG(*fgdTrack->GetTrueParticle());
      
#ifdef DEBUG
      std::cout << " FGDPIDVariation::ApplyVariation(): pdg from local " << pdg << std::endl;  
#endif
    }
    
    // Failed from local
    if (pdg == ParticleId::kInvalidPDG){

#ifdef DEBUG
      std::cout << " FGDPIDVariation::ApplyVariation(): failed pdg from local,  use global " << std::endl;  
#endif
      if (track->GetTrueParticle()){
        pdg = GetPDG(*track->GetTrueParticle());
      }
    }

#ifdef DEBUG
      std::cout << " FGDPIDVariation::ApplyVariation(): pdg  " << pdg << std::endl;  
#endif

    if (pdg == ParticleId::kInvalidPDG){
      return;

    }

    // The un-corrected FGD track  
    const AnaFGDParticleB* original = static_cast<const AnaFGDParticleB*>(fgdTrack->Original);

    if (!original) continue; 
    
    // Apply the actual variation

#ifdef DEBUG
    // Get the pulls prior to variation
    Float_t pullpi0 = fgdTrack->Pullpi;
    Float_t pullmu0 = fgdTrack->Pullmu;
    Float_t pullp0  = fgdTrack->Pullp;
    Float_t pulle0  = fgdTrack->Pulle;
#endif
   
    // Params to vary pulls
    Float_t pull_mean, mean_var, sigma_var;
   
    // Loop over PDG hypos
    for (unsigned int i = 0; i < 4; i++){
     
      if (!GetVariation(pdg, *fgdTrack, pdg_hypos[i],  pull_mean, mean_var, sigma_var, exp)){
       continue; 
      }
      
#ifdef DEBUG
      std::cout << " FGDPIDVariation::ApplyVariation(): variation params for pdg " << pdg_hypos[i] << std::endl; 
      std::cout << " pull_mean " << pull_mean << std::endl;
      std::cout << " mean_var "  << mean_var  << std::endl;
      std::cout << " sigma_var " << sigma_var << std::endl;
#endif
    
      // Set the variation
      SetVariedPull(fgdTrack, pdg_hypos[i], pull_mean, mean_var, sigma_var);
      
#ifdef DEBUG
    std::cout << " FGDPIDVariation::ApplyVariation(): Results intermediate for pdg_hypo: " << pdg_hypos[i] << std::endl;  
    std::cout << " Input track PDG:\t " << pdg << std::endl;  
    std::cout << " Pullmu \t" << pullmu0 << " -->\t " <<  fgdTrack->Pullmu  << std::endl; 
    std::cout << " Pullpi \t" << pullpi0 << " -->\t " <<  fgdTrack->Pullpi  << std::endl; 
    std::cout << " Pullp  \t" << pullp0  << " -->\t " <<  fgdTrack->Pullp   << std::endl;
    std::cout << " Pulle  \t" << pulle0  << " -->\t " <<  fgdTrack->Pulle   << std::endl;
#endif
     
    }

#ifdef DEBUG
    std::cout << " FGDPIDVariation::ApplyVariation(): Results final: " << std::endl;  
    std::cout << " Input track PDG:\t " << pdg << std::endl;  
    std::cout << " Pullmu \t" << pullmu0 << " -->\t " <<  fgdTrack->Pullmu  << std::endl; 
    std::cout << " Pullpi \t" << pullpi0 << " -->\t " <<  fgdTrack->Pullpi  << std::endl; 
    std::cout << " Pullp  \t" << pullp0  << " -->\t " <<  fgdTrack->Pullp   << std::endl;
    std::cout << " Pulle  \t" << pulle0  << " -->\t " <<  fgdTrack->Pulle   << std::endl;
#endif
  
  }

#ifdef DEBUG
  std::cout << " FGDPIDVariation::ApplyVariation(): end \n " << std::endl;  
#endif


}
//**************************************************
void FGDPIDVariation::UpdatePull(
    Float_t& pull,
    const Float_t& pull_mean, 
    const Float_t& mean_var, 
    const Float_t& sigma_var){
  //**************************************************

   // Vary based on mean
   pull += mean_var;

   // Vary based on sigma ratio
   pull =  pull_mean + (pull - pull_mean) * sigma_var; 

}

//**************************************************
void FGDPIDVariation::SetVariedPull(
    AnaFGDParticleB* fgdTrack,
    Int_t pdg_hypo, 
    const Float_t& pull_mean, 
    const Float_t& mean_var, 
    const Float_t& sigma_var){
  //**************************************************
 
  if(!fgdTrack){
    return;  
  }
  Float_t* pull = NULL;
  
  switch (pdg_hypo){
    case ParticleId::kMuonPDG:
      pull = &fgdTrack->Pullmu;
      break;
    case ParticleId::kPionPosPDG:
      pull = &fgdTrack->Pullpi;
      break;
    case ParticleId::kProtonPDG:
      pull = &fgdTrack->Pullp;
      break; 
    case ParticleId::kElectronPDG:
      pull = &fgdTrack->Pulle;
      break; 
    default:
      break;
  }
  
  if (pull == NULL){
    return;
  }

  UpdatePull(*pull, pull_mean, mean_var, sigma_var);
}

//**************************************************
Int_t FGDPIDVariation::GetPDG(const AnaTrueParticleB& track){ 
//**************************************************
  Int_t pdg = ParticleId::kInvalidPDG;

  // Treat muon and pion the same for the moment
  if (abs(track.PDG) == ParticleId::kMuonPDG){
    pdg = ParticleId::kMuonPDG;
  }
  if (abs(track.PDG) == ParticleId::kPionPosPDG){
    pdg = ParticleId::kPiPosPDG;
  }
  else if (abs(track.PDG) == ParticleId::kProtonPDG){
    pdg = ParticleId::kProtonPDG;
  }
  else if (abs(track.PDG) == ParticleId::kElectronPDG){
    pdg = ParticleId::kElectronPDG;
  }

  return pdg;

}




