#include <TVector3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "AnalysisUtils.hxx"
#include "EventBoxId.hxx"
#include "ND280AnalysisUtils.hxx"
#include "CategoriesUtils.hxx"
#include "HighlandAnalysisUtils.hxx"
#include "CutUtils.hxx"
#include "numuCC4piMultiPiUtils.hxx"

//**************************************************
Int_t numuCC4piMultiPi_utils::GetCONTTopology(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det, bool IsAntinu){
  //************************************************
  /* Classify contaminations types
   -1 = no true vertex
    0 = CC 0pi          = mu- + 0 mesons
    1 = CC 1pi+         = mu- + 1 pion+ 
    2 = CC 1pi+ 1pi-/0  = mu+ + 1 pion+ + 1 pion-/1 pion0 
    3 = CC 2pi+         = mu- + 2 pion+ 
    4 = CC rest         = mu- + rest  
    5 = NC + BKG   
    6 = out of FV
  */
  /// primary particles from the true vertex
  Int_t Npipos =    trueVertex.NPrimaryParticles[ParticleId::kPiPos];
  Int_t Npineg =    trueVertex.NPrimaryParticles[ParticleId::kPiNeg];
  Int_t Npi0 =      trueVertex.NPrimaryParticles[ParticleId::kPiZero];

  // get GetTopology for (anti-)numu
  Int_t topo = anaUtils::GetTopology(trueVertex,det,IsAntinu);

  if (topo == 0)                       return 0; // CC 0pi 
  if (topo == 1)                       return 1; // CC 1pi+ 1p/n
  if (topo == 2) {
    if (Npipos == 1 && (Npineg ==1 || Npi0 == 1))  return 2; // CC 1pi+ 1pi- 
    if (Npipos == 2)                               return 3; // CC 2pi+ 
    else return 4; // CC rest
  }
  else if (topo == 3)           return 5; // BKG
  else if (topo == 7)      return 6; // OOFV 
  // else std::cout << "Error in getting topology codes!" << std::endl;
  return -999;


}

