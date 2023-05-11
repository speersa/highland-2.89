//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTruthTrajectoriesModule__TTruthTrajectoryPoint_h
#define ND__TTruthTrajectoriesModule__TTruthTrajectoryPoint_h
namespace ND {
namespace TTruthTrajectoriesModule {
class TTruthTrajectoryPoint;
} // end of namespace.
} // end of namespace.

#include "TObject.h"

namespace ND {
namespace TTruthTrajectoriesModule {
class TTruthTrajectoryPoint : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   Int_t       ProcessType;    ///<  The process type that caused the Monte Carlo to generate this  point.
   Float_t     PositionX;      ///< The X position of the trajectory point [mm].
   Float_t     PositionY;      ///< The Y position of the trajectory point [mm].
   Float_t     PositionZ;      ///< The Z position of the trajectory point [mm].
   Float_t     PositionT;      ///< The time of the trajectory point [ns].
   Float_t     MomentumX;      ///< The X momentum of the particle leaving the trajectory point [MeV].
   Float_t     MomentumY;      ///< The Y momentum of the particle leaving the trajectory point [MeV].
   Float_t     MomentumZ;      ///< The Z position of the particle leaving the trajectory point [MeV].

   TTruthTrajectoryPoint();
   TTruthTrajectoryPoint(const TTruthTrajectoryPoint & );
   virtual ~TTruthTrajectoryPoint();

   ClassDef(TTruthTrajectoryPoint,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif