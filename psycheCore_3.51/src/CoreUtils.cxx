#include "CoreUtils.hxx"
#include <TVector3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <typeinfo>
#include <unistd.h>

namespace anaUtils{
  std::string skimFileName="";
  bool breakLoop=false;
}


//********************************************************************
void anaUtils::ConfigureTreeBranch(TTree* tree, const char* bname, void* add, TBranch** ptr){
  //********************************************************************

  if (!tree->FindLeaf(bname)) return;
  tree->SetBranchAddress(bname,add,ptr);  
}


//********************************************************************
void anaUtils::ReserveArray(Int_t* arr, int n, Int_t ini){
  //********************************************************************

  for(int i = 0; i < n; ++i){
    arr[i] = ini;
  }
  return;
}

//********************************************************************
void anaUtils::ReserveArray(Float_t* arr, int n, Float_t ini){
  //********************************************************************

  for(int i = 0; i < n; ++i){
    arr[i] = ini;
  }
  return;
}


//********************************************************************
void anaUtils::ReserveArray(Weight_h* arr, int n, Weight_h ini){
  //********************************************************************

  for(int i = 0; i < n; ++i){
    arr[i] = ini;
  }
  return;
}

//********************************************************************
void anaUtils::VectorToArray(const TLorentzVector& v, Float_t* array){
  //********************************************************************
  for (UInt_t i=0; i<4;i++) array[i]=v[i];
}

//********************************************************************
void anaUtils::VectorToArray(const TVector3& v, Float_t* array){
  //********************************************************************
  for (UInt_t i=0; i<3;i++) array[i]=v[i];
}

//********************************************************************
TVector3 anaUtils::ArrayToTVector3(const Float_t* array){
  //********************************************************************

  TVector3 v;
  for (UInt_t i=0; i<3;i++) v[i]=array[i];
  return v;
}

//********************************************************************
TLorentzVector anaUtils::ArrayToTLorentzVector(const Float_t* array){
  //********************************************************************

  TLorentzVector v;
  for (UInt_t i=0; i<4;i++) v[i]=array[i];
  return v;
}

//********************************************************************
void anaUtils::CreateArray(Weight_h* &tgtArr, int nObj, Weight_h ini){
  //********************************************************************

  tgtArr = new Weight_h[nObj];
  for(int i = 0; i < nObj; ++i){
    tgtArr[i] = ini;
  }
}

//********************************************************************
void anaUtils::CreateArray(Float_t* &tgtArr, int nObj, Float_t ini){
  //********************************************************************

  tgtArr = new Float_t[nObj];
  for(int i = 0; i < nObj; ++i){
    tgtArr[i] = ini;
  }
}

//********************************************************************
void anaUtils::CreateArray(Int_t* &tgtArr, int nObj, Int_t ini){
  //********************************************************************

  tgtArr = new Int_t[nObj];
  for(int i = 0; i < nObj; ++i){
    tgtArr[i] = ini;
  }
}

//********************************************************************
void anaUtils::CreateArray(bool* &tgtArr, int nObj, bool ini){
  //********************************************************************

  tgtArr = new bool[nObj];
  for(int i = 0; i < nObj; ++i){
    tgtArr[i] = ini;
  }
}

//********************************************************************
Float_t anaUtils::ScalarProduct(Float_t* array1, Float_t* array2, Int_t size){
  //********************************************************************

  Float_t product=0;
  for(int i = 0; i < size; ++i){
    product += array1[i]*array2[i];
  }
  return product;
}

//*****************************************************************************
bool anaUtils::CheckSkimmedEvent(Int_t sRun, Int_t sSubrun, Int_t sEvt){
  //*****************************************************************************  

  if (skimFileName=="") return true;

  static std::ifstream inputFile(skimFileName.c_str(), std::ios::in);
  static bool first=true;
  static bool found=true;

  if (first){
    if (!inputFile) {
      std::cerr << "Cannot open skim file '" << skimFileName << "'. Exit!" << std::endl;
      exit(0);
    }
    first=false;
  }


  static std::string run, subrun, evt;
  char* pEnd;
  if (found && !breakLoop){
    if(!(inputFile >> run >> subrun >> evt)){breakLoop=true;inputFile.close(); }
    found=false;
  }
  if (sRun    == strtod(run.c_str(),     &pEnd) &&
      sSubrun == strtod(subrun.c_str(),  &pEnd) &&
      sEvt    == strtod(evt.c_str(),     &pEnd)){
    found=true;
    return true;
  }
  found= false;


  return false;

}

//********************************************************************
std::string anaUtils::GetSoftwareVersionFromPath(const std::string& path){
  //********************************************************************

  // path is to the packageROOT folder,  so retrieve it from the name
  
  std::string version="";
  size_t lastSlash = path.find_last_of("_");
  if (lastSlash != std::string::npos){
    version = path.substr(lastSlash+1);
  }

  return version;
}

//********************************************************************
std::string anaUtils::GetPackageNameFromProgram(const std::string& program){
  //********************************************************************

  // Imagine we run all an executable (../../../numuCCAnalysis/v1r12/Darwin/RunNumuCCAnalysis.exe) from 
  // another package (PWD=/hep/T2K/nd280rep/ANALYSIS/HIGHLAND2/SIFS2/highland2/numuCCMultiPiAnalysis/v1r12/cmt)

  char the_path[256];

  // Get the current working directory 
  // i.e. /hep/T2K/nd280rep/ANALYSIS/HIGHLAND2/SIFS2/highland2/numuCCMultiPiAnalysis/v1r12/cmt
  getcwd(the_path, 255);

  // Add the relative path to the executable 
  // i.e. /hep/T2K/nd280rep/ANALYSIS/HIGHLAND2/SIFS2/highland2/numuCCMultiPiAnalysis/v1r12/cmt/../../../numuCCAnalysis/v1r12/Darwin/RunNumuCCAnalysis.exe
  strcat(the_path, "/");
  strcat(the_path, program.c_str());  

  return GetPackageNameFromPath(std::string(the_path));
}

//********************************************************************
std::string anaUtils::GetPackageNameFromPath(const std::string& full_path){
  //********************************************************************


  char real_path[256];

  // convert into a canonical path (resolving .., env variables and symbolic links) 
  // i.e. /hep/T2K/nd280rep/ANALYSIS/HIGHLAND2/numuCCAnalysis/Darwin*/bin
  realpath(full_path.c_str(), real_path);

  // convert into string
  std::string path(real_path);

  // Get all path up to the binary directory (excluded)
  // i.e. /hep/T2K/nd280rep/ANALYSIS/HIGHLAND2/numuCCAnalysis
  path = path.substr(0, path.rfind(getenv("ND280_SYSTEM"))-1);

  // Get all path from the last "/" (excluded)
  // i.e. numuCCAnalysis
  path = path.substr(path.find_last_of("/")+1);

  return path;
}


//********************************************************************
std::vector<std::string> anaUtils::GetPackageHierarchy(){
  //********************************************************************


  // TODO. We must identify the package corresponding to the current executable and start by that one

  std::vector<std::string> packages;

  std::string PATHENV = getenv("PATH");

  // Now split 
  std::vector<std::string> vect_tmp;

  anaUtils::Tokenize(PATHENV, vect_tmp, ":");
  
  size_t vsize = vect_tmp.size();
  
  for (int i = 0; i < vect_tmp.size(); i++){
    if (vect_tmp[i].rfind(getenv("ND280_SYSTEM")) != std::string::npos){
      std::string package = GetPackageNameFromPath(vect_tmp[i]);
      if (std::find(packages.begin(), packages.end(), package) == packages.end()){
        packages.push_back(package);
      }
    }
  }
  
  return packages;
}

//*********************************************************
std::string anaUtils::GetVersionSubtractedPackageName(const std::string& name){
  //*********************************************************
 
  return name.substr(0, name.rfind("_"));
  
}


//*********************************************************
bool anaUtils::IsValidValue(Double_t value){
  //*********************************************************

  if (!TMath::Finite(value)) return false;
  if (TMath::IsNaN(value)) return false;

  return true;
}

//*********************************************************
bool anaUtils::IsValidValue(Float_t value){
  //*********************************************************

  if (!TMath::Finite(value)) return false;
  if (TMath::IsNaN(value)) return false;

  return true;
}

