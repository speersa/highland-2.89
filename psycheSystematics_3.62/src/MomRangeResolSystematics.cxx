#include "MomRangeResolSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "EventBoxTracker.hxx"
#include "VersioningUtils.hxx"
#include "Parameters.hxx"
#include "PropagationUtils.hxx"
#include "SystematicUtils.hxx"

//#define DEBUG


//********************************************************************
MomRangeResolSystematics::MomRangeResolSystematics():EventVariationBase(1){
  //********************************************************************

  _mom_range_muon_params   = new BinnedParams("MomRangeResol_muon",   BinnedParams::k3D_SYMMETRIC_NOMEAN, versionUtils::ExtensionSyst());
  _mom_range_proton_params = new BinnedParams("MomRangeResol_proton", BinnedParams::k3D_SYMMETRIC_NOMEAN, versionUtils::ExtensionSyst());

  SetNParameters(systUtils::GetNumberSystParams(*_mom_range_muon_params, false) + 
      systUtils::GetNumberSystParams(*_mom_range_proton_params, false) ); 
}


//********************************************************************
void MomRangeResolSystematics::Initialize(){
  //********************************************************************

  //Register BinnedParams to get proper offsets
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_mom_range_muon_params,   systUtils::GetNumberSystParams(*_mom_range_muon_params,   false));
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_mom_range_proton_params, systUtils::GetNumberSystParams(*_mom_range_proton_params, false));

}



//******************************************************************** 
void MomRangeResolSystematics::Print(Option_t *option) const{
  //******************************************************************** 
  (void)option;

  std::cout << " ***** Bins for the MomRangeResolSystematics **** " << std::endl;
  std::cout << " ***** For bin throw 1 param in case to vary relative resolution  **** " << std::endl;

  unsigned int offset = 0;

  std::cout << " Bins for _mom_range_muon_params " << std::endl;
  _mom_range_muon_params->Print(offset); 

  offset += _mom_range_muon_params->GetNBins();

  std::cout << " Bins for _mom_range_proton_params " << std::endl;

  _mom_range_proton_params->Print(offset); 

  std::cout << " ********* " << std::endl;

}  


