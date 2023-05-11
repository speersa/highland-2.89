#include "ECalEmHipPIDSystematics.hxx"
#include "CutUtils.hxx"
#include "SystematicUtils.hxx"
#include "SystId.hxx"
#include "EventBoxId.hxx"
#include "SampleId.hxx"
#include "VersioningUtils.hxx"

//#define DEBUG

//********************************************************************
ECalEmHipPIDSystematics::ECalEmHipPIDSystematics(bool comp):EventWeightBase(1){
  //********************************************************************
   
  _computecounters = comp;
 
  _ecal_emhip_0 = new BinnedParams("ECal_EMHIPPID", BinnedParams::k3D_EFF_ASSYMMETRIC, versionUtils::ExtensionSyst());
  _ecal_emhip_10 = new BinnedParams("ECal_EMHIPPID_10", BinnedParams::k3D_EFF_ASSYMMETRIC, versionUtils::ExtensionSyst());


  SetNParameters(systUtils::GetNumberSystParams(*_ecal_emhip_0 , true)); 
      
  if (_computecounters){
    _ecal_emhip_0->InitializeEfficiencyCounter();
    _ecal_emhip_10->InitializeEfficiencyCounter();
  }
}

//********************************************************************
Weight_h ECalEmHipPIDSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& boxB, const SelectionBase& sel){
  //********************************************************************

  
  if (_computecounters){
    _ecal_emhip_0->InitializeEfficiencyCounter();
    _ecal_emhip_10->InitializeEfficiencyCounter();
  }

  (void)event;

  // Get the SystBox for this event, and the appropriate selection and branch
  SystBoxB* SystBox = GetSystBox(event, boxB.SelectionEnabledIndex, boxB.SuccessfulBranch);

  Weight_h eventWeight = 1.;

  BinnedParams*  ecal_emhip_params = GetBinnedParams(sel);
  
  if (!ecal_emhip_params){
    return eventWeight;
  }
  
#ifdef DEBUG
  std::cout << " \n ECalEmHipPIDSystematics::Apply(): " << SystBox->nRelevantRecObjects<< std::endl; 
#endif

  AnaECALParticleB* ecalTracks[NMAXPARTICLES];

  // Loop over relevant tracks
  for (Int_t itrk = 0; itrk < SystBox->nRelevantRecObjects; itrk++){

    AnaTrackB* track = static_cast<AnaTrackB*>(SystBox->RelevantRecObjects[itrk]);

    if (!track) continue;

    if (!sel.IsRelevantRecObjectForSystematicInToy(event, boxB, track, SystId::kECalEmHipPID, boxB.SuccessfulBranch)) continue;

    // Should have a true track
    AnaTrueParticleB* truePart = track->GetTrueParticle();
    if (!truePart) continue;

    // Get the ECal segment
    int count = anaUtils::GetTrackerDsEcals(track, ecalTracks);

    if (count < 1) continue;

    AnaECALParticleB* ecalTrack = ecalTracks[0];
    if (!ecalTrack) continue;

    // Protection against tracks with no physical values
    if(ecalTrack->PIDEmHip <= -999) continue;

    Float_t PIDEmHip = ecalTrack->PIDEmHip;

    // Get the PDG
    int pdg = abs(truePart->PDG);   

    BinnedParamsParams params;
    int index;

    // Better way of doing this?
    if(pdg == 211 || pdg == 321) pdg = 13;

    if (!ecal_emhip_params->GetBinValues(pdg, SubDetId::GetSubdetectorEnum(ecalTrack->Detector), truePart->Momentum, params, index)) continue;

    // Use "proper" eff/1-eff value depending on the sign of PIDEmHip, once the uncertainties are gaussian,  should be fine!
    bool found = true;
    if(PIDEmHip < 0){ // EM shower case
      params.meanDATA = 1 - params.meanDATA;
      params.meanMC   = 1 - params.meanMC;
    }

    // Found the correspondence,  now get the weight
    
     eventWeight *= systUtils::ComputeEffLikeWeight(found, toy, GetIndex(), index, params);

#ifdef DEBUG
    std::cout<<"ecal track PIDEmHip  "<< found << " eventWeight local " << eventWeight << std::endl; 
#endif

    if(_computecounters){
      ecal_emhip_params->UpdateEfficiencyCounter(index, found);  
    }

  }

  return eventWeight;
}


//********************************************************************
bool ECalEmHipPIDSystematics::IsRelevantRecObject(const AnaEventC& event, const AnaRecObjectC& recObj) const{
  //********************************************************************

  (void)event;

  const AnaTrackB& track = *static_cast<const AnaTrackB*>(&recObj);

  // Should use exactly one Tracker/DsECal detector --> optimized for tracker analysis at the moment 
  int count = (int)(anaUtils::TrackUsesDet(track, SubDetId::kTopTECAL)) + 
    (int)(anaUtils::TrackUsesDet(track, SubDetId::kBottomTECAL))      + 
    (int)(anaUtils::TrackUsesDet(track, SubDetId::kLeftTECAL))        + 
    (int)(anaUtils::TrackUsesDet(track, SubDetId::kRightTECAL))       + 
    (int)(anaUtils::TrackUsesDet(track, SubDetId::kDSECAL));

  if (count != 1) return false;

  return true;

}

//********************************************************************
BinnedParams* ECalEmHipPIDSystematics::GetBinnedParams(const SelectionBase& sel){
//********************************************************************
  
  SelectionBase& selm = const_cast<SelectionBase&>(sel);
  (void)selm; 
  // if (selm.GetSampleId() == SampleId::kFGD1NuMuCCPhoton ||
  //     selm.GetSampleId() == SampleId::kFGD2NuMuCCPhoton){
  //   return _ecal_emhip_10;
  // }
  
  // Default is the one with cut at 0
  return _ecal_emhip_0;
}
