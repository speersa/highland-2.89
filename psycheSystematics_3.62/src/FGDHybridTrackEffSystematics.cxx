#include "FGDHybridTrackEffSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "EventBoxTracker.hxx"
#include "SystematicUtils.hxx"
#include "ToyBoxTracker.hxx"
#include "SystId.hxx"
#include "EventBoxId.hxx"
#include "VersioningUtils.hxx"


//********************************************************************
FGDHybridTrackEffSystematics::FGDHybridTrackEffSystematics(bool comp):EventWeightBase(1){
//********************************************************************

  _computecounters=comp;
  
  /// Important to note! we will use the following scheme
  /// Main track is a true muon - use FHC numbers
  /// Main track is a true antimuon - use RHC numbers 
  /// Main track is not an (anti)muon and we are in FHC - use FHC numbers
  /// Main track is not an (anti)muon and we are in RHC - use RHC numbers 
  
  _fgd1_fhc = new BinnedParams("FGD1HybridTrackEff_FHC", BinnedParams::k2D_EFF_ASSYMMETRIC, versionUtils::ExtensionSyst());
  _fgd2_fhc = new BinnedParams("FGD2HybridTrackEff_FHC", BinnedParams::k2D_EFF_ASSYMMETRIC, versionUtils::ExtensionSyst());
  _fgd1_rhc = new BinnedParams("FGD1HybridTrackEff_RHC", BinnedParams::k2D_EFF_ASSYMMETRIC, versionUtils::ExtensionSyst());
  _fgd2_rhc = new BinnedParams("FGD2HybridTrackEff_RHC", BinnedParams::k2D_EFF_ASSYMMETRIC, versionUtils::ExtensionSyst());

  SetNParameters(
      systUtils::GetNumberSystParams(*_fgd1_fhc, true) + 
      systUtils::GetNumberSystParams(*_fgd2_fhc, true) +
      systUtils::GetNumberSystParams(*_fgd2_rhc, true) +
      systUtils::GetNumberSystParams(*_fgd2_rhc, true)
      );
    
  if(_computecounters){
    _fgd1_fhc->InitializeEfficiencyCounter();
    _fgd2_fhc->InitializeEfficiencyCounter();
    _fgd1_rhc->InitializeEfficiencyCounter();
    _fgd2_rhc->InitializeEfficiencyCounter();
  }
}

//******************************************************************** 
void FGDHybridTrackEffSystematics::Print(Option_t *option) const{
  //******************************************************************** 
  (void)option;

  std::cout << " ***** Bins for the FGDHybridTrackEffSystematics **** " << std::endl;
  std::cout << " ***** For bin throw 2 params in case to vary both MC and data efficiencies (used depending on the parameter)  **** " << std::endl;
  
  unsigned int offset = 0;

  std::cout << " Bins for _fgd1 FHC " << std::endl;
  _fgd1_fhc->Print(offset); 

  offset += _fgd1_fhc->GetNBins();

  std::cout << " Bins for _fgd2 FHC " << std::endl;
  
  _fgd2_fhc->Print(offset); 
   
  offset += _fgd2_fhc->GetNBins();
   
  std::cout << " Bins for _fgd1 RHC " << std::endl;
  
  _fgd1_rhc->Print(offset); 
   
  offset += _fgd1_rhc->GetNBins();
  
  std::cout << " Bins for _fgd2 RHC " << std::endl;
  
  _fgd2_rhc->Print(offset); 
   
  std::cout << " ********* " << std::endl;

}  



//********************************************************************
void FGDHybridTrackEffSystematics::Initialize(){
//********************************************************************
 
  //Register BinnedParams to get proper offsets
  
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd1_fhc, systUtils::GetNumberSystParams(*_fgd1_fhc, true));
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd2_fhc, systUtils::GetNumberSystParams(*_fgd2_fhc, true));
  
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd1_rhc, systUtils::GetNumberSystParams(*_fgd1_rhc, true));
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd2_rhc, systUtils::GetNumberSystParams(*_fgd2_rhc, true)); 
}


