#include "PropagationUtils.hxx"
#include "ConstituentsUtils.hxx"

//********************************************************************
bool propUtils::IntersectDetector(const si_syst::ParticleState& state, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense,  Double_t step, Int_t NSteps){
//********************************************************************

  Float_t pos_init[3];
  anaUtils::VectorToArray(state.Pos, pos_init);

  
  // Fails if is inside the detector
  if (anaUtils::InDetVolume(det, pos_init)){
      return false;
  }
  
  // Propagate to the  detctor 
  bool ok_to = propUtils::PropagateToDetector(state, det, state_out_first, sense, step, NSteps);
  
  
  // Fails to enter the detector
  if (!ok_to){
    return false;
  }
  
  
  // Propagate from the detector
  bool ok_from = propUtils::PropagateToDetector(state_out_first, det, state_out_second, sense, step, NSteps); 
  
  // Fails to exit the detector
  if (!ok_from){
    return false;
  }
  return true;

}


//********************************************************************
bool propUtils::IntersectDetector(const AnaTrackB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense, si_syst::EndType end, Double_t step, Int_t NSteps){
//********************************************************************

  si_syst::ParticleState state(track, end, PID);
  
  return propUtils::IntersectDetector(state, det, state_out_first, state_out_second, sense, step, NSteps);


}
    
//********************************************************************
bool propUtils::IntersectDetector(const AnaTrueParticleB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense, Double_t step, Int_t NSteps){
//********************************************************************

  si_syst::ParticleState state(track);
  
  return propUtils::IntersectDetector(state, det, state_out_first, state_out_second, sense, step, NSteps);

}


//********************************************************************
bool propUtils::PropagateToDetector(const si_syst::ParticleState& state, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  size_t step_counter = 0;

  state_out = state;

  if (step <= 0){
    return false;
  }
  
  

  for(;;){
    Float_t pos_tmp[3];
    anaUtils::VectorToArray(state_out.Pos, pos_tmp);

    if (anaUtils::InDetVolume(det, pos_tmp)){
      return true;
    }


    if ((Int_t)step_counter > NSteps){
      return false;
    }

    si_syst::TakeSmallStep(state_out, step, sense);

    step_counter++;
    
    
    // A protection against a stopped particle
    if (state_out.Momentum <= 0){
      return false;
    }


  }
  
  return false;

}


//********************************************************************
bool propUtils::PropagateToDetector(const AnaTrackB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, si_syst::EndType end, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track, end, PID);
  

  return propUtils::PropagateToDetector(state, det, state_out, sense, step, NSteps);  

}


//********************************************************************
bool propUtils::PropagateToDetector(const AnaTrueParticleB& track, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track);
  
  return propUtils::PropagateToDetector(state, det, state_out, sense, step, NSteps);  

}

//********************************************************************
bool propUtils::PropagateFromDetector(const si_syst::ParticleState& state, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  size_t step_counter = 0;

  state_out = state;

  if (step <= 0){
    return false;
  }
  si_syst::ParticleState state_prev = state_out; 
  
  Float_t pos_init[3];
  anaUtils::VectorToArray(state_out.Pos, pos_init);

  if (!anaUtils::InDetVolume(det, pos_init)){
      return false;
  }
  
  for(;;){
    Float_t pos_tmp[3];
    anaUtils::VectorToArray(state_out.Pos, pos_tmp);

    if (!anaUtils::InDetVolume(det, pos_tmp)){
      state_out = state_prev;
      return true;
    }
    
    state_prev = state_out;


    if ((Int_t)step_counter > NSteps){
      return false;
    }

    si_syst::TakeSmallStep(state_out, step, sense);

    step_counter++;
    
    
    // A protection against a stopped particle
    if (state_out.Momentum <= 0){
      return false;
    }


  }
  
  return false;

}


//********************************************************************
bool propUtils::PropagateFromDetector(const AnaTrackB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, si_syst::EndType end, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track, end, PID);
  

  return propUtils::PropagateFromDetector(state, det, state_out, sense, step, NSteps);  

}


//********************************************************************
bool propUtils::PropagateFromDetector(const AnaTrueParticleB& track, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track);
  
  return propUtils::PropagateFromDetector(state, det, state_out, sense, step, NSteps);  

}

//********************************************************************
bool propUtils::PropagateToLength(const si_syst::ParticleState& state, Double_t length, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step){ 
  //********************************************************************

  size_t step_counter = 0;

  state_out = state;
  
  if (step <= 0){
    return false;
  }
  
  if (length < 0){
    return false;
  }
 
  if (state.Momentum <= 0.){
    return false;
  }
  
  Int_t NSteps = (Int_t)(length / step);
  
  
  for(;;){

    if ((Int_t)step_counter > NSteps){
      return true;
    }

    si_syst::TakeSmallStep(state_out, step, sense);

    step_counter++;
   
    // A protection against a stopped particle
    if (state_out.Momentum <= 0){
      return false;
    }

  }
  return false; 

}

//********************************************************************
bool propUtils::PropagateToLength(const AnaTrackB& track, Int_t PID, Double_t length, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, si_syst::EndType end, Double_t step){ 
  //********************************************************************

  si_syst::ParticleState state(track, end, PID);
  

  return propUtils::PropagateToLength(state, length, state_out, sense, step);  

}


//********************************************************************
bool propUtils::PropagateToLength(const AnaTrueParticleB& track, Double_t length, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step){ 
  //********************************************************************

  si_syst::ParticleState state(track);
  
  return propUtils::PropagateToLength(state, length, state_out, sense, step);  

}



//********************************************************************
bool propUtils::PropagateFromBox(const si_syst::ParticleState& state, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  size_t step_counter = 0;

  state_out = state;
 
  
  si_syst::ParticleState state_prev = state_out; 
  
  
  if (step <= 0){
    return false;
  }
  
  //Should be inside box to start with
  if (!box.IsInsideBox(state_out.Pos)){
    return false;
  }
   

  for(;;){

    // First point out - assuming small steps
    if (!box.IsInsideBox(state_out.Pos)){
      state_out = state_prev;
      return true;
    }

    state_prev = state_out;

    if ((Int_t)step_counter > NSteps){
      return false;
    }

    si_syst::TakeSmallStep(state_out, step, sense);

    step_counter++;
    
    
    // A protection against a stopped particle
    if (state_out.Momentum <= 0){
      return false;
    }


  }
  
  return false;

}


//********************************************************************
bool propUtils::PropagateFromBox(const AnaTrackB& track, Int_t PID, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, si_syst::EndType end, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track, end, PID);
  

  return propUtils::PropagateFromBox(state, box, state_out, sense, step, NSteps);  

}


//********************************************************************
bool propUtils::PropagateFromBox(const AnaTrueParticleB& track, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track);
  
  return propUtils::PropagateFromBox(state, box, state_out, sense, step, NSteps);  

}

//********************************************************************
bool propUtils::PropagateToBox(const si_syst::ParticleState& state, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  size_t step_counter = 0;

  state_out = state;

  if (step <= 0){
    return false;
  }
  
  //Should be outside the box to start with
 // if (box.IsInsideBox(state_out.Pos)){
   // return false;
  //}
   

  for(;;){

    // First point in - assuming small steps
    if (box.IsInsideBox(state_out.Pos)){
      return true;
    }


    if ((Int_t)step_counter > NSteps){
      return false;
    }

    si_syst::TakeSmallStep(state_out, step, sense);

    step_counter++;
    
    
    // A protection against a stopped particle
    if (state_out.Momentum <= 0){
      return false;
    }


  }
  
  return false;

}


//********************************************************************
bool propUtils::PropagateToBox(const AnaTrackB& track, Int_t PID, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, si_syst::EndType end, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track, end, PID);
  

  return propUtils::PropagateToBox(state, box, state_out, sense, step, NSteps);  

}


//********************************************************************
bool propUtils::PropagateToBox(const AnaTrueParticleB& track, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
    si_syst::SenseType sense, Double_t step, Int_t NSteps){ 
  //********************************************************************

  si_syst::ParticleState state(track);
  
  return propUtils::PropagateToBox(state, box, state_out, sense, step, NSteps);  

}
  
//********************************************************************
bool propUtils::IntersectBox(const si_syst::ParticleState& state, const intersectionUtils::AnaDetector3DBox_AAB& box, 
      si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense, Double_t step, Int_t NSteps){
//********************************************************************

  //Should be outside the box to start with
  if (box.IsInsideBox(state.Pos)){
    return false;
  }
  
  // Propagate to the box
  bool ok_to = propUtils::PropagateToBox(state, box, state_out_first, sense, step, NSteps);
  
  // Fails if does not enter the box
  if (!ok_to){
   return false; 
  }
  
  // Propagate from the box
  bool ok_from = propUtils::PropagateToBox(state_out_first, box, state_out_second, sense, step, NSteps);
  
  // Fails if does not exit the box
  if (!ok_from){
   return false; 
  }
  
  return true;
  
}

//********************************************************************
bool propUtils::IntersectBox(const AnaTrackB& track, Int_t PID, const intersectionUtils::AnaDetector3DBox_AAB& box, 
      si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second, 
      si_syst::SenseType sense, 
      si_syst::EndType end, 
      Double_t step, 
      Int_t NSteps){
//********************************************************************

  si_syst::ParticleState state(track, end, PID);
  return propUtils::IntersectBox(state, box, state_out_first, state_out_second, sense, step, NSteps);
}
    
 
//********************************************************************
bool propUtils::IntersectBox(const AnaTrueParticleB& track, const intersectionUtils::AnaDetector3DBox_AAB& box,
      si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense, Double_t step, Int_t NSteps){
    //********************************************************************

  si_syst::ParticleState state(track);
  return propUtils::IntersectBox(state, box, state_out_first, state_out_second, sense, step, NSteps);

}

//********************************************************************
Float_t propUtils::CorrectMomRangeToVertex(const AnaVertexB& vertex, const AnaTrackB& track, Int_t PID, si_syst::EndType end){
//********************************************************************

  // The dummy default
  Float_t mom_corr = -999;
  
  // Check the PID
  if (abs(PID) != ParticleId::kMuonPDG && abs(PID) != ParticleId::kPiPosPDG  && abs(PID) != ParticleId::kProtonPDG){
    return mom_corr;
  }

  // Get the state
  si_syst::ParticleState state = 
    (end == si_syst::kStart) ? 
    si_syst::ParticleState(track, si_syst::kStart, PID) : 
    si_syst::ParticleState(track, si_syst::kEnd, PID);
  
  
  
  // Set the momentum
  if (abs(PID) == ParticleId::kMuonPDG){
    state.Momentum = track.RangeMomentumMuon;
  }
  
  // If pion momentum is not valid - use muon one
  else if (abs(PID) == ParticleId::kPiPosPDG){
    state.Momentum = track.RangeMomentumPion > 0 ? track.RangeMomentumPion : track.RangeMomentumMuon;
  }
  else if(abs(PID) == ParticleId::kProtonPDG){
    state.Momentum = track.RangeMomentumProton;
  }
 
   
  // Estimate the length
  Float_t length = 
    (end == si_syst::kStart) ? 
    TMath::Sqrt(anaUtils::GetSeparationSquared(vertex.Position, track.PositionStart)) : 
    TMath::Sqrt(anaUtils::GetSeparationSquared(vertex.Position, track.PositionEnd)); 

  
  // Propagate to the length backwards
  si_syst::ParticleState state_out;
  
  bool ok = propUtils::PropagateToLength(state, length, state_out, si_syst::kBackward);

  if (!ok){
    return mom_corr;
  }
 
  return state_out.Momentum;
  
}





