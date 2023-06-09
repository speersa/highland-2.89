//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Apr  5 14:16:33 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80600124-0055_f72mofocwqdr_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TSubBaseShowerObject_h
#define ND__TSubBaseShowerObject_h
namespace ND {
class TSubBaseShowerObject;
} // end of namespace.

#include "ND__TSubBaseObject.h"
#include "TVector3.h"

namespace ND {
class TSubBaseShowerObject : public ND::TSubBaseObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TVector3    Cone;        //The opening angles of the reconstructed shower cone.

   TSubBaseShowerObject();
   TSubBaseShowerObject(const TSubBaseShowerObject & );
   virtual ~TSubBaseShowerObject();

   ClassDef(TSubBaseShowerObject,2); // Generated by MakeProject.
};
} // namespace
#endif
