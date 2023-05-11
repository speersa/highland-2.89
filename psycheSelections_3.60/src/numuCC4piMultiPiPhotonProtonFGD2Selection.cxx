#include "numuCC4piMultiPiPhotonProtonFGD2Selection.hxx"

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
void numuCC4piMultiPiPhotonProtonFGD2Selection::DefineSteps(){
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

  AddStep(StepBase::kAction,      "fill summary",                   new FillSummaryAction_numuCC4piMultiPiPhotonProtonFGD2()); 

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
  AddStep(1,0, StepBase::kCut, "CC-0pi",   new  numuCC4piMultiPi::NoPionCut()); //if passed accum_level=5
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
bool numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
//*********************************************************************
// raise(SIGSEGV);
  if(allCutsPassed[0])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: Fwd CC0pi no proton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton;
  }
  else if(allCutsPassed[1]) {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCC0PiFwdNProtonsNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton;
  }

  else if(allCutsPassed[2])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCC0PiBwd0ProtonsNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton;
  }
  else if(allCutsPassed[3])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCC0PiBwdNProtonsNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton;
  }
  else if(allCutsPassed[4] || allCutsPassed[6])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCC0PiHA0ProtonsNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton;
  }
  else if(allCutsPassed[5] || allCutsPassed[7])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCC0PiHANProtonsNoPhoton" << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton;
  }

  // else if(allCutsPassed[6])  {
  //   static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton;
  // }
  // else if(allCutsPassed[7])  {
  //   static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton;
  // }

  else if(allCutsPassed[8])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCC1PiFwdNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC1PiFwdNoPhoton;
  }
  else if(allCutsPassed[9])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCC1PiHAFwdNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton;
  }

  else if(allCutsPassed[10])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCCOtherFwdNoPhoton" << std::endl;

    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCCOtherFwdNoPhoton;
  }
  else if(allCutsPassed[11])  {
    // std::cout << "numuCC4piMultiPiPhotonProtonFGD2Selection::FillEventSummary: kFGD2NuMuCCPhotonFwd" << std::endl;
    // std::cout << int(SampleId::kFGD2NuMuCCPhotonFwd) << std::endl;
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD2NuMuCCPhotonFwd;
  }

  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);

}


