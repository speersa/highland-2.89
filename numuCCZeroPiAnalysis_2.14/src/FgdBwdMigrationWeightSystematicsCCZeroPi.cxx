#include "FgdBwdMigrationWeightSystematicsCCZeroPi.hxx"

//#define DEBUG


// ********************************************************************
Float_t FgdBwdMigrationWeightSystematicsCCZeroPi::GetSystBinValue(const AnaEventC& event, const ToyBoxB& boxB, const SelectionBase& sel) const{
// ********************************************************************

  (void)sel;
  (void)boxB;
  
  Float_t sample = SampleId::kUnassigned;
  AnaEventSummaryB* summary = static_cast<AnaEventSummaryB*>(event.Summary);
  if (summary){
    sample = summary->EventSample;
  }
  
  
#ifdef DEBUG
  std::cout << " FgdBwdMigrationWeightSystematicsCCZeroPi::GetSystBinValue sample " << sample << std::endl;
#endif
  
  
  return sample;
}

// ********************************************************************
Int_t FgdBwdMigrationWeightSystematicsCCZeroPi::ApplyCorrelation(Int_t index) const{
  // ********************************************************************

  if (!_apply_corr)  
    return index;
  
  // Then do things for the moment depending on the samples
  // index corresponds to samples, currently
  /*  11.5  12.5 0.078 0.3  kFgd2MuTpc       
      12.5  13.5 0.111 0.3  kFgd2MuTpcPTpc  
      13.5  14.5 0.050 0.3  kFgd2MuTpcPFgd  
      14.5  15.5 0.126 0.3  kFgd2MuFgdPTpc  
      15.5  16.5 0.141 0.3  kFgd2MuFgd      
      16.5  17.5 0.070 1.0  kFgd2CC1Pi      
      17.5  18.5 0.111 1.0  kFgd2CCDIS      
      18.5  19.5 0.111 1.0  kFgd2CCMichel   
      19.5  20.5 0.078 0.3  kFgd2MuTpcNP    
      20.5  21.5 0.126 0.3  kFgd2MuFgdPTpcNP
      21.5  22.5 0.141 0.3  kFgd2MuFgdNP       
*/
  // Correlate currently CC0Pi samples: not sure about MuFgd since it can be
  // subject to reco issues
  
  switch ( index ) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 8:
    case 9:
    case 10:
      return 0;
      break;
    // Michel is probably cc1pi
    case 5:
    case 7:
      return 5;
      break;
    default:
      return index;
      break;
  } 
}
