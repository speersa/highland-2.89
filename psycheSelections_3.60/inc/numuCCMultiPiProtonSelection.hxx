#ifndef numuCCMultiPiProtonSelection_h
#define numuCCMultiPiProtonSelection_h

#include "numuCCMultiPiSelection.hxx"

class numuCCMultiPiProtonSelection: public numuCCMultiPiSelection{

public:
  numuCCMultiPiProtonSelection(bool forceBreak=true) : numuCCMultiPiSelection(forceBreak){}
  virtual ~numuCCMultiPiProtonSelection(){}

  void DefineSteps();
  
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCC0Pi0Protons;}
  
  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;
  
};

class FillSummaryAction_numuCCMultiPiProton: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_numuCCMultiPiProton();}
};


class NProtonsCut: public cutUtils::numuCCTrkMultiPi::NProtonsCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new NProtonsCut();}
};

class ZeroProtonsCut: public cutUtils::numuCCTrkMultiPi::ZeroProtonsCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new ZeroProtonsCut();}
};





#endif
