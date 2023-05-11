#ifndef numuCCMultiPiAnalysis_h
#define numuCCMultiPiAnalysis_h

#include "numuCCAnalysis.hxx"
#include "numuCCMultiPiSelection.hxx"
#include "numuCCMultiPiPhotonSelection.hxx"
#include "numuCCMultiPiPhotonFGD2Selection.hxx"
#include "numuCCMultiPiPhotonProtonSelection.hxx"
#include "numuCCMultiPiPhotonProtonFGD2Selection.hxx"
#include "numuCCMultiPiProtonSelection.hxx"
#include "numuCCMultiPiProtonFGD2Selection.hxx"
#include "baseTrackerAnalysis.hxx"
#include "PionInteractionSystematic.hxx"
#include "SIPionSystematics.hxx"

struct PionIntInfo{
    Float_t Ratio;        
    Float_t PionMomBin;
    Float_t IntTypeFull;  
    Float_t DataXSec;
    Float_t MCXSec;
    Float_t DataXSecErr;
    Float_t MCXsecErr;
    
    PionIntInfo(){
      Ratio       = -999;
      PionMomBin  = -999;
      IntTypeFull = -999;
      DataXSec    = -999;
      MCXSec      = -999;
      
    }
    
    void UpdatePionIntInfo(Float_t InRatio, Float_t InPionMomBin, 
        Float_t InIntTypeFull, 
        Float_t InDataXSec, Float_t InMCXSec, 
        Float_t InDataXSec_ext, Float_t InMCXSec_ext, 
        Float_t InDataXSecErr 
        ){
      if (Ratio < InRatio){
        Ratio       = InRatio;
        PionMomBin  = InPionMomBin;
        IntTypeFull = InIntTypeFull;
        DataXSec    = InDataXSec;
        MCXSec      = InMCXSec;
        DataXSec    = InDataXSec_ext;
        MCXSec      = InMCXSec_ext;
        DataXSec    = InDataXSecErr;
      }
    
    }
};


class numuCCMultiPiAnalysis: public baseTrackerAnalysis {
 public:

  numuCCMultiPiAnalysis(AnalysisAlgorithm* ana=NULL);
  virtual ~numuCCMultiPiAnalysis(){
    delete _pionSIManager;
    _pionSIManager = NULL;
    delete _pionObject;
    delete _pionTrueObject;
    _pionObject    = NULL;
    _pionTrueObject = NULL;
  }

  //---- These are mandatory functions

  void DefineSelections();
  void DefineCorrections(){_numuCCAnalysis->DefineCorrections();}
  void DefineMicroTrees(bool addBase=false);
  void DefineTruthTree();

  void FillCategories();

  void FillMicroTrees(bool addBase=false);
  void FillToyVarsInMicroTrees(bool addBase=false);

  bool CheckFillTruthTree(const AnaTrueVertex& vtx);

  using baseTrackerAnalysis::FillTruthTree;
  void FillTruthTree(const AnaTrueVertex& vtx);

  //--------------------

  bool Initialize();

  const ToyBoxCCMultiPi& mybox(){return *static_cast<const ToyBoxCCMultiPi*>(&box());}

  Int_t FindTPCTracks(const ToyBoxB& box, SubDetId::SubDetEnum det, AnaTrackB** TPCtracks);
  
  /// Add all true primary pions  into the truth tree
  void AddAllTruePrimaryPionsVars(); 
  
  /// Fill truth pion info 
  /// The last parameter is
  void FillTruePionInfo(const AnaTrueVertex& vtx);
  
  void SetStoreAllTruePrimaryPions(bool set){
    _storeAllTruePrimaryPions = set;
  }
  
  bool GetStoreAllTruePrimaryPions(){
    return _storeAllTruePrimaryPions;
  }
  
  void SetAddPionSIinfo(bool add){
    _addPionSIinfo = add;
  }
  
  bool GetAddPionSIinfo(){
    return  _addPionSIinfo;
  }
  
  void InitializeAddPionSIinfo();
  
  

protected:
  Int_t _whichFGD; // 1 for FGD1 analysis, 2 for FGD2, 3 for both

