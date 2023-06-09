#include "antiNumuCCMultiPiSelection.hxx"
#include "antiNumuCCSelection.hxx"
#include "baseSelection.hxx"
#include "CutUtils.hxx"
#include "EventBoxUtils.hxx"
#include "SubDetId.hxx"
#include "SystId.hxx"
#include "VersioningUtils.hxx"
#include "SystematicUtils.hxx"
#include "SystematicTuning.hxx"


//********************************************************************
antiNumuCCMultiPiSelection::antiNumuCCMultiPiSelection(bool forceBreak): SelectionBase(forceBreak,EventBoxId::kEventBoxTracker) {
  //********************************************************************
  _antiNumuCCSelection.Initialize();
  _numuCCMultiPiSelection.Initialize(); 
}

//********************************************************************
void antiNumuCCMultiPiSelection::DefineSteps(){
  //********************************************************************

  // Copy all steps from the antiNumuCCSelection
  CopySteps(_antiNumuCCSelection);

  //Pawel - Pions sele
  //Additional actions for the multi-pi selection.
  
  AddStep(StepBase::kAction, "find_pions",                new FindPionsAction_antinuCCMultiPi());
  AddStep(StepBase::kAction, "find_protons",              new FindProtonsAction());
  
  AddStep(StepBase::kAction, "set_vertex_to_box",                 new SetVertexToBoxAction());
  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex", new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",   new FillFgdIsoPionsKinVertexAction());
  
  
  AddStep(StepBase::kAction, "fill_summary antinu_pion",  new FillSummaryAction_antinuCCMultiPi());

  //Add a split to the trunk with 3 branches.
  AddSplit(3);

  //First branch is for CC-0pi
  AddStep(0, StepBase::kCut, "CC-0pi",        new NoPionCut());

  //Second branch is for CC-1pi
  AddStep(1, StepBase::kCut, "CC-1pi",        new OnePionCut(false));

  //Third branch is for CC-Other
  AddStep(2, StepBase::kCut, "CC-Other", new OthersCut());

  // Set the branch aliases to the three branches
  SetBranchAlias(0,"CC-0pi",  0);
  SetBranchAlias(1,"CC-1pi",  1);
  SetBranchAlias(2,"CC-Other",2);

  // By default the preselection correspond to cuts 0-2
  SetPreSelectionAccumLevel(2);

  // Step and Cut numbers needed by CheckRedoSelection
  _MuonPIDCutIndex     = GetCutNumber("muon PID");
  _FindPionsStepIndex  = GetStepNumber("find_pions");

}

//********************************************************************
void antiNumuCCMultiPiSelection::DefineDetectorFV(){
  //********************************************************************

  // The detector in which the selection is applied
  SetDetectorFV(SubDetId::kFGD1);
  
}

//********************************************************************
bool antiNumuCCMultiPiSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

  //taken from numuCCMultiPi
  //CC0pi
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1AntiNuMuCC0Pi;
  }  
  //CC1pi
  else if (allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1AntiNuMuCC1Pi;
  }
  //CCOther
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1AntiNuMuCCOther;
  }

  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}

//*********************************************************************
bool FillSummaryAction_antinuCCMultiPi::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 

  if (!box.HMPtrack) return true;
 

  SampleId::SampleEnum SamplesUsed[3] = {
    SampleId::kFGD1AntiNuMuCC0Pi, 
    SampleId::kFGD1AntiNuMuCC1Pi, 
    SampleId::kFGD1AntiNuMuCCOther
  };
  
  
  
  // Loop over samples
  for (int i = 0; i < 3; i++){
        
    
    
    SampleId::SampleEnum iSample= SamplesUsed[i];
    
    
    
    static_cast<AnaEventSummaryB*>(event.Summary)->LeptonCandidate[iSample] = box.HMPtrack;
  
  
  
    static_cast<AnaEventSummaryB*>(event.Summary)->PionCandidate[iSample] = 
      box.pionBox.GetHMPion(static_cast<AnaEventSummaryB*>(event.Summary)->PionMomentum[iSample], 
          static_cast<AnaEventSummaryB*>(event.Summary)->PionDirection[iSample]);
    
    
    static_cast<AnaEventSummaryB*>(event.Summary)->ProtonCandidate[iSample] = 
      box.pionBox.GetHMProton(static_cast<AnaEventSummaryB*>(event.Summary)->ProtonMomentum[iSample], 
        static_cast<AnaEventSummaryB*>(event.Summary)->ProtonDirection[iSample]);
  
    for (int i = 0; i < 4; ++i){
      static_cast<AnaEventSummaryB*>(event.Summary)->VertexPosition[iSample][i]  = box.HMPtrack->PositionStart[i];
    }
    
    if (box.HMPtrack->GetTrueParticle()){
      static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[iSample] = box.HMPtrack->GetTrueParticle()->TrueVertex;
    }

  
    // Topologies
    static_cast<AnaEventSummaryB*>(event.Summary)->SelPionTopo[iSample]   = box.pionBox.GetPionTopo();
    static_cast<AnaEventSummaryB*>(event.Summary)->SelProtonTopo[iSample] = box.pionBox.GetProtonTopo();
  } 

  

  
  return true;
}

//**************************************************
bool antiNumuCCMultiPiSelection::IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.IsRelevantRecObjectForSystematic(event,track,systId,branch);
}

