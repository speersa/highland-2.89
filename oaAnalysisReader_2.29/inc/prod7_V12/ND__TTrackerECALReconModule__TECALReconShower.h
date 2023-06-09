//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Apr  5 14:16:33 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80600124-0055_f72mofocwqdr_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTrackerECALReconModule__TECALReconShower_h
#define ND__TTrackerECALReconModule__TECALReconShower_h
namespace ND {
namespace TTrackerECALReconModule {
class TECALReconShower;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"

namespace ND {
namespace TTrackerECALReconModule {
class TECALReconShower : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   TVector3    ConeAngle;    //The shower opening angle.
   TVector3    Direction;    //The shower direction.
   double      EDeposit;     //The energy deposited in the shower
   TLorentzVector Position;     //The shower position.
   TLorentzVector PositionVar;    //The shower position variance.
   TLorentzVector BackPosition;    //The charge weighted position of the end of the shower

   TECALReconShower();
   TECALReconShower(const TECALReconShower & );
   virtual ~TECALReconShower();

   ClassDef(TECALReconShower,3); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
