#include "CategUtilsFgdTimeBins.hxx"
#include "ND280AnalysisUtils.hxx"


void fgd_tbins_categs::AddCategories(const std::string& prefix){
  
  
  std::string part_types[] = {"e^{#pm}",  "#pi^{#pm}",    "n",  "p" ,  NAMEOTHER};
  int pdg[]                = {11       ,  211        ,   2112,  2212,  CATOTHER};
  int part_colors[]        = {3        ,  4          ,     95,  7   ,  COLOTHER};
  const int NPART = sizeof(part_types)/sizeof(part_types[0]); 
  
  std::string part_types_oofv[] = {"e^{#pm}",  "#pi^{#pm}",    "n",  "p" ,  NAMEOTHER, NAMEOUTFV};
  int pdg_oofv[]                = {11       ,  211        ,   2112,  2212,  CATOTHER, CATOUTFV};
  int part_colors_oofv[]        = {3        ,  4          ,     95,  7   ,  COLOTHER, COLOUTFV};
  const int NPART_oofv = sizeof(part_types_oofv)/sizeof(part_types_oofv[0]); 
  
  std::string parent_types[] = {"#mu^{#pm}", "e^{#pm}", "#pi^{#pm}", "p"  ,  "nu", "gamma", "#pi^{0}", "n" , NAMEOTHER};
  int parent_pdg[]           = {13         , 11       , 211        ,  2212,  0   , 22     , 111      , 2112, CATOTHER};
  int parent_colors[]        = {2          , 3        , 4          ,  7    , 8   , 31     , 40       , 95  , COLOTHER};
  const int NPARENT = sizeof(parent_types)/sizeof(parent_types[0]);
  
  
  std::string parent_types_oofv[] = {"#mu^{#pm}", "e^{#pm}", "#pi^{#pm}", "p"  ,  "nu", "gamma", "#pi^{0}", "n" , NAMEOTHER, NAMEOUTFV};
  int parent_pdg_oofv[]           = {13         , 11       , 211        ,  2212,  0   , 22     , 111      , 2112, CATOTHER, CATOUTFV};
  int parent_colors_oofv[]        = {2          , 3        , 4          ,  7    , 8   , 31     , 40       , 95  , COLOTHER, COLOUTFV};
  const int NPARENT_oofv = sizeof(parent_types_oofv)/sizeof(parent_types_oofv[0]);
  
  
  std::string detector_types[] = {"TPC1", "TPC2", "TPC3", "FGD1", "FGD2", "DsECAL", "BrECAL", "P0DECAL", "P0D", "SMRD", NAMEOTHER};
  int detector_codes[] = {6, //SubDetId::kTPC1,
                        7, //SubDetId::kTPC2,
                        8, //SubDetId::kTPC3,
                        0, //SubDetId::kFGD1,
                        1, //SubDetId::kFGD2,
                        3, //SubDetId::kDSECAL,
                        4, //SubDetId::kTECAL,
                        5, //SubDetId::kPECAL,
                        2, //SubDetId::kP0D,
                        9, //SubDetId::kSMRD,
                        CATOTHER
                        };
  int detector_colors[] = {2, 3, 4, 7, 6, 31, 51, 1, 65, 9, COLOTHER};
  const int NDETECTOR = sizeof(detector_types)/sizeof(detector_types[0]);
  
  
 
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_particle",          NPART,               part_types,              pdg,                     part_colors);
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_parent",            NPARENT,             parent_types,            parent_pdg,              parent_colors);
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_gparent",           NPARENT,             parent_types,            parent_pdg,              parent_colors);
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_primary",           NPARENT,             parent_types,            parent_pdg,              parent_colors);
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_particle_detector", NDETECTOR,           detector_types,          detector_codes,          detector_colors);
 
 // With OOFGD
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_particle_oofv", NPART_oofv,      part_types_oofv,   pdg_oofv,            part_colors_oofv);
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_parent_oofv",   NPARENT_oofv,    parent_types_oofv, parent_pdg_oofv,     parent_colors_oofv);
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_gparent_oofv",  NPARENT_oofv,    parent_types_oofv, parent_pdg_oofv,     parent_colors_oofv);
 anaUtils:: _categ->AddCategory(prefix+"fgd_tbin_primary_oofv",  NPARENT_oofv,    parent_types_oofv, parent_pdg_oofv,     parent_colors_oofv);
 
}


