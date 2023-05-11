#ifndef FGDPIDVariation_h
#define FGDPIDVariation_h

#include "BinnedParams.hxx"
#include "BaseDataClasses.hxx"
#include "ParticleId.hxx"

class ToyExperiment;


/// This variation smears PID pull parameters of the FGD tracks
/// 
class FGDPIDVariation{
public:

  /// Instantiate the PID variation,  
  FGDPIDVariation(){ 
    _fgd1mean  = NULL;
    _fgd1sigma = NULL;
    _fgd2mean  = NULL;
    _fgd2sigma = NULL;

  }

  virtual ~FGDPIDVariation() {

    if (_fgd1mean)  delete _fgd1mean;  _fgd1mean  = NULL;
    if (_fgd1sigma) delete _fgd1sigma; _fgd1sigma = NULL;
    if (_fgd2mean)  delete _fgd2mean;  _fgd2mean  = NULL;
    if (_fgd2sigma) delete _fgd2sigma; _fgd2sigma = NULL;

  }

  /// Apply variation for a track, the most general case given a certain ToyExperiment
  virtual void ApplyVariation(AnaTrackB* track, const ToyExperiment& exp);

  /// Get variation given a track and a pdg to define a hypo we want to e.g.
  /// vary
  virtual bool GetVariation( 
      const Int_t& pdg_ref, // safety -- local-global truth
      const AnaParticleB& track,
      Int_t pdg_hypo, 
      Float_t& pull_mean, 
      Float_t& mean_var, 
      Float_t& sigma_var, 
      const ToyExperiment& exp) = 0;
 
    
    
  void SetVariedPull(
      AnaFGDParticleB* fgdTrack,
      Int_t pdg_hypo, 
      const Float_t& pull_mean, 
      const Float_t& mean_var, 
      const Float_t& sigma_var);
  
     
  void UpdatePull(
      Float_t& pull, 
      const Float_t& pull_mean, 
      const Float_t& mean_var, 
      const Float_t& sigma_var); 
  
  
  /// Get PDG
  Int_t GetPDG( const AnaTrueParticleB& track);
  
  
  const Int_t pdg_hypos[4] = {
    ParticleId::kMuonPDG, 
    ParticleId::kPionPosPDG,
    ParticleId::kProtonPDG, 
    ParticleId::kElectronPDG
  };
  
  
protected:

  /// Expect that the derived classes should use some data to store the params for the variations
  /// so keep the data-storage here

  BinnedParams* _fgd1mean;
  BinnedParams* _fgd1sigma;
  BinnedParams* _fgd2mean;
  BinnedParams* _fgd2sigma;
  
  
};

#endif
