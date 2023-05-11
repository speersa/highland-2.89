//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jan 20 12:54:43 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file test_ev_anal.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrueVertex_h
#define ND__TTrueVertex_h
namespace ND {
class TTrueVertex;
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"

namespace ND {
class TTrueVertex : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TLorentzVector Position;    //
   Int_t          ID;          //
   double         Pur;         //
   double         Eff;         //

   TTrueVertex();
   TTrueVertex(const TTrueVertex & );
   virtual ~TTrueVertex();

   ClassDef(TTrueVertex,2); // Generated by MakeProject.
};
} // namespace
#endif
