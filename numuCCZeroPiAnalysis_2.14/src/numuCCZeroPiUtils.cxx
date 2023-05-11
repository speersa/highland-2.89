#include "numuCCZeroPiUtils.hxx"
#include <TVector3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "ConstituentsUtils.hxx"
#include "ND280HL2Utils.h"


//#define HAS_FLAT_TREE_DETCROSS_BUG

//**************************************************
numu_cczeropi_utils::CompareEnum numu_cczeropi_utils::CompareSmrdSegmentLength::CompareLength(const AnaRecObjectC* lhsC, 
    const AnaRecObjectC* rhsC) const{
  //**************************************************
  
  const AnaTrackB* lhs = static_cast<const AnaTrackB*>(lhsC);
  const AnaTrackB* rhs = static_cast<const AnaTrackB*>(rhsC);

  if (!lhs && !rhs)
    return numu_cczeropi_utils::kUnassigned;

  if(lhs && !rhs)
    return numu_cczeropi_utils::kFirst;

  if(!lhs && rhs)
    return numu_cczeropi_utils::kSecond;
  
  int nLhs = lhs->nSMRDSegments;
  int nRhs = rhs->nSMRDSegments;
  AnaSMRDParticleB* const* tLhs= lhs->SMRDSegments; 
  AnaSMRDParticleB* const* tRhs= rhs->SMRDSegments; 
 
  if (nLhs>0 && nRhs==0)
    return numu_cczeropi_utils::kFirst;
  else if(nLhs==0 && nRhs>0)
    return numu_cczeropi_utils::kSecond;
  else if (nLhs>0 && nRhs>0){
    
    Float_t Length1 = 0.;
    Float_t Length2 = 0.;
   
    for (int i = 0; i<nLhs; i++){
      if (!tLhs[i]) continue;
      Length1 += static_cast<const AnaSMRDParticle*>(tLhs[i])->Length;
    }
    
    for (int i = 0; i<nRhs; i++){
      if (!tRhs[i]) continue;
      Length2 += static_cast<const AnaSMRDParticle*>(tRhs[i])->Length;
    }
    
    if (Length1 > Length2) return numu_cczeropi_utils::kFirst;
    
    if (Length1 < Length2) return numu_cczeropi_utils::kSecond;
    
    return numu_cczeropi_utils::kUnassigned;
  }
  return numu_cczeropi_utils::kUnassigned;
 
}

//**************************************************
numu_cczeropi_utils::CompareEnum numu_cczeropi_utils::CompareECalSegmentLength::CompareLength(const AnaRecObjectC* lhsC, 
    const AnaRecObjectC* rhsC) const{
  //**************************************************
    
  const AnaTrackB* lhs = static_cast<const AnaTrackB*>(lhsC);
  const AnaTrackB* rhs = static_cast<const AnaTrackB*>(rhsC);
  
  if (!lhs && !rhs)
    return numu_cczeropi_utils::kUnassigned;

  if(lhs && !rhs)
    return numu_cczeropi_utils::kFirst;

  if(!lhs && rhs)
    return numu_cczeropi_utils::kSecond;
  
  int nLhs = lhs->nECALSegments;
  int nRhs = rhs->nECALSegments;
  AnaECALParticleB* const* tLhs= lhs->ECALSegments; 
  AnaECALParticleB* const* tRhs= rhs->ECALSegments; 
 
  if (nLhs>0 && nRhs==0)
    return numu_cczeropi_utils::kFirst;
  else if(nLhs==0 && nRhs>0)
    return numu_cczeropi_utils::kSecond;
  else if (nLhs>0 && nRhs>0){
    
    Float_t Length1 = 0.;
    Float_t Length2 = 0.;
   
    for (int i = 0; i<nLhs; i++){
      if (!tLhs[i]) continue;
      Length1 += static_cast<const AnaECALParticle*>(tLhs[i])->Length;
    }
    
    for (int i = 0; i<nRhs; i++){
      if (!tRhs[i]) continue;
      Length2 += static_cast<const AnaECALParticle*>(tRhs[i])->Length;
    }
    
    if (Length1 > Length2) return numu_cczeropi_utils::kFirst;
    
    if (Length1 < Length2) return numu_cczeropi_utils::kSecond;
    
    return numu_cczeropi_utils::kUnassigned;
  }
  return numu_cczeropi_utils::kUnassigned;
 
}

//**************************************************
numu_cczeropi_utils::CompareEnum numu_cczeropi_utils::CompareFgdSegmentLength::CompareLength(const AnaRecObjectC* lhsC, 
    const AnaRecObjectC* rhsC) const{
  //**************************************************
    
  const AnaTrackB* lhs = static_cast<const AnaTrackB*>(lhsC);
  const AnaTrackB* rhs = static_cast<const AnaTrackB*>(rhsC);
  
  if (!lhs && !rhs)
    return numu_cczeropi_utils::kUnassigned;

  if(lhs && !rhs)
    return numu_cczeropi_utils::kFirst;

  if(!lhs && rhs)
    return numu_cczeropi_utils::kSecond;
  
  int nLhs = lhs->nFGDSegments;
  int nRhs = rhs->nFGDSegments;
  AnaFGDParticleB* const* tLhs = lhs->FGDSegments; 
  AnaFGDParticleB* const* tRhs = rhs->FGDSegments; 
 
  if (nLhs>0 && nRhs==0)
    return numu_cczeropi_utils::kFirst;
  else if(nLhs==0 && nRhs>0)
    return numu_cczeropi_utils::kSecond;
  else if (nLhs>0 && nRhs>0){
    
    Float_t Length1 = 0.;
    Float_t Length2 = 0.;
   
    for (int i = 0; i<nLhs; i++){
      if (!tLhs[i]) continue;
      Length1 += static_cast<const AnaFGDParticle*>(tLhs[i])->Length;
    }
    
    for (int i = 0; i<nRhs; i++){
      if (!tRhs[i]) continue;
      Length2 += static_cast<const AnaFGDParticle*>(tRhs[i])->Length;
    }
    
    if (Length1 > Length2) return numu_cczeropi_utils::kFirst;
    
    if (Length1 < Length2) return numu_cczeropi_utils::kSecond;
    
    return numu_cczeropi_utils::kUnassigned;
  }
  return numu_cczeropi_utils::kUnassigned;
 
}

//**************************************************
bool numu_cczeropi_utils::Compare_FGD_nonTPC_length::operator()(const AnaRecObjectC* lhsC, const AnaRecObjectC* rhsC) const {
  //**************************************************
    
  const AnaTrackB* lhs = static_cast<const AnaTrackB*>(lhsC);
  const AnaTrackB* rhs = static_cast<const AnaTrackB*>(rhsC);
  
  if (!lhs && !rhs)
    return false;

  if(lhs && !rhs)
    return true;

  if(!lhs && rhs)
    return false;
  
  
  //SMRD constituents
  numu_cczeropi_utils::CompareEnum result =_cmpSMRD.CompareLength(lhs, rhs); 
  
  if (result == numu_cczeropi_utils::kFirst) return true;
  
  if (result == numu_cczeropi_utils::kSecond) return false;
    
  //ECal constituents
  result = _cmpECal.CompareLength(lhs, rhs);
  
  if (result == numu_cczeropi_utils::kFirst) return true;
  
  if (result == numu_cczeropi_utils::kSecond) return false;
   
  //FGD constituents
  result = _cmpFGD.CompareLength(lhs, rhs);
  
  return (result == numu_cczeropi_utils::kFirst); 
}

//--------------Starts/ends in FV detector

//**************************************************
bool numu_cczeropi_utils::TrackEndsInBarrelECal(const AnaTrackB& track) {
  //**************************************************

  //explicitely check that a track has ECal segment    
  if(!anaUtils::TrackUsesDet(track, SubDetId::kTECAL))
    return false;

  //double check
  if(track.nECALSegments==0)
    return false;

  if(anaUtils::InDetVolume(SubDetId::kTopTECAL,    track.PositionEnd))
    return true;

  if(anaUtils::InDetVolume(SubDetId::kBottomTECAL, track.PositionEnd))
    return true;

  if(anaUtils::InDetVolume(SubDetId::kLeftTECAL,   track.PositionEnd))
    return true;

  if(anaUtils::InDetVolume(SubDetId::kRightTECAL,  track.PositionEnd))
    return true;

  return false;
}

//**************************************************
bool numu_cczeropi_utils::TrackEndsInSMRD(const AnaTrackB& track) {
  //**************************************************

  //explicitely check that a track has ECal segment    
  if(!anaUtils::TrackUsesDet(track, SubDetId::kSMRD))
    return false;

  //double check
  if(track.nSMRDSegments==0)
    return false;

  if (anaUtils::InDetVolume(SubDetId::kTopSMRD,    track.PositionEnd))
    return true;

  if (anaUtils::InDetVolume(SubDetId::kBottomSMRD, track.PositionEnd))
    return true;

  if (anaUtils::InDetVolume(SubDetId::kLeftSMRD,   track.PositionEnd))
    return true;

  if (anaUtils::InDetVolume(SubDetId::kRightSMRD,  track.PositionEnd))
    return true;

  return false;
}

//**************************************************
bool numu_cczeropi_utils::TrackEndsInBarrelECalFV(const AnaTrackB& track){
  //**************************************************

  //explicitely check that a track has ECal segment    
  if(!anaUtils::TrackUsesDet(track, SubDetId::kTECAL))
    return false;

  //double check
  if(track.nECALSegments==0)
    return false;

  if(anaUtils::InFiducialVolume(SubDetId::kTopTECAL, track.PositionEnd,    numuCCZeroPiDetDef::FVdefminTECALTop,    numuCCZeroPiDetDef::FVdefmaxTECALTop))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kBottomTECAL, track.PositionEnd, numuCCZeroPiDetDef::FVdefminTECALBottom, numuCCZeroPiDetDef::FVdefmaxTECALBottom))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kLeftTECAL, track.PositionEnd,   numuCCZeroPiDetDef::FVdefminTECALLeft,   numuCCZeroPiDetDef::FVdefmaxTECALLeft))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kRightTECAL, track.PositionEnd,  numuCCZeroPiDetDef::FVdefminTECALRight,  numuCCZeroPiDetDef::FVdefmaxTECALRight))
    return true;

  return false;
}

//**************************************************
bool numu_cczeropi_utils::TrackStartsInBarrelECalFV(const AnaTrackB& track){
  //**************************************************

  //explicitely check that a track has ECal segment    
  if(!anaUtils::TrackUsesDet(track, SubDetId::kTECAL))
    return false;

  //double check
  if(track.nECALSegments==0)
    return false;

  if(anaUtils::InFiducialVolume(SubDetId::kTopTECAL, track.PositionStart,    numuCCZeroPiDetDef::FVdefminTECALTop,    numuCCZeroPiDetDef::FVdefmaxTECALTop))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kBottomTECAL, track.PositionStart, numuCCZeroPiDetDef::FVdefminTECALBottom, numuCCZeroPiDetDef::FVdefmaxTECALBottom))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kLeftTECAL, track.PositionStart,   numuCCZeroPiDetDef::FVdefminTECALLeft,   numuCCZeroPiDetDef::FVdefmaxTECALLeft))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kRightTECAL, track.PositionStart,  numuCCZeroPiDetDef::FVdefminTECALRight,  numuCCZeroPiDetDef::FVdefmaxTECALRight))
    return true;

  return false;
}

//**************************************************
bool numu_cczeropi_utils::TrackEndsInSMRDFV(const AnaTrackB& track) {
  //**************************************************

  //explicitely check that a track has ECal segment    
  if(!anaUtils::TrackUsesDet(track, SubDetId::kSMRD))
    return false;

  //double check
  if(track.nSMRDSegments==0)
    return false;


  if(anaUtils::InFiducialVolume(SubDetId::kTopSMRD, track.PositionEnd,    numuCCZeroPiDetDef::FVdefminSMRDTop,    numuCCZeroPiDetDef::FVdefmaxSMRDTop))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kBottomSMRD, track.PositionEnd, numuCCZeroPiDetDef::FVdefminSMRDBottom, numuCCZeroPiDetDef::FVdefmaxSMRDBottom))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kLeftSMRD, track.PositionEnd,   numuCCZeroPiDetDef::FVdefminSMRDLeft,   numuCCZeroPiDetDef::FVdefmaxSMRDLeft))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kRightSMRD, track.PositionEnd,  numuCCZeroPiDetDef::FVdefminSMRDRight,  numuCCZeroPiDetDef::FVdefmaxSMRDRight))
    return true;

  return false;
}

//**************************************************
bool numu_cczeropi_utils::TrackStartsInSMRDFV(const AnaTrackB& track) {
  //**************************************************

  //explicitely check that a track has ECal segment    
  if(!anaUtils::TrackUsesDet(track, SubDetId::kSMRD))
    return false;

  //double check
  if(track.nSMRDSegments==0)
    return false;


  if(anaUtils::InFiducialVolume(SubDetId::kTopSMRD, track.PositionStart,    numuCCZeroPiDetDef::FVdefminSMRDTop,    numuCCZeroPiDetDef::FVdefmaxSMRDTop))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kBottomSMRD, track.PositionStart, numuCCZeroPiDetDef::FVdefminSMRDBottom, numuCCZeroPiDetDef::FVdefmaxSMRDBottom))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kLeftSMRD, track.PositionStart,   numuCCZeroPiDetDef::FVdefminSMRDLeft,   numuCCZeroPiDetDef::FVdefmaxSMRDLeft))
    return true;

  if(anaUtils::InFiducialVolume(SubDetId::kRightSMRD, track.PositionStart,  numuCCZeroPiDetDef::FVdefminSMRDRight,  numuCCZeroPiDetDef::FVdefmaxSMRDRight))
    return true;

  return false;
}

//**************************************************
bool numu_cczeropi_utils::InFGDFV(const SubDetId::SubDetEnum det, const Float_t pos[4]) {
  //**************************************************
  
  bool fgd1 = anaUtils::InFiducialVolume(SubDetId::kFGD1, pos, numuCCZeroPiDetDef::FVdefminFGD1, numuCCZeroPiDetDef::FVdefmaxFGD1);
  bool fgd2 = anaUtils::InFiducialVolume(SubDetId::kFGD2, pos, numuCCZeroPiDetDef::FVdefminFGD2, numuCCZeroPiDetDef::FVdefmaxFGD2);

  
  if( det == SubDetId::kFGD1 ){
    return fgd1;
  }
  else if( det == SubDetId::kFGD2 ){
    return fgd2;
  }
  else if (det == SubDetId::kFGD){
    return (fgd1||fgd2);
  }
  return false;
}

//**************************************************
bool numu_cczeropi_utils::TrackEndsInFGD1FV(const AnaTrackB& track) {
  //**************************************************
  
  return anaUtils::InFiducialVolume(SubDetId::kFGD1, track.PositionEnd, numuCCZeroPiDetDef::FVdefminFGD1, numuCCZeroPiDetDef::FVdefmaxFGD1);
}

//**************************************************
bool numu_cczeropi_utils::TrackEndsInFGD2FV(const AnaTrackB& track) {
  //**************************************************

  return anaUtils::InFiducialVolume(SubDetId::kFGD2, track.PositionEnd, numuCCZeroPiDetDef::FVdefminFGD2, numuCCZeroPiDetDef::FVdefmaxFGD2);
}

//**************************************************
bool numu_cczeropi_utils::TrackStartsInFGD1FV(const AnaTrackB& track) {
  //**************************************************

  return anaUtils::InFiducialVolume(SubDetId::kFGD1, track.PositionStart, numuCCZeroPiDetDef::FVdefminFGD1, numuCCZeroPiDetDef::FVdefmaxFGD1);
}

//**************************************************
bool numu_cczeropi_utils::TrackStartsInFGD2FV(const AnaTrackB& track) {
  //**************************************************

  return anaUtils::InFiducialVolume(SubDetId::kFGD2, track.PositionStart, numuCCZeroPiDetDef::FVdefminFGD2, numuCCZeroPiDetDef::FVdefmaxFGD2);
}

bool numu_cczeropi_utils::CommonVertexCut( const Float_t p1[4], const Float_t p2[4], Float_t _cutX , Float_t _cutY, Float_t _cutZ){
  if (fabs(p1[0]-p2[0]) > _cutX ) return false; 
  if (fabs(p1[1]-p2[1]) > _cutY ) return false; 
  if (fabs(p1[2]-p2[2]) > _cutZ ) return false; 
  
  return true;
  
}

//********************************************************************
Float_t numu_cczeropi_utils::GetRecNuEnergy(const AnaTrackB& track, Float_t mom) {
  //********************************************************************
  // Get the reconstructed neutrino energy using only the kinematic of the muon

  Float_t muMass = 105.658367; //MeV (muon mass)
  Float_t eNuRec = anaUtils::ComputeRecNuEnergyCCQE(mom, muMass, track.DirectionStart[2]);  
  return eNuRec;
}

//********************************************************************
Float_t numu_cczeropi_utils::GetRecNuEnergy(Float_t mumom, TVector3 mudir, TVector3 nudir, bool truenudir) {
  //********************************************************************
  // Get the reconstructed neutrino energy using only the kinematic of the muon

  Float_t eNuRec = numu_cczeropi_utils::ComputeRecNuEnergyCCQE(mumom,mudir,nudir,truenudir); 
  return eNuRec;
}

//********************************************************************
Float_t numu_cczeropi_utils::ComputeRecNuEnergyCCQE(Float_t mumom, TVector3 mudir, TVector3 nudir, bool truenudir) {
  //********************************************************************

  // computes the reconstructed neutrino energy using only muon kinematics

  Float_t muMass = 105.658367; //MeV (muon mass)
  Float_t pMass = 938.27203;   //MeV (proton mass)
  Float_t nMass = 939.56536;   //MeV (neutron mass)
  Float_t V = 25.; //MeV (nuclear potential for carbon) 
  Float_t cosTheta = -2;

  // muon energy
  Float_t Emu = sqrt( pow(muMass,2) + pow(mumom,2) );

  // we use the true neutrino energy
  if (truenudir) {  
    //TVector3 muDir = mumom*(1/mumom.Mag());   // muon direction
    cosTheta = mudir * nudir;
  }
  // we assume the neutrino moves along the z axis  
  else cosTheta = mudir.Z();

  // reconstructed neutrino energy
  Float_t eNuRec = ( ( (pow(pMass,2) - pow(muMass,2)) + 2*Emu*(nMass-V) - pow(nMass-V,2) ) / (-Emu + (nMass-V) + (mumom * cosTheta)))/2; 

  return eNuRec;  
}


//********************************************************************
Float_t numu_cczeropi_utils::ComputeFinalStateEnergy(TVector3 mumom, TVector3 pmom) {
  //********************************************************************
  Float_t muMass = 105.658367; //MeV (muon mass)
  Float_t pMass = 938.27203; //MeV (proton mass)
  Float_t Emu = 0;
  Float_t Ep = 0;
  Float_t Ef = 0;

  // muon energy
  Emu = sqrt(pow(muMass,2) + pow(mumom.Mag(),2));
  // proton energy
  Ep = sqrt(pow(pMass,2) + pow(pmom.Mag(),2));  
  //final state energy
  Ef = Emu + Ep;

  return Ef;
}

//********************************************************************
TVector3 numu_cczeropi_utils::ComputeFinalStateMom(TVector3 mumom, TVector3 pmom) {
  //********************************************************************

  TVector3 finalStateMom; 
  //final state momentum
  finalStateMom = mumom + pmom;  

  return finalStateMom; 
}

//********************************************************************
Float_t numu_cczeropi_utils::ComputeFinalStateMassSquared(TVector3 mumom, TVector3 pmom) {
  //********************************************************************

  Float_t Mf2 = 0;
  TVector3 fmomvect = ComputeFinalStateMom(mumom,pmom);
  Float_t fmom = fmomvect.Mag();
  //final state mass squared
  Mf2 = pow(ComputeFinalStateEnergy(mumom,pmom),2) - pow(fmom,2);  

  return Mf2;
}

//********************************************************************
Float_t numu_cczeropi_utils::ComputeFinalStateCosTheta(TVector3 mumom, TVector3 pmom, TVector3 nudir, bool truenudir) {
  //********************************************************************

  Float_t cosThetaF = 0;  
  TVector3 fmomvect = ComputeFinalStateMom(mumom,pmom);
  Float_t fmom = fmomvect.Mag();
  //final state cosTheta
  if (truenudir) cosThetaF = (fmomvect * nudir)/fmom;    //we use the true neutrino energy
  else cosThetaF = fmomvect.Z()/fmomvect.Mag();    //we assume the neutrino moving along the z axis

  return cosThetaF;
}

//********************************************************************
Float_t numu_cczeropi_utils::ComputeRecNuEnergyTwoTracks(TVector3 mumom, TVector3 pmom, bool truenudir) {
  //********************************************************************
  // Get the reconstructed neutrino energy using the kinematic of both 
  // the muon and the proton

  if (truenudir){
    std::cout << "numu_cczeropi_utils::ComputeRecNuEnergyTwoTracks() cannot be currently used with truenudir=true !!!!";
    exit(1);
  }
  
  Float_t nMass = 939.56536; //MeV (neutron mass)
  Float_t V = 25.; //MeV (nuclear potential) 

  Float_t eNuRec = 0;

  // reconstructed neutrino energy
  TVector3 fMomVect = ComputeFinalStateMom(mumom,pmom);
  Float_t fMom = fMomVect.Mag();
  eNuRec = (ComputeFinalStateMassSquared(mumom,pmom) - pow(nMass,2) + 2*V*ComputeFinalStateEnergy(mumom,pmom) + pow(V,2)) / (2*(V + ComputeFinalStateEnergy(mumom,pmom) - fMom*ComputeFinalStateCosTheta(mumom,pmom,TVector3(0,0,0),truenudir)));

  return eNuRec;  
}

//********************************************************************
Float_t numu_cczeropi_utils::GetRecNuEnergyTwoTracks(TVector3 mumom, TVector3 pmom, bool truenudir) {
  //********************************************************************
  // Get the reconstructed neutrino energy using the kinematic of both 
  // the muon and the proton

  Float_t eNuRec = numu_cczeropi_utils::ComputeRecNuEnergyTwoTracks(mumom, pmom, truenudir);  
  return eNuRec;
}

//********************************************************************
Float_t numu_cczeropi_utils::GetRecQ2(const AnaTrackB& track, Float_t mom) {
  //********************************************************************
  // Get the reconstructed Q2 using reconstructed quantities (assuming the neutrino is moving along the z axis)

  Float_t muMass = 105.658367; //MeV (muon mass)
  Float_t Q2 = anaUtils::ComputeRecQ2CCQE(mom, muMass, track.DirectionStart[2]);  
  return Q2;  
}

