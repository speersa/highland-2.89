#include "FGDPIDMIPLikeCorrection.hxx"
#include "DataClasses.hxx"
#include "HighlandAnalysisUtils.hxx"

//********************************************************************
FGDPIDMIPLikeCorrection::FGDPIDMIPLikeCorrection() :  CorrectionBase() {
//********************************************************************
}

//********************************************************************
void FGDPIDMIPLikeCorrection::Apply(AnaSpillC& spillBB) {
//********************************************************************

  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);

  for (unsigned int i = 0; i < spill.Bunches.size(); i++) {
    AnaTrackB* tracks[NMAXPARTICLES];
    AnaBunch* bunch = static_cast<AnaBunch*>(spill.Bunches[i]);
    int nFGD = anaUtils::GetAllTracksUsingDet(*bunch, SubDetId::kFGD,  tracks);
    for (Int_t j = 0; j < nFGD; j++) {
      AnaTrack* track = static_cast<AnaTrack*>(tracks[j]);
      if (!track){
        continue;
      }
      
      for (int i = 0; i < track->nFGDSegments; i++){
        if (!track->FGDSegments[i])
          continue;
        AnaFGDParticle* fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[i]);
      
        // MIP-like: based on
        // https://www.t2k.org/nd280/physics/SystematicsAndSelection/Meetings/ssv2022/14012022/NC1pi_syst_update/view
        fgdTrack->PIDMIPLike = fgdTrack->E - fgdTrack->X/6.5;
      }
    }
    
  }

}

