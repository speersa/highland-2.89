#ifndef baseToyMaker_h
#define baseToyMaker_h

#include "ToyMaker.hxx"
#include "BinnedPDF.hxx"
#include "TRandom3.h"

/// Creates ToyExperiments

class baseToyMaker: public ToyMaker{
  
public:
  
  /// Create the Toy experiment 
  baseToyMaker(UInt_t seed);
  
  /// Everyone should have a destructor.
  virtual ~baseToyMaker() {}

  /// Fills the Toy Experiment with a given index
  void FillToyExperiment(ToyExperiment& toy);

  /// returns the random seed
  UInt_t GetSeed() const {return _seed;}

  /// Use a random generator for each systematic
  void SetIndividualRandomGenerator(bool ok){ _individualRandomGenerator=ok;}
  

  ///  A virtiual method to allow one to provide a variation based on the toy number,
  /// systematic and a systematic parameter number
  virtual Float_t GetToyVariation(UInt_t itoy, SystematicBase* syst, UInt_t iparam);  

protected:

  // A binned PDF
  BinnedPDF* _binnedPDF;       

  /// A random generator that can be used to generate throws.
  TRandom3 _RandomGenerator;

  TRandom3 _RandomGenerators[NMAXSYSTEMATICS];

  /// The random seed used
  UInt_t _seed;

  UInt_t _seeds[NMAXSYSTEMATICS];

  // Use a random generator for each systematic
  bool _individualRandomGenerator;

};

#endif
