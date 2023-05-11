#include "AnalysisManager.hxx"
#include "Parameters.hxx"
#include "ND280AnalysisUtils.hxx"
#include "VersioningUtils.hxx"
#include "SystematicUtils.hxx"
// Include converters
#include "RedoTreeConverter.hxx"
#include "MiniTreeConverter.hxx"

// Include systematics
#include "BFieldDistortionSystematics.hxx"
#include "MomentumScaleSystematics.hxx"
#include "MomentumResolSystematics.hxx"
#include "ToFResolSystematics.hxx"
#include "ECalEMEnergyResolSystematics.hxx"
#include "ECalEMEnergyScaleSystematics.hxx"

// Efficiency
#include "ChargeIDEffSystematics.hxx"
#include "TPCTrackEffSystematics.hxx"
#include "FGDTrackEffSystematics.hxx"
#include "FGDHybridTrackEffSystematics.hxx"
#include "TPCClusterEffSystematics.hxx"
#include "MichelElectronEffSystematics.hxx"
#include "ECalTrackEffSystematics.hxx"

// Matching
#include "TPCFGDMatchEffSystematics.hxx"
#include "TPCECalMatchEffSystematics.hxx"

// PID syst
#include "TPCPIDSystematics.hxx"
#include "FGDPIDSystematics.hxx"
#include "ECalEmHipPIDSystematics.hxx"
#include "ECalPIDSystematics.hxx"

// Weight
#include "PileUpSystematics.hxx"
#include "ECalPhotonPileUpSystematics.hxx"
#include "FGDMassSystematics.hxx"
#include "OOFVSystematics.hxx"
#include "SandMuonsSystematics.hxx"
#include "SIPionSystematics.hxx"
#include "SIProtonSystematics.hxx"
#include "FluxWeightSystematics.hxx"

// Nue
#include "FGD2ShowerSystematics.hxx"
#include "nueECalPileUpSystematics.hxx"
#include "nueOOFVSystematics.hxx"
#include "nueP0DPileUpSystematics.hxx"
#include "nueTPCPileUpSystematics.hxx"

// 4pi addition
#include "FGDECalMatchEffSystematics.hxx"
#include "FGDECalSMRDMatchEffSystematics.hxx"
#include "TPCP0DMatchEffSystematics.hxx"

// Include selections
// Numu FGD1
#include "numuCCSelection.hxx"
#include "numuCCMultiPiSelection.hxx"
#include "numuCC4piMultiPiSelection.hxx"
#include "numuCCMultiPiProtonSelection.hxx"
#include "numuCCMultiPiPhotonSelection.hxx"
#include "numuCCMultiPiPhotonProtonSelection.hxx"

// Numu FGD2
#include "numuCCFGD2Selection.hxx"
#include "numuCCMultiPiFGD2Selection.hxx"
#include "numuCC4piMultiPiFGD2Selection.hxx"
#include "numuCCMultiPiProtonFGD2Selection.hxx"
#include "numuCCMultiPiPhotonFGD2Selection.hxx"
#include "numuCCMultiPiPhotonProtonFGD2Selection.hxx"

// Numu Bkg in anti-numu, FGD1
#include "numuBkgInAntiNuModeCCSelection.hxx"
#include "numuBkgInAntiNuModeCCMultiTrackSelection.hxx"
#include "numuBkgInAntiNuModeCCMultiPiSelection.hxx"

// Numu Bkg in anti-numu, FGD2
#include "numuBkgInAntiNuModeCCFGD2Selection.hxx"
#include "numuBkgInAntiNuModeCCMultiTrackFGD2Selection.hxx"
#include "numuBkgInAntiNuModeCCMultiPiFGD2Selection.hxx"

// Anti-numu FGD1
#include "antiNumuCCSelection.hxx"
#include "antiNumuCCMultiTrackSelection.hxx"
#include "antiNumuCCMultiPiSelection.hxx"

// Anti-numu FGD2
#include "antiNumuCCFGD2Selection.hxx"
#include "antiNumuCCMultiTrackFGD2Selection.hxx"
#include "antiNumuCCMultiPiFGD2Selection.hxx"

// nue FGD1
#include "nueCCSelection.hxx"

// nue FGD2
#include "nueCCFGD2Selection.hxx"

// gamma FGD1
#include "gammaSelection.hxx"

// gamma FGD2
#include "gammaFGD2Selection.hxx"

// Anti-nue FGD1
#include "antiNueCCSelection.hxx"

// Anti-nue FGD2
#include "antiNueCCFGD2Selection.hxx"

// numu 4pi photon + proton FGD1
#include "numuCC4piMultiPiPhotonProtonSelection.hxx"

// numu 4pi photon + proton FGD2
#include "numuCC4piMultiPiPhotonProtonFGD2Selection.hxx"


//******************************************************************
AnalysisManager::AnalysisManager(){
  //******************************************************************

  _initialisePionSystematics = true;

  DefineProduction();
  DefineInputConverters();
  DefineSelections();
  DefineSystematics();

  //    ND::params().LoadParametersFile("psycheSelections");
  //    ND::params().LoadParametersFile("psycheSteering");
  //    ND::params().LoadParametersFile("psycheSystematics");

  _applyEventVariations      = (bool)ND::params().GetParameterI("psycheSteering.Systematics.ApplyVariationSystematics");
  _applyEventWeights         = (bool)ND::params().GetParameterI("psycheSteering.Systematics.ApplyWeightSystematics");
  _applyFluxWeightSystematic = (bool)ND::params().GetParameterI("psycheSteering.Systematics.ApplyFluxWeightSystematic");

  _flux= NULL;

  // enable/disable flux weighting.
  _applyFluxWeight = (bool)ND::params().GetParameterI("psycheSteering.FluxWeighting.Enable");

  // flux weight file and option
  _fluxFile    = ND::params().GetParameterS("psycheND280Utils.FluxWeighting.Folder");
  _fluxVersion = ND::params().GetParameterS("psycheND280Utils.FluxWeighting.Version");
  _fluxTuning  = ND::params().GetParameterS("psycheND280Utils.FluxWeighting.Tuning");

  if (_applyFluxWeight)
    _flux = new FluxWeighting(_fluxFile, _fluxVersion, _fluxTuning);


  _currentEvent       = -1;
  _exp                = NULL;
  _eventArray         = NULL;
  _samples.clear();
  _currentSampleGroup = NULL;
  _nEventsToProcess   = -1;
  _nEventsProcessed   = 0;
  _nEventsInArray     = 0;

  _mcEventArray       = NULL;
  _dataEventArray     = NULL;
  _nEventsInMCArray   = 0;
  _nEventsInDataArray = 0;
  _doFGD1             = true;
  _doFGD2             = false;
  _main_sel           = -999;

}

//******************************************************************
void AnalysisManager::DefineInputConverters(){
  //******************************************************************
  input().AddConverter("kHighlandTree",  new RedoTreeConverter());
  input().AddConverter("MiniTree",       new MiniTreeConverter());
  //  input().AddConverter(kHighlandTree,  new HighlandTreeConverter());
  //  input().AddConverter(kP0d,       new P0dTreeConverter());
}

//******************************************************************
void AnalysisManager::DefineProduction(){
  //********************************************************************


  // Select the production from the parameters file. This will be used for POT, ...
  if (ND::params().GetParameterI("psycheSteering.POT.Production")==6){
    versionUtils::prod_POT = versionUtils::kProd6;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.POT.Production == 6" << std::endl;
  }
  else if (ND::params().GetParameterI("psycheSteering.POT.Production")==7){
    versionUtils::prod_POT = versionUtils::kProd7;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.POT.Production == 7" << std::endl;
  }

  // Select the production from the parameters file. This will be used for bunching, ...
  if (ND::params().GetParameterI("psycheSteering.Bunching.Production")==6){
    versionUtils::prod_bunching = versionUtils::kProd6;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.Bunching.Production == 6" << std::endl;
  }
  else if (ND::params().GetParameterI("psycheSteering.Bunching.Production")==7){
    versionUtils::prod_bunching = versionUtils::kProd7;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.Bunching.Production == 7" << std::endl;
  }

  // Select the production from the parameters file. This will be used for corrections
  if (ND::params().GetParameterI("psycheSteering.Corrections.Production")==6){
    versionUtils::prod_corrections = versionUtils::kProd6;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.Corrections.Production == 6" << std::endl;
  }
  else if (ND::params().GetParameterI("psycheSteering.Corrections.Production")==7){
    versionUtils::prod_corrections = versionUtils::kProd7;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.Corrections.Production == 7" << std::endl;
  }

  // Select the production from the parameters file. This will be used for systematics
  if (ND::params().GetParameterI("psycheSteering.Systematics.Production")==6){
    versionUtils::prod_systematics = versionUtils::kProd6;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.Systematics.Production == 6" << std::endl;
  }
  else if (ND::params().GetParameterI("psycheSteering.Systematics.Production")==7){
    versionUtils::prod_systematics = versionUtils::kProd7;
    std::cout << "WARNING: production has been overwritten by parameter psycheSteering.Systematics.Production == 7" << std::endl;
  }

  // Select the production from the parameters file. This will be used for run numbering scheme
  if (ND::params().GetParameterI("psycheSteering.RunNumbering.Production.Scheme") == versionUtils::kProd6TNum){ 
    versionUtils::run_numbering_scheme = versionUtils::kProd6TNum;
    std::cout << "Production has been overwritten by parameter psycheSteering.RunNumbering.Production.Scheme == " <<  versionUtils::run_numbering_scheme << std::endl;
  }
  else if (ND::params().GetParameterI("psycheSteering.RunNumbering.Production.Scheme") == versionUtils::kPreProd6TNum){ 
    versionUtils::run_numbering_scheme = versionUtils::kPreProd6TNum;
    std::cout << "Production has been overwritten by parameter psycheSteering.RunNumbering.Production.Scheme == " <<  versionUtils::run_numbering_scheme << std::endl;

  }
  else if (ND::params().GetParameterI("psycheSteering.RunNumbering.Production.Scheme") == versionUtils::kProd7Num){ 
    versionUtils::run_numbering_scheme = versionUtils::kProd7Num;
    std::cout << "Production has been overwritten by parameter psycheSteering.RunNumbering.Production.Scheme == " <<  versionUtils::run_numbering_scheme << std::endl;

  }


}

//******************************************************************
void AnalysisManager::DefineSelections(){
  //******************************************************************

  _StrictExclusiveness = (bool)ND::params().GetParameterI("psycheSteering.Selection.EnsureStrictExclusiveness");
  if(!_StrictExclusiveness){
    std::cout << "AnalysisManager WARNING: The selection do not have to be exclusive to run." << std::endl;
    std::cout << "AnalysisManager WARNING: This is fine but you should be careful because the order in which you sel().AddSelection() now matters!!" << std::endl;
  }
  // Numu FGD1
  sel().AddSelection("kTrackerNumuCC",                       "inclusive numuCC selection",                           new numuCCSelection());
  sel().AddSelection("kTrackerNumuCCMultiPi",                "numuCC MultiPi selection",                             new numuCCMultiPiSelection());
  sel().AddSelection("kTrackerNumuCCMultiPiProton",          "numuCC MultiPi-Proton selection",                      new numuCCMultiPiProtonSelection());
  sel().AddSelection("kTrackerNumuCCMultiPiPhoton",          "numuCC MultiPi-Photon selection",                      new numuCCMultiPiPhotonSelection());
  sel().AddSelection("kTrackerNumuCCMultiPiPhotonProton",    "numuCC MultiPi-Photon-Proton selection",               new numuCCMultiPiPhotonProtonSelection());
  sel().AddSelection("kTrackerNumuCC4piMultiPi",             "numuCC 4pi MultiPi selection",                         new numuCC4piMultiPiSelection());
  sel().AddSelection("kTrackerNumuCC4piMultiPiPhotonProton", "numuCC 4pi MultiPi Photon selection + proton",         new numuCC4piMultiPiPhotonProtonSelection());

  // Anti-numu FGD1
  sel().AddSelection("kTrackerAntiNumuCC",           "antiNumuCC selection",            new antiNumuCCSelection());
  sel().AddSelection("kTrackerAntiNumuCCMultiTrack", "antiNumuCC MultiTrack selection", new antiNumuCCMultiTrackSelection());
  sel().AddSelection("kTrackerAntiNumuCCMultiPi",    "antiNumuCC MultiPi selection",    new antiNumuCCMultiPiSelection());

  // Numu Bkg in anti-numu, FGD1
  sel().AddSelection("kTrackerNumuInAntiNuModeCC",           "numuBkg In AntiNuMode CC selection",           new numuBkgInAntiNuModeCCSelection());
  sel().AddSelection("kTrackerNumuInAntiNuModeCCMultiTrack", "numuBkg In AntiNuMode CCMultiTrack selection", new numuBkgInAntiNuModeCCMultiTrackSelection());
  sel().AddSelection("kTrackerNumuInAntiNuModeCCMultiPi",    "numuBkg In AntiNuMode CCMultiPi selection",    new numuBkgInAntiNuModeCCMultiPiSelection());

  // Numu FGD2
  sel().AddSelection("kTrackerNumuCCFGD2",                    "inclusive numuCC selection in FGD2",                   new numuCCFGD2Selection());
  sel().AddSelection("kTrackerNumuCCMultiPiFGD2",             "numuCC MultiPi selection in FGD2",                     new numuCCMultiPiFGD2Selection());
  sel().AddSelection("kTrackerNumuCCMultiPiProtonFGD2",       "numuCC MultiPi-Proton selection in FGD2",              new numuCCMultiPiProtonFGD2Selection());
  sel().AddSelection("kTrackerNumuCCMultiPiPhotonFGD2",       "numuCC MultiPi-Photon selection in FGD2",              new numuCCMultiPiPhotonFGD2Selection());
  sel().AddSelection("kTrackerNumuCCMultiPiPhotonProtonFGD2", "numuCC MultiPi-Photon-Proton selection in FGD2",       new numuCCMultiPiPhotonProtonFGD2Selection());
  sel().AddSelection("kTrackerNumuCC4piMultiPiFGD2",              "numuCC 4pi MultiPi selection FGD2",                         new numuCC4piMultiPiFGD2Selection());
  sel().AddSelection("kTrackerNumuCC4piMultiPiPhotonProtonFGD2",  "numuCC 4pi MultiPi Photon selection + proton in FGD2", new numuCC4piMultiPiPhotonProtonFGD2Selection());


  // Anti-numu FGD2
  sel().AddSelection("kTrackerAntiNumuCCFGD2",           "antiNumuCC selection in FGD2",            new antiNumuCCFGD2Selection());
  sel().AddSelection("kTrackerAntiNumuCCMultiTrackFGD2", "antiNumuCC MultiTrack selection in FGD2", new antiNumuCCMultiTrackFGD2Selection());
  sel().AddSelection("kTrackerAntiNumuCCMultiPiFGD2",    "antiNumuCC MultiPi selection in FGD2",    new antiNumuCCMultiPiFGD2Selection());

  // Numu Bkg in anti-numu, FGD2
  sel().AddSelection("kTrackerNumuInAntiNuModeCCFGD2",           "numuBkg In AntiNuMode CC selection in FGD2",           new numuBkgInAntiNuModeCCFGD2Selection());
  sel().AddSelection("kTrackerNumuInAntiNuModeCCMultiTrackFGD2", "numuBkg In AntiNuMode CCMultiTrack selection in FGD2", new numuBkgInAntiNuModeCCMultiTrackFGD2Selection());
  sel().AddSelection("kTrackerNumuInAntiNuModeCCMultiPiFGD2",    "numuBkg In AntiNuMode CCMultiPi selection in FGD2",    new numuBkgInAntiNuModeCCMultiPiFGD2Selection());

  // FGD1 nue
  sel().AddSelection("kTrackerNuECC",     "NuECC inclusive selection",     new nueCCSelection    ());
  sel().AddSelection("kTrackerAntiNuECC", "AntiNuECC inclusive selection", new antiNueCCSelection());
  sel().AddSelection("kTrackerGamma",     "GammaBkg selection",            new gammaSelection    ());

  // FGD2 nue
  sel().AddSelection("kTrackerNuECCFGD2",     "NuECC inclusive selection in FGD2",     new nueCCFGD2Selection    ());
  sel().AddSelection("kTrackerAntiNuECCFGD2", "AntiNuECC inclusive selection in FGD2", new antiNueCCFGD2Selection());
  sel().AddSelection("kTrackerGammaFGD2",     "GammaBkg selection in FGD2",            new gammaFGD2Selection    ());

  // Set which run range the selections are valid for using the parameters file
  // If this is not called the selections are applied to all run periods
  // Numu FGD1
  sel().SetValidRunPeriods("kTrackerNumuCC",                        ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPi",                 ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPiProton",           ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPiPhoton",           ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPiPhotonProton",     ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCC4piMultiPi",              ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCC4piMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCC4piMultiPiPhotonProton",  ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCC4piMultiPi.ValidRunPeriods"));


  // Anti-numu FGD1
  sel().SetValidRunPeriods("kTrackerAntiNumuCC",           ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNumuCC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerAntiNumuCCMultiTrack", ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNumuCCMultiTrack.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerAntiNumuCCMultiPi",    ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNumuCCMultiPi.ValidRunPeriods"));

  // Numu Bkg in anti-numu, FGD1
  sel().SetValidRunPeriods("kTrackerNumuInAntiNuModeCC",           ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuInAntiNuModeCC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuInAntiNuModeCCMultiTrack", ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuInAntiNuModeCCMultiTrack.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuInAntiNuModeCCMultiPi",    ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuInAntiNuModeCCMultiPi.ValidRunPeriods"));


  // Same periods as for FGD1
  // Numu FGD2
  sel().SetValidRunPeriods("kTrackerNumuCCFGD2",                       ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPiFGD2",                ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPiProtonFGD2",          ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPiPhotonFGD2",          ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCCMultiPiPhotonProtonFGD2",    ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCCMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCC4piMultiPiFGD2",             ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCC4piMultiPi.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuCC4piMultiPiPhotonProtonFGD2", ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuCC4piMultiPi.ValidRunPeriods"));


  // Anti-numu FGD2
  sel().SetValidRunPeriods("kTrackerAntiNumuCCFGD2",           ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNumuCC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerAntiNumuCCMultiTrackFGD2", ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNumuCCMultiTrack.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerAntiNumuCCMultiPiFGD2",    ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNumuCCMultiPi.ValidRunPeriods"));

  // Numu Bkg in anti-numu, FGD2
  sel().SetValidRunPeriods("kTrackerNumuInAntiNuModeCCFGD2",           ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuInAntiNuModeCC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuInAntiNuModeCCMultiTrackFGD2", ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuInAntiNuModeCCMultiTrack.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerNumuInAntiNuModeCCMultiPiFGD2",    ND::params().GetParameterS("psycheSteering.Selections.TrackerNumuInAntiNuModeCCMultiPi.ValidRunPeriods"));

  // FGD1 nue
  sel().SetValidRunPeriods("kTrackerNuECC",     ND::params().GetParameterS("psycheSteering.Selections.TrackerNuECC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerAntiNuECC", ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNuECC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerGamma",     ND::params().GetParameterS("psycheSteering.Selections.TrackerGamma.ValidRunPeriods"));

  // FGD2 nue
  sel().SetValidRunPeriods("kTrackerNuECCFGD2",     ND::params().GetParameterS("psycheSteering.Selections.TrackerNuECC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerAntiNuECCFGD2", ND::params().GetParameterS("psycheSteering.Selections.TrackerAntiNuECC.ValidRunPeriods"));
  sel().SetValidRunPeriods("kTrackerGammaFGD2",     ND::params().GetParameterS("psycheSteering.Selections.TrackerGamma.ValidRunPeriods"));

  // Numu FGD1
  if (!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCC"))
    sel().DisableSelection("kTrackerNumuCC");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPi"))
    sel().DisableSelection("kTrackerNumuCCMultiPi");  

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPiProton"))
    sel().DisableSelection("kTrackerNumuCCMultiPiProton");  

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPiPhoton"))
    sel().DisableSelection("kTrackerNumuCCMultiPiPhoton");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPiPhotonProton"))
    sel().DisableSelection("kTrackerNumuCCMultiPiPhotonProton"); 

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCC4piMultiPi"))
    sel().DisableSelection("kTrackerNumuCC4piMultiPi");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCC4piMultiPiPhotonProton"))
    sel().DisableSelection("kTrackerNumuCC4piMultiPiPhotonProton");

  // Anti-numu FGD1
  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNumuCC"))
    sel().DisableSelection("kTrackerAntiNumuCC");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNumuCCMultiTrack"))
    sel().DisableSelection("kTrackerAntiNumuCCMultiTrack");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNumuCCMultiPi"))
    sel().DisableSelection("kTrackerAntiNumuCCMultiPi");

  // Numu Bkg in anti-numu, FGD1
  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuInAntiNuModeCC"))
    sel().DisableSelection("kTrackerNumuInAntiNuModeCC");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuInAntiNuModeCCMultiTrack"))
    sel().DisableSelection("kTrackerNumuInAntiNuModeCCMultiTrack");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuInAntiNuModeCCMultiPi"))
    sel().DisableSelection("kTrackerNumuInAntiNuModeCCMultiPi"); 


  // Numu FGD2
  if (!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCFGD2"))
    sel().DisableSelection("kTrackerNumuCCFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPiFGD2"))
    sel().DisableSelection("kTrackerNumuCCMultiPiFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPiProtonFGD2"))
    sel().DisableSelection("kTrackerNumuCCMultiPiProtonFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPiPhotonFGD2"))
    sel().DisableSelection("kTrackerNumuCCMultiPiPhotonFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCCMultiPiPhotonProtonFGD2"))
    sel().DisableSelection("kTrackerNumuCCMultiPiPhotonProtonFGD2");
  
  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCC4piMultiPiFGD2"))
    sel().DisableSelection("kTrackerNumuCC4piMultiPiFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuCC4piMultiPiPhotonProtonFGD2"))
    sel().DisableSelection("kTrackerNumuCC4piMultiPiPhotonProtonFGD2");

  // Anti-numu FGD2
  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNumuCCFGD2"))
    sel().DisableSelection("kTrackerAntiNumuCCFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNumuCCMultiTrackFGD2"))
    sel().DisableSelection("kTrackerAntiNumuCCMultiTrackFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNumuCCMultiPiFGD2"))
    sel().DisableSelection("kTrackerAntiNumuCCMultiPiFGD2"); 

  // Numu Bkg in anti-numu, FGD2
  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuInAntiNuModeCCFGD2"))
    sel().DisableSelection("kTrackerNumuInAntiNuModeCCFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuInAntiNuModeCCMultiTrackFGD2"))
    sel().DisableSelection("kTrackerNumuInAntiNuModeCCMultiTrackFGD2");

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNumuInAntiNuModeCCMultiPiFGD2"))
    sel().DisableSelection("kTrackerNumuInAntiNuModeCCMultiPiFGD2");

  // FGD1 nue
  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNuECC"))
    sel().DisableSelection("kTrackerNuECC");     

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNuECC"))
    sel().DisableSelection("kTrackerAntiNuECC"); 

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerGamma"))
    sel().DisableSelection("kTrackerGamma");        

  // FGD2 nue
  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerNuECCFGD2"))
    sel().DisableSelection("kTrackerNuECCFGD2");     

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerAntiNuECCFGD2"))
    sel().DisableSelection("kTrackerAntiNuECCFGD2"); 

  if(!ND::params().GetParameterI("psycheSteering.Selections.EnableTrackerGammaFGD2"))
    sel().DisableSelection("kTrackerGammaFGD2");     

}

//******************************************************************
void AnalysisManager::DefineSystematics(){
  //******************************************************************

  //--------------- Add Systematic Variations specifying the number of bins in the PDF
  evar().AddEventVariation(SystId::kBFieldDist,  "BFieldDist",  new BFieldDistortionSystematics());
  evar().AddEventVariation(SystId::kMomScale,    "MomScale",    new MomentumScaleSystematics());
  evar().AddEventVariation(SystId::kMomResol,    "MomResol",    new MomentumResolSystematics());
  evar().AddEventVariation(SystId::kTpcPid,      "TpcPid",      new TPCPIDSystematics());
  evar().AddEventVariation(SystId::kFgdPid,      "FgdPid",      new FGDPIDSystematics());
  evar().AddEventVariation(SystId::kToFResol,    "ToFResol",    new ToFResolSystematics());
  evar().AddEventVariation(SystId::kECalEMScale, "ECalEMScale", new ECalEMEnergyScaleSystematics());
  evar().AddEventVariation(SystId::kECalEMResol, "ECalEMResol", new ECalEMEnergyResolSystematics());

  //-------------- Add Systematics Weights
  eweight().AddEventWeight(SystId::kChargeIDEff,       "ChargeIDEff",       new ChargeIDEffSystematics());
  eweight().AddEventWeight(SystId::kTpcClusterEff,     "TpcClusterEff",     new TPCClusterEffSystematics());
  eweight().AddEventWeight(SystId::kTpcTrackEff,       "TpcTrackEff",       new TPCTrackEffSystematics());
  eweight().AddEventWeight(SystId::kTpcFgdMatchEff,    "TpcFgdMatchEff",    new TPCFGDMatchEffSystematics());
  eweight().AddEventWeight(SystId::kFgdTrackEff,       "FgdTrackEff",       new FGDTrackEffSystematics());
  eweight().AddEventWeight(SystId::kFgdHybridTrackEff, "FgdHybridTrackEff", new FGDHybridTrackEffSystematics());
  eweight().AddEventWeight(SystId::kMichelEleEff,      "MichelEleEff",      new MichelElectronEffSystematics());
  eweight().AddEventWeight(SystId::kPileUp,            "PileUp",            new PileUpSystematics());
  eweight().AddEventWeight(SystId::kFgdMass,           "FgdMass",           new FGDMassSystematics());
  eweight().AddEventWeight(SystId::kOOFV,              "OOFV",              new OOFVSystematics());
  eweight().AddEventWeight(SystId::kSIPion,            "SIPion",            new SIPionSystematics());
  eweight().AddEventWeight(SystId::kSIProton,          "SIProton",          new SIProtonSystematics());
  eweight().AddEventWeight(SystId::kSandMu,            "SandMu",            new SandMuonsSystematics());
  eweight().AddEventWeight(SystId::kECalPID,           "ECalPID",           new ECalPIDSystematics());
  eweight().AddEventWeight(SystId::kTpcECalMatchEff,   "TpcECalMatchEff",   new TPCECalMatchEffSystematics());
  eweight().AddEventWeight(SystId::kECalEmHipPID,      "ECalEmHipPID",      new ECalEmHipPIDSystematics());
  eweight().AddEventWeight(SystId::kECalPhotonPileUp,  "ECalPhotonPileUp",  new ECalPhotonPileUpSystematics());
  eweight().AddEventWeight(SystId::kECalTrackEff,      "ECalTrackEff",      new ECalTrackEffSystematics());

  // Nue specific
  eweight().AddEventWeight(SystId::kFGD2Shower,        "FGD2Shower",        new FGD2ShowerSystematics());
  eweight().AddEventWeight(SystId::kNuETPCPileUp,      "NuETPCPileUp",      new nueTPCPileUpSystematics());
  eweight().AddEventWeight(SystId::kNuEP0DPileUp,      "NuEP0DPileUp",      new nueP0DPileUpSystematics());
  eweight().AddEventWeight(SystId::kNuEECalPileUp,     "NuEECalPileUp",     new nueECalPileUpSystematics());
  eweight().AddEventWeight(SystId::kNuEOOFV,           "NuEOOFV",           new nueOOFVSystematics());

  eweight().AddEventWeight(SystId::kFgdECalSmrdMatchEff,      "FgdECalSmrdMatchEff",        new FGDECalSMRDMatchEffSystematics());
  eweight().AddEventWeight(SystId::kTpcP0dMatchEff,           "TpcP0dMatchEff",             new TPCP0DMatchEffSystematics());
  eweight().AddEventWeight(SystId::kFgdECalMatchEff,          "FgdECalMatchEff",            new FGDECalMatchEffSystematics());


  //-------------- Enable systematics in the different event selections

  // First disable all systematics and all the event weight and variations
  syst()   .DisableAllSystematics();
  eweight().DisableAllEventWeights();
  evar()   .DisableAllEventVariations();

  _initialisePionSystematics = (bool) ND::params().GetParameterI("psycheSteering.Weights.EnableSIPion");

  // Then enable the ones specified in the parameters file
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableBFieldDist"))        evar().EnableEventVariation(SystId::kBFieldDist);
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableMomScale"))          evar().EnableEventVariation(SystId::kMomScale);
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableMomResol"))          evar().EnableEventVariation(SystId::kMomResol);
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableTpcPid"))            evar().EnableEventVariation(SystId::kTpcPid);
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableFgdPid"))            evar().EnableEventVariation(SystId::kFgdPid);
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableToFResol"))          evar().EnableEventVariation(SystId::kToFResol);
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableECalMomScale"))      evar().EnableEventVariation(SystId::kECalEMScale);
  if(ND::params().GetParameterI("psycheSteering.Variations.EnableECalMomResol"))      evar().EnableEventVariation(SystId::kECalEMResol);

  if(ND::params().GetParameterI("psycheSteering.Weights.EnableChargeConf"))        eweight().EnableEventWeight(SystId::kChargeIDEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableTpcClusterEff"))     eweight().EnableEventWeight(SystId::kTpcClusterEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableTpcTrackEff"))       eweight().EnableEventWeight(SystId::kTpcTrackEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableTpcFgdMatchEff"))    eweight().EnableEventWeight(SystId::kTpcFgdMatchEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableFgdTrackEff"))       eweight().EnableEventWeight(SystId::kFgdTrackEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableFgdHybridTrackEff")) eweight().EnableEventWeight(SystId::kFgdHybridTrackEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableMichelEleEff"))      eweight().EnableEventWeight(SystId::kMichelEleEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnablePileUp"))            eweight().EnableEventWeight(SystId::kPileUp);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableFgdMass"))           eweight().EnableEventWeight(SystId::kFgdMass);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableOOFV"))              eweight().EnableEventWeight(SystId::kOOFV);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableSIPion"))            eweight().EnableEventWeight(SystId::kSIPion);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableSIProton"))          eweight().EnableEventWeight(SystId::kSIProton);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableSandMuons"))         eweight().EnableEventWeight(SystId::kSandMu);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableECalPID"))           eweight().EnableEventWeight(SystId::kECalPID);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableTpcECalMatchEff"))   eweight().EnableEventWeight(SystId::kTpcECalMatchEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableECalEmHipPID"))      eweight().EnableEventWeight(SystId::kECalEmHipPID);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableECalPhotonPileUp"))  eweight().EnableEventWeight(SystId::kECalPhotonPileUp);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableECalTrackEff"))      eweight().EnableEventWeight(SystId::kECalTrackEff);

  if(ND::params().GetParameterI("psycheSteering.Weights.EnableFGD2Shower"))        eweight().EnableEventWeight(SystId::kFGD2Shower); 
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableNuETPCPileUp"))      eweight().EnableEventWeight(SystId::kNuETPCPileUp);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableNuEP0DPileUp"))      eweight().EnableEventWeight(SystId::kNuEP0DPileUp);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableNuEECalPileUp"))     eweight().EnableEventWeight(SystId::kNuEECalPileUp);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableNuEOOFV"))           eweight().EnableEventWeight(SystId::kNuEOOFV);

  if(ND::params().GetParameterI("psycheSteering.Weights.EnableFGDECalSMRDMatchEff"))       eweight().EnableEventWeight(SystId::kFgdECalSmrdMatchEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableTPCP0DMatchEff"))            eweight().EnableEventWeight(SystId::kTpcP0dMatchEff);
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableFGDECalMatchEff"))           eweight().EnableEventWeight(SystId::kFgdECalMatchEff);

  // Only add flux systematic if we want to vary it - otherwise this messes up the systematic parameter counting since flux parameters are always included even if not enabled
  if(ND::params().GetParameterI("psycheSteering.Weights.EnableFlux")){
    syst().AddFluxSystematic(SystId::kFluxWeight,        "FluxWeight",        new FluxWeightSystematics(_applyFluxWeightSystematic )); 
    syst().EnableSystematic(SystId::kFluxWeight);
  }


  // Temporary: We need to add weights and variations to the systematic manager. TODO
  for (UInt_t i=0;i<eweight().GetNEventWeights();i++){
    EventWeightBase* it = eweight().GetEventWeights()[i];
    if(it->IsEnabled()) syst().AddWeightSystematic(it->GetIndex(), it->GetName(), it);
  }
  for (UInt_t i=0;i<evar().GetNEventVariations();i++){
    EventVariationBase* it = evar().GetEventVariations()[i];
    if(it->IsEnabled()) syst().AddVariationSystematic(it->GetIndex(), it->GetName(), it);
  }

  // Construct the Cov. matrix
  syst().ConstructCovarianceMatrix();


}

//******************************************************************
bool AnalysisManager::ProcessEvent(const ToyExperiment& toy, AnaEventB& event, std::vector<Weight_h>& totalWeightSystVector, std::vector<Weight_h>& fluxWeightSystVector){
  //******************************************************************

  // Method not computing the POTweight
  Float_t POTweight;
  return ProcessEvent(toy,event,totalWeightSystVector,fluxWeightSystVector,POTweight);
}

//******************************************************************
bool AnalysisManager::ProcessEvent(AnaEventB& event){
  //******************************************************************

  // Configure the toy experiment. variation for each of the systematics
  Float_t POTweight;
  // Process the current event (bunch). That means applying the systematics, the selections and computing the weights
  return ProcessEvent(event, POTweight);
}




//******************************************************************
bool AnalysisManager::ProcessEvent(const ToyExperiment& toy, 
    AnaEventB& event, 
    std::vector<Weight_h>& totalWeightSystVector, 
    std::vector<Weight_h>& fluxWeightSystVector,
    Float_t& POTweight){
  //******************************************************************

  /*
     This Method Process one event. That means:

     1. Apply systematic variations
     2. Loop over selections. And for each selection:
     2a. Apply all steps
     2b. Compute the systematic weight when all cuts are passed

Input:
- AnaEventB, but the one to be modified (event). Contains the SystBox

- ToyExperiment,  the toy experiment definition with the variation for each systematic (toy)
Output:
- EventSummary (part of the AnaEventB) containing high level info (candidate, etc)
- The vector of weights for each selection

Return value:
- true when at least one selection has been passed

*/
  bool passed=false;

  /// The vector of systematic weights (one entry per systematic)
  Int_t nWeightSyst= eweight().GetNEnabledEventWeights();
  Weight_h* weightSystDummy = NULL;

  /// Clear the vector of weight and flux systematics (a entry per selection)
  totalWeightSystVector.clear();
  fluxWeightSystVector.clear();

  /// Apply the systematics variations (for all selections)
  /// The event will be modified. All actions below should proceed on the modified event
  if (evar().GetNEventVariations() && _applyEventVariations && event.GetIsMC()){
    // First, reset the event to the original data
    evar().UndoEventVariations(event);
    // Now apply variations to original spill
    evar().ApplyEventVariations(toy, event);
  }


  // Reset event summary sample before applying all selections
  static_cast<AnaEventSummaryB*>(event.Summary)->ResetSummary();

  /// Loop over selections
  for (std::vector<SelectionBase*>::iterator it=sel().GetSelections().begin();it!=sel().GetSelections().end();it++){
    SelectionBase& selec = **it;
    // only enabled selections
    if (!selec.IsEnabled()) continue;
    // check we should apply this selection to this run period
    if (!CheckSelectionAgainstRunPeriod(*it, anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run))) continue;

    selec.InitializeToy(&event);

    /// Initialize the Flux Weight Systematic to 1 (in the case it is not applied)
    Weight_h fluxWeightSyst = 1.;

    /// Initialize the  total weight of Weight Systematics to 1 (in the case they are not applied)
    Weight_h  totalWeightSyst = 1;
    bool redo;
    bool passed_temp = selec.Apply(event,redo);

    if (passed_temp && event.GetIsMC()){


      anaUtils::CreateArray(weightSystDummy, nWeightSyst);

      /// Apply the flux weight
      if (_flux && event.Summary && !event.GetIsSandMC())
        if (static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[selec.GetSampleId()])
          fluxWeightSyst = _flux->GetWeight(static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[selec.GetSampleId()], anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run));

      /// Compute the weight for this selection by applying the systematic weights.
      if (_applyEventWeights || _applyFluxWeightSystematic){
        // apply the detector weight systematics
        if (_applyEventWeights){
          totalWeightSyst = eweight().ComputeEventWeights(selec, toy, event, selec.GetPreviousToyBox(event), weightSystDummy);

          delete [] weightSystDummy;
          weightSystDummy = NULL;
        }
        // apply the Flux systematic independently
        if (_applyFluxWeightSystematic && !event.GetIsSandMC()){
          fluxWeightSyst = syst().ApplyFluxSystematics(toy, event, selec.GetPreviousToyBox(event));
        }
      }
    }

    // add the total weight and flux weight to the vector
    totalWeightSystVector.push_back(totalWeightSyst);
    fluxWeightSystVector.push_back(fluxWeightSyst);

    // If any of the selections is passed the overall passed is true
    if (passed_temp){

      Int_t isel = selec.GetEnabledIndex();
      SetSelectedSelection(isel);
      passed=true;

    }
    selec.FinalizeToy(&event);
  }

  // computes the POT normalization for the current event
  if (_currentSampleGroup){
    Float_t POTdata=0;
    Float_t POTmc=0;
    Float_t POTsand=0;
    _currentSampleGroup->GetPOT(POTdata, POTmc, POTsand);
    POTweight = POTdata/POTmc;
  }

  if (weightSystDummy)
    delete [] weightSystDummy;

  return passed;
}


//******************************************************************
bool AnalysisManager::ProcessEventWithIndividualWeightSyst(
    const ToyExperiment& toy,
    AnaEventB& event,
    Weight_h* WeightSyst, 
    Weight_h& fluxWeightSyst){
  //******************************************************************
  /*
     This Method Process one event. That means:

     1. Apply systematic variations
     2. Loop over selections. And for each selection:
     2a. Apply all steps
     2b. Compute the systematic weight when all cuts are passed

Input:
- AnaEventB, but the one to be modified (event). Contains the SystBox

- ToyExperiment,  the toy experiment definition with the variation for each systematic (toy)
Output:
- EventSummary (part of the AnaEventB) containing high level info (candidate, etc)
- The vector of weights for each weight systemati

Return value:
- true when at least one selection has been passed

*/
  bool passed=false;
  /// Apply the systematics variations (for all selections)
  /// The event will be modified. All actions below should proceed on the modified event
  if (evar().GetNEventVariations() && _applyEventVariations && event.GetIsMC()){
    // First, reset the event to the original data
    evar().UndoEventVariations(event);
    // Now apply variations to original spill
    evar().ApplyEventVariations(toy, event);
  }

  // Reset event summary sample before applying all selections
  static_cast<AnaEventSummaryB*>(event.Summary)->ResetSummary();

  /// Loop over selections
  for (std::vector<SelectionBase*>::iterator it=sel().GetSelections().begin();it!=sel().GetSelections().end();it++){
    SelectionBase& selec = **it;

    // only enabled selections
    if (!selec.IsEnabled()) continue;

    // check we should apply this selection to this run period
    if (!CheckSelectionAgainstRunPeriod(*it, anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run))) continue;

    /// Initialize the Flux Weight Systematic to 1 (in the case it is not applied)
    fluxWeightSyst = 1.;

    bool redo;

    selec.InitializeToy(&event);

    bool passed_temp = selec.Apply(event,redo);

    if (passed_temp && event.GetIsMC()){

      /// Apply the flux weight
      if (_flux && event.Summary && !event.GetIsSandMC())
        if (static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[selec.GetSampleId()])
          fluxWeightSyst = _flux->GetWeight(static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[selec.GetSampleId()],
              anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run));

      /// Compute the weight for this selection by applying the systematic weights.
      if (_applyEventWeights || _applyFluxWeightSystematic){
        // apply the detector weight systematics
        if (_applyEventWeights){
          eweight().ComputeEventWeightsWithSystId(selec, toy, event, selec.GetPreviousToyBox(event), WeightSyst);
          // apply the Flux systematic independently
          if (_applyFluxWeightSystematic && !event.GetIsSandMC()){
            fluxWeightSyst = syst().ApplyFluxSystematics(toy, event, selec.GetPreviousToyBox(event));
          }
        }
      }

      // If any of the selections is passed the overall passed is true
      if (passed_temp){

        Int_t isel = selec.GetEnabledIndex();
        SetSelectedSelection(isel);
        passed=true;
      }
    }
    selec.FinalizeToy(&event);

  }

  return passed;
}

