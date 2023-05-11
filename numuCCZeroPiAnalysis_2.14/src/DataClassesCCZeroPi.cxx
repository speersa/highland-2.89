#include "DataClassesCCZeroPi.hxx"
#include "BasicUtils.hxx"


// ------------- IMPORTANT -------------------
// Conditional compilation for momentum by range calculation (because it needs highlandRecPack, who needs RECPACK)
// Disabled by default. 
// If the line below (#define PRANGE) is uncommented, we should also uncomment "#use highlandRecPack * highland" in the requirements file
// Notice that prange calculation should be also enabled in the parameters file
// -----------------------------------
//#define PRANGE
#ifdef  PRANGE
#include "AnaRecPackManager.hxx"
#endif


//********************************************************************
MomRangeBox::MomRangeBox(){
  //********************************************************************
  MuonCandidate = NULL;
  ProtonCandidate = NULL;

  muon_momrange = -999.;
  muon_momrange_vertex = -999.;
  proton_momrange = -999.;
  proton_momrange_vertex = -999.;

  _selmu_momrange = -999.;
  _selmu_momrange_vertex = -999.;
  _selp_momrange = -999.;
  _selp_momrange_vertex = -999.;

  _n_selp_momrange = 0;
  _n_selmu_momrange = 0;
  _n_selp_momrange_vertex = 0;
  _n_selmu_momrange_vertex = 0;

  _computed_selp_momrange = false;
  _computed_selmu_momrange = false;
  _computed_selp_momrange_vertex = false;
  _computed_selmu_momrange_vertex = false;
}

//********************************************************************
void MomRangeBox::UpdateInputs(AnaTrackB* MuonCandidateBox, AnaTrackB* ProtonCandidateBox){ 
  //********************************************************************
  if (MuonCandidateBox != MuonCandidate){
    MuonCandidate = MuonCandidateBox;
    _computed_selmu_momrange         = false;
    _computed_selmu_momrange_vertex  = false;
    _computed_selp_momrange_vertex = false;

    if(ProtonCandidateBox != ProtonCandidate){
      ProtonCandidate = ProtonCandidateBox; 
      _computed_selp_momrange = false;
      return;
    }
  }
  else if (ProtonCandidateBox != ProtonCandidate){
    ProtonCandidate = ProtonCandidateBox;
    _computed_selmu_momrange_vertex  = false; 
    _computed_selp_momrange = false;
    _computed_selmu_momrange_vertex  = false;
  }

  return;
}


//********************************************************************
Float_t MomRangeBox::selp_momrange_vertex(){
  //********************************************************************

  if(_computed_selp_momrange_vertex){
    return _selp_momrange_vertex;
  }

  _selp_momrange_vertex = -999.;
  if(!ProtonCandidate)
    return _selp_momrange_vertex;

  if (anaUtils::TrackUsesDet(*ProtonCandidate, SubDetId::kTPC))
    return _selp_momrange_vertex;


  if(!MuonCandidate)
    return _selp_momrange_vertex;  

  if (!anaUtils::TrackUsesDet(*MuonCandidate, SubDetId::kTPC))
    return _selp_momrange_vertex;

  // at this point one has two candidates that can be used to calculate the momentum from range  
  // first check whether we already have a calculation performed for these two candidates
  for (int i=0; i<_n_selp_momrange_vertex; i++){
    if (_selp_momrange_vertex_inputs[i].first == MuonCandidate &&
        _selp_momrange_vertex_inputs[i].second == ProtonCandidate){ 
      _computed_selp_momrange_vertex = true; 
      _selp_momrange_vertex = _selp_momrange_vertex_values[i];
      return _selp_momrange_vertex; 
    }
  }

  // add new element to the arrays 
  TVector3 vertex = anaUtils::ArrayToTVector3(MuonCandidate->PositionStart); 
#ifdef  PRANGE
  _selp_momrange_vertex = (float)(ND::tman().GetMomentumFromRangeLinear(ProtonCandidate, vertex,  "Proton")); 
#endif
  _selp_momrange_vertex_values[_n_selp_momrange_vertex] = _selp_momrange_vertex; 
  _selp_momrange_vertex_inputs[_n_selp_momrange_vertex] = std::make_pair(MuonCandidate, ProtonCandidate); 
  _n_selp_momrange_vertex++; //increment the counter

  _computed_selp_momrange_vertex = true; 
  return _selp_momrange_vertex; 
}

