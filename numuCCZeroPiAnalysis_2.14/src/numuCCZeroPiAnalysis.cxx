#include "numuCCZeroPiAnalysis.hxx"
#include "FiducialVolumeDefinition.hxx"
#include "Parameters.hxx"
#include "numuCCZeroPiSelection.hxx"
#include "CategoriesUtils.hxx"
#include "BasicUtils.hxx"
#include "numuCCZeroPiUtils.hxx"

#include "numuCCZeroPiCategoryUtils.hxx"
//#include "FlatTreeConverterGenInfo.hxx"

#include "NuParentDecayPosSystematics.hxx"
#include "FgdBwdMigrationWeightSystematicsCCZeroPi.hxx"

#include "SINeutronSystematics.hxx"

#include "SystIdHighland.hxx"
#include "baseToyMaker.hxx"

#include "TrackerAnalysisUtils.hxx"


//********************************************************************
numuCCZeroPiAnalysis::numuCCZeroPiAnalysis(AnalysisAlgorithm* ana) : baseTrackerAnalysis(ana) {
  //********************************************************************

  // Create a numuCCAnalysis passing this analysis to the constructor. In that way the same managers are used
  _numuCCAnalysis = new numuCCAnalysis(this);

  // Use the numuCCAnalysis (in practice that means that the same box and event will be used for the numuCCAnalysis as for this analysis)
  UseAnalysis(_numuCCAnalysis);

  // Get the version of highlandTools package (have to do it since versioning functionality (compilation time) is not available)
  std::string highlandToolsVersion = "v0r0p0";

  if (getenv("HIGHLANDTOOLSROOT"))
    highlandToolsVersion = anaUtils::GetSoftwareVersionFromPath((std::string)getenv("HIGHLANDTOOLSROOT"));

  // Have to add them manually for older versions 
  _addTruthTreeCategories = CheckBeforeVersion(highlandToolsVersion, "v1r0p0");  

}
//********************************************************************
bool numuCCZeroPiAnalysis::Initialize(){
  //********************************************************************

  // Initialize the baseTrackerAnalysis
  if(!baseTrackerAnalysis::Initialize()) return false;

  if (!_numuCCAnalysis->Initialize()) return false;

  // wether to fill generator level information
  _fillGenInfo        = (bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.FillGeneratorInfo");

  /*
   *   if (_fillGenInfo)
   * // Replace the converter with our custom version
   * input().ReplaceConverter("FlatTree", new FlatTreeConverterGenInfo());
   */


  _numuCCAddonToyVars = (bool)ND::params().GetParameterI("numuCCAnalysis.MicroTrees.AdditionalToyVars");

  // FGD1 or FGD2 analysis to run
  _whichAnalysis = ND::params().GetParameterI("numuCCZeroPiAnalysis.Analysis.Selection");

  if (_whichAnalysis == 1) _fgdID = SubDetId::kFGD1;
  if (_whichAnalysis == 2) _fgdID = SubDetId::kFGD2;
  if (_whichAnalysis >  2) _fgdID = SubDetId::kFGD;


  //whether to add and fill pion true variables
  _addPionTrueVars = (bool) ND::params().GetParameterI("numuCCZeroPiAnalysis.MicroTree.StoreTruePionKinematics"); // disabled by default

  //whether to add and fill proton true variables
  _addProtonTrueVars = (bool) ND::params().GetParameterI("numuCCZeroPiAnalysis.MicroTree.StoreTrueProtonKinematics"); // disabled by default


  _addMECVars = (bool) ND::params().GetParameterI("numuCCZeroPiAnalysis.MicroTree.StoreMECVariables"); // disabled by default

  // Minimum accum level to save event into the output tree
  SetMinAccumCutLevelToSave(ND::params().GetParameterI("numuCCZeroPiAnalysis.MinAccumLevelToSave"));

  /// Fill trees and process weight systematics only when any of the branches is succesful
  SetFillSuccessOnly((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.FillSuccessOnly"));

  // enable/disable range momentum (it's faster without range momentum),  disabled by default
  _prangeEnabled        =   (bool) ND::params().GetParameterI("numuCCZeroPiAnalysis.HighlandRecPack.ComputeRangeMomentum");
  _prangeVertexEnabled  =   (bool) ND::params().GetParameterD("numuCCZeroPiAnalysis.HighlandRecPack.ComputeRangeMomentumVertex");

  _prangeMuon     = (bool) ND::params().GetParameterI("numuCCZeroPiAnalysis.HighlandRecPack.ComputeRangeMomentum.Muon");
  _prangeProton   = (bool) ND::params().GetParameterD("numuCCZeroPiAnalysis.HighlandRecPack.ComputeRangeMomentum.Proton"); 

  _mom_range_box  = NULL;

  //fill pions pdgs
  _pion_pdgs = init_pions();

  // Add standard track categories for the proton candidate
  _addPCandCateg = (bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.AddCategories.ProtonCandidate");
 
  // Add standard categories for ECal Pi0 veto candidate
  _addECalVetoCateg = (bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.AddCategories.ECalPi0VetoCandidate");
 
  if (_addECalVetoCateg){
    anaUtils::AddStandardCategories("ecalveto"); 
  }
  
  if (_addPCandCateg){
    anaUtils::AddStandardCategories("PCan"); 
    anaUtils::AddStandardCategories("fgd2PCan");  
  }
  
  // Add categories specific for the analysis
  numu_cczeropi_categ_utils::AddCategories();
  // Add categories specific for the analysis
  numu_cczeropi_categ_utils::AddCategories("fgd2");

  return true;
}


//********************************************************************
void numuCCZeroPiAnalysis::DefineSelections(){
  //********************************************************************

  bool forceBreak = (bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.ForceBreak");

  if (_whichAnalysis == 1){
    sel().AddSelection("kTrackerNumuCCZeroPi", "inclusive numuCCZeroPi selection",  new numuCCZeroPiSelection(forceBreak, SubDetId::kFGD1));
  }
  else if (_whichAnalysis == 2){
    sel().AddSelection("kTrackerNumuCCZeroPiFGD2", "inclusive numuCCZeroPi FGD2 selection",  new numuCCZeroPiSelection(forceBreak, SubDetId::kFGD2));
  }
  else if (_whichAnalysis > 2){
    sel().AddSelection("kTrackerNumuCCZeroPi",     "inclusive numuCCZeroPi selection",      new numuCCZeroPiSelection(forceBreak, SubDetId::kFGD1));
    sel().AddSelection("kTrackerNumuCCZeroPiFGD2", "inclusive numuCCZeroPi FGD2 selection", new numuCCZeroPiSelection(forceBreak, SubDetId::kFGD2));
    _allowNonExclusiveSelections = true;
  }


}

//********************************************************************
void numuCCZeroPiAnalysis::DefineCorrections(){
  //********************************************************************

  // Same corrections as in numu CC (it will also create the _flux instance for numuCC) 
  _numuCCAnalysis->DefineCorrections();


}


//********************************************************************
void numuCCZeroPiAnalysis::DefineSystematics(){
  //********************************************************************

  // Same systematics as for numuCC
  _numuCCAnalysis->DefineSystematics();
  
  evar().AddEventVariation(SystIdHighland::kNuParentDecayPos, "NuParentDecayPos", new NuParentDecayPosSystematics());
  // FgdBwd systematic
  eweight().AddEventWeight(SystIdHighland::kFgdBwdMigration,  "FgdBwdMigration",  
      new FgdBwdMigrationWeightSystematicsCCZeroPi((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Syst.FgdBwdMigration.ApplyCorrelations")));
 
  eweight().AddEventWeight(SystIdHighland::kSINeutron,  "SINeutron", new SINeutronSystematics());
 
  
}

//********************************************************************
void numuCCZeroPiAnalysis::DefineConfigurations(){
  //********************************************************************

  _ntoys      = (Int_t)ND::params().GetParameterI("baseAnalysis.Systematics.NumberOfToys");
  _randomSeed = (Int_t)ND::params().GetParameterI("baseAnalysis.Systematics.RandomSeed");

  // Same configurations as for numuCC
  _numuCCAnalysis->DefineConfigurations();

  // if (_enableSingleVariationSystConf){
  if ((bool)ND::params().GetParameterI("baseAnalysis.Configurations.EnableSingleVariationSystConfigurations")){
    if ((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Syst.EnableNuParentDecayPos")){
      AddConfiguration(conf(), nuparent_decaypos_syst, _ntoys, _randomSeed, new baseToyMaker(_randomSeed));
      conf().EnableEventVariation(SystIdHighland::kNuParentDecayPos, nuparent_decaypos_syst);
    }
  }
  
  if ((bool)ND::params().GetParameterI("baseAnalysis.Configurations.EnableSingleWeightSystConfigurations")){
    if ((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Syst.EnableFgdBwdMigration")){
      AddConfiguration(conf(), fgd_bwd_migration_syst, _ntoys, _randomSeed, new baseToyMaker(_randomSeed));
      conf().EnableEventWeight(SystIdHighland::kFgdBwdMigration, fgd_bwd_migration_syst);
    }
  }
  
  
  if ((bool)ND::params().GetParameterI("baseAnalysis.Configurations.EnableSingleWeightSystConfigurations")){
    if ((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Syst.EnableSINeutron")){
      AddConfiguration(conf(), si_neutron_syst, _ntoys, _randomSeed, new baseToyMaker(_randomSeed));
      conf().EnableEventWeight(SystIdHighland::kSINeutron, si_neutron_syst);
    }
  }

  _enableAllSystConfig = (bool)ND::params().GetParameterI("baseAnalysis.Configurations.EnableAllSystematics");
  


  if (_enableAllSystConfig){ 
    
    if ((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Syst.EnableNuParentDecayPos")){
      conf().EnableEventVariation(SystIdHighland::kNuParentDecayPos, all_syst);
    }
    
    
    
    // Enable all Event Weights in the default and all_syst configurations
    for (std::vector<ConfigurationBase* >::iterator it= conf().GetConfigurations().begin();it!=conf().GetConfigurations().end();it++){
      Int_t index = (*it)->GetIndex();
      if (index != ConfigurationManager::default_conf && (index != all_syst || !_enableAllSystConfig)) continue;

    
      if ((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Syst.EnableFgdBwdMigration")){
        conf().EnableEventWeight(SystIdHighland::kFgdBwdMigration, index);
      }
    
      if ((bool)ND::params().GetParameterI("numuCCZeroPiAnalysis.Syst.EnableSINeutron")){
        conf().EnableEventWeight(SystIdHighland::kSINeutron, index);
      }

    }
  }

}

//********************************************************************
void numuCCZeroPiAnalysis::DefineMicroTrees(bool addBase){
  //********************************************************************

  // -------- Add variables to the analysis tree ----------------------

  // Variables from the numuCCAnalysis analysis (including the ones in baseAnalysis by default, otherwise addBase should be false
  if (addBase) _numuCCAnalysis->DefineMicroTrees(addBase);


  AddToyVarI(output(), sample_fgdlayer,           "");
  AddToyVarI(output(), sample_fgd2layer_xsec,     "");

  AddToyVarI(output(), sample_clst_fgdlayer,           "");
  AddToyVarI(output(), sample_clst_fgd2layer_xsec,     "");
  AddToyVarI(output(), flag_isFgdBwdMigrated,     "");
  
  // Z position of the reco vertex
  AddToyVarF(output(), selvtx_posZ,     "");
  
  
  // FGD2 position reco category
  AddToyVarI(output(), FGD2_reco_module,            "");

  // FGD2 GV position reco category
  AddToyVarI(output(), FGD2_GV_reco_module,         "");

  // FGD2 muon hit position reco category
  AddToyVarI(output(), FGD2_muon_hit_reco_module,   "");

  // FGD2 proton hit position reco category
  AddToyVarI(output(), FGD2_proton_hit_reco_module, "");
  
  // ECal Pi-0 veto candidate 
  AddVarF(output(),   ecal_pi0_cand_energy,                  "");
  AddVar4VF(output(), ecal_pi0_cand_pos,                     "");
  AddVarI(output(),   ecal_pi0_cand_most_upstream_layer_hit, "");
  AddVarF(output(),   ecal_pi0_cand_pidmipem,                "");


  // Position of the HM TPC track in FGD1 volume
  AddVar4VF(output(),HM_pos,"");

  AddVarF(output(), selmu_invpt,     "");
  AddVarF(output(), selmu_trueinvpt, "");
  AddVarI(output(), selmu_charge,    "selmu_charge");
  AddVarI(output(), selmu_truecharge,"selmu_truecharge");

  // Length of the muon candidate in branch 3
  AddVarF(output(),selmu_length,"");

  // Mom and costheta in the muon Bwd hypo
  AddVarI(output(), selmu_sense,          "muon candidate reconstructed end in FGD FV (1 start, -1 end) ");
  AddVarF(output(), selmu_Bwd_mom,          "muon candidate reconstructed alternate momentum (in the bwd muon hypothesis)");
  AddVarF(output(), selmu_Bwd_costheta,     "muon candidate alternate reconstructed cos(theta) at start (in the bwd muon hypothesis)");

  // Timing
  AddToyVarF(output(), selmu_FGD1_FGD2,       "muon candidate FGD1_FGD2 ToF");
  AddToyVarF(output(), selmu_P0D_FGD1,        "muon candidate P0D_FGD1 ToF");
  AddToyVarF(output(), selmu_ECal_FGD1,       "muon candidate ECal_FGD1 ToF");
  AddToyVarF(output(), selmu_ECal_FGD2,       "muon candidate ECal_FGD2 ToF");
  AddVarI(output(), selmu_Flag_FGD1_FGD2,     "muon candidate availability of FGD1_FGD2 ToF");
  AddVarI(output(), selmu_Flag_P0D_FGD1,      "muon candidate availability of P0D_FGD1 ToF");
  AddVarI(output(), selmu_Flag_ECal_FGD1,     "muon candidate availability of ECal_FGD1 ToF");
  AddVarI(output(), selmu_Flag_ECal_FGD2,     "muon candidate availability of ECal_FGD2 ToF");

  // ------- 2 Tracks specific variables ------------------

  // Michel electrons in FGD1 and FGD2
  AddVarI(output(),nmichel1,"nmichel1");
  AddVarI(output(),nmichel2,"nmichel2");

  // Reconstructed neutrino energy 
  AddToyVarF(output(),nu_e,"");          // muon kinematics only
  //  AddToyVarF(output(),nu_e_truevar,"");  // muon kinematics only (using true variables)
  AddToyVarF(output(),nu_e_2tracks,"");  // muon and proton kinematics
  //  AddToyVarF(output(),nu_e_2tracks_pmomrange, "");   // muon and proton kinematics (using proton momentum by range)
  AddToyVarF(output(),nu_e_2tracks_mumomrange, "");  // muon and proton kinematics (using muon momentum by range)
  //  AddToyVarF(output(),nu_e_2tracks_truevar, "");  // muon and proton kinematics (using true variables)
  AddVarF(output(),nu_e_momrange, "");     // muon kinematics only, using momentum by range of stopping muons
  AddVarF(output(),nu_e_momrange_vertex, "");     // muon kinematics only, using momentum by range of stopping muons in vertex
  // Final state variables
  /*
     AddToyVarF(output(),fin_e, "");
     AddToyVarF(output(),fin_mom, "");
     AddToyVarF(output(),fin_mass, "");
     AddToyVarF(output(),fin_costheta, ""); 
     AddToyVarF(output(),fin_e_pmomrange, "");  // (using proton momentum by range)
     AddToyVarF(output(),fin_mom_pmomrange, "");
     AddToyVarF(output(),fin_mass_pmomrange, "");
     AddToyVarF(output(),fin_costheta_pmomrange, "");
     AddToyVarF(output(),fin_e_mumomrange, ""); // (using muon momentum by range)
     AddToyVarF(output(),fin_mom_mumomrange, "");
     AddToyVarF(output(),fin_mass_mumomrange, "");
     AddToyVarF(output(),fin_costheta_mumomrange, "");
     */
  // Rec and true Q^2
  AddToyVarF(output(),q2_rec, "");
  AddVarF(output(),q2_rec_momrange, "");
  //  AddToyVarF(output(),q2_true, "");
  //  AddToyVarF(output(),q2_truemc, "");

  //--- momentum by range for muons -------
  AddToyVarF(output(),selmu_mom_range_oarecon,  "")

    if (_prangeEnabled && _prangeMuon)
      AddToyVarF(output(),selmu_mom_range,      "");

  if (_prangeVertexEnabled && _prangeMuon)
    AddToyVarF(output(),selmu_mom_range_vertex,   "");  //when using TPC-FGD track to estimate start pos

  //--- angle between muon candidate and neutrino directions -------
  AddVarF(output(),selmu_trueztheta, ""); // true (assuming the neutrino moves along z)
  AddVarF(output(),selmu_truenutheta,""); // true (using the true neutrino direction)

  //--- proton candidate truth variables -------
  AddVarF(output(),   selp_truemom,     "");    // true proton momentum
  AddVar4VF(output(), selp_truepos,     "");    // true proton start position
  AddVar4VF(output(), selp_trueendpos,  "");    // true proton end position
  AddVar3VF(output(), selp_truedir,     "");    // true proton direction
  AddVarF(output(),   selp_trueztheta,  "");    // true angle between proton candidate and neutrino directions (assuming the neutrino moves along z)
  AddVarF(output(),   selp_truenutheta, "");    // true angle between proton candidate and neutrino directions (using the true neutrino direction)
  AddVarI(output(),   selp_true_same,   "same true vertex as selmu");

  // --- HMP  basic vars --- 
  AddToyVarF(   output(), selHMP_mom,     ""   ); // HMP momentum
  AddToyVarVF(  output(), selHMP_pos,     "", 4); // HMP start position
  AddToyVarVF(  output(), selHMP_dir,     "", 3); // HMP direction

  AddVarF(    output(), selHMP_truemom,     "");    // HMP true momentum
  AddVar4VF(  output(), selHMP_truepos,     "");    // HMP true start position
  AddVar3VF(  output(), selHMP_truedir,     "");    // HMP true direction
  AddVarI(    output(), selHMP_truepdg,     "selHMP_truepdg");    // HMP true pdg



  // --- proton candidate recon variables -----
  AddToyVarF(output(),selp_mom,      "");
  AddToyVarF(output(),selp_amom,     "");

  AddToyVarF(output(),selp_mom_range_oarecon, "");

  if (_prangeEnabled && _prangeProton)
    AddToyVarF(output(),selp_mom_range,      "");

  if (_prangeVertexEnabled && _prangeProton)
    AddToyVarF(output(),selp_mom_range_vertex,   "");  //when using TPC-FGD track to estimate start pos


  AddVarF(output(), selp_costheta, "");
  AddVar3VF(output(),selp_dir, "");
  AddVarF(output(),selp_theta, ""); // reconstructed angle between proton candidate and neutrino directions (assuming the neutrino moves along z)
  AddVar4VF(output(),selp_pos, "");
  AddVar4VF(output(),selp_endpos, "");
  AddToyVarF(output(),selp_likep,""); 
  AddToyVarF(output(),selp_likemip,""); 
  AddVarI(output(),selp_closest_tpc, "selp_closest_tpc");
  AddVarI(output(),selp_detectors, "detectors contributing to proton candidate");

  // --- proton candidate info by tpc
  AddVarVI(output(),selp_tpc_det,          "",selp_ntpcs);
  AddVarVI(output(),selp_tpc_nhits,        "",selp_ntpcs);
  AddVarVI(output(),selp_tpc_nnodes,       "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_charge,       "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_mom,          "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_emom,         "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_truemom,      "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_dedx_raw,     "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_dedx_expmu,   "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_dedx_exppi,   "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_dedx_expele,  "",selp_ntpcs);
  AddVarVF(output(),selp_tpc_dedx_expp,    "",selp_ntpcs);
  /*
     AddToyVarVF(output(),selp_tpc_pullmu, "",NMAXTPCS);
     AddToyVarVF(output(),selp_tpc_pullpi, "",NMAXTPCS);
     AddToyVarVF(output(),selp_tpc_pullele,"",NMAXTPCS);
     AddToyVarVF(output(),selp_tpc_pullp,  "",NMAXTPCS);
     AddToyVarVF(output(),selp_tpc_dedx,   "",NMAXTPCS);
     */
  // --- proton candidate info by FGD
  AddVarVI(output(),selp_fgd_det,          "",selp_nfgds);
  AddVarVF(output(),selp_fgd_x,            "",selp_nfgds);
  AddVarVF(output(),selp_fgd_e,            "",selp_nfgds);
  
  AddToyVarVF(output(),selp_fgd_pullp, "", NMAXFGDS);

  // --- Vertex info
  AddVarF(output(),selp_vertex_det,       "");
  AddVar4VF(output(),selp_vertex_pos,      "");
  AddVar4VF(output(),selp_vertex_truepos,  "");

  //--- tracks counters ----
  AddVarI(output(),nalltpctracks,       "nalltpctracks");
  AddVarI(output(),ntpcnegQualityOutFV, "ntpcnegQualityOutFV");
  AddVarI(output(),ntpcposQualityOutFV, "ntpcposQualityOutFV");
  AddVarI(output(),nbadquaFV,           "nbadquaFV");
  AddVarI(output(),nbadquaOutFV,        "nbadquaOutFV");

  AddVarI(output(),nallfgd1tracks,      "nallfgd1tracks");
  AddVarI(output(),nallfgd1conttracks,  "nallfgd1conttracks");

  AddVarI(output(),nfgdContFV,          "nfgdContFV");
  AddVarI(output(),nfgdContOutFV,       "nfgdContOutFV");

  AddVarI(output(),nfgdothertracks,     "nfgdothertracks");
  AddVarI(output(),ntrackertracks,      "ntrackertracks");

  /*
     if(_fillGenInfo){
  // --- generator info ----
  AddVarI(output(),gen_p_esc, "Did the primary proton escape from the nucleus ?");
  AddVarI(output(),gen_p_pdg, "PDG code of the primary proton");
  }
  */


  AddVarI(output(),selp_pdg,"selp_pdg");

  //New vars for truth studies July 2019
  AddVarF(  output(), q0_true,      "q0_true");
  AddVarF(  output(), q3_true,      "q3_true");


  if(_addMECVars){


    AddToyVarF(output(),selp_threemomx,"");
    AddToyVarF(output(),selp_threemomy,"");
    AddToyVarF(output(),selp_threemomz,"");

    AddToyVarF(output(), selmu_infp_mom, "inferred proton momentum from selected muon kinematics"); 
    AddToyVarF(output(), selmu_infp_costheta, "inferred proton costheta from selected muon kinematics"); 
    AddToyVarF(output(), selmu_infp_threemomx, "inferred proton three momentum from selected muon kinematics"); 
    AddToyVarF(output(), selmu_infp_threemomy, "inferred proton three momentum from selected muon kinematics"); 
    AddToyVarF(output(), selmu_infp_threemomz, "inferred proton three momentum from selected muon kinematics"); 
    AddToyVarI(output(), selmu_bin0,"");
    AddToyVarI(output(), selmu_bin1,"");
    AddToyVarI(output(), selmu_bin2,"");
    AddToyVarI(output(), selmu_bin3,"");
    AddToyVarI(output(), selmu_bin4,"");
    AddToyVarI(output(), selmu_bin5,"");

    AddVarF(output(), truep_truemom, "true proton, true momentum of the vertex"); 
    AddVarF(output(), truep_truecostheta, "true proton, true momentum of the vertex"); 
    AddVar3VF(output(), truep_truethreemom, "true proton, true momentum of the vertex"); 

    AddVarF(output(), truemu_infp_mom, "inferred proton momentum from true muon kinematics"); 
    AddVarF(output(), truemu_infp_costheta, "inferred proton costheta from true muon kinematics"); 
    AddVar3VF(output(), truemu_infp_threemom, "inferred proton three momentum from true muon kinematics"); 

    AddVarI(output(), truemu_bin0,"truemu_bin0");
    AddVarI(output(), truemu_bin1,"truemu_bin1");
    AddVarI(output(), truemu_bin2,"truemu_bin2");
    AddVarI(output(), truemu_bin3,"truemu_bin3");
    AddVarI(output(), truemu_bin4,"truemu_bin4");
    AddVarI(output(), truemu_bin5,"truemu_bin5");

    AddVarI(  output(), true_npions,      "true_npions");
    AddVarI(  output(), true_nprotons,    "true_nprotons");
    AddVarI(  output(), true_nneutrons,   "true_nneutrons");
    
    //Variables added by SDolan (02/09/15 ) for CC0Pi hadronic measurments start:

    //--- Stephen's New Varibales for Trasverse calcs ---
    AddToyVarI(output(),selp_NDOF,      "");
    AddToyVarF(output(),selp_Chi2,      "");

    //MEC analysis specific variables:
    AddToyVarF(output(),recDphiT,"");//      "reconstructed delta_phi_T");
    AddToyVarF(output(),trueDphiT,"");//      "true delta_phi_T");
    AddToyVarF(output(),recMrec,"");//      "reconstructed recon target mass under CCQE hyp");
    AddToyVarF(output(),trueMrec,"");//      "true recon target mass under CCQE hyp");
    AddToyVarF(output(),recDalphaT,"");//      "reconstructed delta_alpha_T");
    AddToyVarF(output(),trueDalphaT,"");//      "true delta_alpha_T");
    AddToyVarF(output(),recDpT,"");//      "reconstructed delta_p_T");
    AddToyVarF(output(),trueDpT,"");//      "true delta_p_T");
    AddToyVarD(output(),recPn,"");//      "reconstructed p_n"); // New July 2019, details in Phys. Rev. C 95, 065501
    AddToyVarD(output(),truePn,"");//      "true p_n");

    //Path length + VA Variables:

    AddToyVarF(output(),selmu_3x3_pathLength,"");
    AddToyVarF(output(),selp_3x3_pathLength,"");
    AddToyVarF(output(),selmu_3x3_truepathLength,"");
    AddToyVarF(output(),selp_3x3_truepathLength,"");

    AddToyVarF(output(),selmu_3x3_expVA,"");
    AddToyVarF(output(),selp_3x3_expVA,"");
    AddToyVarF(output(),selmu_3x3_trueexpVA,"");
    AddToyVarF(output(),selp_3x3_trueexpVA,"");
    AddToyVarF(output(),selmup_3x3_expVA,"");
    AddToyVarF(output(),selmup_3x3_trueexpVA,"");


    //True Vertex variables - added by Stephen 20/07/15

    AddVarI(output(), ntruetracks, "ntruetracks");
    AddVarI(output(), ntruefstracks, "ntruefstracks");
    AddVarI(output(), ntrueprotons, "ntrueprotons");
    AddVarI(output(), ntruechargedpions, "ntruechargedpions");
    AddVarI(output(), ntrueother, "ntrueother");
    AddVarI(output(), ntrueotherpdg, "ntrueotherpdg");

    //End of variables added by SDolan for CC0Pi hadronic measurments

  }

}

//********************************************************************
void numuCCZeroPiAnalysis::DefineTruthTree(){
  //********************************************************************

  // Variables from baseAnalysis (run, event, ...)
  _numuCCAnalysis->DefineTruthTree();

  // --- true pion truth variables -------
  if (_addPionTrueVars){
    // ----- Primary -----
    AddVarMF(output(),  trueprim_pi_truepos,          "true primary pion true position",      trueprim_pi_npions, -30, 4); 
    AddVarMF(output(),  trueprim_pi_truedir,          "true primary pion true direction",     trueprim_pi_npions, -30, 3);
    AddVarVF(output(),  trueprim_pi_truemom,          "true primary pion true momentum",      trueprim_pi_npions);
    AddVarVI(output(),  trueprim_pi_truepdg,          "true primary pion true PDG",           trueprim_pi_npions);

    // ----- Secondary -----
    AddVarMF(output(),  truesec_pi_truepos,           "true secondary pion true position",    truesec_pi_npions,  -30, 4); 
    AddVarMF(output(),  truesec_pi_truedir,           "true secondary pion true direction",   truesec_pi_npions,  -30, 3);
    AddVarVF(output(),  truesec_pi_truemom,           "true secondary pion true momentum",    truesec_pi_npions);
    AddVarVI(output(),  truesec_pi_truepdg,           "true secondary pion true PDG",         truesec_pi_npions);
    AddVarVI(output(),  truesec_pi_true_parentpdg,    "true secondary pion true parent PDG",  truesec_pi_npions);
  }

  if (_addProtonTrueVars){
    // ----- Primary -----
    AddVarMF(output(),  trueprim_proton_truepos,          "true primary proton true position",      trueprim_proton_nprotons, -30, 4); 
    AddVarMF(output(),  trueprim_proton_truedir,          "true primary proton true direction",     trueprim_proton_nprotons, -30, 3);
    AddVarVF(output(),  trueprim_proton_truemom,          "true primary proton true momentum",      trueprim_proton_nprotons);

    // ----- Secondary -----
    AddVarMF(output(),  truesec_proton_truepos,           "true secondary proton true position",    truesec_proton_nprotons,  -30, 4); 
    AddVarMF(output(),  truesec_proton_truedir,           "true secondary proton true direction",   truesec_proton_nprotons,  -30, 3);
    AddVarVF(output(),  truesec_proton_truemom,           "true secondary proton true momentum",    truesec_proton_nprotons);
    AddVarVI(output(),  truesec_proton_true_parentpdg,    "true secondary proton true parent PDG",  truesec_proton_nprotons);
  }



  //--- muon variables -------

  //--- vtx variables  -------
  AddVarI(  output(), true_ntracks,       "true_ntracks");
  AddVarI(  output(), true_nprotons,      "true_nprotons");
  AddVarI(  output(), true_npions,        "true_npions");
  AddVarI(  output(), true_nneutrons,     "true_nneutrons");
  


  AddVarF(  output(), q0_true,      "q0_true");
  AddVarF(  output(), q3_true,        "q3_true");


  if(_addMECVars){

    AddVarF(output(), truep_truemom, "true proton, true momentum of the vertex"); 
    AddVarF(output(), truep_truecostheta, "true proton, true momentum of the vertex"); 
    AddVar3VF(output(), truep_truethreemom, "true proton, true momentum of the vertex"); 

    AddVarF(output(), truemu_infp_mom, "inferred proton momentum from true muon kinematics"); 
    AddVarF(output(), truemu_infp_costheta, "inferred proton costheta from true muon kinematics"); 
    AddVar3VF(output(), truemu_infp_threemom, "inferred proton three momentum from true muon kinematics"); 

    AddVarI(output(), truemu_bin0," truemu_bin0");
    AddVarI(output(), truemu_bin1," truemu_bin1");
    AddVarI(output(), truemu_bin2," truemu_bin2");
    AddVarI(output(), truemu_bin3," truemu_bin3");
    AddVarI(output(), truemu_bin4," truemu_bin4");
    AddVarI(output(), truemu_bin5," truemu_bin5");

    //--- vtx variables - added by Stephen ---
    //--- Renamed to avoid redefinition with Jiae's vars

    AddVarI(  output(), true_ntracksSD, "true_ntracks");
    AddVarI(  output(), true_nfstracksSD, "true_ntracks");
    AddVarI(  output(), true_nprotonsSD, "true_nprotons");
    AddVarI(  output(), true_nchargedpionsSD, "true_nchargedpions");
    AddVarI(  output(), true_notherSD, "true_nother");
    AddVarI(  output(), true_notherpdgSD, "true_notherpdg");

    //--- Transverse+M_rec variables - added by Stephen ---   

    AddVarF(output(), trueMrec, "True Reconstructed Target Mass");
    AddVarF(output(), trueDphiT, "True delta phi T");
    AddVarF(output(), trueDpT, "True delta p T");
    AddVarF(output(), trueDalphaT, "True delta alpha T");
    AddVarD(output(), truePn, "True pn"); // new July 19, see Phys. Rev. C 95, 065501



  }


  //--- categories -------
  if (!_addTruthTreeCategories)
    return;
  //categories for color drawing
  AddVarI(output(), CCBwd,                    "CCBwd"); //this filled only for default tree so far
  //AddVarI(output(), fgdtargetCCZeroPi,        "fgd target cc0pi");
  //AddVarI(output(), fgd2locationCCZeroPi,     "fgd2 location cc0pi");
  

}

//********************************************************************
void numuCCZeroPiAnalysis::InitializeConfiguration(){
  //********************************************************************

  // Delete the box and create a new one
  if (_mom_range_box) delete _mom_range_box;
  _mom_range_box = new MomRangeBox(); 


}

//********************************************************************
void numuCCZeroPiAnalysis::FillMicroTrees(bool addBase){
  //********************************************************************

  // Fill variables from numuCCAnalysis
  if (addBase) _numuCCAnalysis->FillMicroTrees(addBase);

  FillHMP_TrueInfo();


  //Events info
  //output().FillVar( ntrackertracks , (Int_t)(numu_cczeropi_box().TrackerTracks.size())); 

  FillMuonCandidateInfo();

  FillProtonCandidateInfo();
  
  FillECalVetoInfo();

  if(_addMECVars)
    FillMECInfo();

  /*
   *   if(_fillGenInfo)
   *   FillGeneratorInfo();
   */

}

//********************************************************************
void numuCCZeroPiAnalysis::FillToyVarsInMicroTrees(bool addBase){
  //********************************************************************
  if (addBase) _numuCCAnalysis->FillToyVarsInMicroTrees(addBase);
 
  // Fill samples
  output().FillToyVar(sample_fgdlayer,       GetSampleFgdLayer());
  output().FillToyVar(sample_fgd2layer_xsec, GetSampleFgd2LayerXsec());
 
  output().FillToyVar(sample_clst_fgdlayer,       GetSampleFgdLayer(true));
  output().FillToyVar(sample_clst_fgd2layer_xsec, GetSampleFgd2LayerXsec(true)); 
  
  if (numu_cczeropi_box().Vertex){
    output().FillToyVar(flag_isFgdBwdMigrated, anaUtils::IsFgdBwdMigrated(*numu_cczeropi_box().Vertex, SubDetId::kFGD)); 
  }
  
  // Fill here Variables specific for the numuCCZeroPi analysis

  FillHMP_ToyVars();

  if (numu_cczeropi_box().Vertex){
    int module = anaUtils::GetFgdModuleType(GetEvent().EventInfo.GetIsMC(), numu_cczeropi_box().Vertex->Position, SubDetId::kFGD2);
    output().FillToyVar(FGD2_reco_module, module);
    
    
    output().FillToyVar(selvtx_posZ, numu_cczeropi_box().Vertex->Position[2]);
    
  }

  bool found_gv = false;

  // Module from GV
  if (numu_cczeropi_box().MuonCandidate && 
      numu_cczeropi_box().ProtonCandidate){

    // Get the global vertex
    AnaTrackB* tracks_tmp[2];
    tracks_tmp[0] = numu_cczeropi_box().MuonCandidate;
    tracks_tmp[1] = numu_cczeropi_box().ProtonCandidate;
    AnaVertexB* vertex_tmp = anaUtils::GetGlobalVertex(GetEvent(), tracks_tmp, 2); 
    if (vertex_tmp){
      output().FillToyVar(FGD2_GV_reco_module,
          anaUtils::GetFgdModuleType(GetEvent().EventInfo.GetIsMC(), vertex_tmp->Position, SubDetId::kFGD2));
      found_gv = true;
    }
  }

  // If the GV was not found (most probably only one candidate track is present) then use the one from the box
  if (!found_gv && numu_cczeropi_box().Vertex){
    output().FillToyVar(FGD2_GV_reco_module, 
        anaUtils::GetFgdModuleType(GetEvent().EventInfo.GetIsMC(), numu_cczeropi_box().Vertex->Position, SubDetId::kFGD2));
  }

  // Module from muon hit
  if (numu_cczeropi_box().MuonCandidate && 
      numu_cczeropi_box().Vertex){

    // Get the hit Z pos
    double z_tmp;

    AnaTrack* track_tmp = static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate);

    if (numu_cczeropi_utils::GetClosestHitPosInZ(track_tmp, 
          numu_cczeropi_box().Vertex->Position, 
          z_tmp)){

      Float_t pos_tmp[3];

      pos_tmp[0] = numu_cczeropi_box().Vertex->Position[0];
      pos_tmp[1] = numu_cczeropi_box().Vertex->Position[1];

      pos_tmp[2] = z_tmp;
      output().FillToyVar(FGD2_muon_hit_reco_module,
          anaUtils::GetFgdModuleType(GetEvent().EventInfo.GetIsMC(), pos_tmp, SubDetId::kFGD2));
    }
  }

  // Module from proton hit
  if (numu_cczeropi_box().ProtonCandidate && 
      numu_cczeropi_box().Vertex){

    // Get the hit Z pos
    double z_tmp;

    AnaTrack* track_tmp = static_cast<AnaTrack*>(numu_cczeropi_box().ProtonCandidate);

    if (numu_cczeropi_utils::GetClosestHitPosInZ(track_tmp, 
          numu_cczeropi_box().Vertex->Position, 
          z_tmp)){

      Float_t pos_tmp[3];

      pos_tmp[0] = numu_cczeropi_box().Vertex->Position[0];
      pos_tmp[1] = numu_cczeropi_box().Vertex->Position[1];

      pos_tmp[2] = z_tmp;
      output().FillToyVar(FGD2_proton_hit_reco_module,
          anaUtils::GetFgdModuleType(GetEvent().EventInfo.GetIsMC(), pos_tmp, SubDetId::kFGD2));
    }
  }





  // variables specific for this analysis
  if (numu_cczeropi_box().MuonCandidate){

    AnaTrack* MuonCandidate = static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate);

    //Timing
    output().FillToyVar(selmu_FGD1_FGD2,  MuonCandidate->ToF.FGD1_FGD2);
    output().FillToyVar(selmu_P0D_FGD1,   MuonCandidate->ToF.P0D_FGD1);
    output().FillToyVar(selmu_ECal_FGD1,  MuonCandidate->ToF.ECal_FGD1);
    output().FillToyVar(selmu_ECal_FGD2,  MuonCandidate->ToF.ECal_FGD2); 


    if (!anaUtils::TrackUsesDet(*(numu_cczeropi_box().MuonCandidate), SubDetId::kTPC)){
      output().FillToyVar(numuCCAnalysis::selmu_costheta,   (Float_t)(numu_cczeropi_box().MuonCandidate->DirectionStart[2]));       
    }

    // **** Momentum from range ***** 
    // momentum from range from oaRecon (production 6)
    output().FillToyVar(selmu_mom_range_oarecon, MuonCandidate->RangeMomentumMuon);   


    if(_prangeEnabled){
      if (!anaUtils::TrackUsesDet(*MuonCandidate, SubDetId::kTPC)){ 
        //this is independent of the presence of proton candidate
        Float_t pr = momrange_box().muon_momrange;   
        // Momentum by range
        output().FillToyVar(selmu_mom_range, pr); 


        if(numu_cczeropi_box().ProtonCandidate){
          if (anaUtils::TrackUsesDet(*(numu_cczeropi_box().ProtonCandidate), SubDetId::kTPC)){ //isnt true in case 4

            // Final state variables
            TVector3 mumom = pr * anaUtils::ArrayToTVector3(MuonCandidate->DirectionStart);
            TVector3 pmom  = numu_cczeropi_box().ProtonCandidate->Momentum  * anaUtils::ArrayToTVector3(numu_cczeropi_box().ProtonCandidate->DirectionStart);
            output().FillToyVar(nu_e_2tracks_mumomrange, numu_cczeropi_utils::GetRecNuEnergyTwoTracks(mumom, pmom, false));
            // Final state variables
            /*
             *             output().FillToyVar(fin_e_mumomrange, numu_cczeropi_utils::ComputeFinalStateEnergy(mumom, pmom));
             *             output().FillToyVar(fin_mom_mumomrange, (Float_t)(numu_cczeropi_utils::ComputeFinalStateMom(mumom, pmom).Mag()));
             *             output().FillToyVar(fin_mass_mumomrange, (Float_t)(sqrt(numu_cczeropi_utils::ComputeFinalStateMassSquared(mumom, pmom))));
             */
            //  output().FillToyVar(fin_costheta_mumomrange, sqrt(numu_cczeropi_utils::ComputeFinalStateCosTheta(mumom, pmom, false)));
          }

        }
      }
    }

    if(_prangeVertexEnabled){
      if (!anaUtils::TrackUsesDet(*MuonCandidate, SubDetId::kTPC)){ 
        if(numu_cczeropi_box().ProtonCandidate){
          if (anaUtils::TrackUsesDet(*(numu_cczeropi_box().ProtonCandidate), SubDetId::kTPC)){ //isnt true in case 4

            Float_t prv = momrange_box().muon_momrange_vertex;   
            output().FillToyVar(selmu_mom_range_vertex, prv); 
          }
        }
      }
    }

    if (_numuCCAddonToyVars){
      // Info in all FGDs 
      for (Int_t subdet = 0; subdet<2; subdet++) {
        if (!SubDetId::GetDetectorUsed(MuonCandidate->Detector, static_cast<SubDetId::SubDetEnum >(subdet))) continue;
        AnaFGDParticle* FGDSegment = static_cast<AnaFGDParticle*>(anaUtils::GetSegmentInDet(*MuonCandidate, static_cast<SubDetId::SubDetEnum >(subdet)));
        if (!FGDSegment) continue;
        output().FillToyVectorVar(numuCCAnalysis::selmu_fgd_pullmu, FGDSegment->Pullmu, subdet);
      }
    }

    // Reconstructed neutrino energy using only muon kinematics    
    output().FillToyVar(nu_e, numu_cczeropi_utils::GetRecNuEnergy(*(numu_cczeropi_box().MuonCandidate),numu_cczeropi_box().MuonCandidate->Momentum));
    //FillToyVar("nu_e", numu_cczeropi_utils::GetRecNuEnergy(numu_cczeropi_box().MuonCandidate->Momentum, numu_cczeropi_box().MuonCandidate->DirectionStart));

    // Reconstructed Q2
    output().FillToyVar(q2_rec, numu_cczeropi_utils::GetRecQ2(*(numu_cczeropi_box().MuonCandidate),numu_cczeropi_box().MuonCandidate->Momentum));

    /*
     *     if (numu_cczeropi_box().Vertex){
     *     if(numu_cczeropi_box().MuonCandidate->GetTrueParticle() && numu_cczeropi_box().Vertex->TrueVertex) {
     *  // True Q2
     *  output().FillToyVar(q2_true, numu_cczeropi_utils::GetTrueQ2(*(numu_cczeropi_box().MuonCandidate), numu_cczeropi_box().Vertex->TrueVertex->NuEnergy));
     *  output().FillToyVar(q2_truemc, static_cast<AnaTrueVertex*>(numu_cczeropi_box().Vertex->TrueVertex)->Q2);
     *  // Reconstructed neutrino energy using only muon kinematics (using true quantities)
     *  output().FillToyVar(nu_e_truevar, numu_cczeropi_utils::GetRecNuEnergy(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Momentum, anaUtils::ArrayToTVector3(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction),true));	
     }
     }
     */
  }

  if (numu_cczeropi_box().ProtonCandidate) {

    AnaTrack* ProtonCandidate = static_cast<AnaTrack*>(numu_cczeropi_box().ProtonCandidate);

    if (numu_cczeropi_box().MuonCandidate){
      //FillToyVar(nu_e_2tracks, numu_cczeropi_utils::GetRecNuEnergyTwoTracks(*(numu_cczeropi_box().MuonCandidate), *(ProtonCandidate)));
      TVector3 mumom = numu_cczeropi_box().MuonCandidate->Momentum   * anaUtils::ArrayToTVector3(numu_cczeropi_box().MuonCandidate->DirectionStart);
      TVector3 pmom  = ProtonCandidate->MomentumProton * anaUtils::ArrayToTVector3(ProtonCandidate->DirectionStart);
      output().FillToyVar(nu_e_2tracks, numu_cczeropi_utils::GetRecNuEnergyTwoTracks(mumom, pmom, false));

      // Final state variables
      /*
       *       output().FillToyVar(fin_e,        numu_cczeropi_utils::ComputeFinalStateEnergy(mumom, pmom));
       *       output().FillToyVar(fin_mom,      (Float_t)numu_cczeropi_utils::ComputeFinalStateMom(mumom, pmom).Mag());
       *       output().FillToyVar(fin_mass,     (Float_t)sqrt(numu_cczeropi_utils::ComputeFinalStateMassSquared(mumom, pmom)));
       */
      //    output().FillToyVar(fin_costheta, sqrt(numu_cczeropi_utils::ComputeFinalStateCosTheta(mumom, pmom, false)));

      /*
       *       if (ProtonCandidate->GetTrueParticle() && numu_cczeropi_box().MuonCandidate->GetTrueParticle()) {
       *       if (numu_cczeropi_box().Vertex && numu_cczeropi_box().Vertex->TrueVertex) {
       *       TVector3 mumom_true = numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Momentum * anaUtils::ArrayToTVector3(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction);
       *       TVector3 pmom_true = ProtonCandidate->GetTrueParticle()->Momentum      * anaUtils::ArrayToTVector3(ProtonCandidate->GetTrueParticle()->Direction);
       *    // Reconstructed neutrino energy using both muon and proton kinematics    
       *    output().FillToyVar(nu_e_2tracks_truevar, numu_cczeropi_utils::GetRecNuEnergyTwoTracks(mumom_true, pmom_true, true));
       }
       }
       */
    }

    //basic kinematic vars
    output().FillToyVar(selp_mom,  ProtonCandidate->Momentum);    
    output().FillToyVar(selp_amom, ProtonCandidate->MomentumProton);

    // PID likelihoods
    output().FillToyVar(selp_likep,  (Float_t)anaUtils::GetPIDLikelihood(    *(ProtonCandidate),2)); 
    output().FillToyVar(selp_likemip,(Float_t)anaUtils::GetPIDLikelihoodMIP( *(ProtonCandidate))); 

    //if no TPC is present then calculate final state variables dependent on prange
    // Reconstructed neutrino energy using both muon and proton kinematics

    // ***** Momentum from range ***** 
    // momentum from range from oaRecon (production 6)
    output().FillToyVar(selp_mom_range_oarecon, ProtonCandidate->RangeMomentumProton);   

    if(_prangeEnabled){
      if (!anaUtils::TrackUsesDet(*ProtonCandidate, SubDetId::kTPC)){ 
        //this is independent of the presence of muon candidate
        Float_t pr = momrange_box().proton_momrange;   
        output().FillToyVar(selp_mom_range, pr);

        /*        
         *                if(numu_cczeropi_box().MuonCandidate){
         *                if (anaUtils::TrackUsesDet(*(numu_cczeropi_box().MuonCandidate), SubDetId::kTPC)){ //isnt true in case 4
         * 
         *      // Final state variables
         *      TVector3 mumom = numu_cczeropi_box().MuonCandidate->Momentum * anaUtils::ArrayToTVector3(numu_cczeropi_box().MuonCandidate->DirectionStart);
         *      TVector3 pmom  = pr * anaUtils::ArrayToTVector3(ProtonCandidate->DirectionStart);
         *      output().FillToyVar(nu_e_2tracks_pmomrange, numu_cczeropi_utils::GetRecNuEnergyTwoTracks(mumom, pmom, false));
         *      // Final state variables
         * 
         *      output().FillToyVar(fin_e_pmomrange, numu_cczeropi_utils::ComputeFinalStateEnergy(mumom, pmom));
         *      output().FillToyVar(fin_mom_pmomrange, (Float_t)(numu_cczeropi_utils::ComputeFinalStateMom(mumom, pmom).Mag()));
         *      output().FillToyVar(fin_mass_pmomrange, (Float_t)(sqrt(numu_cczeropi_utils::ComputeFinalStateMassSquared(mumom, pmom))));
         *      // output().FillToyVar(fin_costheta_pmomrange, sqrt(numu_cczeropi_utils::ComputeFinalStateCosTheta(mumom, pmom, false)));
         * 
         }

         }
         */
      }
    }

    if(_prangeVertexEnabled){
      if (!anaUtils::TrackUsesDet(*ProtonCandidate, SubDetId::kTPC)){ 
        if(numu_cczeropi_box().MuonCandidate){
          if (anaUtils::TrackUsesDet(*(numu_cczeropi_box().MuonCandidate), SubDetId::kTPC)){ //isnt true in case 4

            Float_t prv = momrange_box().proton_momrange_vertex;   
            output().FillToyVar(selp_mom_range_vertex, prv); 
          }
        }
      }
    }

    /*
     *  // Info in all TPCs 
     *  for (Int_t subdet = 0; subdet<3; subdet++) {
     *  if (!SubDetId::GetDetectorUsed(ProtonCandidate->Detector, static_cast<SubDetId::SubDetEnum >(subdet+2))) continue;
     *  AnaTPCParticle* TPCSegment = static_cast<AnaTPCParticle*>(anaUtils::GetSegmentInDet(*ProtonCandidate, static_cast<SubDetId::SubDetEnum >(subdet+2)));
     *  if (!TPCSegment) continue;
     * 
     *  output().FillToyVectorVar(selp_tpc_dedx,   TPCSegment->dEdxMeas, subdet);
     *  output().FillToyVectorVar(selp_tpc_pullmu, TPCSegment->Pullmu,   subdet);
     *  output().FillToyVectorVar(selp_tpc_pullpi, TPCSegment->Pullpi,   subdet);
     *  output().FillToyVectorVar(selp_tpc_pullele,TPCSegment->Pullele,  subdet);
     *  output().FillToyVectorVar(selp_tpc_pullp,  TPCSegment->Pullp,    subdet);    
     }
    */

    // Info in all FGDs - fgd pulls 
    for (Int_t subdet = 0; subdet < 2; subdet++) {
      if (!SubDetId::GetDetectorUsed(ProtonCandidate->Detector, static_cast<SubDetId::SubDetEnum >(subdet))) continue;
      AnaFGDParticle* FGDSegment = static_cast<AnaFGDParticle*>(anaUtils::GetSegmentInDet(*ProtonCandidate, static_cast<SubDetId::SubDetEnum >(subdet)));
      if (!FGDSegment) continue;
      output().FillToyVectorVar(selp_fgd_pullp, FGDSegment->Pullp, subdet);
    }
  }

  if(_addMECVars)
    FillMECToyVarsInMicroTrees();


}

//********************************************************************
void numuCCZeroPiAnalysis::FillMECToyVarsInMicroTrees(){
  //********************************************************************

  if (!numu_cczeropi_box().MuonCandidate) return;
  if (!numu_cczeropi_box().ProtonCandidate) return;

  AnaTrack* MuonCandidate = static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate);

  output().FillToyVar(selmu_infp_mom, numu_cczeropi_utils::InferProtonMomentum(MuonCandidate->Momentum,  numu_cczeropi_utils::GetRecNuEnergy(*(numu_cczeropi_box().MuonCandidate),numu_cczeropi_box().MuonCandidate->Momentum)));
  output().FillToyVar(selmu_infp_costheta, numu_cczeropi_utils::InferProtonAngle(MuonCandidate->Momentum,  numu_cczeropi_utils::GetRecNuEnergy(*(numu_cczeropi_box().MuonCandidate),numu_cczeropi_box().MuonCandidate->Momentum)));
  output().FillToyVar(selmu_infp_threemomx, -(MuonCandidate->Momentum * MuonCandidate->DirectionStart[0])); 
  output().FillToyVar(selmu_infp_threemomy, -(MuonCandidate->Momentum * MuonCandidate->DirectionStart[1])); 
  output().FillToyVar(selmu_infp_threemomz, -(MuonCandidate->Momentum * MuonCandidate->DirectionStart[2]) +  numu_cczeropi_utils::GetRecNuEnergy(*(numu_cczeropi_box().MuonCandidate),numu_cczeropi_box().MuonCandidate->Momentum) ); 


  Float_t mu_mom =   numu_cczeropi_box().MuonCandidate->Momentum;
  Float_t mu_costheta =  numu_cczeropi_box().MuonCandidate->DirectionStart[2];
  Float_t mu_angle_degree = acos(mu_costheta)*180/3.14;

  bool temp_selmu_bin0 = mu_mom < 375 && mu_angle_degree < 60;
  bool temp_selmu_bin1 = mu_mom < 375 && mu_angle_degree > 60;
  bool temp_selmu_bin2 = mu_mom > 375 && mu_mom < 700 && mu_angle_degree < 30;
  bool temp_selmu_bin3 = mu_mom > 375 && mu_mom < 700 && mu_angle_degree > 30;
  bool temp_selmu_bin4 = mu_mom > 700 && mu_mom < 2000;
  bool temp_selmu_bin5 = mu_mom > 2000;

  output().FillToyVar(selmu_bin0, (Int_t)temp_selmu_bin0);
  output().FillToyVar(selmu_bin1, (Int_t)temp_selmu_bin1);
  output().FillToyVar(selmu_bin2, (Int_t)temp_selmu_bin2);
  output().FillToyVar(selmu_bin3, (Int_t)temp_selmu_bin3);
  output().FillToyVar(selmu_bin4, (Int_t)temp_selmu_bin4);
  output().FillToyVar(selmu_bin5, (Int_t)temp_selmu_bin5);

  //Start SDolan Variables 02/09/15 (sorry for the messy constants here! - WIP):


  //These are constants for the reduced VA idea
  // (see http://www.t2k.org/nd280/physics/xsec/subgroup/cc0pi/2015/july-27-2015/vertexActivityInCC0Pi_1p)

  Float_t muonPathLenVaConst = 4.83;
  Float_t pVaC0 = 184.5;
  Float_t pVaC1 = -0.195;
  Float_t pVaC2 = 0.0000606;
  Float_t selmuRecPL=-999, selmuTruePL=-999, selmuRecVAexp=-999, selmuTrueVAexp=-999;
  Float_t selpRecPL=-999, selpTruePL=-999, selpRecVAexp=-999, selpTrueVAexp=-999;

  //Muon VA vars
  selmuRecPL = numu_cczeropi_utils::get3x3PathLength(numu_cczeropi_box().MuonCandidate->DirectionStart);
  selmuTruePL = numu_cczeropi_utils::get3x3PathLength(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction);
  selmuRecVAexp = selmuRecPL*muonPathLenVaConst;
  selmuTrueVAexp = selmuTruePL*muonPathLenVaConst;
  output().FillToyVar(selmu_3x3_pathLength,selmuRecPL);
  output().FillToyVar(selmu_3x3_truepathLength, selmuTruePL);
  output().FillToyVar(selmu_3x3_expVA, selmuRecVAexp);
  output().FillToyVar(selmu_3x3_trueexpVA, selmuTrueVAexp);

  //Proton VA vars
  selpRecPL = numu_cczeropi_utils::get3x3PathLength(numu_cczeropi_box().ProtonCandidate->DirectionStart);
  selpTruePL = numu_cczeropi_utils::get3x3PathLength(numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Direction);
  Float_t protTrueMom = numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Momentum;
  Float_t protRecMom = numu_cczeropi_box().ProtonCandidate->Momentum;
  selpRecVAexp = (pVaC2*protRecMom*protRecMom + pVaC1*protRecMom + pVaC0)*(selpRecPL/19.0);
  selpTrueVAexp = (pVaC2*protTrueMom*protTrueMom + pVaC1*protTrueMom + pVaC0)*(selpTruePL/19.0);    
  output().FillToyVar(selp_3x3_pathLength, selpRecPL);
  output().FillToyVar(selp_3x3_truepathLength, selpTruePL);
  output().FillToyVar(selp_3x3_expVA, selpRecVAexp);
  output().FillToyVar(selp_3x3_trueexpVA, selpTrueVAexp);

  //Combined VA vars
  output().FillToyVar(selmup_3x3_expVA, selmuRecVAexp+selpRecVAexp);
  output().FillToyVar(selmup_3x3_trueexpVA, selmuTrueVAexp+selpTrueVAexp);    

  //if((numu_cczeropi_box().HMPtrack) && (!(numu_cczeropi_box().ProtonCandidate))) cout << "HMP Track Found, no proton track" << endl; 

  if( (numu_cczeropi_box().Vertex) && (numu_cczeropi_box().ProtonCandidate) && !(numu_cczeropi_box().HMPtrack) ) {
    //std::cout << "Filling recon MEC vars using proton candidate" << endl;
    numu_cczeropi_utils::transversityReco transRecVars(numu_cczeropi_box().MuonCandidate, numu_cczeropi_box().ProtonCandidate, numu_cczeropi_box().Vertex);
    output().FillToyVar(recDphiT,transRecVars.dphiT);
    output().FillToyVar(recDpT,transRecVars.dpT);
    output().FillToyVar(recDalphaT,transRecVars.dalphaT);
    output().FillToyVar(recMrec,transRecVars.tgtmrec);

    numu_cczeropi_utils::transversityTrue transTrueVars(numu_cczeropi_box().MuonCandidate, numu_cczeropi_box().ProtonCandidate, numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex);
    output().FillToyVar(trueDphiT,transTrueVars.dphiT);
    output().FillToyVar(trueDpT,transTrueVars.dpT);
    output().FillToyVar(trueDalphaT,transTrueVars.dalphaT);
    output().FillToyVar(trueMrec,transTrueVars.tgtmrec);

    // New variables July 2019:

    Float_t* selp_dir  = numu_cczeropi_box().ProtonCandidate->DirectionStart;
    Float_t  selp_mom  = numu_cczeropi_box().ProtonCandidate->Momentum;
    Float_t* selmu_dir = numu_cczeropi_box().MuonCandidate->DirectionStart;
    Float_t  selmu_mom = numu_cczeropi_box().MuonCandidate->Momentum;

    Float_t  selp_mom_range =  static_cast<AnaTrack*>(numu_cczeropi_box().ProtonCandidate)->RangeMomentumProton;
    Int_t    selp_ntpcs =      static_cast<AnaTrack*>(numu_cczeropi_box().ProtonCandidate)->nTPCSegments;
    Float_t  selmu_mom_range = static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate)->RangeMomentumMuon;
    Int_t    selmu_ntpcs =     static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate)->nTPCSegments;


    Float_t* vertex_pos = numu_cczeropi_box().Vertex->Position;
    TVector3 sel_NuP = anaUtils::GetNuDirRec(vertex_pos);
    TVector3 sel_LeptonP(selmu_dir[0]*selmu_mom, selmu_dir[1]*selmu_mom, selmu_dir[2]*selmu_mom);
    TVector3 sel_HadronP(selp_dir[0]*selp_mom, selp_dir[1]*selp_mom, selp_dir[2]*selp_mom);

    // use range momentum if muon/proton do not have a TPC track
    if(selmu_ntpcs==0){
      sel_LeptonP[0] = selmu_dir[0]*selmu_mom_range;
      sel_LeptonP[1] = selmu_dir[1]*selmu_mom_range;
      sel_LeptonP[2] = selmu_dir[2]*selmu_mom_range;
    }

    if(selp_ntpcs==0){
      sel_HadronP[0] = selp_dir[0]*selp_mom_range;
      sel_HadronP[1] = selp_dir[1]*selp_mom_range;
      sel_HadronP[2] = selp_dir[2]*selp_mom_range;
    }

    output().FillToyVar(recPn,(1.0/1000.0)*numu_cczeropi_utils::Get_pn_reco_C(sel_NuP, sel_LeptonP, sel_HadronP));

    AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex);
    Float_t* NuDir = vtx->NuDir;
    TVector3 true_NuP(NuDir[0], NuDir[1], NuDir[2]);

    /*
    Float_t  NuMom = vtx->NuEnergy;
    Float_t  leptonMom = vtx->LeptonMom;
    Float_t* leptonDir = vtx->LeptonDir;
    Float_t  protonMom = vtx->ProtonMom;
    Float_t* protonDir = vtx->ProtonDir;

    TVector3 true_TrueLeptonP(leptonDir[0]*leptonMom, leptonDir[1]*leptonMom, leptonDir[2]*leptonMom);
    TVector3 true_TrueHadronP(protonDir[0]*protonMom, protonDir[1]*protonMom, protonDir[2]*protonMom);
    */

    Float_t* selp_truedir = numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Direction;
    Float_t  selp_truemom = numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Momentum;
    Float_t* selmu_truedir = numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction;
    Float_t  selmu_truemom = numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Momentum;

    TVector3 true_LeptonP(selmu_truedir[0]*selmu_truemom, selmu_truedir[1]*selmu_truemom, selmu_truedir[2]*selmu_truemom);
    TVector3 true_HadronP(selp_truedir[0]*selp_truemom, selp_truedir[1]*selp_truemom, selp_truedir[2]*selp_truemom);


    output().FillToyVar(truePn,(1.0/1000.0)*numu_cczeropi_utils::Get_pn_reco_C(true_NuP, true_LeptonP, true_HadronP));

    /*

    cout << "selp_dir[2] is: " << selp_dir[2] << endl;
    cout << "selp_mom is: " << selp_mom << endl;
    cout << "selmu_dir[2] is: " << selmu_dir[2] << endl;
    cout << "selmu_mom is: " << selmu_mom << endl;

    cout << "truep_dir[2] is: " << protonDir[2] << endl;
    cout << "truep_mom is: " << protonMom << endl;
    cout << "truemu_dir[2] is: " << leptonDir[2] << endl;
    cout << "truemu_mom is: " << leptonMom << endl;

    cout << "selp_truedir[2] is: " << selp_truedir[2] << endl;
    cout << "selp_truemom is: " << selp_truemom << endl;
    cout << "selmu_truedir[2] is: " << selmu_truedir[2] << endl;
    cout << "selmu_truemom is: " << selmu_truemom << endl;

    cout <<"True dpT and pn is: "<<transTrueVars.dpT<<","<<numu_cczeropi_utils::Get_pn_reco_C(true_NuP, true_LeptonP, true_HadronP)<<endl;
    cout <<"Rec dpT and pn is: "<<transRecVars.dpT<<","<<numu_cczeropi_utils::Get_pn_reco_C(sel_NuP, sel_LeptonP, sel_HadronP)<<endl;
    cout <<"Inferred nu dir from psyche: "; sel_NuP.Print();

    cout <<"TrueT pn is: "<<numu_cczeropi_utils::Get_pn_reco_C(true_NuP, true_TrueLeptonP, true_TrueHadronP)<<endl;

    */

  }

}



//********************************************************************
void numuCCZeroPiAnalysis::FillMuonCandidateInfo(){
  //********************************************************************

  // Overwride Muon candidate variables (since they are not filled in numuccAnalysis when the muon is in FGD)

  if (!numu_cczeropi_box().MuonCandidate) return;

  AnaTrack* MuonCandidate = static_cast<AnaTrack*>( numu_cczeropi_box().MuonCandidate );

  //Timing
  /*
     if( numu_cczeropi_box().type_muon == AnaBoxCCZeroPi::kTPC_Fwd || numu_cczeropi_box().type_muon == AnaBoxCCZeroPi::kFGD_Fwd ){
     output().FillVar(selmu_sense,           1);  
     }else if( numu_cczeropi_box().type_muon == AnaBoxCCZeroPi::kTPC_Bwd || numu_cczeropi_box().type_muon == AnaBoxCCZeroPi::kFGD_Bwd ){
     output().FillVar(selmu_sense,           -1);
     }
     */

  output().FillVar(selmu_Bwd_mom,         MuonCandidate->MomentumFlip);
  output().FillVar(selmu_Bwd_costheta,    MuonCandidate->DirectionStartFlip[2] );	
  output().FillVar(selmu_Flag_FGD1_FGD2,  MuonCandidate->ToF.Flag_FGD1_FGD2       * 2 - 1 );
  output().FillVar(selmu_Flag_P0D_FGD1,   MuonCandidate->ToF.Flag_P0D_FGD1        * 2 - 1 );
  output().FillVar(selmu_Flag_ECal_FGD1,  MuonCandidate->ToF.Flag_ECal_FGD1       * 2 - 1 );
  output().FillVar(selmu_Flag_ECal_FGD2,  MuonCandidate->ToF.Flag_ECal_FGD2       * 2 - 1 );

  // for quality cut studies
  output().FillVar(selmu_invpt, anaUtils::ComputeInversePT(*(numu_cczeropi_box().MuonCandidate)));       
  output().FillVar(selmu_charge, (Int_t)numu_cczeropi_box().MuonCandidate->Charge);     
  if( numu_cczeropi_box().MuonCandidate->GetTrueParticle() ) {
    output().FillVar(selmu_trueinvpt, anaUtils::ComputeInversePT(*(numu_cczeropi_box().MuonCandidate->GetTrueParticle())));       
    output().FillVar(selmu_truecharge, (Int_t)numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Charge);
  }

  if (!anaUtils::TrackUsesDet(*(numu_cczeropi_box().MuonCandidate), SubDetId::kTPC)){
    //  output().FillVar(numuCCAnalysis::selmu_costheta,    numu_cczeropi_box().MuonCandidate->DirectionStart[2]);
    output().FillVectorVarFromArray(numuCCAnalysis::selmu_pos,     numu_cczeropi_box().MuonCandidate->PositionStart,   4);
    output().FillVectorVarFromArray(numuCCAnalysis::selmu_endpos,  numu_cczeropi_box().MuonCandidate->PositionEnd,     4);
    output().FillVectorVarFromArray(numuCCAnalysis::selmu_dir,     numu_cczeropi_box().MuonCandidate->DirectionStart,  3);

    if (anaUtils::InDetVolume(SubDetId::kFGD1,numu_cczeropi_box().MuonCandidate->PositionStart) && 
        anaUtils::TrackUsesOnlyDet(*numu_cczeropi_box().MuonCandidate, SubDetId::kFGD1)) {
      output().FillVar(selmu_length,    numu_cczeropi_utils::GetFGDTrackLength(numu_cczeropi_box().MuonCandidate));
    }

    if(  numu_cczeropi_box().MuonCandidate->GetTrueParticle() ) {
      output().FillVar(numuCCAnalysis::selmu_truemom,         numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Momentum);       
      output().FillVectorVarFromArray(numuCCAnalysis::selmu_truepos,   numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Position,    4);       
      output().FillVectorVarFromArray(numuCCAnalysis::selmu_trueendpos,numu_cczeropi_box().MuonCandidate->GetTrueParticle()->PositionEnd, 4);       
      output().FillVectorVarFromArray(numuCCAnalysis::selmu_truedir,   numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction,   3);       
      output().FillVar(selmu_trueztheta,  (Float_t)acos(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction[2]));   


      if (numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex){
        AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex);
        output().FillVar(selmu_truenutheta, (Float_t)acos(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction*anaUtils::ArrayToTVector3(vtx->NuDir)));
        output().FillVar(numuCCAnalysis::truelepton_mom,vtx->LeptonMom);
        output().FillVar(numuCCAnalysis::truelepton_costheta,(Float_t)cos(anaUtils::ArrayToTVector3(vtx->LeptonDir).Angle(anaUtils::ArrayToTVector3(vtx->NuDir))));
        //q0,q3 - only for muons
        if(vtx->LeptonPDG==13){
          Float_t Enu_true = vtx->NuEnergy;
          Float_t leptonMom = vtx->LeptonMom;
          Float_t leptonNuDir = (Float_t)acos(vtx->LeptonDir*anaUtils::ArrayToTVector3(vtx->NuDir));
          Float_t leptonMass = 105.65837; // Sorry for the hard coding, is this defined somewhere?
          Float_t leptonE = sqrt(leptonMom * leptonMom + leptonMass * leptonMass); 
          output().FillVar(q0_true,  Enu_true - leptonE);      
          output().FillVar(q3_true,  (Float_t)sqrt(leptonMom * leptonMom + Enu_true * Enu_true - 2.0 * leptonMom * Enu_true * leptonNuDir));  
        }
      }

    }

    // Info in all FGDs 
    for (Int_t subdet = 0; subdet<2; subdet++) {
      if (!SubDetId::GetDetectorUsed(numu_cczeropi_box().MuonCandidate->Detector, static_cast<SubDetId::SubDetEnum >(subdet))) continue;
      AnaFGDParticle* FGDSegment = static_cast<AnaFGDParticle*>(anaUtils::GetSegmentInDet(*(numu_cczeropi_box().MuonCandidate), static_cast<SubDetId::SubDetEnum >(subdet)));
      if (!FGDSegment) continue;
      output().FillVectorVar(numuCCAnalysis::selmu_fgd_det,     subdet);
      output().FillVectorVar(numuCCAnalysis::selmu_fgd_x,       FGDSegment->X);
      
      if (!_numuCCAddonToyVars)
        output().FillVectorVar(numuCCAnalysis::selmu_fgd_pullmu, FGDSegment->Pullmu);

      output().IncrementCounterForVar(numuCCAnalysis::selmu_fgd_x);
    }

    if (_prangeEnabled){

      // Momentum by range
      Float_t pr = momrange_box().muon_momrange;
      output().FillVar(nu_e_momrange, numu_cczeropi_utils::GetRecNuEnergy(*(numu_cczeropi_box().MuonCandidate),pr));
      // Reconstructed Q2
      output().FillVar(q2_rec_momrange, numu_cczeropi_utils::GetRecQ2(*(numu_cczeropi_box().MuonCandidate),pr));      

    }

    if (_prangeVertexEnabled){
      if (numu_cczeropi_box().ProtonCandidate){ 
        if (anaUtils::TrackUsesDet(*(numu_cczeropi_box().ProtonCandidate), SubDetId::kTPC)){ //isnt true in case 4
          TVector3 vertex = anaUtils::ArrayToTVector3(numu_cczeropi_box().ProtonCandidate->PositionStart);
          Float_t pr_vertex = momrange_box().muon_momrange_vertex;
          output().FillVar(nu_e_momrange_vertex, 
              numu_cczeropi_utils::GetRecNuEnergy(*(numu_cczeropi_box().MuonCandidate),pr_vertex));
        }
      }
    } 
  } //track does not use TPC

}

//********************************************************************
void numuCCZeroPiAnalysis::FillHMP_TrueInfo(){
  //********************************************************************

  if (!numu_cczeropi_box().HMPtrack) return;

  //true variables
  AnaTrueParticleB* trueTrack = numu_cczeropi_box().HMPtrack->GetTrueParticle();

  if(!trueTrack)  return;

  output().FillVar(                 selHMP_truemom,   trueTrack->Momentum    );       
  output().FillVectorVarFromArray(  selHMP_truepos,   trueTrack->Position,  4);       
  output().FillVectorVarFromArray(  selHMP_truedir,   trueTrack->Direction, 3);       
  output().FillVar(                 selHMP_truepdg,   (Int_t)trueTrack->PDG  );


}

//********************************************************************
void numuCCZeroPiAnalysis::FillHMP_ToyVars(){
  //********************************************************************

  if (!numu_cczeropi_box().HMPtrack) return;

  //true variables
  AnaTrackB* track = numu_cczeropi_box().HMPtrack; 

  output().FillToyVar(                 selHMP_mom,   track->Momentum         );       

  for (int i=0; i<4; i++)
    output().FillToyVectorVar(  selHMP_pos,   track->PositionStart[i],  i);

  for (int i=0; i<3; i++)
    output().FillToyVectorVar(  selHMP_dir,   track->DirectionStart[i], i);  

  //Transverse Vars and M_rec:
  if( (numu_cczeropi_box().Vertex) && (numu_cczeropi_box().MuonCandidate) && (_addMECVars) ){
    //std::cout << "Filling recon MEC vars using HMP candidate" << endl;
    numu_cczeropi_utils::transversityReco transRecVars(numu_cczeropi_box().MuonCandidate, numu_cczeropi_box().HMPtrack, numu_cczeropi_box().Vertex);
    output().FillToyVar(recDphiT,transRecVars.dphiT);
    output().FillToyVar(recDpT,transRecVars.dpT);
    output().FillToyVar(recDalphaT,transRecVars.dalphaT);
    output().FillToyVar(recMrec,transRecVars.tgtmrec);

    numu_cczeropi_utils::transversityTrue transTrueVars(numu_cczeropi_box().MuonCandidate, numu_cczeropi_box().HMPtrack, numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex);
    output().FillToyVar(trueDphiT,transTrueVars.dphiT);
    output().FillToyVar(trueDpT,transTrueVars.dpT);
    output().FillToyVar(trueDalphaT,transTrueVars.dalphaT);
    output().FillToyVar(trueMrec,transTrueVars.tgtmrec);
    //cout << "HMP mom and dir: " << numu_cczeropi_box().HMPtrack->Momentum << ", " << numu_cczeropi_box().HMPtrack->DirectionStart[0] << ", " << numu_cczeropi_box().HMPtrack->DirectionStart[1] << ", " << numu_cczeropi_box().HMPtrack->DirectionStart[2] << endl;
    //cout <<"Recon tgtmRec, dphiT, dpT and dalphaT is:"<<transRecVars.tgtmrec<<","<<transRecVars.dphiT<<","<<transRecVars.dpT<<","<<transRecVars.dalphaT<<endl;


    //New pn variable July 2019

    Float_t* selp_dir  = numu_cczeropi_box().HMPtrack->DirectionStart;
    Float_t  selp_mom  = numu_cczeropi_box().HMPtrack->Momentum;
    Float_t* selmu_dir = numu_cczeropi_box().MuonCandidate->DirectionStart;
    Float_t  selmu_mom = numu_cczeropi_box().MuonCandidate->Momentum;

    Float_t  selp_mom_range =  static_cast<AnaTrack*>(numu_cczeropi_box().HMPtrack)->RangeMomentumProton;
    Int_t    selp_ntpcs =      static_cast<AnaTrack*>(numu_cczeropi_box().HMPtrack)->nTPCSegments;
    Float_t  selmu_mom_range = static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate)->RangeMomentumMuon;
    Int_t    selmu_ntpcs =     static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate)->nTPCSegments;


    Float_t* vertex_pos = numu_cczeropi_box().Vertex->Position;
    TVector3 sel_NuP = anaUtils::GetNuDirRec(vertex_pos);
    TVector3 sel_LeptonP(selmu_dir[0]*selmu_mom, selmu_dir[1]*selmu_mom, selmu_dir[2]*selmu_mom);
    TVector3 sel_HadronP(selp_dir[0]*selp_mom, selp_dir[1]*selp_mom, selp_dir[2]*selp_mom);

    // use range momentum if muon/proton do not have a TPC track
    if(selmu_ntpcs==0){
      sel_LeptonP[0] = selmu_dir[0]*selmu_mom_range;
      sel_LeptonP[1] = selmu_dir[1]*selmu_mom_range;
      sel_LeptonP[2] = selmu_dir[2]*selmu_mom_range;
    }

    if(selp_ntpcs==0){
      sel_HadronP[0] = selp_dir[0]*selp_mom_range;
      sel_HadronP[1] = selp_dir[1]*selp_mom_range;
      sel_HadronP[2] = selp_dir[2]*selp_mom_range;
    }

    output().FillToyVar(recPn,(1.0/1000.0)*numu_cczeropi_utils::Get_pn_reco_C(sel_NuP, sel_LeptonP, sel_HadronP));

    AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex);
    Float_t* NuDir = vtx->NuDir;
    TVector3 true_NuP(NuDir[0], NuDir[1], NuDir[2]);

    /*
    Float_t  leptonMom = vtx->LeptonMom;
    Float_t* leptonDir = vtx->LeptonDir;
    Float_t  protonMom = vtx->ProtonMom;
    Float_t* protonDir = vtx->ProtonDir;

    TVector3 true_TrueLeptonP(leptonDir[0]*leptonMom, leptonDir[1]*leptonMom, leptonDir[2]*leptonMom);
    TVector3 true_TrueHadronP(protonDir[0]*protonMom, protonDir[1]*protonMom, protonDir[2]*protonMom);
    */


    Float_t* selp_truedir = numu_cczeropi_box().HMPtrack->GetTrueParticle()->Direction;
    Float_t  selp_truemom = numu_cczeropi_box().HMPtrack->GetTrueParticle()->Momentum;
    Float_t* selmu_truedir = numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Direction;
    Float_t  selmu_truemom = numu_cczeropi_box().MuonCandidate->GetTrueParticle()->Momentum;

    TVector3 true_LeptonP(selmu_truedir[0]*selmu_truemom, selmu_truedir[1]*selmu_truemom, selmu_truedir[2]*selmu_truemom);
    TVector3 true_HadronP(selp_truedir[0]*selp_truemom, selp_truedir[1]*selp_truemom, selp_truedir[2]*selp_truemom);

    output().FillToyVar(truePn,(1.0/1000.0)*numu_cczeropi_utils::Get_pn_reco_C(true_NuP, true_LeptonP, true_HadronP));



  }
  //else std::cout << "Missing Muon/Vertex Info To fill Rec STV info" << endl;

}

//********************************************************************
void numuCCZeroPiAnalysis::FillProtonCandidateInfo(){
  //********************************************************************

  if (!numu_cczeropi_box().ProtonCandidate) return;

  //true variables
  if(  numu_cczeropi_box().ProtonCandidate->GetTrueParticle() ) {
    output().FillVar(selp_truemom,         numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Momentum);       
    output().FillVectorVarFromArray(selp_truepos,     numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Position,    4);       
    output().FillVectorVarFromArray(selp_trueendpos,  numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->PositionEnd, 4);       
    output().FillVectorVarFromArray(selp_truedir,     numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Direction,   3);       
    output().FillVar(selp_pdg, numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->PDG);

    if (numu_cczeropi_box().Vertex && numu_cczeropi_box().Vertex->TrueVertex) {

      output().FillVar(selp_trueztheta,  (Float_t)acos(numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Direction[2]));       

      output().FillVar(selp_truenutheta, (Float_t)acos(anaUtils::ArrayToTVector3(numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->Direction)*
            anaUtils::ArrayToTVector3(static_cast<AnaTrueVertex*>(numu_cczeropi_box().Vertex->TrueVertex)->NuDir)));

      //Same true vertex for p and mu
      if(numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->TrueVertex && numu_cczeropi_box().MuonCandidate && 
          numu_cczeropi_box().MuonCandidate->GetTrueParticle() && numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex){
        output().FillVar(selp_true_same,  (numu_cczeropi_box().ProtonCandidate->GetTrueParticle()->TrueVertex == numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex) * 2 - 1 );
      }

    }

  }
  //basic kinematic variables that wont be changed by systematics propagation
  output().FillVar(selp_costheta,     numu_cczeropi_box().ProtonCandidate->DirectionStart[2]);
  output().FillVectorVarFromArray(selp_pos,    numu_cczeropi_box().ProtonCandidate->PositionStart, 4);
  output().FillVectorVarFromArray(selp_endpos, numu_cczeropi_box().ProtonCandidate->PositionEnd, 4);
  output().FillVectorVarFromArray(selp_dir,    numu_cczeropi_box().ProtonCandidate->DirectionStart, 3);
  output().FillVar(selp_theta,    acos(numu_cczeropi_box().ProtonCandidate->DirectionStart[2]));


  // The closest TPC
  SubDetId::SubDetEnum tpc = anaUtils::GetClosestTPC(*(numu_cczeropi_box().ProtonCandidate));
  output().FillVar(selp_closest_tpc, (Int_t)(tpc+1));      

  // Track composition
  output().FillVar(selp_detectors, (Int_t)(static_cast<AnaTrack*>(numu_cczeropi_box().ProtonCandidate)->Detectors));      

  // Info in all TPCs 
  for (Int_t subdet = 0; subdet<3; subdet++) {
    if (!SubDetId::GetDetectorUsed(numu_cczeropi_box().ProtonCandidate->Detector, static_cast<SubDetId::SubDetEnum >(subdet+2))) continue;
    AnaTPCParticle* TPCSegment = static_cast<AnaTPCParticle*>(anaUtils::GetSegmentInDet( *numu_cczeropi_box().ProtonCandidate,static_cast<SubDetId::SubDetEnum >(subdet+2)));
    if (!TPCSegment) continue;
    //      output().FillVectorVar(selmu_tpc_det,     (Int_t)TPCSegment->Detector);
    output().FillVectorVar(selp_tpc_det,     subdet);
    output().FillVectorVar(selp_tpc_mom,     TPCSegment->Momentum);
    output().FillVectorVar(selp_tpc_charge,  TPCSegment->Charge);
    //      output().FillVectorVar(selmu_tpc_nhits,   TPCSegment->NHits);
    output().FillVectorVar(selp_tpc_nnodes,  TPCSegment->NNodes);
    output().FillVectorVar(selp_tpc_emom,    TPCSegment->MomentumError);

    //  Float_t Ptrue,PTtrue;
    //      if (anaUtils::ComputeTruePandPT(*TPCSegment,Ptrue,PTtrue))  (TODO)
    //	output().FillVectorVar(selmu_tpc_truemom,  Ptrue);


    //      output().FillVectorVar(selmu_tpc_dedx,    TPCSegment->dEdxMeas);
    if (TPCSegment->Original->Original)
      output().FillVectorVar(selp_tpc_dedx_raw,    (static_cast< const AnaTPCParticle* >(TPCSegment->Original->Original))->dEdxMeas);

    output().FillVectorVar(selp_tpc_dedx_expmu,  TPCSegment->dEdxexpMuon);
    output().FillVectorVar(selp_tpc_dedx_exppi,  TPCSegment->dEdxexpPion);
    output().FillVectorVar(selp_tpc_dedx_expele, TPCSegment->dEdxexpEle);
    output().FillVectorVar(selp_tpc_dedx_expp,   TPCSegment->dEdxexpProton);
    output().IncrementCounterForVar(selp_tpc_det);

  }
  // Info in all FGDs 
  for (Int_t subdet = 0; subdet<2; subdet++) {
    if (!SubDetId::GetDetectorUsed(numu_cczeropi_box().ProtonCandidate->Detector, static_cast<SubDetId::SubDetEnum >(subdet))) continue;
    AnaFGDParticle* FGDSegment = static_cast<AnaFGDParticle*>(anaUtils::GetSegmentInDet( *numu_cczeropi_box().ProtonCandidate,static_cast<SubDetId::SubDetEnum >(subdet)));
    if (!FGDSegment) continue;

    //							      output().FillVectorVar("selp_fgd_det",     (Int_t)FGDSegment->Detector);
    output().FillVectorVar(selp_fgd_det,      subdet);
    output().FillVectorVar(selp_fgd_x,        FGDSegment->X);
    output().FillVectorVar(selp_fgd_e,        FGDSegment->E);
    
    output().IncrementCounterForVar(selp_fgd_det);
  }


}

/*
   void numuCCZeroPiAnalysis::FillGeneratorInfo(){

// Take the HMN track vertex
AnaVertexB* vertex = numu_cczeropi_box().Vertex;

if (!vertex) return;
if (!vertex->TrueVertex) return;

AnaSpillGenInfo* cspill = static_cast<AnaSpillGenInfo*>(&(input().GetSpill()));
std::vector<AnaGenVertex*> vertices = cspill->GenVertices; 

AnaGenVertex* genvertex = NULL;

for (unsigned int i=0;i<vertices.size();i++){
AnaGenVertex* genvertex2 = vertices[i];
if (vertex->TrueVertex->TruthVertexID == genvertex2->TruthVertexID){
genvertex= genvertex2;
}
}

if (!genvertex) return;

bool pfilled=false;
bool mufilled=false;
AnaGenParticle* proton = NULL;
AnaGenParticle* muon = NULL;

for (unsigned int j=0;j<genvertex->GenParticles.size();j++){
AnaGenParticle* part = genvertex->GenParticles[j];

// when plotting NEUT particle's variables remind that in a CCQE interaction:
// neut particle 0 is the neutrino (parent index = 0)
// neut particle 1 is the neutron (parent index = 0)
// neut particle 2 is the primary muon (parent index = 1)
// neut particle 3 is the primary proton (parent index = 2)
// neut secondary particles have parent index = 4

if (part->ParentIndex==2 && part->PDG==2212 && !pfilled){ // the first proton of the list with parent index 2 is the primary proton
output().FillVar(gen_p_esc,   part->Escaped);		
output().FillVar(gen_p_pdg,   part->PDG);		
proton = part;
pfilled=true;
}

if (part->ParentIndex==1 && part->PDG==13 && !mufilled){ // the first muon of the list with parent index 1 is the primary muon
output().FillVar(gen_p_esc,   part->Escaped);		
output().FillVar(gen_p_pdg,   part->PDG);		
muon = part;
mufilled=true;
}
}

}
*/
//********************************************************************
void numuCCZeroPiAnalysis::FillMECInfo(){
  //********************************************************************

  if (!numu_cczeropi_box().MuonCandidate) return;
  if (!numu_cczeropi_box().ProtonCandidate) return;

  // AnaTrack* MuonCandidate = static_cast<AnaTrack*>( numu_cczeropi_box().MuonCandidate );
  AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex);

  int nprotons = 0, npions = 0, nneutrons = 0;


  for(int i = 0; i<vtx->nTrueParticles; i++){
    //std::cout<<"pdg : "<< vtx.TrueParticles[i]->PDG <<std::endl;
    if( vtx->TrueParticles[i]->PDG == 2212 && vtx->TrueParticles[i]->ParentPDG == 0 ) nprotons++; 
    if( ( vtx->TrueParticles[i]->PDG == 211 || vtx->TrueParticles[i]->PDG == -211 )&& vtx->TrueParticles[i]->ParentPDG == 0 ) npions++;
    if( vtx->TrueParticles[i]->PDG == 2112 && vtx->TrueParticles[i]->ParentPDG == 0 ) nneutrons++; 

  }

  output().FillVar(true_nprotons, nprotons);
  output().FillVar(true_npions,   npions);
  output().FillVar(true_nneutrons, nneutrons);


  Float_t temp_threemom[3] = {vtx->ProtonMom * vtx->ProtonDir[0], vtx->ProtonMom * vtx->ProtonDir[1], vtx->ProtonMom * vtx->ProtonDir[2] } ;
  Float_t temp_infp_threemom[3] = {-(vtx->LeptonMom * vtx->LeptonDir[0]), -(vtx->LeptonMom * vtx->LeptonDir[1]), -(vtx->LeptonMom * vtx->LeptonDir[2]) + numu_cczeropi_utils::GetRecNuEnergy(vtx->LeptonMom, vtx->LeptonDir, vtx->NuDir, 0) };


  output().FillVar(truep_truemom, vtx->ProtonMom);
  output().FillVar(truep_truecostheta, vtx->ProtonDir[2]);
  output().FillVectorVarFromArray(truep_truethreemom, temp_threemom,3);
  output().FillVar(truemu_infp_mom,numu_cczeropi_utils::InferProtonMomentum(vtx->LeptonMom, numu_cczeropi_utils::GetRecNuEnergy(vtx->LeptonMom, vtx->LeptonDir, vtx->NuDir, 0)));
  output().FillVar(truemu_infp_costheta,numu_cczeropi_utils::InferProtonAngle(vtx->LeptonMom,numu_cczeropi_utils::GetRecNuEnergy(vtx->LeptonMom, vtx->LeptonDir, vtx->NuDir, 0) ));
  output().FillVectorVarFromArray(truemu_infp_threemom, temp_infp_threemom ,3);


  Float_t mu_mom =  vtx->LeptonMom;
  Float_t mu_costheta = vtx->LeptonDir[2];
  Float_t mu_angle_degree = acos(mu_costheta)*180/3.14;


  bool temp_truemu_bin0 = mu_mom < 375 && mu_angle_degree < 60;
  bool temp_truemu_bin1 = mu_mom < 375 && mu_angle_degree > 60;
  bool temp_truemu_bin2 = mu_mom > 375 && mu_mom < 700 && mu_angle_degree < 30;
  bool temp_truemu_bin3 = mu_mom > 375 && mu_mom < 700 && mu_angle_degree > 30;
  bool temp_truemu_bin4 = mu_mom > 700 && mu_mom < 2000;
  bool temp_truemu_bin5 = mu_mom > 2000;  

  output().FillVar(truemu_bin0, (Int_t)temp_truemu_bin0);
  output().FillVar(truemu_bin1, (Int_t)temp_truemu_bin1);
  output().FillVar(truemu_bin2, (Int_t)temp_truemu_bin2);
  output().FillVar(truemu_bin3, (Int_t)temp_truemu_bin3);
  output().FillVar(truemu_bin4, (Int_t)temp_truemu_bin4);
  output().FillVar(truemu_bin5, (Int_t)temp_truemu_bin5); 


  //Extra Vertex Variables added by Stephen:
  if (numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex){
    AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(numu_cczeropi_box().MuonCandidate->GetTrueParticle()->TrueVertex);
    output().FillVar(ntruetracks, vtx->nTrueParticles);  
    int nprotons=0, nchargedpions=0, nother=0, nfstracks=0;
    for(int i = 0; i<vtx->nTrueParticles; i++){
      if( vtx->TrueParticles[i]->ParentPDG == 0 ) nfstracks++;
      if( vtx->TrueParticles[i]->PDG == 2212 && vtx->TrueParticles[i]->ParentPDG == 0 ) nprotons++;
      else if( (vtx->TrueParticles[i]->PDG == 211 || vtx->TrueParticles[i]->PDG == -211 ) && vtx->TrueParticles[i]->ParentPDG == 0 ) nchargedpions++;
      else if( vtx->TrueParticles[i]->ParentPDG == 0 ){
        output().FillVar(ntrueotherpdg, vtx->TrueParticles[i]->PDG);
        nother++;
      }
    }
    output().FillVar(ntruefstracks, nfstracks);  
    output().FillVar(ntrueprotons, nprotons);
    output().FillVar(ntruechargedpions, nchargedpions);
    output().FillVar(ntrueother, nother);    
  }


}




//********************************************************************
bool numuCCZeroPiAnalysis::CheckFillTruthTree(const AnaTrueVertex& vtx){
  //********************************************************************

  bool saveAllNumuCC= true;

  bool numuCC=vtx.ReacCode>0 && vtx.ReacCode<30 && vtx.NuPDG==14;// && vtx.LeptonPDG==13;


  if (saveAllNumuCC)
    return numu_cczeropi_utils::InFGDFV(_fgdID, vtx.Position ) && numuCC;

  return numu_cczeropi_utils::InFGDFV(_fgdID, vtx.Position) && numuCC && vtx.ReacCode==1;
}

//********************************************************************
void numuCCZeroPiAnalysis::FillTruthTree(const AnaTrueVertex& vtx){
  //********************************************************************


  // Fill the numuCC variables
  // This will fill fgd1 and fgd2 categories as well
  _numuCCAnalysis->FillTruthTree(vtx);

  output().FillVar(true_ntracks,         vtx.nTrueParticles );

  //q0,q3 - only for muons
  if(vtx.LeptonPDG==13){
    Float_t Enu_true = vtx.NuEnergy;
    Float_t leptonMom = vtx.LeptonMom;
    Float_t leptonNuDir = (Float_t)acos(vtx.LeptonDir*anaUtils::ArrayToTVector3(vtx.NuDir));
    Float_t leptonMass = 105.65837; // Sorry for the hard coding, is this defined somewhere?
    Float_t leptonE = sqrt(leptonMom * leptonMom + leptonMass * leptonMass); 
    output().FillVar(q0_true,  Enu_true - leptonE);      
    output().FillVar(q3_true,  (Float_t)sqrt(leptonMom * leptonMom + Enu_true * Enu_true - 2.0 * leptonMom * Enu_true * leptonNuDir));  
  }


  if (_addPionTrueVars){

    //get the true pions from the vertex
    AnaTrueParticleB* tracks[NMAXTRUEPARTICLES];

    // Get all true pion tracks associated with the vertex
    int ntracks = numu_cczeropi_utils::GetParticlesFromVertex(vtx, tracks, _pion_pdgs);
    if((UInt_t)ntracks>NMAXTRUEPARTICLES) ntracks = NMAXTRUEPARTICLES;

    for (int i=0; i<ntracks; i++){
      AnaTrueParticleB* trueTrack = tracks[i];
      if(!trueTrack) continue;

      bool primary = (bool)(trueTrack->ParentPDG == 0);

      //primary
      if (primary){
        output().FillMatrixVarFromArray(  trueprim_pi_truepos,          trueTrack->Position,   4);
        output().FillMatrixVarFromArray(  trueprim_pi_truedir,          trueTrack->Direction,  3);
        output().FillVectorVar(           trueprim_pi_truemom,          trueTrack->Momentum);
        output().FillVectorVar(           trueprim_pi_truepdg,          trueTrack->PDG);
        // increment counter for vector/matrix vars
        output().IncrementCounterForVar(trueprim_pi_truepos);
      }
      //secondary
      else {
        output().FillMatrixVarFromArray(  truesec_pi_truepos,           trueTrack->Position,   4);
        output().FillMatrixVarFromArray(  truesec_pi_truedir,           trueTrack->Direction,  3);
        output().FillVectorVar(           truesec_pi_truemom,           trueTrack->Momentum);
        output().FillVectorVar(           truesec_pi_truepdg,           trueTrack->PDG);
        output().FillVectorVar(           truesec_pi_true_parentpdg,    trueTrack->ParentPDG);
        // increment counter for vector/matrix vars
        output().IncrementCounterForVar(truesec_pi_truepos);
      }
    }    
  }

  if (_addProtonTrueVars){

    //get the true pions from the vertex
    AnaTrueParticleB* tracks[NMAXTRUEPARTICLES];

    std::set<int> proton_tmp;
    proton_tmp.insert(2212);

    // Get all true pion tracks associated with the vertex
    int ntracks = numu_cczeropi_utils::GetParticlesFromVertex(vtx, tracks, proton_tmp);
    if((UInt_t)ntracks>NMAXTRUEPARTICLES) ntracks = NMAXTRUEPARTICLES;

    for (int i=0; i<ntracks; i++){
      AnaTrueParticleB* trueTrack = tracks[i];
      if(!trueTrack) continue;

      bool primary = (bool)(trueTrack->ParentPDG == 0);

      //primary
      if (primary){
        output().FillMatrixVarFromArray(  trueprim_proton_truepos,          trueTrack->Position,   4);
        output().FillMatrixVarFromArray(  trueprim_proton_truedir,          trueTrack->Direction,  3);
        output().FillVectorVar(           trueprim_proton_truemom,          trueTrack->Momentum);
        // increment counter for vector/matrix vars
        output().IncrementCounterForVar(trueprim_proton_truepos);
      }
      //secondary
      else {
        output().FillMatrixVarFromArray(  truesec_proton_truepos,           trueTrack->Position,   4);
        output().FillMatrixVarFromArray(  truesec_proton_truedir,           trueTrack->Direction,  3);
        output().FillVectorVar(           truesec_proton_truemom,           trueTrack->Momentum);
        output().FillVectorVar(           truesec_proton_true_parentpdg,    trueTrack->ParentPDG);
        // increment counter for vector/matrix vars
        output().IncrementCounterForVar(truesec_proton_truepos);
      }
    }    
  }


  int nprotons = 0, npions = 0, nneutrons = 0;
  for(int i = 0; i<vtx.nTrueParticles; i++){
    //std::cout<<"pdg : "<< vtx.TrueParticles[i]->PDG <<std::endl;
    if( vtx.TrueParticles[i]->PDG == 2212 && vtx.TrueParticles[i]->ParentPDG == 0 ) nprotons++;
    if( ( vtx.TrueParticles[i]->PDG == 211 || vtx.TrueParticles[i]->PDG == -211 ) && vtx.TrueParticles[i]->ParentPDG == 0 ) npions++;
     if( vtx.TrueParticles[i]->PDG == 2112 && vtx.TrueParticles[i]->ParentPDG == 0 ) nneutrons++;
  }
  output().FillVar(true_nprotons,    nprotons);
  output().FillVar(true_npions,      npions);
  output().FillVar(true_nneutrons,   nneutrons);
  

  if(_addMECVars){
    Float_t temp_threemom[3] = {vtx.ProtonMom * vtx.ProtonDir[0], vtx.ProtonMom * vtx.ProtonDir[1], vtx.ProtonMom * vtx.ProtonDir[2] } ;    
    Float_t temp_infp_threemom[3] = {-(vtx.LeptonMom * vtx.LeptonDir[0]), -(vtx.LeptonMom * vtx.LeptonDir[1]), -(vtx.LeptonMom * vtx.LeptonDir[2]) + numu_cczeropi_utils::GetRecNuEnergy(vtx.LeptonMom, vtx.LeptonDir, vtx.NuDir, 0) };

    output().FillVar(truep_truemom, vtx.ProtonMom);
    output().FillVar(truep_truecostheta, vtx.ProtonDir[2]);
    output().FillVectorVarFromArray(truep_truethreemom, temp_threemom,3);

    output().FillVar(truemu_infp_mom,numu_cczeropi_utils::InferProtonMomentum(vtx.LeptonMom, numu_cczeropi_utils::GetRecNuEnergy(vtx.LeptonMom, vtx.LeptonDir, vtx.NuDir, 0)));
    output().FillVar(truemu_infp_costheta,numu_cczeropi_utils::InferProtonAngle(vtx.LeptonMom,numu_cczeropi_utils::GetRecNuEnergy(vtx.LeptonMom, vtx.LeptonDir, vtx.NuDir, 0) ));
    output().FillVectorVarFromArray(truemu_infp_threemom, temp_infp_threemom ,3);

    Float_t mu_mom =  vtx.LeptonMom;
    Float_t mu_costheta = vtx.LeptonDir[2];
    Float_t mu_angle_degree = acos(mu_costheta)*180/3.14;

    bool temp_truemu_bin0 = mu_mom < 375 && mu_angle_degree < 60;
    bool temp_truemu_bin1 = mu_mom < 375 && mu_angle_degree > 60;
    bool temp_truemu_bin2 = mu_mom > 375 && mu_mom < 700 && mu_angle_degree < 30;
    bool temp_truemu_bin3 = mu_mom > 375 && mu_mom < 700 && mu_angle_degree > 30;
    bool temp_truemu_bin4 = mu_mom > 700 && mu_mom < 2000;
    bool temp_truemu_bin5 = mu_mom > 2000;

    output().FillVar(truemu_bin0, (Int_t)temp_truemu_bin0);
    output().FillVar(truemu_bin1, (Int_t)temp_truemu_bin1);
    output().FillVar(truemu_bin2, (Int_t)temp_truemu_bin2);
    output().FillVar(truemu_bin3, (Int_t)temp_truemu_bin3);
    output().FillVar(truemu_bin4, (Int_t)temp_truemu_bin4);
    output().FillVar(truemu_bin5, (Int_t)temp_truemu_bin5); 


    //Start of vars added by SDolan 02/09/15:
    numu_cczeropi_utils::transversityTrueT transTrueVarsT(vtx);

    output().FillVar(trueDphiT,transTrueVarsT.dphiT);
    output().FillVar(trueDpT,transTrueVarsT.dpT);
    output().FillVar(trueDalphaT,transTrueVarsT.dalphaT);
    output().FillVar(trueMrec,transTrueVarsT.tgtmrec);

    //July 2019 - code to get pn

    Float_t  NuMom = vtx.NuEnergy;
    const Float_t* NuDir = vtx.NuDir;
    Float_t  leptonMom = vtx.LeptonMom;
    const Float_t* leptonDir = vtx.LeptonDir;
    Float_t  protonMom = vtx.ProtonMom;
    const Float_t* protonDir = vtx.ProtonDir;

    TVector3 true_NuP(NuDir[0]*NuMom, NuDir[1]*NuMom, NuDir[2]*NuMom);
    TVector3 true_LeptonP(leptonDir[0]*leptonMom, leptonDir[1]*leptonMom, leptonDir[2]*leptonMom);
    TVector3 true_HadronP(protonDir[0]*protonMom, protonDir[1]*protonMom, protonDir[2]*protonMom);

    output().FillVar(truePn,(1.0/1000.0)*numu_cczeropi_utils::Get_pn_reco_C(true_NuP, true_LeptonP, true_HadronP));


    // Fill the numuCC variables
    //  _numuCCAnalysis->FillTruthTree(vtx);

    output().FillVar(true_ntracksSD, vtx.nTrueParticles);

    int nprotons=0, nchargedpions=0, nother=0, nfstracks=0;
    for(int i = 0; i<vtx.nTrueParticles; i++){
      if( vtx.TrueParticles[i]->ParentPDG == 0 ) nfstracks++;
      if( vtx.TrueParticles[i]->PDG == 2212 && vtx.TrueParticles[i]->ParentPDG == 0 ) nprotons++;
      else if( (vtx.TrueParticles[i]->PDG == 211 || vtx.TrueParticles[i]->PDG == -211 ) && vtx.TrueParticles[i]->ParentPDG == 0 ) nchargedpions++;
      else if( vtx.TrueParticles[i]->ParentPDG == 0 ){
        output().FillVar(true_notherpdgSD, vtx.TrueParticles[i]->PDG);
        nother++;
      }
    }

    output().FillVar(true_nfstracksSD, nfstracks);
    output().FillVar(true_nprotonsSD, nprotons);
    output().FillVar(true_nchargedpionsSD, nchargedpions);
    output().FillVar(true_notherSD, nother);    
    //End of vars added by SDolan 02/09/15


  }
  
  numu_cczeropi_categ_utils::FillTruthTreeCategories(&vtx, SubDetId::kFGD1);
  numu_cczeropi_categ_utils::FillTruthTreeCategories(&vtx, "fgd2", SubDetId::kFGD2);

  if (!_addTruthTreeCategories)
    return;

  //output().FillVar(fgdtargetCCZeroPi,      anaUtils::_categ->GetCode("fgdtargetCCZeroPi"));
  //output().FillVar(fgd2locationCCZeroPi,   anaUtils::_categ->GetCode("fgd2locationCCZeroPi"));

}


//********************************************************************
//void numuCCZeroPiAnalysis::FinalizeToy(){
//********************************************************************
/*
   _numuCCAnalysis->FinalizeToy();

/// Compute the weight for this selection by applying the systematic weights. 
if (&GetEvent()->Summary && &GetEvent()->SystematicsBox){      
// Override the MainTrack from baseAnalysis
&GetEvent()->SystematicsBox->MainTrack = numu_cczeropi_box().ProtonCandidate;
}
}

}*///TODO

//********************************************************************
void numuCCZeroPiAnalysis::FillCategories(){
  //********************************************************************

  // Fill the track categories for color drawing

  // For the muon candidate
  anaUtils::FillCategories(&GetEvent(), static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate),   "",      SubDetId::kFGD1);
  anaUtils::FillCategories(&GetEvent(), static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate),   "fgd2",  SubDetId::kFGD2);
 
  // These two may have ambiguties when running two selections at the same time
  // For the proton candidate
  if (_addPCandCateg){
    anaUtils::FillCategories(&GetEvent(), static_cast<AnaTrack*>(numu_cczeropi_box().ProtonCandidate), "PCan",     SubDetId::kFGD1);
    anaUtils::FillCategories(&GetEvent(), static_cast<AnaTrack*>(numu_cczeropi_box().ProtonCandidate), "fgd2PCan", SubDetId::kFGD2);
  }
  
  
  if (_addECalVetoCateg){
    if (numu_cczeropi_box().pionBox.nECalPhotons > 0){ 
      anaUtils::FillCategories(&GetEvent(), static_cast<AnaTrack*>(numu_cczeropi_box().pionBox.ECalPhotons[0]), "ecalveto");
    }
  
  }
  
  
  // Fill categories specific for the analysis
  numu_cczeropi_categ_utils::FillCategories(&GetEvent(), static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate),   "",      SubDetId::kFGD1);
  numu_cczeropi_categ_utils::FillCategories(&GetEvent(), static_cast<AnaTrack*>(numu_cczeropi_box().MuonCandidate),   "fgd2",  SubDetId::kFGD2);

}

//********************************************************************
void numuCCZeroPiAnalysis::ProcessMomRange(){
  //********************************************************************
  momrange_box().UpdateInputs(numu_cczeropi_box().MuonCandidate, numu_cczeropi_box().ProtonCandidate); 

  //calculate various momentum from range values
  if(_prangeEnabled){
    if (_prangeProton)
      momrange_box().compute_proton_momrange();
    if (_prangeMuon)
      momrange_box().compute_muon_momrange();
  }
  if(_prangeVertexEnabled){
    if(_prangeProton)
      momrange_box().compute_proton_momrange_vertex();
    if(_prangeMuon)
      momrange_box().compute_muon_momrange_vertex();
  }

}


//********************************************************************
bool numuCCZeroPiAnalysis::CheckBeforeVersion(const std::string& version, const std::string& version0){
  //*******************************************************************

  int v,r,p;
  int v0,r0,p0;
  ParseSoftwareVersion(version,  v, r, p);
  ParseSoftwareVersion(version0, v0,r0,p0);

  if (v<v0) return true;
  else if (v==v0){
    if (r<r0) return true;
    else if (r==r0){
      if (p<p0) return true;
    }
  }

  return false;
}


//********************************************************************
void numuCCZeroPiAnalysis::ParseSoftwareVersion(const std::string& version, int& v, int& r, int& p) {
  //********************************************************************

  // Backward compatibility to deal with both cmt and cmake versioning  
  
  int vloc = version.find("v");
  int rloc = version.find("r");
  int ploc = version.find("p");
  int size = version.length();

  if ((size_t)vloc == std::string::npos && version.length() > 1) {
    // Deal with cmake versions
    if (version.find_last_of(".") == std::string::npos){
      v = std::atoi(version.c_str());
      r = 0;
      p = 0;
      return;
    }
    // Now split 
    std::vector<std::string> vect_tmp;

    anaUtils::Tokenize(version, vect_tmp, ".");
    
    
    if (vect_tmp.size() == 1){
      v = std::atoi(vect_tmp[0].c_str());
      r = 0;
      p = 0;
      return;
    }
    
    if (vect_tmp.size() == 2){
      v = std::atoi(vect_tmp[0].c_str());
      r = std::atoi(vect_tmp[1].c_str());
      p = 0;
      return;
    }
    else if (vect_tmp.size() > 2){
      v = std::atoi(vect_tmp[0].c_str());
      r = std::atoi(vect_tmp[1].c_str());
      p = std::atoi(vect_tmp[2].c_str());
      return;
    }
    
    std::cerr << "*************************************************" << std::endl;
    std::cerr << "*************************************************" << std::endl;
    std::cerr << "WARNING: SoftwareVersion '" << version << "' is not a valid format." << std::endl;
    std::cerr << "*************************************************" << std::endl;
    std::cerr << "*************************************************" << std::endl;
    exit(3);
  }

  if ((size_t)rloc == std::string::npos) {
    // vX
    v = std::atoi(version.substr(vloc+1, size - vloc-1).c_str());
    r = 0;
    p = 0;
  } else if ((size_t)ploc == std::string::npos) {
    // vXrY
    v = std::atoi(version.substr(vloc+1, rloc - vloc-1).c_str());
    r = std::atoi(version.substr(rloc+1, size - rloc-1).c_str());
    p = 0;
  } else {
    // vXrYpZ
    v = std::atoi(version.substr(vloc+1, rloc - vloc-1).c_str());
    r = std::atoi(version.substr(rloc+1, ploc - rloc-1).c_str());
    p = std::atoi(version.substr(ploc+1, size - ploc-1).c_str());
  }

}

