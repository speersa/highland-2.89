//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Mar 26 15:46:42 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90800000-0000_ztbqgqmrv5iz_anal_000_magnet201508airrun8-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule_h
#define ND__TGlobalReconModule_h
namespace ND {
class TGlobalReconModule;
} // end of namespace.

#include "ND__TAnalysisReconModuleBase.h"
#include "Riostream.h"
#include <vector>
#include "TClonesArray.h"
#include "ND__TGlobalReconModule.h"
#include "TObject.h"
#include <string>
#include "TLorentzVector.h"
#include "ND__TTrueVertex.h"
#include "TVector3.h"
#include <utility>
#include "TVector2.h"
#include "ND__TTrueParticle.h"
#include "ND__TSubBaseObject.h"
#include "ND__TSubBaseShowerObject.h"

namespace ND {
class TGlobalReconModule : public ND::TAnalysisReconModuleBase {

public:
// Nested classes forward declaration.
class TGlobalVertex;
class TVertexConstituent;
class TFgdTimeBin;
class TOutermostHits;
class TGlobalHit;
class TGlobalPID;
class TTPCObject;
class TFGDObject;
class TECALObject;
class TP0DObject;
class TSMRDObject;
class TTrackerObject;
class TGlobalPIDAlternate;
class TTPCOtherObject;
class TSMRDHit;

public:
// Nested classes declaration.
class TSMRDHit : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         Wall;        ///< SMRD wall number, 0=Top, 1=Bottom, 2= Right, 3= Left.
   int         Yoke;        ///< Yoke ring number.
   int         Layer;       ///< SMRD ring number.
   int         Tower;       //
   int         Counter;     ///< SMRD scint number.
   double      Charge;      ///< Deposited charge
   double      Time;        ///< The time
   TVector3    Position;    ///< The position
   TVector3    PositionError;    ///< The position variance;
   int         Type;             ///< the hit type (0=X,1=Y,2=Z)

   TSMRDHit();
   TSMRDHit(const TSMRDHit & );
   virtual ~TSMRDHit();

   ClassDef(TSMRDHit,2); // Generated by MakeProject.
};
class TTPCOtherObject : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Charge;      //
   int         Detector;    //
   int         NHits;       //
   double      Chi2;        //
   double      EDeposit;    //
   TLorentzVector FrontPosition;    ///< The Front position of the object.
   TLorentzVector BackPosition;     ///< The Back position of the object.
   TVector3       FrontDirection;    ///< The Front direction of the object.
   TVector3       BackDirection;     ///< The Back direction of the object.
   double         Momentum;          ///< the momentum of the object
   ND::TTrueParticle TrueParticle;      ///< The true particle

   TTPCOtherObject();
   TTPCOtherObject(const TTPCOtherObject & );
   virtual ~TTPCOtherObject();

