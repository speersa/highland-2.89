#include "numuCC4piMultiPiAnalysis.hxx"
#include "CategoriesUtils.hxx"
#include "numuCC4piMultiPiUtils.hxx"
#include "baseToyMaker.hxx"
#include "CutUtils.hxx"
#include "FiducialVolumeDefinition.hxx"
#include "Parameters.hxx"
#include "BasicUtils.hxx"
#include "NuDirUtils.hxx"
#include "oaAnalysisTreeConverter.hxx"
#include "numuCC4piMultiPiPhotonProtonSelection.hxx"

#include "numuCC4piMultiPiFGD2Selection.hxx"
#include "numuCC4piMultiPiPhotonProtonFGD2Selection.hxx"

#define DEBUG
#ifdef DEBUG
#include <signal.h>
#endif


//const UInt_t NMAXMU = 1000;
const UInt_t NMAXTPCSEC = 1000;
const UInt_t NMAXFGDSEC = 1000;
const UInt_t NMAXTPC1 = 1000;

//********************************************************************
numuCC4piMultiPiAnalysis::numuCC4piMultiPiAnalysis(AnalysisAlgorithm* ana) : baseTrackerAnalysis(ana) {
	//****************************************************************
	//Add the package version
	ND::versioning().AddPackage("numuCC4piMultiPiAnalysis", anaUtils::GetSoftwareVersionFromPath((std::string)getenv("NUMUCC4PIMULTIPIANALYSISROOT")));
	
	_pionSIManager = NULL;
}

//********************************************************************
bool numuCC4piMultiPiAnalysis::Initialize(){
	//****************************************************************
	// Initialize the baseTrackerAnalysis
	if(!baseTrackerAnalysis::Initialize()) return false;
	//Minimum accum level to save event into the output tree
	SetMinAccumCutLevelToSave(ND::params().GetParameterI("numuCC4piMultiPiAnalysis.MinAccumLevelToSave"));
	//Add categories
	numuCC4piMultiPiAnalysis::AddCategories();
  	// which analysis: FGD1, FGD2 or FGDs
  _whichFGD = ND::params().GetParameterI("numuCC4piMultiPiAnalysis.Selections.whichFGD");
  _whichSel = ND::params().GetParameterI("numuCC4piMultiPiAnalysis.Selections.whichSelection");
  // _bwd_info = ND::params().GetParameterI("numuCC4piMultiPiAnalysis.Selections.BWDMigrationInformation");
  if (_whichFGD == 2){
    _bwd_info = 1;
  }
  else {_bwd_info = 0;}

  if (_whichFGD == 3) {
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "WARNING: only for events with accum_level > 5 the vars in the output microtree will surely refer to the muon candidate in that FGD" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
  }
  // Select the FGD
  if (_whichFGD == 1) _fgdID = SubDetId::kFGD1;
  if (_whichFGD == 2) _fgdID = SubDetId::kFGD2; 
  //	if (_whichFGD >  2) _fgdID = SubDetId::kFGD; to be added
  // Add Pion SI info to the micro-trees
  _addPionSIinfo  = (bool)ND::params().GetParameterI("numuCC4piMultiPiAnalysis.MicroTrees.AddPionSIinfo");
  _pion_pdgs 		= init_pions();
  _pionSIManager  = new PionSIManager(); 

  return true;
}

//********************************************************************
void numuCC4piMultiPiAnalysis::DefineSelections(){
  //****************************************************************
  // ----- Inclusive CC -----------
  //sel().AddSelection("kTrackerNumuCC4piMultiPi", "exclusive numuCC4piMultiPi selection", new numuCC4piMultiPiSelection(forceBreak)); //true/false for forcing break
  // ----- Exclusive CCMultiPi -----------
  // numu CC 4pi multi-pi
  if (_fgdID==SubDetId::kFGD1){
    if (_whichSel==1) sel().AddSelection("kTrackerNumuCC4piMultiPi",        "4pi numuCC multi-pion selection",     new numuCC4piMultiPiSelection());
    else if (_whichSel==2) sel().AddSelection("kTrackerNumuCC4piMultiPiPhotonProton",    "4pi multi-pion photon proton selection", new numuCC4piMultiPiPhotonProtonSelection());
  }
  else if (_fgdID==SubDetId::kFGD2){
    if (_whichSel==1) sel().AddSelection("kTrackerNumuCC4piMultiPi FGD2",        "4pi numuCC multi-pion selection FGD2",     new numuCC4piMultiPiFGD2Selection());
    else if (_whichSel==2) sel().AddSelection("kTrackerNumuCC4piMultiPiPhotonProton FGD2",    "4pi multi-pion photon proton selection FGD2", new numuCC4piMultiPiPhotonProtonFGD2Selection());
  }
  
  std::cout << "Added selection!" << std::endl;
}

//********************************************************************
void numuCC4piMultiPiAnalysis::DefineCorrections(){
  //****************************************************************
  //Some corrections are defined in baseAnalysis
  baseTrackerAnalysis::DefineCorrections();
}

//********************************************************************
void numuCC4piMultiPiAnalysis::DefineSystematics(){
  //****************************************************************
  //Some systematics are defined in baseAnalysis
  baseTrackerAnalysis::DefineSystematics();	
}

//********************************************************************
void numuCC4piMultiPiAnalysis::DefineConfigurations(){
  //****************************************************************
  baseTrackerAnalysis::DefineConfigurations();
}

//********************************************************************
void numuCC4piMultiPiAnalysis::DefineMicroTrees(bool addBase){
  //****************************************************************
  //Variables from baseAnalysis (run, event, ...)
  if (addBase) baseTrackerAnalysis::DefineMicroTrees(addBase);
  //--- info from true vertex
  AddVarF(output(),Truemu_mom,"");
  AddVar4VF(output(),Truemu_pos,"");
  AddVar3VF(output(),Truemu_dir,"");

  AddVarF(output(),Truemu_costheta,"");
  AddVarI(output(),Truemu_fgdlayer,"");

  AddVar4VF(output(),Truemu_posend,"");

  // AddVarI(output(), Qualifying_sampleID, "");
  //--- toy variables
  AddToyVarI(output(),NLowAngle,"");
  AddToyVarI(output(),NHighAngle,"");
  AddToyVarI(output(),NFwdMuLike, "");
  AddToyVarI(output(),NBwdMuLike, "");
  AddToyVarI(output(),NHAFwdMuLike, "");
  AddToyVarI(output(),NHABwdMuLike, "");
  AddToyVarF(output(),selmu_mom,"");
  AddToyVarF(output(),selmu_costheta,"");
  AddToyVarF(output(),selmu_direction2,"");
  AddToyVarF(output(),selmu_mom_range_oarecon,"")	
    AddToyVarF(output(),selpi_mom,"");
  AddToyVarF(output(),selpi_pull,"");
  AddToyVarF(output(),selpi_costheta,"");
  AddVar3VF(output(),selpi_dir,"");
  AddVarI(output(),selpi_ID,"");

  //--- info from true track
  AddVarI(output(),selmu_PDG,"");
  AddVarI(output(),selmu_ID,"");
  AddVarF(output(),selmu_truemom,"");
  AddVar4VF(output(),selmu_truepos,"");
  AddVar4VF(output(),selmu_trueendpos,"");
  AddVar3VF(output(),selmu_truedir,"");
  AddVarF(output(),selmu_truecostheta,"");
  AddVarI(output(),selmu_truefgdlayer,"");
  //--- info by global
  AddVarI(output(),selmu_HMNT,"");
  AddVarF(output(),selmu_likemu,""); 
  AddVarF(output(),selmu_likemip,""); 
  AddVarI(output(),selmu_end_ecal,"");	
  AddVarF(output(),selmu_ToF_PoD,"");
  AddVarF(output(),selmu_ToF_ECAL,"");
  AddVarF(output(),selmu_ToF_FGD2,"");

  AddVar4VF(output(), selmu_ToF_topology,"")
    AddVarI(output(), selmu_is_flipped,"")
    AddVarI(output(), selpi_is_flipped,"")

    AddVarI(output(), true_nprotons,      "true_nprotons");
  AddVarVF(output(), FGDProtMom,"",         nProtonsFGD); 
  AddVarVI(output(), FGDProtonTId,"",       nProtonsFGD);
  AddVarVI(output(), proton_is_flippedFGD,"",nProtonsFGD);
  AddVarVF(output(), TPCProtMom,"",         nProtonsTPC); 
  AddVarVI(output(), TPCProtonTId,"",       nProtonsTPC);
  AddVarVI(output(), proton_is_flippedTPC,"",nProtonsTPC);

  AddVarI(output(),selmu_detectors,"");
  AddVarF(output(),selmu_charge,"");
  AddVar3VF(output(),selmu_dir,"");

  AddVar3VF(output(),selmu_enddir,"");
  AddVar3VF(output(),selmu_nuvec,"");
  AddVar3VD(output(), selmu_muvec,"");

  AddVar4VF(output(),selmu_pos,"");
  AddVar4VF(output(),selmu_endpos,"");
  AddVarI(output(),selmu_fgdlayer,"");
  AddVar3VF(output(),selmu_1hit_pos,"");
  AddVar3VF(output(),selmu_2hit_pos,"");
  AddVarF(output(),selmu_1hit_charge,"");
  AddVarF(output(),selmu_2hit_charge,"");

  if (_bwd_info){
    AddVar3VF(output(),selmu_1hit_fitpos,"");
    AddVar3VF(output(),selmu_2hit_fitpos,"");
    AddVarF(output(),selmu_1hit_deltapos,"");
    AddVarF(output(),selmu_2hit_deltapos,"");
    AddVarF(output(),selmu_1hit_deltapos2,"");
    AddVarF(output(),selmu_2hit_deltapos2,"");
    AddVar3VF(output(),FGDSeg_1hit_fitpos,"");
    AddVar3VF(output(),FGDSeg_2hit_fitpos,"");
  }

  AddVarI(output(),selmu_pod_nnodes,""); 
  //--- info by TPC
  AddVarVI(output(),selmu_tpc_det,"", 			selmu_ntpcs);
  AddVarVI(output(),selmu_tpc_nnodes,"", 			selmu_ntpcs);
  AddVarVF(output(),selmu_tpc_charge,"", 			selmu_ntpcs);
  AddVarVF(output(),selmu_tpc_mom,"", 			selmu_ntpcs);

  //--- info by FGD
  AddVarVI(output(),selmu_fgd_det,"", 			selmu_nfgds);
  AddVarVI(output(),selmu_fgd_nnodes,"", 			selmu_nfgds);
  AddVarVF(output(),selmu_fgd_x,"", 				selmu_nfgds);
  //--- info by ECAL
  AddVarVI(output(),selmu_ecal_det,"", 			selmu_necals);
  AddVarVI(output(),selmu_ecal_nnodes,"", 		selmu_necals);
  AddVarVF(output(),selmu_ecal_length,"", 		selmu_necals);
  AddVarVF(output(),selmu_ecal_EMenergy,"", 		selmu_necals);
  AddVarVF(output(),selmu_ecal_mipem,"", 			selmu_necals);
  AddVarVI(output(),selpi_ecal_det,"", 			selmu_necals);
  AddVarVI(output(),selpi_ecal_nnodes,"", 		selpi_necals);
  AddVarVF(output(),selpi_ecal_length,"", 		selpi_necals);
  AddVarVF(output(),selpi_ecal_EMenergy,"", 		selpi_necals);
  AddVarVF(output(),selpi_ecal_mipem,"", 			selpi_necals);
  AddVarVF(output(),selpi_ecal_mippion,"", 		selpi_necals);
  AddVarVI(output(),selpi_ecal_pdg,"", 			selpi_necals);
  AddVarVI(output(),selpi_ecal_id,"", 			selpi_necals);
  AddVarVF(output(),selpi_ecal_costheta,"",      	selpi_necals);

  //--- info by TPC
  AddVarVF(output(),TPCSec_MomGlobal,"", 			NTPCSec);
  AddVarMF(output(),TPCSec_pos,"", 				NTPCSec,-NMAXTPCSEC, 4);
  AddVarMF(output(),TPCSec_endpos,"", 			NTPCSec,-NMAXTPCSEC, 4);
  // --- ALL TPC sec tracks 
  AddVarVF(output(),TPCSecMom,"",       			NTPCSec);
  AddVarVF(output(),TPCSecMudEdx,"",  			NTPCSec);
  AddVarVF(output(),TPCSecPidEdx,"",  			NTPCSec);
  AddVarVF(output(),TPCSecPrdEdx,"",  			NTPCSec);
  AddVarVF(output(),TPCSecEldEdx,"",  			NTPCSec);
  AddVarVF(output(),TPCSecLikemu,"",  			NTPCSec);
  AddVarVF(output(),TPCSecLikemip,"",  			NTPCSec);		
  AddVarVI(output(),TPCSecDetectors,"", 			NTPCSec);
  AddVarVI(output(),TPCSecQ,"",         			NTPCSec);
  AddVarVI(output(),TPCSecTId,"",       			NTPCSec);
  AddVarVI(output(),TPCSecIndex,"",     			NTPCSec);
  AddVarVI(output(),TPCSecParentTId,"", 			NTPCSec);
  AddVarVI(output(),TPCSecGParentTId,"",			NTPCSec);
  AddVarMF(output(),TPCSecDir,"",       			NTPCSec,-NMAXTPCSEC,3);
  AddVarMF(output(),TPCSecPosStart,"",  			NTPCSec,-NMAXTPCSEC,3);
  AddVarMF(output(),TPCSecPosEnd,"",    			NTPCSec,-NMAXTPCSEC,3);
  AddVarVF(output(),TPCSecLength,"",           	NTPCSec);

  // --- Pion candidates (positive)
  AddVarVF(output(),PosPionMom,"",          		NPosPion);
  AddVarVF(output(),PosPionCosTheta,"",         	NPosPion);
  AddVarVF(output(),PosPionPidLik,"",       		NPosPion);
  AddVarVF(output(),PosPionPull,"",       		NPosPion);
  AddVarVI(output(),PosPionTId,"",          		NPosPion);
  AddVarVI(output(),PosPionIndex,"",        		NPosPion);
  AddVarVI(output(),PosPionParentTId,"",    		NPosPion);
  AddVarVI(output(),PosPionGParentTId,"",   		NPosPion);
  AddVarMF(output(),PosPionDir,"",          		NPosPion,-NMAXTPCSEC,3);
  AddVarMF(output(),PosPionPosStart,"",     		NPosPion,-NMAXTPCSEC,3);
  AddVarMF(output(),PosPionPosEnd,"",       		NPosPion,-NMAXTPCSEC,3);
  AddVarVF(output(),PosPionLength,"",           	NPosPion);
  AddVarVF(output(),TruePosPionMom,"",          	NPosPion);
  AddVarVF(output(),TruePosPionCosTheta,"",       NPosPion);
  AddVar3VF(output(),TruePosPionDir,"");

  // --- Pion candidates (negative)
  AddVarVF(output(),NegPionMom,"",          		NNegPion);
  AddVarVF(output(),NegPionCosTheta,"",         	NNegPion);
  AddVarVF(output(),NegPionPidLik,"",       		NNegPion);
  AddVarVF(output(),NegPionPull,"",       		NNegPion);
  AddVarVI(output(),NegPionTId,"",          		NNegPion);
  AddVarVI(output(),NegPionIndex,"",		        NNegPion);
  AddVarVI(output(),NegPionParentTId,"",  		NNegPion);
  AddVarVI(output(),NegPionGParentTId,"",   		NNegPion);
  AddVarMF(output(),NegPionDir,"",          		NNegPion,-NMAXTPCSEC,3);
  AddVarMF(output(),NegPionPosStart,"",     		NNegPion,-NMAXTPCSEC,3);
  AddVarMF(output(),NegPionPosEnd,"",       		NNegPion,-NMAXTPCSEC,3);
  AddVarVF(output(),NegPionLength,"",           	NNegPion);

  // --- Pi0 candidates
  AddVarVF(output(),Pi0ElMom,"",       			NPi0El);
  AddVarVF(output(),Pi0ElPull,"",      			NPi0El);
  AddVarVI(output(),Pi0ElTId,"",       			NPi0El);
  AddVarVI(output(),Pi0ElIndex,"",     			NPi0El);
  AddVarVI(output(),Pi0ElParentTId,"", 			NPi0El);
  AddVarVI(output(),Pi0ElGParentTId,"",			NPi0El);
  AddVarVI(output(),Pi0ElVId,"",       			NPi0El);
  AddVarMF(output(),Pi0ElDir,"",       			NPi0El,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0ElPosStart,"",  			NPi0El,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0ElPosEnd,"",    			NPi0El,-NMAXTPCSEC,3);
  AddVarVF(output(),Pi0PosMom,"",       			NPi0Pos);
  AddVarVF(output(),Pi0PosPull,"",      			NPi0Pos);
  AddVarVI(output(),Pi0PosTId,"",       			NPi0Pos);
  AddVarVI(output(),Pi0PosIndex,"",     			NPi0Pos);
  AddVarVI(output(),Pi0PosParentTId,"", 			NPi0Pos);
  AddVarVI(output(),Pi0PosGParentTId,"",			NPi0Pos);
  AddVarVI(output(),Pi0PosVId,"",       			NPi0Pos);
  AddVarMF(output(),Pi0PosDir,"",       			NPi0Pos,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0PosPosStart,"",  			NPi0Pos,-NMAXTPCSEC,3);
  AddVarMF(output(),Pi0PosPosEnd,"",    			NPi0Pos,-NMAXTPCSEC,3);

  // ---- IsoFGD Pion tracks -----
  AddVarVF(output(),FGDPiMomRangeOarecon,"",      NFGDPi);
  AddVarVF(output(),FGDPiCosTheta,"",         	NFGDPi);
  AddVarVF(output(),FGDPiLength,"",           	NFGDPi);
  AddVarVF(output(),FGDPiLengthX,"",           	NFGDPi); 
  AddVarVF(output(),FGDPiPiPull,"",           	NFGDPi); 
  AddVarVF(output(),FGDPiAvgTime,"",          	NFGDPi); 
  AddVarVF(output(),FGDPiDistance,"",         	NFGDPi);
  AddVarVF(output(),FGDPiMuonangle,"",        	NFGDPi); 
  AddVarVI(output(),FGDPiTId,"",              	NFGDPi);
  AddVarVI(output(),FGDPiIndex,"",            	NFGDPi);
  AddVarVI(output(),FGDPiParentTId,"",        	NFGDPi);
  AddVarVI(output(),FGDPiGParentTId,"",       	NFGDPi);
  AddVarVI(output(),FGDPiVId,"",              	NFGDPi);
  AddVarMF(output(),FGDPiDir,"",              	NFGDPi,-NMAXTPCSEC,3);
  AddVarMF(output(),FGDPiPosStart,"",         	NFGDPi,-NMAXTPCSEC,3);
  AddVarMF(output(),FGDPiPosEnd,"",           	NFGDPi,-NMAXTPCSEC,3);
  AddVarVF(output(),FGDPiTimeIni,"",          	NFGDPi); 
  AddVarVF(output(),FGDPiTimeEnd,"",          	NFGDPi); 
  AddVarVF(output(),FGDPiDeltaTimeIniSelMu,"",	NFGDPi);  
  AddVarVF(output(),FGDPiDeltaTimeEndSelMu,"",	NFGDPi); 
  AddVarVF(output(),TrueFGDPiMom,"",  			NFGDPi);
  AddVarVF(output(),TrueFGDPiCosTheta,"",         NFGDPi);
  // ---- IsoFGD electron and positron tracks -----
  AddVarVF(output(),FGDElLength,"",           	NFGDEl); 
  AddVarVF(output(),FGDElLengthX,"",           	NFGDEl);
  AddVarVF(output(),FGDElPiPull,"",           	NFGDEl); 
  AddVarVF(output(),FGDElAvgTime,"",          	NFGDEl); 
  AddVarVI(output(),FGDElTId,"",              	NFGDEl); 
  AddVarVI(output(),FGDElIndex,"",            	NFGDEl); 
  AddVarVI(output(),FGDElParentTId,"",        	NFGDEl); 
  AddVarVI(output(),FGDElGParentTId,"",       	NFGDEl); 
  AddVarVI(output(),FGDElVId,"",              	NFGDEl);
  AddVarVF(output(),FGDElTimeIni,"",          	NFGDEl);  
  AddVarVF(output(),FGDElTimeEnd,"",          	NFGDEl); 
  AddVarVF(output(),FGDElDeltaTimeIniSelMu,"",	NFGDEl);  
  AddVarVF(output(),FGDElDeltaTimeEndSelMu,"",	NFGDEl); 
  AddVarVF(output(),FGDElDistance,"",         	NFGDEl);
  AddVarVF(output(),FGDElMuonangle,"",        	NFGDEl); 
  AddVarVF(output(),FGDElCosTheta,"",         	NFGDEl);
  AddVarMF(output(),FGDElDir,"",              	NFGDEl,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDElPosStart,"",         	NFGDEl,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDElPosEnd,"",           	NFGDEl,-NMAXFGDSEC,3);
  // ---- IsoFGD tracks -----
  AddVarVF(output(),FGDSecLength,"",           	NFGDSec); 
  AddVarVF(output(),FGDSecLengthX,"",           	NFGDSec); 
  AddVarVF(output(),FGDSecPiPull,"",           	NFGDSec); 
  AddVarVF(output(),FGDSecAvgTime,"",          	NFGDSec); 
  AddVarVI(output(),FGDSecContained,"",        	NFGDSec); 
  AddVarVI(output(),FGDSecTId,"",              	NFGDSec); 
  AddVarVI(output(),FGDSecIndex,"",            	NFGDSec); 
  AddVarVI(output(),FGDSecParentTId,"",        	NFGDSec); 
  AddVarVI(output(),FGDSecGParentTId,"",       	NFGDSec);
  AddVarVF(output(),FGDSecTimeIni,"",          	NFGDSec); 
  AddVarVF(output(),FGDSecTimeEnd,"",          	NFGDSec); 
  AddVarVF(output(),FGDSecDeltaTimeIniSelMu,"",	NFGDSec);  
  AddVarVF(output(),FGDSecDeltaTimeEndSelMu,"",	NFGDSec); 
  AddVarVF(output(),FGDSecCosTheta,"",         	NFGDSec);
  AddVarMF(output(),FGDSecDir,"",              	NFGDSec,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDSecPosStart,"",         	NFGDSec,-NMAXFGDSEC,3);
  AddVarMF(output(),FGDSecPosEnd,"",           	NFGDSec,-NMAXFGDSEC,3);
  AddVarF(output(),FGDSeg_1hit_charge,"");
  AddVarF(output(),FGDSeg_2hit_charge,"");
  AddVar3VF(output(),FGDSeg_1hit_pos,"");
  AddVar3VF(output(),FGDSeg_2hit_pos,"");
  // ---- Michel Eletrons ----
  AddVarVI(output(),MENHits,"",    				NME); 
  AddVarVF(output(),MERawCharge,"",				NME); 
  AddVarVF(output(),MEMinTime,"",  				NME); 
  AddVarVF(output(),MEMaxTime,"",  				NME); 
  // ---- TPC1 Tracks ----
  AddVarVF(output(),TPC1TrackMom,"",       		NTPC1Track); 
  AddVarVF(output(),TPC1TrackPhi,"",       		NTPC1Track);
  AddVarVI(output(),TPC1TrackVId,"",       		NTPC1Track); 
  AddVarVI(output(),TPC1TrackTId,"",       		NTPC1Track); 
  AddVarVI(output(),TPC1TrackParentTId,"", 		NTPC1Track); 
  AddVarVI(output(),TPC1TrackGParentTId,"",		NTPC1Track); 
  AddVarMF(output(),TPC1TrackPosStart,"",  		NTPC1Track,-NMAXTPC1,3); 
  AddVarMF(output(),TPC1TrackPosEnd,"",    		NTPC1Track,-NMAXTPC1,3);
  // --- Info to understand Pion SI -----
  if (_addPionSIinfo){
    AddVarVI(output(),IntType,"", 				NInts); 
    AddVarVI(output(),PionType,"", 				NPions); 
    AddVarVF(output(),PionMom,"", 				NPions); 
  }
  //---- Add new vareables ------
  AddVarI(output(),nTotalPi,"NTotalPi");
  AddVarI(output(),nNegPion,"NNegPion");
  AddVarI(output(),nPosPion,"NPosPion");
  AddVarI(output(),nTPCSec,"NTPCSec");
  AddVarI(output(),nFGDSec,"NFGDSec");
  AddVarI(output(),nFGDPi,"NFGDPi");
  AddVarI(output(),nFGDEl,"NFGDEl");
  AddVarI(output(),nPi0El,"NPi0El");
  AddVarI(output(),nPi0Pos,"NPi0Pos");
  AddVarI(output(),nProtonTPC,"NProtonTPC");
  AddVarI(output(),nProtonFGD,"NProtonFGD");
  AddVarI(output(),nECalPhotons,"NECalPhotons");

  AddVarI(output(),nTPCObjects,"nTPCObjects");
  AddVarI(output(),nECalObjects,"nECalObjects");
  AddVarI(output(),nISOFGDObjects,"nISOFGDObjects");

}

//********************************************************************
void numuCC4piMultiPiAnalysis::DefineTruthTree(){
  //****************************************************************
  baseTrackerAnalysis::DefineTruthTree();
  // ----- Primary and Secondary True Pions-----
  AddVarI(output(),NTruePrim_pi,"");
  AddVarF(output(),TruePrim_pi_mom,"");
  AddVarF(output(),TruePrim_pi_costheta,"");
  AddVar3VF(output(),TruePrim_pi_dir,"");
  AddVarI(output(),TruePrim_pi_id,"");
  AddVarI(output(),TruePrim_pi_pdg,"");

  // ----- Negative and Positive Primary True Pions-----
  AddVarF(output(),TrueNegPionMom,"");
  AddVarF(output(),TrueNegPionCosTheta,"");
  AddVar3VF(output(),TrueNegPionDir,"");
  AddVar3VF(output(),TrueNegPionPosStart,"");
  AddVar3VF(output(),TrueNegPionPosEnd,"");

  AddVarF(output(),TruePosPionMom,"");
  AddVarF(output(),TruePosPionCosTheta,"");
  AddVar3VF(output(),TruePosPionDir,"");
  AddVar3VF(output(),TruePosPionPosStart,"");
  AddVar3VF(output(),TruePosPionPosEnd,"");

  AddVarF(output(),Truemu_mom,"");
  AddVar4VF(output(),Truemu_pos,"");
  AddVar3VF(output(),Truemu_dir,"");
  AddVarF(output(),Truemu_costheta,"");
  AddVarI(output(),Truemu_fgdlayer,"");

  AddVar4VF(output(),Truemu_posend,"");


  // true variable
  AddVarI(output(),true_ntracks,"true_ntracks");
  AddVarI(output(),true_nprotons,"true_nprotons");
  AddVarI(output(),true_npions,"true_npions");


}

