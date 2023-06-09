//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov 23 12:47:33 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod6/RQS/oa_nt_beam_80510000-0000_leokxyiuc2jb_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TSmrdReconModule_h
#define ND__TSmrdReconModule_h
namespace ND {
class TSmrdReconModule;
} // end of namespace.

#include "ND__TAnalysisReconModuleBase.h"
#include "TClonesArray.h"
#include "TObject.h"
#include "TLorentzVector.h"
#include "Riostream.h"
#include <string>
#include "TVector3.h"

namespace ND {
class TSmrdReconModule : public ND::TAnalysisReconModuleBase {

public:
// Nested classes forward declaration.
class TSmrdReconHit;
class TSmrdIsoTrack;

public:
// Nested classes declaration.
class TSmrdIsoTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   UInt_t      UniqueID;    //
   string      AlgorithmName;    //
   TLorentzVector FrontPos;         //
   TLorentzVector FrontPosVariance;    //
   TLorentzVector BackPos;             //
   TLorentzVector BackPosVariance;     //
   TVector3       Direction;           //
   TVector3       DirectionVariance;    //
   int            NHits;                //
   int            NNodes;               //
   int            Status;               ///<status of the refitted smrd track (kSuccess)
   int            KalmanStatus;         ///<status to check that a track was successfully Kalman refitted
   int            NDOF;                 //
   double         EDeposit;             ///<total charge of the object
   double         avgtime;              ///<hits averaged time
   double         Range;                //
   double         Chi2;                 //
   double         ThetaAngle;           //
   double         PhiAngle;             //
   TLorentzVector TrueInitPos;          //
   Int_t          TrueInitDet;          //
   TLorentzVector TrueFinalPos;         //
   Int_t          TrueFinalDet;         //
   TLorentzVector TrueInitMom;          //
   int            TrueId;               //
   int            TruePDG;              //
   int            TrueParentId;         //
   double         TrueHitPurity;        //
   double         TrueHitEff;           //

   TSmrdIsoTrack();
   TSmrdIsoTrack(const TSmrdIsoTrack & );
   virtual ~TSmrdIsoTrack();

   ClassDef(TSmrdIsoTrack,2); // Generated by MakeProject.
};
class TSmrdReconHit : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TLorentzVector Position;    //
   TLorentzVector PositionUncertainty;    //
   double         Charge;                 //
   double         dZ;                     //
   double         dT;                     //
   double         ContribCharge[2];       //
   int            Wall;                   //
   int            Yoke;                   //
   int            Layer;                  //
   int            Tower;                  //
   int            Counter;                //
   UInt_t         RMM;                    //
   UInt_t         TFB;                    //
   bool           IsInnerMatched;         //
   bool           IsUsed;                 //

   TSmrdReconHit();
   TSmrdReconHit(const TSmrdReconHit & );
   virtual ~TSmrdReconHit();

   ClassDef(TSmrdReconHit,2); // Generated by MakeProject.
};

public:
// Data Members.
   Int_t       fNSmrdReconHits;    ///< The number of SMRD TReconHits.
   TClonesArray* fSmrdReconHits;     ///< The SMRD TReconHits.
   Int_t         fNSmrdIsoTracks;    ///< The number of SMRD isolated tracks.
   TClonesArray* fSmrdIsoTracks;     ///< The SMRD isolated tracks.

   TSmrdReconModule();
   TSmrdReconModule(const TSmrdReconModule & );
   virtual ~TSmrdReconModule();

   ClassDef(TSmrdReconModule,4); // Generated by MakeProject.
};
} // namespace
#endif