//*********************************************************************
bool FillSummaryAction_numuCC4piMultiPiPhotonProtonFGD2::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*******************************************************************
  // Cast the ToyBox to the appropriate type
  ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&boxB);
  ToyBoxTracker* Tbox = static_cast<ToyBoxTracker*>(&boxB);

  if(!cc4piMultiPibox->MainTrack) return 1;
  Tbox->MainTrack = cc4piMultiPibox->MainTrack;

  AnaEventSummaryB* evesum = static_cast<AnaEventSummaryB*>(event.Summary);

    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton     ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
    // evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
    // evesum->LeptonCandidate[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton   ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC1PiFwdNoPhoton     ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton     ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCCOtherFwdNoPhoton   ] = cc4piMultiPibox->MainTrack;
    evesum->LeptonCandidate[SampleId::kFGD2NuMuCCPhotonFwd          ] = cc4piMultiPibox->MainTrack;


    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
        // evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiHAFwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
        // evesum->LeptonMomentum[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC1PiFwdNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton]  = cc4piMultiPibox->MainTrack->RangeMomentumMuon;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCCOtherFwdNoPhoton]  = cc4piMultiPibox->MainTrack->Momentum;
    evesum->LeptonMomentum[SampleId::kFGD2NuMuCCPhotonFwd]  = cc4piMultiPibox->MainTrack->Momentum;


    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton],          3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton],          3);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton],          3);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton],          3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC1PiFwdNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCCOtherFwdNoPhoton],          3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[SampleId::kFGD2NuMuCCPhotonFwd],                 3);


    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton],              3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton],              3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton],              3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton],              3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton],            3);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton],            3);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC1PiFwdNoPhoton],              3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton],              3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCCOtherFwdNoPhoton],            3);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd, evesum->LeptonDirectionEnd[SampleId::kFGD2NuMuCCPhotonFwd],                   3);


    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton],           4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton],           4);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton],           4);
    //     anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton],           4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC1PiFwdNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCCOtherFwdNoPhoton],           4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[SampleId::kFGD2NuMuCCPhotonFwd],                  4);

    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton],               4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton],               4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton],               4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton],               4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton],             4);

    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton],             4);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton],             4);

    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC1PiFwdNoPhoton],               4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton],               4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCCOtherFwdNoPhoton],             4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd, evesum->LeptonPositionEnd[SampleId::kFGD2NuMuCCPhotonFwd],                    4);


    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton    ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton    ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton    ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton    ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton  ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton  ], 4);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton    ], 4);
    // anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton    ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC1PiFwdNoPhoton   ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton   ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCCOtherFwdNoPhoton   ], 4);
    anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[SampleId::kFGD2NuMuCCPhotonFwd    ], 4);

  if(!cc4piMultiPibox->MainTrack) return 1;
  
    if(cc4piMultiPibox->MainTrack->GetTrueParticle()){
      evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiFwd0ProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiFwdNProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiBwd0ProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiBwdNProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton  ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton  ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      // evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      // evesum->TrueVertex[SampleId::kFGD2NuMuCC0PiHABwdNProtonsNoPhoton    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCC1PiFwdNoPhoton   ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCC1PiHAFwdNoPhoton   ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCCOtherFwdNoPhoton   ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
      evesum->TrueVertex[SampleId::kFGD2NuMuCCPhotonFwd ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
  }
    
  return true;
  // This looks nice, but crashes the code
  // Cast the ToyBox to the appropriate type
  // ToyBoxCC4piMultiPi* cc4piMultiPibox = static_cast<ToyBoxCC4piMultiPi*>(&boxB);
  // ToyBoxTracker* Tbox = static_cast<ToyBoxTracker*>(&boxB);
  
  // AnaEventSummaryB* evesum = static_cast<AnaEventSummaryB*>(event.Summary);

  // if(!cc4piMultiPibox->MainTrack) return 1;
  
  
  // SampleId::SampleEnum SamplesUsed[10] = {

  //   SampleId::kFGD1NuMuCC0PiFwd0ProtonsNoPhoton,    
  //   SampleId::kFGD1NuMuCC0PiFwdNProtonsNoPhoton,    
  //   SampleId::kFGD1NuMuCC0PiBwd0ProtonsNoPhoton,    
  //   SampleId::kFGD1NuMuCC0PiBwdNProtonsNoPhoton,    
  //   SampleId::kFGD2NuMuCC0PiHA0ProtonsNoPhoton,  
  //   SampleId::kFGD2NuMuCC0PiHANProtonsNoPhoton,  
  //   // SampleId::kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton,  
  //   // SampleId::kFGD1NuMuCC0PiHABwdNProtonsNoPhoton,  
  //   SampleId::kFGD1NuMuCC1PiFwdNoPhoton,      
  //   SampleId::kFGD1NuMuCC1PiHAFwdNoPhoton,       
  //   SampleId::kFGD1NuMuCCOtherFwdNoPhoton,     
  //   SampleId::kFGD1NuMuCCPhotonFwd
  // };




  // for (int i = 0; i < 10; i++){
    
    
  //   SampleId::SampleEnum iSample= SamplesUsed[i];
    
  //   evesum->LeptonCandidate[iSample] = cc4piMultiPibox->MainTrack;


  //   evesum->LeptonMomentum[iSample]   = cc4piMultiPibox->MainTrack->Momentum;
 
  //   anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionStart, evesum->LeptonDirectionStart[iSample], 3);

  //   anaUtils::CopyArray(cc4piMultiPibox->MainTrack->DirectionEnd,   evesum->LeptonDirectionEnd[iSample],   3);


  //   anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->LeptonPositionStart[iSample], 4);
  //   anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionEnd,   evesum->LeptonPositionEnd[iSample],   4);


  //   anaUtils::CopyArray(cc4piMultiPibox->MainTrack->PositionStart, evesum->VertexPosition[iSample], 4);



  //   if(cc4piMultiPibox->MainTrack->GetTrueParticle()){
  //     evesum->TrueVertex[iSample    ] = cc4piMultiPibox->MainTrack->GetTrueParticle()->TrueVertex;
  //   }

    
  
    
  // }
    
  // return true;
}

//**************************************************
bool numuCC4piMultiPiPhotonProtonFGD2Selection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _numuCC4piMultiPiPhotonProtonSelection.IsRelevantRecObjectForSystematicInToy(event, box, track, systId, branch); 
}

//**************************************************
bool numuCC4piMultiPiPhotonProtonFGD2Selection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************
  return _numuCC4piMultiPiPhotonProtonSelection.IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, branch); 
}
