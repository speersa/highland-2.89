//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TP0DObject_h
#define ND__TGlobalReconModule__TP0DObject_h
namespace ND {
namespace TGlobalReconModule {
class TP0DObject;
} // end of namespace.
} // end of namespace.

#include "ND__TSubBaseShowerObject.h"
#include "Riostream.h"
#include <vector>

namespace ND {
namespace TGlobalReconModule {
class TP0DObject : public ND::TSubBaseShowerObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Width;       ///< The width of the shower (perpendicular to the direction).
   double      avgtime;     ///< Averaged corrected node time.
   vector<int> ParticleId;    ///< A vector of potential PIDs, sorted by weight, c.f.  TP0DObject::PIDWeight.
   vector<double> PIDWeight;     ///< The weights for the PID hypotheses, c.f. TP0DObject::ParticleId

   TP0DObject();
   TP0DObject(const TP0DObject & );
   virtual ~TP0DObject();

   ClassDef(TP0DObject,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif