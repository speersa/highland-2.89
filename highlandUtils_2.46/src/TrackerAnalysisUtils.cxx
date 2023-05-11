#include "TrackerAnalysisUtils.hxx"
#include <TMath.h>
#include <math.h>
#include "ConstituentsUtils.hxx" 

// ********************************************************************
bool anaUtils::IsValidFgdDetLayer(Float_t layer){
  // ********************************************************************

  return (layer > -1 && layer == std::floor(layer));
}


// ********************************************************************
Float_t anaUtils::GetFGDLayer(const Float_t* pos, SubDetId::SubDetEnum det){
  // ********************************************************************

  if (!SubDetId::IsFGDDetector(det) && det != SubDetId::kFGD){ 
    std::cerr << " anaUtils::GetFGDLayer(): not an FGD detector " << det << std::endl; 
    exit(1);
  }
  
  if (!anaUtils::InDetVolume(det, pos))
    return -1;
  

  Float_t initZ   = 0;
  Float_t finalZ  = 0;
  Float_t barCenter[30];

  // FGD1 or FGD
  if (det == SubDetId::kFGD1 || det == SubDetId::kFGD){ 
    initZ   = 0;
    finalZ  = 0;

    for ( int i = 0; i < 30; i++) { 
      barCenter[i] = DetDef::fgd1BarCenter[i];
      if (i == 0) initZ = barCenter[0 ]- (DetDef::fgdXYBarWidth / 2) - DetDef::fgdXYGlueWidth - DetDef::fgdXYSkinWidth - DetDef::fgdXYAirWidth;
      else initZ = finalZ;
      if      (i%2 == 0) finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + (DetDef::fgdXYMiddleGlueWidth / 2);
      else if (i%2 == 1) finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + DetDef::fgdXYGlueWidth+DetDef::fgdXYSkinWidth + (DetDef::fgdXYAirWidth / 2);
      if (i == 29) finalZ += DetDef::fgdXYAirWidth;
      if (pos[2] > initZ && pos[2] < finalZ) return i;

    }  
  }
  // FGD2 or FGD
  if (det == SubDetId::kFGD2 || det == SubDetId::kFGD){
    initZ   = 0;
    finalZ  = 0;

    // XY modules
    for ( int i = 0; i < 14; i++) {
      barCenter[i] = DetDef::fgd2BarCenter[i];

      if (i%2 == 0){   
        if ( i==0 ) initZ = barCenter[0] - (DetDef::fgdXYBarWidth / 2) - DetDef::fgdXYGlueWidth - DetDef::fgdXYSkinWidth;
        else initZ = barCenter[i]  - (DetDef::fgdXYBarWidth / 2) - DetDef::fgdXYGlueWidth - DetDef::fgdXYSkinWidth;
        finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + (DetDef::fgdXYMiddleGlueWidth / 2);
      }
      else if (i%2 == 1) {
        initZ = barCenter[i]  - (DetDef::fgdXYBarWidth / 2) - (DetDef::fgdXYMiddleGlueWidth / 2);
        finalZ = barCenter[i] + (DetDef::fgdXYBarWidth / 2) + DetDef::fgdXYGlueWidth + DetDef::fgdXYSkinWidth;
      }

      if (pos[2]>initZ && pos[2]<finalZ) return i;
    }

    // Water modules   
    for ( int i = 0; i < 6; i++) {
      barCenter[i] = DetDef::fgd2WaterCenter[i];
      initZ   = barCenter[i] - (DetDef::fgdXYModuleWidth / 2) -  DetDef::fgdXYAirWidth;   
      finalZ  = barCenter[i] + (DetDef::fgdXYModuleWidth / 2) +  DetDef::fgdWaterAirWidth;
      if (pos[2]>initZ && pos[2]<finalZ) return i * 2 + 1.5;
    }

  }

  return -1;

}

//********************************************************************
Float_t anaUtils::GetFGD2LayerCC0PiXSec(const Float_t* pos){
  //********************************************************************

  Float_t Layer = -1;
  
  if (!anaUtils::InDetVolume(SubDetId::kFGD2, pos))
    return Layer;

  if   (pos[2]>=1474     && pos[2]<1484)   {Layer=0.;}//X
  else if(pos[2]>=1484   && pos[2]<1494)   {Layer=1.;}//Y

  else if(pos[2]>=1494   && pos[2]<1526)   {Layer=1.5;}//Water

  else if(pos[2]>=1526   && pos[2]<1536)   {Layer=2.;}//X
  else if(pos[2]>=1536   && pos[2]<1546)   {Layer = 3.;}//Y
  else if(pos[2]>=1546   && pos[2]<1578.5) {Layer = 3.5;}//Water

  else if(pos[2]>=1578.5 && pos[2]<1588.5) {Layer = 4.;}//X
  else if(pos[2]>=1588.5 && pos[2]<1598.5) {Layer = 5.;}//Y
  else if(pos[2]>=1598.5 && pos[2]<1630.5) {Layer = 5.5;}//Water

  else if(pos[2]>=1630.5 && pos[2]<1640.5) {Layer = 6.;}//X
  else if(pos[2]>=1640.5 && pos[2]<1650.5) {Layer = 7.;}//Y
  else if(pos[2]>=1650.5 && pos[2]<1683)   {Layer = 7.5;}//Water

  else if(pos[2]>=1683   && pos[2]<1693)   {Layer = 8.;}//X
  else if(pos[2]>=1693   && pos[2]<1703)   {Layer = 9.;}//Y
  else if(pos[2]>=1703   && pos[2]<1735)   {Layer = 9.5;}//Water

  else if(pos[2]>=1735   && pos[2]<1745)   {Layer = 10.;}//X
  else if(pos[2]>=1745   && pos[2]<1755)   {Layer = 11.;}//Y
  else if(pos[2]>=1755   && pos[2]<1787.5) {Layer = 11.5;}//Water

  else if(pos[2]>=1787.5 && pos[2]<1797.5) {Layer = 12.;}//X
  else if(pos[2]>=1797.5 && pos[2]<1807.5) {Layer = 13.;}//Y
  
  
  return Layer;

}

// ********************************************************************
Float_t anaUtils::GetClosestFgdDetLayer(const Float_t* pos, Float_t& distZ, SubDetId::SubDetEnum det, Float_t step){
  // ********************************************************************

  if (!SubDetId::IsFGDDetector(det) && det != SubDetId::kFGD){ 
    std::cerr << " anaUtils::GetClosestFgdDetLayer(): not an FGD detector " << det << std::endl; 
    exit(1);
  }

  if (step == 0){
    std::cerr << " anaUtils::GetClosestFgdDetLayer(): zero step " << std::endl; 
    exit(1);
  }
  
  Float_t Layer = -1;
  
  distZ = 0.;
  
  if (!anaUtils::InDetVolume(det, pos))
    return Layer;
  
  Float_t dist_pos = 0.;
  Float_t dist_neg = 0.;
  
  Float_t Layer_pos = -1;
  Float_t Layer_neg = -1;
  
  Float_t pos_tmp[3];
  anaUtils::CopyArray(pos, pos_tmp, 3);
  
  // Go in positive Z
  while (anaUtils::InDetVolume(det, pos_tmp)){
    
    Layer_pos = anaUtils::GetFGDLayer(pos_tmp, det);
    
    // Break if there is a valid layer 
    if (anaUtils::IsValidFgdDetLayer(Layer_pos))
      break;
    
    pos_tmp[2] += fabs(step);
    dist_pos   += fabs(step);
  }
  
  // Go back to initial pos
  anaUtils::CopyArray(pos, pos_tmp, 3);
  
  // Go in negative Z
  while (anaUtils::InDetVolume(det, pos_tmp)){
    
    Layer_neg = anaUtils::GetFGDLayer(pos_tmp, det);
    
    // Break if there is a valid layer 
    if (anaUtils::IsValidFgdDetLayer(Layer_neg))
      break;
    
    pos_tmp[2] += -fabs(step);
    dist_neg   += -fabs(step);
  }
  
 
  // Return the layer
  // Both valid
  if (anaUtils::IsValidFgdDetLayer(Layer_pos) && anaUtils::IsValidFgdDetLayer(Layer_neg)){
    
    // Compare the distance
    if (fabs(dist_pos) < fabs(dist_neg)){
      distZ = dist_pos;
      return Layer_pos;
    }
    else{
      distZ = dist_neg;
      return Layer_neg;
    }
  }
  // Pos valid
  else if (anaUtils::IsValidFgdDetLayer(Layer_pos)){
    distZ = dist_pos;
    return Layer_pos;
  }
  // Neg valid
  else if (anaUtils::IsValidFgdDetLayer(Layer_neg)){
    distZ = dist_neg;
    return Layer_neg;
  } 
  
  // No valid
  return Layer;
  
}

