//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 18:05:55 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400000-0000_2sxl5m3goua7_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DECALReconModule__TP0DECALReconShower_h
#define ND__TP0DECALReconModule__TP0DECALReconShower_h
namespace ND {
namespace TP0DECALReconModule {
class TP0DECALReconShower;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "Riostream.h"
#include <string>

namespace ND {
namespace TP0DECALReconModule {
class TP0DECALReconShower : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned int UniqueID;    //The object UniqueID which can be used to match this object  to the Global Recon object.
   TVector3     ConeAngle;    //The opening angle of the corresponding TReconShower.
   TVector3     Direction;    //The Direction of the corresponding TReconShower.
   double       EDeposit;     //The reconstructed energy deposited by the corresponding TReconTrack.
   int          NDOF;         //\short The Number of Degrees of Freedom in the reconstruction of the
   TLorentzVector Position;     //The reconstructed starting 4-position of the TReconTrack.
   double         Quality;      //\short The 'quality' of the reconstruction according to the relevant
   double         AMR;          //PID Variable: Axis Max Ratio - the ratio of primary and secondary components of a 2D PCA.
   double         CWTrackWidth;    //PID Variable: Width of the track in bars, weighted by the charge  in each bar.
   double         Max_Ratio;       //PID Variable: The ratio between highest and lowest hit charges in  the reconstruction cluster.
   double         NormChargeSD;    //PID Variable: Normalised standard deviation of the contributing  reconstructed hit charges.
   double         PathChargeRatio;    //The ratio of total hit charges between the front half and back  half of the TReconShower.
   double         TrShval;            //PID Variable: The output of the ANN using the other PID Variables  as input. Shower-like events have a TrShval close to '0'.
   int            NHits;              //The number of THits which contributed to this reconstruction cluster.
   TVector3       BenCWPosition;      //Ben's charge weighted reconstruction position.
   int            StackNo;            //The stack in which the TReconTrack resides. Uses
   int            TrueID;             //For MC events: The Id of the primary corresponding ND::TG4Trajectory.
   string         Module;             //The name of the module in which the TReconTrack resides.

   TP0DECALReconShower();
   TP0DECALReconShower(const TP0DECALReconShower & );
   virtual ~TP0DECALReconShower();

   ClassDef(TP0DECALReconShower,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif