#include "tutorialSelection.hxx"
#include "baseSelection.hxx"
#include "CutUtils.hxx"
#include "SubDetId.hxx"
#include "EventBoxUtils.hxx"
#include "trackerSelectionUtils.hxx"
#include "tutorialSystId.hxx"


using namespace tutorial;

//********************************************************************
tutorialSelection::tutorialSelection(bool forceBreak): SelectionBase(forceBreak,EventBoxId::kEventBoxTracker) {
//********************************************************************

}

//********************************************************************
void tutorialSelection::DefineDetectorFV(){
//********************************************************************

  // Set the detector Fiducial Volume in which the selection is applied. This is now a mandatory method
  SetDetectorFV(SubDetId::kFGD1);
}

//********************************************************************
void tutorialSelection::DefineSteps(){
//********************************************************************

  // Cuts must be added in the right order
  // last "true" means the step sequence is broken if cut is not passed (default is "false")
  AddStep(StepBase::kCut,    "event quality",      new EventQualityCut(),           true);
  AddStep(StepBase::kCut,    "> 0 tracks ",        new TotalMultiplicityCut(),      true);  
  AddStep(StepBase::kAction, "find leading tracks",new FindLeadingTracksAction());  
  AddStep(StepBase::kAction, "find vertex",        new FindVertexAction());  
  AddStep(StepBase::kAction, "fill_summary",       new FillSummaryAction_tutorial());
  AddStep(StepBase::kCut,    "quality+fiducial",   new TrackQualityFiducialCut(),   true);  
  AddStep(StepBase::kAction, "find veto track",    new FindVetoTrackAction());
  AddStep(StepBase::kCut,    "veto",               new ExternalVetoCut());
  AddStep(StepBase::kAction, "find oofv track",    new FindOOFVTrackAction());
  AddStep(StepBase::kCut,    "External FGD1",      new ExternalFGD1lastlayersCut());
  AddStep(StepBase::kCut,    "muon PID",           new MuonPIDCut());
  
  // This is mandatory. An alias should be given to each of the branches
  SetBranchAlias(0,"trunk");
  
  // By default the preselection correspond to cuts 0-2. 
  // It means that if any of the three first cuts (0,1,2) is not passed 
  // the loop over toys will be broken ===> A single toy will be run
  SetPreSelectionAccumLevel(2);
}

//********************************************************************
bool tutorialSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
//********************************************************************

  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC;
  }
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}

//**************************************************
bool TotalMultiplicityCut::Apply(AnaEventC& event, ToyBoxB& box) const{
//**************************************************

  (void)box; // This is just to avoid a warning (box not used !!!)

  // Check we have at least one reconstructed track in the TPC
  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];
  return (EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPC]>0);
}

//**************************************************
bool TrackQualityFiducialCut::Apply(AnaEventC& event, ToyBoxB& boxB) const{
//**************************************************

  (void)event;  // This is just to avoid a warning (event not used !!!)

  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);

  return (box.Vertex);
}

//**************************************************
bool MuonPIDCut::Apply(AnaEventC& event, ToyBoxB& boxB) const{
//**************************************************

  (void)event;  // This is just to avoid a warning (event not used !!!)
  
  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  if (!box.MainTrack) return false;
  if (box.MainTrack->Momentum < 0.) return false;
  return cutUtils::MuonPIDCut(*(box.MainTrack));
}

//********************************************************************
bool ExternalVetoCut::Apply(AnaEventC& event, ToyBoxB& boxB) const{
//********************************************************************

  (void)event;  // This is just to avoid a warning (event not used !!!)
  
  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  if (!box.MainTrack) return false;
  return cutUtils::ExternalVetoCut(*(box.MainTrack),box.VetoTrack);
}

//********************************************************************
bool ExternalFGD1lastlayersCut::Apply(AnaEventC& event, ToyBoxB& boxB) const{
//********************************************************************

  (void)event;  // This is just to avoid a warning (event not used !!!)
  
  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  /// Reject external background from the last 2 layers of FGD1
  if (!box.MainTrack) return false;  
  if (!box.OOFVtrack) return true;
  return (box.MainTrack->PositionStart[2]<425.);
}

//**************************************************
bool FindVertexAction::Apply(AnaEventC& event, ToyBoxB& boxB) const{
//**************************************************

  (void)event;  // This is just to avoid a warning (event not used !!!)
  
  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  // reset the vertex 
  box.Vertex = NULL;
  
  if (!box.MainTrack) return false;
  
  box.Vertex = new AnaVertexB();
  anaUtils::CreateArray(box.Vertex->Particles, 1);
  
  box.Vertex->nParticles = 0;
  box.Vertex->Particles[box.Vertex->nParticles++] = box.MainTrack;
  
  for(int i = 0; i < 4; ++i){
    box.Vertex->Position[i] = box.MainTrack->PositionStart[i];
  }
  if(  box.MainTrack->GetTrueParticle() ) 
    box.Vertex->TrueVertex = box.MainTrack->GetTrueParticle()->TrueVertex;
  return true;
}

