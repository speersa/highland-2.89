#ifndef DataClassesCCZeroPixsec_hxx
#define DataClassesCCZeroPixsec_hxx

#include "DataClasses.hxx"
#include "BaseDataClasses.hxx"
#include "AnalysisUtils.hxx"

const UInt_t NMAXCHANGES = 10; //max number of changes of lepton/proton candidates due to systematics variations

class MomRangeBox{
public:
 
  MomRangeBox();
  virtual ~MomRangeBox(){}
  
  /// Muon and proton candidates
  AnaTrackB* MuonCandidate;
  AnaTrackB* ProtonCandidate;

  /// Update the information
  void UpdateInputs(AnaTrackB* MuonCandidateBox, AnaTrackB* ProtonCandidateBox); 
      
  /// Momentum by range values to be modified by systematics variations
  Float_t muon_momrange;
  Float_t muon_momrange_vertex;
  Float_t proton_momrange;
  Float_t proton_momrange_vertex;
  
  void compute_muon_momrange(){
   muon_momrange = selmu_momrange(); 
  }
  void compute_muon_momrange_vertex(){
   muon_momrange_vertex = selmu_momrange_vertex(); 
  }
  void compute_proton_momrange(){
   proton_momrange = selp_momrange();
  }
  void compute_proton_momrange_vertex(){
    proton_momrange_vertex = selp_momrange_vertex(); 
  }
  
private:
 
  /// Return the momentum by range values
  Float_t selp_momrange();
  Float_t selmu_momrange();
  Float_t selp_momrange_vertex();
  Float_t selmu_momrange_vertex();

  /// Original values, those NOT to be modified by systematics variations
  Float_t _selmu_momrange;
  Float_t _selmu_momrange_vertex;
  Float_t _selp_momrange;
  Float_t _selp_momrange_vertex;

  /// Whether the mom-range was already computed
  bool _computed_selp_momrange;
  bool _computed_selmu_momrange;
  bool _computed_selp_momrange_vertex;
  bool _computed_selmu_momrange_vertex;

  /// Arrays used to store mom-range values already computed and corresponding candidate inputs
  std::pair<AnaTrackB*, AnaTrackB*> _selp_momrange_vertex_inputs[NMAXCHANGES];  
  std::pair<AnaTrackB*, AnaTrackB*> _selmu_momrange_vertex_inputs[NMAXCHANGES];
  
  Float_t _selp_momrange_vertex_values[NMAXCHANGES];  
  Float_t _selmu_momrange_vertex_values[NMAXCHANGES]; 

  AnaTrackB* _selp_momrange_inputs[NMAXCHANGES];
  AnaTrackB* _selmu_momrange_inputs[NMAXCHANGES];
 
  Float_t _selp_momrange_values[NMAXCHANGES];  
  Float_t _selmu_momrange_values[NMAXCHANGES]; 
  
  /// Counters
  int _n_selp_momrange;
  int _n_selmu_momrange;
  int _n_selp_momrange_vertex;
  int _n_selmu_momrange_vertex;
};


#endif
