#include "MultiParticleBox.hxx"
#include "PropagationUtils.hxx"



//*******************************************************************************
bool multipart::sortbysecdesc(const std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> > &a, 
      const std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> > &b){ 
//*******************************************************************************
  
  return a.second.first > b.second.first; 
}  


//*******************************************************************************
AnaTrackB* multipart::MultiParticleBox::GetHMPosTPCPion(){
//*******************************************************************************
 
  // Check whether positive pions in TPC exist
  if (nPositivePionTPCtracks == 0)
    return NULL;
  
  
  AnaTrackB* tmpPositivePionTPCtracks[NMAXCANDIDATES];
 
  anaUtils::CopyArray(PositivePionTPCtracks, tmpPositivePionTPCtracks, nPositivePionTPCtracks);
  
  
  // Sort them in the decreasing momentum order
  std::sort(tmpPositivePionTPCtracks, tmpPositivePionTPCtracks + nPositivePionTPCtracks, AnaParticleMomB::CompareMomentum);
 
  return tmpPositivePionTPCtracks[0];
}

//*******************************************************************************
AnaTrackB* multipart::MultiParticleBox::GetHMNegTPCPion(){
//*******************************************************************************

  // Check whether positive pions in TPC exist
  if (nNegativePionTPCtracks == 0)
    return NULL;
  
  AnaTrackB* tmpNegativePionTPCtracks[NMAXCANDIDATES];
 
  anaUtils::CopyArray(NegativePionTPCtracks, tmpNegativePionTPCtracks, nNegativePionTPCtracks);
  
  // Sort them in the decreasing momentum order
  std::sort(tmpNegativePionTPCtracks, tmpNegativePionTPCtracks + nNegativePionTPCtracks, AnaParticleMomB::CompareMomentum);
  
  return tmpNegativePionTPCtracks[0];

}

//*******************************************************************************
AnaTrackB* multipart::MultiParticleBox::GetHMTPCProton(){
//*******************************************************************************
 
  // Check whether positive pions in TPC exist
  if (nProtonTPCtracks == 0)
    return NULL;
  
  AnaTrackB* tmpProtonTPCtracks[NMAXCANDIDATES];
 
  anaUtils::CopyArray(ProtonTPCtracks, tmpProtonTPCtracks, nProtonTPCtracks);
  
  // Sort them in the decreasing momentum order
  std::sort(tmpProtonTPCtracks, tmpProtonTPCtracks + nProtonTPCtracks, AnaParticleMomB::CompareMomentum);
 
  return tmpProtonTPCtracks[0];
}


//*******************************************************************************
AnaTrackB* multipart::MultiParticleBox::GetHMProton(){
//*******************************************************************************

  AnaTrackB* tpcProtonCand = NULL;
  
  AnaTrackB* fgdProtonCand = NULL;
  
  // Check whether positive pions in TPC exist
  if (nProtonTPCtracks == 0 && nProtonFGDtracks == 0)
    return NULL;
  
  if (nProtonTPCtracks > 0){
    AnaTrackB* tmpProtonTPCtracks[NMAXCANDIDATES];
 
    anaUtils::CopyArray(ProtonTPCtracks, tmpProtonTPCtracks, nProtonTPCtracks);
  
    // Sort them in the decreasing momentum order
    std::sort(tmpProtonTPCtracks, tmpProtonTPCtracks + nProtonTPCtracks, AnaParticleMomB::CompareMomentum);
   
    tpcProtonCand = tmpProtonTPCtracks[0];
  }
  
  if (nProtonFGDtracks > 0){
    
    multipart::MultiParticleBox::SortIsoFgdProtonsByVertexMom();
    fgdProtonCand = ProtonFGDtracks[0]; 
    
  }
  
  // Return the one with the largest mom
  if (tpcProtonCand && fgdProtonCand){
    return (tpcProtonCand->Momentum > IsoFgdProtonMomVertex[0]) ? tpcProtonCand : fgdProtonCand;
  }
  else if (tpcProtonCand){
    return tpcProtonCand;
  }
  else if (fgdProtonCand){
    return fgdProtonCand;
  }
  
  return NULL; 
}

//*******************************************************************************
AnaTrackB* multipart::MultiParticleBox::GetHMPion(){
//*******************************************************************************

  AnaTrackB* tpcPosPionCand = NULL;
  
  AnaTrackB* tpcNegPionCand = NULL;
  
  AnaTrackB* tpcPionCand = NULL;
  
  AnaTrackB* fgdPionCand = NULL;

  // HMP
  tpcPosPionCand = GetHMPosTPCPion();
  
  // HMN
  tpcNegPionCand = GetHMNegTPCPion();
  
  
  if (tpcPosPionCand && tpcNegPionCand){
    tpcPionCand = (tpcPosPionCand->Momentum > tpcNegPionCand->Momentum) ? tpcPosPionCand : tpcNegPionCand;  
  }
  else if (tpcPosPionCand){
    tpcPionCand = tpcPosPionCand;
  }
  else if (tpcNegPionCand){
    tpcPionCand = tpcNegPionCand;
  }
  

  // FGD pions
  if (nIsoFGDPiontracks > 0){
       
    multipart::MultiParticleBox::SortIsoFgdPionsByVertexMom();
    
    fgdPionCand = IsoFGDPiontracks[0]; 
  }
  
 
  // Return the one with the largest mom
  if (tpcPionCand && fgdPionCand){
    return (tpcPionCand->Momentum > IsoFgdPionMomVertex[0]) ? tpcPionCand : fgdPionCand;
  }
  else if (tpcPionCand){
    return tpcPionCand;
  }
  else if (fgdPionCand){
    return fgdPionCand;
  }
  
  return NULL; 
}

//*******************************************************************************
AnaTrackB* multipart::MultiParticleBox::GetHMProton(Float_t& momentum, Float_t* dir){
//*******************************************************************************

  momentum = -999;
  
  AnaTrackB* cand = NULL;
  
  AnaTrackB* tpcProtonCand = NULL;
  
  AnaTrackB* fgdProtonCand = NULL;
  
  // Check whether positive pions in TPC exist
  if (nProtonTPCtracks == 0 && nProtonFGDtracks == 0)
    return NULL;
  
  if (nProtonTPCtracks > 0){
    AnaTrackB* tmpProtonTPCtracks[NMAXCANDIDATES];
 
    anaUtils::CopyArray(ProtonTPCtracks, tmpProtonTPCtracks, nProtonTPCtracks);
  
    // Sort them in the decreasing momentum order
    std::sort(tmpProtonTPCtracks, tmpProtonTPCtracks + nProtonTPCtracks, AnaParticleMomB::CompareMomentum);
   
    tpcProtonCand = tmpProtonTPCtracks[0];
  }
  
  if (nProtonFGDtracks > 0){
    
    multipart::MultiParticleBox::SortIsoFgdProtonsByVertexMom();
    fgdProtonCand = ProtonFGDtracks[0]; 
    
  }
  
  // Return the one with the largest mom
  if (tpcProtonCand && fgdProtonCand){
    cand = tpcProtonCand->Momentum > IsoFgdProtonMomVertex[0] ? tpcProtonCand : fgdProtonCand;
    
    if (cand == tpcProtonCand){
      momentum = cand->Momentum;
      anaUtils::CopyArray(tpcProtonCand->DirectionStart, dir, 3);
      
    }
    else{
      momentum = IsoFgdProtonMomVertex[0];
      anaUtils::CopyArray(IsoFgdProtonDirVertex[0], dir, 3);
    }
    return cand;
  }
  else if (tpcProtonCand){
    momentum = tpcProtonCand->Momentum;
    anaUtils::CopyArray(tpcProtonCand->DirectionStart, dir, 3);
    return tpcProtonCand;
  }
  else if (fgdProtonCand){
    momentum = IsoFgdProtonMomVertex[0];
    anaUtils::CopyArray(IsoFgdProtonDirVertex[0], dir, 3);
    return fgdProtonCand;
  }
  
  return NULL; 

}

//*******************************************************************************
AnaTrackB* multipart::MultiParticleBox::GetHMPion(Float_t& momentum, Float_t* dir){
//*******************************************************************************

  AnaTrackB* cand = NULL;
  
  momentum = -999;
  
  AnaTrackB* tpcPosPionCand = NULL;
  
  AnaTrackB* tpcNegPionCand = NULL;
  
  AnaTrackB* tpcPionCand = NULL;
  
  AnaTrackB* fgdPionCand = NULL;

  // HMP
  tpcPosPionCand = GetHMPosTPCPion();
  
  // HMN
  tpcNegPionCand = GetHMNegTPCPion();
  
  
  if (tpcPosPionCand && tpcNegPionCand){
    tpcPionCand = (tpcPosPionCand->Momentum > tpcNegPionCand->Momentum) ? tpcPosPionCand : tpcNegPionCand;  
  }
  else if (tpcPosPionCand){
    tpcPionCand = tpcPosPionCand;
  }
  else if (tpcNegPionCand){
    tpcPionCand = tpcNegPionCand;
  }
  

  // FGD pions
  if (nIsoFGDPiontracks > 0){
       
    multipart::MultiParticleBox::SortIsoFgdPionsByVertexMom();
    
    fgdPionCand = IsoFGDPiontracks[0]; 
  
  } 
 
  // Return the one with the largest mom
  if (tpcPionCand && fgdPionCand){
    
    cand = tpcPionCand->Momentum > IsoFgdPionMomVertex[0] ? tpcPionCand : fgdPionCand;
    
    if (cand == tpcPionCand){
      momentum = tpcPionCand->Momentum;
      anaUtils::CopyArray(tpcPionCand->DirectionStart, dir, 3);
    }
    else{
      momentum = IsoFgdPionMomVertex[0];
      anaUtils::CopyArray(IsoFgdPionDirVertex[0], dir, 3);
    }
    
    return cand; 
  }
  else if (tpcPionCand){
    momentum = tpcPionCand->Momentum;
    anaUtils::CopyArray(tpcPionCand->DirectionStart, dir, 3);
    return tpcPionCand;
  }
  else if (fgdPionCand){
    momentum = IsoFgdPionMomVertex[0];
    anaUtils::CopyArray(IsoFgdPionDirVertex[0], dir, 3);
    return fgdPionCand;
  }
  
  return NULL; 
}




//*******************************************************************************
SelTopoId::SelTopoPionEnum multipart::MultiParticleBox::GetPionTopo(){
//*******************************************************************************

  if (nNegativePionTPCtracks > 0 || nPositivePionTPCtracks > 0){
    return SelTopoId::kTPCPion;
  }
  else if (nIsoFGDPiontracks > 0){
    return SelTopoId::kFGDPion;
  }
  else if (nMichelElectrons > 0){
    return SelTopoId::kMEPion;
  }

  return SelTopoId::kPionUnassigned;
  
}

//*******************************************************************************
SelTopoId::SelTopoProtonEnum multipart::MultiParticleBox::GetProtonTopo(){
//*******************************************************************************

  if (nProtonTPCtracks > 0 && nProtonFGDtracks > 0){
    return SelTopoId::kTPCAndFgdProtons;
  } 
  else if (nProtonTPCtracks > 0){
    return SelTopoId::kTPCProton;
  } 
  else if (nProtonFGDtracks > 0){
    return SelTopoId::kFGDProton;
  }
  
  return SelTopoId::kProtonUnassigned;

}

//*******************************************************************************
void multipart::MultiParticleBox::FillFgdIsoPionsKinematicsVertex(){
//*******************************************************************************
  
  if (!Vertex){
    return;
  }
  for (int i = 0; i < nIsoFGDPiontracks; i++){
    if (!IsoFGDPiontracks[i]){
      continue;
    }
    
    // Get the closest pos to the vertex 
    if (anaUtils::GetSeparationSquared(Vertex->Position, IsoFGDPiontracks[i]->PositionStart) < 
        anaUtils::GetSeparationSquared(Vertex->Position, IsoFGDPiontracks[i]->PositionEnd)){ 
      // Correct to the vertex
      IsoFgdPionMomVertex[i] = propUtils::CorrectMomRangeToVertex(*Vertex, *IsoFGDPiontracks[i], ParticleId::kPiPosPDG, si_syst::kStart);
           
      anaUtils::CopyArray(IsoFGDPiontracks[i]->DirectionStart, IsoFgdPionDirVertex[i], 3);
    }
    else{
    
      // Correct to the vertex
      IsoFgdPionMomVertex[i] = propUtils::CorrectMomRangeToVertex(*Vertex, *IsoFGDPiontracks[i], ParticleId::kPiPosPDG, si_syst::kEnd);
      for (int j = 0; j < 3; j ++){
        IsoFgdPionDirVertex[i][j] = -1. * IsoFGDPiontracks[i]->DirectionEnd[j];
      }
    }
  }  
}

//*******************************************************************************
void multipart::MultiParticleBox::FillFgdIsoProtonsKinematicsVertex(){
//*******************************************************************************

  if (!Vertex){
    return;
  }
  
  for (int i = 0; i < nProtonFGDtracks; i++){
    if (!ProtonFGDtracks[i]){
      continue;
    }
  
    // Get the closest pos to the vertex 
    if (anaUtils::GetSeparationSquared(Vertex->Position, ProtonFGDtracks[i]->PositionStart) < 
        anaUtils::GetSeparationSquared(Vertex->Position, ProtonFGDtracks[i]->PositionEnd)){ 
      // Correct to the vertex
      IsoFgdProtonMomVertex[i] = propUtils::CorrectMomRangeToVertex(*Vertex, *ProtonFGDtracks[i], ParticleId::kProtonPDG, si_syst::kStart);
      // Keep the direction
      anaUtils::CopyArray(ProtonFGDtracks[i]->DirectionStart, IsoFgdProtonDirVertex[i], 3);
    }
    else{
    
      // Correct to the vertex
      IsoFgdProtonMomVertex[i] = propUtils::CorrectMomRangeToVertex(*Vertex, *ProtonFGDtracks[i], ParticleId::kProtonPDG, si_syst::kEnd);
      for (int j = 0; j < 3; j ++){
        IsoFgdProtonDirVertex[i][j] = -1. * ProtonFGDtracks[i]->DirectionEnd[j];
    }
    }
  }
  
}

//*******************************************************************************
void multipart::MultiParticleBox::SortIsoFgdProtonsByVertexMom(){
//*******************************************************************************
  if (nProtonFGDtracks == 0)
    return;
  
  
  // Create a pair 
  std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> >* track_kin_pair_tmp = 
    new std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> >[nProtonFGDtracks];
  
  // Fill the pairs
  for (int i = 0; i < nProtonFGDtracks; i++){
   
    std::pair<Float_t, Float_t*> pair_kin_tmp = std::make_pair(IsoFgdProtonMomVertex[i], IsoFgdProtonDirVertex[i]); 
    track_kin_pair_tmp[i] = std::make_pair(ProtonFGDtracks[i], pair_kin_tmp);  
  }
  
  std::sort(track_kin_pair_tmp, track_kin_pair_tmp + nProtonFGDtracks, multipart::sortbysecdesc); 
  
  for (int i = 0; i < nProtonFGDtracks; i++){
   
    ProtonFGDtracks[i] = track_kin_pair_tmp[i].first;
    
    IsoFgdProtonMomVertex[i] = track_kin_pair_tmp[i].second.first;
      
    anaUtils::CopyArray(track_kin_pair_tmp[i].second.second, IsoFgdProtonDirVertex[i], 3);
  }
  delete [] track_kin_pair_tmp; 
  
}

//*******************************************************************************
void multipart::MultiParticleBox::SortIsoFgdPionsByVertexMom(){
//*******************************************************************************
  if (nIsoFGDPiontracks == 0)
    return;
  
  
  // Create a pair 
  std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> >* track_kin_pair_tmp = 
    new std::pair<AnaTrackB*, std::pair<Float_t, Float_t*> >[nIsoFGDPiontracks];
  
  // Fill the pairs
  for (int i = 0; i < nIsoFGDPiontracks; i++){
   
    std::pair<Float_t, Float_t*> pair_kin_tmp = std::make_pair(IsoFgdPionMomVertex[i], IsoFgdPionDirVertex[i]); 
    track_kin_pair_tmp[i] = std::make_pair(IsoFGDPiontracks[i], pair_kin_tmp);  
  }
  
  std::sort(track_kin_pair_tmp, track_kin_pair_tmp + nIsoFGDPiontracks, multipart::sortbysecdesc); 
  
  for (int i = 0; i < nIsoFGDPiontracks; i++){
   
    IsoFGDPiontracks[i] = track_kin_pair_tmp[i].first;
    
    IsoFgdPionMomVertex[i] = track_kin_pair_tmp[i].second.first;
    
    anaUtils::CopyArray(track_kin_pair_tmp[i].second.second, IsoFgdPionDirVertex[i], 3);
  
  }
  delete [] track_kin_pair_tmp; 
  
  
}