//********************************************************************
void MomRangeResolSystematics::Apply(const ToyExperiment& toy, AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

#ifdef DEBUG
  std::cout << "MomRangeResolSystematics::ApplyVariation(): " << box->nRelevantRecObjects << std::endl;  
#endif

  // Loop over relevant tracks for this systematic
  for (Int_t itrk=0;itrk<box->nRelevantRecObjects;itrk++){

    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);

    if (!track) continue;

    if (!track->TrueObject) continue;

#ifdef DEBUG
    std::cout << itrk << std::endl;
    track->Print();
    std::cout<<"\n"<<std::endl;
#endif 

    // Get momentum from range for muon hypothesis
    Float_t p0_range_muon = track->RangeMomentumMuon;

    // Get momentum from range for pion hypothesis
    Float_t p0_range_pion = track->RangeMomentumPion;


    // Get momentum from range for proton hypothesis
    Float_t p0_range_proton = track->RangeMomentumProton;

    // Get the true momentum
    Float_t p0_true = track->GetTrueParticle()->Momentum;


#ifdef DEBUG
    std::cout << "track true momentum   p0_true           --\t "   << p0_true         << std::endl;
    std::cout << "track range momentum  muon p0_range     --\t "   << p0_range_muon   << std::endl;
    std::cout << "track range momentum  pion p0_range     --\t "   << p0_range_pion   << std::endl;
    std::cout << "track range momentum  proton p0_range   --\t "   << p0_range_proton << std::endl;
#endif

    // Get the angle of a track wrt to beam axis: this is used to determine the systematic bins
    Float_t costheta = fabs(track->DirectionStart[2]);

    // Get the detectors involved
    // FGD
    int bin_fgddet = GetFGDDet(track->Detector);
    int bin_outerdet = bin_fgddet;
    SubDetId::SubDetEnum smrd_det   = GetSMRDDet(  track->Detector);
    SubDetId::SubDetEnum tecal_det  = GetTECalDet( track->Detector);
    if(smrd_det!=SubDetId::kInvalid)
      bin_outerdet = smrd_det; 
    else if(tecal_det!=SubDetId::kInvalid)
      bin_outerdet = tecal_det;

#ifdef DEBUG
    std::cout << " bin values: bin_fgddet "<< bin_fgddet << " bin_outerdet " << bin_outerdet << " costheta " << costheta << "\n";
#endif


    // Momentum by range is checked by comparing TPC momentum to a momentum of a stopping part TPC-(FGD-*)
    // In many cases for a tracker analysis an estimated mom-range is lower
    // than the corresponding true mom since a part of an FGD track is missing in the case of
    // TPC-FGD track(s) present for the same vertex,  TPC-FGD is too greedy and
    // sometimes "eats" a few FGD hits around the vertex that belong to an
    // FGD-iso object
    // Having the effect desribed above the treatment similar to TPC-based
    // momentum resolution 

    // Float_t prangev = (1 + sigma * toy.GetToyVariations(_index)->Variations[index]) * (p0_range - p0_true) + p0_true;

    // Should use proper ingredients to avoid a bias,  hence p0_range value
    // should be the one corrected to a possible bias due to a "vertex migration"

    // Correct for three hypotheses: muon, pion, proton
    // Create a vertex and set to to the true one



    AnaVertexB vertex_tmp;

    for(int i = 0; i < 4; ++i){
      vertex_tmp.Position[i] = track->GetTrueParticle()->Position[i];
    }


    bool isStart = anaUtils::GetSeparationSquared(vertex_tmp.Position, track->PositionStart) <
      anaUtils::GetSeparationSquared(vertex_tmp.Position, track->PositionEnd);  

    Float_t pcorr_muon = isStart ? 
      propUtils::CorrectMomRangeToVertex(vertex_tmp, *track, ParticleId::kMuonPDG, si_syst::kStart) :
      propUtils::CorrectMomRangeToVertex(vertex_tmp, *track, ParticleId::kMuonPDG, si_syst::kEnd);

    Float_t pcorr_pion = isStart ? 
      propUtils::CorrectMomRangeToVertex(vertex_tmp, *track, ParticleId::kPiPosPDG, si_syst::kStart) :
      propUtils::CorrectMomRangeToVertex(vertex_tmp, *track, ParticleId::kPiPosPDG, si_syst::kEnd);  


    Float_t pcorr_proton = isStart ? 
      propUtils::CorrectMomRangeToVertex(vertex_tmp, *track, ParticleId::kProtonPDG, si_syst::kStart) :
      propUtils::CorrectMomRangeToVertex(vertex_tmp, *track, ParticleId::kProtonPDG, si_syst::kEnd);

    
    // Get the differences
    Float_t pdiff_muon   = pcorr_muon   - p0_range_muon;
    
    Float_t pdiff_pion   = pcorr_pion   - p0_range_pion;
  
    Float_t pdiff_proton = pcorr_proton - p0_range_proton;
  
#ifdef DEBUG
    std::cout << "muon candidate p_range after vertex corr --\t "   << pcorr_muon   << std::endl;
    std::cout << "pion candidate p_range after vertex corr --\t "   << pcorr_pion   << std::endl;
    std::cout << "proton candidate p_range after vertex corr --\t " << pcorr_proton << std::endl;
#endif

    // Get the extra resolution values: bins are defined by angle
    Float_t sigma;
    Int_t index = -1;

    // Muon and pion
    if (_mom_range_muon_params->GetBinSigmaValue(bin_fgddet, bin_outerdet, costheta, sigma, index)){

      // Add proper offset to the index
      index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_mom_range_muon_params);
#ifdef DEBUG
      std::cout << "muon/pion bin values: sigma " << sigma << " index " << index << std::endl;
#endif

      // Same for pions and muons
      Float_t prangev_muon = (1 + sigma * toy.GetToyVariations(_index)->Variations[index]) * (pcorr_muon - p0_true) + p0_true;
      Float_t prangev_pion = (1 + sigma * toy.GetToyVariations(_index)->Variations[index]) * (pcorr_pion - p0_true) + p0_true;

#ifdef DEBUG
      std::cout << "muon candidate p_range corr after tweak --\t " << prangev_muon << std::endl;
      std::cout << "pion candidate p_range corr after tweak --\t " << prangev_pion << std::endl;
#endif

      // Apply the variation accounting back for the bias
      track->RangeMomentumMuon = prangev_muon - pdiff_muon;

      track->RangeMomentumPion = prangev_pion - pdiff_pion;
       
#ifdef DEBUG
      std::cout << "muon candidate p_range final after tweak --\t " << track->RangeMomentumMuon << std::endl;
      std::cout << "pion candidate p_range final after tweak --\t " << track->RangeMomentumPion  << std::endl;
#endif
      
    }

    // Proton
    if (_mom_range_proton_params->GetBinSigmaValue(bin_fgddet, bin_outerdet, costheta, sigma, index)){
      
      // Add proper offset to the index
      index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_mom_range_proton_params);
