#include "numuCCZeroPiSelection.hxx"
#include "numuCCMultiPiSelection.hxx"
#include "baseSelection.hxx"
#include "CutUtils.hxx"
#include "EventBoxUtils.hxx"
#include "numuCCZeroPiUtils.hxx"
#include <FiducialVolumeDefinition.hxx>
#include "numuCCZeroPiDetectorDefinition.hxx"
#include "SystIdHighland.hxx" 
#include "PropagationUtils.hxx"
#include "HighlandTruthUtils.hxx"
#include <ND280BeamBunching.hxx>


//********************************************************************
numuCCZeroPiSelection::numuCCZeroPiSelection(bool forceBreak, SubDetId::SubDetEnum det): SelectionBase(forceBreak, 
    EventBoxId::kEventBoxTracker) {
  //********************************************************************

  if( det!=SubDetId::kFGD1 &&
      det!=SubDetId::kFGD2){
    std::cout<<" numuCCZeroPiSelection() det bit is not FGD " << det << std::endl;
    exit(1);
  }

  // Detector FV
  _detectorFV = det;



  // Change FV definition to take all thickness
  // Note! this will affect all downstream stuff
  //FVDef::FVdefminFGD1[2] = 0;
  //FVDef::FVdefmaxFGD1[2] = 0;

  //FVDef::FVdefminFGD2[2] = 0;
  //FVDef::FVdefmaxFGD2[2] = 0;
  //If the FV is changed here then it is ok to use FV track categories later,
  //otherwise need wider groups

}

