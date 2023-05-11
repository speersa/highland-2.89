#include "FgdBwdMigrationWeightSystematics.hxx"
#include "SystId.hxx"
#include "ToyBoxTracker.hxx"
#include "EventBoxId.hxx"
#include "CategoriesUtils.hxx"
#include "VersioningUtils.hxx"

//#define DEBUG


//********************************************************************
FgdBwdMigrationWeightSystematics::FgdBwdMigrationWeightSystematics(const std::string& folder, const std::string& name):BinnedParams(
    folder,
    name,
    k1D_SYMMETRIC,
    versionUtils::ExtensionSyst() , 
    false){
  //********************************************************************

  
  SetNParameters(GetNBins());
}

//********************************************************************
Weight_h FgdBwdMigrationWeightSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& boxB, const SelectionBase& sel){
  //********************************************************************

#ifdef DEBUG
  std::cout << " FgdBwdMigrationWeightSystematics::ComputeWeight " << std::endl;
#endif
  
  (void)event;

  Weight_h eventWeight = 1.;

  // From the box get the following info:
  // topolgy from the reco vertrex, and the bwd status
  // Cast the ToyBox to the appropriate type
  const ToyBoxTracker& box = *static_cast<const ToyBoxTracker*>(&boxB); 
 
  if (!box.Vertex || box.Vertex->nParticles==0){
    return eventWeight;  
  }

  if (!box.TrueVertex){
    return eventWeight; // True vertex associated to the recon vertex should exist 
  }

  // Check the FGD detector
  SubDetId::SubDetEnum fgd = static_cast<SubDetId::SubDetEnum>(sel.GetDetectorFV());
  
  if (fgd != SubDetId::kFGD2){
    return eventWeight;
  }
  
  // Check the bwd migration status
  
  Int_t code = anaUtils::GetCodeCCBwdMigrated(box.Vertex->Particles[0], fgd); // RHC at the moment
  
  // CC events in FGD FV
  if (code != 0 && code != 1){
    return eventWeight;
  }
  
  bool isBwdMigrated = (code == 0);
   
   
#ifdef DEBUG
  std::cout << " FgdBwdMigrationWeightSystematics::isBwdMigrated " << isBwdMigrated << std::endl;
#endif
  
  
  /* Classify reaction types
    -1 = no true vertex
     0 = CC 0pi      = mu + X nucleons (+ 0 mesons)
     1 = CC 1pi+(-)  = mu + X nucleons + 1 pion +(-)
     2 = CC other
     3 = BKG: not (anti-)numu, NC
     7 = out of FV
   */
  
   
  Float_t value = GetSystBinValue(event, boxB, sel);
  
  BinnedParamsParams params;
  int index;
  if (!GetBinValues(value, params, index)){
    return eventWeight;
  }
  
  index = ApplyCorrelation(index);
  
  
  // The paramaeters read have the following form: bin defined by topo, fraction
  // of the bwd events for this topo, uncertainty on this fraction
  Float_t bwd_fraction = CorrectFraction(params.mean);
  
  if (bwd_fraction == 0){
    bwd_fraction += 0.0001;
  }
  
  Float_t non_bwd_fraction = 1 - bwd_fraction;

  if (non_bwd_fraction == 0){
    non_bwd_fraction += 0.0001;
  }
  

  Float_t bwd_fraction_sigma = CorrectFraction(params.sigma);
  
  // Calculate the new fraction of the bwd events
  // Add protection so that it cannot go below zero or above 100%
  Float_t bwd_fraction_new      = CorrectFraction(bwd_fraction + bwd_fraction * bwd_fraction_sigma * toy.GetToyVariations(_index)->Variations[index]);
  Float_t non_bwd_fraction_new  = 1 - bwd_fraction_new; 
  
  // Set the systematic weight depending on the bwd status
  eventWeight.Systematic = isBwdMigrated ? bwd_fraction_new / bwd_fraction : non_bwd_fraction_new / non_bwd_fraction;
  
  
#ifdef DEBUG
    std::cout << " eventWeight final " << eventWeight << std::endl; 
#endif

  return eventWeight;
}

// ********************************************************************
Float_t FgdBwdMigrationWeightSystematics::CorrectFraction(Float_t fraction) const{
// ********************************************************************

  if (fraction < 0){
    return 0.;
  }
  
  if (fraction > 1){
    return 1.;
  }
  
  return fraction;
  
}

// ********************************************************************
Float_t FgdBwdMigrationWeightSystematics::GetSystBinValue(const AnaEventC& event, const ToyBoxB& boxB, const SelectionBase& sel) const{
// ********************************************************************

  (void)event;
  (void)sel;
  
  const ToyBoxTracker& box = *static_cast<const ToyBoxTracker*>(&boxB); 
  
  // Check the FGD detector
  SubDetId::SubDetEnum fgd = static_cast<SubDetId::SubDetEnum>(sel.GetDetectorFV());
  
  // Get the topology depending on the truth vertex
 
  Float_t topo =  anaUtils::GetTopology(*static_cast<AnaTrueVertex*>(box.TrueVertex), fgd); // for the moment for FHC case
#ifdef DEBUG
  std::cout << " FgdBwdMigrationWeightSystematics::GetSystBinValue topo " << topo << std::endl;
#endif
  
 return topo; 
 
}


