//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov 23 12:47:33 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod6/RQS/oa_nt_beam_80510000-0000_leokxyiuc2jb_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__NRooTrackerVtx_h
#define ND__NRooTrackerVtx_h
namespace ND {
class NRooTrackerVtx;
} // end of namespace.

#include "ND__JNuBeamFlux.h"
#include "TObjString.h"

namespace ND {
class NRooTrackerVtx : public ND::JNuBeamFlux {

public:
// Nested classes declaration.

public:
// Data Members.
   TObjString* EvtCode;     //
   int         EvtNum;      //
   double      EvtXSec;     //
   double      EvtDXSec;    //
   double      EvtWght;     //
   double      EvtProb;     //
   double      EvtVtx[4];    //
   int         StdHepN;      //
   Int_t      *StdHepPdg;    //[StdHepN]
   Int_t      *StdHepStatus;    //[StdHepN]
   double      StdHepX4[100][4];    //
   double      StdHepP4[100][4];    //
   double      StdHepPolz[100][3];    //
   Int_t      *StdHepFd;              //[StdHepN]
   Int_t      *StdHepLd;              //[StdHepN]
   Int_t      *StdHepFm;              //[StdHepN]
   Int_t      *StdHepLm;              //[StdHepN]
   int         NEnvc;                 //
   Int_t      *NEipvc;                //[NEnvc]
   float       NEpvc[100][3];         //
   Int_t      *NEiorgvc;              //[NEnvc]
   Int_t      *NEiflgvc;              //[NEnvc]
   Int_t      *NEicrnvc;              //[NEnvc]
   float       NEcrsx;                //
   float       NEcrsy;                //
   float       NEcrsz;                //
   float       NEcrsphi;              //
   int         NEnvert;               //
   float       NEposvert[100][3];     //
   Int_t      *NEiflgvert;            //[NEnvert]
   int         NEnvcvert;             //
   float       NEdirvert[300][3];     //
   Float_t    *NEabspvert;            //[NEnvcvert]
   Float_t    *NEabstpvert;           //[NEnvcvert]
   Int_t      *NEipvert;              //[NEnvcvert]
   Int_t      *NEiverti;              //[NEnvcvert]
   Int_t      *NEivertf;              //[NEnvcvert]
   int         NFnvert;               //
   Int_t      *NFiflag;               //[NFnvert]
   Float_t    *NFx;                   //[NFnvert]
   Float_t    *NFy;                   //[NFnvert]
   Float_t    *NFz;                   //[NFnvert]
   Float_t    *NFpx;                  //[NFnvert]
   Float_t    *NFpy;                  //[NFnvert]
   Float_t    *NFpz;                  //[NFnvert]
   Float_t    *NFe;                   //[NFnvert]
   Int_t      *NFfirststep;           //[NFnvert]
   int         NFnstep;               //
   Float_t    *NFecms2;               //[NFnstep]
   TObjString* GeomPath;              //
   TObjString* GeneratorName;         //
   TObjString* OrigFileName;          //
   TObjString* OrigTreeName;          //
   int         OrigEvtNum;            //
   int         OrigTreeEntries;       //
   double      OrigTreePOT;           //
   double      TimeInSpill;           //
   int         TruthVertexID;         //

   NRooTrackerVtx();
   NRooTrackerVtx(const NRooTrackerVtx & );
   virtual ~NRooTrackerVtx();

   ClassDef(NRooTrackerVtx,2); // Generated by MakeProject.
};
} // namespace
#endif
