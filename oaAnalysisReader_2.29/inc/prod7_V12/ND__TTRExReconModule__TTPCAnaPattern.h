//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Apr  5 14:16:32 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80600124-0055_f72mofocwqdr_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTRExReconModule__TTPCAnaPattern_h
#define ND__TTRExReconModule__TTPCAnaPattern_h
namespace ND {
namespace TTRExReconModule {
class TTPCAnaPattern;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TClonesArray.h"

namespace ND {
namespace TTRExReconModule {
class TTPCAnaPattern : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   bool        S1Sflag;     //A flag to say whether this pattern would pass the TPC gas Stage 1 Selection
   int         PatternID;    //The ID of the pattern
   int         NJunctions;    //The number of junctions in the pattern.
   TClonesArray* Junctions;     //The constituent junctions of the pattern
   int           NPaths;        //The number of paths.
   TClonesArray* Paths;         //The constituent paths of the pattern.
   int           TPC;           //The TPC in which the pattern resides.

   TTPCAnaPattern();
   TTPCAnaPattern(const TTPCAnaPattern & );
   virtual ~TTPCAnaPattern();

   ClassDef(TTPCAnaPattern,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
