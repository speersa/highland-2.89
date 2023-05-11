#ifndef TimeDataQualityCorrection_h
#define TimeDataQualityCorrection_h

#include "CorrectionBase.hxx"
#include "SubDetId.hxx"
#include <vector>
#include <utility>
#include <map>

/// Correction aimed to set time quality flags for the sub-detectors. This is
/// relevant for the ToF-based analyses.
/// At the moment (2018) the relevant information is not availalbe via the DB
/// nor with the "standard" DQ flags, also the exact quality definition may
/// depend on thee  analysis and also further studies and checks are needed in
/// order to set the cuts


/// This correction uses the RMS values obtained with inter-detector time
/// checks for nd280 runs(run numbers), based on the values and given cuts,
/// controlled via param files,  one sets the flags

/// At the moment (2018) nd280-cali group provides inter-detector time
/// calibration for FGDs, P0D and ECals,  the sub-detector are calibrated
/// internally prior to the application of the inter-detector checks 

/// Note! if a detector gets a success flag if: it is either not in the list or
/// is the RMS is below the cut. Detectors other than FGD, P0D and ECal will get
/// the bad time quality cut. The currection MUST be run in order to set the
/// flags, w/o it all sub-detectors will get bad time DQ stamps for conservaty.




/// Structure to store RMS values for different detectors

struct RMS_data{
  RMS_data(){
    RMS_ECal = RMS_P0D = RMS_FGD = 0.;
  
  }
  Float_t RMS_ECal;
  Float_t RMS_P0D;
  Float_t RMS_FGD;

};


/// The parameters in baseAnalysis.parameters.dat define the run periods for which
/// this correction should be applied.
class TimeDataQualityCorrection: public CorrectionBase {
public:

  /// Constructor, which reads in the parameter file to set up the run
  /// periods for which the correction should be applied.
  TimeDataQualityCorrection();

  virtual ~TimeDataQualityCorrection() {}

  /// Apply the variation to all tracks with TPC info.
  void Apply(AnaSpillC& spill);

protected:

  void Initialize();
  
  /// Structure to store RMS values for nd280 runs
  /// Map is slow but need a flexible way to associate run with RMSs
  std::map<Int_t, RMS_data> _rms_data;
  
  /// Read data file and update the RMS data
  void AddDataFile(const std::string& filename, SubDetId::SubDetEnum det);
  
  /// Cut values
  Float_t _cut_RMS_ECal;
  Float_t _cut_RMS_P0D;
  Float_t _cut_RMS_FGD;
  
  
private:
  bool _initialized;
  
};

#endif
