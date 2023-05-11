#include "numuCCMultiPiPhotonSelection.hxx"
#include "SystematicTuning.hxx"


/// \anchor numuCCMultiPiPhotonSelection_DefineSteps
//*******************************************************************************
void numuCCMultiPiPhotonSelection::DefineSteps(){
  //*******************************************************************************

  // Copy all steps from the numuCCSelection
  CopySteps(_numuCCSelection);

  AddStep(StepBase::kAction, "find_pions",           new FindPionsAction());
  AddStep(StepBase::kAction, "find_protons",         new FindProtonsAction());

  // Update pion and proton iso momentum vars to the vertex

  AddStep(StepBase::kAction, "set_vertex_to_box",                 new SetVertexToBoxAction());
  AddStep(StepBase::kAction, "fill_iso_fgd_proton_mom_to_vertex", new FillFgdIsoProtonsKinVertexAction());
  AddStep(StepBase::kAction, "find_iso_fgd_pion_mom_to_vertex",   new FillFgdIsoPionsKinVertexAction());


  // numuCCMultiPiPhoton Cuts and Actions
  AddStep(StepBase::kAction, "find_ecal_photons",   new FindECalPhotonsAction());

  AddStep(StepBase::kAction, "fill_summary_multiPiPhoton", new FillSummaryAction_numuCCMultiPiPhoton());

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
  AddStep(1,1, StepBase::kCut, "CC-1pi",   new OnePionCut(true)); // positive pion

  // Cuts for CCOther
  AddStep(1,2, StepBase::kCut, "CC-Other", new OthersCut());

  //Branch names
  SetBranchAlias(0, "CCPhoton", 0);
  SetBranchAlias(1, "CC0pi"   , 1,0);
  SetBranchAlias(2, "CC1pi"   , 1,1);
  SetBranchAlias(3, "CCOther" , 1,2);

}


//********************************************************************
bool numuCCMultiPiPhotonSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

  //CCPhoton
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCPhoton;
  }
  //CC0pi
  else if (allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiNoPhoton;
  }
  //CC1pi
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiNoPhoton;
  }
  //CCOther
  else if (allCutsPassed[3]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOtherNoPhoton;
  }

  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}

//*********************************************************************
bool FillSummaryAction_numuCCMultiPiPhoton::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 


  if (!box.HMNtrack) return true;
  
  SampleId::SampleEnum SamplesUsed[4] = {
    SampleId::kFGD1NuMuCCPhoton, 
    SampleId::kFGD1NuMuCC0PiNoPhoton,  
    SampleId::kFGD1NuMuCC1PiNoPhoton,  
    SampleId::kFGD1NuMuCCOtherNoPhoton
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

//*********************************************************************
bool PhotonCut::Apply(AnaEventC& event, ToyBoxB& box) const{
  //********************************************************************

  (void)event;

  ToyBoxCCMultiPi* ccmultipibox = static_cast<ToyBoxCCMultiPi*>(&box);

  // ECal object passes EmHip and layer cuts
  if (ccmultipibox->pionBox.nECalPhotons > 0) return true;

  // pi0 present doesn't lead to ECalPhoton
  if (ccmultipibox->pionBox.nOtherPions != ccmultipibox->pionBox.nNegPions) return true;

  return false;
}

//*********************************************************************
bool numuCCMultiPiPhotonSelection::IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //*********************************************************************

  // If does not satisfy multi-pi - return false
  if (!numuCCMultiPiSelection::IsRelevantTrueObjectForSystematic(event, trueObj, systId, branch)){
    return false;
  }

  AnaTrueParticleB* truePart=static_cast<AnaTrueParticleB*>(trueObj);

  // TPC-ECal Matching
  if(systId == SystId::kTpcECalMatchEff){
    if(!anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()), truePart->Position)) return false;
  }

  return true;
}

//**************************************************
bool numuCCMultiPiPhotonSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
  //**************************************************

  if (!track) return false;

  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true;

  // all CC inclusive cases
  // This will also take care of the "main" track
  if (_numuCCSelection.IsRelevantSystematic (event, box, systId, branch) &&
      _numuCCSelection.IsRelevantRecObjectForSystematicInToy(event,box,track,systId,branch)) return true;

  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);


  switch (systId){
    // Fall back through the relevant ones
    // TPC reco
    case SystId::kChargeIDEff:
      // TPC matching
    case SystId::kTpcFgdMatchEff:

      // Use the APPLY_SYST_FINE_TUNING concept as well,  since we worry about the "main" track that defines the topology
      if (branch == 2){
        // For CC1pi also the positive Pion in the TPC matters
        if (ccmultipibox->pionBox.nPositivePionTPCtracks==1 && track==ccmultipibox->pionBox.PositivePionTPCtracks[0]) return true;
      }
      else if (branch == 0 || branch == 3){
        // For CCPhoton and CCOther consider the negative pion when there are no other pions
        if (ccmultipibox->pionBox.nNegativePionTPCtracks==1 && track==ccmultipibox->pionBox.NegativePionTPCtracks[0] &&
            ccmultipibox->pionBox.nOtherPions==1 && ccmultipibox->pionBox.nPosPions == 0) return true;

      }
      // Failed above +
      // CC0pi explicit false (should have been covered by numuCC if tuning is ON)
      return false;
      break;
    case SystId::kECalEmHipPID:
      {

        EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);

        AnaTrackB* trackB = static_cast<AnaTrackB*>(track); // reconstructed track

        int nClose = 0;
        int nPass  = 0;

        for (unsigned int i = 0; i < EventBox->nRecObjectsInGroup[EventBoxTracker::kIsoTracksInECal]; i++){
          AnaTrackB* ptrack = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[EventBoxTracker::kIsoTracksInECal][i]);
          AnaECALParticleB* pECAL = static_cast<AnaECALParticleB*>(ptrack->ECALSegments[0]);
          if(pECAL->PIDEmHip > -0.25 && pECAL->PIDEmHip < 0.35) nClose++; // range including 3.9% (largest uncertainty) of objects above and below cut value
          if(pECAL->PIDEmHip < -0.25) nPass++; // objects with emhip much lower than cut value
        }

        if(!nClose) return false; // no objects with emhip close to cut value
        if(nPass)   return false; // at least one object that passes the cut by large margin

        for (unsigned int i = 0; i < EventBox->nRecObjectsInGroup[EventBoxTracker::kIsoTracksInECal]; i++){
          AnaTrackB* ptrack = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[EventBoxTracker::kIsoTracksInECal][i]);
          AnaECALParticleB* pECAL = static_cast<AnaECALParticleB*>(ptrack->ECALSegments[0]);
          if(pECAL->PIDEmHip < -0.25 || pECAL->PIDEmHip > 0.35) continue; // only apply to objects with emhip close to cut
          if (trackB == ptrack) return true;
        }

        return false;
        break; 
      }
    case SystId::kECalPhotonPileUp:
      {
        EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);

        for (unsigned int i = 0; i < EventBox->nRecObjectsInGroup[EventBoxTracker::kIsoTracksInECal]; i++){
	AnaTrackB* ptrack = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[EventBoxTracker::kIsoTracksInECal][i]);
	AnaECALParticleB* pECAL = static_cast<AnaECALParticleB*>(ptrack->ECALSegments[0]);
	if(pECAL) return true; // apply if there is an isoECal object
        }

        return false;
        break;
      }
    case SystId::kTpcECalMatchEff:
      {
        EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);
        
        if(!EventBox->nRecObjectsInGroup[EventBoxTracker::kIsoTracksInECal]) return true; // apply if there is no isoECal object
        
        return false;
        break;
      }
      // The rest of the systematics go here, tuning to come
    default:
      return true;
      break;
  }

  return true;
}