//********************************************************************
void numuCC4piMultiPiAnalysis::FillMicroTrees(bool addBase){
  //****************************************************************
  if (addBase) baseTrackerAnalysis::FillMicroTreesBase(addBase);
  int nTotalPi=0, nnegpion=0, npospion=0, ntpcsec=0, nfgdsec=0, nfgdpi=0, nfgdel=0, npi0el=0, npi0pos=0;

  if ( cc4piMultiPibox().MainTrack ){
    if (cc4piMultiPibox().MainTrack->TrueObject) {
      AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(cc4piMultiPibox().MainTrack->GetTrueParticle()->TrueVertex);
      if(vtx) {
        //--------------------------------------------------------------------------------------------------------------------------------
        if( vtx->LeptonPDG == 13){
          output().FillVar(Truemu_mom,                   	vtx->LeptonMom);
          output().FillVectorVarFromArray(Truemu_pos,    	vtx->Position,4);
          output().FillVectorVarFromArray(Truemu_dir,    	vtx->LeptonDir,3);
          AnaTrueParticleB *particle = cc4piMultiPibox().MainTrack->GetTrueParticle();
          output().FillVectorVarFromArray(Truemu_posend,   particle->PositionEnd,4);

          double costheta_mu_nu_true = cos(anaUtils::ArrayToTVector3(vtx->LeptonDir).Angle(anaUtils::ArrayToTVector3(vtx->NuDir)));
          output().FillVar(Truemu_costheta,              	(Float_t)costheta_mu_nu_true);
          output().FillVar(Truemu_fgdlayer,              	numuCC4piMultiPi_utils::GetFgdLayer(vtx->Position, _fgdID));		
        }
        //--------------------------------------------------------------------------------------------------------------------------------
      }
      output().FillVar(selmu_ID,                        cc4piMultiPibox().MainTrack->GetTrueParticle()->ID);
      output().FillVar(selmu_PDG,                       cc4piMultiPibox().MainTrack->GetTrueParticle()->PDG);
      output().FillVar(selmu_truemom,                   cc4piMultiPibox().MainTrack->GetTrueParticle()->Momentum);
      output().FillVectorVarFromArray(selmu_truedir,    cc4piMultiPibox().MainTrack->GetTrueParticle()->Direction, 3);
      TVector3 nuDirVec1 = anaUtils::GetNuDirRec(cc4piMultiPibox().MainTrack->GetTrueParticle()->Position);
      TVector3 muDirVec1 = anaUtils::ArrayToTVector3(cc4piMultiPibox().MainTrack->GetTrueParticle()->Direction);
      double costheta_mu_nu1 = nuDirVec1.Dot(muDirVec1);
      output().FillVar(selmu_truecostheta, 	 		  (Float_t)costheta_mu_nu1);
      output().FillVectorVarFromArray(selmu_truepos,    cc4piMultiPibox().MainTrack->GetTrueParticle()->Position, 4);
      output().FillVectorVarFromArray(selmu_trueendpos, cc4piMultiPibox().MainTrack->GetTrueParticle()->PositionEnd, 4);
      output().FillVar(selmu_truefgdlayer,              numuCC4piMultiPi_utils::GetFgdLayer(cc4piMultiPibox().MainTrack->GetTrueParticle()->Position, _fgdID));
    }

    AnaTrack* track = static_cast<AnaTrack*>( cc4piMultiPibox().MainTrack );

    Float_t hit1_pos[3]; anaUtils::VectorToArray(track->UpstreamHits_Position[0],hit1_pos);
    Float_t hit2_pos[3]; anaUtils::VectorToArray(track->UpstreamHits_Position[1],hit2_pos);
    output().FillVar(selmu_1hit_charge,                track->UpstreamHits_Charge[0]);
    output().FillVar(selmu_2hit_charge,                track->UpstreamHits_Charge[1]);
    output().FillVectorVarFromArray(selmu_1hit_pos,    hit1_pos, 3);
    output().FillVectorVarFromArray(selmu_2hit_pos,    hit2_pos, 3);

    if(_bwd_info){
      Float_t* fit1_pos = numuCC4piMultiPi_utils::GetFittedPos(track->PositionStart, track->PositionEnd, hit1_pos[2] );
      Float_t* fit2_pos = numuCC4piMultiPi_utils::GetFittedPos(track->PositionStart, track->PositionEnd, hit2_pos[2] );

      output().FillVectorVarFromArray(selmu_1hit_fitpos, fit1_pos, 3);
      output().FillVectorVarFromArray(selmu_2hit_fitpos, fit2_pos, 3);
      output().FillVar(selmu_1hit_deltapos,              numuCC4piMultiPi_utils::GetDeltaPos(hit1_pos,fit1_pos) );
      output().FillVar(selmu_2hit_deltapos,              numuCC4piMultiPi_utils::GetDeltaPos(hit2_pos,fit2_pos) );
      output().FillVar(selmu_1hit_deltapos2,             numuCC4piMultiPi_utils::GetDeltaPos2(hit1_pos,fit1_pos) );
      output().FillVar(selmu_2hit_deltapos2,             numuCC4piMultiPi_utils::GetDeltaPos2(hit2_pos,fit2_pos) );		
    }
    if( track->nP0DSegments>0 ) output().FillVar(selmu_pod_nnodes, track->P0DSegments[0]->NNodes);
    for (Int_t subdet = 0; subdet<3; subdet++) {
      if (!SubDetId::GetDetectorUsed(cc4piMultiPibox().MainTrack->Detector, static_cast<SubDetId::SubDetEnum >(subdet+2))) continue;
      AnaTPCParticle* TPCSegment = static_cast<AnaTPCParticle*>(anaUtils::GetSegmentInDet( *cc4piMultiPibox().MainTrack,static_cast<SubDetId::SubDetEnum >(subdet+2)));
      if (!TPCSegment) continue;
      output().FillVectorVar(selmu_tpc_det,subdet);
      output().FillVectorVar(selmu_tpc_nnodes,      TPCSegment->NNodes);
      output().FillVectorVar(selmu_tpc_charge,      TPCSegment->Charge);
      output().FillVectorVar(selmu_tpc_mom,         TPCSegment->Momentum);

      output().IncrementCounterForVar(selmu_tpc_det);
    }
    for (Int_t subdet = 0; subdet<2; subdet++) {
      if (!SubDetId::GetDetectorUsed(cc4piMultiPibox().MainTrack->Detector, static_cast<SubDetId::SubDetEnum >(subdet))) continue;
      AnaFGDParticle* FGDSegment = static_cast<AnaFGDParticle*>(anaUtils::GetSegmentInDet( *cc4piMultiPibox().MainTrack,static_cast<SubDetId::SubDetEnum >(subdet)));
      if (!FGDSegment) continue;
      output().FillVectorVar(selmu_fgd_det,    subdet);
      output().FillVectorVar(selmu_fgd_x,      FGDSegment->X);
      output().FillVectorVar(selmu_fgd_nnodes, FGDSegment->NNodes);
      output().IncrementCounterForVar(selmu_fgd_det);
    }
    for (Int_t subdet = 0; subdet<9; subdet++) {
      if (!SubDetId::GetDetectorUsed(cc4piMultiPibox().MainTrack->Detector, static_cast<SubDetId::SubDetEnum >(subdet+6))) continue;
      AnaECALParticle* ECALSegment = static_cast<AnaECALParticle*>(anaUtils::GetSegmentInDet( *cc4piMultiPibox().MainTrack,static_cast<SubDetId::SubDetEnum >(subdet+6)));
      if (!ECALSegment) continue;
      output().FillVectorVar(selmu_ecal_det,                     subdet);
      output().FillVectorVar(selmu_ecal_nnodes,                  ECALSegment->NNodes);
      output().FillVectorVar(selmu_ecal_length,                  ECALSegment->Length);
      output().FillVectorVar(selmu_ecal_EMenergy,                ECALSegment->EMEnergy);
      output().FillVectorVar(selmu_ecal_mipem,                   ECALSegment->PIDMipEm);
      output().IncrementCounterForVar(selmu_ecal_det);
    }
    EventBoxB* EventBox = (*_event).EventBoxes[EventBoxId::kEventBoxTracker];
    int nTPC=EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithTPC];
    for (Int_t i=0;i<nTPC;i++){
      ntpcsec++;
      AnaTrack* track = static_cast<AnaTrack*>(EventBox->RecObjectsInGroup[EventBoxTracker::kTracksWithTPC][i]);
      if( !track ) continue;  
      if( cc4piMultiPibox().MainTrack == track ) continue;  
      output().FillVectorVar(TPCSec_MomGlobal,      track->Momentum);
      output().FillMatrixVarFromArray(TPCSec_pos,   track->PositionStart,  4);
      output().FillMatrixVarFromArray(TPCSec_endpos,track->PositionEnd,    4);
      output().IncrementCounter(NTPCSec); 
    }
    // Loop over TPC segments
    for (int j = 0; j < track->nTPCSegments; ++j){ 
      AnaTPCParticleB* TPCSegment = track->TPCSegments[j];
      if (!TPCSegment) continue;
      //Float_t ellklh = (anaUtils::GetPIDLikelihood(*track,0)+anaUtils::GetPIDLikelihood(*track,3))/(1.-anaUtils::GetPIDLikelihood(*track,2)); 
      output().FillVectorVar(TPCSecMom,               TPCSegment->Momentum);
      output().FillVectorVar(TPCSecMudEdx,          	TPCSegment->dEdxexpMuon);
      output().FillVectorVar(TPCSecPidEdx,          	TPCSegment->dEdxexpPion);
      output().FillVectorVar(TPCSecPrdEdx,          	TPCSegment->dEdxexpProton);
      output().FillVectorVar(TPCSecEldEdx,          	TPCSegment->dEdxexpEle);
      output().FillVectorVar(TPCSecLikemu,        		anaUtils::GetPIDLikelihood(*track,0));
      output().FillVectorVar(TPCSecLikemip,       		anaUtils::GetPIDLikelihoodMIP(*track));
      //output().FillVectorVar(TPCSecLikemip,       		ellklh);
      output().FillMatrixVarFromArray(TPCSecPosStart, TPCSegment->PositionStart,3);
      output().FillMatrixVarFromArray(TPCSecPosEnd,   TPCSegment->PositionEnd,3);
      output().FillMatrixVarFromArray(TPCSecDir,      TPCSegment->DirectionStart,3);
      output().FillVectorVar(TPCSecQ,1); 
      if( TPCSegment->GetTrueParticle() ){
        output().FillVectorVar(TPCSecTId,       	TPCSegment->GetTrueParticle()->PDG);
        output().FillVectorVar(TPCSecIndex,     	TPCSegment->GetTrueParticle()->ID);
        output().FillVectorVar(TPCSecParentTId, 	TPCSegment->GetTrueParticle()->ParentPDG);
        output().FillVectorVar(TPCSecGParentTId,	TPCSegment->GetTrueParticle()->GParentPDG);
      }
      output().IncrementCounter(NTPCSec); 
    }
  }
  // --- Fill here more variables for the CCMultiPi analysis -----
  if (cc4piMultiPibox().pionBox.nPositivePionTPCtracks > 0. || cc4piMultiPibox().pionBox.nIsoFGDPiontracks > 0.){
    nTotalPi++;
    if ( cc4piMultiPibox().pionBox.nPositivePionTPCtracks == 1. || cc4piMultiPibox().pionBox.nPositivePionTPCtracks == 2.){
      AnaTrackB* tracktpc = cc4piMultiPibox().pionBox.PositivePionTPCtracks[0];	
      output().FillVectorVarFromArray(selpi_dir,      tracktpc->DirectionStart,3); 
      if( tracktpc->GetTrueParticle() ){
        output().FillVar(selpi_ID,            		tracktpc->GetTrueParticle()->PDG);
      }
    }
    if ( cc4piMultiPibox().pionBox.nIsoFGDPiontracks == 1. || cc4piMultiPibox().pionBox.nIsoFGDPiontracks == 2.){
      AnaTrackB* track =  cc4piMultiPibox().pionBox.IsoFGDPiontracks[0];
      //AnaTrack* isoTrack = static_cast<AnaTrack*>(cc4piMultiPibox().pionBox.IsoFGDPiontracks[0]);
      AnaFGDParticle* fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[0]);
      output().FillVectorVarFromArray(selpi_dir,      fgdTrack->DirectionStart,3); 
      if( track->GetTrueParticle() ){
        output().FillVar(selpi_ID,       			track->GetTrueParticle()->PDG);
      }
    }
  }

  // Selected positive pions 
  for( Int_t i = 0; i <cc4piMultiPibox().pionBox.nPositivePionTPCtracks; i++ ){
    npospion++;
    AnaTrackB *track = cc4piMultiPibox().pionBox.PositivePionTPCtracks[i];
    Float_t ellklh = (anaUtils::GetPIDLikelihood(*track,0)+anaUtils::GetPIDLikelihood(*track,3))/(1.-anaUtils::GetPIDLikelihood(*track,2)); 	
    output().FillVectorVar(PosPionMom,      track->Momentum); 
    output().FillVectorVar(PosPionCosTheta, (Float_t)(track->DirectionStart[2]));   
    output().FillVectorVar(PosPionPidLik,   anaUtils::GetPIDLikelihood(*track,3));    
    output().FillVectorVar(PosPionPull,   	ellklh);
    if( track->TrueObject ){
      output().FillVectorVar(PosPionTId,  track->GetTrueParticle()->PDG);
      output().FillVectorVar(PosPionIndex,track->GetTrueParticle()->ID); 
      output().FillVectorVar(PosPionParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(PosPionGParentTId,track->GetTrueParticle()->GParentPDG);  
      AnaTrueVertex *vtxPi = static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex);
      if (track->GetTrueParticle()->PDG == 211){
        if (vtxPi) {
          output().FillVectorVar(TruePosPionMom,      vtxPi->PionMom); 
          double costheta_ppi_nu_true = cos(anaUtils::ArrayToTVector3(vtxPi->PionDir).Angle(anaUtils::ArrayToTVector3(vtxPi->NuDir)));
          output().FillVectorVar(TruePosPionCosTheta,        (Float_t)costheta_ppi_nu_true); 
          output().FillVectorVarFromArray(TruePosPionDir,     vtxPi->PionDir, 3);
        }
      }
    }
    output().FillMatrixVarFromArray(PosPionPosStart, track->PositionStart, 3); 
    output().FillMatrixVarFromArray(PosPionPosEnd,   track->PositionEnd,3);
    output().FillMatrixVarFromArray(PosPionDir,      track->DirectionStart,3); // Use PosPionTheta to access the angle, it is fille in FillToyVarsInMicroTree
    output().IncrementCounter(NPosPion);
  }

  // Selected negative pions 
  for( Int_t i = 0; i < cc4piMultiPibox().pionBox.nNegativePionTPCtracks; i++ ){
    nnegpion++;
    AnaTrackB *track = cc4piMultiPibox().pionBox.NegativePionTPCtracks[i];
    Float_t ellklh = (anaUtils::GetPIDLikelihood(*track,0)+anaUtils::GetPIDLikelihood(*track,3))/(1.-anaUtils::GetPIDLikelihood(*track,2)); 
    output().FillVectorVar(NegPionMom,      track->Momentum); 
    output().FillVectorVar(NegPionCosTheta, (Float_t)(track->DirectionStart[2])); 
    output().FillVectorVar(NegPionPidLik,   anaUtils::GetPIDLikelihood(*track,3));    
    output().FillVectorVar(NegPionPull,   	ellklh);
    if( track->TrueObject ){
      output().FillVectorVar(NegPionTId,  track->GetTrueParticle()->PDG);
      output().FillVectorVar(NegPionIndex,track->GetTrueParticle()->ID); 
      output().FillVectorVar(NegPionParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(NegPionGParentTId,track->GetTrueParticle()->GParentPDG); 
    }
    output().FillMatrixVarFromArray(NegPionPosStart, track->PositionStart, 3);
    output().FillMatrixVarFromArray(NegPionPosEnd,   track->PositionEnd,3);
    output().FillMatrixVarFromArray(NegPionDir,      track->DirectionStart,3);
    output().IncrementCounter(NNegPion);
  }
  // Selected ecal pions 
  for(Int_t i = 0; i < cc4piMultiPibox().pionBox.nECalPiontracks; i++){
    AnaTrackB* track = cc4piMultiPibox().pionBox.ECalPiontracks[i];
    output().FillVectorVar(selpi_ecal_costheta, 				(Float_t)(track->DirectionStart[2]));  
    if( track->GetTrueParticle() ){
      output().FillVectorVar(selpi_ecal_pdg,       			track->GetTrueParticle()->PDG);
      output().FillVectorVar(selpi_ecal_id,   				track->GetTrueParticle()->ID);	    	
    }
    for (Int_t subdet = 0; subdet<9; subdet++) {
      AnaECALParticle* ECALSegment = static_cast<AnaECALParticle*>(anaUtils::GetSegmentInDet( *track,static_cast<SubDetId::SubDetEnum >(subdet+6)));
      if (!ECALSegment) continue;
      output().FillVectorVar(selpi_ecal_det,                     subdet);
      output().FillVectorVar(selpi_ecal_nnodes,                  ECALSegment->NNodes);
      output().FillVectorVar(selpi_ecal_length,                  ECALSegment->Length);
      output().FillVectorVar(selpi_ecal_EMenergy,                ECALSegment->EMEnergy);
      output().FillVectorVar(selpi_ecal_mipem,                   ECALSegment->PIDMipEm);
      output().FillVectorVar(selpi_ecal_mippion,                 ECALSegment->PIDMipPion);
      output().IncrementCounterForVar(selpi_ecal_det);
    }
    output().IncrementCounter(selpi_necals); 
  }

  // Selected pi0 electron tracks 
  for( Int_t i = 0; i < cc4piMultiPibox().pionBox.nElPi0TPCtracks; i++ ) {
    npi0el++;
    AnaTrackB *track = cc4piMultiPibox().pionBox.ElPi0TPCtracks[i];
    output().FillVectorVar(Pi0ElMom, track->Momentum);
    output().FillVectorVar(Pi0ElPull, anaUtils::GetPIDLikelihood(*track,1)); 
    if( track->GetTrueParticle() ){
      output().FillVectorVar(Pi0ElTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(Pi0ElIndex,     track->GetTrueParticle()->ID);
      output().FillVectorVar(Pi0ElParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(Pi0ElGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex  ){
        output().FillVectorVar(Pi0ElVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
      }
    } 
    output().FillMatrixVarFromArray(Pi0ElPosStart, track->PositionStart,3);
    output().FillMatrixVarFromArray(Pi0ElPosEnd,   track->PositionEnd,3);
    output().FillMatrixVarFromArray(Pi0ElDir,      track->DirectionStart,3);
    output().IncrementCounter(NPi0El);
  }
  // Selected pi0 positron tracks 
  for( Int_t i = 0; i < cc4piMultiPibox().pionBox.nPosPi0TPCtracks; i++ ) {
    npi0pos++;
    AnaTrackB *track = cc4piMultiPibox().pionBox.PosPi0TPCtracks[i];
    output().FillVectorVar(Pi0PosMom, track->Momentum);
    output().FillVectorVar(Pi0PosPull, anaUtils::GetPIDLikelihood(*track,1)); 
    if( track->GetTrueParticle() ){
      output().FillVectorVar(Pi0PosTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(Pi0PosIndex,     track->GetTrueParticle()->ID);
      output().FillVectorVar(Pi0PosParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(Pi0PosGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex  ){
        output().FillVectorVar(Pi0PosVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
      }
    } 
    output().FillMatrixVarFromArray(Pi0PosPosStart, track->PositionStart, 3);
    output().FillMatrixVarFromArray(Pi0PosPosEnd,   track->PositionEnd,   3);
    output().FillMatrixVarFromArray(Pi0PosDir,      track->DirectionStart,3);
    output().IncrementCounter(NPi0Pos);
  }
  // isoFGD pion candidates 
  for (Int_t i=0; i < cc4piMultiPibox().pionBox.nIsoFGDPiontracks; i++){
    nfgdpi++;
    AnaTrackB* track =  cc4piMultiPibox().pionBox.IsoFGDPiontracks[i];
    AnaTrack* isoTrack = static_cast<AnaTrack*>(cc4piMultiPibox().pionBox.IsoFGDPiontracks[i]);
    AnaFGDParticle *fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[0]);
    if( !fgdTrack ) continue; 
    ///checking times
    Float_t timeinipi = fgdTrack->PositionStart[3];
    Float_t timeendpi = fgdTrack->PositionEnd[3];
    output().FillVectorVar(FGDPiPiPull,  fgdTrack->Pullpi); 
    output().FillVectorVar(FGDPiAvgTime, fgdTrack->AvgTime); 
    // Direction of the segment 
    output().FillVectorVar(FGDPiMomRangeOarecon, isoTrack->RangeMomentumMuon);
    output().FillVectorVar(FGDPiCosTheta,(Float_t)(anaUtils::ArrayToTVector3(fgdTrack->DirectionStart).CosTheta()));
    TVector3 nuDirVec = anaUtils::GetNuDirRec(fgdTrack->PositionStart);
    TVector3 muDirVec = anaUtils::ArrayToTVector3(fgdTrack->DirectionStart);
    TVector3 ppiDirVec = anaUtils::ArrayToTVector3(fgdTrack->DirectionStart);
    Float_t costheta_mu_pi = ppiDirVec.Dot(muDirVec);
    output().FillVectorVar(FGDPiMuonangle,(Float_t)costheta_mu_pi);
    output().FillVectorVar(FGDPiLength,fgdTrack->Length); 
    output().FillVectorVar(FGDPiLengthX,  fgdTrack->X); 
    output().FillVectorVar(FGDPiTimeIni, timeinipi);  
    output().FillVectorVar(FGDPiTimeEnd, timeendpi); 
    output().FillMatrixVarFromArray(FGDPiDir,     fgdTrack->DirectionStart,3);
    output().FillMatrixVarFromArray(FGDPiPosStart,fgdTrack->PositionStart, 3);
    output().FillMatrixVarFromArray(FGDPiPosEnd,  fgdTrack->PositionEnd,   3);
    if( track->TrueObject){
      output().FillVectorVar(FGDPiTId,       track->GetTrueParticle()->PDG);
      output().FillVectorVar(FGDPiIndex,     track->GetTrueParticle()->ID); 
      output().FillVectorVar(FGDPiParentTId, track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(FGDPiGParentTId,track->GetTrueParticle()->GParentPDG);
      AnaTrueVertex *vtxPi = static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex);
      if (track->GetTrueParticle()->PDG == 211){
        if (vtxPi) {
          output().FillVectorVar(TrueFGDPiMom,      	vtxPi->PionMom); 
          double costheta_ppi_nu_true_fgd = cos(anaUtils::ArrayToTVector3(vtxPi->PionDir).Angle(anaUtils::ArrayToTVector3(vtxPi->NuDir)));
          output().FillVectorVar(TrueFGDPiCosTheta, 	(Float_t)costheta_ppi_nu_true_fgd); 	
          output().FillVectorVar(FGDPiVId, 			vtxPi->RooVtxIndex);
        }
      }
    }
    if( cc4piMultiPibox().HMNtrack ) { 
      Float_t deltainimuinipi = TMath::Abs(timeinipi-cc4piMultiPibox().HMNtrack->PositionStart[3]);
      Float_t deltaendmuinipi = TMath::Abs(timeendpi-cc4piMultiPibox().HMNtrack->PositionStart[3]); 
      output().FillVectorVar(FGDPiDeltaTimeIniSelMu,deltainimuinipi);  
      output().FillVectorVar(FGDPiDeltaTimeEndSelMu,deltaendmuinipi); 
      // Minimum distance to the muon vertex 
      Float_t dist1 = (anaUtils::ArrayToTVector3(fgdTrack->PositionStart) - anaUtils::ArrayToTVector3(cc4piMultiPibox().HMNtrack->PositionStart)).Mag();
      Float_t dist2 = (anaUtils::ArrayToTVector3(fgdTrack->PositionEnd)   - anaUtils::ArrayToTVector3(cc4piMultiPibox().HMNtrack->PositionStart)).Mag();
      output().FillVectorVar(FGDPiDistance,TMath::Min(dist1,dist2)); 
    }
    output().IncrementCounter(NFGDPi);
  }
  // isoFGD electron and positron candidates 
  for (Int_t i=0;i < cc4piMultiPibox().pionBox.nIsoFGDElPi0tracks;i++){
    nfgdel++;
    AnaTrackB* track =  cc4piMultiPibox().pionBox.IsoFGDElPi0tracks[i];
    AnaFGDParticle *fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[0]);
    if( !fgdTrack ) continue; 
    Float_t timeiniEl = fgdTrack->PositionStart[3];
    Float_t timeendEl = fgdTrack->PositionEnd[3];
    output().FillVectorVar(FGDElCosTheta,(Float_t)(anaUtils::ArrayToTVector3(fgdTrack->DirectionStart).CosTheta()));
    output().FillVectorVar(FGDElPiPull,fgdTrack->Pullpi); 
    output().FillVectorVar(FGDElAvgTime,fgdTrack->AvgTime); 
    output().FillVectorVar(FGDElLength,fgdTrack->Length); 
    output().FillVectorVar(FGDElLengthX,fgdTrack->X); 
    output().FillVectorVar(FGDElTimeIni,timeiniEl);  
    output().FillVectorVar(FGDElTimeEnd,timeendEl); 
    //  Minimum distance to the muon vertex 
    if( cc4piMultiPibox().HMNtrack ) {
      Float_t deltainimuiniEl = TMath::Abs(timeiniEl-cc4piMultiPibox().HMNtrack->PositionStart[3]);
      Float_t deltaendmuiniEl = TMath::Abs(timeendEl-cc4piMultiPibox().HMNtrack->PositionStart[3]);
      Float_t dist1 = (anaUtils::ArrayToTVector3(fgdTrack->PositionStart) - anaUtils::ArrayToTVector3(cc4piMultiPibox().HMNtrack->PositionStart)).Mag();
      Float_t dist2 = (anaUtils::ArrayToTVector3(fgdTrack->PositionEnd)   - anaUtils::ArrayToTVector3(cc4piMultiPibox().HMNtrack->PositionStart)).Mag();
      Float_t prodEl1 = anaUtils::ArrayToTVector3(fgdTrack->DirectionStart)*anaUtils::ArrayToTVector3(cc4piMultiPibox().HMNtrack->DirectionStart); 
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
      if( track->GetTrueParticle()->TrueVertex ){
        output().FillVectorVar(FGDElVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
      }
    }
    output().IncrementCounter(NFGDEl); 
  }
  // All FGD tracks. 
  AnaRecObjectC** allFGDParticles = NULL;
  int nFGD=0;
  if (_fgdID == SubDetId::kFGD1){
    nFGD         = _event->EventBoxes[EventBoxId::kEventBoxTracker]->nRecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC];
    allFGDParticles = _event->EventBoxes[EventBoxId::kEventBoxTracker]->RecObjectsInGroup[EventBoxTracker::kTracksWithFGD1AndNoTPC];  
  }
  else if (_fgdID == SubDetId::kFGD2){
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
    if( cc4piMultiPibox().HMNtrack ) {
      Float_t deltainimuini = TMath::Abs(timeini-cc4piMultiPibox().HMNtrack->PositionStart[3]);
      Float_t deltaendmuini = TMath::Abs(timeend-cc4piMultiPibox().HMNtrack->PositionStart[3]);
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
    output().FillVectorVar(FGDSecAvgTime,          fgdTrack->AvgTime); 
    output().FillVectorVar(FGDSecLengthX,          fgdTrack->X); 
    output().FillVectorVar(FGDSecLength,           fgdTrack->Length); 
    output().IncrementCounter(NFGDSec); 	 
    AnaTrack* track_hits = static_cast<AnaTrack*>(allFGDParticles[i]);
    Float_t hit1_pos[3]; anaUtils::VectorToArray(track_hits->UpstreamHits_Position[0],hit1_pos);
    Float_t hit2_pos[3]; anaUtils::VectorToArray(track_hits->UpstreamHits_Position[1],hit2_pos);
    // Float_t* fit1_pos = numuCC4piMultiPi_utils::GetFittedPos(track_hits->PositionStart, track_hits->PositionEnd, hit1_pos[2] );
    // Float_t* fit2_pos = numuCC4piMultiPi_utils::GetFittedPos(track_hits->PositionStart, track_hits->PositionEnd, hit2_pos[2] );
    output().FillVar(FGDSeg_1hit_charge,                track_hits->UpstreamHits_Charge[0]);
    output().FillVar(FGDSeg_2hit_charge,                track_hits->UpstreamHits_Charge[1]);
    output().FillVectorVarFromArray(FGDSeg_1hit_pos,    hit1_pos, 3);
    output().FillVectorVarFromArray(FGDSeg_2hit_pos,    hit2_pos, 3);
    // output().FillVectorVarFromArray(FGDSeg_1hit_fitpos, fit1_pos, 3);
    // output().FillVectorVarFromArray(FGDSeg_2hit_fitpos, fit2_pos, 3);
  }
  // Retrieve the EventBox such that we can get the number of michel electrons
  EventBoxTracker* EventBox = static_cast<EventBoxTracker*>(_event->EventBoxes[EventBoxId::kEventBoxTracker]);
  SubDetId::SubDetEnum det = static_cast<SubDetId::SubDetEnum>(cc4piMultiPibox().DetectorFV);
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
  if (cc4piMultiPibox().DetectorFV == SubDetId::kFGD1) tpc = SubDetId::kTPC1;  
  AnaTrackB** TPCtracks;
  anaUtils::CreateArray(TPCtracks, NMAXPARTICLES);
  Int_t nTPCtracks = FindTPCTracks(cc4piMultiPibox(), tpc, TPCtracks);
  for( Int_t i = 0; i < nTPCtracks; i++ ) {
    AnaTrackB *track = TPCtracks[i];
    if( !track ) continue;
    Float_t phi=TMath::ATan2(track->DirectionStart[1],track->DirectionStart[0]);
    output().FillVectorVar(TPC1TrackPhi,phi );
    if( track->GetTrueParticle() ){
      output().FillVectorVar(TPC1TrackTId,track->GetTrueParticle()->PDG);
      output().FillVectorVar(TPC1TrackParentTId,track->GetTrueParticle()->ParentPDG);
      output().FillVectorVar(TPC1TrackGParentTId,track->GetTrueParticle()->GParentPDG);
      if( track->GetTrueParticle()->TrueVertex )	{
        output().FillVectorVar(TPC1TrackVId,static_cast<AnaTrueVertex*>(track->GetTrueParticle()->TrueVertex)->RooVtxIndex);
      }
    }
    output().FillMatrixVarFromArray(TPC1TrackPosStart,track->PositionStart,3);
    output().FillMatrixVarFromArray(TPC1TrackPosEnd,  track->PositionEnd,  3);
    output().FillVectorVar(TPC1TrackMom, track->Momentum);
    output().IncrementCounter(NTPC1Track);
  }

  delete TPCtracks;
  // --- Info to understand Pion SI -----
  if (_addPionSIinfo){
    PionInteractionSystematic* pionSI = _pionSIManager->ComputePionWeightInfo(GetEvent(), cc4piMultiPibox().DetectorFV);

    for(int ii = 0; ii < pionSI->nInteractions; ii++){
      int intType = pionSI->typeInteraction[ii];          
      int mech;
      if (intType%10 == 0) mech = 0;
      else if (intType%10 == 1) mech = 1;
      else if (intType%10 == 4) mech = 2;
      else mech=-1;
      output().FillVectorVar(IntType,mech);
      output().IncrementCounter(NInts);
    }
    for(int ns = 0; ns < pionSI->nPions; ns++){
      output().FillVectorVar(PionType,pionSI->pionType[ns]);
      output().FillVectorVar(PionMom,pionSI->initMom[ns]);
      output().IncrementCounter(NPions);
    }
  }
  output().FillVar(nNegPion,nnegpion);
  output().FillVar(nPosPion,npospion);
  output().FillVar(nTPCSec,ntpcsec);
  output().FillVar(nFGDSec,nfgdsec);
  output().FillVar(nFGDPi,nfgdpi);
  output().FillVar(nFGDEl,nfgdel);
  output().FillVar(nPi0El,npi0el);
  output().FillVar(nPi0Pos,npi0pos);	
  output().FillVar(nProtonTPC,cc4piMultiPibox().pionBox.nProtonTPCtracks);	
  output().FillVar(nProtonFGD,cc4piMultiPibox().pionBox.nProtonFGDtracks);	
  output().FillVar(nECalPhotons,cc4piMultiPibox().pionBox.nECalPhotons);	

  for( Int_t i = 0; i < cc4piMultiPibox().pionBox.nProtonTPCtracks; i++ )
  {
    AnaTrackB *track = cc4piMultiPibox().pionBox.ProtonTPCtracks[i];

    output().FillVectorVar(TPCProtMom, track->Momentum);
    output().FillVectorVar(proton_is_flippedTPC, track->GetIsFlipped());

    if( track->GetTrueParticle() )
    {
      output().FillVectorVar(TPCProtonTId,       track->GetTrueParticle()->PDG);
    }
    output().IncrementCounter(nProtonsTPC);        
  }
  //filling FGD proton information
  for( Int_t i = 0; i < cc4piMultiPibox().pionBox.nProtonFGDtracks; i++ )
  {
    AnaTrackB *track = cc4piMultiPibox().pionBox.ProtonFGDtracks[i];
    output().FillVectorVar(FGDProtMom, track->RangeMomentumProton);
    // output().FillVectorVar(proton_is_flippedFGD, track->Is_ToF_Flipped);

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
    AnaTrueVertex *vtxProt = static_cast<AnaTrueVertex*>(cc4piMultiPibox().MainTrack->GetTrueParticle()->TrueVertex);
    for(int i = 0; i<vtxProt->nTrueParticles; i++)
    {
      if( vtxProt->TrueParticles[i]->PDG == 2212 && vtxProt->TrueParticles[i]->ParentPDG == 0 ) 
      {
        nprotons++; 
      }
    }
  }

  EventBoxTracker::RecObjectGroupEnum groupID;
  EventBoxTracker::RecObjectGroupEnum IsoFGDgroupID;

  if (det == SubDetId::kFGD1) groupID = EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD1;
  else groupID = EventBoxTracker::kTracksWithGoodQualityTPCWithStartOrEndInFGD2;


  int nTPCObjects_evt = EventBox->nRecObjectsInGroup[groupID];
  int nECalObjects_evt =EventBox->nRecObjectsInGroup[EventBoxTracker::kTracksWithECal];

  if      (det == SubDetId::kFGD1) IsoFGDgroupID = EventBoxTracker::kTracksWithFGD1AndNoTPC;
  else IsoFGDgroupID = EventBoxTracker::kTracksWithFGD2AndNoTPC;

  int nISOFGDObjects_evt = 0;
  // Get Number of ISO FGD tracks
  for(int i = 0; i < EventBox->nRecObjectsInGroup[IsoFGDgroupID]; i++ ) {
    AnaTrackB *ptrack = static_cast<AnaTrackB*>(EventBox->RecObjectsInGroup[IsoFGDgroupID][i]);
    if (!ptrack) continue;
    // Check if is FGD contained
    if (anaUtils::TrackUsesOnlyDet(*ptrack, det)) nISOFGDObjects_evt++; 
  }


  output().FillVar(nTPCObjects,    		 			nTPCObjects_evt );
  output().FillVar(nECalObjects,   		 			nECalObjects_evt );
  output().FillVar(nISOFGDObjects,    		  nISOFGDObjects_evt );



}

//********************************************************************
void numuCC4piMultiPiAnalysis::FillToyVarsInMicroTrees(bool addBase){
  //****************************************************************

#ifdef DEBUG
  // raise(SIGSEGV);
#endif
  if (addBase) baseTrackerAnalysis::FillToyVarsInMicroTreesBase(addBase);
  if ( cc4piMultiPibox().MainTrack ){
    output().FillToyVar(NLowAngle,    		 			(int)cc4piMultiPibox().LowAngle.size() );
    output().FillToyVar(NHighAngle,   		 			(int)cc4piMultiPibox().HighAngle.size() );
    output().FillToyVar(NFwdMuLike,    		 			(int)cc4piMultiPibox().FwdTracks.size() );
    output().FillToyVar(NBwdMuLike,    		 			(int)cc4piMultiPibox().BwdTracks.size() );
    output().FillToyVar(NHAFwdMuLike,   		 		(int)cc4piMultiPibox().HAFwdTracks.size() );
    output().FillToyVar(NHABwdMuLike,    		 		(int)cc4piMultiPibox().HABwdTracks.size() );
    AnaTrack* track = static_cast<AnaTrack*>(cc4piMultiPibox().MainTrack );
    output().FillVar(selmu_fgdlayer,                   numuCC4piMultiPi_utils::GetFgdLayer(track->PositionStart, _fgdID));

    output().FillToyVar(selmu_mom,           		 	track->Momentum);

    output().FillVar(selmu_HMNT,          			   numuCC4piMultiPi_utils::isHMNT(cc4piMultiPibox().MainTrack,cc4piMultiPibox().LowAngle,true, _fgdID));
    output().FillVar(selmu_likemu,        			   anaUtils::GetPIDLikelihood( *(cc4piMultiPibox().MainTrack),0));
    output().FillVar(selmu_likemip,       			   anaUtils::GetPIDLikelihoodMIP( *(cc4piMultiPibox().MainTrack)));
    output().FillVar(selmu_end_ecal,      			   cutUtils::StoppingBrECALorSMRDCut(track->PositionEnd));
    output().FillVar(selmu_ToF_PoD,       			   track->ToF.P0D_FGD1);
    output().FillVar(selmu_ToF_ECAL,      		  	   track->ToF.ECal_FGD1);
    output().FillVar(selmu_ToF_FGD2,      		  	   track->ToF.FGD1_FGD2);

    ToFSenseCorrector::ToFTopology topologies[ToFSenseCorrector::kToFInvalid];
    Int_t count = ToFSenseCorrector::GetToFTopologies(*track, topologies);
    Float_t track_topology[4] = {-999, -999, -999, -999};
    if (count > 0) {
      // std::cout << "Warning! More than one tof topology detected in this track" << std::endl;
      for (int i = 0; i < min(count, 4); i++){
        // std::cout << topologies[i] << std::endl;
        track_topology[i] = float(topologies[i]);
        // std::cout << track_topology[i] << std::endl;
      }
    }
    output().FillVectorVarFromArray(selmu_ToF_topology,         track_topology, 4);
    if (track->GetIsFlipped()){
      output().FillVar(selmu_is_flipped,         1);
    }
    else{
      output().FillVar(selmu_is_flipped,         0);
    }
    output().FillVar(selmu_detectors,                  track->Detectors);
    output().FillVar(selmu_charge,                     track->Charge);

    output().FillVectorVarFromArray(selmu_dir,         track->DirectionStart, 3);

    output().FillVectorVarFromArray(selmu_enddir,         track->DirectionEnd, 3);

    output().FillVectorVarFromArray(selmu_pos,         track->PositionStart, 4);
    output().FillVectorVarFromArray(selmu_endpos,      track->PositionEnd, 4);
    TVector3 nuDirVec = anaUtils::GetNuDirRec(track->PositionStart);
    TVector3 muDirVec = anaUtils::ArrayToTVector3(track->DirectionStart);
    Float_t costheta_mu_nu = nuDirVec.Dot(muDirVec);
    output().FillToyVar(selmu_costheta, 	 			(Float_t)costheta_mu_nu);
    output().FillToyVar(selmu_direction2, 	 			(Float_t)track->DirectionStart[2]);

    float nuVec[] = { static_cast<float>(nuDirVec.X()), 
      static_cast<float>(nuDirVec.Y()), 
      static_cast<float>(nuDirVec.Z())};

    double muVec[] = {muDirVec.X(), muDirVec.Y(), muDirVec.Z()};
    output().FillVectorVarFromArray(selmu_nuvec,         nuVec, 3);
    output().FillVectorVarFromArray(selmu_muvec,         muVec, 3);


    output().FillToyVar(selmu_mom_range_oarecon, 		track->RangeMomentumMuon);
  }

  if (cc4piMultiPibox().pionBox.nPositivePionTPCtracks > 0. || cc4piMultiPibox().pionBox.nIsoFGDPiontracks > 0.){
    if ( cc4piMultiPibox().pionBox.nPositivePionTPCtracks == 1. || cc4piMultiPibox().pionBox.nPositivePionTPCtracks == 2.){
      AnaTrackB* tracktpc = cc4piMultiPibox().pionBox.PositivePionTPCtracks[0];	
      output().FillToyVar(selpi_mom,      				tracktpc->Momentum); 
      // output().FillToyVar(selpi_is_flipped,   tracktpc->Is_ToF_Flipped); 
      // if (tracktpc->Is_ToF_Flipped){
      //       output().FillVar(proton_is_flippedTPC,         1);
      // }
      // else{
      //       output().FillVar(proton_is_flippedTPC,         0);
      // }

      output().FillToyVar(selpi_costheta, 				(Float_t)(tracktpc->DirectionStart[2]));   
      Float_t ellklh = (anaUtils::GetPIDLikelihood(*tracktpc,3))/(1.-anaUtils::GetPIDLikelihood(*tracktpc,0)); 	
      output().FillToyVar(selpi_pull,   					ellklh);
    }
    if ( cc4piMultiPibox().pionBox.nIsoFGDPiontracks == 1. || cc4piMultiPibox().pionBox.nIsoFGDPiontracks == 2.){
      AnaTrackB* track =  cc4piMultiPibox().pionBox.IsoFGDPiontracks[0];
      AnaTrack* isoTrack = static_cast<AnaTrack*>(cc4piMultiPibox().pionBox.IsoFGDPiontracks[0]);
      AnaFGDParticle* fgdTrack = static_cast<AnaFGDParticle*>(track->FGDSegments[0]);
      output().FillToyVar(selpi_mom,               		isoTrack->RangeMomentumMuon);
      // output().FillToyVar(selpi_is_flipped,      	    isoTrack->Is_ToF_Flipped); 
      // if (isoTrack->Is_ToF_Flipped){
      //       output().FillVar(proton_is_flippedFGD,         1);
      // }
      // else{
      //       output().FillVar(proton_is_flippedFGD,         0);
      // }
      output().FillToyVar(selpi_costheta,          		(Float_t)(anaUtils::ArrayToTVector3(fgdTrack->DirectionStart).CosTheta()));
      Float_t ellklh = (anaUtils::GetPIDLikelihood(*isoTrack,3))/(1.-anaUtils::GetPIDLikelihood(*isoTrack,0)); 	
      output().FillToyVar(selpi_pull,   					ellklh);
    }
  }

  // Fill whether it is signal or bkg
  // Filled also in numuCCAnalysis, overwritten here
  if(cc4piMultiPibox().MainTrack && cc4piMultiPibox().MainTrack->TrueObject) {
    AnaTrueVertex *vtx = static_cast<AnaTrueVertex*>(cc4piMultiPibox().MainTrack->GetTrueParticle()->TrueVertex);
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
}

//********************************************************************
void numuCC4piMultiPiAnalysis::FillTruthTree(const AnaTrueVertex& vtx){

  //****************************************************************
#ifdef DEBUG
  // raise(SIGSEGV);
#endif
  baseTrackerAnalysis::FillTruthTreeBase(vtx, _fgdID, false);
  // std::cout << "baseTrackerAnalysis::FillTruthTreeBase" << std::endl;
  // Fill truth categories for FGD2, same categories with prefix "fgd2", i,e, "fgd2reaction" etc.
  // We could directly set which FGD in the usual categories, but this is not possible for the true vertices
  // anaUtils::FillCategories(&vtx, "fgd2", SubDetId::kFGD2, IsAntinu,GetSpill().GetIsSandMC());
  // Fill whether it is signal or bkg Filled also in numuCCAnalysis, overwritten here
  int ts = 0; // BKG
              // in FGD1 FV
  if (anaUtils::GetTopology(vtx, SubDetId::kFGD1) == 0) ts = 10;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD1) == 1) ts = 11;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD1) == 2) ts = 12;
  // in FGD2 FV
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD2) == 0) ts = 20;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD2) == 1) ts = 21;
  else if (anaUtils::GetTopology(vtx, SubDetId::kFGD2) == 2) ts = 22;

  int nprotons = 0, npions = 0;
  for(int i = 0; i<vtx.nTrueParticles; i++){
    //std::cout<<"pdg : "<< vtx.TrueParticles[i]->PDG <<std::endl;
    if( vtx.TrueParticles[i]->PDG == 2212 && vtx.TrueParticles[i]->ParentPDG == 0 ) nprotons++;
    if( ( vtx.TrueParticles[i]->PDG == 211 || vtx.TrueParticles[i]->PDG == -211 )&& vtx.TrueParticles[i]->ParentPDG == 0 ) npions++;
  }
  output().FillVar(true_signal,ts);
  output().FillVar(true_nprotons,nprotons);
  output().FillVar(true_npions,npions);
  output().FillVar(true_ntracks,vtx.nTrueParticles);

  // Variables for true pion
  // Explicitely order pions in momentum and get the primary one most energetic
  // This is to work for pi- as well (vtx.PionMom was filled with pi+ as for
  // IRODs flat-trees for Oct 2017)
  if (vtx.NPrimaryParticles[ParticleId::kPions] > 0){
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
      output().FillVar(TruePrim_pi_mom, 						particles[0]->Momentum);
      output().FillVar(TruePrim_pi_costheta,  				(Float_t)particles[0]->Direction[2]);
      output().FillVectorVarFromArray(TruePrim_pi_dir, 		particles[0]->Direction, 3);
      output().FillVar(TruePrim_pi_id, 						particles[0]->ID);
      output().FillVar(TruePrim_pi_pdg, 						particles[0]->PDG);
      output().IncrementCounter(NTruePrim_pi); 
      if (particles[0]->PDG == 211){
        output().FillVar(TruePosPionMom,             		particles[0]->Momentum);
        output().FillVar(TruePosPionCosTheta,         		(Float_t)particles[0]->Direction[2]);
        output().FillVectorVarFromArray(TruePosPionDir,     particles[0]->Direction, 3);
        output().FillVectorVarFromArray(TruePosPionPosStart,particles[0]->Position,3); 
        output().FillVectorVarFromArray(TruePosPionPosEnd,  particles[0]->PositionEnd,3);	
        output().IncrementCounterForVar(NTruePosPion);
      }
      if (particles[0]->PDG == -211){
        output().FillVar(TrueNegPionMom,              		particles[0]->Momentum);
        output().FillVar(TrueNegPionCosTheta,         		(Float_t)particles[0]->Direction[2]);
        output().FillVectorVarFromArray(TrueNegPionDir,     particles[0]->Direction, 3);
        output().FillVectorVarFromArray(TrueNegPionPosStart,particles[0]->Position,3); 
        output().FillVectorVarFromArray(TrueNegPionPosEnd,  particles[0]->PositionEnd,3);
        output().IncrementCounterForVar(NTrueNegPion);
      }
    }
  }
  if (vtx.NPrimaryParticles[ParticleId::kMuon] > 0){
    AnaTrueParticleB* trk = NULL;
    std::vector<AnaTrueParticleB*> particles(vtx.NPrimaryParticles[ParticleId::kMuon], NULL);
    int count = 0; 
    for (int it=0; it<vtx.nTrueParticles; it++) {
      trk = vtx.TrueParticles[it];
      if (!trk) continue;
      if (trk->PDG != 13) continue;
      if (trk->ParentID !=0) continue;
      if (count >= vtx.NPrimaryParticles[ParticleId::kMuon]) continue;
      particles[count++] = trk; 
    }
    // Sort 
    std::sort(particles.begin(), particles.end(), AnaTrueParticleB::CompareMomentum);
    for (size_t i = 0; i < particles.size(); i++){
      if (!particles[i]) continue;
      //--------------------------------------------------------------------------------------------------------------------------------
      if( particles[i]->PDG == 13){
        output().FillVar(Truemu_mom,                  particles[i]->Momentum);
        output().FillVectorVarFromArray(Truemu_pos,   particles[i]->Position,4);
        output().FillVectorVarFromArray(Truemu_dir,   particles[i]->Direction,3);

        output().FillVectorVarFromArray(Truemu_posend,   particles[i]->PositionEnd,4);

        output().FillVar(Truemu_costheta,             (Float_t)particles[i]->Direction[2]);
        output().FillVar(Truemu_fgdlayer,             numuCC4piMultiPi_utils::GetFgdLayer(particles[i]->Position, _fgdID));    
      }
    }  
  }
}

//********************************************************************
bool numuCC4piMultiPiAnalysis::CheckFillTruthTree(const AnaTrueVertex& vtx){
  //****************************************************************
  bool TrueNuMuCC = vtx.ReacCode>0 && vtx.ReacCode<30 && vtx.NuPDG==14;

  bool TrueVtxFV = true;
  TrueVtxFV = anaUtils::InFiducialVolume( _fgdID, vtx.Position );
  // GetReactionCC already takes into account the outFV and also the NuWro reaction code for 2p2h in prod5 (that is 70)
  bool numuCCinFV = (anaUtils::GetReactionCC(vtx, _fgdID) == 1);

  // Since our topology definition doesn't consider the reaction code and since a muon pair can be created in the FSI 
  // (likely in DIS) in principle we might have a non-CC vertex categorized as CCother (nevertheless I didn't find any.)
  int topo = anaUtils::GetTopology(vtx, _fgdID);
  bool topoCCinFV = (topo == 0 || topo == 1 || topo == 2);
  // std::cout << "anaUtils::GetReactionCC(vtx, _fgdID)" << anaUtils::GetReactionCC(vtx, _fgdID) << std::endl;
  // std::cout << _fgdID << std::endl;
  // std::cout << "topo" << topo << std::endl;
  // std::cout << "TrueVtxFV " << TrueVtxFV << std::endl;
  // std::cout << "TrueNuMuCC" << TrueNuMuCC <<  std::endl;
  // std::cout << "numuCCinFV" << numuCCinFV << std::endl;
  // std::cout << "topoCCinFV" << topoCCinFV << std::endl;
  return (TrueNuMuCC && TrueVtxFV && numuCCinFV && topoCCinFV);
}

//*********************************************************************
Int_t numuCC4piMultiPiAnalysis::FindTPCTracks(const ToyBoxB& boxB, SubDetId::SubDetEnum det, AnaTrackB** TPCtracks ){
  //****************************************************************
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
void numuCC4piMultiPiAnalysis::AddCategories(){
  //****************************************************************
  const std::string& prefix = "";
  anaUtils::AddStandardCategories("");

  std::string oofv_types[] 					= {"FV", "OOFV FGD1 true<sel", "OOFV FGD1 true>sel", "OOFV Upstream", "OOFV Downstream", "OOFV Neutral", "OOFV Fwd", "OOFV HA", "OOFV Bwd", "OOFV Last", "OOFV Other"};
  int oofv_code[]             				= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int oofv_colors[]           				= {1, 2, 3, 4, 5, 6, 7, 8, 9, 28, 29 };
  const int NOOFVTYPES = sizeof(oofv_types)/sizeof(oofv_types[0]);
  anaUtils::_categ->AddCategory(prefix + "OOFV", NOOFVTYPES, oofv_types, oofv_code, oofv_colors);	

  std::string contribution_types[] = {"CC0#pi", "CC1#pi^{+}", "CC1#pi^{+}1#pi^{-,0}", "CC2#pi^{+}", "CCrest", "BKG"   , NAMEOUTFV};
  int contribution_codes[]         = {0         , 1         , 2                     , 3             , 4     , 5       , 6        };
  int contribution_colors[]        = {2         , 3         , 7                     , 4             , 0     , COLBKG  , 1        };
  const int NCONTRIBUTION = sizeof(contribution_types)/sizeof(contribution_types[0]);
  anaUtils::_categ->AddCategory(prefix + "contribution", NCONTRIBUTION, contribution_types, contribution_codes, contribution_colors);

  std::string dircetion_type[] = {"Fwd FGD1", "Fwd FGD2", "Bwd FGD1", "Bwd noFGD2", NAMEOUTFV};
  int direction_codes[]         = {0         , 1         , 2                     , 3             , 6     };
  int direction_colors[]        = {2         , 3         , 7                     , 4             , 0       };
  const int NDIRECTION = sizeof(dircetion_type)/sizeof(dircetion_type[0]);
  anaUtils::_categ->AddCategory(prefix + "direction", NDIRECTION, dircetion_type, direction_codes, direction_colors);


}

//********************************************************************
void numuCC4piMultiPiAnalysis::FillCategories(){
  //****************************************************************
  const std::string& prefix = "";
  const SubDetId::SubDetEnum det= _fgdID;
  bool IsAntinu = false;

  if ( cc4piMultiPibox().MainTrack ){
    AnaTrack* track = static_cast<AnaTrack*>(cc4piMultiPibox().MainTrack);
    if(track){
      anaUtils::FillCategories(&GetEvent(),track,"",det);
      anaUtils::_categ->SetCode(prefix + "OOFV",    		numuCC4piMultiPi_utils::OOFVCategory(track, det));
    }
    if (cc4piMultiPibox().MainTrack->TrueObject) {
      AnaTrueVertex *trueVertex = static_cast<AnaTrueVertex*>(cc4piMultiPibox().MainTrack->GetTrueParticle()->TrueVertex);
      if(trueVertex) {
        anaUtils::_categ->SetCode(prefix + "contribution",  numuCC4piMultiPi_utils::GetCONTTopology(*trueVertex,det,IsAntinu));
      }	
    }
    if (cc4piMultiPibox().MainTrack->TrueObject) {
      AnaTrueVertex *trueVertex = static_cast<AnaTrueVertex*>(cc4piMultiPibox().MainTrack->GetTrueParticle()->TrueVertex);
      if(trueVertex) {
        anaUtils::_categ->SetCode(prefix + "direction",  numuCC4piMultiPi_utils::DirectionCategory(track, det));
      }	
    }
  }
}

//******************************************************************
int numuCC4piMultiPi_utils::DirectionCategory(AnaTrack* candidate, SubDetId::SubDetEnum det){
  //****************************************************************
  bool fwd = false;
  int fgd = 0;

  if(!candidate) return -1;
  AnaTrueParticle* truetrack = static_cast<AnaTrueParticle*>( candidate->TrueObject );
  if (!truetrack) return -1;
  AnaTrueVertex* truevtx = static_cast<AnaTrueVertex*>( truetrack->TrueVertex );
  if (!truevtx) return -1;
  Float_t* tvertex = truevtx->Position;


  if  (anaUtils::InFiducialVolume(SubDetId::kFGD1, tvertex)) fgd = 1;
  else if (anaUtils::InFiducialVolume(SubDetId::kFGD2, tvertex)) fgd = 2;

  if (candidate->PositionStart[2] < candidate->PositionEnd[2]){
    fwd = true;
  }
  if (fwd){
    if (fgd == 1) return 0;
    else if (fgd == 2) return 1;
  }
  else if (!fwd){
    if (fgd == 1) return 2;
    else if (fgd == 2) return 3;
  }
  if (fgd == 0) return 6;
  
  return -1;

}
//******************************************************************
int numuCC4piMultiPi_utils::OOFVCategory(AnaTrack* candidate, SubDetId::SubDetEnum det){
  //****************************************************************
  /* Classify oofv types
     -1 = no true vertex
     0 = FV   
     1 = OOFV FGD1 true<sel
     2 = OOFV FGD1 true>sel
     3 = OOFV Upstream
     4 = OOFV Downstream
     5 = OOFV Neutral
     6 = OOFV Fwd
     7 = OOFV HA
     8 = OOFV Bwd
     9 = OOFV Last
     10 = OOFV Other
     */

  if(!candidate) return -1;
  AnaTrueParticle* truetrack = static_cast<AnaTrueParticle*>( candidate->TrueObject );
  if (!truetrack) return -1;
  AnaTrueVertex* truevtx = static_cast<AnaTrueVertex*>( truetrack->TrueVertex );
  if (!truevtx) return -1;
  Float_t* tvertex = truevtx->Position;
  if(anaUtils::InFiducialVolume(det, tvertex)) return 0;
  Float_t* tdir = truetrack->Direction;
  Float_t* pos  = truetrack->Position;
  Float_t* fgd_det_min;
  Float_t* fgd_det_max;
  double zup,zdown;
  bool lastmodule = false;

  if (det == SubDetId::kFGD1){
    zup             =-60;
    zdown           = 623;

    fgd_det_min     = DetDef::fgd1min;
    fgd_det_max     = DetDef::fgd1max;

    bool layer28=( pos[2] >429 && pos[2] <435 );
    bool layer29=( pos[2] >442 && pos[2] <445 );

    lastmodule=(layer28 || layer29);

  }
  else{ //det == SubDetId::kFGD2
    zup             = 1300;
    zdown           = 1983;

    fgd_det_min     = DetDef::fgd2min;
    fgd_det_max     = DetDef::fgd2max;

    // Prototype FGD2 last layer definition. To be tunned.
    lastmodule = (pos[2] > 1740);
  }
  //inFGD1scint. Put z condition first to be faster
  if ( tvertex[2]>fgd_det_min[2] && tvertex[2]<fgd_det_max[2] && tvertex[0]>fgd_det_min[0] && tvertex[0]<fgd_det_max[0] && tvertex[1]>fgd_det_min[1] && tvertex[1]<fgd_det_max[1] )	{
    if (tvertex[2]<candidate->PositionStart[2]) return 1;
    else return 2;
  }
  //upstreamFGD1scint
  if ( tvertex[2]>zup && tvertex[2]<fgd_det_min[2] && tvertex[0]>-1335 && tvertex[0]<1335 && tvertex[1]>-1280.5 && tvertex[1]<1280.5 ) return 3;
  //downstreamFGD1scint
  if ( tvertex[2]>fgd_det_max[2] && tvertex[2]<zdown && tvertex[0]>-1335 && tvertex[0]<1335 && tvertex[1]>-1280.5 && tvertex[1]<1280.5 ) return 4;
  //neutralparent
  if ( truetrack->ParentPDG  == 2112 || truetrack->ParentPDG  == 22 ||  truetrack->GParentPDG == 2112 || truetrack->GParentPDG == 22) return 5;
  //forwards
  if (tdir[2]>0 || (fabs(tdir[0]/tdir[2])<0.07 || fabs(tdir[1]/tdir[2])<0.07)) return 6;
  //highangle
  if ((tdir[2]>=0 && tdir[2]<0.5) || (tdir[2]<=0 && tdir[2]>-0.5)) return 7;
  //backwards
  if (tdir[2]<0 || (fabs(tdir[0]/tdir[2])<0.07 || fabs(tdir[1]/tdir[2])<0.07)) return 8;
  //layer2829
  if ( lastmodule ) return 9;
  //other
  return 10;
}


//*******************************************************************
Float_t* numuCC4piMultiPi_utils::GetFittedPos(Float_t* start, Float_t* end, double z){
  //*****************************************************************
  double t = (z-start[2])/(end[2]-start[2]);
  Float_t* pos = new Float_t(3);
  pos[0] = start[0]+(end[0]-start[0])*t;
  pos[1] = start[1]+(end[1]-start[1])*t;
  pos[2] = z;
  return pos;
}

//*******************************************************************
Float_t numuCC4piMultiPi_utils::GetDeltaPos(Float_t* hit, Float_t* fit){
  //*****************************************************************
  Float_t delta = 0;
  if ( hit[0]>-4.6 && hit[0]<0.2 )  delta = hit[1] - fit[1];
  if ( hit[1]>50.4 && hit[1]<55.2 ) delta = hit[0] - fit[0];
  return delta;
}

//*******************************************************************
Float_t numuCC4piMultiPi_utils::GetDeltaPos2(Float_t* hit, Float_t* fit){
  //*****************************************************************
  Float_t delta = 0;
  if ( hit[0]>-4.6 && hit[0]<0.2 )  delta = hit[1]*hit[1] - fit[1]*fit[1];
  if ( hit[1]>50.4 && hit[1]<55.2 ) delta = hit[0]*hit[0] - fit[0]*fit[0];
  return delta;
}
