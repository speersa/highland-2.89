#ifndef ToFTimeSlipCorrection_h
#define ToFTimeSlipCorrection_h

#include "CorrectionBase.hxx"
#include "DataClasses.hxx"
#include "ToFSenseCorrector.hxx"

/// This correction smears and shifts the MC ToF to match data
/// There is also an option to flip track according to ToF
class TRandom;


class ToFTimeSlipCorrection: public CorrectionBase {
public:
 
  enum RunIndex{
    kFHC = 0, 
    kRHC,
    kFHCRun8, 
    kRunIndexCounter
  };


  struct CorrParams{
    CorrParams(){
      Corr1 = 0.;
      Corr2 = 0.; 
    }

    CorrParams(Float_t corr1_in, Float_t corr2_in){
      Corr1  = corr1_in;
      Corr2  = corr2_in;
    }

    Float_t Corr1;
    Float_t Corr2;
  }; 

  ToFTimeSlipCorrection();

  virtual ~ToFTimeSlipCorrection();

  /// Apply the correction to all relevant tracks 
  void Apply(AnaSpillC& spill);

  /// The only thing we allow for the generator is to get the seed
  UInt_t GetRandomSeed() const; 

  /// And change the seed
  void SetRandomSeed(UInt_t seed);

  
  /// Set a topology vector to be used given a spill
  void SetTopoVector(AnaSpillC& spillBB);
  
private:
  
  
  /// Get run index given a spill
  size_t GetRunIndex(AnaSpillC& spillBB) const;
  
  /// Set a topology vector given an index
  void SetTopoVector(const size_t& index);
  

  /// Fill topologies` corr params given an index and a file 
  void FillTopoParams(const size_t& index, const std::string& filename, 
      const std::string& extension);

  /// Dump the parameters
  void Print(Option_t *option="") const;

  /// Fill value utility
  void FillFromMap(ToFSenseCorrector::ToFTopology topo, std::string name); 

  /// Apply the smearing given the value to vary and the topology to be used
  void ApplyCorrection(Float_t& tof_value, Int_t& flag, ToFSenseCorrector::ToFTopology topo) const; 

  /// A pointer to the vector of the correction values for topologies
  std::vector<CorrParams>* _params;
  
  /// A vector of random values for topologies
  std::vector<CorrParams> _rndm_inputs;
  
  /// A vector of vectors to store run-dependent correction values for
  //topologies
  std::vector<std::vector<CorrParams> > _params_vect;
  
  /// A vector to store names of the topologies
  std::vector<std::string> _topo_names;

  /// An utility map to read from data file
  std::map<std::string, CorrParams> _params_map;

  /// Apply MC ToF smearing
  void ApplyToFTimeSlip(AnaTrack& track, ToFSenseCorrector::ToFTopology topo) const;

  /// Initialze random generator
  void InitializeRandomGenerator();
  
  /// Set rndm values
  void SetRandomValues();

  /// A random generator that can be used to generate throws.
  TRandom* _RandomGenerator;

};

#endif
