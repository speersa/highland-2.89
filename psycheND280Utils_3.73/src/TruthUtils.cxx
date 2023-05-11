#include "TruthUtils.hxx"
#include "ConstituentsUtils.hxx"


//**************************************************
Int_t anaUtils::GetNMichelElectrons(const AnaTrueVertexB& trueVertex, SubDetId::SubDetEnum det){
  //**************************************************

  // out of FV
  if ( ! InFiducialVolume(det, trueVertex.Position)) return -999;

  /// particles coming out the vertex
  Int_t NMich=0;

  for (int tit = 0; tit < trueVertex.nTrueParticles; tit++) {
    AnaTrueParticleB* true_track = trueVertex.TrueParticles[tit];

    //if not a pi+/-, a e+/-, a mu+/-
    if( abs(true_track->GParentPDG)!=211) continue;
    if( abs(true_track->ParentPDG)!=13  ) continue;
    if( abs(true_track->PDG)!=11  )       continue;

    NMich++;    
  }

  //  std::cout<<" nb of michel electrons "<<NMich << " " << trueVertex.nTrueParticles <<std::endl;

  return  NMich;
}

//**************************************************
Int_t anaUtils::GetNMichelElectronsAlt(const AnaTrueVertexB& trueVertex, SubDetId::SubDetEnum det){
  //**************************************************

  ///This looks for Michel candidates in the given subdetector coming from a given true vertex
  ///Note that the Michels could also in principle come from other vertices (pileup), so you may want to loop over all vertices or just all tracks in the event if you want to study the effects of pileup Michel clusters.

  std::cout <<"GetNMichelElectronsAlt: This function is still being tested. Use with caution"<<std::endl;

  /// particles coming out the vertex
  std::vector<int> parIDs;
  Int_t NMich=0;


  ///Loop over true particles attached to the vertex
  for (int tit = 0; tit < trueVertex.nTrueParticles; tit++) {

    //Particle originates in the subdetector
    AnaTrueParticleB* true_track = trueVertex.TrueParticles[tit];
    if ( ! InDetVolume(det, true_track->Position)) continue;

    //Particle is an e-(+) with mu-(+) parent
    if( !(true_track->ParentPDG==13&&true_track->PDG==11) && !(true_track->ParentPDG==-13&&true_track->PDG==-11 )) continue;

    Int_t parID = true_track->ParentID;
    //Michel candidate has not already been found for this parent particle
    if (find(parIDs.begin(),parIDs.end(),parID)!= parIDs.end()) continue;
    AnaTrueParticleB* parent = NULL;
    //Retrieve parent info
    for (int j = 0; j < trueVertex.nTrueParticles; j++)
    {
      if (trueVertex.TrueParticles[j]->ID == parID){
        parent = trueVertex.TrueParticles[j];
        break;
      }

    }

    if (parent == NULL) std::cout <<"Can't find Michel parent in vertex"<<std::endl;//Shouldn't ever be called
    else{ 
      Float_t* pos = true_track->Position;
      Float_t* parpos = parent->PositionEnd;
      Float_t dt = pos[3] - parpos[3];
      //      Float_t dx = sqrt( pow(pos[0]-parpos[0],2)+pow(pos[1]-parpos[1],2) + pow(pos[2]-parpos[2],2)  ) ;
      //Decay candidate occurs at the same time or after the end time of the parent
      if (dt>=0)
      {  
        parIDs.push_back(parID);
        NMich++;
      }//dt cut

    }//else (parent found)
  }//Loop over all particles in vertex

  //  std::cout<<" nb of michel electrons "<<NMich << " " << trueVertex.nTrueParticles <<std::endl;
  //


  return  NMich;
}

//**************************************************
Float_t anaUtils::GetTrueLinearLengthInTPC(const AnaTrueParticleB& trueTrack, Float_t& distz){
  //**************************************************

  Float_t dist = -9999999;
  distz = -999;
  for (Int_t idet = 0; idet < trueTrack.nDetCrossings; idet++) {
    //i.e crossing the active part of the tpc
    if (!trueTrack.DetCrossings[idet]->Detector)
      continue;
    if (SubDetId::GetDetectorUsed(trueTrack.DetCrossings[idet]->Detector, SubDetId::kTPC) && trueTrack.DetCrossings[idet]->InActive) {
      Float_t dist_temp = anaUtils::GetSeparationSquared(trueTrack.DetCrossings[idet]->ExitPosition, trueTrack.DetCrossings[idet]->EntrancePosition);
      Float_t distz_temp = fabs(trueTrack.DetCrossings[idet]->ExitPosition[2] - trueTrack.DetCrossings[idet]->EntrancePosition[2]);
      if (dist_temp > dist)
        dist = dist_temp;
      if (distz_temp > distz)
        distz = distz_temp;

    }
  }

  return sqrt(dist);
}

//********************************************************************
int anaUtils::GetAllChargedTrajsInFgdECalInBunch(const AnaEventB& event, AnaTrueParticleB* outTraj[], SubDetId::SubDetEnum det){
  //********************************************************************
  int count = 0;

  if (!SubDetId::IsFGDDetector(det))
    return false;

  AnaTrueParticleB* tracks[NMAXTRUEPARTICLES];
  int ntracks = anaUtils::GetAllChargedTrajInBunch(event, tracks);
  if((UInt_t)ntracks>NMAXTRUEPARTICLES) ntracks = NMAXTRUEPARTICLES;

  for (int i=0; i<ntracks; i++){
    AnaTrueParticleB* track = tracks[i];
    if (!track) continue;

    //should satisfy some minimum criteria in FGD and ECal
    if (anaUtils::TrueParticleEntersDet(track, det) && anaUtils::TrueParticleEntersDet(track, SubDetId::kTECAL) && !anaUtils::TrueParticleCrossesTPC(track))
      outTraj[count++] = track;

  }

  return count;
}


//********************************************************************
int anaUtils::GetAllTrajsInECalInBunch(const AnaEventB& event, AnaTrueParticleB* outTraj[]){
  //********************************************************************
  int count = 0;


  for(Int_t i = 0; i < event.nTrueParticles;i++){

    AnaTrueParticleB* track = event.TrueParticles[i];

    if (!track) continue;

    if(!track->TrueVertex) continue;
    if(track->TrueVertex->Bunch != event.Bunch) continue;

    SubDetId::SubDetEnum ecal_det[20];

    int necal_det =  anaUtils::GetECalDetCrossed(track, ecal_det);

    if (necal_det > 0)
      outTraj[count++] = track;
  }

  return count;
}

//********************************************************************
bool anaUtils::TrueParticleEntersDet(const AnaTrueParticleB* track, SubDetId::SubDetEnum det){
  //********************************************************************

  if(!track)
    return false;


  //this is a check to account for no splitting of truth into sub-detectors for SMRD and ECa
  if (det > SubDetId::kDSECAL && det < SubDetId::kTPC){
    std::cout<< "anaUtils::TrueParticleEntersDet() WARNING: " << det << " is not available from true info " << std::endl;
  } 

  //check that a trajectory crosses volume
  for(Int_t idet=0;idet<track->nDetCrossings;idet++){

    if(!SubDetId::GetDetectorUsed(track->DetCrossings[idet]->Detector, det)) continue;

    return true;

  }

  return false;

}

//********************************************************************
bool anaUtils::TrueParticleCrossesTECal(const AnaTrueParticleB* track, Float_t min_sep){
  //********************************************************************

  if(!track)
    return false;

  Float_t surf_pos[4] = {
    DetDef::tecalTLmin[1],
    DetDef::tecalBLmax[1],
    DetDef::tecalLmin[0],
    DetDef::tecalRmax[0] 
  };

  //check that a trajectory crosses BarrelECal active volume
  for(Int_t idet=0;idet<track->nDetCrossings;idet++){

    AnaDetCrossingB* cross = track->DetCrossings[idet];
    if(!cross)
      continue;

    if(!(cross->Detector & (1<<SubDetId::kTECAL)) || !cross->InActive) continue;

    //since truth info does not allow splitting the ecal sub-volumes --> use hard-coded values 

    // top 
    Float_t sep = 0.;
    if (cross->ExitPosition[1]>1265.){
      sep = cross->ExitPosition[1]-surf_pos[0];
    }
    //bottom
    else if (cross->ExitPosition[1]<-1265.){
      sep = surf_pos[1]-cross->ExitPosition[1];
    }
    //left
    else if (cross->ExitPosition[0]>1300.){
      sep = cross->ExitPosition[0]-surf_pos[2];
    }
    //right
    else if (cross->ExitPosition[0]<-1300.){
      sep = surf_pos[3]-cross->ExitPosition[0];
    }

    if(sep>min_sep)
      return true;
  }

  return false;

}