//**************************************************
bool numuCCMultiPiPhotonSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
  //**************************************************

  const ToyBoxCCMultiPi* ccmultipibox = static_cast<const ToyBoxCCMultiPi*>(&box);

  AnaTrueParticleB* trueTrack = static_cast<AnaTrueParticleB*>(trueObj);
  if (!trueTrack) return false;

  // Apply to all objects,  not fine-tuning
  if (!systTuning::APPLY_SYST_FINE_TUNING) return true;

  // All CC inclusive cases
  // MAIN track mode is taken into account there
  if (_numuCCSelection.IsRelevantSystematic (event, box, systId, branch) &&
      _numuCCSelection.IsRelevantTrueObjectForSystematicInToy(event,box,trueTrack,systId,branch)) return true;

  switch (systId){
    case SystId::kTpcTrackEff:

      // Don't consider pions when there are many TPC ones (a conservative check)
      // Cases in which we must loose two or more pions are excluded (0.01*0.01 probability)
      if (ccmultipibox->pionBox.nNegativePionTPCtracks + ccmultipibox->pionBox.nPositivePionTPCtracks > 2 ||
          ccmultipibox->pionBox.nNegativePionTPCtracks > 1) return false;

      // If the are few TPC pions consider them, muons and electrons
      if (abs(trueTrack->PDG)==211 || abs(trueTrack->PDG)==13 || abs(trueTrack->PDG)==11) return true;

      return false;
      break;

      // SI
    case SystId::kSIPion:

      // No Pion SI systematic when there are many pions
      if (ccmultipibox->pionBox.nOtherPions > 1 || ccmultipibox->pionBox.nPosPions > 2 ) return false;
      return true;
      break;

      // Contributors for relevant objects for proton SI
    case SystId::kSIProton:

      // Main track is done by numuCC
      // If there are  many pions, i.e. topology cannot change, then do not use
      // the systematic
      if (ccmultipibox->pionBox.nOtherPions >1 || ccmultipibox->pionBox.nPosPions > 2 ) return false;
      // Otherwise check that a pion contributes to any of the objects in the
      // box

      return cutUtils::numuCCTrkMultiPi::CheckTrueCausesBoxSimple(*trueTrack, ccmultipibox->pionBox);
      break;

    case SystId::kFgdHybridTrackEff:
      // True track should start in the FGD FV of interest
      // Probably can improve more by requiring that a track corresponds to the
      // selected true vertex
      return anaUtils::InFiducialVolume(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()),
          trueTrack->Position);
      break;

    case SystId::kECalTrackEff:
      // Interested in true objects in the ECal:
      if (!anaUtils::InFiducialVolume(SubDetId::kTECAL,trueTrack->Position) && 
	!anaUtils::InFiducialVolume(SubDetId::kDSECAL,trueTrack->Position)) return false;

      // Only one ECal Photon present and is what defines the CCPhoton topology
      if (ccmultipibox->pionBox.nECalPhotons == 1 && ccmultipibox->pionBox.nOtherPions == ccmultipibox->pionBox.nNegPions){

        // check the true particle produced the shower
        AnaTrackB* photon = ccmultipibox->pionBox.ECalPhotons[0];
        if(photon->GetTrueParticle() && trueTrack->ID == photon->GetTrueParticle()->ID) return true;
        if(photon->GetTrueParticle() && trueTrack->ID == photon->GetTrueParticle()->ParentID) return true;
        if(photon->GetTrueParticle() && trueTrack->ID == photon->GetTrueParticle()->GParentID) return true;
        if(photon->GetTrueParticle() && trueTrack->ID == photon->GetTrueParticle()->PrimaryID) return true;

      }

      // No ECal Photons or TPC pi0s reconstructed, but there is a true ECal Photon
      if (ccmultipibox->pionBox.nECalPhotons == 0 && ccmultipibox->pionBox.nOtherPions == ccmultipibox->pionBox.nNegPions){

        // Check if there is a reconstructed ECal object from this true particle
        // If there is, don't apply the systematic
        EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);
        for(int i = 0; i < EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithECal]; i++ ) {
	AnaTrackB *ptrack = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithECal][i]);

	if(ptrack->GetTrueParticle() && trueTrack->ID == ptrack->GetTrueParticle()->ID) return false;
	if(ptrack->GetTrueParticle() && trueTrack->ID == ptrack->GetTrueParticle()->ParentID) return false;
	if(ptrack->GetTrueParticle() && trueTrack->ID == ptrack->GetTrueParticle()->GParentID) return false;
	if(ptrack->GetTrueParticle() && trueTrack->ID == ptrack->GetTrueParticle()->PrimaryID) return false;
        }

        // only consider EM particles
        if(trueTrack->PDG != 22 && trueTrack->PDG != 11 && trueTrack->PDG != -11) return false;

        // require minimum momentum on true track
        if(trueTrack->Momentum<30) return false;

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

//**************************************************
bool numuCCMultiPiPhotonSelection::IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const{
  //**************************************************

  (void)event;
  (void)box;
  (void)branch;

  switch (systId){ 
    // TPC reco
    case SystId::kChargeIDEff:
    case SystId::kTpcClusterEff:
    case SystId::kTpcTrackEff:
      // FGD
    case SystId::kFgdHybridTrackEff:
    case SystId::kMichelEleEff:
      // TPC matching
    case SystId::kTpcFgdMatchEff:
      // Normalization
    case SystId::kPileUp:
    case SystId::kFgdMass:
    case SystId::kOOFV:
    case SystId::kSandMu:
      // Flux
    case SystId::kFluxWeight:
      // SI
    case SystId::kSIPion:
    case SystId::kSIProton:
      // ECal photons --> ECal-tracker matching should be added as
      // well: ToDo
    case SystId::kECalEmHipPID:
    case SystId::kECalTrackEff:
    case SystId::kECalPhotonPileUp:
    case SystId::kTpcECalMatchEff:
      return true;
      break;
    default:
      return false;
      break;
  }

  return false;
}

//**************************************************
Int_t numuCCMultiPiPhotonSelection::GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************
  Int_t ngroups = numuCCMultiPiSelection::GetRelevantRecObjectGroupsForSystematic(systId, IDs, branch);
  if (ngroups) return ngroups;

  // Consider the systematics specific for the analysis
  std::vector<std::vector<Int_t> > groups(SystId::SystEnumLast_SystId, std::vector<Int_t>(2, -1));


  // Explicitely set the groups for various systeamtics that need them,
  // this allows to have a transparent set/control of the systematics by the
  // selection

  using namespace SystId;

  // --- Systematic         Detectors                                   FGD1                                    FGD2
  groups[kECalEmHipPID      ] =  anaUtils::CreateVectorI(2, EventBoxTracker::kTracksWithECal,          EventBoxTracker::kTracksWithECal);
  groups[kTpcECalMatchEff   ] =  anaUtils::CreateVectorI(2, EventBoxTracker::kTracksWithTPCAndFGD1,    EventBoxTracker::kTracksWithTPCAndFGD2);
  groups[kECalTrackEff      ] =  anaUtils::CreateVectorI(2, EventBoxTracker::kTracksWithECal,          EventBoxTracker::kTracksWithECal);

  // The systematics not mentioned above will get no groups
  // Check the systematic index is ok
  try {
    groups.at(systId);
  }
  catch (const std::out_of_range& oor) {
    std::cerr << this->Name() << " GetRelevantTrueObjectGroupsForSystematic: syst index beyond limits "<< systId << " Error " << oor.what() << '\n';
    exit(1);
  }

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
Int_t numuCCMultiPiPhotonSelection::GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const{
  //**************************************************

  Int_t ngroups = numuCCMultiPiSelection::GetRelevantTrueObjectGroupsForSystematic(systId, IDs, branch);
  
  if (ngroups) return ngroups;

  std::vector<std::vector<Int_t> > groups(SystId::SystEnumLast_SystId, std::vector<Int_t>(1, -1));

  // Explicitely set the groups for various systeamtics that need them,
  // this allows to have a transparent set/control of the systematics by the
  // selection

  using namespace SystId;
  // --- Systematic         Detectors                                   FGD
  groups[ kTpcECalMatchEff  ] =  anaUtils::CreateVectorI(1, EventBoxTracker::kTrueParticlesChargedInTPCInBunch);
  //  groups[ kECalTrackEff     ] =  anaUtils::CreateVectorI(1, EventBoxTracker::kTrueParticlesChargedInTPCInBunch);
  groups[kECalTrackEff      ] =  anaUtils::CreateVectorI(1, EventBoxTracker::kTrueParticlesInECalInBunch);
  // The systematics not mentioned above will get no groups
  
  // Check the systematic index is ok
  try {
    groups.at(systId);
  }
  catch (const std::out_of_range& oor) {
    std::cerr << this->Name() << " GetRelevantTrueObjectGroupsForSystematic: syst index beyond limits "<< systId << " Error " << oor.what() << '\n';
    exit(1);
  }
  if (groups[systId][0] >= 0) IDs[ngroups++] = groups[systId][0];

  return ngroups;
}
