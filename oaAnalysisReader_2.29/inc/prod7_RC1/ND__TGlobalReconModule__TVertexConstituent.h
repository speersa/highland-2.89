//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jan 20 12:54:43 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file test_ev_anal.root
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
   int         Charge;      //
   double      Quality;     //
   TVector3    Momentum;    //
   int         PID;         //

   TVertexConstituent();
   TVertexConstituent(const TVertexConstituent & );
   virtual ~TVertexConstituent();

   ClassDef(TVertexConstituent,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
