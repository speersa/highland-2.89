//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:35 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerReconModule__TTPCTrack_h
#define ND__TTrackerReconModule__TTPCTrack_h
namespace ND {
namespace TTrackerReconModule {
class TTPCTrack;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

namespace ND {
namespace TTrackerReconModule {
class TTPCTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned int UniqueID;    //Unique ID number to allow matching to Global Reconobject.
   int          Detector;    //TPC number 1, 2 or 3
   int          Ndof;        //Number of degrees of freedom in TPC fit
   double       Chi2;        //TPC chi2 calculated after likelihood fit
   int          NHits;       //number of clusters used in TPC fit
   double       Momentum;    //Momentum of the TPC pid in MeV/c
   double       MomentumError;    //Uncertainty in the Momentum in MeV/c from theTPC pid
   double       Charge;           //Charge from the TPC pid (+1, or -1)
   TLorentzVector Position;         //Position at which kinematics are reported in mm, ns
   TLorentzVector PositionVariance;    //Variance in Position  in mm^2, ns^2
   TVector3       Direction;           //TPC pid direction vector in mm
   TVector3       DirectionVariance;    //TPC pid variance in vector direction in mm^2
   double         NTrun;                //70% of the number of clusters
   double         Ccorr;                //Corrected truncated mean charge deposit in PID
   double         PullEle;              //Pull for TPC pid electron hypothesis
   double         PullMuon;             //Pull for TPC pid muon hypothesis
   double         PullPion;             //Pull for TPC pid pion hypothesis
   double         PullKaon;             //Pull for TPC pid kaon hypothesis
   double         PullProton;           //Pull for TPC pid proton hypothesis
   double         dEdxexpEle;           //Estimated dE/dx for electron hypothesis
   double         dEdxexpMuon;          //Estimated dE/dx for muon hypothesis
   double         dEdxexpPion;          //Estimated dE/dx for pion hypothesis
   double         dEdxexpKaon;          //Estimated dE/dx for kaon hypothesis
   double         dEdxexpProton;        //Estimated dE/dx for proton hypothesis
   double         SigmaEle;             //Sigma estimated width of TPC pid electron hypothesis
   double         SigmaMuon;            //Sigma estimated width of TPC pid muon hypothesis
   double         SigmaPion;            //Sigma estimated width of TPC pid pion hypothesis
   double         SigmaKaon;            //Sigma estimated width of TPC pid kaon hypothesis
   double         SigmaProton;          //Sigma estimated width of TPC pid proton hypothesis
   double         Sigma0;               //TPC track diffusion sigma0 parameter
   double         Sigma1;               //TPC track diffusion sigma1 parameter
   double         Sigma2;               //TPC track diffusion sigma2 parameter
   double         MeanDrift;            //TPC track mean drift value used in diffusion model
   int            NConstituents;        //
   TVector3       TrDirection;          //track direction vector
   TVector3       TrDirectionVar;       //variance in track direction vector
   double         TrCurvature;          //track curvature, units are 1/mm
   double         TrCurvatureVar;       //variance in track direction vector, units are(1mm)^2
   bool           HasExtrapolation;     //extrapolation method of vertex is calculated ornot
   double         ExtrapolatedVertexXX;    //for xbar vertex, this is x coordinate in mm
   double         ExtrapolatedVertexZX;    //for xbar vertex, this is z coordinate in mm
   double         ExtrapolatedVertexYY;    //for ybar vertex, this is y coordinate in mm
   double         ExtrapolatedVertexZY;    //for ybar vertex, this is z coordinate in mm
   bool           EnteringFGD;             //not sure

   TTPCTrack();
   TTPCTrack(const TTPCTrack & );
   virtual ~TTPCTrack();

   ClassDef(TTPCTrack,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif