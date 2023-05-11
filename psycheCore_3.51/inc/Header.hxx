#ifndef Header_hxx
#define Header_hxx

#include "CoreDataClasses.hxx"
#include "TChain.h" 

/// This class handles POT info, SoftwareVersion and IsMC

/// Enum to define different POT calculated
enum POTDef{
  kNoCut = 0,
  // Bad beam
  kBadBeam, 
  // Bad ND280
  kBadND280, 
  // Bad ND280 time quality
  kBadND280Time, 
  // Good beam, good ND280
  kGoodBeamGoodND280, 
  // Good beam, good ND280 time
  kGoodBeamGoodND280Time, 
  // Various currents, here apply good beam and good ND280/ND280 time quality
  k0KA,
  k200KA, 
  k250KA, 
  km250KA, 
  kOtherKA, 
  k250KA_ND280Time, 
  km250KA_ND280Time,
  kPOTDefCounter
};



/// Enum for spill counting, should probably use the same as for POT
enum SpillDef{
  kSpillNoCut = 0, 
  kSpillBadBeam,               
  kSpillBadND280,              
  kSpillBadND280Time,          
  kSpillGoodBeamGoodND280,     
  kSpillGoodBeamGoodND280Time, 
  kSpillDefCounter
};


//-------------------------------------------------------------------
class Header{
public :


  /// constructor
  Header(POTDef def = kGoodBeamGoodND280);

  virtual ~Header(){}

  /// Record the POT for the current spill, based on information in the AnaBeam
  /// member of the current AnaSpill.
  void IncrementPOTBySpill(const AnaSpillC& spill);

  /// Directly increment the good POT. Use this for MC files, which don't have
  /// beam information.
  void IncrementPOTByFile(Double_t pot, bool bySpillPOT=true);

  /// Read the "header" tree from the given file, but reset POT counting first
  void ReadHeader(const std::string& file);
  void ReadHeader(TTree* tree);

  /// Read the "header" tree from the given file and increment the existing POT counting
  bool AddHeader(const std::string& file, bool bySpillPOT=false);
  bool AddHeader(TTree* tree, bool bySpillPOT=false);

  /// This is the method used externaly.
  Double_t GetPOT() { return GetPOT(_pot_def); }

  /// This is the method used externaly. It corresponds to POT that passed beam and ND280 quality cuts.
  Int_t GetNSpills() { return GetNSpills(_spill_def); }

  
  /// Get POT given a def
  Double_t GetPOT(POTDef def);

  /// Get spill given a def
  Int_t GetNSpills(SpillDef def);
  
  
  /// Get the total recorded POT counted per file
  Double_t GetPOTCountedPerFile() { return _POT_CountedPerFile; }

  /// Get pot counter
  Int_t GetPOTDefCounter() {return _pot_def_counter;}
 
  /// Get spill counter
  Int_t GetSpillDefCounter() {return _spill_def_counter;} 
  
  const Int_t* GetSpillInfo(){return _SpillInfo;}
  
  const Double_t* GetPOTInfo(){return _POTInfo;}
  
  /// Print the POT information.
  void DumpPOT();

  /// Reset all the information in the header
  void Reset();

  /// Set the Data/MC mode
  bool SetIsMC(bool isMC);

  /// returns the Data/MC mode
  bool GetIsMC() const{return _IsMC;}

  /// Set the software version
  bool SetSoftwareVersion(const std::string& ver);
  
  /// Returns the software version
  const std::string& GetSoftwareVersion(){return _SoftwareVersion;}
  
  /// Set the pot counting
  void SetPOTDef(POTDef def);
  
  POTDef GetPOTDef(){
    return _pot_def;
  }

 public:

  /// POT info
  Double_t _POT_CountedPerFile;
  Double_t _POT_NoCut;
  Double_t _POT_BadBeam;
  Double_t _POT_BadND280;
  Double_t _POT_GoodBeamGoodND280;
  Double_t _POT_0KA;
  Double_t _POT_200KA;
  Double_t _POT_250KA;
  Double_t _POT_m250KA;
  Double_t _POT_OtherKA;
  
  Double_t _POTInfo[kPOTDefCounter];

  /// Spill info
  Int_t _Spill_NoCut;
  Int_t _Spill_BadBeam;
  Int_t _Spill_BadND280;
  Int_t _Spill_GoodBeamGoodND280;
  
  Int_t _SpillInfo[kSpillDefCounter];
  
  /// data or MC mode 
  bool _IsMC;

  /// The software version used to create the original oaAnalysis file of the last input file
  std::string _SoftwareVersion;

  /// iternal variable that tell us whether a file has been added previously
  bool _isFirstFile; //!
  
  Int_t _pot_def_counter;
  Int_t _spill_def_counter;
  POTDef _pot_def; //!
  SpillDef _spill_def; //!
  
};

#endif