//********************************************************************
void numuCCZeroPiSelection::DefineSteps(){
  //********************************************************************

  /*! The selection is organized in the following way.
   * First: in order to onclude bwd tracks in the selection,  first step (after event quality cut) is to apply the ToF
   * and flip tracks if needed,  in this way one can deal with HM track generally (although may modify FV cuts if needed depending on track direction)
   * The key point is to find the vertex,  three possible cases are considered
   * a. HMN track (TPC) in FGD FV defines a vertex
   * b. no HMN track hence the vertex if defined by HMP
   * c. no TPC track candidate available, hence FGD (no TPC) track defines a vertex
   * Proton and muon candidates:
   * a. HMN availalble -> muon candidate, proton is either HMP or FGD-noTPC if available
   * b. HMP available -> proton candidate, muon candidate is FGD-noTPC (if no HMN)
   * c. the longest (considering also ECal and SMRD sub-detectors) FGD-noTPC track is a muon candidate
   * The analysis proceeds with finding all possible proton candidates once the vertex candidate is identified
   */


  //Quality + find all usefull tracks
  AddStep(StepBase::kCut,    "Event quality",           new EventQualityCut(),              true  );

  AddStep(StepBase::kAction, "Find leading tracks",     new zero_pi::FindTrackerTracksAction()    );
  AddStep(StepBase::kAction, "Find candidates",         new zero_pi::FindMuonCandidateAction()    );
  AddStep(StepBase::kAction, "Find vertex",             new zero_pi::FindVertexAction()           );

  //So we have a vertex,  now can look for all possible proton candidates
  AddStep(StepBase::kAction, "Find proton candidates",  new zero_pi::FindProtonCandidatesAction() );  
  AddStep(StepBase::kAction, "Fill summary",            new zero_pi::FillSummaryAction()          );
  AddStep(StepBase::kAction, "Find michel e-",          new zero_pi::FindMichelElectronsAction()  );

  AddStep(StepBase::kAction, "Find ECal photons",       new zero_pi::FindECalPhotonsAction());

  //Split into three branches: HMN track muon candidate,  HMP but no HMN and no HMN + no HMP
  AddSplit(3);

  // First (zero) branch is for cases with HMN muon candidate available
  AddStep(0, StepBase::kCut,    "HMN vertex",                   new zero_pi::MuonCandidate_TPC_VertexCut(), true);  
  AddStep(0, StepBase::kCut,    "Muon PID",                     new zero_pi::MuonCandidate_TPC_MuonPIDCut()     );

  // Add split: this is to isolate DIS events CS
  AddSplit(2, 0);

  AddStep(0, 0, StepBase::kCut,    "1 neg track",                  new zero_pi::OneNegativeTrackCut()              );

  // Add split: this is to isolate CC-1pi control sample and later ME and
  // ECal-veto CSs

  AddSplit(3, 0, 0);

  // A cut to expclicitely require only muon and proton tracks to be present
  AddStep(0, 0, 0, StepBase::kCut,    "Only muon and proton tracks",  new zero_pi::MuonProtonTracksCut()  ); 

  AddStep(0, 0, 0, StepBase::kCut,    "No michel ele",                new zero_pi::MichelElectronCut()    );
  AddStep(0, 0, 0, StepBase::kCut,    "ECal photon veto",             new zero_pi::ZeroECalPhotonsCut());


  // Inversed ME CS and ECal-veto CS
  AddStep(0, 0, 2,  StepBase::kCut,    "Only muon and proton tracks",  new zero_pi::MuonProtonTracksCut()  ); 

  AddSplit(3, 0, 0, 2);

  // Inversed ME CS
  AddStep(0, 0, 2, 0, StepBase::kCut,    "With at least 1 michel ele",   new InvertedStep( new zero_pi::MichelElectronCut()) ); // inverted ME cut
  AddStep(0, 0, 2, 0, StepBase::kCut,    "ECal photon veto",             new zero_pi::ZeroECalPhotonsCut());

  // Inversed ECal-veto CS
  AddStep(0, 0, 2, 1, StepBase::kCut,    "No michel ele",       new zero_pi::MichelElectronCut() );
  AddStep(0, 0, 2, 1, StepBase::kCut,    "ECal photon cand",    new InvertedStep( new zero_pi::ZeroECalPhotonsCut())); // inverted ECal-veto cut



  // Add a split to branch 0 with 3 sub-branches 
  AddSplit(3, 0, 0, 0);

  //--------- Case 0: one single TPC muon track ------------ 
  AddStep(0, 0, 0, 0, StepBase::kCut, "No protons",               new zero_pi::NProtonTracksCut(0));

  //--------- Case 1 and Case 2:  TPC muon + TPC/FGD proton ------------ 
  AddStep(0, 0, 0, 1, StepBase::kCut, "One proton",               new zero_pi::NProtonTracksCut(1));

  AddSplit(2, 0, 0, 0, 1);

  //--------- Case 1: TPC muon + TPC proton  ------------ 
  AddStep(0, 0, 0, 1, 0,  StepBase::kCut,       "One TPC proton",     new zero_pi::N_TPC_ProtonTracksCut(1)         );

  //--------- Case 2: TPC muon + FGD proton  ------------ 
  AddStep(0, 0, 0, 1, 1,  StepBase::kCut,       "One FGD proton",     new zero_pi::N_FGD_ProtonTracksCut(1)         );
  AddStep(0, 0, 0, 1, 1,  StepBase::kCut,       "Stopping proton",    new zero_pi::ProtonCandidate_FGD_StoppingCut());

  //--------- Multi-proton with TPC muon
  AddStep(0, 0, 0, 2, StepBase::kCut,       "Multi protons",      new zero_pi::MultiProtonTracksCut());


  // CC-1pi CS
  AddStep(0, 0, 1, StepBase::kCut,    "HMP track is pion",          new zero_pi::HMP_TPC_PionPIDCut()); 
  AddStep(0, 0, 1, StepBase::kCut,    "Two tracker tracks",         new zero_pi::NTrackerTracksCut(2)); 

  // CC-DIS CS
  AddStep(0, 1, StepBase::kCut,    "HMP track is pion",         new zero_pi::HMP_TPC_PionPIDCut() ); 
  AddStep(0, 1, StepBase::kCut,    "Multi-TPC tracks ",         new zero_pi::MultiTpcTracksCut()  ); 


  //--------- Case 3: TPC proton + FGD muon ------------ 
  AddStep(1, StepBase::kCut,    "HMP vertex",                   new zero_pi::HMP_TPC_VertexCut(),           true);  

  // A cut to expclicitely require only muon and proton tracks to be present 
  AddStep(1, StepBase::kCut,    "Only muon and proton tracks",  new zero_pi::MuonProtonTracksCut()              ); 
  AddStep(1, StepBase::kCut,    "Leading proton TPC track",     new zero_pi::ProtonCandidate_TPC_VertexCut()    ); 

  AddStep(1, StepBase::kAction, "Find correct muon sense",      new zero_pi::FindCorrectMuonSenseAction()       );
  AddStep(1, StepBase::kCut,    "Long FGD track",               new zero_pi::MuonCandidate_FGD_LongFGDTrackCut());
  AddStep(1, StepBase::kCut,    "FGD muon PID",                 new zero_pi::MuonCandidate_FGD_MuonPIDCut()     );
  AddStep(1, StepBase::kCut,    "Common vertex",                new zero_pi::CommonVertexCut_muFGD_pTPC()       );
  AddStep(1, StepBase::kCut,    "Stopping muon",                new zero_pi::MuonCandidate_FGD_StoppingCut()    );

  // Cuts to remove ME and ECal-activity
  AddStep(1, StepBase::kCut,    "No michel ele (FGD case)",     new zero_pi::MichelElectronCut());
  AddStep(1, StepBase::kCut,    "ECal photon veto",             new zero_pi::ZeroECalPhotonsCut());


  // Add a split to branch 1 with 2 sub-branches 
  AddSplit(2, 1);

  //--------- Case 3: one single proton track (TPC) + FGD muon ------------ 
  AddStep(1, 0, StepBase::kCut, "One proton",         new zero_pi::NProtonTracksCut(1)    );

  //--------- Case 3 + multi-protons  ------------ 
  AddStep(1, 1, StepBase::kCut, "Multi -protons",     new zero_pi::MultiProtonTracksCut() );

  //--------- Case 4: one single FGD muon
  AddStep(2, StepBase::kCut,    "Muon cand is a HA cand",     new zero_pi::MuonCandidate_FGD_VertexCut(), true);

  // A cut to expclicitely require only muon and proton tracks to be present
  AddStep(2, StepBase::kCut,    "Only muon and proton tracks", new zero_pi::MuonProtonTracksCut()             ); 

  AddStep(2, StepBase::kCut,    "Stopping muon",        		  new zero_pi::MuonCandidate_FGD_StoppingCut()    );
  AddStep(2, StepBase::kCut,    "Positive time of flight",    new zero_pi::MuonCandidate_FGD_ToFCut()         );
  AddStep(2, StepBase::kCut,    "ECal PID",				            new zero_pi::MuonCandidate_FGD_ECalPIDCut()     );
  AddStep(2, StepBase::kCut,    "ECal PID2 : Length/E",		    new zero_pi::MuonCandidate_FGD_ECalPID2Cut()    );

  AddStep(2, StepBase::kCut,    "No michel ele (FGD case)",   new zero_pi::MichelElectronCut());
  AddStep(2, StepBase::kCut,    "ECal photon veto",           new zero_pi::ZeroECalPhotonsCut());

  // Add a split to branch 0 with 2 sub-branches 
  AddSplit(2, 2);

  //--------- Single FGD muon ------------ 
  AddStep(2, 0, StepBase::kCut, "No proton",      new zero_pi::NProtonTracksCut(0));

  //---------  ------------ 
  AddStep(2, 1, StepBase::kCut, "Multi protons",  new zero_pi::MultiProtonTracksCut());

  // Michel taggig sideband

  SetBranchAlias(0,   "muTPC", 	      0, 0, 0, 0    );
  SetBranchAlias(1,   "muTPC+pTPC",   0, 0, 0, 1, 0 );
  SetBranchAlias(2,   "muTPC+pFGD",   0, 0, 0, 1, 1 ); 
  SetBranchAlias(3,   "muFGD+pTPC",	  1, 0          );
  SetBranchAlias(4,   "muFGD",        2, 0          );

  // Control samples 
  SetBranchAlias(5, "CC 1pi",              0, 0, 1  );
  SetBranchAlias(6, "CC DIS",              0, 1  );
  SetBranchAlias(7, "CC Michel",           0, 0, 2, 0);
  SetBranchAlias(8, "CC ECal-photon veto", 0, 0, 2, 1);

  // Multi-proton topologies
  SetBranchAlias(9,   "muTPC+Np",       0, 0, 0, 2  );
  SetBranchAlias(10,  "muFGD+pTPC+Np",	1, 1        );
  SetBranchAlias(11,  "muFGD+Np",       2, 1        );


}

//**************************************************
void numuCCZeroPiSelection::InitializeEvent(AnaEventC& eventC){
  //**************************************************

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  // Create the appropriate EventBox if it does not exist yet
  if (!event.EventBoxes[EventBoxId::kEventBoxTracker])
    event.EventBoxes[EventBoxId::kEventBoxTracker] = new EventBoxTracker();

  // Now fill the groups

  boxUtils::FillTracksWithTPC(  event,  static_cast<SubDetId::SubDetEnum>(GetDetectorFV()) );
  boxUtils::FillTracksWithFGD(  event,  SubDetId::kFGD  ); //in order to calculate all tracker tracks
  boxUtils::FillTracksWithECal( event                   );



  EventBoxTracker::RecObjectGroupEnum group_FGD = static_cast<SubDetId::SubDetEnum>(GetDetectorFV()) == SubDetId::kFGD1 ?  EventBoxTracker::kTracksWithFGD1AndNoTPC :
    EventBoxTracker::kTracksWithFGD2AndNoTPC;
  int nTracks = event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[group_FGD];

  //sort FGD-nonTPC tracks in a given group
  if ( nTracks > 0){
    std::sort(event.EventBoxes[EventBoxId::kEventBoxTracker]->RecObjectsInGroup[group_FGD], 
        event.EventBoxes[EventBoxId::kEventBoxTracker]->RecObjectsInGroup[group_FGD] + nTracks, 
        numu_cczeropi_utils::Compare_FGD_nonTPC_length());
  }


  boxUtils::FillTrajsChargedInTPC(          event             );
  boxUtils::FillTrajsChargedInFGDAndNoTPC(  event, static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));

  boxUtils::FillTrajsChargedHATracker(      event, static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));

  boxUtils::FillTrajsInECal(                event             );


}

