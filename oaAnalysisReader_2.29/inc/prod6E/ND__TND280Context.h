//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 17 16:53:10 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/PROD6/oa_nd_spl_00011000-0000_4stgpe5m7bc7_anal_000_v11r31p5-wg-bugaboo-bsdv01_2_prod6E.root
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