void fgd_tbins_categs::FillCategories(AnaEventB* event,       AnaTrack* track,  
    AnaFgdTimeBin* bin, const std::string& prefix, const SubDetId::SubDetEnum det, bool useCATSAND){

 
  (void)track;
  
  (void)det;
  
  if (!bin){
    return;
  }
  
  AnaTrueParticleB* true_fgd_tbin = anaUtils::GetTrueParticleByID(*event, bin->G4ID);
 
  // Categories are previously initialized with -999 in CategoryManager::ResetCurrentCategories()

  // Check if this is sandMC (by run number) even if there is no truth association (see bug 1237)
  if (useCATSAND && event->GetIsSandMC()) {
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle", CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_parent"  , CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_gparent" , CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_primary" , CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_detector", CATSAND);
    
    
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_oofv", CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_parent_oofv"  , CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_gparent_oofv" , CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_primary_oofv" , CATSAND);
    anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_detector_oofv", CATSAND);

    // Save the PDG of the track and its ancestor
    
    /*
    if (true_fgd_tbin){
      if (true_fgd_tbin->PDG != 0){
        AnaTrueParticle* trueTrack = static_cast<AnaTrueParticle*>(true_fgd_tbin);
               
        anaUtils::_categ->SetCode(prefix + "particle",  abs(trueTrack->PDG),        CATSAND);
        anaUtils::_categ->SetCode(prefix + "parent",    abs(trueTrack->ParentPDG) , CATSAND);
        anaUtils::_categ->SetCode(prefix + "gparent",   abs(trueTrack->GParentPDG), CATSAND);
        anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_detector",  anaUtils::GetDetector(trueTrack->Position),        CATSAND);
        
        anaUtils::_categ->SetCode(prefix + "particle_oofv",  abs(trueTrack->PDG),        CATSAND);
        anaUtils::_categ->SetCode(prefix + "parent_oofv",    abs(trueTrack->ParentPDG) , CATSAND);
        anaUtils::_categ->SetCode(prefix + "gparent_oofv",   abs(trueTrack->GParentPDG), CATSAND);
      }
    }
    */

    return;
  }

  // First fill with "no truth" value
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle",           CATNOTRUTH);
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_parent"  ,           CATNOTRUTH);
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_gparent" ,           CATNOTRUTH);
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_primary" ,           CATNOTRUTH);
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_detector",  CATNOTRUTH);

  anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_oofv",           CATNOTRUTH);
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_parent_oofv"  ,           CATNOTRUTH);
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_gparent_oofv" ,           CATNOTRUTH);
  anaUtils::_categ->SetCode(prefix + "fgd_tbin_primary_oofv" ,           CATNOTRUTH);
  
  // ----- Particle ------------------------------
  if (true_fgd_tbin) {

    if (true_fgd_tbin->PDG != 0) {
      AnaTrueParticle* trueTrack = static_cast<AnaTrueParticle*>(true_fgd_tbin);
      AnaTrueParticleB* primary = anaUtils::GetTrueParticleByID(*event, trueTrack->PrimaryID);

      anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_detector",  anaUtils::GetDetector(trueTrack->Position),        CATOTHER);
      anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle",  abs(trueTrack->PDG),        CATOTHER);
      anaUtils::_categ->SetCode(prefix + "fgd_tbin_parent",    abs(trueTrack->ParentPDG) , CATOTHER);
      anaUtils::_categ->SetCode(prefix + "fgd_tbin_gparent",   abs(trueTrack->GParentPDG), CATOTHER);
      
      anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_oofv",  abs(trueTrack->PDG),        CATOTHER);
      anaUtils::_categ->SetCode(prefix + "fgd_tbin_parent_oofv",    abs(trueTrack->ParentPDG) , CATOTHER);
      anaUtils::_categ->SetCode(prefix + "fgd_tbin_gparent_oofv",   abs(trueTrack->GParentPDG), CATOTHER);
      
      if (primary) {
        anaUtils::_categ->SetCode(prefix + "fgd_tbin_primary",      abs(primary->PDG),          CATOTHER);
        anaUtils::_categ->SetCode(prefix + "fgd_tbin_primary_oofv", abs(primary->PDG),          CATOTHER);
        // If we indentified a true primary vertex then check OOFV
        if (primary->TrueVertex && !anaUtils::InFiducialVolume(det, primary->TrueVertex->Position)){
          anaUtils::_categ->SetCode(prefix + "fgd_tbin_particle_oofv",           CATOUTFV);
          anaUtils::_categ->SetCode(prefix + "fgd_tbin_parent_oofv"  ,           CATOUTFV);
          anaUtils::_categ->SetCode(prefix + "fgd_tbin_gparent_oofv" ,           CATOUTFV);
          anaUtils::_categ->SetCode(prefix + "fgd_tbin_primary_oofv" ,           CATOUTFV);
        }
      }

    }
  } 

}
