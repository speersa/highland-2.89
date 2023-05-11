#include "VersioningUtils.hxx"
#include "CoreUtils.hxx"

namespace versionUtils{

  Production   prod_POT             = kProdUnassigned;
  Production   prod_bunching        = kProdUnassigned;
  Production   prod_corrections     = kProdUnassigned;
  Production   prod_systematics     = kProdUnassigned;
  RunNumbering run_numbering_scheme = kProdNumUnassigned;
  
}

//***************************************************
void versionUtils::DumpProductions(){
//***************************************************
  std::string tmp;
  
  std::cout << " ***** POT ***** " << std::endl;
  tmp = "";
  switch (prod_POT){
    case kProd6:
      tmp = stringvar(kProd6);
      break;
    case kProd7:
      tmp = stringvar(kProd7);
      break;
    default:
      break;
  }
  std::cout << " *****\t " << tmp << " *****\t " << std::endl;
  std::cout << " ***** POT *****\n " << std::endl; 
  
  
  std::cout << " ***** Bunching ***** " << std::endl;
  tmp = "";
  switch (prod_bunching){
    case kProd6:
      tmp = stringvar(kProd6);
      break;
    case kProd7:
      tmp = stringvar(kProd7);
      break;
    default:
      break;
  }
  
  std::cout << " *****\t " << tmp << " *****\t " << std::endl;
  std::cout << " ***** Bunching *****\n " << std::endl; 
 
  
  std::cout << " ***** Corrections ***** " << std::endl; 
  tmp = "";
  switch (prod_corrections){
    case kProd6:
      tmp = stringvar(kProd6);
      break;
    case kProd7:
      tmp = stringvar(kProd7);
      break;
    default:
      break;
  }
  
  std::cout << " *****\t " << tmp << " *****\t " << std::endl;
  std::cout << " ***** Corrections *****\n " << std::endl; 
  

  std::cout << " ***** Systematics ***** " << std::endl; 
  tmp = "";
  switch (prod_systematics){
    case kProd6:
      tmp = stringvar(kProd6);
      break;
    case kProd7:
      tmp = stringvar(kProd7);
      break;
    default:
      break;
  }
  
  std::cout << " *****\t " << tmp << " *****\t " << std::endl;
  std::cout << " ***** Systematics *****\n " << std::endl; 
  
  std::cout << " ***** Run numbering scheme ***** " << std::endl; 
  tmp = "";
  switch (run_numbering_scheme){
    case kPreProd6TNum:
      tmp = stringvar(kPreProd6TNum );
      break;
    case kProd6TNum:
      tmp = stringvar(kProd6TNum);
      break;
    case kProd7Num:
      tmp = stringvar(kProd7Num);
      break;
    default:
      break;
  }
  
  std::cout << " *****\t " << tmp << " *****\t " << std::endl;
  std::cout << " ***** Run numbering scheme *****\n " << std::endl; 
}



//**************************************************
std::string versionUtils::Extension(versionUtils::Production prod,  bool useProdExt){
//**************************************************

  // Corrections and systematics can store production dependent data 
  // E.g. inside data/Prod6/dataFile_Prod6.dat
  
  std::string prodExt = "";
  
  if (!useProdExt){
    return prodExt;
  }
  
  switch (prod){
    case kProd6:
      prodExt = stringvar(kProd6);
      break;
    case kProd7:
      prodExt = stringvar(kProd7);
      break;
    default:
      prodExt = "k";
      break;
  }
    
  prodExt.erase(0, 1);
  
  return prodExt;
}

//**************************************************
std::string versionUtils::ExtensionSyst(bool useProdExt){
//**************************************************
  return versionUtils::Extension(prod_systematics, useProdExt);
}

//**************************************************
std::string versionUtils::ExtensionCorr(bool useProdExt){
//**************************************************
  return versionUtils::Extension(prod_corrections, useProdExt);
}
