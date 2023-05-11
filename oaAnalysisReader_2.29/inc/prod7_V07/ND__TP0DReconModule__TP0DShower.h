//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:44 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DReconModule__TP0DShower_h
#define ND__TP0DReconModule__TP0DShower_h
namespace ND {
namespace TP0DReconModule {
class TP0DShower;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include <vector>
#include "TLorentzVector.h"
#include "TVector3.h"

namespace ND {
namespace TP0DReconModule {
class TP0DShower : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    //The name of the p0dRecon algorithm that created this object.
   short       Cycle;            //The cycle number, based on the first hit.
   vector<short> Vertices;         //Holds internal Ids of Vertices pertinent to this reconstructed shower.
   vector<short> Particles;        //Holds internal Ids of Particles pertinent to this reconstructed shower.
   vector<short> Tracks;           //Holds internal Ids of Tracks pertinent to this reconstructed shower.
   vector<short> Showers;          //Holds internal Ids of Showers pertinent to this reconstructed shower.
   vector<short> Clusters;         //Holds internal Ids of Clusters pertinent to this reconstructed shower.
   vector<short> Nodes;            //Holds internal Ids of Nodes pertinent to this reconstructed shower.
   vector<short> Hits;             //Holds internal Ids of Hits pertinent to this reconstructed shower.
   short         NHits;            //A count of the Hits associated with this object.
   unsigned int  UniqueID;         //The Unique ID of the corresponding ND::TReconShower, used for  global-subdetector matching.
   int           Status;           //The reported Status of the corresponding ND::TReconShower.
   float         Quality;          //The reported reconstruction 'quality' of the corresponding  ND::TReconShower.
   int           NDOF;             //The Number of Degrees of Freedom in the reconstruction of the corresponding ND::TReconShower.
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of primary true trajectory IDs which contribute to the  ND::THits which are constituents of this shower.
   vector<int>   Truth_TrajIDs;           //The vector of true trajectory IDs which contribute to the ND::THits which are constituents of this shower.
   vector<short> Truth_HitCount;          //The number of THits that each truth trajectory contributed to.
   vector<float> Truth_ChargeShare;       //The weighted reconstructed charge deposited by each truth trajectory.
   float         EDeposit;                //The total reconstructed energy deposit of the corresponding ND::TReconShower.
   float         SideDeposit;             //The deposited charge in the side bars.
   float         EndDeposit;              //The deposited charge in the end p0dules.
   TLorentzVector Position;                //Position of the TShowerState of the corresponding ND::TReconShower.
   TLorentzVector PosVariance;             //Variance on the position of the TShowerState of the corresponding  ND::TReconShower.
   short          ValidDimensions;         //Bit flag demarkating valid dimensions for this shower's position.
   TVector3       Direction;               //Direction of the TShowerState of the corresponding ND::TReconShower.
   TVector3       DirVariance;             //Variance on the TP0DShower::Direction of the TShowerState of the corresponding ND::TReconShower.
   float          Cone;                    //The opening angle of the TShowerState cone of the corresponding  TReconShower.
   float          Width;                   //The 'width' of the shower, the extent perpendicular to the direction.
   float          Length;                  //The RMS length of the shower, the extent parallel to the direction.

   TP0DShower();
   TP0DShower(const TP0DShower & );
   virtual ~TP0DShower();

   ClassDef(TP0DShower,6); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
