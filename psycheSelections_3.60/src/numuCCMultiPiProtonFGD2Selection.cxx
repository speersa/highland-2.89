#include "numuCCMultiPiProtonFGD2Selection.hxx"

//*******************************************************************************
numuCCMultiPiProtonFGD2Selection::numuCCMultiPiProtonFGD2Selection(bool forceBreak): 
  numuCCMultiPiFGD2Selection(forceBreak){
  //*******************************************************************************

  _numuCCMultiPiProtonSelection.Initialize();
  
}

//*******************************************************************************
void numuCCMultiPiProtonFGD2Selection::DefineSteps(){
  //*******************************************************************************
  
  // Copy all steps from the numuCCSelection
  CopySteps(_numuCCFGD2Selection);

  //Additional actions for the multi-pi proton selection.
  
  AddStep(StepBase::kAction, "find_pions",           new FindPionsAction());
  AddStep(StepBase::kAction, "find_protons",         new FindProtonsAction());
  
  // Update pion and proton iso momentum vars to the vertex
 
  AddStep(StepBase::kAction, "set_vertex_to_box",                 new SetVertexToBoxAction());
  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex", new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",   new FillFgdIsoPionsKinVertexAction());
  
  
  AddStep(StepBase::kAction, "fill_summary_multiPiProtonFGD2", new FillSummaryAction_numuCCMultiPiProtonFGD2());
  
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
bool numuCCMultiPiProtonFGD2Selection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

   //CC0pi0Protons
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0Pi0Protons;
  }  
  //CC0piNProtons
  if(allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiNProtons; 
  } 
  //CC1pi
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC1Pi;
  }
  //CCOther
  else if (allCutsPassed[3]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCCOther;
  }
  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}


//*********************************************************************
bool FillSummaryAction_numuCCMultiPiProtonFGD2::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 


  if (!box.HMNtrack) return true;
   
 
  SampleId::SampleEnum SamplesUsed[4] = {
    SampleId::kFGD2NuMuCC0Pi0Protons,
    SampleId::kFGD2NuMuCC0PiNProtons,
    SampleId::kFGD2NuMuCC1Pi,
    SampleId::kFGD2NuMuCCOther
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
bool numuCCMultiPiProtonFGD2Selection::IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiProtonSelection.IsRelevantRecObjectForSystematic(event,track,systId,branch);
}

//**************************************************
bool numuCCMultiPiProtonFGD2Selection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiProtonSelection.IsRelevantTrueObjectForSystematic(event,trueTrack,systId,branch);
}


//**************************************************
Int_t numuCCMultiPiProtonFGD2Selection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiProtonSelection.GetRelevantRecObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
Int_t numuCCMultiPiProtonFGD2Selection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiProtonSelection.GetRelevantTrueObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
bool numuCCMultiPiProtonFGD2Selection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _numuCCMultiPiProtonSelection.IsRelevantSystematic(event,box,systId,branch);
}
//**************************************************
bool numuCCMultiPiProtonFGD2Selection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _numuCCMultiPiProtonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, branch);
}

//**************************************************
bool numuCCMultiPiProtonFGD2Selection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiProtonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, branch);
}

