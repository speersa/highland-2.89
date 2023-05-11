#ifndef numuBkgInAntiNuModeCCMultiPiFGD2Selection_h
#define numuBkgInAntiNuModeCCMultiPiFGD2Selection_h

#include "SelectionBase.hxx"
#include "Parameters.hxx"
#include "numuCCMultiPiFGD2Selection.hxx"
#include "numuCCFGD2Selection.hxx"
#include "numuBkgInAntiNuModeCCFGD2Selection.hxx"
#include "numuBkgInAntiNuModeCCMultiPiSelection.hxx"

class numuBkgInAntiNuModeCCMultiPiFGD2Selection: public SelectionBase{

    public:
        numuBkgInAntiNuModeCCMultiPiFGD2Selection(bool forceBreak=true);
        virtual ~numuBkgInAntiNuModeCCMultiPiFGD2Selection(){}

        void DefineSteps();
        void DefineDetectorFV();
        ToyBoxB* MakeToyBox(){return new ToyBoxCCMultiPi();}
        bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
        SampleId_h GetSampleId(){return SampleId::kFGD2NuMuBkgInAntiNuModeCC;}
        bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
        bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;
        bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
        void InitializeEvent(AnaEventC& event);
        bool CheckRedoSelection(const AnaEventC& event, const ToyBoxB& PreviousToyBox, Int_t& redoFromStep);
          
        Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;    
        Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;

        bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
        bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;

        void SetDetectorFV(SubDetId_h det, Int_t ibranch=-1){
          SelectionBase::SetDetectorFV(det, ibranch);
          // Set to the selection that are used
          _numuCCMultiPiFGD2Selection.SetDetectorFV(det, ibranch); 
          _numuBkgInAntiNuModeCCFGD2Selection.SetDetectorFV(det, ibranch);
          _numuBkgInAntiNuModeCCMultiPiSelection.SetDetectorFV(det, ibranch);
        }
    protected:
       numuCCMultiPiFGD2Selection            _numuCCMultiPiFGD2Selection;
       numuBkgInAntiNuModeCCFGD2Selection    _numuBkgInAntiNuModeCCFGD2Selection;
       numuBkgInAntiNuModeCCMultiPiSelection _numuBkgInAntiNuModeCCMultiPiSelection;
};

class FillSummaryAction_numuBkgMultiPiFGD2: public StepBase{
    public:
        using StepBase::Apply;
        bool Apply(AnaEventC& event, ToyBoxB& box) const;  
        StepBase* MakeClone(){return new FillSummaryAction_numuBkgMultiPiFGD2();
	}
  
};

#endif