//******************************************************************
bool AnalysisManager::ProcessEvent(const ToyExperiment& toy, AnaEventB& event, Weight_h& totalweight,Weight_h& fluxWeightSyst){
  //******************************************************************

  /// The vector of systematic weights (one entry per systematic)
  Int_t nWeightSyst= eweight().GetNEnabledEventWeights();
  Weight_h* weightSystDummy = NULL;

  anaUtils::CreateArray(weightSystDummy, nWeightSyst);
  bool passed = ProcessEvent(toy, event, totalweight, fluxWeightSyst, weightSystDummy);
  delete [] weightSystDummy;
  return passed;

}
//******************************************************************
bool AnalysisManager::ProcessEvent(const ToyExperiment& toy, AnaEventB& event, Weight_h& totalweight,Weight_h& fluxWeightSyst, Weight_h* weights){
  //******************************************************************

  /*
     This Method Process one event. That means:

     1. Apply systematic variations
     2. Loop over selections. And for each selection:
     2a. Apply all steps
     2b. Compute the systematic weight when all cuts are passed

Input:
- AnaEventB, but the one to be modified (event). Contains the SystBox

- ToyExperiment,  the toy experiment definition with the variation for each systematic (toy)
Output:
- EventSummary (part of the AnaEventB) containing high level info (candidate, etc)
- The vector of weights for each selection

Return value:
- true when at least one selection has been passed

*/
  bool passed=false;

  /// Apply the systematics variations (for all selections)
  /// The event will be modified. All actions below should proceed on the modified event
  if (evar().GetNEventVariations() && _applyEventVariations && event.GetIsMC()){
    // First, reset the event to the original data
    evar().UndoEventVariations(event);
    //GetSystematicVariationIndex(const std::string& name)
    // Now apply variations to original spill
    evar().ApplyEventVariations(toy, event);
  }

  // Reset event summary sample before applying all selections
  static_cast<AnaEventSummaryB*>(event.Summary)->ResetSummary();
  /// Loop over selections
  for (std::vector<SelectionBase*>::iterator it=sel().GetSelections().begin();it!=sel().GetSelections().end();it++){
    SelectionBase& selec = **it;
    // only enabled selections
    if (!selec.IsEnabled()) continue;
    if (!CheckSelectionAgainstRunPeriod(*it, anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run))) continue;

    selec.InitializeToy(&event);

    // std::cout << "The selection now being applied is: "<< selec.Name() << std::endl;
    // check we should apply this selection to this run period

    /// Initialize the Flux Weight Systematic to 1 (in the case it is not applied)
    fluxWeightSyst = 1.;

    /// Initialize the  total weight of Weight Systematics to 1 (in the case they are not applied)
    totalweight = 1;

    bool redo = false;


    bool passed_temp = selec.Apply(event,redo);


    if(_StrictExclusiveness && passed_temp && passed){
      std::cerr << "ERROR: DOUBLE EVENT SELECTION with: " << std::endl;
      for (std::vector<SelectionBase*>::iterator it2=sel().GetSelections().begin();it2!=sel().GetSelections().end();++it2){
        SelectionBase& selec2 = **it2;

        // only enabled selections
        if (!selec2.IsEnabled()) continue;

        // check we should apply this selection to this run period
        if (!CheckSelectionAgainstRunPeriod(*it2, anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run))) continue;

        selec.InitializeToy(&event);
        bool passed2 = selec2.Apply(event,redo);

        selec.FinalizeToy(&event);
        if(passed2){
          AnaEventSummaryB* summary = static_cast<AnaEventSummaryB*>(event.Summary);
          std::cerr << "ERROR: - " << selec2.Name() << "  " << SampleId::ConvertSample(summary->EventSample) << std::endl;
        }
      }
      std::cerr << "ERROR: For now exit, modify the selection so that they are orthogonal!!" << std::endl;
      throw;
    }
    if(passed_temp) passed = 1;


    if (passed_temp && event.GetIsMC()){

      /// Apply the flux weight
      if (_flux && event.Summary)
        if (static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[selec.GetSampleId()] && !event.GetIsSandMC())
          fluxWeightSyst = _flux->GetWeight(static_cast<AnaEventSummaryB*>(event.Summary)->TrueVertex[selec.GetSampleId()], anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run));

      /// Compute the weight for this selection by applying the systematic weights.
      if (_applyEventWeights || _applyFluxWeightSystematic){
        // apply the detector weight systematics
        if (_applyEventWeights){
          totalweight = eweight().ComputeEventWeights(selec,toy, event, selec.GetPreviousToyBox(event), weights);
        }
        // apply the Flux systematic independently
        if (_applyFluxWeightSystematic && !event.GetIsSandMC()){
          fluxWeightSyst = syst().ApplyFluxSystematics(toy, event, selec.GetPreviousToyBox(event));
        }
      }
    }


    // If any of the selections is passed the overall passed is true
    if (passed_temp){
      Int_t isel = selec.GetEnabledIndex();
      SetSelectedSelection(isel);
      if(_StrictExclusiveness)
        passed = true;
      else{ 
        selec.FinalizeToy(&event);
        return true;
      }

    }
    selec.FinalizeToy(&event);


  }
  // std::cout << "Finish evaluating an event! No pass!" << std::endl;

  return passed;
}
//******************************************************************
bool AnalysisManager::ProcessEvent( AnaEventB& event, Float_t& POTweight){
  //******************************************************************

  /*
     This Method Process one event. That means:

     2. Loop over selections. And for each selection:
     2a. Apply all steps

Input:
- AnaEventB, but the one to be modified (event). Contains the SystBox

Output:
- EventSummary (part of the AnaEventB) containing high level info (candidate, etc)

Return value:
- true when at least one selection has been passed

*/
  bool passed=false;
  /// Loop over selections

  // Reset event summary sample before applying all selections
  static_cast<AnaEventSummaryB*>(event.Summary)->ResetSummary();

  for (std::vector<SelectionBase*>::iterator it=sel().GetSelections().begin();it!=sel().GetSelections().end();it++){
    SelectionBase& selec = **it;
    // only enabled selections
    if (!selec.IsEnabled()) continue;
    if (!CheckSelectionAgainstRunPeriod(*it, anaUtils::GetRunPeriod(static_cast<AnaEventB*>(&event)->EventInfo.Run))) continue;

    selec.InitializeToy(&event);


    /// Apply the selection
    bool redo;
    if (selec.Apply(event, redo)) passed=true;

    if (passed){
      Int_t isel = selec.GetEnabledIndex();
      SetSelectedSelection(isel);

    }
    selec.FinalizeToy(&event);

  }



  // computes the POT normalization for the current event
  if (_currentSampleGroup){
    Float_t POTdata=0;
    Float_t POTmc=0;
    Float_t POTsand=0;
    _currentSampleGroup->GetPOT(POTdata, POTmc, POTsand);
    POTweight = POTdata/POTmc;
  }

  return passed;
}

//******************************************************************
bool AnalysisManager::LoadEvent(Long64_t& entry){
  //******************************************************************

  AnaSuperEventB* event = LoadSuperEvent(entry);
  if(event==NULL) return false;

  return true;
}
//******************************************************************
bool AnalysisManager::Initialize(Int_t nmax_events){
  //******************************************************************

  //Start by setting up the AnaSuperEventB* array to be large enough to take
  //nmax_events events
  CreateEventArray(nmax_events);

  // Create the array of PreviousToyBox
  sel().CreateToyBoxArray(nmax_events);

  // Create the array of SystBox
  evar().Initialize(nmax_events);
  eweight().Initialize(sel(),nmax_events);
  return true;
}
//******************************************************************
bool AnalysisManager::ReadEvents(Int_t nmax_events){
  //******************************************************************

  // Fill the vector of samples only the first time
  if (_samples.size() == 0){
    std::map< std::string, SampleGroup >& sampleGroups = _exp->GetSampleGroups();
    std::map< std::string, SampleGroup >::iterator sit;
    for (sit = sampleGroups.begin(); sit != sampleGroups.end(); sit++) {
      SampleGroup& sampleGroup = sit->second;

      std::vector<DataSample*>& dataSamples = sampleGroup.GetDataSamples();
      std::vector<DataSample*>::iterator it;
      for (it = dataSamples.begin(); it != dataSamples.end(); it++) {
        DataSample* sample = *it;
        _samples.push_back(sample);
      }

      std::map< std::string, DataSample*>& mcSamples = sampleGroup.GetMCSamples();
      std::map< std::string, DataSample*>::iterator it2;
      for (it2 = mcSamples.begin(); it2 != mcSamples.end(); it2++) {
        std::string name = it2->first;
        DataSample* sample = it2->second;
        _samples.push_back(sample);
      }
    }
    _currentSample = _samples.begin();
  }
  else
    _currentSample++;


  _currentSampleGroup = &(_exp->GetSampleGroup("run1"));

  // Preload events from the current sample
  return ReadEvents(*_currentSample, nmax_events);

}

//******************************************************************
bool AnalysisManager::ReadEvents(DataSample* sample, Int_t nmax_events){
  //******************************************************************

  // Preload in _eventArray the events for the input sample

  if (!ReadEvents(sample->GetFilePath(),nmax_events)) return false;

  Int_t nentries = (Int_t)_input.GetEntries();
  sample->SetNEntries(nentries);

  return true;
}

