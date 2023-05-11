#ifndef ECalEmHipPIDSystematics_h
#define ECalEmHipPIDSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"

class ECalEmHipPIDSystematics: public EventWeightBase {
public:

  ECalEmHipPIDSystematics(bool computecounters=false);  
  
  
  virtual ~ECalEmHipPIDSystematics() {
    if (_ecal_emhip_0)  delete _ecal_emhip_0;  _ecal_emhip_0  = NULL;
    if (_ecal_emhip_10) delete _ecal_emhip_10; _ecal_emhip_10 = NULL;
  }

  /// Apply the systematic
  Weight_h ComputeWeight(const ToyExperiment&, const AnaEventC&, const ToyBoxB&){
    return 1.;
  }

  /// Apply the systematic
  Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel);

  /// Return the proper binned params to be used 
  BinnedParams* GetBinnedParams(const SelectionBase& sel);

protected:

  /// Is this track relevant for this systematic ?
  bool IsRelevantRecObject(const AnaEventC& event, const AnaRecObjectC& recObj) const;
  bool  _computecounters;
  

  
  BinnedParams* _ecal_emhip_0;
  BinnedParams* _ecal_emhip_10;
  
};

#endif
