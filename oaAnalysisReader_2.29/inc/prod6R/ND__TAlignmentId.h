//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov 23 12:47:33 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod6/RQS/oa_nt_beam_80510000-0000_leokxyiuc2jb_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TAlignmentId_h
#define ND__TAlignmentId_h
namespace ND {
class TAlignmentId;
} // end of namespace.

#include "ND__TSHAHashValue.h"
#include "Riostream.h"
#include <string>

namespace ND {
class TAlignmentId : public ND::TSHAHashValue {

public:
// Nested classes declaration.

public:
// Data Members.
   string      fDocString;    //

   TAlignmentId();
   TAlignmentId(const TAlignmentId & );
   virtual ~TAlignmentId();

};
} // namespace
#endif
