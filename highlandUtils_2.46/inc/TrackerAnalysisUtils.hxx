#ifndef TrackerAnalysisUtils_h
#define TrackerAnalysisUtils_h

#include "SubDetId.hxx"
#include "DataClasses.hxx"

/// This namespace contains useful functions for analyses. 
/// This is in addition to those defined in psycheUtils
namespace anaUtils{

  /// Get the FGD layer based on the detector info
  Float_t GetFGDLayer(const Float_t* pos, SubDetId::SubDetEnum det = SubDetId::kFGD);
  
  /// Check whether a layer is a valid detector layer
  bool IsValidFgdDetLayer(Float_t layer); 

  /// Getting FGD layer with an ability to move the position along Z until a
  /// valid (here consider physical X or Y layers, water is not considered) is found: the closest one (upstream vs downstream) is taken 
  Float_t GetClosestFgdDetLayer(const Float_t* pos, Float_t& distZ, SubDetId::SubDetEnum det = SubDetId::kFGD, Float_t step = 0.5); // default step is 0.5 mm
  
  /// Get the FGD2 layer based on some special definition used by CC0Pi xsec
  /// (LM, MB, SD)
  Float_t GetFGD2LayerCC0PiXSec(const Float_t* pos);
  
  Float_t GetClosestFgd2DetLayerCC0PiXSec(const Float_t* pos, Float_t& distZ, Float_t step = 0.5);
   
  
  /// Based on the layer decide whether it is X or Y
  bool IsFgdXLayer(Float_t layer);
  bool IsFgdYLayer(Float_t layer);
  bool IsFgdWaterLayer(Float_t layer);
  
  /// Based on the position decide whether it is X or Y
  bool IsFgdXLayer(const Float_t* pos, SubDetId::SubDetEnum det = SubDetId::kFGD);
  bool IsFgdYLayer(const Float_t* pos, SubDetId::SubDetEnum det = SubDetId::kFGD);
  bool IsFgdWaterLayer(const Float_t* pos);
  
  /// Check whether a given reco track is bwd migrated based on the info of the
  /// corresponding true particle: -1 - undefined, 0 - non-migrated, 1 -
  /// migrated
  Int_t IsFgdBwdMigrated(const AnaParticleB& track, SubDetId::SubDetEnum det = SubDetId::kFGD);
   
  /// Check whether a given object is bwd migrated given the recon vertex:
  /// The corresponding first particle will be used to retrieve the info
  ///  -1 - undefined, 0 - non-migrated, 1 - migrated
  Int_t IsFgdBwdMigrated(const AnaVertexB& vertex, SubDetId::SubDetEnum det = SubDetId::kFGD);

  
}
#endif


