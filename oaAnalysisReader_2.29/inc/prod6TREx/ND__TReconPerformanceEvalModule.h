//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Nov  9 15:39:21 2016 by ROOT version 5.34/09)
//      from the StreamerInfo in file /Users/izmaylov/Downloads/oa_nt_beam_90210000-0000_2e7lhce5kvor_anal_000_prod6amagnet201011waterb-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TReconPerformanceEvalModule_h
#define ND__TReconPerformanceEvalModule_h
namespace ND {
class TReconPerformanceEvalModule;
} // end of namespace.

#include "ND__TAnalysisReconModuleBase.h"
#include "TClonesArray.h"
#include "Riostream.h"
#include <map>
#include "TObject.h"
#include <string>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "ND__TReconPerformanceEvalModule.h"

namespace ND {
class TReconPerformanceEvalModule : public ND::TAnalysisReconModuleBase {

public:
// Nested classes forward declaration.
class TGlobalReconObject;
class TGlobalTruthInfo;

public:
// Nested classes declaration.
class TGlobalTruthInfo : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   bool        SetOK;       //
   double      Momentum;    /// < Momentum of the true trajectory
   TVector3    Direction;    /// < Direction of the true trajectory
   double      Charge;       /// < Charge of the trajectory
   TLorentzVector Position;     /// < Initial position of the trajectory
   double         Efficiency;    /// < Efficiency of this truth matching
   double         Purity;        /// < Purity of this truth matching

   TGlobalTruthInfo();
   TGlobalTruthInfo(const TGlobalTruthInfo & );
   virtual ~TGlobalTruthInfo();

   ClassDef(TGlobalTruthInfo,2); // Generated by MakeProject.
};
class TGlobalReconObject : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   bool        SetOK;       //
   Int_t       NConstituents;    //
   map<string,int>* NModuleConstituents;    //
   string           SubdetectorString;      //
   string           StatusString;           //
   TClonesArray*    GlobalNodes;            //
   Int_t            NGlobalNodes;           //
   Int_t            NGlobalNodesSaved;      //
   double           Momentum;               //
   double           MomentumByRange;        //
   double           MomentumByRangeMuon;    //
   double           MomentumByRangeMuonFlip;    //
   double           MomentumByRangeElectron;    //
   double           MomentumByRangeElectronFlip;    //
   double           MomentumByRangeProton;          //
   double           MomentumByRangeProtonFlip;      //
   TLorentzVector   Position;                       //
   TVector3         Direction;                      //
   double           Charge;                         //
   double           Quality;                        //
   int              NDOF;                           //
   string           ParticleID;                     //
   double           PIDWeight;                      //
   TClonesArray*    MatchingChi2Info;               //
   int              NMatchingChi2Info;              //
   ND::TReconPerformanceEvalModule::TGlobalTruthInfo Truth;                          //
   TClonesArray*                                     Constituents;                   //
   TClonesArray*                                     DownToTrackerConstituents;      //
   Int_t                                             NDownToTrackerConstituents;     //
   UInt_t                                            UniqueID;                       //

   TGlobalReconObject();
   TGlobalReconObject(const TGlobalReconObject & );
   virtual ~TGlobalReconObject();

   ClassDef(TGlobalReconObject,2); // Generated by MakeProject.
};

public:
// Data Members.
   Int_t       fNGlobalReconObjects;    //
   TClonesArray* fGlobalReconObjects;     //
   std::vector<std::pair<std::string,int> > fHitInfo;                //
   bool                                     fSaveAllGlobalNodes;     //

   TReconPerformanceEvalModule();
   TReconPerformanceEvalModule(const TReconPerformanceEvalModule & );
   virtual ~TReconPerformanceEvalModule();

   ClassDef(TReconPerformanceEvalModule,2); // Generated by MakeProject.
};
} // namespace
#endif
