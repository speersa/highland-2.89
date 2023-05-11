//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:09:42 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710119-0055_df7igapcoooo_anal_000_nu-bsdv01_2.root
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
   TLorentzVector Position;    //The position of the vertex
   int            ID;          //The vertex ID from G4
   double         Pur;         //Purity of reconstructed - true vertex association
   double         Eff;         //Efficiency of vertex association of tracks

   TTrueVertex();
   TTrueVertex(const TTrueVertex & );
   virtual ~TTrueVertex();

   ClassDef(TTrueVertex,2); // Generated by MakeProject.
};
} // namespace
#endif
