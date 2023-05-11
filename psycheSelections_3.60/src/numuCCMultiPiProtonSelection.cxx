#include "numuCCMultiPiProtonSelection.hxx"
#include "SystematicTuning.hxx"

/// This is the method where the actual steps are added to the selection
/// \anchor numuCCMultiPiProtonSelection_DefineSteps
//*******************************************************************************
void numuCCMultiPiProtonSelection::DefineSteps(){
  //*******************************************************************************

  // Copy all steps from the numuCCSelection
  CopySteps(_numuCCSelection);

  //Additional actions for the multi-pi proton selection.

  AddStep(StepBase::kAction, "find_pions",           new FindPionsAction());
  AddStep(StepBase::kAction, "find_protons",         new FindProtonsAction());

  // Update pion and proton iso momentum vars to the vertex

  AddStep(StepBase::kAction, "set_vertex_to_box",                 new SetVertexToBoxAction());
  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex", new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",   new FillFgdIsoPionsKinVertexAction());


  AddStep(StepBase::kAction, "fill_summary_multiPiProton", new FillSummaryAction_numuCCMultiPiProton());

  //Add a split to the trunk with 4 branches.
  AddSplit(4);

  // First branch is for CC-0pi0Protons
  AddStep(0, StepBase::kCut, "CC-0pi",        new NoPionCut());


  AddStep(0, StepBase::kCut, "Zero Protons",  new ZeroProtonsCut());

  // Second branch is for CC-0piNProtons
  AddStep(1, StepBase::kCut, "CC-0pi",        new NoPionCut());


  AddStep(1, StepBase::kCut, "N Protons",     new NProtonsCut());  

  // Third branch is for CC-1pi: true -- Positive pion
  AddStep(2, StepBase::kCut, "CC-1pi",        new OnePionCut(true));


  // Fourth branch is for CC-Other
  AddStep(3, StepBase::kCut, "CC-Other", new OthersCut());

  // Set the branch aliases to the three branches
  SetBranchAlias(0,"CC-0pi-0p",  0);
  SetBranchAlias(1,"CC-0pi-Np",  1);
  SetBranchAlias(2,"CC-1pi",     2);
  SetBranchAlias(3,"CC-Other",   3);

  // By default the preselection correspond to cuts 0-2
  SetPreSelectionAccumLevel(2);

}


//********************************************************************
bool numuCCMultiPiProtonSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

  //CC0pi0Protons
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0Pi0Protons;
  }  
  //CC0piNProtons
  if(allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiNProtons; 
  } 
  //CC1pi
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1Pi;
  }
  //CCOther
  else if (allCutsPassed[3]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOther;
  }
  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}


//*********************************************************************
bool FillSummaryAction_numuCCMultiPiProton::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 


  if (!box.HMNtrack) return true;



  SampleId::SampleEnum SamplesUsed[4] = {
    SampleId::kFGD1NuMuCC0Pi0Protons,
    SampleId::kFGD1NuMuCC0PiNProtons,
    SampleId::kFGD1NuMuCC1Pi,
    SampleId::kFGD1NuMuCCOther
  };


  // Loop over samples
  for (int i = 0; i < 4; i++){
    
    
    SampleId::SampleEnum iSample= SamplesUsed[i];
    
    
    static_cast<AnaEventSummaryB*>(event.Summary)->LeptonCandidate[iSample] = box.HMNtrack;
  
  
  
    static_cast<AnaEventSummaryB*>(event.Summary)->PionCandidate[iSample] = 
      box.pionBox.GetHMPion(static_cast<AnaEventSummaryB*>(event.Summary)->PionMomentum[iSample], 
          static_cast<AnaEventSummaryB*>(event.Summary)->PionDirection[iSample]);
    
    
    static_cast<AnaEventSummaryB*>(event.Summary)->ProtonCandidate[iSample] = 
      box.pionBox.GetHMProton(static_cast<AnaEventSummaryB*>(event.Summary)->ProtonMomentum[iSample], 
        static_cast<AnaEventSummaryB*>(event.Summary)->ProtonDirection[iSample]);
  
    for (int i = 0; i < 4; ++i){
      static_cast<AnaEventSummaryB*>(event.Summary)->VertexPosition[iSample][i]  = box.HMNtrack->PositionStart[i];
    }
    
    if (box.HMNtrack->GetTrueParticle()){
      static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[iSample] = box.HMNtrack->GetTrueParticle()->TrueVertex;
    }

  
    // Topologies
    static_cast<AnaEventSummaryB*>(event.Summary)->SelPionTopo[iSample]   = box.pionBox.GetPionTopo();
    static_cast<AnaEventSummaryB*>(event.Summary)->SelProtonTopo[iSample] = box.pionBox.GetProtonTopo();
  } 


  return true;
}

