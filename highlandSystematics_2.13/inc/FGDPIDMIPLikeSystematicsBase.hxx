#ifndef FGDPIDMIPLikeSystematicsBase_h
#define FGDPIDMIPLikeSystematicsBase_h

#include "BinnedParams.hxx"
#include "DataClasses.hxx"
#include "ParticleId.hxx"
#include "EventVariationBase.hxx"



/// This variation smears PID pull parameters of the FGD tracks

class FGDPIDMIPLikeSystematicsBase: public EventVariationBase{ 
public:

  /// Instantiate the PID variation,  
  FGDPIDMIPLikeSystematicsBase(){
    _fgd1mean  = NULL;  
    _fgd1sigma = NULL;    
    _fgd2mean  = NULL;    
    _fgd2sigma = NULL;
  }

  virtual ~FGDPIDMIPLikeSystematicsBase() {

    if (_fgd1mean)  delete _fgd1mean;  _fgd1mean  = NULL;
    if (_fgd1sigma) delete _fgd1sigma; _fgd1sigma = NULL;
    if (_fgd2mean)  delete _fgd2mean;  _fgd2mean  = NULL;
    if (_fgd2sigma) delete _fgd2sigma; _fgd2sigma = NULL;

  }

  /// Apply the systematic
  void Apply(const ToyExperiment& toy, AnaEventC& event);


  /// Apply variation for a track, the most general case given a certain ToyExperiment
  virtual void ApplyVariation(AnaTrackB* track, const ToyExperiment& exp);

  virtual bool GetVariation(
      const AnaTrackB& track,
      const AnaFGDParticle& fgdTrack, 
      Float_t& pull_mean, 
      Float_t& mean_var, 
      Float_t& sigma_var, 
      const ToyExperiment& exp) = 0;


  void SetVariedPIDMIPLike(AnaFGDParticle* fgdTrack, const Float_t& pid_mean, 
      const Float_t& mean_var, 
      const Float_t& sigma_var);
  
  /// Undo  the systematic variations done by ApplyVariation. This is faster tha reseting the full Spill
  bool UndoSystematic(AnaEventC& event);
  
  virtual void Initialize() = 0;
  
protected:

  
  /// Expect that the derived classes should use some data to store the params for the variations
  /// so keep the data-storage here

  BinnedParams* _fgd1mean;
  BinnedParams* _fgd1sigma;
  BinnedParams* _fgd2mean;
  BinnedParams* _fgd2sigma;
};

#endif
