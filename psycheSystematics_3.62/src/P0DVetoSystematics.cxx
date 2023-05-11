#include "P0DVetoSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "VersioningUtils.hxx"

//********************************************************************
P0DVetoSystematics::P0DVetoSystematics():EventWeightBase(1){
//********************************************************************
  
  _p0d = new BinnedParams("P0DVeto", BinnedParams::k1D_SYMMETRIC, versionUtils::ExtensionSyst());

  SetNParameters(_p0d->GetNBins());
}


//********************************************************************
Weight_h P0DVetoSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& eventBB, const ToyBoxB& box){
//********************************************************************

  Weight_h eventWeight= 1;

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB); 

  if( box.DetectorFV != SubDetId::kP0D) return eventWeight;

  // Get the run period (from 0 to 8)
  Int_t runPeriod = anaUtils::GetRunPeriod(event.EventInfo.Run);
  
  // MainTrack should be in FV. This condition is already in box.DetectorFV
  //  if  (!anaUtils::InFiducialVolume(box.DetectorFV, box.MainTrack->PositionStart))  return eventWeight;
  
  // Get the pileup values for this run period
  Float_t veto_corr;
  Float_t veto_corr_error;
  Int_t index;

  if(!_p0d->GetBinValues(runPeriod, veto_corr, veto_corr_error, index)) return eventWeight;
  
  // compute the weight
  eventWeight.Systematic = 1 - veto_corr - veto_corr_error * toy.GetToyVariations(_index)->Variations[index];
  eventWeight.Correction = 1 - veto_corr;

  return eventWeight;
}

