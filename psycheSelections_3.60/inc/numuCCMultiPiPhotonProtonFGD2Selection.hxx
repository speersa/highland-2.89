#ifndef numuCCMultiPiPhotonProtonFGD2Selection_h
#define numuCCMultiPiPhotonProtonFGD2Selection_h

#include "numuCCMultiPiPhotonFGD2Selection.hxx"
#include "numuCCMultiPiProtonFGD2Selection.hxx"
#include "numuCCMultiPiPhotonProtonSelection.hxx"

class numuCCMultiPiPhotonProtonFGD2Selection: public numuCCMultiPiPhotonFGD2Selection{

public:
  numuCCMultiPiPhotonProtonFGD2Selection(bool forceBreak=true) : numuCCMultiPiPhotonFGD2Selection(forceBreak){
    _numuCCMultiPiPhotonProtonSelection.Initialize();
  }
  
  virtual ~numuCCMultiPiPhotonProtonFGD2Selection(){}

  void DefineSteps();
  
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD2NuMuCCPhoton;}

  void SetDetectorFV(SubDetId_h det, Int_t ibranch=-1){
    numuCCMultiPiPhotonFGD2Selection::SetDetectorFV(det, ibranch);
    // Set to the selection that is used
    _numuCCMultiPiPhotonProtonSelection.SetDetectorFV(det, ibranch);
  }

  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;


protected:
  numuCCMultiPiPhotonProtonSelection _numuCCMultiPiPhotonProtonSelection;
  
};


class FillSummaryAction_numuCCMultiPiPhotonProtonFGD2: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_numuCCMultiPiPhotonFGD2();}
};



#endif
