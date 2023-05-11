#include "nueECalPileUpSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "SystematicUtils.hxx"
#include "VersioningUtils.hxx"

//********************************************************************
nueECalPileUpSystematics::nueECalPileUpSystematics():EventWeightBase(1){
//********************************************************************

  _fgd1 = new BinnedParams("nueFGD1_upECal_PileUp",BinnedParams::k1D_SYMMETRIC, versionUtils::ExtensionSyst());
  _fgd2 = new BinnedParams("nueFGD2_upECal_PileUp",BinnedParams::k1D_SYMMETRIC, versionUtils::ExtensionSyst());
  SetNParameters(_fgd1->GetNBins()+_fgd2->GetNBins());
}

//********************************************************************
void nueECalPileUpSystematics::Initialize(){
//********************************************************************
  
  // Register the BinnedParams to have proper offsets for each of them
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd1, _fgd1->GetNBins());
  systUtils::AddBinnedParamsOffsetToSystematic(*this, *_fgd2, _fgd2->GetNBins());
  
}

//******************************************************************** 
void nueECalPileUpSystematics::Print(Option_t *option) const{
  //******************************************************************** 
  (void)option;

  std::cout << " ***** Bins for the nueECalPileUpSystematics ***** " << std::endl;

  unsigned int offset = 0;

  std::cout << " Bins for _fgd1 " << std::endl;
  _fgd1 ->Print(offset); 

  offset += _fgd1->GetNBins();

  std::cout << " Bins for _fgd2 " << std::endl;
  _fgd2 ->Print(offset); 

  std::cout << " ********* " << std::endl;

}  


//********************************************************************
Weight_h nueECalPileUpSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& eventBB, const ToyBoxB& box){
//********************************************************************

  Weight_h eventWeight= 1;

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB); 
  
  // Do not apply for sand
  if (event.GetIsSandMC()) return eventWeight; 
  
  if( box.DetectorFV != SubDetId::kFGD1 && box.DetectorFV != SubDetId::kFGD2) return eventWeight;

  // Get the run period (from 0 to 8)
  Int_t runPeriod = anaUtils::GetRunPeriod(event.EventInfo.Run);
  
  // MainTrack should be in FV. This condition is already in box.DetectorFV
  //  if  (!anaUtils::InFiducialVolume(box.DetectorFV, box.MainTrack->PositionStart))  return eventWeight;
  
  // Get the pileup values for this run period
  Float_t pileup;
  Float_t pileup_error;
  Int_t index;
  if     (box.DetectorFV==SubDetId::kFGD1){
    if(!_fgd1->GetBinValues(runPeriod, pileup, pileup_error, index)) return eventWeight;
    index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_fgd1);

  }
  else if(box.DetectorFV==SubDetId::kFGD2){
    if(!_fgd2->GetBinValues(runPeriod, pileup, pileup_error, index)) return eventWeight;
    index += systUtils::GetBinnedParamsOffsetForSystematic(*this, *_fgd2);

  }
  else return eventWeight;
  
  // compute the weight
  eventWeight.Systematic = 1 - pileup - pileup_error * toy.GetToyVariations(_index)->Variations[index];
  eventWeight.Correction = 1 - pileup;

  return eventWeight;
}

