#include "HighlandKinematicsUtils.hxx"
#include "CoreUtils.hxx"
#include "HEPConstants.hxx"

//********************************************************************
Float_t anaUtils::ComputeQ2(const Float_t* NuP4, const Float_t* LepP4){
  //********************************************************************


  TLorentzVector p4v = anaUtils::ArrayToTLorentzVector(NuP4);

  TLorentzVector p4l = anaUtils::ArrayToTLorentzVector(LepP4);

  TLorentzVector q = p4v - p4l;

  return (-1. * q.M2());


}

//********************************************************************
Float_t anaUtils::ComputeV(const Float_t* NuP4, const Float_t* LepP4){
  //********************************************************************

  TLorentzVector p4v = anaUtils::ArrayToTLorentzVector(NuP4);

  TLorentzVector p4l = anaUtils::ArrayToTLorentzVector(LepP4);

  TLorentzVector q = p4v - p4l;
  return q.Energy();
}

//********************************************************************
Float_t anaUtils::ComputeX(const Float_t* NuP4, const Float_t* LepP4){
  //********************************************************************


  Float_t Q2 = anaUtils::ComputeQ2(NuP4, LepP4);
  Float_t v  = anaUtils::ComputeV(NuP4, LepP4);

  Float_t M = units::mass_nucleon;

  if (M * v <= 0)
    return 0;

  Float_t xbj = 0.5 * Q2 / (M * v);

  return xbj; 

}

//********************************************************************
Float_t anaUtils::ComputeY(const Float_t* NuP4, const Float_t* LepP4){
  //********************************************************************

  Float_t Ev = NuP4[3];

  if (Ev <= 0)
    return 0;

  Float_t v = anaUtils::ComputeV(NuP4, LepP4);
  Float_t y = v / Ev;
  return y;
}

//********************************************************************
Float_t anaUtils::ComputeW(const Float_t* NuP4, const Float_t* LepP4, const Float_t* HitNucP4){
  //********************************************************************

  TLorentzVector p4v  = anaUtils::ArrayToTLorentzVector(NuP4);

  TLorentzVector p4l  = anaUtils::ArrayToTLorentzVector(LepP4);

  TLorentzVector p4n  = anaUtils::ArrayToTLorentzVector(HitNucP4);


  TLorentzVector q = p4v - p4l;
  TLorentzVector w = p4n + q;

  return w.Mag(); 

}

//*******************************************************************
bool anaUtils::RetrieveInitialKinematics(const AnaTrueVertex& vtx, Float_t* p4v, Float_t* p4l, Float_t* p4n, const Int_t size){
//********************************************************************

  if (size != 4){
    std::cout << " anaUtils::RetrieveInitialKinematics(): size of the arrays should be equal to 4! exit " << std::endl;
    exit(1);
  }
 
  
  Float_t Ev = vtx.NuEnergy;

  p4v[0] = Ev * vtx.NuDir[0];
  
  p4v[1] = Ev * vtx.NuDir[1];
  
  p4v[2] = Ev * vtx.NuDir[2];
  
  p4v[3] = Ev;
 
 
  anaUtils::CopyArray(vtx.StruckNucl4Mom, p4n, 4);
  
  if (!units::GetPDGBase()->GetParticle(vtx.LeptonPDG)) // e.g. NC case
    return false; 
  

  Float_t Ml  = units::GetPDGBase()->GetParticle(vtx.LeptonPDG)->Mass(); 

  Float_t El  = sqrt(Ml * Ml + vtx.LeptonMom * vtx.LeptonMom);

  p4l[0] = vtx.LeptonMom * vtx.LeptonDir[0];
  p4l[1] = vtx.LeptonMom * vtx.LeptonDir[1]; 
  p4l[2] = vtx.LeptonMom * vtx.LeptonDir[2];
  p4l[3] = El;
   
  return true;
  
}
  
//********************************************************************
Float_t anaUtils::ComputeV(const AnaTrueVertex& vtx){
  //********************************************************************
  Float_t p4v[4];
  Float_t p4l[4];
  Float_t p4n[4];
  
  if (!anaUtils::RetrieveInitialKinematics(vtx, p4v, p4l, p4n, 4))
    return 0.;
  
  return anaUtils::ComputeV(p4v, p4l); 
}
//********************************************************************
Float_t anaUtils::ComputeQ2(const AnaTrueVertex& vtx){ 

  //********************************************************************

  Float_t p4v[4];
  Float_t p4l[4];
  Float_t p4n[4];
  
  if (!anaUtils::RetrieveInitialKinematics(vtx, p4v, p4l, p4n, 4))
    return 0.;
  
  return anaUtils::ComputeQ2(p4v, p4l); 
}
//********************************************************************
Float_t anaUtils::ComputeX(const AnaTrueVertex& vtx){
  //********************************************************************

  Float_t p4v[4];
  Float_t p4l[4];
  Float_t p4n[4];
  
  if (!anaUtils::RetrieveInitialKinematics(vtx, p4v, p4l, p4n, 4))
    return 0.;
  
  return anaUtils::ComputeX(p4v, p4l); 
}
//********************************************************************
Float_t anaUtils::ComputeY(const AnaTrueVertex& vtx){
  //********************************************************************

  Float_t p4v[4];
  Float_t p4l[4];
  Float_t p4n[4];
  
  if (!anaUtils::RetrieveInitialKinematics(vtx, p4v, p4l, p4n, 4))
    return 0.;

  return anaUtils::ComputeY(p4v, p4l); 
}

//********************************************************************
Float_t anaUtils::ComputeW(const AnaTrueVertex& vtx){ 
  //********************************************************************

  Float_t p4v[4];
  Float_t p4l[4];
  Float_t p4n[4];
  
  if (!anaUtils::RetrieveInitialKinematics(vtx, p4v, p4l, p4n, 4))
    return 0.;

  return anaUtils::ComputeW(p4v, p4l, p4n); 
}






