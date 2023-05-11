//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:36 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
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
   double      Width;       //The width of the shower (perpendicular to the direction).
   double      avgtime;     //Averaged corrected node time.
   vector<int> ParticleId;    //A vector of potential PIDs, sorted by weight, c.f.  TP0DObject::PIDWeight.
   vector<double> PIDWeight;     //The weights for the PID hypotheses, c.f. TP0DObject::ParticleId

   TP0DObject();
   TP0DObject(const TP0DObject & );
   virtual ~TP0DObject();

   ClassDef(TP0DObject,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif