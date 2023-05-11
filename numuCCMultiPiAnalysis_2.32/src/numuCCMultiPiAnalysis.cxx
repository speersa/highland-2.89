#include "numuCCMultiPiAnalysis.hxx"
#include "Parameters.hxx"
#include "numuCCMultiPiFGD2Selection.hxx"
#include "oaAnalysisTreeConverter.hxx"
#include "CategoriesUtils.hxx"
#include "BasicUtils.hxx"

//const bool DEBUG = false;    // debugging flag for FillTruthTree (increases verbosity)

const unsigned int NMAXTPCSEC = 20;
const unsigned int NMAXFGDSEC = 20;
const unsigned int NMAXTPC1 = 20;

//********************************************************************
numuCCMultiPiAnalysis::numuCCMultiPiAnalysis(AnalysisAlgorithm* ana) : baseTrackerAnalysis(ana){
  //********************************************************************

  // Add the package version
  ND::versioning().AddPackage("numuCCMultiPiAnalysis", anaUtils::GetSoftwareVersionFromPath((std::string)getenv("NUMUCCMULTIPIANALYSISROOT")));

  // Create a numuCCAnalysis passing this analysis to the constructor. In that way the same managers are used
  _numuCCAnalysis = new numuCCAnalysis(this);

  // Use the numuCCAnalysis (in practice that means that the same box and event will be used for the numuCCAnalysis as for this analysis)
  UseAnalysis(_numuCCAnalysis);

  _pionSIManager = NULL;
}

//********************************************************************
bool numuCCMultiPiAnalysis::Initialize(){
  //********************************************************************

  // Initialize the numuCCAnalysis
  if (!_numuCCAnalysis->Initialize()) return false;

  // Minimum accum level to save event into the output tree
  SetMinAccumCutLevelToSave(ND::params().GetParameterI("numuCCMultiPiAnalysis.MinAccumLevelToSave"));

  // which analysis: FGD1, FGD2 or FGDs
  _whichFGD = ND::params().GetParameterI("numuCCMultiPiAnalysis.Selections.whichFGD");
  if (_whichFGD == 3) {
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "WARNING: only for events with accum_level > 5 the vars in the output microtree will surely refer to the muon candidate in that FGD" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
  }

  // Select the FGD
  if (_whichFGD == 1) _fgdID = SubDetId::kFGD1;
  if (_whichFGD == 2) _fgdID = SubDetId::kFGD2;
  if (_whichFGD >  2) _fgdID = SubDetId::kFGD;

  // Add Pion SI info to the micro-trees
  _addPionSIinfo = (bool)ND::params().GetParameterI("numuCCMultiPiAnalysis.MicroTrees.AddPionSIinfo");

  SetStoreAllTruePrimaryPions((bool)ND::params().GetParameterI("numuCCMultiPiAnalysis.MicroTrees.StoreAllTruePrimaryPions"));


  _storeRecoPionProtVtx = (bool)ND::params().GetParameterI("numuCCMultiPiAnalysis.MicroTrees.StoreRecoPionProtVtxConst");

  _doMultiPi = (bool)ND::params().GetParameterI("numuCCMultiPiAnalysis.MicroTrees.doMultiPi");

  _doMultiPiPhoton = (bool)ND::params().GetParameterI("numuCCMultiPiAnalysis.MicroTrees.doMultiPiPhoton");

  _doMultiPiProton = (bool)ND::params().GetParameterI("numuCCMultiPiAnalysis.MicroTrees.doMultiPiProton");

  _doMultiPiPhotonProton = (bool)ND::params().GetParameterI("numuCCMultiPiAnalysis.MicroTrees.doMultiPiPhotonProton");

  //TODO give some error if (_doMultiPi + _doMultiPiPhoton + _doMultiPiProton) != 1


  if (_addPionSIinfo){
    InitializeAddPionSIinfo();
  }



  return true;
}

//********************************************************************
void numuCCMultiPiAnalysis::InitializeAddPionSIinfo(){
  //********************************************************************
  
  if (!_addPionSIinfo){
    return;
  }

  
  
  _pionSIManager = new PionSIManager();

  char inputFileName[256];
  
  char inputFileName_ext[256];

  char inputFileNameMC[256];

  _pionObject     = new AnaTrack();
  _pionTrueObject = new AnaTrueParticle();

  _pionObject->TrueObject = _pionTrueObject;
  
  
  sprintf(inputFileNameMC,    "%s/data/PionSI/SIPionXsecMCto8GeVFixG10.dat", getenv("PSYCHEND280UTILSROOT"));
  sprintf(inputFileName,      "%s/data/PionSI/SIPionXsecFixG10.dat",         getenv("PSYCHESYSTEMATICSROOT"));
  sprintf(inputFileName_ext,  "%s/data/PionSI/SIPionXsecto8GeVFixG10.dat",   getenv("PSYCHEND280UTILSROOT"));

  if ((bool)ND::params().GetParameterI("psycheND280Utils.PionSI.UseNEUTCascade")){
    sprintf(inputFileNameMC,    "%s/data/PionSI/SIPionXsecMCto8GeV_NEUTCascade.dat", getenv("PSYCHEND280UTILSROOT"));
    sprintf(inputFileName,      "%s/data/PionSI/SIPionXsec_NEUTCascade.dat",         getenv("PSYCHESYSTEMATICSROOT"));
    sprintf(inputFileName_ext,  "%s/data/PionSI/SIPionXsecto8GeV_NEUTCascade.dat",   getenv("PSYCHEND280UTILSROOT"));
  }
      
  if ((bool)ND::params().GetParameterI("psycheND280Utils.PionSI.UseNEUTCascadeProd6TFix")){
    sprintf(inputFileNameMC,    "%s/data/PionSI/SIPionXsecMCto8GeV_NEUTCascade_p6Tfix.dat", getenv("PSYCHEND280UTILSROOT"));
    sprintf(inputFileName,      "%s/data/PionSI/SIPionXsec_NEUTCascade.dat",                getenv("PSYCHESYSTEMATICSROOT"));
    sprintf(inputFileName_ext,  "%s/data/PionSI/SIPionXsecto8GeV_NEUTCascade.dat",          getenv("PSYCHEND280UTILSROOT"));
  }
      
  anaUtils::LoadPionCrossSections(inputFileName,     _xsec_data,     _err_data);
  
  anaUtils::LoadPionCrossSections(inputFileName_ext, _xsec_data_ext, _err_data_ext);
  
  anaUtils::LoadPionCrossSections(inputFileNameMC,   _xsec_mc,       _err_mc);

  anaUtils::AddStandardCategories("pion");
  
  return;



}

//********************************************************************
void numuCCMultiPiAnalysis::DefineSelections(){
  //********************************************************************

  // Add the selection to the Selection Manager
  if(_whichFGD == 1){ // FGD1
    if (_doMultiPi){
      sel().AddSelection("kTrackerNumuCCMultiPi", "numuCC multi-pionselection", new numuCCMultiPiSelection());
    }
    else if(_doMultiPiPhoton){
      sel().AddSelection("kTrackerNumuCCMultiPiPhoton", "numuCC multi-pionselection-photon",  new numuCCMultiPiPhotonSelection());
    }
    else if(_doMultiPiProton){
      sel().AddSelection("kTrackerNumuCCMultiPiProton", "numuCC multi-pionselection-proton",  new numuCCMultiPiProtonSelection());
    }
    else if(_doMultiPiPhotonProton){
      sel().AddSelection("kTrackerNumuCCMultiPiPhotonProton", "numuCC multi-pionselection-photon-proton",  new numuCCMultiPiPhotonProtonSelection());
    }

  }
  else if (_whichFGD==2){ // FGD2 
    if (_doMultiPi){
      sel().AddSelection("kTrackerNumuCCMultiPiFGD2","numuCCFGD2 multi-pionselection", new numuCCMultiPiFGD2Selection());
    }
    else if(_doMultiPiPhoton){
      sel().AddSelection("kTrackerNumuCCMultiPiPhotonFGD2", "numuCCFGD2 multi-pionselection-photon",  new numuCCMultiPiPhotonFGD2Selection());
    }
    else if(_doMultiPiProton){
      sel().AddSelection("kTrackerNumuCCMultiPiProtonFGD2", "numuCCFGD2 multi-pionselection-proton",  new numuCCMultiPiProtonFGD2Selection());
    }
    else if(_doMultiPiPhotonProton){
      sel().AddSelection("kTrackerNumuCCMultiPiPhotonProtonFGD2", "numuCCFGD2 multi-pionselection-photon-proton",  new numuCCMultiPiPhotonProtonFGD2Selection());
    }

  }
  else if (_whichFGD==3){ // both FGDs, in 2 selections
    if (_doMultiPi){
      sel().AddSelection("kTrackerNumuCCMultiPi",     "numuCC multi-pionselection",     new numuCCMultiPiSelection());
      sel().AddSelection("kTrackerNumuCCMultiPiFGD2", "numuCCFGD2 multi-pionselection", new numuCCMultiPiFGD2Selection());
    }
    else if(_doMultiPiPhoton){
      sel().AddSelection("kTrackerNumuCCMultiPiPhoton",     "numuCC multi-pionselection-photon",     new numuCCMultiPiPhotonSelection());
      sel().AddSelection("kTrackerNumuCCMultiPiPhotonFGD2", "numuCCFGD2 multi-pionselection-photon", new numuCCMultiPiPhotonFGD2Selection());
    }
    else if(_doMultiPiProton){
      sel().AddSelection("kTrackerNumuCCMultiPiProton",     "numuCC multi-pionselection-proton",     new numuCCMultiPiProtonSelection());
      sel().AddSelection("kTrackerNumuCCMultiPiProtonFGD2", "numuCCFGD2 multi-pionselection-proton", new numuCCMultiPiProtonFGD2Selection());
    }
    else if(_doMultiPiPhotonProton){
      sel().AddSelection("kTrackerNumuCCMultiPiPhotonProton",     "numuCC multi-pionselection-photon-proton",     new numuCCMultiPiPhotonProtonSelection());
      sel().AddSelection("kTrackerNumuCCMultiPiPhotonProtonFGD2", "numuCCFGD2 multi-pionselection-photon-proton", new numuCCMultiPiPhotonProtonFGD2Selection());
    }

  }
}

