//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:01:37 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90810096-0055_quxcl5i7qxq4_anal_000_magnet201508waterrun8-bsdv01_2.root
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
