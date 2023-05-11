#include "SIKaonSystematics.hxx"
#include "AnalysisUtils.hxx"
#include "MultiThread.hxx"
#include "SystIdHighland.hxx"
#include <algorithm>

//#define DEBUG

//********************************************************************
SIKaonSystematics::SIKaonSystematics():EventWeightBase(), BinnedParams(){
  //********************************************************************
  
  _initialized = false;
 
  Initialize();

  // Whether to re-weight the cross-sections (i.e. event probability) to some reference cross-section data
  _kInfoManager.GetPropagator()->SetComputeReWeightStatus((bool)ND::params().GetParameterI("highlandSystematics.KaonSI.ReWeight"));


  SetNParameters(_kInfoManager.GetPropagator()->GetParticlePDGs().size() * _kInfoManager.GetPropagator()->GetInteractionTypes().size());

  // Fill the map
  std::set<ParticleId::PdgEnum>::const_iterator      iter1 = _kInfoManager.GetPropagator()->GetParticlePDGs().begin();
  std::set<si_syst::InteractionType>::const_iterator iter2 = _kInfoManager.GetPropagator()->GetInteractionTypes().begin();

  unsigned int count = 0;
  for (; iter1 != _kInfoManager.GetPropagator()->GetParticlePDGs().end(); iter1++){
    for (; iter2 != _kInfoManager.GetPropagator()->GetInteractionTypes().end(); iter2++){
      _params[std::make_pair(*iter1, *iter2)] = count; 
      count++;
    }

  }

  _KaonInteractionsInfo = NULL;
  
}

//********************************************************************
SIKaonSystematics::~SIKaonSystematics(){
  //********************************************************************

  if (_KaonInteractionsInfo){
    for (Int_t k= 0; k<_nevents; k++){
      if(_KaonInteractionsInfo[k])
        delete _KaonInteractionsInfo[k];   
      _KaonInteractionsInfo[k] = NULL;
    }
  }

  delete [] _KaonInteractionsInfo;
  

}

//********************************************************************
void SIKaonSystematics::Initialize(){
  //********************************************************************

  if (_initialized)
    return;
    
  // Set the proper propagator 
  _kInfoManager.SetPropagator(new kaon_si::KaonSIPropagator());
  
  _initialized = true;

}


//********************************************************************
Weight_h SIKaonSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel){
  //********************************************************************

  (void)box;
  
  Weight_h eventWeightFinal;
  
  Float_t eventWeight   = 1.;

  Float_t totalReWeight = 1.;

  Int_t uniqueID = 0;

#ifdef MULTITHREAD
  uniqueID = event.UniqueID;
#else
  (void)event;
#endif
  
  
  // Retrieve the kaon secondary interaction information for the event  
  si_syst::SISystInput& kaonSI = *_KaonInteractionsInfo[uniqueID];

#ifdef DEBUG
  std::cout << " ===== " << std::endl;
  std::cout << " SIKaonSystematics::ComputeWeight" << std::endl;
  std::cout << "nKaons = " << kaonSI.nParticles << std::endl;
#endif

  
   
  // Only bother doing anything if there is at least one kaon in the event.
  if (kaonSI.nParticles == 0) return eventWeight;

  // Loop over the kaons
  for (int i = 0; i < kaonSI.nParticles; i++){


    // Weight for survivial probability
    Float_t survWeight_tmp = 0.;

    // Weight for interactions
    Float_t intWeight_tmp = 1.;   

    // Fine-tuning on whether a track is relevant for the selection
    if (!sel.IsRelevantTrueObjectForSystematicInToy(event, box, const_cast<AnaTrueParticleB*>(kaonSI.Particles[i].trueTrack), 
          SystIdHighland::kSIKaon, box.SuccessfulBranch)){ 
 
#ifdef DEBUG
      std::cout << " Not relevant object  " << std::endl;
#endif      
      continue;
    
    
    }
   
    // Start with survival probability, consider the steps available for each kaon

    size_t nSteps = kaonSI.Particles[i].propSteps.size();

#ifdef DEBUG
    std::cout << "nSteps = " << nSteps << std::endl;          
#endif

    for (size_t ns = 0; ns < nSteps; ns++){
      // For each step loop over the interactions
      size_t nInts = kaonSI.Particles[i].propSteps[ns].size();
      for (size_t nint = 0; nint < nInts; nint++){
        // Get the variation index depending on particle and interaction type -->ToDo
        // ToDo: add interaction type into the cross-section data
        Float_t xsec_tmp = kaonSI.Particles[i].propSteps[ns][nint].XSec + 
            kaonSI.Particles[i].propSteps[ns][nint].XSecErr * toy.GetToyVariations(_index)->Variations[0];
        survWeight_tmp += std::max<Double_t>(xsec_tmp, 0.) - 
          kaonSI.Particles[i].propSteps[ns][nint].XSec;
      }
    }


    // Get the variation index depending on particle and interaction type  
    Float_t var = 0.; // variation
    
    if (kaonSI.Particles[i].intType != si_syst::kNoInteraction){ 

    
      unsigned int index = _params[std::make_pair(
          static_cast<ParticleId::PdgEnum>(kaonSI.Particles[i].trueTrack->PDG), 
          kaonSI.Particles[i].intType
          )];
    
      var = toy.GetToyVariations(_index)->Variations[index];
    }
    
    
    if (kaonSI.Particles[i].XSecData.XSec != 0){
      intWeight_tmp *= 1 + kaonSI.Particles[i].XSecData.XSecErr/(kaonSI.Particles[i].XSecData.XSec) * var;
    }
    

    totalReWeight *= kaonSI.Particles[i].Weight;

#ifdef DEBUG
    std::cout << " ===== Particle weight ===== " << std::endl;  
    std::cout << "survWeight        \t= " << survWeight_tmp                << std::endl;
    std::cout << "exp(-survWeight)  \t= " << exp(-survWeight_tmp)          << std::endl;
    std::cout << "intWeight         \t= " << intWeight_tmp                 << std::endl;
    std::cout << "ReWeight          \t= " << kaonSI.Particles[i].Weight << std::endl;
    std::cout << " ========== " << std::endl;  
#endif

    Float_t factor = exp(-survWeight_tmp) * intWeight_tmp;
    if (factor == 0 || !TMath::Finite(factor) || factor != factor)
      factor = 1.; 

    eventWeight *= factor;

  }//loop over kaons

#ifdef DEBUG
  std::cout << " ===== Total weight ===== " << std::endl;  
  std::cout << " eventWeight    \t= " << eventWeight   << std::endl;
  std::cout << " totalReWeight  \t= " << totalReWeight << std::endl;
  std::cout << " ========== " << std::endl;  
#endif



  if (eventWeight == 0 || !TMath::Finite(eventWeight) || eventWeight != eventWeight)
    eventWeight = 1.; 

#ifdef DEBUG
  std::cout << " eventWeight    \t= " << eventWeight                  << std::endl;
  std::cout << " totalReWeight  \t= " << totalReWeight                << std::endl;
  std::cout << " finalWeightt   \t= " << totalReWeight * eventWeight  << std::endl;
  std::cout << " =====  " << std::endl;
#endif

  eventWeightFinal.Correction = totalReWeight;
  eventWeightFinal.Systematic = totalReWeight * eventWeight;
  
  return eventWeightFinal;
}

