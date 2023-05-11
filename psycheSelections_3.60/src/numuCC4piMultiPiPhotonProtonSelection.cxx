#include "numuCC4piMultiPiPhotonProtonSelection.hxx"

#include "baseSelection.hxx"
#include "SystematicTuning.hxx"
#include "CutUtils.hxx"
#include "EventBoxUtils.hxx"
#include "SubDetId.hxx"
#include "SystId.hxx"
#include "SystematicUtils.hxx"
#include "VersioningUtils.hxx"
#include "trackerSelectionUtils.hxx"
#include <signal.h>


//*********************************************************************
void numuCC4piMultiPiPhotonProtonSelection::DefineSteps(){
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
  AddStep(StepBase::kAction,      "find_protons",                   new FindProtonsAction());
  AddStep(StepBase::kAction,      "find ecal photons",              new numuCC4piMultiPi::FindECalPhotonsAction());


  AddStep(StepBase::kAction,      "Correcttracksense",              new numuCC4piMultiPi::FindCorrectTrackSenseAction()); 
  // AddStep(StepBase::kAction,      "Re finding pions after vertex flipping",                  new numuCC4piMultiPi::FindPionsAction());
  // AddStep(StepBase::kAction,      "Re finding protons after vertex flipping",                   new FindProtonsAction());

  AddStep(StepBase::kAction,      "fill summary",                   new FillSummaryAction_numuCC4piMultiPiPhotonProton()); 

  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex",   new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",     new FillFgdIsoPionsKinVertexAction());

  // Split into two branches for separating out photon-containing events
  AddSplit(2);

  // Add cuts to first branch to select CCPhoton
  AddStep(0, StepBase::kCut, "CC-Photon", new numuCC4piMultiPi::PhotonCut()); //if passed accum_level=5

  AddStep(0, StepBase::kCut,      "Fwd Quality Cut",                new numuCC4piMultiPi::Fwd_Quality());                  //if passed accum_level=6
  AddStep(0, StepBase::kCut,      "Fwd Veto Cut",                   new numuCC4piMultiPi::Fwd_Veto());                     //if passed accum_level=7       
  AddStep(0, StepBase::kCut,      "Fwd PID Cut",                    new numuCC4piMultiPi::Fwd_PID());                      //if passed accum_level=8

  // Opposite-acting cut on second branch to get events which fail photon selection:
  AddStep(1, StepBase::kCut, "No photons (TPC+ECal)", new InvertedStep(new numuCC4piMultiPi::PhotonCut())); //if passed accum_level=5

  // Split second branch into three for CC0pi, CC1pi+ and CCOther
  AddSplit(3,1);

  // Cuts for CC0pi
  AddStep(1,0, StepBase::kCut, "CC-0pi",   new  numuCC4piMultiPi::NoPionCut()); //if passed accum_level=6
  // AddStep(1,0, StepBase::kCut,         "ToF quality",                    new EventTimeQualityCut(),true);                       //if passed accum_level=6

  AddSplit(4,1,0);
  AddStep(1,0,0, StepBase::kCut,      "Fwd Quality Cut",                new numuCC4piMultiPi::Fwd_Quality());                  //if passed accum_level=7
  AddStep(1,0,0, StepBase::kCut,      "Fwd Veto Cut",                   new numuCC4piMultiPi::Fwd_Veto());                     //if passed accum_level=8       
  AddStep(1,0,0, StepBase::kCut,      "Fwd PID Cut",                    new numuCC4piMultiPi::Fwd_PID());                      //if passed accum_level=9

  AddSplit(2,1,0,0);
  AddStep(1,0,0,0,  StepBase::kCut,      "0 proton cut",                new ZeroProtonsCut());                      //if passed accum_level=10
  AddStep(1,0,0,1,  StepBase::kCut,      "N protons cut",               new NProtonsCut());                      //if passed accum_level=10


  AddStep(1,0,1, StepBase::kCut,      "Bwd Quality Cut",                new numuCC4piMultiPi::Bwd_Quality());                  //if passed accum_level=7
  AddStep(1,0,1, StepBase::kCut,      "Bwd Veto Cut",                   new numuCC4piMultiPi::Bwd_Veto());                     //if passed accum_level=8       
  AddStep(1,0,1, StepBase::kCut,      "Bwd PID Cut",                    new numuCC4piMultiPi::Bwd_PID());                      //if passed accum_level=9

  AddSplit(2,1,0,1);
  AddStep(1,0,1,0,  StepBase::kCut,      "0 proton cut",                new ZeroProtonsCut());                      //if passed accum_level=10
  AddStep(1,0,1,1,  StepBase::kCut,      "N protons cut",               new NProtonsCut());                      //if passed accum_level=10



  AddStep(1,0,2, StepBase::kCut,      "HAFwd Quality Cut",                new numuCC4piMultiPi::HAFwd_Quality());                  //if passed accum_level=7
  AddStep(1,0,2, StepBase::kCut,      "HAFwd Veto Cut",                   new numuCC4piMultiPi::HAFwd_Veto());                     //if passed accum_level=8       
  AddStep(1,0,2, StepBase::kCut,      "HAFwd PID Cut",                    new numuCC4piMultiPi::HAFwd_PID());                      //if passed accum_level=9
  AddSplit(2,1,0,2);
  AddStep(1,0,2,0,  StepBase::kCut,      "0 proton cut",                new ZeroProtonsCut());                      //if passed accum_level=10
  AddStep(1,0,2,1,  StepBase::kCut,      "N protons cut",               new NProtonsCut());                      //if passed accum_level=10

  AddStep(1,0,3, StepBase::kCut,      "HABwd Quality Cut",                new numuCC4piMultiPi::HABwd_Quality());                  //if passed accum_level=7
  AddStep(1,0,3, StepBase::kCut,      "HABwd Veto Cut",                   new numuCC4piMultiPi::HABwd_Veto());                     //if passed accum_level=8       
  AddStep(1,0,3, StepBase::kCut,      "HABwd PID Cut",                    new numuCC4piMultiPi::HABwd_PID());                      //if passed accum_level=9
  AddSplit(2,1,0,3);
  AddStep(1,0,3,0,  StepBase::kCut,      "0 proton cut",                new ZeroProtonsCut());                      //if passed accum_level=10
  AddStep(1,0,3,1,  StepBase::kCut,      "N protons cut",               new NProtonsCut());                      //if passed accum_level=10


  // Cuts for CC1pi: true -- Positive pion
  AddStep(1,1, StepBase::kCut, "CC-1pi",   new  numuCC4piMultiPi::OnePionCut(true)); // positive pion

  AddSplit(2,1,1);
  AddStep(1,1,0, StepBase::kCut,      "Fwd Quality Cut",                new numuCC4piMultiPi::Fwd_Quality());                  //if passed accum_level=7
  AddStep(1,1,0, StepBase::kCut,      "Fwd Veto Cut",                   new numuCC4piMultiPi::Fwd_Veto());                     //if passed accum_level=8       
  AddStep(1,1,0, StepBase::kCut,      "Fwd PID Cut",                    new numuCC4piMultiPi::Fwd_PID());                      //if passed accum_level=9

  AddStep(1,1,1, StepBase::kCut,      "HAFwd Quality Cut",                new numuCC4piMultiPi::HAFwd_Quality());                  //if passed accum_level=7
  AddStep(1,1,1, StepBase::kCut,      "HAFwd Veto Cut",                   new numuCC4piMultiPi::HAFwd_Veto());                     //if passed accum_level=8       
  AddStep(1,1,1, StepBase::kCut,      "HAFwd PID Cut",                    new numuCC4piMultiPi::HAFwd_PID());                      //if passed accum_level=9


  // Cuts for CCOther
  AddStep(1,2, StepBase::kCut, "CC-Other", new  numuCC4piMultiPi::OthersCut());

  AddStep(1,2, StepBase::kCut,      "Fwd Quality Cut",                new numuCC4piMultiPi::Fwd_Quality());                  //if passed accum_level=7
  AddStep(1,2, StepBase::kCut,      "Fwd Veto Cut",                   new numuCC4piMultiPi::Fwd_Veto());                     //if passed accum_level=8       
  AddStep(1,2, StepBase::kCut,      "Fwd PID Cut",                    new numuCC4piMultiPi::Fwd_PID());                      //if passed accum_level=9



  SetBranchAlias(0,  "Fwd CC0pi no proton",          1,0,0,0);
  SetBranchAlias(1,  "Fwd CC0pi N protons",          1,0,0,1);

  SetBranchAlias(2,  "Bwd CC0pi no proton",          1,0,1,0);
  SetBranchAlias(3,  "Bwd CC0pi N protons",          1,0,1,1);

  SetBranchAlias(4,  "HAFwd CC0pi no proton",                  1,0,2,0);
  SetBranchAlias(5,  "HAFwd CC0pi N protons",                  1,0,2,1);

  SetBranchAlias(6,  "HABwd CC0pi no proton",                  1,0,3,0);
  SetBranchAlias(7,  "HABwd CC0pi N protons",                  1,0,3,1);


  SetBranchAlias(8,  "Fwd CC1pi",                    1,1,0);
  SetBranchAlias(9,  "HAFwd CC1pi",                    1,1,1);

  SetBranchAlias(10,  "Fwd CCOther",                  1,2);

  SetBranchAlias(11,  "CCPhoton",                     0);



  SetPreSelectionAccumLevel(2);
}


//*********************************************************************
bool numuCC4piMultiPiPhotonProtonSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //*********************************************************************
  // raise(SIGSEGV);
  if(allCutsPassed[0])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC0PiFwd0ProtonsNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton;
  }
  else if(allCutsPassed[1]) {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC0PiFwdNProtonsNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton;
  }

  else if(allCutsPassed[2])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC0PiBwd0ProtonsNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton;
  }
  else if(allCutsPassed[3])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC0PiBwdNProtonsNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton;
  }
  else if(allCutsPassed[4] || allCutsPassed[6])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC0PiHA0ProtonsNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton;
  }
  else if(allCutsPassed[5] || allCutsPassed[7])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC0PiHANProtonsNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton;
  }

  // else if(allCutsPassed[6])  {
  //   static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton;
  // }
  // else if(allCutsPassed[7])  {
  //   static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton;
  // }

  else if(allCutsPassed[8])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC1PiFwdNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiFwdNoPhoton;
  }
  else if(allCutsPassed[9])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCC1PiHAFwdNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton;
  }

  else if(allCutsPassed[10])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCCOtherFwdNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOtherFwdNoPhoton;
  }
  else if(allCutsPassed[11])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonSelection::FillEventSummary: kFGD1NuMuCCPhotonFwd" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCPhotonFwd;
  }

  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);

}