//******************************************************************
bool AnalysisManager::ReadEvents(const std::string& inputFile, Int_t nmax_events){
  //******************************************************************

  // Preload in _eventArray the events for the sample in the inputFile

  std::cout << "AnalysisManager::ReadEvents(). Reading file " << inputFile << std::endl;

  // Open the input file
  if(!_input.Initialize(inputFile.c_str(),"")) return false;

  // Get the number of entries in the input tree
  Int_t nentries = (Int_t)_input.GetEntries();

  // Get the number of events in the input tree
  Int_t nEventsInTree = _input.GetNEvents();

  // just in case we don't run over all entries
  if (nmax_events !=-1)
    nmax_events = std::min(nmax_events-_nEventsProcessed, nEventsInTree);
  else
    nmax_events = nEventsInTree;

  std::cout << "AnalysisManager::ReadEvents(). Preload " << nmax_events << " events" << std::endl;

  Initialize(nmax_events);

  Long64_t entry=0;
  _nEventsInArray=0;
  while((Int_t)_nEventsInArray<nmax_events && entry<nentries){
    // Fill the event structure for the current event (don't delete the previous event)
    if (!_input.LoadEvent(entry,false)) continue;

    // Dump info about number of entries run
    if (entry%10000==0 || entry == nentries)
      std::cout << "entry: " <<  entry  << " of " << nentries << " (" << (100*entry/nentries) << "%)" << std::endl;        

    // Get the SuperEvent and save it into the array
    AnaSuperEventB* event = &_input.GetSuperEvent();

    // Initialize the event for all enabled selections. That means filling the EventBox
    sel().InitializeEvent(*(event->Event));

    // Initialize The SystBox for variation systematics
    evar().InitializeEvent(sel(),*(event->Event));
    eweight().InitializeEvent(sel(),*(event->Event));

    _eventArray[_nEventsInArray] = event;
    _nEventsInArray++;
  }

  std::cout << "AnalysisManager::ReadEvents(). Preloading done of " << _nEventsInArray << " events"<< std::endl;

  //Reset the currentEvent
  _currentEvent=-1;

  return true;
}

//******************************************************************
AnaSuperEventB* AnalysisManager::GetNextSuperEvent(){
  //******************************************************************

  // This function returns the next SuperEvent in the sample list

  // When we arrive to the last event
  if (_nEventsProcessed == _nEventsToProcess) return NULL;

  // increase the current event number
  _currentEvent++;

  // increase the number of events processed
  _nEventsProcessed++;

  // Print the entry number
  // Comment out for now - unless processing lots of events O(100000) this just prints out 0% complete repeatedly
  //    if (_currentEvent%10000==0 || _currentEvent == _nEventsToProcess)
  //        std::cout << "entry: " << _currentEvent << " of " << _nEventsToProcess << " (" << (100*_currentEvent/(_nEventsToProcess)) << "%)" << std::endl;
  return _eventArray[_currentEvent];
}

//******************************************************************
AnaEventB* AnalysisManager::GetNextEvent(){
  //******************************************************************

  AnaSuperEventB* sevent = GetNextSuperEvent();
  if (sevent){
    return static_cast<AnaEventB*>(sevent->Event);
  }
  else{
    return NULL;
  }
}

//******************************************************************
AnaSuperEventB* AnalysisManager::LoadSuperEvent(Long64_t& entry){
  //******************************************************************
  // Fill the event structure for the current event
  if (!_input.LoadEvent(entry,true)) return NULL;

  // Get the SuperEvent
  AnaSuperEventB* event = &_input.GetSuperEvent();

  if(event->Event->GetIsMC()){
    if(_POT_weights.size()) event->POTWeight = _POT_weights[_input.GetChain(_input.GetConverter().GetTreeName().c_str())->GetTreeNumber()];
  }

  return event;
}


//******************************************************************
AnaEventB* AnalysisManager::GetEvent(Int_t evtIndex){
  //******************************************************************

  AnaSuperEventB* sevent = GetSuperEvent(evtIndex);
  if (sevent) return static_cast<AnaEventB*>(sevent->Event);
  else return NULL;
}

//******************************************************************
UInt_t AnalysisManager::GetEntries(){
  //******************************************************************
  return _input.GetEntries();
}

//******************************************************************
void AnalysisManager::CreateEventArray(Int_t nmax_events){
  //******************************************************************

  if (_eventArray){
    // Delete all AnaSuperEventB in the array
    for (UInt_t ev = 0; ev<_nEventsInArray;ev++){
      // The RawEvent must be reset manually (TODO)
      delete _eventArray[ev]->RawEvent;
      delete _eventArray[ev];
    }
    // Delete the array itself
    delete _eventArray;
  }

  // Create a new event array
  _eventArray = new AnaSuperEventB*[nmax_events];
}


//******************************************************************
void AnalysisManager::PreloadEvents(bool preloadData, bool preloadMC){
  //******************************************************************

  if(!_exp){
    std::cout << "There is no Experiment associated with this AnalysisManager, cannot preload events this way. Use ReadEvents(int nevents) method instead." << std::endl;
    return;
  }

  // Fill the vector of samples only the first time
  std::map< std::string, SampleGroup >& sampleGroups = _exp->GetSampleGroups();
  std::map< std::string, SampleGroup >::iterator sit;
  for (sit = sampleGroups.begin(); sit != sampleGroups.end(); sit++) {
    SampleGroup& sampleGroup = sit->second;

    Float_t POTdata=0;
    Float_t POTmc=0;
    Float_t POTsand=0;

    sampleGroup.GetPOT(POTdata, POTmc, POTsand);

    float POT_weight = POTdata/POTmc;
    float POT_weight_sand = POTdata/POTsand;

    std::map< std::string, DataSample*>& mcSamples = sampleGroup.GetMCSamples();
    std::map< std::string, DataSample*>::iterator it2;
    for (it2 = mcSamples.begin(); it2 != mcSamples.end(); it2++) {
      if((it2->first).find("and")!=std::string::npos){
        _POT_weights.push_back(POT_weight_sand);
      }
      else{
        _POT_weights.push_back(POT_weight);
      }
    }
  }

  if(preloadMC) PreloadMCEvents(_exp->GetMCFileVector(), _POT_weights);
  if(preloadData) PreloadDataEvents(_exp->GetDataFileVector());
}

//******************************************************************
bool AnalysisManager::PreloadMCEvents(std::vector<std::string> inputFiles, std::vector<float> POT_weights){
  //******************************************************************

  int nEntries = 0;
  int nmax_events = 0;

  for(std::vector<std::string>::iterator it = inputFiles.begin(); it != inputFiles.end(); ++it){

    std::string inputFile = *it;
    // Open the input file
    if(!_input.Initialize(inputFile.c_str(),"")) continue;

    // Get the number of entries in the input tree
    nEntries += (Int_t)_input.GetEntries();

    // Get the number of events in the input tree
    nmax_events += _input.GetNEvents();
  }


  //Start by setting up the AnaSuperEventB* array to be large enough to take
  //nmax entries.
  CreateMCEventArray(nmax_events);

  _nEventsInMCArray=0;

  // Create the array of PreviousToyBox
  sel().CreateToyBoxArray(nmax_events);

  // Create the array of SystBox
  evar().Initialize(nmax_events);
  eweight().Initialize(sel(),nmax_events);


  for(int i = 0; i < (int)inputFiles.size(); ++i){
    std::string inputFile = inputFiles[i];
    float POT_weight = POT_weights[i];

    // Preload in _eventArray the events for the sample in the inputFile
    std::cout << "AnalysisManager::PreloadMCEvents(). Reading file " << inputFile << std::endl;

    // Open the input file
    if(!_input.Initialize(inputFile.c_str(),"")) continue;

    Long64_t entry=0;

    int nmax_entries = _input.GetEntries();

    while((int)entry < nmax_entries){

      // Fill the event structure for the current event (don't delete the previous event)
      if (!_input.LoadEvent(entry,false)) continue;

      // Dump info about number of entries run
      if (entry%10000==0 || entry == nmax_entries)
        std::cout << "entry: " <<  entry  << " of " << nmax_entries << " (" << (100*entry/nmax_entries) << "%)" << std::endl;        

      // Get the SuperEvent and save it into the array
      AnaSuperEventB* event = &_input.GetSuperEvent();

      // Initialize the event for all enabled selections. That means filling the EventBox
      sel().InitializeEvent(*(event->Event));

      // Initialize The SystBox for variation systematics
      evar().InitializeEvent(sel(),*(event->Event));
      eweight().InitializeEvent(sel(),*(event->Event));

      event->POTWeight = POT_weight;
      _mcEventArray[_nEventsInMCArray] = event;
      _nEventsInMCArray++;
    }
  }

  std::cout << "AnalysisManager::PreloadMCEvents(). Preloading done" << std::endl;
  return true;
}

//******************************************************************
bool AnalysisManager::PreloadDataEvents(std::vector<std::string> inputFiles){
  //******************************************************************

  int nEntries = 0;
  int nmax_events = 0;

  for(std::vector<std::string>::iterator it = inputFiles.begin(); it != inputFiles.end(); ++it){

    std::string inputFile = *it;

    // Open the input file
    if(!_input.Initialize(inputFile.c_str(),"")) continue;

    // Get the number of entries in the input tree
    nEntries += (Int_t)_input.GetEntries();

    // Get the number of events in the input tree
    nmax_events += _input.GetNEvents();
  }

  //Start by setting up the AnaSuperEventB* array to be large enough to take
  //nmax entries.
  CreateDataEventArray(nmax_events);

  _nEventsInDataArray=0;

  for(std::vector<std::string>::iterator it = inputFiles.begin(); it != inputFiles.end(); ++it){

    std::string inputFile = *it;

    // Preload in _eventArray the events for the sample in the inputFile
    std::cout << "AnalysisManager::PreloadDataEvents(). Reading file " << inputFile << std::endl;

    // Open the input file
    if(!_input.Initialize(inputFile.c_str(),"")) continue;

    Long64_t entry=0;

    int nmax_entries = _input.GetEntries();

    while((int)entry < nmax_entries){

      // Fill the event structure for the current event (don't delete the previous event)
      if (!_input.LoadEvent(entry,false)) continue;

      // Dump info about number of entries run
      if (entry%10000==0 || entry == nmax_entries)
        std::cout << "entry: " <<  entry  << " of " << nmax_entries << " (" << (100*entry/nmax_entries) << "%)" << std::endl;        


      // Get the SuperEvent and save it into the array
      AnaSuperEventB* event = &_input.GetSuperEvent();
      _dataEventArray[_nEventsInDataArray] = event;
      _nEventsInDataArray++;
    }
  }

  std::cout << "AnalysisManager::PreloadDataEvents(). Preloading done" << std::endl;
  return true;
}

//******************************************************************
void AnalysisManager::InitialiseMCTChain(){
  //******************************************************************

  _input.Reset();

  _nEventsInMCArray=0;

  std::map< std::string, SampleGroup >& sampleGroups = _exp->GetSampleGroups();
  std::map< std::string, SampleGroup >::iterator sit;
  for (sit = sampleGroups.begin(); sit != sampleGroups.end(); sit++) {
    SampleGroup& sampleGroup = sit->second;

    std::map< std::string, DataSample*>& mcSamples = sampleGroup.GetMCSamples();
    std::map< std::string, DataSample*>::iterator it2;
    for (it2 = mcSamples.begin(); it2 != mcSamples.end(); it2++){
      DataSample* sample = it2->second;
      if(!_input.AddDataFileToConverter(sample->GetFilePath().c_str(),"")) continue;
    }
  }
  std::cout << "AnalysisManager::InitialiseMCTChain(). TChain has all MC files added." << std::endl;
  _nEventsInMCArray = (Int_t)_input.GetNEvents();
}

//******************************************************************
void AnalysisManager::InitialiseDataTChain(){
  //******************************************************************
  std::vector<std::string> inputFiles;
  inputFiles = _exp->GetDataFileVector();


  _input.Reset();

  _nEventsInDataArray=0;
  for(std::vector<std::string>::iterator it = inputFiles.begin(); it != inputFiles.end(); ++it){
    std::string inputFile = *it;
    // Open the input file
    if(!_input.AddDataFileToConverter(inputFile.c_str(),"")) continue;
  }

  std::cout << "AnalysisManager::InitialiseDataTChain(). TChain has all data files added." << std::endl;
  _nEventsInDataArray = (Int_t)_input.GetNEvents();
}

//******************************************************************
AnaSuperEventB* AnalysisManager::GetPreloadedMCSuperEvent(int i){
  //******************************************************************
  if(i >= (int)_nEventsInMCArray){
    std::cout << "Requesting event " << i << " when the MC preloaded event array only has " << _nEventsInMCArray << " entries." << std::endl;
    return NULL;
  }
  return _mcEventArray[i];
}

//******************************************************************
AnaSuperEventB* AnalysisManager::GetPreloadedDataSuperEvent(int i){
  //******************************************************************
  if(i >= (int)_nEventsInDataArray){
    std::cout << "Requesting event " << i << " when the Data preloaded event array only has " << _nEventsInDataArray << " entries." << std::endl;

    return NULL;
  }
  return _dataEventArray[i];
}

//******************************************************************
void AnalysisManager::CreateMCEventArray(Int_t nmax){
  //******************************************************************

  if (_mcEventArray){
    // Delete all AnaSuperEventB in the array
    for (UInt_t ev = 0; ev<_nEventsInMCArray;ev++){
      delete _mcEventArray[ev]->RawEvent;
      delete _mcEventArray[ev];
    }
    // Delete the array itself
    delete _mcEventArray;
  }

  // Create a new event array
  _mcEventArray = new AnaSuperEventB*[nmax];
}

//******************************************************************
void AnalysisManager::CreateDataEventArray(Int_t nmax){
  //******************************************************************

  if (_dataEventArray){
    // Delete all AnaSuperEventB in the array
    for (UInt_t ev = 0; ev<_nEventsInDataArray;ev++){
      delete _dataEventArray[ev]->RawEvent;
      delete _dataEventArray[ev];
    }
    // Delete the array itself
    delete _dataEventArray;
  }
  // Create a new event array
  _dataEventArray = new AnaSuperEventB*[nmax];
}

//******************************************************************
void AnalysisManager::ResetEventsProcessed(){
  //******************************************************************
  _currentEvent = -1;
  _nEventsProcessed = 0;
}

//******************************************************************
bool AnalysisManager::CheckSelectionAgainstRunPeriod(SelectionBase* selec, int RunPeriod){
  //******************************************************************
  return selec->IsValidRun(RunPeriod);
}


//******************************************************************
void AnalysisManager::DumpVariationSystematics(bool detailed){
  //******************************************************************

  if (!detailed){
    syst().DumpVariationSystematics();
    return;
  }

  int nVariationSystematics;

  EventVariationBase** variationSystematics = syst().GetVariationSystematics(nVariationSystematics);

  std::cout << " \n -------- List of VariationSystematics ------------ " << std::endl;
  char out[256];  
  sprintf(out,"%3s: %-25s %-15s %-4s", "#", "name", "pdf", "NPar");
  std::cout << out << "\n" << std::endl;


  Int_t j=0;
  for (int it = 0; it < nVariationSystematics; it++) {
    if (variationSystematics[it]->IsEnabled()){
      sprintf(out,"%3d: %-25s %-15s %-4d", j, variationSystematics[it]->Name().c_str(), 
          variationSystematics[it]->ConvertPDF().c_str(), 
          variationSystematics[it]->GetNParameters());
      std::cout << out << std::endl;
      if (dynamic_cast<BinnedParams*>(variationSystematics[it]))
        dynamic_cast<BinnedParams*>(variationSystematics[it])->Print();
      else
        variationSystematics[it]->Print();
      j++;
    }
  }
  std::cout << " -------------------------------------------------- \n " << std::endl;

  return;

}

//******************************************************************
void AnalysisManager::DumpWeightSystematics(bool detailed){
  //******************************************************************

  if (!detailed){
    syst().DumpWeightSystematics();
    return;
  }


  int nWeightSystematics;

  EventWeightBase** weightSystematics = syst().GetWeightSystematics(nWeightSystematics);

  std::cout << " \n -------- List of WeightSystematics ------------ " << std::endl;
  char out[256];  
  sprintf(out,"%3s: %-25s %-15s %-4s", "#", "name", "pdf", "NPar");
  std::cout << out << "\n" << std::endl;


  Int_t j=0;
  for (int it = 0; it < nWeightSystematics; it++) {
    if (weightSystematics[it]->IsEnabled()){
      sprintf(out,"%3d: %-25s %-15s %-4d", j, weightSystematics[it]->Name().c_str(), 
          weightSystematics[it]->ConvertPDF().c_str(), 
          weightSystematics[it]->GetNParameters());
      std::cout << out << std::endl;
      if (dynamic_cast<BinnedParams*>(weightSystematics[it]))
        dynamic_cast<BinnedParams*>(weightSystematics[it])->Print();
      else
        weightSystematics[it]->Print();
      j++;
    }
  }
  std::cout << " -------------------------------------------------- \n " << std::endl;

  return;
}


