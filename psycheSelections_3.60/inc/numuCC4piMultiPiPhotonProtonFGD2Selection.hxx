#ifndef numuCC4piMultiPiPhotonProtonFGD2Selection_h
#define numuCC4piMultiPiPhotonProtonFGD2Selection_h

#include "numuCC4piMultiPiPhotonProtonSelection.hxx"
#include "numuCCMultiPiPhotonProtonFGD2Selection.hxx"


class numuCC4piMultiPiPhotonProtonFGD2Selection: public numuCC4piMultiPiPhotonProtonSelection{

public:
  numuCC4piMultiPiPhotonProtonFGD2Selection(bool forceBreak=true): numuCC4piMultiPiPhotonProtonSelection(forceBreak){
  }
  virtual ~numuCC4piMultiPiPhotonProtonFGD2Selection(){}
  //---- These are mandatory functions
  void DefineSteps();
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  virtual void DefineDetectorFV(){
    std::cout << "Setting FGD2 Detector FV!" << std::endl;
    SetDetectorFV(SubDetId::kFGD2);
    _numuCCSelection.SetDetectorFV(SubDetId::kFGD2);
    };
  //This selection is to be used in BANFF so this function is mandatory.
  // This does not involve any specific branch so no overloading.
  // bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  // bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;
  // bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;

  // void InitializeEvent(AnaEventC& event);
  // Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  // Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;

  
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCC0PiFwd;}
protected:
  numuCC4piMultiPiPhotonProtonSelection _numuCC4piMultiPiPhotonProtonSelection;

};


  class FillSummaryAction_numuCC4piMultiPiPhotonProtonFGD2: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FillSummaryAction_numuCC4piMultiPiPhotonProton();}
  };



#endif
