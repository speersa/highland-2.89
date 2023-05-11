#ifndef numuCC4piMultiPiAnalysis_h
#define numuCC4piMultiPiAnalysis_h

#include "numuCC4piMultiPiSelection.hxx"
#include "baseTrackerAnalysis.hxx"
#include "PionInteractionSystematic.hxx"

class numuCC4piMultiPiAnalysis: public baseTrackerAnalysis {
	public:
		numuCC4piMultiPiAnalysis(AnalysisAlgorithm* ana=NULL);
		virtual ~numuCC4piMultiPiAnalysis(){
	    	delete _pionSIManager;
	  		_pionSIManager = NULL;
		}

  		//---- These are mandatory functions
		void DefineSelections();
		void DefineCorrections();
		void DefineSystematics();
		void DefineConfigurations();
		void DefineMicroTrees(bool addBase=true);
		void DefineTruthTree();
		void FillMicroTrees(bool addBase=true);
		void FillToyVarsInMicroTrees(bool addBase=true);
		bool CheckFillTruthTree(const AnaTrueVertex& vtx);

		using baseAnalysis::FillTruthTree;
		using baseTrackerAnalysis::FillTruthTreeBase;
		void FillTruthTree(const AnaTrueVertex& vtx);
		
		bool Initialize();
		void AddCategories();
		void FillCategories();
		
		const ToyBoxCC4piMultiPi& cc4piMultiPibox(){return static_cast<const ToyBoxCC4piMultiPi&>( box() );}

		Int_t FindTPCTracks(const ToyBoxB& box, SubDetId::SubDetEnum det, AnaTrackB** TPCtracks);
		
  		/*inline void SetEnableMomRange(bool enable){
    		_prangeEnabled = enable;
  		}
  		inline void SetEnableMomRangeMuon(bool enable){
    		_prangeMuon = enable;
  		}*/

  	private:
  		Int_t _whichFGD; // 1 for FGD1 analysis, 2 for FGD2, 3 for both
      Int_t _whichSel; // 1 - 4pi multi-pi, 2 - 4pi multi-pi extended for 1pi xsec
      int _bwd_info; // Whether include additional information for bwd migration study or not.

 		SubDetId::SubDetEnum _fgdID;
  		bool _addPionSIinfo;
  		/*bool _prangeEnabled;
  		bool _prangeMuon;*/
  
  		/// Pion SI manager
  		PionSIManager* _pionSIManager;

  		std::set<int> init_pions() const{
		    std::set<int> pdgs;
		    pdgs.insert(111); //pi-zero
		    pdgs.insert(211); //pi+
		    pdgs.insert(-211); //pi-
		    return pdgs;
	  	}

  		std::set<int> _pion_pdgs;
	
	public:
		enum enumStandardMicroTrees_numuCC4piMultiPiAnalysis{	
			//---- Add new vareables -----
			Truemu_mom = enumStandardMicroTreesLast_baseTrackerAnalysis+1,
			Truemu_pos,
			Truemu_dir,

      Truemu_posend,

			Truemu_costheta,
			Truemu_fgdlayer,
      // Qualifying_sampleID,
			NLowAngle,
			NHighAngle,
			NFwdMuLike,
			NBwdMuLike,
			NHAFwdMuLike,
			NHABwdMuLike,
			selmu_HMNT,
			selmu_mom,
			selmu_costheta,
      selmu_direction2,
			selmu_mom_range_oarecon,
			selmu_likemu,
			selmu_likemip,
			selmu_end_ecal,
			selmu_PDG,
			selmu_ID,
			selmu_truemom,
			selmu_truedir,
			selmu_truecostheta,
			selmu_truepos,
			selmu_trueendpos,
			selmu_truefgdlayer,
			selmu_ToF_PoD,
			selmu_ToF_ECAL,
			selmu_ToF_FGD2,

      selmu_ToF_topology,
      selmu_is_flipped,
      selpi_is_flipped,

      nProtonsTPC,
      TPCProtMom,
      TPCProtonTId,
      proton_is_flippedTPC,

      nProtonsFGD,
      FGDProtMom,
      FGDProtonTId,
      proton_is_flippedFGD,

			selmu_detectors,
			selmu_charge,
			selmu_dir,
      selmu_enddir,
      selmu_nuvec,
      selmu_muvec,
			selmu_pos,
			selmu_endpos,
			selmu_fgdlayer,
			selmu_1hit_pos,
			selmu_2hit_pos,
			selmu_1hit_charge,
			selmu_2hit_charge,
	 		selmu_1hit_fitpos,
	 	 	selmu_2hit_fitpos,
	 	 	selmu_1hit_deltapos,
			selmu_2hit_deltapos,
	 	 	selmu_1hit_deltapos2,
			selmu_2hit_deltapos2,
			selmu_pod_nnodes,
	 		selmu_ntpcs,
			selmu_tpc_det,
			selmu_tpc_nnodes,
			selmu_tpc_charge,
      selmu_tpc_mom,
			selmu_nfgds,
			selmu_fgd_det,
			selmu_fgd_nnodes,
      selmu_fgd_x,
      selmu_necals,
      selmu_ecal_det,
      selmu_ecal_nnodes,
      selmu_ecal_length,
      selmu_ecal_EMenergy,
      selmu_ecal_mipem,
      selpi_necals,
      selpi_ecal_det,
      selpi_ecal_nnodes,
      selpi_ecal_length,
      selpi_ecal_EMenergy,
      selpi_ecal_mipem,
      selpi_ecal_mippion,
      selpi_ecal_pdg,
      selpi_ecal_id,
      selpi_ecal_costheta,

      NFGDSec,
      FGDSecLength,
      FGDSecLengthX,
      FGDSecPiPull,
      FGDSecContained,
      FGDSecAvgTime,
      FGDSecCosTheta,
      FGDSecTId,
      FGDSecIndex,
      FGDSecParentTId,
      FGDSecGParentTId,
      FGDSecDir,
      FGDSecPosStart,
      FGDSecPosEnd,
      FGDSecTimeIni,
      FGDSecTimeEnd,
      FGDSecDeltaTimeIniSelMu,
      FGDSecDeltaTimeEndSelMu,
      FGDSeg_1hit_charge,
      FGDSeg_2hit_charge,
      FGDSeg_1hit_pos,
      FGDSeg_2hit_pos,
      FGDSeg_1hit_fitpos,
      FGDSeg_2hit_fitpos,

      NTPCSec,
      TPCSec_MomGlobal,
      TPCSec_pos,
      TPCSec_endpos,
      TPCSecMom,
      TPCSecMomEnd,
      TPCSecMudEdx,
      TPCSecPidEdx,
      TPCSecPrdEdx,
      TPCSecEldEdx,
      TPCSecLikemu,
			TPCSecLikemip,
      TPCSecDetectors,
      TPCSecQ,
      TPCSecTId,
      TPCSecIndex,
      TPCSecParentTId,
      TPCSecGParentTId,
      TPCSecDir,
      TPCSecPosStart,
      TPCSecPosEnd,
      TPCSecLength,

      HM_pos,
      NNegPion,
      NegPionMom,
      NegPionCosTheta,
      NegPionPidLik,
      NegPionPull,
      NegPionTId,
      NegPionIndex,
      NegPionParentTId,
      NegPionGParentTId,
      NegPionDir,
      NegPionPosStart,
      NegPionPosEnd,
      NegPionLength,

      selpi_mom,
      selpi_costheta,
      selpi_dir,
      selpi_ID,
      selpi_pull,

      NPosPion,
      PosPionMom,
      PosPionCosTheta,
      PosPionPidLik,
      PosPionPull,
      PosPionTId,
      PosPionIndex,
      PosPionParentTId,
      PosPionGParentTId,
      PosPionDir,
      PosPionPosStart,
      PosPionPosEnd,
      PosPionLength,

