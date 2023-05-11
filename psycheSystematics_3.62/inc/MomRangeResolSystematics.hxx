#ifndef MomRangeResolSystematics_h
#define MomRangeResolSystematics_h

#include "EventVariationBase.hxx"
#include "BinnedParams.hxx"


/// This systematic smears the momentum-by-range by a
/// random amount from a Gaussian distribution.
///
class MomRangeResolSystematics: public EventVariationBase{
public:
  
  /// Instantiate the momentum resolution systematic
  MomRangeResolSystematics();
  
  virtual ~MomRangeResolSystematics() {
    if (_mom_range_muon_params)   delete _mom_range_muon_params;   _mom_range_muon_params   = NULL;
    if (_mom_range_proton_params) delete _mom_range_proton_params; _mom_range_proton_params = NULL;
  }
  
  /// Apply the systematic
  virtual void Apply(const ToyExperiment& toy, AnaEventC& event);
  
  /// Undo  the systematic variations done by ApplyVariation. This is faster tha reseting the full Spill
  virtual bool UndoSystematic(AnaEventC& event);  
    
  void Initialize();
  
    
  void Print(Option_t *option="") const;
  
  
protected:
  
  /// Check whether a RecObject is relevant for this systematic or not
  virtual bool IsRelevantRecObject(const AnaEventC&, const AnaRecObjectC&) const;
  
  /// Get SMRD detector assuming only one can be present
  SubDetId::SubDetEnum GetSMRDDet(unsigned long Detector);
  
  /// Get TECal detector assuming only one can be present
  SubDetId::SubDetEnum GetTECalDet(unsigned long Detector);

  /// Get FGD detector assuming only one can be present
  SubDetId::SubDetEnum GetFGDDet(unsigned long Detector);
    
  BinnedParams* _mom_range_muon_params;
  BinnedParams* _mom_range_proton_params;
  
};

#endif
