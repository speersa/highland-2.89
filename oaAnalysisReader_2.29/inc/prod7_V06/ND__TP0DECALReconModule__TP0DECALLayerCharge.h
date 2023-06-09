//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 18:05:56 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400000-0000_2sxl5m3goua7_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DECALReconModule__TP0DECALLayerCharge_h
#define ND__TP0DECALReconModule__TP0DECALLayerCharge_h
namespace ND {
namespace TP0DECALReconModule {
class TP0DECALLayerCharge;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include <TString.h>

namespace ND {
namespace TP0DECALReconModule {
class TP0DECALLayerCharge : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      FirstTime;    //The earliest hit time of the relevant cluster.
   double      LastTime;     //The latest hit time of the relevant cluster.
   double      Charge[6];    //The total charge deposited in each of 6layers. Index 0  corresponds the innermost layer
   TString     module_name;    //The name of the module.

   TP0DECALLayerCharge();
   TP0DECALLayerCharge(const TP0DECALLayerCharge & );
   virtual ~TP0DECALLayerCharge();

   ClassDef(TP0DECALLayerCharge,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
