//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Mar 26 15:46:42 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90800000-0000_ztbqgqmrv5iz_anal_000_magnet201508airrun8-bsdv01_2.root
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