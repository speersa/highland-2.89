#ifndef numuCCZeroPiAnalysis_h
#define numuCCZeroPiAnalysis_h

#include "numuCCAnalysis.hxx"
#include "numuCCZeroPiSelection.hxx"
//#include "numuFGD2CCZeroPiSelection.hxx"
#include "AnalysisUtils.hxx"
#include "OutputManager.hxx"
#include "DataClassesCCZeroPi.hxx"
#include "NuDirUtils.hxx"

class numuCCZeroPiAnalysis: public baseTrackerAnalysis {
public:
  numuCCZeroPiAnalysis(AnalysisAlgorithm* ana=NULL);
  virtual ~numuCCZeroPiAnalysis(){}

  //---- These are mandatory functions

  void DefineSelections();
  void DefineCorrections();
  void DefineSystematics();
  void DefineConfigurations();
  void DefineMicroTrees(bool addBase=true);
  void DefineTruthTree();
  bool Initialize();
  void InitializeConfiguration();

  void FillMicroTrees(bool addBase=true);
  void FillToyVarsInMicroTrees(bool addBase=true);

  bool CheckFillTruthTree(const AnaTrueVertex& vtx);

  //---------------------------------------

  void FillCategories();

  inline void SetEnableMomRange(bool enable){
    _prangeEnabled = enable;
  }

  inline void SetEnableMomRangeVertex(bool enable){
    _prangeVertexEnabled = enable; 
  }

  inline void SetEnableMomRangeMuon(bool enable){
    _prangeMuon = enable;
  }

  inline void SetEnableMomRangeProton(bool enable){
    _prangeProton = enable; 
  }


  inline void SetFillGenInfo(bool enable){
    _fillGenInfo = enable; 
  }
  
  using baseAnalysis::FillTruthTree;
  void FillTruthTree(const AnaTrueVertex& vtx);
  //--------------------
 
  void ProcessMomRange();

protected:

  const AnaBoxCCZeroPi& numu_cczeropi_box(){return static_cast<const AnaBoxCCZeroPi&>( box() );}

  numuCCAnalysis* _numuCCAnalysis;

  void FillMuonCandidateInfo();

  void FillProtonCandidateInfo();
  
  void FillECalVetoInfo();

  void FillHMP_TrueInfo(); 
  
  void FillHMP_ToyVars(); 
  
  void FillGeneratorInfo();

  void FillMECInfo();

  void FillMECToyVarsInMicroTrees();

  MomRangeBox* _mom_range_box;
  MomRangeBox& momrange_box(){return *_mom_range_box;}
  
  /// Use some functions from psycheCore/Versioning.hxx package since they are defined as private there (for some reason)
  /// Check wether a software version is prior to another
  bool CheckBeforeVersion(const std::string& version, const std::string& version0);

  /// Parse the version, revision and patch numbers
  void ParseSoftwareVersion(const std::string& version, int& v, int& r, int& p);
  
public:
  enum enumStandardMicroTrees_numuCCZeroPiAnalysis{        
    HM_pos= numuCCAnalysis::enumStandardMicroTreesLast_numuCCAnalysis + 1,
    
    //FGD2 and FGD1 variables
    sample_fgdlayer,  // samples + all fgds split into x and y: kFgd1MuTpcX,.. kFgd1MuTpcY,.. kFgd2MuTpcY,..  
    sample_fgd2layer_xsec, // samples + fgd is split into x and y layers based on the cc0pi xsec definition
    
    // Same as above but using the closest (in Z) actual det layer in case the
    // reco pos is not associated to any layer
    sample_clst_fgdlayer,  // samples + all fgds split into x and y: kFgd1MuTpcX,.. kFgd1MuTpcY,.. kFgd2MuTpcY,..  
    sample_clst_fgd2layer_xsec, // samples + fgd is split into x and y layers based on the cc0pi xsec definition
    
    
    // Bwd migration flag
    flag_isFgdBwdMigrated, 
    
    // Z position of the vertex --> separate from selvtx_pos, since the former is a toy variable
    selvtx_posZ,
    
    //very basic vars for HMP
    selHMP_mom, 
    selHMP_dir, 
    selHMP_pos, 
    selHMP_truemom, 
    selHMP_truedir, 
    selHMP_truepos, 
    selHMP_truepdg, 
   
    //Reco FGD2 module
    FGD2_reco_module,             //  defined by Vertex (TPC muon/TPC proton/FGD muon)
    FGD2_GV_reco_module,          //  FGD2 module defined by the global vertex 
    FGD2_muon_hit_reco_module,    //  FGD2 module define by hit pos (closest to the start point) of muon candidate
    FGD2_proton_hit_reco_module,  //  FGD2 module define by hit pos (closest to the start point) of proton candidate

    // Muon candidate
    selmu_invpt,
    selmu_charge,
    selmu_trueinvpt,
    selmu_truecharge,
    selmu_truedir,
    selmu_length,
    //Direction start and momentum for bwd muon hypothesis
    selmu_Bwd_mom,
    selmu_Bwd_costheta,
    //Timing
    selmu_Flag_FGD1_FGD2,
    selmu_FGD1_FGD2,
    selmu_Flag_P0D_FGD1,
    selmu_P0D_FGD1,
    selmu_Flag_ECal_FGD1,
    selmu_ECal_FGD1,
    selmu_Flag_ECal_FGD2,
    selmu_ECal_FGD2,
    nmichel1,
    nmichel2,
    nu_e,          // muon kinematics only
    nu_e_truevar,  // muon kinematics only (using true variables)
    nu_e_2tracks,  // muon and proton kinematics
    nu_e_2tracks_pmomrange,    // muon and proton kinematics (using proton momentum by range)
    nu_e_2tracks_mumomrange,   // muon and proton kinematics (using muon momentum by range)
    nu_e_2tracks_truevar,   // muon and proton kinematics (using true variables)
    nu_e_momrange,      // muon kinematics only, using momentum by range of stopping muons
    nu_e_momrange_vertex,      // muon kinematics only, using momentum by range of stopping muons in vertex
    fin_e, 
    fin_mom, 
    fin_mass, 
    fin_costheta,  
    fin_e_pmomrange,   // (using proton momentum by range)
    fin_mom_pmomrange, 
    fin_mass_pmomrange, 
    fin_costheta_pmomrange, 
    fin_e_mumomrange,  // (using muon momentum by range)
    fin_mom_mumomrange, 
    fin_mass_mumomrange, 
    fin_costheta_mumomrange, 
    q2_rec, 
    q2_rec_momrange, 
    q2_true, 
    q2_truemc, 
    //------------------------------
    // Muon candidate
    //Sense
    selmu_sense, //Which end is inside FGD FV ?
    // momentum from range
    selmu_mom_range_oarecon, // momentum by range available from oaRecon (production 6),  no need to calculate with highlandRecPack
    selmu_mom_range,
    selmu_mom_range_vertex,     //when using TPC-FGD track to estimate start pos
    // true vars
    selmu_trueztheta,  // true (assuming the neutrino moves along z)
    selmu_truenutheta, // true (using the true neutrino direction)
    selp_truemom,               // true proton momentum
    selp_truepos,  // true proton start position
    selp_trueendpos,  // true proton end position
    selp_truedir,  // true proton direction
    selp_trueztheta,  // true angle between proton candidate and neutrino directions (assuming the neutrino moves along z)
    selp_truenutheta, // true angle between proton candidate and neutrino directions (using the true neutrino direction)
    // ----------------------------
    // Proton candidate
    // momentum
    selp_mom,      
    selp_amom, 
    // momentum from range
    selp_mom_range_oarecon, // momentum by range available from oaRecon (production 6),  no need to calculate with highlandRecPack
    selp_mom_range,
    selp_mom_range_vertex,  //when using TPC-FGD track to estimate start pos
    // angles
    selp_costheta, 
    selp_dir, 
    selp_theta,  // reconstructed angle between proton candidate and neutrino directions (assuming the neutrino moves along z)
    // positions
    selp_pos, 
    selp_endpos, 
    // PID
    selp_likep, 
    selp_likemip, 
    // TPC info
    selp_closest_tpc, 
    selp_detectors, 
    selp_ntpcs,
    selp_tpc_det,          
    selp_tpc_nhits,        
    selp_tpc_nnodes,       
    selp_tpc_charge,       
    selp_tpc_mom,          
    selp_tpc_emom,         
    selp_tpc_truemom,      
    selp_tpc_dedx_raw,     
    selp_tpc_dedx_expmu,   
    selp_tpc_dedx_exppi,   
    selp_tpc_dedx_expele,  
    selp_tpc_dedx_expp,    
    selp_tpc_pullmu, 
    selp_tpc_pullpi, 
    selp_tpc_pullele,
    selp_tpc_pullp, 
    selp_tpc_dedx,
    // FGD info
    selp_nfgds,
    selp_fgd_det,   
    selp_fgd_x,     
    selp_fgd_e,     
    selp_fgd_pullp,
    // vertex info
    selp_vertex_det,       
    selp_vertex_pos,      
    selp_vertex_truepos,
    selp_true_same,//same true vertex for selmu and selp
    // -----------------------
    // other candidates
    nalltpctracks,       
    ntpcnegQualityOutFV, 
    ntpcposQualityOutFV, 
    nbadquaFV,           
    nbadquaOutFV,        
    nallfgd1tracks,      
    nallfgd1conttracks,  
    nfgdContFV,          
    nfgdContOutFV,       
    nfgdothertracks,     
    ntrackertracks,  
    // generator level
    gen_p_esc,
    gen_p_pdg,
    
    
    //proton variables
    // split into primary and secondary for convenience
    trueprim_proton_truepos,
    trueprim_proton_truedir,
    trueprim_proton_truemom, 
    trueprim_proton_nprotons,  //counter
    
    truesec_proton_truepos,
    truesec_proton_truedir,
    truesec_proton_truemom, 
    truesec_proton_true_parentpdg,
    truesec_proton_nprotons, //counter
     
    
    //pion variables
    // split into primary and secondary for convenience
    trueprim_pi_truepos,
    trueprim_pi_truedir,
    trueprim_pi_truemom, 
    trueprim_pi_truepdg,
    trueprim_pi_npions, //counter
    
    truesec_pi_truepos,
    truesec_pi_truedir,
    truesec_pi_truemom, 
    truesec_pi_truepdg,
    truesec_pi_true_parentpdg,
    truesec_pi_npions, //counter
    
    //True variable
    true_ntracks,
    true_nprotons,   
    true_npions,
    true_nneutrons, 

    //2p2h variables
    selp_threemomx,
    selp_threemomy,
    selp_threemomz,

    selmu_infp_mom,
    selmu_infp_costheta,
    selmu_infp_threemomx,
    selmu_infp_threemomy,
    selmu_infp_threemomz,
     
    selmu_bin0,
    selmu_bin1,
    selmu_bin2,
    selmu_bin3,
    selmu_bin4,
    selmu_bin5,

    truep_truemom,
    truep_truecostheta,
    truep_truethreemom,

    truemu_infp_mom2,
    truemu_infp_costheta2,
    truemu_infp_mom,
    truemu_infp_costheta,
    truemu_infp_threemom,
    truemu_infp_threemom2,

    truemu_bin0,
    truemu_bin1,
    truemu_bin2,
    truemu_bin3,
    truemu_bin4,
    truemu_bin5,

    //Variables added by SDolan (02/09/15 ) for CC0Pi hadronic measurments start:

    selp_pdg, 
    selp_NDOF,
    selp_Chi2, 

    recDphiT,
    trueDphiT,
    recMrec,
    trueMrec,
    recDpT,
    trueDpT,
    recDalphaT,
    trueDalphaT,
    truePn, // new July 2018
    recPn, // new July 2018

    ntruetracks,
    ntruefstracks,
    ntrueprotons,
    ntruechargedpions,
    ntrueother,
    ntrueotherpdg,

    true_ntracksSD,
    true_nfstracksSD,
    true_nprotonsSD,
    true_nchargedpionsSD,
    true_notherSD,
    true_notherpdgSD,
    
    selmu_3x3_pathLength,
    selp_3x3_pathLength,
    selmu_3x3_truepathLength,
    selp_3x3_truepathLength,
    
    selmu_3x3_expVA,
    selp_3x3_expVA,
    selmu_3x3_trueexpVA,
    selp_3x3_trueexpVA,
    selmup_3x3_expVA,
    selmup_3x3_trueexpVA,
    // Categories for Pi0 ECal-veto candidate
    ecal_pi0_cand_energy, 
    ecal_pi0_cand_pos, 
    ecal_pi0_cand_most_upstream_layer_hit, 
    ecal_pi0_cand_pidmipem, 

    //End of variables added by SDolan for CC0Pi hadronic measurments

    // Some useful vairables for truth studies (new July 2019): 
    q0_true,
    q3_true,
    
    
   
    //categories color drawing 

    CCBwd, 
    fgdtargetCCZeroPi, 
    fgd2locationCCZeroPi, 
    
    enumStandardMicroTreesLast_numuCCZeroPiAnalysis
  };

  enum enumConf_numCCZeroPiAnalysis{
    nuparent_decaypos_syst = baseTrackerAnalysis::enumConfLast_baseTrackerAnalysis + 1,
    fgd_bwd_migration_syst, //  bwd syst
    si_neutron_syst,  // neutron SI
    enumConfLast_numCCZeroPiAnalysis
  };

protected: 
  
  /// Parameter to control whether to use closest in Z option for the layer
  Int_t GetSampleFgdLayer(bool closest = false);
  Int_t GetSampleFgd2LayerXsec(bool closest = false);
  
private:

  /// Flag to enable/disable momentum by range
  bool _prangeEnabled;
  bool _prangeVertexEnabled;
  bool _prangeMuon;
  bool _prangeProton;
  bool _fillGenInfo;
  bool _numuCCAddonToyVars;
  bool _addMECVars;
  
  bool _addPCandCateg;
  bool _addECalVetoCateg;
 
  SubDetId::SubDetEnum _fgdID;
  
  
  Int_t _whichAnalysis;
  
  
  std::set<int> init_pions() const{
    std::set<int> pdgs;
    pdgs.insert(111); //pi-zero
    pdgs.insert(211); //pi+
    pdgs.insert(-211); //pi-
    return pdgs;
  }
  
  std::set<int> _pion_pdgs;
  
  
  bool _addPionTrueVars;  
  bool _addProtonTrueVars; 
  bool _addTruthTreeCategories;

};

#endif