      NPi0El,
      Pi0ElMom,
      Pi0ElPull,
      Pi0ElTId,
      Pi0ElIndex,
      Pi0ElParentTId,
      Pi0ElGParentTId,
      Pi0ElVId,
      Pi0ElDir,
      Pi0ElPosStart,
      Pi0ElPosEnd,

      NPi0Pos,
      Pi0PosMom,
      Pi0PosPull,
      Pi0PosTId,
      Pi0PosIndex,
      Pi0PosParentTId,
      Pi0PosGParentTId,
      Pi0PosVId,
      Pi0PosDir,
      Pi0PosPosStart,
      Pi0PosPosEnd,

      NFGDPi,
      FGDPiLength,
      FGDPiLengthX,
      FGDPiPiPull,
      FGDPiAvgTime,
      FGDPiDistance,
      FGDPiMomRangeOarecon,
      FGDPiMuonangle,
      FGDPiCosTheta,
      FGDPiTId,
      FGDPiIndex,
      FGDPiParentTId,
      FGDPiGParentTId,
      FGDPiVId,
      FGDPiDir,
      FGDPiPosStart,
      FGDPiPosEnd,
      FGDPiTimeIni,
      FGDPiTimeEnd,
      FGDPiDeltaTimeIniSelMu,
      FGDPiDeltaTimeEndSelMu,
      TrueFGDPiMom,
      TrueFGDPiCosTheta,

      NFGDEl,
      FGDElLength,
      FGDElLengthX,
      FGDElPiPull,
      FGDElAvgTime,
      FGDElDistance,
      FGDElMuonangle,
      FGDElCosTheta,
      FGDElTId,
      FGDElIndex,
      FGDElParentTId,
      FGDElGParentTId,
      FGDElVId,
      FGDElDir,
      FGDElPosStart,
      FGDElPosEnd,
      FGDElTimeIni,
      FGDElTimeEnd,
      FGDElDeltaTimeIniSelMu,
      FGDElDeltaTimeEndSelMu,

      NME,
      MENHits,
      MERawCharge,
      MEMinTime,
      MEMaxTime,

      NTPC1Track,
      TPC1TrackMom,
      TPC1TrackPhi,
      TPC1TrackVId,
      TPC1TrackTId,
      TPC1TrackParentTId,
      TPC1TrackGParentTId,
      TPC1TrackPosStart,
      TPC1TrackPosEnd,

      IntType,
      NInts,
      PionType,
      PionMom,
      NPions,

      NTrueNegPion,
      TrueNegPionMom,
      TrueNegPionCosTheta,
      TrueNegPionDir,
      TrueNegPionPosStart,
      TrueNegPionPosEnd, 

      NTruePosPion,
      TruePosPionMom,
      TruePosPionCosTheta,
      TruePosPionDir,
      TruePosPionPosStart,
      TruePosPionPosEnd, 

      NTruePrim_pi,
      TruePrim_pi_mom,
      TruePrim_pi_dir,
      TruePrim_pi_costheta,
      TruePrim_pi_id, 
      TruePrim_pi_pdg, 

      true_ntracks,  
      true_nprotons, 
      true_npions,

      nTotalPi,
      nNegPion,
      nPosPion,
      nTPCSec,
      nFGDSec,
      nFGDPi,
      nFGDEl,
      nPi0El,
      nPi0Pos,
      nProtonTPC,
      nProtonFGD,
      nECalPhotons,


      nTPCObjects,
      nECalObjects,
      nISOFGDObjects,
      //-------------------------------------
      kinematic_weight,

      enumStandardMicroTreesLast_numuCC4piMultiPiAnalysis
    };
};

namespace numuCC4piMultiPi_utils{
  int OOFVCategory(AnaTrack* candidate, SubDetId::SubDetEnum det);
  int DirectionCategory(AnaTrack* candidate, SubDetId::SubDetEnum det);

	Float_t* GetFittedPos(Float_t* start, Float_t* end, double z);
	Float_t GetDeltaPos(Float_t* hit, Float_t* fit);
	Float_t GetDeltaPos2(Float_t* hit, Float_t* fit);
}

#endif
