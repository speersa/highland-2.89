#ifndef numuCCZeroPiUtils_h
#define numuCCZeroPiUtils_h

#include <map>
#include <vector>
#include <set>

#include "DataClassesCCZeroPi.hxx"
#include "numuCCZeroPiDetectorDefinition.hxx"
#include "CutUtils.hxx"

#include <TVector3.h>
#include "Units.hxx"

const Float_t mass_muon = 105.65837 * units::MeV;
const Float_t mass_neutron = 939.565 * units::MeV;
const Float_t mass_proton = 938.272 * units::MeV;

namespace numu_cczeropi_utils{
  /// enum for comparison
  enum CompareEnum{
    kFirst, 
    kSecond, 
    kUnassigned
  };
  
  // Methods for backward migration systematic:

  Float_t* GetFittedPos(Float_t* start, Float_t* end, double z);
  Float_t GetDeltaPos(Float_t* hit, Float_t* fit);
  Float_t GetDeltaPos2(Float_t* hit, Float_t* fit);

  /// ------ FV ------
  /// Check wether the track ends in BarrelEcal Volume
  bool TrackEndsInBarrelECal(const AnaTrackB& track);

  /// Check wether the track ends in SMRD Volume
  bool TrackEndsInSMRD(const AnaTrackB& track);

  /// Check wether the track ends in BarrelEcal Fiducial Volume
  bool TrackEndsInBarrelECalFV(const AnaTrackB& track);
  
  /// Check wether the track starts in BarrelEcal Fiducial Volume
  bool TrackStartsInBarrelECalFV(const AnaTrackB& track);
  
  /// Check wether the track ends in SMRD Fiducial Volume
  bool TrackEndsInSMRDFV(const AnaTrackB& track);
  
  /// Check wether the track starts in SMRD Fiducial Volume
  bool TrackStartsInSMRDFV(const AnaTrackB& track);
  
  /// Check wether the track ends in FGD1 Fiducial Volume  
  bool InFGDFV( const SubDetId::SubDetEnum det, const Float_t pos[3] );
  bool TrackEndsInFGD1FV(const AnaTrackB& track);
  bool TrackEndsInFGD2FV(const AnaTrackB& track);
   
  /// Check wether the track start in FGD1 Fiducial Volume  
  bool TrackStartsInFGD1FV(const AnaTrackB& track);
  bool TrackStartsInFGD2FV(const AnaTrackB& track);
  
  //Common vertex
  bool CommonVertexCut( const Float_t p1[4], const Float_t p2[4], Float_t _cutX , Float_t _cutY, Float_t _cutZ);
  
  /// Reconstructed neutrino energy using only the muon kinematics
  Float_t GetRecNuEnergy(const AnaTrackB& track, Float_t mom);
  Float_t GetRecNuEnergy(Float_t mumom, TVector3 mudir, TVector3 nudir, bool truenudir=false);
  Float_t ComputeRecNuEnergyCCQE(Float_t mumom, TVector3 mudir, TVector3 nudir, bool truenudir=false);

  /// Reconstructed neutrino energy using both muon and proton kinematics
  Float_t ComputeFinalStateEnergy(TVector3 mumom, TVector3 pmom);
  TVector3 ComputeFinalStateMom(TVector3 mumom, TVector3 pmom);
  Float_t ComputeFinalStateMassSquared(TVector3 mumom, TVector3 pmom);
  Float_t ComputeFinalStateCosTheta(TVector3 mumom, TVector3 pmom, TVector3 nudir, bool truenudir=false);
  Float_t ComputeRecNuEnergyTwoTracks(TVector3 mumom, TVector3 pmom, bool truenudir=false);	  
  Float_t GetRecNuEnergyTwoTracks(TVector3 mumom, TVector3 pmom, bool truenudir=false);

  /// Reconstructed Q2
  Float_t GetRecQ2(const AnaTrackB& track, Float_t mom);

  /// True Q2
  Float_t GetTrueQ2(const AnaTrackB& track, Float_t trueNuE);
  
  Float_t GetFGDTrackLength(AnaTrackB* track);

  /// Get direction assuming sline between start and end 
  Float_t* GetSLineDir(Float_t* start, Float_t* end);

  /// Get SMRD detector assuming only one can be present
  SubDetId::SubDetEnum GetSMRDDet(unsigned long Detector);
  
  /// Get TECal detector assuming only one can be present
  SubDetId::SubDetEnum GetTECalDet(unsigned long Detector);
  
  /// Get TECal detector for true track assuming only one is present
  void GetTECalDet(AnaTrueParticleB*, std::set<SubDetId::SubDetEnum>& det_set);
 
  /// Get TECal detector for true track assuming only one is present
  void GetSMRDDet(AnaTrueParticleB*, std::set<SubDetId::SubDetEnum>& det_set);
  
  /// Compare segments length 
  class CompareBasic : public std::binary_function<const AnaRecObjectC*, const AnaRecObjectC*, bool>{
  public:
    bool operator()(const AnaRecObjectC* lhs, const AnaRecObjectC* rhs) const{
      return (CompareLength(lhs, rhs) == numu_cczeropi_utils::kFirst);
    };
    virtual ~CompareBasic(){};
    virtual numu_cczeropi_utils::CompareEnum CompareLength(const AnaRecObjectC* lhs, const AnaRecObjectC* rhs) const = 0;
  };

  class CompareSmrdSegmentLength : CompareBasic{
  public:
    numu_cczeropi_utils::CompareEnum CompareLength(const AnaRecObjectC* lhs, const AnaRecObjectC* rhs) const;
  };
  
  class CompareECalSegmentLength : CompareBasic{
  public:
    numu_cczeropi_utils::CompareEnum CompareLength(const AnaRecObjectC* lhs, const AnaRecObjectC* rhs) const;
  };
  
  class CompareFgdSegmentLength : CompareBasic{
  public:
    numu_cczeropi_utils::CompareEnum CompareLength(const AnaRecObjectC* lhs, const AnaRecObjectC* rhs) const;
  };

   
  /// Comparator to sort FGD, non-TPC tracks
  class Compare_FGD_nonTPC_length : public std::binary_function<const AnaRecObjectC*, const AnaRecObjectC*, bool>{
  public:
    bool operator()(const AnaRecObjectC* lhs, const AnaRecObjectC* rhs) const;
  private:
    CompareSmrdSegmentLength  _cmpSMRD;
    CompareECalSegmentLength  _cmpECal;
    CompareFgdSegmentLength   _cmpFGD;
  };
  
  /// Get the position of the closest edge hit to a given point in Z
  /// The criteria of how the hits are stored is not very obvious (how to distinguish between X/Y/Z hits), 
  /// So for the moment just retrieve Z info since it is relevant for the analysis
  bool GetClosestHitPosInZ(AnaTrack* track, Float_t* pos, double& z_pos);
  
   
   /*
   * !!!! March 20, 2015: these functions will be migratated to HighlandAnalysisUtils.hxx as soon as the new highland2/psyche
   * framework is in place and the head version is usable 
   */ 
  
  /// Get particles given the true vertex: primary and secondary
  /// Required PDGs should be provided as a std::set
  /// A mode paramter is used to set whether to retrieve primary/secondary/all particles (mode = 0/1/2(anything else) respectively):
  //  default 2 -- i.e. all
  /// Particles are sorted in decreasing momentum  
  int GetParticlesFromVertex(const AnaTrueVertexB& vertex, AnaTrueParticleB* outTraj[], const std::set<int>& particlePDGs, 
      unsigned int mode = 2);
 
  /// Compare function for AnaTrueObject(s)
  bool CompareMomentum(const AnaTrueParticleB* t1, const AnaTrueParticleB* t2); 
  
  /*
   * !!!! March 20, 2015: these functions will be migratated to HighlandAnalysisUtils.hxx as soon as the new highland2/psyche
   * framework is in place and the head version is usable 
   */

  /// Functions used to inferred proton kinematics from muon kinematics under CCQE assumption. 
  /// Used for 2p2h analysis
  // Infer Proton Momentum from Muon kinematics
  Float_t InferProtonMomentum(Float_t muon_momentum, Float_t nu_energy);

  // Infer Proton CosTheta from Muon kinematics
  Float_t InferProtonAngle(Float_t muon_momentum, Float_t nu_energy);
 
  // Infer Proton Three Momentum Vector from Muon kinematics
  void InferProtonThreeMomentum(Float_t muon_momentum, Float_t muon_direction[3], Float_t nu_energy, Float_t* proton_vector);

  // Start Hadronic vertex probe variables added by SDolan 02/09/15:

  bool isMECSignalRegion(AnaTrackB*, AnaTrackB*, AnaVertexB* );
  bool isMECSidebandRegion(AnaTrackB*, AnaTrackB*, AnaVertexB* );

  Float_t getReconDPhiT(AnaTrackB*, AnaTrackB*, AnaVertexB* );
  Float_t getTrueDPhiT(AnaTrackB*, AnaTrackB*, AnaTrueVertexB* );

  Float_t getReconMRec(AnaTrackB*, AnaTrackB*, AnaVertexB* );
  Float_t getTrueMRec(AnaTrackB*, AnaTrackB*, AnaTrueVertexB* );

  
  class transversityTrue{
  public: 
    Float_t tgtmrec, dphiT, dpT, dalphaT;
    transversityTrue(AnaTrackB*, AnaTrackB*, AnaTrueVertexB*); 
  };
  
  class transversityReco{  
  public: 
    Float_t tgtmrec, dphiT, dpT, dalphaT;
    transversityReco(AnaTrackB*, AnaTrackB*, AnaVertexB*); 
  };

  class transversityTrueT{
  public: 
    Float_t tgtmrec, dphiT, dpT, dalphaT;
    transversityTrueT(const AnaTrueVertex&); 
  };
  
  Float_t get3x3PathLength(Float_t*);

  // End of hadronic vertex probe variables added by SDolan 02/09/15

  bool VetoCut(const AnaEventB& event, AnaTrackB& candidate);


//******************************************************************
//******************************************************************
//** ADDED LOTS OF NEW FUNCTIONS SHAMELESSLY STOLEN FROM NUISANCE **
//******************************************************************
//******************************************************************

// Copyright 2016 L. Pickering, P Stowell, R. Terri, C. Wilkinson, C. Wret

/*******************************************************************************
*    This file was part of NUISANCE.
*
*    NUISANCE is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    NUISANCE is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with NUISANCE.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

// IF YOU FIND A BUG IN THIS, PLEASE LET A NUISANCE-PERSON KNOW!

//NUISANCE: a neutrino cross-section generator tuning and comparison framework.
//P. Stowell, C. Wret, C. Wilkinson, L. Pickering, et. al., 2017 JINST 12 P01016, arXiv:1612.07393


  /// Hadronic mass reconstruction
  double Wrec(TLorentzVector pnu, TLorentzVector pmu);

  /// Hadronic mass true from initial state particles and muon; useful if the full
  /// FSI vectors aren't not saved and we for some reasons need W_true
  double Wtrue(TLorentzVector pnu, TLorentzVector pmu, TLorentzVector pnuc);


  /// Reconstruct Q2QE given just the maximum energy proton.
  double ProtonQ2QErec(double pE, double binding);


  /*
    CC1pi0 MiniBooNE
  */
  /// Reconstruct Enu from CCpi0 vectors and binding energy
  double EnuCC1pi0rec(TLorentzVector pnu, TLorentzVector pmu,
                      TLorentzVector ppi0 = TLorentzVector(0, 0, 0, 0));

  /// Reconstruct Q2 from CCpi0 vectors and binding energy
  double Q2CC1pi0rec(TLorentzVector pnu, TLorentzVector pmu,
                     TLorentzVector ppi0 = TLorentzVector(0, 0, 0, 0));


  /*
    CCQE MiniBooNE/MINERvA
  */
  /// Function to calculate the reconstructed Q^{2}_{QE}
  double Q2QErec(TLorentzVector pmu, double costh, double binding,
                 bool neutrino = true);

  /// Function returns the reconstructed E_{nu} values
  double EnuQErec(TLorentzVector pmu, double costh, double binding,
                  bool neutrino = true);

  //! Function to calculate the reconstructed Q^{2}_{QE}
  double Q2QErec(double pl, double costh, double binding,
           bool neutrino = true);

  //! Function returns the reconstructed E_{nu} values
  double EnuQErec(double pl, double costh, double binding,
      bool neutrino = true);

  /*
    CC1pi+ MiniBooNE
  */

  /// returns reconstructed Enu a la MiniBooNE CCpi+
  /// returns reconstructed Enu a la MiniBooNE CCpi+
  // Also for when not having pion info (so when we have a Michel tag in T2K)
  double EnuCC1piprec(TLorentzVector pnu, TLorentzVector pmu, TLorentzVector ppip,
                      bool pionInfo = true);

  /// returns reconstructed Enu assumming resonance interaction where intermediate
  /// resonance was a Delta
  double EnuCC1piprecDelta(TLorentzVector pnu, TLorentzVector pmu);

  /// returns reconstructed in a variety of flavours
  double Q2CC1piprec(TLorentzVector pnu, TLorentzVector pmu, TLorentzVector ppip,
                     int enuType = 0, bool pionInfo = true);

  /*
    T2K CC1pi+ on CH
  */
  double thq3pi_CC1pip_T2K(TLorentzVector pnu, TLorentzVector pmu,
                           TLorentzVector ppi);
  double q3_CC1pip_T2K(TLorentzVector pnu, TLorentzVector pmu,
                       TLorentzVector ppi);
  double WrecCC1pip_T2K_MB(TLorentzVector pnu, TLorentzVector pmu,
                           TLorentzVector ppip);
  double EnuCC1piprec_T2K_eMB(TLorentzVector pnu, TLorentzVector pmu,
                              TLorentzVector ppi);

  /*
    nucleon single pion
  */
  double MpPi(TLorentzVector pp, TLorentzVector ppi);

  // As defined in PhysRevC.95.065501
  // Using prescription from arXiv 1805.05486 
  Float_t Get_pn_reco_C(TVector3 NuP, TVector3 LeptonP, TVector3 HadronP);

  //For T2K inferred kinematics analyis - variables defined as on page 7 of T2K TN287v11 (and now arXiv 1802.05078)
  double ppInfK(TLorentzVector pmu, double costh, double binding, bool neutrino);
  TVector3 tppInfK(TLorentzVector pmu, double costh, double binding, bool neutrino);
  double cthpInfK(TLorentzVector pmu, double costh, double binding, bool neutrino);

  double CosThAdler(TLorentzVector Pnu, TLorentzVector Pmu, TLorentzVector Ppi, TLorentzVector Pprot);
  double PhiAdler(TLorentzVector Pnu, TLorentzVector Pmu, TLorentzVector Ppi, TLorentzVector Pprot);
 
}
#endif
