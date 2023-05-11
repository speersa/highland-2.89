#include "numuCCMultiPiPhotonFGD2Selection.hxx"
#include "SystematicTuning.hxx"

//*******************************************************************************
numuCCMultiPiPhotonFGD2Selection::numuCCMultiPiPhotonFGD2Selection(bool forceBreak): 
  numuCCMultiPiFGD2Selection(forceBreak){
  //*******************************************************************************
  _numuCCMultiPiPhotonSelection.Initialize();
}


/// \anchor numuCCMultiPiPhotonSelection_DefineSteps
//*******************************************************************************
void numuCCMultiPiPhotonFGD2Selection::DefineSteps(){
  //*******************************************************************************

  // Copy all steps from the numuCCSelection
  CopySteps(_numuCCFGD2Selection);

  AddStep(StepBase::kAction, "find_pions",           new FindPionsAction());
  AddStep(StepBase::kAction, "find_protons",         new FindProtonsAction());

  // Update pion and proton iso momentum vars to the vertex

  AddStep(StepBase::kAction, "set_vertex_to_box",                 new SetVertexToBoxAction());
  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex", new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",   new FillFgdIsoPionsKinVertexAction());


  // numuCCMultiPiPhoton Cuts and Actions
  AddStep(StepBase::kAction, "find_ecal_photons",   new FindECalPhotonsAction());

  AddStep(StepBase::kAction, "fill_summary_multiPiPhoton_FGD2", new FillSummaryAction_numuCCMultiPiPhotonFGD2());

  // Split into two branches for separating out photon-containing events
  AddSplit(2);

  // Add cuts to first branch to select CCPhoton
  AddStep(0, StepBase::kCut, "CC-Photon", new PhotonCut());

  // Opposite-acting cut on second branch to get events which fail photon selection:
  AddStep(1, StepBase::kCut, "No photons (TPC+ECal)", new InvertedStep(new PhotonCut()));

  // Split second branch into three for CC0pi, CC1pi+ and CCOther
  AddSplit(3,1);

  // Cuts for CC0pi
  AddStep(1,0, StepBase::kCut, "CC-0pi",   new NoPionCut());

  // Cuts for CC1pi: true -- Positive pion
  AddStep(1,1, StepBase::kCut, "CC-1pi",   new OnePionCut(true));

  // Cuts for CCOther
  AddStep(1,2, StepBase::kCut, "CC-Other", new OthersCut());

  //Branch names
  SetBranchAlias(0, "CCPhoton", 0);
  SetBranchAlias(1, "CC0pi"   , 1,0);
  SetBranchAlias(2, "CC1pi"   , 1,1);
  SetBranchAlias(3, "CCOther" , 1,2);

}


//********************************************************************
bool numuCCMultiPiPhotonFGD2Selection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

  //CCPhoton
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCCPhoton;
  }
  //CC0pi
  else if (allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiNoPhoton;
  }
  //CC1pi
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC1PiNoPhoton;
  }
  //CCOther
  else if (allCutsPassed[3]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCCOtherNoPhoton;
  }

  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}

//*********************************************************************
bool FillSummaryAction_numuCCMultiPiPhotonFGD2::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 


  if (!box.HMNtrack) return true;

  
  SampleId::SampleEnum SamplesUsed[4] = {
    SampleId::kFGD2NuMuCCPhoton, 
    SampleId::kFGD2NuMuCC0PiNoPhoton,  
    SampleId::kFGD2NuMuCC1PiNoPhoton,  
    SampleId::kFGD2NuMuCCOtherNoPhoton
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
bool numuCCMultiPiPhotonFGD2Selection::IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiPhotonSelection.IsRelevantRecObjectForSystematic(event,track,systId,branch);
}

//**************************************************
bool numuCCMultiPiPhotonFGD2Selection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiPhotonSelection.IsRelevantTrueObjectForSystematic(event,trueTrack,systId,branch);
}


//**************************************************
Int_t numuCCMultiPiPhotonFGD2Selection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiPhotonSelection.GetRelevantRecObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
Int_t numuCCMultiPiPhotonFGD2Selection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiPhotonSelection.GetRelevantTrueObjectGroupsForSystematic(systId, IDs, branch);
}

//**************************************************
bool numuCCMultiPiPhotonFGD2Selection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _numuCCMultiPiPhotonSelection.IsRelevantSystematic(event,box,systId,branch);
}
//**************************************************
bool numuCCMultiPiPhotonFGD2Selection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _numuCCMultiPiPhotonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, branch);
}

//**************************************************
bool numuCCMultiPiPhotonFGD2Selection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  return _numuCCMultiPiPhotonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, branch);
}