//**************************************************
bool antiNumuCCMultiPiSelection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.IsRelevantTrueObjectForSystematic(event,trueTrack,systId,branch);
}

//**************************************************
bool antiNumuCCMultiPiSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  if (!track) return false;

  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);
  
  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true;

  // Check inclusive first
  if (_antiNumuCCSelection.IsRelevantSystematic (event, box, systId, branch) && 
      _antiNumuCCSelection.IsRelevantRecObjectForSystematicInToy(event,box,track,systId,branch)) return true;
  
  switch (systId){
    // Fall back through the relevant ones
    // TPC reco
    case SystId::kChargeIDEff:
      // TPC matching
    case SystId::kTpcFgdMatchEff:

      // Use the APPLY_SYST_FINE_TUNING concept as well,  since we worry about the "main" track that defines the topology 
      if (branch == 1){
        // For CC-1pi also the negative Pion in the TPC matters
        if (ccmultipibox->pionBox.nNegativePionTPCtracks == 1 && track==ccmultipibox->pionBox.NegativePionTPCtracks[0]) return true; 
      }
      else if (branch == 2){
        // For CC-Other consider the positive pion when there are no other pions
        if (ccmultipibox->pionBox.nPositivePionTPCtracks == 1 && track==ccmultipibox->pionBox.PositivePionTPCtracks[0] && 
            ccmultipibox->pionBox.nOtherPions == 1 && ccmultipibox->pionBox.nNegPions == 0) return true;  

      }
      // Failed above + 
      // CC0pi explicit false (should have been covered by numuCC if tuning is ON)
      return false;
      break;
      
    default:
      break;
  }
  
  // The rest of the systematics gets tuning from numu multi-pi
  return _numuCCMultiPiSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, branch);

}


//**************************************************
bool  antiNumuCCMultiPiSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);
  
  AnaTrueParticleB* trueTrack = static_cast<AnaTrueParticleB*>(trueObj);
  if (!trueTrack) return false;
  
  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true;

  // all CC inclusive cases
  // MAIN track mode is taken into account there
  if (_antiNumuCCSelection.IsRelevantSystematic (event, box, systId, branch) && 
      _antiNumuCCSelection.IsRelevantTrueObjectForSystematicInToy(event,box,trueTrack,systId,branch)) return true;

  switch (systId){
    case SystId::kTpcTrackEff:
      
      // Don't consider pions when there are many TPC ones (a conservative check)
      // Cases in which we must loose two or more pions are excluded (0.01*0.01 probability)
      if (ccmultipibox->pionBox.nNegativePionTPCtracks+ccmultipibox->pionBox.nPositivePionTPCtracks > 2 ||
          ccmultipibox->pionBox.nPositivePionTPCtracks > 1) return false; 
      
      // If the are few TPC pions consider them, muons and electrons 
      if (abs(trueTrack->PDG)==211 || abs(trueTrack->PDG)==13 || abs(trueTrack->PDG)==11) return true;  
      
      return false;
      break;
      
    // SI
    case SystId::kSIPion:
      // No Pion SI systematic when there are many pions 
      if (ccmultipibox->pionBox.nOtherPions >1 || ccmultipibox->pionBox.nNegPions > 2 ) return false; 
      return true;
      break;
    
    // Contributors for relevant objects for proton SI
    case SystId::kSIProton:
     
      // Main track is done by numuCC
      // If there are  many pions, i.e. topology cannot change, then do not use
      // the systematic
      if (ccmultipibox->pionBox.nOtherPions >1 || ccmultipibox->pionBox.nNegPions > 2 ) return false; 
      // Otherwise check that a pion contributes to any of the objects in the
      // box
      return cutUtils::numuCCTrkMultiPi::CheckTrueCausesBoxSimple(*trueTrack, ccmultipibox->pionBox);
      break;
    default:
      break;
  }

  // For the rest of the systematic use numuCC multi-pion tuning
  return _numuCCMultiPiSelection.IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, branch);

}

//**************************************************
bool antiNumuCCMultiPiSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.IsRelevantSystematic(event, box, systId, branch);
}

//**************************************************
Int_t antiNumuCCMultiPiSelection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
//**************************************************

  return _numuCCMultiPiSelection.GetRelevantRecObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
Int_t antiNumuCCMultiPiSelection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
//**************************************************

  return _numuCCMultiPiSelection.GetRelevantTrueObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
void antiNumuCCMultiPiSelection::InitializeEvent(AnaEventC& eventC){
  //**************************************************

  AnaEventB& event = *static_cast<AnaEventB*>(&eventC); 
  
  _antiNumuCCSelection.InitializeEvent(event); 
  
  boxUtils::FillTracksWithECal(event);
  boxUtils::FillFGDMichelElectrons(event, (SubDetId::SubDetEnum)GetDetectorFV());
  
  boxUtils::FillTrajsInECal(event);
}

//********************************************************************
bool antiNumuCCMultiPiSelection::CheckRedoSelection(const AnaEventC& event, const ToyBoxB& PreviousToyBox, Int_t& redoFromStep){
  //********************************************************************

  // Must redo selection if antiNumuCCSelection decides so
  if( _antiNumuCCSelection.CheckRedoSelection(event,PreviousToyBox,redoFromStep)) return true;

  // Otherwise selection should not be redone since the number of tracks with TPC and FGD will not be changed by systematics
  return false;
}
