//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:43 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
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
   double      Charge;      //Deposited charge
   double      Time;        //Hit time [ns]
   TVector3    Position;    //Hit position in global ND coordinates [mm]
   TVector3    PositionError;    //The variance on ND::TGlobalReconModule::TGlobalHit::Position [mm]
   int         Type;             //The hit 'type': (0=X,1=Y,2=Z)

   TGlobalHit();
   TGlobalHit(const TGlobalHit & );
   virtual ~TGlobalHit();

   ClassDef(TGlobalHit,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif