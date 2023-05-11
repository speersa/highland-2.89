#ifndef tofSystematics_h
#define tofSystematics_h

#include "EventVariationBase.hxx"
#include "BinnedParams.hxx"
#include "ToFSenseCorrector.hxx"

class ToFResolSystematics: public EventVariationBase{
public:
  enum RunIndex{
    kFHC = 0, 
    kRHC,
    kFHCRun8, 
    kRunIndexCounter
  };

  ToFResolSystematics();

  virtual ~ToFResolSystematics() {
    if (_fhc_input) delete _fhc_input; _fhc_input = NULL;
    if (_rhc_input) delete _rhc_input; _rhc_input = NULL;

  }

  /// Apply the systematic
  virtual void Apply(const ToyExperiment& toy, AnaEventC& event);

  /// Undo  the systematic variations done by ApplyVariation. This is faster tha reseting the full Spill
  virtual bool UndoSystematic(AnaEventC& event);
  
  
  
  void Print(Option_t *option="") const;


protected:

  /// Fill sigma inputs
  void FillSigmaValues(const RunIndex& index, BinnedParams* params);
  
  /// Get run index given an event
  ToFResolSystematics::RunIndex GetRunIndex(AnaEventC& event) const;
  
  /// ToF sense corrector
  ToFSenseCorrector _tofCorrector;

  /// Parameters to contol whether to apply additional smearing for ECal and P0D
  /// ToF values  
  bool    _add_smear_run8_p0d_ecal;
  Float_t _smear_scale_run8_p0d_ecal;
 
  
  /// Get the index of the variation
  size_t GetVariationIndex(const RunIndex& run_index, const ToFSenseCorrector::ToFTopology& topo) const;
  
  
  /// Sigma values since mean is supposed to be already "fixed" by a dedicated (highland2) correction
  Float_t _tof_sigmas[kRunIndexCounter][ToFSenseCorrector::kToFInvalid];

  
  BinnedParams* _fhc_input;
  BinnedParams* _rhc_input;
  BinnedParams* _fhc_run8_input;

  
};

#endif
