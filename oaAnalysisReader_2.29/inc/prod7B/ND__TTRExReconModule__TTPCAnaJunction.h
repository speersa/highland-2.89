//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTRExReconModule__TTPCAnaJunction_h
#define ND__TTRExReconModule__TTPCAnaJunction_h
namespace ND {
namespace TTRExReconModule {
class TTPCAnaJunction;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

namespace ND {
namespace TTRExReconModule {
class TTPCAnaJunction : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   Int_t       JunctionID;    ///< A unique identifier for the junction within the pattern.
   Int_t       JunctionMatchingID;    //< A unique identifier for the junction within the event.
   TLorentzVector Position;              ///< The spatial coordinates of the junction
   Int_t          NPaths;                ///< The number of paths connected to the junction.
   Int_t         *PathIDs;               //[NPaths]
   TVector3       MaximumCoordinates;    ///< The most extreme hit positions in the positive direction
   TVector3       MinimumCoordinates;    ///< The most extreme hit positions in the negative direction

   TTPCAnaJunction();
   TTPCAnaJunction(const TTPCAnaJunction & );
   virtual ~TTPCAnaJunction();

   ClassDef(TTPCAnaJunction,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