//*********************************************************************
bool FillSummaryAction_numuCC4piMultiPiPhotonProton::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*******************************************************************
  // Cast the ToyBox to the appropriate type
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&boxB);
  ToyBoxTracker* Tbox = static_cast<ToyBoxTracker*>(&boxB);

  if(!cc4piMultiPibox->MainTrack) return 1;

  Tbox->MainTrack = cc4piMultiPibox->MainTrack;

  AnaEventSummaryB* evesum = static_cast<AnaEventSummaryB*>(event.Summary);

  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
  // evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
  // evesum->LeptonCandidate[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC1PiFwdNoPhoton     ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton     ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCCOtherFwdNoPhoton   ] = cc4piMultiPibox->MainTrack;
  evesum->LeptonCandidate[SampleId::kFGD1NuMuCCPhotonFwd          ] = cc4piMultiPibox->MainTrack;


  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
  // evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiHAFwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
  // evesum->LeptonMomentum[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC1PiFwdNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCCOtherFwdNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
  evesum->LeptonMomentum[SampleId::kFGD1NuMuCCPhotonFwd]  = cc4piMultiPibox->MainTrack->Momentum;


  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton],          3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton],          3);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton],          3);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton],          3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC1PiFwdNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCCOtherFwdNoPhoton],          3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD1NuMuCCPhotonFwd],                 3);

