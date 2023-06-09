//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
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
