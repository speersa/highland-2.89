#ifndef numuCCMultiPiPhotonSelection_h
#define numuCCMultiPiPhotonSelection_h

#include "numuCCMultiPiSelection.hxx"

class numuCCMultiPiPhotonSelection: public numuCCMultiPiSelection{

public:
  numuCCMultiPiPhotonSelection(bool forceBreak=true) : numuCCMultiPiSelection(forceBreak){}

  virtual ~numuCCMultiPiPhotonSelection(){}

  void DefineSteps();

  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCCPhoton;}

  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;

  bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;

  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;

  Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
};


class FillSummaryAction_numuCCMultiPiPhoton: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_numuCCMultiPiPhoton();}
};


class FindECalPhotonsAction: public cutUtils::numuCCTrkMultiPi::FindECalPhotonsActionBase{  
public:
  FindECalPhotonsAction(){
    _ecalPhotonSelParams.PIDEmHipCut = 
      (Float_t)ND::params().GetParameterD("psycheSelections.numuCCMultiPiPhoton.Cuts.PIDEmHipCut");
    _ecalPhotonSelParams.ECalMostUpstreamLayerHitCut = 
      (Int_t)ND::params().GetParameterI("psycheSelections.numuCCMultiPiPhoton.Cuts.ECalMostUpstreamLayerHitCut");
    _ecalPhotonSelParams.ECalNHitsCut =
     (Int_t)ND::params().GetParameterI("psycheSelections.numuCCMultiPiPhoton.Cuts.ECalNHitsCut"); 
  }
  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new FindECalPhotonsAction();}
};


class PhotonCut: public StepBase{
public:
  using StepBase::Apply;
  PhotonCut(){};
  bool      Apply    (AnaEventC& event, ToyBoxB& box) const;
  StepBase* MakeClone(){return new PhotonCut();}
};
#endif
