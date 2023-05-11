//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:43 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerReconModule__TTrueParticle_h
#define ND__TTrackerReconModule__TTrueParticle_h
namespace ND {
namespace TTrackerReconModule {
class TTrueParticle;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "ND__TTrueVertex.h"

namespace ND {
namespace TTrackerReconModule {
class TTrueParticle : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         ID;          //Trajectoy  Id
   double      Pur;         //The purity for matching
   double      Eff;         //The efficiency for matching
   ND::TTrueVertex Vertex;      //True vertex associated to this TrueParticle

   TTrueParticle();
   TTrueParticle(const TTrueParticle & );
   virtual ~TTrueParticle();

   ClassDef(TTrueParticle,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
