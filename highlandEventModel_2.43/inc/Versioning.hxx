#ifndef VERSIONING_HXX_SEEN
#define VERSIONING_HXX_SEEN
#include "oaAnalysisReaderProjectHeaders.h"

/// This file contains pre-processor directives related to the
/// oaAnalysis file format that was used to generate the  oaAnalysisReader classes
/// Depending on the file format, different bits of highland need to
/// be conditionally compiled.
///
/// oaAnalysisReader advertises a few low-level directives. This file
/// defines higher-level directives (related to specific features that
/// are enabled/disabled in each version), to make using the directives
/// easier and more transparent.
///
/// http://www.t2k.org/nd280/datacomp/production005)
///
/// Respin 5D: this is a finished sand-MC production, using software version v10r11p11.  Users should use respin 5D for their sand interaction MC samples.
/// Respin 5E: this is a finished full MC production, using software version v10r11p17.
/// Respin 5F: this is an finished full MC and full data production, using software version v10r11p21 (and v10r11p23).
///            The data reprocessing includes improvements to the calibration constants.  Users should use this respin for their data and MC samples.
/// Respin 5G: this is a finished spill data production, using software version v10r11p27.  This processing was done at request of pi0 calibration task force.
///            It includes improvements to p0dRecon aimed at fixing data/MC discrepancies seen in pi0 analysis.
/// Respin 5H: this is a respin for Read Data Run 5 (First Pass) only, using software version v10r11p23 and updated Beam Summary Data Files (of Jul 5, 2014).
///
/// http://www.t2k.org/nd280/datacomp/production006/production006
///
/// Respin 6A: this is a stopped,failed production, using software version v11r29.  The production was stopped because of several serious bugs (989: 990: 992:995).
/// Respin 6B: this is an ongoing production, using software version v11r31. For Real Data run 5, only run 55 was processed as First Pass with early Beam Summary Data Files.
///            Analysers should use this respin for MCP.
/// Respin 6C: this is a v11r31 respin for Real Data runs 5 and 6. The First Pass Processing (fpp) used pre-existing calibration tables and early BSD.
///            Partially Calibration 1 (pc1) contains updated calibration tables, updated BSD but no inter-detector timing.
///            Real Data Processing (rdp) contains the full set of calibrations, corrections, BSD and inter-detector timing. For run6 the rdp has incomplete constants and BSD.
/// Respin 6D: this is a MC only production using nd280 v11r31 on top of neut 5.3.2.2 (additional proton FSI)
/// Respin 6E: RDP only using v11r31p5 which features new P0D ECal timing calibrations. Run 7 FPP goes as this respin.
/// Respin 6F: this an RDP and MCP respin using v11r31 with nd280Analysis v1r47p1 prepended to the CMTPATH.
///            It features additional FGD vertex information frozen into oaAnalysis v5r29p25. The RDP files are missing the BSD.
/// Respin 6G: this is an RDP-only respin using nd280 v11r31p7. It features additional FGD vertex information frozen into oaAnalysis v5r29p25.
/// Respin 6H: this is an MCP-only respin using nd280 v11r31p9 (same as v11r31p7 but with incorrect software tags). It features the trexRecon replacement of tpcRecon and is
///            intended both for trexRecon validation and tpcGas analysis.
/// Respin 6I: this is an RDP-only respin using nd280 v11r37 (same as v11r31p9 but with correct software tags). It features the trexRecon replacement of tpcRecon and is
///            intended both for trexRecon validation and tpcGas analysis.
/// Respin 6J: this is a Neut MCP-only respin using nd280 v11r31p11. It features the new NeutG4CascadeInterface_QGSP_BERT physics list for nd280mc.
/// Respin 6K: this is an RDP-only respin using nd280 v11r31p5.  This has correct ECAL timing corrections (and other ECAL corrections) for runs 5 and 6.
///            For runs 1-4 the output is the same as respin 6E and has just been copied over from 6E. Analysers should use this respin for RDP. 
/// Respin 6L: this is an MCP-only production using nd280v11r31p27 to produce run7 and run8 magnet MCP with the 2015-08 baseline (featuring 5/6 fgd2 water panels).
/// Respin 6M: this is RDP (ANAL stage only) respin using RECO files of 6K and the same nd280 version (v11r31p5). The reason for it was the BSD update (BSD release announced on Oct 21, 2016). Analysers should use this respin for Runs 1-6 RDP.
/// Respin 6N: nd280 v11r31p27 (update for no water in first FGD2 panel). FPP for 2016 Run 8, and a second RDP for Run 7.  Analysers should use this respin for Run 7 RDP.
/// Respin 6O: nd280 v11r31p27. Second FPP for 2016 Run 8 this time with good FGD timing markers. First FPP for 2017 Run 8 with bad timing markers (incomplete or not treating timing jitters correctly).  PC1 for all of Run8.  Analysers should use this respin for Run8 PC1.
/// Respin 6P: nd280 v11r31p29. FPP for 2017 Run 9.
/// Respin 6Q: nd280 v11r31p37 RDP for Run 4 air data  (also MC mini prod being deleted - tag can be used for data)
/// Respin 6R: nd280 v11r31p35.  MCP run5water - NEUT 5.4.0 (before coherent on hydrogen bug fix).  Part of validation process, not used for physics analyses
/// Respin 6S: nd280v11r31p41.  MC run4air - NEUT 5.4.0.1 (includes coherent on hydrogen bug fix)
/// Respin 6T: nd280v11r31p43.  MC run4air - NEUT 5.4.0.1 ( note, NEUT vectors were done with nd280v11r31p41, though this won't affect anything.  nd280 processing stage done with nd280v11r31p43 )
/// Respin 6U: nd280v11r31p43 with p6 geom fixed (magnet_ecal_production6 = 0).  MC run4air - NEUT5.4.0.1  NEUT_D   (note:  NEUT vectors done with nd280v11r31p41)
/// Respin 6V: reserved for nd180v11r31p45 
/// Respin 6W: nd280v11r31p57  
/// Respin 6X: nd280v11r31p51 prod6T with an updated oaAnalysis to include FGD hit info saved for FGD-tracks
/// Respin 6Y: v11r31p61, oaAnalysis/v5r29p35/,   - includes additional FGD truth info
/// Respin 6Z: v11r31p63, oaAnalysis v5r29p35 -- a fix to nd280mc to save properly G4 trajectory entrance/exit point in FGDs
/// Respin 6AA: v11r31p67, oaAnalysis v5r29p37 -- a proper()!) fix to nd280mc to save properly G4 trajectory entrance/exit point in FGDs
  
 
 
/// http://www.t2k.org/nd280/datacomp/production007/production_7_status

/// Respin  7A:   Testing production 7  (v12r9) with P6 NEUT (5.3.2).  For validation purposes.  Known bug in FGD PID.  MC:  Run7water, Run8air
/// Respin  7B:   Testing production 7  (v12r15) with FGD PID fix,  P6 NEUT (5.3.2).  For validation purposes.  Data:  Run7water RDP.  Coming soon:  MC run4air, Data run4air RDP.
/// Respin  7B:   Testing production 7 (v12r19) with TPC dEdX fix in GEANT4, B field in yokes 
/// Respins 7_V:  Production 7 validation iterations (13.X git/cmake version numbering) series

/// The table below shows the versions 

/// prod       nd280        nd280Analysis     oaAnalysis 
///------------------------------------------------------
/// 5D         v10r11                         v5r11       
/// 5E         v10r11p17                      v5r15p1
/// 5F         v10r11p19                      v5r15p3
/// 5G         v10r11p27                      v5r15p3
///
/// 6A         v11r29       v1r39             v5r29p17 
/// 6B-6D      v11r31       v1r43             v5r29p19     *
///            v11r31p1     v1r45             v5r29p19   
///            v11r31p3     v1r43p1           v5r29p21     
/// 6E, 6K     v11r31p5     v1r43p1           v5r29p21     *  Vector to store the ID of the Trajectory that created the hit in FGD1
/// 6F         v11r31       v1r47p1           v5r29p25     *  (nd280Analysis v1r47p1 preappend to CMTPATH)
/// 6G         v11r31p7     v1r47p1           v5r29p25        fgdVA_verNearQ ... _rect
/// 6H         v11r31p9     v1r43p5           v5r31p9      *
/// 6I         v11r37       v1r43p5           v5r31p9
/// 6J         v11r31p11    v1r43             v5r29p19 
/// 6L         v11r31p27    v1r47p1           v5r29p25
/// 6M         v11r31p5     v1r43p1           v5r29p21
/// 6N         v11r31p27    v1r47p1           v5r29p25
/// 6O         v11r31p27    v1r47p1           v5r29p25
/// 6P         v11r31p29    v1r47p1           v5r29p25
/// 6Q         v11r31p37    v1r47p1           v5r29p25
/// 6R         v11r31p35    v1r43p7           v5r29p29
/// 6S         v11r31p41    v1r47p1           v5r29p25
/// 6T, 6U     v11r31p43    v1r47p5           v5r29p31
/// 6V         v11r31p45    v1r47p5           v5r29p31
/// 6W         v11r31p57    v1r47p9           v5r29p33
/// 6X         v11r31p51    v1r47p9           v5r29p33
/// 6Y         v11r31p61    v1r47p11          v5r29p35 
/// 6Z         v11r31p63    v1r47p11          v5r29p35
/// 6AA        v11r31p67    v1r47p13          v5r29p37
//
//
///
/// 7RC1       v12r5        v1r51             v6r1
/// 7A         v12r9        v1r59             v6r3
/// 7B         v12r15       v1r59             v6r3
/// 7B (new)   v12r19       v1r65             v637         * naming is confusing but this is how it is called by nd280-computing, will re-name for further prod7 iterations
/// 7_V01      13.7         --                6.14
/// 7_V02      13.9         --                6.14
/// 7_V03      13.9         --                6.14
/// 7_V06      13.14        --                6.17
/// 7_V07      13.15        --                7.2
/// 7_V09      13.16        --                7.3
/// 7_V12      13.21        --                7.4
/// Show those are the readers we need 

