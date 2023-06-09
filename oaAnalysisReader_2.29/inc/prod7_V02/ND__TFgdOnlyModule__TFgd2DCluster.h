//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:35 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TFgdOnlyModule__TFgd2DCluster_h
#define ND__TFgdOnlyModule__TFgd2DCluster_h
namespace ND {
namespace TFgdOnlyModule {
class TFgd2DCluster;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <map>

namespace ND {
namespace TFgdOnlyModule {
class TFgd2DCluster : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    //The name of the algorithm..
   TLorentzVector Position;         //Charge-weighted position of the cluster.
   TVector3       PCADirection;     //Primary PCA eigenvector, associated with the direction of the cluster.
   TVector3       StartPosition;    //Identified "start" position of the cluster, from extrapolating along PCADrection.
   TVector3       EndPosition;      //Identified "end" position of the cluster, from extrapolating along PCADirection.
   double         Range;            //Range of shower along PCADirection
   double         AvgHitTime;       //Average time of hits in the cluster
   double         EDeposit;         //The energy deposited in the cluster.
   int            NumHits;          //The number of hits contributing to this cluster.
   std::map<int,int> Trajectories;     //Map of true trajectory IDs to the number of G4 contributors that contributed to this cluster.
   int               NDOF;             //The number of degrees of freedom in the reconstruction.
   double            Quality;          //The goodness of fit for the reconstruction.
   int               Status;           //The fit status.

   TFgd2DCluster();
   TFgd2DCluster(const TFgd2DCluster & );
   virtual ~TFgd2DCluster();

   ClassDef(TFgd2DCluster,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