//********************************************************************
Float_t numu_cczeropi_utils::GetTrueQ2(const AnaTrackB& track, Float_t trueNuE) {
  //********************************************************************
  // Get the reconstructed Q2 using true quantities (assuming the neutrino is moving along the z axis)

  Float_t muMass = 105.658367; //MeV (muon mass)
  Float_t trueQ2 = anaUtils::ComputeQ2(track.GetTrueParticle()->Momentum, muMass, 
      track.GetTrueParticle()->Direction[2], trueNuE);

  return trueQ2;  
}

//**************************************************
Float_t numu_cczeropi_utils::GetFGDTrackLength(AnaTrackB* track){
  //**************************************************

  if(track->nFGDSegments>0)
    return track->FGDSegments[0]->X;

  return 0.;

}


//********************************************************************
Float_t* numu_cczeropi_utils::GetSLineDir(Float_t* start, Float_t* end){
  //********************************************************************
  static Float_t uf[3] = {0, 0, 0};
  TVector3 u(end[0]-start[0], end[1]-start[1], end[2]-start[2]);
  if (u.Mag()!=0){
    u *= 1/(u.Mag());
    uf[0] = u.X();
    uf[1] = u.Y();
    uf[2] = u.Z();
  }
  return uf;

}


//**************************************************
SubDetId::SubDetEnum numu_cczeropi_utils::GetTECalDet(unsigned long Detector) {
  //**************************************************
  SubDetId::SubDetEnum det = SubDetId::kInvalid;
  if(SubDetId::GetDetectorUsed(Detector,      SubDetId::kTopTECAL))
    det = SubDetId::kTopTECAL;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kLeftTECAL))
    det = SubDetId::kLeftTECAL;                    
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kRightTECAL))
    det = SubDetId::kRightTECAL;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kBottomTECAL))
    det = SubDetId::kBottomTECAL;

  return det;
}



//**************************************************
SubDetId::SubDetEnum numu_cczeropi_utils::GetSMRDDet(unsigned long Detector) {
  //**************************************************
  SubDetId::SubDetEnum det = SubDetId::kInvalid;
  if(SubDetId::GetDetectorUsed(Detector,      SubDetId::kTopSMRD))
    det = SubDetId::kTopSMRD;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kLeftSMRD))
    det = SubDetId::kLeftSMRD;                    
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kRightSMRD))
    det = SubDetId::kRightSMRD;
  else if(SubDetId::GetDetectorUsed(Detector, SubDetId::kBottomSMRD))
    det = SubDetId::kBottomSMRD;

  return det;
}

//**************************************************
void numu_cczeropi_utils::GetTECalDet(AnaTrueParticleB* trueTrack, std::set<SubDetId::SubDetEnum>& det_set) {
  //**************************************************
  if (!trueTrack)
    return;


  for(Int_t idet=0;idet<trueTrack->nDetCrossings;idet++){
   
#ifdef  HAS_FLAT_TREE_DETCROSS_BUG
    
    if(((trueTrack->DetCrossings[idet]->Detector & (1<<SubDetId::kTECAL)) || (trueTrack->DetCrossings[idet]->Detector & (1<<SubDetId::kInvalid))) && trueTrack->DetCrossings[idet]->InActive) {// TEMP!!! to work with spoiled flat trees
      
      //safety check to ignore PECAL and SMRD
      if (trueTrack->DetCrossings[idet]->EntrancePosition[2]>DetDef::tecalRmax[2] || trueTrack->DetCrossings[idet]->EntrancePosition[2]<DetDef::tecalRmin[2])
        continue;
       
      //safety check to ignore PECAL and SMRD
      if (fabs(trueTrack->DetCrossings[idet]->EntrancePosition[1])>2010.)
        continue;
    
      //safety check to ignore PECAL and SMRD
      if (fabs(trueTrack->DetCrossings[idet]->EntrancePosition[0])>1830.)
        continue;      
     
#else
     if((trueTrack->DetCrossings[idet]->Detector & (1<<SubDetId::kTECAL)) && trueTrack->DetCrossings[idet]->InActive) {// TEMP!!! to work with spoiled flat trees

#endif 
      
     
      //use geometry info to split between sub-detectors
      if (trueTrack->DetCrossings[idet]->EntrancePosition[1]>1265.)
        det_set.insert(SubDetId::kTopTECAL);

      else if (trueTrack->DetCrossings[idet]->EntrancePosition[1]<-1265.)
        det_set.insert(SubDetId::kBottomTECAL);

      else if (trueTrack->DetCrossings[idet]->EntrancePosition[0]>1300.)
        det_set.insert(SubDetId::kLeftTECAL);

      else if (trueTrack->DetCrossings[idet]->EntrancePosition[0]<-1300.) 
        det_set.insert(SubDetId::kRightTECAL);

    }
  }

  return;
}



//**************************************************
void numu_cczeropi_utils::GetSMRDDet(AnaTrueParticleB* trueTrack, std::set<SubDetId::SubDetEnum>& det_set) {
//**************************************************

  if (!trueTrack)
    return;

  for(Int_t idet=0;idet<trueTrack->nDetCrossings;idet++){
    //InActive flag is not set for SMRD in oaAnalysis
 
#ifdef  HAS_FLAT_TREE_DETCROSS_BUG 
    if((trueTrack->DetCrossings[idet]->Detector & (1<<SubDetId::kSMRD)) || (trueTrack->DetCrossings[idet]->Detector & (1<<SubDetId::kInvalid))) {// TEMP!!! to work with spoiled flat trees
#else
    if(trueTrack->DetCrossings[idet]->Detector & (1<<SubDetId::kSMRD)) { 
#endif
      //use geometry info to split between sub-detectors
      if (trueTrack->DetCrossings[idet]->EntrancePosition[1]>2010.)
        det_set.insert(SubDetId::kTopSMRD);

      if (trueTrack->DetCrossings[idet]->EntrancePosition[1]<-2010.)
        det_set.insert(SubDetId::kBottomSMRD);

      if (trueTrack->DetCrossings[idet]->EntrancePosition[0]>1830.)
        det_set.insert(SubDetId::kLeftSMRD);

      if (trueTrack->DetCrossings[idet]->EntrancePosition[0]<-1830.) 
        det_set.insert(SubDetId::kRightSMRD);
    }
  }

  return;
}

//********************************************************************
int numu_cczeropi_utils::GetParticlesFromVertex(const AnaTrueVertexB& vertex, AnaTrueParticleB* outTraj[], 
    const std::set<int>& particlePDGs, unsigned int mode){
  //********************************************************************

  int count = 0; 

  // check whether any particle is provided
  if (particlePDGs.size() < 1) return count;

  std::set<int>::const_iterator it;

  //loop through trajectories associated with the vertex
  for (int i=0; i<vertex.nTrueParticles; i++){

    AnaTrueParticleB* trueTrack = vertex.TrueParticles[i];
    if(!trueTrack)                continue;

    switch (mode){
      // primary
      case 0:
        if (trueTrack->ParentPDG != 0) 
          continue; 
        break;
        // secondary
      case 1:
        if (trueTrack->ParentPDG == 0) 
          continue;
        break;
        // all
      default:
        break;
    }

    // PDG should be in the list
    bool found_pdg = false;
    for (it=particlePDGs.begin(); it!=particlePDGs.end(); it++){
      if (trueTrack->PDG == (*it)){
        found_pdg = true;
        break;
      }
    }

    if (!found_pdg) continue;

    outTraj[count++] = trueTrack;
  }
  
  //sort in decreasing momentum
  std::sort(&outTraj[0], &outTraj[count], numu_cczeropi_utils::CompareMomentum);
 
  return count;
}




//********************************************************************
bool numu_cczeropi_utils::CompareMomentum(const AnaTrueParticleB* t1, const AnaTrueParticleB* t2){
//********************************************************************

    // function to sort tracks in decreasing momentum order

    // set null pointer to be sorted the very last.
    Float_t m1 = -3e6;
    Float_t m2 = -3e6;
    if (t1 != NULL) m1 = t1->Momentum;
    if (t2 != NULL) m2 = t2->Momentum;

    // Also send inf to the end
    if (! TMath::Finite(m1)) m1 = -2e6;
    if (! TMath::Finite(m2)) m2 = -2e6;

    // Set nan to be -1e6 so they are sorted last. Leaving them as nan can cause
    // bad things to happen...
    if (m1 != m1) m1 = -1e6;
    if (m2 != m2) m2 = -1e6;

    return m1 > m2;
}


//********************************************************************
bool numu_cczeropi_utils::GetClosestHitPosInZ(AnaTrack* track, Float_t* pos, double& z_pos){
//********************************************************************
  if (!track) return false;
  
  // Get either the first or last hit
  z_pos =  fabs(track->UpstreamHits_Position[0].Z() - pos[2]) <
    fabs(track->DownstreamHits_Position[0].Z() - pos[2]) ?
    track->UpstreamHits_Position[0].Z() :
    track->DownstreamHits_Position[0].Z(); 

  return true;

}

//********************************************************************
 Float_t numu_cczeropi_utils::InferProtonMomentum(Float_t muon_momentum, Float_t nu_energy){
//********************************************************************

   Float_t muon_energy = sqrt(muon_momentum*muon_momentum + mass_muon*mass_muon);
   Float_t proton_energy = nu_energy + mass_proton - muon_energy; 
   Float_t proton_momentum = sqrt(proton_energy*proton_energy - mass_proton*mass_proton);
   
   return proton_momentum;
}

//********************************************************************
 Float_t numu_cczeropi_utils::InferProtonAngle(Float_t muon_momentum, Float_t nu_energy){
//********************************************************************

   Float_t muon_energy = sqrt(muon_momentum*muon_momentum + mass_muon*mass_muon);
   Float_t proton_energy = nu_energy + mass_proton - muon_energy; 
   Float_t proton_momentum = sqrt(proton_energy*proton_energy - mass_proton*mass_proton);
   Float_t proton_angle = (nu_energy*nu_energy + proton_momentum*proton_momentum - muon_momentum*muon_momentum)/(2*nu_energy*proton_momentum);

   return proton_angle;
}

//********************************************************************
 void numu_cczeropi_utils::InferProtonThreeMomentum(Float_t muon_momentum, Float_t muon_direction[3], Float_t nu_energy, 
     Float_t* proton_vector){
//********************************************************************
   proton_vector[0] = -(muon_direction[0] * muon_momentum);
   proton_vector[1] = -(muon_direction[1] * muon_momentum);
   proton_vector[2] = -(muon_direction[2] * muon_momentum) + nu_energy;
 }

//****************************************************************************************************
//****************************************************************************************************
//**************       Hadronic vertex probe variables added by SDolan 02/09/15      *****************
//****************************************************************************************************
//****************************************************************************************************


//****************************************************************************************************
bool numu_cczeropi_utils::isMECSignalRegion(AnaTrackB* ProtonCandidate, AnaTrackB* MuonCandidate, AnaVertexB* Vertex){
//**************************************************
  //cout << "Initialising MEC cut signal" << endl;
  NeutrinoUtils::IniCCQE();
 
  //Float_t  selp_costheta = ProtonCandidate->DirectionStart[2];
  //Float_t* selp_pos = ProtonCandidate->PositionStart;
  Float_t* selp_endpos = ProtonCandidate->PositionEnd;
  Float_t* selp_dir = ProtonCandidate->DirectionStart;
  //Float_t  selp_theta = acos(ProtonCandidate->DirectionStart[2]);  
  Float_t  selp_mom = ProtonCandidate->Momentum;
  Float_t  selp_Chi2 = -999.;//ProtonCandidate->Chi2;
  Float_t  selp_NDOF = -999.;//ProtonCandidate->NDOF;
  Int_t  selp_ntpcs = -999.;//ProtonCandidate->NTPCs;
  Int_t  selp_nfgds = -999.;//ProtonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Proton = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(ProtonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selp_tpc_nhits[3];//TPCSegment_Proton->NHits;
  Float_t  selp_tpc_charge[3];//TPCSegment_Proton->Charge;
  
  //double    selp_amom = ProtonCandidate->MomentumProton;

  ///Float_t  selmu_costheta = MuonCandidate->DirectionStart[2];
  //Float_t* selmu_pos = MuonCandidate->PositionStart;
  Float_t* selmu_endpos = MuonCandidate->PositionEnd;
  Float_t* selmu_dir = MuonCandidate->DirectionStart;
  //Float_t  selmu_theta = acos(MuonCandidate->DirectionStart[2]);  
  Float_t  selmu_mom = MuonCandidate->Momentum;
  Float_t  selmu_Chi2 = -999.;//MuonCandidate->Chi2;
  Float_t  selmu_NDOF = -999.;//MuonCandidate->NDOF;
  Int_t  selmu_ntpcs = -999.;//MuonCandidate->NTPCs;
  Int_t  selmu_nfgds = -999.;//MuonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Muon = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(MuonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selmu_tpc_nhits[3];//TPCSegment_Muon->NHits;
  Float_t  selmu_tpc_charge[3];//TPCSegment_Muon->Charge;
  //double    selmu_amom = MuonCandidate->MomentumMuon;
  
  Float_t* vertex_pos = Vertex->Position;
  
  //cout << "Starting MEC cut signal" << endl;

  
  ND280HL2Utils::SetNeutrinoRec(vertex_pos);
  //cout << "Set Nu Rec" << endl;

  const Int_t nmurec = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fMuonRec,   NeutrinoTools::MuonMass(),   selmu_dir, selmu_mom, vertex_pos, selmu_endpos, selmu_Chi2, selmu_NDOF, selmu_ntpcs, selmu_nfgds, selmu_tpc_nhits, selmu_tpc_charge);
  //cout << "Set mu Rec" << endl;

  
  NeutrinoUtils::SetMuonNRec(nmurec);
  //cout << "Set mun Rec" << endl;

  const Int_t nprec  = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fProtonRec, NeutrinoTools::ProtonMass(), selp_dir,  selp_mom,  vertex_pos, selp_endpos,  selp_Chi2,  selp_NDOF,  selp_ntpcs,  selp_nfgds,  selp_tpc_nhits,  selp_tpc_charge);
  //cout << "Set p Rec" << endl;
  
  NeutrinoUtils::SetProtonNRec(nprec);
  //cout << "Set pn Rec" << endl;
  
  NeutrinoUtils::SetDeltaPt();
  NeutrinoUtils::SetReconTgtMass();
  
  double dphiT = *(NeutrinoUtils::fDeltaRecPhi_t);
  double tgtmrec = *(NeutrinoUtils::fReconRecTgtMass);
  
  //cout << "DeltaPhiT is: " << *(NeutrinoUtils::fDeltaRecPhi_t) << endl;
  //cout << "ReconTargetMass is: " << *(NeutrinoUtils::fReconRecTgtMass) << endl;
  
  double aCut = 0.0;
  double bCut = 3.16;
  double cCut = -1.56;
  
  
  if(dphiT > (aCut*dphiT*tgtmrec) + (bCut*tgtmrec) + cCut) return true;
  else return false;
  
}

