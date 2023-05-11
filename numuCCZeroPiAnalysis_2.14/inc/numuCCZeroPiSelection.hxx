#ifndef numuCCZeroPiSelection_h
#define numuCCZeroPiSelection_h

#include "SelectionBase.hxx"
#include "SubDetId.hxx"
#include "Parameters.hxx"
#include "ToFSenseCorrector.hxx"
#include "numuCCSelection.hxx"
#include "ToyBoxTracker.hxx"
#include "SampleId.hxx"
#include "MultiParticleBox.hxx"
#include "CutUtils.hxx"

/// Enum to define type of a particular candidate
/// More to come if needed to split between e.g. bwd and fwd candidates
namespace zero_pi{

  enum CandidateType{
    kHMN,
    kHMP, 
    kFGD, 
    kUnassigned
  };  
  
  // Do some hack to re-use the available sample id`s but for CCZeroPi purposes
  // This is to avoid extending the AnaEventSummary class  
  enum SampleType{
    kFgd1MuTpc       = SampleId::kFGD1NuMuCC,
    kFgd1MuTpcPTpc   = SampleId::kFGD1NuMuCCQE,
    kFgd1MuTpcPFgd   = SampleId::kFGD1NuMuCC0Pi,
    kFgd1MuFgdPTpc   = SampleId::kFGD1NuMuCC1Pi,
    kFgd1MuFgd       = SampleId::kFGD1NuMuCCOther,
    kFgd1CC1Pi       = SampleId::kFGD1NuMuCC0PiFwd,
    kFgd1CCDIS       = SampleId::kFGD1NuMuCC1PiFwd,
    kFgd1CCMichel    = SampleId::kFGD1NuMuCCOtherFwd,
    kFgd1CCECalVeto  = SampleId::kFGD1NuMuCC0PiBwd,
    kFgd1MuTpcNP     = SampleId::kFGD1NuMuCC1PiBwd,
    kFgd1MuFgdPTpcNP = SampleId::kFGD1NuMuCCOtherBwd,
    kFgd1MuFgdNP     = SampleId::kFGD1NuMuCC0PiHAFwd,
    
    
    kFgd2MuTpc       = SampleId::kFGD1NuMuCC1PiHAFwd,
    kFgd2MuTpcPTpc   = SampleId::kFGD1NuMuCCOtherHAFwd,
    kFgd2MuTpcPFgd   = SampleId::kFGD1NuMuCC0PiHABwd,
    kFgd2MuFgdPTpc   = SampleId::kFGD1NuMuCC1PiHABwd,
    kFgd2MuFgd       = SampleId::kFGD1NuMuCCOtherHABwd,
    kFgd2CC1Pi       = SampleId::kFGD2NuMuCC,
    kFgd2CCDIS       = SampleId::kFGD2NuMuCC0Pi,
    kFgd2CCMichel    = SampleId::kFGD2NuMuCC1Pi,
    kFgd2CCECalVeto  = SampleId::kFGD2NuMuCCOther,  
    kFgd2MuTpcNP     = SampleId::kFGD2NuMuCC0PiFwd, 
    kFgd2MuFgdPTpcNP = SampleId::kFGD2NuMuCC1PiFwd,
    kFgd2MuFgdNP     = SampleId::kFGD2NuMuCCOtherFwd, 
    kEndOfSamples
    
  };
}

class numuCCZeroPiSelection: public SelectionBase{
public:
  numuCCZeroPiSelection(bool forceBreak=true, SubDetId::SubDetEnum=SubDetId::kFGD1);
  virtual ~numuCCZeroPiSelection(){}

  //---- These are mandatory functions
  void DefineSteps();
  
  void DefineDetectorFV(){
    SetDetectorFV(_detectorFV);
  }
   
  void InitializeEvent(AnaEventC& event);
  inline ToyBoxB* MakeToyBox();
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  
  // Systematics related
  
  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  
  bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const; 

  bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;
  
  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* track, SystId_h systId, Int_t branch) const;
  
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;
  
    Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;

  // To do the reverse based on ToF toy variation
  void InitializeToy(const AnaEventC* event = NULL) const{}
  
  void FinalizeToy(const AnaEventC* event = NULL) const{}

  
