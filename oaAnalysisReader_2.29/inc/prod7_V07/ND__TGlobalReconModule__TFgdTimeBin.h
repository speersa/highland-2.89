//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:43 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TGlobalReconModule__TFgdTimeBin_h
#define ND__TGlobalReconModule__TFgdTimeBin_h
namespace ND {
namespace TGlobalReconModule {
class TFgdTimeBin;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TVector3.h"
#include "ND__TGlobalReconModule__TOutermostHits.h"
#include "Riostream.h"
#include <vector>
#include "TClonesArray.h"
#include "ND__TGlobalReconModule__TGlobalHit.h"

namespace ND {
namespace TGlobalReconModule {
class TFgdTimeBin : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      minTime;     //Bin start time.
   double      maxTime;     //Bin end time.
   int         nHits[2];    //Number of hits in FGD1 (nHits[0]), and 2 (nHits[1])
   double      rawChargeSum[2];    //Summed hit charge in FGD1 (rawChargeSum[0]), and 2 (rawChargeSum[1])
   float       chargePerLayer[2][30];    //\brief Summed hit charge for layer x in FGD1 (chargePerLayer[0][x]),  and 2 (chargePerLayer[1][x])
   TVector3    chargeWeightedPos[2];     //\brief Charge weighted average hit position in FGD1 chargeWeightedPos[0]) and 2 (chargeWeightedPos[1])
   ND::TGlobalReconModule::TOutermostHits FGD1OutermostHits;        //A named collection of the outermost hits in X,Y, and Z from FGD1
   ND::TGlobalReconModule::TOutermostHits FGD2OutermostHits;        //A named collection of the outermost hits in X,Y, and Z from FGD2
   vector<int>                            FGD1HitLayer;             //Vector to store the layer number of each hit in FGD1
   vector<float>                          FGD1HitPosition;          //Vector to store the X or Y position of each hit in FGD1
   vector<float>                          FGD1HitQ;                 //Vector to store the charge of each hit in FGD1
   vector<float>                          FGD1HitTrueE;             //Vector to store the true edeposit of each hit in FGD1
   vector<float>                          FGD1HitT;                 //Vector to store the time of each hit in FGD1
   vector<int>                            FGD1HitTrajID;            //Vector to store the ID of the Trajectory that created the hit in FGD1
   vector<int>                            FGD2HitLayer;             //Vector to store the layer number of each hit in FGD2
   vector<float>                          FGD2HitPosition;          //Vector to store the X or Y position of each hit in FGD2
   vector<float>                          FGD2HitQ;                 //Vector to store the charge of each hit in FGD2
   vector<float>                          FGD2HitTrueE;             //Vector to store the true edeposit of each hit in FGD2
   vector<float>                          FGD2HitT;                 //Vector to store the time of each hit in FGD2
   vector<int>                            FGD2HitTrajID;            //Vector to store the ID of the Trajectory that created the hit in FGD1
   int                                    NFGD1Unused;              //Number of hits unused in FGD1
   TClonesArray*                          FGD1Unused;               //The vector unused hits in FGD1
   int                                    NFGD2Unused;              //Number of hits unused in FGD2
   TClonesArray*                          FGD2Unused;               //The vector unused hits in FGD2
   int                                    g4ID;                     //The ID for the G4 trajectory that contributed most to this time bin.
   ND::TGlobalReconModule::TGlobalHit     hackFGDUnused;            //This is just here to fool TFile::MakeProject, not a real object.

   TFgdTimeBin();
   TFgdTimeBin(const TFgdTimeBin & );
   virtual ~TFgdTimeBin();

   ClassDef(TFgdTimeBin,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