//**************************************************
bool numu_cczeropi_utils::isMECSidebandRegion(AnaTrackB* ProtonCandidate, AnaTrackB* MuonCandidate, AnaVertexB* Vertex){
//**************************************************
  NeutrinoUtils::IniCCQE();
 
  //Float_t  selp_costheta = ProtonCandidate->DirectionStart[2];
  ///Float_t* selp_pos = ProtonCandidate->PositionStart;
  Float_t* selp_endpos = ProtonCandidate->PositionEnd;
  Float_t* selp_dir = ProtonCandidate->DirectionStart;
  //Float_t  selp_theta = acos(ProtonCandidate->DirectionStart[2]);  
  Float_t  selp_mom = ProtonCandidate->Momentum;
  Float_t  selp_Chi2 = -999.;//ProtonCandidate->Chi2;
  Float_t  selp_NDOF = -999.;//ProtonCandidate->NDOF;
  Int_t  selp_ntpcs = -999.;//ProtonCandidate->NTPCs;
  Int_t  selp_nfgds = -999.;//ProtonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Proton = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(ProtonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selp_tpc_nhits[3];//TPCSegment_Proton->NHits;
  Float_t  selp_tpc_charge[3];//TPCSegment_Proton->Charge;
  
  //double    selp_amom = ProtonCandidate->MomentumProton;

  //Float_t  selmu_costheta = MuonCandidate->DirectionStart[2];
  //Float_t* selmu_pos = MuonCandidate->PositionStart;
  Float_t* selmu_endpos = MuonCandidate->PositionEnd;
  Float_t* selmu_dir = MuonCandidate->DirectionStart;
  //Float_t  selmu_theta = acos(MuonCandidate->DirectionStart[2]);  
  Float_t  selmu_mom = MuonCandidate->Momentum;
  Float_t  selmu_Chi2 = -999.;//MuonCandidate->Chi2;
  Float_t  selmu_NDOF = -999.;//MuonCandidate->NDOF;
  Int_t  selmu_ntpcs = -999.;//MuonCandidate->NTPCs;
  Int_t  selmu_nfgds = -999.;//MuonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Muon = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(MuonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selmu_tpc_nhits[3];//TPCSegment_Muon->NHits;
  Float_t  selmu_tpc_charge[3];//TPCSegment_Muon->Charge;
  //double    selmu_amom = MuonCandidate->MomentumMuon;
  
  Float_t* vertex_pos = Vertex->Position;
  
  //cout << "Starting MEC cut signal" << endl;

  
  ND280HL2Utils::SetNeutrinoRec(vertex_pos);
  //cout << "Set Nu Rec" << endl;

  const Int_t nmurec = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fMuonRec,   NeutrinoTools::MuonMass(),   selmu_dir, selmu_mom, vertex_pos, selmu_endpos, selmu_Chi2, selmu_NDOF, selmu_ntpcs, selmu_nfgds, selmu_tpc_nhits, selmu_tpc_charge);
  //cout << "Set mu Rec" << endl;

  
  NeutrinoUtils::SetMuonNRec(nmurec);
  //cout << "Set mun Rec" << endl;

  const Int_t nprec  = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fProtonRec, NeutrinoTools::ProtonMass(), selp_dir,  selp_mom,  vertex_pos, selp_endpos,  selp_Chi2,  selp_NDOF,  selp_ntpcs,  selp_nfgds,  selp_tpc_nhits,  selp_tpc_charge);
  //cout << "Set p Rec" << endl;
  
  NeutrinoUtils::SetProtonNRec(nprec);
  //cout << "Set pn Rec" << endl;
  
  NeutrinoUtils::SetDeltaPt();
  NeutrinoUtils::SetReconTgtMass();
  
  double dphiT = *(NeutrinoUtils::fDeltaRecPhi_t);
  double tgtmrec = *(NeutrinoUtils::fReconRecTgtMass);
  
  //cout << "DeltaPhiT is: " << *(NeutrinoUtils::fDeltaRecPhi_t) << endl;
  //cout << "ReconTargetMass is: " << *(NeutrinoUtils::fReconRecTgtMass) << endl;
  
  double aCut = 0.0;
  double bCut = 3.16;
  double cCut = -1.56;
//  double resMtgtSideBandCut = 0.75;
  double ccqeDeltaPhitSideBandCut = 0.8;
  double ccqeMtgtMaxSideBandCut = 1.2;
 // double ccqeMtgtMinSideBandCut = resMtgtSideBandCut;
  
  if((tgtmrec < ccqeMtgtMaxSideBandCut) && (dphiT < ccqeDeltaPhitSideBandCut) && (dphiT < (aCut*tgtmrec*tgtmrec) + bCut*tgtmrec + cCut)) return true;
  else return false;
  
}


//**************************************************
Float_t numu_cczeropi_utils::getReconDPhiT(AnaTrackB* ProtonCandidate, AnaTrackB* MuonCandidate, AnaVertexB* Vertex){
//**************************************************
  NeutrinoUtils::IniCCQE();
 
  //Float_t  selp_costheta = ProtonCandidate->DirectionStart[2];
  //Float_t* selp_pos = ProtonCandidate->PositionStart;
  Float_t* selp_endpos = ProtonCandidate->PositionEnd;
  Float_t* selp_dir = ProtonCandidate->DirectionStart;
  //Float_t  selp_theta = acos(ProtonCandidate->DirectionStart[2]);  
  Float_t  selp_mom = ProtonCandidate->Momentum;
  Float_t  selp_Chi2 = -999.;//ProtonCandidate->Chi2;
  Float_t  selp_NDOF = -999.;//ProtonCandidate->NDOF;
  Int_t  selp_ntpcs = -999.;//ProtonCandidate->NTPCs;
  Int_t  selp_nfgds = -999.;//ProtonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Proton = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(ProtonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selp_tpc_nhits[3];//TPCSegment_Proton->NHits;
  Float_t  selp_tpc_charge[3];//TPCSegment_Proton->Charge;
  
  //double    selp_amom = ProtonCandidate->MomentumProton;

 // Float_t  selmu_costheta = MuonCandidate->DirectionStart[2];
 // Float_t* selmu_pos = MuonCandidate->PositionStart;
  Float_t* selmu_endpos = MuonCandidate->PositionEnd;
  Float_t* selmu_dir = MuonCandidate->DirectionStart;
 // Float_t  selmu_theta = acos(MuonCandidate->DirectionStart[2]);  
  Float_t  selmu_mom = MuonCandidate->Momentum;
  Float_t  selmu_Chi2 = -999.;//MuonCandidate->Chi2;
  Float_t  selmu_NDOF = -999.;//MuonCandidate->NDOF;
  Int_t  selmu_ntpcs = -999.;//MuonCandidate->NTPCs;
  Int_t  selmu_nfgds = -999.;//MuonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Muon = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(MuonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selmu_tpc_nhits[3];//TPCSegment_Muon->NHits;
  Float_t  selmu_tpc_charge[3];//TPCSegment_Muon->Charge;
  //double    selmu_amom = MuonCandidate->MomentumMuon;
  
  Float_t* vertex_pos = Vertex->Position;
  
  //cout << "Starting MEC cut signal" << endl;

  
  ND280HL2Utils::SetNeutrinoRec(vertex_pos);
  //cout << "Set Nu Rec" << endl;

  const Int_t nmurec = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fMuonRec,   NeutrinoTools::MuonMass(),   selmu_dir, selmu_mom, vertex_pos, selmu_endpos, selmu_Chi2, selmu_NDOF, selmu_ntpcs, selmu_nfgds, selmu_tpc_nhits, selmu_tpc_charge);
  //cout << "Set mu Rec" << endl;

  
  NeutrinoUtils::SetMuonNRec(nmurec);
  //cout << "Set mun Rec" << endl;

  const Int_t nprec  = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fProtonRec, NeutrinoTools::ProtonMass(), selp_dir,  selp_mom,  vertex_pos, selp_endpos,  selp_Chi2,  selp_NDOF,  selp_ntpcs,  selp_nfgds,  selp_tpc_nhits,  selp_tpc_charge);
  //cout << "Set p Rec" << endl;
  
  NeutrinoUtils::SetProtonNRec(nprec);
  //cout << "Set pn Rec" << endl;
  
  NeutrinoUtils::SetDeltaPt();
  
  Float_t dphiT = *(NeutrinoUtils::fDeltaRecPhi_t);

  //cout << "Recon dphiT is: " << dphiT << endl;

  return dphiT;
}

