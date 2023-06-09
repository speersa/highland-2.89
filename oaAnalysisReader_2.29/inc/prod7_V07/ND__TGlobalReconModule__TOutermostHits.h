//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:43 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
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
   ND::TGlobalReconModule::TGlobalHit hitMinX;     //Hit with lowest X position.
   ND::TGlobalReconModule::TGlobalHit hitMaxX;     //Hit with highest X position.
   ND::TGlobalReconModule::TGlobalHit hitMinY;     //Hit with lowest Y position.
   ND::TGlobalReconModule::TGlobalHit hitMaxY;     //Hit with highest Y position.
   ND::TGlobalReconModule::TGlobalHit hitMinZ;     //Hit with lowest Z position.
   ND::TGlobalReconModule::TGlobalHit hitMaxZ;     //Hit with highest Z position.

   TOutermostHits();
   TOutermostHits(const TOutermostHits & );
   virtual ~TOutermostHits();

   ClassDef(TOutermostHits,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
