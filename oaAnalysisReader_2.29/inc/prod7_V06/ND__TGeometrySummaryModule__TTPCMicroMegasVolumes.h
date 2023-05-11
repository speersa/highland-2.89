//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 18:05:54 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400000-0000_2sxl5m3goua7_anal_000_magnet201011airrun4-bsdv01_2.root
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
   std::map<int,std::pair<int,const TGeoNode*> > MMvolumes;    // (pair<int,pair<int,const TGeoNode*> >)

   TTPCMicroMegasVolumes();
   TTPCMicroMegasVolumes(const TTPCMicroMegasVolumes & );
   virtual ~TTPCMicroMegasVolumes();

   ClassDef(TTPCMicroMegasVolumes,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif