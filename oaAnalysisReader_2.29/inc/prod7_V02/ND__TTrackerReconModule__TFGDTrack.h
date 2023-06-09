//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:36 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerReconModule__TFGDTrack_h
#define ND__TTrackerReconModule__TFGDTrack_h
namespace ND {
namespace TTrackerReconModule {
class TFGDTrack;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

namespace ND {
namespace TTrackerReconModule {
class TFGDTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned int UniqueID;    //Unique ID number to allow matching to Global Reconobject.
   int          Detector;    //FGD number 1 or 2
   int          Ndof;        //Number of degrees of freedom in FGD track fit
   double       Chi2;        //Chi2 of the FGD track fit the FGD track starting position vector coordinates in order x,y,z,t where x,y,z are in mm, t is in ns
   TLorentzVector Position;    //
   TVector3       Direction;    //
   double         EDeposit;     //

   TFGDTrack();
   TFGDTrack(const TFGDTrack & );
   virtual ~TFGDTrack();

   ClassDef(TFGDTrack,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
