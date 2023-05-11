#ifndef ProductionUtils_h
#define ProductionUtils_h

#include "VersionManager.hxx"
#include "oaAnalysisReaderProjectHeaders.h"

  /// Enum for the different productions suported
namespace ProdId{
  enum ProdEnum{
    unknown=UNKNOWN_PRODUCTION,
    PROD5D,
    PROD5E,
    PROD5F,
    PROD5G,
    PROD6PRE,
    PROD6A,
    PROD6B,
    PROD6C,
    PROD6D,
    PROD6E,
    PROD6F,
    PROD6G,
    PROD6H,
    PROD6I,
    PROD6J,
    PROD6K,
    PROD6L,
    PROD6M,
    PROD6N, 
    PROD6O,
    PROD6P,
    PROD6Q, 
    PROD6R, 
    PROD6S,
    PROD6T,
    PROD6U,
    PROD6V,
    PROD6W,
    PROD6X,
    PROD6Y, 
    PROD6Z,
    PROD6AA, 
    PROD7RC1,
    PROD7A,
    PROD7B1,
    PROD7B2, 
    PROD7V01,
    PROD7V02, 
    PROD7V03,
    PROD7V06,
    PROD7V07,
    PROD7V09,
    PROD7V12, 
    PROD7DEVEL
  };
}

/// This namespace contains useful functions for analyses. 
/// This is in addition to those defined in psycheUtils
namespace anaUtils{

    /// Get Production Id from nd280AnalysisTools
    ProdId_h GetProductionIdFromoaAnalysisReader();

    /// Add the standard production versions
    void AddStandardProductions();
}
#endif