//********************************************************************
bool numuCCZeroPiSelection::FillEventSummary(AnaEventC& eventC, Int_t allCutsPassed[]){
  //********************************************************************

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  using namespace zero_pi;


  // Define depending on the detector bit provided

  bool isFGD1 = (_detectorFV == SubDetId::kFGD1);


  //                                                                                  FGD1                                                        FGD2                                                                                    
  if (allCutsPassed[0])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuTpc)       : static_cast<SampleId::SampleEnum>(kFgd2MuTpc);
  if (allCutsPassed[1])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuTpcPTpc)   : static_cast<SampleId::SampleEnum>(kFgd2MuTpcPTpc);
  if (allCutsPassed[2])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuTpcPFgd)   : static_cast<SampleId::SampleEnum>(kFgd2MuTpcPFgd);
  if (allCutsPassed[3])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuFgdPTpc)   : static_cast<SampleId::SampleEnum>(kFgd2MuFgdPTpc);
  if (allCutsPassed[4])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuFgd)       : static_cast<SampleId::SampleEnum>(kFgd2MuFgd);
  if (allCutsPassed[5])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1CC1Pi)       : static_cast<SampleId::SampleEnum>(kFgd2CC1Pi);
  if (allCutsPassed[6])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1CCDIS)       : static_cast<SampleId::SampleEnum>(kFgd2CCDIS);
  if (allCutsPassed[7])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1CCMichel)    : static_cast<SampleId::SampleEnum>(kFgd2CCMichel);
  if (allCutsPassed[8])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1CCECalVeto)  : static_cast<SampleId::SampleEnum>(kFgd2CCECalVeto);
  if (allCutsPassed[9])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuTpcNP)     : static_cast<SampleId::SampleEnum>(kFgd2MuTpcNP);
  if (allCutsPassed[10])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuFgdPTpcNP) : static_cast<SampleId::SampleEnum>(kFgd2MuFgdPTpcNP);
  if (allCutsPassed[11])
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = isFGD1 ? static_cast<SampleId::SampleEnum>(kFgd1MuFgdNP)     : static_cast<SampleId::SampleEnum>(kFgd2MuFgdNP);




  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);

}

// Related to systematics