//********************************************************************
bool anaUtils::TrueParticleCrossesSMRD(const AnaTrueParticleB* track, Float_t min_sep){
  //********************************************************************

  if(!track)
    return false;

  Float_t surf_pos[4] = {
    DetDef::smrdTLmin[1],
    DetDef::smrdBLmax[1],
    DetDef::smrd6Lmin[0],
    DetDef::smrd6Rmax[0] 
  };

  //loop through det crossings
  for(Int_t idet=0;idet<track->nDetCrossings;idet++){

    AnaDetCrossingB* cross = track->DetCrossings[idet];
    if(!cross)
      continue;

    //InActive flag is not set for SMRD in oaAnalysis
    if(!(cross->Detector & (1<<SubDetId::kSMRD)))
      continue;

    // top 
    Float_t sep = 0.;
    if (cross->ExitPosition[1]>2010.){
      sep = cross->ExitPosition[1]-surf_pos[0];
    }
    //bottom
    else if (cross->ExitPosition[1]<-2010.){
      sep = surf_pos[1]-cross->ExitPosition[1];
    }
    //left
    else if (cross->ExitPosition[0]>1830.){
      sep = cross->ExitPosition[0]-surf_pos[2];
    }
    //right
    else if (cross->ExitPosition[0]<-1830.){
      sep = surf_pos[3]-cross->ExitPosition[0];
    }

    if(sep>min_sep)
      return true;
  }

  return false;

}

//********************************************************************
bool anaUtils::TrueParticleCrossesFGD(const AnaTrueParticleB* track, SubDetId::SubDetEnum det){
  //********************************************************************

  if(!track)
    return false;

  if  (det!=SubDetId::kFGD && !SubDetId::IsFGDDetector(det))
    return false;


  //loop through det crossings
  for(Int_t idet=0;idet<track->nDetCrossings;idet++){

    AnaDetCrossingB* cross = track->DetCrossings[idet];
    if(!cross)
      continue;

    // i.e crossing the active part of the FGD
    if (!SubDetId::GetDetectorUsed(track->DetCrossings[idet]->Detector, det) || !track->DetCrossings[idet]->InActive)
      continue;

    //the separation should be done using the z position, since the fgd is separated by layer in z,
    //making the z position the reconstructed quantity to be cut on
    Float_t sep = fabs(track->DetCrossings[idet]->EntrancePosition[2] - track->DetCrossings[idet]->ExitPosition[2]);

    //should be at least two layers
    if(sep>DetDef::fgdXYModuleWidth)
      return true;

  }

  return false;

}

//********************************************************************
bool anaUtils::TrueParticleCrossesTPC(const AnaTrueParticleB* track, SubDetId::SubDetEnum det){
  //********************************************************************

  if (!track)
    return false;

  if (det!=SubDetId::kTPC && !SubDetId::IsTPCDetector(det))
    return false;

  Float_t dist=-999999.;

  //loop through det crossings
  for(Int_t idet=0;idet<track->nDetCrossings;idet++){

    AnaDetCrossingB* cross = track->DetCrossings[idet];
    if(!cross)
      continue;

    // i.e crossing the active part of the TPC 
    if (!SubDetId::GetDetectorUsed(track->DetCrossings[idet]->Detector, det) || !track->DetCrossings[idet]->InActive)
      continue;

    Float_t sep = anaUtils::GetSeparationSquared(track->DetCrossings[idet]->EntrancePosition, track->DetCrossings[idet]->ExitPosition);
    if (sep>dist) dist = sep;
  }

  if (dist > 62500)//bigger than the ~1/4 of the width of the TPC
    return true;

  return false;

}