//**************************************************
Float_t numu_cczeropi_utils::getTrueDPhiT(AnaTrackB* ProtonCandidate, AnaTrackB* MuonCandidate, AnaTrueVertexB* Vertex){
//**************************************************
  NeutrinoUtils::IniCCQE();
 
  Float_t* selp_truedir = ProtonCandidate->GetTrueParticle()->Direction;
  Float_t  selp_truemom = ProtonCandidate->GetTrueParticle()->Momentum;
  Float_t  selp_pdg = ProtonCandidate->GetTrueParticle()->PDG;

  Float_t* selmu_truedir = MuonCandidate->GetTrueParticle()->Direction;
  Float_t  selmu_truemom = MuonCandidate->GetTrueParticle()->Momentum;
  Float_t  selmu_pdg = MuonCandidate->GetTrueParticle()->PDG;

  AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(Vertex);

  Float_t* nu_truedir = vtx->NuDir; 
  Float_t  nu_trueE = 600.00; 

  //cout << "Some true vars: " << endl;
  //cout << selp_truedir[0] << endl << selp_truemom << endl << selp_pdg << endl << selmu_truedir[0] << endl << selmu_truemom << endl << selmu_pdg << endl << nu_truedir[0] << endl;

  ND280HL2Utils::SetNeutrinoSim(nu_truedir, nu_trueE);

  const Int_t nmusim = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fMuonSim,   NeutrinoTools::MuonMass(),   selmu_truedir, selmu_truemom, selmu_pdg);
  NeutrinoUtils::SetMuonNSim(nmusim);

  //proton: truep is the one out of nucleus
  const Int_t npsim  = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fProtonSim, NeutrinoTools::ProtonMass(), selp_truedir,   selp_truemom,   selp_pdg);

  NeutrinoUtils::SetProtonNSim(npsim);

  NeutrinoUtils::SetDeltaPt();
  
  Float_t dphiT = *(NeutrinoUtils::fDeltaSimPhi_t);

  //cout << "True dphiT is: " << dphiT << endl;

  return dphiT;

}

//**************************************************
Float_t numu_cczeropi_utils::getReconMRec(AnaTrackB* ProtonCandidate, AnaTrackB* MuonCandidate, AnaVertexB* Vertex){
//**************************************************
  NeutrinoUtils::IniCCQE();
 
  //Float_t  selp_costheta = ProtonCandidate->DirectionStart[2];
  //Float_t* selp_pos = ProtonCandidate->PositionStart;
  Float_t* selp_endpos = ProtonCandidate->PositionEnd;
  Float_t* selp_dir = ProtonCandidate->DirectionStart;
  //Float_t  selp_theta = acos(ProtonCandidate->DirectionStart[2]);  
  Float_t  selp_mom = ProtonCandidate->Momentum;
  Float_t  selp_Chi2 = -999.;//ProtonCandidate->Chi2;
  Float_t  selp_NDOF = -999.;//ProtonCandidate->NDOF;
  Int_t  selp_ntpcs = -999.;//ProtonCandidate->NTPCs;
  Int_t  selp_nfgds = -999.;//ProtonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Proton = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(ProtonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selp_tpc_nhits[3];//TPCSegment_Proton->NHits;
  Float_t  selp_tpc_charge[3];//TPCSegment_Proton->Charge;
  
  //double    selp_amom = ProtonCandidate->MomentumProton;

  //Float_t  selmu_costheta = MuonCandidate->DirectionStart[2];
  //Float_t* selmu_pos = MuonCandidate->PositionStart;
  Float_t* selmu_endpos = MuonCandidate->PositionEnd;
  Float_t* selmu_dir = MuonCandidate->DirectionStart;
  //Float_t  selmu_theta = acos(MuonCandidate->DirectionStart[2]);  
  Float_t  selmu_mom = MuonCandidate->Momentum;
  Float_t  selmu_Chi2 = -999.;//MuonCandidate->Chi2;
  Float_t  selmu_NDOF = -999.;//MuonCandidate->NDOF;
  Int_t  selmu_ntpcs = -999.;//MuonCandidate->NTPCs;
  Int_t  selmu_nfgds = -999.;//MuonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Muon = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(MuonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selmu_tpc_nhits[3];//TPCSegment_Muon->NHits;
  Float_t  selmu_tpc_charge[3];//TPCSegment_Muon->Charge;
  //double    selmu_amom = MuonCandidate->MomentumMuon;
  
  Float_t* vertex_pos = Vertex->Position;
  
  //cout << "Starting MEC cut signal" << endl;

  
  ND280HL2Utils::SetNeutrinoRec(vertex_pos);
  //cout << "Set Nu Rec" << endl;

  const Int_t nmurec = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fMuonRec,   NeutrinoTools::MuonMass(),   selmu_dir, selmu_mom, vertex_pos, selmu_endpos, selmu_Chi2, selmu_NDOF, selmu_ntpcs, selmu_nfgds, selmu_tpc_nhits, selmu_tpc_charge);
  //cout << "Set mu Rec" << endl;

  
  NeutrinoUtils::SetMuonNRec(nmurec);
  //cout << "Set mun Rec" << endl;

  const Int_t nprec  = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fProtonRec, NeutrinoTools::ProtonMass(), selp_dir,  selp_mom,  vertex_pos, selp_endpos,  selp_Chi2,  selp_NDOF,  selp_ntpcs,  selp_nfgds,  selp_tpc_nhits,  selp_tpc_charge);
  //cout << "Set p Rec" << endl;
  
  NeutrinoUtils::SetProtonNRec(nprec);
  //cout << "Set pn Rec" << endl;
  
  NeutrinoUtils::SetReconTgtMass();
  
  Float_t tgtmrec = *(NeutrinoUtils::fReconRecTgtMass);

  //cout << "Recon tgtmRec is: " << tgtmrec << endl;

  return tgtmrec;
  
}


//**************************************************
Float_t numu_cczeropi_utils::getTrueMRec(AnaTrackB* ProtonCandidate, AnaTrackB* MuonCandidate, AnaTrueVertexB* Vertex){
//**************************************************
  NeutrinoUtils::IniCCQE();
 
  Float_t* selp_truedir = ProtonCandidate->GetTrueParticle()->Direction;
  Float_t  selp_truemom = ProtonCandidate->GetTrueParticle()->Momentum;
  Float_t  selp_pdg = ProtonCandidate->GetTrueParticle()->PDG;

  Float_t* selmu_truedir = MuonCandidate->GetTrueParticle()->Direction;
  Float_t  selmu_truemom = MuonCandidate->GetTrueParticle()->Momentum;
  Float_t  selmu_pdg = MuonCandidate->GetTrueParticle()->PDG;

  AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(Vertex);

  Float_t* nu_truedir = vtx->NuDir; 
  Float_t  nu_trueE = 600.00; 

  ND280HL2Utils::SetNeutrinoSim(nu_truedir, nu_trueE);

  const Int_t nmusim = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fMuonSim,   NeutrinoTools::MuonMass(),   selmu_truedir, selmu_truemom, selmu_pdg);
  NeutrinoUtils::SetMuonNSim(nmusim);

  //proton: truep is the one out of nucleus
  const Int_t npsim  = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fProtonSim, NeutrinoTools::ProtonMass(), selp_truedir,   selp_truemom,   selp_pdg);

   NeutrinoUtils::SetProtonNSim(npsim);

 
  
  NeutrinoUtils::SetReconTgtMass();
  
  Float_t tgtmrec = *(NeutrinoUtils::fReconSimTgtMass);

  //cout << "True tgtmRec is: " << tgtmrec << endl;

  return tgtmrec;
  
}

numu_cczeropi_utils::transversityReco::transversityReco(AnaTrackB* MuonCandidate, AnaTrackB* ProtonCandidate, AnaVertexB* Vertex){
  NeutrinoUtils::IniCCQE();

  AnaTrack* ProtonCandidateA = static_cast<AnaTrack*>(ProtonCandidate);
  AnaTrack* MuonCandidateA = static_cast<AnaTrack*>(MuonCandidate);

 
  //Float_t  selp_costheta = ProtonCandidate->DirectionStart[2];
  //Float_t* selp_pos = ProtonCandidate->PositionStart;
  Float_t* selp_endpos = ProtonCandidate->PositionEnd;
  Float_t* selp_dir = ProtonCandidate->DirectionStart;
  //Float_t  selp_theta = acos(ProtonCandidate->DirectionStart[2]);  
  Float_t  selp_mom = ProtonCandidate->Momentum;
  Float_t  selp_mom_range = ProtonCandidateA->RangeMomentumProton;
  Float_t  selp_Chi2 = -999.;//ProtonCandidate->Chi2;
  Float_t  selp_NDOF = -999.;//ProtonCandidate->NDOF;
  Int_t  selp_ntpcs = ProtonCandidate->nTPCSegments;
  Int_t  selp_nfgds = -999.;//ProtonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Proton = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(ProtonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selp_tpc_nhits[3];//TPCSegment_Proton->NHits;
  Float_t  selp_tpc_charge[3];//TPCSegment_Proton->Charge;
  
  //double    selp_amom = ProtonCandidate->MomentumProton;

  //Float_t  selmu_costheta = MuonCandidate->DirectionStart[2];
  //Float_t* selmu_pos = MuonCandidate->PositionStart;
  Float_t* selmu_endpos = MuonCandidate->PositionEnd;
  Float_t* selmu_dir = MuonCandidate->DirectionStart;
  //Float_t  selmu_theta = acos(MuonCandidate->DirectionStart[2]);  
  Float_t  selmu_mom = MuonCandidate->Momentum;
  Float_t  selmu_mom_range = MuonCandidateA->RangeMomentumMuon;
  Float_t  selmu_Chi2 = -999.;//MuonCandidate->Chi2;
  Float_t  selmu_NDOF = -999.;//MuonCandidate->NDOF;
  Int_t  selmu_ntpcs = MuonCandidate->nTPCSegments;
  Int_t  selmu_nfgds = -999.;//MuonCandidate->NFGDs;
  //AnaTpcTrack* TPCSegment_Muon = static_cast<AnaTpcTrack*>(anaUtils::GetSegmentInDet(MuonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
  Int_t  selmu_tpc_nhits[3];//TPCSegment_Muon->NHits;
  Float_t  selmu_tpc_charge[3];//TPCSegment_Muon->Charge;
  //double    selmu_amom = MuonCandidate->MomentumMuon;
  
  Float_t* vertex_pos = Vertex->Position;
  
  //cout << "Starting MEC cut signal" << endl;

  
  ND280HL2Utils::SetNeutrinoRec(vertex_pos);
  //cout << "Set Nu Rec" << endl;
  Int_t nmurec;
  if(selmu_ntpcs==0) nmurec = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fMuonRec,   NeutrinoTools::MuonMass(),   selmu_dir, selmu_mom_range, vertex_pos, selmu_endpos, selmu_Chi2, selmu_NDOF, selmu_ntpcs, selmu_nfgds, selmu_tpc_nhits, selmu_tpc_charge);
  else nmurec = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fMuonRec,   NeutrinoTools::MuonMass(),   selmu_dir, selmu_mom, vertex_pos, selmu_endpos, selmu_Chi2, selmu_NDOF, selmu_ntpcs, selmu_nfgds, selmu_tpc_nhits, selmu_tpc_charge);
  //cout << "Set mu Rec" << endl;

  
  NeutrinoUtils::SetMuonNRec(nmurec);
  //cout << "Set mun Rec" << endl;
  Int_t nprec;
  if(selp_ntpcs==0) nprec  = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fProtonRec, NeutrinoTools::ProtonMass(), selp_dir,  selp_mom_range,  vertex_pos, selp_endpos,  selp_Chi2,  selp_NDOF,  selp_ntpcs,  selp_nfgds,  selp_tpc_nhits,  selp_tpc_charge);
  else nprec  = ND280HL2Utils::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fProtonRec, NeutrinoTools::ProtonMass(), selp_dir,  selp_mom,  vertex_pos, selp_endpos,  selp_Chi2,  selp_NDOF,  selp_ntpcs,  selp_nfgds,  selp_tpc_nhits,  selp_tpc_charge);
  //cout << "Set p Rec" << endl;
  
  NeutrinoUtils::SetProtonNRec(nprec);
  //cout << "Set pn Rec" << endl;
  
  NeutrinoUtils::SetReconTgtMass();
  NeutrinoUtils::SetDeltaPt();
  
  tgtmrec = *(NeutrinoUtils::fReconRecTgtMass);
  dphiT = *(NeutrinoUtils::fDeltaRecPhi_t);
  dpT = (NeutrinoUtils::fDeltaRecPt)->Mag();
  dalphaT = (NeutrinoUtils::fDeltaRecPt)->Theta();

  // cout << "HMP mom and dir: " << selp_mom << ", " << selp_dir[0] << ", " << selp_dir[1] << ", " << selp_dir[2] << endl;
  // cout <<"Recon tgtmRec, dphiT, dpT and dalphaT is:"<<tgtmrec<<","<<dphiT<<","<<dpT<<","<<dalphaT<<endl;
  
}

numu_cczeropi_utils::transversityTrue::transversityTrue(AnaTrackB* MuonCandidate, AnaTrackB* ProtonCandidate, AnaTrueVertexB* Vertex){
  NeutrinoUtils::IniCCQE();
 
  Float_t* selp_truedir = ProtonCandidate->GetTrueParticle()->Direction;
  Float_t  selp_truemom = ProtonCandidate->GetTrueParticle()->Momentum;
  Float_t  selp_pdg = ProtonCandidate->GetTrueParticle()->PDG;

  Float_t* selmu_truedir = MuonCandidate->GetTrueParticle()->Direction;
  Float_t  selmu_truemom = MuonCandidate->GetTrueParticle()->Momentum;
  Float_t  selmu_pdg = MuonCandidate->GetTrueParticle()->PDG;

  AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(Vertex);

  Float_t* nu_truedir = vtx->NuDir; 
  Float_t  nu_trueE = 600.00; 

  ND280HL2Utils::SetNeutrinoSim(nu_truedir, nu_trueE);

  const Int_t nmusim = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fMuonSim,   NeutrinoTools::MuonMass(),   selmu_truedir, selmu_truemom, selmu_pdg);
  NeutrinoUtils::SetMuonNSim(nmusim);

  //proton: truep is the one out of nucleus
  const Int_t npsim  = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fProtonSim, NeutrinoTools::ProtonMass(), selp_truedir,   selp_truemom,   selp_pdg);

  NeutrinoUtils::SetProtonNSim(npsim); 
  
  NeutrinoUtils::SetReconTgtMass();
  NeutrinoUtils::SetDeltaPt();
  
  tgtmrec = *(NeutrinoUtils::fReconSimTgtMass);
  dphiT = *(NeutrinoUtils::fDeltaSimPhi_t);
  dpT = (NeutrinoUtils::fDeltaSimPt)->Mag();
  dalphaT = (NeutrinoUtils::fDeltaSimPt)->Theta();

  // cout << "HMP mom and dir: " << selp_truemom << ", " << selp_truedir[0] << ", " << selp_truedir[1] << ", " << selp_truedir[2] << endl;
  // cout <<"True tgtmRec, dphiT, dpT and dalphaT is:"<<tgtmrec<<","<<dphiT<<","<<dpT<<","<<dalphaT<<endl;  
}

numu_cczeropi_utils::transversityTrueT::transversityTrueT(const AnaTrueVertex& vtx){
  NeutrinoUtils::IniCCQE();

   
  Float_t* selp_truedir = (Float_t*)vtx.ProtonDir;
  Float_t  selp_truemom = vtx.ProtonMom;
  Float_t  selp_pdg = 2212;

  Float_t* selmu_truedir = (Float_t*)vtx.LeptonDir;
  Float_t  selmu_truemom = vtx.LeptonMom;
  Float_t  selmu_pdg = vtx.LeptonPDG;

  Float_t* nu_truedir = (Float_t*)vtx.NuDir; 
  Float_t  nu_trueE = 600.00; 

  ND280HL2Utils::SetNeutrinoSim(nu_truedir, nu_trueE);

  const Int_t nmusim = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fMuonSim,   NeutrinoTools::MuonMass(),   selmu_truedir, selmu_truemom, selmu_pdg);
  NeutrinoUtils::SetMuonNSim(nmusim);

  //proton: truep is the one out of nucleus
  const Int_t npsim  = ND280HL2Utils::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fProtonSim, NeutrinoTools::ProtonMass(), selp_truedir,   selp_truemom,   selp_pdg);

  NeutrinoUtils::SetProtonNSim(npsim); 
  
  NeutrinoUtils::SetReconTgtMass();
  NeutrinoUtils::SetDeltaPt();
  
  tgtmrec = *(NeutrinoUtils::fReconSimTgtMass);
  dphiT = *(NeutrinoUtils::fDeltaSimPhi_t);
  dpT = (NeutrinoUtils::fDeltaSimPt)->Mag();
  dalphaT = (NeutrinoUtils::fDeltaSimPt)->Theta();

  //cout <<"TrueT tgtmRec, dphiT, dpT and dalphaT is:"<<tgtmrec<<","<<dphiT<<","<<dpT<<","<<dalphaT<<endl;  
  
}

// Path Length Functions: 

Float_t numu_cczeropi_utils::get3x3PathLength(Float_t* dir){
  Float_t barL = 9.61; //mm
  Float_t numBars = 1.5;//3x3 box around the vertex in the centre bar -> 1.5 bars on each side  
  Float_t pathLen=numBars*barL*sqrt((tan(dir[0])*(tan(dir[0])))+(tan(dir[1])*(tan(dir[1])))+1);
  return pathLen;
}
  
// ********************************************************************
Float_t* numu_cczeropi_utils::GetFittedPos(Float_t* start, Float_t* end, double z){
// ********************************************************************

  double t = (z-start[2])/(end[2]-start[2]);
  Float_t* pos = new Float_t(3);
  pos[0] = start[0]+(end[0]-start[0])*t;
  pos[1] = start[1]+(end[1]-start[1])*t;
  pos[2] = z;
  
  return pos;

}

// ********************************************************************
Float_t numu_cczeropi_utils::GetDeltaPos(Float_t* hit, Float_t* fit){
// ********************************************************************

  Float_t delta = 0;
  if ( hit[0]>-4.6 && hit[0]<0.2 )  delta = hit[1] - fit[1];
  if ( hit[1]>50.4 && hit[1]<55.2 ) delta = hit[0] - fit[0];

  return delta;

}

// ********************************************************************
Float_t numu_cczeropi_utils::GetDeltaPos2(Float_t* hit, Float_t* fit){
// ********************************************************************

  Float_t delta = 0;
  if ( hit[0]>-4.6 && hit[0]<0.2 )  delta = hit[1]*hit[1] - fit[1]*fit[1];
  if ( hit[1]>50.4 && hit[1]<55.2 ) delta = hit[0]*hit[0] - fit[0]*fit[0];

  return delta;

}

//********************************************************************
bool numu_cczeropi_utils::VetoCut(const AnaEventB& event, AnaTrackB& candidate){
  //********************************************************************

  AnaTrackB* VetoTrack = cutUtils::FindVetoTrack(event, candidate);
  if (VetoTrack) {
    //if (VetoTrack->PositionStart[2]-candidate.PositionStart[2]<-100. && VetoTrack->Momentum/candidate.Momentum>0.8) return false;
    if (VetoTrack->PositionStart[2]<-890.00) return false;
  }
  return true;

}




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
// However, note that I tried to change all the unites to be in MeV, I may have messed something up here ... 

//NUISANCE: a neutrino cross-section generator tuning and comparison framework.
//P. Stowell, C. Wret, C. Wilkinson, L. Pickering, et. al., 2017 JINST 12 P01016, arXiv:1612.07393



const double mn  = 939.565;  // neutron mass
const double mp  = 938.272;   // proton mass
const double mmu = 105.65837;   // muon mass
//These numbers are not hard coded in NUISANCE, but I put them here for the moment


//********************************************************
double numu_cczeropi_utils::ProtonQ2QErec(double pE, double binding) {
  //********************************************************

  const double V = binding;           // binding potential
  const double mn_eff = mn - V;               // effective proton mass
  const double pki = (pE) - mp;

  double q2qe = mn_eff * mn_eff - mp * mp + 2 * mn_eff * (pki + mp - mn_eff);

  return q2qe;
};

//********************************************************************
double numu_cczeropi_utils::EnuQErec(TLorentzVector pmu, double costh, double binding,
                          bool neutrino) {
  //********************************************************************

  // Convert all values to GeV
  const double V = binding;           // binding potential

  double mN_eff = mn - V;
  double mN_oth = mp;

  if (!neutrino) {
    mN_eff = mp - V;
    mN_oth = mn;
  }

  double el = pmu.E() ;
  double pl = (pmu.Vect().Mag()) ;  // momentum of lepton
  double ml = sqrt(el * el - pl * pl);     // lepton mass

  double rEnu =
      (2 * mN_eff * el - ml * ml + mN_oth * mN_oth - mN_eff * mN_eff) /
      (2 * (mN_eff - el + pl * costh));

  return rEnu;
};

double numu_cczeropi_utils::Q2QErec(TLorentzVector pmu, double costh, double binding,
                         bool neutrino) {
  double el = pmu.E() ;
  double pl = (pmu.Vect().Mag()) ;  // momentum of lepton
  double ml = sqrt(el * el - pl * pl);     // lepton mass

  double rEnu = EnuQErec(pmu, costh, binding, neutrino);
  double q2 = -ml * ml + 2. * rEnu * (el - pl * costh);

  return q2;
};

double numu_cczeropi_utils::EnuQErec(double pl, double costh, double binding,
                          bool neutrino) {
  if (pl < 0) return 0.;  // Make sure nobody is silly

  double mN_eff = mn - binding ;
  double mN_oth = mp;

  if (!neutrino) {
    mN_eff = mp - binding ;
    mN_oth = mn;
  }
  double ml = mmu;
  double el = sqrt(pl * pl + ml * ml);

  double rEnu =
      (2 * mN_eff * el - ml * ml + mN_oth * mN_oth - mN_eff * mN_eff) /
      (2 * (mN_eff - el + pl * costh));

  return rEnu;
};

double numu_cczeropi_utils::Q2QErec(double pl, double costh, double binding,
                         bool neutrino) {
  if (pl < 0) return 0.;  // Make sure nobody is silly

  double ml = mmu;
  double el = sqrt(pl * pl + ml * ml);

  double rEnu = EnuQErec(pl, costh, binding, neutrino);
  double q2 = -ml * ml + 2. * rEnu * (el - pl * costh);

  return q2;
};

//********************************************************************
// Reconstructs Enu for CC1pi0
// Very similar for CC1pi+ reconstruction
double numu_cczeropi_utils::EnuCC1pi0rec(TLorentzVector pnu, TLorentzVector pmu,
                              TLorentzVector ppi0) {
  //********************************************************************

  double E_mu = pmu.E();
  double p_mu = pmu.Vect().Mag();
  double m_mu = sqrt(E_mu * E_mu - p_mu * p_mu);
  double th_nu_mu = pnu.Vect().Angle(pmu.Vect());

  double E_pi0 = ppi0.E();
  double p_pi0 = ppi0.Vect().Mag();
  double m_pi0 = sqrt(E_pi0 * E_pi0 - p_pi0 * p_pi0);
  double th_nu_pi0 = pnu.Vect().Angle(ppi0.Vect());

  const double m_n = mn;  // neutron mass
  const double m_p = mp;   // proton mass
  double th_pi0_mu = ppi0.Vect().Angle(pmu.Vect());

  double rEnu = (m_mu * m_mu + m_pi0 * m_pi0 + m_n * m_n - m_p * m_p -
                 2 * m_n * (E_pi0 + E_mu) + 2 * E_pi0 * E_mu -
                 2 * p_pi0 * p_mu * cos(th_pi0_mu)) /
                (2 * (E_pi0 + E_mu - p_pi0 * cos(th_nu_pi0) -
                      p_mu * cos(th_nu_mu) - m_n));

  return rEnu;
};

//********************************************************************
// Reconstruct Q2 for CC1pi0
// Beware: uses true Enu, not reconstructed Enu
double numu_cczeropi_utils::Q2CC1pi0rec(TLorentzVector pnu, TLorentzVector pmu,
                             TLorentzVector ppi0) {
  //********************************************************************

  double E_mu = pmu.E() ;                  // energy of lepton in GeV
  double p_mu = pmu.Vect().Mag() ;         // momentum of lepton
  double m_mu = sqrt(E_mu * E_mu - p_mu * p_mu);  // lepton mass
  double th_nu_mu = pnu.Vect().Angle(pmu.Vect());

  // double rEnu = EnuCC1pi0rec(pnu, pmu, ppi0); //reconstructed neutrino energy
  // Use true neutrino energy
  double rEnu = pnu.E() ;
  double q2 = -m_mu * m_mu + 2. * rEnu * (E_mu - p_mu * cos(th_nu_mu));

  return q2;
};

//********************************************************************
// Reconstruct Enu for CC1pi+
// pionInfo reflects if we're using pion kinematics or not
// In T2K CC1pi+ CH the Michel tag is used for pion in which pion kinematic info
// is lost and Enu is reconstructed without pion kinematics
double numu_cczeropi_utils::EnuCC1piprec(TLorentzVector pnu, TLorentzVector pmu,
                              TLorentzVector ppi, bool pionInfo) {
  //********************************************************************

  double E_mu = pmu.E() ;
  double p_mu = pmu.Vect().Mag() ;
  double m_mu = sqrt(E_mu * E_mu - p_mu * p_mu);

  double E_pi = ppi.E() ;
  double p_pi = ppi.Vect().Mag() ;
  double m_pi = sqrt(E_pi * E_pi - p_pi * p_pi);

  const double m_n = mn;  // neutron/proton mass
  // should really take proton mass for proton interaction, neutron for neutron
  // interaction. However, difference is pretty much negligable here!

  // need this angle too
  double th_nu_pi = pnu.Vect().Angle(ppi.Vect());
  double th_nu_mu = pnu.Vect().Angle(pmu.Vect());
  double th_pi_mu = ppi.Vect().Angle(pmu.Vect());

  double rEnu = -999;
  // If experiment doesn't have pion kinematic information (T2K CC1pi+ CH
  // example of this; Michel e sample has no directional information on pion)
  // We'll need to modify the reconstruction variables
  if (!pionInfo) {
    // Assumes that pion angle contribution contributes net zero
    // Also assumes the momentum of reconstructed pions when using Michel
    // electrons is 130 MeV
    // So need to redefine E_pi and p_pi
    // It's a little unclear what happens to the pmu . ppi term (4-vector); do
    // we include the angular contribution?
    // This below doesn't
    th_nu_pi = M_PI / 2.;
    p_pi = 0.130;
    E_pi = sqrt(p_pi * p_pi + m_pi * m_pi);
    // rEnu = (m_mu*m_mu + m_pi*m_pi - 2*m_n*(E_mu + E_pi) + 2*E_mu*E_pi -
    // 2*p_mu*p_pi) / (2*(E_mu + E_pi - p_mu*cos(th_nu_mu) - m_n));
  }

  rEnu =
      (m_mu * m_mu + m_pi * m_pi - 2 * m_n * (E_pi + E_mu) + 2 * E_pi * E_mu -
       2 * p_pi * p_mu * cos(th_pi_mu)) /
      (2 * (E_pi + E_mu - p_pi * cos(th_nu_pi) - p_mu * cos(th_nu_mu) - m_n));

  return rEnu;
};

//********************************************************************
// Reconstruct neutrino energy from outgoing particles; will differ from the
// actual neutrino energy. Here we use assumption of a Delta resonance
double numu_cczeropi_utils::EnuCC1piprecDelta(TLorentzVector pnu, TLorentzVector pmu) {
  //********************************************************************

  const double m_Delta = 1232;  // PDG value for Delta mass in MeV
  const double m_n = mn;  // neutron/proton mass
  // should really take proton mass for proton interaction, neutron for neutron
  // interaction. However, difference is pretty much negligable here!

  double E_mu = pmu.E();
  double p_mu = pmu.Vect().Mag();
  double m_mu = sqrt(E_mu * E_mu - p_mu * p_mu);
  double th_nu_mu = pnu.Vect().Angle(pmu.Vect());

  double rEnu = (m_Delta * m_Delta - m_n * m_n - m_mu * m_mu + 2 * m_n * E_mu) /
                (2 * (m_n - E_mu + p_mu * cos(th_nu_mu)));

  return rEnu;
};

// MOVE TO T2K UTILS!
//********************************************************************
// Reconstruct Enu using "extended MiniBooNE" as defined in Raquel's T2K TN
//
// Supposedly includes pion direction and binding energy of target nucleon
// I'm not convinced (yet), maybe
double numu_cczeropi_utils::EnuCC1piprec_T2K_eMB(TLorentzVector pnu, TLorentzVector pmu,
                                      TLorentzVector ppi) {
  //********************************************************************

  // Unit vector for neutrino momentum
  TVector3 p_nu_vect_unit = pnu.Vect() * (1. / pnu.E());

  double E_mu = pmu.E() ;
  TVector3 p_mu_vect = pmu.Vect() * (1. );

  double E_pi = ppi.E() ;
  TVector3 p_pi_vect = ppi.Vect() * (1. );

  double E_bind =
      27. ;  // This should be roughly correct for CH; but not clear!
  double m_p = mp;

  // Makes life a little easier, gonna square this one
  double a1 = m_p - E_bind - E_mu - E_pi;
  // Just gets the magnitude square of the muon and pion momentum vectors
  double a2 = (p_mu_vect + p_pi_vect).Mag2();
  // Gets the somewhat complicated scalar product between neutrino and
  // (p_mu+p_pi), scaled to Enu
  double a3 = p_nu_vect_unit * (p_mu_vect + p_pi_vect);

  double rEnu =
      (m_p * m_p - a1 * a1 + a2) / (2 * (m_p - E_bind - E_mu - E_pi + a3));

  return rEnu;
}

//********************************************************************
// Reconstructed Q2 for CC1pi+
//
// enuType describes how the neutrino energy is reconstructed
// 0 uses true neutrino energy; case for MINERvA and MiniBooNE
// 1 uses "extended MiniBooNE" reconstructed (T2K CH)
// 2 uses "MiniBooNE" reconstructed (EnuCC1piprec with pionInfo = true) (T2K CH)
//        "MiniBooNE" reconstructed (EnuCC1piprec with pionInfo = false, the
//        case for T2K when using Michel tag) (T2K CH)
// 3 uses Delta for reconstruction (T2K CH)
double numu_cczeropi_utils::Q2CC1piprec(TLorentzVector pnu, TLorentzVector pmu,
                             TLorentzVector ppi, int enuType, bool pionInfo) {
  //********************************************************************

  double E_mu = pmu.E() ;                  // energy of lepton in GeV
  double p_mu = pmu.Vect().Mag() ;         // momentum of lepton
  double m_mu = sqrt(E_mu * E_mu - p_mu * p_mu);  // lepton mass
  double th_nu_mu = pnu.Vect().Angle(pmu.Vect());

  // Different ways of reconstructing the neutrino energy; default is just to
  // use the truth (case 0)
  double rEnu = -999;

  switch (enuType) {
    case 0:  // True neutrino energy, default; this is the case for when Q2
             // defined as Q2 true (MiniBooNE, MINERvA)
      rEnu = pnu.E() ;
      break;
    case 1:  // Extended MiniBooNE reconstructed, as defined by Raquel's CC1pi+
             // CH T2K analysis
             // Definitely uses pion info :)
      rEnu = EnuCC1piprec_T2K_eMB(pnu, pmu, ppi);
      break;
    case 2:  // MiniBooNE reconstructed, as defined by MiniBooNE and Raquel's
             // CC1pi+ CH T2K analysis and Linda's CC1pi+ H2O
      // Can have this with and without pion info, depending on if Michel tag
      // used (Raquel)
      rEnu = EnuCC1piprec(pnu, pmu, ppi, pionInfo);
      break;
    case 3:
      rEnu = EnuCC1piprecDelta(pnu, pmu);
      break;

  }  // No need for default here since default value of enuType = 0, defined in
     // header

  double q2 = -m_mu * m_mu + 2. * rEnu * (E_mu - p_mu * cos(th_nu_mu));

  return q2;
};

//********************************************************************
// Returns the reconstructed W from a nucleon and an outgoing pion
//
// Could do this a lot more clever (pp + ppi).Mag() would do the job, but this
// would be less instructive
//********************************************************************
double numu_cczeropi_utils::MpPi(TLorentzVector pp, TLorentzVector ppi) {
  double E_p = pp.E();
  double p_p = pp.Vect().Mag();
  double m_p = sqrt(E_p * E_p - p_p * p_p);

  double E_pi = ppi.E();
  double p_pi = ppi.Vect().Mag();
  double m_pi = sqrt(E_pi * E_pi - p_pi * p_pi);

  double th_p_pi = pp.Vect().Angle(ppi.Vect());

  // fairly easy thing to derive since bubble chambers measure the proton!
  double invMass = sqrt(m_p * m_p + m_pi * m_pi + 2 * E_p * E_pi -
                        2 * p_pi * p_p * cos(th_p_pi));

  return invMass;
};

//********************************************************