//********************************************************************
void numuCCMultiPiAnalysis::DefineMicroTrees(bool addBase){
  //********************************************************************

  // -------- Add variables to the analysis tree ----------------------

  // Variables from the numuCCAnalysis analysis (including the ones in baseTrackerAnalysis by default, otherwise addBase should be false)
  if (addBase) _numuCCAnalysis->DefineMicroTrees(addBase);

  // --- Add here more variables for the CCMultiPi analysis -----

  AddVarI(output(),MuonVertexId, "");
  AddVarI(output(),MuonIndex,"");

  // --- Pion candidates 
  AddToyVarVF(output(),NegPionMom,"",       NNegPion);
  AddToyVarVF(output(),NegPionTheta,"",     NNegPion);

  AddVarVF(output(),NegPionPidLik,"",       NNegPion);
  AddVarVF(output(),NegPionMipPidLik,"",     NNegPion);
  AddVarVI(output(),NegPionTId,"",          NNegPion);
  AddVarVI(output(),NegPionIndex,"",        NNegPion);
  AddVarVI(output(),NegPionParentTId,"",    NNegPion);
  AddVarVI(output(),NegPionGParentTId,"",   NNegPion);
  AddVarVF(output(),NegPionTrueMom,"",      NNegPion);
  AddVarMF(output(),NegPionTrueStartDir,"", NNegPion,-NMAXTPCSEC,3);
  AddVarVI(output(),NegPionVId,"",          NNegPion);
  AddVarMF(output(),NegPionDir,"",          NNegPion,-NMAXTPCSEC,3);
  AddVarMF(output(),NegPionPosStart,"",     NNegPion,-NMAXTPCSEC,3);
  AddVarMF(output(),NegPionPosEnd,"",       NNegPion,-NMAXTPCSEC,3);

  AddToyVarVF(output(),PosPionMom,"",       NPosPion);
  AddToyVarVF(output(),PosPionTheta,"",     NPosPion);

  AddVarVF(output(),PosPionPidLik,"",       NPosPion);
  AddVarVF(output(),PosPionMipPidLik,"",     NPosPion);
  AddVarVI(output(),PosPionTId,"",          NPosPion);
  AddVarVI(output(),PosPionIndex,"",        NPosPion);
  AddVarVI(output(),PosPionParentTId,"",    NPosPion);
  AddVarVI(output(),PosPionGParentTId,"",   NPosPion);
  AddVarVF(output(),PosPionTrueMom,"",      NPosPion);
  AddVarMF(output(),PosPionTrueStartDir,"", NPosPion,-NMAXTPCSEC,3);
  AddVarVI(output(),PosPionVId,"",          NPosPion);
  AddVarMF(output(),PosPionDir,"",          NPosPion,-NMAXTPCSEC,3);
  AddVarMF(output(),PosPionPosStart,"",     NPosPion,-NMAXTPCSEC,3);
  AddVarMF(output(),PosPionPosEnd,"",       NPosPion,-NMAXTPCSEC,3);

  // --- Pi0 candidates
  AddVarVF(output(),Pi0ElMom,"",       NPi0El);
  AddVarVF(output(),Pi0ElPull,"",      NPi0El);
  AddVarVI(output(),Pi0ElTId,"",       NPi0El);
  AddVarVI(output(),Pi0ElIndex,"",     NPi0El);
  AddVarVI(output(),Pi0ElParentTId,"", NPi0El);
  AddVarVI(output(),Pi0ElGParentTId,"",NPi0El);
  AddVarVI(output(),Pi0ElVId,"",       NPi0El);
  AddVarMF(output(),Pi0ElDir,"",       NPi0El,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0ElPosStart,"",  NPi0El,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0ElPosEnd,"",    NPi0El,-NMAXTPCSEC,3);

  AddVarVF(output(),Pi0PosMom,"",       NPi0Pos);
  AddVarVF(output(),Pi0PosPull,"",      NPi0Pos);
  AddVarVI(output(),Pi0PosTId,"",       NPi0Pos);
  AddVarVI(output(),Pi0PosIndex,"",     NPi0Pos);
  AddVarVI(output(),Pi0PosParentTId,"", NPi0Pos);
  AddVarVI(output(),Pi0PosGParentTId,"",NPi0Pos);
  AddVarVI(output(),Pi0PosVId,"",       NPi0Pos);
  AddVarMF(output(),Pi0PosDir,"",       NPi0Pos,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0PosPosStart,"",  NPi0Pos,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0PosPosEnd,"",    NPi0Pos,-NMAXTPCSEC,3);

  // --- ALL TPC sec tracks 
  AddVarVF(output(),TPCSecMom,"",       NTPCSec);
  AddVarVF(output(),TPCSecMuPidLik,"",  NTPCSec);
  AddVarVF(output(),TPCSecPiPidLik,"",  NTPCSec);
  AddVarVF(output(),TPCSecPrPidLik,"",  NTPCSec);
  AddVarVF(output(),TPCSecElPidLik,"",  NTPCSec);
  AddVarVI(output(),TPCSecDetectors,"", NTPCSec);
  AddVarVI(output(),TPCSecQ,"",         NTPCSec);
  AddVarVI(output(),TPCSecTId,"",       NTPCSec);
  AddVarVI(output(),TPCSecIndex,"",     NTPCSec);
  AddVarVI(output(),TPCSecParentTId,"", NTPCSec);
  AddVarVI(output(),TPCSecGParentTId,"",NTPCSec);
  AddVarMF(output(),TPCSecDir,"",       NTPCSec,-NMAXTPCSEC,3);
  AddVarMF(output(),TPCSecPosStart,"",  NTPCSec,-NMAXTPCSEC,3);
  AddVarMF(output(),TPCSecPosEnd,"",    NTPCSec,-NMAXTPCSEC,3);

  // ---- IsoFGD Pion tracks -----
  AddVarVF(output(),FGDPiLength,"",           NFGDPi); 
  AddVarVF(output(),FGDPiPiPull,"",           NFGDPi); 
  AddVarVF(output(),FGDPiAvgTime,"",          NFGDPi); 
  AddVarVF(output(),FGDPiDistance,"",         NFGDPi);
  AddVarVF(output(),FGDPiMuonangle,"",        NFGDPi);  
  AddVarVF(output(),FGDPiCosTheta,"",         NFGDPi);
  AddVarVI(output(),FGDPiTId,"",              NFGDPi);
  AddVarVI(output(),FGDPiIndex,"",            NFGDPi);
  AddVarVI(output(),FGDPiParentTId,"",        NFGDPi);
  AddVarVI(output(),FGDPiGParentTId,"",       NFGDPi);
  AddVarVI(output(),FGDPiVId,"",              NFGDPi);
  AddVarMF(output(),FGDPiDir,"",              NFGDPi,-NMAXTPCSEC,3);
  AddVarMF(output(),FGDPiPosStart,"",         NFGDPi,-NMAXTPCSEC,3);
  AddVarMF(output(),FGDPiPosEnd,"",           NFGDPi,-NMAXTPCSEC,3);
  AddVarVF(output(),FGDPiTimeIni,"",          NFGDPi); 
  AddVarVF(output(),FGDPiTimeEnd,"",          NFGDPi); 
  AddVarVF(output(),FGDPiDeltaTimeIniSelMu,"",NFGDPi);  
  AddVarVF(output(),FGDPiDeltaTimeEndSelMu,"",NFGDPi); 

  // ---- IsoFGD electron and positron tracks -----
  AddVarVF(output(),FGDElLength,"",           NFGDEl); 
  AddVarVF(output(),FGDElPiPull,"",           NFGDEl); 
  AddVarVF(output(),FGDElAvgTime,"",          NFGDEl); 
  AddVarVI(output(),FGDElTId,"",              NFGDEl); 
  AddVarVI(output(),FGDElIndex,"",            NFGDEl); 
  AddVarVI(output(),FGDElParentTId,"",        NFGDEl); 
  AddVarVI(output(),FGDElGParentTId,"",       NFGDEl); 
  AddVarVI(output(),FGDElVId,"",              NFGDEl);
  AddVarVF(output(),FGDElTimeIni,"",          NFGDEl);  
  AddVarVF(output(),FGDElTimeEnd,"",          NFGDEl); 
  AddVarVF(output(),FGDElDeltaTimeIniSelMu,"",NFGDEl);  
  AddVarVF(output(),FGDElDeltaTimeEndSelMu,"",NFGDEl); 
  AddVarVF(output(),FGDElDistance,"",         NFGDEl);
  AddVarVF(output(),FGDElMuonangle,"",        NFGDEl); 
  AddVarVF(output(),FGDElCosTheta,"",         NFGDEl);
  AddVarMF(output(),FGDElDir,"",              NFGDEl,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDElPosStart,"",         NFGDEl,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDElPosEnd,"",           NFGDEl,-NMAXFGDSEC,3);


  // ---- IsoFGD tracks -----
  AddVarVF(output(),FGDSecLength,"",           NFGDSec); 
  AddVarVF(output(),FGDSecPiPull,"",           NFGDSec);
  AddVarVF(output(),FGDSecProtPull,"",         NFGDSec); 
  AddVarVF(output(),FGDSecAvgTime,"",          NFGDSec); 
  AddVarVI(output(),FGDSecContained,"",        NFGDSec); 
  AddVarVI(output(),FGDSecTId,"",              NFGDSec); 
  AddVarVI(output(),FGDSecIndex,"",            NFGDSec); 
  AddVarVI(output(),FGDSecParentTId,"",        NFGDSec); 
  AddVarVI(output(),FGDSecGParentTId,"",       NFGDSec);
  AddVarVF(output(),FGDSecTimeIni,"",          NFGDSec); 
  AddVarVF(output(),FGDSecTimeEnd,"",          NFGDSec); 
  AddVarVF(output(),FGDSecDeltaTimeIniSelMu,"",NFGDSec);  
  AddVarVF(output(),FGDSecDeltaTimeEndSelMu,"",NFGDSec); 
  AddVarVF(output(),FGDSecCosTheta,"",         NFGDSec);
  AddVarMF(output(),FGDSecDir,"",              NFGDSec,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDSecPosStart,"",         NFGDSec,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDSecPosEnd,"",           NFGDSec,-NMAXFGDSEC,3);


  // ---- Michel Eletrons ----
  AddVarVI(output(),MENHits,"",    NME); 
  AddVarVF(output(),MERawCharge,"",NME); 
  AddVarVF(output(),MEMinTime,"",  NME); 
  AddVarVF(output(),MEMaxTime,"",  NME); 

  // ---- TPC1 Tracks ----
  AddVarVF(output(),TPC1TrackMom,"",       NTPC1Track); 
  AddVarVF(output(),TPC1TrackCosTheta,"",  NTPC1Track);
  AddVarVF(output(),TPC1TrackPhi,"",       NTPC1Track);
  AddVarVI(output(),TPC1TrackVId,"",       NTPC1Track); 
  AddVarVI(output(),TPC1TrackTId,"",       NTPC1Track); 
  AddVarVI(output(),TPC1TrackParentTId,"", NTPC1Track); 
  AddVarVI(output(),TPC1TrackGParentTId,"",NTPC1Track); 
  AddVarMF(output(),TPC1TrackPosStart,"",  NTPC1Track,-NMAXTPC1,3); 
  AddVarMF(output(),TPC1TrackPosEnd,"",    NTPC1Track,-NMAXTPC1,3); 

  // --- Info to understand Pion SI -----
  if (_addPionSIinfo){
    AddVarVI(output(),IntType,         "", NInts);
    AddVarVI(output(),IntTypeFull,     "", NInts);
    AddVarVF(output(),DataToMCRatio,   "", NInts);
    AddVarVF(output(),DataXSec,        "", NInts);
    AddVarVF(output(),DataXSec_ext,    "", NInts);
    AddVarVF(output(),MCXSec,          "", NInts);
    AddVarVF(output(),DataXSecErr,     "", NInts);
    AddVarVF(output(),DataXSecErr_ext, "", NInts);
    AddVarVF(output(),MCXSecErr,       "", NInts);
    
    AddVarVF(output(),PionMomBinInt, "", NInts);


    AddVarVI(output(),PionType,      "", NPions);
    AddVarVF(output(),PionMom,       "", NPions);

    AddVarF(output(),LargestRatio,            "");
    AddVarF(output(),LargestRatioPionMomBin,  "");
    AddVarF(output(),LargestRatioIntTypeFull, "");
    AddVarF(output(),LargestRatioDataXSec,    "");
    AddVarF(output(),LargestRatioMCXSec,      "");

  }

  //--- true pion variables -------
  AddVarF(   output(), truepi_mom,      "true pion momentum");
  AddVarF(   output(), truepi_costheta, "true pion cos(theta)");
  AddVar3VF( output(), truepi_dir,      "true pion direction");
  AddVarI(   output(), truepi_id,       "true pion id");
  AddVarI(   output(), truepi_pdg,      "true pion pdg");

  //Photon variables helpful for photon samples
  AddVarVF(output(),ECalPhotonEnergy,               "", NECalIsoObjects);
  AddVarVF(output(),ECalPhotonPositionX,            "", NECalIsoObjects);
  AddVarVF(output(),ECalPhotonPositionY,            "", NECalIsoObjects);
  AddVarVF(output(),ECalPhotonPositionZ,            "", NECalIsoObjects);
  AddVarVF(output(),ECalPhotonPIDEmHip,             "", NECalIsoObjects);
  AddVarVF(output(),ECalPhotonPIDQuality,           "", NECalIsoObjects);
  AddVarVI(output(),ECalPhotonClustering3DSeedType, "", NECalIsoObjects);
  AddVarVI(output(),ECalPhotonNHits,                "", NECalIsoObjects);
  AddVarVI(output(),ECalPhotonDetector,             "", NECalIsoObjects);

  //Proton variables helpful for proton samples
  AddVarI(output(), true_nprotons,      "true_nprotons");
  AddVarVF(output(), FGDProtMom,"",         nProtonsFGD); 
  AddVarVI(output(), FGDProtonTId,"",       nProtonsFGD);
  AddVarVF(output(), TPCProtMom,"",         nProtonsTPC); 
  AddVarVI(output(), TPCProtonTId,"",       nProtonsTPC);

  //--- kinematics to vertex vars -------

  if (_storeRecoPionProtVtx){
    AddToyVarF( output(), sel_pi_mom_vertex,   "");
    AddToyVarF( output(), sel_prot_mom_vertex, "");
    AddToyVarF( output(), sel_pi_truemom,      "");
    AddToyVarF( output(), sel_prot_truemom,    "");

    AddToyVar3VF( output(), sel_pi_dir_vertex,   "");
    AddToyVar3VF( output(), sel_prot_dir_vertex, "");
    AddToyVar3VF( output(), sel_pi_truedir,      "");
    AddToyVar3VF( output(), sel_prot_truedir,    "");


    AddToyVarI( output(), sel_pi_topo,         "");
    AddToyVarI( output(), sel_prot_topo,       "");


    AddToyVarF( output(), sel_pi_range_vtx,       "");
    AddToyVarF( output(), sel_prot_range_vtx,     "");

  }


}

//********************************************************************
void numuCCMultiPiAnalysis::DefineTruthTree(){
  //********************************************************************

  // Variables from the numuCCAnalysis analysis
  _numuCCAnalysis->DefineTruthTree();

  if (_storeAllTruePrimaryPions){
    AddAllTruePrimaryPionsVars();
  }

  //--- true pion variables -------
  AddVarF(   output(), truepi_mom,      "true pion momentum");
  AddVarF(   output(), truepi_costheta, "true pion cos(theta)");
  AddVar3VF( output(), truepi_dir,      "true pion direction");
  AddVarI(   output(), truepi_id,       "true pion id");
  AddVarI(   output(), truepi_pdg,      "true pion pdg");
}

//********************************************************************
void numuCCMultiPiAnalysis::AddAllTruePrimaryPionsVars(){
  //********************************************************************
  _storeAllTruePrimaryPions = true;

  // --- true pion variables for all pions ---
  AddVarVF(output(), TrueNegPionMom,      "", NTrueNegPion);
  AddVarMF(output(), TrueNegPionStartDir, "", NTrueNegPion,  -NMAXTRUEPARTICLES, 3);
  AddVarMF(output(), TrueNegPionStartPos, "", NTrueNegPion,  -NMAXTRUEPARTICLES, 4);
  AddVarMF(output(), TrueNegPionEndPos,   "", NTrueNegPion,  -NMAXTRUEPARTICLES, 4);

  AddVarVF(output(), TruePosPionMom,      "", NTruePosPion);
  AddVarMF(output(), TruePosPionStartDir, "", NTruePosPion,  -NMAXTRUEPARTICLES, 3);
  AddVarMF(output(), TruePosPionStartPos, "", NTruePosPion,  -NMAXTRUEPARTICLES, 4);
  AddVarMF(output(), TruePosPionEndPos,   "", NTruePosPion,  -NMAXTRUEPARTICLES, 4);

}

