#include "EventBoxUtils.hxx"
#include "CutUtils.hxx"
#include "ND280AnalysisUtils.hxx"
#include "EventBoxTracker.hxx"

//********************************************************************
void boxUtils::FillTracksWithTPC(AnaEventB& event, SubDetId::SubDetEnum det){
//********************************************************************

  bool processFGD1 = false;
  bool processFGD2 = false;
  bool processTPC  = false;
  
  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  
  // Don't fill it when already filled by other selection
  if (!EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPC]){
    processTPC = true;
  }
  
  if ((det==SubDetId::kFGD1 || det==SubDetId::kFGD) && !EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD1]) processFGD1 = true;
  if ((det==SubDetId::kFGD2 || det==SubDetId::kFGD) && !EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD2]) processFGD2 = true;

  if (!processFGD1 && !processFGD2 && !processTPC) return;

  AnaTrackB* selTracks[NMAXPARTICLES];
  int nTPC = anaUtils::GetAllTracksUsingTPC(event, selTracks);

  if (processTPC){
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPC]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPC], nTPC);
  }

  if (processFGD1){
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD1FV]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD1FV], nTPC);

    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD1FV]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD1FV], nTPC);

    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1], nTPC);
    
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD1]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD1], nTPC);
    
    if(!EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]){
      EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]=0;
      anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1], nTPC);
    }else{
      anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1], 
                         EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]+nTPC, 
                         EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]);
    }

  }
  if (processFGD2){
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD2FV]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD2FV], nTPC);

    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD2FV]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD2FV], nTPC);
    

    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2], nTPC);
    

    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD2]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD2], nTPC);
    
    if(!EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]){
      EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]=0;
      anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2], nTPC);
    }else{
      anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2], 
                         EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]+nTPC, 
                         EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]);
    }
  }

  //loop over tpc tracks
  for (Int_t i=0;i<nTPC; ++i){
    AnaTrackB* track = selTracks[i];
    if (!track) continue;
    if (track->nTPCSegments==0){
      std::cout << "Warning. This track has no TPC segments" << std::endl;
      continue;
    }
    // FV
    bool inFGD1start_FV  = false;
    bool inFGD1end_FV    = false;
    bool inFGD2start_FV  = false;
    bool inFGD2end_FV    = false;
    
    // Active volume
    bool inFGD1start  = false;
    bool inFGD1end    = false;
    bool inFGD2start  = false;
    bool inFGD2end    = false;


    if (processTPC){
      EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPC][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPC]++] = track;
      if(processFGD1)
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]++] = track;
      if(processFGD2)
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]++] = track;
    }
    // Does it have FGD as well ? here not...
    if (processFGD1 && anaUtils::TrackUsesDet(*track, SubDetId::kFGD1))
      EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD1][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD1]++] = track;

    if (processFGD2 && anaUtils::TrackUsesDet(*track, SubDetId::kFGD2))
      EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD2][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD2]++] = track;
        
    // Apply the fiducial cut
    inFGD1start_FV = cutUtils::FiducialCut(track->PositionStart, SubDetId::kFGD1);
    inFGD1end_FV   = cutUtils::FiducialCut(track->PositionEnd,   SubDetId::kFGD1);
     
    inFGD2start_FV = cutUtils::FiducialCut(track->PositionStart, SubDetId::kFGD2);
    inFGD2end_FV   = cutUtils::FiducialCut(track->PositionEnd,   SubDetId::kFGD2);
  
    // Apply active volume cut
    
    inFGD1start = anaUtils::InDetVolume(SubDetId::kFGD1, track->PositionStart);
    inFGD1end   = anaUtils::InDetVolume(SubDetId::kFGD1, track->PositionEnd);
     
    inFGD2start = anaUtils::InDetVolume(SubDetId::kFGD2, track->PositionStart);
    inFGD2end   = anaUtils::InDetVolume(SubDetId::kFGD2, track->PositionEnd);
    
    
    
    if (processFGD1){
      if (inFGD1start_FV){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD1FV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD1FV]++] = track;
      }
    }
    
    if (processFGD2){
      if (inFGD2start_FV){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD2FV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD2FV]++] = track;
      }
    }
    
    // Apply the track quality cut
    if (!cutUtils::TrackQualityCut(*track)) continue;
   
    if (processFGD1){
      // FV
      if (inFGD1start_FV){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD1FV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD1FV]++] = track;
      }
     
      // Active
      if (inFGD1start){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1]++] = track;  
      }
      else if (inFGD1end){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1]++] = track;  
      }
    }
    if (processFGD2){
      // FV
      if (inFGD2start_FV){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD2FV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD2FV]++] = track;
      }
      // Active
      
      if (inFGD2start){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2]++] = track;  
      }
      else if (inFGD2end){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2]++] = track;  
      }
    }
       
  }
  if (processFGD1){
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD1FV],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD1FV], nTPC);
    
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD1FV],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD1FV], nTPC);
     
    
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1], nTPC);
    
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD1],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD1], nTPC);
    
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1], 
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]+nTPC);

  }
  if (processFGD2){
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD2FV],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInFGD2FV], nTPC);
    
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD2FV],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInFGD2FV], nTPC);
   

    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2],
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2], nTPC);
 
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD2],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndFGD2], nTPC);
    
    anaUtils::ResizeArray(EventBox-> RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2],
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2], 
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]+nTPC);

  }

}

