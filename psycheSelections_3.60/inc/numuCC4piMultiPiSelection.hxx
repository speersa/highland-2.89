#ifndef numuCC4piMultiPiSelection_h
#define numuCC4piMultiPiSelection_h

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

class numuCC4piMultiPiSelection: public SelectionBase{
public:
  numuCC4piMultiPiSelection(bool forceBreak=true);
  virtual ~numuCC4piMultiPiSelection(){}
  //---- These are mandatory functions
  void DefineSteps();
  virtual void DefineDetectorFV();
  inline ToyBoxB* MakeToyBox();
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCC0PiFwd;}

  bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;

  void InitializeEvent(AnaEventC& event);
  Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  
  virtual void InitializeToy(const AnaEventC* eventC) const;

  virtual void FinalizeToy(const AnaEventC* eventC) const;

protected:

  /// A corrector to deal with various ToF business
  ToFSenseCorrector _tofCorrector;
  /// Whether to flip the track based on ToF   
  bool _apply_ToF_based_Flip; 

};

class ToyBoxCC4piMultiPi: public ToyBoxTracker{
public:

  ToyBoxCC4piMultiPi() {
    MainTrack = NULL;
    LowAngle.clear(); HighAngle.clear();
    FwdTracks.clear();      BwdTracks.clear();      HAFwdTracks.clear();      HABwdTracks.clear();
    FwdTracks_Veto.clear(); BwdTracks_Veto.clear(); HAFwdTracks_Veto.clear(); HABwdTracks_Veto.clear();
    FwdTracks_PID.clear();  BwdTracks_PID.clear();  HAFwdTracks_PID.clear();  HABwdTracks_PID.clear(); CSFD2Tracks_PID.clear(); CSECALTracks_PID.clear();
    pionBox.Reset();
  }

  virtual void Reset(){
    ResetBase();
    MainTrack = NULL;
    LowAngle.clear(); HighAngle.clear();
    FwdTracks.clear();      BwdTracks.clear();      HAFwdTracks.clear();      HABwdTracks.clear();
    FwdTracks_Veto.clear(); BwdTracks_Veto.clear(); HAFwdTracks_Veto.clear(); HABwdTracks_Veto.clear();
    FwdTracks_PID.clear();  BwdTracks_PID.clear();  HAFwdTracks_PID.clear();  HABwdTracks_PID.clear(); CSFD2Tracks_PID.clear(); CSECALTracks_PID.clear();
    pionBox.Reset();
  }

  virtual ~ToyBoxCC4piMultiPi(){}
  
 
  /// For storing tracks information in the bunch.
  AnaTrackB* MainTrack;
  std::vector<AnaTrackB*> LowAngle, HighAngle;
  std::vector<AnaTrackB*> FwdTracks,      BwdTracks,      HAFwdTracks,      HABwdTracks;
  std::vector<AnaTrackB*> FwdTracks_Veto, BwdTracks_Veto, HAFwdTracks_Veto, HABwdTracks_Veto;
  std::vector<AnaTrackB*> FwdTracks_PID,  BwdTracks_PID,  HAFwdTracks_PID,  HABwdTracks_PID, CSFD2Tracks_PID, CSECALTracks_PID;

  multipart::MultiParticleBox pionBox;
  
  virtual const multipart::MultiParticleBox* GetMultiParticleBox() const{
    return &pionBox;
}
};

inline ToyBoxB* numuCC4piMultiPiSelection::MakeToyBox() {return new ToyBoxCC4piMultiPi();}

namespace numuCC4piMultiPi{	
  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box);
  
  class TotalMultiplicityCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new TotalMultiplicityCut();}
  };

  class SortTracksToFAction: public StepBase{
  public:
    using StepBase::Apply;
    SortTracksToFAction(){}
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new SortTracksToFAction();} 
  };

  class TrackGQandFVCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new TrackGQandFVCut();}
  };

  class FindVertexAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FindVertexAction();}
  };

  class VetoAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new VetoAction();}
  };

  class PIDAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new PIDAction();}
  };

  void FindECALPionInfo(const AnaEventC& event, const multipart::PionSelectionParams& params, multipart::MultiParticleBox& pionBox);
  void FillPionInfo(const AnaEventC& event, multipart::MultiParticleBox& pionBox, const multipart::PionSelectionParams& params);
  
  class FindPionsAction: public StepBase{
  public:
    using StepBase::Apply;
    FindPionsAction(){
      pionSelParams.useTPCPions                 = (bool)ND::params().GetParameterI("psycheSelections.numuCC4piMultiPi.UseTPCPions");
      pionSelParams.useME                       = (bool)ND::params().GetParameterI("psycheSelections.numuCC4piMultiPi.UseME");
      pionSelParams.useFGDPions                 = (bool)ND::params().GetParameterI("psycheSelections.numuCC4piMultiPi.UseFGDPions");
      pionSelParams.useECalPions                = (bool)ND::params().GetParameterI("psycheSelections.numuCC4piMultiPi.UseECalPions");
    } 
    bool Apply(AnaEventC& event, ToyBoxB& box) const;  
    StepBase* MakeClone(){return new FindPionsAction();}
  protected:
    mutable multipart::PionSelectionParams pionSelParams;
  };

  /// Find the correct sense of a secondary track by comparing its start and end positions with the vertex
  /// True -- no flip was applied, false - flip applied since sense does not
  /// match the vertex
  bool FindCorrectSense(AnaTrackB* track, AnaVertexB* vertex);
  
  /// Find correct sense for pion candidates given a vertex
  void FindPionCorrectTrackSense(const ToyBoxB& box);

  class FindCorrectTrackSenseAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FindCorrectTrackSenseAction();}
  protected:
    std::set<AnaTrackB*>* _vertex_flipped_tracks; 
  };

  class FillSummaryAction_numuCC4piMultiPi: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FillSummaryAction_numuCC4piMultiPi();}
  };

  class Fwd_Quality: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new Fwd_Quality();}
  };

  class Fwd_Veto: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new Fwd_Veto();}
  };

  class Fwd_PID: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new Fwd_PID();}
  };

  class Bwd_Quality: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new Bwd_Quality();}
  };

  class Bwd_Veto: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new Bwd_Veto();}
  };

  class Bwd_PID: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new Bwd_PID();}
  };

  class HAFwd_Quality: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HAFwd_Quality();}
  };

  class HAFwd_Veto: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HAFwd_Veto();}
  };

  class HAFwd_PID: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HAFwd_PID();}
  };

  class HABwd_Quality: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HABwd_Quality();}
  };

  class HABwd_Veto: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HABwd_Veto();}
  };

  class HABwd_PID: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HABwd_PID();}
  };

  class NoPionCut: public cutUtils::numuCCTrkMultiPi::NoPionCutBase{  
  public:
    const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
      return numuCC4piMultiPi::GetPionBox(box);  
    }
    StepBase* MakeClone(){return new NoPionCut();}
  };

  class OnePionCut: public cutUtils::numuCCTrkMultiPi::OnePionCutBase{  
  public:
    OnePionCut(bool posPionMode): cutUtils::numuCCTrkMultiPi::OnePionCutBase(posPionMode){}
    virtual ~OnePionCut(){}
    const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
      return numuCC4piMultiPi::GetPionBox(box);  
    }
    StepBase* MakeClone(){return new OnePionCut(_posPionMode);}
  };
 
  class OthersCut: public cutUtils::numuCCTrkMultiPi::OthersCutBase{  
  public:
    const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
      return numuCC4piMultiPi::GetPionBox(box);  
    } 
    StepBase* MakeClone(){return new OthersCut();}
  protected:
    bool CheckECalPhotons(const ToyBoxB& box) const{
      const multipart::MultiParticleBox& pionBox = GetPionBox(box);
      // Will be probably removed
      if (pionBox.nECalPhotons > 0){
        return true; 
      }
      return false;
    } 
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
      return numuCC4piMultiPi::GetPionBox(box);  
    }
    StepBase* MakeClone(){return new FindECalPhotonsAction();}
  };
   
  class ZeroECalPhotonsCut: public cutUtils::numuCCTrkMultiPi::ZeroECalPhotonsCutBase{  
  public:
    const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
      return numuCC4piMultiPi::GetPionBox(box);  
    }
    StepBase* MakeClone(){return new ZeroECalPhotonsCut();}
  };

};
namespace numuCC4piMultiPi_utils{
  
