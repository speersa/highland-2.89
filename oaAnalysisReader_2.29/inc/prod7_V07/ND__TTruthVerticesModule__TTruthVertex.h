//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jul 27 10:02:44 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710040-0003_c37su7dkqshx_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTruthVerticesModule__TTruthVertex_h
#define ND__TTruthVerticesModule__TTruthVertex_h
namespace ND {
namespace TTruthVerticesModule {
class TTruthVertex;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "TLorentzVector.h"
#include "Riostream.h"
#include <string>
#include <vector>

namespace ND {
namespace TTruthVerticesModule {
class TTruthVertex : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   int         ID;          //A number which uniquely identifies this vertex within the event.  This ID is the interface between the Truth Vertices module  and other eventAnalysis modules. Other modules should use this  number to reference trajectories.
   TLorentzVector Position;    //Position and time of the vertex
   string         Generator;    //The generator that created the vertex. eg: "genie:mean@free-spill"
   string         ReactionCode;    //The Reaction code according to the generator  For Genie this will be of the form:  "nu:14;tgt:1000260560;N:2112;proc:Weak[CC],QES;" For Neut it will be an integer, see definitions here: http://www.t2k.org/asg/xsec/niwgdocs/neut_xsecs/neutmodesC.h/view
   int            Subdetector;     //Subdetector which the vertex occurs in.
   double         Fiducial;        //The distance inside the local fiducial volume [mm].  Not currently set for any detector other than the P0D.
   int            NPrimaryTraj;    //The number of primary trajectories  (ie: the number of primary  particles exiting the interaction vertex).
   vector<int>    PrimaryTrajIDs;    //\brief ID numbers which uniquely identify the trajectories of the  primary particles of the vertex within the event.
   int            NeutrinoPDG;       //The PDG number of the incoming neutrino.  Set to 0 in the absence of a neutrino.
   TLorentzVector NeutrinoMomentum;    //The four-momentum of the incoming neutrino.  Set to (-999999.9, -999999.9, -999999.9, -999999.9) in the  absence of a neutrino.
   int            TargetPDG;           //The (extended for nuclei) PDG number of the target.  Set to 0 in the absence of a target.
   TLorentzVector TargetMomentum;      //The four-momentum of the target.  Set to (-999999.9, -999999.9, -999999.9, -999999.9) in the  absence of a target.

   TTruthVertex();
   TTruthVertex(const TTruthVertex & );
   virtual ~TTruthVertex();

   ClassDef(TTruthVertex,3); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
