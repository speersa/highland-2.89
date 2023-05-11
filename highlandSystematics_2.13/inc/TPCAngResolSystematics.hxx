#ifndef TPCAngResolSystematics_h
#define TPCAngResolSystematics_h

#include "BinnedParams.hxx"
#include "EventVariationBase.hxx"

class TPCAngResolSystematics: public EventVariationBase {
public:

  TPCAngResolSystematics();
  
  virtual ~TPCAngResolSystematics(){}
  
  /// Apply the systematic
  void Apply(const ToyExperiment& toy, AnaEventC& event);  
  
  /// Get the variation
  bool GetVariation(
      const AnaParticleB& track,
      Float_t& mean, 
      Float_t& mean_var, 
      Float_t& sigma_var, 
      const ToyExperiment& exp);
  
  /// Undo  the systematic variations done by ApplyVariation. This is faster tha reseting the full Spill
  bool UndoSystematic(AnaEventC& event);
      
  void Initialize();

  void Print(Option_t *option="") const;
    
protected:

  /// Is this track relevant for this systematic ?
  bool IsRelevantRecObject(const AnaEventC& event, const AnaRecObjectC& track) const;

  /// Store parameters here
  BinnedParams* _tpcmean;
  BinnedParams* _tpcsigma;

};

#endif
