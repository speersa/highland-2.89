//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TGlobalVertex_h
#define ND__TGlobalReconModule__TGlobalVertex_h
namespace ND {
namespace TGlobalReconModule {
class TGlobalVertex;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "ND__TTrueVertex.h"
#include "ND__TGlobalReconModule__TVertexConstituent.h"

namespace ND {
namespace TGlobalReconModule {
class TGlobalVertex : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         PrimaryIndex;    ///< The index of the corresponding primary vertex
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   int         Status;           ///< The status for the fit.
   double      Quality;          ///<  The quality of the fit.  For Vertices created using -O TGlobalReconModule=UseECalVertices  the quality denotes whether all constituents were correctly found  1: for all found  0: for not all found  Not finding them is an internal TGlobalReconModule error and these  vertices should not be trusted.
   int         NDOF;             ///< The number of degrees of freedom.
   TLorentzVector Position;         ///< The position of the vertex.
   TLorentzVector Variance;         ///< The position variance;
   Int_t          NTrueVertices;    ///< The true vertex
   TClonesArray*  TrueVertices;     ///< The true vertex
   Int_t          NConstituents;    ///< Constituent tracks
   TClonesArray*  Constituents;     ///< Constituent tracks
   ND::TTrueVertex hackTrueVertexObject;    ///< This is just here to fool TFile::MakeProject, not a real object.
   ND::TGlobalReconModule::TVertexConstituent hackVertexConstituentObject;    ///< This is just here to fool TFile::MakeProject, not a real object.

   TGlobalVertex();
   TGlobalVertex(const TGlobalVertex & );
   virtual ~TGlobalVertex();

   ClassDef(TGlobalVertex,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
