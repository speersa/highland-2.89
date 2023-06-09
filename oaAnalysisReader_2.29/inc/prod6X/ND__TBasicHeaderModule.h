//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Mar 26 15:46:42 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90800000-0000_ztbqgqmrv5iz_anal_000_magnet201508airrun8-bsdv01_2.root
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
