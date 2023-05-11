//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTRExReconModule__TTPCAnaPath_h
#define ND__TTRExReconModule__TTPCAnaPath_h
namespace ND {
namespace TTRExReconModule {
class TTPCAnaPath;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TVector3.h"

namespace ND {
namespace TTRExReconModule {
class TTPCAnaPath : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   Int_t       PathID;      ///< A unique identifier for the path within the pattern.
   Int_t       G4ID;        ///< G4 ID of the primary true trajectory associated with this path.
   Int_t       PathMatchingID;    //< A unique identifier for the path within the event.
   TVector3    FirstPosition;     ///< The start position of the path.
   TVector3    LastPosition;      ///< The end position of the path.
   Double_t    Time;              ///< The T0 for the path.
   Double_t    Length;            ///< The length of the path.
   Double_t    Momentum;          ///< The momentum of the path.
   Double_t    MomentumError;     ///< The momentum error of the path.
   TVector3    Direction;         ///< The direction of the path.
   Bool_t      IsContained;       ///< True if the path does not leave the TPC; false otherwise.
   Bool_t      LikFit;            ///< True if the likelihood fit was performed
   Bool_t      Success;           ///< True if the likelihood fit succeeded
   Double_t    FitLikelihood;     ///< Value of log likelihood from fit
   Int_t       T0Source;          ///< Enumerator of T0 sources.
   Int_t       NClusters;         ///< Number of clusters in the path.
   Double_t    Charge;            ///< Charge of the path
   Double_t    ElePull;           //
   Double_t    EleExp;            //
   Double_t    EleSigma;          //
   Double_t    MuonPull;          //
   Double_t    MuonExp;           //
   Double_t    MuonSigma;         //
   Double_t    PionPull;          //
   Double_t    PionExp;           //
   Double_t    PionSigma;         //
   Double_t    ProtonPull;        //
   Double_t    ProtonExp;         //
   Double_t    ProtonSigma;       //
   Double_t    KaonPull;          //
   Double_t    KaonExp;           //
   Double_t    KaonSigma;         //
   Double_t    PDist;             //
   Double_t    PEField;           //
   Double_t    T0Range[2];        //
   Double_t    T0RangeDeltaX[2];    //
   Int_t       PID;                 ///< The PID of the path.
   Double_t    NetCharge;           ///< The total charge left by the path on the micromegas
   Int_t       NJunctions;          ///< The number of junctions to which the path connects.
   Int_t      *JunctionIDs;         //[NJunctions]
   Int_t       NMatchingPaths;      ///< The number of paths to which this path might be matched.
   Int_t      *MatchingPathIDs;     //[NMatchingPaths]
   Double_t   *PathMatchingLikelihood;    //[NMatchingPaths]
   Int_t       NMatchingPatterns;         //
   Int_t      *MatchingPatternIDs;        //[NMatchingPatterns]
   Int_t      *MatchingPatternPathIDs;    //[NMatchingPatterns]
   Double_t   *PatternMatchingLikelihood;    //[NMatchingPatterns]

   TTPCAnaPath();
   TTPCAnaPath(const TTPCAnaPath & );
   virtual ~TTPCAnaPath();

   ClassDef(TTPCAnaPath,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
