#include "ECalPhotonPileUpSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "ToyBoxTracker.hxx"
#include "MultiParticleBox.hxx"
#include "SystematicUtils.hxx"
#include "VersioningUtils.hxx"

//#define DEBUG

//********************************************************************
ECalPhotonPileUpSystematics::ECalPhotonPileUpSystematics():BinnedParams("ECalPhotonPileUp",k1D_EFF_SYMMETRIC, 
 versionUtils::ExtensionSyst()){
  //********************************************************************
  SetNParameters(GetNBins());
}

//********************************************************************
Weight_h ECalPhotonPileUpSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& eventBB, const ToyBoxB& boxB){
  //********************************************************************

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB); 

  // Cast the ToyBox to the appropriate type
  const ToyBoxTracker& box = *static_cast<const ToyBoxTracker*>(&boxB); 

  Weight_h eventWeight = 1;

  // Get the multi-particle box
  const multipart::MultiParticleBox* pionBox = box.GetMultiParticleBox();

  if (!pionBox)
    return eventWeight;

  BinnedParamsParams params;
  int index;

  if (!GetBinValues(anaUtils::GetRunPeriod(event.EventInfo.Run),params, index)) 
    return eventWeight;

  // Consider two cases
  // 1. ECal candidate is fake -- use "efficiency"
  // 2. No fake ECal candidate -- use "inefficiency"

  bool found = false;

  if (!pionBox->nECalPhotons)
    found = false;

  if (pionBox->nECalPhotons){
    // Get true vertex
    if (box.MainTrack){
      if (box.MainTrack->GetTrueParticle()){
        if (box.MainTrack->GetTrueParticle()->TrueVertex){
          // Get the true vertex position
          Float_t* pos = box.MainTrack->GetTrueParticle()->TrueVertex->Position;
          // Check that the truth vertex is in the FV
          if (anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(box.DetectorFV), pos)){

	  int nfound = 0;
	  for(int i = 0; i < pionBox->nECalPhotons; i++){
	    if (pionBox->ECalPhotons[i]->GetTrueParticle()){
	      AnaTrueParticleB* primary = anaUtils::GetTrueParticleFromTrueVertex(*box.MainTrack->GetTrueParticle()->TrueVertex,
		pionBox->ECalPhotons[i]->GetTrueParticle()->PrimaryID);
	      if(!primary && pionBox->ECalPhotons[i]->GetTrueParticle()->PrimaryID != -999) nfound = nfound + 1;
	    }
	  }

	  if(nfound) found = true;
	  else return eventWeight;

          }  
        }
      }
    }
  }


  eventWeight *= systUtils::ComputeEffLikeWeight(found, toy, GetIndex(), index, params);

#ifdef DEBUG
  std::cout << "Run: " << event.EventInfo.Run  
    << " index " << index << " variation " << toy.GetToyVariations(_index)->Variations[index] 
    << " weight " << eventWeight << std::endl;
#endif

  return eventWeight;

}

