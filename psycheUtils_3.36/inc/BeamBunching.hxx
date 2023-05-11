#ifndef BeamBunching_h
#define BeamBunching_h

#include "BaseDataClasses.hxx"

class BeamBunching {

public:
  
  BeamBunching(){
    _nbunches = 0.;
    _rcut  = 4. * 15.;
    _lcut  = 4. * 15.;
  }
  BeamBunching(const std::string& filename){ReadBeamBunchStructure(filename);}
  
  virtual ~BeamBunching(){}

  /// Read the bunch structure for analysis usage. 
  void ReadBeamBunchStructure(const std::string& filename);

  /// Define the Bunch Period from the run number. 
  Int_t GetBunchPeriod(const AnaEventB& event); 

  /// Get the central time for bunch ibunch
  Float_t GetBunchCentralTime(const AnaEventB& event, Int_t ibunch); 

  /// Number of bunches in the run period for the current run
  UInt_t GetNBunches(const AnaEventB& event); 

  /// The run number for a given time
  virtual Int_t GetBunch(Float_t tTrack, Int_t run, bool isMC, bool cosmic_mode) const;
  
  
  /// Return  left cut used
  Float_t GetLCut() const{
    return _lcut;
  }
  
  /// Return right cut used
  Float_t GetRCut() const{
    return _rcut;
  }


    /// Set right cut centre + right_cut
  /// If sigma is set then the cut is _nsigmas*_sigma
  void SetRCut(Float_t rcut){
    _rcut = rcut;
  }
  
  /// Set left cut centre - left_cut
  /// If sigma is set then the cut is _nsigmas*_sigma
  void SetLCut(Float_t lcut){
    _lcut = lcut;
  }
  
protected:

  UInt_t _nbunches;

  std::vector<Float_t>               bunch_time_mc;    // Bunch times in MC 
  std::vector<std::vector<Float_t> > bunch_time_data;  // Bunch times in Data
  std::vector<std::pair<int,int> >   bunchrunperiod;   // Last  run in  Data period.  
  
  Float_t _lcut;
  
  Float_t _rcut;
  
};

#endif
