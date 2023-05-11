//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Mar 26 15:46:42 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90800000-0000_ztbqgqmrv5iz_anal_000_magnet201508airrun8-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TND280Context_h
#define ND__TND280Context_h
namespace ND {
class TND280Context;
} // end of namespace.

#include "TNamed.h"

namespace ND {
class TND280Context {

public:
// Nested classes forward declaration.
enum Time { kDefault_Time };

public:
// Nested classes declaration.

public:
// Data Members.
   int         fPartition;    //
   int         fRun;          //
   int         fSubRun;       //
   int         fEvent;        //
   int         fSpill;        //
   UInt_t      fTimeStamp;    //

   TND280Context();
   TND280Context(const TND280Context & );
   virtual ~TND280Context();

};
} // namespace
#endif
