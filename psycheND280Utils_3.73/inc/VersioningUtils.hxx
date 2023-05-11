#ifndef VersioningUtils_h
#define VersioningUtils_h

#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>

namespace versionUtils { 
  
  
  enum RunNumbering{
    kPreProd6TNum = 0,
    kProd6TNum, 
    kProd7Num, 
    kProdNumUnassigned
  };
  
  enum Production{
    kProd6, 
    kProd7, 
    kProdUnassigned
  };
  
  
  extern Production     prod_POT;    
  extern Production     prod_bunching;    
  extern Production     prod_corrections;    
  extern Production     prod_systematics;    
  extern RunNumbering   run_numbering_scheme; 

  void DumpProductions();

  std::string Extension(versionUtils::Production prod, bool useProdExt=true); 
  
  /// Get the extension to be used in e.g. BinnedParams file
  /// Will be used for folder and file name 
  /// E.g. /data/Extension/file_name+_Extension
  std::string ExtensionSyst(bool useProdExt=true); 
 
  /// Extension for corrections
  std::string ExtensionCorr(bool useProdExt=true); 

}


#endif


