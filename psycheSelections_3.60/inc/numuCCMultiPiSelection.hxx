#ifndef numuCCMultiPiSelection_h
#define numuCCMultiPiSelection_h

#include "numuCCSelection.hxx"
#include "Parameters.hxx"
#include "CutUtils.hxx"

class numuCCMultiPiSelection: public SelectionBase{

public:
  numuCCMultiPiSelection(bool forceBreak=true);
  virtual ~numuCCMultiPiSelection(){}

  void DefineSteps();
  void DefineDetectorFV();
  inline ToyBoxB* MakeToyBox();
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCC0Pi;}
  bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;

  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;

  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  void InitializeEvent(AnaEventC& event);
  bool CheckRedoSelection(const AnaEventC& event, const ToyBoxB& PreviousToyBox,  Int_t& redoFromStep);

  Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;

  void SetDetectorFV(SubDetId_h det, Int_t ibranch=-1){
    SelectionBase::SetDetectorFV(det, ibranch);
    // Set to the selection that is used
    _numuCCSelection.SetDetectorFV(det, ibranch);
  }

protected:
  numuCCSelection _numuCCSelection;

  Int_t _MuonPIDCutIndex;
  Int_t _FindPionsStepIndex;  
};

class ToyBoxCCMultiPi: public ToyBoxTracker{

public:
  ToyBoxCCMultiPi(){}

  virtual ~ToyBoxCCMultiPi(){}

  void Reset(){
    pionBox.Reset();
  }

  multipart::MultiParticleBox pionBox;

  virtual const multipart::MultiParticleBox* GetMultiParticleBox() const{
    return &pionBox;
  }

};

inline ToyBoxB* numuCCMultiPiSelection::MakeToyBox(){return new ToyBoxCCMultiPi();}

namespace numuCCMultiPi{

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box);
};


class NoPionCut: public cutUtils::numuCCTrkMultiPi::NoPionCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new NoPionCut();}
};

class OnePionCut: public cutUtils::numuCCTrkMultiPi::OnePionCutBase{  
public:

  OnePionCut(bool posPionMode): cutUtils::numuCCTrkMultiPi::OnePionCutBase(posPionMode){}
  virtual ~OnePionCut(){}

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }

  StepBase* MakeClone(){return new OnePionCut(_posPionMode);}
};

class OthersCut: public cutUtils::numuCCTrkMultiPi::OthersCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new OthersCut();}
};

class FillSummaryAction_numuCCMultiPi: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_numuCCMultiPi();}
};

class FindPionsAction: public cutUtils::numuCCTrkMultiPi::FindPionsActionBase{
public:
  using StepBase::Apply;
  FindPionsAction():cutUtils::numuCCTrkMultiPi::FindPionsActionBase(false){  // false means is not RHC
    _pionSelParams.useTPCPions                 = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.UseTPCPions");
    _pionSelParams.useME                       = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.UseME");
    _pionSelParams.useFGDPions                 = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.UseFGDPions");
  }

  StepBase* MakeClone(){return new FindPionsAction();}
  
  virtual const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
};

class FindProtonsAction: public cutUtils::numuCCTrkMultiPi::FindProtonsActionBase{
public:
  using StepBase::Apply;
  FindProtonsAction(){
    _protonSelParams.tpcPIDCut  = (Float_t)ND::params().GetParameterD("psycheSelections.numuCCMultiPi.Protons.TPCPIDCut");
    _protonSelParams.fgd1PIDCut = (Float_t)ND::params().GetParameterD("psycheSelections.numuCCMultiPi.Protons.FGD1PIDCut");
    _protonSelParams.fgd2PIDCut = (Float_t)ND::params().GetParameterD("psycheSelections.numuCCMultiPi.Protons.FGD2PIDCut");
  } 
  StepBase* MakeClone(){return new FindProtonsAction();}

  virtual const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  

};


class SetVertexToBoxAction: public StepBase, cutUtils::numuCCTrkMultiPi::MultiParticleBoxGetter{  
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }

  StepBase* MakeClone(){return new SetVertexToBoxAction();}

};

class FillFgdIsoPionsKinVertexAction: public cutUtils::numuCCTrkMultiPi::FillFgdIsoPionsKinVertexActionBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }

  StepBase* MakeClone(){return new FillFgdIsoPionsKinVertexAction();}
};

class FillFgdIsoProtonsKinVertexAction: public cutUtils::numuCCTrkMultiPi::FillFgdIsoProtonsKinVertexActionBase{  
public:
  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }    
  StepBase* MakeClone(){return new FillFgdIsoProtonsKinVertexAction();}
};
#endif
