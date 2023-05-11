//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Nov 23 12:47:33 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod6/RQS/oa_nt_beam_80510000-0000_leokxyiuc2jb_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TTruthTrajectoriesModule_h
#define ND__TTruthTrajectoriesModule_h
namespace ND {
class TTruthTrajectoriesModule;
} // end of namespace.

#include "ND__TAnalysisTruthModuleBase.h"
#include "Riostream.h"
#include <set>
#include "TClonesArray.h"
#include "TObject.h"
#include <string>
#include "TLorentzVector.h"
#include <vector>
#include "ND__TTruthTrajectoriesModule.h"
#include "TVector3.h"

namespace ND {
class TTruthTrajectoriesModule : public ND::TAnalysisTruthModuleBase {

public:
// Nested classes forward declaration.
class TTruthTrajectory;
class TTruthTrajectoryPoint;

public:
// Nested classes declaration.
class TTruthTrajectoryPoint : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   Int_t       ProcessType;    //
   Float_t     PositionX;      //
   Float_t     PositionY;      //
   Float_t     PositionZ;      //
   Float_t     PositionT;      //
   Float_t     MomentumX;      //
   Float_t     MomentumY;      //
   Float_t     MomentumZ;      //

   TTruthTrajectoryPoint();
   TTruthTrajectoryPoint(const TTruthTrajectoryPoint & );
   virtual ~TTruthTrajectoryPoint();

   ClassDef(TTruthTrajectoryPoint,2); // Generated by MakeProject.
};
class TTruthTrajectory : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   Int_t       ID;          ///< Trajectory's ID number. Uniquely identifies this trajectory within the event. Used by other oaAnalysis modules to reference trajectories.
   Int_t       PDG;         ///< Particle PDG code
   string      Name;        ///< Particle name
   Int_t       Category;    ///< Classifier of the particle type
   TLorentzVector InitMomentum;    ///< The Initial momentum of the particle at creation [MeV].
   TLorentzVector InitPosition;    ///< Initial Position at which the particle was created [mm].
   TLorentzVector FinalPosition;    ///< Final Position at which the particle stopped or left the simulation [mm].
   Int_t          ParentID;         ///< Parent particle's Trajectory ID. If this is a primary trajectory, the ParentID = 0.
   Int_t          PrimaryID;        ///< ID of the primary particle at the top of this particle's parent chain. If this is a primary trajectory, then PrimaryID = ID.
   double         Mass;             ///< Mass of the particle [MeV].
   int            Charge;           ///< Charge in units of |e|/3. (e.g. an electron has charge -3)
   vector<ND::TTruthTrajectoriesModule::TTruthTrajectoryPoint> Points;           //
   vector<int>                                                 TraceSubdetectors;    //
   vector<bool>                                                TraceInActive;        //
   vector<TLorentzVector>                                      TraceEntrancePosition;    //
   vector<TLorentzVector>                                      TraceExitPosition;        //
   vector<TVector3>                                            TraceEntranceMomentum;    //
   vector<TVector3>                                            TraceExitMomentum;        //
   Int_t                                                       InitSubdetector;          //
   Int_t                                                       FinalSubdetector;         //
   Bool_t                                                      EnteredSubdetector[13];    ///< DEPRECATED - use TraceSubdetectors
   Bool_t                                                      ExitedSubdetector[13];     ///< DEPRECATED - use TraceSubdetectors
   TLorentzVector                                              EntrancePosition[13];      ///< DEPRECATED - use TraceEntrancePosition
   TLorentzVector                                              ExitPosition[13];          ///< DEPRECATED - use TraceEntrancePosition
   TVector3                                                    EntranceMomentum[13];      ///< DEPRECATED - use TraceEntrancePosition
   TVector3                                                    ExitMomentum[13];          ///< DEPRECATED - use TraceEntrancePosition

   TTruthTrajectory();
   TTruthTrajectory(const TTruthTrajectory & );
   virtual ~TTruthTrajectory();

   ClassDef(TTruthTrajectory,2); // Generated by MakeProject.
};

public:
// Data Members.
   UInt_t      fMaxNTrajectories;    ///< The maximum number of trajectories that can be saved from a single event. Initialised by the constructor.
   Double_t    fMinLength;           ///< Minimum Length of Trajectories that will be saved in mm. All primary particles will be saved regardless of this.
   Bool_t      fSaveOnlyP0DTrackerECALTrajectories;    ///< Whether to save all trajectories, or only those which intersect the P0D, Tracker or ECals.
   Bool_t      fSaveParentChain;                       ///< Whether saving a trajectory should also trigger the saving of all the trajectories in its parent chain.
   std::set<int> fSaveList;                              ///< List of the trajectory IDs which are to be saved from the current event.
   Int_t         fNTraj;                                 ///< [branch] Total number of trajectories saved from the event 
   Int_t         fNTrajLepton;                           ///< [branch] Number of Charged Lepton trajectories saved from the event
   Int_t         fNTrajBaryon;                           ///< [branch] Number of Charged Baryon Trajectories saved from the event
   Int_t         fNTrajMeson;                            ///< [branch] Number of Charged Meson Trajectories saved from the event
   Int_t         fNTrajPhoton;                           ///< [branch] Number of Photon Trajectories saved from the event
   Int_t         fNTrajOtherCharged;                     ///< [branch] Number of Other Charged Trajectories saved from the event
   Int_t         fNTrajOtherNeutral;                     ///< [branch] Number of Other Neutral Trajectories saved from the event
   Int_t         fNTrajOther;                            ///< [branch] Number of Any Other Trajectories saved from the event
   TClonesArray* fTrajectories;                          //

   TTruthTrajectoriesModule();
   TTruthTrajectoriesModule(const TTruthTrajectoriesModule & );
   virtual ~TTruthTrajectoriesModule();

   ClassDef(TTruthTrajectoriesModule,2); // Generated by MakeProject.
};
} // namespace
#endif