/// productions                         oa/eventAnalysis     oaAnalysisReader
///-------------------------------------------------------------------------
/// 5D                                  v5r11                prod5D   
/// 5E                                  v5r15p1               
/// 5F, 5G                              v5r15p3              prod5F
/// 
/// -----
/// 6B-6D, 6J                           v5r29p19             prod6B 
/// 6E, 6K, 6M                          v5r29p21             prod6E
/// 6F, 6G, 6L, 6N, 6O, 6P, 6Q, 6S      v5r29p25             prod6G
/// 6H-6I                               v5r31p9  (TREX)      prod6TREx
/// 6R                                  v5r29p29             prod6R
/// 6T, 6U, 6V                          v5r29p31             prod6T
/// 6W, 6X                              v5r29p33             prod6X
/// 6Y, 6Z                              v5r29p35             prod6Y
/// 6AA                                 v5r29p37             prod6AA 
///
/// -----                               v6r1     (P7 RC1)    prod7_RC1
/// 7A, 7B                              v6r3                 prod7_RC2
/// 7B (new)                            v6r7                 prod7B
/// 7_V0(1,2,3)                         6.14                 prod7_V02 
/// 7_V06                               6.17                 prod7_V06
/// 7_V07                               7.2                  prod7_V07
/// 7_V09                               7.3                  prod7_V09
/// 7_V12                               7.4                  prod7_V12
///--------------------------------------------------------------

/// nd280 version for production 5D is v10r11p0 to v10r11p15 
#define VERSION_PROD5D (BEFORE_ANATOOLS_FILE(10,11,17))

/// nd280 version for production 5E is v10r11p17 
#define VERSION_PROD5E (EQUALS_ANATOOLS_FILE(10,11,17))

/// nd280 version for production 5F goes from v10r11p19 to v10r11p23
#define VERSION_PROD5F (!BEFORE_ANATOOLS_FILE(10,11,19) && BEFORE_ANATOOLS_FILE(10,11,25))

/// nd280 version for production 5G is v10r11p27
#define VERSION_PROD5G (EQUALS_ANATOOLS_FILE(10,11,27))

/// nd280 version for pre production 6 goes from v11r17 to v11r27
#define VERSION_PROD6PRE (!BEFORE_ANATOOLS_FILE(11,17,0) && BEFORE_ANATOOLS_FILE(11,29,0))

/// nd280 version for Production 6A is v11r29
#define VERSION_PROD6A (EQUALS_ANATOOLS_FILE(11,29,0))

/// nd280 version for Production 6B is v11r31
#define VERSION_PROD6B (EQUALS_ANATOOLS_FILE(11,31,0))

/// v11r31p9 was used for TREx validation/production based on prod-6 for the rest of
/// the software (only reconstruction was updated for TREx usage)
/// New oaAnalysis module and new reconstruction was introduced:
#define VERSION_PROD6HI (EQUALS_ANATOOLS_FILE(11,31,9))


/// nd280 version for produciton 6J:
/// this is a Neut MCP-only respin using nd280 v11r31p11. 
/// It features the new NeutG4CascadeInterface_QGSP_BERT physics list for nd280mc
/// The appropiate updated pion SI systematics tables should be also used for this production 
#define VERSION_PROD6J (EQUALS_ANATOOLS_FILE(11,31,11))

/// nd280 version for production 6X v11r31p51
#define VERSION_PROD6X (EQUALS_ANATOOLS_FILE(11,31,51))

#define VERSION_PROD6Y (EQUALS_ANATOOLS_FILE(11,31,61))

#define VERSION_PROD6Z (EQUALS_ANATOOLS_FILE(11,31,63))

#define VERSION_PROD6AA (EQUALS_ANATOOLS_FILE(11,31,67))

/// Production 7 version
#define VERSION_PROD7 (!BEFORE_ANATOOLS_FILE(12,0,0))

#define VERSION_PROD7_GIT_CMAKE_SERIES (!BEFORE_ANATOOLS_FILE(13, 0, 0))


///--------------------------------------------------------------


/// For production 6 pre-production files, we need to disable all corrections.
#define VERSION_DISABLE_CORRECTIONS VERSION_PROD6PRE

/// For production 6 pre-production or production 6A files, we need to disable all production dependent corrections
#define VERSION_DISABLE_PROD_CORRECTIONS (VERSION_PROD6PRE || VERSION_PROD6A)

/// The B-field distortion refit info changed interface between P5 and P6.
/// In P5F, we had Charge, Momentum, Position and Direction saved
#define VERSION_HAS_BFIELD_REFIT_FULL VERSION_PROD5F

/// In P6, we have only the B-field refit Momentum (and it changed name).
#define VERSION_HAS_BFIELD_REFIT_BASIC (!BEFORE_ANATOOLS_FILE(11,17,0))

/// Whether there is any B-field information. Although the momentum name is
/// different in P5/P6 oaAnalysis files, we kept the same name in highland.
/// Note that there is a gap between P5 and P6 pre-production files where
/// no B-field info was saved...
#define VERSION_HAS_BFIELD_REFIT (VERSION_HAS_BFIELD_REFIT_FULL || VERSION_HAS_BFIELD_REFIT_BASIC )

/// TPC E-field refit information was added in v11r17.
#define VERSION_HAS_EFIELD_REFIT (!BEFORE_ANATOOLS_FILE(11,17,0))

/// P5 files didn't store the ECal LLR (PID) variables directly, and they had
/// to be calculated using a tool in nd280AnalysisTools. In P6, they are
/// stored directly in the oaAnalysis file.
#define VERSION_HAS_ECAL_LLR (!BEFORE_ANATOOLS_FILE(11,0,0))

/// P5 files had CT5POT (and needed a correction to use CT4POT for some beam runs). P6 files
/// have an OfficalPOT variable.
#define VERSION_HAS_OFFICIAL_POT (!BEFORE_ANATOOLS_FILE(11,17,0))

/// P6 files have refits of each global track for electron/muon/proton hypotheses
/// in both the forwards and backwards directions.
#define VERSION_HAS_REVERSED_REFITS (!BEFORE_ANATOOLS_FILE(11,17,0))

