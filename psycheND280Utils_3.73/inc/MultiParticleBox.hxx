#ifndef MultiParticleBox_h
#define MultiParticleBox_h

#include "BaseDataClasses.hxx"
#include "CoreUtils.hxx"

const Int_t NMAXCANDIDATES = 50;

namespace multipart{
  // Enum to deal with pions, ecal photons, protons
  enum BoxItems{
    kBoxPions = 0, 
    kBoxProtons, 
    kBoxECalPhotons, 
    kBoxAll
  };
  
  
  
  /// This is a structure to define parameters relevant for pions selection
  /// (initially for tracker analysis) 
  /// Basically whether to fill certain variables and which type of cuts to
  /// apply
  /// It also has a reference track: e.g. the main track not to be considered as
  /// pion candidate
  struct PionSelectionParams{
    PionSelectionParams(){
      useTPCPions                 = false;
      useME                       = false;
      useFGDPions                 = false;
      useECalPions                = false;
      nRefTracks = 0; 
    }
    
    
    void Reset(){ 
      nRefTracks = 0;
    }

    bool       useTPCPions;
    bool       useME;
    bool       useFGDPions;
    bool       useECalPions;
    
    AnaTrackB* refTracks[NMAXCANDIDATES];
    Int_t nRefTracks; 
  };


  /// Sorting
  bool sortbysecdesc(const std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> > &a, 
      const std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> > &b);



  /// This is a structure to provide params relevant for protons selection 
  /// PID cuts for TPC and FGD,  reference tracks not to be considered as
  /// relevant ones
  struct ProtonSelectionParams{
    ProtonSelectionParams(){
      tpcPIDCut  = -999;
      fgd1PIDCut = -999;
      fgd2PIDCut = -999;
      nRefTracks = 0; 
    }
    
    void Reset(){ 
      nRefTracks = 0;
    }
    
    
    Float_t tpcPIDCut;
    Float_t fgd1PIDCut;
    Float_t fgd2PIDCut; 

    AnaTrackB* refTracks[NMAXCANDIDATES];
    Int_t nRefTracks; 
  }; 

  /// This is a structure to provide params relevant for ECal Photon candidates
  /// seleciton: e.g. to be used in numuCCMultiPi-Photon based analyses
  struct ECalPhotonSelectionParams{
    ECalPhotonSelectionParams(){
      PIDEmHipCut                 = -999;
      ECalMostUpstreamLayerHitCut = -999;
      ECalNHitsCut                = -999;
    }
    
    Float_t PIDEmHipCut;
    Int_t   ECalMostUpstreamLayerHitCut;
    Int_t   ECalNHitsCut;
  };


  /// This is a collection of objects useful e.g. for ToyBoxes used 
  /// for analysis which utilize various pion/proton topologies
  struct MultiParticleBox{
    MultiParticleBox(){
      nPositivePionTPCtracks = 0;
      nNegativePionTPCtracks = 0;
      nMichelElectrons       = 0;
      nIsoFGDPiontracks      = 0;
      nPosPi0TPCtracks       = 0;
      nElPi0TPCtracks        = 0;
      nIsoFGDElPi0tracks     = 0;
      nPosPions              = 0;
      nNegPions              = 0;
      nOtherPions            = 0;

      nProtonTPCtracks       = 0;
      nProtonFGDtracks       = 0;

      nECalPiontracks        = 0;

      Detector = SubDetId::kInvalid;

      anaUtils::ClearArray(PositivePionTPCtracks, NMAXCANDIDATES);
      anaUtils::ClearArray(NegativePionTPCtracks, NMAXCANDIDATES);
      anaUtils::ClearArray(MichelElectrons,       NMAXCANDIDATES);
      anaUtils::ClearArray(IsoFGDPiontracks,      NMAXCANDIDATES);
      anaUtils::ClearArray(PosPi0TPCtracks,       NMAXCANDIDATES);
      anaUtils::ClearArray(ElPi0TPCtracks,        NMAXCANDIDATES);
      anaUtils::ClearArray(IsoFGDElPi0tracks,     NMAXCANDIDATES);

      anaUtils::ClearArray(ProtonTPCtracks,       NMAXCANDIDATES);
      anaUtils::ClearArray(ProtonFGDtracks,       NMAXCANDIDATES);
      
      anaUtils::ClearArray(ECalPiontracks,        NMAXCANDIDATES);
      
      anaUtils::ClearArray(ECalPhotons,           NMAXCANDIDATES);

      for (int i = 0; i < NMAXCANDIDATES; i++){
        
        IsoFgdProtonMomVertex[i] = -999;
        
        IsoFgdPionMomVertex[i]   = -999;
        
        for (int j = 0; j < 3; j++){
          IsoFgdProtonDirVertex[i][j] = -999;
          IsoFgdPionDirVertex[i][j]   = -999;
        }
      }
      
      
      ECalPi0Photon = NULL;

      Vertex = NULL;
      
      nECalPhotons = 0;

    }