// std::cout << "Writing costheta to eventsummary: " << cc4piMultiPibox->MainTrack->DirectionStart[2] << std::endl;
// std::cout << "#############################################" << std::endl;

  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton],              3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton],              3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton],              3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton],              3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton],            3);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton],            3);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC1PiFwdNoPhoton],              3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton],              3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCCOtherFwdNoPhoton],            3);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD1NuMuCCPhotonFwd],                   3);


  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton],           4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton],           4);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton],           4);
  //     anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton],           4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC1PiFwdNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCCOtherFwdNoPhoton],           4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD1NuMuCCPhotonFwd],                  4);

  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton],               4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton],               4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton],               4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton],               4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton],             4);

  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton],             4);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton],             4);

  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC1PiFwdNoPhoton],               4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton],               4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCCOtherFwdNoPhoton],             4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD1NuMuCCPhotonFwd],                    4);


  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton    ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton    ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton    ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton    ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton  ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton  ], 4);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton    ], 4);
  // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton    ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC1PiFwdNoPhoton   ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton   ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCCOtherFwdNoPhoton   ], 4);
  anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD1NuMuCCPhotonFwd    ], 4);


  if(cc4piMultiPibox->MainTrack->GetTrueParticle()){
    evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiHA0ProtonsNoPhoton  ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiHANProtonsNoPhoton  ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    // evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    // evesum->TrueVertex[SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCC1PiFwdNoPhoton   ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton   ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCCOtherFwdNoPhoton   ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
    evesum->TrueVertex[SampleId::kFGD1NuMuCCPhotonFwd ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
  }
  return true;

}

//**************************************************
bool numuCC4piMultiPiPhotonProtonSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************
  (void)event;

  switch (systId){

    // Special treatments go first.
    // High angle only (FGD-ECAL matching stuff)

    case SystId::kTpcP0dMatchEff:
      if (branch == 2 || branch ==3) return true;
      else return false;
      break;
    case SystId::kFgdECalMatchEff:
    case SystId::kFgdECalSmrdMatchEff:
      if (branch == 4 || branch == 5 || branch == 6 || branch == 7 || branch == 9) return true;
      else return false;
      break;


      // TPC tracking. Low angle only.
    case SystId::kChargeIDEff:
    case SystId::kTpcClusterEff:
    case SystId::kTpcTrackEff:
      if ((branch != 4) && (branch != 5) && (branch != 6) && (branch != 7 ) && (branch != 9) ) return true;
      else return false;
      break;


      // FGD    
    case SystId::kECalTrackEff:    
    case SystId::kFgdHybridTrackEff:                                                     
    case SystId::kMichelEleEff:
      // FGD matching
      // TPC matching
    case SystId::kTpcFgdMatchEff:
      //Not entirely sure why this is relevant for non-backawrd samples?
      // Normalization
    case SystId::kPileUp:
    case SystId::kFgdMass:
    case SystId::kOOFV:                                                                
    case SystId::kSandMu: 
      // SI
    case SystId::kSIPion:
    case SystId::kSIProton:

      // ECAL Related
      // All branches have a photon/no photon split, so these are always relevant imo.
    case SystId::kECalPhotonPileUp:
    case SystId::kECalEmHipPID:
    case SystId::kTpcECalMatchEff:        

      // Finally, flux weight.
    case SystId::kFluxWeight:
      return true;
      break;




    default:
      return false;
      break;
  }

  return false;
}



//**************************************************
bool numuCC4piMultiPiPhotonProtonSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************
  // all CC4piMultiPibox cases
  const ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<const ToyBoxCC4piMultiPi*>(&box);
  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);

  if (!track) return false;
  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true; 

  if (_numuCCSelection.IsRelevantSystematic (event, box, systId, branch) &&
      _numuCCSelection.IsRelevantRecObjectForSystematicInToy(event,box,track,systId,branch)) return true;


  // all CC4piMultiPibox cases
  switch (systId){
    // Fall back through the relevant ones
    // TPC reco

    // No tunning for this
    case SystId::kTpcClusterEff:
      return true;
      break;

    case SystId::kChargeIDEff:
    case SystId::kTpcFgdMatchEff:
      // CC0pi0p already handled by numuCCSelection tunning.
      // For CC-N-Protons consider proton TPC objects
      if (track == cc4piMultiPibox->MainTrack) return true;  
      if (branch == 1 || branch == 3 || branch == 5 || branch == 7)
      {
        if (ccmultipibox->pionBox.nProtonTPCtracks==1 && track==ccmultipibox->pionBox.ProtonTPCtracks[0]) return true;
      }
      // For CC1pi also the positive Pion in the TPC matters
      if (branch == 8 || branch == 9){
        if (ccmultipibox->pionBox.nPositivePionTPCtracks==1 && track==ccmultipibox->pionBox.PositivePionTPCtracks[0]) return true;
      }
      // For CCPhoton (why ?) and CCOther consider the negative pion when there are no other pions
      else if (branch == 10 || branch == 11){
        if (ccmultipibox->pionBox.nNegativePionTPCtracks==1 && track==ccmultipibox->pionBox.NegativePionTPCtracks[0] &&
            ccmultipibox->pionBox.nOtherPions==1 && ccmultipibox->pionBox.nPosPions == 0) return true;
      }
      return false;

      break;

      // ECAL Related 
      // These are mostly related to the photon/no split that happens in the very beginning.
      // Since all branches have this split, these syst are relevant in every branch.
    case SystId::kECalEmHipPID:
    case SystId::kECalPhotonPileUp:
    case SystId::kTpcECalMatchEff:
      // Let photon proton method make decision for low angle samples.
      // CC0Pi0p or CC0PiNp
      if(branch == 0 || branch == 2) return _numuCCMultiPiPhotonProtonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 1);
      if(branch == 1 || branch == 3) return _numuCCMultiPiPhotonProtonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 2);
      // CC1Pi
      if(branch == 8 ) return _numuCCMultiPiPhotonProtonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 3);
      // CCOther
      if(branch == 10) return _numuCCMultiPiPhotonProtonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 4);
      // CCPhoton
      if(branch == 11) return _numuCCMultiPiPhotonProtonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 0);
      // High Angle samples always true
      if (branch == 4 || branch == 5 || branch == 6 || branch == 7 || branch == 9){
        if (track == cc4piMultiPibox->MainTrack) return true;  
      }
      return false;
      break;

      // This is only relevant in backward samples.
    case SystId::kTpcP0dMatchEff:
      {
        // BWD
        if (branch == 2 || branch == 3){
          if (track == cc4piMultiPibox->MainTrack) return true; 
          // No BWD 1pi or BWD ccother, so this is it
        }
        return false;
        break;
      }


    case SystId::kFgdECalMatchEff:
    case SystId::kFgdECalSmrdMatchEff:
      {
        // Only relevant for High Angle Samples
        if (branch == 4 || branch == 5 || branch == 6 || branch == 7 || branch == 9){
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
bool numuCC4piMultiPiPhotonProtonSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************
  const ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<const ToyBoxCC4piMultiPi*>(&box);
  //const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);

  AnaTrueParticleB* track = static_cast<AnaTrueParticleB*>(trueObj);


  if (!track) return false;
  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true;

  if (_numuCCSelection.IsRelevantSystematic (event, box, systId, branch) &&
      _numuCCSelection.IsRelevantTrueObjectForSystematicInToy(event,box,track,systId,branch)) {
    return true;
  }

  // all CC4piMultiPibox cases
  switch (systId){
    case SystId::kTpcFgdMatchEff:
      // In low angle samples TPCs are used to track muons therefore relevant.
      if ((branch>-1 && branch<4) || branch == 8 || branch == 10 || branch == 11) {
        if(cc4piMultiPibox->MainTrack) return true;   
      }
      // CC1Pi track pi+
      if (branch == 8 || branch == 9){
        if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1) return true; 
      }
      // CCOther and CCPhoton track other pions
      if (branch == 10 || branch == 11){
        if (cc4piMultiPibox->pionBox.nOtherPions==1) return true;  
      }
      return false;
      break;


      // The CCPhoton-Proton selection implementation is used here
    case SystId::kTpcTrackEff:                                                                
      // Don't consider pions when there are many TPC ones (a conservative check)
      // Cases in which we must loose two or more pions are excluded (0.01*0.01 probability)
      if (cc4piMultiPibox->pionBox.nNegativePionTPCtracks + cc4piMultiPibox->pionBox.nPositivePionTPCtracks > 2 ||
          cc4piMultiPibox->pionBox.nNegativePionTPCtracks > 1) return false;

      // If the are few TPC pions consider them, muons, electrons and protons
      if (abs(track->PDG)==211 || abs(track->PDG)==13 || abs(track->PDG)==11 || abs(track->PDG)==2212) return true;

      return false;
      break;

    case SystId::kTpcP0dMatchEff:
      if (branch == 2 || branch == 3){
        if(cc4piMultiPibox->MainTrack) return true;   
      }
      // Not entirely sure why but lets just keep them here for the moment.
      if (branch == 8 || branch == 9){
        if (cc4piMultiPibox->pionBox.nPositivePionTPCtracks==1) return true; 
      }
      if (branch == 10 || branch == 11){
        if (cc4piMultiPibox->pionBox.nOtherPions==1 && cc4piMultiPibox->pionBox.nPosPions == 0) return true;  
      }
      return false;
      break;

    case SystId::kTpcECalMatchEff:
      // CC0pi0p
      if(branch == 0 || branch == 2) return _numuCCMultiPiPhotonProtonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, track, systId, 1);
      // High Angle Samples
      // CC0PiNp
      if(branch == 1 || branch == 3) return _numuCCMultiPiPhotonProtonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, track, systId, 2);
      // CC1Pi
      if(branch == 8) return _numuCCMultiPiPhotonProtonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, track, systId, 3);
      // CCOther
      if(branch == 10) return _numuCCMultiPiPhotonProtonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, track, systId, 4);
      // High Angle samples use 4pi treatment
      // Always relevant for highangle samples!
      if (branch == 4 || branch == 5 || branch == 6 || branch == 7 || branch == 9){ 
        return true;
      }
      // CCPhoton
      if(branch == 11) return _numuCCMultiPiPhotonProtonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, track, systId, 0);

      return false;
      break;



    case SystId::kFgdECalMatchEff:
    case SystId::kFgdECalSmrdMatchEff:
      if (branch == 4 || branch == 5 || branch == 6 || branch == 7 || branch == 9) return true; 
      return false;
      break;

      // pion SI
      // Trust photon proton over 4pi.
    case SystId::kSIPion:
      if (cc4piMultiPibox->pionBox.nOtherPions > 1 || cc4piMultiPibox->pionBox.nPosPions > 2 ) return false;
      return true;
      break;


    case SystId::kFgdHybridTrackEff:
      return anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()),
          track->Position);
      break;


      // Contributors for relevant objects for proton SI
      // Trust photon proton over 4pi.
    case SystId::kSIProton:
      // Speical treatment for 0p and Np samples.
      //Proton Samples requiers sliglhy different treatment
      //If event has more than one proton turn off, because it is unlikely SI will change topology, otherwise true
      if (branch == 0 || branch == 1 || branch == 2 || branch == 3 || branch == 4 || branch == 5 || branch == 6 || branch == 7)
      {
        if ((cc4piMultiPibox->pionBox.nProtonTPCtracks+cc4piMultiPibox->pionBox.nProtonFGDtracks) > 1 ) return false;
        else return true;
      }
      // Otherwise rollout standard treatment.
      // If there are  many pions, i.e. topology cannot change, then do not use
      // the systematic
      if (cc4piMultiPibox->pionBox.nOtherPions >1 || cc4piMultiPibox->pionBox.nPosPions > 2 ) return false; 

      // Otherwise check that a proton contributes to any of the objects in the
      // box

      return cutUtils::numuCCTrkMultiPi::CheckTrueCausesBoxSimple(*track, cc4piMultiPibox->pionBox);
      break;

      // To be tuned
    case SystId::kECalTrackEff: 
      // Otherwise let old selection decide.
      if (!anaUtils::InFiducialVolume(SubDetId::kTECAL,track->Position) && 
          !anaUtils::InFiducialVolume(SubDetId::kDSECAL,track->Position)) return false;

      // Only one ECal Photon present and is what defines the CCPhoton topology
      if (cc4piMultiPibox->pionBox.nECalPhotons == 1 && cc4piMultiPibox->pionBox.nOtherPions == cc4piMultiPibox->pionBox.nNegPions){

        // check the true particle produced the shower
        AnaTrackB* photon = cc4piMultiPibox->pionBox.ECalPhotons[0];
        if(photon->GetTrueParticle() && track->ID == photon->GetTrueParticle()->ID) return true;
        if(photon->GetTrueParticle() && track->ID == photon->GetTrueParticle()->ParentID) return true;
        if(photon->GetTrueParticle() && track->ID == photon->GetTrueParticle()->GParentID) return true;
        if(photon->GetTrueParticle() && track->ID == photon->GetTrueParticle()->PrimaryID) return true;

      }

      // No ECal Photons or TPC pi0s reconstructed, but there is a true ECal Photon
      if (cc4piMultiPibox->pionBox.nECalPhotons == 0 && cc4piMultiPibox->pionBox.nOtherPions == cc4piMultiPibox->pionBox.nNegPions){

        // Check if there is a reconstructed ECal object from this true particle
        // If there is, don't apply the systematic
        EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);
        for(int i = 0; i < EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithECal]; i++ ) {
          AnaTrackB *ptrack = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithECal][i]);

          if(ptrack->GetTrueParticle() && track->ID == ptrack->GetTrueParticle()->ID) return false;
          if(ptrack->GetTrueParticle() && track->ID == ptrack->GetTrueParticle()->ParentID) return false;
          if(ptrack->GetTrueParticle() && track->ID == ptrack->GetTrueParticle()->GParentID) return false;
          if(ptrack->GetTrueParticle() && track->ID == ptrack->GetTrueParticle()->PrimaryID) return false;
        }

        // only consider EM particles
        if(track->PDG != 22 && track->PDG != 11 && track->PDG != -11) return false;

        // require minimum momentum on true track
        if(track->Momentum<30) return false;

        // No reconstructed object associated with the true track - apply systematic
        return true;
      }

      return false;
      break;

    default:
      return true;
      break;
  }
  // For the rest of the systematic return true
  return true;
}


//*********************************************************************
bool numuCC4piMultiPi::PhotonCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //********************************************************************

  (void)event;

  ToyBoxCC4piMultiPi* ccmultipibox = static_cast<ToyBoxCC4piMultiPi*>(&box);
  int nECALPhotons;
  int nOtherPions;
  int nNegPions;
  nECALPhotons = ccmultipibox->pionBox.nECalPhotons;
  nOtherPions = ccmultipibox->pionBox.nOtherPions;
  nNegPions = ccmultipibox->pionBox.nNegPions;
  // std::cout << "nECALPhotons:" << nECALPhotons << std::endl;
  // std::cout << "nOtherPions:" << nOtherPions << std::endl;
  // std::cout << "nNegPions:" << nNegPions << std::endl;
  // ECal object passes EmHip and layer cuts
  if (ccmultipibox->pionBox.nECalPhotons > 0) return true;

  // pi0 present doesn't lead to ECalPhoton
  if (ccmultipibox->pionBox.nOtherPions != ccmultipibox->pionBox.nNegPions) return true;

  return false;
}
