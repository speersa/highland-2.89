//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jan 20 12:54:43 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file test_ev_anal.root
//////////////////////////////////////////////////////////


#ifndef ND__TGeometrySummaryModule__TDetectorBoundingBox_h
#define ND__TGeometrySummaryModule__TDetectorBoundingBox_h
namespace ND {
namespace TGeometrySummaryModule {
class TDetectorBoundingBox;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TVector3.h"

namespace ND {
namespace TGeometrySummaryModule {
class TDetectorBoundingBox : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TVector3    Minimum;     //
   TVector3    Maximum;     //

   TDetectorBoundingBox();
   TDetectorBoundingBox(const TDetectorBoundingBox & );
   virtual ~TDetectorBoundingBox();

   ClassDef(TDetectorBoundingBox,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