  enum TopoEnum {
		CC_0pi_0meson = 0,
		CC_1pi_0meson = 1, 
		CC_other = 2,
		BKG = 3, 
	};
  
  enum MainTrackTopo{
    kLAFwd = 0, 
    kLABwd, 
    kHAFwd, 
    kHABwd, 
    kUnassigned
  };


  /// This is FV definition for truth etc
  const Float_t FGD1FVmin4pi[3] = {57.66, 57.66, 0.};
	const Float_t FGD1FVmax4pi[3] = {57.66, 57.66, 0.};

  const Float_t FGD2FVmin4pi[3] = {57.66, 57.66, 0.};
	const Float_t FGD2FVmax4pi[3] = {57.66, 57.66, 0.};
  
	const Float_t startFGD1LAFVmin[3] = {57.66, 57.66, 10.125};
	const Float_t startFGD1LAFVmax[3] = {57.66, 57.66, 0.};
	const Float_t startFGD1HAFVmin[3] = {57.66, 57.66, 10.125};
	const Float_t startFGD1HAFVmax[3] = {57.66, 57.66, 10.125};

  // Under development
  const Float_t startFGD2LAFVmin[3] = {57.66, 57.66, 10.125};
	const Float_t startFGD2LAFVmax[3] = {57.66, 57.66, 0.};
	const Float_t startFGD2HAFVmin[3] = {57.66, 57.66, 10.125};
	const Float_t startFGD2HAFVmax[3] = {57.66, 57.66, 10.125};
  
  
	const Float_t _FVdefminDsECal[3] = {40, 40, 25.};   // "z == 25." to reject peak near the DsECal beginning in both data and MC
	const Float_t _FVdefmaxDsECal[3] = {40, 40, 18.17}; // reject last layer in both data and MC
	const Float_t _FVdefminFGD2[3]   = {76.88, 38.44, 0.};     //9.61*8, 9.61*4
	const Float_t _FVdefmaxFGD2[3]   = {76.88, 38.44, 10.125}; //9.61*8, 9.61*4

	// Int_t GetCONTTopology(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  
  
	int GetFgdLayer(Float_t* pos, SubDetId::SubDetEnum det);
  
	bool isHMNT(const AnaTrackB* candidate, std::vector<AnaTrackB*> GroupTracks, bool lowangle, SubDetId::SubDetEnum det);
	
  bool VetoCut(numuCC4piMultiPi_utils::MainTrackTopo topo, const AnaEventB& event, AnaTrackB& candidate, SubDetId::SubDetEnum det);
	
  bool ExternalCut(numuCC4piMultiPi_utils::MainTrackTopo topo, const AnaEventC& event, AnaTrackB& candidate, SubDetId::SubDetEnum det);
	
  int PIDCut(numuCC4piMultiPi_utils::MainTrackTopo topo, const AnaTrackB& candidate, SubDetId::SubDetEnum det);
	/// Whether the track is muon-like, as defined for the NuMu analysis.
	
  bool BWDMuonPIDCut(const AnaTrackB& track);
	
  /// Whether the track is muon-like using ECAL information.
	bool MuonECALPIDCut(const AnaTrackB& track);
  
}

#endif
