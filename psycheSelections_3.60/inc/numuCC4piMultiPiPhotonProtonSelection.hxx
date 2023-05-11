#ifndef numuCC4piMultiPiPhotonProtonSelection_h
#define numuCC4piMultiPiPhotonProtonSelection_h

#include "numuCCMultiPiProtonSelection.hxx"
#include "numuCC4piMultiPiSelection.hxx"
#include "numuCCMultiPiPhotonProtonSelection.hxx"


class numuCC4piMultiPiPhotonProtonSelection: public numuCC4piMultiPiSelection{

public:
  numuCC4piMultiPiPhotonProtonSelection(bool forceBreak=true): numuCC4piMultiPiSelection(forceBreak){
  }
  virtual ~numuCC4piMultiPiPhotonProtonSelection(){}
  //---- These are mandatory functions
  void DefineSteps();
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  virtual void DefineDetectorFV(){
    SetDetectorFV(SubDetId::kFGD1);
    _numuCCSelection.SetDetectorFV(SubDetId::kFGD1);
    };
  //This selection is to be used in BANFF so this function is mandatory.
  // This does not involve any specific branch so no overloading.
  // bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  // bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;
  

  // void InitializeEvent(AnaEventC& event);
  // Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  // Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;

  
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCC0PiFwd;}

protected:
  numuCCSelection _numuCCSelection;
  numuCCMultiPiPhotonProtonSelection _numuCCMultiPiPhotonProtonSelection;
};


  class FillSummaryAction_numuCC4piMultiPiPhotonProton: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FillSummaryAction_numuCC4piMultiPiPhotonProton();}
  };
namespace numuCC4piMultiPi{
  class PhotonCut: public StepBase{
  public:
    using StepBase::Apply;
    PhotonCut(){};
    bool      Apply    (AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new PhotonCut();}
  };
}
#endif