//********************************************************************
Float_t MomRangeBox::selmu_momrange_vertex(){
  //********************************************************************

  if(_computed_selmu_momrange_vertex){
    return _selmu_momrange_vertex;
  }

  _selmu_momrange_vertex = -999.;
  if(!MuonCandidate)
    return _selmu_momrange_vertex;

  if (anaUtils::TrackUsesDet(*MuonCandidate, SubDetId::kTPC))
    return _selmu_momrange_vertex;


  if(!ProtonCandidate)
    return _selmu_momrange_vertex;  

  if (!anaUtils::TrackUsesDet(*ProtonCandidate, SubDetId::kTPC))
    return _selmu_momrange_vertex;

  // at this point one has two candidates that can be used to calculate the momentum from range  
  // first check whether we already have a calculation performed for these two candidates
  for (int i=0; i<_n_selmu_momrange_vertex; i++){
    if (_selmu_momrange_vertex_inputs[i].first == MuonCandidate &&
        _selmu_momrange_vertex_inputs[i].second == ProtonCandidate){ 
      _computed_selmu_momrange_vertex = true; 
      _selmu_momrange_vertex = _selmu_momrange_vertex_values[i];
      return _selmu_momrange_vertex; 
    }
  }

  // add new element to the arrays 
  TVector3 vertex = anaUtils::ArrayToTVector3(ProtonCandidate->PositionStart); 
#ifdef  PRANGE
  _selmu_momrange_vertex = (float)(ND::tman().GetMomentumFromRangeLinear(MuonCandidate, vertex,  "Muon")); 
#endif
  _selmu_momrange_vertex_values[_n_selmu_momrange_vertex] = _selmu_momrange_vertex; 
  _selp_momrange_vertex_inputs[_n_selmu_momrange_vertex]  = std::make_pair(MuonCandidate, ProtonCandidate); 
  _n_selmu_momrange_vertex++; //increment the counter

  _computed_selmu_momrange_vertex = true; 
  return _selmu_momrange_vertex; 
}

//********************************************************************
Float_t MomRangeBox::selp_momrange(){
  //********************************************************************

  if(_computed_selp_momrange){
    return _selp_momrange;
  }

  _selp_momrange = -999.;
  if(!ProtonCandidate)
    return _selp_momrange;

  if (anaUtils::TrackUsesDet(*ProtonCandidate, SubDetId::kTPC))
    return _selp_momrange;

  // at this point one has candidate(s) that can be used to calculate the momentum from range  
  // first check whether we already have a calculation performed for the candidate(s)
  for (int i=0; i<_n_selp_momrange_vertex; i++){
    if (_selp_momrange_inputs[i] == ProtonCandidate){ 
      _computed_selp_momrange = true;
      _selp_momrange = _selp_momrange_values[i]; 
      return _selp_momrange;
    }
  }

  // add new element to the arrays 
#ifdef  PRANGE
  _selp_momrange = (float)(ND::tman().GetMomentumFromRangeLinear(ProtonCandidate,  "Proton")); 
#endif 
  _selp_momrange_values[_n_selp_momrange] =  _selp_momrange; 
  _selp_momrange_inputs[_n_selp_momrange] = ProtonCandidate; 
  _n_selp_momrange++; //increment the counter
  _computed_selp_momrange = true;
  return _selp_momrange;
}

//********************************************************************
Float_t MomRangeBox::selmu_momrange(){
  //********************************************************************

  if(_computed_selmu_momrange)
    return _selmu_momrange;

  _selmu_momrange = -999.;
  if(!MuonCandidate)
    return _selmu_momrange;

  if (anaUtils::TrackUsesDet(*MuonCandidate, SubDetId::kTPC))
    return _selp_momrange;

  // at this point one has candidate(s) that can be used to calculate the momentum from range  
  // first check whether we already have a calculation performed for the candidate(s)
  for (int i=0; i<_n_selmu_momrange_vertex; i++){
    if (_selp_momrange_inputs[i] == ProtonCandidate){ 
      _computed_selmu_momrange = true;
      _selmu_momrange = _selmu_momrange_values[i]; 
      return _selmu_momrange;
    }
  }

  // add new element to the arrays 
#ifdef  PRANGE
  _selmu_momrange = (float)(ND::tman().GetMomentumFromRangeLinear(MuonCandidate,  "Muon")); 
#endif  
  _selmu_momrange_values[_n_selmu_momrange] =  _selmu_momrange; 
  _selmu_momrange_inputs[_n_selmu_momrange] = ProtonCandidate; 
  _n_selmu_momrange++; //increment the counter
  _computed_selmu_momrange = true;
  return _selmu_momrange;
}

