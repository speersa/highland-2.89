//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:44 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
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
   int         JunctionID;    //A unique identifier for the junction within the pattern.
   int         JunctionMatchingID;    //< A unique identifier for the junction within the event.
   TLorentzVector Position;              //The spatial coordinates of the junction
   int            NPaths;                //The number of paths connected to the junction.
   Int_t         *PathIDs;               //[NPaths]
   TVector3       MaximumCoordinates;    //The most extreme hit positions in the positive direction
   TVector3       MinimumCoordinates;    //The most extreme hit positions in the negative direction

   TTPCAnaJunction();
   TTPCAnaJunction(const TTPCAnaJunction & );
   virtual ~TTPCAnaJunction();

   ClassDef(TTPCAnaJunction,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
