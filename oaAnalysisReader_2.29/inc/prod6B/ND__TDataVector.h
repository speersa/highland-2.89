//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov  4 15:38:32 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/valid/oa_nt_beam_90210042-0030_bbzjto7xz4zh_anal_000_prod6amagnet201011waterb-bsdv01_2.root
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