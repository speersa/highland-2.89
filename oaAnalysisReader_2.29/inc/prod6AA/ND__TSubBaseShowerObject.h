//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:01:37 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90810096-0055_quxcl5i7qxq4_anal_000_magnet201508waterrun8-bsdv01_2.root
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
   TVector3    Cone;        ///< The opening angles of the cone (only for showers)

   TSubBaseShowerObject();
   TSubBaseShowerObject(const TSubBaseShowerObject & );
   virtual ~TSubBaseShowerObject();

   ClassDef(TSubBaseShowerObject,2); // Generated by MakeProject.
};
} // namespace
#endif