//********************************************************************
Weight_h FGDHybridTrackEffSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& boxB){
//********************************************************************

  Weight_h eventWeight=1; 
  BinnedParamsParams params;

  // Cast the ToyBox to the appropriate type
  const ToyBoxTracker& box = *static_cast<const ToyBoxTracker*>(&boxB); 

  // Get the SystBox for this event, and the appropriate selection and branch
  SystBoxB* SystBox = GetSystBox(event,box.SelectionEnabledIndex,box.SuccessfulBranch);

  if(_computecounters){
    _fgd1_fhc->InitializeEfficiencyCounter();
    _fgd2_fhc->InitializeEfficiencyCounter();
    _fgd1_rhc->InitializeEfficiencyCounter();
    _fgd2_rhc->InitializeEfficiencyCounter();
  }
  
  // Get the direction of the main track
  AnaTrackB *maintrack = box.MainTrack;	
  if(!maintrack)  return eventWeight;
  
  
  BinnedParams* hybrid_params = GetBinnedParams(*maintrack, event, box.DetectorFV);
  
  if (!hybrid_params){
    return eventWeight;
  }
  
  if (box.DetectorFV != SubDetId::kFGD1 && 
      box.DetectorFV != SubDetId::kFGD2){
    return eventWeight;
  }
  
  for (Int_t itrue=0;itrue< SystBox->nRelevantTrueObjects; itrue++){      
    AnaTrueParticleB* trueTrack = static_cast<AnaTrueParticleB*>(SystBox->RelevantTrueObjects[itrue]);            

    // TODO by now the reco track associated to the true is the first one found, we should use instead a criteria to decide.
    // by now since it's very rare it's like that.
    // retrieve the reconstructed track associated
    AnaTrackB* recoTrack = static_cast<AnaTrackB*>(SystBox->RelevantTrueObjectsReco[itrue]);

    // Get the cos (theta), where theta is the angle between the main track and the FGD track
    Float_t costheta = 0;
    if (recoTrack)
      costheta = anaUtils::ScalarProduct(maintrack->DirectionStart, recoTrack->DirectionStart);
    else
      costheta = anaUtils::ScalarProduct(maintrack->DirectionStart, trueTrack->Direction);

    Float_t pdg = (Float_t)trueTrack->PDG;
    bool found = (recoTrack);
    
    // Get the FGD tracking efficiency
    Int_t index = -1;
   
    if (!hybrid_params->GetBinValues(fabs(pdg),costheta, params, index)) continue;
    
    // save the index of the varied parameters into the systematics box
    if(_computecounters){
      hybrid_params->UpdateEfficiencyCounter(index, found); 
    }
      
    // Add proper offset to the index
    index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *hybrid_params);
      
    
    eventWeight *= systUtils::ComputeEffLikeWeight(found, toy, GetIndex(), index, params);
  }

  return eventWeight;

}

//********************************************************************
bool FGDHybridTrackEffSystematics::IsRelevantTrueObject(const AnaEventC& event, const AnaTrueObjectC& trueTrack) const{
//********************************************************************

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  //we should not take into account the tracks that are matched to the tpc,
  //this is done in tpc-fgd matching efficiency  
  for (Int_t i=0;i<EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPC];i++){
    AnaRecObjectC* track = EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPC][i];
    if (CheckTrueRecoAssociation(trueTrack, *track))
      return false;
  }

  return true;
}

//********************************************************************
BinnedParams* FGDHybridTrackEffSystematics::GetBinnedParams(const AnaTrackB& track, const AnaEventC& eventBB, const SubDetId_h det){
//********************************************************************
 
  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB); 
  
  
  // Check the run mode
  
  bool isFHC = true;
  if (anaUtils::IsRHC(anaUtils::GetRunPeriod(event.EventInfo.Run)))
    isFHC = false;
  
  // Check the proper lepton
  Int_t PDG = 0; 
  
  if (track.GetTrueParticle()){
    PDG = track.GetTrueParticle()->PDG;
  }
    
  if (det == SubDetId::kFGD1){
    /// Main track is a true muon - use FHC numbers
    if (PDG == 13){
      return _fgd1_fhc;
    }
    /// Main track is a true antimuon - use RHC numbers
    else if (PDG == -13){
      return _fgd1_rhc;
    }
    /// Main track is not an (anti)muon and we are in FHC - use FHC numbers
    else if (isFHC){
      return _fgd1_fhc;
    }
    /// Main track is not an (anti)muon and we are in RHC - use RHC numbers 
    else if (!isFHC){
      return _fgd1_rhc;
    }
  }
  else if (det == SubDetId::kFGD2){
    /// Main track is a true muon - use FHC numbers
    if (PDG == 13){
      return _fgd2_fhc;
    }
    /// Main track is a true antimuon - use RHC numbers
    else if (PDG == -13){
      return _fgd2_rhc;
    }
    /// Main track is not an (anti)muon and we are in FHC - use FHC numbers
    else if (isFHC){
      return _fgd2_fhc;
    }
    /// Main track is not an (anti)muon and we are in RHC - use RHC numbers 
    else if (!isFHC){
      return _fgd2_rhc;
    }
  }
  
  return NULL;

}