//********************************************************************
void numuCCMultiPiAnalysis::FillMicroTrees(bool addBase){
  //********************************************************************
  // Variables from the numuCCAnalysis analysis (including the ones in baseTrackerAnalysis by default, otherwise addBase should be false)
  if (addBase) _numuCCAnalysis->FillMicroTrees(addBase);

  if (mybox().MainTrack  ) {
    if( mybox().MainTrack->TrueObject ){
      output().FillVar(MuonIndex,mybox().MainTrack->TrueObject->ID);
      if( mybox().MainTrack->GetTrueParticle()->TrueVertex ) 
        output().FillVar(MuonVertexId,static_cast<AnaTrueVertex*>(mybox().MainTrack->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    }
  }

  // --- Fill here more variables for the CCMultiPi analysis -----
  // Selected negative pions 
  for( Int_t i = 0; i < mybox().pionBox.nNegativePionTPCtracks; i++ ){

    AnaTrackB *track = mybox().pionBox.NegativePionTPCtracks[i];

    output().FillVectorVar(NegPionPidLik,   anaUtils::GetPIDLikelihood(*track,3));    

    Float_t miplklh = (anaUtils::GetPIDLikelihood(*track,0)+anaUtils::GetPIDLikelihood(*track,3))/(1.-anaUtils::GetPIDLikelihood(*track,2)); 
    output().FillVectorVar(NegPionMipPidLik,   miplklh);

    if( track->TrueObject ){
      output().FillVectorVar(NegPionTId,  track->GetTrueParticle()->PDG);
      output().FillVectorVar(NegPionIndex,track->GetTrueParticle()->ID); 
      output().FillVectorVar(NegPionParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(NegPionGParentTId,track->GetTrueParticle()->GParentPDG);

      output().FillVectorVar(NegPionTrueMom, track->GetTrueParticle()->Momentum);
      output().FillMatrixVarFromArray(NegPionTrueStartDir, track->GetTrueParticle()->Direction, 3);

      output().FillVectorVar(NegPionTId,  track->GetTrueParticle()->PDG);
      if( track->GetTrueParticle()->TrueVertex )
        output().FillVectorVar(NegPionVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    }
    output().FillMatrixVarFromArray(NegPionPosStart, track->PositionStart, 3);
    output().FillMatrixVarFromArray(NegPionPosEnd,   track->PositionEnd,3);
    output().FillMatrixVarFromArray(NegPionDir,      track->DirectionStart,3);
    output().IncrementCounter(NNegPion);
  }

  // Selected positive pions 
  for( Int_t i = 0; i <mybox().pionBox.nPositivePionTPCtracks; i++ ){
    AnaTrackB *track = mybox().pionBox.PositivePionTPCtracks[i];

    // output().FillVectorVar(PosPionMom,      track->Momentum); Filled in FillToyVarsInMicroTree
    output().FillVectorVar(PosPionPidLik,   anaUtils::GetPIDLikelihood(*track,3));    


    Float_t miplklh = (anaUtils::GetPIDLikelihood(*track,0)+anaUtils::GetPIDLikelihood(*track,3))/(1.-anaUtils::GetPIDLikelihood(*track,2)); 
    output().FillVectorVar(PosPionMipPidLik,   miplklh);

    if( track->TrueObject ){
      output().FillVectorVar(PosPionTId,  track->GetTrueParticle()->PDG);
      output().FillVectorVar(PosPionIndex,track->GetTrueParticle()->ID); 
      output().FillVectorVar(PosPionParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(PosPionGParentTId,track->GetTrueParticle()->GParentPDG);

      output().FillVectorVar(PosPionTrueMom, track->GetTrueParticle()->Momentum);
      output().FillMatrixVarFromArray(PosPionTrueStartDir, track->GetTrueParticle()->Direction, 3);

      if( track->GetTrueParticle()->TrueVertex )
        output().FillVectorVar(PosPionVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    }

    output().FillMatrixVarFromArray(PosPionPosStart, track->PositionStart, 3); 
    output().FillMatrixVarFromArray(PosPionPosEnd,   track->PositionEnd,3);
    output().FillMatrixVarFromArray(PosPionDir,      track->DirectionStart,3); // Use PosPionTheta to access the angle, it is fille in FillToyVarsInMicroTree
    output().IncrementCounter(NPosPion);
  }

  // Primary pion

  if (GetVertex() && GetVertex()->TrueVertex){
    AnaTrueVertex* vtx =  static_cast<AnaTrueVertex*>(GetVertex()->TrueVertex);
    if ((*vtx).NPrimaryParticles[ParticleId::kPions] > 0) {

      // variables not filled previously, look for pion in AnaTrueVertex
      AnaTrueParticleB* trk = NULL;
      std::vector<AnaTrueParticleB*> particles((*vtx).NPrimaryParticles[ParticleId::kPions], NULL);
      int count = 0; 
      for (int it=0; it<(*vtx).nTrueParticles; it++) {
        trk = (*vtx).TrueParticles[it];
        if (!trk) continue;
        if (abs(trk->PDG) != 211) continue;
        if (trk->ParentID !=0) continue;
        if (count >= (*vtx).NPrimaryParticles[ParticleId::kPions]) continue;
        particles[count++] = trk; 
      }

      // Sort 
      std::sort(particles.begin(), particles.end(), AnaTrueParticleB::CompareMomentum);

      if (particles[0]){    
        output().FillVar(truepi_mom, particles[0]->Momentum);
        output().FillVar(truepi_costheta, (Float_t)cos(anaUtils::ArrayToTVector3(particles[0]->Direction).Angle(anaUtils::ArrayToTVector3(vtx->NuDir))));
        output().FillVectorVarFromArray(truepi_dir, particles[0]->Direction, 3);

        output().FillVar(truepi_id, particles[0]->ID);
        output().FillVar(truepi_pdg, particles[0]->PDG);

      }
    }
  }

  //filling ECAL photon information
  for (unsigned int i=0; i<mybox().pionBox.nECalPhotons; i++){

    AnaTrackB* photon = mybox().pionBox.ECalPhotons[i];
    AnaECALParticleB* photonECAL = static_cast<AnaECALParticleB*>(photon->ECALSegments[0]);

    output().FillVectorVar(ECalPhotonEnergy,               photonECAL->EMEnergy);
    output().FillVectorVar(ECalPhotonPositionX,            photonECAL->PositionStart[0]);
    output().FillVectorVar(ECalPhotonPositionY,            photonECAL->PositionStart[1]);
    output().FillVectorVar(ECalPhotonPositionZ,            photonECAL->PositionStart[2]);
    output().FillVectorVar(ECalPhotonPIDEmHip,             photonECAL->PIDEmHip);
    output().FillVectorVar(ECalPhotonPIDQuality,           photonECAL->PIDQuality);
    output().FillVectorVar(ECalPhotonClustering3DSeedType, photonECAL->Clustering3DSeedType);
    output().FillVectorVar(ECalPhotonNHits,                photonECAL->NHits);

    Int_t detector = photonECAL->Detector;
    output().FillVectorVar(ECalPhotonDetector,          detector);

    output().IncrementCounter(NECalIsoObjects);
  }

  //filling TPC proton information
  for( Int_t i = 0; i < mybox().pionBox.nProtonTPCtracks; i++ )
  {
    AnaTrackB *track = mybox().pionBox.ProtonTPCtracks[i];

    output().FillVectorVar(TPCProtMom, track->Momentum);

    if( track->GetTrueParticle() )
    {
      output().FillVectorVar(TPCProtonTId,       track->GetTrueParticle()->PDG);
    }
    output().IncrementCounter(nProtonsTPC);        
  }
  //filling FGD proton information
  for( Int_t i = 0; i < mybox().pionBox.nProtonFGDtracks; i++ )
  {
    AnaTrackB *track = mybox().pionBox.ProtonFGDtracks[i];
    output().FillVectorVar(FGDProtMom, track->RangeMomentumProton);

    if( track->GetTrueParticle() )
    {
      output().FillVectorVar(FGDProtonTId,       track->GetTrueParticle()->PDG);
    }
    output().IncrementCounter(nProtonsFGD);
  }
  //filling true proton information
  int nprotons = 0;
  if (GetVertex() && GetVertex()->TrueVertex)
  {
    AnaTrueVertex *vtxProt = static_cast<AnaTrueVertex*>(mybox().MainTrack->GetTrueParticle()->TrueVertex);
    for(int i = 0; i<vtxProt->nTrueParticles; i++)
    {
      if( vtxProt->TrueParticles[i]->PDG == 2212 && vtxProt->TrueParticles[i]->ParentPDG == 0 ) 
      {
        nprotons++; 
      }
    }
  }
  output().FillVar(true_nprotons,nprotons);


  // Selected pi0 electron tracks 
  for( Int_t i = 0; i < mybox().pionBox.nElPi0TPCtracks; i++ ) {
    AnaTrackB *track = mybox().pionBox.ElPi0TPCtracks[i];
    output().FillVectorVar(Pi0ElMom, track->Momentum);
    output().FillVectorVar(Pi0ElPull, anaUtils::GetPIDLikelihood(*track,1)); 
    if( track->GetTrueParticle() ){
      output().FillVectorVar(Pi0ElTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(Pi0ElIndex,     track->GetTrueParticle()->ID);
      output().FillVectorVar(Pi0ElParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(Pi0ElGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex  )
        output().FillVectorVar(Pi0ElVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    } 

    output().FillMatrixVarFromArray(Pi0ElPosStart, track->PositionStart, 3);
    output().FillMatrixVarFromArray(Pi0ElPosEnd,   track->PositionEnd,   3);
    output().FillMatrixVarFromArray(Pi0ElDir,      track->DirectionStart,3);
    output().IncrementCounter(NPi0El);
  }

  // Selected pi0 positron tracks 
  for( Int_t i = 0; i < mybox().pionBox.nPosPi0TPCtracks; i++ ) {
    AnaTrackB *track = mybox().pionBox.PosPi0TPCtracks[i];
    output().FillVectorVar(Pi0PosMom, track->Momentum);
    output().FillVectorVar(Pi0PosPull, anaUtils::GetPIDLikelihood(*track,1)); 
    if( track->GetTrueParticle() ){
      output().FillVectorVar(Pi0PosTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(Pi0PosIndex,     track->GetTrueParticle()->ID);
      output().FillVectorVar(Pi0PosParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(Pi0PosGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex  )
        output().FillVectorVar(Pi0PosVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    } 

    output().FillMatrixVarFromArray(Pi0PosPosStart, track->PositionStart, 3);
    output().FillMatrixVarFromArray(Pi0PosPosEnd,   track->PositionEnd,   3);
    output().FillMatrixVarFromArray(Pi0PosDir,      track->DirectionStart,3);
    output().IncrementCounter(NPi0Pos);
  }


  // All TPC secondary tracks 
  for( Int_t i = 0; i < mybox().nPositiveTPCtracks; i++ ) {
    AnaTrackB *track = mybox().PositiveTPCtracks[i];

    if( mybox().HMNtrack == track ) continue; // This is the muon

    output().FillVectorVar(TPCSecMom,               track->Momentum);
    output().FillVectorVar(TPCSecPiPidLik,          anaUtils::GetPIDLikelihood(*track,3));
    output().FillVectorVar(TPCSecMuPidLik,          anaUtils::GetPIDLikelihood(*track,0));
    output().FillVectorVar(TPCSecElPidLik,          anaUtils::GetPIDLikelihood(*track,1));
    output().FillVectorVar(TPCSecPrPidLik,          anaUtils::GetPIDLikelihood(*track,2));
    output().FillMatrixVarFromArray(TPCSecPosStart, track->PositionStart,3);
    output().FillMatrixVarFromArray(TPCSecPosEnd,   track->PositionEnd,3);
    output().FillMatrixVarFromArray(TPCSecDir,      track->DirectionStart,3);
    output().FillVectorVar(TPCSecQ,1); 
    if( track->GetTrueParticle() ){
      output().FillVectorVar(TPCSecTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(TPCSecIndex,     track->GetTrueParticle()->ID);
      output().FillVectorVar(TPCSecParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(TPCSecGParentTId,track->GetTrueParticle()->GParentPDG);
    }

    output().IncrementCounter(NTPCSec); 
  }


  for( Int_t i = 0; i < mybox().nNegativeTPCtracks; i++ ) {
    AnaTrackB *track = mybox().NegativeTPCtracks[i];
    if( mybox().HMNtrack == track ) continue; // This is the muon

    output().FillVectorVar(TPCSecMom,               track->Momentum);
    output().FillVectorVar(TPCSecPiPidLik,          anaUtils::GetPIDLikelihood(*track,3));
    output().FillVectorVar(TPCSecMuPidLik,          anaUtils::GetPIDLikelihood(*track,0));
    output().FillVectorVar(TPCSecElPidLik,          anaUtils::GetPIDLikelihood(*track,1));
    output().FillVectorVar(TPCSecPrPidLik,          anaUtils::GetPIDLikelihood(*track,2));
    output().FillMatrixVarFromArray(TPCSecPosStart, track->PositionStart,3);
    output().FillMatrixVarFromArray(TPCSecPosEnd,   track->PositionEnd,3);
    output().FillMatrixVarFromArray(TPCSecDir,      track->DirectionStart,3);
    output().FillVectorVar(TPCSecQ,-1); 
    if( track->GetTrueParticle() ){
      output().FillVectorVar(TPCSecTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(TPCSecIndex,     track->GetTrueParticle()->ID);
      output().FillVectorVar(TPCSecParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(TPCSecGParentTId,track->GetTrueParticle()->GParentPDG);
    }
    output().IncrementCounter(NTPCSec); 
  }

  // isoFGD pion candidates 
  for (Int_t i=0;i < mybox().pionBox.nIsoFGDPiontracks;i++){
    AnaTrackB* track =  mybox().pionBox.IsoFGDPiontracks[i];
    AnaFGDParticle *fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[0]);
    if( !fgdTrack ) continue; 
    ///checking times
    Float_t timeinipi = fgdTrack->PositionStart[3];
    Float_t timeendpi = fgdTrack->PositionEnd[3];

    output().FillVectorVar(FGDPiPiPull,  fgdTrack->Pullpi); 
    output().FillVectorVar(FGDPiAvgTime, fgdTrack->AvgTime); 
    // Direction of the segment 
    output().FillVectorVar(FGDPiCosTheta,(Float_t)(anaUtils::ArrayToTVector3(fgdTrack->DirectionStart).CosTheta()));
    //output().FillVectorVar(FGDPiLength,fgdTrack->Length); 
    output().FillVectorVar(FGDPiLength,  fgdTrack->X); 
    output().FillVectorVar(FGDPiTimeIni, timeinipi);  
    output().FillVectorVar(FGDPiTimeEnd, timeendpi); 

    output().FillMatrixVarFromArray(FGDPiDir,     fgdTrack->DirectionStart,3);
    output().FillMatrixVarFromArray(FGDPiPosStart,fgdTrack->PositionStart, 3);
    output().FillMatrixVarFromArray(FGDPiPosEnd,  fgdTrack->PositionEnd,   3);
    if( track->GetTrueParticle() ){
      output().FillVectorVar(FGDPiTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(FGDPiIndex,     track->GetTrueParticle()->ID); 
      output().FillVectorVar(FGDPiParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(FGDPiGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex )
        output().FillVectorVar(FGDPiVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    }
    if( mybox().HMNtrack ) { 
      Float_t deltainimuinipi = TMath::Abs(timeinipi-mybox().HMNtrack->PositionStart[3]);
      Float_t deltaendmuinipi = TMath::Abs(timeendpi-mybox().HMNtrack->PositionStart[3]); 
      output().FillVectorVar(FGDPiDeltaTimeIniSelMu,deltainimuinipi);  
      output().FillVectorVar(FGDPiDeltaTimeEndSelMu,deltaendmuinipi); 
      // Minimum distance to the muon vertex 
      Float_t dist1 = (anaUtils::ArrayToTVector3(fgdTrack->PositionStart) - anaUtils::ArrayToTVector3(mybox().HMNtrack->PositionStart)).Mag();
      Float_t dist2 = (anaUtils::ArrayToTVector3(fgdTrack->PositionEnd)   - anaUtils::ArrayToTVector3(mybox().HMNtrack->PositionStart)).Mag();
      output().FillVectorVar(FGDPiDistance,TMath::Min(dist1,dist2)); 
    }
    output().IncrementCounter(NFGDPi);
  }

  // isoFGD electron and positron candidates 
  for (Int_t i=0;i < mybox().pionBox.nIsoFGDElPi0tracks;i++){
    AnaTrackB* track =  mybox().pionBox.IsoFGDElPi0tracks[i];
    AnaFGDParticle *fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[0]);
    if( !fgdTrack ) continue; 
    Float_t timeiniEl = fgdTrack->PositionStart[3];
    Float_t timeendEl = fgdTrack->PositionEnd[3];
    output().FillVectorVar(FGDElCosTheta,(Float_t)(anaUtils::ArrayToTVector3(fgdTrack->DirectionStart).CosTheta()));
    output().FillVectorVar(FGDElPiPull,fgdTrack->Pullpi); 
    output().FillVectorVar(FGDElAvgTime,fgdTrack->AvgTime); 
    //output().FillVectorVar(FGDElLength,fgdTrack->Length); 
    output().FillVectorVar(FGDElLength,fgdTrack->X); 
    output().FillVectorVar(FGDElTimeIni,timeiniEl);  
    output().FillVectorVar(FGDElTimeEnd,timeendEl); 
    //  Minimum distance to the muon vertex 
    if( mybox().HMNtrack ) {
      Float_t deltainimuiniEl = TMath::Abs(timeiniEl-mybox().HMNtrack->PositionStart[3]);
      Float_t deltaendmuiniEl = TMath::Abs(timeendEl-mybox().HMNtrack->PositionStart[3]);
      Float_t dist1 = (anaUtils::ArrayToTVector3(fgdTrack->PositionStart) - anaUtils::ArrayToTVector3(mybox().HMNtrack->PositionStart)).Mag();
      Float_t dist2 = (anaUtils::ArrayToTVector3(fgdTrack->PositionEnd)   - anaUtils::ArrayToTVector3(mybox().HMNtrack->PositionStart)).Mag();
      Float_t prodEl1 = anaUtils::ArrayToTVector3(fgdTrack->DirectionStart)*anaUtils::ArrayToTVector3(mybox().HMNtrack->DirectionStart);

      output().FillVectorVar(FGDElDeltaTimeIniSelMu,deltainimuiniEl);  
      output().FillVectorVar(FGDElDeltaTimeEndSelMu,deltaendmuiniEl);  
      output().FillVectorVar(FGDElDistance,TMath::Min(dist1,dist2));
      output().FillVectorVar(FGDElMuonangle,prodEl1);

    }
    // Direction and position  of the segment
    output().FillMatrixVarFromArray(FGDElDir,     fgdTrack->DirectionStart,3);
    output().FillMatrixVarFromArray(FGDElPosStart,fgdTrack->PositionStart, 3);
    output().FillMatrixVarFromArray(FGDElPosEnd,  fgdTrack->PositionEnd,   3);

    if( track->GetTrueParticle() ){
      output().FillVectorVar(FGDElTId,track->GetTrueParticle()->PDG);
      output().FillVectorVar(FGDElIndex,track->GetTrueParticle()->ID);       
      output().FillVectorVar(FGDElParentTId,track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(FGDElGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex )
        output().FillVectorVar(FGDElVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    }
    output().IncrementCounter(NFGDEl); 
  }

  // All FGD tracks. 
  AnaRecObjectC** allFGDParticles = NULL;
  int nFGD = 0;
  if (box().DetectorFV == SubDetId::kFGD1){
    nFGD         = _event->EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC];
    allFGDParticles = _event->EventBoxes[EventBoxId::kEventBoxTracker]->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC];  
  }
  else if (box().DetectorFV == SubDetId::kFGD2){
    nFGD         = _event->EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC];
    allFGDParticles = _event->EventBoxes[EventBoxId::kEventBoxTracker]->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD2AndNoTPC];  
  }
  for (Int_t i=0;i<nFGD;i++){
    AnaTrackB* track = static_cast<AnaTrackB*>(allFGDParticles[i]);
    AnaFGDParticle *fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[0]);
    if( !fgdTrack ) continue; 
    ///checking times
    Float_t timeini = fgdTrack->PositionStart[3];
    Float_t timeend = fgdTrack->PositionEnd[3];
    output().FillVectorVar(FGDSecTimeIni,timeini);  
    output().FillVectorVar(FGDSecTimeEnd,timeend); 

    if( track->GetTrueParticle() ){
      output().FillVectorVar(FGDSecTId,track->GetTrueParticle()->PDG);
      output().FillVectorVar(FGDSecIndex,track->GetTrueParticle()->ID); 
      output().FillVectorVar(FGDSecParentTId,track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(FGDSecGParentTId,track->GetTrueParticle()->GParentPDG);
    }

    if( mybox().HMNtrack ) {
      Float_t deltainimuini = TMath::Abs(timeini-mybox().HMNtrack->PositionStart[3]);
      Float_t deltaendmuini = TMath::Abs(timeend-mybox().HMNtrack->PositionStart[3]);
      output().FillVectorVar(FGDSecDeltaTimeIniSelMu,deltainimuini);  
      output().FillVectorVar(FGDSecDeltaTimeEndSelMu,deltaendmuini); 
    }

    // Direction of the segment 
    output().FillVectorVar(FGDSecCosTheta,(Float_t)(anaUtils::ArrayToTVector3(fgdTrack->DirectionStart).CosTheta()));
    output().FillMatrixVarFromArray(FGDSecDir,     fgdTrack->DirectionStart,3);
    output().FillMatrixVarFromArray(FGDSecPosStart,fgdTrack->PositionStart, 3);
    output().FillMatrixVarFromArray(FGDSecPosEnd,  fgdTrack->PositionEnd,   3);
    output().FillVectorVar(FGDSecContained,        fgdTrack->Containment);
    output().FillVectorVar(FGDSecPiPull,           fgdTrack->Pullpi);
    output().FillVectorVar(FGDSecProtPull,         fgdTrack->Pullp); 
    output().FillVectorVar(FGDSecAvgTime,          fgdTrack->AvgTime); 
    output().FillVectorVar(FGDSecLength,           fgdTrack->X); 
    //output().FillVectorVar(FGDSecLength,           fgdTrack->Length); 
    output().IncrementCounter(NFGDSec); 

  }

  // Retrieve the EventBox such that we can get the number of michel electrons
  EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(_event->EventBoxes[EventBoxId::kEventBoxTracker]);
  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(mybox().DetectorFV);

  // Fill ME variables. 
  for (Int_t i=0;i < EventBox->nFGDMichelElectrons[det] ;i++){
    AnaFgdTimeBin* me =  static_cast<AnaFgdTimeBin*>(EventBox->FGDMichelElectrons[det][i]);
    if( me->NHits[0] != 0 ) {
      output().FillVectorVar(MENHits,(Int_t)me->NHits[0]);
      output().FillVectorVar(MERawCharge,me->RawChargeSum[0]);
    }
    else {
      output().FillVectorVar(MENHits,(Int_t)me->NHits[1]); 
      output().FillVectorVar(MERawCharge,me->RawChargeSum[1]);
    }
    output().FillVectorVar(MEMinTime,me->MinTime);
    output().FillVectorVar(MEMaxTime,me->MaxTime);
    output().IncrementCounter(NME);
  }

  // Fill TPC1 track variables 
  SubDetId::SubDetEnum tpc = SubDetId::kTPC1;
  if (box().DetectorFV == SubDetId::kFGD1) tpc = SubDetId::kTPC2;  

  AnaTrackB** TPCtracks;
  anaUtils::CreateArray(TPCtracks, NMAXPARTICLES);
  Int_t nTPCtracks = FindTPCTracks(mybox(), tpc, TPCtracks);

  for( Int_t i = 0; i < nTPCtracks; i++ ) {
    AnaTrackB *track = TPCtracks[i];
    if( !track ) continue;
    Float_t phi=TMath::ATan2(track->DirectionStart[1],track->DirectionStart[0]);
    output().FillVectorVar(TPC1TrackPhi,phi );
    if( track->GetTrueParticle() ){
      output().FillVectorVar(TPC1TrackTId,track->GetTrueParticle()->PDG);
      output().FillVectorVar(TPC1TrackParentTId,track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(TPC1TrackGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex )	
        output().FillVectorVar(TPC1TrackVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
    }
    output().FillMatrixVarFromArray(TPC1TrackPosStart,track->PositionStart,3);
    output().FillMatrixVarFromArray(TPC1TrackPosEnd,  track->PositionEnd,  3);
    output().FillVectorVar(TPC1TrackMom, track->Momentum);
    output().IncrementCounter(NTPC1Track);
  }
  delete TPCtracks;

  // --- Info to understand Pion SI -----
  if (_addPionSIinfo){
   
    PionInteractionSystematic* pionSI = _pionSIManager->ComputePionWeightInfo(GetEvent(), mybox().DetectorFV);

    PionIntInfo pionInfo;


    for(int ii = 0; ii < pionSI->nInteractions; ii++){

      unsigned int momBin = (int)((pionSI->pInteraction[ii]*0.1) + 0.5);

      int intType = pionSI->typeInteraction[ii];  

      if(_xsec_data[intType][momBin] != 0.0){

        int mech;
        if      (intType%10 == 0) mech = 0;
        else if (intType%10 == 1) mech = 1;
        else if (intType%10 == 4) mech = 2;
        else mech=-1;
        output().FillVectorVar(IntType,mech);
        output().FillVectorVar(IntTypeFull, intType);

        Float_t data_to_mc = 0; 

        if (_xsec_mc[intType][momBin] != 0){
          data_to_mc = _xsec_data[intType][momBin] / _xsec_mc[intType][momBin];
          output().FillVectorVar(DataToMCRatio, data_to_mc);
        }
        output().FillVectorVar(DataXSec,     _xsec_data[intType][momBin]);
        output().FillVectorVar(DataXSec_ext, _xsec_data_ext[intType][momBin]);
        output().FillVectorVar(MCXSec,       _xsec_mc[intType][momBin]);
        
        output().FillVectorVar(DataXSecErr,     _err_data[intType][momBin]);
        output().FillVectorVar(DataXSecErr_ext, _err_data_ext[intType][momBin]);
        output().FillVectorVar(MCXSecErr,       _err_mc[intType][momBin]);

        output().FillVectorVar(PionMomBinInt, (Float_t)momBin);

        // Update pionInfo
        pionInfo.UpdatePionIntInfo(data_to_mc, momBin, intType, 
            _xsec_data[intType][momBin], _xsec_mc[intType][momBin], 
            _err_data[intType][momBin], _err_mc[intType][momBin], 
            _err_data[intType][momBin]);

        output().IncrementCounter(NInts);
      }


    }
    (static_cast<AnaTrueParticle*>(_pionObject->GetTrueParticle()))->PDG = CATOTHER;

    // Fill the largest ratio
    if  ( pionSI->nInteractions > 0){ 
      output().FillVar(LargestRatio,            pionInfo.Ratio);
      output().FillVar(LargestRatioPionMomBin,  pionInfo.PionMomBin);
      output().FillVar(LargestRatioIntTypeFull, pionInfo.IntTypeFull);
      output().FillVar(LargestRatioDataXSec,    pionInfo.DataXSec);
      output().FillVar(LargestRatioMCXSec,      pionInfo.MCXSec);

      if (pionInfo.IntTypeFull < 100. && pionInfo.IntTypeFull >= 0){
        (static_cast<AnaTrueParticle*>(_pionObject->GetTrueParticle()))->PDG = 211;
      }
      else if (pionInfo.IntTypeFull >= 100){
        (static_cast<AnaTrueParticle*>(_pionObject->GetTrueParticle()))->PDG = -211;
      }
    }

    // Do categories here for pion
    if (_addPionSIinfo){
      anaUtils::FillCategories(&GetEvent(), _pionObject, "pion", SubDetId::kFGD);
      // Fill the tree for the current configuration provided the true codes for color drawing
      std::map< std::string, TrackCategoryDefinition* >::iterator it;
      Int_t categ_index = AnalysisAlgorithm::firstCategory;
      for (it=cat().GetCategories().begin();it!=cat().GetCategories().end();it++, categ_index++ ){
        std::string categ_name = it->first;
        TrackCategoryDefinition& categ = *(it->second);
        if (categ.IsMultiType()){
          for (unsigned int i=0;i<categ.GetNTypes();i++)
            output().FillVectorVar(categ_index, (int)cat().CheckCategoryType(categ_name,i),i);
        }
        else output().FillVar(categ_index, cat().GetCode(categ_name));  
      }
    }
    
    for(int ns = 0; ns < pionSI->nPions; ns++){
      output().FillVectorVar(PionType,pionSI->pionType[ns]);
      output().FillVectorVar(PionMom,pionSI->initMom[ns]);
      output().IncrementCounter(NPions);
    }
  }

  baseTrackerAnalysis::FillEffCounters();


}

//*********************************************************************
Int_t numuCCMultiPiAnalysis::FindTPCTracks(const ToyBoxB& boxB, SubDetId::SubDetEnum det, AnaTrackB** TPCtracks ){
  //*********************************************************************

  // Get tracks in a specific TPC

  const ToyBoxTracker& box = *static_cast<const ToyBoxTracker*>(&boxB);

  Int_t nTPCtracks = 0;

  for(int i = 0; i < box.nPositiveTPCtracks; i++ ) {
    AnaTrackB *ptrack = box.PositiveTPCtracks[i];
    if( SubDetId::GetDetectorUsed(ptrack->Detector, det) ){
      TPCtracks[nTPCtracks++] = ptrack; 
    }
  }

  for(int i = 0; i < box.nNegativeTPCtracks; i++ ) {
    AnaTrackB *ptrack = box.NegativeTPCtracks[i];
    if( SubDetId::GetDetectorUsed(ptrack->Detector, det) ){
      TPCtracks[nTPCtracks++] = ptrack; 
    }
  }

  return nTPCtracks;
}

//********************************************************************
void numuCCMultiPiAnalysis::FillToyVarsInMicroTrees(bool addBase){
  //********************************************************************

  // Variables from the numuCCAnalysis analysis (including the ones in baseTrackerAnalysis by default, otherwise addBase should be false)
  if (addBase) _numuCCAnalysis->FillToyVarsInMicroTrees(addBase);

  // Fill here Variables specific for the numuCCMultiPi analysis - pion momentum and angle for CC-1pi analysis
  for( Int_t i = 0; i <mybox().pionBox.nPositivePionTPCtracks; i++ ){
    AnaTrackB *track = mybox().pionBox.PositivePionTPCtracks[i];
    output().FillToyVectorVar(PosPionMom,    track->Momentum, i);
    output().FillToyVectorVar(PosPionTheta,  (Float_t)acos(track->DirectionStart[2]), i);
  }

  for( Int_t i = 0; i <mybox().pionBox.nNegativePionTPCtracks; i++ ){
    AnaTrackB *track = mybox().pionBox.NegativePionTPCtracks[i];
    output().FillToyVectorVar(NegPionMom,    track->Momentum, i);
    output().FillToyVectorVar(NegPionTheta,  (Float_t)acos(track->DirectionStart[2]), i);
  }

  // Fill whether it is signal or bkg
  // Filled also in numuCCAnalysis, overwritten here
  if(box().MainTrack && box().MainTrack->TrueObject) {
    AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(box().MainTrack->GetTrueParticle()->TrueVertex);
    if (vtx) {
      int ts = 0; // BKG
      // in FGD1 FV
      if (anaUtils::GetTopology(*vtx, SubDetId::kFGD1) == 0) ts = 10;
      else if (anaUtils::GetTopology(*vtx, SubDetId::kFGD1) == 1) ts = 11;
      else if (anaUtils::GetTopology(*vtx, SubDetId::kFGD1) == 2) ts = 12;
      // in FGD2 FV
      else if (anaUtils::GetTopology(*vtx, SubDetId::kFGD2) == 0) ts = 20;
      else if (anaUtils::GetTopology(*vtx, SubDetId::kFGD2) == 1) ts = 21;
      else if (anaUtils::GetTopology(*vtx, SubDetId::kFGD2) == 2) ts = 22;
      output().FillToyVar(true_signal, ts);
    }
  }


  if (_storeRecoPionProtVtx){

    // Fill proton and pion vars to the vertex 
    Float_t mom_pion_tmp   = -999;
    Float_t mom_proton_tmp = -999;

    Float_t dir_pion_tmp[3] = {-999};

    Float_t dir_proton_tmp[3] = {-999};



    AnaTrackB* pionCand = const_cast<multipart::MultiParticleBox&>(mybox().pionBox).GetHMPion(mom_pion_tmp, dir_pion_tmp);
    if (pionCand){
      output().FillToyVar(sel_pi_mom_vertex, mom_pion_tmp);

      output().FillToyVectorVarFromArray(sel_pi_dir_vertex, dir_pion_tmp, 3);


      if (pionCand->GetTrueParticle()){     
        output().FillToyVar(sel_pi_truemom, pionCand->GetTrueParticle()->Momentum);
        output().FillToyVectorVarFromArray(sel_pi_truedir, pionCand->GetTrueParticle()->Direction, 3);

      }


      output().FillToyVar(sel_pi_topo, const_cast<multipart::MultiParticleBox&>(mybox().pionBox).GetPionTopo());

      AnaVertexB* vertex = const_cast<multipart::MultiParticleBox&>(mybox().pionBox).Vertex;

      if (pionCand && vertex){


        Float_t range_start = TMath::Sqrt(anaUtils::GetSeparationSquared(vertex->Position, pionCand->PositionStart));

        Float_t range_end = TMath::Sqrt(anaUtils::GetSeparationSquared(vertex->Position, pionCand->PositionEnd));

        if (range_start > range_end){
          output().FillToyVar(sel_pi_range_vtx, range_start);
        }
        else{
          output().FillToyVar(sel_pi_range_vtx, range_end);
        }


      }

    }


    AnaTrackB* protonCand = const_cast<multipart::MultiParticleBox&>(mybox().pionBox).GetHMProton(mom_proton_tmp, dir_proton_tmp);
    if (protonCand){
      output().FillToyVar(sel_prot_mom_vertex, mom_proton_tmp);


      output().FillToyVectorVarFromArray(sel_prot_dir_vertex, dir_proton_tmp, 3);


      if (protonCand->GetTrueParticle()){
        output().FillToyVar(sel_prot_truemom, protonCand->GetTrueParticle()->Momentum);
        output().FillToyVectorVarFromArray(sel_prot_truedir, protonCand->GetTrueParticle()->Direction, 3);
      }

      output().FillToyVar(sel_prot_topo, const_cast<multipart::MultiParticleBox&>(mybox().pionBox).GetProtonTopo());
    }


    AnaVertexB* vertex = const_cast<multipart::MultiParticleBox&>(mybox().pionBox).Vertex;

    if (protonCand && vertex){


      Float_t range_start = TMath::Sqrt(anaUtils::GetSeparationSquared(vertex->Position, protonCand->PositionStart));

      Float_t range_end = TMath::Sqrt(anaUtils::GetSeparationSquared(vertex->Position, protonCand->PositionEnd));

      if (range_start > range_end){
        output().FillToyVar(sel_prot_range_vtx, range_start);
      }
      else{
        output().FillToyVar(sel_prot_range_vtx, range_end);
      }


    }



  }



}

//********************************************************************
bool numuCCMultiPiAnalysis::CheckFillTruthTree(const AnaTrueVertex& vtx){
  //********************************************************************

  // GetReactionCC already takes into account the outFV and also
  // the NuWro reaction code for 2p2h in prod5 (that is 70)
  bool numuCCinFV = (anaUtils::GetReactionCC(vtx, _fgdID) == 1);

  // Since our topology definition doesn't consider the reaction code
  // and since a muon pair can be created in the FSI (likely in DIS)
  // in principle we might have a non-CC vertex categorized as CCother
  // (nevertheless I didn't find any.)
  int topo = anaUtils::GetTopology(vtx, _fgdID);
  bool topoCCinFV = (topo == 0 || topo == 1 || topo == 2);

  return (numuCCinFV || topoCCinFV);
}

//********************************************************************
void numuCCMultiPiAnalysis::FillTruthTree(const AnaTrueVertex& vtx){
  //********************************************************************
  // Variables from the numuCCAnalysis analysis
  _numuCCAnalysis->FillTruthTree(vtx);

  FillTruePionInfo(vtx); 

  // Fill whether it is signal or bkg
  // Filled also in numuCCAnalysis, overwritten here
  int ts = 0; // BKG
  // in FGD1 FV
  if (anaUtils::GetTopology(vtx, SubDetId::kFGD1) == 0) ts = 10;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD1) == 1) ts = 11;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD1) == 2) ts = 12;
  // in FGD2 FV
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD2) == 0) ts = 20;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD2) == 1) ts = 21;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD2) == 2) ts = 22;
  output().FillVar(true_signal, ts);

}
//********************************************************************
void numuCCMultiPiAnalysis::FillTruePionInfo(const AnaTrueVertex& vtx){
  //********************************************************************

  // Variables for true pion
  // Explicitely order pions in momentum and get the primary one most energetic
  // This is to work for pi- as well (vtx.PionMom was filled with pi+ as for
  // IRODs flat-trees for Oct 2017)
  if (vtx.NPrimaryParticles[ParticleId::kPions] > 0) {
    // variables not filled previously, look for pion in AnaTrueVertex
    AnaTrueParticleB* trk = NULL;
    std::vector<AnaTrueParticleB*> particles(vtx.NPrimaryParticles[ParticleId::kPions], NULL);

    int count = 0; 
    for (int it=0; it<vtx.nTrueParticles; it++) {
      trk = vtx.TrueParticles[it];
      if (!trk) continue;
      if (abs(trk->PDG) != 211) continue;
      if (trk->ParentID !=0) continue;
      if (count >= vtx.NPrimaryParticles[ParticleId::kPions]) continue;
      particles[count++] = trk; 
    }

    // Sort 
    std::sort(particles.begin(), particles.end(), AnaTrueParticleB::CompareMomentum);

    if (particles[0]){    
      output().FillVar(truepi_mom, particles[0]->Momentum);
      output().FillVar(truepi_costheta, (Float_t)cos(anaUtils::ArrayToTVector3(particles[0]->Direction).Angle(anaUtils::ArrayToTVector3(vtx.NuDir))));
      output().FillVectorVarFromArray(truepi_dir, particles[0]->Direction, 3);
      output().FillVar(truepi_id, particles[0]->ID);
      output().FillVar(truepi_pdg, particles[0]->PDG);
    }
  }

  if (!_storeAllTruePrimaryPions)
    return;

  // Fill info for all vars positive and negative separately
  if (vtx.NPrimaryParticles[ParticleId::kPiNeg] > 0){
    AnaTrueParticleB* trk = NULL;
    std::vector<AnaTrueParticleB*> particles(vtx.NPrimaryParticles[ParticleId::kPiNeg], NULL);

    int count = 0; 
    for (int it=0; it<vtx.nTrueParticles; it++) {
      trk = vtx.TrueParticles[it];
      if (!trk) continue;
      if (trk->PDG != -211) continue;
      if (trk->ParentID !=0) continue;
      if (count >= vtx.NPrimaryParticles[ParticleId::kPiNeg]) continue;
      particles[count++] = trk; 
    }

    // Sort 
    std::sort(particles.begin(), particles.end(), AnaTrueParticleB::CompareMomentum);
    for (size_t i = 0; i < particles.size(); i++){
      if (!particles[i]) continue;

      output().FillVectorVar(TrueNegPionMom, particles[i]->Momentum);

      output().FillMatrixVarFromArray(TrueNegPionStartPos, particles[i]->Position,    4 );
      output().FillMatrixVarFromArray(TrueNegPionEndPos,   particles[i]->PositionEnd, 4 );
      output().FillMatrixVarFromArray(TrueNegPionStartDir, particles[i]->Direction,   3 );

      output().IncrementCounterForVar(TrueNegPionMom);
    }  
  }

  if (vtx.NPrimaryParticles[ParticleId::kPiPos] > 0){
    AnaTrueParticleB* trk = NULL;
    std::vector<AnaTrueParticleB*> particles(vtx.NPrimaryParticles[ParticleId::kPiPos], NULL);

    int count = 0; 
    for (int it=0; it<vtx.nTrueParticles; it++) {
      trk = vtx.TrueParticles[it];
      if (!trk) continue;
      if (trk->PDG != 211) continue;
      if (trk->ParentID !=0) continue;
      if (count >= vtx.NPrimaryParticles[ParticleId::kPiPos]) continue;
      particles[count++] = trk; 
    }

    // Sort 
    std::sort(particles.begin(), particles.end(), AnaTrueParticleB::CompareMomentum);
    for (size_t i = 0; i < particles.size(); i++){
      if (!particles[i]) continue;

      output().FillVectorVar(TruePosPionMom, particles[i]->Momentum);

      output().FillMatrixVarFromArray(TruePosPionStartPos, particles[i]->Position,    4 );
      output().FillMatrixVarFromArray(TruePosPionEndPos,   particles[i]->PositionEnd, 4 );
      output().FillMatrixVarFromArray(TruePosPionStartDir, particles[i]->Direction,   3 );

      output().IncrementCounterForVar(TruePosPionMom);
    }  
  }

}


//********************************************************************
void numuCCMultiPiAnalysis::FillCategories(){
  //********************************************************************
  _numuCCAnalysis->FillCategories();
}

