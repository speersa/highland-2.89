// Macro used to make plots for TN-277.
// You need to define the path to your root files. Remove any runs that are not relevant to your analysis. 
// POT scaling is done run-by-run.
// You may need to modify the macro for additional decorations.

// Define histograms here 
const int n = 11;
TH1D* CCH[n]; TH1D* CCHnPi[n]; TH1D* GammaH[n]; TH1D* MuonBkg[n]; TH1D* OtherBkgH[n]; TH1D* ProtonBkg[n];  
TH1D* CCSignalNeutrinoParent[9]; TH1D* CCSignalInteractions[5]; TH1D* GammaInteraction[8]; TH1D* GammaDetector[12]; TH1D* GammaOOFGDTarget[10]; 
TH1D* MuonBkgInteractions[6]; TH1D* ProtonBkgInteractions[8]; TH1D* OtherBkgBreakdown[8];
TH1D* MuonBkgInteractionsAngle[6]; TH1D* ProtonBkgInteractionsAngle[8]; TH1D* OtherBkgBreakdownAngle[8]; TH1D* GammaInteractionAngle[8]; TH1D* CCSignalInteractionsAngle[5]; 
TH1D* ElecMomRes[2]; TH1D* ElecAngRes[2];
TH2D* ElecMomRes2D[2]; TH2D* ElecAngRes2D[2]; TH2D* MomTheta2D[3];  
TH1D* DataH[n];

// Efficiency histograms
TH1D* EffTrue; TH1D* NEffTrue; TH1D* AngTrue; TH1D* PosTrue; TH1D* EffTrue2;
TH1D* EffTrueCC0Pi; TH1D* AngTrueCC0Pi;
TH1D* EffTrueCCOther; TH1D* AngTrueCCOther;
TH1D* PurTrue;  TH1D* NPurTrue; TH1D* PurAngTrue;

TH1D* SEffTrue; TH1D* SNEffTrue; TH1D* SAngTrue; TH1D* SPosTrue; TH1D* SEffTrue2;
TH1D* SEffTrueCC0Pi; TH1D* SAngTrueCC0Pi;
TH1D* SEffTrueCCOther; TH1D* SAngTrueCCOther;
TH1D* SPurTrue;  TH1D* SNPurTrue; TH1D* SPurAngTrue;

TH1D* SEffTrueEventsCC0Pi; TH1D* SEffTrueEventsCCOther; TH1D* SAngTrueEventsCC0Pi; TH1D* SAngTrueEventsCCOther; TH1D* SEffTrueEventsCCInc; TH1D* SAngTrueEventsCCInc; 

// Efficiency histograms in the restricted phase-space
TH1D* SignalSelMom; TH1D* TruthSelMom; TH1D* SignalSelAng; TH1D* TruthSelAng;
TH1D* SignalSelMom2; TH1D* TruthSelMom2; TH1D* SignalSelMom3; TH1D* TruthSelMom3; TH1D* SignalSelMom4; TH1D* TruthSelMom4; TH1D* SignalSelMom5; TH1D* TruthSelMom5;  
TH2D *TrueMomCosTruth; TH2D *TrueMomCosSelec; 

// Angular bins for xs measurement
const int nangxs = 3;
Double_t xsangparnum[nangxs] = {0.7071, 0.88, 1.001};
const int n1 = 11;
Double_t momparnum[n1] = {300,600,800,1000,1200,1600,2000,2400,2800,3200,30000};
const int n2 = 8;
Double_t angparnum[n2] = {0.7071, 0.75, 0.80, 0.85, 0.90, 0.95, 0.975, 1.001};
const int n2pos = 6;
Double_t angparnumpos[n2pos] = {0.7071, 0.80, 0.85, 0.90, 0.95, 1.001};

const int n3 = 5;
Double_t momparxsfhc[n3] = {0.0, 300.0, 1600.0, 3200.0, 30000.0};
const int n4 = 4;
Double_t momparxsrhc[n4] = {0.0, 300.0, 1600.0, 30000.0};

const int n5 = 9;
Double_t momparnum2[n5] = {300,800,1200,1600,2000,2400,2800,3200,30000};
Double_t momparnum3[n5+1] = {300,800,1200,1600,2000,2400,2800,3200,4000,6000};

// Minimum momentum for xs measurement
const Double_t MINMOMENTUM = 300.0;

// FGD mass corrections - not applied in highland
const Float_t fgd1massweight = 0.994;
const Float_t fgd2massweight = 0.9945;

// Which selection - by default is FHC CC-nue
bool mixccsignal = true; // add cc0pi and ccother
bool isgenie = false;
bool positive = false; // CC-anue or positron selection for gamma
bool isrhc = false;
bool isgamma = false;

bool addratio = true; // Add data/mc plot at the bottom of the distribution
bool drawerror = false; // Draw systematic uncertainties on the momentum distribution

// FGD where the selection is done, 0 for FGD1, 1 for FGD2
int whichfgd=0;

// Special for accum_level cuts
int ACCUMLEVELCUT = 3;

void nuePlots(){

  if(isrhc){
    if(positive) xsangparnum[1] = 0.92;
    else xsangparnum[1] = 0.95;
  }

  // Set T2K style
  TStyle* t2kstyle = SetT2KStyle();
  gROOT->SetStyle(t2kstyle->GetName());

  // Colours for THStacks, same as highland
  Int_t parcolour[6]  = {2 , 3 , 6 , 4 , 48 , 8};
  Int_t intcolour[10] = {6 , 7 , 798 , 3 , 1 , 2 , 48, 8, 18, 25};
  //                             5  
  // -----------------------------------------------------------------------------------------
  // OUTPUT
  // -----------------------------------------------------------------------------------------
  TString outFile = GetOutputFilename();
  cout << "INFO::Output filename: " << outFile << endl;

  TLatex latex;
  latex.SetTextSize(0.15);
  // --------------------------------------------------------------------
  // Define all histograms
  DefineHistograms(whichfgd);

  // -----------------------------------------------------------------------------------------
  // Paths where the files are
  // -----------------------------------------------------------------------------------------
  
  // -----------------------------------------------------------------------------------------
  // NUE
  // -----------------------------------------------------------------------------------------
  TString datapath                     = "/path/to/directory/";

  TString MCSelectionFileRun2air       = datapath + TString("run2airdpm.txt.root");
  TString DataSelectionFileRun2air     = datapath + TString("DataRun2Air.txt.root");
  TString MCSelectionFileRun2water     = datapath + TString("run2waterdpm.txt.root");
  TString DataSelectionFileRun2water   = datapath + TString("DataRun2WaterAll.txt.root");
  TString MCSelectionFileRun3air       = datapath + TString("neutmc_nue_fhc_run3air.root");
  TString DataSelectionFileRun3air     = datapath + TString("DataRun3Air.txt.root");
  TString MCSelectionFileRun3bair      = datapath + TString("run3bairdpm.txt.root");
  TString DataSelectionFileRun3bair    = datapath + TString("DataRun3bAir.txt.root");
  TString MCSelectionFileRun4air       = datapath + TString("neutmc_nue_fhc_run4air.root");
  TString DataSelectionFileRun4air     = datapath + TString("DataRun4Air.txt.root");
  TString MCSelectionFileRun4water     = datapath + TString("neutmc_nue_fhc_run4water.root");
  TString DataSelectionFileRun4water   = datapath + TString("DataRun4Water.txt.root");
  TString MCSelectionFileRun7cwater    = datapath + TString("run7waterdpmNu.txt.root");
  TString DataSelectionFileRun7cwater  = datapath + TString("DataRun7Water.txt.root");
  TString MCSelectionFileRun8air       = datapath + TString("neutmc_nue_fhc_run8air.root");
  TString DataSelectionFileRun8air     = datapath + TString("DataRun8air.txt.root");
  TString MCSelectionFileRun8water     = datapath + TString("neutmc_nue_fhc_run8water.root");
  TString DataSelectionFileRun8water   = datapath + TString("DataRun8water.txt.root");

  TString MCSelectionFileRun5water     = datapath + TString("run5waterdpmANu.txt.root");
  TString DataSelectionFileRun5water   = datapath + TString("DataRun5AntiNeutrino.txt.root");
  TString MCSelectionFileRun6bair      = datapath + TString("neutmc_nue_rhc_run6bair.root");
  TString DataSelectionFileRun6bair    = datapath + TString("DataRun6bAntiNeutrinoAll.txt.root");
  TString MCSelectionFileRun6cair      = datapath + TString("run6cairdpmANu.txt.root");
  TString DataSelectionFileRun6cair    = datapath + TString("DataRun6cAntiNeutrino.txt.root");
  TString MCSelectionFileRun6dair      = datapath + TString("neutmc_nue_rhc_run6dair.root");
  TString DataSelectionFileRun6dair    = datapath + TString("DataRun6dAntiNeutrino.txt.root");
  TString MCSelectionFileRun6eair      = datapath + TString("neutmc_nue_rhc_run6eair.root");
  TString DataSelectionFileRun6eair    = datapath + TString("DataRun6eAntiNeutrino.txt.root");
  TString MCSelectionFileRun7bwater    = datapath + TString("neutmc_nue_rhc_run7bwater.root");
  TString DataSelectionFileRun7bwater  = datapath + TString("DataRun7AntiNeutrino.txt.root");

  TString SandSelectionFileFHC         = datapath + TString("sand_nue_fhc_FGD1.root");
  TString SandSelectionFileRHC         = datapath + TString("sand_nue_rhc_FGD1.root");

  // -----------------------------------------------------------------------------------------
  // ANUE
  // -----------------------------------------------------------------------------------------
  TString datapath_anue                     = "/path/to/directory/";

  TString MCSelectionFileRun2air_anue       = datapath_anue + TString("run2airdpm.txtPos.root");
  TString DataSelectionFileRun2air_anue     = datapath_anue + TString("DataRun2Air.txtPos.root");
  TString MCSelectionFileRun2water_anue     = datapath_anue + TString("run2waterdpm.txtPos.root");
  TString DataSelectionFileRun2water_anue   = datapath_anue + TString("DataRun2WaterAll.txtPos.root");
  TString MCSelectionFileRun3air_anue       = datapath_anue + TString("neutmc_anue_fhc_run3air.root");
  TString DataSelectionFileRun3air_anue     = datapath_anue + TString("DataRun3Air.txtPos.root");
  TString MCSelectionFileRun3bair_anue      = datapath_anue + TString("run3bairdpm.txtPos.root");
  TString DataSelectionFileRun3bair_anue    = datapath_anue + TString("DataRun3bAir.txtPos.root");
  TString MCSelectionFileRun4air_anue       = datapath_anue + TString("neutmc_anue_fhc_run4air.root");
  TString DataSelectionFileRun4air_anue     = datapath_anue + TString("DataRun4Air.txtPos.root");
  TString MCSelectionFileRun4water_anue     = datapath_anue + TString("neutmc_anue_fhc_run4water.root");
  TString DataSelectionFileRun4water_anue   = datapath_anue + TString("DataRun4Water.txtPos.root");
  TString MCSelectionFileRun7cwater_anue    = datapath_anue + TString("run7waterdpmNu.txtPos.root");
  TString DataSelectionFileRun7cwater_anue  = datapath_anue + TString("DataRun7Water.txtPos.root");
  //TString MCSelectionFileRun8air_anue       = datapath_anue + TString("");
  //TString DataSelectionFileRun8air_anue     = datapath_anue + TString("");
  //TString MCSelectionFileRun8water_anue     = datapath_anue + TString("");
  //TString DataSelectionFileRun8water_anue   = datapath_anue + TString("");

  TString MCSelectionFileRun5water_anue     = datapath_anue + TString("run5waterdpmANu.txtPos.root");
  TString DataSelectionFileRun5water_anue   = datapath_anue + TString("DataRun5AntiNeutrino.txtPos.root");
  TString MCSelectionFileRun6bair_anue      = datapath_anue + TString("neutmc_anue_rhc_run6bair.root");
  TString DataSelectionFileRun6bair_anue    = datapath_anue + TString("DataRun6bAntiNeutrinoAll.txtPos.root");
  TString MCSelectionFileRun6cair_anue      = datapath_anue + TString("run6cairdpmANu.txtPos.root");
  TString DataSelectionFileRun6cair_anue    = datapath_anue + TString("DataRun6cAntiNeutrino.txtPos.root");
  TString MCSelectionFileRun6dair_anue      = datapath_anue + TString("neutmc_anue_rhc_run6dair.root");
  TString DataSelectionFileRun6dair_anue    = datapath_anue + TString("DataRun6dAntiNeutrino.txtPos.root");
  TString MCSelectionFileRun6eair_anue      = datapath_anue + TString("neutmc_anue_rhc_run6eair.root");
  TString DataSelectionFileRun6eair_anue    = datapath_anue + TString("DataRun6eAntiNeutrino.txtPos.root");
  TString MCSelectionFileRun7bwater_anue    = datapath_anue + TString("neutmc_anue_rhc_run7water.root");
  TString DataSelectionFileRun7bwater_anue  = datapath_anue + TString("DataRun7AntiNeutrino.txtPos.root");

  TString SandSelectionFileFHC_anue         = datapath_anue + TString("sand_anue_fhc_FGD1.root");
  TString SandSelectionFileRHC_anue         = datapath_anue + TString("sand_anue_rhc_FGD1.root");

  // -----------------------------------------------------------------------------------------
  // HMN GAMMA
  // -----------------------------------------------------------------------------------------
  TString datapath_gammaHMN                     = "/path/to/directory/";

  TString MCSelectionFileRun2air_gammaHMN       = datapath_gammaHMN + TString("run2airdpm.txtGamma.root");
  TString DataSelectionFileRun2air_gammaHMN     = datapath_gammaHMN + TString("DataRun2Air.txtGamma.root");
  TString MCSelectionFileRun2water_gammaHMN     = datapath_gammaHMN + TString("run2waterdpm.txtGamma.root");
  TString DataSelectionFileRun2water_gammaHMN   = datapath_gammaHMN + TString("DataRun2WaterAll.txtGamma.root");
  TString MCSelectionFileRun3air_gammaHMN       = datapath_gammaHMN + TString("neutmc_gammaHMN_fhc_run3air.root");
  TString DataSelectionFileRun3air_gammaHMN     = datapath_gammaHMN + TString("DataRun3Air.txtGamma.root");
  TString MCSelectionFileRun3bair_gammaHMN      = datapath_gammaHMN + TString("run3bairdpm.txtGamma.root");
  TString DataSelectionFileRun3bair_gammaHMN    = datapath_gammaHMN + TString("DataRun3bAir.txtGamma.root");
  TString MCSelectionFileRun4air_gammaHMN       = datapath_gammaHMN + TString("neutmc_gammaHMN_fhc_run4air.root");
  TString DataSelectionFileRun4air_gammaHMN     = datapath_gammaHMN + TString("DataRun4Air.txtGamma.root");
  TString MCSelectionFileRun4water_gammaHMN     = datapath_gammaHMN + TString("neutmc_gammaHMN_fhc_run4water.root");
  TString DataSelectionFileRun4water_gammaHMN   = datapath_gammaHMN + TString("DataRun4Water.txtGamma.root");
  TString MCSelectionFileRun7cwater_gammaHMN    = datapath_gammaHMN + TString("run7waterdpmNu.txtGamma.root");
  TString DataSelectionFileRun7cwater_gammaHMN  = datapath_gammaHMN + TString("DataRun7Water.txtGamma.root");
  TString MCSelectionFileRun8air_gammaHMN       = datapath_gammaHMN + TString("neutmc_gammaHMN_fhc_run8air.root");
  TString DataSelectionFileRun8air_gammaHMN     = datapath_gammaHMN + TString("DataRun8airHMNgamma.txt.root");
  TString MCSelectionFileRun8water_gammaHMN     = datapath_gammaHMN + TString("neutmc_gammaHMN_fhc_run8water.root");
  TString DataSelectionFileRun8water_gammaHMN   = datapath_gammaHMN + TString("DataRun8waterHMNgamma.txt.root");

  TString MCSelectionFileRun5water_gammaHMN     = datapath_gammaHMN + TString("run5waterdpmANu.txtGamma.root");
  TString DataSelectionFileRun5water_gammaHMN   = datapath_gammaHMN + TString("DataRun5AntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun6bair_gammaHMN      = datapath_gammaHMN + TString("neutmc_gammaHMN_rhc_run6bair.root");
  TString DataSelectionFileRun6bair_gammaHMN    = datapath_gammaHMN + TString("DataRun6bAntiNeutrinoAll.txtGamma.root");
  TString MCSelectionFileRun6cair_gammaHMN      = datapath_gammaHMN + TString("run6cairdpmANu.txtGamma.root");
  TString DataSelectionFileRun6cair_gammaHMN    = datapath_gammaHMN + TString("DataRun6cAntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun6dair_gammaHMN      = datapath_gammaHMN + TString("neutmc_gammaHMN_rhc_run6dair.root");
  TString DataSelectionFileRun6dair_gammaHMN    = datapath_gammaHMN + TString("DataRun6dAntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun6eair_gammaHMN      = datapath_gammaHMN + TString("neutmc_gammaHMN_rhc_run6eair.root");
  TString DataSelectionFileRun6eair_gammaHMN    = datapath_gammaHMN + TString("DataRun6eAntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun7bwater_gammaHMN    = datapath_gammaHMN + TString("neutmc_gammaHMN_rhc_run7water.root");
  TString DataSelectionFileRun7bwater_gammaHMN  = datapath_gammaHMN + TString("DataRun7AntiNeutrino.txtGamma.root");

  TString SandSelectionFileFHC_gammaHMN         = datapath_gammaHMN + TString("sand_gammaHMNWVeto_fhc_FGD1.root");
  TString SandSelectionFileRHC_gammaHMN         = datapath_gammaHMN + TString("sand_gammaHMNWVeto_rhc_FGD1.root");

  // -----------------------------------------------------------------------------------------
  // HMP GAMMA
  // -----------------------------------------------------------------------------------------
  TString datapath_gammaHMP                     = "/path/to/directory/";

  TString MCSelectionFileRun2air_gammaHMP       = datapath_gammaHMP + TString("run2airdpm.txtGamma.root");
  TString DataSelectionFileRun2air_gammaHMP     = datapath_gammaHMP + TString("DataRun2Air.txtGamma.root");
  TString MCSelectionFileRun2water_gammaHMP     = datapath_gammaHMP + TString("run2waterdpm.txtGamma.root");
  TString DataSelectionFileRun2water_gammaHMP   = datapath_gammaHMP + TString("DataRun2WaterAll.txtGamma.root");
  TString MCSelectionFileRun3air_gammaHMP       = datapath_gammaHMP + TString("neutmc_gammaHMP_fhc_run3air.root");
  TString DataSelectionFileRun3air_gammaHMP     = datapath_gammaHMP + TString("DataRun3Air.txtGamma.root");
  TString MCSelectionFileRun3bair_gammaHMP      = datapath_gammaHMP + TString("run3bairdpm.txtGamma.root");
  TString DataSelectionFileRun3bair_gammaHMP    = datapath_gammaHMP + TString("DataRun3bAir.txtGamma.root");
  TString MCSelectionFileRun4air_gammaHMP       = datapath_gammaHMP + TString("neutmc_gammaHMP_fhc_run4air.root");
  TString DataSelectionFileRun4air_gammaHMP     = datapath_gammaHMP + TString("DataRun4Air.txtGamma.root");
  TString MCSelectionFileRun4water_gammaHMP     = datapath_gammaHMP + TString("neutmc_gammaHMP_fhc_run4water.root");
  TString DataSelectionFileRun4water_gammaHMP   = datapath_gammaHMP + TString("DataRun4Water.txtGamma.root");
  TString MCSelectionFileRun7cwater_gammaHMP    = datapath_gammaHMP + TString("run7waterdpmNu.txtGamma.root");
  TString DataSelectionFileRun7cwater_gammaHMP  = datapath_gammaHMP + TString("DataRun7Water.txtGamma.root");
  TString MCSelectionFileRun8air_gammaHMP       = datapath_gammaHMP + TString("neutmc_gammaHMP_fhc_run8air.root");
  TString DataSelectionFileRun8air_gammaHMP     = datapath_gammaHMP + TString("DataRun8airHMPgamma.txt.root");
  TString MCSelectionFileRun8water_gammaHMP     = datapath_gammaHMP + TString("neutmc_gammaHMP_fhc_run8water.root");
  TString DataSelectionFileRun8water_gammaHMP   = datapath_gammaHMP + TString("DataRun8waterHMPgamma.txt.root");

  TString MCSelectionFileRun5water_gammaHMP     = datapath_gammaHMP + TString("run5waterdpmANu.txtGamma.root");
  TString DataSelectionFileRun5water_gammaHMP   = datapath_gammaHMP + TString("DataRun5AntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun6bair_gammaHMP      = datapath_gammaHMP + TString("neutmc_gammaHMP_rhc_run6bair.root");
  TString DataSelectionFileRun6bair_gammaHMP    = datapath_gammaHMP + TString("DataRun6bAntiNeutrinoAll.txtGamma.root");
  TString MCSelectionFileRun6cair_gammaHMP      = datapath_gammaHMP + TString("run6cairdpmANu.txtGamma.root");
  TString DataSelectionFileRun6cair_gammaHMP    = datapath_gammaHMP + TString("DataRun6cAntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun6dair_gammaHMP      = datapath_gammaHMP + TString("neutmc_gammaHMP_rhc_run6dair.root");
  TString DataSelectionFileRun6dair_gammaHMP    = datapath_gammaHMP + TString("DataRun6dAntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun6eair_gammaHMP      = datapath_gammaHMP + TString("neutmc_gammaHMP_rhc_run6eair.root");
  TString DataSelectionFileRun6eair_gammaHMP    = datapath_gammaHMP + TString("DataRun6eAntiNeutrino.txtGamma.root");
  TString MCSelectionFileRun7bwater_gammaHMP    = datapath_gammaHMP + TString("neutmc_gammaHMP_rhc_run7water.root");
  TString DataSelectionFileRun7bwater_gammaHMP  = datapath_gammaHMP + TString("DataRun7AntiNeutrino.txtGamma.root");

  TString SandSelectionFileFHC_gammaHMP         = datapath_gammaHMP + TString("sand_gammaHMPWVeto_fhc_FGD1.root");
  TString SandSelectionFileRHC_gammaHMP         = datapath_gammaHMP + TString("sand_gammaHMPWVeto_rhc_FGD1.root");

  // -----------------------------------------------------------------------------------------
  // FGD2
  // -----------------------------------------------------------------------------------------
  if(whichfgd == 1){
    datapath = TString("/path/to/directory/"); 
    
    MCSelectionFileRun2air       = datapath + TString("run2airNeut.root");
    MCSelectionFileRun2water     = datapath + TString("run2waterNeut.root");
    MCSelectionFileRun3air       = datapath + TString("run3airNeut.root");
    MCSelectionFileRun3bair      = datapath + TString("run3bairNeut.txt.root");
    MCSelectionFileRun4air       = datapath + TString("run4airNeut.root");
    MCSelectionFileRun4water     = datapath + TString("run4waterNeut.root");
    MCSelectionFileRun5water     = datapath + TString("run5waterNeut.txtGamma.root");
    MCSelectionFileRun6bair      = datapath + TString("run5waterNeut2.txtGamma.root");
    MCSelectionFileRun6cair      = datapath + TString("run5waterNeut3.txtGamma.root");
    MCSelectionFileRun6dair      = datapath + TString("run5waterNeut4.txtGamma.root");
    MCSelectionFileRun6eair      = datapath + TString("run5waterNeut5.txtGamma.root");
    MCSelectionFileRun7bwater    = datapath + TString("run5waterNeut.txtGamma.root");

    DataSelectionFileRun2air     = datapath + TString("DataRun2Air.txt.root");
    DataSelectionFileRun2water   = datapath + TString("DataRun2Water.root");
    DataSelectionFileRun3air     = datapath + TString("DataRun3cAir.txt.root");
    DataSelectionFileRun3bair    = datapath + TString("DataRun3bAir.txt.root");
    DataSelectionFileRun4air     = datapath + TString("DataRun4Air.txt.root");
    DataSelectionFileRun4water   = datapath + TString("DataRun4Water.txt.root");
    DataSelectionFileRun5water   = datapath + TString("DataRun5AntiNeutrinoWater.txtGamma.root");
    DataSelectionFileRun6bair    = datapath + TString("DataRun6bAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun6cair    = datapath + TString("DataRun6cAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun6dair    = datapath + TString("DataRun6dAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun6eair    = datapath + TString("DataRun6eAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun7bwater  = datapath + TString("DataRun7bAntiNeutrinoWater.txtGamma.root");

    datapath_gammaHMN                     = "/path/to/directory/";
    MCSelectionFileRun2air_gammaHMN       = datapath_gammaHMN + TString("run2airNeutGamma.root");
    MCSelectionFileRun2water_gammaHMN     = datapath_gammaHMN + TString("run2waterNeutGamma.root");
    MCSelectionFileRun3air_gammaHMN       = datapath_gammaHMN + TString("run3airNeutGamma.root");
    MCSelectionFileRun3bair_gammaHMN      = datapath_gammaHMN + TString("run3bairNeut.txtGamma.root");
    MCSelectionFileRun4air_gammaHMN       = datapath_gammaHMN + TString("run4airNeutGamma.root");
    MCSelectionFileRun4water_gammaHMN     = datapath_gammaHMN + TString("run4waterNeutGamma.root");
    MCSelectionFileRun5water_gammaHMN     = datapath_gammaHMN + TString("run5waterNeut.txtGamma.root");
    MCSelectionFileRun6bair_gammaHMN      = datapath_gammaHMN + TString("run5waterNeut2.txtGamma.root");
    MCSelectionFileRun6cair_gammaHMN      = datapath_gammaHMN + TString("run5waterNeut3.txtGamma.root");
    MCSelectionFileRun6dair_gammaHMN      = datapath_gammaHMN + TString("run5waterNeut4.txtGamma.root");
    MCSelectionFileRun6eair_gammaHMN      = datapath_gammaHMN + TString("run5waterNeut2.txtGamma.root");
    MCSelectionFileRun7bwater_gammaHMN    = datapath_gammaHMN + TString("run5waterNeut.txtGamma.root");

    datapath_gammaHMN                     = "/path/to/directory/";
    DataSelectionFileRun2air_gammaHMN     = datapath_gammaHMN + TString("DataRun2Air.txtGamma.root");
    DataSelectionFileRun2water_gammaHMN   = datapath_gammaHMN + TString("DataRun2WaterGamma.root");
    DataSelectionFileRun3air_gammaHMN     = datapath_gammaHMN + TString("DataRun3cAir.txtGamma.root");
    DataSelectionFileRun3bair_gammaHMN    = datapath_gammaHMN + TString("DataRun3bAir.txtGamma.root");
    DataSelectionFileRun4air_gammaHMN     = datapath_gammaHMN + TString("DataRun4Air.txtGamma.root");
    DataSelectionFileRun4water_gammaHMN   = datapath_gammaHMN + TString("DataRun4Water.txtGamma.root");
    DataSelectionFileRun5water_gammaHMN   = datapath_gammaHMN + TString("DataRun5AntiNeutrinoWater.txtGamma.root");
    DataSelectionFileRun6bair_gammaHMN    = datapath_gammaHMN + TString("DataRun6bAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun6cair_gammaHMN    = datapath_gammaHMN + TString("DataRun6cAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun6dair_gammaHMN    = datapath_gammaHMN + TString("DataRun6dAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun6eair_gammaHMN    = datapath_gammaHMN + TString("DataRun6eAntiNeutrinoAir.txtGamma.root");
    DataSelectionFileRun7bwater_gammaHMN  = datapath_gammaHMN + TString("DataRun7bAntiNeutrinoWater.txtGamma.root");
  }

  // -----------------------------------------------------------------------------------------
  // GENIE
  // -----------------------------------------------------------------------------------------
  if(isgenie){
    MCSelectionFileRun2air       = datapath + TString("grun2airdpm.txt.root");
    MCSelectionFileRun2water     = datapath + TString("grun2waterdpm.txt.root");
    MCSelectionFileRun3air       = datapath + TString("geniemc_nue_fhc_run3air.root");
    MCSelectionFileRun3bair      = datapath + TString("grun3bairdpm.txt.root");
    MCSelectionFileRun4air       = datapath + TString("geniemc_nue_fhc_run4air.root");
    MCSelectionFileRun4water     = datapath + TString("geniemc_nue_fhc_run4water.root");
    MCSelectionFileRun7cwater    = datapath + TString("grun7waterdpmNu.txt.root");
    MCSelectionFileRun8air       = datapath + TString("geniemc_nue_fhc_run8air.root");
    MCSelectionFileRun8water     = datapath + TString("geniemc_nue_fhc_run8water.root");
    
    MCSelectionFileRun5water     = datapath + TString("grun5waterdpmANu.txt.root");
    MCSelectionFileRun6bair      = datapath + TString("geniemc_nue_rhc_run6bair.root");
    MCSelectionFileRun6cair      = datapath + TString("grun6cairdpmANu.txt.root");
    MCSelectionFileRun6dair      = datapath + TString("geniemc_nue_rhc_run6dair.root");
    MCSelectionFileRun6eair      = datapath + TString("geniemc_nue_rhc_run6eair.root");
    MCSelectionFileRun7bwater    = datapath + TString("geniemc_nue_rhc_run7bwater.root");

    MCSelectionFileRun2air_anue       = datapath_anue + TString("grun2airdpm.txtPos.root");
    MCSelectionFileRun2water_anue     = datapath_anue + TString("grun2waterdpm.txtPos.root");
    MCSelectionFileRun3air_anue       = datapath_anue + TString("geniemc_anue_fhc_run3air.root");
    MCSelectionFileRun3bair_anue      = datapath_anue + TString("grun3bairdpm.txtPos.root");
    MCSelectionFileRun4air_anue       = datapath_anue + TString("geniemc_anue_fhc_run4air.root");
    MCSelectionFileRun4water_anue     = datapath_anue + TString("geniemc_anue_fhc_run4water.root");
    MCSelectionFileRun7cwater_anue    = datapath_anue + TString("grun7waterdpmNu.txtPos.root");
    // MCSelectionFileRun8air_anue       = datapath_anue + TString("");
    // DataSelectionFileRun8air_anue     = datapath_anue + TString("");
    // MCSelectionFileRun8water_anue     = datapath_anue + TString("");
    // DataSelectionFileRun8water_anue   = datapath_anue + TString("");
    
    MCSelectionFileRun5water_anue     = datapath_anue + TString("grun5waterdpmANu.txtPos.root");
    MCSelectionFileRun6bair_anue      = datapath_anue + TString("geniemc_anue_rhc_run6bair.root");
    MCSelectionFileRun6cair_anue      = datapath_anue + TString("grun6cairdpmANu.txtPos.root");
    MCSelectionFileRun6dair_anue      = datapath_anue + TString("geniemc_anue_rhc_run6dair.root");
    MCSelectionFileRun6eair_anue      = datapath_anue + TString("geniemc_anue_rhc_run6eair.root");
    MCSelectionFileRun7bwater_anue    = datapath_anue + TString("geniemc_anue_rhc_run7water.root");

    datapath_gammaHMN = "/path/to/directory/";
    MCSelectionFileRun2air_gammaHMN       = datapath_gammaHMN + TString("grun2airdpm.txtGamma.root");
    MCSelectionFileRun2water_gammaHMN     = datapath_gammaHMN + TString("grun2waterdpm.txtGamma.root");
    MCSelectionFileRun3air_gammaHMN       = datapath_gammaHMN + TString("geniemc_gammaHMN_fhc_run3air.root");
    MCSelectionFileRun3bair_gammaHMN      = datapath_gammaHMN + TString("grun3bairdpm.txtGamma.root");
    MCSelectionFileRun4air_gammaHMN       = datapath_gammaHMN + TString("geniemc_gammaHMN_fhc_run4air.root");
    MCSelectionFileRun4water_gammaHMN     = datapath_gammaHMN + TString("geniemc_gammaHMN_fhc_run4water.root");
    MCSelectionFileRun7cwater_gammaHMN    = datapath_gammaHMN + TString("grun7waterdpmNu.txtGamma.root");
    MCSelectionFileRun8air_gammaHMN       = datapath_gammaHMN + TString("geniemc_gammaHMN_fhc_run8air.root");
    MCSelectionFileRun8water_gammaHMN     = datapath_gammaHMN + TString("geniemc_gammaHMN_fhc_run8water.root");
    
    MCSelectionFileRun5water_gammaHMN     = datapath_gammaHMN + TString("grun5waterdpmANu.txtGamma.root");
    MCSelectionFileRun6bair_gammaHMN      = datapath_gammaHMN + TString("geniemc_gammaHMN_rhc_run6bair.root");
    MCSelectionFileRun6cair_gammaHMN      = datapath_gammaHMN + TString("grun6cairdpmANu.txtGamma.root");
    MCSelectionFileRun6dair_gammaHMN      = datapath_gammaHMN + TString("geniemc_gammaHMN_rhc_run6dair.root");
    MCSelectionFileRun6eair_gammaHMN      = datapath_gammaHMN + TString("geniemc_gammaHMN_rhc_run6eair.root");
    MCSelectionFileRun7bwater_gammaHMN    = datapath_gammaHMN + TString("geniemc_gammaHMN_rhc_run7water.root");

    datapath_gammaHMP = "/path/to/directory/";
    MCSelectionFileRun2air_gammaHMP       = datapath_gammaHMP + TString("grun2airdpm.txtGamma.root");
    MCSelectionFileRun2water_gammaHMP     = datapath_gammaHMP + TString("grun2waterdpm.txtGamma.root");
    MCSelectionFileRun3air_gammaHMP       = datapath_gammaHMP + TString("geniemc_gammaHMP_fhc_run3air.root");
    MCSelectionFileRun3bair_gammaHMP      = datapath_gammaHMP + TString("grun3bairdpm.txtGamma.root");
    MCSelectionFileRun4air_gammaHMP       = datapath_gammaHMP + TString("geniemc_gammaHMP_fhc_run4air.root");
    MCSelectionFileRun4water_gammaHMP     = datapath_gammaHMP + TString("geniemc_gammaHMP_fhc_run4water.root");
    MCSelectionFileRun7cwater_gammaHMP    = datapath_gammaHMP + TString("grun7waterdpmNu.txtGamma.root");
    MCSelectionFileRun8air_gammaHMP       = datapath_gammaHMP + TString("geniemc_gammaHMP_fhc_run8air.root");
    MCSelectionFileRun8water_gammaHMP     = datapath_gammaHMP + TString("geniemc_gammaHMP_fhc_run8water.root");
    
    MCSelectionFileRun5water_gammaHMP     = datapath_gammaHMP + TString("grun5waterdpmANu.txtGamma.root");
    MCSelectionFileRun6bair_gammaHMP      = datapath_gammaHMP + TString("geniemc_gammaHMP_rhc_run6bair.root");
    MCSelectionFileRun6cair_gammaHMP      = datapath_gammaHMP + TString("grun6cairdpmANu.txtGamma.root");
    MCSelectionFileRun6dair_gammaHMP      = datapath_gammaHMP + TString("geniemc_gammaHMP_rhc_run6dair.root");
    MCSelectionFileRun6eair_gammaHMP      = datapath_gammaHMP + TString("geniemc_gammaHMP_rhc_run6eair.root");
    MCSelectionFileRun7bwater_gammaHMP    = datapath_gammaHMP + TString("geniemc_gammaHMP_rhc_run7water.root");
  }

  // -----------------------------------------------------------------------------------------
  // Fill data and MC histograms. POT normalisation run-by-run
  // -----------------------------------------------------------------------------------------

  if(isgamma){
    if(!positive){
      if(isrhc){
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun5water_gammaHMN) + GetPOTFromFile(DataSelectionFileRun6bair_gammaHMN) + GetPOTFromFile(DataSelectionFileRun6cair_gammaHMN) + GetPOTFromFile(DataSelectionFileRun6dair_gammaHMN) + GetPOTFromFile(DataSelectionFileRun6eair_gammaHMN) + GetPOTFromFile(DataSelectionFileRun7bwater_gammaHMN);
	
	FillDataHistograms(DataSelectionFileRun5water_gammaHMN);
	FillDataHistograms(DataSelectionFileRun6bair_gammaHMN);
	FillDataHistograms(DataSelectionFileRun6cair_gammaHMN);
	FillDataHistograms(DataSelectionFileRun6dair_gammaHMN);
	FillDataHistograms(DataSelectionFileRun6eair_gammaHMN);
	FillDataHistograms(DataSelectionFileRun7bwater_gammaHMN);
	
	FillMCHistograms(MCSelectionFileRun5water_gammaHMN,DataSelectionFileRun5water_gammaHMN);
	FillMCHistograms(MCSelectionFileRun6bair_gammaHMN,DataSelectionFileRun6bair_gammaHMN);
	FillMCHistograms(MCSelectionFileRun6cair_gammaHMN,DataSelectionFileRun6cair_gammaHMN);
	FillMCHistograms(MCSelectionFileRun6dair_gammaHMN,DataSelectionFileRun6dair_gammaHMN);
	FillMCHistograms(MCSelectionFileRun6eair_gammaHMN,DataSelectionFileRun6eair_gammaHMN);
	FillMCHistograms(MCSelectionFileRun7bwater_gammaHMN,DataSelectionFileRun7bwater_gammaHMN);

	if(whichfgd == 0)
	  FillMCHistograms(SandSelectionFileRHC_gammaHMN, totaldatapot, true);
      }
      else{
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun2air_gammaHMN) + GetPOTFromFile(DataSelectionFileRun2water_gammaHMN) + GetPOTFromFile(DataSelectionFileRun3bair_gammaHMN) + GetPOTFromFile(DataSelectionFileRun3air_gammaHMN) + GetPOTFromFile(DataSelectionFileRun4air_gammaHMN) + GetPOTFromFile(DataSelectionFileRun4water_gammaHMN);

	if(whichfgd == 0){
	  totaldatapot = GetPOTFromFile(DataSelectionFileRun2air_gammaHMN) + GetPOTFromFile(DataSelectionFileRun2water_gammaHMN) + GetPOTFromFile(DataSelectionFileRun3bair_gammaHMN) + GetPOTFromFile(DataSelectionFileRun3air_gammaHMN) + GetPOTFromFile(DataSelectionFileRun4air_gammaHMN) + GetPOTFromFile(DataSelectionFileRun4water_gammaHMN) + GetPOTFromFile(DataSelectionFileRun7cwater_gammaHMN) + GetPOTFromFile(DataSelectionFileRun8water_gammaHMN) + GetPOTFromFile(DataSelectionFileRun8air_gammaHMN);
	}
	
	
	FillDataHistograms(DataSelectionFileRun2air_gammaHMN);
	FillDataHistograms(DataSelectionFileRun2water_gammaHMN);
	FillDataHistograms(DataSelectionFileRun3bair_gammaHMN);
	FillDataHistograms(DataSelectionFileRun3air_gammaHMN);
	FillDataHistograms(DataSelectionFileRun4air_gammaHMN);
	FillDataHistograms(DataSelectionFileRun4water_gammaHMN);	
	if(whichfgd == 0){
	  FillDataHistograms(DataSelectionFileRun7cwater_gammaHMN);
	  FillDataHistograms(DataSelectionFileRun8air_gammaHMN);
	  FillDataHistograms(DataSelectionFileRun8water_gammaHMN);
	}
	
	FillMCHistograms(MCSelectionFileRun2air_gammaHMN, DataSelectionFileRun2air_gammaHMN);
	FillMCHistograms(MCSelectionFileRun2water_gammaHMN, DataSelectionFileRun2water_gammaHMN);
	FillMCHistograms(MCSelectionFileRun3bair_gammaHMN, DataSelectionFileRun3bair_gammaHMN);
	FillMCHistograms(MCSelectionFileRun3air_gammaHMN, DataSelectionFileRun3air_gammaHMN);
	FillMCHistograms(MCSelectionFileRun4air_gammaHMN, DataSelectionFileRun4air_gammaHMN);
	FillMCHistograms(MCSelectionFileRun4water_gammaHMN, DataSelectionFileRun4water_gammaHMN);
	if(whichfgd == 0){
	  FillMCHistograms(MCSelectionFileRun7cwater_gammaHMN, DataSelectionFileRun7cwater_gammaHMN);
	  FillMCHistograms(MCSelectionFileRun8air_gammaHMN, DataSelectionFileRun8air_gammaHMN);
	  FillMCHistograms(MCSelectionFileRun8water_gammaHMN, DataSelectionFileRun8water_gammaHMN);
	  
	  FillMCHistograms(SandSelectionFileFHC_gammaHMN, totaldatapot, true);
	}
      }
    }
    else{
      if(isrhc){
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun5water_gammaHMP) + GetPOTFromFile(DataSelectionFileRun6bair_gammaHMP) + GetPOTFromFile(DataSelectionFileRun6cair_gammaHMP) + GetPOTFromFile(DataSelectionFileRun6dair_gammaHMP) + GetPOTFromFile(DataSelectionFileRun6eair_gammaHMP) + GetPOTFromFile(DataSelectionFileRun7bwater_gammaHMP);
	
	FillDataHistograms(DataSelectionFileRun5water_gammaHMP);
	FillDataHistograms(DataSelectionFileRun6bair_gammaHMP);
	FillDataHistograms(DataSelectionFileRun6cair_gammaHMP);
	FillDataHistograms(DataSelectionFileRun6dair_gammaHMP);
	FillDataHistograms(DataSelectionFileRun6eair_gammaHMP);
	FillDataHistograms(DataSelectionFileRun7bwater_gammaHMP);
	
	FillMCHistograms(MCSelectionFileRun5water_gammaHMP,DataSelectionFileRun5water_gammaHMP);
	FillMCHistograms(MCSelectionFileRun6bair_gammaHMP,DataSelectionFileRun6bair_gammaHMP);
	FillMCHistograms(MCSelectionFileRun6cair_gammaHMP,DataSelectionFileRun6cair_gammaHMP);
	FillMCHistograms(MCSelectionFileRun6dair_gammaHMP,DataSelectionFileRun6dair_gammaHMP);
	FillMCHistograms(MCSelectionFileRun6eair_gammaHMP,DataSelectionFileRun6eair_gammaHMP);
	FillMCHistograms(MCSelectionFileRun7bwater_gammaHMP,DataSelectionFileRun7bwater_gammaHMP);
	
	FillMCHistograms(SandSelectionFileRHC_gammaHMP, totaldatapot, true);
      }
      else{
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun2air_gammaHMP) + GetPOTFromFile(DataSelectionFileRun2water_gammaHMP) + GetPOTFromFile(DataSelectionFileRun3bair_gammaHMP) + GetPOTFromFile(DataSelectionFileRun3air_gammaHMP) + GetPOTFromFile(DataSelectionFileRun4air_gammaHMP) + GetPOTFromFile(DataSelectionFileRun4water_gammaHMP) + GetPOTFromFile(DataSelectionFileRun7cwater_gammaHMP) + GetPOTFromFile(DataSelectionFileRun8water_gammaHMP) + GetPOTFromFile(DataSelectionFileRun8air_gammaHMP);
	
	//totaldatapot = GetPOTFromFile(DataSelectionFileRun8water_gammaHMP) + GetPOTFromFile(DataSelectionFileRun8air_gammaHMP);
	
	FillDataHistograms(DataSelectionFileRun2air_gammaHMP);
	FillDataHistograms(DataSelectionFileRun2water_gammaHMP);
	FillDataHistograms(DataSelectionFileRun3bair_gammaHMP);
	FillDataHistograms(DataSelectionFileRun3air_gammaHMP);
	FillDataHistograms(DataSelectionFileRun4air_gammaHMP);
	FillDataHistograms(DataSelectionFileRun4water_gammaHMP);
	FillDataHistograms(DataSelectionFileRun7cwater_gammaHMP);
	
	FillDataHistograms(DataSelectionFileRun8air_gammaHMP);
	FillDataHistograms(DataSelectionFileRun8water_gammaHMP);
	
	FillMCHistograms(MCSelectionFileRun2water_gammaHMP, DataSelectionFileRun2water_gammaHMP);
	FillMCHistograms(MCSelectionFileRun2air_gammaHMP, DataSelectionFileRun2air_gammaHMP);
	FillMCHistograms(MCSelectionFileRun3bair_gammaHMP, DataSelectionFileRun3bair_gammaHMP);
	FillMCHistograms(MCSelectionFileRun3air_gammaHMP, DataSelectionFileRun3air_gammaHMP);
	FillMCHistograms(MCSelectionFileRun4air_gammaHMP, DataSelectionFileRun4air_gammaHMP);
	FillMCHistograms(MCSelectionFileRun4water_gammaHMP, DataSelectionFileRun4water_gammaHMP);
	FillMCHistograms(MCSelectionFileRun7cwater_gammaHMP, DataSelectionFileRun7cwater_gammaHMP);
	
	FillMCHistograms(MCSelectionFileRun8air_gammaHMP, DataSelectionFileRun8air_gammaHMP);
	FillMCHistograms(MCSelectionFileRun8water_gammaHMP, DataSelectionFileRun8water_gammaHMP);
	
	FillMCHistograms(SandSelectionFileFHC_gammaHMP, totaldatapot, true);
      }
    }
  }
  else{ // nue - antinue selections
    if(!positive){
      if(isrhc){
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun5water) + GetPOTFromFile(DataSelectionFileRun6bair) + GetPOTFromFile(DataSelectionFileRun6cair) + GetPOTFromFile(DataSelectionFileRun6dair) + GetPOTFromFile(DataSelectionFileRun6eair) + GetPOTFromFile(DataSelectionFileRun7bwater);
	
	FillDataHistograms(DataSelectionFileRun5water);
	FillDataHistograms(DataSelectionFileRun6bair);
	FillDataHistograms(DataSelectionFileRun6cair);
	FillDataHistograms(DataSelectionFileRun6dair);
	FillDataHistograms(DataSelectionFileRun6eair);
	FillDataHistograms(DataSelectionFileRun7bwater);
	
	FillMCHistograms(MCSelectionFileRun5water,DataSelectionFileRun5water);
	FillMCHistograms(MCSelectionFileRun6bair,DataSelectionFileRun6bair);
	FillMCHistograms(MCSelectionFileRun6cair,DataSelectionFileRun6cair);
	FillMCHistograms(MCSelectionFileRun6dair,DataSelectionFileRun6dair);
	FillMCHistograms(MCSelectionFileRun6eair,DataSelectionFileRun6eair);
	FillMCHistograms(MCSelectionFileRun7bwater,DataSelectionFileRun7bwater);
	if(whichfgd == 0)
	  FillMCHistograms(SandSelectionFileRHC, totaldatapot, true);
      }
      else{
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun2air) + GetPOTFromFile(DataSelectionFileRun2water) + GetPOTFromFile(DataSelectionFileRun3bair) + GetPOTFromFile(DataSelectionFileRun3air) + GetPOTFromFile(DataSelectionFileRun4air) + GetPOTFromFile(DataSelectionFileRun4water);
	
	if(whichfgd == 0)
	  totaldatapot = GetPOTFromFile(DataSelectionFileRun2air) + GetPOTFromFile(DataSelectionFileRun2water) + GetPOTFromFile(DataSelectionFileRun3bair) + GetPOTFromFile(DataSelectionFileRun3air) + GetPOTFromFile(DataSelectionFileRun4air) + GetPOTFromFile(DataSelectionFileRun4water) + GetPOTFromFile(DataSelectionFileRun7cwater) + GetPOTFromFile(DataSelectionFileRun8water) + GetPOTFromFile(DataSelectionFileRun8air);
	
	FillDataHistograms(DataSelectionFileRun2air);
	FillDataHistograms(DataSelectionFileRun2water);
	FillDataHistograms(DataSelectionFileRun3bair);
	FillDataHistograms(DataSelectionFileRun3air);
	FillDataHistograms(DataSelectionFileRun4air);
	FillDataHistograms(DataSelectionFileRun4water);
	
	if(whichfgd == 0){
	  FillDataHistograms(DataSelectionFileRun7cwater);
	  FillDataHistograms(DataSelectionFileRun8air);
	  FillDataHistograms(DataSelectionFileRun8water);
	}
	
	FillMCHistograms(MCSelectionFileRun2water, DataSelectionFileRun2water);
	FillMCHistograms(MCSelectionFileRun2air, DataSelectionFileRun2air);
	FillMCHistograms(MCSelectionFileRun3bair, DataSelectionFileRun3bair);
	FillMCHistograms(MCSelectionFileRun3air, DataSelectionFileRun3air);
	FillMCHistograms(MCSelectionFileRun4air, DataSelectionFileRun4air);
	FillMCHistograms(MCSelectionFileRun4water, DataSelectionFileRun4water);
	
	if(whichfgd == 0){
	  FillMCHistograms(MCSelectionFileRun7cwater, DataSelectionFileRun7cwater);
	  FillMCHistograms(MCSelectionFileRun8air, DataSelectionFileRun8air);
	  FillMCHistograms(MCSelectionFileRun8water, DataSelectionFileRun8water);
	  
	  FillMCHistograms(SandSelectionFileFHC, totaldatapot, true);
	}
      }
    }
    else{
      if(isrhc){
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun5water_anue) + GetPOTFromFile(DataSelectionFileRun6bair_anue) + GetPOTFromFile(DataSelectionFileRun6cair_anue) + GetPOTFromFile(DataSelectionFileRun6dair_anue) + GetPOTFromFile(DataSelectionFileRun6eair_anue) + GetPOTFromFile(DataSelectionFileRun7bwater_anue);
	
	FillDataHistograms(DataSelectionFileRun5water_anue);
	FillDataHistograms(DataSelectionFileRun6bair_anue);
	FillDataHistograms(DataSelectionFileRun6cair_anue);
	FillDataHistograms(DataSelectionFileRun6dair_anue);
	FillDataHistograms(DataSelectionFileRun6eair_anue);
	FillDataHistograms(DataSelectionFileRun7bwater_anue);
	
	FillMCHistograms(MCSelectionFileRun5water_anue,DataSelectionFileRun5water_anue);
	FillMCHistograms(MCSelectionFileRun6bair_anue,DataSelectionFileRun6bair_anue);
	FillMCHistograms(MCSelectionFileRun6cair_anue,DataSelectionFileRun6cair_anue);
	FillMCHistograms(MCSelectionFileRun6dair_anue,DataSelectionFileRun6dair_anue);
	FillMCHistograms(MCSelectionFileRun6eair_anue,DataSelectionFileRun6eair_anue);
	FillMCHistograms(MCSelectionFileRun7bwater_anue,DataSelectionFileRun7bwater_anue);
	
	FillMCHistograms(SandSelectionFileRHC_anue, totaldatapot, true);
      }
      else{
	Double_t totaldatapot = GetPOTFromFile(DataSelectionFileRun2air_anue) + GetPOTFromFile(DataSelectionFileRun2water_anue) + GetPOTFromFile(DataSelectionFileRun3bair_anue) + GetPOTFromFile(DataSelectionFileRun3air_anue) + GetPOTFromFile(DataSelectionFileRun4air_anue) + GetPOTFromFile(DataSelectionFileRun4water_anue) + GetPOTFromFile(DataSelectionFileRun7cwater_anue);
	
	FillDataHistograms(DataSelectionFileRun2air_anue);
	FillDataHistograms(DataSelectionFileRun2water_anue);
	FillDataHistograms(DataSelectionFileRun3bair_anue);
	FillDataHistograms(DataSelectionFileRun3air_anue);
	FillDataHistograms(DataSelectionFileRun4air_anue);
	FillDataHistograms(DataSelectionFileRun4water_anue);
	FillDataHistograms(DataSelectionFileRun7cwater_anue);
	
	//FillDataHistograms(DataSelectionFileRun8air_anue);
	//FillDataHistograms(DataSelectionFileRun8water_anue);
	
	FillMCHistograms(MCSelectionFileRun2water_anue, DataSelectionFileRun2water_anue);
	FillMCHistograms(MCSelectionFileRun2air_anue, DataSelectionFileRun2air_anue);
	FillMCHistograms(MCSelectionFileRun3bair_anue, DataSelectionFileRun3bair_anue);
	FillMCHistograms(MCSelectionFileRun3air_anue, DataSelectionFileRun3air_anue);
	FillMCHistograms(MCSelectionFileRun4air_anue, DataSelectionFileRun4air_anue);
	FillMCHistograms(MCSelectionFileRun4water_anue, DataSelectionFileRun4water_anue);
	FillMCHistograms(MCSelectionFileRun7cwater_anue, DataSelectionFileRun7cwater_anue);
	
	//FillMCHistograms(MCSelectionFileRun8air_anue, DataSelectionFileRun8air_anue);
	//FillMCHistograms(MCSelectionFileRun8water_anue, DataSelectionFileRun8water_anue);
	
	FillMCHistograms(SandSelectionFileFHC_anue, totaldatapot, true);
      }
    }
  }

  // Get neutrino fluxes
  TH1D* fluxhisto3[4];
  fluxhisto3[0] = GetMeanNeutrinoEnergy("nue", true);
  fluxhisto3[1] = GetMeanNeutrinoEnergy("nueb", true);
  fluxhisto3[2] = GetMeanNeutrinoEnergy("nue", false);
  fluxhisto3[3] = GetMeanNeutrinoEnergy("nueb", false);

  fluxhisto3[0]->SetLineColor(kRed);
  fluxhisto3[1]->SetLineColor(kOrange);
  fluxhisto3[2]->SetLineColor(kBlue);
  fluxhisto3[3]->SetLineColor(kCyan);

  fluxhisto3[0]->Scale(1/fluxhisto3[0]->Integral());
  fluxhisto3[1]->Scale(1/fluxhisto3[1]->Integral());
  fluxhisto3[2]->Scale(1/fluxhisto3[2]->Integral());
  fluxhisto3[3]->Scale(1/fluxhisto3[3]->Integral());

  TLegend *mylegend300 = new TLegend(0.53,0.65,0.85,0.85);
  mylegend300->SetFillColor(0); // white background
  mylegend300->SetBorderSize(0);
  mylegend300->SetTextSize(0.036);
  mylegend300->AddEntry(fluxhisto3[0],"FHC T2K #nu_{e} flux","l");
  mylegend300->AddEntry(fluxhisto3[1],"FHC T2K #bar#nu_{e} flux","l");
  mylegend300->AddEntry(fluxhisto3[2],"RHC T2K #nu_{e} flux","l");
  mylegend300->AddEntry(fluxhisto3[3],"RHC T2K #bar#nu_{e} flux","l");

  TCanvas *c300 = new TCanvas("FluxCompNorm","FluxCompNorm");
  fluxhisto3[0]->SetStats(0);
  fluxhisto3[0]->SetTitle("T2K #nu_{e} and #bar#nu_{e} fluxes");
  fluxhisto3[0]->GetYaxis()->SetTitleOffset(1.2);
  fluxhisto3[0]->GetXaxis()->SetTitle("E_{#nu} [GeV]");
  fluxhisto3[0]->GetXaxis()->SetRangeUser(0.0,10.0);
  fluxhisto3[0]->GetYaxis()->SetRangeUser(0.0,0.1);
  fluxhisto3[0]->GetYaxis()->SetTitle("#nu_{e}/#bar#nu_{e} flux (/cm^{2}/50 MeV/10^{21} POT)");
  //fluxhisto3[0]->GetYaxis()->SetTitle(" ");
  fluxhisto3[0]->Draw("hist");
  fluxhisto3[1]->Draw("samehist");
  fluxhisto3[2]->Draw("samehist");
  fluxhisto3[3]->Draw("samehist");
  mylegend300->Draw();

  TH1D* fluxhisto4[4];
  fluxhisto4[0] = GetMeanNeutrinoEnergy("nue", true);
  fluxhisto4[1] = GetMeanNeutrinoEnergy("nueb", true);
  fluxhisto4[2] = GetMeanNeutrinoEnergy("nue", false);
  fluxhisto4[3] = GetMeanNeutrinoEnergy("nueb", false);

  fluxhisto4[0]->SetLineColor(kRed);
  fluxhisto4[1]->SetLineColor(kOrange);
  fluxhisto4[2]->SetLineColor(kBlue);
  fluxhisto4[3]->SetLineColor(kCyan);

  TLegend *mylegend301 = new TLegend(0.53,0.65,0.85,0.85);
  mylegend301->SetFillColor(0); // white background
  mylegend301->SetBorderSize(0);
  mylegend301->SetTextSize(0.036);
  mylegend301->AddEntry(fluxhisto4[0],"FHC T2K #nu_{e} flux","l");
  mylegend301->AddEntry(fluxhisto4[1],"FHC T2K #bar#nu_{e} flux","l");
  mylegend301->AddEntry(fluxhisto4[2],"RHC T2K #nu_{e} flux","l");
  mylegend301->AddEntry(fluxhisto4[3],"RHC T2K #bar#nu_{e} flux","l");

  TCanvas *c301 = new TCanvas("FluxComp","FluxComp");
  fluxhisto4[0]->SetStats(0);
  fluxhisto4[0]->SetTitle("T2K #nu_{e} and #bar#nu_{e} fluxes");
  fluxhisto4[0]->GetYaxis()->SetTitleOffset(1.2);
  fluxhisto4[0]->GetXaxis()->SetTitle("E_{#nu} [GeV]");
  fluxhisto4[0]->GetXaxis()->SetRangeUser(0.0,10.0);
  fluxhisto4[0]->GetYaxis()->SetTitle("#nu_{e}/#bar#nu_{e} flux (/cm^{2}/50 MeV/10^{21} POT)");
  c301->SetLogy();
  //fluxhisto4[0]->GetYaxis()->SetTitle(" ");
  fluxhisto4[0]->Draw("hist");
  fluxhisto4[1]->Draw("samehist");
  fluxhisto4[2]->Draw("samehist");
  fluxhisto4[3]->Draw("samehist");
  mylegend301->Draw();

  TH1D* fluxhisto; TH1D* fluxhisto2;
  Int_t fluxtype = -1;
  if(positive){
    if(isrhc){
      fluxhisto  = GetMeanNeutrinoEnergy("nueb", false);
      fluxhisto2 = GetMeanNeutrinoEnergy("nueb", false);
      fluxtype   = 6;
    }
    else{
      fluxhisto  =  GetMeanNeutrinoEnergy("nueb", true);
      fluxhisto2 =  GetMeanNeutrinoEnergy("nueb", true);
      fluxtype   = 5;
    }
  }
  else{
    if(isrhc){
      fluxhisto  = GetMeanNeutrinoEnergy("nue", false);
      fluxhisto2 = GetMeanNeutrinoEnergy("nue", false);
      fluxtype   = 4;
    }
    else{
      fluxhisto  = GetMeanNeutrinoEnergy("nue", true);
      fluxhisto2 = GetMeanNeutrinoEnergy("nue", true);
      fluxtype   = 3;
    }
  }

  cout << "INFO::Flux info: Mean energy = " << fluxhisto->GetMean() << " , integral = " << fluxhisto->Integral() << endl;
  fluxhisto->Scale(10e-10);

  TH1D* gammamchisto = (TH1D*)GammaH[5]->Clone("gammamchisto");
  TH1D* gammamchisto2 = (TH1D*)GammaH[5]->Clone("gammamchisto2");
  TH1D* othermchisto = (TH1D*)OtherBkgH[5]->Clone("othermchisto");
  othermchisto->Add(MuonBkg[5]);
  othermchisto->Add(ProtonBkg[5]);
  TH1D* signalmchisto = (TH1D*)CCH[5]->Clone("signalmchisto");
  signalmchisto->Add(CCHnPi[5]);

  IncludeOverflow(gammamchisto);
  IncludeOverflow(othermchisto);
  IncludeOverflow(signalmchisto);

  if(isgamma){
    gammamchisto->Add(othermchisto);
    gammamchisto->Add(signalmchisto);
    gammamchisto2->Add(othermchisto);
    gammamchisto2->Add(signalmchisto);
  }

  // Theta plots
  TH1D* thetamchisto_4  = (TH1D*)CCH[4]->Clone("thetamchisto_4");
  thetamchisto_4->Add(CCHnPi[4]);
  thetamchisto_4->Add(GammaH[4]);
  thetamchisto_4->Add(MuonBkg[4]);
  thetamchisto_4->Add(OtherBkgH[4]);
  thetamchisto_4->Add(ProtonBkg[4]);

  IncludeOverflow(thetamchisto_4);

  // Decorate
  thetamchisto_4->SetLineColor(kWhite);
  thetamchisto_4->SetFillColor(kBlue);
  thetamchisto_4->SetFillStyle(3018);
  thetamchisto_4->SetMarkerStyle(1);
  thetamchisto_4->SetMarkerSize(0.00001);

  // Histograms for fractional errors
  TH1 *sdetsysthistofrac; TH1 *sxssysthistofrac; TH1 *sfluxsysthistofrac;
  TH1 *odetsysthistofrac; TH1 *oxssysthistofrac; TH1 *ofluxsysthistofrac;
  TH1 *gdetsysthistofrac; TH1 *gxssysthistofrac; TH1 *gfluxsysthistofrac;

  if(drawerror){
    TString selstring("FHCNUE_ALLGAMMABKG");
    if(positive)
      selstring = "FHCANUE_ALLGAMMABKG";
    if(isrhc){
      selstring = "RHCNUE_ALLGAMMABKG";
      if(positive)
	selstring = "RHCANUE_ALLGAMMABKG";
    }
    if(isgamma){
      selstring = "FHCGAMMASIDEBAND_ALLGAMMABKG";
      if(positive)
	selstring = "FHCANUEGAMMASIDEBAND_ALLGAMMABKG";
      if(isrhc){
	selstring = "RHCGAMMASIDEBAND_ALLGAMMABKG";
	if(positive)
	  selstring = "RHCANUEGAMMASIDEBAND_ALLGAMMABKG";
      }
    }
    
    TH1 *gdetsysthisto  = GetSystVector("DetSyst.root",  selstring.Data(), gammamchisto);
    TH1 *gxssysthisto   = GetSystVector("XsSyst.root",   selstring.Data(), gammamchisto);
    TH1 *gfluxsysthisto = GetSystVector("FluxSyst.root", selstring.Data(), gammamchisto, true);

    gdetsysthistofrac  = GetSystVector("DetSyst.root",  selstring.Data(), gammamchisto, false, true);
    gxssysthistofrac   = GetSystVector("XsSyst.root",   selstring.Data(), gammamchisto, false, true);
    gfluxsysthistofrac = GetSystVector("FluxSyst.root", selstring.Data(), gammamchisto, true,  true);
    
    for(Int_t i=1; i <= gammamchisto->GetNbinsX(); i++){
      Double_t nevents = sqrt(gdetsysthisto->GetBinContent(i)*gdetsysthisto->GetBinContent(i) + gxssysthisto->GetBinContent(i)*gxssysthisto->GetBinContent(i) + gfluxsysthisto->GetBinContent(i)*gfluxsysthisto->GetBinContent(i));
      gammamchisto->SetBinContent(i, nevents);
    }

    selstring = "FHCNUE_CCINCLUSIVE";
    if(positive)
      selstring = "FHCANUE_CCINCLUSIVE";
    if(isrhc){
      selstring = "RHCNUE_CCINCLUSIVE";
      if(positive)
	selstring = "RHCANUE_CCINCLUSIVE";
    }

    if(!isgamma){
      TH1 *sdetsysthisto  = GetSystVector("DetSyst.root",  selstring.Data(), signalmchisto);
      TH1 *sxssysthisto   = GetSystVector("XsSyst.root",   selstring.Data(), signalmchisto);
      TH1 *sfluxsysthisto = GetSystVector("FluxSyst.root", selstring.Data(), signalmchisto, true);

      sdetsysthistofrac  = GetSystVector("DetSyst.root",  selstring.Data(), signalmchisto, false, true);
      sxssysthistofrac   = GetSystVector("XsSyst.root",   selstring.Data(), signalmchisto, false, true);
      sfluxsysthistofrac = GetSystVector("FluxSyst.root", selstring.Data(), signalmchisto, true,  true);
    
      for(Int_t i=1; i <= gammamchisto->GetNbinsX(); i++){
	Double_t nevents = sqrt(sdetsysthisto->GetBinContent(i)*sdetsysthisto->GetBinContent(i) + sxssysthisto->GetBinContent(i)*sxssysthisto->GetBinContent(i) + sfluxsysthisto->GetBinContent(i)*sfluxsysthisto->GetBinContent(i));
	gammamchisto->SetBinContent(i, nevents + gammamchisto->GetBinContent(i));
      }
      
      selstring = "FHCNUE_ALLOTHERBKG";
      if(positive)
	selstring = "FHCANUE_ALLOTHERBKG";
      if(isrhc){
	selstring = "RHCNUE_ALLOTHERBKG";
	if(positive)
	  selstring = "RHCANUE_ALLOTHERBKG";
      }
      
      TH1 *odetsysthisto  = GetSystVector("DetSyst.root",  selstring.Data(), othermchisto);
      TH1 *oxssysthisto   = GetSystVector("XsSyst.root",   selstring.Data(), othermchisto);
      TH1 *ofluxsysthisto = GetSystVector("FluxSyst.root", selstring.Data(), othermchisto, true);

      odetsysthistofrac  = GetSystVector("DetSyst.root",  selstring.Data(), othermchisto, false, true);
      oxssysthistofrac   = GetSystVector("XsSyst.root",   selstring.Data(), othermchisto, false, true);
      ofluxsysthistofrac = GetSystVector("FluxSyst.root", selstring.Data(), othermchisto, true,  true);
      
      for(Int_t i=1; i <= gammamchisto->GetNbinsX(); i++){
	Double_t nevents = sqrt(odetsysthisto->GetBinContent(i)*odetsysthisto->GetBinContent(i) + oxssysthisto->GetBinContent(i)*oxssysthisto->GetBinContent(i) + ofluxsysthisto->GetBinContent(i)*ofluxsysthisto->GetBinContent(i));
	gammamchisto->SetBinContent(i, nevents + gammamchisto->GetBinContent(i));
      }

      TH1D* thetamchisto_1 = GetThetaSystematic(gdetsysthistofrac, gxssysthistofrac, gfluxsysthistofrac, MomTheta2D[1]);
      thetamchisto_1->SetNameTitle("thetamchisto_1","thetamchisto_1");
      TH1D* thetamchisto_2 = GetThetaSystematic(odetsysthistofrac, oxssysthistofrac, ofluxsysthistofrac, MomTheta2D[2]);
      thetamchisto_2->SetNameTitle("thetamchisto_2","thetamchisto_2");
      TH1D* thetamchisto_3 = GetThetaSystematic(sdetsysthistofrac, sxssysthistofrac, sfluxsysthistofrac, MomTheta2D[0]);
      thetamchisto_3->SetNameTitle("thetamchisto_3","thetamchisto_3");
      
      for(Int_t i=0; i <= thetamchisto_4->GetNbinsX(); i++){
	thetamchisto_4->SetBinError(i, thetamchisto_1->GetBinContent(i) + thetamchisto_2->GetBinContent(i) + thetamchisto_3->GetBinContent(i));
      }
    }
    else{
      MomTheta2D[1]->Add(MomTheta2D[2]);
      MomTheta2D[1]->Add(MomTheta2D[0]);
      TH1D* thetamchisto_1 = GetThetaSystematic(gdetsysthistofrac, gxssysthistofrac, gfluxsysthistofrac, MomTheta2D[1]);
      thetamchisto_1->SetNameTitle("thetamchisto_1","thetamchisto_1");
      for(Int_t i=0; i <= thetamchisto_4->GetNbinsX(); i++){
	thetamchisto_4->SetBinError(i, thetamchisto_1->GetBinContent(i));
      }
    }
  }

  /*
  TFile *file1 = new TFile("rhcnue_outfile.root","READ");
  TH2D* histo = (TH2D*)file1->Get("MomSignalElec2D");
  TH2D* ahisto = (TH2D*)file1->Get("AngSignalElec2D");
  TGraphAsymmErrors* effmom = (TGraphAsymmErrors*)file1->Get("momeffGraph");
  TGraphAsymmErrors* effang = (TGraphAsymmErrors*)file1->Get("angeffGraph");
  TH1D* momdis = (TH1D*)file1->Get("SEffTrueEventsCCInc");
  TH1D* angdis = (TH1D*)file1->Get("SAngTrueEventsCCInc");
  histo->SetDirectory(0);
  ahisto->SetDirectory(0);
  momdis->SetDirectory(0);
  angdis->SetDirectory(0);
  file1->Close();
  cout << histo->GetEntries() << endl;

  TFile *file2 = new TFile("rhcanue_outfile.root","READ");
  TH2D* histo2 = (TH2D*)file2->Get("MomSignalElec2D");
  TH2D* ahisto2 = (TH2D*)file2->Get("AngSignalElec2D");
  TGraphAsymmErrors* effmom2 = (TGraphAsymmErrors*)file2->Get("momeffGraph");
  TGraphAsymmErrors* effang2 = (TGraphAsymmErrors*)file2->Get("angeffGraph");
  TH1D* momdis2 = (TH1D*)file2->Get("SEffTrueEventsCCInc");
  TH1D* angdis2 = (TH1D*)file2->Get("SAngTrueEventsCCInc");
  ahisto2->SetDirectory(0);
  histo2->SetDirectory(0);
  momdis2->SetDirectory(0);
  angdis2->SetDirectory(0);
  file2->Close();
  cout << histo2->GetEntries() << endl;

  ElecAngRes2D[0]->Add(ahisto2);
  ElecAngRes2D[0]->Add(ahisto);
  ElecMomRes2D[0]->Add(histo2);
  ElecMomRes2D[0]->Add(histo);
  */

  TFile *f = new TFile(outFile.Data(), "RECREATE");
  c300->Write();
  c301->Write();
  fluxhisto2->SetNameTitle("NuEFlux","NuEFlux");
  if(positive)
    fluxhisto2->SetNameTitle("ANuEFlux","ANuEFlux");
  fluxhisto2->Write();

  if(drawerror){
    TString selstring("FHCNUE_ALLGAMMABKG");
    if(positive)
      selstring = "FHCANUE_ALLGAMMABKG";
    if(isrhc){
      selstring = "RHCNUE_ALLGAMMABKG";
      if(positive)
        selstring = "RHCANUE_ALLGAMMABKG";
    }
    if(isgamma){
      selstring = "FHCGAMMASIDEBAND_ALLGAMMABKG";
      if(positive)
        selstring = "FHCANUEGAMMASIDEBAND_ALLGAMMABKG";
      if(isrhc){
        selstring = "RHCGAMMASIDEBAND_ALLGAMMABKG";
        if(positive)
          selstring = "RHCANUEGAMMASIDEBAND_ALLGAMMABKG";
      }
    }

    TCanvas *cSystUncerGammaBkg =  GetTotalSystematicHisto(gammamchisto2, gxssysthistofrac, gdetsysthistofrac, gfluxsysthistofrac, selstring.Data());
    cSystUncerGammaBkg->Write();

    if(!isgamma){
      selstring = "FHCNUE_CCINCLUSIVE";
      if(positive)
	selstring = "FHCANUE_CCINCLUSIVE";
      if(isrhc){
	selstring = "RHCNUE_CCINCLUSIVE";
	if(positive)
	  selstring = "RHCANUE_CCINCLUSIVE";
      }

      TCanvas *cSystUncerSignal =  GetTotalSystematicHisto(signalmchisto, sxssysthistofrac, sdetsysthistofrac, sfluxsysthistofrac, selstring.Data());
      cSystUncerSignal->Write();

      selstring = "FHCNUE_ALLOTHERBKG";
      if(positive)
        selstring = "FHCANUE_ALLOTHERBKG";
      if(isrhc){
        selstring = "RHCNUE_ALLOTHERBKG";
        if(positive)
          selstring = "RHCANUE_ALLOTHERBKG";
      }
      
      TCanvas *cSystUncerOtherBkg =  GetTotalSystematicHisto(othermchisto, oxssysthistofrac, odetsysthistofrac, ofluxsysthistofrac, selstring.Data());
      cSystUncerOtherBkg->Write();
    }
  }

  // -----------------------------------------------------------------------------------------
  // Draw data and MC on canvas. Decorate
  // -----------------------------------------------------------------------------------------

  for(Int_t j = 0; j < n; j++){
    CCH[j]->SetStats(0);
    CCHnPi[j]->SetStats(0);
    GammaH[j]->SetStats(0);
    MuonBkg[j]->SetStats(0);
    OtherBkgH[j]->SetStats(0);
    ProtonBkg[j]->SetStats(0);
    DataH[j]->SetStats(0);
    
    CCH[j]->SetLineColor(intcolour[0]);
    CCH[j]->SetFillColor(intcolour[0]);
    if(mixccsignal){
      CCH[j]->SetLineColor(intcolour[5]);
      CCH[j]->SetFillColor(intcolour[5]);
    }
    CCH[j]->SetFillStyle(3352);// 3000 + intcolour[0] 3944
    CCHnPi[j]->SetLineColor(intcolour[1]);
    CCHnPi[j]->SetFillColor(intcolour[1]);
    CCHnPi[j]->SetFillStyle(3000 + intcolour[1]);
    GammaH[j]->SetLineColor(intcolour[2]);
    GammaH[j]->SetFillColor(intcolour[2]);
    GammaH[j]->SetFillStyle(3005);
    MuonBkg[j]->SetLineColor(intcolour[3]);
    MuonBkg[j]->SetFillColor(intcolour[3]);
    MuonBkg[j]->SetFillStyle(3000 + intcolour[3]);
    OtherBkgH[j]->SetLineColor(intcolour[4]);
    OtherBkgH[j]->SetFillColor(intcolour[4]);
    OtherBkgH[j]->SetFillStyle(3000 + intcolour[4]);
    ProtonBkg[j]->SetLineColor(intcolour[6]);
    ProtonBkg[j]->SetFillColor(intcolour[6]);
    ProtonBkg[j]->SetFillStyle(3000 + intcolour[6]);

    IncludeOverflow(CCH[j]);
    IncludeOverflow(CCHnPi[j]);
    IncludeOverflow(GammaH[j]);
    IncludeOverflow(MuonBkg[j]);
    IncludeOverflow(OtherBkgH[j]);
    IncludeOverflow(ProtonBkg[j]);
    IncludeOverflow(DataH[j]);

    IncludeUnderflow(CCH[j]);
    IncludeUnderflow(CCHnPi[j]);
    IncludeUnderflow(GammaH[j]);
    IncludeUnderflow(MuonBkg[j]);
    IncludeUnderflow(OtherBkgH[j]);
    IncludeUnderflow(ProtonBkg[j]);
    IncludeUnderflow(DataH[j]);

    TH1D* allmchisto = (TH1D*)CCH[j]->Clone("allmchisto");
    allmchisto->Add(GammaH[j]);
    allmchisto->Add(MuonBkg[j]);
    allmchisto->Add(OtherBkgH[j]);
    allmchisto->Add(ProtonBkg[j]);
    allmchisto->Add(CCHnPi[j]);

    // Decorate
    allmchisto->SetLineColor(kWhite);
    allmchisto->SetFillColor(kBlue);
    allmchisto->SetFillStyle(3018);
    allmchisto->SetMarkerStyle(1);
    allmchisto->SetMarkerSize(0.00001);

    TLegend *mylegend1 = new TLegend(0.40,0.30,0.85,0.87);
    if(j==4) mylegend1->SetY1(0.48);
    mylegend1->SetFillColor(0); // white background
    mylegend1->SetBorderSize(0);
    mylegend1->SetTextSize(0.039);

    Double_t dataentries = DataH[j]->Integral();
    Double_t cc0pientries = CCH[j]->Integral();
    Double_t ccotherentries = CCHnPi[j]->Integral();
    Double_t gammaentries = GammaH[j]->Integral();
    Double_t muonentries = MuonBkg[j]->Integral();
    Double_t protonentries = ProtonBkg[j]->Integral();
    Double_t otherentries = OtherBkgH[j]->Integral();
    Double_t allmcentries = cc0pientries + ccotherentries + gammaentries + muonentries + protonentries + otherentries;
    Double_t ccincentries = cc0pientries + ccotherentries;

    //mixccsignal
    if(mixccsignal){
      CCH[j]->Add(CCHnPi[j]);
    }
    
    if(!isrhc){
      mylegend1->AddEntry((TObject*)0    ,Form("T2K FHC %.2f #times 10^{20} POT", totaldatapot*1e-20), "" );
    }
    else{
      mylegend1->AddEntry((TObject*)0    ,Form("T2K RHC %.2f #times 10^{20} POT", totaldatapot*1e-20), "" );
    }

    mylegend1->AddEntry((TObject*)0    ,"", "" );

    mylegend1->AddEntry(DataH[j]    ,Form("Data                       %i", (Int_t)dataentries) );
    if(!isgenie)
      mylegend1->AddEntry((TObject*)0, Form("NEUT  5.3.2 Total  %.2f",allmcentries), "");
    else
      mylegend1->AddEntry((TObject*)0, Form("GENIE 2.8.0 Total   %.2f",allmcentries), "");

    if(positive){
      if(mixccsignal){
	mylegend1->AddEntry(CCH[j]      ,Form("#bar#nu_{e} CC                          %.2f (%.2f\%)", ccincentries,100*ccincentries/allmcentries) ,"f");
      }
      else{
	mylegend1->AddEntry(CCH[j]      ,Form("#bar#nu_{e} CC-0#pi                 %.2f (%.2f\%)", cc0pientries,100*cc0pientries/allmcentries) ,"f");
	mylegend1->AddEntry(CCHnPi[j]   ,Form("#bar#nu_{e} CC-Other            %.2f (%.2f\%)", ccotherentries,100*ccotherentries/allmcentries),"f");
      }
      mylegend1->AddEntry(GammaH[j]   ,Form("#gamma background          %.2f (%.2f\%)",gammaentries,100*gammaentries/allmcentries)    ,"f");
      mylegend1->AddEntry(MuonBkg[j]  ,Form("#mu background              %.2f (%.2f\%)",   muonentries,100*muonentries/allmcentries)      ,"f");
      if(!isgamma)
	mylegend1->AddEntry(ProtonBkg[j],Form("Proton background   %.2f (%.2f\%)", protonentries, 100*protonentries/allmcentries  ),"f");
      mylegend1->AddEntry(OtherBkgH[j],Form("Other background     %.2f (%.2f\%)", otherentries,100*otherentries/allmcentries)    ,"f");
    }
    else{
      if(mixccsignal){
	mylegend1->AddEntry(CCH[j]      ,Form("#nu_{e} CC                          %.2f (%.2f\%)", ccincentries,100*ccincentries/allmcentries) ,"f");
      }
      else{
	mylegend1->AddEntry(CCH[j]      ,Form("#nu_{e} CC-0#pi                 %.2f (%.2f\%)", cc0pientries,100*cc0pientries/allmcentries) ,"f");
	mylegend1->AddEntry(CCHnPi[j]   ,Form("#nu_{e} CC-Other            %.2f (%.2f\%)", ccotherentries,100*ccotherentries/allmcentries),"f");
      }
      mylegend1->AddEntry(GammaH[j]   ,Form("#gamma background          %.2f (%.2f\%)",gammaentries,100*gammaentries/allmcentries)    ,"f");
      mylegend1->AddEntry(MuonBkg[j]  ,Form("#mu background              %.2f (%.2f\%)",   muonentries,100*muonentries/allmcentries)      ,"f");
      mylegend1->AddEntry(OtherBkgH[j],Form("Other background     %.2f (%.2f\%)", otherentries,100*otherentries/allmcentries)    ,"f");
    }

    TString hsn = CCH[j]->GetName(); hsn += "_hs0";
    TString hst = CCH[j]->GetTitle(); hst += "_hs0";
    THStack *hs0 = new THStack(hsn.Data(),hst.Data());
    hs0->Add(OtherBkgH[j],"same");
    if(positive)
      hs0->Add(ProtonBkg[j],"same");
    hs0->Add(MuonBkg[j],"same");
    hs0->Add(GammaH[j],"same");
    if(mixccsignal){
      hs0->Add(CCH[j],"same");
    }
    else{
      hs0->Add(CCHnPi[j],"same");
      hs0->Add(CCH[j],"sames");
    }  
    
    TString dhsn = DataH[j]->GetName(); dhsn += "par_can";
    TString dhst = DataH[j]->GetTitle(); dhst += "par_can";
    TCanvas *c = new TCanvas(dhsn.Data(),dhst.Data()); // 1500, 1250
    
    if(!addratio || j == 3 || j > 6){
      // Set text size for external naming - for example T2K Preliminary
      //tpt->SetTextSize(0.04);
      hs0->Draw("");

      //c->Update();
      //TPaveStats *ps = (TPaveStats*)hs0->GetStack()->Last()->FindObject("stats");
      //ps->SetY1NDC(0.83); ps->SetY2NDC(0.87);
      //ps->SetX1NDC(0.44); ps->SetX2NDC(0.64);
      //ps->SetBorderSize(1);
      //ps->SetTextSize(0.03);
      //ps->SetOptStat(1000000);
      
      //TPaveText *pstext = (TPaveText*)hs0->GetStack()->Last()->FindObject("title");
      //pstext->SetTextSize(0.1);
      
      //c->Modified();
      
      hs0->SetTitle("FHC CC-#nu_{e} Inclusive");
      if(positive)
	hs0->SetTitle("FHC CC-#bar#nu_{e} Inclusive");
      if(isrhc){
	hs0->SetTitle("RHC CC-#nu_{e} Inclusive");
	if(positive)
	  hs0->SetTitle("RHC CC-#bar#nu_{e} Inclusive");
      }

      if(whichfgd == 0)
	hs0->SetTitle(Form("FGD1 %s",hs0->GetTitle()));
      else if(whichfgd == 1)
	hs0->SetTitle(Form("FGD2 %s",hs0->GetTitle()));
      
      if(j == 0){
	hs0->GetXaxis()->SetTitle("Cos(#theta)");
	hs0->GetYaxis()->SetTitle("Entries / 0.05");
      }
      else if(j == 1){
	hs0->GetXaxis()->SetTitle("Q^{2} [GeV^{2}/c^{2}]");
	hs0->GetYaxis()->SetTitle("Entries / 0.05 [GeV^{2}/c^{2}]");
      }
      else if(j == 2){
	hs0->GetXaxis()->SetTitle("Sin(#theta)");
	hs0->GetYaxis()->SetTitle("Entries / 0.05");
      }
      else if(j == 3){
	hs0->GetXaxis()->SetTitle("Recon Position Z [mm]");
	hs0->GetYaxis()->SetTitle("Entries");
      }
      else if(j == 4){
	hs0->GetXaxis()->SetTitle("#theta [rad]");
	hs0->GetYaxis()->SetTitle("Entries / 0.1 [rad]"); // 0.1575
	if(drawerror){
	  thetamchisto_4->Draw("same e2");
	 
	  mylegend1->AddEntry((TObject*)0    ,"", "" );
	  mylegend1->AddEntry(allmchisto   , "Systematic Uncertainties"  ,"f");
	}
      }
      else if(j == 5){
	hs0->GetXaxis()->SetTitle("p_{e} [MeV/c]");
	hs0->GetYaxis()->SetTitle("Entries / 300 [MeV/c]");
	if(drawerror){
	  //allmchisto->Draw("e2same");
	  for(Int_t i=1; i <= gammamchisto->GetNbinsX(); i++)
	    allmchisto->SetBinError(i, gammamchisto->GetBinContent(i));
	  allmchisto->Draw("same e2");
	 
	  mylegend1->AddEntry((TObject*)0    ,"", "" );
	  mylegend1->AddEntry(allmchisto   , "Systematic Error"  ,"f");
	}
      }
      else if(j == 6){
	hs0->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	hs0->GetYaxis()->SetTitle("Entries / 300 [MeV/c]");
      }
      else if(j == 7){
	hs0->GetXaxis()->SetTitle("FGD1-BrECal ToF [ns]");
	if(whichfgd == 1)
	  hs0->GetXaxis()->SetTitle("FGD2-BrECal ToF [ns]");
      }
      else if(j == 8){
	hs0->GetXaxis()->SetTitle("FGD1-DsECal ToF [ns]");
	if(whichfgd == 1)
	  hs0->GetXaxis()->SetTitle("FGD2-DsECal ToF [ns]");
      }
      else if(j == 9){
	hs0->GetXaxis()->SetTitle("L_{e}");
	hs0->GetYaxis()->SetTitle("Entries");
      }
      else if(j == 10){
	hs0->GetXaxis()->SetTitle("E / p");
	hs0->GetYaxis()->SetTitle("Entries");
      }
      else if(j == 11){
	hs0->GetXaxis()->SetTitle("p [MeV/c]");
	hs0->GetYaxis()->SetTitle("Entries");
      }
      
      DataH[j]->SetMarkerStyle(20);
      //DataH[j]->SetMarkerSize(2);
      DataH[j]->Draw("samese");
      
      //c->Update();
      //TPaveStats *ps2 = (TPaveStats*)DataH[j]->FindObject("stats");
      //ps2->SetX1NDC(0.64); ps2->SetX2NDC(0.84);
      //ps2->SetY1NDC(0.83); ps2->SetY2NDC(0.87);
      //ps2->SetBorderSize(1);
      //ps2->SetTextSize(0.03);
      //c->Modified();
      
      mylegend1->Draw();
      c->RedrawAxis();
    }
    else{
      // Set text size for external naming - for example T2K Preliminary
      //tpt->SetTextSize(5.75); // 0.15

      TPad *pad1 = new TPad("pad1", "pad1", 0, 0.31, 1, 1.0);
      pad1->SetBottomMargin(0.015); // Upper and lower plot are joined
      //pad1->SetGridx();         // Vertical grid
      pad1->Draw();             // Draw the upper pad: pad1
      pad1->cd();               // pad1 becomes the current pa
      
      hs0->Draw("");
      hs0->SetTitle("FHC CC-#nu_{e} Inclusive");
      if(positive)
	hs0->SetTitle("FHC CC-#bar#nu_{e} Inclusive");
      if(isrhc){
	hs0->SetTitle("RHC CC-#nu_{e} Inclusive");
	if(positive)
	  hs0->SetTitle("RHC CC-#bar#nu_{e} Inclusive");
      }
      
      if(isgamma){
	hs0->SetTitle("FHC HMN #gamma selection");
	if(positive)
	  hs0->SetTitle("FHC HMP #gamma selection");
	if(isrhc){
	  hs0->SetTitle("RHC HMN #gamma selection");
	  if(positive)
	    hs0->SetTitle("RHC HMP #gamma selection");
	}
      }

     if(whichfgd == 0)
	hs0->SetTitle(Form("FGD1 %s",hs0->GetTitle()));
      else if(whichfgd == 1)
	hs0->SetTitle(Form("FGD2 %s",hs0->GetTitle())); 
      
      if(j == 0){
	hs0->GetXaxis()->SetTitle("cos(#theta)");
	hs0->GetYaxis()->SetTitle("Entries / 0.05");
      }
      else if(j == 1){
	hs0->GetXaxis()->SetTitle("Q^{2} [GeV^{2}/c^{2}]");
	hs0->GetYaxis()->SetTitle("Entries / 0.05 [GeV^{2}/c^{2}]");
      }
      else if(j == 2){
	hs0->GetXaxis()->SetTitle("sin(#theta)");
	hs0->GetYaxis()->SetTitle("Entries / 0.05");
      }
      else if(j == 3){
	hs0->GetXaxis()->SetTitle("Recon Position Z [mm]");
	hs0->GetYaxis()->SetTitle("Entries");
      }
      else if(j == 4){
	hs0->GetXaxis()->SetTitle("#theta [rad]");
	hs0->GetYaxis()->SetTitle("Entries / 0.1 [rad]"); // 0.1575
	if(drawerror){
	  thetamchisto_4->Draw("same e2");
	 
	  mylegend1->AddEntry((TObject*)0    ,"", "" );
	  mylegend1->AddEntry(allmchisto   , "Systematic Uncertainties"  ,"f");
	}
      }
      else if(j == 5){
	hs0->GetXaxis()->SetTitle("p [MeV/c]");
	hs0->GetYaxis()->SetTitle("Entries / 300 [MeV/c]");
	if(drawerror){
	  for(Int_t i=1; i <= gammamchisto->GetNbinsX(); i++)
	    allmchisto->SetBinError(i, gammamchisto->GetBinContent(i));
	  allmchisto->Draw("e2same");
	  mylegend1->AddEntry((TObject*)0    ,"", "" );
	  mylegend1->AddEntry(allmchisto   , "Systematic Uncertainties"  ,"f");
	}
      }
      else if(j == 6){
	hs0->GetXaxis()->SetTitle("p_{t} [MeV/c]");
	hs0->GetYaxis()->SetTitle("Entries / 300 [MeV/c]");
      }

      //hs0->GetYaxis()->SetNdivisions(505);
      //hs0->GetYaxis()->SetTitleSize(45);
      //hs0->GetYaxis()->SetTitleFont(43);
      hs0->GetYaxis()->SetTitleOffset(1.3); // 1.6
      //hs0->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
      //hs0->GetYaxis()->SetLabelSize(38);
      
      hs0->SetTitle("");

      DataH[j]->SetMarkerStyle(20);
      //DataH[j]->SetMarkerSize(2);
      DataH[j]->Draw("sameep");
      mylegend1->Draw();
      //pad1->cd();
      //pad1->RedrawAxis();
  
      c->cd();
      TPad *pad2 = new TPad("pad2", "pad2", 0, 0.01, 1, 0.30);
      pad2->SetTopMargin(0);
      pad2->SetBottomMargin(0.25);
      //pad2->SetGridx(); // vertical grid
      pad2->Draw();
      pad2->cd();       // pad2 becomes the current pad
      
      TH1D *dataratio3 = (TH1D*)DataH[j]->Clone(Form("%s_dataratio3",DataH[j]->GetName()));
      TH1D *mcratio    = (TH1D*)CCH[j]->Clone(Form("%s_mcratio",CCH[j]->GetName()));
      if(!mixccsignal)
	mcratio->Add(CCHnPi[j]);
      mcratio->Add(GammaH[j]);
      mcratio->Add(MuonBkg[j]);
      mcratio->Add(ProtonBkg[j]);
      mcratio->Add(OtherBkgH[j]);
      
      dataratio3->SetMinimum(0.0);
      dataratio3->SetMaximum(2.55); // .. range - 2.95
      mcratio->Sumw2();
      dataratio3->Sumw2();
      dataratio3->SetStats(0);
      dataratio3->Divide(mcratio);

      if(drawerror && j == 5){
	TH1D *mcratio2    = (TH1D*)mcratio->Clone("mcratio2");
	mcratio2->Add(gammamchisto);

	TH1D *dataratio4 = (TH1D*)dataratio3->Clone("dataratio4");
	TH1D *dataratio5 = (TH1D*)mcratio->Clone(Form("%s_dataratio5",DataH[j]->GetName()));

	//dataratio4->SetMinimum(0.0);
	//dataratio4->SetMaximum(2.95); // .. range
	//mcratio2->Sumw2();
	//dataratio5->Sumw2();
	//dataratio4->SetStats(0);
	mcratio2->Divide(dataratio5);
	for(Int_t i=1; i <= dataratio5->GetNbinsX(); i++){
	  //cout << i << ". = " << mcratio2->GetBinContent(i) << " , " << dataratio5->GetBinContent(i) << endl;
	  dataratio4->SetBinContent(i, 1.0);
	  dataratio4->SetBinError(i, mcratio2->GetBinContent(i)-1.0);
	}

	dataratio4->SetFillColor(kBlue);
	dataratio4->SetLineColor(kBlue);
	dataratio4->SetFillStyle(3018);
	dataratio4->SetMarkerStyle(1);
	dataratio4->SetMarkerSize(0.00001);
	dataratio4->Draw("e2");
	dataratio4->SetTitle("");

	// Y axis ratio plot settings
	dataratio4->GetYaxis()->SetTitle("Data / MC");
	//dataratio4->GetYaxis()->SetNdivisions(505);
	//dataratio4->GetYaxis()->SetTitleSize(45);
	//dataratio4->GetYaxis()->SetTitleFont(43);
	dataratio4->GetYaxis()->SetTitleOffset(1.30);
	//dataratio4->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	//dataratio4->GetYaxis()->SetLabelSize(38);

	//dataratio4->GetXaxis()->SetTitleSize(45); // 14
	//dataratio4->GetXaxis()->SetTitleFont(43);
	dataratio4->GetXaxis()->SetTitleOffset(1.3); // 3.2
	//dataratio4->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	//dataratio4->GetXaxis()->SetLabelSize(38); // 14
	dataratio4->GetXaxis()->SetTitle("p [MeV/c]");
	
	if(isgamma){
	  if(isrhc){
	    if(positive)
	      latex.DrawLatex(1100,-0.75,"(c)");
	    else
	      latex.DrawLatex(1100,-0.75,"(b)");
	  }
	  else{
	    latex.DrawLatex(1100,-0.75,"(a)");
	  }
	}
	else{
	  //latex.DrawLatex(4500,-0.75,"p [MeV/c]");
	  if(isrhc){
	    if(positive)
	      latex.DrawLatex(2700,-0.75,"(c)");
	    else
	      latex.DrawLatex(2700,-0.75,"(b)");
	  }
	  else{
	    latex.DrawLatex(2700,-0.75,"(a)");
	  }
	}
      }
      else if(drawerror && j == 4){
	TH1D *dataratio4 = (TH1D*)dataratio3->Clone("dataratio4");
	TH1D *dataratio5 = (TH1D*)mcratio->Clone(Form("%s_dataratio5",DataH[j]->GetName()));
	
	TH1D *mcratio2    = (TH1D*)thetamchisto_4->Clone("thetamchisto_4new");
	for(Int_t i=1; i <= thetamchisto_4->GetNbinsX(); i++){
	  mcratio2->SetBinContent(i, thetamchisto_4->GetBinContent(i) + thetamchisto_4->GetBinError(i));
	}
	mcratio2->Divide(dataratio5);

	for(Int_t i=1; i <= dataratio5->GetNbinsX(); i++){
	  dataratio4->SetBinContent(i, 1.0);
	  dataratio4->SetBinError(i, mcratio2->GetBinContent(i)-1.0);
	}

	dataratio4->SetFillColor(kBlue);
	dataratio4->SetLineColor(kBlue);
	dataratio4->SetFillStyle(3018);
	dataratio4->SetMarkerStyle(1);
	dataratio4->SetMarkerSize(0.00001);
	dataratio4->Draw("e2");
	dataratio4->SetTitle("");

	// Y axis ratio plot settings
	dataratio4->GetYaxis()->SetTitle("Data / MC");
	//dataratio4->GetYaxis()->SetNdivisions(505);
	//dataratio4->GetYaxis()->SetTitleSize(45);
	//dataratio4->GetYaxis()->SetTitleFont(43);
	dataratio4->GetYaxis()->SetTitleOffset(1.30);
	//dataratio4->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	//dataratio4->GetYaxis()->SetLabelSize(38);

	//dataratio4->GetXaxis()->SetTitleSize(45); // 15
	//dataratio4->GetXaxis()->SetTitleFont(43);
	dataratio4->GetXaxis()->SetTitleOffset(1.3); // 3.2
	//dataratio4->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	//dataratio4->GetXaxis()->SetLabelSize(38); // 15
	dataratio4->GetXaxis()->SetTitle("#theta [rad]");

	//latex.DrawLatex(1.40,-0.75,"#theta [rad]");
	if(isrhc){
	  if(positive)
	    latex.DrawLatex(0.8,-0.75,"(c)");
	  else
	    latex.DrawLatex(0.8,-0.75,"(b)");
	}
	else{
	  latex.DrawLatex(0.8,-0.75,"(a)");
	}
	
      }

      dataratio3->SetMarkerStyle(21);
      dataratio3->Draw("epsame");
      dataratio3->SetTitle("");
      
      // Y axis ratio plot settings
      dataratio3->GetYaxis()->SetTitle("Data / MC");
      dataratio3->GetYaxis()->SetNdivisions(505);
      dataratio3->GetYaxis()->SetTitleSize(15); // 45
      dataratio3->GetYaxis()->SetTitleFont(43);
      dataratio3->GetYaxis()->SetTitleOffset(1.30);
      dataratio3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
      dataratio3->GetYaxis()->SetLabelSize(15); // 38
      
      // X axis ratio plot settings
      if(j == 0){
	dataratio3->GetXaxis()->SetTitle("cos(#theta)");
      }
      else if(j == 1){
	dataratio3->GetXaxis()->SetTitle("Q^{2} [GeV^{2}/c^{2}]");
      }
      else if(j == 2){
	dataratio3->GetXaxis()->SetTitle("sin(#theta)");
      }
      else if(j == 3){
	dataratio3->GetXaxis()->SetTitle("Recon Position Z [mm]");
      }
      else if(j == 4){
	dataratio3->GetXaxis()->SetTitle("#theta [rad]");
      }
      else if(j == 5){
	dataratio3->GetXaxis()->SetTitle("p [MeV/c]");	
      }
      else if(j == 6){
	dataratio3->GetXaxis()->SetTitle("p_{t} [MeV/c]");	
      }

      dataratio3->GetXaxis()->SetTitleSize(15); // 45
      dataratio3->GetXaxis()->SetTitleFont(43);
      dataratio3->GetXaxis()->SetTitleOffset(3.5); // 4.8
      dataratio3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
      dataratio3->GetXaxis()->SetLabelSize(15); // 38
      
      TLine *line = new TLine(0,1,5400,1);
      if(isgamma){
	line->SetX2(2100);
      }
      line->SetLineColor(kRed);
      TLine *line2 = new TLine(0,1,1,1);
      line2->SetLineColor(kRed);
      TLine *line3 = new TLine(0,1,1.6,1); // 3.15
      line3->SetLineColor(kRed);
      TLine *line4 = new TLine(0,1,2000,1);
      line4->SetLineColor(kRed);
      
      //dataratio->Draw("ep");
      //dataratio->GetXaxis()->SetTitle("p [MeV/c]");
      //dataratio->GetYaxis()->SetTitle("Data/MC");
      //dataratio->SetTitle("Data/MC");
      if(j == 4)
	line3->Draw();
      else if(j == 5)
	line->Draw();
      else if(j == 6)
	line4->Draw();
      else
	line2->Draw();
    }
    //tpt->SetTextSize(5.75); // 0.15
    //tpt->Draw();
    //c->GetCanvas()->SetGrayscale();
    //tpt->DrawLatex(0.5,0.1,"b");
    c->Write();
    
  }
  
  // Set text size for external naming - for example T2K Preliminary
  //tpt->SetTextSize(0.04);

  // -----------------------------------------------------------------------------------------
  // Draw efficiencies
  // -----------------------------------------------------------------------------------------

  if(!isgamma){
    
    IncludeOverflow(SEffTrue); IncludeOverflow(EffTrue); IncludeOverflow(SPurTrue); IncludeOverflow(PurTrue);
    cout << "INFO::TOTAL SELECTED EVENTS = " << SEffTrue->Integral() << " , TOTAL TRUTH EVENTS = " << EffTrue->Integral() << endl;
    cout << "INFO::TOTAL EFFICIENCY      = " << SEffTrue->Integral()/EffTrue->Integral() << endl;
    cout << "INFO::TOTAL SIGNAL EVENTS   = " << SPurTrue->Integral() << " , TOTAL EVENTS = " << PurTrue->Integral() << endl;
    cout << "INFO::TOTAL PURITY          = " << SPurTrue->Integral()/PurTrue->Integral() << endl;

    EffTrue->Write();
    SEffTrue->Write();
    SAngTrue->Write();
    AngTrue->Write();
    // Efficiency-purity histograms
    TCanvas *momeff = GetEffPurGraph(1, SEffTrue, EffTrue, SPurTrue, PurTrue);//, SEffTrueEventsCCInc); 
    //tpt->Draw();
    momeff->Write();
    TCanvas *angeff = GetEffPurGraph(2, SAngTrue, AngTrue, SPurAngTrue, PurAngTrue);//, SAngTrueEventsCCInc);
    //tpt->Draw();
    angeff->Write();
    Int_t cc0pitype = 100;
    if(positive)
      cc0pitype = 102;
    TCanvas *momeffCC0Pi = GetEffPurGraph(cc0pitype, SEffTrueCC0Pi, EffTrueCC0Pi, SEffTrueCCOther, EffTrueCCOther, SEffTrueEventsCC0Pi, SEffTrueEventsCCOther); 
    //tpt->Draw();
    momeffCC0Pi->Write();
    TCanvas *angeffCC0Pi = GetEffPurGraph(cc0pitype+1, SAngTrueCC0Pi, AngTrueCC0Pi, SAngTrueCCOther, AngTrueCCOther, SAngTrueEventsCC0Pi, SAngTrueEventsCCOther);
    //tpt->Draw();
    angeffCC0Pi->Write();
    TCanvas *fluxeff = GetEffPurGraph(fluxtype, SNEffTrue, NEffTrue, SNPurTrue, NPurTrue, fluxhisto); 
    fluxeff->Write();
    
    TCanvas *zposeff = GetEffPurGraph(0, SNPurTrue, NPurTrue, SPosTrue, PosTrue); 
    //tpt->Draw();
    zposeff->Write();

    for(int i = 1; i <= SEffTrue->GetNbinsX(); i++){
      //cout << EffTrue->GetBinContent(i) << " , " << SEffTrue->GetBinContent(i) << endl;
      EffTrue2->SetBinContent(i, EffTrue->GetBinContent(i));
      SEffTrue2->SetBinContent(i, SEffTrue->GetBinContent(i));
    }
    TGraphAsymmErrors *momeffGraph = new TGraphAsymmErrors(SEffTrue2, EffTrue2);
    TGraphAsymmErrors *angeffGraph = new TGraphAsymmErrors(SAngTrue, AngTrue);
    momeffGraph->Write("momeffGraph");
    angeffGraph->Write("angeffGraph");
    SEffTrueEventsCCInc->Write();
    SAngTrueEventsCCInc->Write();

    // For neut-genie comparisons
    TH1D* SignalSelMomNew    = new TH1D("SignalSelMomNew"  ,"SignalSelMomNew"  ,SignalSelMom->GetNbinsX(), 0, SignalSelMom->GetNbinsX());
    TH1D* TruthSelMomNew     = new TH1D("TruthSelMomNew"   ,"TruthSelMomNew"   ,TruthSelMom->GetNbinsX(),  0, TruthSelMom->GetNbinsX());

    for(int i = 1; i <= SignalSelMom->GetNbinsX(); i++){
      SignalSelMomNew->SetBinContent(i, SignalSelMom->GetBinContent(i));
      TruthSelMomNew->SetBinContent(i, TruthSelMom->GetBinContent(i));
    }

    SignalSelAng->Sumw2(true);
    TruthSelAng->Sumw2(true);
    TGraphAsymmErrors *EffSignalSelMom = new TGraphAsymmErrors(SignalSelMomNew,TruthSelMomNew,"b(0.0001,1)");
    TGraphAsymmErrors *EffSignalSelAng = new TGraphAsymmErrors(SignalSelAng,TruthSelAng,"b(0.0001,1)");

    TAxis *ax = EffSignalSelMom->GetHistogram()->GetXaxis();
    Double_t x1 = ax->GetBinLowEdge(1);
    Double_t x2 = ax->GetBinUpEdge(ax->GetNbins());
    EffSignalSelMom->GetHistogram()->GetXaxis()->Set(SignalSelMom->GetNbinsX(),x1,x2);

    for(int i = 0; i < n1-1; i++){
      TString temp = Form("%i - %i MeV/c", (Int_t)momparnum[i], (Int_t)momparnum[i+1]);
      EffSignalSelMom->GetHistogram()->GetXaxis()->SetBinLabel(i+1, temp.Data());
    }

    TString temptitle = Form(", %g <= cos(#theta) <= %g, p > %g MeV/c", 0.707, 1.00, MINMOMENTUM);
    TString namestring("FHC CC-#nu_{e}");
    if(positive)
      namestring = "FHC CC-#bar#nu_{e}";
    if(isrhc){
      namestring = "RHC CC-#nu_{e}";
      if(positive)
	namestring = "RHC CC-#bar#nu_{e}";
    }
    temptitle = namestring + temptitle;

    //
    Int_t nbinsx = SignalSelMom2->GetNbinsX() + SignalSelMom3->GetNbinsX() + 2;
    TH1D* SignalSelMom2New = new TH1D("SignalSelMom2New"  ,"SignalSelMom2New" ,nbinsx, 0, nbinsx);
    TH1D* TruthSelMom2New  = new TH1D("TruthSelMom2New"   ,"TruthSelMom2New"  ,nbinsx, 0, nbinsx);

    for(int i = 1; i <= SignalSelMom2->GetNbinsX(); i++){
      SignalSelMom2New->SetBinContent(i, SignalSelMom2->GetBinContent(i));
      TruthSelMom2New->SetBinContent(i, TruthSelMom2->GetBinContent(i));
    }

    for(int i = 1; i <= SignalSelMom3->GetNbinsX(); i++){
      Int_t ibin = i + SignalSelMom2->GetNbinsX() + 1;
      SignalSelMom2New->SetBinContent(ibin, SignalSelMom3->GetBinContent(i));
      TruthSelMom2New->SetBinContent(ibin, TruthSelMom3->GetBinContent(i));
    }

    TGraphAsymmErrors *EffSignalSelMom2 = new TGraphAsymmErrors(SignalSelMom2New,TruthSelMom2New);
    TAxis *ax1 = EffSignalSelMom2->GetHistogram()->GetXaxis();
    Double_t x11 = ax1->GetBinLowEdge(1);
    Double_t x21 = ax1->GetBinUpEdge(ax1->GetNbins());
    EffSignalSelMom2->GetHistogram()->GetXaxis()->Set(SignalSelMom2New->GetNbinsX(),x11,x21);

    for(Int_t k=0; k < SignalSelMom2->GetNbinsX(); k++){
      TString binname = Form("%i - %i", (Int_t)momparnum2[k], (Int_t)momparnum2[k+1]);
      EffSignalSelMom2->GetHistogram()->GetXaxis()->SetBinLabel(k+1, binname.Data());
    }

    for(Int_t k=SignalSelMom2->GetNbinsX()+1; k < nbinsx-1; k++){
      Int_t nnn = SignalSelMom2->GetNbinsX()+1;
      TString binname = Form("%i - %i", (Int_t)momparnum2[k-nnn], (Int_t)momparnum2[k+1-nnn]);
      EffSignalSelMom2->GetHistogram()->GetXaxis()->SetBinLabel(k+1, binname.Data());
    }

    //
    nbinsx = SignalSelMom4->GetNbinsX() + SignalSelMom5->GetNbinsX() + 1;
    TH1D* SignalSelMom3New = new TH1D("SignalSelMom3New"  ,"SignalSelMom3New" ,nbinsx, 0, nbinsx);
    TH1D* TruthSelMom3New  = new TH1D("TruthSelMom3New"   ,"TruthSelMom3New"  ,nbinsx, 0, nbinsx);

    for(int i = 1; i <= SignalSelMom4->GetNbinsX(); i++){
      SignalSelMom3New->SetBinContent(i, SignalSelMom4->GetBinContent(i));
      TruthSelMom3New->SetBinContent(i, TruthSelMom4->GetBinContent(i));
    }

    for(int i = 1; i <= SignalSelMom5->GetNbinsX(); i++){
      Int_t ibin = i + SignalSelMom4->GetNbinsX();
      SignalSelMom3New->SetBinContent(ibin, SignalSelMom5->GetBinContent(i));
      TruthSelMom3New->SetBinContent(ibin, TruthSelMom5->GetBinContent(i));
    }

    TGraphAsymmErrors *EffSignalSelMom3 = new TGraphAsymmErrors(SignalSelMom3New,TruthSelMom3New);
    TAxis *ax1 = EffSignalSelMom3->GetHistogram()->GetXaxis();
    Double_t x11 = ax1->GetBinLowEdge(1);
    Double_t x21 = ax1->GetBinUpEdge(ax1->GetNbins());
    EffSignalSelMom3->GetHistogram()->GetXaxis()->Set(SignalSelMom3New->GetNbinsX(),x11,x21);

    for(Int_t k=0; k < SignalSelMom4->GetNbinsX(); k++){
      if(isrhc){
	TString binname = Form("%i - %i", (Int_t)momparxsrhc[k], (Int_t)momparxsrhc[k+1]);
	EffSignalSelMom3->GetHistogram()->GetXaxis()->SetBinLabel(k+1, binname.Data());
      }
      else{
	TString binname = Form("%i - %i", (Int_t)momparxsfhc[k], (Int_t)momparxsfhc[k+1]);
        EffSignalSelMom3->GetHistogram()->GetXaxis()->SetBinLabel(k+1, binname.Data());
      }
    }
    
    for(Int_t k=SignalSelMom4->GetNbinsX(); k < nbinsx-1; k++){
      Int_t nnn = SignalSelMom4->GetNbinsX();
      if(isrhc){
	TString binname = Form("%i - %i", (Int_t)momparxsrhc[k-nnn], (Int_t)momparxsrhc[k+1-nnn]);
	EffSignalSelMom3->GetHistogram()->GetXaxis()->SetBinLabel(k+1, binname.Data());
      }
      else{
	TString binname = Form("%i - %i", (Int_t)momparxsfhc[k-nnn], (Int_t)momparxsfhc[k+1-nnn]);
        EffSignalSelMom3->GetHistogram()->GetXaxis()->SetBinLabel(k+1, binname.Data());
      }
    }

    //
    if(isgenie){
      EffSignalSelMom->SetNameTitle("GenieEffMom","GenieEffMom");
      EffSignalSelMom->SetMarkerColor(4);
      EffSignalSelMom->SetMarkerStyle(4);
      EffSignalSelMom->SetLineColor(4);

      EffSignalSelAng->SetNameTitle("GenieEffAng","GenieEffAng");
      EffSignalSelAng->SetMarkerColor(4);
      EffSignalSelAng->SetMarkerStyle(4);
      EffSignalSelAng->SetLineColor(4);

      EffSignalSelMom2->SetNameTitle("GenieEffMom2","GenieEffMom2");
      EffSignalSelMom2->SetMarkerColor(4);
      EffSignalSelMom2->SetMarkerStyle(4);
      EffSignalSelMom2->SetLineColor(4);

      EffSignalSelMom3->SetNameTitle("GenieEffMom3","GenieEffMom3");
      EffSignalSelMom3->SetMarkerColor(4);
      EffSignalSelMom3->SetMarkerStyle(4);
      EffSignalSelMom3->SetLineColor(4);
    }
    else{
      EffSignalSelMom->SetNameTitle("NeutEffMom","NeutEffMom");
      EffSignalSelMom->SetMarkerColor(2);
      EffSignalSelMom->SetMarkerStyle(25);
      EffSignalSelMom->SetLineColor(2);

      EffSignalSelAng->SetNameTitle("NeutEffAng","NeutEffAng");
      EffSignalSelAng->SetMarkerColor(2);
      EffSignalSelAng->SetMarkerStyle(25);
      EffSignalSelAng->SetLineColor(2);

      EffSignalSelMom2->SetNameTitle("NeutEffMom2","NeutEffMom2");
      EffSignalSelMom2->SetMarkerColor(2);
      EffSignalSelMom2->SetMarkerStyle(25);
      EffSignalSelMom2->SetLineColor(2);

      EffSignalSelMom3->SetNameTitle("NeutEffMom3","NeutEffMom3");
      EffSignalSelMom3->SetMarkerColor(2);
      EffSignalSelMom3->SetMarkerStyle(25);
      EffSignalSelMom3->SetLineColor(2);
    }

    EffSignalSelMom->SetTitle(temptitle.Data());
    EffSignalSelMom->GetYaxis()->SetTitleOffset(1.2);
    EffSignalSelMom->GetYaxis()->SetRangeUser(0.0,1.0);
    EffSignalSelMom->GetYaxis()->SetTitle("Efficiency");

    EffSignalSelAng->SetTitle(temptitle.Data());
    EffSignalSelAng->GetYaxis()->SetTitleOffset(1.2);
    EffSignalSelAng->GetYaxis()->SetRangeUser(0.0,1.0);
    EffSignalSelAng->GetYaxis()->SetTitle("Efficiency");
    EffSignalSelAng->GetXaxis()->SetTitle("Cos(#theta)");

    temptitle = namestring + TString(" Efficiencies");
    EffSignalSelMom2->SetTitle(temptitle.Data());
    EffSignalSelMom2->GetYaxis()->SetTitleOffset(1.2);
    EffSignalSelMom2->GetYaxis()->SetRangeUser(0.0,1.0);
    EffSignalSelMom2->GetYaxis()->SetTitle("Efficiency");
    EffSignalSelMom2->GetXaxis()->SetLabelSize(0.025);

    EffSignalSelMom3->SetTitle(temptitle.Data());
    EffSignalSelMom3->GetYaxis()->SetTitleOffset(1.2);
    EffSignalSelMom3->GetYaxis()->SetRangeUser(0.0,1.0);
    EffSignalSelMom3->GetYaxis()->SetTitle("Efficiency");

    EffSignalSelMom->Write();
    EffSignalSelAng->Write();
    EffSignalSelMom2->Write();
    EffSignalSelMom3->Write();

    TrueMomCosSelec->Divide(TrueMomCosTruth);
    TrueMomCosSelec->SetStats(0);
    TrueMomCosSelec->GetYaxis()->SetTitle("cos(#theta)_{true}");
    TrueMomCosSelec->GetXaxis()->SetTitle("p_{true} MeV/c");
    temptitle = namestring + TString("  p-cos(#theta) efficiency");
    if(isgenie)
      temptitle += TString(" Genie");
    else
      temptitle += TString(" Neut");
    TrueMomCosSelec->SetTitle(temptitle.Data());
    TCanvas *Eff2d = new TCanvas("Eff2d","Eff2d");
    TrueMomCosSelec->Draw("colz");
    //tpt->Draw();
    Eff2d->Write();
  }

  // -----------------------------------------------------------------------------------------
  // Additional plots
  // -----------------------------------------------------------------------------------------

  // Momentum and angular resolutions
  TCanvas* Cmomresallelec = new TCanvas("Cmomresallelec", "Cmomresallelec");
  ElecMomRes2D[1]->Draw("colz");
  ElecMomRes2D[1]->SetTitle("True vs Reco electron momentum");
  ElecMomRes2D[1]->GetYaxis()->SetTitle("Reco p_{e} [MeV/c]");
  ElecMomRes2D[1]->GetXaxis()->SetTitle("True p_{e} [MeV/c]");
  //tpt->Draw();
  Cmomresallelec->Write();
  
  TCanvas* Cmomressigelec = new TCanvas("Cmomressigelec", "Cmomressigelec"); // ,1500,1250
  Cmomressigelec->cd();
  ElecMomRes2D[0]->Draw("colz");
  ElecMomRes2D[0]->SetStats(0);
  ElecMomRes2D[0]->SetTitle("");
  /*
  //ElecMomRes2D[0]->SetTitle("True vs Reco signal electron momentum");
  //ElecMomRes2D[0]->GetYaxis()->SetNdivisions(505);
  ElecMomRes2D[0]->GetYaxis()->SetTitleSize(45);
  ElecMomRes2D[0]->GetYaxis()->SetTitleFont(43);
  ElecMomRes2D[0]->GetYaxis()->SetTitleOffset(1.5);
  ElecMomRes2D[0]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ElecMomRes2D[0]->GetYaxis()->SetLabelSize(38);
  
  ElecMomRes2D[0]->GetXaxis()->SetTitleSize(45); // 15
  ElecMomRes2D[0]->GetXaxis()->SetTitleFont(43);
  ElecMomRes2D[0]->GetXaxis()->SetTitleOffset(1.5);
  ElecMomRes2D[0]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ElecMomRes2D[0]->GetXaxis()->SetLabelSize(38); // 15

  ElecMomRes2D[0]->GetZaxis()->SetTitleSize(45); // 15
  ElecMomRes2D[0]->GetZaxis()->SetTitleFont(43);
  ElecMomRes2D[0]->GetZaxis()->SetTitleOffset(1.12);
  ElecMomRes2D[0]->GetZaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ElecMomRes2D[0]->GetZaxis()->SetLabelSize(38); // 15
  */
  ElecMomRes2D[0]->GetYaxis()->SetTitle("p_{reco} [MeV/c]");
  ElecMomRes2D[0]->GetXaxis()->SetTitle("p_{true} [MeV/c]");
  ElecMomRes2D[0]->GetZaxis()->SetTitle("Events");
  gPad->Update();
  gPad->SetTicks();
  gPad->RedrawAxis();
  ElecMomRes2D[0]->Write();
  //tpt->Draw();
  Cmomressigelec->Write();

  TCanvas* Cangresallelec = new TCanvas("Cangresallelec", "Cangresallelec");
  ElecAngRes2D[1]->Draw("colz");
  ElecAngRes2D[1]->SetTitle("True vs Reco cos(#theta)");
  ElecAngRes2D[1]->GetYaxis()->SetTitle("Reco cos(#theta)");
  ElecAngRes2D[1]->GetXaxis()->SetTitle("True cos(#theta)");
  Cangresallelec->Write();

  TCanvas* Cangressigelec = new TCanvas("Cangressigelec", "Cangressigelec"); // ,1500,1250
  Cangressigelec->cd();
  ElecAngRes2D[0]->Draw("colz");
  ElecAngRes2D[0]->SetStats(0);
  ElecAngRes2D[0]->SetTitle("");
  /*
  //ElecAngRes2D[0]->SetTitle("True vs Reco signal cos(#theta)");
  //ElecAngRes2D[0]->GetYaxis()->SetNdivisions(505);
  ElecAngRes2D[0]->GetYaxis()->SetTitleSize(45);
  ElecAngRes2D[0]->GetYaxis()->SetTitleFont(43);
  ElecAngRes2D[0]->GetYaxis()->SetTitleOffset(1.5);
  ElecAngRes2D[0]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ElecAngRes2D[0]->GetYaxis()->SetLabelSize(38);
  
  ElecAngRes2D[0]->GetXaxis()->SetTitleSize(45); // 15
  ElecAngRes2D[0]->GetXaxis()->SetTitleFont(43);
  ElecAngRes2D[0]->GetXaxis()->SetTitleOffset(1.5);
  ElecAngRes2D[0]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ElecAngRes2D[0]->GetXaxis()->SetLabelSize(38); // 15

  ElecAngRes2D[0]->GetZaxis()->SetTitleSize(45); // 15
  ElecAngRes2D[0]->GetZaxis()->SetTitleFont(43);
  ElecAngRes2D[0]->GetZaxis()->SetTitleOffset(1.12);
  ElecAngRes2D[0]->GetZaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ElecAngRes2D[0]->GetZaxis()->SetLabelSize(38); // 15
  */
  ElecAngRes2D[0]->GetYaxis()->SetTitle("#theta_{reco} [rad]");
  ElecAngRes2D[0]->GetXaxis()->SetTitle("#theta_{true} [rad]");
  ElecAngRes2D[0]->GetZaxis()->SetTitle("Events");
  //latex.DrawLatex(1.40,-0.75,"#theta [rad]");
  //tpt->Draw();
  gPad->RedrawAxis();
  gPad->SetTicks();
  gPad->Update();
  ElecAngRes2D[0]->Write();
  Cangressigelec->Write();

  TCanvas* Cmomresallelec1D = new TCanvas("Cmomresallelec1D", "Cmomresallelec1D");
  ElecMomRes[1]->Draw("");
  ElecMomRes[1]->SetTitle("Electron momentum resolution");
  ElecMomRes[1]->GetYaxis()->SetTitle("Entries");
  ElecMomRes[1]->GetXaxis()->SetTitle("(p_{true}-p_{reco})/p_{true}");
  //tpt->Draw();
  Cmomresallelec1D->Write();

  TCanvas* Cmomressigelec1D = new TCanvas("Cmomressigelec1D", "Cmomressigelec1D");
  ElecMomRes[0]->Draw("");
  ElecMomRes[0]->SetTitle("Signal Electron momentum resolution");
  ElecMomRes[0]->GetYaxis()->SetTitle("Entries");
  ElecMomRes[0]->GetXaxis()->SetTitle("(p_{true}-p_{reco})/p_{true}");
  //tpt->Draw();
  Cmomressigelec1D->Write();

  TCanvas* Cangresallelec1D = new TCanvas("Cangresallelec1D", "Cangresallelec1D");
  ElecAngRes[1]->Draw("");
  ElecAngRes[1]->SetTitle("Electron angular resolution");
  ElecAngRes[1]->GetYaxis()->SetTitle("Entries");
  ElecAngRes[1]->GetXaxis()->SetTitle("(cos(#theta)_{true}-cos(#theta)_{reco})/cos(#theta)_{true}");
  //tpt->Draw();
  Cangresallelec1D->Write();

  TCanvas* Cangressigelec1D = new TCanvas("Cangressigelec1D", "Cangressigelec1D");
  ElecAngRes[0]->Draw("");
  ElecAngRes[0]->SetTitle("Signal Electron angular resolution");
  ElecAngRes[0]->GetYaxis()->SetTitle("Entries");
  ElecAngRes[0]->GetXaxis()->SetTitle("(cos(#theta)_{true}-cos(#theta)_{reco})/cos(#theta)_{true}");
  //Cangressigelec1D->Update();
  //TPaveStats *st = (TPaveStats*)ElecAngRes[0]->FindObject("stats");
  //st->SetOptStat(10);
  //Cangressigelec1D->Modified();
  //tpt->Draw();
  Cangressigelec1D->Write();

  // Signal split into neutrino interactions
  CCSignalInteractions[0]->SetLineColor(intcolour[0] + 40);
  CCSignalInteractions[0]->SetFillColor(intcolour[0] + 40);
  CCSignalInteractions[0]->SetFillStyle(3000 + intcolour[0]);
  CCSignalInteractions[4]->SetLineColor(intcolour[1] + 40);
  CCSignalInteractions[4]->SetFillColor(intcolour[1] + 40);
  CCSignalInteractions[4]->SetFillStyle(3000 + intcolour[1]);
  CCSignalInteractions[3]->SetLineColor(intcolour[2] + 40);
  CCSignalInteractions[3]->SetFillColor(intcolour[2] + 40);
  CCSignalInteractions[3]->SetFillStyle(3000 + intcolour[2]);
  CCSignalInteractions[2]->SetLineColor(intcolour[3] + 40);
  CCSignalInteractions[2]->SetFillColor(intcolour[3] + 40);
  CCSignalInteractions[2]->SetFillStyle(3000 + intcolour[3]);
  CCSignalInteractions[1]->SetLineColor(intcolour[4] + 40);
  CCSignalInteractions[1]->SetFillColor(intcolour[4] + 40);
  CCSignalInteractions[1]->SetFillStyle(3000 + intcolour[4]);

  for(Int_t i=0; i < 5; i++){
    IncludeOverflow(CCSignalInteractions[i]);
    CCSignalInteractions[i]->SetStats(0);
  }

  THStack *hsNuESig = new THStack("","");
  hsNuESig->Add(CCSignalInteractions[1]);
  hsNuESig->Add(CCSignalInteractions[2]);
  hsNuESig->Add(CCSignalInteractions[3]);
  hsNuESig->Add(CCSignalInteractions[4]);
  hsNuESig->Add(CCSignalInteractions[0]);

  Double_t ccqel_nuesig = CCSignalInteractions[0]->Integral();
  Double_t ccres_nuesig = CCSignalInteractions[4]->Integral();
  Double_t ccdis_nuesig = CCSignalInteractions[3]->Integral();
  Double_t cccoh_nuesig = CCSignalInteractions[2]->Integral();
  Double_t ccmec_nuesig = CCSignalInteractions[1]->Integral();
  Double_t ccall_nuesig = ccqel_nuesig + ccres_nuesig + ccdis_nuesig + cccoh_nuesig + ccmec_nuesig;

  TLegend *mylegendNuESig = new TLegend(0.35,0.48,0.85,0.88);
  mylegendNuESig->SetFillColor(0); // white background
  mylegendNuESig->SetBorderSize(0);
  mylegendNuESig->SetTextSize(0.032);
  if(!positive){
    mylegendNuESig->AddEntry(CCSignalInteractions[0]     ,Form("CC-#nu_{e} QEL  %.2f  (%.2f\%)",ccqel_nuesig,100*ccqel_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[4]     ,Form("CC-#nu_{e} RES  %.2f  (%.2f\%)",ccres_nuesig,100*ccres_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[3]     ,Form("CC-#nu_{e} DIS  %.2f  (%.2f\%)",ccdis_nuesig,100*ccdis_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[2]     ,Form("CC-#nu_{e} COH  %.2f  (%.2f\%)",cccoh_nuesig,100*cccoh_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[1]     ,Form("CC-#nu_{e} 2p2h %.2f  (%.2f\%)",ccmec_nuesig,100*ccmec_nuesig/ccall_nuesig)        ,"f");
  }
  else{
    mylegendNuESig->AddEntry(CCSignalInteractions[0]     ,Form("CC-#bar#nu_{e} QEL  %.2f  (%.2f\%)",ccqel_nuesig,100*ccqel_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[4]     ,Form("CC-#bar#nu_{e} RES  %.2f  (%.2f\%)",ccres_nuesig,100*ccres_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[3]     ,Form("CC-#bar#nu_{e} DIS  %.2f  (%.2f\%)",ccdis_nuesig,100*ccdis_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[2]     ,Form("CC-#bar#nu_{e} COH  %.2f  (%.2f\%)",cccoh_nuesig,100*cccoh_nuesig/ccall_nuesig)        ,"f");
    mylegendNuESig->AddEntry(CCSignalInteractions[1]     ,Form("CC-#bar#nu_{e} 2p2h %.2f  (%.2f\%)",ccmec_nuesig,100*ccmec_nuesig/ccall_nuesig)        ,"f");
  }

  TCanvas *cNUEInteractions = new TCanvas("NUEInteractions","NUEInteractions");
  hsNuESig->Draw();
  hsNuESig->GetXaxis()->SetTitle("p [MeV/c]");
  hsNuESig->GetYaxis()->SetTitle("Events / 300 [Mev/c]");
  hsNuESig->GetYaxis()->SetTitleOffset(1.2);
  hsNuESig->SetTitle("FHC CC-#nu_{e}");
  if(isrhc)
    hsNuESig->SetTitle("RHC CC-#nu_{e}");
  if(positive){
    hsNuESig->SetTitle("FHC CC-#bar#nu_{e}");
    if(isrhc)
      hsNuESig->SetTitle("RHC CC-#bar#nu_{e}");
  }

  if(isgenie)
    hsNuESig->SetTitle(Form("GENIE %s", hsNuESig->GetTitle()));
  else
    hsNuESig->SetTitle(Form("NEUT %s", hsNuESig->GetTitle()));

  mylegendNuESig->Draw();
  //tpt->Draw();
  cNUEInteractions->Write();
  // ------------------------------------------------------------------------------
  CCSignalInteractionsAngle[0]->SetLineColor(intcolour[0] + 40);
  CCSignalInteractionsAngle[0]->SetFillColor(intcolour[0] + 40);
  CCSignalInteractionsAngle[0]->SetFillStyle(3000 + intcolour[0]);
  CCSignalInteractionsAngle[4]->SetLineColor(intcolour[1] + 40);
  CCSignalInteractionsAngle[4]->SetFillColor(intcolour[1] + 40);
  CCSignalInteractionsAngle[4]->SetFillStyle(3000 + intcolour[1]);
  CCSignalInteractionsAngle[3]->SetLineColor(intcolour[2] + 40);
  CCSignalInteractionsAngle[3]->SetFillColor(intcolour[2] + 40);
  CCSignalInteractionsAngle[3]->SetFillStyle(3000 + intcolour[2]);
  CCSignalInteractionsAngle[2]->SetLineColor(intcolour[3] + 40);
  CCSignalInteractionsAngle[2]->SetFillColor(intcolour[3] + 40);
  CCSignalInteractionsAngle[2]->SetFillStyle(3000 + intcolour[3]);
  CCSignalInteractionsAngle[1]->SetLineColor(intcolour[4] + 40);
  CCSignalInteractionsAngle[1]->SetFillColor(intcolour[4] + 40);
  CCSignalInteractionsAngle[1]->SetFillStyle(3000 + intcolour[4]);

  for(Int_t i=0; i < 5; i++){
    IncludeOverflow(CCSignalInteractionsAngle[i]);
    IncludeUnderflow(CCSignalInteractionsAngle[i]);
    CCSignalInteractionsAngle[i]->SetStats(0);
  }

  THStack *hsNuESigAngle = new THStack("","");
  hsNuESigAngle->Add(CCSignalInteractionsAngle[1]);
  hsNuESigAngle->Add(CCSignalInteractionsAngle[2]);
  hsNuESigAngle->Add(CCSignalInteractionsAngle[3]);
  hsNuESigAngle->Add(CCSignalInteractionsAngle[4]);
  hsNuESigAngle->Add(CCSignalInteractionsAngle[0]);

  Double_t ccqel_nuesigAngle = CCSignalInteractionsAngle[0]->Integral();
  Double_t ccres_nuesigAngle = CCSignalInteractionsAngle[4]->Integral();
  Double_t ccdis_nuesigAngle = CCSignalInteractionsAngle[3]->Integral();
  Double_t cccoh_nuesigAngle = CCSignalInteractionsAngle[2]->Integral();
  Double_t ccmec_nuesigAngle = CCSignalInteractionsAngle[1]->Integral();
  Double_t ccall_nuesigAngle = ccqel_nuesigAngle + ccres_nuesigAngle + ccdis_nuesigAngle + cccoh_nuesigAngle + ccmec_nuesigAngle;

  TLegend *mylegendNuESigAngle = new TLegend(0.20,0.48,0.55,0.88);
  mylegendNuESigAngle->SetFillColor(0); // white background
  mylegendNuESigAngle->SetBorderSize(0);
  mylegendNuESigAngle->SetTextSize(0.032);
  if(!positive){
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[0]     ,Form("CC-#nu_{e} QEL  %.2f  (%.2f\%)",ccqel_nuesigAngle,100*ccqel_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[4]     ,Form("CC-#nu_{e} RES  %.2f  (%.2f\%)",ccres_nuesigAngle,100*ccres_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[3]     ,Form("CC-#nu_{e} DIS  %.2f  (%.2f\%)",ccdis_nuesigAngle,100*ccdis_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[2]     ,Form("CC-#nu_{e} COH  %.2f  (%.2f\%)",cccoh_nuesigAngle,100*cccoh_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[1]     ,Form("CC-#nu_{e} 2p2h %.2f  (%.2f\%)",ccmec_nuesigAngle,100*ccmec_nuesigAngle/ccall_nuesigAngle)        ,"f");
  }
  else{
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[0]     ,Form("CC-#bar#nu_{e} QEL  %.2f  (%.2f\%)",ccqel_nuesigAngle,100*ccqel_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[4]     ,Form("CC-#bar#nu_{e} RES  %.2f  (%.2f\%)",ccres_nuesigAngle,100*ccres_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[3]     ,Form("CC-#bar#nu_{e} DIS  %.2f  (%.2f\%)",ccdis_nuesigAngle,100*ccdis_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[2]     ,Form("CC-#bar#nu_{e} COH  %.2f  (%.2f\%)",cccoh_nuesigAngle,100*cccoh_nuesigAngle/ccall_nuesigAngle)        ,"f");
    mylegendNuESigAngle->AddEntry(CCSignalInteractionsAngle[1]     ,Form("CC-#bar#nu_{e} 2p2h %.2f  (%.2f\%)",ccmec_nuesigAngle,100*ccmec_nuesigAngle/ccall_nuesigAngle)        ,"f");
  }
  
  TCanvas *cNUEInteractionsAngle = new TCanvas("NUEInteractionsAngle","NUEInteractionsAngle");
  hsNuESigAngle->Draw();
  hsNuESigAngle->GetXaxis()->SetTitle("cos(#theta)");
  hsNuESigAngle->GetYaxis()->SetTitle("Events / 300 [Mev/c]");
  hsNuESigAngle->GetYaxis()->SetTitleOffset(1.2);
  hsNuESigAngle->SetTitle("FHC CC-#nu_{e}");
  if(isrhc)
    hsNuESigAngle->SetTitle("RHC CC-#nu_{e}");
  if(positive){
    hsNuESigAngle->SetTitle("FHC CC-#bar#nu_{e}");
    if(isrhc)
      hsNuESigAngle->SetTitle("RHC CC-#bar#nu_{e}");
  }
  
  if(isgenie)
    hsNuESigAngle->SetTitle(Form("GENIE %s", hsNuESig->GetTitle()));
  else
    hsNuESigAngle->SetTitle(Form("NEUT %s", hsNuESig->GetTitle()));
  
  mylegendNuESigAngle->Draw();
  //tpt->Draw();
  cNUEInteractionsAngle->Write();
  // ------------------------------------------------------------------------------
  // Signal split into parent components
  TCanvas* Cneutrinoparent = new TCanvas("Cneutrinoparent", "Cneutrinoparent");

  CCSignalNeutrinoParent[0]->SetLineColor(intcolour[0]);
  CCSignalNeutrinoParent[0]->SetFillColor(intcolour[0]);
  CCSignalNeutrinoParent[0]->SetFillStyle(3000 + intcolour[0]);
  CCSignalNeutrinoParent[2]->SetLineColor(intcolour[1]);
  CCSignalNeutrinoParent[2]->SetFillColor(intcolour[1]);
  CCSignalNeutrinoParent[2]->SetFillStyle(3000 + intcolour[1]);
  CCSignalNeutrinoParent[3]->SetLineColor(48);
  CCSignalNeutrinoParent[3]->SetFillColor(48);
  CCSignalNeutrinoParent[3]->SetFillStyle(3048);
  //CCSignalNeutrinoParent[1]->SetLineColor(intcolour[5]);
  //CCSignalNeutrinoParent[1]->SetFillColor(intcolour[5]);
  //CCSignalNeutrinoParent[1]->SetFillStyle(3000 + intcolour[5]);

  CCSignalNeutrinoParent[4]->SetLineColor(intcolour[2]);
  CCSignalNeutrinoParent[4]->SetFillColor(intcolour[2]);
  CCSignalNeutrinoParent[4]->SetFillStyle(3000 + intcolour[2]);
  CCSignalNeutrinoParent[5]->SetLineColor(intcolour[3]);
  CCSignalNeutrinoParent[5]->SetFillColor(intcolour[3]);
  CCSignalNeutrinoParent[5]->SetFillStyle(3000 + intcolour[3]);
  CCSignalNeutrinoParent[7]->SetLineColor(intcolour[4]);
  CCSignalNeutrinoParent[7]->SetFillColor(intcolour[4]);
  CCSignalNeutrinoParent[7]->SetFillStyle(3000 + intcolour[4]);
  CCSignalNeutrinoParent[6]->SetLineColor(intcolour[6]);
  CCSignalNeutrinoParent[6]->SetFillColor(intcolour[6]);
  CCSignalNeutrinoParent[6]->SetFillStyle(3000 + intcolour[6]);

  for(Int_t i=0; i < 9; i++){
    IncludeOverflow(CCSignalNeutrinoParent[i]);
    CCSignalNeutrinoParent[i]->SetStats(0);
  }

  CCSignalNeutrinoParent[2]->Add(CCSignalNeutrinoParent[1]);

  THStack *hsNuParent = new THStack("","");
  hsNuParent->Add(CCSignalNeutrinoParent[7],"sames");
  if(positive)
    hsNuParent->Add(CCSignalNeutrinoParent[6],"sames");
  hsNuParent->Add(CCSignalNeutrinoParent[5],"sames");
  hsNuParent->Add(CCSignalNeutrinoParent[4],"sames");
  hsNuParent->Add(CCSignalNeutrinoParent[3],"sames");
  hsNuParent->Add(CCSignalNeutrinoParent[2],"sames");
  //hsNuParent->Add(CCSignalNeutrinoParent[1],"sames");
  hsNuParent->Add(CCSignalNeutrinoParent[0],"sames");

  Double_t parent_dataentries = CCSignalNeutrinoParent[8]->Integral();
  Double_t parent_muonentries = CCSignalNeutrinoParent[0]->Integral();
  Double_t parent_kaonentries = CCSignalNeutrinoParent[2]->Integral();
  Double_t parent_otherentries = CCSignalNeutrinoParent[3]->Integral();
  Double_t parent_gammaentries = CCSignalNeutrinoParent[4]->Integral();
  Double_t parent_muonbkgentries = CCSignalNeutrinoParent[5]->Integral();
  Double_t parent_protonentries = CCSignalNeutrinoParent[6]->Integral();
  Double_t parent_otherbkgentries = CCSignalNeutrinoParent[7]->Integral();
  Double_t parent_allmcentries = parent_muonentries + parent_kaonentries + parent_otherentries + parent_gammaentries + parent_muonbkgentries + parent_protonentries + parent_otherbkgentries;

  TLegend *mylegendNuParent = new TLegend(0.35,0.48,0.85,0.88);
  mylegendNuParent->SetFillColor(0);
  mylegendNuParent->SetBorderSize(0);
  mylegendNuParent->SetTextSize(0.032);

  if(!isrhc){
    mylegendNuParent->AddEntry((TObject*)0    ,Form("T2K FHC %.2f #times 10^{20} POT", totaldatapot*1e-20), "" );
  }
  else{
    mylegendNuParent->AddEntry((TObject*)0    ,Form("T2K RHC %.2f #times 10^{20} POT", totaldatapot*1e-20), "" );
  }
  
  mylegendNuParent->AddEntry((TObject*)0    ,"", "" );
  
  if(positive){
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[8]    ,Form("Data                       %i", (Int_t)parent_dataentries) );
    mylegendNuParent->AddEntry((TObject*)0, Form("NEUT 5.3.2 Total   %.2f",parent_allmcentries), "");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[0]      ,Form("parent #mu                 %.2f    (%.2f\%)", parent_muonentries,100*parent_muonentries/parent_allmcentries) ,"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[2]   ,Form("parent #Kappa                %.2f  (%.2f\%)", parent_kaonentries,100*parent_kaonentries/parent_allmcentries),"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[3]   ,Form("parent Other           %.2f     (%.2f\%)",parent_otherentries,100*parent_otherentries/parent_allmcentries)    ,"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[4]  ,Form("#gamma background         %.2f  (%.2f\%)",   parent_gammaentries,100*parent_gammaentries/parent_allmcentries)      ,"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[5], Form("#mu background         %.2f    (%.2f\%)", parent_muonbkgentries, 100*parent_muonbkgentries/parent_allmcentries  ),"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[6],Form("Proton background  %.2f   (%.2f\%)", parent_protonentries, 100*parent_protonentries/parent_allmcentries  ),"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[7],Form("Other background  %.2f    (%.2f\%)", parent_otherbkgentries,100*parent_otherbkgentries/parent_allmcentries)    ,"f");
  }
  else{
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[8]    ,Form("Data                       %i", (Int_t)parent_dataentries) );
    mylegendNuParent->AddEntry((TObject*)0, Form("NEUT 5.3.2 Total   %.2f",parent_allmcentries), "");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[0]      ,Form("parent #mu                 %.2f    (%.2f\%)", parent_muonentries,100*parent_muonentries/parent_allmcentries) ,"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[2]   ,Form("parent #Kappa                %.2f  (%.2f\%)", parent_kaonentries,100*parent_kaonentries/parent_allmcentries),"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[3]   ,Form("parent Other           %.2f     (%.2f\%)",parent_otherentries,100*parent_otherentries/parent_allmcentries)    ,"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[4]  ,Form("#gamma background         %.2f  (%.2f\%)",   parent_gammaentries,100*parent_gammaentries/parent_allmcentries)      ,"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[5], Form("#mu background         %.2f    (%.2f\%)", parent_muonbkgentries, 100*parent_muonbkgentries/parent_allmcentries  ),"f");
    mylegendNuParent->AddEntry(CCSignalNeutrinoParent[7],Form("Other background  %.2f    (%.2f\%)", parent_otherbkgentries,100*parent_otherbkgentries/parent_allmcentries)    ,"f");
  }

  if(!addratio){
    hsNuParent->Draw("");
    hsNuParent->SetTitle("FHC CC-#nu_{e} Inclusive");
    if(positive)
      hsNuParent->SetTitle("FHC CC-#bar#nu_{e} Inclusive");
    if(isrhc){
      hsNuParent->SetTitle("RHC CC-#nu_{e} Inclusive");
      if(positive)
	hsNuParent->SetTitle("RHC CC-#bar#nu_{e} Inclusive");
    }

    hsNuParent->GetXaxis()->SetTitle("p_{e} [MeV/c]");
    hsNuParent->GetYaxis()->SetTitle("Events / 300 [MeV/c]");
    hsNuParent->GetYaxis()->SetTitleOffset(1.2);
    CCSignalNeutrinoParent[8]->Draw("samese");
    //CCSignalNeutrinoParent[8]->SetMarkerStyle(25);
    //CCSignalNeutrinoParent[8]->SetMarkerColor(6);
    //CCSignalNeutrinoParent[8]->SetLineColor(6);
    //CCSignalNeutrinoParent[8]->Draw("samesp HIST");
    mylegendNuParent->Draw();
  }
  else{
    // Set text size for external naming - for example T2K Preliminary
    //tpt->SetTextSize(0.15);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.31, 1, 1.0);
    pad1->SetBottomMargin(0.015); // Upper and lower plot are joined
    //pad1->SetGridx();         // Vertical grid
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pa
    
    hsNuParent->Draw("");
    hsNuParent->SetTitle("FHC CC-#nu_{e} Inclusive");
    if(positive)
      hsNuParent->SetTitle("FHC CC-#bar#nu_{e} Inclusive");
    if(isrhc){
      hsNuParent->SetTitle("RHC CC-#nu_{e} Inclusive");
      if(positive)
        hsNuParent->SetTitle("RHC CC-#bar#nu_{e} Inclusive");
    }

    hsNuParent->GetXaxis()->SetTitle("p_{e} [MeV/c]");
    hsNuParent->GetYaxis()->SetTitle("Events / 300 [MeV/c]");
    hsNuParent->GetYaxis()->SetTitleOffset(1.2);
    CCSignalNeutrinoParent[8]->Draw("samese");
    mylegendNuParent->Draw();

    Cneutrinoparent->cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.25);
    //pad2->SetGridx(); // vertical grid
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    
    TH1D *dataratio3 = (TH1D*)CCSignalNeutrinoParent[8]->Clone(Form("%s_dataratio3",CCSignalNeutrinoParent[8]->GetName()));
    TH1D *mcratio    = (TH1D*)CCSignalNeutrinoParent[0]->Clone(Form("%s_mcratio",CCSignalNeutrinoParent[0]->GetName()));
    for(Int_t i=2; i < 8; i++){
      mcratio->Add(CCSignalNeutrinoParent[i]);
    }
    
    dataratio3->SetMinimum(0.0);
    dataratio3->SetMaximum(2.95); // .. range
    mcratio->Sumw2();
    dataratio3->Sumw2();
    dataratio3->SetStats(0);
    dataratio3->Divide(mcratio);
    dataratio3->SetMarkerStyle(21);
    dataratio3->Draw("ep");
    dataratio3->SetTitle("");
    
    // Y axis ratio plot settings
    dataratio3->GetYaxis()->SetTitle("Data / MC");
    dataratio3->GetYaxis()->SetNdivisions(505);
    dataratio3->GetYaxis()->SetTitleSize(12);
    dataratio3->GetYaxis()->SetTitleFont(43);
    dataratio3->GetYaxis()->SetTitleOffset(1.25);
    dataratio3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    dataratio3->GetYaxis()->SetLabelSize(12);
    
    // X axis ratio plot settings
    dataratio3->GetXaxis()->SetTitle("p [MeV/c]");
    dataratio3->GetXaxis()->SetTitleSize(15);
    dataratio3->GetXaxis()->SetTitleFont(43);
    dataratio3->GetXaxis()->SetTitleOffset(4.0);
    dataratio3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    dataratio3->GetXaxis()->SetLabelSize(15);
    
    TLine *line = new TLine(0,1,5400,1);
    line->SetLineColor(kRed);
    
    //dataratio->Draw("ep");
    //dataratio->GetXaxis()->SetTitle("p [MeV/c]");
    //dataratio->GetYaxis()->SetTitle("Data/MC");
    //dataratio->SetTitle("Data/MC");
    line->Draw();
  }
  //tpt->Draw();
  Cneutrinoparent->Write();

  // Set text size for external naming - for example T2K Preliminary
  //tpt->SetTextSize(0.04);

  // Muon and proton backgrounds
  TCanvas* Cmuonbkg = new TCanvas("Cmuonbkg", "Cmuonbkg");
  MuonBkgInteractions[5]->SetLineColor(intcolour[0] + 40);
  MuonBkgInteractions[5]->SetFillColor(intcolour[0] + 40);
  MuonBkgInteractions[5]->SetFillStyle(3000 + intcolour[0]);
  MuonBkgInteractions[4]->SetLineColor(intcolour[1] + 40);
  MuonBkgInteractions[4]->SetFillColor(intcolour[1] + 40);
  MuonBkgInteractions[4]->SetFillStyle(3000 + intcolour[1]);
  MuonBkgInteractions[3]->SetLineColor(intcolour[2] + 40);
  MuonBkgInteractions[3]->SetFillColor(intcolour[2] + 40);
  MuonBkgInteractions[3]->SetFillStyle(3000 + intcolour[2]);
  MuonBkgInteractions[2]->SetLineColor(intcolour[4] + 40);
  MuonBkgInteractions[2]->SetFillColor(intcolour[4] + 40);
  MuonBkgInteractions[2]->SetFillStyle(3000 + intcolour[4]);
  MuonBkgInteractions[1]->SetLineColor(intcolour[5] + 40);
  MuonBkgInteractions[1]->SetFillColor(intcolour[5] + 40);
  MuonBkgInteractions[1]->SetFillStyle(3000 + intcolour[5]);
  MuonBkgInteractions[0]->SetLineColor(intcolour[6] + 40);
  MuonBkgInteractions[0]->SetFillColor(intcolour[6] + 40);
  MuonBkgInteractions[0]->SetFillStyle(3000 + intcolour[6]);

  for(Int_t i=0; i < 6; i++){
    IncludeOverflow(MuonBkgInteractions[i]);
    MuonBkgInteractions[i]->SetStats(0);
  }

  THStack *hsmuonbkg = new THStack("","");
  hsmuonbkg->Add(MuonBkgInteractions[5]);
  hsmuonbkg->Add(MuonBkgInteractions[4]);
  hsmuonbkg->Add(MuonBkgInteractions[3]);
  hsmuonbkg->Add(MuonBkgInteractions[2]);
  hsmuonbkg->Add(MuonBkgInteractions[1]);
  hsmuonbkg->Add(MuonBkgInteractions[0]);

  TLegend *mylegendmuonbkg = new TLegend(0.53,0.48,0.83,0.88);
  mylegendmuonbkg->SetFillColor(0);
  mylegendmuonbkg->SetBorderSize(0);
  mylegendmuonbkg->SetTextSize(0.032);
  mylegendmuonbkg->AddEntry(MuonBkgInteractions[0]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-QEL/2p2h"   ,"f");
  mylegendmuonbkg->AddEntry(MuonBkgInteractions[1]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-RES"        ,"f");
  mylegendmuonbkg->AddEntry(MuonBkgInteractions[2]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-COH"        ,"f");
  mylegendmuonbkg->AddEntry(MuonBkgInteractions[3]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-DIS"        ,"f");
  mylegendmuonbkg->AddEntry(MuonBkgInteractions[4]     ,"#nu_{#mu}/#bar#nu_{#mu} Other"         ,"f");
  mylegendmuonbkg->AddEntry(MuonBkgInteractions[5]     ,"OOFV"                                  ,"f");

  hsmuonbkg->Draw();
  hsmuonbkg->GetXaxis()->SetTitle("p_{e} [MeV/c]");
  hsmuonbkg->GetYaxis()->SetTitle("Events / 300 [MeV/c]");
  hsmuonbkg->GetYaxis()->SetTitleOffset(1.2);
  hsmuonbkg->SetTitle("FHC CC-#nu_{e} muon background");
  if(isrhc)
    hsmuonbkg->SetTitle("RHC CC-#nu_{e} muon background");
  if(positive){
    hsmuonbkg->SetTitle("FHC CC-#bar#nu_{e} muon background");
    if(isrhc)
      hsmuonbkg->SetTitle("RHC CC-#bar#nu_{e} muon background");
  }

  if(isgenie)
    hsmuonbkg->SetTitle(Form("GENIE %s", hsmuonbkg->GetTitle()));
  else
    hsmuonbkg->SetTitle(Form("NEUT %s", hsmuonbkg->GetTitle()));

  mylegendmuonbkg->Draw();
  //tpt->Draw();
  Cmuonbkg->Write();
  // ---------------------------------------------------------------------------------------------------
  TCanvas* CmuonbkgAngle = new TCanvas("CmuonbkgAngle", "CmuonbkgAngle");
  MuonBkgInteractionsAngle[5]->SetLineColor(intcolour[0] + 40);
  MuonBkgInteractionsAngle[5]->SetFillColor(intcolour[0] + 40);
  MuonBkgInteractionsAngle[5]->SetFillStyle(3000 + intcolour[0]);
  MuonBkgInteractionsAngle[4]->SetLineColor(intcolour[1] + 40);
  MuonBkgInteractionsAngle[4]->SetFillColor(intcolour[1] + 40);
  MuonBkgInteractionsAngle[4]->SetFillStyle(3000 + intcolour[1]);
  MuonBkgInteractionsAngle[3]->SetLineColor(intcolour[2] + 40);
  MuonBkgInteractionsAngle[3]->SetFillColor(intcolour[2] + 40);
  MuonBkgInteractionsAngle[3]->SetFillStyle(3000 + intcolour[2]);
  MuonBkgInteractionsAngle[2]->SetLineColor(intcolour[4] + 40);
  MuonBkgInteractionsAngle[2]->SetFillColor(intcolour[4] + 40);
  MuonBkgInteractionsAngle[2]->SetFillStyle(3000 + intcolour[4]);
  MuonBkgInteractionsAngle[1]->SetLineColor(intcolour[5] + 40);
  MuonBkgInteractionsAngle[1]->SetFillColor(intcolour[5] + 40);
  MuonBkgInteractionsAngle[1]->SetFillStyle(3000 + intcolour[5]);
  MuonBkgInteractionsAngle[0]->SetLineColor(intcolour[6] + 40);
  MuonBkgInteractionsAngle[0]->SetFillColor(intcolour[6] + 40);
  MuonBkgInteractionsAngle[0]->SetFillStyle(3000 + intcolour[6]);

  for(Int_t i=0; i < 6; i++){
    IncludeOverflow(MuonBkgInteractionsAngle[i]);
    IncludeUnderflow(MuonBkgInteractionsAngle[i]);
    MuonBkgInteractionsAngle[i]->SetStats(0);
  }

  THStack *hsmuonbkgAngle = new THStack("","");
  hsmuonbkgAngle->Add(MuonBkgInteractionsAngle[5]);
  hsmuonbkgAngle->Add(MuonBkgInteractionsAngle[4]);
  hsmuonbkgAngle->Add(MuonBkgInteractionsAngle[3]);
  hsmuonbkgAngle->Add(MuonBkgInteractionsAngle[2]);
  hsmuonbkgAngle->Add(MuonBkgInteractionsAngle[1]);
  hsmuonbkgAngle->Add(MuonBkgInteractionsAngle[0]);

  TLegend *mylegendmuonbkgAngle = new TLegend(0.23,0.48,0.53,0.88);
  mylegendmuonbkgAngle->SetFillColor(0);
  mylegendmuonbkgAngle->SetBorderSize(0);
  mylegendmuonbkgAngle->SetTextSize(0.032);
  mylegendmuonbkgAngle->AddEntry(MuonBkgInteractionsAngle[0]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-QEL/2p2h"   ,"f");
  mylegendmuonbkgAngle->AddEntry(MuonBkgInteractionsAngle[1]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-RES"        ,"f");
  mylegendmuonbkgAngle->AddEntry(MuonBkgInteractionsAngle[2]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-COH"        ,"f");
  mylegendmuonbkgAngle->AddEntry(MuonBkgInteractionsAngle[3]     ,"#nu_{#mu}/#bar#nu_{#mu} CC-DIS"        ,"f");
  mylegendmuonbkgAngle->AddEntry(MuonBkgInteractionsAngle[4]     ,"#nu_{#mu}/#bar#nu_{#mu} Other"         ,"f");
  mylegendmuonbkgAngle->AddEntry(MuonBkgInteractionsAngle[5]     ,"OOFV"                                  ,"f");

  hsmuonbkgAngle->Draw();
  hsmuonbkgAngle->GetXaxis()->SetTitle("Cos(#theta)");
  hsmuonbkgAngle->GetYaxis()->SetTitle("Events / 0.05");
  hsmuonbkgAngle->GetYaxis()->SetTitleOffset(1.2);
  hsmuonbkgAngle->SetTitle("FHC CC-#nu_{e} muon background");
  if(isrhc)
    hsmuonbkgAngle->SetTitle("RHC CC-#nu_{e} muon background");
  if(positive){
    hsmuonbkgAngle->SetTitle("FHC CC-#bar#nu_{e} muon background");
    if(isrhc)
      hsmuonbkgAngle->SetTitle("RHC CC-#bar#nu_{e} muon background");
  }

  if(isgenie)
    hsmuonbkgAngle->SetTitle(Form("GENIE %s", hsmuonbkgAngle->GetTitle()));
  else
    hsmuonbkgAngle->SetTitle(Form("NEUT %s", hsmuonbkgAngle->GetTitle()));

  mylegendmuonbkgAngle->Draw();
  //tpt->Draw();
  CmuonbkgAngle->Write();
  // ---------------------------------------------------------------------------------------------------
  TCanvas* Cprotonbkg = new TCanvas("Cprotonbkg", "Cprotonbkg");
  ProtonBkgInteractions[7]->SetLineColor(intcolour[0] + 40);
  ProtonBkgInteractions[7]->SetFillColor(intcolour[0] + 40);
  ProtonBkgInteractions[7]->SetFillStyle(3000 + intcolour[0]);
  ProtonBkgInteractions[6]->SetLineColor(intcolour[1] + 40);
  ProtonBkgInteractions[6]->SetFillColor(intcolour[1] + 40);
  ProtonBkgInteractions[6]->SetFillStyle(3000 + intcolour[1]);
  ProtonBkgInteractions[5]->SetLineColor(intcolour[2] + 40);
  ProtonBkgInteractions[5]->SetFillColor(intcolour[2] + 40);
  ProtonBkgInteractions[5]->SetFillStyle(3000 + intcolour[2]);
  ProtonBkgInteractions[4]->SetLineColor(intcolour[3] + 40);
  ProtonBkgInteractions[4]->SetFillColor(intcolour[3] + 40);
  ProtonBkgInteractions[4]->SetFillStyle(3000 + intcolour[3]);
  ProtonBkgInteractions[3]->SetLineColor(intcolour[4] + 40);
  ProtonBkgInteractions[3]->SetFillColor(intcolour[4] + 40);
  ProtonBkgInteractions[3]->SetFillStyle(3000 + intcolour[4]);
  ProtonBkgInteractions[2]->SetLineColor(intcolour[5] + 40);
  ProtonBkgInteractions[2]->SetFillColor(intcolour[5] + 40);
  ProtonBkgInteractions[2]->SetFillStyle(3000 + intcolour[5]);
  ProtonBkgInteractions[1]->SetLineColor(intcolour[6] + 40);
  ProtonBkgInteractions[1]->SetFillColor(intcolour[6] + 40);
  ProtonBkgInteractions[1]->SetFillStyle(3000 + intcolour[6]);
  ProtonBkgInteractions[0]->SetLineColor(intcolour[7] + 40);
  ProtonBkgInteractions[0]->SetFillColor(intcolour[7] + 40);
  ProtonBkgInteractions[0]->SetFillStyle(3000 + intcolour[7]);

  for(Int_t i=0; i < 8; i++){
    IncludeOverflow(ProtonBkgInteractions[i]);
    ProtonBkgInteractions[i]->SetStats(0);
  }

  THStack *hsprotbkg = new THStack("","");
  hsprotbkg->Add(ProtonBkgInteractions[7]);
  hsprotbkg->Add(ProtonBkgInteractions[6]);
  hsprotbkg->Add(ProtonBkgInteractions[5]);
  hsprotbkg->Add(ProtonBkgInteractions[4]);
  hsprotbkg->Add(ProtonBkgInteractions[3]);
  hsprotbkg->Add(ProtonBkgInteractions[2]);
  hsprotbkg->Add(ProtonBkgInteractions[1]);
  hsprotbkg->Add(ProtonBkgInteractions[0]);

  TLegend *mylegendprotbkg = new TLegend(0.53,0.48,0.83,0.88);
  mylegendprotbkg->SetFillColor(0);
  mylegendprotbkg->SetBorderSize(0);
  mylegendprotbkg->SetTextSize(0.032);
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[0]     ,"CC-QEL/2p2h"   ,"f");
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[1]     ,"CC-RES"        ,"f");
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[2]     ,"CC-DIS"        ,"f");
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[3]     ,"NC-QEL"        ,"f");
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[4]     ,"NC-RES"        ,"f");
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[5]     ,"NC-DIS"        ,"f");
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[6]     ,"OOFV"          ,"f");
  mylegendprotbkg->AddEntry(ProtonBkgInteractions[7]     ,"Out of FGD"    ,"f");

  hsprotbkg->Draw();
  hsprotbkg->GetXaxis()->SetTitle("p_{e} [MeV/c]");
  hsprotbkg->GetYaxis()->SetTitle("Events / 300 [Mev/c]");
  hsprotbkg->GetYaxis()->SetTitleOffset(1.2);
  hsprotbkg->SetTitle("FHC CC-#nu_{e} proton background");
  if(isrhc)
    hsprotbkg->SetTitle("RHC CC-#nu_{e} proton background");
  if(positive){
    hsprotbkg->SetTitle("FHC CC-#bar#nu_{e} proton background");
    if(isrhc)
      hsprotbkg->SetTitle("RHC CC-#bar#nu_{e} proton background");
  }

  if(isgenie)
    hsprotbkg->SetTitle(Form("GENIE %s", hsprotbkg->GetTitle()));
  else
    hsprotbkg->SetTitle(Form("NEUT %s", hsprotbkg->GetTitle()));

  mylegendprotbkg->Draw();
  //tpt->Draw();
  Cprotonbkg->Write();
  // ---------------------------------------------------------------------------------------------------
  TCanvas* CprotonbkgAngle = new TCanvas("CprotonbkgAngle", "CprotonbkgAngle");
  ProtonBkgInteractionsAngle[7]->SetLineColor(intcolour[0] + 40);
  ProtonBkgInteractionsAngle[7]->SetFillColor(intcolour[0] + 40);
  ProtonBkgInteractionsAngle[7]->SetFillStyle(3000 + intcolour[0]);
  ProtonBkgInteractionsAngle[6]->SetLineColor(intcolour[1] + 40);
  ProtonBkgInteractionsAngle[6]->SetFillColor(intcolour[1] + 40);
  ProtonBkgInteractionsAngle[6]->SetFillStyle(3000 + intcolour[1]);
  ProtonBkgInteractionsAngle[5]->SetLineColor(intcolour[2] + 40);
  ProtonBkgInteractionsAngle[5]->SetFillColor(intcolour[2] + 40);
  ProtonBkgInteractionsAngle[5]->SetFillStyle(3000 + intcolour[2]);
  ProtonBkgInteractionsAngle[4]->SetLineColor(intcolour[3] + 40);
  ProtonBkgInteractionsAngle[4]->SetFillColor(intcolour[3] + 40);
  ProtonBkgInteractionsAngle[4]->SetFillStyle(3000 + intcolour[3]);
  ProtonBkgInteractionsAngle[3]->SetLineColor(intcolour[4] + 40);
  ProtonBkgInteractionsAngle[3]->SetFillColor(intcolour[4] + 40);
  ProtonBkgInteractionsAngle[3]->SetFillStyle(3000 + intcolour[4]);
  ProtonBkgInteractionsAngle[2]->SetLineColor(intcolour[5] + 40);
  ProtonBkgInteractionsAngle[2]->SetFillColor(intcolour[5] + 40);
  ProtonBkgInteractionsAngle[2]->SetFillStyle(3000 + intcolour[5]);
  ProtonBkgInteractionsAngle[1]->SetLineColor(intcolour[6] + 40);
  ProtonBkgInteractionsAngle[1]->SetFillColor(intcolour[6] + 40);
  ProtonBkgInteractionsAngle[1]->SetFillStyle(3000 + intcolour[6]);
  ProtonBkgInteractionsAngle[0]->SetLineColor(intcolour[7] + 40);
  ProtonBkgInteractionsAngle[0]->SetFillColor(intcolour[7] + 40);
  ProtonBkgInteractionsAngle[0]->SetFillStyle(3000 + intcolour[7]);

  for(Int_t i=0; i < 8; i++){
    IncludeOverflow(ProtonBkgInteractionsAngle[i]);
    IncludeUnderflow(ProtonBkgInteractionsAngle[i]);
    ProtonBkgInteractionsAngle[i]->SetStats(0);
  }

  THStack *hsprotbkgAngle = new THStack("","");
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[7]);
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[6]);
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[5]);
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[4]);
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[3]);
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[2]);
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[1]);
  hsprotbkgAngle->Add(ProtonBkgInteractionsAngle[0]);

  TLegend *mylegendprotbkgAngle = new TLegend(0.23,0.48,0.53,0.88);
  mylegendprotbkgAngle->SetFillColor(0);
  mylegendprotbkgAngle->SetBorderSize(0);
  mylegendprotbkgAngle->SetTextSize(0.032);
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[0]     ,"CC-QEL/2p2h"   ,"f");
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[1]     ,"CC-RES"        ,"f");
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[2]     ,"CC-DIS"        ,"f");
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[3]     ,"NC-QEL"        ,"f");
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[4]     ,"NC-RES"        ,"f");
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[5]     ,"NC-DIS"        ,"f");
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[6]     ,"OOFV"          ,"f");
  mylegendprotbkgAngle->AddEntry(ProtonBkgInteractionsAngle[7]     ,"Out of FGD"    ,"f");

  hsprotbkgAngle->Draw();
  hsprotbkgAngle->GetXaxis()->SetTitle("Cos(#theta)");
  hsprotbkgAngle->GetYaxis()->SetTitle("Events / 0.05");
  hsprotbkgAngle->GetYaxis()->SetTitleOffset(1.2);
  hsprotbkgAngle->SetTitle("FHC CC-#nu_{e} proton background");
  if(isrhc)
    hsprotbkgAngle->SetTitle("RHC CC-#nu_{e} proton background");
  if(positive){
    hsprotbkgAngle->SetTitle("FHC CC-#bar#nu_{e} proton background");
    if(isrhc)
      hsprotbkgAngle->SetTitle("RHC CC-#bar#nu_{e} proton background");
  }

  if(isgenie)
    hsprotbkgAngle->SetTitle(Form("GENIE %s", hsprotbkgAngle->GetTitle()));
  else
    hsprotbkgAngle->SetTitle(Form("NEUT %s", hsprotbkgAngle->GetTitle()));

  mylegendprotbkgAngle->Draw();
  //tpt->Draw();
  CprotonbkgAngle->Write();
  // ---------------------------------------------------------------------------------------------------
  // Other bkg
  TCanvas *cOtherbkg = new TCanvas("cOtherbkg","cOtherbkg");
  OtherBkgBreakdown[0]->SetLineColor(intcolour[0] + 40);
  OtherBkgBreakdown[0]->SetFillColor(intcolour[0] + 40);
  OtherBkgBreakdown[0]->SetFillStyle(3000 + intcolour[0]);
  OtherBkgBreakdown[1]->SetLineColor(intcolour[1] + 40);
  OtherBkgBreakdown[1]->SetFillColor(intcolour[1] + 40);
  OtherBkgBreakdown[1]->SetFillStyle(3000 + intcolour[1]);
  OtherBkgBreakdown[3]->SetLineColor(intcolour[2] + 40);
  OtherBkgBreakdown[3]->SetFillColor(intcolour[2] + 40);
  OtherBkgBreakdown[3]->SetFillStyle(3000 + intcolour[2]);
  OtherBkgBreakdown[4]->SetLineColor(intcolour[3] + 40);
  OtherBkgBreakdown[4]->SetFillColor(intcolour[3] + 40);
  OtherBkgBreakdown[4]->SetFillStyle(3000 + intcolour[3]);
  OtherBkgBreakdown[6]->SetLineColor(intcolour[4] + 40);
  OtherBkgBreakdown[6]->SetFillColor(intcolour[4] + 40);
  OtherBkgBreakdown[6]->SetFillStyle(3000 + intcolour[4]);
  OtherBkgBreakdown[5]->SetLineColor(intcolour[5] + 40);
  OtherBkgBreakdown[5]->SetFillColor(intcolour[5] + 40);
  OtherBkgBreakdown[5]->SetFillStyle(3000 + intcolour[5]);
  OtherBkgBreakdown[2]->SetLineColor(1);
  OtherBkgBreakdown[2]->SetFillColor(1);
  OtherBkgBreakdown[2]->SetFillStyle(3024);
  OtherBkgBreakdown[7]->SetLineColor(intcolour[6] + 40);
  OtherBkgBreakdown[7]->SetFillColor(intcolour[6] + 40);
  OtherBkgBreakdown[7]->SetFillStyle(3000 + intcolour[6]);

  for(Int_t i=0; i < 8; i++){
    IncludeOverflow(OtherBkgBreakdown[i]);
    OtherBkgBreakdown[i]->SetStats(0);
  }

  THStack *hsOtherbkg = new THStack("","");
  hsOtherbkg->Add(OtherBkgBreakdown[7]);
  if(!positive)
    hsOtherbkg->Add(OtherBkgBreakdown[2]);
  hsOtherbkg->Add(OtherBkgBreakdown[5]);
  hsOtherbkg->Add(OtherBkgBreakdown[6]);
  hsOtherbkg->Add(OtherBkgBreakdown[4]);
  hsOtherbkg->Add(OtherBkgBreakdown[3]);
  hsOtherbkg->Add(OtherBkgBreakdown[1]);
  hsOtherbkg->Add(OtherBkgBreakdown[0]);

  Double_t otherbkg_pionentries = OtherBkgBreakdown[0]->Integral();
  Double_t otherbkg_protentries = OtherBkgBreakdown[1]->Integral();
  Double_t otherbkg_epi0entries = OtherBkgBreakdown[3]->Integral();
  Double_t otherbkg_emupentries = OtherBkgBreakdown[4]->Integral();
  Double_t otherbkg_egamentries = OtherBkgBreakdown[6]->Integral();
  Double_t otherbkg_enueentries = OtherBkgBreakdown[5]->Integral();
  Double_t otherbkg_sandentries = OtherBkgBreakdown[2]->Integral();
  Double_t otherbkg_otheentries = OtherBkgBreakdown[7]->Integral();
  Double_t otherbkg_allentries  = otherbkg_pionentries + otherbkg_protentries + otherbkg_epi0entries + otherbkg_emupentries + otherbkg_egamentries + otherbkg_enueentries + otherbkg_sandentries + otherbkg_otheentries;

  TLegend *mylegendOtherbkg = new TLegend(0.43,0.48,0.83,0.88);
  mylegendOtherbkg->SetFillColor(0);
  mylegendOtherbkg->SetBorderSize(0);
  mylegendOtherbkg->SetTextSize(0.032);
  mylegendOtherbkg->AddEntry(OtherBkgBreakdown[0]     ,Form("Pions                    %.2f (%.2f\%)",otherbkg_pionentries,100*otherbkg_pionentries/otherbkg_allentries              ),"f");
  if(!positive)
    mylegendOtherbkg->AddEntry(OtherBkgBreakdown[1]     ,Form("Protons                 %.2f (%.2f\%)",otherbkg_protentries,100*otherbkg_protentries/otherbkg_allentries              ),"f");
  mylegendOtherbkg->AddEntry(OtherBkgBreakdown[3]     ,Form("e- from #pi^{0}             %.2f (%.2f\%)",otherbkg_epi0entries,100*otherbkg_epi0entries/otherbkg_allentries              ),"f");
  mylegendOtherbkg->AddEntry(OtherBkgBreakdown[4]     ,Form("e- from #mu/#pi           %.2f (%.2f\%)",otherbkg_emupentries,100*otherbkg_emupentries/otherbkg_allentries              ),"f");
  mylegendOtherbkg->AddEntry(OtherBkgBreakdown[6]     ,Form("e- from OOFV #gamma   %.2f (%.2f\%)",otherbkg_egamentries,100*otherbkg_egamentries/otherbkg_allentries              ),"f");
  mylegendOtherbkg->AddEntry(OtherBkgBreakdown[5]     ,Form("CC-#nu_{e}/#bar#nu_{e}              %.2f (%.2f\%)",otherbkg_enueentries,100*otherbkg_enueentries/otherbkg_allentries       ),"f");
  mylegendOtherbkg->AddEntry(OtherBkgBreakdown[2]     ,Form("Sand                    %.2f (%.2f\%)",otherbkg_sandentries,100*otherbkg_sandentries/otherbkg_allentries              ),"f");
  mylegendOtherbkg->AddEntry(OtherBkgBreakdown[7]     ,Form("Other                    %.2f (%.2f\%)",otherbkg_otheentries,100*otherbkg_otheentries/otherbkg_allentries              ),"f");

  hsOtherbkg->Draw();
  hsOtherbkg->GetXaxis()->SetTitle("p_{e} [MeV/c]");
  hsOtherbkg->GetYaxis()->SetTitle("Events / 300 [MeV/c]");
  hsOtherbkg->GetYaxis()->SetTitleOffset(1.2);
  hsOtherbkg->SetTitle("FHC CC-#nu_{e} other background");
  if(isrhc)
    hsOtherbkg->SetTitle("RHC CC-#nu_{e} other background");
  if(positive){
    hsOtherbkg->SetTitle("FHC CC-#bar#nu_{e} other background");
    if(isrhc)
      hsOtherbkg->SetTitle("RHC CC-#bar#nu_{e} other background");
  }
  if(isgamma){
    hsOtherbkg->SetTitle("FHC HMN #gamma selection: other background");
    if(isrhc)
      hsOtherbkg->SetTitle("RHC HMN #gamma selection: other background");
    if(positive){
      hsOtherbkg->SetTitle("FHC HMP #gamma selection: other background");
      if(isrhc)
	hsOtherbkg->SetTitle("RHC HMP #gamma selection: other background");
    }
  }

  if(isgenie)
    hsOtherbkg->SetTitle(Form("GENIE %s", hsOtherbkg->GetTitle()));
  else
    hsOtherbkg->SetTitle(Form("NEUT %s", hsOtherbkg->GetTitle()));

  mylegendOtherbkg->Draw();
  //tpt->Draw();
  cOtherbkg->Write();
  // ---------------------------------------------------------------------------------------------------
  TCanvas *cOtherbkgAngle = new TCanvas("cOtherbkgAngle","cOtherbkgAngle");
  OtherBkgBreakdownAngle[0]->SetLineColor(intcolour[0] + 40);
  OtherBkgBreakdownAngle[0]->SetFillColor(intcolour[0] + 40);
  OtherBkgBreakdownAngle[0]->SetFillStyle(3000 + intcolour[0]);
  OtherBkgBreakdownAngle[1]->SetLineColor(intcolour[1] + 40);
  OtherBkgBreakdownAngle[1]->SetFillColor(intcolour[1] + 40);
  OtherBkgBreakdownAngle[1]->SetFillStyle(3000 + intcolour[1]);
  OtherBkgBreakdownAngle[3]->SetLineColor(intcolour[2] + 40);
  OtherBkgBreakdownAngle[3]->SetFillColor(intcolour[2] + 40);
  OtherBkgBreakdownAngle[3]->SetFillStyle(3000 + intcolour[2]);
  OtherBkgBreakdownAngle[4]->SetLineColor(intcolour[3] + 40);
  OtherBkgBreakdownAngle[4]->SetFillColor(intcolour[3] + 40);
  OtherBkgBreakdownAngle[4]->SetFillStyle(3000 + intcolour[3]);
  OtherBkgBreakdownAngle[6]->SetLineColor(intcolour[4] + 40);
  OtherBkgBreakdownAngle[6]->SetFillColor(intcolour[4] + 40);
  OtherBkgBreakdownAngle[6]->SetFillStyle(3000 + intcolour[4]);
  OtherBkgBreakdownAngle[5]->SetLineColor(intcolour[5] + 40);
  OtherBkgBreakdownAngle[5]->SetFillColor(intcolour[5] + 40);
  OtherBkgBreakdownAngle[5]->SetFillStyle(3000 + intcolour[5]);
  OtherBkgBreakdownAngle[2]->SetLineColor(1);
  OtherBkgBreakdownAngle[2]->SetFillColor(1);
  OtherBkgBreakdownAngle[2]->SetFillStyle(3024);
  OtherBkgBreakdownAngle[7]->SetLineColor(intcolour[6] + 40);
  OtherBkgBreakdownAngle[7]->SetFillColor(intcolour[6] + 40);
  OtherBkgBreakdownAngle[7]->SetFillStyle(3000 + intcolour[6]);

  for(Int_t i=0; i < 8; i++){
    IncludeOverflow(OtherBkgBreakdownAngle[i]);
    IncludeUnderflow(OtherBkgBreakdownAngle[i]);
    OtherBkgBreakdownAngle[i]->SetStats(0);
  }

  THStack *hsOtherbkgAngle = new THStack("","");
  hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[7]);
  if(!positive)
    hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[2]);
  hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[5]);
  hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[6]);
  hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[4]);
  hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[3]);
  hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[1]);
  hsOtherbkgAngle->Add(OtherBkgBreakdownAngle[0]);

  Double_t otherbkg_pionentriesAngle = OtherBkgBreakdownAngle[0]->Integral();
  Double_t otherbkg_protentriesAngle = OtherBkgBreakdownAngle[1]->Integral();
  Double_t otherbkg_epi0entriesAngle = OtherBkgBreakdownAngle[3]->Integral();
  Double_t otherbkg_emupentriesAngle = OtherBkgBreakdownAngle[4]->Integral();
  Double_t otherbkg_egamentriesAngle = OtherBkgBreakdownAngle[6]->Integral();
  Double_t otherbkg_enueentriesAngle = OtherBkgBreakdownAngle[5]->Integral();
  Double_t otherbkg_sandentriesAngle = OtherBkgBreakdownAngle[2]->Integral();
  Double_t otherbkg_otheentriesAngle = OtherBkgBreakdownAngle[7]->Integral();
  Double_t otherbkg_allentriesAngle  = otherbkg_pionentriesAngle + otherbkg_protentriesAngle + otherbkg_epi0entriesAngle + otherbkg_emupentriesAngle + otherbkg_egamentriesAngle + otherbkg_enueentriesAngle + otherbkg_sandentriesAngle + otherbkg_otheentriesAngle;

  TLegend *mylegendOtherbkgAngle = new TLegend(0.23,0.48,0.53,0.88);
  mylegendOtherbkgAngle->SetFillColor(0);
  mylegendOtherbkgAngle->SetBorderSize(0);
  mylegendOtherbkgAngle->SetTextSize(0.032);
  mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[0]     ,Form("Pions                    %.2f (%.2f\%)",otherbkg_pionentriesAngle,100*otherbkg_pionentriesAngle/otherbkg_allentriesAngle              ),"f");
  if(!positive)
    mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[1]     ,Form("Protons                 %.2f (%.2f\%)",otherbkg_protentriesAngle,100*otherbkg_protentriesAngle/otherbkg_allentriesAngle              ),"f");
  mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[3]     ,Form("e- from #pi^{0}             %.2f (%.2f\%)",otherbkg_epi0entriesAngle,100*otherbkg_epi0entriesAngle/otherbkg_allentriesAngle              ),"f");
  mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[4]     ,Form("e- from #mu/#pi           %.2f (%.2f\%)",otherbkg_emupentriesAngle,100*otherbkg_emupentriesAngle/otherbkg_allentriesAngle              ),"f");
  mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[6]     ,Form("e- from OOFV #gamma   %.2f (%.2f\%)",otherbkg_egamentriesAngle,100*otherbkg_egamentriesAngle/otherbkg_allentriesAngle              ),"f");
  mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[5]     ,Form("CC-#nu_{e}/#bar#nu_{e}              %.2f (%.2f\%)",otherbkg_enueentriesAngle,100*otherbkg_enueentriesAngle/otherbkg_allentriesAngle       ),"f");
  mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[2]     ,Form("Sand                    %.2f (%.2f\%)",otherbkg_sandentriesAngle,100*otherbkg_sandentriesAngle/otherbkg_allentriesAngle              ),"f");
  mylegendOtherbkgAngle->AddEntry(OtherBkgBreakdownAngle[7]     ,Form("Other                    %.2f (%.2f\%)",otherbkg_otheentriesAngle,100*otherbkg_otheentriesAngle/otherbkg_allentriesAngle              ),"f");

  hsOtherbkgAngle->Draw();
  hsOtherbkgAngle->GetXaxis()->SetTitle("Cos(#theta)");
  hsOtherbkgAngle->GetYaxis()->SetTitle("Events / 0.05");
  hsOtherbkgAngle->GetYaxis()->SetTitleOffset(1.2);
  hsOtherbkgAngle->SetTitle("FHC CC-#nu_{e} other background");
  if(isrhc)
    hsOtherbkgAngle->SetTitle("RHC CC-#nu_{e} other background");
  if(positive){
    hsOtherbkgAngle->SetTitle("FHC CC-#bar#nu_{e} other background");
    if(isrhc)
      hsOtherbkgAngle->SetTitle("RHC CC-#bar#nu_{e} other background");
  }
  if(isgamma){
    hsOtherbkgAngle->SetTitle("FHC HMN #gamma selection: other background");
    if(isrhc)
      hsOtherbkgAngle->SetTitle("RHC HMN #gamma selection: other background");
    if(positive){
      hsOtherbkgAngle->SetTitle("FHC HMP #gamma selection: other background");
      if(isrhc)
	hsOtherbkgAngle->SetTitle("RHC HMP #gamma selection: other background");
    }
  }

  if(isgenie)
    hsOtherbkgAngle->SetTitle(Form("GENIE %s", hsOtherbkg->GetTitle()));
  else
    hsOtherbkgAngle->SetTitle(Form("NEUT %s", hsOtherbkg->GetTitle()));

  mylegendOtherbkgAngle->Draw();
  //tpt->Draw();
  cOtherbkgAngle->Write();
  // ---------------------------------------------------------------------------------------------------
  // Gamma background
  TCanvas* CgammabkgInt = new TCanvas("CgammabkgInt", "CgammabkgInt");
  GammaInteraction[7]->SetLineColor(intcolour[0] + 40);
  GammaInteraction[7]->SetFillColor(intcolour[0] + 40);
  GammaInteraction[7]->SetFillStyle(3000 + intcolour[0]);
  GammaInteraction[0]->SetLineColor(intcolour[1] + 40);
  GammaInteraction[0]->SetFillColor(intcolour[1] + 40);
  GammaInteraction[0]->SetFillStyle(3000 + intcolour[1]);
  GammaInteraction[1]->SetLineColor(intcolour[2] + 40);
  GammaInteraction[1]->SetFillColor(intcolour[2] + 40);
  GammaInteraction[1]->SetFillStyle(3000 + intcolour[2]);
  GammaInteraction[2]->SetLineColor(intcolour[3] + 40);
  GammaInteraction[2]->SetFillColor(intcolour[3] + 40);
  GammaInteraction[2]->SetFillStyle(3000 + intcolour[3]);
  GammaInteraction[3]->SetLineColor(intcolour[4] + 40);
  GammaInteraction[3]->SetFillColor(intcolour[4] + 40);
  GammaInteraction[3]->SetFillStyle(3000 + intcolour[4]);
  GammaInteraction[4]->SetLineColor(intcolour[5] + 40);
  GammaInteraction[4]->SetFillColor(intcolour[5] + 40);
  GammaInteraction[4]->SetFillStyle(3000 + intcolour[5]);
  GammaInteraction[5]->SetLineColor(intcolour[6] + 40);
  GammaInteraction[5]->SetFillColor(intcolour[6] + 40);
  GammaInteraction[5]->SetFillStyle(3000 + intcolour[6]);
  GammaInteraction[6]->SetLineColor(intcolour[7] + 40);
  GammaInteraction[6]->SetFillColor(intcolour[7] + 40);
  GammaInteraction[6]->SetFillStyle(3000 + intcolour[7]);

  for(Int_t i=0; i < 8; i++){
    IncludeOverflow(GammaInteraction[i]);
    GammaInteraction[i]->SetStats(0);
  }

  THStack *hsGammInt = new THStack("","");
  hsGammInt->Add(GammaInteraction[7]);
  hsGammInt->Add(GammaInteraction[6]);
  hsGammInt->Add(GammaInteraction[4]);
  hsGammInt->Add(GammaInteraction[3]);
  hsGammInt->Add(GammaInteraction[5]);
  hsGammInt->Add(GammaInteraction[1]);
  hsGammInt->Add(GammaInteraction[0]);
  hsGammInt->Add(GammaInteraction[2]);

  Double_t gammaInt_cc0pi0entries = GammaInteraction[2]->Integral();
  Double_t gammaInt_cc1pi0entries = GammaInteraction[0]->Integral();
  Double_t gammaInt_ccnpi0entries = GammaInteraction[1]->Integral();
  Double_t gammaInt_nc0pi0entries = GammaInteraction[5]->Integral();
  Double_t gammaInt_nc1pi0entries = GammaInteraction[3]->Integral();
  Double_t gammaInt_ncnpi0entries = GammaInteraction[4]->Integral();
  Double_t gammaInt_oofventries   = GammaInteraction[6]->Integral();
  Double_t gammaInt_otherentries  = GammaInteraction[7]->Integral();
  Double_t gammaInt_allentries    = gammaInt_cc0pi0entries + gammaInt_cc1pi0entries + gammaInt_ccnpi0entries + gammaInt_nc0pi0entries + gammaInt_nc1pi0entries + gammaInt_ncnpi0entries + gammaInt_oofventries + gammaInt_otherentries;

  TLegend *mylegendGammInt = new TLegend(0.53,0.48,0.83,0.88);
  mylegendGammInt->SetFillColor(0);
  mylegendGammInt->SetBorderSize(0);
  mylegendGammInt->SetTextSize(0.032);
  mylegendGammInt->AddEntry(GammaInteraction[2]     ,Form("CC 0#pi^{0}    %.2f (%.2f\%)",gammaInt_cc0pi0entries,100*gammaInt_cc0pi0entries/gammaInt_allentries  ),"f");
  mylegendGammInt->AddEntry(GammaInteraction[0]     ,Form("CC 1#pi^{0}    %.2f (%.2f\%)",gammaInt_cc1pi0entries,100*gammaInt_cc1pi0entries/gammaInt_allentries  ),"f");
  mylegendGammInt->AddEntry(GammaInteraction[1]     ,Form("CC >1#pi^{0}   %.2f (%.2f\%)",gammaInt_ccnpi0entries,100*gammaInt_ccnpi0entries/gammaInt_allentries  ),"f");
  mylegendGammInt->AddEntry(GammaInteraction[5]     ,Form("NC 0#pi^{0}    %.2f (%.2f\%)",gammaInt_nc0pi0entries,100*gammaInt_nc0pi0entries/gammaInt_allentries  ),"f");
  mylegendGammInt->AddEntry(GammaInteraction[3]     ,Form("NC 1#pi^{0}    %.2f (%.2f\%)",gammaInt_nc1pi0entries,100*gammaInt_nc1pi0entries/gammaInt_allentries  ),"f");
  mylegendGammInt->AddEntry(GammaInteraction[4]     ,Form("NC >1#pi^{0}   %.2f (%.2f\%)",gammaInt_ncnpi0entries,100*gammaInt_ncnpi0entries/gammaInt_allentries  ),"f");
  mylegendGammInt->AddEntry(GammaInteraction[6]     ,Form("OOFV      %.2f (%.2f\%)",gammaInt_oofventries,100*gammaInt_oofventries/gammaInt_allentries      ),"f");
  mylegendGammInt->AddEntry(GammaInteraction[7]     ,Form("OOFGD   %.2f (%.2f\%)",gammaInt_otherentries,100*gammaInt_otherentries/gammaInt_allentries    ),"f");

  hsGammInt->Draw();
  hsGammInt->GetXaxis()->SetTitle("p_{e} [MeV/c]");
  hsGammInt->GetYaxis()->SetTitle("Events / 300 [MeV/c]");
  hsGammInt->GetYaxis()->SetTitleOffset(1.2);
  hsGammInt->GetXaxis()->SetRangeUser(0,2000);
  hsGammInt->SetTitle("FHC CC-#nu_{e} #gamma background");
  if(isrhc)
    hsGammInt->SetTitle("RHC CC-#nu_{e} #gamma background");
  if(positive){
    hsGammInt->SetTitle("FHC CC-#bar#nu_{e} #gamma background");
    if(isrhc)
      hsGammInt->SetTitle("RHC CC-#bar#nu_{e} #gamma background");
  }
  if(isgamma){
    hsGammInt->SetTitle("FHC HMN #gamma selection: #gamma signal");
    if(isrhc)
      hsGammInt->SetTitle("RHC HMN #gamma selection: #gamma signal");
    if(positive){
      hsGammInt->SetTitle("FHC HMP #gamma selection: #gamma signal");
      if(isrhc)
	hsGammInt->SetTitle("RHC HMP #gamma selection: #gamma signal");
    }
  }

  if(isgenie)
    hsGammInt->SetTitle(Form("GENIE %s", hsGammInt->GetTitle()));
  else
    hsGammInt->SetTitle(Form("NEUT %s", hsGammInt->GetTitle()));

  mylegendGammInt->Draw();
  //tpt->Draw();
  CgammabkgInt->Write();
  // ---------------------------------------------------------------------------------------------------
  TCanvas* CgammabkgIntAngle = new TCanvas("CgammabkgIntAngle", "CgammabkgIntAngle");
  GammaInteractionAngle[7]->SetLineColor(intcolour[0] + 40);
  GammaInteractionAngle[7]->SetFillColor(intcolour[0] + 40);
  GammaInteractionAngle[7]->SetFillStyle(3000 + intcolour[0]);
  GammaInteractionAngle[0]->SetLineColor(intcolour[1] + 40);
  GammaInteractionAngle[0]->SetFillColor(intcolour[1] + 40);
  GammaInteractionAngle[0]->SetFillStyle(3000 + intcolour[1]);
  GammaInteractionAngle[1]->SetLineColor(intcolour[2] + 40);
  GammaInteractionAngle[1]->SetFillColor(intcolour[2] + 40);
  GammaInteractionAngle[1]->SetFillStyle(3000 + intcolour[2]);
  GammaInteractionAngle[2]->SetLineColor(intcolour[3] + 40);
  GammaInteractionAngle[2]->SetFillColor(intcolour[3] + 40);
  GammaInteractionAngle[2]->SetFillStyle(3000 + intcolour[3]);
  GammaInteractionAngle[3]->SetLineColor(intcolour[4] + 40);
  GammaInteractionAngle[3]->SetFillColor(intcolour[4] + 40);
  GammaInteractionAngle[3]->SetFillStyle(3000 + intcolour[4]);
  GammaInteractionAngle[4]->SetLineColor(intcolour[5] + 40);
  GammaInteractionAngle[4]->SetFillColor(intcolour[5] + 40);
  GammaInteractionAngle[4]->SetFillStyle(3000 + intcolour[5]);
  GammaInteractionAngle[5]->SetLineColor(intcolour[6] + 40);
  GammaInteractionAngle[5]->SetFillColor(intcolour[6] + 40);
  GammaInteractionAngle[5]->SetFillStyle(3000 + intcolour[6]);
  GammaInteractionAngle[6]->SetLineColor(intcolour[7] + 40);
  GammaInteractionAngle[6]->SetFillColor(intcolour[7] + 40);
  GammaInteractionAngle[6]->SetFillStyle(3000 + intcolour[7]);

  for(Int_t i=0; i < 8; i++){
    IncludeOverflow(GammaInteractionAngle[i]);
    IncludeUnderflow(GammaInteractionAngle[i]);
    GammaInteractionAngle[i]->SetStats(0);
  }

  THStack *hsGammIntAngle = new THStack("","");
  hsGammIntAngle->Add(GammaInteractionAngle[7]);
  hsGammIntAngle->Add(GammaInteractionAngle[6]);
  hsGammIntAngle->Add(GammaInteractionAngle[4]);
  hsGammIntAngle->Add(GammaInteractionAngle[3]);
  hsGammIntAngle->Add(GammaInteractionAngle[5]);
  hsGammIntAngle->Add(GammaInteractionAngle[1]);
  hsGammIntAngle->Add(GammaInteractionAngle[0]);
  hsGammIntAngle->Add(GammaInteractionAngle[2]);

  Double_t gammaInt_cc0pi0entriesAngle = GammaInteractionAngle[2]->Integral();
  Double_t gammaInt_cc1pi0entriesAngle = GammaInteractionAngle[0]->Integral();
  Double_t gammaInt_ccnpi0entriesAngle = GammaInteractionAngle[1]->Integral();
  Double_t gammaInt_nc0pi0entriesAngle = GammaInteractionAngle[5]->Integral();
  Double_t gammaInt_nc1pi0entriesAngle = GammaInteractionAngle[3]->Integral();
  Double_t gammaInt_ncnpi0entriesAngle = GammaInteractionAngle[4]->Integral();
  Double_t gammaInt_oofventriesAngle   = GammaInteractionAngle[6]->Integral();
  Double_t gammaInt_otherentriesAngle  = GammaInteractionAngle[7]->Integral();
  Double_t gammaInt_allentriesAngle    = gammaInt_cc0pi0entriesAngle + gammaInt_cc1pi0entriesAngle + gammaInt_ccnpi0entriesAngle + gammaInt_nc0pi0entriesAngle + gammaInt_nc1pi0entriesAngle + gammaInt_ncnpi0entriesAngle + gammaInt_oofventriesAngle + gammaInt_otherentriesAngle;

  TLegend *mylegendGammIntAngle = new TLegend(0.23,0.48,0.53,0.88);
  mylegendGammIntAngle->SetFillColor(0);
  mylegendGammIntAngle->SetBorderSize(0);
  mylegendGammIntAngle->SetTextSize(0.032);
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[2]     ,Form("CC 0#pi^{0}    %.2f (%.2f\%)",gammaInt_cc0pi0entriesAngle,100*gammaInt_cc0pi0entriesAngle/gammaInt_allentriesAngle  ),"f");
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[0]     ,Form("CC 1#pi^{0}    %.2f (%.2f\%)",gammaInt_cc1pi0entriesAngle,100*gammaInt_cc1pi0entriesAngle/gammaInt_allentriesAngle  ),"f");
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[1]     ,Form("CC >1#pi^{0}   %.2f (%.2f\%)",gammaInt_ccnpi0entriesAngle,100*gammaInt_ccnpi0entriesAngle/gammaInt_allentriesAngle  ),"f");
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[5]     ,Form("NC 0#pi^{0}    %.2f (%.2f\%)",gammaInt_nc0pi0entriesAngle,100*gammaInt_nc0pi0entriesAngle/gammaInt_allentriesAngle  ),"f");
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[3]     ,Form("NC 1#pi^{0}    %.2f (%.2f\%)",gammaInt_nc1pi0entriesAngle,100*gammaInt_nc1pi0entriesAngle/gammaInt_allentriesAngle  ),"f");
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[4]     ,Form("NC >1#pi^{0}   %.2f (%.2f\%)",gammaInt_ncnpi0entriesAngle,100*gammaInt_ncnpi0entriesAngle/gammaInt_allentriesAngle  ),"f");
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[6]     ,Form("OOFV      %.2f (%.2f\%)",gammaInt_oofventriesAngle,100*gammaInt_oofventriesAngle/gammaInt_allentriesAngle      ),"f");
  mylegendGammIntAngle->AddEntry(GammaInteractionAngle[7]     ,Form("OOFGD   %.2f (%.2f\%)",gammaInt_otherentriesAngle,100*gammaInt_otherentriesAngle/gammaInt_allentriesAngle    ),"f");

  hsGammIntAngle->Draw();
  hsGammIntAngle->GetXaxis()->SetTitle("Cos(#theta)");
  hsGammIntAngle->GetYaxis()->SetTitle("Events / 0.05");
  hsGammIntAngle->GetYaxis()->SetTitleOffset(1.2);
  hsGammIntAngle->GetXaxis()->SetRangeUser(0,2000);
  hsGammIntAngle->SetTitle("FHC CC-#nu_{e} #gamma background");
  if(isrhc)
    hsGammIntAngle->SetTitle("RHC CC-#nu_{e} #gamma background");
  if(positive){
    hsGammIntAngle->SetTitle("FHC CC-#bar#nu_{e} #gamma background");
    if(isrhc)
      hsGammIntAngle->SetTitle("RHC CC-#bar#nu_{e} #gamma background");
  }
  if(isgamma){
    hsGammIntAngle->SetTitle("FHC HMN #gamma selection: #gamma signal");
    if(isrhc)
      hsGammIntAngle->SetTitle("RHC HMN #gamma selection: #gamma signal");
    if(positive){
      hsGammIntAngle->SetTitle("FHC HMP #gamma selection: #gamma signal");
      if(isrhc)
	hsGammIntAngle->SetTitle("RHC HMP #gamma selection: #gamma signal");
    }
  }

  if(isgenie)
    hsGammIntAngle->SetTitle(Form("GENIE %s", hsGammInt->GetTitle()));
  else
    hsGammIntAngle->SetTitle(Form("NEUT %s", hsGammInt->GetTitle()));

  mylegendGammIntAngle->Draw();
  //tpt->Draw();
  CgammabkgIntAngle->Write();
  // ---------------------------------------------------------------------------------------------------
  // Gamma bkg from OOFGD
  TCanvas* CgammabkgOOFGDTarget = new TCanvas("CgammabkgOOFGDTarget", "CgammabkgOOFGDTarget");
  GammaOOFGDTarget[0]->SetLineColor(intcolour[0] + 40);
  GammaOOFGDTarget[0]->SetFillColor(intcolour[0] + 40);
  GammaOOFGDTarget[0]->SetFillStyle(3000 + intcolour[0]);
  GammaOOFGDTarget[1]->SetLineColor(intcolour[1] + 40);
  GammaOOFGDTarget[1]->SetFillColor(intcolour[1] + 40);
  GammaOOFGDTarget[1]->SetFillStyle(3000 + intcolour[1]);
  GammaOOFGDTarget[2]->SetLineColor(intcolour[2] + 40);
  GammaOOFGDTarget[2]->SetFillColor(intcolour[2] + 40);
  GammaOOFGDTarget[2]->SetFillStyle(3000 + intcolour[2]);
  GammaOOFGDTarget[3]->SetLineColor(intcolour[3] + 40);
  GammaOOFGDTarget[3]->SetFillColor(intcolour[3] + 40);
  GammaOOFGDTarget[3]->SetFillStyle(3000 + intcolour[3]);
  GammaOOFGDTarget[4]->SetLineColor(intcolour[4] + 40);
  GammaOOFGDTarget[4]->SetFillColor(intcolour[4] + 40);
  GammaOOFGDTarget[4]->SetFillStyle(3000 + intcolour[4]);
  GammaOOFGDTarget[5]->SetLineColor(intcolour[5] + 40);
  GammaOOFGDTarget[5]->SetFillColor(intcolour[5] + 40);
  GammaOOFGDTarget[5]->SetFillStyle(3000 + intcolour[5]);
  GammaOOFGDTarget[6]->SetLineColor(intcolour[6] + 40);
  GammaOOFGDTarget[6]->SetFillColor(intcolour[6] + 40);
  GammaOOFGDTarget[6]->SetFillStyle(3000 + intcolour[6]);
  GammaOOFGDTarget[7]->SetLineColor(intcolour[8] + 40);
  GammaOOFGDTarget[7]->SetFillColor(intcolour[8] + 40);
  GammaOOFGDTarget[7]->SetFillStyle(3000 + intcolour[8]);
  GammaOOFGDTarget[8]->SetLineColor(1);
  GammaOOFGDTarget[8]->SetFillColor(1);
  GammaOOFGDTarget[8]->SetFillStyle(3024);
  GammaOOFGDTarget[9]->SetLineColor(intcolour[9] + 40);
  GammaOOFGDTarget[9]->SetFillColor(intcolour[9] + 40);
  GammaOOFGDTarget[9]->SetFillStyle(3000 + intcolour[9]);

  for(Int_t i=0; i < 10; i++){
    IncludeOverflow(GammaOOFGDTarget[i]);
    GammaOOFGDTarget[i]->SetStats(0);
  }

  THStack *hsGammTarget = new THStack("","");
  hsGammTarget->Add(GammaOOFGDTarget[9]);
  hsGammTarget->Add(GammaOOFGDTarget[8]);
  hsGammTarget->Add(GammaOOFGDTarget[7]);
  hsGammTarget->Add(GammaOOFGDTarget[6]);
  hsGammTarget->Add(GammaOOFGDTarget[5]);
  hsGammTarget->Add(GammaOOFGDTarget[4]);
  hsGammTarget->Add(GammaOOFGDTarget[3]);
  hsGammTarget->Add(GammaOOFGDTarget[2]);
  hsGammTarget->Add(GammaOOFGDTarget[1]);
  hsGammTarget->Add(GammaOOFGDTarget[0]);

  Double_t oofgd_hydrogenevents = GammaOOFGDTarget[0]->Integral();
  Double_t oofgd_carbonevents   = GammaOOFGDTarget[1]->Integral();
  Double_t oofgd_oxygenevents   = GammaOOFGDTarget[2]->Integral();
  Double_t oofgd_alumevents     = GammaOOFGDTarget[3]->Integral();
  Double_t oofgd_ironevents     = GammaOOFGDTarget[4]->Integral();
  Double_t oofgd_copperevents   = GammaOOFGDTarget[5]->Integral();
  Double_t oofgd_zincevents     = GammaOOFGDTarget[6]->Integral();
  Double_t oofgd_leadevents     = GammaOOFGDTarget[7]->Integral();
  Double_t oofgd_sandevents     = GammaOOFGDTarget[8]->Integral();
  Double_t oofgd_otherevents    = GammaOOFGDTarget[9]->Integral();
  Double_t oofgd_allevents      = oofgd_hydrogenevents + oofgd_carbonevents + oofgd_oxygenevents + oofgd_alumevents + oofgd_ironevents + oofgd_copperevents + oofgd_zincevents + oofgd_leadevents + oofgd_sandevents + oofgd_otherevents;

  TLegend *mylegendGammTarget = new TLegend(0.43,0.48,0.83,0.88);
  mylegendGammTarget->SetFillColor(0);
  mylegendGammTarget->SetBorderSize(0);
  mylegendGammTarget->SetTextSize(0.032);
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[0]   ,Form("Hydrogen     %.2f (%.2f\%)", oofgd_hydrogenevents,100*oofgd_hydrogenevents/oofgd_allevents ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[1]   ,Form("Carbon       %.2f (%.2f\%)", oofgd_carbonevents,100*oofgd_carbonevents/oofgd_allevents     ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[2]   ,Form("Oxygen       %.2f (%.2f\%)", oofgd_oxygenevents,100*oofgd_oxygenevents/oofgd_allevents     ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[3]   ,Form("Aluminium    %.2f (%.2f\%)", oofgd_alumevents,100*oofgd_alumevents/oofgd_allevents    ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[4]   ,Form("Iron         %.2f (%.2f\%)", oofgd_ironevents,100*oofgd_ironevents/oofgd_allevents         ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[5]   ,Form("Copper       %.2f (%.2f\%)", oofgd_copperevents,100*oofgd_copperevents/oofgd_allevents     ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[6]   ,Form("Zinc         %.2f (%.2f\%)", oofgd_zincevents,100*oofgd_zincevents/oofgd_allevents         ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[7]   ,Form("Lead         %.2f (%.2f\%)", oofgd_leadevents,100*oofgd_leadevents/oofgd_allevents         ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[8]   ,Form("Sand         %.2f (%.2f\%)", oofgd_sandevents,100*oofgd_sandevents/oofgd_allevents         ),"f");
  mylegendGammTarget->AddEntry(GammaOOFGDTarget[9]   ,Form("Other        %.2f (%.2f\%)", oofgd_otherevents,100*oofgd_otherevents/oofgd_allevents        ),"f");

  hsGammTarget->Draw();
  hsGammTarget->GetXaxis()->SetTitle("p_{e} [MeV/c]");
  hsGammTarget->GetYaxis()->SetTitle("Events / 300 [MeV/c]");
  hsGammTarget->GetYaxis()->SetTitleOffset(1.2);
  hsGammTarget->GetXaxis()->SetRangeUser(0,2000);
  hsGammTarget->SetTitle("FHC CC-#nu_{e} OOFGD #gamma background");
  if(isrhc)
    hsGammTarget->SetTitle("RHC CC-#nu_{e} OOFGD #gamma background");
  if(positive){
    hsGammTarget->SetTitle("FHC CC-#bar#nu_{e} OOFGD #gamma background");
    if(isrhc)
      hsGammTarget->SetTitle("RHC CC-#bar#nu_{e} OOFGD #gamma background");
  }
  if(isgamma){
    hsGammTarget->SetTitle("FHC HMN #gamma selection: OOFGD #gamma background");
    if(isrhc)
      hsGammTarget->SetTitle("RHC HMN #gamma selection: OOFGD #gamma background");
    if(positive){
      hsGammTarget->SetTitle("FHC HMP #gamma selection: OOFGD #gamma background");
      if(isrhc)
	hsGammTarget->SetTitle("RHC HMP #gamma selection: OOFGD #gamma background");
    }
  }
  
  if(isgenie)
    hsGammTarget->SetTitle(Form("GENIE %s", hsGammTarget->GetTitle()));
  else
    hsGammTarget->SetTitle(Form("NEUT %s", hsGammTarget->GetTitle()));

  mylegendGammTarget->Draw();
  //tpt->Draw();
  CgammabkgOOFGDTarget->Write();

  // OOFGD Gamma detector
  TCanvas* CgammabkgOOFGDDet = new TCanvas("CgammabkgOOFVDet", "CgammabkgOOFVDet");
  GammaDetector[2]->SetLineColor(intcolour[0] + 40);
  GammaDetector[2]->SetFillColor(intcolour[0] + 40);
  GammaDetector[2]->SetFillStyle(3000 + intcolour[0]);
  GammaDetector[3]->SetLineColor(intcolour[1] + 40);
  GammaDetector[3]->SetFillColor(intcolour[1] + 40);
  GammaDetector[3]->SetFillStyle(3000 + intcolour[1]);
  GammaDetector[4]->SetLineColor(intcolour[2] + 40);
  GammaDetector[4]->SetFillColor(intcolour[2] + 40);
  GammaDetector[4]->SetFillStyle(3000 + intcolour[2]);
  GammaDetector[6]->SetLineColor(intcolour[3] + 40);
  GammaDetector[6]->SetFillColor(intcolour[3] + 40);
  GammaDetector[6]->SetFillStyle(3000 + intcolour[3]);
  GammaDetector[7]->SetLineColor(intcolour[4] + 40);
  GammaDetector[7]->SetFillColor(intcolour[4] + 40);
  GammaDetector[7]->SetFillStyle(3000 + intcolour[4]);
  GammaDetector[8]->SetLineColor(intcolour[5] + 40);
  GammaDetector[8]->SetFillColor(intcolour[5] + 40);
  GammaDetector[8]->SetFillStyle(3000 + intcolour[5]);
  GammaDetector[9]->SetLineColor(intcolour[6] + 40);
  GammaDetector[9]->SetFillColor(intcolour[6] + 40);
  GammaDetector[9]->SetFillStyle(3000 + intcolour[6]);
  GammaDetector[5]->SetLineColor(intcolour[7] + 40);
  GammaDetector[5]->SetFillColor(intcolour[7] + 40);
  GammaDetector[5]->SetFillStyle(3000 + intcolour[7]);
  GammaDetector[0]->SetLineColor(intcolour[8] + 40);
  GammaDetector[0]->SetFillColor(intcolour[8] + 40);
  GammaDetector[0]->SetFillStyle(3000 + intcolour[8]);
  GammaDetector[1]->SetLineColor(intcolour[9] + 40);
  GammaDetector[1]->SetFillColor(intcolour[9] + 40);
  GammaDetector[1]->SetFillStyle(3000 + intcolour[9]);
  GammaDetector[10]->SetLineColor(1);
  GammaDetector[10]->SetFillColor(1);
  GammaDetector[10]->SetFillStyle(3024);
  GammaDetector[11]->SetLineColor(33);
  GammaDetector[11]->SetFillColor(33);
  GammaDetector[11]->SetFillStyle(3023);

  THStack *hsGammOut = new THStack("","");
  hsGammOut->Add(GammaDetector[11]);
  hsGammOut->Add(GammaDetector[10]);
  hsGammOut->Add(GammaDetector[5]);
  hsGammOut->Add(GammaDetector[9]);
  hsGammOut->Add(GammaDetector[8]);
  hsGammOut->Add(GammaDetector[7]);
  hsGammOut->Add(GammaDetector[6]);
  hsGammOut->Add(GammaDetector[1]);
  hsGammOut->Add(GammaDetector[0]);
  hsGammOut->Add(GammaDetector[4]);
  hsGammOut->Add(GammaDetector[3]);
  hsGammOut->Add(GammaDetector[2]);

  Double_t oofvgamma_p0dentries    = GammaDetector[2]->Integral();
  Double_t oofvgamma_dsecalentries = GammaDetector[3]->Integral();
  Double_t oofvgamma_brecalentries = GammaDetector[4]->Integral();
  Double_t oofvgamma_fgd1entries   = GammaDetector[0]->Integral();
  Double_t oofvgamma_fgd2entries   = GammaDetector[1]->Integral();
  Double_t oofvgamma_tpc1entries   = GammaDetector[6]->Integral();
  Double_t oofvgamma_tpc2entries   = GammaDetector[7]->Integral();
  Double_t oofvgamma_tpc3entries   = GammaDetector[8]->Integral();
  Double_t oofvgamma_smrdentries   = GammaDetector[9]->Integral();
  Double_t oofvgamma_pecalentries  = GammaDetector[5]->Integral();
  Double_t oofvgamma_sandentries   = GammaDetector[10]->Integral();
  Double_t oofvgamma_otherentries  = GammaDetector[11]->Integral();
  Double_t oofvgamma_allentries    = oofvgamma_p0dentries + oofvgamma_dsecalentries + oofvgamma_brecalentries + oofvgamma_fgd1entries + oofvgamma_fgd2entries + oofvgamma_tpc1entries + oofvgamma_tpc2entries + oofvgamma_tpc3entries + oofvgamma_smrdentries + oofvgamma_pecalentries + oofvgamma_sandentries + oofvgamma_otherentries;

  TLegend *mylegendGammOut = new TLegend(0.43,0.40,0.85,0.88);
  mylegendGammOut->SetFillColor(0); // white background
  mylegendGammOut->SetBorderSize(0);
  mylegendGammOut->SetTextSize(0.032);
  mylegendGammOut->AddEntry(GammaDetector[2]       ,Form("P0D     %.2f (%.2f\%)"      ,oofvgamma_p0dentries,100*oofvgamma_p0dentries/oofvgamma_allentries),      "lf");
  mylegendGammOut->AddEntry(GammaDetector[3]       ,Form("DsEcal  %.2f (%.2f\%)"      ,oofvgamma_dsecalentries,100*oofvgamma_dsecalentries/oofvgamma_allentries),"lf");
  mylegendGammOut->AddEntry(GammaDetector[4]       ,Form("BrEcal  %.2f (%.2f\%)"      ,oofvgamma_brecalentries,100*oofvgamma_brecalentries/oofvgamma_allentries),"lf");
  mylegendGammOut->AddEntry(GammaDetector[0]       ,Form("FGD1    %.2f (%.2f\%)"      ,oofvgamma_fgd1entries,100*oofvgamma_fgd1entries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[1]       ,Form("FGD2    %.2f (%.2f\%)"      ,oofvgamma_fgd2entries,100*oofvgamma_fgd2entries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[6]       ,Form("TPC1    %.2f (%.2f\%)"      ,oofvgamma_tpc1entries,100*oofvgamma_tpc1entries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[7]       ,Form("TPC2    %.2f (%.2f\%)"      ,oofvgamma_tpc2entries,100*oofvgamma_tpc2entries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[8]       ,Form("TPC3    %.2f (%.2f\%)"      ,oofvgamma_tpc3entries,100*oofvgamma_tpc3entries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[9]       ,Form("SMRD    %.2f (%.2f\%)"      ,oofvgamma_smrdentries,100*oofvgamma_smrdentries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[5]       ,Form("P0DEcal %.2f (%.2f\%)"      ,oofvgamma_pecalentries,100*oofvgamma_pecalentries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[10]      ,Form("Sand    %.2f (%.2f\%)"      ,oofvgamma_sandentries,100*oofvgamma_sandentries/oofvgamma_allentries),    "lf");
  mylegendGammOut->AddEntry(GammaDetector[11]      ,Form("Other   %.2f (%.2f\%)"      ,oofvgamma_otherentries,100*oofvgamma_otherentries/oofvgamma_allentries),  "lf");

  hsGammOut->Draw();
  hsGammOut->GetXaxis()->SetTitle("Momentum [MeV/c]");
  hsGammOut->GetYaxis()->SetTitle("Events / 300 [MeV/c]");
  hsGammOut->GetYaxis()->SetTitleOffset(1.2);
  hsGammOut->GetXaxis()->SetRangeUser(0,2000);
  hsGammOut->SetTitle("FHC CC-#nu_{e} OOFV #gamma background");
  if(isrhc)
    hsGammOut->SetTitle("RHC CC-#nu_{e} OOFV #gamma background");
  if(positive){
    hsGammOut->SetTitle("FHC CC-#bar#nu_{e} OOFV #gamma background");
    if(isrhc)
      hsGammOut->SetTitle("RHC CC-#bar#nu_{e} OOFV #gamma background");
  }
  if(isgamma){
    hsGammOut->SetTitle("FHC HMN #gamma selection: OOFV #gamma background");
    if(isrhc)
      hsGammOut->SetTitle("RHC HMN #gamma selection: OOFV #gamma background");
    if(positive){
      hsGammOut->SetTitle("FHC HMP #gamma selection: OOFV #gamma background");
      if(isrhc)
	hsGammOut->SetTitle("RHC HMP #gamma selection: OOFV #gamma background");
    }
  }

  if(isgenie)
    hsGammOut->SetTitle(Form("GENIE %s", hsGammOut->GetTitle()));
  else
    hsGammOut->SetTitle(Form("NEUT %s", hsGammOut->GetTitle()));

  mylegendGammOut->Draw();
  //tpt->Draw();
  CgammabkgOOFGDDet->Write();
  
}

// ----------------------------------------------------------------------------
TCanvas* GetEffPurGraph(Int_t type, TH1D* effdenom, TH1D* effnom, TH1D* purdenom, TH1D* purnom, TH1D* selhisto=NULL, TH1D* selhisto2=NULL){

  effdenom->Sumw2(true);
  effnom->Sumw2(true);
  purdenom->Sumw2(true);
  purnom->Sumw2(true);
  TGraphAsymmErrors *Purity = new TGraphAsymmErrors(purdenom,purnom,"b(0.0001,1)");
  TGraphAsymmErrors *Efficiency = new TGraphAsymmErrors(effdenom,effnom,"b(0.0001,1)");

  TString cname("cnull");
  if(type == 0)
    cname = "cEffPos";
  else if(type == 1 || type == 12)
    cname = "cEffPurMom";
  else if(type == 2 || type == 22)
    cname = "cEffPurAng";
  else if(type == 3 || type == 4 || type == 5 || type == 6)
    cname = "cEffPurEv";
  else if(type == 100 || type == 102)
    cname = "cEffPurMomCC0Pi";
  else if(type == 101 || type == 103)
    cname = "cEffPurAngCC0Pi";

  gStyle->SetPadTickX(0);
  gStyle->SetPadTickY(0);

  TCanvas *c91 = new TCanvas(cname.Data(), cname.Data());
  Purity->Draw("*a");
  //Purity->Draw("e");
  Purity->SetMarkerColor(2);
  Purity->SetMarkerStyle(25);
  Purity->SetLineColor(2);
  Purity->GetYaxis()->SetTitleOffset(1.2);
  Purity->GetYaxis()->SetRangeUser(0,1);

  if(type == 0)
    Purity->GetXaxis()->SetTitle("Z [mm]");
  else if(type == 1 || type == 12 || type == 100 || type == 102)
    Purity->GetXaxis()->SetTitle("p_{true} [MeV/c]");
  else if(type == 2 || type == 22 || type == 101 || type == 103)
    Purity->GetXaxis()->SetTitle("#theta_{true}");
  else if(type == 3 || type == 4 || type == 5 || type == 6)
    Purity->GetXaxis()->SetTitle("E_{v} [GeV]");

  if(type == 0){
    Purity->SetTitle("FHC CC-#nu_{e} Efficiency");
    Purity->GetYaxis()->SetTitle("Vertex Efficiency");
    if(isrhc)
      Purity->SetTitle("RHC CC-#nu_{e} Efficiency");
    if(positive){
      Purity->SetTitle("FHC CC-#bar#nu_{e} Efficiency");
      if(isrhc)
	Purity->SetTitle("RHC CC-#bar#nu_{e} Efficiency");
    }
  }
  else if(type < 100){
    Purity->SetTitle("FHC CC-#nu_{e} Purity-Efficiency");
    Purity->GetYaxis()->SetTitle("CC-#nu_{e} Purity-Efficiency");
    if(isrhc)
      Purity->SetTitle("RHC CC-#nu_{e} Purity-Efficiency");
    if(positive){
      Purity->SetTitle("FHC CC-#bar#nu_{e} Efficiency");
      if(isrhc)
	Purity->SetTitle("RHC CC-#bar#nu_{e} Efficiency");
    }
  }
  else if(type == 100 || type == 101){
    Purity->SetTitle("FHC CC-#nu_{e} Efficiency");
    Purity->GetYaxis()->SetTitle("#nu_{e} CC-0#pi/CC-Other Efficiency");
    if(isrhc)
      Purity->SetTitle("RHC CC-#nu_{e} Efficiency");
  }
  else if(type == 102 || type == 103){
    Purity->SetTitle("FHC CC-#bar#nu_{e} Efficiency");
    Purity->GetYaxis()->SetTitle("#bar#nu_{e} CC-0#pi/CC-Other Efficiency");
    if(isrhc)
      Purity->SetTitle("RHC CC-#bar#nu_{e} Efficiency");
  }

  if(isgenie)
    Purity->SetTitle(Form("GENIE %s", Purity->GetTitle()));
  else
    Purity->SetTitle(Form("NEUT %s", Purity->GetTitle()));

  if(type > 0){
    Efficiency->Draw("*same");
    Efficiency->SetMarkerColor(4);
    Efficiency->SetMarkerStyle(4);
    Efficiency->SetLineColor(4);
    Efficiency->GetYaxis()->SetRangeUser(0,1);
  }

  TLegend *mylegend3 = new TLegend(0.51,0.73,0.75,0.89);
  mylegend3->SetFillColor(0); // white background
  mylegend3->SetBorderSize(0);
  mylegend3->SetTextSize(0.036);
  if(type < 100){
    mylegend3->AddEntry(Purity,"Purity","lp");
    mylegend3->AddEntry(Efficiency,"Efficiency","lp");
  }
  else{
    mylegend3->AddEntry(Efficiency,"CC-0#pi Efficiency","lp");
    mylegend3->AddEntry(Purity,"CC-Other Efficiency","lp");
  }

  if(type == 1 || type == 12){
    TLegendEntry* entry = mylegend3->AddEntry("","Momentum","f");
    entry->SetLineColor(30);
  }
  else if(type == 2 || type == 22){
    TLegendEntry* entry = mylegend3->AddEntry("","Cos(#theta)","f");
    entry->SetLineColor(30);
  }
  else if(type == 3){
    TLegendEntry* entry = mylegend3->AddEntry("","T2K FHC #nu_{e} Flux","f");
    entry->SetLineColor(30);
  }
  else if(type == 4){
    TLegendEntry* entry = mylegend3->AddEntry("","T2K RHC #nu_{e} Flux","f");
    entry->SetLineColor(30);
  }
  else if(type == 5){
    TLegendEntry* entry = mylegend3->AddEntry("","T2K FHC #bar#nu_{e} Flux","f");
    entry->SetLineColor(30);
  }
  else if(type == 6){
    TLegendEntry* entry = mylegend3->AddEntry("","T2K RHC #bar#nu_{e} Flux","f");
    entry->SetLineColor(30);
  }
  

  if(selhisto && !selhisto2){
    c91->Update();
    Float_t Mrightmax = 1.1*selhisto->GetMaximum();
    Float_t Mscale = gPad->GetUymax()/Mrightmax;
    selhisto->SetLineWidth(2);
    selhisto->SetLineColor(30);
    selhisto->SetFillColor(30);
    selhisto->SetFillStyle(4000); // transparent
    selhisto->Scale(Mscale);
    selhisto->Draw("samehist");
    
    // Draw axis on the right side
    TGaxis *Maxis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0,Mrightmax,510,"+L");
    Maxis->SetLineColor(30);
    Maxis->SetLabelColor(30);
    Maxis->SetTitleColor(30);
    Maxis->SetTitleOffset(1.15);
    if(type == 1 || type == 12){
      Maxis->SetTitle("Events / 300 [MeV/c]");
      Maxis->SetName("axismom");
    }
    else if(type == 2 || type == 22){
      Maxis->SetTitle("Events / 0.1");
      Maxis->SetName("axisangle");
    }
    else if(type == 3 || type == 4){
      Maxis->SetTitle("#nu flux (#times 10^{10} cm^{2}/50 MeV/10^{21} POT)");
      Maxis->SetName("axisenu");
    }
    else if(type == 5 || type == 6){
      Maxis->SetTitle("#bar#nu flux (#times 10^{10} cm^{2}/50 MeV/10^{21} POT)");
      Maxis->SetName("axisenu");
    }
    Maxis->Draw();
  }

  if(selhisto && selhisto2){
    c91->Update();
    Float_t CC0Pirightmax = 1.1*selhisto2->GetMaximum();
    if(selhisto->GetMaximum() > selhisto2->GetMaximum())
      CC0Pirightmax = 1.1*selhisto->GetMaximum();
    Float_t CC0Piscale = gPad->GetUymax()/CC0Pirightmax;
    selhisto2->SetLineWidth(2);
    selhisto2->SetLineStyle(kDashed);
    selhisto2->SetLineColor(33);
    selhisto2->SetFillColor(33);
    selhisto2->SetFillStyle(4000); // transparent
    selhisto2->Scale(CC0Piscale);
    selhisto2->Draw("samehist");
    
    selhisto->SetLineWidth(2);
    selhisto->SetLineColor(30);
    selhisto->SetFillColor(30);
    selhisto->SetFillStyle(4000); // transparent
    selhisto->Scale(CC0Piscale);
    selhisto->Draw("samehist");
    
    mylegend3->AddEntry(selhisto,"CC-0#pi Momentum","fl");
    mylegend3->AddEntry(selhisto2,"CC-Other Momentum","fl");
    
    // Draw axis on the right side
    TGaxis *CC0Piaxis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0,CC0Pirightmax,510,"+L");
    CC0Piaxis->SetLineColor(30);
    CC0Piaxis->SetLabelColor(30);
    CC0Piaxis->SetTitleColor(30);
    CC0Piaxis->SetTitleOffset(1.15);
    if(type == 100 || type == 102){
      CC0Piaxis->SetTitle("Events / 300 [MeV/c]");
      CC0Piaxis->SetName("axismom");
    }
    else if(type == 101 || type == 103){
      CC0Piaxis->SetTitle("Events / 0.1");
      CC0Piaxis->SetName("axisangle");
    }
    CC0Piaxis->Draw();
  }

  if(type > 0)
    mylegend3->Draw();
  //cout << Purity->GetName() << " , " << Efficiency->GetName() << endl;
  //if(selhisto) cout << selhisto->GetName() << endl;
  //if(selhisto2) cout << selhisto2->GetName() << endl;
  return c91;
}

// ----------------------------------------------------------------------------
void FillDataHistograms(TString datafile){

  Int_t run, subrun, evt, selelec_FGD, TPCVetoNNearTracks, TPCVetoNFarTracks, nfgdonlytracks, accum_level;
  Float_t selelec_mom, selelec_costheta, selelec_startpos[4], selelec_startdir[4], PairTrack_InvMass, PairTrack_mom, PairTrack_costheta, selelec_Q2recQE, weight_corr_total, selelec_ecalemene, selelec_ToF_ECal_FGD1, selelec_ToF_ECal_FGD2, selelec_ToF_DsECal_FGD1, selelec_ToF_DsECal_FGD2, selelec_likeelec, selelec_ElemomTPCBack, selelec_fgd_V33[2], selelec_fgd_V77[2];

  TFile *dataFile   = new TFile(datafile.Data(), "READ");
  TTree *TreeSignal = (TTree*)dataFile->Get("default");

  TreeSignal->SetBranchAddress("run",                            &run);
  TreeSignal->SetBranchAddress("subrun",                         &subrun);
  TreeSignal->SetBranchAddress("evt",                            &evt);
  TreeSignal->SetBranchAddress("selelec_mom",                    &selelec_mom);
  TreeSignal->SetBranchAddress("selelec_costheta",               &selelec_costheta);
  TreeSignal->SetBranchAddress("selelec_Q2recQE",                &selelec_Q2recQE);
  TreeSignal->SetBranchAddress("selelec_startpos",               &selelec_startpos);
  TreeSignal->SetBranchAddress("selelec_startdir",               &selelec_startdir);
  TreeSignal->SetBranchAddress("selelec_FGD",                    &selelec_FGD);
  TreeSignal->SetBranchAddress("PairTrack_InvMass",              &PairTrack_InvMass);
  TreeSignal->SetBranchAddress("PairTrack_mom",                  &PairTrack_mom);
  TreeSignal->SetBranchAddress("PairTrack_costheta",             &PairTrack_costheta);
  TreeSignal->SetBranchAddress("weight_corr_total",              &weight_corr_total);
  TreeSignal->SetBranchAddress("selelec_ecalemene",              &selelec_ecalemene);
  TreeSignal->SetBranchAddress("TPCVetoNNearTracks",             &TPCVetoNNearTracks);
  TreeSignal->SetBranchAddress("TPCVetoNFarTracks",              &TPCVetoNFarTracks);
  TreeSignal->SetBranchAddress("nfgdonlytracks",                 &nfgdonlytracks);
  TreeSignal->SetBranchAddress("accum_level",                    &accum_level);
  TreeSignal->SetBranchAddress("selelec_ToF_ECal_FGD1",          &selelec_ToF_ECal_FGD1);
  TreeSignal->SetBranchAddress("selelec_ToF_ECal_FGD2",          &selelec_ToF_ECal_FGD2);
  TreeSignal->SetBranchAddress("selelec_ToF_DsECal_FGD1",        &selelec_ToF_DsECal_FGD1);
  TreeSignal->SetBranchAddress("selelec_ToF_DsECal_FGD2",        &selelec_ToF_DsECal_FGD2);
  TreeSignal->SetBranchAddress("selelec_likeelec",               &selelec_likeelec);
  TreeSignal->SetBranchAddress("selelec_ElemomTPCBack",          &selelec_ElemomTPCBack);
  TreeSignal->SetBranchAddress("selelec_fgd_V33",                &selelec_fgd_V33);
  TreeSignal->SetBranchAddress("selelec_fgd_V77",                &selelec_fgd_V77);

  std::cout << "INFO::Running on data file " << datafile << " with pot " << GetPOTFromFile(datafile) << std::endl;

  for(Int_t i = 0; i < TreeSignal->GetEntries(); i++){
    TreeSignal->GetEntry(i);

    if(accum_level < ACCUMLEVELCUT) continue;

    Double_t pt = selelec_mom*sqrt(1-selelec_costheta*selelec_costheta);
    if(selelec_FGD == 1){
      selelec_ToF_ECal_FGD1 = selelec_ToF_ECal_FGD2;
      selelec_ToF_DsECal_FGD1 = selelec_ToF_DsECal_FGD2;
    }
    
    DataH[0]->Fill(selelec_costheta);
    DataH[1]->Fill(selelec_Q2recQE);
    DataH[2]->Fill(pt/selelec_mom);
    DataH[3]->Fill(selelec_startpos[2]);
    DataH[4]->Fill(acos(selelec_costheta));
    DataH[5]->Fill(selelec_mom);
    DataH[6]->Fill(pt);
    if(selelec_ToF_ECal_FGD1 != -999)
      DataH[7]->Fill(selelec_ToF_ECal_FGD1);
    if(selelec_ToF_DsECal_FGD1 != -999)
      DataH[8]->Fill(selelec_ToF_DsECal_FGD1);
    if(accum_level == 3 && selelec_ecalemene != -999)
      DataH[9]->Fill(selelec_likeelec);
    if(accum_level == 6 && selelec_ecalemene != -999)
      DataH[10]->Fill(selelec_ecalemene/selelec_mom);

    CCSignalNeutrinoParent[8]->Fill(selelec_mom);
  }
  
}

// ----------------------------------------------------------------------------
void FillMCHistograms(TString mcfile, Double_t datapot, bool issand=false){

  // Tree variables
  Int_t run, subrun, evt, truevtx_mass_component, nue_cc0pi, nue_ccother, nu_truereac, TPCVetoNNearTracks, TPCVetoNFarTracks, accum_level;
  Float_t truelepton_mom,  truelepton_costheta_nuDir, nu_trueE, truevtx_pos[4], truelepton_pos[4], weight[1];

  Int_t nuesimpletopo, nuesimpleparent, fgd2nuesimpletopo, fgd2nuesimpleparent,  particle, nu_pdg, parent, gparent, NuParentPDGRaw, target, selelec_FGD, NTruePions, NTruePi0, NTrueKaonRhoEta, detector, NWEIGHTSYST, nue_cc0pi, nue_ccother, reaction, nfgdonlytracks, nfgdtracks, fgd2reaction;
  Float_t nu_trueE, selelec_mom, selelec_costheta, selelec_true_mom, selelec_true_costheta, selelec_startpos[4], selelec_startdir[4], selelec_true_pos[4], PairTrack_InvMass, PairTrack_mom, PairTrack_costheta, weight_corr_total, truelepton_mom, truelepton_pos[4], selelec_Q2recQE, selelec_ecalemene, ECALNCMinZ, TPCVetoDeltaz, selelec_ToF_ECal_FGD1, selelec_ToF_ECal_FGD2, selelec_ToF_DsECal_FGD1, selelec_ToF_DsECal_FGD2, selelec_likeelec, selelec_ElemomTPCBack, selelec_fgd_V33[2], selelec_fgd_V77[2];

  // pot ratio
  Double_t mcpot = GetPOTFromFile(mcfile);
  Double_t potratio = datapot/mcpot;

  std::cout << "INFO::Running on mc file " << mcfile << " with pot " << mcpot << " and pot ratio " << potratio << std::endl;

  TFile *mcFile      = new TFile(mcfile.Data(), "READ");
  TTree *TruthSignal = (TTree*)mcFile->Get("truth");
  TTree *TreeSignal  = (TTree*)mcFile->Get("default");

  TruthSignal->SetBranchAddress("run",                            &run);
  TruthSignal->SetBranchAddress("nu_truereac",                    &nu_truereac);
  TruthSignal->SetBranchAddress("truelepton_mom",                 &truelepton_mom);
  TruthSignal->SetBranchAddress("truelepton_costheta_nuDir",      &truelepton_costheta_nuDir);
  TruthSignal->SetBranchAddress("nu_trueE",                       &nu_trueE);
  TruthSignal->SetBranchAddress("detector",                       &detector);
  // 0: FGD1, 1: FGD2, 2: P0D, 3: DsEcal, 4: BrEcal, 5: P0DEcal, 6: TPC1, 7: TPC2, 8: TPC3, 9: SMRD, 999: Other, -1: NoTruth
  TruthSignal->SetBranchAddress("truelepton_pos",                 &truelepton_pos);
  TruthSignal->SetBranchAddress("weight",                         &weight);
  TruthSignal->SetBranchAddress("nue_cc0pi",                      &nue_cc0pi);
  TruthSignal->SetBranchAddress("nue_ccother",                    &nue_ccother);
  // 1: FGD1, 4: FGD2scint, 5: FGD2water
  TruthSignal->SetBranchAddress("truevtx_mass_component",         &truevtx_mass_component);

  TreeSignal->SetBranchAddress("selelec_mom",                     &selelec_mom);
  TreeSignal->SetBranchAddress("selelec_costheta",                &selelec_costheta);
  TreeSignal->SetBranchAddress("selelec_true_mom",                &selelec_true_mom);
  TreeSignal->SetBranchAddress("selelec_true_costheta",           &selelec_true_costheta);
  TreeSignal->SetBranchAddress("selelec_startpos",                &selelec_startpos);
  TreeSignal->SetBranchAddress("selelec_startdir",                &selelec_startdir);
  TreeSignal->SetBranchAddress("selelec_true_pos",                &selelec_true_pos);
  TreeSignal->SetBranchAddress("truevtx_mass_component",          &truevtx_mass_component);
  TreeSignal->SetBranchAddress("run",                             &run);
  TreeSignal->SetBranchAddress("subrun",                          &subrun);
  TreeSignal->SetBranchAddress("evt",                             &evt);
  TreeSignal->SetBranchAddress("nuesimpletopo",                   &nuesimpletopo);
  TreeSignal->SetBranchAddress("nuesimpleparent",                 &nuesimpleparent);
  TreeSignal->SetBranchAddress("fgd2nuesimpletopo",               &fgd2nuesimpletopo);
  TreeSignal->SetBranchAddress("fgd2nuesimpleparent",             &fgd2nuesimpleparent);
  TreeSignal->SetBranchAddress("particle",                        &particle);
  TreeSignal->SetBranchAddress("nu_pdg",                          &nu_pdg);
  TreeSignal->SetBranchAddress("nu_truereac",                     &nu_truereac);
  TreeSignal->SetBranchAddress("parent",                          &parent);
  TreeSignal->SetBranchAddress("gparent",                         &gparent);
  TreeSignal->SetBranchAddress("nu_trueE",                        &nu_trueE);
  TreeSignal->SetBranchAddress("NuParentPDGRaw",                  &NuParentPDGRaw);
  TreeSignal->SetBranchAddress("target",                          &target);
  // 1: Hydrogen, 6: Carbon, 8: Oxygen, 13: Aluminium, 26: Iron, 29: Copper, 30: Zinc, 82: Lead, 999: Other, -1: No truth
  TreeSignal->SetBranchAddress("selelec_FGD",                     &selelec_FGD);
  TreeSignal->SetBranchAddress("NTruePions",                      &NTruePions);
  TreeSignal->SetBranchAddress("NTruePi0",                        &NTruePi0);
  TreeSignal->SetBranchAddress("NTrueKaonRhoEta",                 &NTrueKaonRhoEta);
  TreeSignal->SetBranchAddress("detector",                        &detector);
  TreeSignal->SetBranchAddress("PairTrack_InvMass",               &PairTrack_InvMass);
  TreeSignal->SetBranchAddress("PairTrack_mom",                   &PairTrack_mom);
  TreeSignal->SetBranchAddress("PairTrack_costheta",              &PairTrack_costheta);
  TreeSignal->SetBranchAddress("weight_corr_total",               &weight_corr_total);
  TreeSignal->SetBranchAddress("NWEIGHTSYST",                     &NWEIGHTSYST);
  TreeSignal->SetBranchAddress("truelepton_mom",                  &truelepton_mom);
  TreeSignal->SetBranchAddress("truelepton_pos",                  &truelepton_pos);
  TreeSignal->SetBranchAddress("truelepton_costheta_nuDir",       &truelepton_costheta_nuDir);
  TreeSignal->SetBranchAddress("selelec_Q2recQE",                 &selelec_Q2recQE);
  TreeSignal->SetBranchAddress("nue_cc0pi",                       &nue_cc0pi);
  TreeSignal->SetBranchAddress("nue_ccother",                     &nue_ccother);
  TreeSignal->SetBranchAddress("truelepton_costheta_nuDir",       &truelepton_costheta_nuDir);
  TreeSignal->SetBranchAddress("reaction",                        &reaction);
  TreeSignal->SetBranchAddress("fgd2reaction",                    &fgd2reaction);
  TreeSignal->SetBranchAddress("selelec_ecalemene",               &selelec_ecalemene);
  TreeSignal->SetBranchAddress("TPCVetoNNearTracks",              &TPCVetoNNearTracks);
  TreeSignal->SetBranchAddress("TPCVetoNFarTracks",               &TPCVetoNFarTracks);
  TreeSignal->SetBranchAddress("ECALNCMinZ",                      &ECALNCMinZ);
  TreeSignal->SetBranchAddress("nfgdonlytracks",                  &nfgdonlytracks);
  TreeSignal->SetBranchAddress("nfgdtracks",                      &nfgdtracks);
  TreeSignal->SetBranchAddress("TPCVetoDeltaz",                   &TPCVetoDeltaz);
  TreeSignal->SetBranchAddress("accum_level",                     &accum_level);
  TreeSignal->SetBranchAddress("selelec_ToF_ECal_FGD1",           &selelec_ToF_ECal_FGD1);
  TreeSignal->SetBranchAddress("selelec_ToF_ECal_FGD2",           &selelec_ToF_ECal_FGD2);
  TreeSignal->SetBranchAddress("selelec_ToF_DsECal_FGD1",         &selelec_ToF_DsECal_FGD1);
  TreeSignal->SetBranchAddress("selelec_ToF_DsECal_FGD2",         &selelec_ToF_DsECal_FGD2);
  TreeSignal->SetBranchAddress("selelec_likeelec",                &selelec_likeelec);
  TreeSignal->SetBranchAddress("selelec_ElemomTPCBack",           &selelec_ElemomTPCBack);
  TreeSignal->SetBranchAddress("selelec_fgd_V33",                 &selelec_fgd_V33);
  TreeSignal->SetBranchAddress("selelec_fgd_V77",                 &selelec_fgd_V77);

  // Truth 
  for(Int_t i = 0; i < TruthSignal->GetEntries(); i++){
    TruthSignal->GetEntry(i);

    if(issand) break;
    //if(truelepton_costheta_nuDir == -999) continue;

    Double_t masscorr = 1.0;
    if(truevtx_mass_component == 1 || truevtx_mass_component == 4) // FGD1 or FGD2 scint (4)
      masscorr = fgd1massweight;
    else if(truevtx_mass_component == 5) // FGD2 water (5)
      masscorr = fgd2massweight;

    Double_t allweight = weight[0]*masscorr*potratio;

    EffTrue->Fill(truelepton_mom, weight[0]*masscorr);
    NEffTrue->Fill(nu_trueE/1000.0, weight[0]*masscorr);
    AngTrue->Fill(acos(truelepton_costheta_nuDir), weight[0]*masscorr);
    PosTrue->Fill(truelepton_pos[2], weight[0]*masscorr);
    SEffTrueEventsCCInc->Fill(truelepton_mom, allweight);
    SAngTrueEventsCCInc->Fill(acos(truelepton_costheta_nuDir), allweight);

    if(nue_cc0pi == 1){
      EffTrueCC0Pi->Fill(truelepton_mom, weight[0]*masscorr);
      AngTrueCC0Pi->Fill(truelepton_costheta_nuDir, weight[0]*masscorr);
      SEffTrueEventsCC0Pi->Fill(truelepton_mom, allweight);
      SAngTrueEventsCC0Pi->Fill(truelepton_costheta_nuDir, allweight);
    }
    else{
      EffTrueCCOther->Fill(truelepton_mom, weight[0]*masscorr);
      AngTrueCCOther->Fill(truelepton_costheta_nuDir, weight[0]*masscorr);
      SEffTrueEventsCCOther->Fill(truelepton_mom, allweight);
      SAngTrueEventsCCOther->Fill(truelepton_costheta_nuDir, allweight);
    }
    
    // Efficiency plots for neut-genie comparisons
    if(truelepton_costheta_nuDir > xsangparnum[0] && truelepton_mom > MINMOMENTUM){
      TruthSelMom->Fill(truelepton_mom, weight[0]);
      TruthSelAng->Fill(truelepton_costheta_nuDir, weight[0]);
      TrueMomCosTruth->Fill(truelepton_mom, truelepton_costheta_nuDir, weight[0]);
    }
    
    if(truelepton_costheta_nuDir > xsangparnum[0] && truelepton_costheta_nuDir <= xsangparnum[1]){
      TruthSelMom2->Fill(truelepton_mom, weight[0]);
      TruthSelMom4->Fill(truelepton_mom, weight[0]);
    }
    else if(truelepton_costheta_nuDir > xsangparnum[1] && truelepton_costheta_nuDir < xsangparnum[2]){
      TruthSelMom3->Fill(truelepton_mom, weight[0]);
      TruthSelMom5->Fill(truelepton_mom, weight[0]);
    }
    
  }

  // Selection
  for(Int_t i = 0; i < TreeSignal->GetEntries(); i++){
    TreeSignal->GetEntry(i);

    if(selelec_true_costheta == -999) selelec_true_costheta = 1.0;
    
    Double_t masscorr = 1.0;
    if(truevtx_mass_component == 1 || truevtx_mass_component == 4) // FGD1 or FGD2 scint (4)
      masscorr = fgd1massweight;
    else if(truevtx_mass_component == 5) // FGD2 water (5)
      masscorr = fgd2massweight;

    if(accum_level < ACCUMLEVELCUT) continue;

    if(selelec_FGD == 1){
      selelec_ToF_ECal_FGD1 = selelec_ToF_ECal_FGD2;
      selelec_ToF_DsECal_FGD1 = selelec_ToF_DsECal_FGD2;
      nuesimpletopo = fgd2nuesimpletopo;
      nuesimpleparent = fgd2nuesimpleparent;
      reaction = fgd2reaction;
    }

    Double_t allweight = weight_corr_total*potratio*masscorr;
    Double_t wnopot = weight_corr_total*masscorr;

    Double_t pt = selelec_mom*sqrt(1-selelec_costheta*selelec_costheta);

    Double_t p = selelec_mom;
    if(p >= 5400) p = 5250;
    Double_t theta = acos(selelec_costheta);
    if(theta >= 1.6) theta = 1.55;
    
    if(nuesimpletopo == 1){ // nue CC0pi
      CCH[0]->Fill(selelec_costheta,allweight);
      CCH[1]->Fill(selelec_Q2recQE,allweight);
      CCH[2]->Fill(pt/selelec_mom,allweight);
      CCH[3]->Fill(selelec_startpos[2],allweight);
      CCH[4]->Fill(acos(selelec_costheta),allweight);
      CCH[5]->Fill(selelec_mom,allweight);
      CCH[6]->Fill(pt,allweight);
      if(selelec_ToF_ECal_FGD1 != -999)
	CCH[7]->Fill(selelec_ToF_ECal_FGD1,allweight);
      if(selelec_ToF_DsECal_FGD1 != -999)
	CCH[8]->Fill(selelec_ToF_DsECal_FGD1,allweight);
      if(accum_level == 3 && selelec_ecalemene != -999)
	CCH[9]->Fill(selelec_likeelec,allweight);
      if(accum_level == 6 && selelec_ecalemene != -999)
	CCH[10]->Fill(selelec_ecalemene/selelec_mom,allweight);

      // Fill neutrino parent
      if(nuesimpleparent == 1){
	CCSignalNeutrinoParent[0]->Fill(selelec_mom,allweight);
      }
      else if(nuesimpleparent == 2){
	if(abs(NuParentPDGRaw) == 130)
	  CCSignalNeutrinoParent[1]->Fill(selelec_mom,allweight);
	else
	  CCSignalNeutrinoParent[2]->Fill(selelec_mom,allweight);
      }
      else{
	CCSignalNeutrinoParent[3]->Fill(selelec_mom,allweight);
      }

      // Fill neutrino interactions
      if(abs(nu_truereac) == 1){
	CCSignalInteractions[0]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[0]->Fill(selelec_costheta,allweight);
      }
      else if(abs(nu_truereac) == 2){
	CCSignalInteractions[1]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[1]->Fill(selelec_costheta,allweight);
      }
      else if(abs(nu_truereac) == 16){
	CCSignalInteractions[2]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[2]->Fill(selelec_costheta,allweight);
      }
      else if(abs(nu_truereac) > 16){
	CCSignalInteractions[3]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[3]->Fill(selelec_costheta,allweight);
      }
      else{
	CCSignalInteractions[4]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[4]->Fill(selelec_costheta,allweight);
      }

      // Electron momentum and angular resolution
      ElecMomRes[0]->Fill((selelec_true_mom-selelec_mom)/selelec_true_mom,allweight);
      ElecMomRes[1]->Fill((selelec_true_mom-selelec_mom)/selelec_true_mom,allweight);
      ElecAngRes[0]->Fill((truelepton_costheta_nuDir-selelec_costheta)/truelepton_costheta_nuDir,allweight);
      ElecAngRes[1]->Fill((truelepton_costheta_nuDir-selelec_costheta)/truelepton_costheta_nuDir,allweight);
      ElecMomRes2D[0]->Fill(selelec_true_mom,selelec_mom,allweight);
      ElecMomRes2D[1]->Fill(selelec_true_mom,selelec_mom,allweight);
      ElecAngRes2D[0]->Fill(acos(truelepton_costheta_nuDir),acos(selelec_costheta),allweight);
      ElecAngRes2D[1]->Fill(acos(truelepton_costheta_nuDir),acos(selelec_costheta),allweight);

      // Efficiency histograms
      SEffTrue->Fill(truelepton_mom,wnopot);
      SNEffTrue->Fill(nu_trueE/1000.0,wnopot);
      SPurTrue->Fill(selelec_true_mom,wnopot);
      PurTrue->Fill(selelec_true_mom,wnopot);
      SNPurTrue->Fill(nu_trueE/1000.0,wnopot);
      NPurTrue->Fill(nu_trueE/1000.0,wnopot);
      SAngTrue->Fill(acos(truelepton_costheta_nuDir),wnopot);
      SPurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
      PurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
      SPosTrue->Fill(truelepton_pos[2],wnopot);
      SEffTrueCC0Pi->Fill(truelepton_mom, wnopot);
      SAngTrueCC0Pi->Fill(truelepton_costheta_nuDir, wnopot);
      MomTheta2D[0]->Fill(p,theta,allweight);
      
      // Efficiency plots for neut-genie comparisons
      if(truelepton_costheta_nuDir > xsangparnum[0] && truelepton_mom > MINMOMENTUM){
	SignalSelMom->Fill(truelepton_mom, wnopot);
	SignalSelAng->Fill(truelepton_costheta_nuDir, wnopot);
	TrueMomCosSelec->Fill(truelepton_mom, truelepton_costheta_nuDir, wnopot);
      }
      
      if(truelepton_costheta_nuDir > xsangparnum[0] && truelepton_costheta_nuDir <= xsangparnum[1]){
	SignalSelMom2->Fill(truelepton_mom, wnopot);
	SignalSelMom4->Fill(truelepton_mom, wnopot);
      }
      else if(truelepton_costheta_nuDir > xsangparnum[1] && truelepton_costheta_nuDir < xsangparnum[2]){
	SignalSelMom3->Fill(truelepton_mom, wnopot);
	SignalSelMom5->Fill(truelepton_mom, wnopot);
      }
      
    }
    else if(nuesimpletopo == 2){ // nue CCother
      CCHnPi[0]->Fill(selelec_costheta,allweight);
      CCHnPi[1]->Fill(selelec_Q2recQE,allweight);
      CCHnPi[2]->Fill(pt/selelec_mom,allweight);
      CCHnPi[3]->Fill(selelec_startpos[2],allweight);
      CCHnPi[4]->Fill(acos(selelec_costheta),allweight);
      CCHnPi[5]->Fill(selelec_mom,allweight);
      CCHnPi[6]->Fill(pt,allweight);
      if(selelec_ToF_ECal_FGD1 != -999)
	CCHnPi[7]->Fill(selelec_ToF_ECal_FGD1,allweight);
      if(selelec_ToF_DsECal_FGD1 != -999)
	CCHnPi[8]->Fill(selelec_ToF_DsECal_FGD1,allweight);
      if(accum_level == 3 && selelec_ecalemene != -999)
	CCHnPi[9]->Fill(selelec_likeelec,allweight);
      if(accum_level == 6 && selelec_ecalemene != -999)
	CCHnPi[10]->Fill(selelec_ecalemene/selelec_mom,allweight);

      // Fill neutrino parent
      if(nuesimpleparent == 1){
	CCSignalNeutrinoParent[0]->Fill(selelec_mom,allweight);
      }
      else if(nuesimpleparent == 2){
	if(abs(NuParentPDGRaw) == 130)
	  CCSignalNeutrinoParent[1]->Fill(selelec_mom,allweight);
	else
	  CCSignalNeutrinoParent[2]->Fill(selelec_mom,allweight);
      }
      else{
	CCSignalNeutrinoParent[3]->Fill(selelec_mom,allweight);
      }

      // Fill neutrino interactions
      if(abs(nu_truereac) == 1){
	CCSignalInteractions[0]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[0]->Fill(selelec_costheta,allweight);
      }
      else if(abs(nu_truereac) == 2){
	CCSignalInteractions[1]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[1]->Fill(selelec_costheta,allweight);
      }
      else if(abs(nu_truereac) == 16){
	CCSignalInteractions[2]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[2]->Fill(selelec_costheta,allweight);
      }
      else if(abs(nu_truereac) > 16){
	CCSignalInteractions[3]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[3]->Fill(selelec_costheta,allweight);
      }
      else{
	CCSignalInteractions[4]->Fill(selelec_mom,allweight);
	CCSignalInteractionsAngle[4]->Fill(selelec_costheta,allweight);
      }

      // Electron momentum and angular resolution
      ElecMomRes[0]->Fill((selelec_true_mom-selelec_mom)/selelec_true_mom,allweight);
      ElecMomRes[1]->Fill((selelec_true_mom-selelec_mom)/selelec_true_mom,allweight);
      ElecAngRes[0]->Fill((truelepton_costheta_nuDir-selelec_costheta)/truelepton_costheta_nuDir,allweight);
      ElecAngRes[1]->Fill((truelepton_costheta_nuDir-selelec_costheta)/truelepton_costheta_nuDir,allweight);
      ElecMomRes2D[0]->Fill(selelec_true_mom,selelec_mom,allweight);
      ElecMomRes2D[1]->Fill(selelec_true_mom,selelec_mom,allweight);
      ElecAngRes2D[0]->Fill(acos(truelepton_costheta_nuDir),acos(selelec_costheta),allweight);
      ElecAngRes2D[1]->Fill(acos(truelepton_costheta_nuDir),acos(selelec_costheta),allweight);

      // Efficiency histograms
      SEffTrue->Fill(truelepton_mom,wnopot);
      SNEffTrue->Fill(nu_trueE/1000.0,wnopot);
      SPurTrue->Fill(selelec_true_mom,wnopot);
      PurTrue->Fill(selelec_true_mom,wnopot);
      SNPurTrue->Fill(nu_trueE/1000.0,wnopot);
      NPurTrue->Fill(nu_trueE/1000.0,wnopot);
      SAngTrue->Fill(acos(truelepton_costheta_nuDir),wnopot);
      SPurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
      PurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
      SPosTrue->Fill(truelepton_pos[2],wnopot);
      SEffTrueCCOther->Fill(truelepton_mom, wnopot);
      SAngTrueCCOther->Fill(truelepton_costheta_nuDir, wnopot);
      MomTheta2D[0]->Fill(p,theta,allweight);
      
      // Efficiency plots for neut-genie comparisons
      if(truelepton_costheta_nuDir > xsangparnum[0] && truelepton_mom > MINMOMENTUM){
	SignalSelMom->Fill(truelepton_mom, wnopot);
	SignalSelAng->Fill(truelepton_costheta_nuDir, wnopot);
	TrueMomCosSelec->Fill(truelepton_mom, truelepton_costheta_nuDir, wnopot);
      }
      
      if(truelepton_costheta_nuDir > xsangparnum[0] && truelepton_costheta_nuDir <= xsangparnum[1]){
	SignalSelMom2->Fill(truelepton_mom, wnopot);
	SignalSelMom4->Fill(truelepton_mom, wnopot);
      }
      else if(truelepton_costheta_nuDir > xsangparnum[1] && truelepton_costheta_nuDir < xsangparnum[2]){
	SignalSelMom3->Fill(truelepton_mom, wnopot);
	SignalSelMom5->Fill(truelepton_mom, wnopot);
      }
      
    }
    else if(nuesimpletopo == 3){ // gamma background
      GammaH[0]->Fill(selelec_costheta,allweight);
      GammaH[1]->Fill(selelec_Q2recQE,allweight);
      GammaH[2]->Fill(pt/selelec_mom,allweight);
      GammaH[3]->Fill(selelec_startpos[2],allweight);
      GammaH[4]->Fill(acos(selelec_costheta),allweight);
      GammaH[5]->Fill(selelec_mom,allweight);
      GammaH[6]->Fill(pt,allweight);
      if(selelec_ToF_ECal_FGD1 != -999)
	GammaH[7]->Fill(selelec_ToF_ECal_FGD1,allweight);
      if(selelec_ToF_DsECal_FGD1 != -999)
	GammaH[8]->Fill(selelec_ToF_DsECal_FGD1,allweight);
      if(accum_level == 3 && selelec_ecalemene != -999)
	GammaH[9]->Fill(selelec_likeelec,allweight);
      if(accum_level == 6 && selelec_ecalemene != -999)
	GammaH[10]->Fill(selelec_ecalemene/selelec_mom,allweight);

      CCSignalNeutrinoParent[4]->Fill(selelec_mom,allweight);

      if(reaction != 7 && reaction != 777){ // In FV , 777 -> sand
	if(abs(nu_truereac) <= 30){ // CC
	  if(NTruePi0 == 1){
	    GammaInteraction[0]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[0]->Fill(selelec_costheta,allweight);
	  }
	  else if(NTruePi0 > 1){
	    GammaInteraction[1]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[1]->Fill(selelec_costheta,allweight);
	  }
	  else{
	    GammaInteraction[2]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[2]->Fill(selelec_costheta,allweight);
	  }
	}
	else{ // NC
	  if(NTruePi0 == 1){
	    GammaInteraction[3]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[3]->Fill(selelec_costheta,allweight);
	  }
	  else if(NTruePi0 > 1){
	    GammaInteraction[4]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[4]->Fill(selelec_costheta,allweight);
	  }
	  else{
	    GammaInteraction[5]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[5]->Fill(selelec_costheta,allweight);
	  }
	}
      }
      else{
	if(detector < 2 && detector > -1){ // OOFV but in FGD
	  if(selelec_FGD == detector){
	    GammaInteraction[6]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[6]->Fill(selelec_costheta,allweight);
	  }
	  else{
	    GammaInteraction[7]->Fill(selelec_mom,allweight);
	    GammaInteractionAngle[7]->Fill(selelec_costheta,allweight);
	  }

	  if(detector == 0)
	    GammaDetector[0]->Fill(selelec_mom,allweight);
	  else if(detector == 1)
	    GammaDetector[1]->Fill(selelec_mom,allweight);
	}
	else{ // OOFGD
	  GammaInteraction[7]->Fill(selelec_mom,allweight);
	  GammaInteractionAngle[7]->Fill(selelec_costheta,allweight);

	  if(detector == 2)
	    GammaDetector[2]->Fill(selelec_mom,allweight);
	  else if(detector == 3)
	    GammaDetector[3]->Fill(selelec_mom,allweight);
	  else if(detector == 4)
	    GammaDetector[4]->Fill(selelec_mom,allweight);
	  else if(detector == 5)
	    GammaDetector[5]->Fill(selelec_mom,allweight);
	  else if(detector == 6)
	    GammaDetector[6]->Fill(selelec_mom,allweight);
	  else if(detector == 7)
	    GammaDetector[7]->Fill(selelec_mom,allweight);
	  else if(detector == 8)
	    GammaDetector[8]->Fill(selelec_mom,allweight);
	  else if(detector == 9)
	    GammaDetector[9]->Fill(selelec_mom,allweight);
	  else if(detector == 777)
	    GammaDetector[10]->Fill(selelec_mom,allweight);
	  else if(detector >= 10 || detector < 0)
	    GammaDetector[11]->Fill(selelec_mom,allweight);
	}

	if(selelec_FGD != detector){
	  if(target == 1)
	    GammaOOFGDTarget[0]->Fill(selelec_mom,allweight);
	  else if(target == 6)
	    GammaOOFGDTarget[1]->Fill(selelec_mom,allweight);
	  else if(target == 8)
	    GammaOOFGDTarget[2]->Fill(selelec_mom,allweight);
	  else if(target == 13)
	    GammaOOFGDTarget[3]->Fill(selelec_mom,allweight);
	  else if(target == 26)
	    GammaOOFGDTarget[4]->Fill(selelec_mom,allweight);
	  else if(target == 29)
	    GammaOOFGDTarget[5]->Fill(selelec_mom,allweight);
	  else if(target == 30)
	    GammaOOFGDTarget[6]->Fill(selelec_mom,allweight);
	  else if(target == 82)
	    GammaOOFGDTarget[7]->Fill(selelec_mom,allweight);
	  else if(target == 777) // sand
	    GammaOOFGDTarget[8]->Fill(selelec_mom,allweight);
	  else
	    GammaOOFGDTarget[9]->Fill(selelec_mom,allweight);
	}
      }

      ElecMomRes[1]->Fill((selelec_true_mom-selelec_mom)/selelec_true_mom);
      ElecAngRes[1]->Fill((truelepton_costheta_nuDir-selelec_costheta)/truelepton_costheta_nuDir);
      ElecMomRes2D[1]->Fill(selelec_true_mom,selelec_mom);
      ElecAngRes2D[1]->Fill(acos(truelepton_costheta_nuDir),acos(selelec_costheta),allweight);
      MomTheta2D[1]->Fill(p,theta,allweight);

      // Purities
      PurTrue->Fill(selelec_true_mom,wnopot);
      NPurTrue->Fill(nu_trueE/1000.0,wnopot);
      PurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
    }
    else if(nuesimpletopo == 4){ // muon background
      MuonBkg[0]->Fill(selelec_costheta,allweight);
      MuonBkg[1]->Fill(selelec_Q2recQE,allweight);
      MuonBkg[2]->Fill(pt/selelec_mom,allweight);
      MuonBkg[3]->Fill(selelec_startpos[2],allweight);
      MuonBkg[4]->Fill(acos(selelec_costheta),allweight);
      MuonBkg[5]->Fill(selelec_mom,allweight);
      MuonBkg[6]->Fill(pt,allweight);
      if(selelec_ToF_ECal_FGD1 != -999)
	MuonBkg[7]->Fill(selelec_ToF_ECal_FGD1,allweight);
      if(selelec_ToF_DsECal_FGD1 != -999)
	MuonBkg[8]->Fill(selelec_ToF_DsECal_FGD1,allweight);
      if(accum_level == 3 && selelec_ecalemene != -999)
	MuonBkg[9]->Fill(selelec_likeelec,allweight);
      if(accum_level == 6 && selelec_ecalemene != -999)
	MuonBkg[10]->Fill(selelec_ecalemene/selelec_mom,allweight);

      CCSignalNeutrinoParent[5]->Fill(selelec_mom,allweight);

      // Muon true channels
      if(reaction != 7){
	if(abs(nu_truereac) < 10){
	  MuonBkgInteractions[0]->Fill(selelec_mom,allweight);
	  MuonBkgInteractionsAngle[0]->Fill(selelec_costheta,allweight);
	}
	else if(abs(nu_truereac) == 16){
	  MuonBkgInteractions[2]->Fill(selelec_mom,allweight);
	  MuonBkgInteractionsAngle[2]->Fill(selelec_costheta,allweight);
	}
	else if(abs(nu_truereac) > 10 && abs(nu_truereac) < 26){
	  MuonBkgInteractions[1]->Fill(selelec_mom,allweight);
	  MuonBkgInteractionsAngle[1]->Fill(selelec_costheta,allweight);
	}
	else if(abs(nu_truereac) == 26){
	  MuonBkgInteractions[3]->Fill(selelec_mom,allweight);
	  MuonBkgInteractionsAngle[3]->Fill(selelec_costheta,allweight);
	}
	else{
	  MuonBkgInteractions[4]->Fill(selelec_mom,allweight);
	  MuonBkgInteractionsAngle[5]->Fill(selelec_costheta,allweight);
	}
      }
      else{
	MuonBkgInteractions[5]->Fill(selelec_mom,allweight);
	MuonBkgInteractionsAngle[5]->Fill(selelec_costheta,allweight);
      }

      // Purities
      PurTrue->Fill(selelec_true_mom,wnopot);
      NPurTrue->Fill(nu_trueE/1000.0,wnopot);
      PurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
      MomTheta2D[2]->Fill(p,theta,allweight);
    }
    else if(nuesimpletopo == 8){ // proton background
      ProtonBkg[0]->Fill(selelec_costheta,allweight);
      ProtonBkg[1]->Fill(selelec_Q2recQE,allweight);
      ProtonBkg[2]->Fill(pt/selelec_mom,allweight);
      ProtonBkg[3]->Fill(selelec_startpos[2],allweight);
      ProtonBkg[4]->Fill(acos(selelec_costheta),allweight);
      ProtonBkg[5]->Fill(selelec_mom,allweight);
      ProtonBkg[6]->Fill(pt,allweight);
      if(selelec_ToF_ECal_FGD1 != -999)
	ProtonBkg[7]->Fill(selelec_ToF_ECal_FGD1,allweight);
      if(selelec_ToF_DsECal_FGD1 != -999)
	ProtonBkg[8]->Fill(selelec_ToF_DsECal_FGD1,allweight);
      if(accum_level == 3 && selelec_ecalemene != -999)
	ProtonBkg[9]->Fill(selelec_likeelec,allweight);
      if(accum_level == 6 && selelec_ecalemene != -999)
	ProtonBkg[10]->Fill(selelec_ecalemene/selelec_mom,allweight);

      CCSignalNeutrinoParent[6]->Fill(selelec_mom,allweight);

      // Proton true channels
      if(reaction != 7){
	if(abs(nu_truereac) < 10){
	  ProtonBkgInteractions[0]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[0]->Fill(selelec_costheta,allweight);
	}
	else if(abs(nu_truereac) > 10 && abs(nu_truereac) < 26){
	  ProtonBkgInteractions[1]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[1]->Fill(selelec_costheta,allweight);
	}
	else if(abs(nu_truereac) == 26){
	  ProtonBkgInteractions[2]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[2]->Fill(selelec_costheta,allweight);
	}
	else if(abs(nu_truereac) > 26 && abs(nu_truereac) < 45){
	  ProtonBkgInteractions[3]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[3]->Fill(selelec_costheta,allweight);
	}
	else if(abs(nu_truereac) == 46){
	  ProtonBkgInteractions[4]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[4]->Fill(selelec_costheta,allweight);
	}
	else{
	  ProtonBkgInteractions[5]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[5]->Fill(selelec_costheta,allweight);
	}
      }
      else{
	if(detector < 2){
	  ProtonBkgInteractions[6]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[6]->Fill(selelec_costheta,allweight);
	}
	else{
	  ProtonBkgInteractions[7]->Fill(selelec_mom,allweight);
	  ProtonBkgInteractionsAngle[7]->Fill(selelec_costheta,allweight);
	}
      }

      // Purities
      PurTrue->Fill(selelec_true_mom,wnopot);
      NPurTrue->Fill(nu_trueE/1000.0,wnopot);
      PurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
      MomTheta2D[2]->Fill(p,theta,allweight);
    }
    else{ // other background
      OtherBkgH[0]->Fill(selelec_costheta,allweight);
      OtherBkgH[1]->Fill(selelec_Q2recQE,allweight);
      OtherBkgH[2]->Fill(pt/selelec_mom,allweight);
      OtherBkgH[3]->Fill(selelec_startpos[2],allweight);
      OtherBkgH[4]->Fill(acos(selelec_costheta),allweight);
      OtherBkgH[5]->Fill(selelec_mom,allweight);
      OtherBkgH[6]->Fill(pt,allweight);
      if(selelec_ToF_ECal_FGD1 != -999)
	OtherBkgH[7]->Fill(selelec_ToF_ECal_FGD1,allweight);
      if(selelec_ToF_DsECal_FGD1 != -999)
	OtherBkgH[8]->Fill(selelec_ToF_DsECal_FGD1,allweight);
      if(accum_level == 3 && selelec_ecalemene != -999)
	OtherBkgH[9]->Fill(selelec_likeelec,allweight);
      if(accum_level == 6 && selelec_ecalemene != -999)
	OtherBkgH[10]->Fill(selelec_ecalemene/selelec_mom,allweight);

      CCSignalNeutrinoParent[7]->Fill(selelec_mom,allweight);

      if(particle == 211 || particle == -211){
	OtherBkgBreakdown[0]->Fill(selelec_mom,allweight);
	OtherBkgBreakdownAngle[0]->Fill(selelec_costheta,allweight);
      }
      else if(particle == 2212){
	OtherBkgBreakdown[1]->Fill(selelec_mom,allweight);
	OtherBkgBreakdownAngle[1]->Fill(selelec_costheta,allweight);
      }
      else if(particle == 777){
	OtherBkgBreakdown[2]->Fill(selelec_mom,allweight);
	OtherBkgBreakdownAngle[2]->Fill(selelec_costheta,allweight);
      }
      else if(particle == 11 || particle == -11){
	ElecMomRes[1]->Fill((selelec_true_mom-selelec_mom)/selelec_true_mom,allweight);
	ElecAngRes[1]->Fill((truelepton_costheta_nuDir-selelec_costheta)/truelepton_costheta_nuDir,allweight);
	ElecMomRes2D[1]->Fill(selelec_true_mom,selelec_mom,allweight);
	ElecAngRes2D[1]->Fill(acos(truelepton_costheta_nuDir),acos(selelec_costheta),allweight);

	if(parent == 111){
	  OtherBkgBreakdown[3]->Fill(selelec_mom,allweight);
	  OtherBkgBreakdownAngle[3]->Fill(selelec_costheta,allweight);
	}
	else if(abs(parent) == 13 || abs(parent) == 211){
	  OtherBkgBreakdown[4]->Fill(selelec_mom,allweight);
	  OtherBkgBreakdownAngle[4]->Fill(selelec_costheta,allweight);
	}
	else if(parent == 0 && abs(nu_pdg) == 12){
	  OtherBkgBreakdown[5]->Fill(selelec_mom,allweight);
	  OtherBkgBreakdownAngle[5]->Fill(selelec_costheta,allweight);
	}
	else if(parent == 22){
	  OtherBkgBreakdown[6]->Fill(selelec_mom,allweight);
	  OtherBkgBreakdownAngle[6]->Fill(selelec_costheta,allweight);
	}
	else{
	  OtherBkgBreakdown[7]->Fill(selelec_mom,allweight);
	  OtherBkgBreakdownAngle[7]->Fill(selelec_costheta,allweight);
	}
      }
      
      // Purities
      PurTrue->Fill(selelec_true_mom,wnopot);
      NPurTrue->Fill(nu_trueE/1000.0,wnopot);
      PurAngTrue->Fill(acos(selelec_true_costheta),wnopot);
      MomTheta2D[2]->Fill(p,theta,allweight);
    }

  }

  //mcFile->Close();

}

// ----------------------------------------------------------------------------
void FillMCHistograms(TString mcfile, TString datafile, bool issand=false){

  FillMCHistograms(mcfile, GetPOTFromFile(datafile), issand);

}

// ----------------------------------------------------------------------------
void DefineHistograms(Int_t whichfgd){

  TString histname[7] = {"CC0Pi","CCOther","GammaBkg","MuonBkg","ProtonBkg","OtherBkg","Data"};
  Int_t bin  = 18; Int_t xmin  = 0; Int_t xmax  = 5400; Int_t xmax2  = 1.0; Int_t binang = 16;
  Double_t xmax3 = 1.6;//3.15;

  for(Int_t j = 0; j < 5; j++){
    if(j == 3){
      if(whichfgd == 0){
	CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),175,100,450);
	CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),175,100,450);
	GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),175,100,450);
	MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),175,100,450);
	ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),175,100,450);
	OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),175,100,450);
	DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),175,100,450);
      }
      else if(whichfgd == 1){
	CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),200,1450,1850);
	CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),200,1450,1850);
	GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),200,1450,1850);
	MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),200,1450,1850);
	ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),200,1450,1850);
	OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),200,1450,1850);
	DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),200,1450,1850);
      }
    }
    else if(j == 4){
      CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),binang,xmin,xmax3);
      CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),binang,xmin,xmax3);
      GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),binang,xmin,xmax3);
      MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),binang,xmin,xmax3);
      ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),binang,xmin,xmax3);
      OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),binang,xmin,xmax3);
      DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),binang,xmin,xmax3);
    }
    else{
      CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),bin+2,xmin,xmax2);
      CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),bin+2,xmin,xmax2);
      GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),bin+2,xmin,xmax2);
      MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),bin+2,xmin,xmax2);
      ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),bin+2,xmin,xmax2);
      OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),bin+2,xmin,xmax2);
      DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),bin+2,xmin,xmax2);
    }
  }

  if(isgamma){
    bin = 7;
    xmax = 2100;
  }

  for(Int_t j = 5; j < n; j++){
    if(j == 6){
      CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),bin,xmin,2700.0);
      CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),bin,xmin,2700.0);
      GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),bin,xmin,2700.0);
      MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),bin,xmin,2700.0);
      ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),bin,xmin,2700.0);
      OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),bin,xmin,2700.0);
      DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),bin,xmin,2700.0);
    }
    else if(j == 7 || j == 8){
      CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),40,-20,20.0);
      CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),40,-20,20.0);
      GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),40,-20,20.0);
      MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),40,-20,20.0);
      ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),40,-20,20.0);
      OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),40,-20,20.0);
      DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),40,-20,20.0);
    }
    else if(j == 9){
      CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),51,0,1.02);
      CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),51,0,1.02);
      GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),51,0,1.02);
      MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),51,0,1.02);
      ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),51,0,1.02);
      OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),51,0,1.02);
      DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),51,0,1.02);
    }
    else if(j == 10){
      CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),100,0,5);
      CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),100,0,5);
      GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),100,0,5);
      MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),100,0,5);
      ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),100,0,5);
      OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),100,0,5);
      DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),100,0,5);
    }
    else{
      CCH[j]       = new TH1D(Form("%s_%i",histname[0].Data(),j),Form("%s_%i",histname[0].Data(),j),bin,xmin,xmax);
      CCHnPi[j]    = new TH1D(Form("%s_%i",histname[1].Data(),j),Form("%s_%i",histname[1].Data(),j),bin,xmin,xmax);
      GammaH[j]    = new TH1D(Form("%s_%i",histname[2].Data(),j),Form("%s_%i",histname[2].Data(),j),bin,xmin,xmax);
      MuonBkg[j]   = new TH1D(Form("%s_%i",histname[3].Data(),j),Form("%s_%i",histname[3].Data(),j),bin,xmin,xmax);
      ProtonBkg[j] = new TH1D(Form("%s_%i",histname[4].Data(),j),Form("%s_%i",histname[4].Data(),j),bin,xmin,xmax);
      OtherBkgH[j] = new TH1D(Form("%s_%i",histname[5].Data(),j),Form("%s_%i",histname[5].Data(),j),bin,xmin,xmax);
      DataH[j]     = new TH1D(Form("%s_%i",histname[6].Data(),j),Form("%s_%i",histname[6].Data(),j),bin,xmin,xmax);
    }
  }

  for(Int_t j = 0; j < 3; j++){
    MomTheta2D[j] = new TH2D(Form("MomTheta2D_%i",j),Form("MomTheta2D_%i",j),bin,xmin,xmax,binang,xmin,xmax3);
  }
  
  TString nuparentname[9] = {"NeutrinoParentMuon","NeutrinoParentK0","NeutrinoParentKaon","NeutrinoParentOther", "NeutrinoParentGamma", "NeutrinoParentMuonBkg", "NeutrinoParentProton", "NeutrinoParentOtherBkg", "DataParent"}; 
  for(Int_t j = 0; j < 9; j++){
    CCSignalNeutrinoParent[j] = new TH1D(nuparentname[j].Data(),nuparentname[j].Data(),bin,xmin,xmax);
  }
  
  TString nuinteractionsname[5] = {"CCQEL","CCMEC","CCCOH","CCDIS","CCRES"}; 
  for(Int_t j = 0; j < 5; j++){
    CCSignalInteractions[j] = new TH1D(nuinteractionsname[j].Data(),nuinteractionsname[j].Data(),bin,xmin,xmax);
    CCSignalInteractionsAngle[j] = new TH1D(Form("%s_angle",nuinteractionsname[j].Data()),Form("%s_angle",nuinteractionsname[j].Data()),bin+2,xmin,xmax2);
  }
  
  TString gammaintname[8] = {"GammaCC1pi0","GammaCCnPi0","GammaCC0pi0","GammaNC1pi0","GammaNCnPi0","GammaNC0Pi0","GammaOOFV","GammaOOFGD"};
  for(Int_t j = 0; j < 8; j++){
    GammaInteraction[j]      =  new TH1D(gammaintname[j].Data(),gammaintname[j].Data(),bin,xmin,xmax);
    GammaInteractionAngle[j] =  new TH1D(Form("%s_angle",gammaintname[j].Data()),Form("%s_angle",gammaintname[j].Data()),bin+2,xmin,xmax2);
  }
  
  TString gammadetname[12] = {"GammaFGD1","GammaFGD2","GammaP0D","GammaDsECal","GammaBrECal","GammaP0DECal","GammaTPC1","GammaTPC2","GammaTPC3","GammaSMRD","GammaSand","GammaOther"};
  for(Int_t j = 0; j < 12; j++){
    GammaDetector[j] =  new TH1D(gammadetname[j].Data(),gammadetname[j].Data(),bin,xmin,xmax);
  }
  
  TString gammatargetname[10] = {"GammaHydrogen","GammaCarbon","GammaOxygen","GammaAluminium","GammaIron","GammaCopper","GammaZinc","GammaLead","GammaTargetSand","GammaTargetOther"};
  for(Int_t j = 0; j < 10; j++){
    GammaOOFGDTarget[j] =  new TH1D(gammatargetname[j].Data(),gammatargetname[j].Data(),bin,xmin,xmax);
  }
  
  TString muonintname[6] = {"MuonCCQEL","MuonCCRES","MuonCCCOH","MuonCCDIS","MuonCCOther","MuonOOFV"};
  for(Int_t j = 0; j < 6; j++){
    MuonBkgInteractions[j]      =  new TH1D(muonintname[j].Data(),muonintname[j].Data(),bin,xmin,xmax);
    MuonBkgInteractionsAngle[j] =  new TH1D(Form("%s_angle",muonintname[j].Data()),Form("%s_angle",muonintname[j].Data()),bin+2,xmin,xmax2);
  }

  TString protonintname[8] = {"ProtonCCQEL","ProtonCCRES","ProtonCCDIS","ProtonNCRES","ProtonNCDIS","ProtonNCQEL","ProtonOOFV","ProtonOOFGD"};
  for(Int_t j = 0; j < 8; j++){
    ProtonBkgInteractions[j]      =  new TH1D(protonintname[j].Data(),protonintname[j].Data(),bin,xmin,xmax);
    ProtonBkgInteractionsAngle[j] =  new TH1D(Form("%s_angle",protonintname[j].Data()),Form("%s_angle",protonintname[j].Data()),bin+2,xmin,xmax2);
  }

  TString otherbkgname[8] = {"OtherPion","OtherPtoton","OtherSand","OtherPi0","OtherMuPi","OtherNuE","OtherGamma","OtherOther"};
  for(Int_t j = 0; j < 8; j++){
    OtherBkgBreakdown[j]      =  new TH1D(otherbkgname[j].Data(),otherbkgname[j].Data(),bin,xmin,xmax);
    OtherBkgBreakdownAngle[j] =  new TH1D(Form("%s_angle",otherbkgname[j].Data()),Form("%s_angle",otherbkgname[j].Data()),bin+2,xmin,xmax2);
  }
  
  TString elecresolname[2] = {"MomSignalElec","MomAllElec"};
  TString elecresol2Dname[2] = {"MomSignalElec2D","MomAllElec2D"};
  for(Int_t j = 0; j < 2; j++){
    ElecMomRes[j] =  new TH1D(elecresolname[j].Data(),elecresolname[j].Data(),4*bin,-xmax2,xmax2);
    ElecMomRes2D[j] =  new TH2D(elecresol2Dname[j].Data(),elecresol2Dname[j].Data(),2*bin,xmin,xmax,2*bin,xmin,xmax);
  }

  elecresolname[0] = "AngSignalElec"; elecresolname[1] = "AngAllElec";
  elecresol2Dname[0] = "AngSignalElec2D"; elecresol2Dname[1] = "AngAllElec2D";
  for(Int_t j = 0; j < 2; j++){
    ElecAngRes[j] =  new TH1D(elecresolname[j].Data(),elecresolname[j].Data(),32*bin,-xmax2,xmax2);
    ElecAngRes2D[j] =  new TH2D(elecresol2Dname[j].Data(),elecresol2Dname[j].Data(),2*binang,xmin,xmax3,2*binang,xmin,xmax3);
  }
  
  // Efficiency histograms
  const int nn = 14;
  Double_t parnum[nn-1] = {0.0,300,600,900,1200,1500,1800,2100,2400,2700,3000,4200,5400};
  Double_t newparnum[nn] = {0.0,0.3,0.6,0.9,1.2,1.5,1.8,2.1,2.4,2.7,3.0,4.2,5.4,10.0};
  Double_t angnum[nn+1] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.6,3.14};
  //Double_t angnum[nn] = {-1,0,0.2,0.4,0.6,0.7,0.8,0.9,1};

  EffTrue                     = new TH1D("EffTrue"                   ,"EffTrue"                  ,nn-1-1,parnum);
  PurTrue                     = new TH1D("PurTrue"                   ,"PurTrue"                  ,nn-1-1,parnum);
  SEffTrue                    = new TH1D("SEffTrue"                  ,"SEffTrue"                 ,nn-1-1,parnum);
  SPurTrue                    = new TH1D("SPurTrue"                  ,"SPurTrue"                 ,nn-1-1,parnum);
  NEffTrue                    = new TH1D("NEffTrue"                  ,"NEffTrue"                 ,nn-1,newparnum);
  NPurTrue                    = new TH1D("NPurTrue"                  ,"NPurTrue"                 ,nn-1,newparnum);
  SNEffTrue                   = new TH1D("SNEffTrue"                 ,"SNEffTrue"                ,nn-1,newparnum);
  SNPurTrue                   = new TH1D("SNPurTrue"                 ,"SNPurTrue"                ,nn-1,newparnum);

  AngTrue                     = new TH1D("AngTrue"                   ,"AngTrue"                  ,nn-1+1,angnum);
  SAngTrue                    = new TH1D("SAngTrue"                  ,"SAngTrue"                 ,nn-1+1,angnum);
  PurAngTrue                  = new TH1D("PurAngTrue"                ,"PurAngTrue"               ,nn-1+1,angnum);
  SPurAngTrue                 = new TH1D("SPurAngTrue"               ,"SPurAngTrue"              ,nn-1+1,angnum);

  EffTrue2                    = new TH1D("EffTrue2"                  ,"EffTrue2"                 ,nn-1-1,parnum);
  SEffTrue2                   = new TH1D("SEffTrue2"                 ,"SEffTrue2"                ,nn-1-1,parnum);

  const int nnn = 7;
  Double_t posnum1[nnn] = {150,200,250,300,350,400,450};
  const int nnnn = 9;
  Double_t posnum2[nnnn] = {1450,1500,1550,1600,1650,1700,1750,1800,1850};
  if(whichfgd == 0){
    PosTrue                     = new TH1D("PosTrue"                   ,"PosTrue"                  ,nnn-1,posnum1);
    SPosTrue                    = new TH1D("SPosTrue"                  ,"SPosTrue"                 ,nnn-1,posnum1);
  }
  else{
    PosTrue                     = new TH1D("PosTrue"                   ,"PosTrue"                  ,nnnn-1,posnum2);
    SPosTrue                    = new TH1D("SPosTrue"                  ,"SPosTrue"                 ,nnnn-1,posnum2);
  }

  EffTrueCC0Pi                = new TH1D("EffTrueCC0Pi"               ,"EffTrueCC0Pi"            ,nn-1-1,parnum);
  EffTrueCCOther              = new TH1D("EffTrueCCOther"             ,"EffTrueCCOther"          ,nn-1-1,parnum);
  SEffTrueCC0Pi               = new TH1D("SEffTrueCC0Pi"              ,"SEffTrueCC0Pi"           ,nn-1-1,parnum);
  SEffTrueCCOther             = new TH1D("SEffTrueCCOther"            ,"SEffTrueCCOther"         ,nn-1-1,parnum);
  AngTrueCC0Pi                = new TH1D("AngTrueCC0Pi"               ,"AngTrueCC0Pi"            ,nn-1,angnum);
  AngTrueCCOther              = new TH1D("AngTrueCCOther"             ,"AngTrueCCOther"          ,nn-1,angnum);
  SAngTrueCC0Pi               = new TH1D("SAngTrueCC0Pi"              ,"SAngTrueCC0Pi"           ,nn-1,angnum);
  SAngTrueCCOther             = new TH1D("SAngTrueCCOther"            ,"SAngTrueCCOther"         ,nn-1,angnum);

  SEffTrueEventsCC0Pi         = new TH1D("SEffTrueEventsCC0Pi"        ,"SEffTrueEventsCC0Pi"     ,33,0,9999);
  SEffTrueEventsCCOther       = new TH1D("SEffTrueEventsCCOther"      ,"SEffTrueEventsCCOther"   ,33,0,9999);
  SAngTrueEventsCC0Pi         = new TH1D("SAngTrueEventsCC0Pi"        ,"SAngTrueEventsCC0Pi"     ,20,-1,1);
  SAngTrueEventsCCOther       = new TH1D("SAngTrueEventsCCOther"      ,"SAngTrueEventsCCOther"   ,20,-1,1);
  //SEffTrueEventsCCInc         = new TH1D("SEffTrueEventsCCInc"        ,"SEffTrueEventsCCInc"     ,33,0,9999);
  //SAngTrueEventsCCInc         = new TH1D("SAngTrueEventsCCInc"        ,"SAngTrueEventsCCInc"     ,20,-1,1);
  SEffTrueEventsCCInc         = new TH1D("SEffTrueEventsCCInc"        ,"SEffTrueEventsCCInc"     ,nn-1-1,parnum);
  SAngTrueEventsCCInc         = new TH1D("SAngTrueEventsCCInc"        ,"SAngTrueEventsCCInc"     ,nn-1+1,angnum);

  SignalSelMom                = new TH1D("SignalSelMom"               ,"SignalSelMom"            ,n1-1,momparnum);
  TruthSelMom                 = new TH1D("TruthSelMom"                ,"TruthSelMom"             ,n1-1,momparnum);

  SignalSelMom2               = new TH1D("SignalSelMom2"              ,"SignalSelMom2"           ,n5-1,momparnum2);
  TruthSelMom2                = new TH1D("TruthSelMom2"               ,"TruthSelMom2"            ,n5-1,momparnum2);
  SignalSelMom3               = new TH1D("SignalSelMom3"              ,"SignalSelMom3"           ,n5-1,momparnum2);
  TruthSelMom3                = new TH1D("TruthSelMom3"               ,"TruthSelMom3"            ,n5-1,momparnum2);
  
  if(positive){
    SignalSelAng                = new TH1D("SignalSelAng"               ,"SignalSelAng"            ,n2pos-1,angparnumpos);
    TruthSelAng                 = new TH1D("TruthSelAng"                ,"TruthSelAng"             ,n2pos-1,angparnumpos);
    TrueMomCosTruth             = new TH2D("TrueMomCosTruth"            ,"TrueMomCosTruth"         ,n5,momparnum3,n2pos-1,angparnumpos);
    TrueMomCosSelec             = new TH2D("TrueMomCosSelec"            ,"TrueMomCosSelec"         ,n5,momparnum3,n2pos-1,angparnumpos);
  }
  else{
    SignalSelAng                = new TH1D("SignalSelAng"               ,"SignalSelAng"            ,n2-1,angparnum);
    TruthSelAng                 = new TH1D("TruthSelAng"                ,"TruthSelAng"             ,n2-1,angparnum);
    TrueMomCosTruth             = new TH2D("TrueMomCosTruth"            ,"TrueMomCosTruth"         ,n5,momparnum3,n2-1,angparnum);
    TrueMomCosSelec             = new TH2D("TrueMomCosSelec"            ,"TrueMomCosSelec"         ,n5,momparnum3,n2-1,angparnum);
  }

  if(isrhc){
    SignalSelMom4               = new TH1D("SignalSelMom4"              ,"SignalSelMom4"           ,n4-1,momparxsrhc);
    TruthSelMom4                = new TH1D("TruthSelMom4"               ,"TruthSelMom4"            ,n4-1,momparxsrhc);
    SignalSelMom5               = new TH1D("SignalSelMom5"              ,"SignalSelMom5"           ,n4-1,momparxsrhc);
    TruthSelMom5                = new TH1D("TruthSelMom5"               ,"TruthSelMom5"            ,n4-1,momparxsrhc);
  }
  else{
    SignalSelMom4               = new TH1D("SignalSelMom4"              ,"SignalSelMom4"           ,n3-1,momparxsfhc);
    TruthSelMom4                = new TH1D("TruthSelMom4"               ,"TruthSelMom4"            ,n3-1,momparxsfhc);
    SignalSelMom5               = new TH1D("SignalSelMom5"              ,"SignalSelMom5"           ,n3-1,momparxsfhc);
    TruthSelMom5                = new TH1D("TruthSelMom5"               ,"TruthSelMom5"            ,n3-1,momparxsfhc);
  }

  
}

// ----------------------------------------------------------------------------
Double_t GetPOTFromFile(TString file){
  
  TFile *File      = new TFile(file.Data(), "READ");
  TTree *POTSignal = (TTree*)File->Get("header");

  Header header;
  header.AddHeader(POTSignal);
  //header.DumpPOT();
  
  Double_t pot = header.GetPOT();
  
  File->Close();

  return pot;

}

// ----------------------------------------------------------------------------
void IncludeUnderflow(TH1D *h){
  //add underflow to bin=0
  int nentries = h->GetEntries();
  float firstbc = h->GetBinContent(1);
  float firstberr = h->GetBinError(1);
  float underflow =  h->GetBinContent(0);
  float underflowerr =  h->GetBinError(0);
  //float err =  TMath::Sqrt(firstberr*firstberr+underflowerr*underflowerr);
  h->SetBinContent(1,firstbc+underflow);
  //h->SetBinError(0,err);
  h->SetEntries(nentries);
  
}

// ----------------------------------------------------------------------------
void IncludeOverflow(TH1D *h){
  //add overflow to bin=nbin
  int nentries = h->GetEntries();
  int nbin = h->GetNbinsX();
  double lastbc = h->GetBinContent(nbin);
  double lastberr = h->GetBinError(nbin);
  double overflow =  h->GetBinContent(nbin+1);
  double overflowerr =  h->GetBinError(nbin+1);
  //is it right to sum in quadrature? in case of poisson error sum the entries and then calculate the err is the same as calculate the sum of the errors. But for MC the errors are scaled so no longer poissonian
  //double err =  TMath::Sqrt(lastberr*lastberr+overflowerr*overflowerr);
  //cout << lastbc << " , " << overflow << " , " << endl;
  h->SetBinContent(nbin,overflow+lastbc);
  //h->SetBinError(nbin,err);
  // Restore numbre of entries
  h->SetEntries(nentries);

}

