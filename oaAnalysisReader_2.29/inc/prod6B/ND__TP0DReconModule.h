//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov  4 15:38:32 2016 by ROOT version 5.34/34)
//      from the StreamerInfo in file /hep/T2K/DataDir/valid/oa_nt_beam_90210042-0030_bbzjto7xz4zh_anal_000_prod6amagnet201011waterb-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DReconModule_h
#define ND__TP0DReconModule_h
namespace ND {
class TP0DReconModule;
} // end of namespace.

#include "ND__TAnalysisReconModuleBase.h"
#include "TClonesArray.h"
#include "Riostream.h"
#include <vector>
#include "TPRegexp.h"
#include <map>
#include "TObject.h"
#include <string>
#include "TLorentzVector.h"
#include "TVector3.h"
namespace std {} using namespace std;
namespace std {} using namespace std;

namespace ND {
class TP0DReconModule : public ND::TAnalysisReconModuleBase {

public:
// Nested classes forward declaration.
class TP0DAlgoRes;
class TP0DVertex;
class TP0DParticle;
class TP0DShower;
class TP0DTrack;
class TP0DNode;
class TP0DHit;
class TP0DCluster;

public:
// Nested classes declaration.
class TP0DCluster : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   short       Cycle;            ///< The cycle number, based on the first hit.
   vector<short> Vertices;         ///< A vector of vertices associated with this object.
   vector<short> Particles;        ///< A vector of particles associated with this object.
   vector<short> Tracks;           ///< A vector of tracks associated with this object.
   vector<short> Showers;          ///< A vector of showers associated with this object.
   vector<short> Clusters;         ///< A vector of clusters associated with this object.
   vector<short> Nodes;            ///< A vector of nodes associated with this object.
   vector<short> Hits;             ///< A vector of hits associated with this object.
   short         NHits;            ///< A count of the Hits associated with this object.
   UInt_t        UniqueID;         //Unique id for the object.
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of Primary Trajectory IDs.
   vector<int>   Truth_TrajIDs;           ///< The vector of Trajectory IDs
   vector<short> Truth_HitCount;          //The vector of hit counts.
   vector<float> Truth_ChargeShare;       //The vector of charge shares.
   short         NFiducialHits;           ///< The number of fiducial hits.
   float         EDeposit;                ///< The deposited charge for the shower.
   TLorentzVector Position;                ///< The start position of the object.
   TLorentzVector PosVariance;             ///< The position variance;
   short          ValidDimensions;         //The number of valid dimensions for the object.  
   float          Moments[9];              ///< Moments of the Cluster.(arraySize = 9)

   TP0DCluster();
   TP0DCluster(const TP0DCluster & );
   virtual ~TP0DCluster();

   ClassDef(TP0DCluster,8); // Generated by MakeProject.
};
class TP0DHit : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   UInt_t      GeomID;      ///< Geometry ID
   UInt_t      ChanID;      ///< Channel ID
   float       Charge;      ///< Hit charge without attenuation correction
   float       Time;        ///< Hit time as reported by hit->GetTime()

   TP0DHit();
   TP0DHit(const TP0DHit & );
   virtual ~TP0DHit();

