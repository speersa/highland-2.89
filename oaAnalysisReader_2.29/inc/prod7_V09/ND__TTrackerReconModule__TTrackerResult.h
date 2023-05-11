//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:09:42 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710119-0055_df7igapcoooo_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerReconModule__TTrackerResult_h
#define ND__TTrackerReconModule__TTrackerResult_h
namespace ND {
namespace TTrackerReconModule {
class TTrackerResult;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include "TClonesArray.h"
#include <vector>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "ND__TTrackerReconModule__TTrueParticle.h"
#include "ND__TTrackerReconModule__TTrackerConstituent.h"
#include "ND__TTrackerReconModule__TTPCTrack.h"
#include "ND__TTrackerReconModule__TFGDTrack.h"
#include "ND__TTrackerReconModule__TTrackerNode.h"

namespace ND {
namespace TTrackerReconModule {
class TTrackerResult : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   unsigned int UniqueID;    //Unique ID number to allow matching to Global Reconobject.
   string       AlgorithmName;    //The name of the algorithm that created this object.
   int          Detectors;        //Detectors used
   unsigned long Status;           //The status for the fit.
   double        Quality;          //The quality of the fit.(probability(chi2,ndof))
   int           NDOF;             //The number of degrees of freedom.
   double        Chi2;             //The chi2 of the fit.
   int           NHits;            //The number of hits.
   int           NConstituents;    //The number of constituents (tracks and pids) usedto build this track
   int           ConstitIdx[2];    //Index into Constituents of the constituents usedto build this track
   int           NTotalConstituents;    //Number of all constituents, andconstituents-constituents...
   TClonesArray* Constituents;          //All constituents, and constituents-constituents...
   bool          isForward;             //Sense of object.
   double        Charge;                //The Charge (+-1)
   double        EDeposit;              //The deposited charge for the object (number of pe's)
   double        Length;                //The total length of the object in mm
   int           matchingFailure_flag;    //Flag a object where the TPC-FGD matchingfailed
   vector<double> Likelihoods;             //
   vector<int>    Pids;                    //the PID that goes with Likelihoods
   TLorentzVector Position;                //track position 4-vector (x,y,z,t) in mm, ns
   TLorentzVector Variance;                //track position variance 4-vectorvar(x),var(y),var(z),var(t) in mm^2, ns^2
   TVector3       Direction;               //track direction vector
   TVector3       DirectionVariance;       //track direction variance
   double         Momentum;                //track momentum MeV/c
   double         MomentumError;           //track momentum MeV/c
   ND::TTrackerReconModule::TTrueParticle TrueParticle;            //information about the true particleassociated with this track
   int                                    NTPCs;                   //Number of TPC tracks used to build this track
   TClonesArray*                          TPC;                     //Information about the TPC pids/tracks used to buildthis track
   int                                    NFGDs;                   //Number of FGD Specific objects
   TClonesArray*                          FGD;                     //FGD objects associated with track
   int                                    NNodes;                  //The number of nodes (fgd hits + tpc tracks)
   TClonesArray*                          Nodes;                   //Kinematics of the track at each node in the track fit
   ND::TTrackerReconModule::TTrackerConstituent hackConstituentsObject;    //This is just here to foolTFile::MakeProject, not areal object.
   ND::TTrackerReconModule::TTPCTrack           hackTPCTrack;              //This is just here to fool TFile::MakeProject,not a real object.
   ND::TTrackerReconModule::TFGDTrack           hackFGDTrack;              //This is just here to fool TFile::MakeProject,not a real object.
   ND::TTrackerReconModule::TTrackerNode        hackNodes;                 //This is just here to fool TFile::MakeProject,not a real object.

   TTrackerResult();
   TTrackerResult(const TTrackerResult & );
   virtual ~TTrackerResult();

   ClassDef(TTrackerResult,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif