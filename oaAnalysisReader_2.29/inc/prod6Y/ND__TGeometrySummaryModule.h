//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 17:55:46 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400072-0007_ok762udcurva_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGeometrySummaryModule_h
#define ND__TGeometrySummaryModule_h
namespace ND {
class TGeometrySummaryModule;
} // end of namespace.

#include "ND__TAnalysisHeaderModuleBase.h"
#include "ND__TGeometrySummaryModule.h"
#include "Riostream.h"
#include <map>
#include <utility>
#include "TGeoNode.h"
#include "TObject.h"
#include "TVector3.h"

namespace ND {
class TGeometrySummaryModule : public ND::TAnalysisHeaderModuleBase {

public:
// Nested classes forward declaration.
class TDetectorBoundingBox;
class TTPCMicroMegasVolumes;

public:
// Nested classes declaration.
class TTPCMicroMegasVolumes : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   std::map<int,std::pair<int,const TGeoNode*> > MMvolumes;    //

   TTPCMicroMegasVolumes();
   TTPCMicroMegasVolumes(const TTPCMicroMegasVolumes & );
   virtual ~TTPCMicroMegasVolumes();

   ClassDef(TTPCMicroMegasVolumes,2); // Generated by MakeProject.
};
class TDetectorBoundingBox : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TVector3    Minimum;     //
   TVector3    Maximum;     //

   TDetectorBoundingBox();
   TDetectorBoundingBox(const TDetectorBoundingBox & );
   virtual ~TDetectorBoundingBox();

   ClassDef(TDetectorBoundingBox,2); // Generated by MakeProject.
};

public:
// Data Members.
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fFGD1;       //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fFGD2;       //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fP0D;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fFGD1Active;    //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fFGD2Active;    //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fP0DActive;     //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTPC1;          //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTPC2;          //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTPC3;          //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fDSECAL;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTECAL1;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTECAL2;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTECAL3;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTECAL4;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTECAL5;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fTECAL6;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fPECAL1;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fPECAL2;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fPECAL3;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fPECAL4;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fPECAL5;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fPECAL6;        //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fSMRD1;         //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fSMRD2;         //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fSMRD3;         //
   ND::TGeometrySummaryModule::TDetectorBoundingBox* fSMRD4;         //
   ND::TGeometrySummaryModule::TTPCMicroMegasVolumes* fMM;            //
   std::map<int,std::pair<int,const TGeoNode*> >      MMmap;          //

   TGeometrySummaryModule();
   TGeometrySummaryModule(const TGeometrySummaryModule & );
   virtual ~TGeometrySummaryModule();

   ClassDef(TGeometrySummaryModule,4); // Generated by MakeProject.
};
} // namespace
#endif