// ********************************************************************
Float_t anaUtils::GetClosestFgd2DetLayerCC0PiXSec(const Float_t* pos, Float_t& distZ, Float_t step){
  // ********************************************************************

  if (step == 0){
    std::cerr << " anaUtils::GetClosestFgd2DetLayerCC0PiXSec(): zero step " << std::endl; 
    exit(1);
  }
  
  Float_t Layer = -1;
  
  distZ = 0.;
  
  if (!anaUtils::InDetVolume(SubDetId::kFGD2, pos))
    return Layer;
  
  Float_t dist_pos = 0.;
  Float_t dist_neg = 0.;
  
  Float_t Layer_pos = -1;
  Float_t Layer_neg = -1;
  
  Float_t pos_tmp[3];
  anaUtils::CopyArray(pos, pos_tmp, 3);
  
  // Go in positive Z
  while (anaUtils::InDetVolume(SubDetId::kFGD2, pos_tmp)){
    
    Layer_pos = anaUtils::GetFGD2LayerCC0PiXSec(pos_tmp);
    
    // Break if there is a valid layer 
    if (anaUtils::IsValidFgdDetLayer(Layer_pos))
      break;
    
    pos_tmp[2] += fabs(step);
    dist_pos   += fabs(step);
  }
  
  // Go back to initial pos
  anaUtils::CopyArray(pos, pos_tmp, 3);
  
  // Go in negative Z
  while (anaUtils::InDetVolume(SubDetId::kFGD2, pos_tmp)){
    
    Layer_neg = anaUtils::GetFGD2LayerCC0PiXSec(pos_tmp);
    
    // Break if there is a valid layer 
    if (anaUtils::IsValidFgdDetLayer(Layer_neg))
      break;
    
    pos_tmp[2] += -fabs(step);
    dist_neg   += -fabs(step);
  }
   
  // Return the layer
  // Both valid
  if (anaUtils::IsValidFgdDetLayer(Layer_pos) && anaUtils::IsValidFgdDetLayer(Layer_neg)){
    // Compare the distance
    if (fabs(dist_pos) < fabs(dist_neg)){
      distZ = dist_pos;
      return Layer_pos;
    }
    else{
      distZ = dist_neg;
      return Layer_neg;
    }
  }
  // Pos valid
  else if (anaUtils::IsValidFgdDetLayer(Layer_pos)){
    distZ = dist_pos;
    return Layer_pos;
  }
  // Neg valid
  else if (anaUtils::IsValidFgdDetLayer(Layer_neg)){
    distZ = dist_neg;
    return Layer_neg;
  } 
  
  // No valid
  return Layer;
  
}






// ********************************************************************
bool anaUtils::IsFgdXLayer(Float_t layer){
// ********************************************************************

  if (layer < 0) return false;
  
  // X are even ones (starting from zero)
  
  // Ignore the water 
  if (layer != std::floor(layer)) return false;
   
  return (int(layer) % 2 == 0);
  
  
}

// ********************************************************************
bool anaUtils::IsFgdYLayer(Float_t layer){
// ********************************************************************

  if (layer < 0) return false;
  
  // Y are odd ones 
  
  // Ignore the water 
  if (layer != std::floor(layer)) return false;
    
  return (int(layer) % 2 == 1);

}

// ********************************************************************
bool anaUtils::IsFgdWaterLayer(Float_t layer){
// ********************************************************************

  if (layer < 0) return false;

  if (std::fmod(layer, 1.0) == 0.5) return true;
  
  return false;
  
}

// ********************************************************************
bool anaUtils::IsFgdXLayer(const Float_t* pos, SubDetId::SubDetEnum det){
// ********************************************************************

  Float_t layer = anaUtils::GetFGDLayer(pos, det);
  return anaUtils::IsFgdXLayer(layer);
  
}

// ********************************************************************
bool anaUtils::IsFgdYLayer(const Float_t* pos, SubDetId::SubDetEnum det){
// ********************************************************************

  Float_t layer = anaUtils::GetFGDLayer(pos, det);
  return anaUtils::IsFgdYLayer(layer);

}

// ********************************************************************
bool anaUtils::IsFgdWaterLayer(const Float_t* pos){
// ********************************************************************
  
  Float_t layer = anaUtils::GetFGDLayer(pos);
  return anaUtils::IsFgdWaterLayer(layer);
  
}

// ********************************************************************
Int_t anaUtils::IsFgdBwdMigrated(const AnaParticleB& track, SubDetId::SubDetEnum det){
// ********************************************************************
  
  // set to undefined
  Int_t isBwdMigrated = -1;
  
  if (!track.GetTrueParticle()) return isBwdMigrated;
  
  Float_t selmu_truezcth = track.GetTrueParticle()->Direction[2];
  
  Float_t dist = - 999.;
  
  // For reconstructed layer use the closest one
  Float_t RecoLayer = anaUtils::GetClosestFgdDetLayer(track.PositionStart,  dist, det);

  Float_t TrueLayer = anaUtils::GetFGDLayer(track.GetTrueParticle()->Position, det);
  
  // Check one has a valid layer
  if (RecoLayer < 0 || TrueLayer < 0)
    return isBwdMigrated;
  
  // Non-migrated
  isBwdMigrated = 0;

  if ( (TrueLayer - RecoLayer) >= 0.5 && selmu_truezcth > 0) isBwdMigrated = 1;
  if ( (RecoLayer - TrueLayer) >= 0.5 && selmu_truezcth < 0) isBwdMigrated = 1;
  
  return isBwdMigrated; 
}

// ********************************************************************
Int_t anaUtils::IsFgdBwdMigrated(const AnaVertexB& vertex, SubDetId::SubDetEnum det){
// ********************************************************************
  Int_t isBwdMigrated = -1;

  if (vertex.nParticles == 0 || !vertex.Particles[0]) return isBwdMigrated;
  
  return anaUtils::IsFgdBwdMigrated(*vertex.Particles[0], det);
  
  return isBwdMigrated; 
}