   ClassDef(TTPCOtherObject,2); // Generated by MakeProject.
};
class TGlobalPIDAlternate : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned long Detectors;    ///< Detectors used, defined according to the formula in GetDetectorNumber.
   bool          DetectorUsed[19];    ///< Detectors used (NDETSUSED = 19)
   unsigned long Status;              ///< The status for the fit.
   int           NDOF;                ///< The number of degrees of freedom.
   double        Chi2;                ///< The chi2 of the fit.
   double        Charge;              ///< The Charge
   double        Length;              ///< The length of the track or shower (RMS)
   int           ParticleId;          ///< the PDG code obtained in the recon combined PID
   double        PIDWeight;           ///< the PID weight for this hypothesis
   TLorentzVector FrontPosition;       ///< The position of the object.
   TLorentzVector BackPosition;        ///< The position of the object.
   TLorentzVector FrontPositionVar;    ///< The position variance;
   TLorentzVector BackPositionVar;     ///< The position variance;
   TVector3       FrontDirection;      ///< The direction of the object.
   TVector3       BackDirection;       ///< The direction of the object.
   TVector3       FrontDirectionVar;    ///< The direction variance of the object.
   TVector3       BackDirectionVar;     ///< The direction variance of the object.
   double         FrontMomentum;        ///< the momentum of the object
   double         BackMomentum;         ///< the momentum of the object
   double         FrontMomentumError;    ///< the error on the momentum of the object
   double         BackMomentumError;     ///< the error on the momentum of the object
   TLorentzVector PositionAtTrueVertex;    ///< The position at the true vertex.
   TLorentzVector PositionVarAtTrueVertex;    ///< The position variance at the true vertex.
   TVector3       DirectionAtTrueVertex;      ///< The direction at the true vertex.
   TVector3       DirectionVarAtTrueVertex;    ///< The direction variance at the true vertex.
   double         MomentumAtTrueVertex;        ///< The momentum at the true vertex.
   double         MomentumErrorAtTrueVertex;    ///< The error of the momentum at the true vertex.

   TGlobalPIDAlternate();
   TGlobalPIDAlternate(const TGlobalPIDAlternate & );
   virtual ~TGlobalPIDAlternate();

   ClassDef(TGlobalPIDAlternate,2); // Generated by MakeProject.
};
class TTrackerObject : public ND::TSubBaseObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Charge;      //
   int         matchingFailure_flag;    //

   TTrackerObject();
   TTrackerObject(const TTrackerObject & );
   virtual ~TTrackerObject();

   ClassDef(TTrackerObject,2); // Generated by MakeProject.
};
class TSMRDObject : public ND::TSubBaseObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      avgtime;     //Avergaed light-propagation corrected hit time

   TSMRDObject();
   TSMRDObject(const TSMRDObject & );
   virtual ~TSMRDObject();

   ClassDef(TSMRDObject,2); // Generated by MakeProject.
};
class TP0DObject : public ND::TSubBaseShowerObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Width;       ///< The width of the shower (perpendicular to the direction)
   double      avgtime;     ///< Averaged, corrected node time.
   vector<int> ParticleId;    ///< A vector of potential PIDs, sorted by weight
   vector<double> PIDWeight;     //

   TP0DObject();
   TP0DObject(const TP0DObject & );
   virtual ~TP0DObject();

   ClassDef(TP0DObject,2); // Generated by MakeProject.
};
class TECALObject : public ND::TSubBaseShowerObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      TrShVal;     ///< Value to seperate track from shower
   double      EMHadVal;    ///< Value to seperate EM from Hadronic.
   double      LLR_MIP_EM;    ///< Value to separate MIP-like objects (e.g. muons) from EM showers (e.g. photons/electrons). -9999 indicates an error.
   double      LLR_MIP_Pion;    ///< Value to separate MIP-like objects (e.g. muons) from showering pions. -9999 indicates an error.
   double      LLR_EM_HIP;      ///< Value to separate light tracks/MIP-like objects (e.g. muons) from heavy tracks / Highly-ionising particles (specifically proton). -9999 indicates an error.
   TVector3    Width;           ///< The width of track
   double      AverageHitTime;    ///< The charged weighted average time for the ECal cluster
   double      EMEnergy;          ///< fitted em energy for the shower
   double      EMEnergyError;     //
   double      KFParameter;       ///< The Kalman Fitter Pid variables
   int         KFNNodes;          ///< The Kalman Fitter Pid variables
   double      KFParameterNodes;    ///< The Kalman Fitter Pid variables
   double      KFQuality;           ///< The Kalman Fitter Pid variables
   int         KFNDOF;              ///< The Kalman Fitter Pid variables
   double      KFHitQuality;        ///< The Kalman Fitter Pid variables
   double      MElectronTag_NDelayedCluster;    ///< Michel Electron Delayed Cluster Variables
   vector<double> MElectronTag_NDelayedHits;       ///< The number of hits in a Michel electron candidate.
   vector<double> MElectronTag_DeltaX;             ///< The X displacement of the Michel electron candidate from the original ECal cluster.
   vector<double> MElectronTag_DeltaY;             ///< The Y displacement of the Michel electron candidate from the original ECal cluster.
   vector<double> MElectronTag_DeltaZ;             ///< The Z displacement of the Michel electron candidate from the original ECal cluster.
   vector<double> MElectronTag_DeltaT;             ///< The time displacement of the Michel electron candidate from the original ECal cluster.
   vector<double> MElectronTag_EDep;               ///< The energy deposited by the Michel electron candidate.
   vector<double> MElectronTag_TrackEnd;           ///<MElectronTag_TrackEnd refers to which end of the Cluster the MichelCandidate was observed; +1 means it was observed at the outermost end (the end with the highest layer number), -1 means the innermost end (lowest layer number)
   double         EMEnergy_Likelihood_energyGrad;    ///< EM energy fit likelihood variables.
   double         EMEnergy_Likelihood_energy_qsumGrad;    ///< EM energy fit likelihood variables.
   double         EMEnergy_Likelihood_qsum_like;          ///< EM energy fit likelihood variables.
   double         EMEnergy_Para_QSum;                     ///< EM energy fit parameter variables.
   double         EMEnergy_Para_QMean;                    ///< EM energy fit parameter variables.
   double         EMEnergy_Para_QRMS;                     ///< EM energy fit parameter variables.
   double         EMEnergy_Para_QSkew;                    ///< EM energy fit parameter variables.
   double         EMEnergy_Para_QMax;                     ///< EM energy fit parameter variables.
   int            IsShowerLike;                           ///< Has the value 1 if this is a shower according to ecalRecon with default cuts.
   int            IsTrackLike;                            ///< Has the value 1 if this is a track according to ecalRecon with default cuts.
   double         PID_AMR;                                ///< Comparison of an objects width to length
   double         PID_Angle;                              ///< The zenith angle with respect to each detector.
   double         PID_Max_Ratio;                          ///< The ratio of highest layer charge and the smallest layer charge
   double         PID_ShowerAngle;                        ///< The angle from the start of an object to its width at its charge centre
   double         PID_Asymmetry;                          ///< Ratio of the big width of an object by its small width.
   double         PID_MeanPosition;                       ///< The charge weight position with respect to the object start position.
   double         PID_ShowerWidth;                        ///< Width at the charge centre
   int            mostUpStreamLayerHit;                   ///< ECal layer hit info
   int            mostDownStreamLayerHit;                 ///< ECal layer hit info

   TECALObject();
   TECALObject(const TECALObject & );
   virtual ~TECALObject();

   ClassDef(TECALObject,2); // Generated by MakeProject.
};
class TFGDObject : public ND::TSubBaseObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      avgtime;     ///< Average fully corrected FGD hit time.
   float       chargePerLayer[30];    //
   float       chargePerLayerAttenCorr[30];    //
   int         fgdContainment;                 ///< Fully contained PID information. Indicates whether the FGD PID algorithm determined the track to be fully contained in FGD1 or FGD2 (=1 or 2), stopping in FGD1 or FGD2 (=-1 or -2), or other (0).
   double      E;                              ///< Measured energy in an FGD.
   double      x;                              ///< Distance traveled in an FGD.
   double      E_exp_muon;                     ///< Expected energy deposit for a muon.
   double      E_exp_pion;                     ///< Expected energy deposit for a pion.
   double      E_exp_proton;                   ///< Expected energy deposit for a proton.
   double      sigmaE_muon;                    ///< Expected energy uncertainty for a muon.
   double      sigmaE_pion;                    ///< Expected energy uncertainty for a pion.
   double      sigmaE_proton;                  ///< Expected energy uncertainty for a proton.
   double      PullMuon;                       ///< The FGD PID pull value for a muon.
   double      PullPion;                       ///< The FGD PID pull value for a pion.
   double      PullProton;                     ///< The FGD PID pull value for a proton.
   double      PullNotSet;                     ///< PullNotSet = 1 if the pull is not set, and 0 otherwise.
   bool        isFgdVA;                        //
   bool        isFgdVA_flag;                   //
   int         globpassVA_flag;                /// FGD vertex activity Vertex (1) or Entrance (2)
   double      fgdVA_upMinZ;                   ///< FGD vertex activity values.
   double      fgdVA_downMaxZ;                 ///< FGD vertex activity values.
   double      fgdVA_upCosTheta;               ///< FGD vertex activity values.
   double      fgdVA_downCosTheta;             ///< FGD vertex activity values.
   double      fgdVA_otherUpQ;                 ///< FGD vertex activity values.
   double      fgdVA_otherDownQ;               ///< FGD vertex activity values.
   double      fgdVA_verQ;                     ///< FGD vertex activity values.
   double      fgdVA_verLayQ;                  ///< FGD vertex activity values.
   double      fgdVA_verNearQ;                 ///< FGD vertex activity values.
   double      fgdVA_verNextNearQ;             ///< FGD vertex activity values.
   double      fgdVA_verNextNextNearQ;         ///< FGD vertex activity values.
   double      fgdVA_verNearQ_rect;            ///< FGD vertex activity 2x3.
   double      fgdVA_verNextNearQ_rect;        ///< FGD vertex activity 2x5.
   double      fgdVA_verNextNextNearQ_rect;    ///< FGD vertex activity 2x7.
   double      fgdVA_totalQ;                   ///< FGD vertex activity values.
   double      fgdVA_totalCorrE;               ///< FGD vertex activity values.
   bool        isFgdEA;                        //
   bool        isFgdEA_flag;                   //
   int         globpassEA_flag;                /// FGD end activity End (1) or Exit (2)
   double      fgdEA_otherUpQ;                 ///< FGD end activity values.
   double      fgdEA_otherDownQ;               ///< FGD end activity values.
   double      fgdEA_verQ;                     ///< FGD end activity values.
   double      fgdEA_verLayQ;                  ///< FGD end activity values.
   double      fgdEA_verNearQ;                 ///< FGD end activity values.
   double      fgdEA_verNextNearQ;             ///< FGD end activity values.
   double      fgdEA_verNextNextNearQ;         ///< FGD end activity values.
   double      fgdEA_verNearQ_rect;            ///< FGD end activity values.
   double      fgdEA_verNextNearQ_rect;        ///< FGD end activity values.
   double      fgdEA_verNextNextNearQ_rect;    ///< FGD end activity values.
   vector<int> fgdhits_Layer;                  //
   vector<TVector3> fgdhits_Position;               //
   vector<float>    fgdhits_Time;                   //
   vector<float>    fgdhits_Charge;                 //
   vector<int>      fgdhits_TrajID;                 //

   TFGDObject();
   TFGDObject(const TFGDObject & );
   virtual ~TFGDObject();

   ClassDef(TFGDObject,2); // Generated by MakeProject.
};
class TTPCObject : public ND::TSubBaseObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Charge;      ///< Charge from the TPC pid (+1, or -1)
   double      NTrun;       ///< 70% of the number of cluster
   double      Ccorr;       ///< Corrected truncated mean charge deposit in PID
   double      PullEle;     ///< Pull for TPC pid electron hypothesis
   double      PullMuon;    ///< Pull for TPC pid muon hypothesis
   double      PullPion;    ///< Pull for TPC pid pion hypothesis
   double      PullKaon;    ///< Pull for TPC pid kaon hypothesis
   double      PullProton;    ///< Pull for TPC pid proton hypothesis
   double      dEdxexpEle;    ///< Estimated dE/dx for electron hypothesis
   double      dEdxexpMuon;    ///< Estimated dE/dx for muon hypothesis
   double      dEdxexpPion;    ///< Estimated dE/dx for pion hypothesis
   double      dEdxexpKaon;    ///< Estimated dE/dx for kaon hypothesis
   double      dEdxexpProton;    ///< Estimated dE/dx for proton hypothesis
   double      SigmaEle;         ///< Sigma estimated width of TPC pid electron hypothesis
   double      SigmaMuon;        ///< Sigma estimated width of TPC pid muon hypothesis
   double      SigmaPion;        ///< Sigma estimated width of TPC pid pion hypothesis
   double      SigmaKaon;        ///< Sigma estimated width of TPC pid kaon hypothesis
   double      SigmaProton;      ///< Sigma estimated width of TPC pid proton hypothesis
   vector<int> T0Source;         ///< The T0Source, the values are defined in TTPCFitStatusBranch.hxx, the TTPCT0Source enumeration.
   vector<int> NHorRows;         ///< The number of horizontal clusters in the track
   vector<int> NVerRows;         ///< The number of vertical clusters in the track
   double      PDist;            ///< Placeholder for momentum of BField refit.
   double      PEField;          ///< Placeholder for momentum of EField refit.
   double      TPCLength;        ///< TPC track length.
   int         KalmanFitType;    ///< Record of why the track was refit with a kalman filter fit instead of the likelihood fit.

   TTPCObject();
   TTPCObject(const TTPCObject & );
   virtual ~TTPCObject();

   ClassDef(TTPCObject,2); // Generated by MakeProject.
};
class TGlobalPID : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   UInt_t      UniqueID;    ///< Unique identifier for global recon objects (needed fro broken association)
   vector<UInt_t> BrokenUniqueIDs;    ///< the broken partners unique IDs
   string         AlgorithmName;      ///< The name of the algorithm that created this object.
   unsigned long  Detectors;          ///<     Detectors used
   bool           DetectorUsed[19];    ///< Detectors used. Index order from 0 to 18: [TPC1, TPC2, TPC3, FGD1, FGD2,P0D, DSECal, TopSMRD, BottomSMRD, LeftSMRD, RightSMRD, TopPECal, BottomPECal, LeftPECal, RightPECal, TopTECal, BottomTECal, LeftTECal, RightTECal].
   unsigned long  Status;              ///< The status for the fit.
   int            NDOF;                ///< The number of degrees of freedom.
   double         Chi2;                ///< The chi2 of the fit.
   int            NNodes;              ///< The number of nodes.
   int            NHits;               ///< The number of hits.
   int            NConstituents;       ///< The number of constituents.
   bool           isForward;           ///< Sense of object.
   bool           SenseOK;             ///< Sense of object.
   bool           IsCurvBack;          ///< A curving-back object
   bool           IsFgdECalIncremental;    ///< A track created by FGD-ECal matching algorithm
   double         Charge;                  ///< The Charge
   double         EDeposit;                ///< The deposited charge for the object.
   TVector3       Cone;                    ///< The opening angles of the cone (only for showers)
   double         Width;                   ///< The width of the shower (perpendicular to the direction)
   double         Length;                  ///< The length of the track or shower (RMS)
   vector<int>    ParticleIds;             ///< the PDG codes obtained in the recon combined PID
   vector<double> PIDWeights;              ///< the PID likelihoods for combined PID
   TLorentzVector FrontPosition;           ///< The position of the object.
   TLorentzVector BackPosition;            ///< The position of the object
   TVector3       FrontDirection;          ///< The direction of the object.
   TVector3       BackDirection;           ///< The direction of the object.
   double         FrontMomentum;           ///< the momentum of the object
   double         FrontCharge;             ///< the charge of the object at the first state
   double         BackMomentum;            ///< the momentum of the object
   double         BackCharge;              ///< the momentum of the object at the back state
   double         FrontMomentumError;      ///< the error on the momentum of the object
   double         BackMomentumError;       ///< the error on the momentum of the object
   double         FrontStateCov[7][7];     ///< full covariance matrix for front state: pos,  dir, q/p
   double         BackStateCov[7][7];      ///< full covariance matrix for last state: pos, dir, q/p
   double         RangeMomentumMuon;       ///< the momentum by range for the muon hypothesis
   double         RangeMomentumMuonFlip;    ///< the momentum by range for the flipped muon hypothesis
   double         RangeMomentumElectron;    ///< the momentum by range for the electron hypothesis
   double         RangeMomentumElectronFlip;    ///< the momentum by range for the flipped electron hypothesis
   double         RangeMomentumProton;          ///< the momentum by range for the proton hypothesis
   double         RangeMomentumProtonFlip;      ///< the momentum by range for the flipped proton hypothesis
   vector<pair<int,TVector2> > NodeTimes;                    ///< vector of pairs, sub-detecor number and time-stamps of edge nodes in this subdetector
   TLorentzVector              PositionAtTrueVertex;         ///< Position at the true vertex.
   TVector3                    DirectionAtTrueVertex;        ///< Direction at the true vertex.
   double                      MomentumAtTrueVertex;         ///< Momentum at the true vertex.
   double                      MomentumErrorAtTrueVertex;    ///< Error of the momentum at the true vertex.
   double                      ChargeAtTrueVertex;           ///< Charge at the true vertex.
   double                      StateCovAtTrueVertex[7][7];    ///< Full covariance matrix for the state: pos,  dir, q/p at the true vertex.
   int                         EntranceOK[25];                ///< Status of the subdetector entrance.
   int                         ExitOK[25];                    ///< Status of the subdetector exit.
   TLorentzVector              EntrancePosition[25];          ///< The position of the object at the entrance of each subdetector.
   TLorentzVector              ExitPosition[25];              ///< The position of the object at the exit of each subdetector.
   TVector3                    EntranceDirection[25];         ///< The direction of the object at the entrance of each subdetector volume.
   TVector3                    ExitDirection[25];             ///< The direction of the object at the exit of each subdetector.
   double                      EntranceMomentum[25];          ///< The momentum of the object at the entrance of each subdetector.
   double                      ExitMomentum[25];              ///< The momentum of the object at the exit of each subdetector.
   TLorentzVector              EntrancePositionErr[25];       ///< The error of the position of the object at the entrance of each subdetector.
   TLorentzVector              ExitPositionErr[25];           ///< The error of the position of the object at the exit of each subdetector.
   TVector3                    EntranceDirectionErr[25];      ///< The error of the direction of the object at the entrance of each subdetector.
   TVector3                    ExitDirectionErr[25];          ///< The error of the direction of the object at the exit of each subdetector.
   double                      EntranceMomentumErr[25];       ///< The error of the momentum of the object at the entrance of each subdetector.
   double                      ExitMomentumErr[25];           ///< The error of the momentum of the object at the exit of each subdetector.
   Int_t                       NHitsSaved;                    ///< Number of entries in the HitsSaved array.
   TClonesArray*               HitsSaved;                     ///< the two first and two last hits (TGlobalHit).
   ND::TTrueParticle           TrueParticle;                  ///< The true particle
   Int_t                       NTRACKERs;                     ///< Number of Tracker objects.
   TClonesArray*               TRACKER;                       ///< Tracker specific variables.
   Int_t                       NTPCs;                         ///< Number of TPC objects.
   TClonesArray*               TPC;                           ///< TPC specific variables.
   Int_t                       NFGDs;                         ///< Number of FGD objects.
   TClonesArray*               FGD;                           ///< FGD specific variables.
   Int_t                       NECALs;                        ///< Number of ECAL objects.
   Int_t                       NDsECALs;                      ///< Number of DsECAL objects.
   Int_t                       NTrECALs;                      ///< Number of TrECAL objects.
   TClonesArray*               ECAL;                          ///< ECAL specific variables.
   Int_t                       NP0DECALs;                     ///< Number of P0DECAL objects.
   TClonesArray*               P0DECAL;                       ///< P0DECAL specific variables.
   Int_t                       NP0Ds;                         ///< Number of P0D objects.
   TClonesArray*               P0D;                           ///< P0D specific variables.
   Int_t                       NSMRDs;                        ///< Number of SMRD objects.
   TClonesArray*               SMRD;                          ///< SMRD specific variables.
   Int_t                       NAlternates;                   ///< Number of entries in the alternate hypotheses list.
   TClonesArray*               Alternates;                    ///< List of alternate hypotheses
   ND::TGlobalReconModule::TTPCObject hackTPCObject;                 ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TFGDObject hackFGDObject;                 ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TECALObject hackECALObject;                ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TP0DObject  hackP0DObject;                 ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TSMRDObject hackSMRDObject;                ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TTrackerObject hackTrackerObject;             ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TGlobalPIDAlternate hackGlobalPIDAlternate;        ///< This is just here to fool TFile::MakeProject, not a real object.

   TGlobalPID();
   TGlobalPID(const TGlobalPID & );
   virtual ~TGlobalPID();

   ClassDef(TGlobalPID,2); // Generated by MakeProject.
};
class TGlobalHit : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Charge;      ///< Deposited charge
   double      Time;        ///< The time
   TVector3    Position;    ///< The position
   TVector3    PositionError;    ///< The position variance;
   int         Type;             ///< the hit type (0=X,1=Y,2=Z)

   TGlobalHit();
   TGlobalHit(const TGlobalHit & );
   virtual ~TGlobalHit();

   ClassDef(TGlobalHit,2); // Generated by MakeProject.
};
class TOutermostHits : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   ND::TGlobalReconModule::TGlobalHit hitMinX;     ///< Hit with lowest X position.
   ND::TGlobalReconModule::TGlobalHit hitMaxX;     ///< Hit with highest X position.
   ND::TGlobalReconModule::TGlobalHit hitMinY;     ///< Hit with lowest Y position.
   ND::TGlobalReconModule::TGlobalHit hitMaxY;     ///< Hit with highest Y position.
   ND::TGlobalReconModule::TGlobalHit hitMinZ;     ///< Hit with lowest Z position.
   ND::TGlobalReconModule::TGlobalHit hitMaxZ;     ///< Hit with highest Z position.

   TOutermostHits();
   TOutermostHits(const TOutermostHits & );
   virtual ~TOutermostHits();

   ClassDef(TOutermostHits,2); // Generated by MakeProject.
};
class TFgdTimeBin : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      minTime;     ///< Bin start time.
   double      maxTime;     ///< Bin end time.
   int         nHits[2];    //
   double      rawChargeSum[2];    //
   float       chargePerLayer[2][30];    //
   TVector3    chargeWeightedPos[2];     //
   ND::TGlobalReconModule::TOutermostHits FGD1OutermostHits;        //
   ND::TGlobalReconModule::TOutermostHits FGD2OutermostHits;        //
   vector<int>                            FGD1HitLayer;             //
   vector<float>                          FGD1HitPosition;          //
   vector<float>                          FGD1HitQ;                 //
   vector<float>                          FGD1HitT;                 //
   vector<int>                            FGD1HitTrajID;            //
   vector<int>                            FGD2HitLayer;             //
   vector<float>                          FGD2HitPosition;          //
   vector<float>                          FGD2HitQ;                 //
   vector<float>                          FGD2HitT;                 //
   vector<int>                            FGD2HitTrajID;            //
   Int_t                                  NFGD1Unused;              ///<   Number of hits unused in FGD1
   TClonesArray*                          FGD1Unused;               ///<   The vector unused hits in FGD1
   Int_t                                  NFGD2Unused;              ///<   Number of hits unused in FGD2
   TClonesArray*                          FGD2Unused;               ///<   The vector unused hits in FGD2
   int                                    g4ID;                     ///< The ID for the G4 trajectory that contributed most to this time bin.
   ND::TGlobalReconModule::TGlobalHit     hackFGDUnused;            ///< This is just here to fool TFile::MakeProject, not a real object.

   TFgdTimeBin();
   TFgdTimeBin(const TFgdTimeBin & );
   virtual ~TFgdTimeBin();

   ClassDef(TFgdTimeBin,2); // Generated by MakeProject.
};
class TVertexConstituent : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         Charge;      ///< Charge of constituent tracks
   double      Quality;     ///< Quality (chi2) of constituent tracks
   TVector3    Momentum;    ///< 3-momentum of constituent tracks
   int         PID;         ///< The TGlobalPIDs associated to the vertex

   TVertexConstituent();
   TVertexConstituent(const TVertexConstituent & );
   virtual ~TVertexConstituent();

   ClassDef(TVertexConstituent,2); // Generated by MakeProject.
};
class TGlobalVertex : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         PrimaryIndex;    ///< The index of the corresponding primary vertex
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   int         Status;           ///< The status for the fit.
   double      Quality;          ///< The quality of the fit.
   int         NDOF;             ///< The number of degrees of freedom.
   TLorentzVector Position;         ///< The position of the vertex.
   TLorentzVector Variance;         ///< The position variance;
   Int_t          NTrueVertices;    ///< The true vertex
   TClonesArray*  TrueVertices;     ///< The true vertex
   Int_t          NConstituents;    ///< Constituent tracks
   TClonesArray*  Constituents;     ///< Constituent tracks
   ND::TTrueVertex hackTrueVertexObject;    ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TVertexConstituent hackVertexConstituentObject;    //

   TGlobalVertex();
   TGlobalVertex(const TGlobalVertex & );
   virtual ~TGlobalVertex();

   ClassDef(TGlobalVertex,2); // Generated by MakeProject.
};

