//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Mar 26 15:46:42 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90800000-0000_ztbqgqmrv5iz_anal_000_magnet201508airrun8-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TDatum_h
#define ND__TDatum_h
namespace ND {
class TDatum;
} // end of namespace.

#include "TNamed.h"
#include "ND__TDatum.h"

namespace ND {
class TDatum : public TNamed {

public:
// Nested classes declaration.

public:
// Data Members.
   ND::TDatum* fParent;     //

   TDatum();
   TDatum(const TDatum & );
   virtual ~TDatum();

   ClassDef(TDatum,3); // Generated by MakeProject.
};
} // namespace
#endif
