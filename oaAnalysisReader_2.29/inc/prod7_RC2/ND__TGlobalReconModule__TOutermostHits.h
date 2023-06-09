//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Sep 15 17:37:36 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/oa_nt_beam_80730000-0000_ngg4oj3wpuhl_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TOutermostHits_h
#define ND__TGlobalReconModule__TOutermostHits_h
namespace ND {
namespace TGlobalReconModule {
class TOutermostHits;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "ND__TGlobalReconModule__TGlobalHit.h"

namespace ND {
namespace TGlobalReconModule {
class TOutermostHits : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   ND::TGlobalReconModule::TGlobalHit hitMinX;     //
   ND::TGlobalReconModule::TGlobalHit hitMaxX;     //
   ND::TGlobalReconModule::TGlobalHit hitMinY;     //
   ND::TGlobalReconModule::TGlobalHit hitMaxY;     //
   ND::TGlobalReconModule::TGlobalHit hitMinZ;     //
   ND::TGlobalReconModule::TGlobalHit hitMaxZ;     //

   TOutermostHits();
   TOutermostHits(const TOutermostHits & );
   virtual ~TOutermostHits();

   ClassDef(TOutermostHits,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
