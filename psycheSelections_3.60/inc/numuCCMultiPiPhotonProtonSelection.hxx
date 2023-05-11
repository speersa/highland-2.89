#ifndef numuCCMultiPiPhotonProtonSelection_h
#define numuCCMultiPiPhotonProtonSelection_h

#include "numuCCMultiPiPhotonSelection.hxx"
#include "numuCCMultiPiProtonSelection.hxx"

class numuCCMultiPiPhotonProtonSelection: public numuCCMultiPiPhotonSelection{

public:
  numuCCMultiPiPhotonProtonSelection(bool forceBreak=true) : numuCCMultiPiPhotonSelection(forceBreak){}

  virtual ~numuCCMultiPiPhotonProtonSelection(){}

  void DefineSteps();

  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCCPhoton;}

  
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;

};


class FillSummaryAction_numuCCMultiPiPhotonProton: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_numuCCMultiPiPhotonProton();}
};

#endif