// ----------------------------------------------------------------------------
TStyle* SetT2KStyle(Int_t WhichStyle = 1, TString styleName = "T2K") {
  TStyle *t2kStyle= new TStyle(styleName, "T2K approved plots style");
  
  // -- WhichStyle --
  // 1 = presentation large fonts
  // 2 = presentation small fonts
  // 3 = publication/paper

  Int_t FontStyle = 22;
  Float_t FontSizeLabel = 0.035;
  Float_t FontSizeTitle = 0.05;
  Float_t YOffsetTitle = 1.3;
 
  switch(WhichStyle) {
  case 1:
    FontStyle = 42;
    FontSizeLabel = 0.035;
    FontSizeTitle = 0.04;
    YOffsetTitle = 1.20;
    break;
  case 2:
    FontStyle = 42;
    FontSizeLabel = 0.035;
    FontSizeTitle = 0.05;
    YOffsetTitle = 1.6;
    break;
  case 3:
    FontStyle = 132;
    FontSizeLabel = 0.035;
    FontSizeTitle = 0.05;
    YOffsetTitle = 1.6;
    break;
  }
  
  // use plain black on white colors
  t2kStyle->SetFrameBorderMode(0);
  t2kStyle->SetCanvasBorderMode(0);
  t2kStyle->SetPadBorderMode(0);
  t2kStyle->SetCanvasBorderSize(0);
  t2kStyle->SetFrameBorderSize(0);
  t2kStyle->SetDrawBorder(0);
  t2kStyle->SetTitleBorderSize(0);
  
  t2kStyle->SetPadColor(0);
  t2kStyle->SetCanvasColor(0);
  t2kStyle->SetStatColor(0);
  t2kStyle->SetFillColor(0);
  
  // Set the size (in pixels) of the small lines drawn at the end of the error bars
  t2kStyle->SetEndErrorSize(4);

  // Set option to strip decimals when drawing axis labels. 
  t2kStyle->SetStripDecimals(kFALSE);

  t2kStyle->SetLegendBorderSize(0);
  t2kStyle->SetLegendFont(FontStyle);

  // set the paper & margin sizes
  t2kStyle->SetPaperSize(20, 26);
  t2kStyle->SetPadTopMargin(0.1);
  t2kStyle->SetPadBottomMargin(0.15);
  t2kStyle->SetPadRightMargin(0.13); // 0.075 -> 0.13 for colz option
  t2kStyle->SetPadLeftMargin(0.16);//to include both large/small font options
  
  // Fonts, sizes, offsets
  t2kStyle->SetTextFont(FontStyle);
  t2kStyle->SetTextSize(0.08);
  
  t2kStyle->SetLabelFont(FontStyle, "x");
  t2kStyle->SetLabelFont(FontStyle, "y");
  t2kStyle->SetLabelFont(FontStyle, "z");
  t2kStyle->SetLabelFont(FontStyle, "t");
  t2kStyle->SetLabelSize(FontSizeLabel, "x");
  t2kStyle->SetLabelSize(FontSizeLabel, "y");
  t2kStyle->SetLabelSize(FontSizeLabel, "z");
  t2kStyle->SetLabelOffset(0.015, "x");
  t2kStyle->SetLabelOffset(0.015, "y");
  t2kStyle->SetLabelOffset(0.015, "z");

  t2kStyle->SetTitleFont(FontStyle, "x");
  t2kStyle->SetTitleFont(FontStyle, "y");
  t2kStyle->SetTitleFont(FontStyle, "z");
  t2kStyle->SetTitleFont(FontStyle, "t");
  t2kStyle->SetTitleSize(FontSizeTitle, "y");
  t2kStyle->SetTitleSize(FontSizeTitle, "x");
  t2kStyle->SetTitleSize(FontSizeTitle, "z");
  t2kStyle->SetTitleOffset(1.14, "x");
  t2kStyle->SetTitleOffset(YOffsetTitle, "y");
  t2kStyle->SetTitleOffset(1.2, "z");

  t2kStyle->SetTitleStyle(0);
  t2kStyle->SetTitleFontSize(0.06);//0.08
  t2kStyle->SetTitleFont(FontStyle, "pad");
  t2kStyle->SetTitleBorderSize(0);
  t2kStyle->SetTitleX(0.1f);
  t2kStyle->SetTitleW(0.8f);
  
  // use bold lines and markers
  t2kStyle->SetMarkerStyle(20);
  t2kStyle->SetHistLineWidth( Width_t(2.5) );
  t2kStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes
  
  // get rid of X error bars and y error bar caps
  //t2kStyle->SetErrorX(0.001);
  
  // do not display any of the standard histogram decorations
  //t2kStyle->SetOptTitle(0);
  t2kStyle->SetOptStat(10);
  t2kStyle->SetOptFit(0);
  
  // put tick marks on top and RHS of plots
  //t2kStyle->SetPadTickX(1);
  //t2kStyle->SetPadTickY(1);
  
  // -- color --
  // functions blue
  t2kStyle->SetFuncColor(600-4);

  t2kStyle->SetFillColor(1); // make color fillings (not white)
  // - color setup for 2D -
  // - "cold"/ blue-ish -
  //Double_t red[]   = { 0.00, 0.00, 0.00 };
  //Double_t green[] = { 1.00, 0.00, 0.00 };
  //Double_t blue[]  = { 1.00, 1.00, 0.25 };
  // - "warm" red-ish colors -
  Double_t red[]   = {1.00, 1.00, 0.25 };
  Double_t green[] = {1.00, 0.00, 0.00 };
  Double_t blue[]  = {0.00, 0.00, 0.00 };

  Double_t stops[] = { 0.25, 0.75, 1.00 };
  const Int_t NRGBs = 3;
  const Int_t NCont = 500;

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  t2kStyle->SetNumberContours(NCont);

  // - Rainbow -
  //  t2kStyle->SetPalette(1);  // use the rainbow color set

  // -- axis --
  t2kStyle->SetStripDecimals(kFALSE); // don't do 1.0 -> 1
  //  TGaxis::SetMaxDigits(3); // doesn't have an effect 
  // no supressed zeroes!
  t2kStyle->SetHistMinimumZero(kTRUE);
  

  return(t2kStyle);
}