//**************************************************
bool numuCCMultiPiProtonSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************

  (void)event;
  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);

  switch (systId){
      // TPC reco
    case SystId::kChargeIDEff:
    case SystId::kTpcClusterEff:
    case SystId::kTpcTrackEff:
      // FGD
    case SystId::kFgdHybridTrackEff:
    case SystId::kMichelEleEff:
      // TPC matching
    case SystId::kTpcFgdMatchEff:
      // Normalization
    case SystId::kPileUp:
    case SystId::kFgdMass:
    case SystId::kOOFV:
    case SystId::kSandMu:
      // Flux
    case SystId::kFluxWeight:
      // SI
    case SystId::kSIPion:
    case SystId::kSIProton:
      return true;
      break;
    default:
      return false;
      break;
  }

  return false;
}


//**************************************************
bool numuCCMultiPiProtonSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, 
    const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  if (!track) return false;

  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true; 

  // all CC inclusive cases
  // This will also take care of the "main" track 
  if (_numuCCSelection.IsRelevantSystematic (event, box, systId, branch) && 
      _numuCCSelection.IsRelevantRecObjectForSystematicInToy(event,box,track,systId,branch)) return true;

  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);

  switch (systId){
    // Fall back through the relevant ones
    // TPC reco
    case SystId::kChargeIDEff:
      // TPC matching
    case SystId::kTpcFgdMatchEff:

      // Use the APPLY_SYST_FINE_TUNING concept as well,  since we worry about the "main" track that defines the topology
      if (branch == 1)
      {
        if (ccmultipibox->pionBox.nProtonTPCtracks==1 && track==ccmultipibox->pionBox.ProtonTPCtracks[0]) return true;
      }
      else if (branch == 2){
        // For CC-1pi also the positive Pion in the TPC matters
        if (ccmultipibox->pionBox.nPositivePionTPCtracks==1 && track==ccmultipibox->pionBox.PositivePionTPCtracks[0]) return true; 
      }
      else if (branch == 3){
        // For CC-Other consider the negative pion when there are no other pions
        if (ccmultipibox->pionBox.nNegativePionTPCtracks==1 && track==ccmultipibox->pionBox.NegativePionTPCtracks[0] && 
            ccmultipibox->pionBox.nOtherPions==1 && ccmultipibox->pionBox.nPosPions == 0) return true;  

      }
      // Failed above + 
      // CC0pi explicit false (should have been covered by numuCC if tuning is ON)
      return false;
      break;
      // The rest of the systematics go here, tuning to come
    default:
      return true;
      break;
  }

  return true;

}


//**************************************************
bool numuCCMultiPiProtonSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);

  AnaTrueParticleB* trueTrack = static_cast<AnaTrueParticleB*>(trueObj);
  if (!trueTrack) return false;

  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true;

  // All CC inclusive cases
  // MAIN track mode is taken into account there
  if (_numuCCSelection.IsRelevantSystematic (event, box, systId, branch) && 
      _numuCCSelection.IsRelevantTrueObjectForSystematicInToy(event,box,trueTrack,systId,branch)) return true;

  switch (systId){
    case SystId::kTpcTrackEff:

      // Don't consider pions when there are many TPC ones (a conservative check)
      // Cases in which we must loose two or more pions are excluded (0.01*0.01 probability)
      if (ccmultipibox->pionBox.nNegativePionTPCtracks+ccmultipibox->pionBox.nPositivePionTPCtracks > 2 ||
          ccmultipibox->pionBox.nNegativePionTPCtracks > 1) return false; 

      //For proton samples we have to consider protons
      if(branch == 0 || branch == 1)
      {
        if (abs(trueTrack->PDG)==211 || abs(trueTrack->PDG)==13 || abs(trueTrack->PDG)==11 || abs(trueTrack->PDG)==2212) return true;  
      }
      // If the are few TPC pions consider them, muons and electrons
      if (abs(trueTrack->PDG)==211 || abs(trueTrack->PDG)==13 || abs(trueTrack->PDG)==11) return true;  

      return false;
      break;

      // SI
    case SystId::kSIPion:

      // No Pion SI systematic when there are many pions 
      if (ccmultipibox->pionBox.nOtherPions >1 || ccmultipibox->pionBox.nPosPions > 2 ) return false; 
      return true;
      break;

      // Contributors for relevant objects for proton SI
    case SystId::kSIProton:
      // Main track is done by numuCC

      //Proton Samples requiers sliglhy different treatment
      //If event has more than one proton turn off, because it is unlikely SI will change topology, otherwise true
      if(branch == 0 || branch == 1)
      {
        if( (ccmultipibox->pionBox.nProtonTPCtracks+ccmultipibox->pionBox.nProtonFGDtracks)> 1 ) return false;
        else return true;
      }
      // If there are  many pions, i.e. topology cannot change, then do not use
      // the systematic
      if (ccmultipibox->pionBox.nOtherPions >1 || ccmultipibox->pionBox.nPosPions > 2 ) return false; 
      // Otherwise check that a pion contributes to any of the objects in the
      // box

      return cutUtils::numuCCTrkMultiPi::CheckTrueCausesBoxSimple(*trueTrack, ccmultipibox->pionBox);
      break; 

    case SystId::kFgdHybridTrackEff:
      // True track should start in the FGD FV of interest
      // Probably can imporve more by requiring that a track corresponds to the
      // selected true vertex
      return anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()), 
          trueTrack->Position); 
      break;

    default:
      return true;
      break;
  }

  // For the rest of the systematic return true
  return true;
}

