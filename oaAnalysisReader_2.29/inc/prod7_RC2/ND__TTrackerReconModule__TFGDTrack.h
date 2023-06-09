//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Sep 15 17:37:36 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/oa_nt_beam_80730000-0000_ngg4oj3wpuhl_anal_000_nu-bsdv01_2.root
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
   UInt_t      UniqueID;    ///< Unique ID number to allow matching to Global Recon
   int         Detector;    ///< FGD number 1 or 2
   int         Ndof;        ///< Number of degrees of freedom in FGD track fit
   double      Chi2;        ///< Chi2 of the FGD track fit
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
