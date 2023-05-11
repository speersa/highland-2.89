#include "ToFResolSystematics.hxx"
#include "EventBoxTracker.hxx"
#include "Parameters.hxx"
#include "ND280AnalysisUtils.hxx"
#include "VersioningUtils.hxx"


// #define DEBUG

//********************************************************************
ToFResolSystematics::ToFResolSystematics():EventVariationBase(1){
  //********************************************************************
  
  _fhc_input      = new BinnedParams("ToFResolution_FHCRun2-4_p6M", BinnedParams::k1D_SYMMETRIC_NOMEAN, versionUtils::ExtensionSyst());
  _rhc_input      = new BinnedParams("ToFResolution_RHCRun5-9_p6M", BinnedParams::k1D_SYMMETRIC_NOMEAN, versionUtils::ExtensionSyst());
  _fhc_run8_input = new BinnedParams("ToFResolution_FHCRun8_p6M",   BinnedParams::k1D_SYMMETRIC_NOMEAN, versionUtils::ExtensionSyst());
  
  SetNParameters(_rhc_input->GetNBins() + _fhc_input->GetNBins() + _fhc_run8_input->GetNBins());
  
  RunIndex index = kFHC;
  
  FillSigmaValues(index, _fhc_input);
  
  index = kRHC;
  
  FillSigmaValues(index, _rhc_input);
  
  
  index = kFHCRun8;
  
  FillSigmaValues(index, _fhc_run8_input);
  
  // Wether to add additional smearing for Run8 - will scale the smearing for
  // P0D and ECal time values
  _add_smear_run8_p0d_ecal   = (bool)ND::params().GetParameterI("psycheSystematics.ToFResol.Run8.AddSmearECalP0D");
  _smear_scale_run8_p0d_ecal = (Float_t)ND::params().GetParameterD("psycheSystematics.ToFResol.Run8.SmearScaleECalP0D");
  
#ifdef DEBUG
  Print();
#endif
  
}

//********************************************************************
void ToFResolSystematics::Apply(const ToyExperiment& toy, AnaEventC& eventBB){
  //********************************************************************

  
  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB); 
  
  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);
  if (!box) return;

  Float_t scale_run8_p0d_ecal =  1.;
 
  
  RunIndex index = GetRunIndex(eventBB);
   
  if (_add_smear_run8_p0d_ecal){
    Int_t period = anaUtils::GetRunPeriod(event.EventInfo.Run); 
    if (period == 17 || period == 18){
      scale_run8_p0d_ecal = _smear_scale_run8_p0d_ecal; 
    }
  }
  
  // ToF.Det1_Det2 = t_det1 - t_det2
  
  // Loop though the tracks and apply the smearing
  for (int i = 0; i < box->nRelevantRecObjects; i++){
    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[i]);

    ToFSenseCorrector::ToFTopology topologies[ToFSenseCorrector::kToFInvalid];

    Int_t count = ToFSenseCorrector::GetToFTopologies(*track, topologies);

    for (Int_t j = 0; j < count; j++){
      
      ToFSenseCorrector::ToFTopology topo = topologies[j];

      if (topo == ToFSenseCorrector::kToFTopo_FGD1FGD2){
        // double before, after;
        // before = track->ToF.FGD1_FGD2;
        // std::cout << "Before: " << track->ToF.FGD1_FGD2 << std::endl; // ToF values b4 applying correction
        // std::cout << "index: " << index << std::endl; // This should be fhc, rhc, fhc run8
        // std::cout << "_index" << _index << std::endl; // parameter index maybe?
        // std::cout << "Variation: " << toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1P0D_Shower)] << std::endl;
        // std::cout << "sigma: " << _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1FGD2] << std::endl; 
        track->ToF.FGD1_FGD2 +=  _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1FGD2] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1FGD2)];

        // track->ToF.FGD1_FGD2 += _RandomGenerators[syst->GetIndex()].Gaus(0.,
        //                        _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1FGD2]*
        //                         toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1FGD2)])

        // after = track->ToF.FGD1_FGD2;
        // std::cout << "After: " << track->ToF.FGD1_FGD2  << std::endl;
        // std::cout << "Difference: " << after - before << std::endl;
        // std::cout << "sigma * variation? " 
      }

      if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Track) 
        track->ToF.P0D_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1P0D_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1P0D_Track)] * scale_run8_p0d_ecal;

      if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Shower) 
        track->ToF.P0D_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1P0D_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1P0D_Shower)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track) 
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track)] * scale_run8_p0d_ecal;
     
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower) 
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track)  
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower) 
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track)  
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower) 
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track)  
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower) 
        track->ToF.ECal_FGD1 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower)] * scale_run8_p0d_ecal;
    
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track) 
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower) 
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track)  {
        // std::cout << "Before: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track)] * scale_run8_p0d_ecal;
        // std::cout << "After: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction

      }
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower) {
        // std::cout << "Before: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower)] * scale_run8_p0d_ecal;
        // std::cout << "After: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
      }
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track) { 
        // std::cout << "kToFTopo_FGD2ECAL_HAStartFgd_Track Before: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
        // std::cout << "Sigma: " <<  _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track]  << std::endl;
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track] * 
        toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track)] * scale_run8_p0d_ecal;
          // std::cout << "After: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction

      }
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower) {
        // std::cout << "kToFTopo_FGD2ECAL_HAStartFgd_Shower Before: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
        // std::cout << "Sigma: " <<  _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower]  << std::endl;
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower] * 
        toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower)] * scale_run8_p0d_ecal;
        // std::cout << "After: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction

      }
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track)  {
        // std::cout << "kToFTopo_FGD2ECAL_HAEndFgd_Track Before: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
        // std::cout << "Sigma: " <<  _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track]  << std::endl;
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track)] * scale_run8_p0d_ecal;
        // std::cout << "After: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction

      }
      if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower) {
        // std::cout << "kToFTopo_FGD2ECAL_HAEndFgd_Shower Before: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
        // std::cout << "Sigma: " <<  _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower]  << std::endl;
        track->ToF.ECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower)] * scale_run8_p0d_ecal;
        // std::cout << "After: " << track->ToF.ECal_FGD2 << std::endl; // ToF values b4 applying correction
      }
      if (topo == ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track) 
        track->ToF.DSECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track)] * scale_run8_p0d_ecal;
      
      if (topo == ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower) 
        track->ToF.DSECal_FGD2 +=   _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower)] * scale_run8_p0d_ecal;
 
      if (topo == ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1)
        // std::cout << "kToFTopo_FGD1FGD2_NoStopFGD1 Before: " << track->ToF.FGD1_FGD2 << std::endl; // ToF values b4 applying correction
        // std::cout << "Sigma: " <<  _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1]  << std::endl;
        track->ToF.FGD1_FGD2 +=  _tof_sigmas[index][ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1] * 
          toy.GetToyVariations(_index)->Variations[GetVariationIndex(index, ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1)]; 
    }
  }

}

//********************************************************************
void ToFResolSystematics::FillSigmaValues(const RunIndex& index, BinnedParams* params){
//********************************************************************

  // Get the systematic source values 
  for (int j = 0; j < ToFSenseCorrector::kToFInvalid; j++){
    params->GetSigmaValueForBin(static_cast<ToFSenseCorrector::ToFTopology>(j),  _tof_sigmas[index][j]);
  }
  
}


//********************************************************************
size_t ToFResolSystematics::GetVariationIndex(const RunIndex& run_index, const ToFSenseCorrector::ToFTopology& topo) const{
//********************************************************************
  
  return (size_t)(run_index *  ToFSenseCorrector::kToFInvalid) + (size_t)topo;
  
}

//********************************************************************
ToFResolSystematics::RunIndex ToFResolSystematics::GetRunIndex(AnaEventC& eventBB) const{
   //********************************************************************
   
  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB);
  
  //FHC
  RunIndex index = kFHC;
  
  //RHC
  if (anaUtils::IsRHC(event.EventInfo.Run)){
    index = kRHC;
  
  }
  
  
  Int_t run_period = anaUtils::GetRunPeriod(event.EventInfo.Run); 
  
  if (run_period == 17 || run_period == 18){
    index = kFHCRun8;
  } 
  
  
  return index;
}

//********************************************************************
bool ToFResolSystematics::UndoSystematic(AnaEventC& event){
  //********************************************************************

  // Get the SystBox for this event
  SystBoxB* box = GetSystBox(event);

  for (int i = 0; i < box->nRelevantRecObjects; i++){

    AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[i]);
    if(!track->Original){ std::cout<<"ToFResolSystematics::UndoSystematic:: No original object , not able to undo variation"<<std::endl; continue; }
    const AnaTrackB* orig = static_cast<const AnaTrackB*>(track->Original);

    if (track->ToF.Flag_FGD1_FGD2)
      track->ToF.FGD1_FGD2 = orig->ToF.FGD1_FGD2;

    if (track->ToF.Flag_P0D_FGD1)
      track->ToF.P0D_FGD1 = orig->ToF.P0D_FGD1;

    if (track->ToF.Flag_ECal_FGD1)
      track->ToF.ECal_FGD1 = orig->ToF.ECal_FGD1;

    if (track->ToF.Flag_ECal_FGD2)
      track->ToF.ECal_FGD2 = orig->ToF.ECal_FGD2;
    
    if (track->ToF.Flag_DSECal_FGD2)
      track->ToF.DSECal_FGD2 = orig->ToF.DSECal_FGD2;
  }

  return false;
}


//******************************************************************** 
void ToFResolSystematics::Print(Option_t *option) const{
  //******************************************************************** 
  (void)option;

  std::cout << " ***** Bins for the ToFResolSystematics **** " << std::endl;

  unsigned int offset = 0;

  std::cout << " Bins for _fhc_input " << std::endl;
  _fhc_input ->Print(offset); 

  offset += _fhc_input->GetNBins();

  std::cout << " Bins for _rhc_input " << std::endl;
  _rhc_input ->Print(offset); 

  std::cout << " ********* " << std::endl;

}
