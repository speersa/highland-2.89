//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 17:55:45 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400072-0007_ok762udcurva_anal_000_magnet201011airrun4-bsdv01_2.root
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