  SubDetId::SubDetEnum _fgdID;

  bool _addPionSIinfo;
  
  
 
  bool _useData8GeVTablesPionSI;
 
  AnaTrack* _pionObject;
  AnaTrueParticle* _pionTrueObject;
  
  /// Pion SI manager
  PionSIManager* _pionSIManager;
  
  /// Whether to store truth info for all primary pions
  bool _storeAllTruePrimaryPions;
  
  /// Whether to store leading reco proton/pion kinematic with a vertex
  /// constraint
  
  bool _storeRecoPionProtVtx;

  bool _doMultiPi;

  bool _doMultiPiPhoton;
  
  bool _doMultiPiPhotonProton;
  
  bool _doMultiPiProton;
  
  
  /// Pion SI studies
  Float_t _xsec_data[NINTERACTIONS][NMAXMOMBINS];
  Float_t _err_data[NINTERACTIONS][NMAXMOMBINS];
  
  // As for July 2022. Two sets of tables are used for data: in psycheND280Utils: up to 8GeV and
  // more general ones in psycheSystematics, both are mostly equal,  just
  // extended binning, check both
  Float_t _xsec_data_ext[NINTERACTIONS][801];
  Float_t _err_data_ext[NINTERACTIONS][801]; 
  
  
  Float_t _xsec_mc[NINTERACTIONS][801]; // TO CHECK - DIFFERENT NUMBER OF BINS USED WRT DATA
  Float_t _err_mc[NINTERACTIONS][801]; // TO CHECK - DIFFERENT NUMBER OF BINS USED WRT DATA
 
  
  Int_t _interactionID[3];
  


  numuCCAnalysis* _numuCCAnalysis;

public:

  enum enumStandardMicroTrees_numuMultiPiAnalysis{
    HM_pos= numuCCAnalysis::enumStandardMicroTreesLast_numuCCAnalysis + 1,
    MuonVertexId,
    MuonIndex,
    NNegPion,
    NegPionMom,
    NegPionTheta, 
    NegPionPidLik,
    NegPionMipPidLik,
    NegPionTId,
    NegPionIndex,
    NegPionParentTId,
    NegPionGParentTId,
    NegPionTrueMom, 
    NegPionTrueStartDir, 
    NegPionVId,
    NegPionDir,
    NegPionPosStart,
    NegPionPosEnd,
    NPosPion,
    PosPionMom,
    PosPionTheta,
    PosPionPidLik,
    PosPionMipPidLik,
    PosPionTId,
    PosPionIndex,
    PosPionParentTId,
    PosPionGParentTId,
    PosPionTrueMom, 
    PosPionTrueStartDir, 
    PosPionVId,
    PosPionDir,
    PosPionPosStart,
    PosPionPosEnd,
    NPi0El,
    Pi0ElMom,
    Pi0ElPull,
    Pi0ElTId,
    Pi0ElIndex,
    Pi0ElParentTId,
    Pi0ElGParentTId,
    Pi0ElVId,
    Pi0ElDir,
    Pi0ElPosStart,
    Pi0ElPosEnd,
    NPi0Pos,
    Pi0PosMom,
    Pi0PosPull,
    Pi0PosTId,
    Pi0PosIndex,
    Pi0PosParentTId,
    Pi0PosGParentTId,
    Pi0PosVId,
    Pi0PosDir,
    Pi0PosPosStart,
    Pi0PosPosEnd,
    NTPCSec,
    TPCSecMom,
    TPCSecPiPidLik,
    TPCSecMuPidLik,
    TPCSecPrPidLik,
    TPCSecElPidLik,
    TPCSecDetectors,
    TPCSecQ,
    TPCSecTId,
    TPCSecIndex,
    TPCSecParentTId,
    TPCSecGParentTId,
    TPCSecDir,
    TPCSecPosStart,
    TPCSecPosEnd,
    NFGDPi,
    FGDPiLength,
    FGDPiPiPull,
    FGDPiAvgTime,
    FGDPiDistance,
    FGDPiMuonangle,
    FGDPiCosTheta,
    FGDPiTId,
    FGDPiIndex,
    FGDPiParentTId,
    FGDPiGParentTId,
    FGDPiVId,
    FGDPiDir,
    FGDPiPosStart,
    FGDPiPosEnd,
    FGDPiTimeIni,
    FGDPiTimeEnd,
    FGDPiDeltaTimeIniSelMu,
    FGDPiDeltaTimeEndSelMu,
    NFGDEl,
    FGDElLength,
    FGDElPiPull,
    FGDElAvgTime,
    FGDElDistance,
    FGDElMuonangle,
    FGDElCosTheta,
    FGDElTId,
    FGDElIndex,
    FGDElParentTId,
    FGDElGParentTId,
    FGDElVId,
    FGDElDir,
    FGDElPosStart,
    FGDElPosEnd,
    FGDElTimeIni,
    FGDElTimeEnd,
    FGDElDeltaTimeIniSelMu,
    FGDElDeltaTimeEndSelMu,
    NFGDSec,
    FGDSecLength,
    FGDSecPiPull,
    FGDSecProtPull,
    FGDSecContained,
    FGDSecAvgTime,
    FGDSecCosTheta,
    FGDSecTId,
    FGDSecIndex,
    FGDSecParentTId,
    FGDSecGParentTId,
    FGDSecDir,
    FGDSecPosStart,
    FGDSecPosEnd,
    FGDSecTimeIni,
    FGDSecTimeEnd,
    FGDSecDeltaTimeIniSelMu,
    FGDSecDeltaTimeEndSelMu,
    NME,
    MENHits,
    MERawCharge,
    MEMinTime,
    MEMaxTime,
    NTPC1Track,
    TPC1TrackMom,
    TPC1TrackCosTheta,
    TPC1TrackPhi,
    TPC1TrackVId,
    TPC1TrackTId,
    TPC1TrackParentTId,
    TPC1TrackGParentTId,
    TPC1TrackPosStart,
    TPC1TrackPosEnd,
    
