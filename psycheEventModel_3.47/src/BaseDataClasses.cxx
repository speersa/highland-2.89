#define BaseDataClasses_C

#include "BaseDataClasses.hxx"
#include "TMath.h"
#include "BasicUtils.hxx"

// //********************************************************************
// AnaTimeNode::AnaTimeNode(){
// //********************************************************************

//   Detector  = -999;
//   TimeStart = -999;
//   TimeEnd   = -999;
// }

// //********************************************************************
// AnaTimeNode::AnaTimeNode(const AnaTimeNode& anaTime){
// //********************************************************************

//   Detector  = anaTime.Detector;
//   TimeStart = anaTime.TimeStart;
//   TimeEnd   = anaTime.TimeEnd;
// }

//********************************************************************
void AnaToF::Print() const{
  //********************************************************************

  std::cout << "-------- AnaToF --------- " << std::endl;
  
  dump_var(FGD1_FGD2);
  dump_var(Flag_FGD1_FGD2); 
  
  dump_var(P0D_FGD1);  
  dump_var(Flag_P0D_FGD1);
  
  dump_var(DSECal_FGD1);
  dump_var(Flag_DSECal_FGD1);
  
  dump_var(ECal_FGD1);         
  dump_var(Flag_ECal_FGD1);         
  
  dump_var(ECal_FGD2);         
  dump_var(Flag_ECal_FGD1);         
  
  dump_var(DSECal_FGD2);       
  dump_var(Flag_DSECal_FGD2);       
  
  std::cout << "----------------- " << std::endl;
  
  
}
//********************************************************************
AnaTPCParticleB::AnaTPCParticleB():AnaParticleMomB() {
  //********************************************************************

  MomentumError  = -999;
  RefitMomentum  = -999;
  EFieldRefitMomentum  = -999;

  dEdxMeas        = -999;
  dEdxexpMuon     = -999;
  dEdxexpEle      = -999;
  dEdxexpPion     = -999;
  dEdxexpProton   = -999;
  dEdxSigmaMuon   = -999;
  dEdxSigmaEle    = -999;
  dEdxSigmaPion   = -999;
  dEdxSigmaProton = -999;
}

//********************************************************************
AnaTPCParticleB::AnaTPCParticleB(const AnaTPCParticleB& seg):AnaParticleMomB(seg){
  //********************************************************************

  MomentumError  = seg.MomentumError;
  RefitMomentum  = seg.RefitMomentum;
  EFieldRefitMomentum       = seg.EFieldRefitMomentum;

  dEdxMeas      = seg.dEdxMeas; 
  dEdxexpMuon   = seg.dEdxexpMuon; 
  dEdxexpEle    = seg.dEdxexpEle; 
  dEdxexpPion   = seg.dEdxexpPion;  
  dEdxexpProton = seg.dEdxexpProton; 

  dEdxSigmaMuon   = seg.dEdxSigmaMuon; 
  dEdxSigmaEle    = seg.dEdxSigmaEle; 
  dEdxSigmaPion   = seg.dEdxSigmaPion; 
  dEdxSigmaProton = seg.dEdxSigmaProton;
}

//********************************************************************
void AnaTPCParticleB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaTPCParticleB --------- " << std::endl;

  AnaParticleMomB::Print();
}

//********************************************************************
AnaTPCParticleB::~AnaTPCParticleB(){
  //********************************************************************
}

//********************************************************************
AnaFGDParticleB::AnaFGDParticleB():AnaParticleB() {
  //********************************************************************
  X           = -999;
  E           = -999;
  Containment = -999;
  Pullmu      = -999;
  Pullp       = -999;
  Pullpi      = -999;
  Pullno      = -999;
  Pulle       = -999;

}

//********************************************************************
AnaFGDParticleB::AnaFGDParticleB(const AnaFGDParticleB& seg):AnaParticleB(seg){
  //********************************************************************
  X           = seg.X;  
  E           = seg.E;
  Containment = seg.Containment;

  Pullmu      = seg.Pullmu;
  Pullp       = seg.Pullp;
  Pullpi      = seg.Pullpi;
  Pullno      = seg.Pullno; 
  Pulle       = seg.Pulle;
}

//********************************************************************
AnaECALParticleB::AnaECALParticleB():AnaParticleB() {
  //********************************************************************
  
  Clustering3DSeedType         = -999;
  ClusteringAdded3DClusterHits = -999;
  PIDQuality                   = -999;
  PIDMipPion                   = -999;
  PIDMipEm                     = -999;
  PIDEmHip                     = -999;
  Length                       = -999;
  EMEnergy                     = -999;
  EDeposit                     = -999;
  IsShowerLike                 = -999;
  AvgTime                      = -999;
  MostUpStreamLayerHit         = -999;
  anaUtils::ReserveArray(ShowerPosition, 3);
}

//********************************************************************
AnaECALParticleB::AnaECALParticleB(const AnaECALParticleB& seg):AnaParticleB(seg){
  //********************************************************************
  
  Clustering3DSeedType         = seg.Clustering3DSeedType;
  ClusteringAdded3DClusterHits = seg.ClusteringAdded3DClusterHits;
  PIDQuality                   = seg.PIDQuality;
  PIDMipPion                   = seg.PIDMipPion;
  PIDMipEm                     = seg.PIDMipEm;
  PIDEmHip                     = seg.PIDEmHip;
  Length                       = seg.Length;
  EMEnergy                     = seg.EMEnergy;
  EDeposit                     = seg.EDeposit;
  IsShowerLike                 = seg.IsShowerLike;
  AvgTime                      = seg.AvgTime;
  MostUpStreamLayerHit         = seg.MostUpStreamLayerHit;
  anaUtils::CopyArray(seg.ShowerPosition, ShowerPosition, 3);
}

//********************************************************************
AnaSMRDParticleB::AnaSMRDParticleB():AnaParticleB() {
  //********************************************************************
  AvgTime = -999;
}

//********************************************************************
AnaSMRDParticleB::AnaSMRDParticleB(const AnaSMRDParticleB& seg):AnaParticleB(seg){
  //********************************************************************

  AvgTime = seg.AvgTime;
}

//********************************************************************
AnaP0DParticleB::AnaP0DParticleB():AnaParticleB() {
  //********************************************************************

  Length = -999;
  ELoss = -999;

}

//********************************************************************
AnaP0DParticleB::AnaP0DParticleB(const AnaP0DParticleB& seg):AnaParticleB(seg){
  //********************************************************************
  Length = seg.Length;
  ELoss = seg.ELoss; 
}

//********************************************************************
AnaTrackerTrackB::AnaTrackerTrackB():AnaParticleMomB(){
  //********************************************************************

}

//********************************************************************
AnaTrackerTrackB::AnaTrackerTrackB(const AnaTrackerTrackB& seg):AnaParticleMomB(seg){
  //********************************************************************

}

//********************************************************************
AnaParticleMomE::AnaParticleMomE(){
  //********************************************************************

  Charge            = -999;
  Momentum          = -999;
  MomentumEnd       = -999;
}

//********************************************************************
AnaParticleMomE::~AnaParticleMomE(){
  //********************************************************************

}

//********************************************************************
AnaParticleMomE::AnaParticleMomE(const AnaParticleMomE& part){
  //********************************************************************

  Charge            = part.Charge;
  Momentum          = part.Momentum;
  MomentumEnd       = part.MomentumEnd;
}

//********************************************************************
void AnaParticleMomE::Print() const{
  //********************************************************************

  std::cout << "Charge:               " << Charge             << std::endl;
  std::cout << "Momentum:             " << Momentum           << std::endl;
  std::cout << "MomentumEnd:          " << MomentumEnd        << std::endl;
}

//********************************************************************
AnaParticleMomB::AnaParticleMomB():AnaParticleB(),AnaParticleMomE(){
  //********************************************************************

}

//********************************************************************
AnaParticleMomB::~AnaParticleMomB(){
  //********************************************************************

}

//********************************************************************
AnaParticleMomB::AnaParticleMomB(const AnaParticleMomB& part):AnaParticleB(part),AnaParticleMomE(part){
  //********************************************************************

}

//********************************************************************
bool AnaParticleMomB::CompareMomentum(const AnaRecObjectC* p1, const AnaRecObjectC* p2){
  //********************************************************************

  // function to sort particles in decreasing momentum order
  const AnaParticleMomB* t1 = dynamic_cast<const AnaParticleMomB*>(p1);
  const AnaParticleMomB* t2 = dynamic_cast<const AnaParticleMomB*>(p2);

  // set null pointer to be sorted the very last.
  Float_t m1 = -3e6;
  Float_t m2 = -3e6;
  if (t1) m1 = t1->Momentum;
  if (t2) m2 = t2->Momentum;

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
void AnaParticleMomB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaParticleMomB --------- " << std::endl;

  AnaParticleB::Print();
  AnaParticleMomE::Print();
}

//********************************************************************
AnaParticleB::AnaParticleB(): AnaRecObjectC(){
  //********************************************************************

  NHits             = -999;
  NNodes            = -999;

  anaUtils::ReserveArray(DirectionStart, 3);
  anaUtils::ReserveArray(PositionStart,  4);
  anaUtils::ReserveArray(PositionEnd,    4);
  anaUtils::ReserveArray(DirectionEnd,   3);

  Original  = NULL;
}

