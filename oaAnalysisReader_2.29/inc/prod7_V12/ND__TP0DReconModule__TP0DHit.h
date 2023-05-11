//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Apr  5 14:16:34 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80600124-0055_f72mofocwqdr_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DReconModule__TP0DHit_h
#define ND__TP0DReconModule__TP0DHit_h
namespace ND {
namespace TP0DReconModule {
class TP0DHit;
} // end of namespace.
} // end of namespace.

#include "TObject.h"

namespace ND {
namespace TP0DReconModule {
class TP0DHit : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned int GeomID;      //Geometry Id of the TSingleHit.
   unsigned int ChanID;      //Channel Id of the TSingleHit.
   float        Charge;      //Reconstructed hit charge without attenuation correction from the  corresponding TSingleHit.
   float        Time;        //Reconstructed hit time from the corresponding TSingleHit.

   TP0DHit();
   TP0DHit(const TP0DHit & );
   virtual ~TP0DHit();

   ClassDef(TP0DHit,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif