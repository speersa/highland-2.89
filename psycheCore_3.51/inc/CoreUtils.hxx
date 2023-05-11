#ifndef CoreUtils_h
#define CoreUtils_h

#include "BasicTypes.hxx"
#include "WeightType.hxx"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "CoreDataClasses.hxx"
#include "TTree.h"
#include "Deprecated.hxx"
#include <utility>
#include <vector>
#include <set>
#include <stdarg.h>
#include <stdexcept>


#define VA_LENGTH(...) VA_LENGTH_(0, ## __VA_ARGS__,\
    30, 29, 28, 27, 26, 25, 24, 23, 22, 21, \
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11, \
    10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0)

#define VA_LENGTH_(\
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,\
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,\
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, N, ...) N


#define UseVarFunc(Func, ...) Func(VA_LENGTH(__VA_ARGS__), __VA_ARGS__)


#define dump_array3(par) std::cout << std::fixed    << \
  std::setw(10) << std::left   << #par   << ": \t"  << \
  std::setw(10) << std::right  << par[0] << " "     << \
  std::setw(10) << std::right  << par[1] << " "     << \
  std::setw(10) << std::right  << par[2] << std::endl;

#define dump_array4(par) std::cout << std::fixed    << \
  std::setw(10) << std::left   << #par   << ": \t"  << \
  std::setw(10) << std::right  << par[0] << " "     << \
  std::setw(10) << std::right  << par[1] << " "     << \
  std::setw(10) << std::right  << par[2] << " "     << \
  std::setw(10) << std::right  << par[3] << std::endl;


#define dump_var(par)  std::cout << std::fixed << std::setw(20) << std::left << #par << ":\t" << \
  std::setw(10) << std::right << par << std::endl;


#define dump_vector(par, n) \
  std::cout<< #par << " *** start *** \n "; \
  for (int i = 0; i < n; i++) std::cout << " \t " << par[i] << " \n "; \
  std::cout << #par << " *** end *** " << std::endl; 

#define stringvar(var) #var



/// This namespace contains useful functions for analyses
namespace anaUtils{
  
  /// Scale array
  template <typename T> void ScaleArray(const T* srcArr, T* tgtArr, size_t nObj, Float_t factor){
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = factor * srcArr[i];
  }

  /// Copying of an array 
  template <typename T> void CopyArray(const T* srcArr, T* tgtArr, size_t nObj){
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = srcArr[i];
  }

  /// Sum arrays 
  template <typename T> void SumArrays(const T* Arr1, const T* Arr2, T* tgtArr, size_t nObj){
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = Arr1[i] + Arr2[i];
  }

  /// Subtract an array for another
  template <typename T> void SubtractArray(const T* Arr1, const T* Arr2, T* tgtArr, size_t nObj){
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = Arr1[i] - Arr2[i];
  }

  /// Copying of an array 
  template <typename T1, typename T2> void CopyArray(const T1* srcArr, T2* tgtArr, size_t nObj){
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = srcArr[i];
  }

  /// Resize an array, basic case for int(s), float(s) etc 
  template <typename T> void ResizeArray(T* &tgtArr, size_t nObjNew, size_t nObjOrig){
    T* tmp = new T[nObjNew];
    for (size_t i = 0; i < nObjNew; i++) 
      tmp[i] = (i < nObjOrig ? tgtArr[i] : 0);

    delete [] tgtArr;
    tgtArr = tmp;
  }

  /// Resize an array with Weight_h 
  inline void ResizeArray(Weight_h* &tgtArr, size_t nObjNew, size_t nObjOrig){
    Weight_h* tmp = new Weight_h[nObjNew];
    for (size_t i = 0; i < nObjNew; i++) 
      tmp[i] = (i < nObjOrig ? tgtArr[i] : 1);

    delete [] tgtArr;
    tgtArr = tmp;
  }

  /// Resize an array, general case of pointers
  template <typename T> void ResizeArray(T** &tgtArr, size_t nObjNew, size_t nObjOrig){
    T** tmp = new T*[nObjNew];
    for (size_t i = 0; i < nObjNew; i++) 
      tmp[i] = (i < nObjOrig ? tgtArr[i] : NULL);
    delete [] tgtArr;
    tgtArr = tmp;
  }

  /// Keep unique elements
  template <typename T> size_t KeepUniqueElementsInArray(T* &tgtArr, size_t nObjOrig){
    std::set<T> set_tmp;
    for (size_t i = 0; i < nObjOrig; i++){ 
      if (!tgtArr[i]) continue;
      set_tmp.insert(tgtArr[i]);
    }

    size_t set_tmp_size = set_tmp.size();

    T* tmp = new T[set_tmp_size];
    for (size_t i = 0; i < set_tmp_size; i++) 
      tmp[i] = set_tmp[i];
    delete [] tgtArr;
    tgtArr = tmp;
    return set_tmp_size;
  }

  /// Keep unique elements, general case of pointers
  /// Do not consider it to be serted since is machine dependent
  /// a<b is not guaranteed to do one thing or another, but a program that depends on a<b being consistent
  /// will be well behaved (consider adding pointers to a set) 
  template <typename T> size_t KeepUniqueElementsInArray(T** &tgtArr, size_t nObjOrig){
    std::set<T*> set_tmp;
    for (size_t i = 0; i < nObjOrig; i++){ 
      if (!tgtArr[i]) continue;
      set_tmp.insert(tgtArr[i]);
    }

    size_t set_tmp_size = set_tmp.size();

    T** tmp = new T*[set_tmp_size];
    for (size_t i = 0; i < set_tmp_size; i++) 
      tmp[i] = set_tmp[i];
    delete [] tgtArr;
    tgtArr = tmp;
    return set_tmp_size;
  }


  /// Clear an array
  template <typename T> void ClearArray(T** tgtArr, size_t nObj){
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = NULL;
  }

  /// Reserve an array
  template <typename T> void ReserveArray(T** tgtArr, size_t nObj){
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = new T();
  }

  /// Create an array
  template <typename T> void CreateArray(T** &tgtArr, size_t nObj){
    tgtArr = new T*[nObj];
    for (size_t i = 0; i < nObj; i++) 
      tgtArr[i] = NULL;
  }

  /// Create a vector of Int_t of a given size 
  /// This is to avoid using C++11 initialization for the moment
  inline std::vector<Int_t> CreateVectorI(size_t count, ...) {
    std::vector<Int_t> vect;
    if (count == 0) return vect;
    va_list args;
    va_start(args, count);

    for (size_t i = 0; i < count; i++) {
      vect.push_back(va_arg(args, int));
    }
    va_end(args);
    return vect;
  }

  /// Create a vector of floats of a given size 
  /// This is to avoid using C++11 initialization for the moment
  inline std::vector<Float_t> CreateVectorF(size_t count, ...) {
    std::vector<Float_t> vect;
    if (count == 0) return vect;
    va_list args;
    va_start(args, count);

    for (size_t i = 0; i < count; i++) {
      vect.push_back(va_arg(args, double));
    }
    va_end(args);
    return vect;
  }

  /* CINT is not happy with it
     template<typename T> std::vector<T> CreateVector(size_t count, ...) {
     std::vector<T> vect;

     if (count == 0) return vect;
     va_list args;
     va_start(args, count);

     for (size_t i = 0; i < count; i++) {
     vect.push_back(va_arg(args, T));
     }
     va_end(args);

     return vect;
     };
     */


  void VectorToArray(const TLorentzVector& v, Float_t* array);  
  void VectorToArray(const TVector3& v, Float_t* array);

  TVector3 ArrayToTVector3(const Float_t* array);
  TLorentzVector ArrayToTLorentzVector(const Float_t* array);

  /// Scalar product of two Float_t arrays. Provided their size
  Float_t ScalarProduct(Float_t* array1, Float_t* array2, Int_t size=3);

  void ConfigureTreeBranch(TTree* tree, const char* bname, void* add, TBranch** ptr = 0);


  void ReserveArray(Int_t*    arr, int n, Int_t    ini=-999.);
  void ReserveArray(Float_t*  arr, int n, Float_t  ini=-999.);
  void ReserveArray(Weight_h* arr, int n, Weight_h ini=1);


  /// Specific methods with the default parameters
  void CreateArray(Weight_h*            &tgtArr,  int nObj, Weight_h ini=1);
  void CreateArray(Float_t*             &tgtArr,  int nObj, Float_t ini=0);
  void CreateArray(Int_t*               &tgtArr,  int nObj, Int_t ini=0);
  void CreateArray(bool*                &tgtArr,  int nObj, bool ini=true);


  /// Check if a given event was already found
  bool CheckSkimmedEvent(Int_t sRun, Int_t sSubrun, Int_t sEvt);

  /// Extern variables for skimming functionality
  extern std::string skimFileName;
  extern bool breakLoop;

  /// Get The software version from the path of the package
  std::string GetSoftwareVersionFromPath(const std::string& path);

  /// Get the package name provided the name of the executable being run
  std::string GetPackageNameFromProgram(const std::string& program);

  /// Get the package name provided a path containing the package name
  std::string GetPackageNameFromPath(const std::string& path);

  /// Get the vector of packages ordered following the package hierarchy
  std::vector<std::string> GetPackageHierarchy();
  
  /// Get version subtracted package name:
  /// This is when a package comes as packageName_someversion
  /// All after the last "_" is subtracted
  std::string GetVersionSubtractedPackageName(const std::string& name);

  /// Check the validity of values
  bool IsValidValue(Float_t value);
  bool IsValidValue(Double_t value);


  /// An utility fuction to tokenize a string 

  template < class ContainerT > void Tokenize(const std::string& str, ContainerT& tokens,
      const std::string& delimiters = " ", bool trimEmpty = false){

    std::string::size_type pos, lastPos = 0, length = str.length();


    typedef typename ContainerT::value_type value_type;
    typedef typename ContainerT::size_type size_type; 


    while(lastPos < length + 1)
    {
      pos = str.find_first_of(delimiters, lastPos);
      if(pos == std::string::npos)
      {
        pos = length;
      }

      if(pos != lastPos || !trimEmpty)
        tokens.push_back(value_type(str.data()+lastPos,
              (size_type)(pos)-lastPos));

      lastPos = pos + 1;
    }

  }
}
#endif
