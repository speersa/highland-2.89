#include "numuCC4piMultiPiFGD2Selection.hxx"
#include "numuCC4piMultiPiSelection.hxx"

#include "baseSelection.hxx"
#include "SystematicTuning.hxx"
#include "CutUtils.hxx"
#include "EventBoxUtils.hxx"
#include "Parameters.hxx"
#include "SubDetId.hxx"
#include "SystId.hxx"
#include "SystematicUtils.hxx"
#include "VersioningUtils.hxx"
#include "trackerSelectionUtils.hxx"

#include <TVector3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "AnalysisUtils.hxx"
#include "EventBoxId.hxx"
#include "ND280AnalysisUtils.hxx"
// #include "CategoriesUtils.hxx"
// #include "HighlandAnalysisUtils.hxx"
#include "CutUtils.hxx"
// #define DEBUG
#ifdef DEBUG
  #include <signal.h>
#endif

//*********************************************************************
void numuCC4piMultiPiFGD2Selection::DefineSteps(){
  //*******************************************************************
  AddStep(StepBase::kCut,         "event quality",                  new EventQualityCut(),true);                           //if passed accum_level=1
  // AddStep(StepBase::kCut,         "ToF quality",                    new EventTimeQualityCut(),true);                       //if passed accum_level=2
  AddStep(StepBase::kCut,         "> 0 tracks ",                    new numuCC4piMultiPi::TotalMultiplicityCut(),true);    //if passed accum_level=3
  AddStep(StepBase::kAction,      "sort TPC tracks",                new numuCC4piMultiPi::SortTracksToFAction());
  AddStep(StepBase::kCut,         "quality+fiducial",               new numuCC4piMultiPi::TrackGQandFVCut(),true);         //if passed accum_level=4  
  AddStep(StepBase::kAction,      "veto Action",                    new numuCC4piMultiPi::VetoAction());  
  AddStep(StepBase::kAction,      "muon PID Action",                new numuCC4piMultiPi::PIDAction());
  AddStep(StepBase::kAction,      "find vertex",                    new numuCC4piMultiPi::FindVertexAction()); 
  AddStep(StepBase::kAction,      "finding pions",                  new numuCC4piMultiPi::FindPionsAction());
  AddStep(StepBase::kAction,      "find ecal photons",              new numuCC4piMultiPi::FindECalPhotonsAction());
  AddStep(StepBase::kAction,      "Correcttracksense",              new numuCC4piMultiPi::FindCorrectTrackSenseAction()); 
  AddStep(StepBase::kAction,      "fill summary",                   new numuCC4piMultiPi::FillSummaryAction_numuCC4piMultiPiFGD2()); 

  AddSplit(4);
  AddStep(0, StepBase::kCut,      "Fwd Quality Cut",                new numuCC4piMultiPi::Fwd_Quality());                  //if passed accum_level=5
  AddStep(0, StepBase::kCut,      "Fwd Veto Cut",                   new numuCC4piMultiPi::Fwd_Veto());                     //if passed accum_level=6       
  AddStep(0, StepBase::kCut,      "Fwd PID Cut",                    new numuCC4piMultiPi::Fwd_PID());                      //if passed accum_level=7

  AddSplit(3,0);
  AddStep(0,0, StepBase::kCut,    "Fwd CC-0pi",                     new numuCC4piMultiPi::NoPionCut());                    //if passed accum_level=8
  //AddStep(0,0, StepBase::kCut,    "Fwd ECal Pi0 veto",              new numuCC4piMultiPi::EcalPi0VetoCut());             
  AddStep(0,0, StepBase::kCut,    "Fwd No_ECal_photons_cut",        new numuCC4piMultiPi::ZeroECalPhotonsCut());           //if passed accum_level=9

  AddStep(0,1, StepBase::kCut,    "Fwd CC-1pi",                     new numuCC4piMultiPi::OnePionCut(true));               //if passed accum_level=8
  //AddStep(0,1, StepBase::kCut,    "Fwd ECal Pi0 veto",              new numuCC4piMultiPi::EcalPi0VetoCut());               
  AddStep(0,1, StepBase::kCut,    "Fwd No_ECal_photons_cut",        new numuCC4piMultiPi::ZeroECalPhotonsCut());           //if passed accum_level=9

  AddStep(0,2, StepBase::kCut,    "Fwd CC-Other",                   new numuCC4piMultiPi::OthersCut());                    //if passed accum_level=8


  AddStep(1, StepBase::kCut,      "Bwd Quality Cut",                new numuCC4piMultiPi::Bwd_Quality());              
  AddStep(1, StepBase::kCut,      "Bwd Veto Cut",                   new numuCC4piMultiPi::Bwd_Veto());                 
  AddStep(1, StepBase::kCut,      "Bwd PID Cut",                    new numuCC4piMultiPi::Bwd_PID());                               

  AddSplit(3,1);
  AddStep(1,0, StepBase::kCut,    "Bwd CC-0pi",                     new numuCC4piMultiPi::NoPionCut());
  //AddStep(1,0, StepBase::kCut,    "Bwd ECal Pi0 veto",              new numuCC4piMultiPi::EcalPi0VetoCut());              
  AddStep(1,0, StepBase::kCut,    "Bwd No_ECal_photons_cut",        new numuCC4piMultiPi::ZeroECalPhotonsCut());

  AddStep(1,1, StepBase::kCut,    "Bwd CC-1pi",                     new numuCC4piMultiPi::OnePionCut(true)); 
  //AddStep(1,1, StepBase::kCut,    "Bwd ECal Pi0 veto",              new numuCC4piMultiPi::EcalPi0VetoCut());              
  AddStep(1,1, StepBase::kCut,    "Bwd No_ECal_photons_cut",        new numuCC4piMultiPi::ZeroECalPhotonsCut());

  AddStep(1,2, StepBase::kCut,    "Bwd CC-Other",                   new numuCC4piMultiPi::OthersCut());                   


  AddStep(2, StepBase::kCut,      "HAFwd Quality Cut",              new numuCC4piMultiPi::HAFwd_Quality());           
  AddStep(2, StepBase::kCut,      "HAFwd Veto Cut",                 new numuCC4piMultiPi::HAFwd_Veto());               
  AddStep(2, StepBase::kCut,      "HAFwd PID Cut",                  new numuCC4piMultiPi::HAFwd_PID());                       

  AddSplit(3,2);
  AddStep(2,0, StepBase::kCut,    "HAFwd CC-0pi",                   new numuCC4piMultiPi::NoPionCut());
  //AddStep(2,0, StepBase::kCut,    "HAFwd ECal Pi0 veto",            new numuCC4piMultiPi::EcalPi0VetoCut());                
  AddStep(2,0, StepBase::kCut,    "HAFwd No_ECal_photons_cut",      new numuCC4piMultiPi::ZeroECalPhotonsCut());

  AddStep(2,1, StepBase::kCut,    "HAFwd CC-1pi",                   new numuCC4piMultiPi::OnePionCut(true));
  //AddStep(2,1, StepBase::kCut,    "HAFwd ECal Pi0 veto",            new numuCC4piMultiPi::EcalPi0VetoCut());               
  AddStep(2,1, StepBase::kCut,    "HAFwd No_ECal_photons_cut",      new numuCC4piMultiPi::ZeroECalPhotonsCut());

  AddStep(2,2, StepBase::kCut,    "HAFwd CC-Other",                 new numuCC4piMultiPi::OthersCut());                   


  AddStep(3, StepBase::kCut,      "HABwd Quality Cut",              new numuCC4piMultiPi::HABwd_Quality());           
  AddStep(3, StepBase::kCut,      "HABwd Veto Cut",                 new numuCC4piMultiPi::HABwd_Veto());              
  AddStep(3, StepBase::kCut,      "HABwd PID Cut",                  new numuCC4piMultiPi::HABwd_PID());                  

  AddSplit(3,3);
  AddStep(3,0, StepBase::kCut,    "HABwd CC-0pi",                   new numuCC4piMultiPi::NoPionCut());
  //AddStep(3,0, StepBase::kCut,    "HABwd ECal Pi0 veto",            new numuCC4piMultiPi::EcalPi0VetoCut());              
  AddStep(3,0, StepBase::kCut,    "HABwd No_ECal_photons_cut",      new numuCC4piMultiPi::ZeroECalPhotonsCut());

  AddStep(3,1, StepBase::kCut,    "HABwd CC-1pi",                   new numuCC4piMultiPi::OnePionCut(true)); 
  //AddStep(3,1, StepBase::kCut,    "HABwd ECal Pi0 veto",            new numuCC4piMultiPi::EcalPi0VetoCut());              
  AddStep(3,1, StepBase::kCut,    "HABwd No_ECal_photons_cut",      new numuCC4piMultiPi::ZeroECalPhotonsCut());

  AddStep(3,2, StepBase::kCut,    "HABwd CC-Other",                 new numuCC4piMultiPi::OthersCut());                    

  SetBranchAlias(0,  "Fwd CC0pi",          0,0);
  SetBranchAlias(1,  "Fwd CC1pi",          0,1);
  SetBranchAlias(2,  "Fwd CCOther",        0,2);

  SetBranchAlias(3,  "Bwd CC0pi",          1,0);
  SetBranchAlias(4,  "Bwd CC1pi",          1,1);
  SetBranchAlias(5,  "Bwd CCOther",        1,2);

  SetBranchAlias(6,  "HAFwd CC0pi",        2,0);
  SetBranchAlias(7,  "HAFwd CC1pi",        2,1);
  SetBranchAlias(8,  "HAFwd CCOther",      2,2);

  SetBranchAlias(9,  "HABwd CC0pi",        3,0);
  SetBranchAlias(10, "HABwd CC1pi",        3,1);
  SetBranchAlias(11, "HABwd CCOther",      3,2);


  SetPreSelectionAccumLevel(2);

}

//*********************************************************************
void numuCC4piMultiPiFGD2Selection::DefineDetectorFV(){
  //*******************************************************************
  // Change FV definition to take all thickness
  // Note! this will affect all downstream stuff
  // 
  // This can be done only in highland --- TO BE CHANGED WHEN MOVED TO PSYCHE
  // FVDef::FVdefminFGD1[2] = 0;
  // FVDef::FVdefmaxFGD1[2] = 0;
  // The detector in which the selection is applied
  std::cout << "numuCC4piMultiPiFGD2Selection::DefineDetectorFV" << std::endl;
  SetDetectorFV(SubDetId::kFGD2);
}


//*********************************************************************
bool numuCC4piMultiPi::FillSummaryAction_numuCC4piMultiPiFGD2::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*******************************************************************
  // Cast the ToyBox to the appropriate type
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&boxB);
  if(!cc4piMultiPibox->MainTrack) return 1;
  AnaEventSummaryB* evesum = static_cast<AnaEventSummaryB*>(event.Summary);

   SampleId::SampleEnum SamplesUsed[12] = {
    SampleId::kFGD2NuMuCC0PiFwdNoPhoton,     
    SampleId::kFGD2NuMuCC1PiFwdNoPhoton,     
    SampleId::kFGD2NuMuCCOtherFwdNoPhoton,   
                                         
    SampleId::kFGD2NuMuCC0PiBwdNoPhoton,     
    SampleId::kFGD2NuMuCC1PiBwdNoPhoton,     
    SampleId::kFGD2NuMuCCOtherBwdNoPhoton,   
                                         
    SampleId::kFGD2NuMuCC0PiHAFwdNoPhoton,   
    SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton,   
    SampleId::kFGD2NuMuCCOtherHAFwdNoPhoton, 
                                         
    SampleId::kFGD2NuMuCC0PiHABwdNoPhoton,   
    SampleId::kFGD2NuMuCC1PiHABwdNoPhoton,   
    SampleId::kFGD2NuMuCCOtherHABwdNoPhoton
   };
  
  
  for (int i = 0; i < 12; i++){
    
    
    SampleId::SampleEnum iSample = SamplesUsed[i];
    
    evesum->LeptonCandidate[iSample] = cc4piMultiPibox->MainTrack;
  

    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[iSample], 4);

    if(cc4piMultiPibox->MainTrack->GetTrueParticle()){
    
      evesum->TrueVertex[iSample] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;

    }
  }
  return true;
}
