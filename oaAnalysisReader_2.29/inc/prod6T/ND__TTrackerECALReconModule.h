//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Sep  5 15:48:12 2019 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod6T/oa_nt_beam_90210000-0000_mghj7aenjmue_anal_000_magnet201011waterrun2-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerECALReconModule_h
#define ND__TTrackerECALReconModule_h
namespace ND {
class TTrackerECALReconModule;
} // end of namespace.

#include "ND__TAnalysisReconModuleBase.h"
#include "TClonesArray.h"
#include "TObject.h"
#include "TVector3.h"
#include "ND__TTrackerECALReconModule.h"
#include "Riostream.h"
#include <string>
#include <vector>
#include "TLorentzVector.h"

namespace ND {
class TTrackerECALReconModule : public ND::TAnalysisReconModuleBase {

public:
// Nested classes forward declaration.
class TECALReconObject;
class TECALReconTrack;
class TECALReconShower;
class TECALReconCluster;
class TECALReconUnmatchedObject;

public:
// Nested classes declaration.
class TECALReconUnmatchedObject : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         NHits;       ///< Number of hits in the cluster
   int         View;        ///< View of the cluster. View 0 - Y measuring (odd) Layers and View 1 - X measuring (even) layers
   double      TotalHitCharge;    ///< Summed hit charge in the cluster in units of MIPs
   double      AverageHitTime;    ///< Average time of the cluster in ns
   TVector3    FrontPosition;     ///< Position of the end of the cluster closest to the centre of the tracker
   TVector3    BackPosition;      ///< Position in end of the cluster furthest from the centre of the track
   int         mostUpStreamLayerHit;    ///< The layer closest to the centre of the tracker that was hit by the cluster
   int         mostDownStreamLayerHit;    ///< The layer furthest from the centre of the tracker that was hit by the cluster
   Int_t       G4ID;                      ///< Truth-matched particle ID.
   Int_t       G4ID_Primary;              //G4ID of the primary particle associated with this object.
   Int_t       G4ID_Recursive;            //G4ID of the highest-level parent particle that enters the ECal module
   Int_t       G4ID_Single;               //The single true particle that contributed most hits to this object.

   TECALReconUnmatchedObject();
   TECALReconUnmatchedObject(const TECALReconUnmatchedObject & );
   virtual ~TECALReconUnmatchedObject();

   ClassDef(TECALReconUnmatchedObject,2); // Generated by MakeProject.
};
class TECALReconCluster : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TLorentzVector Position;    ///< The cluster position.
   TLorentzVector PositionVar;    ///< The cluster position variance.
   int            NDOF;           ///< The number of degrees of freedom in the reconstruction.
   double         Quality;        ///< The goodness of fit for the reconstruction.
   int            Status;         ///< The fit status.
   double         EDeposit;       ///< The charge deposited by the cluster.

   TECALReconCluster();
   TECALReconCluster(const TECALReconCluster & );
   virtual ~TECALReconCluster();

   ClassDef(TECALReconCluster,2); // Generated by MakeProject.
};
class TECALReconShower : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TVector3    ConeAngle;    ///< The shower opening angle.
   TVector3    Direction;    ///< The shower direction.
   double      EDeposit;     ///< The energy deposited in the shower
   int         NDOF;         ///< The number of degrees of freedom in the reconstruction.
   TLorentzVector Position;     ///< The shower position.
   TLorentzVector PositionVar;    ///< The shower position variance.
   TLorentzVector BackPosition;    ///< The charge weighted position of the end of the shower
   double         Quality;         ///< The goodness of fit for the reconstruction.
   int            Status;          ///< The fit status.

   TECALReconShower();
   TECALReconShower(const TECALReconShower & );
   virtual ~TECALReconShower();

   ClassDef(TECALReconShower,2); // Generated by MakeProject.
};
class TECALReconTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Curvature;    ///< The track curvature around the X axis.
   TVector3    Direction;    ///< The track direction.
   double      EDeposit;     ///< The charge deposited by the track in units of MIPs
   int         NDOF;         ///< The number of degrees of freedom in the reconstruction.
   TLorentzVector Position;     ///< The track starting position.
   TLorentzVector PositionVar;    ///< The track starting position variance.
   TLorentzVector BackPosition;    ///< The position of the end of the track
   double         Quality;         ///< The goodness of fit for the reconstruction.
   TVector3       Width;           ///< The width of the track.
   int            Status;          ///< The fit status.

   TECALReconTrack();
   TECALReconTrack(const TECALReconTrack & );
   virtual ~TECALReconTrack();

   ClassDef(TECALReconTrack,2); // Generated by MakeProject.
};
class TECALReconObject : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         Radon_XY_First_Prong_NHits;    ///< The number of hits in the first radon line in the XY view
   int         Radon_XY_First_Prong_Angle;    ///< The angle from the radon Y axis to the line perpendicular to the first radon line in the XY view
   int         Radon_XY_First_Prong_Distance;    ///< The perpendicular distance from the cluster centre to the first radon line in the XY view
   int         Radon_XY_Second_Prong_NHits;      ///< The number of hits in the second radon line in the XY view
   int         Radon_XY_Second_Prong_Angle;      ///< The angle from the radon Y axis to the line perpendicular to the first radon line in the XY view
   int         Radon_XY_Second_Prong_Distance;    ///< The perpendicular distance from the cluster centre to the first radon line in the XY view
   int         Radon_XY_Third_Prong_NHits;        ///< The number of hits in the first radon line in the XY view
   int         Radon_XY_Third_Prong_Angle;        ///< The angle from the radon Y axis to the line perpendicular to the first radon line in the XY view
   int         Radon_XY_Third_Prong_Distance;     ///< The perpendicular distance from the cluster centre to the first radon line in the XY view
   int         Radon_XZ_First_Prong_NHits;        ///< The number of hits in the first radon line in the XZ view
   int         Radon_XZ_First_Prong_Angle;        ///< The angle from the radon Y axis to the line perpendicular to the first radon line in the XZ view
   int         Radon_XZ_First_Prong_Distance;     ///< The perpendicular distance from the cluster centre to the first radon line in the XZ view
   int         Radon_XZ_Second_Prong_NHits;       ///< The number of hits in the second radon line in the XZ view
   int         Radon_XZ_Second_Prong_Angle;       ///< The angle from the radon Y axis to the line perpendicular to the second radon line in the XZ view
   int         Radon_XZ_Second_Prong_Distance;    ///< The perpendicular distance from the cluster centre to the second radon line in the XZ view
   int         Radon_XZ_Third_Prong_NHits;        ///< The number of hits in the third radon line in the XZ view
   int         Radon_XZ_Third_Prong_Angle;        ///< The angle from the radon Y axis to the line perpendicular to the third radon line in the XZ view
   int         Radon_XZ_Third_Prong_Distance;     ///< The perpendicular distance from the cluster centre to the third radon line in the XZ view
   int         Radon_YZ_First_Prong_NHits;        ///< The number of hits in the first radon line in the YZ view
   int         Radon_YZ_First_Prong_Angle;        ///< The angle from the radon Y axis to the line perpendicular to the first radon line in the YZ view
   int         Radon_YZ_First_Prong_Distance;     ///< The perpendicular distance from the cluster centre to the first radon line in the YZ view
   int         Radon_YZ_Second_Prong_NHits;       ///< The number of hits in the second radon line in the YZ view
   int         Radon_YZ_Second_Prong_Angle;       ///< The angle from the radon Y axis to the line perpendicular to the second radon line in the YZ view
   int         Radon_YZ_Second_Prong_Distance;    ///< The perpendicular distance from the cluster centre to the second radon line in the YZ view
   int         Radon_YZ_Third_Prong_NHits;        ///< The number of hits in the third radon line in the YZ view
   int         Radon_YZ_Third_Prong_Angle;        ///< The angle from the radon Y axis to the line perpendicular to the third radon line in the YZ view
   int         Radon_YZ_Third_Prong_Distance;     ///< The perpendicular distance from the cluster centre to the third radon line in the YZ view
   TVector3    Radon_3D_First_Prong_Direction;    ///< The 3D direction of the first radon line, in global coordinates.  This will be (0,0,0) if no line is reconstructed
   int         Radon_3D_First_Prong_NHits;        ///< The number of hits in the first 3D radon line.  This will be 0 if no line is reconstructed
   TVector3    Radon_3D_Second_Prong_Direction;    ///< The 3D direction of the second radon line, in global coordinates.  This will be (0,0,0) if no line is reconstructed
   int         Radon_3D_Second_Prong_NHits;        ///< The number of hits in the second 3D radon line.  This will be 0 if no line is reconstructed
   TVector3    Radon_3D_Third_Prong_Direction;     ///< The 3D direction of the third radon line, in global coordinates.  This will be (0,0,0) if no line is reconstructed
   int         Radon_3D_Third_Prong_NHits;         ///< The number of hits in the third 3D radon line.  This will be 0 if no line is reconstructed
   ND::TTrackerECALReconModule::TECALReconTrack Track;                              ///< Objects to store information for a track.
   ND::TTrackerECALReconModule::TECALReconShower Shower;                             ///< Objects to store information for a shower.
   ND::TTrackerECALReconModule::TECALReconCluster Cluster;                            ///< Objects to store information for a cluster.
   UInt_t                                         UniqueID;                           ///< Unique ID number to allow matching to Global Recon object
   Int_t                                          G4ID;                               ///< G4ID for truth matched objects, using TrackTruthInfo (the original truth-matching algorithm).
   Int_t                                          G4ID_Primary;                       //G4ID of the primary particle associated with this object.
   Double_t                                       Completeness_Primary;               ///< Truth-matching completeness for G4ID_Primary
   Double_t                                       Cleanliness_Primary;                ///< Truth-matching cleanliness for G4ID_Primary
   Int_t                                          G4ID_Recursive;                     //G4ID of the highest-level parent particle that enters the ECal module.
   Int_t                                          G4ID_Recursive2;                    //G4ID of the highest-level parent particle that enters the ECal module.
   Int_t                                          G4ID_Recursive3;                    //G4ID of the highest-level parent particle that enters the ECal module.
   Int_t                                          G4ID_Recursive4;                    //G4ID of the highest-level parent particle that enters the ECal module.
   Double_t                                       Completeness_Recursive;             ///< Truth-matching completeness for G4ID_Recursive
   Double_t                                       Cleanliness_Recursive;              //
   Int_t                                          G4ID_Single;                        //The single true particle that contributed most hits to this object.
   Double_t                                       Completeness_Single;                ///< Truth-matching completeness for G4ID_Single
   Double_t                                       Cleanliness_Single;                 ///< Truth-matching cleanliness for G4ID_Single
   Bool_t                                         IsTrackLike;                        ///< Boolean value reflecting whether this object is "track-like", based on default cuts in ecalRecon
   Bool_t                                         IsShowerLike;                       ///< Boolean value reflecting whether this object is "shower-like", based on default cuts in ecalRecon
   Int_t                                          TimeBunch;                          ///< Timebunch that the object occurred in - currently not filled
   Int_t                                          NHits;                              ///< Number of hits in this object
   Int_t                                          NIsXHits;                           ///< Number of hits with precise X information in the object
   Int_t                                          NIsYHits;                           ///< Number of hits with precise Y information in the object
   Int_t                                          NIsZHits;                           ///< Number of hits with precise Z information in the object
   Int_t                                          NLayersHit;                         ///< Number of layers hit by this object
   Int_t                                          maxPerpBarHit;                      //The maximum bar number hit in a cluster
   Int_t                                          maxParaBarHit;                      //The maximum bar number hit in a cluster
   Int_t                                          minBarHit;                          //The minimum bar number hit in a cluster
   Int_t                                          mostUpStreamLayerHit;               ///< The layer closest to the centre of the tracker that was hit by the object.  ECal layers are zero ordered, so this starts at 0
   Int_t                                          mostDownStreamLayerHit;             //The layer furthest from the centre of the tracker that was hit
   Double_t                                       TotalHitCharge;                     ///< Sum of charges of the consitituent hits in reconstructed object.
   Double_t                                       AverageHitTime;                     ///< Average time of hits in reconstructed object.
   string                                         Module;                             ///< Name of ECAL module in which object was reconstructed.
   Double_t                                       ObjectLength;                       ///< Recon object length in mm
   double                                         PID_AMR;                            ///< Ratio of the length to the width of the reconstructed object.
   double                                         PID_Circularity;                    //The combined "circularity" of the object. (showers) 0.0 <= circularity <= 1.0 (tracks)
   double                                         PID_CircularityView0;               ///< The "circularity" in view 0 (odd layers) of the object. (showers) 0.0 <= circularity <= 1.0 (tracks)
   double                                         PID_CircularityView1;               ///< The "circularity" in view 1 (even layers - including 0) of the object. (showers) 0.0 <= circularity <= 1.0 (tracks)
   double                                         PID_Angle;                          ///< The zenith angle with respect to each detector.
   double                                         PID_Max_Ratio;                      ///< The maximum ratio between the charge in the largest charge layer over the smallest
   double                                         PID_ShowerAngle;                    ///< The angle from the start of an object to its width at its charge centre
   double                                         PID_Asymmetry;                      ///< Ratio of the big width of an object by its small width.
   double                                         PID_MeanPosition;                   ///< The charge weight position with respect to the object start position.
   double                                         PID_Qskew;                          ///< Skew of the Q distribution
   double                                         PID_ShowerWidth;                    ///< Width at the charge centre
   double                                         PID_EMLikelihood;                   ///< Electro-magnetic likelihood
   double                                         PID_TrShval;                        ///< Value to seperate tracks from showers.  0 = shower-like, 1 = track-like, though there can be values outside this range
   double                                         PID_EMHadVal;                       ///< Value to seperate EM from Hadronic showers - not currently used.
   double                                         PID_TruncatedMaxRatio;              ///< A truncated Max Ratio. See the ecalRecon documentation for the full definition.
   double                                         PID_TransverseChargeRatio;          //A variable sensitive to the charge distribution in the plane transverse to a shower/track direction. 
   double                                         PID_NormalizedMipChi2;              ///< A variable sensitive to the shape of the dE/dx distribution along the track. See the ecalRecon documentation for the full definition.
   double                                         PID_NormalizedMipChi2AllLayers;     ///< A variable sensitive to the shape of the dE/dx distribution along the track. See the ecalRecon documentation for the full definition.
   double                                         PID_FrontBackRatio;                 ///< The ratio of the charge in equal length blocks at each end of the track.
   double                                         PID_FrontBackRatioNumerator;        ///< The numerator of the front - back ratio
   double                                         PID_FrontBackRatioDenominator;      ///< The denominator of the front - back ratio
   double                                         Containment;                        //Containment: contained = 1.0, not-contained = 0.0.
   double                                         PID_LLR_MIP_EM;                     //
   double                                         PID_LLR_MIP_Pion;                   //
   double                                         PID_LLR_EM_HIP;                     //
   double                                         PID_LLR_MIP_EM_LowMomentum;         //
   double                                         AverageZPosition;                   ///< Average Z position of the object (using the number of hits) without charge weighting.
   double                                         EMEnergyFit_Result;                 ///< The result from the EM energy fit to the cluster
   double                                         EMEnergyFit_Uncertainty;            ///< The uncertainty of the EM energy fit to the cluster
   double                                         EMEnergyFit_Likelihood_energyGrad;    ///< Energy fit experts please fill this in
   double                                         EMEnergyFit_Likelihood_energy_qsumGrad;    ///< Energy fit experts please fill this in
   double                                         EMEnergyFit_Likelihood_qsum_like;          ///< Energy fit experts please fill this in
   double                                         EMEnergyFit_Para_QSum;                     ///< The summed charge present in the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QMean;                    ///< The mean charge of hits in the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QRMS;                     ///< The RMS of the hit charges for the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QSkew;                    ///< The skew of hit charges for the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QMax;                     ///< The maximum hit charge within the cluster in units of MIPs
   double                                         MElectronTag_NDelayedCluster;              ///< The number of delayed Michel electron candidate clusters
   vector<double>                                 MElectronTag_NDelayedHits;                 ///< The number of hits in a Michel electron candidate
   vector<double>                                 MElectronTag_DeltaX;                       ///< The X displacement of the Michel electron candidate from the original ECal cluster
   vector<double>                                 MElectronTag_DeltaY;                       ///< The Y displacement of the Michel electron candidate from the original ECal cluster
   vector<double>                                 MElectronTag_DeltaZ;                       ///< The Z displacement of the Michel electron candidate from the original ECal cluster
   vector<double>                                 MElectronTag_DeltaT;                       ///< The time displacement of the Michel electron candidate from the original ECal cluster
   vector<double>                                 MElectronTag_EDep;                         ///< The energy deposited by the Michel electron candidate
   vector<double>                                 MElectronTag_TrackEnd;                     //which end of the Cluster the MichelCandidate was observed.
   double                                         Thrust;                                    //
   TVector3                                       ThrustOrigin;                              //
   TVector3                                       ThrustAxis;                                //
   int                                            KFNNodes;                                  //
   int                                            KFMultiTracksTPC;                          //
   int                                            KFMultiTracksECAL;                         //
   int                                            KFNDOF;                                    //
   double                                         KFQuality;                                 //
   double                                         KFParameter;                               //
   double                                         KFParameterNodes;                          //
   double                                         KFHitQuality;                              //
   bool                                           KFIsMatched;                               //
   int                                            KFNNodesEcalStandAlone;                    //
   int                                            KFMultiTracksTPCEcalStandAlone;            //
   int                                            KFMultiTracksECALEcalStandAlone;           //
   int                                            KFNDOFEcalStandAlone;                      //
   double                                         KFQualityEcalStandAlone;                   //
   double                                         KFParameterEcalStandAlone;                 //
   double                                         KFParameterNodesEcalStandAlone;            //
   double                                         KFHitQualityEcalStandAlone;                //
   bool                                           KFIsMatchedEcalStandAlone;                 //
   double                                         MatchingLikelihood;                        //
   int                                            FirstLayer;                                ///< The first layer hit
   int                                            LastLayer;                                 ///< The last layer hit
   int                                            NHitsAtLayersWithManyHits;                 /// <The number of hits in a layer when there are at least 2 hits (in that layer)
   int                                            NLayersOneHits;                            //
   int                                            NLayersTwoHits;                            ///< The number of layers which have at least 2 hits
   int                                            NLayersThreeHits;                          ///< The number of layers which have at least 3 hits
   int                                            NLayersFourHits;                           ///< The number of layers which have at least 4 hits
   int                                            NLayersFiveHits;                           ///< The number of layers which have at least 5 hits
   int                                            NLayersSixHits;                            ///< The number of layers which have at least 6 hits
   int                                            NLayersSevenHits;                          ///< The number of layers which have at least 7 hits
   int                                            FirstLayerManyHits;                        ///< The number of the first layer in which there are at least 2 hits
   int                                            SecondLayerManyHits;                       ///< The number of the second layer in which there are at least 2 hits
   int                                            ThirdLayerManyHits;                        ///< The number of the third layer in which there are at least 2 hits
   int                                            LastLayerManyHits;                         ///< The last layer in which there are at least 2 hits
   int                                            MaxHitsInALayer;                           ///< The layer which received the maximum number of hits
   int                                            MaxHitChargeLayer;                         ///< The layer which received the highest hit charge
   TVector3                                       Pointing;                                  //

   TECALReconObject();
   TECALReconObject(const TECALReconObject & );
   virtual ~TECALReconObject();

   ClassDef(TECALReconObject,2); // Generated by MakeProject.
};

public:
// Data Members.
   Int_t       fNUnmatchedObjects;    //
   double      total;                 //
   bool        fIsMC;                 //
   TClonesArray* fUnmatchedObjects;     //

   TTrackerECALReconModule();
   TTrackerECALReconModule(const TTrackerECALReconModule & );
   virtual ~TTrackerECALReconModule();

   ClassDef(TTrackerECALReconModule,2); // Generated by MakeProject.
};
} // namespace
#endif
