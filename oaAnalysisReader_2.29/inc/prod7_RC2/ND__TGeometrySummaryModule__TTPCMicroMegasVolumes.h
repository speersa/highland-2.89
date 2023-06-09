//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Sep 15 17:37:36 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/oa_nt_beam_80730000-0000_ngg4oj3wpuhl_anal_000_nu-bsdv01_2.root
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
