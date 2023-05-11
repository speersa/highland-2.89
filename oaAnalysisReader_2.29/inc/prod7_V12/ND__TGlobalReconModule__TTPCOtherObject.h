//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Apr  5 14:16:33 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80600124-0055_f72mofocwqdr_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TTPCOtherObject_h
#define ND__TGlobalReconModule__TTPCOtherObject_h
namespace ND {
namespace TGlobalReconModule {
class TTPCOtherObject;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "ND__TTrueParticle.h"

namespace ND {
namespace TGlobalReconModule {
class TTPCOtherObject : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      Charge;      //
   int         Detector;    //
   int         NHits;       //
   double      Chi2;        //
   double      EDeposit;    //
   TLorentzVector FrontPosition;    //The Front position of the object.
   TLorentzVector BackPosition;     //The Back position of the object.
   TVector3       FrontDirection;    //The Front direction of the object.
   TVector3       BackDirection;     //The Back direction of the object.
   double         Momentum;          //the momentum of the object
   ND::TTrueParticle TrueParticle;      //The true particle

   TTPCOtherObject();
   TTPCOtherObject(const TTPCOtherObject & );
   virtual ~TTPCOtherObject();

   ClassDef(TTPCOtherObject,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
