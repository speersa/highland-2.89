//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Apr  5 14:16:34 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80600124-0055_f72mofocwqdr_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DReconModule__TP0DAlgoRes_h
#define ND__TP0DReconModule__TP0DAlgoRes_h
namespace ND {
namespace TP0DReconModule {
class TP0DAlgoRes;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include <vector>

namespace ND {
namespace TP0DReconModule {
class TP0DAlgoRes : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    //
   short       Cycle;            //The cycle number, based on the first hit.
   vector<short> Vertices;         //Holds internal Ids of Vertices pertinent to this algorithm result.
   vector<short> Particles;        //Holds internal Ids of Particles pertinent to this algorithm result.
   vector<short> Tracks;           //Holds internal Ids of Tracks pertinent to this algorithm result.
   vector<short> Showers;          //Holds internal Ids of Showers pertinent to this algorithm result.
   vector<short> Clusters;         //Holds internal Ids of Clusters pertinent to this algorithm result.
   vector<short> Nodes;            //Holds internal Ids of Nodes pertinent to this algorithm result.
   vector<short> Hits;             //Holds internal Ids of Hits pertinent to this algorithm result.
   short         NHits;            //A count of the Hits associated with this object.
   unsigned int  UniqueID;         //UNUSED: A unique ID used for reconstruction objects.
   string        FullName;         //The name of the p0dRecon algorithm that corresponds to this
   vector<short> AlgoResults;      //Holds internal Ids of daughter algorithm results to this one.
   short         Parent;           //The internal Id of the parent algorithm result of this one.
   short         UsedHitCluster;    //The internal Id of the cluster of hits which were used in a
   short         UnusedHitCluster;    //The internal Id of the cluster of hits which were not used in a

   TP0DAlgoRes();
   TP0DAlgoRes(const TP0DAlgoRes & );
   virtual ~TP0DAlgoRes();

   ClassDef(TP0DAlgoRes,6); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
