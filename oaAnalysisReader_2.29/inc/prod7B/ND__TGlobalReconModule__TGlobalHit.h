//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TGlobalHit_h
#define ND__TGlobalReconModule__TGlobalHit_h
namespace ND {
namespace TGlobalReconModule {
class TGlobalHit;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TVector3.h"

namespace ND {
namespace TGlobalReconModule {
class TGlobalHit : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Charge;      ///< Deposited charge
   double      Time;        ///< Hit time [ns]
   TVector3    Position;    ///< Hit position in global ND coordinates [mm]
   TVector3    PositionError;    ///< The variance on ND::TGlobalReconModule::TGlobalHit::Position [mm]
   int         Type;             ///< The hit 'type': (0=X,1=Y,2=Z)

   TGlobalHit();
   TGlobalHit(const TGlobalHit & );
   virtual ~TGlobalHit();

   ClassDef(TGlobalHit,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
