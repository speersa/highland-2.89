#ifndef FGDTrackEffSystematics_h
#define FGDTrackEffSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"


class FGDTrackEffSystematics: public EventWeightBase {
  public:

    FGDTrackEffSystematics(bool computecounters=false);
    virtual ~FGDTrackEffSystematics() {
      if (_fgd1) delete _fgd1; _fgd1 = NULL; 
      if (_fgd2) delete _fgd2; _fgd2 = NULL; 
    }

  using EventWeightBase::ComputeWeight;
  Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box);

  void Initialize();
  
protected:

  /// Is this true track relevant for this systematic ?
  bool IsRelevantTrueObject(const AnaEventC& event, const AnaTrueObjectC& trueTrack) const;
  
protected:
  bool  _computecounters;
  
public:
  //TODO
  
  BinnedParams* _fgd1;
  BinnedParams* _fgd2;
};

#endif
