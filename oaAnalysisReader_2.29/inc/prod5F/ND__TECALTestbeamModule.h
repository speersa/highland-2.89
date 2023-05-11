//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Nov  8 13:36:45 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/valid/oa_nt_beam_90410000-0002_g6rrt6tsqxr2_anal_000_prod005magnet201011waterc-bsdv01.root
//////////////////////////////////////////////////////////


#ifndef ND__TECALTestbeamModule_h
#define ND__TECALTestbeamModule_h
namespace ND {
class TECALTestbeamModule;
} // end of namespace.

#include "ND__TAnalysisReconModuleBase.h"

namespace ND {
class TECALTestbeamModule : public ND::TAnalysisReconModuleBase {

public:
// Nested classes declaration.

public:
// Data Members.
   int         Cerenkov1Lo[23];    //
   int         Cerenkov2Lo[23];    //
   int         Cerenkov1Hi[23];    //
   int         Cerenkov2Hi[23];    //
   int         TOF[23];            //
   int         TriggerWord;        //
   int         PIDResult;          //
   double      Momentum;           //
   int         Angle;              //

   TECALTestbeamModule();
   TECALTestbeamModule(const TECALTestbeamModule & );
   virtual ~TECALTestbeamModule();

   ClassDef(TECALTestbeamModule,2); // Generated by MakeProject.
};
} // namespace
#endif