#ifndef numuCC4piMultiPiFGD2Selection_h
#define numuCC4piMultiPiFGD2Selection_h

#include "SelectionBase.hxx"
#include "Parameters.hxx"
#include "ToyBoxTracker.hxx"
#include "EventBoxId.hxx"
#include "SystId.hxx"
#include "SubDetId.hxx"
#include "CutUtils.hxx"
#include "SampleId.hxx"
#include "MultiParticleBox.hxx"
#include "ToFSenseCorrector.hxx"

#include "BaseDataClasses.hxx"
// #include "DataClasses.hxx"
#include "ToyBoxB.hxx"
// #include "CategoriesUtils.hxx"
#include "MultiParticleBox.hxx"
#include "numuCC4piMultiPiSelection.hxx"

class numuCC4piMultiPiFGD2Selection: public numuCC4piMultiPiSelection{
public:
  numuCC4piMultiPiFGD2Selection(bool forceBreak=true): numuCC4piMultiPiSelection(forceBreak){}
  virtual ~numuCC4piMultiPiFGD2Selection(){}
  //---- These are mandatory functions
  void DefineSteps();
  void DefineDetectorFV();

  // bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  // bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;

  

protected:
  numuCC4piMultiPiSelection _numuCC4piMultiPiSelection;

};



namespace numuCC4piMultiPi{	

  
  /// Find the correct sense of a secondary track by comparing its start and end positions with the vertex
  /// True -- no flip was applied, false - flip applied since sense does not
  /// match the vertex
  
  /// Find correct sense for pion candidates given a vertex


  class FillSummaryAction_numuCC4piMultiPiFGD2: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FillSummaryAction_numuCC4piMultiPiFGD2();}
  };


};

#endif