#ifdef DEBUG
      std::cout << "proton bin values: sigma " << sigma << " index " << index << std::endl;
#endif

      Float_t prangev_proton = (1 + sigma * toy.GetToyVariations(_index)->Variations[index]) * (pcorr_proton - p0_true) + p0_true;

#ifdef DEBUG
      std::cout << "proton candidate p_range corr after tweak --\t " << prangev_proton << std::endl;
#endif

      // Apply the variation accounting back for the bias
      track->RangeMomentumProton = prangev_proton - pdiff_proton;
      
#ifdef DEBUG
      std::cout << "proton candidate p_range final after tweak --\t " << track->RangeMomentumProton  << std::endl;
#endif
    }

  }

}

//********************************************************************
bool MomRangeResolSystematics::UndoSystematic(AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

  for (Int_t itrk=0;itrk<box->nRelevantRecObjects;itrk++){
    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);
    // Go back to the corrected momentum
    track->RangeMomentumMuon   = track->GetOriginalTrack()->RangeMomentumMuon;

    track->RangeMomentumPion   = track->GetOriginalTrack()->RangeMomentumPion;

    track->RangeMomentumProton = track->GetOriginalTrack()->RangeMomentumProton;
  }
  // Don't reset the spill to corrected
  return false;
}

//********************************************************************
bool MomRangeResolSystematics::IsRelevantRecObject(const AnaEventC& event, const AnaRecObjectC& recObj) const{
  //********************************************************************
  (void)(event);

  const AnaTrackB* track = static_cast<const AnaTrackB*>(&recObj);

  // do nothing if the momentum value is a default one (-999),  and less than RP default 0.1
  if (track->RangeMomentumMuon < 0.5) return false;

  //ignore tracks with more than one segment in SMRD or ECal
  // if (track->nECALSegments>1 || track->nSMRDSegments>1) return false;

  //want the candidate with no TPC
  // if(SubDetId::GetDetectorUsed(track->Detector, SubDetId::kTPC))
  //  return false;

  return true;
}

//**************************************************
SubDetId::SubDetEnum MomRangeResolSystematics::GetFGDDet(unsigned long Detector) {
  //**************************************************
  SubDetId::SubDetEnum det = SubDetId::kInvalid;
  if(SubDetId::GetDetectorUsed(Detector,      SubDetId::kFGD1))
    det = SubDetId::kFGD1;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kFGD2))
    det = SubDetId::kFGD2;       

  return det;
}


//**************************************************
SubDetId::SubDetEnum MomRangeResolSystematics::GetTECalDet(unsigned long Detector) {
  //**************************************************
  SubDetId::SubDetEnum det = SubDetId::kInvalid;
  if(SubDetId::GetDetectorUsed(Detector,      SubDetId::kTopTECAL))
    det = SubDetId::kTopTECAL;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kLeftTECAL))
    det = SubDetId::kLeftTECAL;                    
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kRightTECAL))
    det = SubDetId::kRightTECAL;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kBottomTECAL))
    det = SubDetId::kBottomTECAL;

  return det;
}



//**************************************************
SubDetId::SubDetEnum MomRangeResolSystematics::GetSMRDDet(unsigned long Detector) {
  //**************************************************
  SubDetId::SubDetEnum det = SubDetId::kInvalid;
  if(SubDetId::GetDetectorUsed(Detector,      SubDetId::kTopSMRD))
    det = SubDetId::kTopSMRD;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kLeftSMRD))
    det = SubDetId::kLeftSMRD;                    
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kRightSMRD))
    det = SubDetId::kRightSMRD;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kBottomSMRD))
    det = SubDetId::kBottomSMRD;

  return det;
}
