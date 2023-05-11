#ifndef FluxWeightSystematics_h
#define FluxWeightSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"
#include "FluxWeighting.hxx"
#include <TMatrixD.h>

/// This is a normalization systematic. It takes into account the uncertainty on the neutrino flux

struct BinDef{
  BinDef(std::string inname, Int_t inmin, Int_t inmax, Int_t inmode_min, Int_t inmode_max){
    Name     = inname;
    TypeMin  = inmin;
    TypeMax  = inmax;
    ModeMin  = inmode_min;
    ModeMax  = inmode_max;          
  } 
  std::string Name;
  Int_t TypeMin;
  Int_t TypeMax;
  Int_t ModeMin;
  Int_t ModeMax;
};

class FluxWeightSystematics: public EventWeightBase{
  public:

    // Since the systematic is used for both, applying flux weight (used by
    // many analses) and systematic (limited need) add a parameter to check
    // whether the systematic part (retrieved from flux covariance) should be
    // applied
    FluxWeightSystematics(const std::string& file, bool apply_syst, FluxWeighting::Plane plane = FluxWeighting::kND5);
    
    FluxWeightSystematics(bool apply_syst, FluxWeighting::Plane plane = FluxWeighting::kND5);
    
    
    virtual ~FluxWeightSystematics() {
      delete   _flux;   _flux = NULL;
      delete _params; _params = NULL;
    }

    /// Apply this systematic
    using EventWeightBase::ComputeWeight;
    Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box);
    
    void Print(Option_t *option="") const;
    
protected:
    
  /// Access to the flux weighting.
  FluxWeighting* _flux;
  
  /// Utility function to read the input (from beam MC group) and fill the
  /// needed info
  void InitializeSystematics(); 
  
  /// Fill the binned params
  void FillBins();

  /// Fill the matrices
  void FillMatrices();
  
  
private:
  /// Default plane used for the weighting
  const FluxWeighting::Plane _ndplane;
  
  /// Binned params to be filled from the input data
  BinnedParams* _params;
  
  /// File used
  std::string _file;
  
  /// Root file used
  TFile* _root_file;
  
  /// Whether to apply systematic part, if false won`t read the covariances either
  bool _apply_syst;
};


#endif