public:
// Data Members.
   bool        fRecPackInitialized;    //
   vector<string> fALLMODULES;            //
   bool           fPassedDetector[25];    //
   bool           fTestTPCInfo;           ///< For tests only.
   Int_t          fNTPCPIDs;              ///< For tests only.
   TClonesArray*  fTPCPIDs;               ///< For tests only (TTpcPID).
   Int_t          fNVertices;             ///< The number of added primary vertices.
   TClonesArray*  fVertices;              ///< The TGlobalVertex vector of vertices.
   Int_t          fPVInd;                 ///< The last primary vertex index.
   Int_t          fNSVertices;            ///< Number of added secondary vertices.
   Int_t          fNPIDs;                 ///< The number of global objects.
   TClonesArray*  fPIDs;                  ///< The vector of TGlobalPID.
   Int_t          fNTPCOthers;            ///< The number of TPC other objects.
   TClonesArray*  fTPCOthers;             ///<  The vector of TPC other objects (TTPCOtherObject).
   Int_t          fNTPCUnused;            ///<  Number of hits unused in the TPC.
   Int_t          fNFGD1Unused;           ///<  Number of hits unused in the FGD1.
   Int_t          fNFGD2Unused;           ///<  Number of hits unused in the FGD2.
   Int_t          fNP0DUnused;            ///<  Number of hits unused in the P0D.
   TClonesArray*  fP0DUnused;             ///<  The vector unused hits in the P0D (TGlobalHit).
   TClonesArray*  fSMRDUnused;            ///<  The vector unused hits in the SMRD (TSMRDHit).
   Int_t          fNSMRDTopUnused;        ///<  Number of hits unused in the SMRDTop.
   Int_t          fNSMRDBottomUnused;     ///<  Number of hits unused in the SMRDBottom.
   Int_t          fNSMRDLeftUnused;       ///<  Number of hits unused in the SMRDLeft.
   Int_t          fNSMRDRightUnused;      ///< Number of hits unused in the SMRDRight.
   Int_t          fNSMRDUnused;           ///<  Number of all hits unused in the SMRD
   ND::TGlobalReconModule::TOutermostHits fP0DOutermostHits;      ///< Outermost hits in the P0D.
   double                                 fEarliestTrackMedianHitTime;    ///<  Median hit time of the earliest track.
   Int_t                                  fNFgdTimeBins;                  ///<  Number of hit time bins in the FGD as determined by fgdRecon.
   TClonesArray*                          fFgdTimeBins;                   ///<  Information for each hit time bin (TFgdTimeBins).
   Int_t                                  fNP0DECAL;                      ///<  Number of objects containing the P0DECAL.
   Int_t                                  fNDsECAL;                       ///<  Number of objects containing the DsECAL.
   Int_t                                  fNTrECAL;                       ///<  Number of objects containing the TrECAL.
   Int_t                                  fNTPC;                          ///<  Number of objects containing the TPC.
   Int_t                                  fNFGD;                          ///<  Number of objects containing the FGD.
   Int_t                                  fNP0D;                          ///<  Number of objects containing the P0D.
   Int_t                                  fNSMRD;                         ///<  Number of objects containing the SMRD.
   Int_t                                  fNP0DECALIso;                   ///<  Number of objects in the P0DECAL only.
   Int_t                                  fNTrECALIso;                    ///<  Number of objects in the TrECAL only.
   Int_t                                  fNDsECALIso;                    ///<  Number of objects in the DsECAL only.
   Int_t                                  fNTPCIso;                       ///<  Number of objects in the TPC only.
   Int_t                                  fNFGDIso;                       ///<  Number of objects in the FGD only.
   Int_t                                  fNP0DIso;                       ///<  Number of objects in the P0D only.
   Int_t                                  fNSMRDIso;                      ///<  Number on objects in the SMRD only.

   TGlobalReconModule();
   TGlobalReconModule(const TGlobalReconModule & );
   virtual ~TGlobalReconModule();

   ClassDef(TGlobalReconModule,4); // Generated by MakeProject.
};
} // namespace
#endif
