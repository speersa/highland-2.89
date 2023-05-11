#ifndef FGDPIDSystematics_h
#define FGDPIDSystematics_h

#include "EventVariationBase.hxx"
#include "FGDPIDVariation.hxx"

/// This systematic smears the pull of each FGD track segment
class FGDPIDSystematics: public FGDPIDVariation, public EventVariationBase {
public:

  /// Instantiate the FGD PID systematic
  FGDPIDSystematics();
  
  virtual ~FGDPIDSystematics(){}
  
  /// Apply the systematic
  void Apply(const ToyExperiment& toy, AnaEventC& event);
  
  
  /// Get the variation
  bool GetVariation(
      const Int_t& pdg_ref, 
      const AnaParticleB& track,
      Int_t pdg_hypo, 
      Float_t& pull_mean, 
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


};

#endif
