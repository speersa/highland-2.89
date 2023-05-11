#ifndef CategToolsNueCC_hxx
#define CategToolsNueCC_hxx

#include "BasicUtils.hxx"
#include "CategoriesUtils.hxx"

namespace nue_categs {

  /// Return the code of the "nufamilynue" category this track (and it's vertex) belong in.
  Int_t GetNuFamilyNuE(AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu);

  /// Return the code of the "nuesimple" category.
  Int_t GetNuESimpleCat(AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu, bool ccincl=false);

  /// Return the code of the "nuesimpleparent" category.
  Int_t GetNuESimpleParent(AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu);

  /// Return the code of the "nuesimplereac" category.
  Int_t GetNuESimpleReac(AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu);
  // For truth tree
  Int_t GetNuEReaction(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det, bool AntiNu);

  /// Return the code of the "nuesimpletopology" category.
  Int_t GetNuESimpleTopology(AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu, bool ccincl=false);

  /// Return the code of the "nuereactionnofv" category.  
  Int_t GetNuEReactionNoFgdFV(AnaTrackB* track, bool AntiNu);
  // For truth tree
  Int_t GetNuEReactionNoFgdFV(const AnaTrueVertex& trueVertex, bool AntiNu);

  /// Return the code of the "nuemectopology" category.  
  Int_t GetNuEMec(AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu);
  
  /// Return the code of the "nuereaction" category.  
  Int_t GetNuEReaction(AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu);
  	
  /// Add the custom categories for color drawing.
  void AddCategories(const std::string& prefix, bool AntiNu);

  /// Fill the track categories for color drawing.
  void FillCategories(AnaEventB* event, AnaTrackB* track, const std::string& prefix, const SubDetId::SubDetEnum det, bool AntiNu);
  /// Fill the vertex categories for the truth tree
  void FillTruthCategories(const AnaTrueVertex& trueVertex, const std::string& prefix, const SubDetId::SubDetEnum det, bool AntiNu);

  /// Whether this vertex results in a gamma conversion.
  bool IsRelaxedGammaSignal(AnaTrackB* track, const SubDetId::SubDetEnum det);

  /// Whether this gamma is coming from a neutrino interaction in FGD.
  bool IsRelaxedGammaSignalOOFGD(AnaTrackB* track, const SubDetId::SubDetEnum det);

  /// Whether this vertex results in a gamma conversion.
  bool IsGammaSignal(AnaTrackB* track, const SubDetId::SubDetEnum det);

  /// Whether this gamma is coming from a neutrino interaction in FGD.
  bool IsGammaSignalOOFGD(AnaTrackB* track, const SubDetId::SubDetEnum det);

  /// Whether this vertex matches the signal definition (a NuE interaction).
  bool IsNuESignal(const AnaTrueVertexB& vtx, const SubDetId::SubDetEnum det, bool AntiNu);
  
  /// nueCC inFGD but out of FV
  bool IsNuECCinFGDOOFV(const AnaTrueVertexB& vtx, const SubDetId::SubDetEnum det, bool AntiNu);
  
  /// Whether this vertex is true CCQE.
  bool IsNuECCQE(const AnaTrueVertexB& vtx, const SubDetId::SubDetEnum det, bool AntiNu);

  /// Whether this vertex is true CCnonQE.
  bool IsNuECCnonQE(const AnaTrueVertexB& vtx, const SubDetId::SubDetEnum det, bool AntiNu);

  /// Whether this vertex is true CC0pi.
  bool IsNuECC0pi(const AnaTrueVertexB& vtx, const SubDetId::SubDetEnum det, bool AntiNu);
  
  /// Whether this vertex is true CC0pi.
  bool IsNuECCother(const AnaTrueVertexB& vtx, const SubDetId::SubDetEnum det, bool AntiNu);

  /// Whether the selected electron is coming from vertex
  bool IsElectronFromVertex(AnaTrueParticleB* truetrack);

  /// The number of true charge pions
  Int_t NpiC(const AnaTrueVertexB& vtx);

  /// The number of true pi0s
  Int_t Npi0(const AnaTrueVertexB& vtx);
  
  /// The number of true protons
  Int_t Nproton(const AnaTrueVertexB& vtx);

  /// The number of true neutrons
  Int_t Nneutron(const AnaTrueVertexB& vtx);
  
  /// The number of true kaons, rhos and etas
  Int_t NKaonRhoEta(const AnaTrueVertexB& vtx);

  /// Get the code for the frompi0 category.
  Int_t GetPi0Code(AnaEventB* event, AnaTrackB* track);

  // Get the code for the gammapi0infv category
  Int_t GetRelaxedGammaPi0inFV(AnaEventB* event, AnaTrackB* track, const SubDetId::SubDetEnum det,  bool seperateSand, bool AntiNu);

  // Get the code for the gammapi0infvoofv category
  Int_t GetRelaxedGammaPi0FV(AnaEventB* event, AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu);

  // Get the code for the gammapi0infgdoofgd category
  Int_t GetRelaxedGammaPi0FGD(AnaEventB* event, AnaTrackB* track, const SubDetId::SubDetEnum det, bool AntiNu );


  bool HasParentOfType(AnaEventB* event, AnaTrueParticleB* track, int pdg);

  /// Gamma sideband categories
  bool ThereWasGammaInFGD(const AnaTrueVertexB& vtx, const SubDetId::SubDetEnum det, bool SaveAllTruthGammaInFGD);
  bool IsNCGammaSignal(const AnaTrueVertexB& vtx, SubDetId::SubDetEnum FGD);
  
  Int_t GetPiTopo(AnaTrackB* track);
  Int_t GetReactionNoFVGamma(AnaTrackB* track);
  // For truth tree
  Int_t GetReactionNoFVGamma(const AnaTrueVertex& trueVertex); 

  /// Special categories for nu-elec elastic
  Int_t GetNuElecElasticCat(AnaTrackB* track, const SubDetId::SubDetEnum det);
  Int_t GetNuElecElasticTopo(AnaTrackB*track, const SubDetId::SubDetEnum det);

}

#endif
