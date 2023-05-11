#include "numuCCZeroPiCategoryUtils.hxx"
#include "HighlandAnalysisUtils.hxx"
#include "CategoriesUtils.hxx"
#include "numuCCZeroPiDetectorDefinition.hxx"
#include "numuCCZeroPiUtils.hxx"

using namespace numu_cczeropi_categ_utils;

//reduced categories holding only relvent info (for pretty plots)

std::string ReducedCateg::reac_types[ReducedCateg::NREACTYPES]  = {"CCQE","2p2h","RES","Other"};
int ReducedCateg::reac_codes[ReducedCateg::NREACTYPES]          = { 0    , 1    , 2   , 3     };
int ReducedCateg::reac_colors[ReducedCateg::NREACTYPES]         = { 2    , 4    , 3   , 7     };

//********************************************************************
int  ReducedCateg::GetRedReac(const AnaTrueVertex* trueVertex){
  //********************************************************************
  if(!trueVertex) return 3;

  Int_t reac   = trueVertex->ReacCode;
  Int_t nutype = trueVertex->NuPDG;
  if (nutype!=14)                      return 3;
  if (abs(reac) == 1)                  return 0;
  if (abs(reac) == 2 )                 return 1;
  // in NuWro prod 5 2p2h code is 70 (Neut does not have 70 at all)
  if (abs(reac) == 70 )                return 1;
  if (abs(reac) >10 && abs(reac)<14)   return 2;

  return 3;
}

//********************************************************************
int  ReducedCateg::GetRedReac(const AnaTrack* track){
  //********************************************************************

  if (!track) return 3;

  if (!track->GetTrueParticle()) return 3;

  if (!track->GetTrueParticle()->TrueVertex) return 3;

  AnaTrueVertex* trueVertex = static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex);
  return ReducedCateg::GetRedReac(trueVertex); 
}

// CC-zero pi vertex target in FGD
std::string FGDTargetCateg::fgdtarget_types[FGDTargetCateg::NFGDTARGETS] = {  
  "#nu_{#mu} CC0#pi on Oxygen",
  "#nu_{#mu} CC-other on Oxygen",                             
  "Other on Oxygen",
  "#nu_{#mu} CC0#pi on Carbon",
  "#nu_{#mu} CC-other on Carbon",
  "Other on Carbon",
  "Other Material",
  "OOFV"};

int FGDTargetCateg::fgdtarget_codes[FGDTargetCateg::NFGDTARGETS]  = { 0, 1, 2, 3, 4, 5,   CATOTHER, CATOUTFV};
int FGDTargetCateg::fgdtarget_colors[FGDTargetCateg::NFGDTARGETS] = { 7, 4, 3, 2, 6, 31,  COLOTHER, COLOUTFV}; 


//********************************************************************
int  FGDTargetCateg::GetFGDTargetCCZeroPi(const AnaTrueVertex* trueVertex, SubDetId::SubDetEnum det){
  //********************************************************************

  /* Classify target types
     0 = CC0pi Oxygen
     1 = CC-other Oxygen
     2 = Other reaction Oxygen (NC, nue, anti-numu)
     3 = CC0Pi Carbon
     4 = CC-other Carbon
     5 = Other reaction Carbon
     CATOTHER = Other Material (G10, glue, iron, etc.)
     CATOUTFV = Out FV
     CATNOTRUTH = No truth
     */

  if(!trueVertex)
    return CATNOTRUTH;

  // get GetTopology for numu
  Int_t topo = anaUtils::GetTopology(*trueVertex, det);

  if (topo == CATOUTFV)
    return topo;

  // Nuclear codes are given as 10-digit numbers +-100ZZZAAAI.
  //For a nucleus consisting of np protons and nn neutrons
  // A = np + nn and Z = np.
  // I gives the isomer level, with I = 0 corresponding
  // to the ground state and I >0 to excitations
  //
  //!!! I = 1 is assigned for all excitation states in Geant4

  int targetcode = anaUtils::GetTargetCode(trueVertex);

  int categ = CATOTHER;

  switch (targetcode){
    //Oxygen
    case 8:
      categ = 2;
      if (topo==0){
        categ = 0;
      }
      else if (topo==1 || topo==2){
        categ = 1;
      }
      return categ;
      break;

      //Carbon
    case 6:
      categ = 5;
      if (topo==0){
        categ = 3;
      }
      else if (topo==1 || topo==2){
        categ = 4;
      }
      return categ;
      break;

    default:
      break;
  }

  return CATOTHER; //Other material

}
//********************************************************************
int  FGDTargetCateg::GetFGDTargetCCZeroPi(const AnaTrack* track, SubDetId::SubDetEnum det){
  //********************************************************************
  if (!track)
    return CATNOTRUTH;

  if (!track->GetTrueParticle())
    return CATNOTRUTH;

  if (!track->GetTrueParticle()->TrueVertex)
    return CATNOTRUTH;

  AnaTrueVertex* trueVertex = static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex);
  return GetFGDTargetCCZeroPi(trueVertex, det); 

}

// CC-zero pi FGD2 vertex location: to differentiate between vertical/horizontal layers,  water modules, gaps etc
std::string  FGD2LocationCateg::fgd2location_types[FGD2LocationCateg::NFGD2LOCATIONS]  = {
  "vertical (XZ) layer", 
  "horizontal (YZ) layer", 
  "water module", "gap",
  "non #nu_{#mu} CC0#pi", 
  "OOFV"};

int  FGD2LocationCateg::fgd2location_codes[   FGD2LocationCateg::NFGD2LOCATIONS]  = {0, 1, 2, 3, CATOTHER, CATOUTFV};
int  FGD2LocationCateg::fgd2location_colors[  FGD2LocationCateg::NFGD2LOCATIONS]  = {2, 3, 4, 7, COLOTHER, COLOUTFV};


//********************************************************************
int  FGD2LocationCateg::GetFGD2LocationCCZeroPi(const AnaTrueVertex* trueVertex){
  //********************************************************************
  if(!trueVertex)
    return CATNOTRUTH;

  // get GetTopology for numu
  Int_t topo = anaUtils::GetTopology(*trueVertex, SubDetId::kFGD2);

  if (topo == CATOUTFV)
    return topo;

  if (topo>2)
    return CATOTHER;

  // Create a fake MC event
  return anaUtils::GetFgdModuleTypeNoFV(true, trueVertex->Position);

}

//********************************************************************
int  FGD2LocationCateg::GetFGD2LocationCCZeroPi(const AnaTrack* track){
  //********************************************************************

  if (!track)
    return CATNOTRUTH;

  if (!track->GetTrueParticle())
    return CATNOTRUTH;

  if (!track->GetTrueParticle()->TrueVertex)
    return CATNOTRUTH;

  AnaTrueVertex* trueVertex = static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex);
  return GetFGD2LocationCCZeroPi(trueVertex); 
}

//********************************************************************
void numu_cczeropi_categ_utils::AddCategories(const std::string prefix){
  //********************************************************************

  // FGD target
  FGDTargetCateg::AddCategories(prefix);

  // CC-zero pi FGD2 vertex location: to differentiate between vertical/horizontal layers,  water modules, gaps etc
  FGD2LocationCateg::AddCategories(prefix);

  // Cat with reduced info for nice plots
  ReducedCateg::AddCategories(prefix);

}


//********************************************************************
void numu_cczeropi_categ_utils::FillCategories(AnaEventB* event, const AnaTrack* track, const std::string& prefix,
    const SubDetId::SubDetEnum det){
  //********************************************************************
  (void)event;
  anaUtils::_categ->SetCode(prefix + "fgdtargetCCZeroPi",     FGDTargetCateg::GetFGDTargetCCZeroPi(       track, det)); 
  anaUtils::_categ->SetCode(prefix + "fgd2locationCCZeroPi",  FGD2LocationCateg::GetFGD2LocationCCZeroPi( track)); 
  anaUtils::_categ->SetCode(prefix + "reducedReaction",       ReducedCateg::GetRedReac( track)); 

}

//********************************************************************
void numu_cczeropi_categ_utils::FillCategories(AnaEventB* event, const AnaTrack* track, const SubDetId::SubDetEnum det){
  //********************************************************************
  return  numu_cczeropi_categ_utils::FillCategories(event, track, "", det); 
}


//********************************************************************
void numu_cczeropi_categ_utils::FillTruthTreeCategories(const AnaTrueVertex* vertex,  const std::string& prefix, const SubDetId::SubDetEnum det){
  //********************************************************************

  anaUtils::_categ->SetCode(prefix + "fgdtargetCCZeroPi",     FGDTargetCateg::GetFGDTargetCCZeroPi(       vertex, det));  
  anaUtils::_categ->SetCode(prefix + "fgd2locationCCZeroPi",  FGD2LocationCateg::GetFGD2LocationCCZeroPi( vertex)); 
  anaUtils::_categ->SetCode(prefix + "reducedReaction",       ReducedCateg::GetRedReac( vertex)); 

}

//********************************************************************
void numu_cczeropi_categ_utils::FillTruthTreeCategories(const AnaTrueVertex* vertex, const SubDetId::SubDetEnum det){
  //********************************************************************
  return  numu_cczeropi_categ_utils::FillTruthTreeCategories(vertex, "", det); 
}
