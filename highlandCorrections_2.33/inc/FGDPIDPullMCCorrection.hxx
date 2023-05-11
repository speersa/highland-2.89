#ifndef FGDPIDPullMCCorrection_h
#define FGDPIDPullMCCorrection_h

#include "CorrectionBase.hxx"
#include "FGDPIDVariation.hxx"
#include "ToyExperiment.hxx"


/// This class defines a correction that affects the pulls of FGD iso objects 

class FGDPIDPullMCCorrection: public FGDPIDVariation, public CorrectionBase {

public:
  
  FGDPIDPullMCCorrection();

  virtual ~FGDPIDPullMCCorrection() {}

  /// Apply the correction to all the relevant objects: FGD constituent of an AnaTrack 
  void Apply(AnaSpillC& spill);

  /// Get the variation
  bool GetVariation(
      const Int_t& pdg_ref, 
      const AnaParticleB& track,
      Int_t pdg_hypo, 
      Float_t& pull_mean, 
      Float_t& mean_var, 
      Float_t& sigma_var, 
      const ToyExperiment& exp); 

protected:
  
  /// Check whether a track is relevant to apply the correction: e.g. momentum resolution was studied for tracker objects only 
  /// Probably should be moved to a base class
  bool IsRelevantObject(const AnaRecObjectC* object) {(void)object; return true;} // all considered for the moment
  
  
  /// Some default toy experiment,  not used at the moment
  ToyExperiment _exp;  
};

#endif
