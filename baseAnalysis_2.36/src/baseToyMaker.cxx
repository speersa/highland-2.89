#include "baseToyMaker.hxx"
#include "Parameters.hxx"
#include "SystId.hxx"
#include "TVectorT.h"
//******************************************************************
baseToyMaker::baseToyMaker(UInt_t seed):ToyMaker(){
  //******************************************************************

  _binnedPDF = new BinnedGaussian(10,0,1);  

  // Set the seed
  _RandomGenerator.SetSeed(seed);

  // Use a random generator for each systematic
  _individualRandomGenerator = (bool) (ND::params().GetParameterI("baseAnalysis.Systematics.IndividualRandomGenerator")); 

  if (_individualRandomGenerator){
    for (UInt_t isyst = 0; isyst<NMAXSYSTEMATICS;isyst++){
      SystematicBase* syst = _systematics[isyst];
      if (!syst) continue;

      _seeds[isyst] = syst->GetIndex() + seed*NMAXSYSTEMATICS;
      _RandomGenerators[isyst].SetSeed(_seeds[isyst]);
    }
  }

  // Save the random Seed
  _seed = seed;
}

//******************************************************************
void baseToyMaker::FillToyExperiment(ToyExperiment& toy){
  //******************************************************************

  // Set the same weight (1) for al toys. This will be later normalized to the number of toys
  Float_t weight = 1.;


  for (UInt_t isyst = 0; isyst<NMAXSYSTEMATICS;isyst++){
    SystematicBase* syst = _systematics[isyst];
    if (!syst) continue;

    // Create the proper structure for the ToyExperiment adding each of the toyVariations
    toy.AddToyVariation(syst->GetIndex(), syst->GetNParameters());

    // Use the covariance or correlation matrix if present
    if (syst->GetLCovMatrix() || syst->GetLCorrMatrix()){
      // Create the vector of the corresponding params
      TVectorT<double> vec(syst->GetNParameters());

      // Fill with random vars
      for (UInt_t ipar = 0; ipar < syst->GetNParameters(); ipar++){
        vec[ipar] = _RandomGenerators[isyst].Gaus(0.,1.);
      }

      // Apply the covariance/correlation
      vec *= syst->GetLCovMatrix() ? (*syst->GetLCovMatrix()) : (*syst->GetLCorrMatrix());

      // Set the variations
      for (UInt_t ipar = 0; ipar < syst->GetNParameters(); ipar++){
        toy.SetToyVariation(syst->GetIndex(), ipar, vec[ipar], weight); 
      }
      continue;
    }


    // Get all the parameters for this systematic

    // Loop over parameters for this systematic
    for (UInt_t ipar = 0; ipar < syst->GetNParameters(); ipar++){
    
      Float_t var = GetToyVariation(toy.GetToyIndex(), syst, ipar);
      
      toy.SetToyVariation(syst->GetIndex(), ipar, var, weight); 
    }


  }
}

//******************************************************************
Float_t baseToyMaker::GetToyVariation(UInt_t itoy, SystematicBase* syst, UInt_t ipar){
  //******************************************************************
  (void)itoy;
  (void)ipar;
   
  if (!syst){
    return 0.;
  }

  if (_individualRandomGenerator){
    if      (syst->PDF() == SystematicBase::kUniform)  return _RandomGenerators[syst->GetIndex()].Uniform(0.,1.);
    else if (syst->PDF() == SystematicBase::kGaussian) return _RandomGenerators[syst->GetIndex()].Gaus(0.,1.);	
  }
  else{
    if      (syst->PDF() == SystematicBase::kUniform)  return _RandomGenerator.Uniform(0.,1.);
    else if (syst->PDF() == SystematicBase::kGaussian) return _RandomGenerator.Gaus(0.,1.);	
  }

  return 0.; 
}

