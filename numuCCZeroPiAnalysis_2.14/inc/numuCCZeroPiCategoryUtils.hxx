#ifndef numuCCZeroPiCategoryUtils_h
#define numuCCZeroPiCategoryUtils_h
#include "CategoriesUtils.hxx"
#include "DataClassesCCZeroPi.hxx"

/// various functions to add/fill categories specific for numuCC-zero pi selection work
namespace numu_cczeropi_categ_utils{
   
  /// simple struct to define FGD target material categories
  class FGDTargetCateg{
  public:
    static const int NFGDTARGETS = 8;
    
    static std::string fgdtarget_types[NFGDTARGETS];
                                            
    static int fgdtarget_codes[NFGDTARGETS];        
    static int fgdtarget_colors[NFGDTARGETS];       
    
    /// add categories for track category tools
    static void AddCategories(const std::string prefix = ""){
      anaUtils::_categ->AddCategory(prefix + "fgdtargetCCZeroPi", NFGDTARGETS, fgdtarget_types, fgdtarget_codes, fgdtarget_colors);
    }
     
    /// get code for FGD target category
    static int GetFGDTargetCCZeroPi(const AnaTrueVertex* trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1);

    /// get code for FGD target category
    static int GetFGDTargetCCZeroPi(const AnaTrack* track,           const SubDetId::SubDetEnum det=SubDetId::kFGD1);
 
  };
  
  /// simple struct to define FGD target material categories
  class FGD2LocationCateg{
  public:
    static const int NFGD2LOCATIONS = 6;
    
    static std::string fgd2location_types[NFGD2LOCATIONS];
                                            
    static int fgd2location_codes[NFGD2LOCATIONS];        
    static int fgd2location_colors[NFGD2LOCATIONS];       
    
    /// add categories for track category tools
    static void AddCategories(const std::string prefix = ""){
      anaUtils::_categ->AddCategory(prefix + "fgd2locationCCZeroPi", NFGD2LOCATIONS, fgd2location_types, fgd2location_codes, fgd2location_colors);
    }
     
    /// get code for FGD target category
    static int GetFGD2LocationCCZeroPi(const AnaTrueVertex* trueVertex);

    /// get code for FGD target category
    static int GetFGD2LocationCCZeroPi(const AnaTrack* track);
 
  };

  /// simple struct to define categories with only relevent infomation
  class ReducedCateg{
  public:

    // Define a new reaction category that only shows most relevent reactions
    static const int NREACTYPES = 4;
    static std::string reac_types[NREACTYPES];
    static int         reac_codes[NREACTYPES];
    static int         reac_colors[NREACTYPES];      
    
    /// add categories for track category tools
    static void AddCategories(const std::string prefix = ""){
      anaUtils::_categ->AddCategory(prefix + "reducedReaction", NREACTYPES, reac_types, reac_codes, reac_colors);
    }
    /// get code for category
    static int GetRedReac(const AnaTrueVertex* trueVertex);
    static int GetRedReac(const AnaTrack* track);
 
  };


  

  /// add the categories
  void AddCategories(const std::string prefix="");
   
  /// fill the categories
  void FillCategories(AnaEventB* event, const AnaTrack* track, const SubDetId::SubDetEnum det=SubDetId::kFGD1); 
  void FillCategories(AnaEventB* event, const AnaTrack* track, const std::string& prefix, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  
  void FillTruthTreeCategories(const AnaTrueVertex* vertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  void FillTruthTreeCategories(const AnaTrueVertex* vertex, const std::string& prefix, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  
}

#endif
