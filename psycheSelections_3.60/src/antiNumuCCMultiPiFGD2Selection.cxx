#include "antiNumuCCMultiPiFGD2Selection.hxx"
#include "antiNumuCCMultiPiSelection.hxx"
#include "numuCCFGD2Selection.hxx"
#include "baseSelection.hxx"
#include "CutUtils.hxx"
#include "EventBoxUtils.hxx"
#include "Parameters.hxx"
#include "SubDetId.hxx"
#include "SystId.hxx"
#include "VersioningUtils.hxx"
#include "SystematicUtils.hxx"


//*******************************************************************************
antiNumuCCMultiPiFGD2Selection::antiNumuCCMultiPiFGD2Selection(bool forceBreak): SelectionBase(forceBreak,EventBoxId::kEventBoxTracker){
  //*******************************************************************************
  // Initialize selections being used
  _antiNumuCCFGD2Selection.Initialize();
  _antiNumuCCMultiPiSelection.Initialize();
}

//*******************************************************************************
void antiNumuCCMultiPiFGD2Selection::DefineSteps(){
  //*******************************************************************************

  // Copy all steps from the numuCCFGD2Selection
  CopySteps(_antiNumuCCFGD2Selection);

  //Additional actions for the multi-pi selection.
  AddStep(StepBase::kAction, "find_pions",               new FindPionsAction_antinuCCMultiPi());
  AddStep(StepBase::kAction, "find_protons",             new FindProtonsAction());
   
  AddStep(StepBase::kAction, "set_vertex_to_box",                 new SetVertexToBoxAction());
  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex", new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",   new FillFgdIsoPionsKinVertexAction()); 
  
  AddStep(StepBase::kAction, "fill_summary_multiPiFGD2", new FillSummaryAction_antiNumuCCMultiPiFGD2());
  
  //Add a split to the trunk with 3 branches.
  AddSplit(3);

  //First branch is for CC-0pi
  AddStep(0, StepBase::kCut, "CC-0pi",        new NoPionCut());

  //Second branch is for CC-1pi
  AddStep(1, StepBase::kCut, "CC-1pi",        new OnePionCut(false));

  //Third branch is for CC-Other
  AddStep(2, StepBase::kCut, "CC-Other",      new OthersCut());

  // Set the branch aliases to the three branches
  SetBranchAlias(0,"CC-0pi",0);
  SetBranchAlias(1,"CC-1pi",1);
  SetBranchAlias(2,"CC-Other",2);

  // By default the preselection correspond to cuts 0-2
  SetPreSelectionAccumLevel(2);
}


//*******************************************************************************
void antiNumuCCMultiPiFGD2Selection::DefineDetectorFV(){
  //*******************************************************************************

  // The detector in which the selection is applied
  SetDetectorFV(SubDetId::kFGD2);

}

//********************************************************************
bool antiNumuCCMultiPiFGD2Selection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

  //CC0pi
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2AntiNuMuCC0Pi;
  }  
  //CC1pi
  else if (allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2AntiNuMuCC1Pi;
  }
  //CCOther
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2AntiNuMuCCOther;
  }

  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}


//*********************************************************************
bool FillSummaryAction_antiNumuCCMultiPiFGD2::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 

  if (!box.HMPtrack) return true;


  SampleId::SampleEnum SamplesUsed[3] = {
    SampleId::kFGD2AntiNuMuCC0Pi, 
    SampleId::kFGD2AntiNuMuCC1Pi, 
    SampleId::kFGD2AntiNuMuCCOther
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
bool antiNumuCCMultiPiFGD2Selection::IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _antiNumuCCFGD2Selection.IsRelevantRecObjectForSystematic(event,track,systId,branch);
}

//**************************************************
bool antiNumuCCMultiPiFGD2Selection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _antiNumuCCFGD2Selection.IsRelevantTrueObjectForSystematic(event,trueTrack,systId,branch);
}

//**************************************************
bool antiNumuCCMultiPiFGD2Selection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _antiNumuCCMultiPiSelection.IsRelevantRecObjectForSystematicInToy(event, box, recObj, systId, branch);
}

//**************************************************
bool antiNumuCCMultiPiFGD2Selection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _antiNumuCCMultiPiSelection.IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, branch);
}


//**************************************************
bool antiNumuCCMultiPiFGD2Selection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _antiNumuCCMultiPiSelection.IsRelevantSystematic(event,box,systId,branch);
}

//**************************************************
Int_t antiNumuCCMultiPiFGD2Selection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
//**************************************************

  return _antiNumuCCMultiPiSelection.GetRelevantRecObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
Int_t antiNumuCCMultiPiFGD2Selection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
//**************************************************

  return _antiNumuCCMultiPiSelection.GetRelevantTrueObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
void antiNumuCCMultiPiFGD2Selection::InitializeEvent(AnaEventC& eventBB){
  //**************************************************

  AnaEventB& event = *static_cast<AnaEventB*>(&eventBB); 

  _antiNumuCCFGD2Selection.InitializeEvent(event);	
  boxUtils::FillTracksWithECal(event);
  boxUtils::FillFGDMichelElectrons(event, (SubDetId::SubDetEnum)GetDetectorFV());

  boxUtils::FillTrajsInECal(event);

}

//********************************************************************
bool antiNumuCCMultiPiFGD2Selection::CheckRedoSelection(const AnaEventC& event, const ToyBoxB& PreviousToyBox, Int_t& redoFromStep){
  //********************************************************************

  return _antiNumuCCMultiPiSelection.CheckRedoSelection(event, PreviousToyBox, redoFromStep);							    
}