   ClassDef(TP0DHit,2); // Generated by MakeProject.
};
class TP0DNode : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   vector<short> Hits;        ///< A vector of hits associated with this object.
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of Primary Trajectory IDs.
   vector<int>   Truth_TrajIDs;           ///< The vector of Trajectory IDs
   vector<short> Truth_HitCount;          //The vector of hit counts.
   vector<float> Truth_ChargeShare;       //The vector of charge shares.  
   float         EDeposit;                ///< The deposited charge for the node.
   TLorentzVector Position;                ///< The position of the track.
   TLorentzVector PosVariance;             //
   short          ValidDimensions;         //The number of valid dimensions for the object.
   TVector3       Direction;               ///< The direction of the track.
   TVector3       DirVariance;             //

   TP0DNode();
   TP0DNode(const TP0DNode & );
   virtual ~TP0DNode();

   ClassDef(TP0DNode,6); // Generated by MakeProject.
};
class TP0DTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   short       Cycle;            ///< The cycle number, based on the first hit.
   vector<short> Vertices;         ///< A vector of vertices associated with this object.
   vector<short> Particles;        ///< A vector of particles associated with this object.
   vector<short> Tracks;           ///< A vector of tracks associated with this object.
   vector<short> Showers;          ///< A vector of showers associated with this object.
   vector<short> Clusters;         ///< A vector of clusters associated with this object.
   vector<short> Nodes;            ///< A vector of nodes associated with this object.
   vector<short> Hits;             ///< A vector of hits associated with this object.
   short         NHits;            ///< A count of the Hits associated with this object.
   UInt_t        UniqueID;         //Unique id for the object.
   int           Status;           ///< The status for the fit.
   float         Quality;          ///< The quality of the fit.
   int           NDOF;             ///< The number of degrees of freedom.
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of Primary Trajectory IDs.
   vector<int>   Truth_TrajIDs;           ///< The vector of Trajectory IDs
   vector<short> Truth_HitCount;          //The vector of hit counts.
   vector<float> Truth_ChargeShare;       //The vector of charge shares. 
   float         EDeposit;                ///< The deposited charge for the track.
   float         SideDeposit;             ///< The deposited charge in the side bars.
   float         EndDeposit;              ///< The deposited charge in the end p0dules.
   TLorentzVector Position;                ///< The position of the track.
   TLorentzVector PosVariance;             //
   short          ValidDimensions;         //The number of valid dimensions for the object.
   TVector3       Direction;               ///< The direction of the track.
   TVector3       DirVariance;             //
   float          Length;                  ///< The length of the track in the P0D

   TP0DTrack();
   TP0DTrack(const TP0DTrack & );
   virtual ~TP0DTrack();

   ClassDef(TP0DTrack,7); // Generated by MakeProject.
};
class TP0DShower : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   short       Cycle;            ///< The cycle number, based on the first hit.
   vector<short> Vertices;         ///< A vector of vertices associated with this object.
   vector<short> Particles;        ///< A vector of particles associated with this object.
   vector<short> Tracks;           ///< A vector of tracks associated with this object.
   vector<short> Showers;          ///< A vector of showers associated with this object.
   vector<short> Clusters;         ///< A vector of clusters associated with this object.
   vector<short> Nodes;            ///< A vector of nodes associated with this object.
   vector<short> Hits;             ///< A vector of hits associated with this object.
   short         NHits;            ///< A count of the Hits associated with this object.
   UInt_t        UniqueID;         //The number of valid dimensions for the object
   int           Status;           ///< The status for the fit.
   float         Quality;          ///< The quality of the fit.
   int           NDOF;             ///< The number of degrees of freedom.
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of Primary Trajectory IDs.
   vector<int>   Truth_TrajIDs;           ///< The vector of Trajectory IDs
   vector<short> Truth_HitCount;          //The vector of hit counts.
   vector<float> Truth_ChargeShare;       //The vector of charge shares. 
   float         EDeposit;                ///< The deposited charge for the shower.
   float         SideDeposit;             ///< The deposited charge in the side bars.
   float         EndDeposit;              //
   TLorentzVector Position;                ///< The start position of the object.
   TLorentzVector PosVariance;             //
   short          ValidDimensions;         //The number of valid dimensions for the object.
   TVector3       Direction;               ///< The direction of the object.
   TVector3       DirVariance;             //
   float          Cone;                    ///< The opening angle of the cone.
   float          Width;                   ///< The width of the shower (perpendicular to the direction)
   float          Length;                  //

   TP0DShower();
   TP0DShower(const TP0DShower & );
   virtual ~TP0DShower();

   ClassDef(TP0DShower,6); // Generated by MakeProject.
};
class TP0DParticle : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   short       Cycle;            ///< The cycle number, based on the first hit.
   vector<short> Vertices;         ///< A vector of vertices associated with this object.
   vector<short> Particles;        ///< A vector of particles associated with this object.
   vector<short> Tracks;           ///< A vector of tracks associated with this object.
   vector<short> Showers;          ///< A vector of showers associated with this object.
   vector<short> Clusters;         ///< A vector of clusters associated with this object.
   vector<short> Nodes;            ///< A vector of nodes associated with this object.
   vector<short> Hits;             ///< A vector of hits associated with this object.
   short         NHits;            ///< A count of the Hits associated with this object.
   UInt_t        UniqueID;         //Unique id for the object. 
   int           Status;           ///< The status for the fit.
   float         Quality;          ///< The quality of the fit.
   int           NDOF;             ///< The number of degrees of freedom.
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of Primary Trajectory IDs.
   vector<int>   Truth_TrajIDs;           ///< The vector of Trajectory IDs
   vector<short> Truth_HitCount;          //The vector of hit counts.
   vector<float> Truth_ChargeShare;       //The vector of charge shares. 
   float         SideDeposit;             ///< The deposited charge in the side bars.
   float         EndDeposit;              ///< The deposited charge in the end p0dules. 
   TLorentzVector Position;                ///< The start position of the object.
   TLorentzVector PosVariance;             ///< The position variance;
   short          ValidDimensions;         //The number of valid dimensions for the object
   TVector3       Direction;               ///< The direction of the object.
   TVector3       DirVariance;             //
   float          Momentum;                ///< The momentum of the object.
   float          Charge;                  ///< The charge of the identified particle.
   vector<string> realPIDNames;            ///< Names for the stored PID variables based on TRealDatums
   vector<vector<float> > realPIDValues;           ///< Values for the stored PID variables based on TRealDatums
   vector<string>         integerPIDNames;         ///< Names for the stored PID variables based on TIntegerDatums
   vector<vector<short> > integerPIDValues;        ///< Values for the stored PID variables based on TIntegerDatums
   vector<short>          PID;                     ///< A vector of potential PIDs, sorted by weight
   vector<float>          PID_weight;              //

   TP0DParticle();
   TP0DParticle(const TP0DParticle & );
   virtual ~TP0DParticle();

   ClassDef(TP0DParticle,6); // Generated by MakeProject.
};
class TP0DVertex : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   short       Cycle;            ///< The cycle number, based on the first hit.
   vector<short> Vertices;         ///< A vector of vertices associated with this object.
   vector<short> Particles;        ///< A vector of particles associated with this object.
   vector<short> Tracks;           ///< A vector of tracks associated with this object.
   vector<short> Showers;          ///< A vector of showers associated with this object.
   vector<short> Clusters;         ///< A vector of clusters associated with this object.
   vector<short> Nodes;            ///< A vector of nodes associated with this object.
   vector<short> Hits;             ///< A vector of hits associated with this object.
   short         NHits;            ///< A count of the Hits associated with this object.
   UInt_t        UniqueID;         ///< Unique id for the object
   int           Status;           ///< The status for the fit.
   float         Quality;          ///< The quality of the fit.
   int           NDOF;             ///< The number of degrees of freedom.
   vector<int>   Truth_PrimaryTrajIDs;    //The vector of Primary Trajectory IDs. 
   vector<int>   Truth_TrajIDs;           ///< The vector of Trajectory IDs
   vector<short> Truth_HitCount;          //The vector of hit counts. 
   vector<float> Truth_ChargeShare;       //The vector of charge shares.
   TLorentzVector Position;                ///< The position of the vertex.
   TLorentzVector PosVariance;             ///< The position variance;
   short          ValidDimensions;         //The number of valid dimensions for the object.
   float          Fiducial;                //< The distance to the outside of the fiducial volume (negative if the vertex is outside).

   TP0DVertex();
   TP0DVertex(const TP0DVertex & );
   virtual ~TP0DVertex();

   ClassDef(TP0DVertex,5); // Generated by MakeProject.
};
class TP0DAlgoRes : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    ///< The name of the algorithm that created this object.
   short       Cycle;            ///< The cycle number, based on the first hit.
   vector<short> Vertices;         ///< A vector of vertices associated with this object.
   vector<short> Particles;        ///< A vector of particles associated with this object.
   vector<short> Tracks;           ///< A vector of tracks associated with this object.
   vector<short> Showers;          ///< A vector of showers associated with this object.
   vector<short> Clusters;         ///< A vector of clusters associated with this object.
   vector<short> Nodes;            ///< A vector of nodes associated with this object.
   vector<short> Hits;             ///< A vector of hits associated with this object.
   short         NHits;            ///< A count of the Hits associated with this object.
   UInt_t        UniqueID;         ///< Unique id for the object.
   string        FullName;         ///< The name of the algorithm that created this result.
   vector<short> AlgoResults;      ///< A vector of results beneath this result
   short         Parent;           ///< The ID of the parent algorithm result (-1 for highest result)
   short         UsedHitCluster;    ///< The ID of the cluster of used hits for this algo result
   short         UnusedHitCluster;    ///< The ID of the cluster of unused hits for this algo result

   TP0DAlgoRes();
   TP0DAlgoRes(const TP0DAlgoRes & );
   virtual ~TP0DAlgoRes();

   ClassDef(TP0DAlgoRes,6); // Generated by MakeProject.
};

