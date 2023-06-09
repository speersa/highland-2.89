//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:36 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerECALReconModule__TECALReconCluster_h
#define ND__TTrackerECALReconModule__TECALReconCluster_h
namespace ND {
namespace TTrackerECALReconModule {
class TECALReconCluster;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"

namespace ND {
namespace TTrackerECALReconModule {
class TECALReconCluster : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TLorentzVector Position;    //The cluster position.
   TLorentzVector PositionVar;    //The cluster position variance.
   int            NDOF;           //The number of degrees of freedom in the reconstruction.
   double         EDeposit;       //The charge deposited by the cluster.

   TECALReconCluster();
   TECALReconCluster(const TECALReconCluster & );
   virtual ~TECALReconCluster();

   ClassDef(TECALReconCluster,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
