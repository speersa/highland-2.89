//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Sep 15 17:37:36 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/oa_nt_beam_80730000-0000_ngg4oj3wpuhl_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TDataVector_h
#define ND__TDataVector_h
namespace ND {
class TDataVector;
} // end of namespace.

#include "ND__TData.h"
#include "Riostream.h"
#include <vector>
#include "ND__TDatum.h"

namespace ND {
class TDataVector : public ND::TData {

public:
// Nested classes declaration.

public:
// Data Members.
   vector<ND::TDatum*> fVector;     //

   TDataVector();
   TDataVector(const TDataVector & );
   virtual ~TDataVector();

   ClassDef(TDataVector,5); // Generated by MakeProject.
};
} // namespace
#endif