//********************************************************************
void SIKaonSystematics::FillSystBox(const AnaEventC& eventC, const SelectionBase& sel, Int_t ibranch){
  //********************************************************************

  Int_t uniqueID = 0;    
#ifdef MULTITHREAD
  uniqueID = event.UniqueID;
#endif

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventC); 

  // TODO:Need a better way of doing this
  AnaTrueParticleB* allTrajInBunch[NMAXTRUEPARTICLES];
  int count = 0;
  count = anaUtils::GetAllTrajInBunch(event, allTrajInBunch);
  if((UInt_t)count > NMAXTRUEPARTICLES) count = NMAXTRUEPARTICLES;

  // Compute Kaon weight info needed by KaonSISystematics (TODO, only when this systematic is enabled)
  //  if (KaonWeightInfo) delete KaonWeightInfo;

 
  _KaonInteractionsInfo[uniqueID] = _kInfoManager.CollectParticleInteractions(allTrajInBunch, count,
      static_cast<SubDetId::SubDetEnum>(sel.GetDetectorFV(ibranch)));

}


//********************************************************************
void SIKaonSystematics::InitializeSystBoxes(Int_t nsel, Int_t isel, Int_t nbranches, Int_t nevents){
  //********************************************************************
  
  //  TODO: This is a temporary solution to make this work with multithreading. Instead we would need a derived SystBox

  // Although the SystBox is actually not used we need to create it because SystematicBase::InitializeEvent uses it
  EventWeightBase::InitializeSystBoxes(nsel,isel,nbranches,nevents);

  // Since this is called for several selections use for the moment a single one for all selections
  if (_KaonInteractionsInfo) return;

#ifndef MULTITHREAD
  nevents=1;
#endif

  _KaonInteractionsInfo = new si_syst::SISystInput*[nevents];
  _nevents = nevents;
  for (Int_t k = 0; k < nevents; k++)
    _KaonInteractionsInfo[k] = NULL;

}





//********************************************************************
void SIKaonSystematics::FinalizeEvent(const AnaEventC& event){
  //********************************************************************

  //  TODO: This is a temporary solution to make this work with multithreading. Instead we would need a derived SystBox

  // Although the SystBox is actually not used we need to create it because SystematicBase::FinalizeEvent uses it
  EventWeightBase::FinalizeEvent(event);

  Int_t uniqueID = 0;
#ifdef MULTITHREAD
  uniqueID = event.UniqueID;
#endif

  if (_KaonInteractionsInfo[uniqueID])
    delete _KaonInteractionsInfo[uniqueID];
  _KaonInteractionsInfo[uniqueID] = NULL;

}
