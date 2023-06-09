//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Mar  3 11:08:52 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../buildlocalreader.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerECALReconModule__TECALReconVertexTrack_h
#define ND__TTrackerECALReconModule__TECALReconVertexTrack_h
namespace ND {
namespace TTrackerECALReconModule {
class TECALReconVertexTrack;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

namespace ND {
namespace TTrackerECALReconModule {
class TECALReconVertexTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   Int_t       Status;      //
   UInt_t      UniqueID;    //
   Int_t       NHits;       //
   Float_t     MatchingLikelihood;    //
   TLorentzVector FrontPosition;         //
   TVector3       FrontDirection;        //
   Int_t          FrontLayerNumber;      //
   TLorentzVector BackPosition;          //
   TVector3       BackDirection;         //
   Int_t          BackLayerNumber;       //
   Float_t        TotalCharge;           //
   Float_t        StraightTrackLength;    //
   Float_t        NodeTrackLength;        //
   Float_t        AverageHitTime;         //
   Int_t          G4IDSingle;             //
   double         PID_LLR_MIP_EM;         //
   double         PID_LLR_EM_HIP;         //
   double         PID_LLR_MIP_HIP;        //
   double         PID_LLR_MIP_HIP_VACut;    //
   double         Containment;              //

   TECALReconVertexTrack();
   TECALReconVertexTrack(const TECALReconVertexTrack & );
   virtual ~TECALReconVertexTrack();

   ClassDef(TECALReconVertexTrack,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