//********************************************************************
void CenterHistoTitles(TH1 *thisHisto){
  //********************************************************************
  thisHisto->GetXaxis()->CenterTitle();
  thisHisto->GetYaxis()->CenterTitle();
  thisHisto->GetZaxis()->CenterTitle();

}

//********************************************************************
int AddGridLinesToPad(TPad *thisPad) {
  //********************************************************************
  thisPad->SetGridx();
  thisPad->SetGridy();
  return(0);

}

//********************************************************************
TH1D* GetMeanNeutrinoEnergy(TString neutrino, bool isfhc){
  //********************************************************************

  Double_t potperrun[12] = {7.93271e+19, 2.17273e+19, 1.36447e+20, 3.42548e+20, 4.3468e+19,  1.28838e+20 , 5.07819e+19, 7.75899e+19, 8.51429e+19, 2.43662e+20, 3.9039e+19, 5.72958e+20};
  // Run                        2      ,    3b      ,     3c     ,      4     ,     5c    ,    6b        ,     6c     ,    6d      ,      6e    ,     7b     ,    7c,       8

  const char* _dir = "/afs/cern.ch/work/g/gechrist/t2k/nd280Highland2v2r27/psyche/psycheND280Utils/v3r25p1";
  if(isfhc){
    TH1D* FluxHistograms[6];
    std::string fluxFileName = std::string(_dir) + "/data/tuned13av2/run2/nd5_tuned13av2_13anom_run2_numode_fine.root";
    FluxHistograms[0] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[0]->SetNameTitle("Run2_NuEFlux","Run2_NuEFlux");
    Double_t nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    Double_t datapot_norm = nueflux*potperrun[0]/1e21;
    FluxHistograms[0]->Scale(datapot_norm/FluxHistograms[0]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run3b/nd5_tuned13av2_13anom_run3b_numode_fine.root";
    FluxHistograms[1] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[1]->SetNameTitle("Run3b_NuEFlux","Run3b_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[1]/1e21;
    FluxHistograms[1]->Scale(datapot_norm/FluxHistograms[1]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run3c/nd5_tuned13av2_13anom_run3c_numode_fine.root";
    FluxHistograms[2] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[2]->SetNameTitle("Run3c_NuEFlux","Run3c_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[2]/1e21;
    FluxHistograms[2]->Scale(datapot_norm/FluxHistograms[2]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run4/nd5_tuned13av2_13anom_run4_numode_fine.root";
    FluxHistograms[3] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[3]->SetNameTitle("Run4_NuEFlux","Run4_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[3]/1e21;
    FluxHistograms[3]->Scale(datapot_norm/FluxHistograms[3]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run7c/nd5_tuned13av2_13anom_run7c_numode_fine.root";
    FluxHistograms[4] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[4]->SetNameTitle("Run7c_NuEFlux","Run7c_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[10]/1e21;
    FluxHistograms[4]->Scale(datapot_norm/FluxHistograms[4]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run8/nd5_tuned13av2_13anom_run8_numode_fine.root";
    FluxHistograms[5] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[5]->SetNameTitle("Run8_NuEFlux","Run8_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[11]/1e21;
    FluxHistograms[5]->Scale(datapot_norm/FluxHistograms[5]->Integral());

    for(Int_t i = 1; i < 6; i++)
      FluxHistograms[0]->Add(FluxHistograms[i]);

    TH1D* totalflux = (TH1D*)FluxHistograms[0]->Clone();
    totalflux->SetDirectory(0);

    for(Int_t i = 1; i < 6; i++)
      delete FluxHistograms[i];

    return totalflux;
  }
  else{
    TH1D* FluxHistograms[6];

    std::string fluxFileName = std::string(_dir) + "/data/tuned13av2/run5c/nd5_tuned13av2_13anom_run5c_antinumode_fine.root";
    FluxHistograms[0] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[0]->SetNameTitle("Run5c_NuEFlux","Run5c_NuEFlux");
    Double_t nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    Double_t datapot_norm = nueflux*potperrun[4]/1e21;
    FluxHistograms[0]->Scale(datapot_norm/FluxHistograms[0]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run6b/nd5_tuned13av2_13anom_run6b_antinumode_fine.root";
    FluxHistograms[1] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[1]->SetNameTitle("Run6b_NuEFlux","Run6b_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[5]/1e21;
    FluxHistograms[1]->Scale(datapot_norm/FluxHistograms[1]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run6c/nd5_tuned13av2_13anom_run6c_antinumode_fine.root";
    FluxHistograms[2] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[2]->SetNameTitle("Run6c_NuEFlux","Run6c_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[6]/1e21;
    FluxHistograms[2]->Scale(datapot_norm/FluxHistograms[2]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run6d/nd5_tuned13av2_13anom_run6d_antinumode_fine.root";
    FluxHistograms[3] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[3]->SetNameTitle("Run6d_NuEFlux","Run6d_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[7]/1e21;
    FluxHistograms[3]->Scale(datapot_norm/FluxHistograms[3]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run6e/nd5_tuned13av2_13anom_run6e_antinumode_fine.root";
    FluxHistograms[4] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[4]->SetNameTitle("Run6e_NuEFlux","Run6e_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[8]/1e21;
    FluxHistograms[4]->Scale(datapot_norm/FluxHistograms[4]->Integral());

    fluxFileName = std::string(_dir) + "/data/tuned13av2/run7b/nd5_tuned13av2_13anom_run7b_antinumode_fine.root";
    FluxHistograms[5] = GetFluxHistogram(fluxFileName, std::string(neutrino.Data()));
    FluxHistograms[5]->SetNameTitle("Run7b_NuEFlux","Run7b_NuEFlux");
    nueflux = GetFluxIntegral(fluxFileName, std::string(neutrino.Data()));
    datapot_norm = nueflux*potperrun[9]/1e21;
    FluxHistograms[5]->Scale(datapot_norm/FluxHistograms[5]->Integral());

    for(Int_t i = 1; i < 6; i++)
      FluxHistograms[0]->Add(FluxHistograms[i]);

    TH1D* totalflux = (TH1D*)FluxHistograms[0]->Clone();
    totalflux->SetDirectory(0);

    for(Int_t i = 1; i < 6; i++)
      delete FluxHistograms[i];

    return totalflux;
  }

  return NULL;

}

//********************************************************************
TH1D* GetFluxHistogram(std::string file, std::string flux){
  //********************************************************************

  TFile* tempfile    = new TFile(file.c_str(),"READ");
  TH1D* temphist;
  if(flux == "nue")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_nue");
  else if(flux == "nueb")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_nueb");
  else if(flux == "numu")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_numu");
  else if(flux == "numub")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_numub");

  temphist->SetDirectory(0);
  tempfile->Close();

  return temphist;

}

//********************************************************************
Double_t GetFluxIntegral(std::string file, std::string flux){
  //********************************************************************

  TFile* tempfile    = new TFile(file.c_str(),"READ");
  TH1D* temphist;
  if(flux == "nue")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_nue");
  else if(flux == "nueb")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_nueb");
  else if(flux == "numu")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_numu");
  else if(flux == "numub")
    temphist = (TH1D*)tempfile->Get("enu_nd5_tuned13a_numub");

  Double_t integral = 0.0;
  if(temphist)
    integral = temphist->Integral();

  delete temphist;
  tempfile->Close();

  return integral;

}

//********************************************************************
TH1* GetSystVector(TString filename, TString selection, TH1* selhisto, bool isFlux=false, bool onlyfrac=false){
  //********************************************************************

  TH1* eventhisto = (TH1*)selhisto->Clone("eventhisto");

  TFile *SystFile = new TFile(filename.Data(), "READ");

  TIter next(SystFile->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())){
    TString classname(key->GetClassName());
    if(!classname.Contains("TH1")) continue;
    
    TH1* h = (TH1*)key->ReadObj();
    TString hname(h->GetName());
    if(!isFlux){
      if(!hname.Contains("ALLSysts")) continue;
    }

    if(!hname.Contains(selection.Data())) continue;
    cout << "Found systematic histo " << hname << endl;

    if(h->GetNbinsX() != selhisto->GetNbinsX()){
      cout << "WARNING::Binning of the systematics histogram is different from the selection binning" << endl;
      //continue;
    }

    // Fill histogram
    for(Int_t i=1; i <= h->GetNbinsX(); i++){
      if(i > eventhisto->GetNbinsX()) continue;
      Double_t nevents = selhisto->GetBinContent(i)*h->GetBinContent(i);
      eventhisto->SetBinContent(i, nevents);
      if(onlyfrac)
	eventhisto->SetBinContent(i, h->GetBinContent(i));
    }
    //h->SetDirectory(0);
  }

  SystFile->Close();

  return eventhisto;

}

//********************************************************************
TCanvas* GetTotalSystematicHisto(TH1* hist, TH1* xshisto, TH1* dethisto, TH1* fluxhisto, TString ssample){
  //********************************************************************

  TH1* TotalMomSystHisto = dethisto->Clone("TotalMomSystHisto");
    
  // Fill the total systematic histo
  for(Int_t i = 0; i <= xshisto->GetNbinsX(); i++){
    Double_t xssystnum = xshisto->GetBinContent(i);
    Double_t detsystnum = dethisto->GetBinContent(i);
    Double_t fluxsystnum = fluxhisto->GetBinContent(i);
    Double_t systnum = sqrt(xssystnum*xssystnum + fluxsystnum*fluxsystnum + detsystnum*detsystnum);
    //cout << "Flux syst = " << fluxsystnum << " , det syst = " << detsystnum << " , xs syst = " << xssystnum << " , total = " << systnum <<endl;
    TotalMomSystHisto->SetBinContent(i, systnum);
  }

  TString canvas_string = TString("Canvas_") + ssample + TString("_DetXsFlux") ;
  TCanvas* tepcanvas = new TCanvas(canvas_string.Data(), canvas_string.Data());

  xshisto->SetLineColor(kBlue);
  dethisto->SetLineColor(14);
  fluxhisto->SetLineColor(kBlack);
  TotalMomSystHisto->SetLineColor(kRed);

  xshisto->SetLineStyle(kDashed);
  dethisto->SetLineStyle(6);
  fluxhisto->SetLineStyle(4);

  TString samplename;
  if(ssample.Contains("CCINCLUSIVE"))
    samplename = "Signal";
  else if(ssample.Contains("ALLGAMMABKG"))
    samplename = "Gamma background";
  else if(ssample.Contains("ALLOTHERBKG"))
    samplename = "Muon-Other background";
  if(ssample.Contains("FHCANUE") || ssample.Contains("RHCANUE"))
    samplename = "Muon-Proton-Other background";

  if(ssample.Contains("FHCNUE"))
    samplename += TString(" FHC CC-#nu_{e}");
  else if(ssample.Contains("FHCANUE"))
    samplename += TString(" FHC CC-#bar#nu_{e}");
  else if(ssample.Contains("RHCNUE"))
    samplename += TString(" RHC CC-#nu_{e}");
  else if(ssample.Contains("RHCANUE"))
    samplename += TString(" RHC CC-#bar#nu_{e}");

  if(ssample.Contains("SIDEBAND")){
    samplename = "Gamma sideband";
    if(ssample.Contains("FHCGAMMA"))
      samplename += TString(" FHC HMN");
    else if(ssample.Contains("FHCANUE"))
      samplename += TString(" FHC HMP");
    else if(ssample.Contains("RHCGAMMA"))
      samplename += TString(" RHC HMN");
    else if(ssample.Contains("RHCANUE"))
      samplename += TString(" RHC HMP");
  }

  xshisto->GetYaxis()->SetRangeUser(0,1);
  dethisto->GetYaxis()->SetRangeUser(0,1);
  fluxhisto->GetYaxis()->SetRangeUser(0,1);
  TotalMomSystHisto->GetYaxis()->SetRangeUser(0,1);

  if(!ssample.Contains("CCINCLUSIVE")){
    xshisto->GetXaxis()->SetRangeUser(0,2500);
    dethisto->GetXaxis()->SetRangeUser(0,2500);
    fluxhisto->GetXaxis()->SetRangeUser(0,2500);
    TotalMomSystHisto->GetXaxis()->SetRangeUser(0,2500);
    hist->GetXaxis()->SetRangeUser(0,2500);
  }

  hist->SetStats(0);
  hist->SetLineWidth(2);
  hist->SetLineColor(30);
  hist->SetFillColor(30);
  hist->SetFillStyle(4000);
  hist->GetXaxis()->SetTitle("Momentum [MeV/c]");
  hist->GetYaxis()->SetTitle("Fractional Error");
  hist->GetYaxis()->SetTitleOffset(1.2);
  Float_t rightmax = 1.1*hist->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  //hist->Scale(scale);

  Float_t rightmax = 1.1*hist->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  hist->Scale(scale);
  hist->GetYaxis()->SetRangeUser(0,1);

  TLegend *mylegend1 = new TLegend(0.25,0.65,0.80,0.88);
  mylegend1->SetFillColor(0); // white background
  mylegend1->SetBorderSize(0);
  mylegend1->SetTextSize(0.036);
  mylegend1->AddEntry(TotalMomSystHisto, "All sytematics",            "l");
  mylegend1->AddEntry(xshisto,           "Total XS sytematics",       "l");
  mylegend1->AddEntry(dethisto,          "Total Detector sytematics", "l");
  mylegend1->AddEntry(fluxhisto,         "Total Flux sytematics",     "l");
  mylegend1->AddEntry(hist,              samplename.Data(),           "l");

  hist->Draw();
  hist->SetTitle(samplename.Data());
  TotalMomSystHisto->Draw("same");
  xshisto->Draw("same");
  dethisto->Draw("same");
  fluxhisto->Draw("same");
  mylegend1->Draw();

  tepcanvas->Update();
  // Draw axis on the right side
  // Remove y-axis tick on the left and x-axis ticks on top
  gPad->SetTicks(0,0);
  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
  axis->SetLineColor(30);
  axis->SetLabelColor(30);
  axis->SetTitleColor(30);
  axis->SetTitleOffset(1.1);
  axis->SetTitle("Events / 300 [MeV/c]");
  axis->Draw();

  return tepcanvas;

}

//********************************************************************
TH1* GetThetaSystematic(TH1* detsysthistofrac, TH1* xssysthistofrac, TH1* fluxsysthistofrac, TH2* histo2D){
  //********************************************************************

  TH1D* thetamchisto_sig[3];
  TH1D* thetamchisto  = (TH1D*)CCH[4]->Clone("thetamchisto");

  for(Int_t i=0; i < 3; i++)
    thetamchisto_sig[i] = (TH1D*)CCH[4]->Clone(Form("thetamchisto_%i",i));

  for(Int_t i=0; i <= thetamchisto->GetNbinsX(); i++){
    thetamchisto_sig[0]->SetBinContent(i,0.0);
    thetamchisto_sig[1]->SetBinContent(i,0.0);
    thetamchisto_sig[2]->SetBinContent(i,0.0);
    thetamchisto->SetBinContent(i,0.0);
  }
  
  for(Int_t i=0; i <= histo2D->GetNbinsX(); i++){
    Double_t detmombinsyst  = detsysthistofrac->GetBinContent(i);
    Double_t xsmombinsyst   = xssysthistofrac->GetBinContent(i);
    Double_t fluxmombinsyst = fluxsysthistofrac->GetBinContent(i);
    
    for(Int_t j=0; j <= histo2D->GetNbinsY(); j++){
      Double_t systevents = histo2D->GetBinContent(i,j);

      Double_t defaultevents = thetamchisto_sig[0]->GetBinContent(j);
      thetamchisto_sig[0]->SetBinContent(j,systevents*detmombinsyst + defaultevents);

      defaultevents = thetamchisto_sig[1]->GetBinContent(j);
      thetamchisto_sig[1]->SetBinContent(j,systevents*xsmombinsyst + defaultevents);

      defaultevents = thetamchisto_sig[2]->GetBinContent(j);
      thetamchisto_sig[2]->SetBinContent(j,systevents*fluxmombinsyst + defaultevents);
    }
  }

  for(Int_t i=1; i <= thetamchisto->GetNbinsX(); i++){
    Double_t nevents = sqrt(thetamchisto_sig[0]->GetBinContent(i)*thetamchisto_sig[0]->GetBinContent(i) + thetamchisto_sig[1]->GetBinContent(i)*thetamchisto_sig[1]->GetBinContent(i) + thetamchisto_sig[2]->GetBinContent(i)*thetamchisto_sig[2]->GetBinContent(i));
    thetamchisto->SetBinContent(i, nevents + thetamchisto->GetBinContent(i));
  }

  return thetamchisto;

}

//********************************************************************
TString GetOutputFilename(){
  //********************************************************************

  TString outFile               = "fhcnue_outfile";
  if(isrhc)
    outFile               = "rhcnue_outfile";

  if(positive){
    outFile               = "fhcanue_outfile";
    if(isrhc)
      outFile               = "rhcanue_outfile";
  }

  if(isgamma){
    outFile               = "fhcgammaHMN_outfile";
    if(isrhc)
      outFile               = "rhcgammaHMN_outfile";

    if(positive){
      outFile               = "fhcgammaHMP_outfile";
      if(isrhc)
	outFile               = "rhcgammaHMP_outfile";
    }
  }
  
  if(isgenie){
    outFile               = "gfhcnue_outfile";
    if(isrhc)
      outFile               = "grhcnue_outfile";
    
    if(positive){
      outFile               = "gfhcanue_outfile";
      if(isrhc)
	outFile               = "grhcanue_outfile";
    }
    
    if(isgamma){
      outFile               = "gfhcgammaHMN_outfile";
      if(isrhc)
	outFile               = "grhcgammaHMN_outfile";
      
      if(positive){
	outFile               = "gfhcgammaHMP_outfile";
	if(isrhc)
	  outFile               = "grhcgammaHMP_outfile";
      }
    }
  }

  if(whichfgd == 1)
    outFile += TString("_fgd2");

  outFile += TString(".root");

  return outFile;

}
