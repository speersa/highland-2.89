//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:09:41 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710119-0055_df7igapcoooo_anal_000_nu-bsdv01_2.root
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