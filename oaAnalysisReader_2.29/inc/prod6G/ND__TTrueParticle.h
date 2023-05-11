//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 17 16:54:42 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/PROD6/oa_nd_spl_00011000-0000_4stg6pqnornm_anal_001_v11r31p5-wg-bugaboo-bsdv01_2_prod6G.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrueParticle_h
#define ND__TTrueParticle_h
namespace ND {
class TTrueParticle;
} // end of namespace.

#include "TObject.h"
#include "ND__TTrueVertex.h"

namespace ND {
class TTrueParticle : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         ID;          ///< Trajectoy  Id
   double      Pur;         ///< The purity for matching the rec particle with the true particle
   double      Eff;         ///< The efficiency for matching the rec particle with the true particle
   ND::TTrueVertex Vertex;      ///< True vertex associated to this TrueParticle

   TTrueParticle();
   TTrueParticle(const TTrueParticle & );
   virtual ~TTrueParticle();

   ClassDef(TTrueParticle,2); // Generated by MakeProject.
};
} // namespace
#endif