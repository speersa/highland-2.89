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
numuCC4piMultiPiSelection::numuCC4piMultiPiSelection(bool forceBreak): SelectionBase(forceBreak,EventBoxId::kEventBoxTracker) {
  //*******************************************************************
  // Initialize systematic tuning parameters
  systTuning::Initialize();
  _apply_ToF_based_Flip = (bool)ND::params().GetParameterI("psycheSelections.numuCC4piMultiPiSelection.ToF.ApplyToFFlip"); 
}

//*********************************************************************
void numuCC4piMultiPiSelection::DefineSteps(){
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
  AddStep(StepBase::kAction,      "fill summary",                   new numuCC4piMultiPi::FillSummaryAction_numuCC4piMultiPi()); 

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
void numuCC4piMultiPiSelection::InitializeToy(const AnaEventC* eventC) const{
  //*******************************************************************
  const AnaEventB& event = *static_cast<const AnaEventB*>(eventC);
  
  const ToyBoxB& box = GetPreviousToyBox(*eventC);
  const ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<const ToyBoxCC4piMultiPi*>(&box);

  // Retrieve the EventBoxTracker
  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];
  if (!EventBox) {
    std::cout << "No EventBoxTracker! Exiting..." << std::endl;
    return;}

  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(GetDetectorFV());

  // Exit for the moment since assume detector should be FGD1 or FGD2
  if (det != SubDetId::kFGD1 && det != SubDetId::kFGD2){
    std::cout << " numuCC4piMultiPiSelection::InitializeToy: provided detecor " << det << "is not FGD1 or FGD2" << std::endl;
    exit(1);
  } 

  EventBoxTracker::RecObjectGroupEnum groupID;


  if      (det == SubDetId::kFGD1) groupID = EventBoxTracker::kTracksWithFGD1;
  else                             groupID = EventBoxTracker::kTracksWithFGD2;

  int nFGD = EventBox->nRecObjectsInGroup[groupID];

  // 1. ForceForward 
  for (Int_t i=0;i<nFGD; ++i){
    AnaTrackB* track = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[groupID][i]);
    if (!track) {
      continue; 
    }
    if (!_tofCorrector.IsForward(*track)) {
      _tofCorrector.ForceForward(*track);
    }
  }


  // 2. ToF based flip
  if (!_apply_ToF_based_Flip){
    return;
  }

  // Exit for the moment since assume detector should be FGD1 or FGD2
  if (det != SubDetId::kFGD1 && det != SubDetId::kFGD2){
    std::cout << " numuCC4piMultiPiSelection::InitializeToy: provided detecor " << det << "is not FGD1 or FGD2" << std::endl;
    exit(1);
  } 


  for (Int_t i=0;i<nFGD; ++i){
    AnaTrackB* track = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[groupID][i]);
    if (!track) {
      continue; 
    }

    ToFSenseCorrector::ToFTopology topologies[ToFSenseCorrector::kToFInvalid];
    Int_t count = ToFSenseCorrector::GetToFTopologies(*track, topologies);
    for (Int_t j = 0; j < count; j++){
      ToFSenseCorrector::ToFTopology topo = topologies[j];
      // std::cout << "_tofCorrector.CheckNeedApplyToFBasedFlip(*track, topo)" << _tofCorrector.CheckNeedApplyToFBasedFlip(*track, topo) << " " << topo << std::endl;

      if (_tofCorrector.CheckNeedApplyToFBasedFlip(*track, topo)) {

        if (det == SubDetId::kFGD1){
          // std::cout << "Not flipping!" << std::endl;
          if (
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD1FGD2 ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD1ECAL_LAStartFgd_Track ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD1ECAL_LAStartFgd_Shower ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD1P0D_Shower ||  
               topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD1FGD2 ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD1ECAL_LAStartFgd_Track ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD1ECAL_LAStartFgd_Shower 

             )
            continue;
        }

        if (det == SubDetId::kFGD2){
          // std::cout << "Not flipping!" << std::endl;
          if (
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2DSECAL_LAStartFgd_Track ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2DSECAL_LAStartFgd_Shower ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2ECAL_LAStartFgd_Track ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2ECAL_LAStartFgd_Shower ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2DSECAL_LAStartFgd_Track ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2DSECAL_LAStartFgd_Shower ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2ECAL_LAEndFgd_Track ||
              topo == ToFSenseCorrector::ToFTopology::kToFTopo_FGD2ECAL_LAEndFgd_Shower 

             )
            continue;
        }

        track->Flip();
      
      }
    }
  }
}


//*********************************************************************
void numuCC4piMultiPiSelection::FinalizeToy(const AnaEventC* eventC) const{
  //*******************************************************************
// std::cout << "numuCC4piMultiPiSelection::FinalizeToy" << std::endl;
  const AnaEventB& event = *static_cast<const AnaEventB*>(eventC);
  
  for (int it = 0; it < event.nParticles; it++) {
    AnaTrackB* track = static_cast<AnaTrackB*>(event.Particles[it]);
    track->UnFlip();
  }
  

}

//*********************************************************************
void numuCC4piMultiPiSelection::DefineDetectorFV(){
  //*******************************************************************
  // Change FV definition to take all thickness
  // Note! this will affect all downstream stuff
  // 
  // This can be done only in highland --- TO BE CHANGED WHEN MOVED TO PSYCHE
  // FVDef::FVdefminFGD1[2] = 0;
  // FVDef::FVdefmaxFGD1[2] = 0;
  // The detector in which the selection is applied
  SetDetectorFV(SubDetId::kFGD1);
}

//*********************************************************************
void numuCC4piMultiPiSelection::InitializeEvent(AnaEventC& eventBB){
  //*******************************************************************
  AnaEventB& event = *static_cast<AnaEventB*>(&eventBB);

  // Create the appropriate EventBox if it does not exist yet
  if (!event.EventBoxes[EventBoxId::kEventBoxTracker]) event.EventBoxes[EventBoxId::kEventBoxTracker] = new EventBoxTracker();
  boxUtils::FillTracksWithTPC(event,  static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));
  boxUtils::FillTracksWithFGD(event,  static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));
  boxUtils::FillTracksWithECal(event);
  boxUtils::FillTrajsChargedInTPC(event);
  boxUtils::FillTrajsChargedInFGDAndNoTPC(event,  static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));
  boxUtils::FillTrajsChargedHATracker(event,  static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));
  boxUtils::FillTrajsInECal(event);
  boxUtils::FillFGDMichelElectrons(event, static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));

}

//**************************************************
bool numuCC4piMultiPi::TotalMultiplicityCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)box;
  // Check we have at least one reconstructed track in the FGD
  EventBoxB* eventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];
  SubDetId_h det = box.DetectorFV;

  if (det == SubDetId::kFGD1){
    return eventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1] > 0;
  }
  else if (det == SubDetId::kFGD2){
    return eventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2] > 0;
  }

  return false;
}

