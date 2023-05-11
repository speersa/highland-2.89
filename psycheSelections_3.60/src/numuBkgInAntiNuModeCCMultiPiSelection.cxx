#include "numuBkgInAntiNuModeCCMultiPiSelection.hxx"
#include "numuBkgInAntiNuModeCCSelection.hxx"
#include "antiNumuCCMultiPiSelection.hxx"
#include "baseSelection.hxx"
#include "CutUtils.hxx"
#include "Parameters.hxx"
#include "SubDetId.hxx"
#include "EventBoxId.hxx"
#include "SystId.hxx"

//********************************************************************
numuBkgInAntiNuModeCCMultiPiSelection::numuBkgInAntiNuModeCCMultiPiSelection(bool forceBreak): SelectionBase(forceBreak,EventBoxId::kEventBoxTracker) {
  //********************************************************************

  // Initialize the numuCCMultiPiSelection, which is used
  _numuCCMultiPiSelection.Initialize();
}

//********************************************************************
void numuBkgInAntiNuModeCCMultiPiSelection::DefineSteps(){
  //********************************************************************

  // Copy all steps from the numuBkgInAntiNuModeCCSelection
  CopySteps(_numuBkgInAntiNuModeCCSelection);

  //Additional actions for the multi-pi selection.
  AddStep(StepBase::kAction, "find_pions",                     new FindPionsAction());
  AddStep(StepBase::kAction, "find_protons",                   new FindProtonsAction());
  
  AddStep(StepBase::kAction, "set_vertex_to_box",                 new SetVertexToBoxAction());
  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex", new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",   new FillFgdIsoPionsKinVertexAction()); 
  
  AddStep(StepBase::kAction, "fill summary numuBkg_CCMultiPi", new FillSummaryAction_numuBkg_CCMultiPi());  

  //Add a split to the trunk with 3 branches.
  AddSplit(3);

  //First branch is for CC-0pi
  AddStep(0, StepBase::kCut, "CC-0pi",        new NoPionCut());

  //Second branch is for CC-1pi
  AddStep(1, StepBase::kCut, "CC-1pi",        new OnePionCut(true));

  //Third branch is for CC-Other
  AddStep(2, StepBase::kCut, "CC-Other", new OthersCut());

  // Set the branch aliases to the three branches
  SetBranchAlias(0,"CC-0pi",0);
  SetBranchAlias(1,"CC-1pi",1);
  SetBranchAlias(2,"CC-Other",2);

  // By default the preselection correspond to cuts 0-2
  SetPreSelectionAccumLevel(2);
}

//********************************************************************
void numuBkgInAntiNuModeCCMultiPiSelection::DefineDetectorFV(){
  //********************************************************************

  // The detector in which the selection is applied
  SetDetectorFV(SubDetId::kFGD1);
}

//********************************************************************
bool numuBkgInAntiNuModeCCMultiPiSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

  //CC0pi
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuBkgInAntiNuModeCC0Pi;
  }  
  //CC1pi
  else if (allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuBkgInAntiNuModeCC1Pi;
  }
  //CCOther
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuBkgInAntiNuModeCCOther;
  }

  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}

//*********************************************************************
bool FillSummaryAction_numuBkg_CCMultiPi::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 

  if(!box.HMNtrack) return true;

  SampleId::SampleEnum SamplesUsed[3] = {
    SampleId::kFGD1NuMuBkgInAntiNuModeCC0Pi, 
    SampleId::kFGD1NuMuBkgInAntiNuModeCC1Pi, 
    SampleId::kFGD1NuMuBkgInAntiNuModeCCOther
  };
  
   // Loop over samples
  for (int i = 0; i < 3; i++){
   
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
bool numuBkgInAntiNuModeCCMultiPiSelection::IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.IsRelevantRecObjectForSystematic(event,track,systId,branch);
}

//**************************************************
bool numuBkgInAntiNuModeCCMultiPiSelection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.IsRelevantTrueObjectForSystematic(event,trueTrack,systId,branch);
}

//**************************************************
bool numuBkgInAntiNuModeCCMultiPiSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _numuCCMultiPiSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, branch);
}

//**************************************************
bool numuBkgInAntiNuModeCCMultiPiSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, branch);
}

//**************************************************
bool numuBkgInAntiNuModeCCMultiPiSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.IsRelevantSystematic(event, box, systId, branch);
}

//**************************************************
Int_t numuBkgInAntiNuModeCCMultiPiSelection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.GetRelevantRecObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
Int_t numuBkgInAntiNuModeCCMultiPiSelection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiSelection.GetRelevantTrueObjectGroupsForSystematic(systId, IDs, branch);
}


//**************************************************
void numuBkgInAntiNuModeCCMultiPiSelection::InitializeEvent(AnaEventC& event){
  //**************************************************

  _numuCCMultiPiSelection.InitializeEvent(event);
}

//********************************************************************
bool numuBkgInAntiNuModeCCMultiPiSelection::CheckRedoSelection(const AnaEventC& event, const ToyBoxB& PreviousToyBox, Int_t& redoFromStep){
  //********************************************************************

  // Must redo selection if _numuBkgInAntiNuModeCCSelection decides so
  if( _numuBkgInAntiNuModeCCSelection.CheckRedoSelection(event,PreviousToyBox,redoFromStep)) return true;

  // Otherwise selection should not be redone since the number of tracks with TPC and FGD will not be changed by systematics
  return false;
}

