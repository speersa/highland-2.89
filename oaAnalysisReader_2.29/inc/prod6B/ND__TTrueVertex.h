//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov  4 15:38:32 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/valid/oa_nt_beam_90210042-0030_bbzjto7xz4zh_anal_000_prod6amagnet201011waterb-bsdv01_2.root
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