    virtual ~MultiParticleBox(){
      Reset();
    }

    void Reset(){
      anaUtils::ClearArray(PositivePionTPCtracks, NMAXCANDIDATES);
      anaUtils::ClearArray(NegativePionTPCtracks, NMAXCANDIDATES);
      anaUtils::ClearArray(MichelElectrons,       NMAXCANDIDATES);
      anaUtils::ClearArray(IsoFGDPiontracks,      NMAXCANDIDATES);
      anaUtils::ClearArray(PosPi0TPCtracks,       NMAXCANDIDATES);
      anaUtils::ClearArray(ElPi0TPCtracks,        NMAXCANDIDATES);
      anaUtils::ClearArray(IsoFGDElPi0tracks,     NMAXCANDIDATES);


      anaUtils::ClearArray(ProtonTPCtracks,       NMAXCANDIDATES);
      anaUtils::ClearArray(ProtonFGDtracks,       NMAXCANDIDATES);
      
      anaUtils::ClearArray(ECalPiontracks,        NMAXCANDIDATES);
      
      anaUtils::ClearArray(ECalPhotons,        NMAXCANDIDATES);

      for (int i = 0; i < NMAXCANDIDATES; i++){
        
        IsoFgdProtonMomVertex[i] = -999;
        
        IsoFgdPionMomVertex[i]   = -999;
        
        for (int j = 0; j < 3; j++){
          IsoFgdProtonDirVertex[i][j] = -999;
          IsoFgdPionDirVertex[i][j]   = -999;
        }  
      }
     
      nPositivePionTPCtracks = 0;
      nNegativePionTPCtracks = 0;
      nMichelElectrons       = 0;
      nIsoFGDPiontracks      = 0;
      nPosPi0TPCtracks       = 0;
      nElPi0TPCtracks        = 0;
      nIsoFGDElPi0tracks     = 0;
      nPosPions              = 0;
      nNegPions              = 0;
      nOtherPions            = 0;

      ECalPi0Photon = NULL;

      Vertex = NULL;

      nProtonTPCtracks       = 0;
      nProtonFGDtracks       = 0;
      
      nECalPiontracks = 0;
      
      nECalPhotons = 0;

    }
    /// Get most energetic TPC positive pion candidate
    AnaTrackB* GetHMPosTPCPion();

    /// Get most energetic TPC proton candidate
    AnaTrackB* GetHMTPCProton();  

    /// Get most energetic TPC negative pion candidate
    AnaTrackB* GetHMNegTPCPion();

    /// Get most energetic proton candidate no matter TPC or FGD it is 
    AnaTrackB* GetHMProton();

    /// Get most energetic pion candidate no matter TPC or FGD it is 
    AnaTrackB* GetHMPion();


    /// Get most energetic proton candidate no matter TPC or FGD it is, fill the
    /// momentum as well so that it can be used later this is needed since the
    /// momentum may be the one corrected to the vertex
    /// the direction is filled as well
    AnaTrackB* GetHMProton(Float_t& momentum, Float_t* dir);

    /// Get most energetic proton candidate no matter TPC or FGD it is, fill the
    /// momentum as well so that it can be used later this is needed since the
    /// momentum may be the one corrected to the vertex 
    /// the direction is filled as well
    AnaTrackB* GetHMPion(Float_t& momentum, Float_t* dir);

    /// Get the selected pion topology (more relevant for the 1pi ones!!)
    SelTopoId::SelTopoPionEnum GetPionTopo();

    /// Get the selected proton topology
    SelTopoId::SelTopoProtonEnum GetProtonTopo();


    /// Correct momentum for FGD iso pions for the reco vertex 
    void FillFgdIsoPionsKinematicsVertex();

    // Correct momentum for FGD iso protons for the reco vertex 
    void FillFgdIsoProtonsKinematicsVertex();


    /// Positive  TPC pion candidates 
    AnaTrackB* PositivePionTPCtracks[NMAXCANDIDATES];
    int nPositivePionTPCtracks;

    /// Negative TPC pion candidates 
    AnaTrackB* NegativePionTPCtracks[NMAXCANDIDATES];
    int nNegativePionTPCtracks;

    ///  Michel Electron candidates 
    AnaFgdTimeBinB* MichelElectrons[NMAXCANDIDATES];
    int nMichelElectrons;

    /// IsoFGD Pion candidates 
    AnaTrackB* IsoFGDPiontracks[NMAXCANDIDATES];
    int nIsoFGDPiontracks;

    /// Momentum corrected to the vertex
    Float_t IsoFgdPionMomVertex[NMAXCANDIDATES];
    
    /// Angles corrected for the presence of vertex - in order one flips a
    /// direction
    Float_t IsoFgdPionDirVertex[NMAXCANDIDATES][3];
    
    /// An utility function to sort iso fgd tracks based on momentum corrected
    /// to the vertex
    void SortIsoFgdPionsByVertexMom();

    /// Electrons and positrons from Pio in the TPC
    AnaTrackB* PosPi0TPCtracks[NMAXCANDIDATES];
    AnaTrackB* ElPi0TPCtracks[NMAXCANDIDATES];
    int nPosPi0TPCtracks;
    int nElPi0TPCtracks;

    /// IsoFGD electron and positron candidates 
    AnaTrackB* IsoFGDElPi0tracks[NMAXCANDIDATES];
    int nIsoFGDElPi0tracks;

    AnaTrackB* ECalPi0Photon;


    int nPosPions;
    int nNegPions;
    int nOtherPions;

    /// The vertex corresponding to the box
    AnaVertexB* Vertex;

    /// Proton candidates
    AnaTrackB* ProtonTPCtracks[NMAXCANDIDATES];
    int nProtonTPCtracks;

    AnaTrackB* ProtonFGDtracks[NMAXCANDIDATES];
    int nProtonFGDtracks;

    /// Momentum corrected to the vertex
    Float_t IsoFgdProtonMomVertex[NMAXCANDIDATES];
     
    /// Angle corrected for the presence of vertex - in order one flips a
    /// direction
    Float_t IsoFgdProtonDirVertex[NMAXCANDIDATES][3];

    /// An utility function to sort iso fgd tracks based on momentum corrected
    /// to the vertex
    void SortIsoFgdProtonsByVertexMom();
    
    /// ECal pion candidates
    AnaTrackB* ECalPiontracks[NMAXCANDIDATES];
    int nECalPiontracks;
    
    /// ECal photon candidates
    /// The box owns these objects
    AnaTrackB* ECalPhotons[NMAXCANDIDATES];
    int nECalPhotons;
    
    SubDetId::SubDetEnum Detector;

  };
};
#endif
