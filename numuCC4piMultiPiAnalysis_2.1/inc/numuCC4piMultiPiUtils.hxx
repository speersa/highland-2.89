#ifndef numuCC4piMultiPiUtils_h
#define numuCC4piMultiPiUtils_h

#include "BaseDataClasses.hxx"
#include "DataClasses.hxx"
#include "ToyBoxB.hxx"
#include "CategoriesUtils.hxx"
#include "MultiParticleBox.hxx"
	
namespace numuCC4piMultiPi_utils{
  
  // enum TopoEnum {
	// 	CC_0pi_0meson = 0,
	// 	CC_1pi_0meson = 1, 
	// 	CC_other = 2,
	// 	BKG = 3, 
	// };
  
  // enum MainTrackTopo{
  //   kLAFwd = 0, 
  //   kLABwd, 
  //   kHAFwd, 
  //   kHABwd, 
  //   kUnassigned
  // };


  /// This is FV definition for truth etc
//   const Float_t FGD1FVmin4pi[3] = {57.66, 57.66, 0.};
// 	const Float_t FGD1FVmax4pi[3] = {57.66, 57.66, 0.};

//   const Float_t FGD2FVmin4pi[3] = {57.66, 57.66, 0.};
// 	const Float_t FGD2FVmax4pi[3] = {57.66, 57.66, 0.};
  
// 	const Float_t startFGD1LAFVmin[3] = {57.66, 57.66, 10.125};
// 	const Float_t startFGD1LAFVmax[3] = {57.66, 57.66, 0.};
// 	const Float_t startFGD1HAFVmin[3] = {57.66, 57.66, 10.125};
// 	const Float_t startFGD1HAFVmax[3] = {57.66, 57.66, 10.125};

//   // Under development
//   const Float_t startFGD2LAFVmin[3] = {57.66, 57.66, 10.125};
// 	const Float_t startFGD2LAFVmax[3] = {57.66, 57.66, 0.};
// 	const Float_t startFGD2HAFVmin[3] = {57.66, 57.66, 10.125};
// 	const Float_t startFGD2HAFVmax[3] = {57.66, 57.66, 10.125};
  
  
// 	const Float_t _FVdefminDsECal[3] = {40, 40, 25.};   // "z == 25." to reject peak near the DsECal beginning in both data and MC
// 	const Float_t _FVdefmaxDsECal[3] = {40, 40, 18.17}; // reject last layer in both data and MC
// 	const Float_t _FVdefminFGD2[3]   = {76.88, 38.44, 0.};     //9.61*8, 9.61*4
// 	const Float_t _FVdefmaxFGD2[3]   = {76.88, 38.44, 10.125}; //9.61*8, 9.61*4

	Int_t GetCONTTopology(const AnaTrueVertex& trueVertex, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool IsAntinu = false);
  
  
}

#endif
