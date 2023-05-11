#ifndef PropagationUtils_h
#define PropagationUtils_h

/// This is for propagation in small steps
#include "SecondaryInteractionSystematic.hxx"
#include "SubDetId.hxx"
#include "IntersectionUtils.hxx"


namespace propUtils{
    
 
  /// An utility function used to propagate a state TO a given
  /// detector - i.e first point when a track enters a detector will be provided
  /// together with the corresponding kinematics 
  /// One has to provide a sense of the propagation,  a step size,  and a max
  /// number of steps together with a detector bit 
  /// State is supposed to be ouside the detector
  bool PropagateToDetector(const si_syst::ParticleState& state, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm

  bool PropagateToDetector(const AnaTrackB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, si_syst::EndType end = si_syst::kStart,
      Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  
  bool PropagateToDetector(const AnaTrueParticleB& track, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  
  /// An utility function used to propagate a state FROM a given
  /// detector - i.e first point when a track exits a detector will be provided
  /// together with the corresponding kinematics 
  /// One has to provide a sense of the propagation,  a step size,  and a max
  /// number of steps together with a detector bit 
  /// State is supposed to be inside the detector
 
  bool PropagateFromDetector(const si_syst::ParticleState& state, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm

  bool PropagateFromDetector(const AnaTrackB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, si_syst::EndType end = si_syst::kStart, 
      Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  bool PropagateFromDetector(const AnaTrueParticleB& track, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm

  
  /// An utility function to INTERSECT a detector,  two states will be returned:
  /// two interestction points along a track (assuming a given sense,  forward or
  /// backward)
  /// Will return FALSE if: a track does not intersect a detector, 
  /// If a track starts inside a detector 
  /// If a track ends inside a detector
  /// For the last two cases one can use PropageTo and PropagateFrom utils
  bool IntersectDetector(const si_syst::ParticleState& state, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  bool IntersectDetector(const AnaTrackB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense = si_syst::kForward, si_syst::EndType end = si_syst::kStart, 
      Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  bool IntersectDetector(const AnaTrueParticleB& track, Int_t PID, SubDetId::SubDetEnum det, si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  /// Propagation to a given length
  bool PropagateToLength(const si_syst::ParticleState& state, Double_t length, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10); //step in mm

  bool PropagateToLength(const AnaTrackB& track, Int_t PID, Double_t length, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, si_syst::EndType end = si_syst::kStart, Double_t step = 10); //step in mm
  
  
  bool PropagateToLength(const AnaTrueParticleB& track, Double_t length, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10); //step in mm
  
  
  /// Propagation FROM a given box: an object is assumed to be inside the
  /// box - propagation will fail if it is not there to start with
  /// the propagation ends at the border of the box (first step that exits -
  /// take care of small steps)
  bool PropagateFromBox(const si_syst::ParticleState& state, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm

  bool PropagateFromBox(const AnaTrackB& track, Int_t PID, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, si_syst::EndType end = si_syst::kStart,
      Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  
  bool PropagateFromBox(const AnaTrueParticleB& track, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  
  /// Propagation TO a given box: an object is assumed to be inside the
  /// box - propagation will fail if it is not outside to start with
  /// the propagation ends at the border of the box (first step that enters -
  /// take care of small steps)
 
  bool PropagateToBox(const si_syst::ParticleState& state, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm

  bool PropagateToBox(const AnaTrackB& track, Int_t PID, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, si_syst::EndType end = si_syst::kStart, 
      Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  
  bool PropagateToBox(const AnaTrueParticleB& track, const intersectionUtils::AnaDetector3DBox_AAB& box, si_syst::ParticleState& state_out, 
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm
 
  
  /// An utility function to INTERSECT a given box,  two states will be returned:
  /// two interestction points along a track (assuming a given sense,  forward or
  /// backward)
  /// Will return FALSE if: a track does not intersect a box, 
  /// If a track starts inside a box 
  /// If a track ends inside a box
  /// For the last two cases one can use PropageTo and PropagateFrom utils
  bool IntersectBox(const si_syst::ParticleState& state, const intersectionUtils::AnaDetector3DBox_AAB& box, 
      si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm

  bool IntersectBox(const AnaTrackB& track, Int_t PID, const intersectionUtils::AnaDetector3DBox_AAB& box, 
      si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second, 
      si_syst::SenseType sense = si_syst::kForward, si_syst::EndType end = si_syst::kStart, Double_t step = 10, Int_t NSteps = 10000); //step in mm
  
  
  bool IntersectBox(const AnaTrueParticleB& track, const intersectionUtils::AnaDetector3DBox_AAB& box,
      si_syst::ParticleState& state_out_first,
      si_syst::ParticleState& state_out_second,
      si_syst::SenseType sense = si_syst::kForward, Double_t step = 10, Int_t NSteps = 10000); //step in mm
    
  
  /// Correct momentum by range value via propagating back to the reco vertex:
  /// back means we propagate backwards along the length between the track start
  /// point and the vertex position
  Float_t CorrectMomRangeToVertex(const AnaVertexB& vertex, const AnaTrackB& track, Int_t PID, si_syst::EndType end);
  
  
};


#endif