public:
// Data Members.
   Short_t     fNAlgoResults;    ///<  The number of Algorithm Results
   Short_t     fNVertices;       ///<  The number of added vertices
   Short_t     fNParticles;      ///<  The number of particles
   Short_t     fNShowers;        ///<  The number of showers
   Short_t     fNTracks;         ///<  The number of tracks
   Short_t     fNNodes;          ///<  The number of track nodes
   Short_t     fNClusters;       ///<  The number of clusters
   Short_t     fNHits;           ///<  The number of hits that are saved
   TClonesArray* fAlgoResults;     ///<  The TP0DAlgoRes vector of Algorithm Results.
   TClonesArray* fVertices;        ///<  The TP0DVertex vector of vertices.
   TClonesArray* fParticles;       ///<  The TP0DParticle vector of particles.
   TClonesArray* fShowers;         ///<  The TP0DShower vector of showers.
   TClonesArray* fTracks;          ///<  The TP0DTrack vector of tracks.
   TClonesArray* fNodes;           ///<  The TP0DNode vector of nodes.
   TClonesArray* fHits;            ///<  The TP0DHit vector of hits.
   TClonesArray* fClusters;        ///<  The TP0DCluster vector of clusters
   vector<TPRegexp> fRejectAlgoResultList;    //
   std::map<UInt_t,short> fTempHitMap;              //

   TP0DReconModule();
   TP0DReconModule(const TP0DReconModule & );
   virtual ~TP0DReconModule();

   ClassDef(TP0DReconModule,6); // Generated by MakeProject.
};
} // namespace
#endif
