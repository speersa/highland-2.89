//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGeometrySummaryModule__TTPCMicroMegasVolumes_h
#define ND__TGeometrySummaryModule__TTPCMicroMegasVolumes_h
namespace ND {
namespace TGeometrySummaryModule {
class TTPCMicroMegasVolumes;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <map>
#include <utility>
#include "TGeoNode.h"

namespace ND {
namespace TGeometrySummaryModule {
class TTPCMicroMegasVolumes : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   std::map<int,std::pair<int,const TGeoNode*> > MMvolumes;    //

   TTPCMicroMegasVolumes();
   TTPCMicroMegasVolumes(const TTPCMicroMegasVolumes & );
   virtual ~TTPCMicroMegasVolumes();

   ClassDef(TTPCMicroMegasVolumes,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
