#ifndef HighlandKinematicsUtils_h
#define HighlandKinematicsUtils_h

#include "DataClasses.hxx"

/// This contains useful functions related to kinematics: both,  true and reco
/// info

namespace anaUtils{

  /// Calculate various kinematic variables given the ingredients: deal with
  /// arrays, assume one is careful with the proper inputs...

  
  /// Transferred energy: four-momentum of neutrino and lepton
  Float_t ComputeV(const Float_t* NuP4, const Float_t* LepP4); 
  
  /// Transferred four-momentum: four-momentum of neutrino and lepton
  Float_t ComputeQ2(const Float_t* NuP4, const Float_t* LepP4); 
  
  /// Bjorken scaling: four-momentum of neutrino and lepton
  Float_t ComputeX(const Float_t* NuP4, const Float_t* LepP4);
  
  /// Inelasticity: four momentum of neutrino and lepton
  Float_t ComputeY(const Float_t* NuP4, const Float_t* LepP4);
  
  /// Hadronic invariant mass: four-momentum of neutrino and lepton,  and stuck
  /// nucleon
  Float_t ComputeW(const Float_t* NuP4, const Float_t* LepP4, const Float_t* HitNucP4); 
  
  /// Utility: get kinematics from the truth vertex: four-momentums for, lepton
  /// and stuck nucleon
  bool RetrieveInitialKinematics(const AnaTrueVertex& vtx, Float_t* NuP4, Float_t* LepP4, Float_t* HitNucP4, const Int_t size);
  
  
  /// Calculate varios kinematic variables for the truth vertex
  /// Transferred energy
  Float_t ComputeV(const AnaTrueVertex&); 
  
  /// Transferred four-momentum
  Float_t ComputeQ2(const AnaTrueVertex&); 
  
  /// Bjorken scaling
  Float_t ComputeX(const AnaTrueVertex&);
  
  /// Inelasticity
  Float_t ComputeY(const AnaTrueVertex&);
  
  /// Hadronic invariant mass
  Float_t ComputeW(const AnaTrueVertex&);
  
  
};




#endif
