#ifndef numuCCMultiPiProtonFGD2Selection_h
#define numuCCMultiPiProtonFGD2Selection_h

#include "numuCCMultiPiFGD2Selection.hxx"
#include "numuCCMultiPiProtonSelection.hxx"


class numuCCMultiPiProtonFGD2Selection: public numuCCMultiPiFGD2Selection{

public:
  numuCCMultiPiProtonFGD2Selection(bool forceBreak=true);
  virtual ~numuCCMultiPiProtonFGD2Selection(){}

  void DefineSteps();
  
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD2NuMuCC0Pi0Protons;}
  
  bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;

  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;
 
  Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  
  void SetDetectorFV(SubDetId_h det, Int_t ibranch=-1){
    numuCCMultiPiFGD2Selection::SetDetectorFV(det, ibranch);
    // Set to the selection that is used
    _numuCCMultiPiProtonSelection.SetDetectorFV(det, ibranch);
  }


protected:
  numuCCMultiPiProtonSelection _numuCCMultiPiProtonSelection;

};

class FillSummaryAction_numuCCMultiPiProtonFGD2: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_numuCCMultiPiProtonFGD2();}
};




#endif
