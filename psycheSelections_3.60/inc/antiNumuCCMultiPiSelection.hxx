#ifndef antiNumuCCMultiPiSelection_h
#define antiNumuCCMultiPiSelection_h

#include "SelectionBase.hxx"
#include "antiNumuCCSelection.hxx"
#include "numuCCMultiPiSelection.hxx"



class antiNumuCCMultiPiSelection: public SelectionBase{
public:
  antiNumuCCMultiPiSelection(bool forceBreak=true);
  virtual ~antiNumuCCMultiPiSelection(){}

  //---- These are mandatory functions
  void DefineSteps();
  void DefineDetectorFV();
  
  ToyBoxB* MakeToyBox(); 
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD1AntiNuMuCC0Pi;}
  bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  void InitializeEvent(AnaEventC& event);
  bool CheckRedoSelection(const AnaEventC& event, const ToyBoxB& PreviousToyBox, Int_t& redoFromStep);
   
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;
  
  Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;    
  Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
 
  void SetDetectorFV(SubDetId_h det, Int_t ibranch=-1){
    SelectionBase::SetDetectorFV(det, ibranch);
    // Set to the selection that are used
    _antiNumuCCSelection.SetDetectorFV(det, ibranch); 
    _numuCCMultiPiSelection.SetDetectorFV(det, ibranch); 
  }



protected:
  antiNumuCCSelection _antiNumuCCSelection;
  numuCCMultiPiSelection _numuCCMultiPiSelection;
  
  Int_t _MuonPIDCutIndex;
  Int_t _FindPionsStepIndex; 
};

class ToyBoxAntiCCMultiPi: public ToyBoxCCMultiPi{

public:
  ToyBoxAntiCCMultiPi(){}

  virtual ~ToyBoxAntiCCMultiPi(){}

};

inline ToyBoxB* antiNumuCCMultiPiSelection::MakeToyBox(){return new ToyBoxAntiCCMultiPi();}



class FillSummaryAction_antinuCCMultiPi: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_antinuCCMultiPi();}
};

class FindPionsAction_antinuCCMultiPi: public cutUtils::numuCCTrkMultiPi::FindPionsActionBase{
public:
  using StepBase::Apply;
  FindPionsAction_antinuCCMultiPi():cutUtils::numuCCTrkMultiPi::FindPionsActionBase(true){ // true means is RHC
    _pionSelParams.useTPCPions                 = (bool)ND::params().GetParameterI("psycheSelections.antinumuCCMultiPi.UseTPCPions");
    _pionSelParams.useME                       = (bool)ND::params().GetParameterI("psycheSelections.antinumuCCMultiPi.UseME");
    _pionSelParams.useFGDPions                 = (bool)ND::params().GetParameterI("psycheSelections.antinumuCCMultiPi.UseFGDPions");
  } 
  StepBase* MakeClone(){return new FindPionsAction_antinuCCMultiPi();}
  
  virtual const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  
};


#endif
