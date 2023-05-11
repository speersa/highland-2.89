//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:35 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
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