SampleId_h GetSampleId(){
    
    if (GetDetectorFV() == SubDetId::kFGD1)
      return SampleId::kFGD1NuMuCC0Pi;
    else
      return SampleId::kFGD2NuMuCC0Pi;
  } 
  
  
private:
  SubDetId::SubDetEnum _detectorFV;
};



class AnaBoxCCZeroPi: public ToyBoxTracker{

public:
 
  AnaBoxCCZeroPi(SubDetId::SubDetEnum detFV = SubDetId::kFGD1) {
    MuonCandidate   = NULL;
    ProtonCandidate = NULL;

    nProtonTPCCandidates    = 0;
    nProtonFGDCandidates    = 0;
    
    DetectorFV = detFV;
    
    VertexType = zero_pi::kUnassigned;
    
    
  }
  
  virtual ~AnaBoxCCZeroPi(){}
  
  
  multipart::MultiParticleBox pionBox;
   
  virtual void Reset(){
    MuonCandidate   = NULL;
    ProtonCandidate = NULL;

    // Pion box
    pionBox.Reset(); 
 
    // Proton candidates
    nProtonTPCCandidates    = 0;
    nProtonFGDCandidates    = 0;
    
    VertexType = zero_pi::kUnassigned; 
    
    
  } 
    
    
  virtual const multipart::MultiParticleBox* GetMultiParticleBox() const{
    return &pionBox;
  }
  
  /// Muon and proton candidate
  AnaTrackB*  MuonCandidate;
  AnaTrackB*  ProtonCandidate;
 
  /// Proton candidates,  these are tracks that can be considered as possible proton candidates, basically
  /// satisfy some PID cuts, these are for multi-proton selections
  AnaTrackB* ProtonTPCCandidates[50];
  int nProtonTPCCandidates;
  
  AnaTrackB* ProtonFGDCandidates[50];
  int nProtonFGDCandidates;

  SubDetId::SubDetEnum DetectorFV;
  
  zero_pi::CandidateType VertexType;
  
  
};

inline ToyBoxB* numuCCZeroPiSelection::MakeToyBox() {return new AnaBoxCCZeroPi(static_cast<SubDetId::SubDetEnum>(GetDetectorFV()));}


/// ------ zero_pi ------- toolbox
namespace zero_pi{
  
  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box);
  /// Basic cuts and actions
  
  /// ------ Summary ------
  class FillSummaryAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;  
    StepBase* MakeClone(){return new FillSummaryAction();}
  };
 
  /// Find Muon and Proton candidates for all topologies --> NEED TO BE MODIFIED
  /// IF WANT TO USE TOF
  class FindTrackerTracksAction: public FindLeadingTracksAction{
    StepBase* MakeClone(){return new FindTrackerTracksAction();}
  };
  
  /// Find muon candidate
  class FindMuonCandidateAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FindMuonCandidateAction();}
  };
  
  /// Find Proton candidates: TPC and FGD
  class FindProtonCandidatesAction: public StepBase{
  public:
    FindProtonCandidatesAction(){
      /// muTPC + pTPC
      _cutX_FGD1_vtxTPC_pTPC = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutX_vtxTPC_pTPC"); 
      _cutY_FGD1_vtxTPC_pTPC = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutY_vtxTPC_pTPC"); 
      _cutZ_FGD1_vtxTPC_pTPC = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutZ_vtxTPC_pTPC");
      
      _cutX_FGD2_vtxTPC_pTPC = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutX_vtxTPC_pTPC"); 
      _cutY_FGD2_vtxTPC_pTPC = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutY_vtxTPC_pTPC"); 
      _cutZ_FGD2_vtxTPC_pTPC = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutZ_vtxTPC_pTPC");
      
      /// muTPC + pFGD
      _cutX_FGD1_vtxTPC_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutX_vtxTPC_pFGD"); 
      _cutY_FGD1_vtxTPC_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutY_vtxTPC_pFGD"); 
      _cutZ_FGD1_vtxTPC_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutZ_vtxTPC_pFGD");
    
      _cutX_FGD2_vtxTPC_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutX_vtxTPC_pFGD"); 
      _cutY_FGD2_vtxTPC_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutY_vtxTPC_pFGD"); 
      _cutZ_FGD2_vtxTPC_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutZ_vtxTPC_pFGD");
      
       /// muFGD + pFGD
      _cutX_FGD1_vtxFGD_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutX_vtxFGD_pFGD"); 
      _cutY_FGD1_vtxFGD_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutY_vtxFGD_pFGD"); 
      _cutZ_FGD1_vtxFGD_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutZ_vtxFGD_pFGD");
    
      _cutX_FGD2_vtxFGD_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutX_vtxFGD_pFGD"); 
      _cutY_FGD2_vtxFGD_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutY_vtxFGD_pFGD"); 
      _cutZ_FGD2_vtxFGD_pFGD = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutZ_vtxFGD_pFGD");

      /// FGD PID
      _cut_proton_PID_FGD1 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.FGDProtonPID"); 
      _cut_proton_PID_FGD2 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.FGDProtonPID"); 
      
      /// TPC PID
      _cut_proton_PID_TPC = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.TPCProtonPID");  
    }
    
    
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FindProtonCandidatesAction();}
 
  protected:
    /// Select cuts to be used
    void UpdateParams(zero_pi::CandidateType vtx_type, zero_pi::CandidateType proton_type, SubDetId::SubDetEnum det) const; 
    
    void SetDefaultParams() const{
      _cutX   = _cutX_FGD1_vtxTPC_pTPC;
      _cutY   = _cutY_FGD1_vtxTPC_pTPC;
      _cutZ   = _cutZ_FGD1_vtxTPC_pTPC;
      _cutPID = _cut_proton_PID_TPC;
    }
    
    /// Various cuts to be used to select candidates 
    /// Common vertex
    /// FGD1 muTPC-pTPC
    Float_t _cutX_FGD1_vtxTPC_pTPC;
    Float_t _cutY_FGD1_vtxTPC_pTPC; 
    Float_t _cutZ_FGD1_vtxTPC_pTPC; 
     
    /// FGD2 muTPC-pTPC
    Float_t _cutX_FGD2_vtxTPC_pTPC;
    Float_t _cutY_FGD2_vtxTPC_pTPC; 
    Float_t _cutZ_FGD2_vtxTPC_pTPC; 
     
    /// FGD1 muTPC-pFGD
    Float_t _cutX_FGD1_vtxTPC_pFGD;
    Float_t _cutY_FGD1_vtxTPC_pFGD; 
    Float_t _cutZ_FGD1_vtxTPC_pFGD; 
     
    /// FGD2 muTPC-pFGD
    Float_t _cutX_FGD2_vtxTPC_pFGD;
    Float_t _cutY_FGD2_vtxTPC_pFGD; 
    Float_t _cutZ_FGD2_vtxTPC_pFGD; 
     
    /// FGD1 muFGD-pFGD
    Float_t _cutX_FGD1_vtxFGD_pFGD;
    Float_t _cutY_FGD1_vtxFGD_pFGD; 
    Float_t _cutZ_FGD1_vtxFGD_pFGD; 
     
    /// FGD2 muFGD-pFGD
    Float_t _cutX_FGD2_vtxFGD_pFGD;
    Float_t _cutY_FGD2_vtxFGD_pFGD; 
    Float_t _cutZ_FGD2_vtxFGD_pFGD; 
    
    /// FGD PID
    Float_t _cut_proton_PID_FGD1;
    Float_t _cut_proton_PID_FGD2;
    Float_t _cut_proton_PID_TPC;
    
    
    /// Cuts currently used
    mutable Float_t _cutX;
    mutable Float_t _cutY;
    mutable Float_t _cutZ;
    mutable Float_t _cutPID;
    
  };

  /// Define an interaction vertex to be processed
  class FindVertexAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FindVertexAction();}
  }; 
   
  /// Find Michel electrons
  class FindMichelElectronsAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FindMichelElectronsAction();}
  };

  
  class FindECalPhotonsAction: public cutUtils::numuCCTrkMultiPi::FindECalPhotonsActionBase{  
  public:
    FindECalPhotonsAction(){
      _ecalPhotonSelParams.PIDEmHipCut = 
        (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.ECalPhotons.PIDEmHipCut");
    _ecalPhotonSelParams.ECalMostUpstreamLayerHitCut = 
      (Int_t)ND::params().GetParameterI("numuCCZeroPiAnalysis.Cuts.ECalPhotons.CalMostUpstreamLayerHitCut");
    _ecalPhotonSelParams.ECalNHitsCut = 
      (Int_t)ND::params().GetParameterI("numuCCZeroPiAnalysis.Cuts.ECalPhotons.ECalNHitsCut");
    }
    const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
      return zero_pi::GetPionBox(box);  
    }
    StepBase* MakeClone(){return new FindECalPhotonsAction();}
  };

  class ZeroECalPhotonsCut: public cutUtils::numuCCTrkMultiPi::ZeroECalPhotonsCutBase{  
  public:

    const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
      return zero_pi::GetPionBox(box);  
    }
    StepBase* MakeClone(){return new ZeroECalPhotonsCut();}
  };
  
  // No Michel electrons: takes into account a special case when a muon
  // candidate is contained inside FGD
  class MichelElectronCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MichelElectronCut();}
  };

  
  //N tracker tracks
  class NTrackerTracksCut: public StepBase{
  public:
    
    NTrackerTracksCut(int nCut = 1){
      _nCut = nCut;
    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new NTrackerTracksCut(_nCut);}
  protected:
    int _nCut;
  };
  
  // A cut on number of tracker tracks: should be muon + nProtonCandidates
  class MuonProtonTracksCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonProtonTracksCut();}
  }; 

  // A cut on number of proton candidates
  class NProtonTracksCut: public NTrackerTracksCut{
  public:
    NProtonTracksCut(int nCut = 1): NTrackerTracksCut(nCut) {}
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new NProtonTracksCut(_nCut);}
  }; 
  
  class MultiProtonTracksCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MultiProtonTracksCut();}
  }; 

  // A cut on number of TPC proton candidates
  class N_TPC_ProtonTracksCut: public NTrackerTracksCut{
  public:
    N_TPC_ProtonTracksCut(int nCut = 1): NTrackerTracksCut(nCut) {}
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new N_TPC_ProtonTracksCut(_nCut);}
  };
  
  // A cut on number of FGD proton candidates
  class N_FGD_ProtonTracksCut: public NTrackerTracksCut{
  public:
    N_FGD_ProtonTracksCut(int nCut = 1): NTrackerTracksCut(nCut) {}
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new N_FGD_ProtonTracksCut(_nCut);}
  }; 

  class OneNegativeTrackCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new OneNegativeTrackCut();}
  };
  
 
  // Muon candidate TPC vertex
  class MuonCandidate_TPC_VertexCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_TPC_VertexCut();}
  };
  
  // Proton candidate TPC vertex
  class HMP_TPC_VertexCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HMP_TPC_VertexCut();}
  };
  
  // Proton candidate TPC vertex
  class ProtonCandidate_TPC_VertexCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new ProtonCandidate_TPC_VertexCut();}
  };
  
  
  // Muon candidate FGD vertex
  class MuonCandidate_FGD_VertexCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_FGD_VertexCut();}
  };
  
  // Sense using the vertex constrain to reverse a track
  class FindCorrectMuonSenseAction: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new FindCorrectMuonSenseAction();}
  };

  // Muon candidate
  class MuonCandidate_TPC_MuonPIDCut: public MuonPIDCut{
  public:
    StepBase* MakeClone(){return new MuonCandidate_TPC_MuonPIDCut();}
  };
  

  class MuonCandidate_FGD_LongFGDTrackCut: public StepBase{
  public:
    MuonCandidate_FGD_LongFGDTrackCut(){
      _cutFGD1 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.LongFGDTrack"); 
      _cutFGD2 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.LongFGDTrack"); 
    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_FGD_LongFGDTrackCut();}

  protected:
    Float_t _cutFGD1;
    Float_t _cutFGD2;
  };

  class MuonCandidate_FGD_MuonPIDCut: public StepBase{
  public:
    MuonCandidate_FGD_MuonPIDCut(){
      _cutFGD1 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.FGDMuonPID"); 
      _cutFGD2 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.FGDMuonPID"); 
    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_FGD_MuonPIDCut();}

  protected:
    Float_t _cutFGD1;
    Float_t _cutFGD2;
  };
  
  class MuonCandidate_FGD_StoppingCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_FGD_StoppingCut();}
  };

  class ProtonCandidate_FGD_StoppingCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new ProtonCandidate_FGD_StoppingCut();}
  };
 
   
  class CommonVertexCut_muFGD_pTPC: public StepBase{
  public:
    CommonVertexCut_muFGD_pTPC(){
      _cutXFGD1 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutX_muFGD_pTPC"); 
      _cutYFGD1 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutY_muFGD_pTPC"); 
      _cutZFGD1 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD1.CutZ_muFGD_pTPC");
    
      _cutXFGD2 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutX_muFGD_pTPC"); 
      _cutYFGD2 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutY_muFGD_pTPC"); 
      _cutZFGD2 = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.FGD2.CutZ_muFGD_pTPC");
    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new CommonVertexCut_muFGD_pTPC();}
  private:
    
    Float_t _cutXFGD1;
    Float_t _cutYFGD1;
    Float_t _cutZFGD1; 
    
    Float_t _cutXFGD2;
    Float_t _cutYFGD2;
    Float_t _cutZFGD2; 
 
  };
  
  // High-angle selection 
  class MuonCandidate_FGD_ECalPIDCut: public StepBase{
  public:
    MuonCandidate_FGD_ECalPIDCut(){ 
      _HA_ECalPID_cut = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.HA_ECal_PID"); 

    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_FGD_ECalPIDCut();}

  private:
    Float_t _HA_ECalPID_cut;  
  };

  class MuonCandidate_FGD_ECalPID2Cut: public StepBase{
  public:
    MuonCandidate_FGD_ECalPID2Cut(){ 
      _HA_ECalPID2_cut  = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.HA_ECal_PID2"); 

    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_FGD_ECalPID2Cut();}

  private:
    Float_t _HA_ECalPID2_cut;  
  };
  
  class MuonCandidate_FGD_ToFCut: public StepBase{
  public:
    MuonCandidate_FGD_ToFCut(){
      
      // Whether to use ToF information for cuts
      _useToFInfo          = (bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Selections.UseToFInfo");
      
      _HA_ECal_FGD1_ToFCut = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.HA_ECal_FGD1_ToFCut");
      _HA_ECal_FGD2_ToFCut = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.HA_ECal_FGD2_ToFCut");
    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MuonCandidate_FGD_ToFCut();}

  private:
    Float_t _HA_ECal_FGD1_ToFCut;
    Float_t _HA_ECal_FGD2_ToFCut;
    bool _useToFInfo;
  };


  /// Control-samples
  class HMP_TPC_PionPIDCut: public StepBase{
  public:
    HMP_TPC_PionPIDCut(){
      _mip_lhood_cut  = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.PionPID.MipLHood");
      _pion_lhood_cut = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.PionPID.PionLHood");
      _min_mom_cut    = (Float_t)ND::params().GetParameterD("numuCCZeroPiAnalysis.Cuts.PionPID.MomentumCut");
    }
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new HMP_TPC_PionPIDCut();}

  private:
    Float_t _mip_lhood_cut;
    Float_t _pion_lhood_cut;
    Float_t _min_mom_cut;

  };

  class MultiTpcTracksCut: public StepBase{
  public:
    using StepBase::Apply;
    bool Apply(AnaEventC& event, ToyBoxB& box) const;
    StepBase* MakeClone(){return new MultiTpcTracksCut();}
  };
 
  /// ----- Utility Actions -----
  
  /// ---------FGD PIDs---------
  bool FGDProtonPIDCut(   const AnaTrackB& track, Float_t cut);
  bool FGDMuonPIDCut  (   const AnaTrackB& track, Float_t cut);
  
  bool TPCProtonPIDCut(   const AnaTrackB& track, Float_t cut);

  /// Fnd the correct sense of a secondary track by comparing its start and end positions with the vertex
  void FindCorrectSense(AnaTrackB* track, AnaVertexB* vertex);
 
  void BuildVertex(AnaVertexB*& vertex, AnaTrackB* track);
  
  //return total number of tracker tracks
  int GetNTrackerTracks(const AnaEventC& event);
  
  /// Check a track leaves tracker: end point in TPC or is inside FGD FV but
  /// outside FV
  bool TrackLeavesTracker(const AnaTrackB& track);

  
}//zero_pi


#endif
