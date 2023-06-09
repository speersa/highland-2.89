//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 18:05:55 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400000-0000_2sxl5m3goua7_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerECALReconModule__TECALReconObject_h
#define ND__TTrackerECALReconModule__TECALReconObject_h
namespace ND {
namespace TTrackerECALReconModule {
class TECALReconObject;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "ND__TTrackerECALReconModule__TECALReconTrack.h"
#include "ND__TTrackerECALReconModule__TECALReconShower.h"
#include "ND__TTrackerECALReconModule__TECALReconCluster.h"
#include "Riostream.h"
#include <string>
#include "TVector3.h"

namespace ND {
namespace TTrackerECALReconModule {
class TECALReconObject : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   bool        FilledAsTrack;    //Was filled by a Track-like TReconPID \note This is an ease of use boolean NOT a PID. For determining PID please  use the PID variables.
   bool        FilledAsShower;    //Was filled by a Shower-like TReconPID \note This is an ease of use boolean NOT a PID. For determining PID please  use the PID variables.
   ND::TTrackerECALReconModule::TECALReconTrack Track;             //Objects to store information for a track.
   ND::TTrackerECALReconModule::TECALReconShower Shower;            //Objects to store information for a shower.
   ND::TTrackerECALReconModule::TECALReconCluster Cluster;           //Objects to store information for a cluster.
   unsigned int                                   UniqueID;          //Unique ID number to allow matching to Global Recon object.
   int                                            G4ID;              //G4ID for truth matched objects, using TrackTruthInfo the original truth-matching algorithm).
   int                                            G4ID_Primary;      //G4ID of the primary particle associated with this object.  See TShowerTruthInfo in oaUtility for details.
   double                                         Completeness_Primary;    //Truth-matching completeness for G4ID_Primary
   double                                         Cleanliness_Primary;     //Truth-matching cleanliness for G4ID_Primary
   int                                            G4ID_Recursive;          //G4ID of the highest-level parent particle that enters the ECal module,  and which had a daughter that contributed to this object. See TShowerTruthInfo in oaUtility for details.
   int                                            G4ID_Recursive2;         //G4ID of the highest-level parent particle that enters the ECal module,  and which had a daughter that contributed to this object. See TShowerTruthInfo in oaUtility for details.
   int                                            G4ID_Recursive3;         //G4ID of the highest-level parent particle that enters the ECal module,  and which had a daughter that contributed to this object. See TShowerTruthInfo in oaUtility for details.
   int                                            G4ID_Recursive4;         //G4ID of the highest-level parent particle that enters the ECal module,  and which had a daughter that contributed to this object. See TShowerTruthInfo in oaUtility for details.
   double                                         Completeness_Recursive;    //Truth-matching completeness for G4ID_Recursive
   double                                         Cleanliness_Recursive;     //Truth-matching cleanliness for G4ID_Recursive
   int                                            G4ID_Single;               //The single true particle that contributed most hits to this object.  Should be the same as G4ID in most cases  (unless two particles contributed the same amount).  See TShowerTruthInfo in oaUtility for details.
   float                                          Proximity_Single;          //The proximity of the energy depoisited by the G4ID_Single trajectory to the reconstructed hit.
   double                                         Completeness_Single;       //The Completeness of the single biggest contributor to the cluster.
   double                                         Cleanliness_Single;        //The cleanliness (hit purity) of the single biggest contributor   to the cluster. shower, provided it is below a proximity cutoff.
   int                                            NHits;                     //Number of hits in this object
   int                                            NIsXHits;                  //Number of hits with precise X information in the object
   int                                            NIsYHits;                  //Number of hits with precise Y information in the object
   int                                            NIsZHits;                  //Number of hits with precise Z information in the object
   int                                            NLayersHit;                //Number of layers hit by this object
   int                                            MaxPerpBarHit;             //\ The maximum bar number hit in a cluster, for layers perpendicular  to the beam axis
   int                                            MaxParaBarHit;             //The maximum bar number hit in a cluster, for layers parallel to  the beam axis
   int                                            MinBarHit;                 //The minimum bar number hit in a cluster  The minimum value of this is 0 for all ECals
   int                                            InnerMostLayerHit;         //The layer closest to the tracker that was hit by the object. 0 indexed.
   int                                            OuterMostLayerHit;         //The layer furthest from the tracker that was hit by the object.  This is layer number 30 (the 31st layer) for Barrel ECals and layer  number 33 (the 34th layer) for the downstream ECal
   double                                         TotalHitCharge;            //Sum of charges of the consitituent hits in reconstructed object.
   double                                         AverageHitTime;            //Average time of hits in reconstructed object.
   string                                         Module;                    //Name of ECAL module in which object was reconstructed.
   double                                         ObjectLength;              //Recon object length in mm
   double                                         PID_Circularity;           //The combined "circularity" of the object.  (showers) 0.0 <= circularity <= 1.0 (tracks)  This variable is a replacement for AMR.  PID_Circularity = PID_CircularityView0 * PID_CircularityView1
   double                                         PID_Angle;                 //The zenith angle with respect to each detector.
   double                                         PID_ShowerAngle;           //The angle from the start of an object to its width at its charge centre
   double                                         PID_Asymmetry;             //Ratio of the big width of an object by its small width.
   double                                         PID_TruncatedMaxRatio;     //A truncated Max Ratio. See ecalRecon docs for the full definition.
   double                                         PID_TransverseChargeRatio;    //A variable sensitive to the charge distribution in the plane  transverse to a shower/track direction.  See the ecalRecon documentation for the full definition.
   double                                         PID_FrontBackRatio;           //The ratio of the charge in equal length blocks at each end of the track. \note  Assumes particle is coming from the tracker into the ECal.
   double                                         Containment;                  //Containment: contained = 1.0, not-contained = 0.0, default = -1.0.      An object is classed as contained if it has no hits in the outer bars   of the ECal (bar number 0 or the maximum bar in a layer)   and no hits in the outermost layer of the ECal.
   double                                         PID_LLR_Quality;              //A quality flag for the likelihood PID variables.   Good quality = 0, Bad quality != 0.   The quality criteria is defined in ecalRecon.
   double                                         PID_LLR_MIP_EM;               //A combined discriminator for separating MIPs from EM showers.   Positive values = EM shower-like;   Negative values = MIP-like.    Analysers should check the PID_LLR_Quality flag before using this variable.
   double                                         PID_LLR_MIP_Pion;             //Discriminator for tagging showering pions in a sample of MIP-like tracks.  Positive values = showering pion-like;  Negative values = MIP-like.
   double                                         PID_LLR_EM_HIP;               //A combined discriminator for separating protons from electrons.  Positive values = stopping track-like;  Negative values = EM shower-like.
   double                                         PID_LLR_MIP_EM_LowMomentum;    //A combined discriminator for separating MIPs from EM showers.  This is similar to LLR_MIP_EM but trained specifically on  low-momentum electrons and muon. NB: this variable is still being  developed and should be considered to be unstable.    Positive values = electron-like;   Negative values = muon-like.   See the ecalRecon documentation for more details.
   double                                         AverageZPosition;              //Unweighted average Z position of object-constituent hits.
   double                                         EMEnergyFit_Result;            //The result from the EM energy fit to the cluster
   double                                         EMEnergyFit_Uncertainty;       //The uncertainty of the EM energy fit to the cluster
   double                                         EMEnergyFit_Likelihood_energyGrad;    //Energy fit experts please fill this in
   double                                         EMEnergyFit_Likelihood_energy_qsumGrad;    //Energy fit experts please fill this in
   double                                         EMEnergyFit_Likelihood_qsum_like;          //Energy fit experts please fill this in
   double                                         EMEnergyFit_Para_QSum;                     //The summed charge present in the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QMean;                    //The mean charge of hits in the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QRMS;                     //The RMS of the hit charges for the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QSkew;                    //The skew of hit charges for the cluster in units of MIPs
   double                                         EMEnergyFit_Para_QMax;                     //The maximum hit charge in units of MIPs.
   double                                         Thrust;                                    //
   TVector3                                       ThrustOrigin;                              //
   TVector3                                       ThrustAxis;                                //
   double                                         MatchingLikelihood;                        //The matching likelihood
   int                                            NHitsAtLayersWithManyHits;                 //The number of hits in a layer when there are at least 2 hits.
   int                                            NLayersTwoHits;                            //The number of layers which have at least 2 hits.
   int                                            NLayersThreeHits;                          //The number of layers which have at least 3 hits.
   int                                            FirstLayerManyHits;                        //The number of the first layer in which there are at least 2 hits.
   int                                            LastLayerManyHits;                         //The last layer in which there are at least 2 hits.
   int                                            MaxHitsInALayer;                           //The layer which received the maximum number of hits.
   int                                            MaxHitChargeLayer;                         //The layer which received the highest hit charge.
   int                                            Clustering_3DSeedType;                     //The 3D seed type from the 3D clustering algorithm (-1 means was not  created by 3D clustering, 0 means seed was from a pair of crossed bars, 1  means seed was from a double ended bar). Further details can be found in  TECAL3DClusters.cxx in ecalRecon.
   TVector3                                       Pointing;                                  //Pointing vector.

   TECALReconObject();
   TECALReconObject(const TECALReconObject & );
   virtual ~TECALReconObject();

   ClassDef(TECALReconObject,3); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
