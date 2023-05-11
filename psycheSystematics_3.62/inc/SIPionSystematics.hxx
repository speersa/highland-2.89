#ifndef SIPionSystematics_h
#define SIPionSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"
#include "PionInteractionSystematic.hxx"

const unsigned int NINTERACTIONS=200;
const unsigned int NMAXMOMBINS=201;

struct ExcludedWeights {
  int IntBin;
  std::set<unsigned int> momBins;
  
  ExcludedWeights(){
    IntBin = -1;
    momBins.clear();
  }
  
  void Clear(){
    IntBin = -1;
    momBins.clear();
  }


};



class SIPionSystematics: public EventWeightBase, public BinnedParams {
  public:

  SIPionSystematics();
  
  /// Constructor which allows to provide user`s manager for pion SI
  SIPionSystematics(PionSIManager*);
  
  virtual ~SIPionSystematics(); 
  
  /// Apply the systematic
  Weight_h ComputeWeight(const ToyExperiment&    , const AnaEventC&      , const ToyBoxB&){return 1;}
  Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel);

  /// Create the array of PionInteractionSystematic
  void InitializeSystBoxes(Int_t nsel, Int_t isel, Int_t nbranch, Int_t nevents);
 
  /// Delete the PionInteractionSystematic for this event
  void FinalizeEvent(const AnaEventC& event);
  
  
  /// Initilaize the systematics itself, basically the manager if it does not
  /// exist
  virtual void Initialize();
   
protected:
  
  /// Initialize the constructor
  void CtrInitialize();

  /// Fill the SystBox for this event, selection and branch
  void FillSystBox(const AnaEventC& event, const SelectionBase& sel, Int_t ibranch);
  
  /// Clear pion weight for toy
  void ClearPionWeightInfoToy(){
  
    if (_pionWeightInfoToy){
      delete _pionWeightInfoToy;
    }
    
    _pionWeightInfoToy = 0;
  }
  
  /// Retrieve pion interaction systematic given an index
  virtual PionInteractionSystematic* GetPionWeightInfo(const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel); 
    
 
  Float_t _xsec_data[NINTERACTIONS][NMAXMOMBINS];
  Float_t _err_data[NINTERACTIONS][NMAXMOMBINS];
  
  
  Float_t _xsec_mc[NINTERACTIONS][801]; // TO CHECK - DIFFERENT NUMBER OF BINS USED WRT DATA
  Float_t _err_mc[NINTERACTIONS][801]; // TO CHECK - DIFFERENT NUMBER OF BINS USED WRT DATA

  /// Pion SI systematic associated quantities. TODO: better way of handeling this
  PionInteractionSystematic** _pionWeightInfo;
   
  
  /// Pion SI associated quanities - toy based
  PionInteractionSystematic* _pionWeightInfoToy;
  
  /// A manager that grabs the needed data for systematics calculation
  PionSIManager* _pionSIManager;
  
  
  Int_t _interactionID[3];
  
  bool _initialized;
 
  
  /// A param to control whether to use toy or event based pion si info
  bool _useToyBasedPionSI;
  
  
  /// A param to control whether to use new treatement where MC-to-Data is done
  /// directly inside the syst
  bool _useMCtoDataOnTheFly;
  
  /// A vector of bins to exclude
  std::vector<ExcludedWeights> _excludedWeights;
  
  /// A function to check whether a certain interaction and mom bins should be
  /// excluded from the re-weighting
  bool CheckIsExcludedWeight(int intType, unsigned int momBin);
  
  /// Print excluded weights: interactions and mom bins
  void PrintExcludedWeights();
};

#endif
