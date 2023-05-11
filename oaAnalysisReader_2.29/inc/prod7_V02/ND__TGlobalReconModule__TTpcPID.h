//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:36 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TTpcPID_h
#define ND__TGlobalReconModule__TTpcPID_h
namespace ND {
namespace TGlobalReconModule {
class TTpcPID;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include "TVector3.h"
#include <vector>
#include "TLorentzVector.h"
#include "ND__TTrueParticle.h"

namespace ND {
namespace TGlobalReconModule {
class TTpcPID : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    //The name of the algorithm that created this object.
   unsigned long Detectors;        //Detectors used, defined according to the algorithm in GetDetectorNumber.
   unsigned long Status;           //The status for the fit, from: object->CheckStatus(object->kSuccess).
   int           NDOF;             //The number of degrees of freedom.
   double        Chi2;             //The chi2 of the fit.
   int           NNodes;           //The number of nodes
   int           NHits;            //The number of hits.
   int           NConstituents;    //The number of constituents.
   bool          isForward;        //Sense of object.
   double        Charge;           //The Charge
   double        EDeposit;         //The deposited charge for the object.
   TVector3      Cone;             //The opening angles of the cone (only for showers)
   double        Width;            //The width of the shower (perpendicular to the direction)
   double        Length;           //The total length of the object
   vector<double> Likelihoods;      /// the PID likelihoods for combined PID
   TLorentzVector FrontPosition;    //The position of the object.
   TLorentzVector BackPosition;     //The position of the object.
   TLorentzVector FrontPositionVar;    //The position variance;
   TLorentzVector BackPositionVar;     //The position variance;
   TVector3       FrontDirection;      //The direction of the object.
   TVector3       BackDirection;       //The direction of the object.
   TVector3       FrontDirectionVar;    //The direction variance of the object.
   TVector3       BackDirectionVar;     //The direction variance of the object.
   double         FrontMomentum;        //the momentum of the object
   double         BackMomentum;         //the momentum of the object
   double         FrontMomentumError;    //the error on the momentum of the object
   double         BackMomentumError;     //the error on the momentum of the object
   TLorentzVector PositionAtTrueVertex;    //Position at true vertex.
   TLorentzVector PositionVarAtTrueVertex;    //The position variance at the true vertex.
   TVector3       DirectionAtTrueVertex;      //Direction at the true vertex.
   TVector3       DirectionVarAtTrueVertex;    //The direction variance at the true vertex.
   double         MomentumAtTrueVertex;        //Momentum at the true vertex.
   double         MomentumErrorAtTrueVertex;    //The momentum variance at the true vertex.
   vector<TLorentzVector*> EntrancePosition;             //the position of the object at the entrance of each subdetector
   vector<TLorentzVector*> ExitPosition;                 //the position of the object at the exit of each subdetector
   ND::TTrueParticle       TrueParticle;                 //The true particle

   TTpcPID();
   TTpcPID(const TTpcPID & );
   virtual ~TTpcPID();

   ClassDef(TTpcPID,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