//**************************************************
Int_t numuCCZeroPiSelection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  // Consider the systematics specific for the analysis
  std::vector<std::vector<Int_t> > groups(SystIdHighland::SystEnumLast_SystIdHighland, std::vector<Int_t>(2, -1));


  // Explicitely set the groups for various systeamtics that need them, 
  // this allows to have a transparent set/control of the systematics by the
  // selection  

  using namespace SystId;
  using namespace anaUtils;

  // --- Systematic         Detectors                                   FGD1                                    FGD2 
  groups[kBFieldDist                  ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kMomScale                    ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kMomResol                    ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kTpcPid                      ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kChargeIDEff                 ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kTpcClusterEff               ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kTpcTrackEff                 ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kMomRangeResol               ] = CreateVectorI(2, EventBoxTracker::kTracksWithFGD1,                 EventBoxTracker::kTracksWithFGD2);
  groups[kToFResol                    ] = CreateVectorI(2, EventBoxTracker::kTracksWithFGD1,                 EventBoxTracker::kTracksWithFGD2);
  groups[kMomBiasFromVertexMigration  ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2); // For the moment mom-range is not modified
  groups[kTpcFgdMatchEff              ] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,           EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kFgdPid                      ] = CreateVectorI(2, EventBoxTracker::kTracksWithFGD1AndNoTPC,         EventBoxTracker::kTracksWithFGD2AndNoTPC);
  groups[kFgdHybridTrackEff           ] = CreateVectorI(2, EventBoxTracker::kTracksWithFGD1AndNoTPC,         EventBoxTracker::kTracksWithFGD2AndNoTPC);
  groups[kECalEMResol                 ] = CreateVectorI(2, EventBoxTracker::kTracksWithECal,                 EventBoxTracker::kTracksWithECal);
  groups[kECalEMScale                 ] = CreateVectorI(2, EventBoxTracker::kTracksWithECal,                 EventBoxTracker::kTracksWithECal);
  groups[kECalTrackEff                ] = CreateVectorI(2, EventBoxTracker::kTracksWithECal,                 EventBoxTracker::kTracksWithECal);
  groups[kECalPID                     ] = CreateVectorI(2, EventBoxTracker::kTracksWithECal,                 EventBoxTracker::kTracksWithECal);
  groups[kFgdECalMatchEff             ] = CreateVectorI(2, EventBoxTracker::kTracksWithFGD1AndTECAL,         EventBoxTracker::kTracksWithFGD2AndTECAL);
  groups[kFgdECalSmrdMatchEff         ] = CreateVectorI(2, EventBoxTracker::kTracksWithFGD1AndTECAL,         EventBoxTracker::kTracksWithFGD2AndTECAL);

  // The systematics not mentioned above will get no groups --> wont be applied
  Int_t ngroups = 0;

  // Check the systematic index is ok
  try {
    groups.at(systId);
  }
  catch (const std::out_of_range& oor) {
    std::cerr << this->Name() << " GetRelevantTrueObjectGroupsForSystematic: syst index beyond limits "<< systId << " Error " << oor.what() << '\n';
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

//**************************************************
Int_t numuCCZeroPiSelection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  // Consider the systematics specific for the analysis: extenstion for highland
  // systematics
  std::vector<std::vector<Int_t> > groups(SystIdHighland::SystEnumLast_SystIdHighland, std::vector<Int_t>(2, -1));


  // Explicitely set the groups for various systeamtics that need them, 
  // this allows to have a transparent set/control of the systematics by the
  // selection  

  using namespace SystId;
  using namespace anaUtils;

  // --- Systematic         Detectors                                   FGD1                                                    FGD2 
  groups[kTpcFgdMatchEff      ] = CreateVectorI(1, EventBoxTracker::kTrueParticlesChargedInTPCorFGDInBunch);
  groups[kTpcTrackEff         ] = CreateVectorI(1, EventBoxTracker::kTrueParticlesChargedInTPCInBunch);
  groups[kFgdHybridTrackEff   ] = CreateVectorI(2, EventBoxTracker::kTrueParticlesChargedInFGD1AndNoTPCInBunch, EventBoxTracker::kTrueParticlesChargedInFGD2AndNoTPCInBunch);
  groups[kECalTrackEff        ] = CreateVectorI(2, EventBoxTracker::kTrueParticlesInECalInBunch,                EventBoxTracker::kTrueParticlesInECalInBunch);

  groups[kFgdECalMatchEff     ] = CreateVectorI(2, EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch,   EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch);
  groups[kFgdECalSmrdMatchEff ] = CreateVectorI(2, EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch,   EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch);



  // The systematics not mentioned above will get no groups
  Int_t ngroups = 0;

  // Check the systematic index is ok
  try {
    groups.at(systId);
  }
  catch (const std::out_of_range& oor) {
    std::cerr << this->Name() << " GetRelevantTrueObjectGroupsForSystematic: syst index beyond limits "<< systId << " Error " << oor.what() << '\n';
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


//**************************************************
bool numuCCZeroPiSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************

  // This is for efficiency-like systematis

  (void)event;
  const AnaBoxCCZeroPi * cczeropi_box = static_cast<const AnaBoxCCZeroPi*>(&box);

  if (!cczeropi_box->MuonCandidate) return false;

  using namespace SystId;
  using namespace SystIdHighland;

  switch (systId){
    // Charge and PID identification 
    case kChargeIDEff:    
      // Efficiencies for TPC tracking
    case kTpcClusterEff:     
    case kTpcTrackEff:
      // TPC matching
    case kTpcFgdMatchEff:
      // FGD reconstruction efficiencies
    case kFgdHybridTrackEff:
      return true;
      break;
      // ME efficiencies
      // Apply when the cut is used
    case kMichelEleEff: 
      // CSs with 1pi and CC-other
      if (branch == 5 || branch == 6){
        return false;
      }

      // pTPC-muFGD when FGD segment is contained
      if  (branch == 3 || branch == 10){
        // If the FGD track is only in FGD then no need to apply ME
        if (anaUtils::TrackUsesOnlyDet(*(cczeropi_box->MuonCandidate), cczeropi_box->DetectorFV))
          return false;
      }
      return true;
      break;

      // Pile-up: tracker
    case kPileUp:
      // Detector mass: normalization
    case kFgdMass:
      // OOFV - need to check whether it is the proper one!
    case kOOFV: 
      // GEANT 4 model
    case kSIPion:
    case kSIProton:
      // Effects from sand-muons: tracker
    case kSandMu:
      return true;
      break;
      // ECal PID and track eff: apply to relevant branches: ECal veto or ECal
      // info usage in muFGD branches (not TPC due vertex), the latter case is
      // treated it tuning the systematic per track 
    case kECalPID:
    case kECalTrackEff:

      // If using veto then apply only for relevant branches
      if (branch == 5 || branch == 6){
        return false;
      }

      if (branch == 4 || branch == 11){
        return true;
      }

      return true;
      break;


    // Only relevant if ECal veto is used and should not be applied 
    case SystId::kECalPhotonPileUp:
      // If using veto then apply only for relevant branches
      if (branch == 5 || branch == 6){
        return false;
      }
      return true;
      break;

      // High-angle matching
    case kFgdECalMatchEff: 
    case kFgdECalSmrdMatchEff:
      // Flux
    case kFluxWeight:
      //  Bwd migration
    case kFgdBwdMigration:
    case kSINeutron:
      return true;
      break;
    default:
      return false;
      break;
  }

  return false;
}

//**************************************************
bool numuCCZeroPiSelection::IsRelevantRecObjectForSystematic(const AnaEventC& event,
    AnaRecObjectC* recObj,
    SystId_h systId,
    Int_t branch) const{
  //**************************************************
  (void)event;
  (void)branch;

  AnaTrackB* track = static_cast<AnaTrackB*>(recObj);

  // True track should always exist
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

//**************************************************
bool numuCCZeroPiSelection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  (void)event;
  (void)branch;

  AnaTrueParticleB* trueTrack = static_cast<AnaTrueParticleB*>(trueObj);

  // HybridTrackEff
  if (systId == SystId::kFgdHybridTrackEff){    
    if (!anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()), trueTrack->Position)) return false;
  }

  return true;
}

//**************************************************
bool numuCCZeroPiSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* trackObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  (void)event;

  AnaTrackB* track = static_cast<AnaTrackB*>(trackObj);

  if (!track) return false;

  const AnaBoxCCZeroPi* cczeropi_box = static_cast<const AnaBoxCCZeroPi*>(&box);

  if (!cczeropi_box->MuonCandidate) 
    return false;

  switch (systId){
    case SystId::kECalPID: 
      // When pi-zero veto is OFF the systematic is applied for the reco object
      // that corresponds to the muon candidate of the topologies CC-0Pi with
      // FGD muon candidate w/o the TPC proton vertex
      if (branch == 4 || branch == 11){
         // If a track enters SMRD then there is no need to apply a cuts since SMRD presence is already a good criteria to select muons
        if (!SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kSMRD)){
          if (cczeropi_box->MuonCandidate->nECALSegments > 0 && track->nECALSegments > 0){
            return cczeropi_box->MuonCandidate->ECALSegments[0] == track->ECALSegments[0];
          }
        }
      }
 
      return true;
      break; 

      // The rest of the systematics go here, tuning to come
    default:
      return true;
      break;
  }

  return true;



}


//**************************************************
bool numuCCZeroPiSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& eventBB, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB); 



  if (!trueObj) return false;

  const AnaBoxCCZeroPi* cczeropi_box = static_cast<const AnaBoxCCZeroPi*>(&box); 

  if (!cczeropi_box->MuonCandidate) return false;
  
    
  AnaTrueParticleB* trueTrack = static_cast<AnaTrueParticleB*>(trueObj);

    
  if (!trueTrack){
    return false;
  }

  
  

  switch (systId){ 
    case SystId::kECalTrackEff:
      // When pi-zero veto is OFF the systematic is applied for the true object
      // that corresponds to the muon candidate of the CC0Pi topologies with
      // FGD muon candidate w/o the TPC proton vertex
        if (branch == 4 || branch == 11){
          if( cczeropi_box->MuonCandidate->nECALSegments > 0 ){
            return cczeropi_box->MuonCandidate->ECALSegments[0]->GetTrueParticle() == trueObj;
          } 
        }
        return false;
      return true;
      break;

    case SystIdHighland::kSINeutron : 
      {
        bool contributes = false;

        // Wether it affects a reco track in FGD1 or FGD2 
        EventBoxTracker* EventBox = static_cast<EventBoxTracker*>((event).EventBoxes[EventBoxId::kEventBoxTracker]);

        EventBoxTracker::RecObjectGroupEnum groupID = static_cast<SubDetId::SubDetEnum>(GetDetectorFV()) == SubDetId::kFGD1 ?
          EventBoxTracker::kTracksWithFGD1 :
          EventBoxTracker::kTracksWithFGD2;

        int nTracks =   EventBox->nRecObjectsInGroup[groupID];

        for (Int_t i=0;i<nTracks; ++i){
          AnaTrackB* track = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[groupID][i]);
          if (!track) continue;

          int gen;
          if (anaUtils::CheckTrueCausesRecoFull(event, *trueTrack, *track, gen)){
            contributes = true;
            break;
          }
        }


        // Check wether it affects a hit in FGD1 or FGD2  

        Int_t ibunch = event.Bunch;

        Float_t selTime = anaUtils::GetND280Bunching().GetBunchCentralTime(event, ibunch);

        Float_t numWidthsReqInSorting = 4; 
        Float_t binBunchWidth = 25.; 
        Float_t binTimeOffsetToBunch = -13.;


        for( Int_t i = 0; i < event.nFgdTimeBins; i++ ){

          AnaFgdTimeBin *FgdTimeBin = static_cast<AnaFgdTimeBin*>(event.FgdTimeBins[i]);

          Float_t binTime = FgdTimeBin->MinTime - binTimeOffsetToBunch;


          // This bunch
          if (fabs(binTime - selTime) > numWidthsReqInSorting * binBunchWidth){
            continue;
          }

#if VERSION_HAS_FGD_HIT_INFO
          
#if VERSION_HAS_FGD_HIT_TRUE_TRAJ_ID

          // Now check individual hits
          for (int j = 0; j < FgdTimeBin->nFgdHits; j++){

            if (!FgdTimeBin->FgdHits[j]){
              continue;
            }

            // now check hits for a given FGD

            bool ifdet =  SubDetId::GetDetectorUsed(FgdTimeBin->FgdHits[j]->Detector, _detectorFV);

            if (!ifdet){
              continue;
            }

            // Now check the contributor
            std::vector<int> gen_vect;
            gen_vect.clear();
            if (anaUtils::CheckTrueCausesHitFull(event, *trueTrack, *(FgdTimeBin->FgdHits[j]), gen_vect)){
              contributes = true;  
            } 

          }
          
#endif
#endif
        }
        return contributes;
      }
      break;

    default:
      return true;
      break;
  }

  // For the rest of the systematic return true
  return true;
}

//********************************************************************
bool zero_pi::FillSummaryAction::Apply(AnaEventC& eventC, ToyBoxB& box) const{
  //********************************************************************

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 

  if(!cczeropi_box->MuonCandidate) return false;

  SampleId::SampleEnum sample = cczeropi_box->DetectorFV == SubDetId::kFGD1 ? SampleId::kFGD1NuMuCC0Pi : SampleId::kFGD2NuMuCC0Pi;

  // Have the muon candidate, so fill lepton candidate summary info
  static_cast<AnaEventSummaryB*>(event.Summary)->LeptonCandidate[sample] = cczeropi_box->MuonCandidate;

  // We have the HM negative and positive candidates now, so can fill the summary information
  for(int i = 0; i < 4; ++i){
    static_cast<AnaEventSummaryB*>(event.Summary)->VertexPosition[sample][i] = cczeropi_box->MuonCandidate->PositionStart[i];
  }
  if(cczeropi_box->MuonCandidate->GetTrueParticle()){
    static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[sample] = cczeropi_box->MuonCandidate->GetTrueParticle()->TrueVertex;
  }

  return true;
}





//Find muon canidate
//**************************************************
bool zero_pi::FindMuonCandidateAction::Apply(AnaEventC& eventC, ToyBoxB& box) const{
  //**************************************************

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  EventBoxTracker::RecObjectGroupEnum group_FGD = cczeropi_box->DetectorFV == SubDetId::kFGD1 ?  EventBoxTracker::kTracksWithFGD1AndNoTPC :
    EventBoxTracker::kTracksWithFGD2AndNoTPC;

  int nTracks = event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[group_FGD];

  //select muon candidate
  if (cczeropi_box->HMNtrack){
    cczeropi_box->MuonCandidate = cczeropi_box->HMNtrack;
  }else if ( nTracks > 0 ){
    cczeropi_box->MuonCandidate = static_cast<AnaTrackB*>(
        event.EventBoxes[EventBoxId::kEventBoxTracker]->RecObjectsInGroup[group_FGD][0]
        ); 
  }

  cczeropi_box->MainTrack = cczeropi_box->MuonCandidate; 

  return cczeropi_box->MainTrack;
}

//**************************************************
bool zero_pi::FindVertexAction::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 

  (void)event;

  // Reset the vertex 
  if (cczeropi_box->Vertex) delete cczeropi_box->Vertex;
  cczeropi_box->Vertex = NULL;

  // Also the true vertex
  cczeropi_box->TrueVertex = NULL;

  AnaTrackB* track = NULL;

  if (cczeropi_box->MuonCandidate && SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kTPC)){
    track = cczeropi_box->MuonCandidate;
  }

  if (!track)
    track = cczeropi_box->HMPtrack;

  if (!track){
    track = cczeropi_box->MuonCandidate;
  }

  BuildVertex(cczeropi_box->Vertex, track);

  cczeropi_box->VertexType = zero_pi::kUnassigned;

  if (cczeropi_box->Vertex){
    cczeropi_box->VertexType = zero_pi::kFGD;

    if (cczeropi_box->Vertex->Particles[0] == cczeropi_box->HMNtrack)
      cczeropi_box->VertexType = zero_pi::kHMN;

    if (cczeropi_box->Vertex->Particles[0] == cczeropi_box->HMPtrack)
      cczeropi_box->VertexType = zero_pi::kHMP;
  }

  // Assign the true vertex to the box (e.g. needed for flux weighting)
  if (cczeropi_box->Vertex)
    cczeropi_box->TrueVertex = cczeropi_box->Vertex->TrueVertex;

  return (bool)(cczeropi_box->Vertex);

}



//**************************************************
bool zero_pi::FindProtonCandidatesAction::Apply(AnaEventC& eventC, ToyBoxB& box) const{
  //**************************************************

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  //should be a vertex
  if(!cczeropi_box->Vertex) return false;  

  EventBoxTracker::RecObjectGroupEnum group_FGD = cczeropi_box->DetectorFV == SubDetId::kFGD1 ?  EventBoxTracker::kTracksWithFGD1AndNoTPC :
    EventBoxTracker::kTracksWithFGD2AndNoTPC;


  //update the cuts
  UpdateParams(cczeropi_box->VertexType, zero_pi::kHMP, cczeropi_box->DetectorFV);

  //TPC candidates,  for the moment consider good quality TPC tracks in FV
  for (int i=0; i < cczeropi_box->nPositiveTPCtracks; i++){

    AnaTrackB* track = cczeropi_box->PositiveTPCtracks[i]; 
    if (!track) continue;

    //0. a check that it is not a muon candidate
    if (track == cczeropi_box->MuonCandidate) continue;

    //1. vertex cut
    if (!cutUtils::CommonVertexCut(*(static_cast<AnaTrackB*>(cczeropi_box->Vertex->Particles[0])), *track, 
          _cutX, _cutY, _cutZ)) continue;

    //2. TPC PID
    if (!zero_pi::TPCProtonPIDCut(*track, _cutPID)) 
      continue;

    // Add candidate
    cczeropi_box->ProtonTPCCandidates[cczeropi_box->nProtonTPCCandidates++] = track;

    if (!cczeropi_box->ProtonCandidate) cczeropi_box->ProtonCandidate = track;

  }


  UpdateParams(cczeropi_box->VertexType, zero_pi::kFGD, cczeropi_box->DetectorFV);

  //FGD candidates
  for (int i=0; i<event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[group_FGD]; i++){
    AnaTrackB* track = static_cast<AnaTrackB*>(event.EventBoxes[EventBoxId::kEventBoxTracker]->RecObjectsInGroup[group_FGD][i]); 
    if (!track) continue;

    //0. a check that it is not a muon candidate
    if (track == cczeropi_box->MuonCandidate) continue;

    //1. should be FGD contained
    if (!anaUtils::TrackUsesOnlyDet(*track, cczeropi_box->DetectorFV)) continue;

    //2. find correct sense with a vertex constrain
    zero_pi::FindCorrectSense(track, cczeropi_box->Vertex);

    //3. vertex cut
    if (!cutUtils::CommonVertexCut(*(static_cast<AnaTrackB*>(cczeropi_box->Vertex->Particles[0])), *track, 
          _cutX, _cutY, _cutZ)) continue;

    //4. FGD PID
    if (!zero_pi::FGDProtonPIDCut(*track, _cutPID)) 
      continue;

    // Add candidate
    cczeropi_box->ProtonFGDCandidates[cczeropi_box->nProtonFGDCandidates++] = track;

    if (!cczeropi_box->ProtonCandidate) cczeropi_box->ProtonCandidate = track;

  }


  return true;
}

//**************************************************
void zero_pi::FindProtonCandidatesAction::UpdateParams(zero_pi::CandidateType vtx_type, zero_pi::CandidateType proton_type, 
    SubDetId::SubDetEnum det) const{
  //**************************************************
  if(det!=SubDetId::kFGD1 &&
      det!=SubDetId::kFGD2)
    return SetDefaultParams();

  if (vtx_type == zero_pi::kUnassigned || proton_type == zero_pi::kUnassigned)
    return SetDefaultParams();

  _cutPID = _cut_proton_PID_TPC;

  if (proton_type == zero_pi::kFGD)
    _cutPID = (det == SubDetId::kFGD1) ? _cut_proton_PID_FGD1 : _cut_proton_PID_FGD2;


  if (vtx_type == zero_pi::kHMN || vtx_type == zero_pi::kHMP){

    if (proton_type == zero_pi::kHMP){
      _cutX = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxTPC_pTPC : _cutX_FGD2_vtxTPC_pTPC;
      _cutY = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxTPC_pTPC : _cutX_FGD2_vtxTPC_pTPC;
      _cutZ = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxTPC_pTPC : _cutX_FGD2_vtxTPC_pTPC;
    }
    else{
      _cutX = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxTPC_pFGD : _cutX_FGD2_vtxTPC_pFGD;
      _cutY = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxTPC_pFGD : _cutX_FGD2_vtxTPC_pFGD;
      _cutZ = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxTPC_pFGD : _cutX_FGD2_vtxTPC_pFGD;
    }
    return;

  }
  // FGD vertex
  else {
    if (proton_type == zero_pi::kFGD){
      _cutX = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxFGD_pFGD : _cutX_FGD2_vtxFGD_pFGD;
      _cutY = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxFGD_pFGD : _cutX_FGD2_vtxFGD_pFGD;
      _cutZ = (det == SubDetId::kFGD1) ? _cutX_FGD1_vtxFGD_pFGD : _cutX_FGD2_vtxFGD_pFGD;
      return;
    }

    return SetDefaultParams();
  }
}


//**************************************************
bool zero_pi::FindMichelElectronsAction::Apply(AnaEventC& eventC, ToyBoxB& box) const{
  //**************************************************

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  // Fill the box only the first time this is used
  EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);
  if (EventBox->FGDMichelElectrons[cczeropi_box->DetectorFV]) return true;

  anaUtils::CreateArray(EventBox->FGDMichelElectrons[cczeropi_box->DetectorFV], NMAXFGDTIMEBINS);
  EventBox->nFGDMichelElectrons[cczeropi_box->DetectorFV] = anaUtils::GetFGDMichelElectrons(event, cczeropi_box->DetectorFV, 
      EventBox->FGDMichelElectrons[cczeropi_box->DetectorFV]);
  anaUtils::ResizeArray(EventBox->FGDMichelElectrons[cczeropi_box->DetectorFV], EventBox->nFGDMichelElectrons[cczeropi_box->DetectorFV],NMAXFGDTIMEBINS);

  return true;
}



//**************************************************
bool zero_pi::MichelElectronCut::Apply(AnaEventC& eventC, ToyBoxB& box) const{
  //**************************************************

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);

  if (!cczeropi_box->MuonCandidate) return false;

  // If the FGD track is only in FGD then no need to apply this cut
  if (anaUtils::TrackUsesOnlyDet(*(cczeropi_box->MuonCandidate), cczeropi_box->DetectorFV))
    return true;

  return EventBox->nFGDMichelElectrons[cczeropi_box->DetectorFV] == 0;
}



//**************************************************
bool zero_pi::MuonProtonTracksCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  int nTracker = zero_pi::GetNTrackerTracks(event);

  return nTracker == 1 + cczeropi_box->nProtonTPCCandidates + cczeropi_box->nProtonFGDCandidates; // only muon + nproton tracks
}

//**************************************************
bool zero_pi::NTrackerTracksCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  (void)box;

  int nTracker = zero_pi::GetNTrackerTracks(event);

  return nTracker == _nCut;  
}

//**************************************************
bool zero_pi::OneNegativeTrackCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;
  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);


  // Exactly one negative track with good quality and in FV
  return cczeropi_box->nNegativeTPCtracks == 1; 
}

