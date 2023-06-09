//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jan 20 12:54:43 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file test_ev_anal.root
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
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   int         Detector;         ///< Detector used (1,2,3 for TPC, or 4,5 for FGD?)
   int         NHits;            ///< The number of hits.
   TClonesArray* Hits;             ///< The hits
   double        EDeposit;         ///< The deposited charge for the object.
   TLorentzVector FrontPosition;    ///< The position of the track at its
   TLorentzVector BackPosition;     ///< The position of the track at its
   ND::TTrackerReconModule::TUnusedHit hackHits;         ///<This is just here to fool TFile::MakeProject, not

   TTrackOther();
   TTrackOther(const TTrackOther & );
   virtual ~TTrackOther();

   ClassDef(TTrackOther,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
