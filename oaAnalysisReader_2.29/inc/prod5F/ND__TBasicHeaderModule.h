//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Nov  8 13:36:45 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/valid/oa_nt_beam_90410000-0002_g6rrt6tsqxr2_anal_000_prod005magnet201011waterc-bsdv01.root
//////////////////////////////////////////////////////////


#ifndef ND__TBasicHeaderModule_h
#define ND__TBasicHeaderModule_h
namespace ND {
class TBasicHeaderModule;
} // end of namespace.

#include "ND__TAnalysisHeaderModuleBase.h"

namespace ND {
class TBasicHeaderModule : public ND::TAnalysisHeaderModuleBase {

public:
// Nested classes declaration.

public:
// Data Members.
   Char_t      fSoftwareVersion[50];    //
   bool        fSoftware;               //

   TBasicHeaderModule();
   TBasicHeaderModule(const TBasicHeaderModule & );
   virtual ~TBasicHeaderModule();

   ClassDef(TBasicHeaderModule,2); // Generated by MakeProject.
};
} // namespace
#endif