//********************************************************************
void numuCCZeroPiAnalysis::FillECalVetoInfo(){
  //********************************************************************

  if (!numu_cczeropi_box().pionBox.ECalPi0Photon) return;
  if (numu_cczeropi_box().pionBox.ECalPi0Photon->nECALSegments < 1 || !numu_cczeropi_box().pionBox.ECalPi0Photon->ECALSegments[0]) return;
  
  AnaECALParticleB* ecalSeg = numu_cczeropi_box().pionBox.ECalPi0Photon->ECALSegments[0];
 
  
  output().FillVar(                ecal_pi0_cand_energy,                  ecalSeg->EMEnergy);
  
  output().FillVectorVarFromArray( ecal_pi0_cand_pos,                     ecalSeg->PositionStart, 4);
  
  output().FillVar(                ecal_pi0_cand_most_upstream_layer_hit, ecalSeg->MostUpStreamLayerHit);
  
  output().FillVar(                ecal_pi0_cand_pidmipem,                ecalSeg->PIDMipEm);


}

//********************************************************************
Int_t numuCCZeroPiAnalysis::GetSampleFgdLayer(bool closest){
  //********************************************************************

  
  Int_t smpl_fgdlayer       = SampleId::kUnassigned;
  
  AnaEventSummaryB* summary = static_cast<AnaEventSummaryB*>(GetEvent().Summary);
  if (summary && summary->EventSample != SampleId::kUnassigned){


    // Samples start from 1
    int index = 0;
    int add_cnt = zero_pi::kEndOfSamples / 2;

    if (summary->EventSample > add_cnt)
      index = 1;

    // Get the FGD layer
    int layer = -999;
    
    Float_t dist; 
    
    Float_t layer_fgd = closest ?  anaUtils::GetClosestFgdDetLayer(numu_cczeropi_box().Vertex->Position, dist) : 
      anaUtils::GetFGDLayer(numu_cczeropi_box().Vertex->Position);
     
    if (anaUtils::IsFgdXLayer(layer_fgd))
      layer = 0;

    if (anaUtils::IsFgdYLayer(layer_fgd))
      layer = 1;
    
    if (layer > -1)  
      smpl_fgdlayer = summary->EventSample + (index + layer) * add_cnt;
  
  }
  
  return smpl_fgdlayer;
  
}


//********************************************************************
Int_t numuCCZeroPiAnalysis::GetSampleFgd2LayerXsec(bool closest){
  //********************************************************************

  // Fill samples
  Int_t smpl_fgd2layer_xsec = SampleId::kUnassigned;
  
  AnaEventSummaryB* summary = static_cast<AnaEventSummaryB*>(GetEvent().Summary);
  if (summary && summary->EventSample != SampleId::kUnassigned){


    // Samples start from 1
    int index = 0;
    int add_cnt = zero_pi::kEndOfSamples / 2;

    if (summary->EventSample > add_cnt)
      index = 1;

    // FGD2 var
    Float_t dist;
    
    Float_t FgdLayerFgd2XSec = closest ?  anaUtils::GetClosestFgd2DetLayerCC0PiXSec(numu_cczeropi_box().Vertex->Position, dist) : 
      anaUtils::GetFGD2LayerCC0PiXSec(numu_cczeropi_box().Vertex->Position);

    // Get the FGD layer
    int layer_fgd2 = -999;

    if (anaUtils::IsFgdXLayer(FgdLayerFgd2XSec))
      layer_fgd2 = 0;

    if (anaUtils::IsFgdYLayer(FgdLayerFgd2XSec))
      layer_fgd2 = 1; 

    if (index == 0){
      smpl_fgd2layer_xsec = summary->EventSample;  
    }  
    else if (layer_fgd2 > -1){
      smpl_fgd2layer_xsec = summary->EventSample + (layer_fgd2) * add_cnt;
    }
    
  }
  
 return  smpl_fgd2layer_xsec;

}

