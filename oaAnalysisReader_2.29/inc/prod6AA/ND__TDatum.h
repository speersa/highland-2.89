//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:01:37 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90810096-0055_quxcl5i7qxq4_anal_000_magnet201508waterrun8-bsdv01_2.root
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