/// P6 files have momentum from range estiamtates for a global track, assuming electron/muon/proton hypotheses
/// in both the forwards and backwards directions.
#define VERSION_HAS_PRANGE_ESTIMATES (!BEFORE_ANATOOLS_FILE(11,17,0))

/// P6 files have node times updated with t_vs_dist fit results
/// independently for each sub-detector
#define VERSION_HAS_TIME_FITS (!BEFORE_ANATOOLS_FILE(11,17,0))

/// P6 files have have both vertex (start or entrance) and end (stop or exit) activities
/// calculated for FGD tracks
#define VERSION_HAS_FGD_VERTEX_AND_END_ACTIVITY (!BEFORE_ANATOOLS_FILE(11,17,0))

/// P6 files have or to store information for single hits in FgdTimeBin
#define VERSION_HAS_FGD_HIT_INFO (!BEFORE_ANATOOLS_FILE(11,17,0))

/// P6 iteration with Vector to store the ID of the Trajectory that created the hit in FGD
#define VERSION_HAS_FGD_HIT_TRUE_TRAJ_ID (!BEFORE_ANATOOLS_FILE(11,31,3))

/// In production 7 for FGD tracks individual hits are stored
#define VERSION_HAS_FGD_HIT_INFO_IN_FGD_TRACKS (VERSION_PROD7 ||  VERSION_PROD6X || VERSION_PROD6Y || VERSION_PROD6Z || VERSION_PROD6AA)

/// P6 files use the same method for main track fitting and alternates fitting
#define VERSION_HAS_EQUIVALENT_MAIN_AND_ALT_FITS (!BEFORE_ANATOOLS_FILE(11,17,0))

/// For preproduction 6 the number of nodes for TPC objects was 2
#define VERSION_HAS_TWO_TPC_NODES VERSION_PROD6PRE

/// For production 6 P0D objects got hits/nodes averaged time stamps 
#define VERSION_HAS_P0D_AVERAGED_TIME (!BEFORE_ANATOOLS_FILE(11,17,0)) 

/// This is to check whether some obsolete ECal PID variables were deleted 
#define VERSION_HAS_REMOVED_OBSOLETE_ECAL_PID_VARS (VERSION_PROD6HI  || VERSION_PROD7)

/// This is to check whether a version has some obsolete TruthVars removed
/// (those related to detector intersection) 
#define VERSION_HAS_REMOVED_OBSOLETE_TRUTH_SUBDETECTOR_NON_TRACE_VARS (VERSION_PROD6HI || VERSION_PROD7)


/// Version with NEUT G4 Cascade interface, special prod6j respin and consider
/// it also for the future prod7 iterations,  will be updated 
//#define VERSION_HAS_NEUT_G4_CASCADE (VERSION_PROD6J)


/// For production 7 iteration substitute the NNodes (later treated as a figure
/// of merit for track quality)
/// with the actual number of horizontal and vertical clusters used in the fit
/// (as recommended by TREx group and can be indeed
/// considered as a proper characteristic of track quality)
#define VERSION_HAS_NUMBER_OF_FITTED_CLUSTERS (VERSION_PROD6HI || VERSION_PROD7)

/// For production 7 fgdRecon provides PID for electrons
#define VERSION_HAS_FGD_ELECTRON_PID VERSION_PROD7

/// For production 7 provide seeding info for ECal clusters
#define VERSION_HAS_ECAL_3D_CLUSTERING_ALGORITHM VERSION_PROD7 


/// Production 7 with mom-range for pion hypothesis and mom-range calculated up
/// to the downstream TPC - for systematics
#define VERSION_HAS_PRANGE_PION_ENDTPC_ESTIMATES  (!BEFORE_ANATOOLS_FILE(13,14,0))

/// Version that has true energy stored for FGD hits and tracks

#define VERSION_HAS_FGD_TRUE_ENERGY (!BEFORE_ANATOOLS_FILE(13, 15, 0) || VERSION_PROD6Y || VERSION_PROD6Z || VERSION_PROD6AA)

#define VERSION_HAS_ECAL_CLUSTERING_ADDED3DCLUSTERHITS (!BEFORE_ANATOOLS_FILE(13, 15, 0))

#endif
