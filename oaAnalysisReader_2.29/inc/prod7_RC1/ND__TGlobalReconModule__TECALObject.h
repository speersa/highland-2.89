//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jan 20 12:54:43 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file test_ev_anal.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TECALObject_h
#define ND__TGlobalReconModule__TECALObject_h
namespace ND {
namespace TGlobalReconModule {
class TECALObject;
} // end of namespace.
} // end of namespace.

#include "ND__TSubBaseShowerObject.h"
#include "TVector3.h"

namespace ND {
namespace TGlobalReconModule {
class TECALObject : public ND::TSubBaseShowerObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      LLR_MIP_EM;    //
   double      LLR_MIP_Pion;    //
   double      LLR_EM_HIP;      //
   double      LLR_MIP_EM_LowMomentum;    //
   double      LLR_MIP_HIP_VACut;         //
   double      AverageHitTime;            //
   double      AverageZPosition;          //
   double      EMEnergyFit_Result;        //
   double      EMEnergyFit_Uncertainty;    //
   int         FilledAsType;               //
   double      PID_Circularity;            //
   double      PID_Angle;                  //
   double      PID_ShowerAngle;            //
   double      PID_Asymmetry;              //
   double      PID_TruncatedMaxRatio;      //
   double      PID_TransverseChargeRatio;    //
   double      PID_FrontBackRatio;           //
   double      Containment;                  //
   double      Thrust;                       //
   TVector3    ThrustOrigin;                 //
   TVector3    ThrustAxis;                   //
   int         InnerMostLayerHit;            //
   int         OuterMostLayerHit;            //
   TVector3    Width;                        //

   TECALObject();
   TECALObject(const TECALObject & );
   virtual ~TECALObject();

   ClassDef(TECALObject,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
