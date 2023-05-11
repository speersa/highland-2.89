#include "TimeDataQualityCorrection.hxx"
#include "DataClasses.hxx"
#include "Parameters.hxx"
#include <iostream>
#include <assert.h> 

//********************************************************************
TimeDataQualityCorrection::TimeDataQualityCorrection() :  CorrectionBase() {
  //********************************************************************
  _rms_data.clear();

  // Read the cut values
  _cut_RMS_ECal = ND::params().GetParameterD("highlandCorrections.TimeDataQualityCorrection.RMSCut.ECal");
  _cut_RMS_P0D  = ND::params().GetParameterD("highlandCorrections.TimeDataQualityCorrection.RMSCut.P0D");
  _cut_RMS_FGD  = ND::params().GetParameterD("highlandCorrections.TimeDataQualityCorrection.RMSCut.FGD");

  _initialized = false;

  Initialize();


}

//********************************************************************
void TimeDataQualityCorrection::Initialize() {
  //********************************************************************

  // Read the data
  std::string folder_name = std::string(getenv("HIGHLANDCORRECTIONSROOT")) + "/data/TimeDQ/";

  // ECal
  AddDataFile(folder_name + "ECal_interdet_timecali_RMS_run8.dat", SubDetId::kECAL);

  // P0D
  AddDataFile(folder_name + "P0D_interdet_timecali_RMS_run8.dat", SubDetId::kP0D);

}

//********************************************************************
void TimeDataQualityCorrection::AddDataFile(const std::string& filename, SubDetId::SubDetEnum det) {
  //******************************************

  std::ifstream inputFile(filename.c_str(), std::ios::in);

  if (!inputFile){
    std::cerr << " TimeDataQualityCorrection: Cannot open input file '" << filename << "'. Exit!" << std::endl;
    exit(0);
  }
  // Known detectors
  if (det != SubDetId::kFGD && det != SubDetId::kP0D && det != SubDetId::kECAL){
    std::cerr << " TimeDataQualityCorrection: Unknown detector '" << det << "Use FGD, ECal or P0D" << "'. Exit!" << std::endl;
    exit(0);
  }

  Int_t run;
  Float_t offset, rms; 

  while (inputFile >> run >> offset  >> rms ){
    switch (det){  
      case SubDetId::kFGD:  
        _rms_data[run].RMS_FGD = rms;
        break;  
      case SubDetId::kECAL:  
        _rms_data[run].RMS_ECal = rms;
        break;

      case SubDetId::kP0D:
        _rms_data[run].RMS_P0D = rms;
        break;
      default:  
        break;  
    }  
  }

  if (_rms_data.empty()){
    std::cerr << " TimeDataQualityCorrection: No data was read. Check the inputs. Exit!" << std::endl;
    exit(0);
  }

  inputFile.close(); 

}

//********************************************************************
void TimeDataQualityCorrection::Apply(AnaSpillC& spillBB) {
  //********************************************************************

  // Correction was applied when making the flat tree.
  //  if (ND::input().InputIsFlatTree()) return;

  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);

  // Get the data-quality info
  assert(spill.DataQuality);
  AnaDataQuality* dq = dynamic_cast<AnaDataQuality*>(spill.DataQuality);

  assert(dq);


  // For the MC set everything to true for consistency
  if (spill.GetIsMC()){
    for (int i = 0; i < 5; i++){
      dq->DetTimeFlag[i] = 0;
    }
    // Global flag
    dq->GoodTimeDaq = true;

    return;
  }

  // Set all relevant ones to good first
  ///Int_t DetTimeFlag[5];
  /// [0] = TPC
  /// [1] = FGD
  /// [2] = ECAL
  /// [3] = P0D
  /// [4] = SMRD

  dq->DetTimeFlag[1] = 0;
  dq->DetTimeFlag[2] = 0;
  dq->DetTimeFlag[3] = 0;

  // Global flag is set based on the sub-detector ones
  spill.DataQuality->GoodTimeDaq = 1;

  // Now check whether the run is present and check the RMS wrt a sub-detector cut
  // Get the run number
  Int_t run = spill.EventInfo->Run;

  std::map<Int_t, RMS_data>::const_iterator it;
  it = _rms_data.find(run);

  if (it ==_rms_data.end()){
    return;
  }

  /// Check the values and set
  if (it->second.RMS_FGD > _cut_RMS_FGD){
    dq->DetTimeFlag[1] = 1; // bad
  }

  if (it->second.RMS_ECal > _cut_RMS_ECal){
    dq->DetTimeFlag[2] = 1; // bad
  }

  if (it->second.RMS_P0D > _cut_RMS_P0D){
    dq->DetTimeFlag[3] = 1; // bad
  }

  // Set the global one
  if (dq->DetTimeFlag[1] != 0 || dq->DetTimeFlag[2] != 0 || dq->DetTimeFlag[3] != 0){
    spill.DataQuality->GoodTimeDaq = 0;
  }

  return;

}