//**************************************************
bool zero_pi::MuonCandidate_TPC_VertexCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  return (cczeropi_box->Vertex && cczeropi_box->VertexType == zero_pi::kHMN);
}


//**************************************************
bool zero_pi::HMP_TPC_VertexCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  return (cczeropi_box->Vertex && cczeropi_box->VertexType == zero_pi::kHMP);
}

//**************************************************
bool zero_pi::ProtonCandidate_TPC_VertexCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  if (!cczeropi_box->ProtonCandidate) return false;

  return (cczeropi_box->Vertex && cczeropi_box->VertexType == zero_pi::kHMP && 
      cczeropi_box->ProtonCandidate == cczeropi_box->Vertex->Particles[0]);
}

//Number of proton tracks

//**************************************************
bool zero_pi::NProtonTracksCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  return cczeropi_box->nProtonTPCCandidates + cczeropi_box->nProtonFGDCandidates == _nCut;
}

//**************************************************
bool zero_pi::N_TPC_ProtonTracksCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  return cczeropi_box->nProtonTPCCandidates == _nCut;
}

//**************************************************
bool zero_pi::N_FGD_ProtonTracksCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  return cczeropi_box->nProtonFGDCandidates == _nCut;
}

//**************************************************
bool zero_pi::MultiProtonTracksCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  return cczeropi_box->nProtonTPCCandidates + cczeropi_box->nProtonFGDCandidates > 1;
}

//Proton candidate in FGD
//**************************************************
bool zero_pi::ProtonCandidate_FGD_StoppingCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 

  // Needed to compute the momentum by range

  if(!cczeropi_box->ProtonCandidate) return false;

  // apply it only if the FGD track is contained 
  if ( !anaUtils::TrackUsesOnlyDet(*(cczeropi_box->ProtonCandidate), cczeropi_box->DetectorFV) ) return false;

  //TODO
  return true;
}

//Muon candidate in FGD 

//**************************************************
bool zero_pi::MuonCandidate_FGD_VertexCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  return (cczeropi_box->Vertex && cczeropi_box->VertexType == zero_pi::kFGD && 
      anaUtils::InFiducialVolume(cczeropi_box->DetectorFV, cczeropi_box->Vertex->Position)); 
}

//**************************************************
bool zero_pi::CommonVertexCut_muFGD_pTPC::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 

  if (!cczeropi_box->MuonCandidate || !cczeropi_box->ProtonCandidate) return false;

  if (cczeropi_box->DetectorFV == SubDetId::kFGD1) 
    return cutUtils::CommonVertexCut(*(cczeropi_box->MuonCandidate), *(cczeropi_box->ProtonCandidate), 
        _cutXFGD1, _cutYFGD1, _cutZFGD1);
  else
    return cutUtils::CommonVertexCut(*(cczeropi_box->MuonCandidate), *(cczeropi_box->ProtonCandidate), 
        _cutXFGD2, _cutYFGD2, _cutZFGD2);
}

//**************************************************
bool zero_pi::MuonCandidate_FGD_LongFGDTrackCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 

  if (!cczeropi_box->MuonCandidate) return false;

  Float_t length = 0;

  if(cczeropi_box->MuonCandidate->nFGDSegments>0) 
    length = cczeropi_box->MuonCandidate->FGDSegments[0]->X;

  if (cczeropi_box->DetectorFV == SubDetId::kFGD1)
    return (!anaUtils::TrackUsesOnlyDet(*(cczeropi_box->MuonCandidate), SubDetId::kFGD1) || length>_cutFGD1);

  if (cczeropi_box->DetectorFV == SubDetId::kFGD2)
    return (!anaUtils::TrackUsesOnlyDet(*(cczeropi_box->MuonCandidate), SubDetId::kFGD2) || length>_cutFGD2);

  return false;
}

//**************************************************
bool zero_pi::MuonCandidate_FGD_MuonPIDCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 

  if (!cczeropi_box->MuonCandidate) return false;

  // apply it only if the FGD track is contained 
  if (!anaUtils::TrackUsesOnlyDet(*(cczeropi_box->MuonCandidate), cczeropi_box->DetectorFV)) return true;

  if (cczeropi_box->DetectorFV == SubDetId::kFGD1)
    return zero_pi::FGDMuonPIDCut(*(cczeropi_box->MuonCandidate), _cutFGD1);

  if (cczeropi_box->DetectorFV == SubDetId::kFGD2)
    return zero_pi::FGDMuonPIDCut(*(cczeropi_box->MuonCandidate), _cutFGD2);

  return false;
}

//**************************************************
bool zero_pi::MuonCandidate_FGD_StoppingCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************
  // Needed to compute the momentum by range

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 

  if (!cczeropi_box->MuonCandidate) return false;

  // if the FGD track is only in FGD it should be contained
  if (anaUtils::TrackUsesOnlyDet(*(cczeropi_box->MuonCandidate), cczeropi_box->DetectorFV))
    //TODO!
    return true;

  // if the FGD track has other detectors it should end in those (have end point in reduced FV)
  if (SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kTECAL) && numu_cczeropi_utils::TrackEndsInBarrelECalFV(*(cczeropi_box->MuonCandidate)))
    return true;

  if (SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kSMRD) && numu_cczeropi_utils::TrackEndsInSMRDFV(*(cczeropi_box->MuonCandidate)))
    return true;

  return false;
}


//**************************************************
bool zero_pi::FindCorrectMuonSenseAction::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi * cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box); 
  if (!cczeropi_box->MuonCandidate) return false;

  // it must reverse the track only if it is a FGD track (no TPC segments)
  if (anaUtils::TrackUsesDet(*(cczeropi_box->MuonCandidate), SubDetId::kTPC)) return false;

  zero_pi::FindCorrectSense(cczeropi_box->MuonCandidate, cczeropi_box->Vertex);
  return true;
}


//**************************************************
bool zero_pi::MuonCandidate_FGD_ToFCut::Apply(AnaEventC& event, ToyBoxB& box ) const{
  //**************************************************

  (void) event;
  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  // Do not apply if needed
  if (!_useToFInfo)
    return true;

  if ( !cczeropi_box->MuonCandidate || SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kTPC) ) return false;

  AnaTrackB* track = cczeropi_box->MuonCandidate;

  if ( cczeropi_box->DetectorFV == SubDetId::kFGD1 && track->ToF.Flag_ECal_FGD1 ){
    return track->ToF.ECal_FGD1 > _HA_ECal_FGD1_ToFCut;	
  }

  if ( cczeropi_box->DetectorFV == SubDetId::kFGD2 && track->ToF.Flag_ECal_FGD2 ){
    return track->ToF.ECal_FGD2 > _HA_ECal_FGD2_ToFCut;	
  }

  if ( cczeropi_box->DetectorFV == SubDetId::kFGD2 && track->ToF.Flag_ECal_FGD2 ){
    return track->ToF.DSECal_FGD2 > _HA_ECal_FGD2_ToFCut; 
  }

  return false;
}

//**************************************************
bool zero_pi::MuonCandidate_FGD_ECalPIDCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void) event;

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  if( !cczeropi_box->MuonCandidate || SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kTPC)) return false;

  // if a track enters SMRD then there is no need to apply a cuts since SMRD presence is already a good criteria to select muons
  if (SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kSMRD)) return true;

  if( cczeropi_box->MuonCandidate->nECALSegments > 0 ){
    return cczeropi_box->MuonCandidate->ECALSegments[0]->PIDMipEm < _HA_ECalPID_cut;
  } 

  return false;

}

//**************************************************
bool zero_pi::MuonCandidate_FGD_ECalPID2Cut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void) event;

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);


  if (!cczeropi_box->MuonCandidate || SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kTPC)) return false;

  // if a track enters SMRD then there is no need to apply a cuts since SMRD presence is already a good criteria to select muons
  if (SubDetId::GetDetectorUsed(cczeropi_box->MuonCandidate->Detector, SubDetId::kSMRD)) return true;


  if ( cczeropi_box->MuonCandidate->nECALSegments > 0 ){
    AnaECALParticle* ECalSeg = static_cast<AnaECALParticle*>( cczeropi_box->MuonCandidate->ECALSegments[0] );
    return ECalSeg->Length / ECalSeg->EMEnergy > _HA_ECalPID2_cut;
  } 

  return false;

}

// Cuts and actions related to control samples
//**************************************************
bool zero_pi::HMP_TPC_PionPIDCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //**************************************************

  (void)event;

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  if (!cczeropi_box->HMPtrack) return false;
  AnaTrackB* track = cczeropi_box->HMPtrack;

  Float_t PIDLikelihood[4];
  anaUtils::GetPIDLikelihood(*track, PIDLikelihood);


  if (((PIDLikelihood[0] + PIDLikelihood[3])/(1 - PIDLikelihood[2]) > _mip_lhood_cut ||
        track->Momentum > _min_mom_cut) && (PIDLikelihood[3] > _pion_lhood_cut)){
    return true;
  }

  return false;

}

//**************************************************
bool zero_pi::MultiTpcTracksCut::Apply(AnaEventC& eventC, ToyBoxB& box) const{
  //**************************************************
  //more than two tracks in TPC and FV!

  AnaEventB& event = static_cast<AnaEventB&>(eventC);

  AnaBoxCCZeroPi* cczeropi_box = static_cast<AnaBoxCCZeroPi*>(&box);

  int nTracks = 0;

  switch (cczeropi_box->DetectorFV){ 
    case SubDetId::kFGD1:
      nTracks = event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD1FV]; 
      break;
    case SubDetId::kFGD2:
      nTracks = event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD2FV]; 
      break;
    default:
      break;
  }

  return (nTracks>2);
}

//**************************************************
bool zero_pi::FGDMuonPIDCut(const AnaTrackB& track, Float_t cut){
  //**************************************************

  if (track.nFGDSegments == 0) return false;

  return track.FGDSegments[0]->Pullmu > cut;
}

//**************************************************
bool zero_pi::FGDProtonPIDCut(const AnaTrackB& track, Float_t cut){
  //**************************************************

  if (track.nFGDSegments == 0) return false;

  return track.FGDSegments[0]->Pullp > cut;
}

//**************************************************
bool zero_pi::TPCProtonPIDCut(const AnaTrackB& track, Float_t cut){
  //**************************************************

  return anaUtils::GetPIDLikelihood(track, 2) > cut;
}

//********************************************************************
void zero_pi::FindCorrectSense(AnaTrackB* track, AnaVertexB* vertex) {
  //********************************************************************

  if (!track) return;
  if (!vertex) return;

  AnaTrack* ctrack = static_cast<AnaTrack*>(track);

  Float_t distStart = anaUtils::GetSeparationSquared(track->PositionStart, vertex->Position);
  Float_t distEnd   = anaUtils::GetSeparationSquared(track->PositionEnd, vertex->Position);

  if (distEnd < distStart)
    ctrack->Flip();
}

//********************************************************************
void zero_pi::BuildVertex(AnaVertexB*& vertex, AnaTrackB* track) {
  //********************************************************************
  // reset the vertex 
  if (vertex) delete vertex;
  vertex = NULL;

  if (!track) return;

  vertex = new AnaVertexB();
  anaUtils::CreateArray(vertex->Particles, 1);

  vertex->nParticles = 0;
  vertex->Particles[vertex->nParticles++] = track;

  for(int i = 0; i < 4; ++i){
    vertex->Position[i] = track->PositionStart[i];
  }
  if ( track->GetTrueParticle() ) 
    vertex->TrueVertex = track->GetTrueParticle()->TrueVertex;
}

//********************************************************************
int zero_pi::GetNTrackerTracks(const AnaEventC& eventC) {
  //********************************************************************
  const AnaEventB& event = static_cast< const AnaEventB&>(eventC);

  //FGD tracks
  int nFGD = event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC] +
    event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC];

  int nTracker = event.EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPC] + nFGD;

  return nTracker;
}

//********************************************************************
bool zero_pi::TrackLeavesTracker(const AnaTrackB& track) {
  //********************************************************************
  if (anaUtils::InDetVolume(SubDetId::kTPC, track.PositionEnd)){
    return true;
  }

  if (anaUtils::InDetVolume(SubDetId::kFGD1, track.PositionEnd)){
    // Want only X and Y
    Float_t pos_tmp[3];
    pos_tmp[0] = track.PositionEnd[0];
    pos_tmp[1] = track.PositionEnd[1];
    pos_tmp[2] = 200;

    if (!anaUtils::InDetVolume(SubDetId::kFGD1, pos_tmp)){
      return true;
    }
  }

  if (anaUtils::InDetVolume(SubDetId::kFGD2, track.PositionEnd)){
    // Want only X and Y
    Float_t pos_tmp[3];
    pos_tmp[0] = track.PositionEnd[0];
    pos_tmp[1] = track.PositionEnd[1];
    pos_tmp[2] = 1600;

    if (!anaUtils::InDetVolume(SubDetId::kFGD2, pos_tmp)){
      return true;
    }
  }

  return false;  

}


//********************************************************************
const multipart::MultiParticleBox& zero_pi::GetPionBox(const ToyBoxB& box){
  //********************************************************************
  const AnaBoxCCZeroPi& cczeropibox = static_cast<const AnaBoxCCZeroPi&>(box);
  return cczeropibox.pionBox;    
}
