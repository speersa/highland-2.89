#ifndef ToFCorrection_h
#define ToFCorrection_h

#include "CorrectionBase.hxx"
#include "DataClasses.hxx"
#include "ToFSenseCorrector.hxx"

/// This correction smears and shifts the MC ToF to match data
/// There is also an option to flip track according to ToF
class TRandom;


class ToFCorrection: public CorrectionBase {
public:
 
  enum RunIndex{
    kFHC = 0, 
    kRHC,
    kFHCRun8, 
    kRunIndexCounter
  };

  enum CorrTopology{

    kP0D_FGD1_ToF_MC_TrueFwd_Track = 0,                 
    kP0D_FGD1_ToF_MC_TrueBwd_Track,                
    kP0D_FGD1_ToF_MC_Sand_Track,                       

    kP0D_FGD1_ToF_MC_TrueFwd_Shower,                
    kP0D_FGD1_ToF_MC_TrueBwd_Shower,                
    kP0D_FGD1_ToF_MC_Sand_Shower,                      

    kFGD1_FGD2_ToF_MC_TrueFwd,                      
    kFGD1_FGD2_ToF_MC_TrueBwd,                      
    kFGD1_FGD2_ToF_MC_Sand,                            

    kECal_FGD1_ToF_MC_LAStartFgd_TrueFwd_Shower,    
    kECal_FGD1_ToF_MC_LAStartFgd_TrueBwd_Shower,    
    kECal_FGD1_ToF_MC_LAStartFgd_TrueFwd_Track,     
    kECal_FGD1_ToF_MC_LAStartFgd_TrueBwd_Track,     
    kECal_FGD1_ToF_MC_LAStartFgd_Sand_Shower,          
    kECal_FGD1_ToF_MC_LAStartFgd_Sand_Track,           

    kECal_FGD1_ToF_MC_LAEndFgd_TrueFwd_Shower,      
    kECal_FGD1_ToF_MC_LAEndFgd_TrueBwd_Shower,      
    kECal_FGD1_ToF_MC_LAEndFgd_TrueFwd_Track,       
    kECal_FGD1_ToF_MC_LAEndFgd_TrueBwd_Track, // low stat for sand     

    kECal_FGD1_ToF_MC_HAStartFgd_TrueFwd_Shower,    
    kECal_FGD1_ToF_MC_HAStartFgd_TrueBwd_Shower,    
    kECal_FGD1_ToF_MC_HAStartFgd_TrueFwd_Track,     
    kECal_FGD1_ToF_MC_HAStartFgd_TrueBwd_Track,     
    kECal_FGD1_ToF_MC_HAStartFgd_Sand_Shower,          
    kECal_FGD1_ToF_MC_HAStartFgd_Sand_Track,           

    kECal_FGD1_ToF_MC_HAEndFgd_TrueFwd_Shower,      
    kECal_FGD1_ToF_MC_HAEndFgd_TrueBwd_Shower,      
    kECal_FGD1_ToF_MC_HAEndFgd_TrueFwd_Track,       
    kECal_FGD1_ToF_MC_HAEndFgd_TrueBwd_Track,       
    kECal_FGD1_ToF_MC_HAEndFgd_Sand_Shower,            
    kECal_FGD1_ToF_MC_HAEndFgd_Sand_Track,             


    kECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Track,     
    kECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Track,     
    kECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Shower,    
    kECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Shower,    
    kECal_FGD2_ToF_MC_LAStartFgd_Sand_Track,        
    kECal_FGD2_ToF_MC_LAStartFgd_Sand_Shower,       

    kECal_FGD2_ToF_MC_LAEndFgd_TrueFwd_Track,       
    kECal_FGD2_ToF_MC_LAEndFgd_TrueBwd_Track,       
    kECal_FGD2_ToF_MC_LAEndFgd_TrueFwd_Shower,      
    kECal_FGD2_ToF_MC_LAEndFgd_TrueBwd_Shower,      
    kECal_FGD2_ToF_MC_LAEndFgd_Sand_Track,          
    kECal_FGD2_ToF_MC_LAEndFgd_Sand_Shower,         

    kECal_FGD2_ToF_MC_HAStartFgd_TrueFwd_Track,     
    kECal_FGD2_ToF_MC_HAStartFgd_TrueBwd_Track,     
    kECal_FGD2_ToF_MC_HAStartFgd_TrueFwd_Shower,    
    kECal_FGD2_ToF_MC_HAStartFgd_TrueBwd_Shower,    
    kECal_FGD2_ToF_MC_HAStartFgd_Sand_Track,        
    kECal_FGD2_ToF_MC_HAStartFgd_Sand_Shower,       

    kECal_FGD2_ToF_MC_HAEndFgd_TrueFwd_Track,       
    kECal_FGD2_ToF_MC_HAEndFgd_TrueBwd_Track,       
    kECal_FGD2_ToF_MC_HAEndFgd_TrueFwd_Shower,      
    kECal_FGD2_ToF_MC_HAEndFgd_TrueBwd_Shower,      
    kECal_FGD2_ToF_MC_HAEndFgd_Sand_Track,   //  low statistics      

    kDSECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Track,   
    kDSECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Track,   
    kDSECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Shower,  
    kDSECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Shower,  
    kDSECal_FGD2_ToF_MC_LAStartFgd_Sand_Track,     
    kDSECal_FGD2_ToF_MC_LAStartFgd_Sand_Shower,     

    kFGD1_FGD2_ToF_MC_NoStopFGD1_TrueFwd,           
    kFGD1_FGD2_ToF_MC_NoStopFGD1_TrueBwd,           
    kFGD1_FGD2_ToF_MC_NoStopFGD1_Sand,             

    kCorrTopoCounter  // will use it for array counter...

  };




  struct CorrParams{
    CorrParams(){
      Mean = 0.;
      Sigma = 0.; 
    }

    CorrParams(Float_t mean_in, Float_t sigma_in){
      Mean  = mean_in;
      Sigma = sigma_in;
    }

    Float_t Mean;
    Float_t Sigma;
  }; 

  ToFCorrection();

  virtual ~ToFCorrection();

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
  void FillFromMap(CorrTopology topo, std::string name); 

  /// Apply the smearing given the value to vary and the topology to be used
  void ApplyCorrection(Float_t& tof_value, CorrTopology topo) const; 

  /// A pointer to the vector of the correction values for topologies
  std::vector<CorrParams>* _params;
  
  /// A vector of vectors to store run-dependent correction values for
  //topologies
  std::vector<std::vector<CorrParams> > _params_vect;
  
  /// A vector to store names of the topologies
  std::vector<std::string> _topo_names;

  /// An utility map to read from data file
  std::map<std::string, CorrParams> _params_map;

  /// Apply MC ToF smearing
  void ApplyToFSmear(AnaTrack& track, ToFSenseCorrector::ToFTopology topo, bool IsSandMC) const;

  /// Initialze random generator
  void InitializeRandomGenerator();

  /// A random generator that can be used to generate throws.
  TRandom* _RandomGenerator;

};

#endif
