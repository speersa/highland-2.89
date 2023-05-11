//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 18:05:55 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400000-0000_2sxl5m3goua7_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TSMRDObject_h
#define ND__TGlobalReconModule__TSMRDObject_h
namespace ND {
namespace TGlobalReconModule {
class TSMRDObject;
} // end of namespace.
} // end of namespace.

#include "ND__TSubBaseObject.h"

namespace ND {
namespace TGlobalReconModule {
class TSMRDObject : public ND::TSubBaseObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      avgtime;     //Avergaed light-propagation corrected hit time

   TSMRDObject();
   TSMRDObject(const TSMRDObject & );
   virtual ~TSMRDObject();

   ClassDef(TSMRDObject,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