//********************************************************************
void boxUtils::FillTracksWithFGD(AnaEventB& event, SubDetId::SubDetEnum det){
//********************************************************************

  bool processFGD1 = false;
  bool processFGD2 = false;

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  // Don't fill it when already filled by other selection
  if ((det==SubDetId::kFGD1 || det==SubDetId::kFGD) && !EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC]) processFGD1 = true;
  if ((det==SubDetId::kFGD2 || det==SubDetId::kFGD) && !EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC]) processFGD2 = true;
  if (!processFGD1 && !processFGD2) return;

  AnaTrackB* selTracks[NMAXPARTICLES];
  int nFGD =anaUtils::GetAllTracksUsingDet(event,det, selTracks);
  
  if (processFGD1){
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC], nFGD);
    
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1], nFGD);
    
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1InFGD1FV]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1InFGD1FV], nFGD);
   
    
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndTECAL]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndTECAL], nFGD);
    
    
    if(!EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]){
      EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]=0;
      anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1], nFGD);
    }
    else{
      anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1], 
                         EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]+nFGD, 
                         EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]);
    }
  }
  if (processFGD2){
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC], nFGD);
    
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2], nFGD);
    
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2InFGD2FV]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2InFGD2FV], nFGD);
    
    EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndTECAL]=0;
    anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndTECAL], nFGD);
    

    if(!EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]){
      EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]=0;
      anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2], nFGD);
    }
    else{
      anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2], 
          EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]+nFGD, 
          EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]);
    }
  }
  

  //loop over fgd tracks
  for (Int_t i=0;i<nFGD; ++i){
    AnaTrackB* track = selTracks[i];
    if (track->nFGDSegments==0){
      std::cout << "Warning. This track has no FGD segments" << std::endl;
      continue;
    }

    bool inFGD1start = false;
    bool inFGD1end   = false;
    bool inFGD2start = false;
    bool inFGD2end   = false;
    
    if (processFGD1){
      if (SubDetId::GetDetectorUsed(track->Detector, SubDetId::kFGD1)){
        if (!SubDetId::GetDetectorUsed(track->Detector, SubDetId::kTPC)){
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC]++] = track;
          //tracks with TPC already saved, we only need to add those that are not in the tpc
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]++] = track;
        }
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1]++] = track;

        // apply FGD1 FV cut
        inFGD1start = cutUtils::FiducialCut(track->PositionStart, SubDetId::kFGD1);
        inFGD1end   = cutUtils::FiducialCut(track->PositionEnd,   SubDetId::kFGD1);
        
        if (SubDetId::GetDetectorUsed(track->Detector, SubDetId::kTECAL)){
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndTECAL][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndTECAL]++] = track;
        }
        
        if (inFGD1start){
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1InFGD1FV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1InFGD1FV]++] = track;
        }
      }
    }
    if (processFGD2){
      if (SubDetId::GetDetectorUsed(track->Detector, SubDetId::kFGD2)){
        if (!SubDetId::GetDetectorUsed(track->Detector, SubDetId::kTPC)){
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC]++] = track;
          //tracks with TPC already saved, we only need to add those that are not in the tpc
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]++] = track;
        }
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2]++] = track;

        inFGD2start = cutUtils::FiducialCut(track->PositionStart, SubDetId::kFGD2);
        inFGD2end   = cutUtils::FiducialCut(track->PositionEnd,   SubDetId::kFGD2);
        
        if (SubDetId::GetDetectorUsed(track->Detector, SubDetId::kTECAL)){
            EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndTECAL][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndTECAL]++] = track;
          }

        // apply FGD2 FV cut    
        if (inFGD2start){
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2InFGD2FV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2InFGD2FV]++] = track;
        }
      }
    }
  }
  if (processFGD1){
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC], 
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC], nFGD);
    
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1],         
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1], nFGD);
    
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1InFGD1FV],         
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1InFGD1FV], nFGD);
 
    
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndTECAL],         
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndTECAL], nFGD);
    

    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1],    
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1], 
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD1]+nFGD);
  }
  if (processFGD2){
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC], 
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC], nFGD);
    
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2],         
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2], nFGD);
    
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2InFGD2FV],         
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2InFGD2FV], nFGD);
    
    
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndTECAL],         
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndTECAL], nFGD);
    
    anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2],    
                       EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2], 
                      EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCorFGD2]+nFGD);
  }

}

//********************************************************************
void boxUtils::FillTrajsChargedInTPC(AnaEventB& event){
//********************************************************************

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];
  // Don't fill it when already filled by other selection
  // Don't fill it when already filled by other selection
  if (EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCInBunch]) return;

  AnaTrueParticleB* trajs[NMAXTRUEPARTICLES];
  Int_t nTPC = anaUtils::GetAllChargedTrajInTPCInBunch(event, trajs);
  if(NMAXTRUEPARTICLES<(UInt_t)nTPC) nTPC=NMAXTRUEPARTICLES;
  anaUtils::CreateArray(EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCInBunch],nTPC);
  anaUtils::CopyArray(trajs, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCInBunch], nTPC);
  EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCInBunch] = nTPC;
}

//********************************************************************
void boxUtils::FillTrajsChargedInFGDAndNoTPC(AnaEventB& event, SubDetId::SubDetEnum det){
//********************************************************************

  bool processFGD1 = false;
  bool processFGD2 = false;

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  // Don't fill it when already filled by other selection
  if ((det==SubDetId::kFGD1 || det==SubDetId::kFGD) && !EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1AndNoTPCInBunch]) processFGD1 = true;
  if ((det==SubDetId::kFGD2 || det==SubDetId::kFGD) && !EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2AndNoTPCInBunch]) processFGD2 = true;

  if (!processFGD1 && !processFGD2) return;

  if (processFGD1){
    AnaTrueParticleB* trajs[NMAXTRUEPARTICLES];
    Int_t nFGD = anaUtils::GetAllChargedTrajInFGDAndNoTPCInBunch(event, trajs, SubDetId::kFGD1);
    if(NMAXTRUEPARTICLES<(UInt_t)nFGD) nFGD=NMAXTRUEPARTICLES;    
    anaUtils::CreateArray(EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1AndNoTPCInBunch],nFGD);
    anaUtils::CopyArray(trajs, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1AndNoTPCInBunch], nFGD);
    EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1AndNoTPCInBunch] = nFGD;
  }
  if (processFGD2){
    AnaTrueParticleB* trajs[NMAXTRUEPARTICLES];
    Int_t nFGD = anaUtils::GetAllChargedTrajInFGDAndNoTPCInBunch(event, trajs, SubDetId::kFGD2);
    if(NMAXTRUEPARTICLES<(UInt_t)nFGD) nFGD=NMAXTRUEPARTICLES;    
    anaUtils::CreateArray(EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2AndNoTPCInBunch],nFGD);
    anaUtils::CopyArray(trajs, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2AndNoTPCInBunch], nFGD);
    EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2AndNoTPCInBunch] = nFGD;
  }
}

//********************************************************************
void boxUtils::FillTrajsChargedInTPCorFGD(AnaEventB& event, SubDetId::SubDetEnum det){
//********************************************************************
  
  (void)det;
  
  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  // Don't fill it when already filled by other selection
  if (EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCorFGDInBunch]) return;

  AnaTrueParticleB* trajs[NMAXTRUEPARTICLES];
  Int_t count = anaUtils::GetAllChargedTrajInTPCFGDInBunch(event, trajs);
  if((UInt_t)count>NMAXTRUEPARTICLES) count = NMAXTRUEPARTICLES;
  anaUtils::CreateArray(EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCorFGDInBunch],count);
  anaUtils::CopyArray(trajs, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCorFGDInBunch], count);
  EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInTPCorFGDInBunch] = count;
}

//********************************************************************
void boxUtils::FillTrajsChargedHATracker(AnaEventB& event, SubDetId::SubDetEnum det){
//********************************************************************

  bool processFGD1 = false;
  bool processFGD2 = false;

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  // Don't fill it when already filled by other selection
  if ((det==SubDetId::kFGD1 || det==SubDetId::kFGD) && !EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch]) processFGD1 = true;
  if ((det==SubDetId::kFGD2 || det==SubDetId::kFGD) && !EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch]) processFGD2 = true;

  if (!processFGD1 && !processFGD2) return;

  if (processFGD1){
    AnaTrueParticleB* trajs[NMAXTRUEPARTICLES];
    Int_t nFGD = anaUtils::GetAllChargedTrajsInFgdECalInBunch(event, trajs, SubDetId::kFGD1);
    if(NMAXTRUEPARTICLES<(UInt_t)nFGD) nFGD=NMAXTRUEPARTICLES;    
    // Fill the box
    anaUtils::CreateArray( EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch], nFGD);
    anaUtils::CopyArray(trajs, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch], nFGD);
    EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD1ECalHAInBunch] = nFGD;
    
  }
  if (processFGD2){
    AnaTrueParticleB* trajs[NMAXTRUEPARTICLES];
    Int_t nFGD = anaUtils::GetAllChargedTrajsInFgdECalInBunch(event, trajs, SubDetId::kFGD2);
    if(NMAXTRUEPARTICLES<(UInt_t)nFGD) nFGD=NMAXTRUEPARTICLES;    
    // Fill the box
    anaUtils::CreateArray( EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch], nFGD);
    anaUtils::CopyArray(trajs, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch], nFGD);
    EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInFGD2ECalHAInBunch] = nFGD;
  }
}

//********************************************************************
void boxUtils::FillTracksWithECal(AnaEventB& event){
//********************************************************************

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  // Don't fill it when already filled by other selection
  if (EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithECal]) return;

  AnaTrackB* allTracksUsingECAL[NMAXPARTICLES];
  Int_t count = anaUtils::GetAllTracksUsingECAL(event, allTracksUsingECAL);
  
  if (NMAXPARTICLES < (UInt_t)count) count = NMAXPARTICLES;    
    
  // Fill the box
  anaUtils::CreateArray( EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithECal], count);
  anaUtils::CopyArray(allTracksUsingECAL, EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithECal], count);
  EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithECal] = count;

  
  AnaTrackB* allIsoTracksInECAL[NMAXPARTICLES];
  count = anaUtils::GetAllIsoTracksInECAL(event, allIsoTracksInECAL);
  
  if(NMAXPARTICLES < (UInt_t)count) count = NMAXPARTICLES;    
  
  // Fill the box
  anaUtils::CreateArray( EventBox->RecObjectsInGroup[EventBoxTracker::kIsoTracksInECal], count);
  anaUtils::CopyArray(allIsoTracksInECAL, EventBox->RecObjectsInGroup[EventBoxTracker::kIsoTracksInECal], count);
  EventBox->nRecObjectsInGroup[EventBoxTracker::kIsoTracksInECal] = count;
  
  
}



//********************************************************************
void boxUtils::FillTrajsInECal(AnaEventB& event){
//********************************************************************

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  
  // Don't fill it when already filled by other selection
  if (EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesInECalInBunch]) return;

  AnaTrueParticleB* trajs[NMAXTRUEPARTICLES];
  Int_t nECal = anaUtils::GetAllTrajsInECalInBunch(event, trajs);
  
  if(NMAXTRUEPARTICLES<(UInt_t)nECal) nECal = NMAXTRUEPARTICLES;    
    
  // Fill the box
  anaUtils::CreateArray( EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesInECalInBunch], nECal);
  anaUtils::CopyArray(trajs, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesInECalInBunch], nECal);
  EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesInECalInBunch] = nECal;
    
}

//********************************************************************
void boxUtils::FillTracksWithP0D(AnaEventB& event)
//********************************************************************
{
  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];
  //Skip if already filled
  if (EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInP0DFV]) return;

  //Get P0D tracks
  AnaTrackB* p0dTracks[NMAXPARTICLES];
  int nP0D = anaUtils::GetAllTracksUsingP0D(event,p0dTracks);
  if ( (UInt_t)nP0D>NMAXPARTICLES) nP0D = NMAXPARTICLES;

  EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithP0D]                   = 0;
  EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndP0D]             = 0;
  EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCAndP0D]  = 0;
  EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInP0DFV]            = 0;
  EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInP0DFV] = 0;
  EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithP0DAndNoTPC]           = 0;

  anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithP0D],                   nP0D);
  anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndP0D],             nP0D);
  anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCAndP0D],  nP0D);
  anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInP0DFV],            nP0D);
  anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInP0DFV], nP0D);
  anaUtils::CreateArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithP0DAndNoTPC],           nP0D);

  //Loop over P0D Tracks
  for (int i = 0; i < nP0D; i++)
  {
    AnaTrackB* track = p0dTracks[i];
    if (!track->Original) continue;
    if (track->nP0DSegments == 0 ) continue;
    if (track->Momentum < 0 ) continue;

    //Any P0D track
    EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithP0D][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithP0D]++] = track;

    //Tracks with no TPC
    if (track->nTPCSegments == 0)
    {
      EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithP0DAndNoTPC][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithP0DAndNoTPC]++] = track;
      continue;
    }else{
    //Track with TPC
      if (!anaUtils::InFiducialVolume(SubDetId::kP0D,track->PositionStart)) continue;


      EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInP0DFV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInP0DFV]++] = track;
      
      if (SubDetId::GetDetectorUsed(track->Detector, SubDetId::kTPC)){
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndP0D][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndP0D]++] = track;

        if (cutUtils::TrackQualityCut(*track))
        {
          EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCAndP0D][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCAndP0D]++] = track;
        }//passes quality cut
      }

      if (cutUtils::TrackQualityCut(*track))
      {
        EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInP0DFV][EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInP0DFV]++] = track;
      }//passes quality cut

    }//TPC tracks
  }//Loop over tracks
  anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithP0D],
                     EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithP0D], nP0D);
  anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithP0DAndNoTPC],
                     EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithP0DAndNoTPC], nP0D);
  anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCInP0DFV],
                     EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCInP0DFV], nP0D);
  anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInP0DFV],
                     EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCInP0DFV], nP0D);
  anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndP0D],
                     EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPCAndP0D], nP0D);
  anaUtils::ResizeArray(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCAndP0D],
                     EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithGoodQualityTPCAndP0D], nP0D);

}


//********************************************************************
void boxUtils::FillTrajsChargedInP0D(AnaEventB& event)
//********************************************************************
{

  EventBoxB* EventBox = event.EventBoxes[EventBoxId::kEventBoxTracker];

  if (EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DInBunch]) return;

  AnaTrueParticleB* trueP0DTracks[NMAXTRUEPARTICLES];
  AnaTrueParticleB* trueP0DTracksWithTPC[NMAXTRUEPARTICLES];
  AnaTrueParticleB* trueP0DTracksNoTPC[NMAXTRUEPARTICLES];

  
  Int_t count = 0;
  count = anaUtils::GetAllChargedTrajInP0DInBunch(event,trueP0DTracks);
  if ((UInt_t)count>NMAXTRUEPARTICLES ) count = NMAXTRUEPARTICLES;
  anaUtils::CreateArray(EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DInBunch],count);
  anaUtils::CopyArray(trueP0DTracks, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DInBunch], count);
  EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DInBunch] = count;

  count = 0;
  count = anaUtils::GetAllChargedTrajInP0DAndTPCInBunch(event,trueP0DTracksWithTPC);
  if ((UInt_t)count>NMAXTRUEPARTICLES ) count = NMAXTRUEPARTICLES;
  anaUtils::CreateArray(EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DAndTPCInBunch],count);
  anaUtils::CopyArray(trueP0DTracksWithTPC, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DAndTPCInBunch], count);
  EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DAndTPCInBunch] = count;

  count = 0;
  count = anaUtils::GetAllChargedTrajInP0DAndNoTPCInBunch(event,trueP0DTracksNoTPC);
  if ((UInt_t)count>NMAXTRUEPARTICLES ) count = NMAXTRUEPARTICLES;
  anaUtils::CreateArray(EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DAndNoTPCInBunch],count);
  anaUtils::CopyArray(trueP0DTracksNoTPC, EventBox->TrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DAndNoTPCInBunch], count);
  EventBox->nTrueObjectsInGroup[EventBoxTracker::kTrueParticlesChargedInP0DAndNoTPCInBunch] = count;

}

//*********************************************************************
void boxUtils::FillFGDMichelElectrons(AnaEventB& event, SubDetId::SubDetEnum det){
//*********************************************************************

  // Should be FGD
  if (det != SubDetId::kFGD && !SubDetId::IsFGDDetector(det))
    return;
  
  
  SubDetId::SubDetEnum fgd_det[2];
  fgd_det[0] = SubDetId::kFGD1;
  fgd_det[1] = SubDetId::kFGD2;
   
  if (det == SubDetId::kFGD1)
    fgd_det[1] = SubDetId::kFGD1;
 
  if (det == SubDetId::kFGD2)
    fgd_det[0] = SubDetId::kFGD2;


  EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(event.EventBoxes[EventBoxId::kEventBoxTracker]);
  
  if (!EventBox) return;
  
  for (int i = 0; i < 2; i++){
    if (EventBox->FGDMichelElectrons[fgd_det[i]]) continue;
    anaUtils::CreateArray(EventBox->FGDMichelElectrons[fgd_det[i]], NMAXFGDTIMEBINS);
    EventBox->nFGDMichelElectrons[fgd_det[i]] = anaUtils::GetFGDMichelElectrons(event, det, 
        EventBox->FGDMichelElectrons[fgd_det[i]]);
    anaUtils::ResizeArray(EventBox->FGDMichelElectrons[fgd_det[i]], 
        EventBox->nFGDMichelElectrons[fgd_det[i]], NMAXFGDTIMEBINS);
  }
}


