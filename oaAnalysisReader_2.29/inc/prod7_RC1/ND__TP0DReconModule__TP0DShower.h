//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jan 20 12:54:43 2017 by ROOT version 5.34/34)
//      from the StreamerInfo in file test_ev_anal.root
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
   string      AlgorithmName;    //
   short       Cycle;            ///< The cycle number, based on the first hit.
   vector<short> Vertices;         //
   vector<short> Particles;        //
   vector<short> Tracks;           //
   vector<short> Showers;          //
   vector<short> Clusters;         //
   vector<short> Nodes;            //
   vector<short> Hits;             //
   short         NHits;            ///< A count of the Hits associated with this object.
   UInt_t        UniqueID;         //
   int           Status;           //
   float         Quality;          //
   int           NDOF;             //
   vector<int>   Truth_PrimaryTrajIDs;    //
   vector<int>   Truth_TrajIDs;           //
   vector<short> Truth_HitCount;          //
   vector<float> Truth_ChargeShare;       //
   float         EDeposit;                //
   float         SideDeposit;             //
   float         EndDeposit;              //
   TLorentzVector Position;                //
   TLorentzVector PosVariance;             //
   short          ValidDimensions;         //
   TVector3       Direction;               //
   TVector3       DirVariance;             //
   float          Cone;                    //
   float          Width;                   //
   float          Length;                  //

   TP0DShower();
   TP0DShower(const TP0DShower & );
   virtual ~TP0DShower();

   ClassDef(TP0DShower,6); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