//********************************************************************
AnaParticleB::~AnaParticleB(){
  //********************************************************************

}

//********************************************************************
AnaParticleB::AnaParticleB(const AnaParticleB& part): AnaRecObjectC(part){
  //********************************************************************

  NHits             = part.NHits;
  NNodes            = part.NNodes;

  anaUtils::CopyArray(part.DirectionStart,  DirectionStart, 3);
  anaUtils::CopyArray(part.DirectionEnd,    DirectionEnd,   3);
  anaUtils::CopyArray(part.PositionStart,   PositionStart,  4);
  anaUtils::CopyArray(part.PositionEnd,     PositionEnd,    4);

  // A pointer to the original particle
  Original = &part;
}

//**************************************************
bool AnaParticleB::CompareNHits(const AnaRecObjectC* p1, const AnaRecObjectC* p2){
  //**************************************************

  // function to sort particles in decreasing nhits order
  const AnaParticleB* t1 = dynamic_cast<const AnaParticleB*>(p1);
  const AnaParticleB* t2 = dynamic_cast<const AnaParticleB*>(p2);

  // set null pointer to be sorted the very last.
  if (!t1 && !t2)
    return false;

  if (t1 && !t2)
    return true;

  if (!t1 && t2)
    return false;

  return t1->NHits > t2->NHits;
}

//********************************************************************
void AnaParticleB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaParticleB --------- " << std::endl;

  AnaRecObjectC::Print();

  std::cout << "NHits:                " << NHits              << std::endl;
  std::cout << "NNodes:               " << NNodes             << std::endl;

  dump_array4(PositionStart);
  dump_array4(PositionEnd);

  dump_array3(DirectionStart);
  dump_array3(DirectionEnd);
}

//********************************************************************
AnaTrackB::AnaTrackB(): AnaParticleMomB(){
  //********************************************************************

  Index               = -999;
  RangeMomentumMuon   = -999;
  RangeMomentumProton = -999;
  RangeMomentumPion   = -999;

  MomentumFlip        = -999;

  TPCQualityCut     = -999;

  nTPCSegments = 0;
  nFGDSegments = 0;
  nP0DSegments = 0;
  nECALSegments = 0;
  nSMRDSegments = 0;

  TPCSegmentsVect.clear();
  FGDSegmentsVect.clear();
  P0DSegmentsVect.clear();
  ECALSegmentsVect.clear();
  SMRDSegmentsVect.clear();

  IsFlipped = false;
}

//********************************************************************
AnaTrackB::~AnaTrackB(){
  //********************************************************************

  for (Int_t i=0;i<nTPCSegments;i++){
    delete TPCSegments[i];    
    TPCSegments[i] = NULL;
  }
  for (Int_t i=0;i<nFGDSegments;i++){
    delete FGDSegments[i];    
    FGDSegments[i] = NULL;
  }
  for (Int_t i=0;i<nECALSegments;i++){
    delete ECALSegments[i];    
    ECALSegments[i] = NULL;
  }
  for (Int_t i=0;i<nSMRDSegments;i++){
    delete SMRDSegments[i];    
    SMRDSegments[i] = NULL;
  }
  for (Int_t i=0;i<nP0DSegments;i++){
    delete P0DSegments[i];    
    P0DSegments[i] = NULL;
  }

  if (TPCSegmentsVect.size()>0  && nTPCSegments ==0) for (UInt_t i=0;i<TPCSegmentsVect.size(); i++) delete TPCSegmentsVect[i];
  if (FGDSegmentsVect.size()>0  && nFGDSegments ==0) for (UInt_t i=0;i<FGDSegmentsVect.size(); i++) delete FGDSegmentsVect[i];
  if (P0DSegmentsVect.size()>0  && nP0DSegments ==0) for (UInt_t i=0;i<P0DSegmentsVect.size(); i++) delete P0DSegmentsVect[i];
  if (ECALSegmentsVect.size()>0 && nECALSegments==0) for (UInt_t i=0;i<ECALSegmentsVect.size();i++) delete ECALSegmentsVect[i];
  if (SMRDSegmentsVect.size()>0 && nSMRDSegments==0) for (UInt_t i=0;i<SMRDSegmentsVect.size();i++) delete SMRDSegmentsVect[i];

  nTPCSegments = 0;
  nFGDSegments = 0;
  nP0DSegments = 0;
  nECALSegments = 0;
  nSMRDSegments = 0;

  TPCSegmentsVect.clear();
  FGDSegmentsVect.clear();
  P0DSegmentsVect.clear();
  ECALSegmentsVect.clear();
  SMRDSegmentsVect.clear();
}

//********************************************************************
AnaTrackB::AnaTrackB(const AnaTrackB& track):AnaParticleMomB(track){
  //********************************************************************

  Index               = track.Index;
  RangeMomentumMuon   = track.RangeMomentumMuon;

  RangeMomentumProton = track.RangeMomentumProton;


  RangeMomentumPion   = track.RangeMomentumPion;

  MomentumFlip      = track.MomentumFlip;

  TPCQualityCut     = track.TPCQualityCut;
  ToF               = track.ToF;
  
  IsFlipped         = track.IsFlipped;

  nTPCSegments  = track.nTPCSegments;
  nFGDSegments  = track.nFGDSegments;
  nP0DSegments  = track.nP0DSegments;
  nECALSegments = track.nECALSegments;
  nSMRDSegments = track.nSMRDSegments;

  for (Int_t i=0;i<track.nTPCSegments;i++)
    TPCSegments[i] = track.TPCSegments[i]->Clone();

  for (Int_t i=0;i<track.nFGDSegments;i++)
    FGDSegments[i] = track.FGDSegments[i]->Clone();

  for (Int_t i=0;i<track.nECALSegments;i++)
    ECALSegments[i] = track.ECALSegments[i]->Clone();

  for (Int_t i=0;i<track.nSMRDSegments;i++)
    SMRDSegments[i] = track.SMRDSegments[i]->Clone();

  for (Int_t i=0;i<track.nP0DSegments;i++)
    P0DSegments[i] = track.P0DSegments[i]->Clone();

  TPCSegmentsVect.clear();
  FGDSegmentsVect.clear();
  P0DSegmentsVect.clear();
  ECALSegmentsVect.clear();
  SMRDSegmentsVect.clear();
}

//********************************************************************
void AnaTrackB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaTrackB --------- " << std::endl;

  AnaParticleMomB::Print();

  std::cout << "MomentumFlip:         " << MomentumFlip         << std::endl;
  std::cout << "RangeMomentumMuon:    " << RangeMomentumMuon    << std::endl;
  std::cout << "RangeMomentumProton:  " << RangeMomentumProton  << std::endl;
  std::cout << "RangeMomentumPion:    " << RangeMomentumPion    << std::endl;

  std::cout << "NTPCs:                " << nTPCSegments       << std::endl;
  std::cout << "NFGDs:                " << nFGDSegments       << std::endl;
  std::cout << "NP0Ds:                " << nP0DSegments       << std::endl;
  std::cout << "NECALs:               " << nECALSegments      << std::endl;
  std::cout << "NSMRDs:               " << nSMRDSegments      << std::endl;
  
  std::cout << "IsFlipped:            " << IsFlipped          << std::endl;
  
  ToF.Print();
  

}

//********************************************************************
bool AnaTrackB::CompareMuonRangeMomentum(const AnaRecObjectC* p1, const AnaRecObjectC* p2){
  //********************************************************************

  const AnaTrackB* t1 = dynamic_cast<const AnaTrackB*>(p1);
  const AnaTrackB* t2 = dynamic_cast<const AnaTrackB*>(p2);

  // set null pointer to be sorted the very last.
  Float_t m1 = -3e6;
  Float_t m2 = -3e6;
  if (t1) m1 = t1->RangeMomentumMuon;
  if (t2) m2 = t2->RangeMomentumMuon;

  // Also send inf to the end
  if (!TMath::Finite(m1)) m1 = -2e6;
  if (!TMath::Finite(m2)) m2 = -2e6;

  // this is compiler dependent
  if (m1 != m1) m1 = -1e6;
  if (m2 != m2) m2 = -1e6;

  return m1 > m2;
}


//********************************************************************
bool AnaTrackB::CompareProtonRangeMomentum(const AnaRecObjectC* p1, const AnaRecObjectC* p2){
  //********************************************************************

  const AnaTrackB* t1 = dynamic_cast<const AnaTrackB*>(p1);
  const AnaTrackB* t2 = dynamic_cast<const AnaTrackB*>(p2);

  // set null pointer to be sorted the very last.
  Float_t m1 = -3e6;
  Float_t m2 = -3e6;
  if (t1) m1 = t1->RangeMomentumProton;
  if (t2) m2 = t2->RangeMomentumProton;

  // Also send inf to the end
  if (!TMath::Finite(m1)) m1 = -2e6;
  if (!TMath::Finite(m2)) m2 = -2e6;

  // this is compiler dependent
  if (m1 != m1) m1 = -1e6;
  if (m2 != m2) m2 = -1e6;

  return m1 > m2;
}

//********************************************************************
bool AnaTrackB::ComparePionRangeMomentum(const AnaRecObjectC* p1, const AnaRecObjectC* p2){
  //********************************************************************

  const AnaTrackB* t1 = dynamic_cast<const AnaTrackB*>(p1);
  const AnaTrackB* t2 = dynamic_cast<const AnaTrackB*>(p2);

  // set null pointer to be sorted the very last.
  Float_t m1 = -3e6;
  Float_t m2 = -3e6;
  if (t1) m1 = t1->RangeMomentumPion;
  if (t2) m2 = t2->RangeMomentumPion;

  // Also send inf to the end
  if (!TMath::Finite(m1)) m1 = -2e6;
  if (!TMath::Finite(m2)) m2 = -2e6;

  // this is compiler dependent
  if (m1 != m1) m1 = -1e6;
  if (m2 != m2) m2 = -1e6;

  return m1 > m2;
}

//********************************************************************
void AnaTrackB::Flip(){
  //********************************************************************

  // std::cout << "FlipTrack" << std::endl;
  //Flip the charge
  Charge = -1. * Charge;
  
  // Update flipped status
  if (IsFlipped == true)        IsFlipped = false;
  else if (IsFlipped == false)  IsFlipped = true;

  // Position
  Float_t pos_tmp[4];
  anaUtils::CopyArray(PositionStart,  pos_tmp,        4);
  anaUtils::CopyArray(PositionEnd,    PositionStart,  4);
  anaUtils::CopyArray(pos_tmp,        PositionEnd,     4);

  // DirectionEnd is proved to provide more stable results than reverse refit: (acceptably) worse resolution but
  // not fit failures
  Float_t dir_tmp_start[3] = {static_cast<Float_t>(-1. * DirectionStart[0]), 
    static_cast<Float_t>(-1. * DirectionStart[1]), 
    static_cast<Float_t>(-1. * DirectionStart[2])}; 
  
  Float_t dir_tmp_end[3]   = {static_cast<Float_t>(-1. * DirectionEnd[0]), 
    static_cast<Float_t>(-1. * DirectionEnd[1]),   
    static_cast<Float_t>(-1. * DirectionEnd[2])};
  
  anaUtils::CopyArray(dir_tmp_end,    DirectionStart,  3); 
  
  anaUtils::CopyArray(dir_tmp_start,  DirectionEnd,    3); 

  // Check whether a track uses TPC
  if (SubDetId::GetDetectorUsed(Detector, SubDetId::kTPC)){
    //Momentum
    std::swap(Momentum, MomentumFlip);
  }
}

//********************************************************************
void AnaTrackB::UnFlip(){
  //********************************************************************
  if (IsFlipped){
    Flip();  
  }
  IsFlipped = false;
}

//********************************************************************
AnaDetCrossingB::AnaDetCrossingB(){
  //********************************************************************

  InActive = 0;
  Detector = 0;

  anaUtils::ReserveArray(EntrancePosition, 4);
  anaUtils::ReserveArray(ExitPosition,     4);

  anaUtils::ReserveArray(EntranceMomentum, 3);
  anaUtils::ReserveArray(ExitMomentum,     3);
  
  ExitOK     = 0;
  EntranceOK = 0;
}

//********************************************************************
AnaDetCrossingB::AnaDetCrossingB(const AnaDetCrossingB& cross){
  //********************************************************************

  Detector = cross.Detector;
  InActive = cross.InActive;

  anaUtils::CopyArray(cross.EntrancePosition,  EntrancePosition,   4);
  anaUtils::CopyArray(cross.ExitPosition,      ExitPosition,       4);

  anaUtils::CopyArray(cross.EntranceMomentum,  EntranceMomentum,   3);
  anaUtils::CopyArray(cross.ExitMomentum,      ExitMomentum,       3);
  
  EntranceOK = cross.EntranceOK;
  ExitOK     = cross.ExitOK;
}

//********************************************************************
AnaTrueParticleB::AnaTrueParticleB():AnaTrueObjectC(){
  //********************************************************************

  PDG           = -999;
  PrimaryID     = -999;
  ParentID      = 0; // These are 0 as it has a special meaning
  ParentPDG     = 0; // These are 0 as it has a special meaning
  GParentID     = 0; // These are 0 as it has a special meaning
  GParentPDG    = 0;

  anaUtils::ReserveArray(Position, 4);
  anaUtils::ReserveArray(PositionEnd, 4);
  anaUtils::ReserveArray(Direction, 3);

  Momentum      = -999;
  Charge        = -999;
  VertexID      = -999;
  TrueVertex    = NULL;
  nDetCrossings = 0;
  DetCrossings  = NULL;
  DetCrossingsVect.clear();

  IsTruePrimaryPi0DecayPhoton      = false;
  IsTruePrimaryPi0DecayPhotonChild = false;
}

//********************************************************************
AnaTrueParticleB::~AnaTrueParticleB(){
  //********************************************************************

  for (Int_t i=0;i<nDetCrossings;i++)
    delete DetCrossings[i];

  if (DetCrossingsVect.size()>0 && nDetCrossings==0)   for (UInt_t i=0;i<DetCrossingsVect.size();i++)  delete DetCrossingsVect[i];
  DetCrossingsVect.clear();

  nDetCrossings = 0;

  // Must delete array of pointers, since we re-create this every time we apply a selection
  if(DetCrossings != NULL) delete [] DetCrossings;
  DetCrossings = NULL;      
}

//********************************************************************
AnaTrueParticleB::AnaTrueParticleB(const AnaTrueParticleB& truePart):AnaTrueObjectC(truePart){
  //********************************************************************

  PDG        = truePart.PDG;
  PrimaryID  = truePart.PrimaryID;
  ParentID   = truePart.ParentID;
  ParentPDG  = truePart.ParentPDG;
  GParentID  = truePart.GParentID;
  GParentPDG = truePart.GParentPDG;

  anaUtils::CopyArray(truePart.Position,    Position,    4);
  anaUtils::CopyArray(truePart.PositionEnd, PositionEnd, 4);
  anaUtils::CopyArray(truePart.Direction,   Direction,   3);

  Momentum   = truePart.Momentum;
  Charge     = truePart.Charge;
  VertexID   = truePart.VertexID;
  TrueVertex = truePart.TrueVertex;

  IsTruePrimaryPi0DecayPhoton      = truePart.IsTruePrimaryPi0DecayPhoton;
  IsTruePrimaryPi0DecayPhotonChild = truePart.IsTruePrimaryPi0DecayPhotonChild;

  /// store for each subdetector
  /// if the true truePart enter the active volume of the subdetector i
  /// what is the entrance position of the subdetector i
  ///  "    "  "   exit       "               "        

  anaUtils::CreateArray(DetCrossings, truePart.nDetCrossings);
  for (Int_t i=0;i<truePart.nDetCrossings;i++){
    DetCrossings[i] = truePart.DetCrossings[i]->Clone();
  }
  nDetCrossings = truePart.nDetCrossings;

  DetCrossingsVect.clear();

}

//********************************************************************
bool AnaTrueParticleB::CompareMomentum(const AnaTrueObjectC* p1, const AnaTrueObjectC* p2){
  //********************************************************************
  // function to sort particles in decreasing momentum order
  // set null pointer to be sorted the very last.

  const AnaTrueParticleB* t1 = dynamic_cast<const AnaTrueParticleB*>(p1);
  const AnaTrueParticleB* t2 = dynamic_cast<const AnaTrueParticleB*>(p2);


  Float_t m1 = -3e6;
  Float_t m2 = -3e6;
  if (t1) m1 = t1->Momentum;
  if (t2) m2 = t2->Momentum;

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
void AnaTrueParticleB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaTrueParticleB --------- " << std::endl;

  AnaTrueObjectC::Print();

  std::cout << "PDG:        " << PDG << std::endl;
  std::cout << "ParentID:   " << ParentID << std::endl;
  std::cout << "ParentPDG:  " << ParentPDG << std::endl;
  std::cout << "GParentID:  " << GParentID << std::endl;
  std::cout << "GParentPDG: " << GParentPDG << std::endl;
  std::cout << "Momentum:   " << Momentum << std::endl;
  std::cout << "Charge:     " << Charge << std::endl;
  std::cout << "Position:   " << Position[0]  << " " << Position[1]  << " " << Position[2] << " " << Position[3] << std::endl;
  std::cout << "Direction:  " << Direction[0] << " " << Direction[1] << " " << Direction[2] << std::endl;
  std::cout << "VertexID:   " << VertexID << std::endl;
}

//********************************************************************
AnaTrueVertexB::AnaTrueVertexB():AnaTrueObjectC(){
  //********************************************************************

  Detector = 0;

  NuEnergy      = -999;
  NuPDG         = -999;
  Bunch         = -999;

  anaUtils::ReserveArray(Position, 4);

  TrueParticles = NULL;
  nTrueParticles = 0;

  TrueParticlesIDsVect.clear();
}

//********************************************************************
AnaTrueVertexB::~AnaTrueVertexB(){
  //********************************************************************

  // Must delete array of pointers, since we re-create this every time we apply a selection
  if(TrueParticles != NULL) delete [] TrueParticles;
  TrueParticles = NULL;      

  TrueParticlesIDsVect.clear();
}

//********************************************************************
AnaTrueVertexB::AnaTrueVertexB(const AnaTrueVertexB& vertex):AnaTrueObjectC(vertex){
  //********************************************************************

  NuEnergy      = vertex.NuEnergy;
  NuPDG         = vertex.NuPDG;
  Bunch         = vertex.Bunch;
  Detector      = vertex.Detector;

  anaUtils::CopyArray(vertex.Position, Position, 4);

  anaUtils::CreateArray(TrueParticles, vertex.nTrueParticles);
  for (Int_t i=0;i<vertex.nTrueParticles;i++){
    TrueParticles[i] = vertex.TrueParticles[i];
  }

  nTrueParticles = vertex.nTrueParticles;

  TrueParticlesIDsVect.clear();
}

//********************************************************************
void AnaTrueVertexB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaTrueVertexB --------- " << std::endl;

  AnaTrueObjectC::Print();

  std::cout << "NuPDG:            " << NuPDG << std::endl;
  std::cout << "NuEnergy:         " << NuEnergy << std::endl;
  std::cout << "Bunch:            " << Bunch << std::endl;
  std::cout << "Detector:         " << Detector << std::endl;
  std::cout << "Position:         " << Position[0]  << " " << Position[1]  << " " << Position[2] << " " << Position[3] << std::endl;
  std::cout << "NTrueParticles:      " << nTrueParticles << std::endl;
}

//********************************************************************
AnaDelayedClustersB::AnaDelayedClustersB(){
  //********************************************************************
  MinTime = -999;
  MaxTime = -999;

  NHits = -999;
  RawChargeSum = -999;
}

//********************************************************************
AnaDelayedClustersB::AnaDelayedClustersB(const AnaDelayedClustersB& clusters){
  //********************************************************************

  MinTime = clusters.MinTime;
  MinTime = clusters.MaxTime;
  NHits   = clusters.NHits;
  RawChargeSum = clusters.RawChargeSum;
}

//********************************************************************
AnaBunchB::AnaBunchB():AnaBunchC(){
  //********************************************************************

  Vertices.clear();
  Particles.clear();

  DelayedClusters=NULL;
  nDelayedClusters=0;
}

//********************************************************************
AnaBunchB::~AnaBunchB(){
  //********************************************************************

  for (UInt_t i=0;i<Vertices.size();i++)
    delete Vertices[i];

  Vertices.clear();

  for (UInt_t i=0;i<Particles.size();i++)
    delete Particles[i];

  Particles.clear();

  for (Int_t i=0;i<nDelayedClusters;i++){
    delete DelayedClusters[i];
    DelayedClusters[i] = NULL;
  }
  nDelayedClusters = 0;
  if (DelayedClusters) delete [] DelayedClusters;
  DelayedClusters = NULL;    
}

//********************************************************************
AnaBunchB::AnaBunchB(const AnaBunchB& bunch):AnaBunchC(bunch){
  //********************************************************************

  Vertices.clear();
  for (UInt_t i=0;i<bunch.Vertices.size();i++)
    Vertices.push_back(bunch.Vertices[i]->Clone());

  Particles.clear();
  for (UInt_t i=0;i<bunch.Particles.size();i++)
    Particles.push_back(bunch.Particles[i]->Clone());

  nDelayedClusters = 0;

  //  anaUtils::CreateArray(DelayedClusters, bunch.nDelayedClusters);

  DelayedClusters = new AnaDelayedClustersB*[bunch.nDelayedClusters];
  for(int i = 0; i < bunch.nDelayedClusters; ++i){
    DelayedClusters[i] = NULL;
  }

  for (Int_t i=0;i<bunch.nDelayedClusters;i++){
    DelayedClusters[nDelayedClusters] = bunch.DelayedClusters[i]->Clone();
    nDelayedClusters++;
  }

}

//********************************************************************
void AnaBunchB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaBunchB --------- " << std::endl;

  AnaBunchC::Print();

  std::cout << "NVertices:        " << (int)Vertices.size()  << std::endl;
  std::cout << "NParticles:       " << (int)Particles.size()  << std::endl;
  std::cout << "NDelayedClusters: " << nDelayedClusters  << std::endl;
}

//********************************************************************
AnaVertexB* AnaBunchB::GetPrimaryVertex(){
  //********************************************************************

  if ((int)Vertices.size()==0) return NULL;

  AnaVertexB* vertex0 = Vertices.front();
  if (vertex0->PrimaryIndex == -1) {
    if (Bunch != vertex0->Bunch)
      std::cout << "WARNING: this vertex is not in this bunch " << Bunch << std::endl;
    return (Vertices.front());
  }

  std::vector<AnaVertexB*>::const_iterator it;
  for (it = Vertices.begin(); it != Vertices.end(); it++) {
    if ( (*it)->PrimaryIndex ==-1 ) {
      std::cout << "WARNING: here you are the PrimaryVertex with PrimaryIndex -1, but they are not properly sorted!" << std::endl;
      AnaVertexB* thisvertex= *it;
      if (Bunch != thisvertex->Bunch)
        std::cout << "WARNING: this vertex is not in this bunch " << Bunch << std::endl;
      return (*it);
    }
  }

  std::cout << "WARNING: Primary Vertex not found, here you are the vertex with PrimaryIndex: " << Vertices.front()->PrimaryIndex << std::endl;
  if (Bunch != vertex0->Bunch)
    std::cout << "WARNING: this vertex is not in this bunch " << Bunch << std::endl;
  return (Vertices.front());
}

//********************************************************************
bool AnaBunchB::IsEmpty() const{
  //********************************************************************
  return (Particles.empty() && Vertices.empty());
}

//********************************************************************
AnaFgdTimeBinB::AnaFgdTimeBinB(){
  //********************************************************************
  MinTime = -999;

  for (Int_t i=0;i<2;i++){
    NHits[i] = -999;
    RawChargeSum[i] = -999;
  }
}

//********************************************************************
AnaFgdTimeBinB::~AnaFgdTimeBinB(){
  //********************************************************************

}

//********************************************************************
AnaFgdTimeBinB::AnaFgdTimeBinB(const AnaFgdTimeBinB& bin){
  //********************************************************************

  MinTime = bin.MinTime;

  for (Int_t i=0;i<2;i++){
    NHits[i] = bin.NHits[i];
    RawChargeSum[i] = bin.RawChargeSum[i];
  }
}

//********************************************************************
void AnaFgdTimeBinB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaFgdTimeBinB --------- " << std::endl;

  std::cout << "MinTime:  " << MinTime << std::endl;
}

//********************************************************************
AnaSpillB::AnaSpillB():AnaSpillC(){
  //********************************************************************

  GeomID=999;
  NTotalTrueVertices = 999;
  NTotalTrueParticles   = 999;
  TrueVertices.clear();    
  TrueParticles.clear();    
  FgdTimeBins.clear();    
  OutOfBunch = NULL;
  EventInfo = NULL;
  Beam = NULL;
  DataQuality = NULL;
  //    isClone = false;
}

//********************************************************************
AnaSpillB::~AnaSpillB(){
  //********************************************************************

  // TrueVertex's are not cloned. Only delete them in the raw spill
  if (!isClone){
    for (UInt_t i=0;i<TrueVertices.size();i++)
      delete TrueVertices[i];    
  }

  TrueVertices.clear();    

  // TrueParticles are not cloned.  Only delete them in the raw spill
  if (!isClone){
    for (UInt_t i=0;i<TrueParticles.size();i++)
      delete TrueParticles[i];    
  }

  TrueParticles.clear();    

  for (UInt_t i=0;i<FgdTimeBins.size();i++)
    delete FgdTimeBins[i];    

  FgdTimeBins.clear();    


  if (OutOfBunch)
    delete OutOfBunch;

  if (EventInfo)
    delete EventInfo;

  if (Beam)
    delete Beam;

  if (DataQuality)
    delete DataQuality;

}

//********************************************************************
AnaSpillB::AnaSpillB(const AnaSpillB& spill):AnaSpillC(spill){
  //********************************************************************

  GeomID=spill.GeomID;

  NTotalTrueVertices = spill.NTotalTrueVertices;
  NTotalTrueParticles   = spill.NTotalTrueParticles;

  // Don't clone truth
  TrueVertices.clear();
  for (UInt_t i=0;i<spill.TrueVertices.size();i++)
    TrueVertices.push_back(spill.TrueVertices[i]);

  // Don't clone truth
  TrueParticles.clear();
  for (UInt_t i=0;i<spill.TrueParticles.size();i++)
    TrueParticles.push_back(spill.TrueParticles[i]);

  FgdTimeBins.clear();
  for (UInt_t i=0;i<spill.FgdTimeBins.size();i++)
    FgdTimeBins.push_back(spill.FgdTimeBins[i]->Clone());


  EventInfo = NULL;
  if (spill.EventInfo)
    EventInfo = spill.EventInfo->Clone();

  Beam = NULL;
  if (spill.Beam)
    Beam = spill.Beam->Clone();

  DataQuality = NULL;
  if (spill.DataQuality)
    DataQuality = spill.DataQuality->Clone();

  OutOfBunch = NULL;
  if (spill.OutOfBunch)
    OutOfBunch = spill.OutOfBunch->Clone();
}


//********************************************************************
AnaTrueParticleB* AnaSpillB::GetTrueParticleByID(int ID) {
  //********************************************************************

  for (std::vector<AnaTrueParticleB*>::const_iterator it = TrueParticles.begin(); it != TrueParticles.end(); it++){
    if ((*it)->ID == ID){
      return (*it);
    }
  }

  return NULL;

}

//********************************************************************
AnaTrueVertexB* AnaSpillB::GetTrueVertexByID(int ID) {
  //********************************************************************

  for (std::vector<AnaTrueVertexB*>::const_iterator it = TrueVertices.begin(); it != TrueVertices.end(); it++){
    if ((*it)->ID == ID){
      return (*it);
    }
  }

  return NULL;

}


//********************************************************************
AnaParticleB* AnaSpillB::GetParticleByUniqueID(int ID) {
  //********************************************************************

  std::vector<AnaBunchC*> allBunches = Bunches;
  if (OutOfBunch) allBunches.push_back(OutOfBunch);

  for (UInt_t i=0;i<allBunches.size();i++){
    AnaBunchB* bunch = static_cast<AnaBunchB*>(allBunches[i]);

    for (UInt_t j=0;j<bunch->Particles.size();j++){
      AnaParticleB* part = bunch->Particles[j];
      if (part && part->UniqueID == ID){
        return part;
      }  
    }
  }

  return NULL;

}
//********************************************************************
void AnaSpillB::associateTrueObjectToParticle(AnaRecObjectC* recoObject) {
  //********************************************************************
  if (!recoObject){
    return;
  }

  recoObject->TrueObject = NULL;
  AnaTrueParticleB* trueParticle = GetTrueParticleByID(recoObject->TrueID);
  if (trueParticle){
    recoObject->TrueObject = trueParticle;
  }



}
//********************************************************************
void AnaSpillB::RedoLinks(bool full){
  //********************************************************************
  //--------- This codes redo all links between objects after cloning or reading MiniTree -------------
  if (full){
    // AnaTrueVertexB
    for (std::vector<AnaTrueVertexB*>::iterator it = TrueVertices.begin(); it != TrueVertices.end();it++){
      AnaTrueVertexB* vertex = *it;
      vertex->nTrueParticles = 0;
      
      if (!vertex->TrueParticles){
        
        anaUtils::CreateArray(vertex->TrueParticles, (Int_t)vertex->TrueParticlesIDsVect.size());
      }
      for (std::vector<Int_t>::iterator it1 = vertex->TrueParticlesIDsVect.begin(); it1 != vertex->TrueParticlesIDsVect.end(); it1++){
        AnaTrueParticleB* trueParticle = GetTrueParticleByID(*it1);
        if (trueParticle){
          vertex->TrueParticles[vertex->nTrueParticles++] = trueParticle;
        }
      } 
    }

    // AnaTrueParticleB
    for (std::vector<AnaTrueParticleB*>::iterator it = TrueParticles.begin(); it != TrueParticles.end();it++){
      (*it)->TrueVertex = NULL;
      AnaTrueVertexB* trueVertex = GetTrueVertexByID((*it)->VertexID);
      if (trueVertex){
        (*it)->TrueVertex = trueVertex;
      }
    }
  }
  





  std::vector<AnaBunchC*> allBunches = Bunches;
  if (OutOfBunch) allBunches.push_back(OutOfBunch);

  for (UInt_t i=0;i<allBunches.size();i++){
    AnaBunchB* bunch = static_cast<AnaBunchB*>(allBunches[i]);

    for (UInt_t k=0;k<bunch->Particles.size();k++){
      AnaParticleB* part = bunch->Particles[k];

      if (full){
        associateTrueObjectToParticle(part);


        // Constituents

        AnaTrackB* track = dynamic_cast<AnaTrackB*>(bunch->Particles[k]);
        if (!track) continue;

        for (Int_t j = 0; j < track->nTPCSegments; j++){

          associateTrueObjectToParticle(track->TPCSegments[j]);
        }

        for (Int_t j = 0; j < track->nFGDSegments; j++){
          associateTrueObjectToParticle(track->FGDSegments[j]);
        }

        for (Int_t j = 0; j < track->nECALSegments; j++){
          associateTrueObjectToParticle(track->ECALSegments[j]);
        }

        for (Int_t j = 0;j < track->nSMRDSegments; j++){
          associateTrueObjectToParticle(track->SMRDSegments[j]);
        }

        for (Int_t j = 0; j < track->nP0DSegments; j++){
          associateTrueObjectToParticle(track->P0DSegments[j]);
        }
      }


      associateParticleToTrueParticle(part);
    }
    
    

    for (UInt_t j=0;j<bunch->Vertices.size();j++){
      AnaVertexB* vertex = bunch->Vertices[j];
      // Get true vertex

      if (full){
        vertex->TrueVertex = NULL;
        AnaTrueVertexB* trueVertex = GetTrueVertexByID(vertex->TrueID);
        if (trueVertex){
          vertex->TrueVertex = trueVertex;
        }
        // Particles
        
        vertex->nParticles = 0;
        
        if (!vertex->Particles){
          anaUtils::CreateArray(vertex->Particles, (Int_t)vertex->ParticlesIDsVect.size());
        }
        
        for (std::vector<Int_t>::iterator it = vertex->ParticlesIDsVect.begin(); it != vertex->ParticlesIDsVect.end(); it++){
          AnaParticleB* particle = GetParticleByUniqueID(*it);
          if (particle){
            vertex->Particles[vertex->nParticles++] = particle;
          }
        } 
      }
      

      associateVertexToTrueVertex(vertex);
      
      
      for (Int_t k=0;k<vertex->nParticles;k++){
        bool found=false;
        
        if (!vertex->Particles[k]) continue; // Particles in a vertex can be NULL in some cases (see oaAnalysisTreeConverter::FindParticle)
        for (UInt_t l=0;l<bunch->Particles.size();l++){
          if (vertex->Particles[k]->UniqueID == bunch->Particles[l]->UniqueID){
            // AnaVertexB::Particles
            vertex->Particles[k] = bunch->Particles[l];
            // AnaParticle::ReconVertices
            
            associateVertexToParticle(vertex->Particles[k], vertex);
            
            found=true;
            break;
          }
        }
        if (!found){
          for (UInt_t i2=0;i2<allBunches.size();i2++){
            if ((Int_t)i2==bunch->Bunch) continue;
            AnaBunchB* bunch2 = static_cast<AnaBunchB*>(allBunches[i2]);
            for (UInt_t l=0;l<bunch2->Particles.size();l++){
              if (vertex->Particles[k]->UniqueID == bunch2->Particles[l]->UniqueID){
                // AnaVertexB::Particles
                vertex->Particles[k] = bunch2->Particles[l];
                // AnaParticle::ReconVertices
                associateVertexToParticle(vertex->Particles[k], vertex);
                found=true;
                break;
              }                
            }
            if (found) break;
          }
        }
        
      }
    }
  }
  
  
}

//********************************************************************
void AnaSpillB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaSpillB --------- " << std::endl;

  if (EventInfo)
    EventInfo->Print();
  else
    std::cout << "NO Event Info available !!!" << std::endl;
  std::cout << "GeomID:              " << GeomID                    << std::endl;
  std::cout << "NBunches:            " << (int)Bunches.size()       << std::endl;
  std::cout << "NTotalTrueVertices:  " << NTotalTrueVertices        << std::endl;
  std::cout << "NSavedTrueVertices:  " << (int)TrueVertices.size()  << std::endl;
  std::cout << "NTotalTrueParticles: " << NTotalTrueParticles       << std::endl;
  std::cout << "NSavedTrueParticles: " << (int)TrueParticles.size() << std::endl;
  std::cout << "NFgdTimeBins:        " << (int)FgdTimeBins.size()   << std::endl;
  if (DataQuality){
    std::cout << "Good DQ:             " << DataQuality->GoodDaq      << std::endl;
    std::cout << "Good TimeDQ:         " << DataQuality->GoodTimeDaq  << std::endl;
  }
  else
    std::cout << "NO DataQuality Info available !!!" << std::endl;
  if (Beam){
    std::cout << "Good Spill:          " << Beam->GoodSpill << std::endl;
    std::cout << "POT since last Spill:" << Beam->POTSincePreviousSavedSpill << std::endl;
  }
  else
    std::cout << "NO Beam Info available !!!" << std::endl;
}

//********************************************************************
void AnaSpillB::CopyArraysIntoVectors(){
  //********************************************************************

  // Add OutOfBunch to the vector of bunches
  std::vector<AnaBunchC*> bunches = Bunches;
  if (OutOfBunch) bunches.push_back(OutOfBunch);

  for (std::vector<AnaBunchC*>::iterator it=bunches.begin();it!=bunches.end();it++){
    AnaBunchB* bunch = static_cast<AnaBunchB*>(*it);      
    for (UInt_t i=0;i<bunch->Particles.size();i++){
      AnaTrackB* track = dynamic_cast<AnaTrackB*>(bunch->Particles[i]);
      if (!track) continue;
      track->TPCSegmentsVect.clear();
      for (Int_t j=0;j<track->nTPCSegments;j++)
        track->TPCSegmentsVect.push_back(track->TPCSegments[j]);       

      track->FGDSegmentsVect.clear();
      for (Int_t j=0;j<track->nFGDSegments;j++)
        track->FGDSegmentsVect.push_back(track->FGDSegments[j]);

      track->ECALSegmentsVect.clear();
      for (Int_t j=0;j<track->nECALSegments;j++)
        track->ECALSegmentsVect.push_back(track->ECALSegments[j]);

      track->SMRDSegmentsVect.clear();
      for (Int_t j=0;j<track->nSMRDSegments;j++)
        track->SMRDSegmentsVect.push_back(track->SMRDSegments[j]);

      track->P0DSegmentsVect.clear();
      for (Int_t j=0;j<track->nP0DSegments;j++)
        track->P0DSegmentsVect.push_back(track->P0DSegments[j]);

    }      
    for (UInt_t i=0;i<bunch->Vertices.size();i++){
      AnaVertexB* vertex = bunch->Vertices[i];

      vertex->ParticlesIDsVect.clear();
      for (Int_t j=0;j<vertex->nParticles;j++){
        vertex->ParticlesIDsVect.push_back(vertex->Particles[j]->UniqueID);
      }
    }

  }


  for (std::vector<AnaTrueVertexB*>::iterator it=TrueVertices.begin();it!=TrueVertices.end();it++){
    AnaTrueVertexB* vertex = *it;
    vertex->TrueParticlesIDsVect.clear();
    for (Int_t j=0;j<vertex->nTrueParticles;j++)
      vertex->TrueParticlesIDsVect.push_back(vertex->TrueParticles[j]->ID);
  }
  
  
  for (std::vector<AnaTrueVertexB*>::iterator it=TrueVertices.begin();it!=TrueVertices.end();it++){
    AnaTrueVertexB* vertex = *it;
    vertex->TrueParticlesIDsVect.clear();
    for (Int_t j=0;j<vertex->nTrueParticles;j++)
      vertex->TrueParticlesIDsVect.push_back(vertex->TrueParticles[j]->ID);
  }
  
  for (std::vector<AnaTrueParticleB*>::iterator it=TrueParticles.begin();it!=TrueParticles.end();it++){
    AnaTrueParticleB* truePart = *it;
    truePart->DetCrossingsVect.clear();
    for (Int_t j=0;j<truePart->nDetCrossings;j++)
      truePart->DetCrossingsVect.push_back(truePart->DetCrossings[j]);
  }


}

//*****************************************************************************
void AnaSpillB::CopyVectorsIntoArrays(){
  //*****************************************************************************

  // Add OutOfBunch to the vector of bunches
  std::vector<AnaBunchC*> bunches = Bunches;
  if (OutOfBunch) bunches.push_back(OutOfBunch);

  // Copy the std::vectors into the arrays for AnaTrackB::XXXSegments
  for (std::vector<AnaBunchC*>::iterator it=bunches.begin();it!=bunches.end();it++){

    AnaBunchB* bunch = static_cast<AnaBunchB*>(*it);
    for (UInt_t i=0;i<bunch->Particles.size();i++){
      AnaTrackB* track = dynamic_cast<AnaTrackB*>(bunch->Particles[i]);
      if (!track) continue;
      track->nTPCSegments=0;
      for (UInt_t j=0;j<track->TPCSegmentsVect.size();j++)
        track->TPCSegments[track->nTPCSegments++]=track->TPCSegmentsVect[j];

      track->nFGDSegments=0;
      for (UInt_t j=0;j<track->FGDSegmentsVect.size();j++)
        track->FGDSegments[track->nFGDSegments++]=track->FGDSegmentsVect[j];

      track->nECALSegments=0;
      for (UInt_t j=0;j<track->ECALSegmentsVect.size();j++)
        track->ECALSegments[track->nECALSegments++]=track->ECALSegmentsVect[j];

      track->nSMRDSegments=0;
      for (UInt_t j=0;j<track->SMRDSegmentsVect.size();j++)
        track->SMRDSegments[track->nSMRDSegments++]=track->SMRDSegmentsVect[j];

      track->nP0DSegments=0;
      for (UInt_t j=0;j<track->P0DSegmentsVect.size();j++){
        track->P0DSegments[track->nP0DSegments++]=track->P0DSegmentsVect[j];}
    }
  }


  // Copy the std::vectors into the arrays for AnaTrueParticleB::DetCrossings
  for (std::vector<AnaTrueParticleB*>::iterator it=TrueParticles.begin();it!=TrueParticles.end();it++){
    AnaTrueParticleB* truePart = *it;
    truePart->nDetCrossings = 0;
    anaUtils::CreateArray(truePart->DetCrossings, (Int_t)truePart->DetCrossingsVect.size());
    for (UInt_t j=0;j<truePart->DetCrossingsVect.size();j++)
      truePart->DetCrossings[truePart->nDetCrossings++] = truePart->DetCrossingsVect[j];
  }

}

//********************************************************************
AnaEventInfoB::AnaEventInfoB(){
  //********************************************************************

  Run       = -999;
  SubRun    = -999;
  Event     = -999;
  IsMC      = false;
  IsSand    = false;
}

//********************************************************************
AnaEventInfoB::~AnaEventInfoB(){
  //********************************************************************


}

//********************************************************************
AnaEventInfoB::AnaEventInfoB(const AnaEventInfoB& spill){
  //********************************************************************
  Run       = spill.Run;
  SubRun    = spill.SubRun;
  Event     = spill.Event;
  IsMC      = spill.IsMC;
  IsSand    = spill.IsSand;
}

//********************************************************************
void AnaEventInfoB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaEventInfoB --------- " << std::endl;

  std::cout << "IsMC:               " << IsMC << std::endl;
  std::cout << "IsSand:             " << IsSand << std::endl;
  std::cout << "Run:                " << Run << std::endl;
  std::cout << "SubRun:             " << SubRun << std::endl;
  std::cout << "Evt:                " << Event << std::endl;
}

//********************************************************************
void AnaEventInfoB::SetIsSandMC(){
  //********************************************************************
  std::stringstream sRun;
  sRun << Run;
  IsSand = ((sRun.str())[4]=='7');
}


//********************************************************************
AnaDataQualityB::AnaDataQualityB(){
  //********************************************************************

  GoodDaq     = false;
  GoodTimeDaq = false;
}

//********************************************************************
AnaDataQualityB::AnaDataQualityB(const AnaDataQualityB& dq){
  //********************************************************************

  GoodDaq     = dq.GoodDaq;
  GoodTimeDaq = dq.GoodTimeDaq;
}

//********************************************************************
AnaBeamB::AnaBeamB(){
  //********************************************************************

  GoodSpill                     = -999;
  POTSincePreviousSavedSpill    = -999;
  SpillsSincePreviousSavedSpill = -999;
}

//********************************************************************
AnaBeamB::AnaBeamB(const AnaBeamB& beam){
  //********************************************************************

  GoodSpill                     = beam.GoodSpill;
  POTSincePreviousSavedSpill    = beam.POTSincePreviousSavedSpill;
  SpillsSincePreviousSavedSpill = beam.SpillsSincePreviousSavedSpill;
}

//********************************************************************
AnaVertexB::AnaVertexB():AnaRecObjectC(){
  //********************************************************************

  PrimaryIndex = -999;

  anaUtils::ReserveArray(Position, 4);

  Original     = NULL;
  TrueVertex   = NULL;
  Particles = NULL;
  nParticles = 0;
  TrueVerticesMatch.clear();

  ParticlesIDsVect.clear();
}

//********************************************************************
AnaVertexB::~AnaVertexB(){
  //********************************************************************
  // Must delete array of pointers, since we re-create this every time we apply a selection
  if(Particles != NULL) delete [] Particles;
  Particles = NULL;

  ParticlesIDsVect.clear();
}


//********************************************************************
AnaVertexB::AnaVertexB(const AnaVertexB& vertex):AnaRecObjectC(vertex){
  //********************************************************************

  PrimaryIndex = vertex.PrimaryIndex;

  anaUtils::CopyArray(vertex.Position, Position, 4);

  anaUtils::CreateArray(Particles, vertex.nParticles);   
  anaUtils::CopyArray(vertex.Particles, Particles, vertex.nParticles);

  nParticles   = vertex.nParticles;

  TrueVertex   = vertex.TrueVertex;

  // the associated true vertices
  TrueVerticesMatch.clear();
  for (UInt_t i=0;i<vertex.TrueVerticesMatch.size();i++)  TrueVerticesMatch.push_back(vertex.TrueVerticesMatch[i]);

  // A ponter to the original vertex
  Original = &vertex;

  ParticlesIDsVect.clear();
}

//********************************************************************
bool AnaVertexB::ComparePrimaryIndex(const AnaRecObjectC* p1, const AnaRecObjectC* p2){
  //********************************************************************

  // function to sort global vertices in increasing PrimaryIndex order

  const AnaVertexB* t1 = dynamic_cast<const AnaVertexB*>(p1);
  const AnaVertexB* t2 = dynamic_cast<const AnaVertexB*>(p2);

  // set null pointer to be 999 so they are sorted last
  Int_t m1 = 999;
  Int_t m2 = 999;
  if (t1) m1 = t1->PrimaryIndex;
  if (t2) m2 = t2->PrimaryIndex;

  // set nan to be 999 so they are sorted last
  if (m1 != m1) m1 = 999;
  if (m2 != m2) m2 = 999;

  // sort by PrimaryIndex
  if (m1 != m2 || ! t1 || ! t2) return m1 < m2;

  // else if same PrimaryIndex, sort by higher momentum constituent (->Particles should be already sorted by momentum)
  // TODO: we assume Particles are global tracks here, because not all particles have momentum
  if (t1->nParticles > 0 && t2->nParticles > 0) {
    if (t1->Particles[0] && t2->Particles[0] && t1->Particles[0] != t2->Particles[0])
      return static_cast<AnaTrackB*>(t1->Particles[0])->Momentum > static_cast<AnaTrackB*>(t2->Particles[0])->Momentum;
  }

  // else if same higher momentum particle, sort by number of constituent particles
  if (t1->nParticles != t2->nParticles) return t1->nParticles > t2->nParticles;

  // else if same constituents, sort by position.Z
  return t1->Position[2] < t2->Position[2];
}

//********************************************************************
void AnaVertexB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaVertexB --------- " << std::endl;

  AnaRecObjectC::Print();

  std::cout << "PrimaryIndex:        " << PrimaryIndex << std::endl;
  std::cout << "Position:            " << Position[0] << " " << Position[1] << " " << Position[2] << " " << Position[3] << std::endl;
  std::cout << "NReconParticles:     " << nParticles << std::endl;
  std::cout << "NTrueVerticesMatch:  " << (int)TrueVerticesMatch.size() << std::endl;
}

//********************************************************************
int AnaVertexB::GetTrueVertices(AnaTrueVertexB** arr){
  //********************************************************************

  int count = 0;

  std::vector<std::pair<AnaTrueVertexB*, AnaRecTrueMatchB> >::const_iterator it;
  for (it = TrueVerticesMatch.begin(); it != TrueVerticesMatch.end(); it++){
    arr[count] = it->first;
    count++;
  }

  return count;
}

//********************************************************************
AnaTrueVertexB* AnaVertexB::GetMainTrueVertex(bool warning){
  //********************************************************************
  if ((int)TrueVerticesMatch.size()==0) return NULL;
  if (warning && Bunch != TrueVerticesMatch.front().first->Bunch)
    std::cout << "WARNING: this true vertex is not in this bunch: " << Bunch << " vs " << TrueVerticesMatch.front().first->Bunch << std::endl;
  return TrueVerticesMatch.front().first;
}

//********************************************************************
Float_t AnaVertexB::GetMainTrueVertexCleanliness(){
  //********************************************************************

  if((int)TrueVerticesMatch.size()==0) {
    std::cout << "error: there is no true vertices associated to this global vertex" << std::endl;
    return 0;
  }

  if ( ! TrueVerticesMatch.front().first) {
    std::cout << "error: the main associated true vertex is null" << std::endl;
    return 0;
  }

  if (Bunch != TrueVerticesMatch.front().first->Bunch)
    std::cout << "WARNING: this true vertex is not in this bunch " << Bunch << std::endl;

  return TrueVerticesMatch.front().second.Cleanliness;
}

//********************************************************************
Float_t AnaVertexB::GetMainTrueVertexCompleteness(){
  //********************************************************************

  if((int)TrueVerticesMatch.size()==0) {
    std::cout << "error: there is no true vertices associated to this global vertex" << std::endl;
    return 0;
  }

  if ( ! TrueVerticesMatch.front().first) {
    std::cout << "error: the main associated true vertex is null" << std::endl;
    return 0;
  }

  if (Bunch != TrueVerticesMatch.front().first->Bunch)
    std::cout << "WARNING: this true vertex is not in this bunch " << Bunch << std::endl;

  return TrueVerticesMatch.front().second.Completeness;
}

//********************************************************************
Float_t AnaVertexB::GetTrueVertexCleanliness(const AnaTrueVertexB& trueVertex){
  //********************************************************************

  std::vector<std::pair<AnaTrueVertexB*, AnaRecTrueMatchB> >::const_iterator it;
  for (it = TrueVerticesMatch.begin(); it != TrueVerticesMatch.end(); it++) {
    if ( ! it->first) std::cout << "error: this true vertex is null" << std::endl;
    if ( ! it->first) continue;
    if (it->first->ID == trueVertex.ID) {
      if (Bunch != it->first->Bunch)
        std::cout << "WARNING: this true vertex is not in this bunch " << Bunch << std::endl;
      return (it->second.Cleanliness);
    }
  }

  std::cout << "ERROR: this true vertex seems not associated to this global vertex " << std::endl;
  return 0;
}

//********************************************************************
Float_t AnaVertexB::GetTrueVertexCompleteness(const AnaTrueVertexB& trueVertex){
  //********************************************************************

  std::vector<std::pair<AnaTrueVertexB*, AnaRecTrueMatchB> >::const_iterator it;
  for (it = TrueVerticesMatch.begin(); it != TrueVerticesMatch.end(); it++) {
    if ( ! it->first) std::cout << "error: this true vertex is null" << std::endl;
    if ( ! it->first) continue;
    if (it->first->ID == trueVertex.ID) {
      if (Bunch != it->first->Bunch)
        std::cout << "WARNING: this true vertex is not in this bunch " << Bunch << std::endl;
      return (it->second.Completeness);
    }
  }

  std::cout << "ERROR: this true vertex seems not associated to this global vertex " << std::endl;
  return 0;
}

//********************************************************************
AnaEventSummaryB::AnaEventSummaryB(): AnaEventSummaryC() {
  //********************************************************************
  // std::cout << "Initializing Event Summary!" << std::endl;

  for(int i = 0; i < SampleId::kNSamples; ++i){



    LeptonCandidate[i]  = NULL;

    PionCandidate[i]    = NULL;

    ProtonCandidate[i]  = NULL;

    RooVertexIndex[i] = -1;
    TrueVertex[i] = NULL;

    for(int j = 0; j < 4; ++j){
      VertexPosition[i][j] = -999;
      LeptonPositionStart[i][j]   = -999;
      LeptonPositionEnd[i][j]   = -999;

    }


    for(int j = 0; j < 3; ++j){
      PionDirection[i][j]   = -999;
      ProtonDirection[i][j] = -999;

      LeptonDirectionStart[i][j]   = -999;
      LeptonDirectionEnd[i][j]   = -999;
    }


    LeptonMomentum[i] = -999;
    ProtonMomentum[i] = -999;
    PionMomentum[i]   = -999;

    SelPionTopo[i]   = SelTopoId::kPionUnassigned;


    SelProtonTopo[i] = SelTopoId::kProtonUnassigned;

  }

  EventSample   = SampleId::kUnassigned;


}



//********************************************************************
void AnaEventSummaryB::ResetSummary(){
  //********************************************************************

  for(int i = 0; i < SampleId::kNSamples; ++i){

    LeptonCandidate[i]  = NULL;

    PionCandidate[i]    = NULL;

    ProtonCandidate[i]  = NULL;

    RooVertexIndex[i] = -1;
    TrueVertex[i] = NULL;

    for(int j = 0; j < 4; ++j){
      VertexPosition[i][j] = -999;
      LeptonPositionStart[i][j]   = -999;
      LeptonPositionEnd[i][j]   = -999;

      
    }

    for(int j = 0; j < 3; ++j){
      PionDirection[i][j]   = -999;
      ProtonDirection[i][j] = -999;
      LeptonDirectionStart[i][j]   = -999;
      LeptonDirectionEnd[i][j]   = -999;

    }

  
    LeptonMomentum[i] = -999;
    ProtonMomentum[i] = -999;
    PionMomentum[i]   = -999;


    SelPionTopo[i]   = SelTopoId::kPionUnassigned;


    SelProtonTopo[i] = SelTopoId::kProtonUnassigned;

  }

  EventSample   = SampleId::kUnassigned;




}

//********************************************************************
AnaEventB::AnaEventB():AnaEventC(){
  //********************************************************************

  Particles = NULL;
  Vertices = NULL;
  TrueParticles = NULL;
  TrueVertices = NULL;
  FgdTimeBins = NULL;
  nParticles = 0;
  nVertices = 0;
  nFgdTimeBins = 0;
  nTrueParticles = 0;
  nTrueVertices = 0;
  Beam = NULL;
  DataQuality = NULL;

  DelayedClusters=NULL;
  nDelayedClusters=0;

  Summary = new AnaEventSummaryB();
}

//********************************************************************
AnaEventB::~AnaEventB(){
  //********************************************************************

  for (Int_t i=0;i<nParticles;i++){
    delete Particles[i];
    Particles[i] = NULL;
  }
  nParticles = 0;    
  if (Particles) delete [] Particles;
  Particles = NULL;

  for (Int_t i=0;i<nVertices;i++){
    delete Vertices[i];
    Vertices[i] = NULL;
  }
  nVertices = 0;
  if (Vertices) delete [] Vertices;
  Vertices = NULL;    

  // TrueParticles are not cloned.  Only delete them in the raw spill
  if (!isClone){
    for (Int_t i=0;i<nTrueParticles;i++){
      delete TrueParticles[i];
      TrueParticles[i] = NULL;
    }
  }
  nTrueParticles = 0;
  if (TrueParticles) delete [] TrueParticles;
  TrueParticles = NULL;

  // TrueVertex's are not cloned. Only delete them in the raw spill
  if (!isClone){
    for (Int_t i=0;i<nTrueVertices;i++){
      delete TrueVertices[i];
      TrueVertices[i] = NULL;
    }
  }

  nTrueVertices = 0;
  if (TrueVertices) delete [] TrueVertices;
  TrueVertices = NULL;

  for (Int_t i=0;i<nFgdTimeBins;i++){
    delete FgdTimeBins[i];
    FgdTimeBins[i] = NULL;
  }

  nFgdTimeBins = 0;
  if (FgdTimeBins) delete [] FgdTimeBins;
  FgdTimeBins = NULL;

  if (Beam){
    delete Beam;
    Beam = NULL;
  }

  if (DataQuality){
    delete DataQuality;
    DataQuality = NULL;
  }

  for (Int_t i=0;i<nDelayedClusters;i++){
    delete DelayedClusters[i];
    DelayedClusters[i] = NULL;
  }
  nDelayedClusters = 0;
  if (DelayedClusters) delete [] DelayedClusters;
  DelayedClusters = NULL;

}

//********************************************************************
void AnaEventB::Copy(const AnaEventC& eventC, bool copyBunchInfo, bool cloneTruth){
  //********************************************************************

  //    AnaEventC::Copy(event,copyBunchInfo,cloneTruth);

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventC);

  if (copyBunchInfo){
    nParticles = 0;
    anaUtils::CreateArray(Particles, event.nParticles);
    for (Int_t i=0;i<event.nParticles;i++){
      Particles[nParticles] = event.Particles[i]->Clone();
      nParticles++;
    }
    nVertices = 0;
    anaUtils::CreateArray(Vertices, event.nVertices);
    for (Int_t i=0;i<event.nVertices;i++){
      Vertices[nVertices] = event.Vertices[i]->Clone();
      nVertices++;
    }
    //        Weight = event.Weight;
    Bunch = event.Bunch;
    //        Summary = event.Summary;
  }

  nTrueVertices = 0;
  anaUtils::CreateArray(TrueVertices, event.nTrueVertices);
  for (Int_t i=0;i<event.nTrueVertices;i++){
    if (cloneTruth){
      TrueVertices[nTrueVertices] = event.TrueVertices[i]->Clone();
      // must clear particles since we need to redo the links below
      TrueVertices[nTrueVertices]->nTrueParticles = 0;
      nTrueVertices++;
    }
    else{
      TrueVertices[nTrueVertices] = event.TrueVertices[i];
      nTrueVertices++;
    }
  }

  nTrueParticles = 0;
  anaUtils::CreateArray(TrueParticles, event.nTrueParticles);
  for (Int_t i=0;i<event.nTrueParticles;i++){
    if (cloneTruth){
      TrueParticles[nTrueParticles] = event.TrueParticles[i]->Clone();
      for(int j = 0; j < nTrueVertices; ++j){
        if(TrueParticles[nTrueParticles]->VertexID == TrueVertices[j]->ID){
          // Associate the vertex to this particle
          TrueParticles[nTrueParticles]->TrueVertex = TrueVertices[j];

          // add this particle to the list of true particles in the true vertex
          if(TrueVertices[j]->nTrueParticles == 0){
            anaUtils::CreateArray(TrueVertices[j]->TrueParticles, event.nTrueParticles);
          }
          TrueVertices[j]->TrueParticles[TrueVertices[j]->nTrueParticles] = TrueParticles[nTrueParticles];	
          TrueVertices[j]->nTrueParticles++;
          break;
        }
      } 
      nTrueParticles++;
    }
    else{
      TrueParticles[nTrueParticles] = event.TrueParticles[i];
      nTrueParticles++;
    }
  }

  nFgdTimeBins = 0;
  anaUtils::CreateArray(FgdTimeBins, event.nFgdTimeBins);
  for (Int_t i=0;i<event.nFgdTimeBins;i++){
    FgdTimeBins[nFgdTimeBins] = event.FgdTimeBins[i]->Clone();
    nFgdTimeBins++;
  }


  // Fill the FGD time bins vector
  nDelayedClusters = 0;
  //  anaUtils::CreateArray(DelayedClusters, event.nDelayedClusters);

  DelayedClusters = new AnaDelayedClustersB*[event.nDelayedClusters];
  for(int i = 0; i < event.nDelayedClusters; ++i){
    DelayedClusters[i] = NULL;
  }
  for (Int_t i=0;i<event.nDelayedClusters;i++){
    DelayedClusters[nDelayedClusters] = event.DelayedClusters[i]->Clone();
    nDelayedClusters++;
  }


  EventInfo = event.EventInfo;

  Beam = NULL;
  if (event.Beam)
    Beam = event.Beam->Clone();

  DataQuality = NULL;
  if (event.DataQuality)
    DataQuality = event.DataQuality->Clone();

}

//********************************************************************
AnaEventB::AnaEventB(const AnaEventB& event):AnaEventC(event){
  //********************************************************************

  // copy bunch info but don't clone truth
  Copy(event, true, false);
}

//********************************************************************
void AnaEventB::Print() const{
  //********************************************************************

  std::cout << "-------- AnaEventB --------- " << std::endl;

  EventInfo.Print();

  std::cout << "Bunch:              " << Bunch                    << std::endl;
  std::cout << "NParticles:         " << nParticles               << std::endl;
  std::cout << "NVertices:          " << nVertices                << std::endl;
  std::cout << "NTrueParticles:     " << nTrueParticles           << std::endl;
  std::cout << "NTrueVertices:      " << nTrueVertices            << std::endl;
  std::cout << "NFgdTimeBins:       " << nFgdTimeBins             << std::endl;
  std::cout << "Good DQ:            " << DataQuality->GoodDaq     << std::endl;
  std::cout << "Good TimeDQ:        " << DataQuality->GoodTimeDaq << std::endl;
  std::cout << "Good Spill:         " << Beam->GoodSpill          << std::endl;
}

//********************************************************************
std::string AnaEventB::GetEventInfoString() const{
  //********************************************************************

  std::stringstream sRun;
  sRun << EventInfo.Run;

  std::stringstream sSubRun;
  sSubRun << EventInfo.SubRun;

  std::stringstream sEvent;
  sEvent << EventInfo.Event;

  std::stringstream sBunch;
  sBunch << Bunch;

  return "("+sRun.str()+"/"+sSubRun.str()+"/"+sEvent.str()+"/"+sBunch.str()+")";
}

//*****************************************************************************
AnaEventB::AnaEventB(const AnaSpillB& spill, const AnaBunchB& bunch){
  //*****************************************************************************

  nEventBoxes=0;
  for (UInt_t i=0;i<NMAXEVENTBOXES;i++)
    EventBoxes[i]=NULL;

  // The initial weight of the Event is 1;
  Weight=1;

  // Must create a summary object when we create an event
  // This is initialised to NULL and SampleId::kUnassigned, so you know it has not passed a selection
  Summary = new AnaEventSummaryB();


  UniqueID = 0;
  isClone = false;  
  Particles = NULL;
  Vertices = NULL;
  TrueParticles = NULL;
  TrueVertices = NULL;
  FgdTimeBins = NULL;
  nParticles = 0;
  nVertices = 0;
  nFgdTimeBins = 0;
  nTrueParticles = 0;
  nTrueVertices = 0;
  Beam = NULL;
  DataQuality = NULL;

  //------ Copy from Spill and Bunch ----------------

  Weight      = bunch.Weight;
  Bunch       = bunch.Bunch;
  EventInfo   = *spill.EventInfo;
  Beam        = spill.Beam->Clone();
  DataQuality = spill.DataQuality->Clone();

  // Fill the recon particles vector
  nParticles = 0;
  anaUtils::CreateArray(Particles, bunch.Particles.size());
  for (UInt_t i=0;i<bunch.Particles.size();i++){
    Particles[nParticles] = bunch.Particles[i]->Clone();
    nParticles++;
  }

  // Fill the recon vertices vector
  nVertices = 0;
  anaUtils::CreateArray(Vertices, bunch.Vertices.size());
  for (UInt_t i=0;i<bunch.Vertices.size();i++){
    Vertices[nVertices] = bunch.Vertices[i]->Clone();
    nVertices++;
  }

  // Fill the true particles vector
  nTrueParticles = 0;
  anaUtils::CreateArray(TrueParticles, spill.TrueParticles.size());
  for (UInt_t i=0;i<spill.TrueParticles.size();i++){
    TrueParticles[nTrueParticles] = spill.TrueParticles[i]->Clone();
    nTrueParticles++;
  }

  // Fill the true vertices vector
  nTrueVertices = 0;
  anaUtils::CreateArray(TrueVertices, spill.TrueVertices.size());
  for (UInt_t i=0;i<spill.TrueVertices.size();i++){
    TrueVertices[nTrueVertices] = spill.TrueVertices[i]->Clone();
    nTrueVertices++;
  }

  // Fill the FGD time bins vector
  nFgdTimeBins = 0;
  anaUtils::CreateArray(FgdTimeBins, spill.FgdTimeBins.size());
  for (UInt_t i=0;i<spill.FgdTimeBins.size();i++){
    FgdTimeBins[nFgdTimeBins] = spill.FgdTimeBins[i]->Clone();
    nFgdTimeBins++;
  }

  // Fill the FGD time bins vector
  nDelayedClusters = 0;
  //  anaUtils::CreateArray(DelayedClusters, bunch.nDelayedClusters);

  DelayedClusters = new AnaDelayedClustersB*[bunch.nDelayedClusters];
  for(int i = 0; i < bunch.nDelayedClusters; ++i){
    DelayedClusters[i] = NULL;
  }

  for (Int_t i=0;i<bunch.nDelayedClusters;i++){
    DelayedClusters[nDelayedClusters] = bunch.DelayedClusters[i]->Clone();
    nDelayedClusters++;
  }

}