    IntType,
    IntTypeFull,
    PionMomBinInt, 
    NInts, 
    DataToMCRatio,
    DataXSec,
    DataXSec_ext, 
    MCXSec,
    DataXSecErr, 
    DataXSecErr_ext, 
    MCXSecErr, 
    PionType,
    PionMom,
    NPions,
    LargestRatio,        
    LargestRatioPionMomBin,
    LargestRatioIntTypeFull,  
    LargestRatioDataXSec, 
    LargestRatioMCXSec,   
    
    
    NECalIsoObjects,
    ECalPhotonEnergy,
    ECalPhotonPositionX,
    ECalPhotonPositionY,
    ECalPhotonPositionZ,
    ECalPhotonPIDEmHip,
    ECalPhotonPIDQuality,
    ECalPhotonClustering3DSeedType, 
    ECalPhotonNHits,
    ECalPhotonDetector,

    true_nprotons,
    nProtonsTPC,
    TPCProtMom,
    TPCProtonTId,
    nProtonsFGD,
    FGDProtMom,
    FGDProtonTId,
         
    truepi_mom,
    truepi_dir,
    truepi_costheta,
    truepi_id, 
    truepi_pdg,
    
    sel_pi_mom_vertex, 
    sel_prot_mom_vertex,
    
    sel_pi_dir_vertex, 
    sel_prot_dir_vertex,
    
    sel_pi_truedir, 
    sel_prot_truedir,
    
    sel_pi_truemom, 
    sel_prot_truemom, 
   
    sel_pi_topo, 
    sel_prot_topo,
    
    sel_pi_range_vtx,
    sel_prot_range_vtx, 
    
    NTrueNegPion,
    TrueNegPionMom,
    TrueNegPionStartPos,
    TrueNegPionStartDir,
    TrueNegPionEndPos,
    
    NTruePosPion,
    TruePosPionMom,
    TruePosPionStartPos,
    TruePosPionStartDir,
    TruePosPionEndPos,

    enumStandardMicroTreesLast_numuCCMultiPiAnalysis
  };
};

#endif
