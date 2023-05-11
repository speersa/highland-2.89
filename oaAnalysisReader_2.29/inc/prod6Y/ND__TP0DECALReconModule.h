//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Fri Jul 15 17:55:45 2022 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_90400072-0007_ok762udcurva_anal_000_magnet201011airrun4-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TP0DECALReconModule_h
#define ND__TP0DECALReconModule_h
namespace ND {
class TP0DECALReconModule;
} // end of namespace.

#include "ND__TAnalysisReconModuleBase.h"
#include "TClonesArray.h"
#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "Riostream.h"
#include <string>
#include <TString.h>

namespace ND {
class TP0DECALReconModule : public ND::TAnalysisReconModuleBase {

public:
// Nested classes forward declaration.
class TP0DECALReconTrack;
class TP0DECALReconShower;
class TP0DECALLayerCharge;

public:
// Nested classes declaration.
class TP0DECALLayerCharge : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   double      FirstTime;    ///< first time of hits in hit
   double      LastTime;     ///< last time of hits in hit
   double      Charge[6];    ///< summed charge in each of 6 layers; index 0 is the innermost layer
   TString     module_name;    ///< string dictating the module of the detector

   TP0DECALLayerCharge();
   TP0DECALLayerCharge(const TP0DECALLayerCharge & );
   virtual ~TP0DECALLayerCharge();

   ClassDef(TP0DECALLayerCharge,2); // Generated by MakeProject.
};
class TP0DECALReconShower : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   UInt_t      UniqueID;    ///< The object UniqueID which can be used to match this object to the Global Recon object
   TVector3    ConeAngle;    ///< The shower opening angle.
   TVector3    Direction;    ///< The shower direction.
   double      EDeposit;     ///< the energy deposited in the shower.
   int         NDOF;         ///< the number of degrees of freedom in the reconstruction.
   TLorentzVector Position;     ///< the shower starting position.
   double         Quality;      ///< the goodness of fit for the reconstruction.
   double         AMR;          ///< The Pid Variables         
   double         CWTrackWidth;    ///< The Pid Variables  
   double         Max_Ratio;       ///< The Pid Variables 
   double         NormChargeSD;    ///< The Pid Variables   
   double         PathChargeRatio;    ///< The Pid Variables 
   double         TrShval;            ///< The Pid Variables  
   int            NHits;              //
   TVector3       BenCWPosition;      ///<Ben CW position.
   int            StackNo;            ///< Stack of interaction
   int            TrueID;             ///< Truth ID
   string         Module;             ///< P0D ECal module in which shower was found.

   TP0DECALReconShower();
   TP0DECALReconShower(const TP0DECALReconShower & );
   virtual ~TP0DECALReconShower();

   ClassDef(TP0DECALReconShower,2); // Generated by MakeProject.
};
class TP0DECALReconTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   UInt_t      UniqueID;    //
   double      Curvature;    ///< The track curvature around the X axis.
   TVector3    Direction;    ///< The track direction.
   double      EDeposit;     ///< the energy deposited in the track.
   int         NDOF;         ///< the number of degrees of freedom in the reconstruction.
   TLorentzVector Position;     ///< the track starting position.
   double         Quality;      ///< the goodness of fit for the reconstruction.
   TVector3       Width;        ///< the width of the track.
   double         AMR;          ///< The Pid Variables
   double         CWTrackWidth;    ///< The Pid Variables
   double         Max_Ratio;       ///< The Pid Variables
   double         NormChargeSD;    ///< The Pid Variables
   double         PathChargeRatio;    ///< The Pid Variables
   double         TrShval;            ///< The Pid Variables
   int            NHits;              //
   TVector3       BenCWPosition;      ///<Ben CW position.
   int            StackNo;            ///< Stack of interaction
   string         Module;             ///< P0D ECal module in which track was found
   int            TrueID;             ///< Truth ID.
   int            TruePDG;            ///< PDG code of true particle.
   int            TrueParentID;       ///< ID of parent particle in truth.
   double         TrueHitPurity;      ///< True hit purity.
   double         TrueHitEfficiency;    ///< True hit efficiency.
   TLorentzVector TrueInitPos;          ///< Initial position in truth.
   TLorentzVector TrueFinalPos;         ///< Final position in truth.
   TLorentzVector TrueInitMom;          ///< Initial momentum in truth.

   TP0DECALReconTrack();
   TP0DECALReconTrack(const TP0DECALReconTrack & );
   virtual ~TP0DECALReconTrack();

   ClassDef(TP0DECALReconTrack,2); // Generated by MakeProject.
};

public:
// Data Members.
   Int_t       fNReconTracks;    ///< Number of objects in clones array.
   Int_t       fNReconShowers;    ///< Number of objects in clones array.
   Int_t       fNLayerCharge;     ///< Number of objects in clones array.
   TClonesArray* fReconTracks;      ///< TClonesArray of TP0DECALReconTrack Objects
   TClonesArray* fReconShowers;     ///< TClonesArray of TP0DECALReconShower Objects
   TClonesArray* fLayerCharge;      ///< TClonesArray of TP0DECALLayerCharge Objects

   TP0DECALReconModule();
   TP0DECALReconModule(const TP0DECALReconModule & );
   virtual ~TP0DECALReconModule();

   ClassDef(TP0DECALReconModule,3); // Generated by MakeProject.
};
} // namespace
#endif
