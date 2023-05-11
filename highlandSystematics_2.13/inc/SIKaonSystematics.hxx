#ifndef SIKaonSystematics_h
#define SIKaonSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"
#include "KaonInteractionSystematic.hxx"

/*!
 *  A class to propagate systematics for kaon secondary interactions (uncertainites in GEANT4 model)
 *  uses KaonInteractionSystematic to collect the inputs (event based): kaons with their probabilities
 *  to travel through the detector (volume of interset, VOI) media and corresponding interactions (if occured in VOI)
 *  This class will take care of modifying the probabilities based on toy weights
 *  
 */

class SIKaonSystematics: public EventWeightBase, public BinnedParams {
  public:

  SIKaonSystematics();
  
  virtual ~SIKaonSystematics();
  
    /// Apply the systematic
  Weight_h ComputeWeight(const ToyExperiment&    , const AnaEventC&      , const ToyBoxB&){return 1;}
  Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel);

  
  /// Create the array of ProtonInteractionSystematic
  void InitializeSystBoxes(Int_t nsel, Int_t isel, Int_t nbranch, Int_t nevents);
 
  /// Delete the ProtonInteractionSystematic for this event
  void FinalizeEvent(const AnaEventC& event);

  /// Initilaize the systematics itself, basically the manager
  virtual void Initialize();

protected:
 
  /// Fill the SystBox for this event, selection and branch
  void FillSystBox(const AnaEventC& event, const SelectionBase& sel, Int_t ibranch);
 
protected:
  
  
  Int_t _nevents;
  
  /// Manager to collect kaon interactions
  si_syst::ParticleSIManager _kInfoManager;
  si_syst::SISystInput**     _KaonInteractionsInfo;
  
  /// The correspondence between particle, interaction and variartion param
  std::map<std::pair<ParticleId::PdgEnum, si_syst::InteractionType>, unsigned int> _params; 
   
  bool _initialized;
};

#endif