//**************************************************
int anaUtils::GetECalDetCrossed(const AnaTrueParticleB* track, SubDetId::SubDetEnum det[]) {
  //**************************************************

  int count = 0;

  if (!track)
    return count;

  for (Int_t idet = 0; idet < track->nDetCrossings; idet++){

    if((track->DetCrossings[idet]->Detector & (1<<SubDetId::kTECAL)) && track->DetCrossings[idet]->InActive) {

      //use geometry info to split between sub-detectors
      if (track->DetCrossings[idet]->EntrancePosition[1] > 1265.        || track->DetCrossings[idet]->ExitPosition[1] > 1265)
        det[count++] = SubDetId::kTopTECAL;

      else if (track->DetCrossings[idet]->EntrancePosition[1] < -1265.  || track->DetCrossings[idet]->ExitPosition[1] < -1265.)
        det[count++] = SubDetId::kBottomTECAL;

      else if (track->DetCrossings[idet]->EntrancePosition[0] > 1300.   || track->DetCrossings[idet]->ExitPosition[0] > 1300.)
        det[count++] = SubDetId::kLeftTECAL;

      else if (track->DetCrossings[idet]->EntrancePosition[0] < -1300.  || track->DetCrossings[idet]->ExitPosition[0] < -1300.) 
        det[count++] = SubDetId::kRightTECAL;

    }

    else if((track->DetCrossings[idet]->Detector & (1<<SubDetId::kPECAL)) && track->DetCrossings[idet]->InActive) {

      //use geometry info to split between sub-detectors
      if (track->DetCrossings[idet]->EntrancePosition[1] > 1265.        || track->DetCrossings[idet]->ExitPosition[1] > 1265)
        det[count++] = SubDetId::kTopPECAL;

      else if (track->DetCrossings[idet]->EntrancePosition[1 ] < -1265. || track->DetCrossings[idet]->ExitPosition[1] < -1265.)
        det[count++] = SubDetId::kBottomPECAL;

      else if (track->DetCrossings[idet]->EntrancePosition[0] > 1300.   || track->DetCrossings[idet]->ExitPosition[0] > 1300.)
        det[count++] = SubDetId::kLeftPECAL;

      else if (track->DetCrossings[idet]->EntrancePosition[0] < -1300.  || track->DetCrossings[idet]->ExitPosition[0] < -1300.) 
        det[count++] = SubDetId::kRightPECAL;
    }
    else if((track->DetCrossings[idet]->Detector & (1<<SubDetId::kDSECAL)) && track->DetCrossings[idet]->InActive) {
      det[count++] = SubDetId::kDSECAL;
    }
  }
  return count;
}



//**************************************************
int anaUtils::GetSMRDDetCrossed(const AnaTrueParticleB* track, SubDetId::SubDetEnum det[]) {
  //**************************************************
  int count = 0;

  if (!track)
    return count;

  for(Int_t idet=0;idet<track->nDetCrossings;idet++){
    //InActive flag is not set for SMRD in oaAnalysis

    if(!(track->DetCrossings[idet]->Detector & (1<<SubDetId::kSMRD))) 
      continue;
    
    //use geometry info to split between sub-detectors
    if (track->DetCrossings[idet]->EntrancePosition[1]>2010.)
      det[count++] = SubDetId::kTopSMRD;

    if (track->DetCrossings[idet]->EntrancePosition[1]<-2010.)
      det[count++] = SubDetId::kBottomSMRD;

    if (track->DetCrossings[idet]->EntrancePosition[0]>1830.)
      det[count++] = SubDetId::kLeftSMRD;

    if (track->DetCrossings[idet]->EntrancePosition[0]<-1830.) 
      det[count++] = SubDetId::kRightSMRD;
  }

  return count;
}

//**************************************************
int anaUtils::GetFGDDetCrossed(const AnaTrueParticleB* track, SubDetId::SubDetEnum det[]) {
  //**************************************************
  int count = 0;

  if (!track)
    return count;

  for(Int_t idet=0;idet<track->nDetCrossings;idet++){

    // i.e crossing the active part of the FGD
    if (SubDetId::GetDetectorUsed(track->DetCrossings[idet]->Detector, SubDetId::kFGD1) 
        && track->DetCrossings[idet]->InActive)
      det[count++] = SubDetId::kFGD1;

    if (SubDetId::GetDetectorUsed(track->DetCrossings[idet]->Detector, SubDetId::kFGD2) 
        && track->DetCrossings[idet]->InActive)
      det[count++] = SubDetId::kFGD2;

  }

  return count;
}


//**************************************************
bool anaUtils::GetDetectorUsed(const AnaDetCrossingB& cross, SubDetId::SubDetEnum det, bool check_active){
  //**************************************************

  if (det == SubDetId::kInvalid)
    return false;

  if (SubDetId::IsSMRDDetector(det)){
    if (!SubDetId::GetDetectorUsed(cross.Detector, SubDetId::kSMRD))
      return false;
    
    // This is to account for possible changes upstream
    if (SubDetId::GetDetectorUsed(cross.Detector, det))
      return true;
    
    // Ignore active check since is not set for SMRD
    switch (det){
      case SubDetId::kTopSMRD:
        return (cross.EntrancePosition[1] > std::min(DetDef::smrdTLmin[1], DetDef::smrdTRmin[1]));  
        break;
      case SubDetId::kBottomSMRD:
        return (cross.EntrancePosition[1] < std::max(DetDef::smrdBLmax[1], DetDef::smrdBRmax[1]));  
        break;
      case SubDetId::kLeftSMRD:
        return (cross.EntrancePosition[0] > DetDef::smrd78Lmin[0]);  
        break;
      case SubDetId::kRightSMRD:
        return (cross.EntrancePosition[0] < DetDef::smrd78Rmax[0]);  
        break;
      default:
        return false;
        break;
    }
  }
  else if (SubDetId::IsTECALDetector(det)){
    if (!SubDetId::GetDetectorUsed(cross.Detector, SubDetId::kTECAL))
      return false;
    
    if (check_active && !cross.InActive) 
      return false;
    
    // This is to account for possible changes upstream
    if (SubDetId::GetDetectorUsed(cross.Detector, det))
      return true;
    
    
    switch (det){
      case SubDetId::kTopTECAL:
        return (cross.EntrancePosition[1] > std::min(DetDef::tecalTLmin[1], DetDef::tecalTRmin[1]));  
        break;
      case SubDetId::kBottomTECAL:
        return (cross.EntrancePosition[1] < std::max(DetDef::tecalBLmax[1], DetDef::tecalBRmax[1]));  
        break;
      case SubDetId::kLeftTECAL:
        return (cross.EntrancePosition[0] > DetDef::tecalLmin[0]);  
        break;
      case SubDetId::kRightTECAL:
        return (cross.EntrancePosition[0] < DetDef::tecalRmax[0]);  
        break;
      default:
        return false;
        break;
    }

  }
  else if (SubDetId::IsPECALDetector(det)){
    if (!SubDetId::GetDetectorUsed(cross.Detector, SubDetId::kPECAL))
      return false;
    
    if (check_active && !cross.InActive) 
      return false;
    
    // This is to account for possible changes upstream
    if (SubDetId::GetDetectorUsed(cross.Detector, det))
      return true;
    
    switch (det){
      case SubDetId::kTopPECAL:
        return (cross.EntrancePosition[1] > std::min(DetDef::pecalTLmin[1], DetDef::pecalTRmin[1]));  
        break;
      case SubDetId::kBottomPECAL:
        return (cross.EntrancePosition[1] < std::max(DetDef::pecalBLmax[1], DetDef::pecalBRmax[1]));  
        break;
      case SubDetId::kLeftPECAL:
        return (cross.EntrancePosition[0] > DetDef::pecalLmin[0]);  
        break;
      case SubDetId::kRightPECAL:
        return (cross.EntrancePosition[0] < DetDef::pecalRmax[0]);  
        break;
      default:
        return false;
        break;
    }
  }
   
  if (check_active && !cross.InActive) return false;
  
  return SubDetId::GetDetectorUsed(cross.Detector, det); 

}




//**************************************************
AnaDetCrossingB* anaUtils::GetAnaDetCrossing(const AnaTrueParticleB* track, SubDetId::SubDetEnum det, bool check_active) {
  //**************************************************
  AnaDetCrossingB* cross = NULL;

  if (det == SubDetId::kInvalid)
    return cross;

  if (!track) return cross;


  for (int i = 0; i < track->nDetCrossings; i++){

    if (!track->DetCrossings[i]) continue;

    // Check that a detector (or subsystem) of interest is used
    if (!anaUtils::GetDetectorUsed(*track->DetCrossings[i], det, check_active))
      continue;

    cross = track->DetCrossings[i];
    // Proceed with the first crossing found
    break;
  }

  return cross;

}

//**************************************************
Float_t anaUtils::GetEntranceMomentum(const AnaDetCrossingB& cross){
  //************************************************** 
  return sqrt(pow(cross.EntranceMomentum[0],2) +
      pow(cross.EntranceMomentum[1],2) + 
      pow(cross.EntranceMomentum[2],2));  
}

//**************************************************
Float_t anaUtils::GetExitMomentum(const AnaDetCrossingB& cross){
  //**************************************************

  return sqrt(pow(cross.ExitMomentum[0],2) +
      pow(cross.ExitMomentum[1],2) + 
      pow(cross.ExitMomentum[2],2));  
}

//**************************************************
bool anaUtils::CheckTrueCausesTrueSimple(const AnaTrueParticleB& trueTrack1, const AnaTrueParticleB& trueTrack2){
//**************************************************

  if (trueTrack1.ID == trueTrack2.ID)
      return true;
     
  if (trueTrack1.ID == trueTrack2.ParentID)
    return true;
    
  if (trueTrack1.ID == trueTrack2.GParentID)
      return true;
  
  if (trueTrack1.ID == trueTrack2.PrimaryID)
      return true;
  
  return false;
  
}
   
//**************************************************
bool anaUtils::CheckTrueCausesRecoSimple(const AnaTrueParticleB& trueTrack, const AnaParticleB& track){
//**************************************************

  if (!track.GetTrueParticle()){
    return false;
  }
  
  return CheckTrueCausesTrueSimple(trueTrack, *track.GetTrueParticle());
  
  
}

//**************************************************
bool anaUtils::CheckTrueCausesTrueFull(const AnaEventB& event, const AnaTrueParticleB& trueTrack1, const AnaTrueParticleB& trueTrack2, int& gen){
//**************************************************
  
  
  if (trueTrack1.ID == trueTrack2.ID){
    gen = 0;  
    return true;
  }
     
  if (trueTrack1.ID == trueTrack2.ParentID){
    gen = 1;
    return true;
  }
    
  if (trueTrack1.ID == trueTrack2.GParentID){
    gen = 2;
    return true;
  }
  
  // Start looping over parents 
  AnaTrueParticleB* trueCandidate = anaUtils::GetTrueParticleByID(event, trueTrack2.GParentID);
  
  int gen_tmp = 2; 
 
  while (trueCandidate){
    if (trueCandidate->ID == trueTrack1.ID){
      gen = gen_tmp;
      return true;
   } 
   
   trueCandidate = (trueCandidate->ParentID==0) ? NULL : anaUtils::GetTrueParticleByID(event, trueCandidate->ParentID);
   gen_tmp++;
  }
  
  return false;
  
}




//**************************************************
bool anaUtils::CheckTrueCausesRecoFull(const AnaEventB& event, const AnaTrueParticleB& trueTrack, const AnaParticleB& track, int& gen){
//**************************************************
  
  if (!track.GetTrueParticle()){
    return false;
  }
  
  return CheckTrueCausesTrueFull(event, trueTrack, *track.GetTrueParticle(), gen);
  
 
}

//********************************************************************
Int_t anaUtils::GetTrueParticlesFromTrueVertex(const AnaTrueVertexB& vertex, AnaTrueParticleB* outTraj[], 
    const std::set<int>& particlePDGs, unsigned int mode){
  //********************************************************************

  int count = 0; 

  // check whether any particle is provided
  if (particlePDGs.size() < 1) return count;

  std::set<int>::const_iterator it;

  //loop through trajectories associated with the vertex
  for (int i = 0; i < vertex.nTrueParticles; i++){

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
    for (it = particlePDGs.begin(); it != particlePDGs.end(); it++){
      if (trueTrack->PDG == (*it)){
        found_pdg = true;
        break;
      }
    }

    if (!found_pdg) continue;

    outTraj[count++] = trueTrack;
  }

  // std::sort(&outTraj[0], &outTraj[count], AnaTrueParticleB::CompareMomentum);

  return count;
}

//********************************************************************
AnaTrueParticleB* anaUtils::GetTrueParticleFromTrueVertex(const AnaTrueVertexB& vertex, Int_t ID){
  //********************************************************************

  // Loop through trajectories associated with the vertex
  for (int i = 0; i < vertex.nTrueParticles; i++){

    AnaTrueParticleB* trueTrack = vertex.TrueParticles[i];
    if (!trueTrack)
      continue;
    
    if (trueTrack->ID == ID)
      return trueTrack;
  }
  
  return NULL;
}

