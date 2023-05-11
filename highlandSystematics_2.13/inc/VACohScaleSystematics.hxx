#ifndef VACohScaleSystematics_h
#define VACohScaleSystematics_h

#include "ND280AnalysisUtils.hxx"
#include "EventVariationBase.hxx"
#include "BinnedParams.hxx"
#include <string>

class VACohScaleSystematics: public EventVariationBase, public BinnedParams {
public:
    VACohScaleSystematics();
    virtual ~VACohScaleSystematics() {}
    /// Apply this systematic
  	virtual void Apply(const ToyExperiment& toy, AnaEventC& event);
    /// Undo  the systematic variations done by ApplyVariation. This is faster tha reseting the full Spill
  	virtual bool UndoSystematic(AnaEventC& event);

protected:
    /// Is this track relevant for this systematic ?
  	Int_t GetRelevantRecObjectGroups(const SelectionBase& sel, Int_t* IDs) const;
};
#endif
