#ifndef ECalPhotonPileUpSystematics_h
#define ECalPhotonPileUpSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"
#include "FluxWeighting.hxx"

/// This is a normalization systematic. It takes into account the uncertainty on the 
/// probability to select a "fake" ECal-shower candidate used for pi-zero
/// tagging

class ECalPhotonPileUpSystematics: public EventWeightBase, public BinnedParams {
  public:

    ECalPhotonPileUpSystematics();  
    virtual ~ECalPhotonPileUpSystematics() {}

    /// Apply this systematic
    using EventWeightBase::ComputeWeight;
    Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box);
};


#endif