// Reconstruct the hadronic mass using neutrino and muon
// Could technically do E_nu = EnuCC1pipRec(pnu,pmu,ppi) too, but this wwill be
// reconstructed Enu; so gives reconstructed Wrec which most of the time isn't
// used!
//
// Only MINERvA uses this so far; and the Enu is Enu_true
// If we want W_true need to take initial state nucleon motion into account
// Return value is in MeV!!!
double numu_cczeropi_utils::Wrec(TLorentzVector pnu, TLorentzVector pmu) {
  //********************************************************

  double E_mu = pmu.E();
  double p_mu = pmu.Vect().Mag();
  double m_mu = sqrt(E_mu * E_mu - p_mu * p_mu);
  double th_nu_mu = pnu.Vect().Angle(pmu.Vect());

  const double m_p = mp;

  // MINERvA cut on W_exp which is tuned to W_true; so use true Enu from
  // generators
  double E_nu = pnu.E();

  double w_rec = sqrt(m_p * m_p + m_mu * m_mu - 2 * m_p * E_mu +
                      2 * E_nu * (m_p - E_mu + p_mu * cos(th_nu_mu)));

  return w_rec;
};

//********************************************************
// Reconstruct the true hadronic mass using the initial state and muon
// Could technically do E_nu = EnuCC1pipRec(pnu,pmu,ppi) too, but this wwill be
// reconstructed Enu; so gives reconstructed Wrec which most of the time isn't
// used!
//
// No one seems to use this because it's fairly MC dependent!
// Return value is in MeV!!!
double numu_cczeropi_utils::Wtrue(TLorentzVector pnu, TLorentzVector pmu,
                       TLorentzVector pnuc) {
  //********************************************************

  // Could simply do the TLorentzVector operators here but this is more
  // instructive?
  // ... and prone to errors ...

  double E_mu = pmu.E();
  double p_mu = pmu.Vect().Mag();
  double m_mu = sqrt(E_mu * E_mu - p_mu * p_mu);
  double th_nu_mu = pnu.Vect().Angle(pmu.Vect());

  double E_nuc = pnuc.E();
  double p_nuc = pnuc.Vect().Mag();
  double m_nuc = sqrt(E_nuc * E_nuc - p_nuc * p_nuc);
  double th_nuc_mu = pmu.Vect().Angle(pnuc.Vect());
  double th_nu_nuc = pnu.Vect().Angle(pnuc.Vect());

  double E_nu = pnu.E();

  double w_rec = sqrt(m_nuc * m_nuc + m_mu * m_mu - 2 * E_nu * E_mu +
                      2 * E_nu * p_mu * cos(th_nu_mu) - 2 * E_nuc * E_mu +
                      2 * p_nuc * p_mu * cos(th_nuc_mu) + 2 * E_nu * E_nuc -
                      2 * E_nu * p_nuc * cos(th_nu_nuc));

  return w_rec;
};


TVector3 GetVectorInTPlane(const TVector3 &inp, const TVector3 &planarNormal) {
  TVector3 pnUnit = planarNormal.Unit();
  double inpProjectPN = inp.Dot(pnUnit);

  TVector3 InPlanarInput = inp - (inpProjectPN * pnUnit);
  return InPlanarInput;
}

TVector3 GetUnitVectorInTPlane(const TVector3 &inp,
                               const TVector3 &planarNormal) {
  return GetVectorInTPlane(inp, planarNormal).Unit();
}

Double_t GetDeltaPhiT(TVector3 const &V_lepton, TVector3 const &V_other,
                      TVector3 const &Normal, bool PiMinus = false) {
  TVector3 V_lepton_T = GetUnitVectorInTPlane(V_lepton, Normal);

  TVector3 V_other_T = GetUnitVectorInTPlane(V_other, Normal);

  return PiMinus ? acos(V_lepton_T.Dot(V_other_T))
                 : (M_PI - acos(V_lepton_T.Dot(V_other_T)));
}

TVector3 GetDeltaPT(TVector3 const &V_lepton, TVector3 const &V_other,
                    TVector3 const &Normal) {
  TVector3 V_lepton_T = GetVectorInTPlane(V_lepton, Normal);

  TVector3 V_other_T = GetVectorInTPlane(V_other, Normal);

  return V_lepton_T + V_other_T;
}

Double_t GetDeltaAlphaT(TVector3 const &V_lepton, TVector3 const &V_other,
                        TVector3 const &Normal, bool PiMinus = false) {
  TVector3 DeltaPT = GetDeltaPT(V_lepton, V_other, Normal);

  return GetDeltaPhiT(V_lepton, DeltaPT, Normal, PiMinus);
}


// As defined in PhysRevC.95.065501
// Using prescription from arXiv 1805.05486 

Float_t numu_cczeropi_utils::Get_pn_reco_C(TVector3 NuP, TVector3 LeptonP, TVector3 HadronP) {

  Float_t el = sqrt(LeptonP.Mag()*LeptonP.Mag() + mmu*mmu);
  Float_t eh = sqrt(HadronP.Mag()*HadronP.Mag() + mp*mp);

  TVector3 dpt = GetDeltaPT(LeptonP, HadronP, NuP);
  Float_t dptMag = dpt.Mag();

  Float_t ma = 6*mn + 6*mp - 92.16; // target mass (E is from PhysRevC.95.065501)
  Float_t map = ma - mn + 27.13; // reminant mass

  Float_t pmul = LeptonP.Dot(NuP.Unit());
  Float_t phl = HadronP.Dot(NuP.Unit());

  Float_t R = ma + pmul + phl - el - eh;

  Float_t dpl = 0.5*R - (map*map + dptMag*dptMag)/(2*R);
  //Float_t dpl = ((R*R)-(dptMag*dptMag)-(map*map))/(2*R); // as in in PhysRevC.95.065501 - gives same result

  Float_t pn_reco = sqrt((dptMag*dptMag) + (dpl*dpl));

  //std::cout << "DUBUG INFO " << std::endl;
  //NuP.Print();
  //LeptonP.Print();
  //HadronP.Print();
  //std::cout << "el is " <<  el << std::endl;
  //std::cout << "eh is " <<  eh << std::endl;
  //dpt.Print();
  //std::cout << "      Get_pn_reco_C: dpt Mag, pn " <<  dptMag << ", " << pn_reco << std::endl;
  //std::cout << "dpl is " <<  dpl << std::endl;
  //std::cout << "pn_reco is " <<  pn_reco << std::endl;
  //getchar();



  return pn_reco;
}




// Get Cos theta with Adler angles
double numu_cczeropi_utils::CosThAdler(TLorentzVector Pnu, TLorentzVector Pmu, TLorentzVector Ppi, TLorentzVector Pprot) {
  // Get the "resonance" lorentz vector (pion proton system)
  TLorentzVector Pres = Pprot + Ppi;
  // Boost the particles into the resonance rest frame so we can define the x,y,z axis
  Pnu.Boost(Pres.BoostVector());
  Pmu.Boost(-Pres.BoostVector());
  Ppi.Boost(-Pres.BoostVector());

  // The z-axis is defined as the axis of three-momentum transfer, \vec{k}
  // Also unit normalise the axis
  TVector3 zAxis = (Pnu.Vect()-Pmu.Vect())*(1.0/((Pnu.Vect()-Pmu.Vect()).Mag()));

  // Then the angle between the pion in the "resonance" rest-frame and the z-axis is the theta Adler angle
  double costhAdler = cos(Ppi.Vect().Angle(zAxis));

  return costhAdler;
}

// Get phi with Adler angles, a bit more complicated...
double numu_cczeropi_utils::PhiAdler(TLorentzVector Pnu, TLorentzVector Pmu, TLorentzVector Ppi, TLorentzVector Pprot) {

  // Get the "resonance" lorentz vector (pion proton system)
  TLorentzVector Pres = Pprot + Ppi;
  // Boost the particles into the resonance rest frame so we can define the x,y,z axis
  Pnu.Boost(Pres.BoostVector());
  Pmu.Boost(-Pres.BoostVector());
  Ppi.Boost(-Pres.BoostVector());

  // The z-axis is defined as the axis of three-momentum transfer, \vec{k}
  // Also unit normalise the axis
  TVector3 zAxis = (Pnu.Vect()-Pmu.Vect())*(1.0/((Pnu.Vect()-Pmu.Vect()).Mag()));

  // The y-axis is then defined perpendicular to z and muon momentum in the resonance frame
  TVector3 yAxis = Pnu.Vect().Cross(Pmu.Vect());
  yAxis *= 1.0/double(yAxis.Mag());

  // And the x-axis is then simply perpendicular to z and x
  TVector3 xAxis = yAxis.Cross(zAxis);
  xAxis *= 1.0/double(xAxis.Mag());

  // Get the project of the pion momentum on to the zaxis
  TVector3 PiVectZ = zAxis*Ppi.Vect().Dot(zAxis);
  // The subtract the projection off the pion vector to get to get the plane
  TVector3 PiPlane = Ppi.Vect() - PiVectZ;

  // Then finally construct phi as the angle between pion projection and x axis
  double phi = -999.99;

  if (PiPlane.Y() > 0) {
    phi = (180./M_PI)*PiPlane.Angle(xAxis);
  } else if (PiPlane.Y() < 0) {
    phi = (180./M_PI)*(2*M_PI-PiPlane.Angle(xAxis));
  } else if (PiPlane.Y() == 0) {
    TRandom3 rand;
    double randNo = rand.Rndm();
    if (randNo > 0.5) {
      phi = (180./M_PI)*PiPlane.Angle(xAxis);
    } else {
      phi = (180./M_PI)*(2*M_PI-PiPlane.Angle(xAxis));
    }
  }

  return phi;
}

//********************************************************************
double numu_cczeropi_utils::ppInfK(TLorentzVector pmu, double costh, double binding,
                          bool neutrino) {
  //********************************************************************

  // Convert all values to GeV
  const double V = binding ;           // binding potential
  double el = pmu.E() ;
  double pl = (pmu.Vect().Mag()) ;  // momentum of lepton

  double enu = EnuQErec(pmu, costh, binding, neutrino);

  double ep_inf = enu - el + mp;
  double pp_inf = sqrt(ep_inf * ep_inf - mp * mp);

  return pp_inf;
};

//********************************************************************
TVector3 numu_cczeropi_utils::tppInfK(TLorentzVector pmu, double costh, double binding,
                          bool neutrino) {
  //********************************************************************

  // Convert all values to GeV
  const double V = binding ;           // binding potential
  double pl_x = pmu.X() ;
  double pl_y = pmu.Y() ;
  double pl_z= pmu.Z() ;

  double enu = EnuQErec(pmu, costh, binding, neutrino);

  TVector3 tpp_inf(-pl_x, -pl_y, -pl_z+enu);

  return tpp_inf;
};

//********************************************************************
double numu_cczeropi_utils::cthpInfK(TLorentzVector pmu, double costh, double binding,
                          bool neutrino) {
  //********************************************************************

  // Convert all values to GeV
  const double V = binding ;           // binding potential
  double el = pmu.E() ;
  double pl = (pmu.Vect().Mag()) ;  // momentum of lepton

  double enu = EnuQErec(pmu, costh, binding, neutrino);

  double ep_inf = enu - el + mp;
  double pp_inf = sqrt(ep_inf * ep_inf - mp * mp);

  double cth_inf = (enu*enu + pp_inf*pp_inf - pl*pl)/(2*enu*pp_inf);

  return cth_inf;
};



