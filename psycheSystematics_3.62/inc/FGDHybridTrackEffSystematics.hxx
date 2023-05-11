#ifndef FGDHybridTrackEffSystematics_h
#define FGDHybridTrackEffSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"


class FGDHybridTrackEffSystematics: public EventWeightBase {
  public:

    FGDHybridTrackEffSystematics(bool computecounters=false);
    virtual ~FGDHybridTrackEffSystematics() {
      if (_fgd1_fhc) delete _fgd1_fhc; _fgd1_fhc = NULL; 
      if (_fgd2_fhc) delete _fgd2_fhc; _fgd2_fhc = NULL;
      if (_fgd1_rhc) delete _fgd1_rhc; _fgd1_rhc = NULL; 
      if (_fgd2_rhc) delete _fgd2_rhc; _fgd2_rhc = NULL; 

    }

    using EventWeightBase::ComputeWeight;
    Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box);
    
    void Initialize();
    
    void Print(Option_t *option="") const;
  
     
protected:

  /// Is this true track relevant for this systematic ?
  bool IsRelevantTrueObject(const AnaEventC& event, const AnaTrueObjectC& trueTrack) const;
  
  
  /// Return the proper binned params to be used 
  BinnedParams* GetBinnedParams(const AnaTrackB& track, const AnaEventC& event, const SubDetId_h det);

protected:
  bool  _computecounters;

public:
  //TODO

  BinnedParams* _fgd1_fhc;
  BinnedParams* _fgd2_fhc;
  BinnedParams* _fgd1_rhc;
  BinnedParams* _fgd2_rhc;
 
};

#endif
