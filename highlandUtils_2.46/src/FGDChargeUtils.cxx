#include "FGDChargeUtils.hxx"
#include "Parameters.hxx"
#include "TMath.h"

// ********************************************************************
anaUtils::FGDChargeCorrector::FGDChargeCorrector(){
  // ********************************************************************

  // Read and set parameters
  _extraFiberLength = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.WLS.MPPCtoBarEdgeDistance");
  _barLength        = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.WLS.BarLength");

  _attParams[0] = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.WLS.LongComponentFraction");
  _attParams[1] = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.WLS.LongAttLength");
  _attParams[2] = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.WLS.ShortAttLength");
  _attParams[3] = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.WLS.BarLightDecayLength");
  _attParams[4] = _barLength; 
  _attParams[5] = _extraFiberLength;

  _birksC = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.Scintillator.BirksConstant");

  _peuMeV = (Float_t)ND::params().GetParameterD("highlandUtils.FGD.Scintillator.peuMeV");
}

// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetBirksCorrection(const Float_t& dE,
    const Float_t& dX) const{
  // ********************************************************************

  // The Birk's correction was tested using M11 data by P. Kitching, 
  // documented in the FGD NIM paper, up to ~10 MIPs of charge deposit.
  // This equates to ~20MeV deposited.
  // As birksC * de/dx approaches and exceeds 1 the Birk's correction gets un-physically large and negative
  // Capping the de at 30 MeV prevents this, and still applies some correction to the very high charge hits.
  // This should probably be studied in more detail.

  Float_t dE_tmp = dE;

  // Return negative value in case something is wrong
  if (dX <= 0.){
    return -999.;
  }

  if (dE_tmp > 30.){
    dE_tmp = 30.;
  } 

  return 1. / (1. - _birksC * dE_tmp / dX);

}

// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetBirksCorrection(const Float_t& dE,
    const Float_t& dX, const Float_t& cutoff) const{
  // ********************************************************************

  // The Birk's correction was tested using M11 data by P. Kitching, 
  // documented in the FGD NIM paper, up to ~10 MIPs of charge deposit.
  // This equates to ~20MeV deposited.
  // As birksC * de/dx approaches and exceeds 1 the Birk's correction gets un-physically large and negative
  // Capping the de at 30 MeV prevents this, and still applies some correction to the very high charge hits.
  // This should probably be studied in more detail.

  Float_t dE_tmp = dE;

  // Return negative value in case something is wrong
  if (dX <= 0.){
    return -999.;
  }

  if (dE_tmp > 30.){
    dE_tmp = 30.;
  } 

  if ((dE_tmp / dX) > cutoff) {
    return 1. / (1. - _birksC * cutoff);
  }
  else {
    return 1. / (1. - _birksC * dE_tmp / dX);
  }

}


// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetEnergy(const Float_t& charge) const{
  // ********************************************************************
  return charge / _peuMeV;
}

// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetEnergy(const AnaHit& hit) const{
  // ********************************************************************
  return GetEnergy(hit.Charge);
}

// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetAttenuation(const Float_t& pathlength) const{
  // ********************************************************************

  Float_t attenuation =(_attParams[0] * exp(-(pathlength + _attParams[5]) / _attParams[1]) + 
      (1. - _attParams[0]) * exp(-(pathlength + _attParams[5]) / _attParams[2])) *
    (1. - 0.5 * (exp(-_attParams[3] * (_attParams[4] - pathlength)) + exp(-_attParams[3] * pathlength)));   

  //Return negative value in case something is wrong
  if (attenuation <= 0.){
    return -1.;
  }

  return attenuation;
}

// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetAttenuationCorrection(const Float_t& pathlength) const{ 
  // ********************************************************************

  Float_t attenuation = GetAttenuation(pathlength);

  //Return negative value in case something is wrong
  if (attenuation < 0.){
    return -1.;
  }

  return 1. / attenuation;
}

// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetPathLengthInFiber(const Float_t* pos, const AnaHit::TypeEnum& type) const{
  // ********************************************************************

  // Return negative value in case something is wrong
  if (!IsValidHitType(type)){
    return -999.;
  }

  Float_t center = 0.;

  Float_t mppcPos = (type==AnaHit::kYZ) ? center - _barLength / 2. : center + _barLength / 2.;

  Float_t hitPos = (type==AnaHit::kYZ) ? pos[0] : pos[1];

  return TMath::Abs(mppcPos - hitPos);      
}

// ********************************************************************
Float_t anaUtils::FGDChargeCorrector::GetPathLengthInFiber(const AnaHit& hit, const Float_t* pos) const{
  // ********************************************************************
  return GetPathLengthInFiber(pos, static_cast<AnaHit::TypeEnum>(hit.Type));
}

// ********************************************************************  
Float_t anaUtils::FGDChargeCorrector::GetFiberCorrectedEnergy(const Float_t& charge, 
    const Float_t* pos, 
    const AnaHit::TypeEnum& type) const{
  // ********************************************************************

  // Return negative value in case something is wrong
  if (!IsValidHitType(type)){
    return -999.;
  }


  Float_t pathlength  = GetPathLengthInFiber(pos, type);
  Float_t charge_corr = charge * GetAttenuationCorrection(pathlength);

  return GetEnergy(charge_corr);

}

// ********************************************************************  
Float_t anaUtils::FGDChargeCorrector::GetFiberCorrectedEnergy(const AnaHit& hit, 
    const Float_t* pos) const{
  // ********************************************************************
  return GetFiberCorrectedEnergy(hit.Charge, pos, static_cast<AnaHit::TypeEnum>(hit.Type));  
}

// ********************************************************************  
Float_t anaUtils::FGDChargeCorrector::GetCalibratedEDeposit(const Float_t& charge, 
    const Float_t* pos, const Float_t& dX, const AnaHit::TypeEnum& type) const{
  // ********************************************************************  
 
  
  // Return negative value in case something is wrong
  if (!IsValidHitType(type)){
    return -999.;
  }

  
  Float_t EDeposit = GetFiberCorrectedEnergy(charge, pos, type);

  Float_t corrBirks = GetBirksCorrection(EDeposit, dX);

  return corrBirks * EDeposit;

}

// ********************************************************************  
Float_t anaUtils::FGDChargeCorrector::GetCalibratedEDeposit(const Float_t& charge, 
    const Float_t* pos, const Float_t& dX, const AnaHit::TypeEnum& type, const Float_t& cutoff) const{
  // ********************************************************************  
 
  
  // Return negative value in case something is wrong
  if (!IsValidHitType(type)){
    return -999.;
  }

  
  Float_t EDeposit = GetFiberCorrectedEnergy(charge, pos, type);

  Float_t corrBirks = GetBirksCorrection(EDeposit, dX, cutoff);

  return corrBirks * EDeposit;

}

// ********************************************************************  
Float_t anaUtils::FGDChargeCorrector::GetCalibratedEDeposit(const AnaHit& hit, 
    const Float_t* pos, const Float_t& dX) const{
  // ********************************************************************  

  return GetCalibratedEDeposit(hit.Charge, pos, dX, static_cast<AnaHit::TypeEnum>(hit.Type));

}

// ********************************************************************  
Float_t anaUtils::FGDChargeCorrector::GetCalibratedEDeposit(const AnaHit& hit, 
    const Float_t* pos, const Float_t& dX, const Float_t& cutoff) const{
  // ********************************************************************  

  return GetCalibratedEDeposit(hit.Charge, pos, dX, static_cast<AnaHit::TypeEnum>(hit.Type), cutoff);

}

//********************************************************************
bool anaUtils::FGDChargeCorrector::IsValidHitType(const AnaHit::TypeEnum& type) const{
  //********************************************************************

  if (type != AnaHit::kXZ && type != AnaHit::kYZ){
    return false;
  }

  return true;
}