//********************************************************************
bool FillSummaryAction_tutorial::Apply(AnaEventC& eventC, ToyBoxB& boxB) const{
//********************************************************************

  AnaEventB& event = *static_cast<AnaEventB*>(&eventC); 
  
  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  if(!box.HMNtrack) return 1;
  
  static_cast<AnaEventSummaryB*>(event.Summary)->LeptonCandidate[SampleId::kFGD1NuMuCC] = box.HMNtrack;
  for(int i = 0; i < 4; ++i){
    static_cast<AnaEventSummaryB*>(event.Summary)->VertexPosition[SampleId::kFGD1NuMuCC][i] = box.HMNtrack->PositionStart[i];
  }
  if(box.HMNtrack->GetTrueParticle()) static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[SampleId::kFGD1NuMuCC] = box.HMNtrack->GetTrueParticle()->TrueVertex;
  
  return true;
}

//**************************************************
bool FindLeadingTracksAction::Apply(AnaEventC& eventC, ToyBoxB& boxB) const{
//**************************************************

  // Cast the event
  AnaEventB& event = *static_cast<AnaEventB*>(&eventC); 
  
  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  // Find leading tracks with good quality and only in FGD FV
  trackerSelUtils::FindLeadingTracks(event,box);
  
  // For this selection the main track is the HMN track
  box.MainTrack = box.HMNtrack;
  return true;
}

//**************************************************
bool FindVetoTrackAction::Apply(AnaEventC& eventC, ToyBoxB& boxB) const{
//**************************************************

  // Cast the event
  AnaEventB& event = *static_cast<AnaEventB*>(&eventC); 
  
  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  box.VetoTrack = cutUtils::FindVetoTrack(event, *(box.MainTrack));  
  return true;
}

//**************************************************
bool FindOOFVTrackAction::Apply(AnaEventC& eventC, ToyBoxB& boxB) const{
//**************************************************

  // Cast the event
  AnaEventB& event = *static_cast<AnaEventB*>(&eventC); 

  // cast the box to the appropriate type
  ToyBoxTracker& box = *static_cast<ToyBoxTracker*>(&boxB);
  
  box.OOFVtrack = cutUtils::FindFGDOOFVtrack(event, *(box.MainTrack), static_cast<SubDetId::SubDetEnum>(box.DetectorFV));
  return true;
}

//**************************************************
void tutorialSelection::InitializeEvent(AnaEventC& eventC){
//**************************************************

  // Cast the event
  AnaEventB& event = *static_cast<AnaEventB*>(&eventC); 

  // Create the appropriate EventBox if it does not exist yet
  if (!event.EventBoxes[EventBoxId::kEventBoxTracker])
    event.EventBoxes[EventBoxId::kEventBoxTracker] = new EventBoxTracker();

  // Fill all objects needed by the selection in the event box
  boxUtils::FillTracksWithTPC(event,             static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));
  boxUtils::FillTracksWithFGD(event,             static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));
  boxUtils::FillTrajsChargedInTPC(event);
  boxUtils::FillTrajsChargedInFGDAndNoTPC(event, static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));
}


//**************************************************
Int_t tutorialSelection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
//**************************************************

  std::vector<std::vector<Int_t> > groups(tutorialSystId::tutorialSystEnumLast_SystId, std::vector<Int_t>(2, -1));
  groups.resize(tutorialSystId::tutorialSystEnumLast_SystId);
   
  
  // Explicitely set the groups for various systeamtics that need them, 
  // this allows to have a transparent set/control of the systematics by the
  // selection  

  using namespace tutorialSystId;
  using namespace anaUtils;
  // --- Systematic         Detectors                                   FGD1                                    FGD2 
  groups[kTutorialVariation] = CreateVectorI(2, EventBoxTracker::kTracksWithTPCInFGD1FV,  EventBoxTracker::kTracksWithTPCInFGD2FV );
  
  
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
  // No branches
  (void)branch;
  SubDetId_h det = GetDetectorFV();
  
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
bool tutorialSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
//**************************************************

  (void)event;
  (void)branch;
  (void)box;
  
  // Direct list of (Efficiency/Weight-like) systematics that a relevant for the selection 
  switch (systId){
    // Fall through the relevant ones - our e.g. syst and also flux
    case tutorialSystId::kTutorialWeight:
    // Flux
    case SystId::kFluxWeight:
      return true;
      break;
    default:
     return false;
     break;
  } 
  return false;
}





