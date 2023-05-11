#ifndef CorrId_hxx_seen
#define CorrId_hxx_seen


/// Enumeration for various corrections used inside highland2
namespace CorrId{

  enum CorrEnum {
    kDQCorr = 0,   
    kCT4POTCorr,        
    kFlipKinCorr,      
    kRightECalRun3And4Corr, 
    kMomRangeCorr,
    kMomResolMCCorr,
    kPileUpCorr,        
    kToFCorr,
    kToFTimeSlipCorr, 
    kTPCdEdxDataCorr, 
    kTPCdEdxMCCorr,
    kTPCdEdxExpCorr, 
    kTPCPIDPullMCCorr, 
    kFGDPIDPullMCCorr, 
    kFGDPIDCorr, 
    kGlobalAltMomCorr, 
    kTimeDQCorr, 
    kFGDMIPLikeCorr
  };
}

#endif
