//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Thu Nov 25 13:45:36 2021 by ROOT version 5.34/34)
//      from the StreamerInfo in file /t2k/izmaylov/T2K_ND280_ANALYSIS/ANALYSIS/oaAnalysisReader/p7_V03_oa_nt_beam_90400128-0055_5dkklck5zqqj_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DReconModule__TP0DVertex_h
#define ND__TP0DReconModule__TP0DVertex_h
namespace ND {
namespace TP0DReconModule {
class TP0DVertex;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include <vector>
#include "TLorentzVector.h"

namespace ND {
namespace TP0DReconModule {
class TP0DVertex : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    //
   short       Cycle;            //The cycle number, based on the first hit.
   vector<short> Vertices;         //Holds internal Ids of Vertices pertinent to this reconstructed vertex.
   vector<short> Particles;        //Holds internal Ids of Particles pertinent to this reconstructed vertex.
   vector<short> Tracks;           //Holds internal Ids of Tracks pertinent to this reconstructed vertex.
   vector<short> Showers;          //Holds internal Ids of Showers pertinent to this reconstructed vertex.
   vector<short> Clusters;         //Holds internal Ids of Clusters pertinent to this reconstructed vertex.
   vector<short> Nodes;            //Holds internal Ids of Nodes pertinent to this reconstructed vertex.
   vector<short> Hits;             //Holds internal Ids of Hits pertinent to this reconstructed vertex.
   short         NHits;            //A count of the Hits associated with this object.
   unsigned int  UniqueID;         //The Unique ID of the corresponding ND::TReconVertex, used for  global-subdetector matching.
   int           Status;           //The reported Status of the corresponding ND::TReconVertex.
   float         Quality;          //The reported reconstruction 'quality' of the corresponding  ND::TReconVertex.
   int           NDOF;             //The Number of Degrees of Freedom in the reconstruction of the
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of primary true trajectory IDs which contribute to the  ND::THits which are constituents of this vertex.
   vector<int>   Truth_TrajIDs;           //The vector of true trajectory IDs which contribute to the ND::THits which are constituents of this vertex.
   vector<short> Truth_HitCount;          //The number of THits that each truth trajectory contributed to.
   vector<float> Truth_ChargeShare;       //The weighted reconstructed charge deposited by each truth  trajectory.
   TLorentzVector Position;                //Position of the TVertexState of the corresponding ND::TReconVertex.
   TLorentzVector PosVariance;             //Variance on the position of the TVertexState of the corresponding  ND::TReconVertex.
   short          ValidDimensions;         //Bit flag demarkating valid dimensions for this vertex's position.
   float          Fiducial;                //The distance to the outside of the fiducial volume

   TP0DVertex();
   TP0DVertex(const TP0DVertex & );
   virtual ~TP0DVertex();

   ClassDef(TP0DVertex,5); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
