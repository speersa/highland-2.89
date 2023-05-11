#ifndef CategoriesUtils_h
#define CategoriesUtils_h

#include "DataClasses.hxx"
#include "CategoryManager.hxx"

/// This namespace contains useful functions for analyses. Functions include
/// those related to fiducial volumes, accessing tracks with specific
/// characteristics, and more.
namespace anaUtils{

  /// Add the standard categories only, given a prefix for their name.
  void AddStandardCategories(const std::string& prefix = "");
  
  /// Add the standard categories only, given a prefix for their name.
  void AddStandardAntiNumuCategories(const std::string& prefix = "");
  
  /// Classify reaction topologies
  Int_t GetTopology(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  Int_t GetTopology_no1pi(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);

  /// get code for CC Bwd migrated
  Int_t GetCodeCCBwdMigrated(const AnaParticleB* track, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);

  /// Classify the topology type for nu-mu CC pi-zero analysis
  Int_t GetTopology_withpi0(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  Int_t GetTopologyCCPiZero(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);

  /// Classify reaction topologies in special attention to MEC process
  Int_t GetMECTopology(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1,bool IsAntinu = false);
  
  /// Classify reaction topologies adding CC-photon
  Int_t GetCCPhotonTopology(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det, bool IsAntinu=false);
  
  /// Fill the track categories for color drawing.
  void FillCategories(AnaEventB* event,       AnaTrack* track,        const std::string& prefix, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false, bool useCATSAND = true);
  void FillCategories(AnaEventB* event,       AnaTrack* track,                                   const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false, bool useCATSAND = true);
  void FillCategories(const AnaTrueVertexB* vertex, const std::string& prefix, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false, bool IsSand = false);
  void FillCategories(const AnaTrueVertexB* vertex,                            const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false, bool IsSand = false);
  void SetCategoriesDefaultCode(const std::string& prefix, const int code = CATNOTRUTH);
  
  /// Fill time slip specific categories
  void FillTimeSlipCategories(const AnaTrack& track, const std::string& prefix);

  /// Return the code for the "antinumuparent" category.
  /// Although this category is not one of the standard ones (it is added in
  /// antiNuMuCCAnalysis), the function is useful to have here as it is used in
  /// baseAnalysis::FillRedoSelectionVariables().
  Int_t GetAntiNuMuParent(AnaTrueVertex* trueVertex, AnaTrack* track);

  /// Classify reaction types
  Int_t GetReaction(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  Int_t GetReactionCC(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  Int_t GetReactionNoFgdFv(const AnaTrueVertex& trueVertex, bool IsAntinu = false);

  /// Classify reaction types,
  /// Returns the same codes as GetReaction(), except for no '8', which corresponds to sand muons
  Int_t GetReactionSand(const AnaEventB& event, const AnaTrack& track, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  Int_t GetReactionSand(const AnaEventB& event, const AnaTrueVertex& trueVertex,const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  Int_t GetReactionSandCC(const AnaEventB& event, const AnaTrack& track, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  Int_t GetReactionSandCC(const AnaEventB& event, const AnaTrueVertex& trueVertex,const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);

  /// Classify reaction types for antinu
  Int_t GetTopology_antinu(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetTopology_no1pi_antinu(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetTopology_withpi0_antinu(const AnaTrueVertex& trueVertex,const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetTopologyCCPiZero_antinu(const AnaTrueVertex& trueVertex,const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetMECTopology_antinu(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetReaction_antinu(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetReactionCC_antinu(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetReactionNoFgdFv_antinu(const AnaTrueVertex& trueVertex);
  Int_t GetReactionSand_antinu(const AnaEventB& event, const AnaTrack& track, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetReactionSand_antinu(const AnaEventB& event, const AnaTrueVertex& trueVertex,const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetReactionSandCC_antinu(const AnaEventB& event, const AnaTrack& track, const SubDetId::SubDetEnum det=SubDetId::kFGD1);
  Int_t GetReactionSandCC_antinu(const AnaEventB& event, const AnaTrueVertex& trueVertex,const SubDetId::SubDetEnum det=SubDetId::kFGD1);

  /// Get the code for filling the target PDG category.
  Int_t GetTargetCode(const AnaTrueVertex* trueVertex);

  enum TopoEnum {
    CC_0pi_0meson = 0,
    CC_1pi_0meson = 1, //used for both 1piplus and 1piminus
    CC_other = 2,
    BKG = 3, // NC + (anti)nu
    // used only up to here, by now
    CC_0pi_0meson_1p,
    CC_0pi_0meson_Np, // N = more than 1
    CC_0pi_0meson_0n,
    CC_0pi_0meson_1n,
    CC_0pi_0meson_Nn, // N = more than 1
    CC_1piplus_0meson,
    CC_1piminus_0meson,
    CC_1pi0_0meson,
    CC_Npi0_X,  // N = more than 1
    CC_photon
  };

}
#endif

//  LocalWords:  ifndef
