//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 18:05:56 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400000-0000_2sxl5m3goua7_anal_000_magnet201011airrun4-bsdv01_2.root
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
   int         ProcessType;    //The process type that caused the Monte Carlo to generate this  point.
   float       PositionX;      //The X position of the trajectory point [mm].
   float       PositionY;      //The Y position of the trajectory point [mm].
   float       PositionZ;      //The Z position of the trajectory point [mm].
   float       PositionT;      //The time of the trajectory point [ns].
   float       MomentumX;      //The X momentum of the particle leaving the trajectory point [MeV].
   float       MomentumY;      //The Y momentum of the particle leaving the trajectory point [MeV].
   float       MomentumZ;      //The Z position of the particle leaving the trajectory point [MeV].

   TTruthTrajectoryPoint();
   TTruthTrajectoryPoint(const TTruthTrajectoryPoint & );
   virtual ~TTruthTrajectoryPoint();

   ClassDef(TTruthTrajectoryPoint,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