//**************************************************
bool numuCC4piMultiPi::SortTracksToFAction::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);

  // Retrieve the EventBoxTracker
  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];


  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(box.DetectorFV);

  // Exit for the moment since assume detector should be FGD1 or FGD2
  if (det != SubDetId::kFGD1 && det != SubDetId::kFGD2){
    std::cout << " numuCC4piMultiPi::SortTracksToFAction: provided detecor " << det << "is not FGD1 or FGD2" << std::endl;
    exit(1);
  } 

  EventBoxTracker::RecObjectGroupEnum groupID;


  //Find TPCGoodQuality tracks in Fwd and Bwd

  if      (det == SubDetId::kFGD1) groupID = EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1;
  else                             groupID = EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2;


  int nTPC = EventBox->nRecObjectsInGroup[groupID];

  const Float_t* cutMin = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::FGD1FVmin4pi : numuCC4piMultiPi_utils::FGD2FVmin4pi;
  const Float_t* cutMax = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::FGD1FVmax4pi : numuCC4piMultiPi_utils::FGD2FVmax4pi;



  //Find TPCGoodQuality tracks in Fwd and Bwd
  for (Int_t i=0;i<nTPC; ++i){
    AnaTrackB* track = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[groupID][i]);
    if (!track) continue;
    // Apply the fiducial cut
    if ( anaUtils::InFiducialVolume(det, track->PositionStart, cutMin, cutMax) ) {
      if ( track->Charge!=-1 ) continue;
      cc4piMultiPibox->LowAngle.push_back(track);
    } 
  }
  // Sort TPCGoodQuality using Momentum method
  std::sort(cc4piMultiPibox->LowAngle.begin(), cc4piMultiPibox->LowAngle.end(), AnaTrackB::CompareMomentum);

  int nECALTracks=EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithECal];
  for(int i=0;i<nECALTracks;i++){
    AnaTrackB* track = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithECal][i]);
    if (!track) continue;
    // Apply the fiducial cut
    if ( anaUtils::InFiducialVolume(det, track->PositionStart, cutMin, cutMax) ) {
      if ( cutUtils::TrackQualityCut(*track) ) continue;
      if ( cutUtils::StoppingBrECALorSMRDCut(track->PositionEnd)==-1 ) continue;
      cc4piMultiPibox->HighAngle.push_back(track);
    }
  }
  // Sort HighAngle using RangeMomentumMuon method
  std::sort(cc4piMultiPibox->HighAngle.begin(), cc4piMultiPibox->HighAngle.end(), AnaTrackB::CompareMuonRangeMomentum);

  return true;
}

//**************************************************
bool numuCC4piMultiPi::TrackGQandFVCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event; 
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);


  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(box.DetectorFV);

  // Exit for the moment since assume detector should be FGD1 or FGD2
  if (!SubDetId::IsFGDDetector(det)){
    std::cout << " numuCC4piMultiPi::TrackGQandFVCut: provided detecor " << det << "is not FGD1 or FGD2" << std::endl;
    exit(1);
  } 

  const Float_t* cutMinLA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1LAFVmin : numuCC4piMultiPi_utils::startFGD2LAFVmin;
  const Float_t* cutMaxLA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1LAFVmax : numuCC4piMultiPi_utils::startFGD2LAFVmax;
  const Float_t* cutMinHA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1HAFVmin : numuCC4piMultiPi_utils::startFGD2HAFVmin;
  const Float_t* cutMaxHA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1HAFVmax : numuCC4piMultiPi_utils::startFGD2HAFVmax;


  for(UInt_t i=0;i<cc4piMultiPibox->LowAngle.size();i++ ){
    if ( anaUtils::InFiducialVolume(det, cc4piMultiPibox->LowAngle[i]->PositionStart, cutMinLA, cutMaxLA) ) {
      if ( ToFSenseCorrector::IsForward(*cc4piMultiPibox->LowAngle[i]) ) cc4piMultiPibox->FwdTracks.push_back(cc4piMultiPibox->LowAngle[i]);
      else {cc4piMultiPibox->BwdTracks.push_back(cc4piMultiPibox->LowAngle[i]); 
      }
      break;
    }
  }
  for(UInt_t i=0;i<cc4piMultiPibox->HighAngle.size();i++){
    if ( anaUtils::InFiducialVolume(det, cc4piMultiPibox->HighAngle[i]->PositionStart, cutMinHA, cutMaxHA) ) {
      if ( ToFSenseCorrector::IsForward(*cc4piMultiPibox->HighAngle[i]) ) cc4piMultiPibox->HAFwdTracks.push_back(cc4piMultiPibox->HighAngle[i]);
      else {cc4piMultiPibox->HABwdTracks.push_back(cc4piMultiPibox->HighAngle[i]); 
      }
    }
  }
  if      ( cc4piMultiPibox->FwdTracks.size()>0   ) { cc4piMultiPibox->MainTrack = cc4piMultiPibox->FwdTracks[0];   return true; }
  else if ( cc4piMultiPibox->BwdTracks.size()>0   ) { cc4piMultiPibox->MainTrack = cc4piMultiPibox->BwdTracks[0];   return true; }
  else if ( cc4piMultiPibox->HAFwdTracks.size()>0 ) { cc4piMultiPibox->MainTrack = cc4piMultiPibox->HAFwdTracks[0]; return true; }
  else if ( cc4piMultiPibox->HABwdTracks.size()>0 ) { cc4piMultiPibox->MainTrack = cc4piMultiPibox->HABwdTracks[0]; return true; }

  return false;
}

//**************************************************
bool numuCC4piMultiPi::VetoAction::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  AnaEventB& eventB = *static_cast<AnaEventB*>(&event);
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);

  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(box.DetectorFV);

  // Exit for the moment since assume detector should be FGD1 or FGD2
  if (!SubDetId::IsFGDDetector(det)){
    std::cout << " numuCC4piMultiPi::VetoAction: provided detecor " << det << "is not FGD1 or FGD2" << std::endl;
    exit(1);
  } 

  for (UInt_t i=0;i<cc4piMultiPibox->FwdTracks.size();i++){
    if ( numuCC4piMultiPi_utils::VetoCut(numuCC4piMultiPi_utils::kLAFwd,eventB,*(cc4piMultiPibox->FwdTracks[i]), det) ) {
      if ( numuCC4piMultiPi_utils::ExternalCut(numuCC4piMultiPi_utils::kLAFwd,event,*(cc4piMultiPibox->FwdTracks[i]), det)){
        cc4piMultiPibox->FwdTracks_Veto.push_back(cc4piMultiPibox->FwdTracks[i]);
      }
    }
  }
  for (UInt_t i=0;i<cc4piMultiPibox->BwdTracks.size();i++){
    if ( numuCC4piMultiPi_utils::ExternalCut(numuCC4piMultiPi_utils::kLABwd,event,*(cc4piMultiPibox->BwdTracks[i]), det)){
      cc4piMultiPibox->BwdTracks_Veto.push_back(cc4piMultiPibox->BwdTracks[i]);
    }
  }
  for (UInt_t i=0;i<cc4piMultiPibox->HAFwdTracks.size();i++){
    if ( numuCC4piMultiPi_utils::VetoCut(numuCC4piMultiPi_utils::kHAFwd,eventB,*(cc4piMultiPibox->HAFwdTracks[i]), det)){
      cc4piMultiPibox->HAFwdTracks_Veto.push_back(cc4piMultiPibox->HAFwdTracks[i]);
    }
  }
  for (UInt_t i=0;i<cc4piMultiPibox->HABwdTracks.size();i++){
    if ( numuCC4piMultiPi_utils::VetoCut(numuCC4piMultiPi_utils::kHABwd,eventB,*(cc4piMultiPibox->HABwdTracks[i]), det)){
      cc4piMultiPibox->HABwdTracks_Veto.push_back(cc4piMultiPibox->HABwdTracks[i]);
    }
  }
  if      ( cc4piMultiPibox->FwdTracks_Veto.size()>0   ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->FwdTracks_Veto[0];
  else if ( cc4piMultiPibox->BwdTracks_Veto.size()>0   ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->BwdTracks_Veto[0];
  else if ( cc4piMultiPibox->HAFwdTracks_Veto.size()>0 ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->HAFwdTracks_Veto[0];
  else if ( cc4piMultiPibox->HABwdTracks_Veto.size()>0 ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->HABwdTracks_Veto[0];

  return true;
}

//**************************************************
bool numuCC4piMultiPi::PIDAction::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(box.DetectorFV);
  for (UInt_t i=0;i<cc4piMultiPibox->FwdTracks_Veto.size();i++){
    if ( numuCC4piMultiPi_utils::PIDCut(numuCC4piMultiPi_utils::kLAFwd,*(cc4piMultiPibox->FwdTracks_Veto[i]), det)==1 ){ 
      cc4piMultiPibox->FwdTracks_PID.push_back(cc4piMultiPibox->FwdTracks_Veto[i]);
    }
  }
  for (UInt_t i=0;i<cc4piMultiPibox->BwdTracks_Veto.size();i++){
    if ( numuCC4piMultiPi_utils::PIDCut(numuCC4piMultiPi_utils::kLABwd,*(cc4piMultiPibox->BwdTracks_Veto[i]), det)==1 ) cc4piMultiPibox->BwdTracks_PID.push_back(cc4piMultiPibox->BwdTracks_Veto[i]);
  }
  for (UInt_t i=0;i<cc4piMultiPibox->HAFwdTracks_Veto.size();i++){
    if ( numuCC4piMultiPi_utils::PIDCut(numuCC4piMultiPi_utils::kHAFwd,*(cc4piMultiPibox->HAFwdTracks_Veto[i]), det)==1 ) cc4piMultiPibox->HAFwdTracks_PID.push_back(cc4piMultiPibox->HAFwdTracks_Veto[i]);
  }
  for (UInt_t i=0;i<cc4piMultiPibox->HABwdTracks_Veto.size();i++){
    if ( numuCC4piMultiPi_utils::PIDCut(numuCC4piMultiPi_utils::kHABwd,*(cc4piMultiPibox->HABwdTracks_Veto[i]), det)==1 ) cc4piMultiPibox->HABwdTracks_PID.push_back(cc4piMultiPibox->HABwdTracks_Veto[i]);
  }
  if      ( cc4piMultiPibox->FwdTracks_PID.size()>0    ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->FwdTracks_PID[0];
  else if ( cc4piMultiPibox->BwdTracks_PID.size()>0    ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->BwdTracks_PID[0];
  else if ( cc4piMultiPibox->HAFwdTracks_PID.size()>0  ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->HAFwdTracks_PID[0];
  else if ( cc4piMultiPibox->HABwdTracks_PID.size()>0  ) cc4piMultiPibox->MainTrack = cc4piMultiPibox->HABwdTracks_PID[0];
  return true;
}

//**************************************************
bool numuCC4piMultiPi::FindVertexAction::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //**************************************************
  (void)event;
  ToyBoxTracker& box    = *static_cast<ToyBoxTracker*>(&boxB);
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&boxB);

  // reset the vertex
  box.Vertex = NULL;
  if ( !cc4piMultiPibox->MainTrack ) return false;
  box.Vertex = new AnaVertexB();
  anaUtils::CreateArray(box.Vertex->Particles, 1);
  box.Vertex->nParticles = 0;
  box.Vertex->Particles[box.Vertex->nParticles++] = cc4piMultiPibox->MainTrack;

  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(box.DetectorFV);

  const Float_t* cutMin = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::FGD1FVmin4pi : numuCC4piMultiPi_utils::FGD2FVmin4pi;
  const Float_t* cutMax = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::FGD1FVmax4pi : numuCC4piMultiPi_utils::FGD2FVmax4pi;

  if( anaUtils::InFiducialVolume(det, cc4piMultiPibox->MainTrack->PositionStart, cutMin, cutMax) ){

    anaUtils::CopyArray( cc4piMultiPibox->MainTrack->PositionStart, box.Vertex->Position, 4);

  }
  //else anaUtils::CopyArray( cc4piMultiPibox->MainTrack->PositionEnd, box.Vertex->Position, 4);
  if ( cc4piMultiPibox->MainTrack->TrueObject ) box.TrueVertex = box.Vertex->TrueVertex = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
  return true;
}

//*********************************************************************
bool numuCC4piMultiPi::FindPionsAction::Apply(AnaEventC& event, ToyBoxB& box) const{
  //*******************************************************************
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  pionSelParams.refTracks[0] = cc4piMultiPibox->MainTrack;
  pionSelParams.nRefTracks = 1;

  cc4piMultiPibox->pionBox.Detector = (SubDetId::SubDetEnum)box.DetectorFV;

  cc4piMultiPibox->pionBox.Reset(); //trying to see if difference

  // Fill the info
  numuCC4piMultiPi::FillPionInfo(event, cc4piMultiPibox->pionBox, pionSelParams);         /// do a new 
  int nnegpions        = cc4piMultiPibox->pionBox.nNegativePionTPCtracks;
  int npospions        = cc4piMultiPibox->pionBox.nPositivePionTPCtracks;
  int nisofgdpions     = cc4piMultiPibox->pionBox.nIsoFGDPiontracks;
  //int necalpions       = cc4piMultiPibox->pionBox.nECalPiontracks;
  int nmichelelectrons = cc4piMultiPibox->pionBox.nMichelElectrons;
  int npi0             = cc4piMultiPibox->pionBox.nPosPi0TPCtracks + cc4piMultiPibox->pionBox.nElPi0TPCtracks;
  int pionFGD          = nmichelelectrons;

  if (!nmichelelectrons && nisofgdpions > 0) pionFGD = 1;
  //if (!nmichelelectrons && nisofgdpions > 0) pionFGD = nisofgdpions;
  cc4piMultiPibox->pionBox.nPosPions   = npospions + pionFGD;
  cc4piMultiPibox->pionBox.nOtherPions = nnegpions + npi0;
  cc4piMultiPibox->pionBox.nNegPions = nnegpions;
  return true;
}

//*********************************************************************
const multipart::MultiParticleBox& numuCC4piMultiPi::GetPionBox(const ToyBoxB& box){
  //*******************************************************************
  const ToyBoxCC4piMultiPi& cc4piMultiPibox = static_cast<const ToyBoxCC4piMultiPi&>(box);
  return cc4piMultiPibox.pionBox;  
}

//**************************************************
void numuCC4piMultiPi::FindECALPionInfo(const AnaEventC& event, const multipart::PionSelectionParams& params,
    multipart::MultiParticleBox& pionBox){
  //**************************************************
  pionBox.nECalPiontracks  = 0;
  Float_t cut1 = 0;
  Float_t cut2 = 0.4;
  Float_t cut3 = 1.0;
  EventBoxTracker::RecObjectGroupEnum groupID;
  if      (pionBox.Detector == SubDetId::kFGD1) groupID = EventBoxTracker::kTracksWithECal;
  else if (pionBox.Detector == SubDetId::kFGD2) groupID = EventBoxTracker::kTracksWithECal;
  else return;
  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];
  for (int i=0; i < EventBox->nRecObjectsInGroup[groupID]; i++){
    AnaTrackB* track = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[groupID][i]);
    if (!track) continue;


    // Check that at track is not within the reference ones
    bool found = false;
    for (int j = 0; j < params.nRefTracks; j++){
      if (track == params.refTracks[j]){
        found = true;
        break;
      }
    }

    if (found){
      continue;
    }

    if ( !numuCC4piMultiPi_utils::MuonECALPIDCut(*track) ){ 
      if ( cutUtils::StoppingBrECALorSMRDCut(track->PositionEnd)== 0 ) continue;                                  // check if stop in ECal
      if( track->nECALSegments > 0 ){
        
        AnaECALParticleB* ECalSeg = track->ECALSegments[0];

        if ( ECalSeg->Length > 0 && ECalSeg->EMEnergy > 0 ) {
          if ( ECalSeg->PIDMipEm > cut1 &&  ECalSeg->PIDMipPion > cut1 ) {
            if ( ECalSeg->Length/ECalSeg->EMEnergy > cut2 && ECalSeg->Length/ECalSeg->EMEnergy < cut3 ){
              pionBox.ECalPiontracks[pionBox.nECalPiontracks++] = track;
            }
          }
        }
      }  
    }
  }
}

//*********************************************************************
bool numuCC4piMultiPi::FindCorrectSense(AnaTrackB* track, AnaVertexB* vertex){
  //*******************************************************************
  if (!track) return true;
  if (!vertex) return true;

  Float_t distStart = anaUtils::GetSeparationSquared(track->PositionStart, vertex->Position);
  Float_t distEnd   = anaUtils::GetSeparationSquared(track->PositionEnd, vertex->Position);

  if (distEnd < distStart){ 
    track->Flip();
    return false;
  }
  return true;
}

//********************************************************************
void numuCC4piMultiPi::FindPionCorrectTrackSense(const ToyBoxB& box){
  //********************************************************************
  const ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<const ToyBoxCC4piMultiPi*>(&box);

  if (!cc4piMultiPibox->Vertex) return;


  if ( cc4piMultiPibox->pionBox.nPositivePionTPCtracks > 0. ) {
    for (int i=0; i < cc4piMultiPibox->pionBox.nPositivePionTPCtracks; i++){
      AnaTrackB* track = cc4piMultiPibox->pionBox.PositivePionTPCtracks[i];
      if (!track) continue;
      numuCC4piMultiPi::FindCorrectSense(track, cc4piMultiPibox->Vertex); 

    }
  }
  if ( cc4piMultiPibox->pionBox.nNegativePionTPCtracks > 0. ) {
    for (int i=0; i < cc4piMultiPibox->pionBox.nNegativePionTPCtracks; i++){
      AnaTrackB* track = cc4piMultiPibox->pionBox.NegativePionTPCtracks[i];
      if (!track) continue;
      numuCC4piMultiPi::FindCorrectSense(track, cc4piMultiPibox->Vertex); 
    }
  }
  if ( cc4piMultiPibox->pionBox.nIsoFGDPiontracks > 0. ) {
    for (int i=0; i < cc4piMultiPibox->pionBox.nIsoFGDPiontracks; i++){
      AnaTrackB* track = cc4piMultiPibox->pionBox.IsoFGDPiontracks[i];
      if (!track) continue;
      numuCC4piMultiPi::FindCorrectSense(track, cc4piMultiPibox->Vertex);
    
    }
  }
  if ( cc4piMultiPibox->pionBox.nECalPiontracks > 0. ) {
    for (int i=0; i < cc4piMultiPibox->pionBox.nECalPiontracks; i++){
      AnaTrackB* track = cc4piMultiPibox->pionBox.ECalPiontracks[i];
      if (!track) continue;
      numuCC4piMultiPi::FindCorrectSense(track, cc4piMultiPibox->Vertex);
    }
  }

}

//********************************************************************
bool numuCC4piMultiPi::FindCorrectTrackSenseAction::Apply(AnaEventC& event, ToyBoxB& box) const{
  //********************************************************************
  (void)event;
  numuCC4piMultiPi::FindPionCorrectTrackSense(box);
  return true;
}

//*********************************************************************
void numuCC4piMultiPi::FillPionInfo(const AnaEventC& event, multipart::MultiParticleBox& pionBox, const multipart::PionSelectionParams& params){
  //*********************************************************************
  EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);
  if (!EventBox){
    std::cout << " numuCC4piMultiPi::FillPionInfo(): EventBoxTracker not available " << std::endl;  
    exit(1);
  }
  if (!SubDetId::IsFGDDetector(pionBox.Detector)){
    std::cout << " numuCC4piMultiPi::FillPionInfo(): provided detecor " << pionBox.Detector << "is not FGD1 or FGD2" << std::endl;
    exit(1);
  } 

  EventBoxTracker::RecObjectGroupEnum groupID;
  if      (pionBox.Detector == SubDetId::kFGD1) groupID = EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1;
  else if (pionBox.Detector == SubDetId::kFGD2) groupID = EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2;
  else return;

  if (params.useTPCPions) cutUtils::FindGoodQualityTPCPionInfo(event, pionBox, params, 
      groupID); 

  if (params.useFGDPions) cutUtils::FindIsoFGDPionInfo(event, pionBox, params);

  if (params.useECalPions) numuCC4piMultiPi::FindECALPionInfo(event, params, pionBox);

  if (params.useME) pionBox.nMichelElectrons =  EventBox->nFGDMichelElectrons[pionBox.Detector];

  return;
}

//*********************************************************************
bool numuCC4piMultiPi::FillSummaryAction_numuCC4piMultiPi::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*******************************************************************
  // Cast the ToyBox to the appropriate type
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&boxB);
  if(!cc4piMultiPibox->MainTrack) return 1;
  AnaEventSummaryB* evesum = static_cast<AnaEventSummaryB*>(event.Summary);

  SampleId::SampleEnum SamplesUsed[12] = {
    SampleId::kFGD1NuMuCC0PiFwdNoPhoton,     
    SampleId::kFGD1NuMuCC1PiFwdNoPhoton,     
    SampleId::kFGD1NuMuCCOtherFwdNoPhoton,   

    SampleId::kFGD1NuMuCC0PiBwdNoPhoton,     
    SampleId::kFGD1NuMuCC1PiBwdNoPhoton,     
    SampleId::kFGD1NuMuCCOtherBwdNoPhoton,   

    SampleId::kFGD1NuMuCC0PiHAFwdNoPhoton,   
    SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton,   
    SampleId::kFGD1NuMuCCOtherHAFwdNoPhoton, 

    SampleId::kFGD1NuMuCC0PiHABwdNoPhoton,   
    SampleId::kFGD1NuMuCC1PiHABwdNoPhoton,   
    SampleId::kFGD1NuMuCCOtherHABwdNoPhoton
  };


  for (int i = 0; i < 12; i++){

    SampleId::SampleEnum iSample= SamplesUsed[i];


    evesum->LeptonCandidate[iSample] = cc4piMultiPibox->MainTrack;


    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[iSample], 4);

    if(cc4piMultiPibox->MainTrack->GetTrueParticle()){

      evesum->TrueVertex[iSample] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;

    }
  }



  return true;
}

//*********************************************************************
bool numuCC4piMultiPiSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //*******************************************************************
  // raise(SIGSEGV);
  if(allCutsPassed[0])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiFwdNoPhoton;
  if(allCutsPassed[1])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiFwdNoPhoton;
  if(allCutsPassed[2])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOtherFwdNoPhoton;

  if(allCutsPassed[3])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiBwdNoPhoton;
  if(allCutsPassed[4])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiBwdNoPhoton;
  if(allCutsPassed[5])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOtherBwdNoPhoton;

  if(allCutsPassed[6])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiHAFwdNoPhoton;
  if(allCutsPassed[7])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton;
  if(allCutsPassed[8])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOtherHAFwdNoPhoton;

  if(allCutsPassed[9])  static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiHABwdNoPhoton;
  if(allCutsPassed[10]) static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiHABwdNoPhoton;
  if(allCutsPassed[11]) static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOtherHABwdNoPhoton;

  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}

//**************************************************
bool numuCC4piMultiPi::Fwd_Quality::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->FwdTracks.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::Fwd_Veto::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->FwdTracks_Veto.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::Fwd_PID::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->FwdTracks_PID.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::Bwd_Quality::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->BwdTracks.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::Bwd_Veto::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->BwdTracks_Veto.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::Bwd_PID::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->BwdTracks_PID.size()>0 && cc4piMultiPibox->FwdTracks_PID.size()==0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::HAFwd_Quality::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->HAFwdTracks.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::HAFwd_Veto::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->HAFwdTracks_Veto.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::HAFwd_PID::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->HAFwdTracks_PID.size()>0 && cc4piMultiPibox->FwdTracks_PID.size()==0 && cc4piMultiPibox->BwdTracks_PID.size()==0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::HABwd_Quality::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->HABwdTracks.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::HABwd_Veto::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->HABwdTracks_Veto.size()>0) return true;
  return false;
}

//**************************************************
bool numuCC4piMultiPi::HABwd_PID::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)event;
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  if (cc4piMultiPibox->HABwdTracks_PID.size()>0 && cc4piMultiPibox->FwdTracks_PID.size()==0 && cc4piMultiPibox->BwdTracks_PID.size()==0 && cc4piMultiPibox->HAFwdTracks_PID.size()==0) return true;
  return false;
}

//*********************************************************************
Int_t  numuCC4piMultiPiSelection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //*******************************************************************

  std::vector<std::vector<Int_t> > groups(SystId::SystEnumLast_SystId, std::vector<Int_t>(2, -1));
  groups.resize(SystId::SystEnumLast_SystId);
  // Explicitely set the groups for various systeamtics that need them, this allows to have 
  // a transparent set/control of the systematics by the selection  
  using namespace SystId;
  using namespace anaUtils;
  // --- Systematic         Detectors                                   FGD1                                    FGD2 
  // General numuCC
  // groups[   kBFieldDist                 ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  groups[   kBFieldDist    ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCInFGD1FV,  EventBoxTracker::kTracksWithTPCInFGD2FV );
  groups[   kMomScale                   ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  groups[   kMomResol                   ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  groups[   kTpcPid                     ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  // groups[   kChargeIDEff                ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  groups[   kChargeIDEff                ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCInFGD1FV,          EventBoxTracker::kTracksWithTPCInFGD2FV           );

  groups[   kTpcClusterEff              ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           ); 
  groups[   kTpcTrackEff                ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPC,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  groups[   kFgdHybridTrackEff          ] = CreateVectorI( 2, EventBoxTracker::kTracksWithFGD1AndNoTPC,        EventBoxTracker::kTracksWithFGD2AndNoTPC         );
  groups[   kFgdPid                     ] = CreateVectorI( 2, EventBoxTracker::kTracksWithFGD1AndNoTPC,        EventBoxTracker::kTracksWithFGD2AndNoTPC         );
  //groups[   kOOFV                       ] = CreateVectorI( 2, EventBoxTracker::kTracksWithFGD1,                EventBoxTracker::kTracksWithFGD2                 );


     
  groups[ kTpcFgdMatchEff             ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  
  // 4pi specific
  groups[   kMomRangeResol              ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kMomBiasFromVertexMigration ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  groups[   kToFResol                   ] = CreateVectorI( 2, EventBoxTracker::kTracksWithFGD1,                EventBoxTracker::kTracksWithFGD2                 );
  groups[   kECalEMResol                ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kECalEMScale                ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kECalTrackEff               ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kECalPID                    ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kTpcECalMatchEff            ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPCAndFGD1,          EventBoxTracker::kTracksWithTPCAndFGD2           );
  groups[   kTpcP0dMatchEff             ] = CreateVectorI( 2, EventBoxTracker::kTracksWithTPC,                 EventBoxTracker::kTracksWithTPC                  );
  groups[   kFgdECalMatchEff            ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kFgdECalSmrdMatchEff        ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kECalPhotonPileUp           ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );
  groups[   kECalEmHipPID               ] = CreateVectorI( 2, EventBoxTracker::kTracksWithECal,                EventBoxTracker::kTracksWithECal                 );

  // The systematics not mentioned above will get no groups
  Int_t ngroups = 0;
  // Check the systematic index is ok
  try {
    groups.at(systId);
  }
  catch (const std::out_of_range& oor) {
    std::cerr << this->Name() << " GetRelevantRecObjectGroupsForSystematic: syst index beyond limits "<< systId << " Error " << oor.what() << '\n';
    exit(1);
  } 
  SubDetId_h det = GetDetectorFV(branch);
  if (det == SubDetId::kFGD1){
    if (groups[systId][0] >= 0) IDs[ngroups++] = groups[systId][0];
  }
  else   if (det == SubDetId::kFGD2){
    if (groups[systId][1] >= 0) IDs[ngroups++] = groups[systId][1];
  }
  else if (det == SubDetId::kFGD){
    if (groups[systId][0] >= 0) IDs[ngroups++] = groups[systId][0];
    if (groups[systId][0] != groups[systId][1]){
      IDs[ngroups++] = groups[systId][1];
    }   
  }
  return ngroups;
}

//*********************************************************************
Int_t numuCC4piMultiPiSelection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //*******************************************************************
  // Consider the systematics specific for the analysis
  std::vector<std::vector<Int_t> > groups(SystId::SystEnumLast_SystId, std::vector<Int_t>(2, -1));
  // Explicitely set the groups for various systeamtics that need them, 
  // this allows to have a transparent set/control of the systematics by the
  // selection  
  using namespace SystId;
  using namespace anaUtils;
  // --- Systematic         Detectors                                   FGD1                                                    FGD2 
  groups[ kTpcTrackEff          ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesChargedInTPCInBunch,          EventBoxTracker::kTrueParticlesChargedInTPCInBunch    );
  groups[ kTpcFgdMatchEff       ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesChargedInTPCorFGDInBunch,     EventBoxTracker::kTrueParticlesChargedInTPCorFGDInBunch    );
  groups[ kTpcECalMatchEff      ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesChargedInTPCInBunch,          EventBoxTracker::kTrueParticlesChargedInTPCInBunch         );
  groups[ kTpcP0dMatchEff       ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesChargedInTPCInBunch,          EventBoxTracker::kTrueParticlesChargedInTPCInBunch         );
  groups[ kECalTrackEff         ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesInECalInBunch,                EventBoxTracker::kTrueParticlesInECalInBunch               );
  groups[ kFgdECalMatchEff      ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch,   EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch  );
  groups[ kFgdECalSmrdMatchEff  ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch,   EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch  );
  groups[ kFgdHybridTrackEff    ] = CreateVectorI( 2, EventBoxTracker::kTrueParticlesChargedInFGD1AndNoTPCInBunch, EventBoxTracker::kTrueParticlesChargedInFGD2AndNoTPCInBunch);

  // The systematics not mentioned above will get no groups
  // Check the systematic index is ok
  try {
    groups.at(systId);
  }
  catch (const std::out_of_range& oor) {
    std::cerr << this->Name() << " GetRelevantTrueObjectGroupsForSystematic: syst index beyond limits "<< systId << " Error " << oor.what() << '\n';
    exit(1);
  }
  (void)branch;
  SubDetId_h det = GetDetectorFV();
  size_t ngroups = 0;
  if (det == SubDetId::kFGD1){
    if (groups[systId][0] >= 0) IDs[ngroups++] = groups[systId][0];
  }
  else   if (det == SubDetId::kFGD2){
    if (groups[systId][1] >= 0) IDs[ngroups++] = groups[systId][1];
  }
  else if (det == SubDetId::kFGD){
    if (groups[systId][0] >= 0) IDs[ngroups++] = groups[systId][0];
    if (groups[systId][0] != groups[systId][1]){
      IDs[ngroups++] = groups[systId][1];
    }   
  }
  return ngroups;
}

//*********************************************************************
bool numuCC4piMultiPiSelection::IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const{
  //*******************************************************************
  (void)event;
  (void)branch;
  (void)systId;
  AnaTrackB* track = static_cast<AnaTrackB*>(recObj);
  if (!track) return false;
  if (!track->TrueObject) return false;

  if (systId == SystId::kTpcClusterEff){
    if (track->nTPCSegments == 0) return false;
    //    AnaTPCParticleB* tpcTrack = static_cast<AnaTPCParticleB*>(track->TPCSegments[0]);
    AnaTPCParticleB* tpcTrack = static_cast<AnaTPCParticleB*>(anaUtils::GetSegmentWithMostNodesInClosestTpc(*track));      
    if (!tpcTrack) return false;
    // 19 for numu analysis: just above the TPC quality cut threshold
    if (tpcTrack->NNodes == 19)
      return true;  
    return false;
  } 
  return true;
}

//*********************************************************************
bool numuCC4piMultiPiSelection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //*******************************************************************
  (void)event;
  (void)branch;
  (void)systId;
  AnaTrueParticleB* track = static_cast<AnaTrueParticleB*>(trueObj);
  if (!track) return false;  
  if (systId == SystId::kTpcTrackEff){
    if (!anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()), track->Position)) return false;
  }  
  else if (systId == SystId::kFgdTrackEff){
    if (!anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()), track->Position)) return false;
  }  
  else if (systId == SystId::kFgdHybridTrackEff){    
    if (!anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()), track->Position)) return false;
  }
  return true;
}

//**************************************************
bool numuCC4piMultiPiSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************
  (void)event;

  switch (systId){
    // Fall through the relevant ones
    //ECAL
    case SystId::kECalTrackEff:         
      //Apply for CC0pi and CC1pi branches
      if (branch > 5 && branch <12) return true;
    case SystId::kECalPID:                                                 
      return false;  
      break; 
    
    case SystId::kECalPhotonPileUp:
      if (branch == 0 || branch == 3 || branch == 6 || branch == 9 || branch == 1 || branch == 4 || branch == 7 || branch == 10) return true;                                                   
      return false;  
      break; 

      // TPC reco
    case SystId::kChargeIDEff:
    case SystId::kTpcClusterEff:

    case SystId::kTpcTrackEff:               
      if (branch>-1 && branch<6) return true;                                             
      return false;  
      break;                                         
      // FGD
    case SystId::kFgdHybridTrackEff:                                                     
    case SystId::kMichelEleEff:
      // FGD matching
    case SystId::kFgdECalMatchEff:
    case SystId::kFgdECalSmrdMatchEff:
      // TPC matching
    case SystId::kTpcFgdMatchEff:
    case SystId::kTpcECalMatchEff:                                                     
    case SystId::kTpcP0dMatchEff:
      // Normalization
    case SystId::kPileUp:
      return true;
      break;  
    case SystId::kFgdMass:
      return true;
      break;  
    case SystId::kOOFV:                                                                
    case SystId::kSandMu: 
      return true;
      break;             
      // Flux
    case SystId::kFluxWeight:
      return true;
      break;  
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
bool numuCC4piMultiPiSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************
  // all CC4piMultiPibox cases
  const ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<const ToyBoxCC4piMultiPi*>(&box);
  if (!track) return false;
  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true; 

  // all CC4piMultiPibox cases
  switch (systId){
    // Fall back through the relevant ones
    // TPC reco
    case SystId::kChargeIDEff:
      {
        if (track == cc4piMultiPibox->MainTrack) return true;
        if (branch == 1 || branch == 4 || branch == 7 || branch == 10){
          // For CC-1pi also the positive Pion in the TPC matters
          if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.PositivePionTPCtracks[0]) return true; 
        }
        if (branch == 2 || branch == 5 || branch == 8 ||  branch == 11){
          // For CC-Other consider the negative pion when there are no other pions
          if (cc4piMultiPibox->pionBox.nNegativePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.NegativePionTPCtracks[0] && cc4piMultiPibox->pionBox.nOtherPions==1) return true;  
        }
        return false;
      } 

    case SystId::kTpcClusterEff:
      {
        if (track == cc4piMultiPibox->MainTrack) return true;
        if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.PositivePionTPCtracks[0]) return true; 
        return false;
        break;
      }

      // TPC matching
    case SystId::kTpcFgdMatchEff:
      {
        if (track == cc4piMultiPibox->MainTrack) return true;
        if (branch == 1 || branch == 4 || branch == 7 || branch == 10){
          // For CC-1pi also the positive Pion in the TPC matters
          if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.PositivePionTPCtracks[0]) return true; 
        }
        if (branch == 2 || branch == 5 || branch == 8 || branch == 11){
          // For CC-Other consider the negative pion when there are no other pions
          if (cc4piMultiPibox->pionBox.nNegativePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.NegativePionTPCtracks[0] && cc4piMultiPibox->pionBox.nOtherPions==1) return true;  
        }
        return false;
        break;
      }

    case SystId::kTpcP0dMatchEff:
      {
        if (branch == 3 || branch == 4 || branch == 5){
          if (track == cc4piMultiPibox->MainTrack) return true; 
          if (branch == 4 && cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.PositivePionTPCtracks[0]) return true; 
          if (branch == 5 && cc4piMultiPibox->pionBox.nNegativePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.NegativePionTPCtracks[0] && cc4piMultiPibox->pionBox.nOtherPions==1) return true;  
        }
        return false;
        break;
      }

    case SystId::kTpcECalMatchEff:
      {
        if (branch > 5 && branch <12){
          if (track == cc4piMultiPibox->MainTrack) return true;  
          if (branch == 7 || branch == 10){
            // For CC1pi also the positive Pion in the TPC matters
            if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.PositivePionTPCtracks[0]) return true; 
          }
          if (branch == 8 || branch == 11){
            // For CCOther consider the negative pion when there are no other pions
            if (cc4piMultiPibox->pionBox.nNegativePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.NegativePionTPCtracks[0] && cc4piMultiPibox->pionBox.nOtherPions==1) return true;  
          }
        }
        return false;
        break;
      }

    case SystId::kFgdECalMatchEff:
      { 
        if (branch > 5 && branch <12){
          if (track == cc4piMultiPibox->MainTrack) return true;
          if (branch == 7 || branch == 10){
            // For CC1pi also the positive Pion in the TPC matters
            if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.PositivePionTPCtracks[0]) return true; 
          }
          if (branch == 8 || branch == 11){
            // For CCOther consider the negative pion when there are no other pions
            if (cc4piMultiPibox->pionBox.nNegativePionTPCtracks==1 && track==cc4piMultiPibox->pionBox.NegativePionTPCtracks[0] && cc4piMultiPibox->pionBox.nOtherPions==1) return true;  
          }
        }
        return false;
        break;
      }

    case SystId::kFgdECalSmrdMatchEff:
      {
        if (branch > 5 && branch <12){
          if (track == cc4piMultiPibox->MainTrack) return true;
        }
        return false;
        break;
      }

    default:
      return true;
      break;

  }
  // For the rest of the systematic return true
  return true;
}

//**************************************************
bool numuCC4piMultiPiSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************
  const ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<const ToyBoxCC4piMultiPi*>(&box);
  AnaTrueParticleB* track = static_cast<AnaTrueParticleB*>(trueObj);

  if (!track) return false;
  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true;
  // all CC4piMultiPibox cases
  switch (systId){
    case SystId::kTpcFgdMatchEff:
      {
        if (branch>-1 && branch<6) {
          if(cc4piMultiPibox->MainTrack) return true;   
        }
        if (branch == 1 || branch == 4 || branch == 7 || branch == 10){
          if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1) return true; 
        }
        if (branch == 2 || branch == 5 || branch == 8 || branch == 11){
          if (cc4piMultiPibox->pionBox.nOtherPions==1) return true;  
        }
        return false;
        break;
      }

    case SystId::kFgdHybridTrackEff:
      {
        // True track should start in the FGD FV of interest
        // Probably can imporve more by requiring that a track corresponds to the selected true vertex
        return anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()), 
            track->Position); 
        break;
      }
      /*
         case SystId::kTpcTrackEff:                                                                
         {
         if (branch>-1 && branch<6) {
         if (cc4piMultiPibox->MainTrack->GetTrueParticle() && track->ID  == cc4piMultiPibox->MainTrack->GetTrueParticle()->ID) return true; 
      // If the are few TPC pions consider them, muons, electrons 
      if (abs(track->PDG)==211 || abs(track->PDG)==13 || abs(track->PDG)==11) return true;  
      // Don't consider pions when there are many TPC ones (a conservative check). Cases in which we must loose two or more pions are excluded (0.01*0.01 probability)
      if (cc4piMultiPibox->pionBox.nNegativePionTPCtracks+cc4piMultiPibox->pionBox.nPositivePionTPCtracks > 2 || cc4piMultiPibox->pionBox.nNegativePionTPCtracks > 1) return false; 
      } 
      return false;
      break;
      }
      */
    case SystId::kTpcP0dMatchEff:
      {
        if (branch>2 && branch<6){
          if(cc4piMultiPibox->MainTrack) return true;   
        }
        if (branch == 1 || branch == 4 || branch == 7 || branch == 10){
          if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1) return true; 
        }
        if (branch == 2 || branch == 5 || branch == 8 || branch == 11){
          if (cc4piMultiPibox->pionBox.nOtherPions==1 && cc4piMultiPibox->pionBox.nPosPions == 0) return true;  
        }
        return false;
        break;
      }

    case SystId::kTpcECalMatchEff:                                                        
      {
        if (branch>5 && branch<12) return true; 
        return false;
        break;
      }

    case SystId::kFgdECalMatchEff:
      {
        if (branch>5 && branch<12) return true; 
        return false;
        break;
      }

    case SystId::kFgdECalSmrdMatchEff:
      {
        if (branch>5 && branch<12) return true; 
        return false;
        break;
      }

      // pion SI
    case SystId::kSIPion:
      {
        if (track->ID == cc4piMultiPibox->MainTrack->GetTrueParticle()->ID){
          if (abs(cc4piMultiPibox->MainTrack->GetTrueParticle()->PDG)        == 211) return true;
          if (abs(cc4piMultiPibox->MainTrack->GetTrueParticle()->ParentPDG)  == 211) return true;
          if (abs(cc4piMultiPibox->MainTrack->GetTrueParticle()->GParentPDG) == 211) return true;
          return false;
        }
        // If this track is NOT associated to the MainTrack, consider the posibility of this track to become the MainTrack and be identified as muon
        // For the moment assume a negative pion may become the MainTrack if its momentum its above 90% of the current MainTrack momentum. 
        // Ideally we should check that this true pion is not associated to any reconstructed track, but this is not possible now without looping.
        // Multiply by the charge of the MainTrack such that it can be use for antiNumu selection
        else if (track->PDG == 211*((Int_t)cc4piMultiPibox->MainTrack->Charge) && track->Momentum > 0.9*cc4piMultiPibox->MainTrack->Momentum) return true;
        return false;
        break;
      }

      // Contributors for relevant objects for proton SI
    case SystId::kSIProton:
      {
        if (track->ID == cc4piMultiPibox->MainTrack->GetTrueParticle()->ID){
          if (cc4piMultiPibox->MainTrack->GetTrueParticle()->PDG        == 2212) return true;
          if (cc4piMultiPibox->MainTrack->GetTrueParticle()->ParentPDG  == 2212) return true;
          if (cc4piMultiPibox->MainTrack->GetTrueParticle()->GParentPDG == 2212) return true;
          return false;
        }
        // If this track is NOT associated to the MainTrack, consider the posibility of this track to become the MainTrack
        else if (track->PDG == 2212 && track->Momentum > 0.9*cc4piMultiPibox->MainTrack->Momentum) return true;
        return false;
        break;
      }

      // To be tuned
    case SystId::kECalTrackEff: 
      {
        if (branch > 5 && branch < 12){
          if (track->PDG == 13 && cc4piMultiPibox->MainTrack->GetTrueParticle()->PDG!=13) return true;
        }
        return false;
        break;
      }

    default:
      return true;
      break;
  }
  // For the rest of the systematic return true
  return true;
}


//******************************************************************
int numuCC4piMultiPi_utils::GetFgdLayer(Float_t* pos, SubDetId::SubDetEnum det){
  //****************************************************************
  if (!SubDetId::IsFGDDetector(det) && det != SubDetId::kFGD){ 
    std::cerr << " anaUtils::GetFGDLayer(): not an FGD detector " << det << std::endl; 
    exit(1);
  }

  if (!anaUtils::InDetVolume(det, pos))
    return -1;


  Float_t initZ   = 0;
  Float_t finalZ  = 0;
  Float_t barCenter[30];

  // FGD1 or FGD
  if (det == SubDetId::kFGD1 || det == SubDetId::kFGD){ 
    initZ   = 0;
    finalZ  = 0;

    for ( int i = 0; i < 30; i++) { 
      barCenter[i] = DetDef::fgd1BarCenter[i];
      if (i == 0) initZ = barCenter[0 ]- (DetDef::fgdXYBarWidth / 2) - DetDef::fgdXYGlueWidth - DetDef::fgdXYSkinWidth - DetDef::fgdXYAirWidth;
      else initZ = finalZ;
      if      (i%2 == 0) finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + (DetDef::fgdXYMiddleGlueWidth / 2);
      else if (i%2 == 1) finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + DetDef::fgdXYGlueWidth+DetDef::fgdXYSkinWidth + (DetDef::fgdXYAirWidth / 2);
      if (i == 29) finalZ += DetDef::fgdXYAirWidth;
      if (pos[2] > initZ && pos[2] < finalZ) return i;

    }  
  }
  // FGD2 or FGD
  if (det == SubDetId::kFGD2 || det == SubDetId::kFGD){
    initZ   = 0;
    finalZ  = 0;

    // XY modules
    for ( int i = 0; i < 14; i++) {
      barCenter[i] = DetDef::fgd2BarCenter[i];

      if (i%2 == 0){   
        if ( i==0 ) initZ = barCenter[0] - (DetDef::fgdXYBarWidth / 2) - DetDef::fgdXYGlueWidth - DetDef::fgdXYSkinWidth;
        else initZ = barCenter[i]  - (DetDef::fgdXYBarWidth / 2) - DetDef::fgdXYGlueWidth - DetDef::fgdXYSkinWidth;
        finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + (DetDef::fgdXYMiddleGlueWidth / 2);
      }
      else if (i%2 == 1) {
        initZ = barCenter[i]  - (DetDef::fgdXYBarWidth / 2) - (DetDef::fgdXYMiddleGlueWidth / 2);
        finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + DetDef::fgdXYGlueWidth + DetDef::fgdXYSkinWidth;
      }

      if (pos[2]>initZ && pos[2]<finalZ) return i;
    }

    // Water modules   
    for ( int i = 0; i < 6; i++) {
      barCenter[i] = DetDef::fgd2WaterCenter[i];
      initZ   = barCenter[i] - (DetDef::fgdXYModuleWidth / 2) -  DetDef::fgdXYAirWidth;   
      finalZ  = barCenter[i] + (DetDef::fgdXYModuleWidth / 2) +  DetDef::fgdWaterAirWidth;
      if (pos[2]>initZ && pos[2]<finalZ) return i * 2 + 1.5;
    }

  }

  return -1;

}


//******************************************************************
bool numuCC4piMultiPi_utils::isHMNT(const AnaTrackB* candidate, std::vector<AnaTrackB*> GroupTracks,  bool lowangle, SubDetId::SubDetEnum det) {
  //****************************************************************

  const Float_t* cutMinLA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1LAFVmin : numuCC4piMultiPi_utils::startFGD2LAFVmin;
  const Float_t* cutMaxLA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1LAFVmax : numuCC4piMultiPi_utils::startFGD2LAFVmax;
  const Float_t* cutMinHA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1HAFVmin : numuCC4piMultiPi_utils::startFGD2HAFVmin;
  const Float_t* cutMaxHA = (det == SubDetId::kFGD1) ?  numuCC4piMultiPi_utils::startFGD1HAFVmax : numuCC4piMultiPi_utils::startFGD2HAFVmax;

  for (UInt_t i=0;i<GroupTracks.size(); ++i){
    if (lowangle) {
      if ( anaUtils::InFiducialVolume(det, GroupTracks[i]->PositionStart, cutMinLA, cutMaxLA) ) return GroupTracks[i]->Momentum == candidate->Momentum;
    }
    else {
      if ( anaUtils::InFiducialVolume(det, GroupTracks[i]->PositionStart, cutMinHA, cutMaxHA) ) return GroupTracks[i]->RangeMomentumMuon == candidate->RangeMomentumMuon;
    }
  }
  return false;
}

//******************************************************************
bool numuCC4piMultiPi_utils::VetoCut(numuCC4piMultiPi_utils::MainTrackTopo topo, const AnaEventB& event, AnaTrackB& candidate, 
    SubDetId::SubDetEnum det){
  //****************************************************************

  // To be updated for FGD2
  (void)det;

  if (topo == numuCC4piMultiPi_utils::kLAFwd) {
    AnaTrackB* VetoTrack = cutUtils::FindVetoTrack(event, candidate);
    if (VetoTrack) {
      if (VetoTrack->PositionStart[2]-candidate.PositionStart[2]<-100. && VetoTrack->Momentum/candidate.Momentum>0.8) return false;
    }
    return true;
  }
  if (topo == numuCC4piMultiPi_utils::kHAFwd) {
    AnaTrackB* VetoTrack = cutUtils::FindVetoTrack(event, candidate);
    if (VetoTrack) {
      if (VetoTrack->PositionStart[2]-candidate.PositionStart[2]<-150. && VetoTrack->Momentum/candidate.RangeMomentumMuon>0.9) return false;
    }
    return true;
  }
  if (topo == numuCC4piMultiPi_utils::kHABwd) {
    AnaTrackB* VetoTrack = cutUtils::FindVetoTrack(event, candidate);
    if (VetoTrack) {
      if (VetoTrack->PositionStart[2]-candidate.PositionStart[2]<-400. && VetoTrack->Momentum/candidate.RangeMomentumMuon>0.9) return false;
    }
    return true;
  }
  return true;
}

//******************************************************************
bool numuCC4piMultiPi_utils::ExternalCut(numuCC4piMultiPi_utils::MainTrackTopo topo, const AnaEventC& event, AnaTrackB& candidate, 
    SubDetId::SubDetEnum det){
  //****************************************************************

  // To be updated for FGD2
  // (void)det;

  if ( topo == numuCC4piMultiPi_utils::kLAFwd ) {
    if ( GetFgdLayer(candidate.PositionStart, det) > 27) {
      EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];
      int nFgdTracks=EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC];
      for (Int_t i=0;i<nFgdTracks;i++){
        AnaTrackB* track = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC][i]);
        AnaFGDParticleB *fgdTrack = track->FGDSegments[0];
        if( !fgdTrack ) continue;
        if( SubDetId::GetDetectorUsed(fgdTrack->Detector,SubDetId::kFGD1) ) return false;
      }
    }
    return true;
  }
  if ( topo == numuCC4piMultiPi_utils::kLABwd) {
    if ( GetFgdLayer(candidate.PositionStart, det) < 2 ) return false;
    return true;
  }
  return true;
}

//*******************************************************************
int numuCC4piMultiPi_utils::PIDCut(numuCC4piMultiPi_utils::MainTrackTopo topo, const AnaTrackB& candidate, SubDetId::SubDetEnum det) {
  //*****************************************************************
  if ( topo == numuCC4piMultiPi_utils::kLAFwd ) {
    if (cutUtils::MuonPIDCut(candidate)){
      if ( det == SubDetId::kFGD1 && anaUtils::InFiducialVolume(SubDetId::kFGD2, candidate.PositionEnd, numuCC4piMultiPi_utils::_FVdefminFGD2, numuCC4piMultiPi_utils::_FVdefmaxFGD2) ) {
        if ( candidate.Momentum>280. ) return 2;
      }
      if ( candidate.nECALSegments>0 ) {
        if ( candidate.ECALSegments[0]->PIDMipEm>15 ) {
          if ( anaUtils::TrackUsesDet(candidate,SubDetId::kTECAL) ) return 3;
          if ( anaUtils::InFiducialVolume(SubDetId::kDSECAL, candidate.PositionEnd, numuCC4piMultiPi_utils::_FVdefminDsECal, numuCC4piMultiPi_utils::_FVdefmaxDsECal) ) return 3;
        }
      }
      return 1;
    }
    return 0;
  }
  else if ( topo == numuCC4piMultiPi_utils::kLABwd  ) {
    //if ( anaUtils::GetPIDLikelihood(candidate, 0, false) > 0.05 ) return 1;  // old BWD muon PID
    if ( numuCC4piMultiPi_utils::BWDMuonPIDCut(candidate) ) return 1;      // new BWD muon PID (added by Danaisis)
    return 0;
  }
  else if ( topo == numuCC4piMultiPi_utils::kHAFwd ||  topo == numuCC4piMultiPi_utils::kHABwd) {
    if ( numuCC4piMultiPi_utils::MuonECALPIDCut(candidate) ) return 1;
    return 0;
  }
  return 1;
}

//**************************************************
bool numuCC4piMultiPi_utils::BWDMuonPIDCut(const AnaTrackB& track){
  //************************************************
  Float_t cut1 = 0.95;
  Float_t cut2 = 0.65;
  Float_t cut3 = 0.05;
  Float_t pcut1 = 200;
  Float_t PIDLikelihood[4];
  anaUtils::GetPIDLikelihood(track, PIDLikelihood);
  if (track.Momentum < pcut1 ){
    if (((PIDLikelihood[0]+PIDLikelihood[3])/(1-PIDLikelihood[2]) > cut1 ) && (PIDLikelihood[0] > cut2)) return true;
  }
  if (track.Momentum >= pcut1 ){
    if (PIDLikelihood[0] > cut3) return true; 
  } 
  return false;
}

//**************************************************
bool numuCC4piMultiPi_utils::MuonECALPIDCut(const AnaTrackB& track){
  //************************************************
  Float_t cut1 = 0.0;
  Float_t cut2 = 1.0;
  Float_t cut3 = 2.6;
  // if a track enters SMRD then there is no need to apply a cuts since SMRD presence is already a good criteria to select muons
  // if ( SubDetId::GetDetectorUsed(track.Detector, SubDetId::kSMRD) ) return true;
  if( track.nECALSegments > 0 ){
    AnaECALParticleB* ECalSeg = static_cast<AnaECALParticleB*>( track.ECALSegments[0] );
    if ( ECalSeg->PIDMipEm>-100 && ECalSeg->Length>0 && ECalSeg->EMEnergy>0 ) {
      if ( ECalSeg->PIDMipEm < cut1 && ECalSeg->Length/ECalSeg->EMEnergy > cut2 && ECalSeg->Length/ECalSeg->EMEnergy < cut3) return true;
    }
  }
  return false;
}