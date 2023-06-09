//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov  4 11:44:16 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/valid/oa_nt_beam_90410000-0000_h252u2jujozw_anal_000_prod005magnet201011waterc-bsdv01.root
//////////////////////////////////////////////////////////


#ifndef ND__ToaAnalysisUtils_h
#define ND__ToaAnalysisUtils_h
namespace ND {
class ToaAnalysisUtils;
} // end of namespace.

#include "TObject.h"

namespace ND {
class ToaAnalysisUtils : public TObject {

public:
// Nested classes forward declaration.
enum EParticleCategory { kDefault_EParticleCategory };
enum ESubdetector { kDefault_ESubdetector };

public:
// Nested classes declaration.

public:
// Data Members.

   ToaAnalysisUtils();
   ToaAnalysisUtils(const ToaAnalysisUtils & );
   virtual ~ToaAnalysisUtils();

   ClassDef(ToaAnalysisUtils,2); // Generated by MakeProject.
};
} // namespace
#endif
