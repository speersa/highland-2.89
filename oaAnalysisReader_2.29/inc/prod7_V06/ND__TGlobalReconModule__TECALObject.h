//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 18:05:55 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400000-0000_2sxl5m3goua7_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TECALObject_h
#define ND__TGlobalReconModule__TECALObject_h
namespace ND {
namespace TGlobalReconModule {
class TECALObject;
} // end of namespace.
} // end of namespace.

#include "ND__TSubBaseShowerObject.h"
#include "TVector3.h"

namespace ND {
namespace TGlobalReconModule {
class TECALObject : public ND::TSubBaseShowerObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Length;      //The length of the track or shower, its value depends on if the object is reconstructed as track-like or shower-like.
   double      EDeposit;    //Deposited energy. Its value depends on if the object is reconstructed as track-like or shower-like If IsTrackLike EDeposit is the total charge in the cluster in MEU. If IsShowerLike it is the result of the Tracker ECal EMEnergyFit in MeV.
   double      LLR_Quality;    //\brief PID quality flag.   A non-zero indicates an bad quality.  If this value is non-zero the PID values are set to -9999.
   double      LLR_MIP_EM;     //\brief Value to separate MIP-like objects (e.g. muons) from EM showers e.g. photons/electrons). -9999 indicates an error.
   double      LLR_MIP_Pion;    //\brief Value to separate MIP-like objects (e.g. muons) from showering  pions. -9999 indicates an error.
   double      LLR_EM_HIP;      //\brief Value to separate light tracks/MIP-like objects (e.g. muons) from  heavy tracks / Highly-ionising particles (specifically proton).  -9999 indicates an error.
   double      LLR_MIP_EM_LowMomentum;    //UNSTABLE: A combined discriminator for separating MIPs from EM showers.  This is similar to LLR_MIP_EM but trained specifically on  low-momentum electrons and muon. NB: this variable is still being  developed and should be considered to be unstable. Positive values = electron-like;  Negative values = muon-like.  See the ecalRecon documentation for more details.  -9999 indicates an error.
   double      LLR_MIP_HIP_VACut;         //UNSTABLE: Only filled for FilledAsType == 2  Recalculates PID variables for a vertex track where the X% (20% by  default) hits nearest to the reconstructed vertex are ignored.
   double      AverageHitTime;            //The charged weighted average time for the ECal cluster
   double      AverageZPosition;          //Unweighted average Z position of object-constituent hits.
   double      EMEnergyFit_Result;        //The result from the EM energy fit to the cluster
   double      EMEnergyFit_Uncertainty;    //The uncertainty of the EM energy fit to the cluster
   int         FilledAsType;               //\brief Whether the object was filled as a shower (or a track.). This is      NOT a PID.         This lets you know how some of these variables were filled from the     original ECal cluster. ECal-iso vertex tracks do not fill many of these     variables. Showers and Tracks differ in their definitions of Width and     Length, and EDeposit.     Cone is filled from the alternate Shower hypothesis for Track-like     clusters.     2. ECal-iso vertex track     1. Shower-like     0. Track-like     -1. Default value
   double      PID_Circularity;            //
   double      PID_Angle;                  //The zenith angle with respect to each detector.
   double      PID_ShowerAngle;            //The angle from the start of an object to its width at its charge centre
   double      PID_Asymmetry;              //Ratio of the big width of an object by its small width.
   double      PID_TruncatedMaxRatio;      //A truncated Max Ratio. See ecalRecon docs for the full definition.
   double      PID_TransverseChargeRatio;    //\brief A variable sensitive to the charge distribution in the plane     transverse to a shower/track direction.         See the ecalRecon documentation for the full definition.
   double      PID_FrontBackRatio;           //The ratio of the charge in equal length blocks at each end of the track.        \note     Assumes particle is coming from the tracker into the ECal.
   double      Containment;                  //Containment: contained = 1.0, not-contained = 0.0, default = -1.0.         An object is classed as contained if it has no hits in the outer bars     of the ECal (bar number 0 or the maximum bar in a layer)     and no hits in the outermost layer of the ECal.
   double      Thrust;                       //
   TVector3    ThrustOrigin;                 //
   TVector3    ThrustAxis;                   //
   int         InnerMostLayerHit;            //\brief Zero-indexed layer number of tracker-closest layer with an ECal  hit belonging to this object.
   int         OuterMostLayerHit;            //\brief Zero-indexed layer number of tracker-farthest layer with an ECal  hit belonging to this object.
   TVector3    Width;                        //TrackShower width         Filled depending on `FilledAsShower`.     * Track: `ND::TReconTrack::GetWidth`     * Shower: All three components are = `Length*tan(PID_ShowerAngle)`

   TECALObject();
   TECALObject(const TECALObject & );
   virtual ~TECALObject();

   ClassDef(TECALObject,3); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
