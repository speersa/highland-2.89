#include "numuCCMultiPiPhotonProtonSelection.hxx"
#include "SystematicTuning.hxx"


/// \anchor numuCCMultiPiPhotonProtonSelection_DefineSteps
//*******************************************************************************
void numuCCMultiPiPhotonProtonSelection::DefineSteps(){
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

  AddStep(StepBase::kAction, "fill_summary_multiPiPhotonProton", new FillSummaryAction_numuCCMultiPiPhotonProton());

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

  // Split into zero and N protons
  AddSplit(2, 1, 0);

  // CC-0pi0Protons
  AddStep(1, 0, 0,  StepBase::kCut, "Zero Protons",  new ZeroProtonsCut());

  // CC-0piNProtons
  AddStep(1, 0, 1,  StepBase::kCut, "N Protons",     new NProtonsCut());  


  // Cuts for CC1pi: true -- Positive pion
  AddStep(1,1, StepBase::kCut, "CC-1pi",   new OnePionCut(true)); // positive pion

  // Cuts for CCOther
  AddStep(1,2, StepBase::kCut, "CC-Other", new OthersCut());

  //Branch names
  SetBranchAlias(0, "CCPhoton", 0);
  SetBranchAlias(1, "CC0pi-0p", 1, 0, 0);
  SetBranchAlias(2, "CC0pi-Np", 1, 0, 1);
  SetBranchAlias(3, "CC1pi"   , 1, 1);
  SetBranchAlias(4, "CCOther" , 1, 2);

}


//********************************************************************
bool numuCCMultiPiPhotonProtonSelection::FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]){
  //********************************************************************

  //CCPhoton
  if(allCutsPassed[0]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCPhoton;
  }
  //CC0pi - 0 protons
  else if (allCutsPassed[1]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0Pi0ProtonsNoPhoton;
  }

  //CC0pi - N protons
  else if (allCutsPassed[2]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC0PiNProtonsNoPhoton;
  }

  //CC1pi
  else if (allCutsPassed[3]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCC1PiNoPhoton;
  }
  //CCOther
  else if (allCutsPassed[4]){
    static_cast<AnaEventSummaryB*>(event.Summary)->EventSample = SampleId::kFGD1NuMuCCOtherNoPhoton;
  }

  // otherwise kUnassigned is used from the EventSummary constructor
  return (static_cast<AnaEventSummaryB*>(event.Summary)->EventSample != SampleId::kUnassigned);
}

//*********************************************************************
bool FillSummaryAction_numuCCMultiPiPhotonProton::Apply(AnaEventC& event, ToyBoxB& boxB) const{
  //*********************************************************************

  // Cast the ToyBox to the appropriate type
  ToyBoxCCMultiPi& box = *static_cast<ToyBoxCCMultiPi*>(&boxB); 


  if (!box.HMNtrack) return true;
  
  SampleId::SampleEnum SamplesUsed[5] = {
    SampleId::kFGD1NuMuCCPhoton, 
    SampleId::kFGD1NuMuCC0Pi0ProtonsNoPhoton, 
    SampleId::kFGD1NuMuCC0PiNProtonsNoPhoton, 
    SampleId::kFGD1NuMuCC1PiNoPhoton, 
    SampleId::kFGD1NuMuCCOtherNoPhoton};

  // Loop over samples
  for (int i = 0; i < 5; i++){
    
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
bool numuCCMultiPiPhotonProtonSelection::IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, 
    AnaRecObjectC* track, SystId_h systId, Int_t branch) const{
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

      // For CC-N-Protons consider proton TPC objects
      if (branch == 2)
      {
        if (ccmultipibox->pionBox.nProtonTPCtracks==1 && track==ccmultipibox->pionBox.ProtonTPCtracks[0]) return true;
      }
      // For CC1pi also the positive Pion in the TPC matters
      if (branch == 3){
        if (ccmultipibox->pionBox.nPositivePionTPCtracks==1 && track==ccmultipibox->pionBox.PositivePionTPCtracks[0]) return true;
      }

      // For CCPhoton (why ?) and CCOther consider the negative pion when there are no other pions
      else if (branch == 0 || branch == 4){
        if (ccmultipibox->pionBox.nNegativePionTPCtracks==1 && track==ccmultipibox->pionBox.NegativePionTPCtracks[0] &&
            ccmultipibox->pionBox.nOtherPions==1 && ccmultipibox->pionBox.nPosPions == 0) return true;

      }
      // Failed above +
      // CC0pi explicit false (should have been covered by numuCC if tuning is ON)
      return false;
      break;
    case SystId::kECalEmHipPID:
    case SystId::kECalPhotonPileUp:
    case SystId::kTpcECalMatchEff:
      if(branch == 2) return numuCCMultiPiPhotonSelection::IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 1);
      if(branch == 3) return numuCCMultiPiPhotonSelection::IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 2);
      if(branch == 4) return numuCCMultiPiPhotonSelection::IsRelevantRecObjectForSystematicInToy(event, box, track, systId, 3);
      return numuCCMultiPiPhotonSelection::IsRelevantRecObjectForSystematicInToy(event, box, track, systId, branch);
      break; 

      // The rest of the systematics go here, tuning to come
    default:
      return true;
      break;
  }

  return true;
}



//**************************************************
bool numuCCMultiPiPhotonProtonSelection::IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, 
    AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const{
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

      // If the are few TPC pions consider them, muons, electrons and protons
      if (abs(trueTrack->PDG)==211 || abs(trueTrack->PDG)==13 || abs(trueTrack->PDG)==11 || abs(trueTrack->PDG)==2212) return true;

      return false;
      break;
      
        
    case SystId::kSIProton:
      
        //Proton Samples requiers sliglhy different treatment
        //If event has more than one proton turn off, because it is unlikely SI will change topology, otherwise true
        if (branch == 1 || branch == 2)
        {
            if ((ccmultipibox->pionBox.nProtonTPCtracks+ccmultipibox->pionBox.nProtonFGDtracks) > 1 ) return false;
            else return true;
        }
        // If there are  many pions, i.e. topology cannot change, then do not use
        // the systematic
        if (ccmultipibox->pionBox.nOtherPions >1 || ccmultipibox->pionBox.nPosPions > 2 ) return false; 
        
        // If is CC-photon -- apply if a proton is a contributor
        if (branch ==0){
	// Tristan: commented out since causes compilation issues, not sure it's needed?
	//          return cutUtils::numuCCTrkMultiPi::CheckTrueCausesBoxSimple(*trueTrack, ccmultipibox->pionBox, multipart::kBoxECalPhotons);
        
        }
        
        // Otherwise check that a proton contributes to any of the objects in the
        // box

        return cutUtils::numuCCTrkMultiPi::CheckTrueCausesBoxSimple(*trueTrack, ccmultipibox->pionBox);
        break; 
        
    case SystId::kSIPion: 
    case SystId::kFgdHybridTrackEff:
    case SystId::kECalTrackEff:
    case SystId::kTpcECalMatchEff:
      if(branch == 2) return numuCCMultiPiPhotonSelection::IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, 1);
      if(branch == 3) return numuCCMultiPiPhotonSelection::IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, 2);
      if(branch == 4) return numuCCMultiPiPhotonSelection::IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, 3);
      return numuCCMultiPiPhotonSelection::IsRelevantTrueObjectForSystematicInToy(event, box, trueObj, systId, branch);
      break;
    default:
      return true;
      break;
  }

  // For the rest of the systematic return true
  return true;
}
