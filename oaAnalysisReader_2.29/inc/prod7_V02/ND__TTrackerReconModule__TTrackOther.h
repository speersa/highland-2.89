//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:36 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerReconModule__TTrackOther_h
#define ND__TTrackerReconModule__TTrackOther_h
namespace ND {
namespace TTrackerReconModule {
class TTrackOther;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "ND__TTrackerReconModule__TUnusedHit.h"

namespace ND {
namespace TTrackerReconModule {
class TTrackOther : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    //The name of the algorithm that created this object.
   int         Detector;         //Detector used (1,2,3 for TPC, or 4,5 for FGD?)
   int         NHits;            //The number of hits.
   TClonesArray* Hits;             //The hits
   double        EDeposit;         //The deposited charge for the object.
   TLorentzVector FrontPosition;    //The position of the track at itsupstream-most end (x,y,z,t) in mm, ns
   TLorentzVector BackPosition;     //The position of the track at itsdownstream-most end     (x,y,z,t) in mm,ns
   ND::TTrackerReconModule::TUnusedHit hackHits;         //This is just here to fool TFile::MakeProject, nota real object.

   TTrackOther();
   TTrackOther(const TTrackOther & );
   virtual ~TTrackOther();

   ClassDef(TTrackOther,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
