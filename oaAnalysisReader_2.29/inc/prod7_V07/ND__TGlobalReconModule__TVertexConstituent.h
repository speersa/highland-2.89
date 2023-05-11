//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:43 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TVertexConstituent_h
#define ND__TGlobalReconModule__TVertexConstituent_h
namespace ND {
namespace TGlobalReconModule {
class TVertexConstituent;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TVector3.h"

namespace ND {
namespace TGlobalReconModule {
class TVertexConstituent : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         Charge;      //Charge of the constituent track
   double      Quality;     //Quality (chi2) of the constituent track
   TVector3    Momentum;    //3-momentum of the constituent track
   int         PID;         //The TGlobalPID of the constituent track

   TVertexConstituent();
   TVertexConstituent(const TVertexConstituent & );
   virtual ~TVertexConstituent();

   ClassDef(TVertexConstituent,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif