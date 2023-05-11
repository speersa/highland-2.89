#ifndef ToFSenseCorrector_h
#define ToFSenseCorrector_h

#include "BaseDataClasses.hxx"

class ToFSenseCorrector {
public:  
  /// Various bits to check which ToF relevant topology has to be checked/present etc
  /// ToF was studied with specific samples and this is why it matters,  more details will
  /// be provided in the dedicated TNs
  enum ToFTopology{
    kToFTopo_FGD1FGD2 = 0, 
    kToFTopo_FGD1P0D_Track,
    kToFTopo_FGD1P0D_Shower, 
    kToFTopo_FGD1ECAL_LAStartFgd_Track, 
    kToFTopo_FGD1ECAL_LAStartFgd_Shower, 
    kToFTopo_FGD1ECAL_LAEndFgd_Track, 
    kToFTopo_FGD1ECAL_LAEndFgd_Shower, 
    kToFTopo_FGD1ECAL_HAStartFgd_Track, 
    kToFTopo_FGD1ECAL_HAStartFgd_Shower, 
    kToFTopo_FGD1ECAL_HAEndFgd_Track, 
    kToFTopo_FGD1ECAL_HAEndFgd_Shower,
    kToFTopo_FGD2ECAL_LAStartFgd_Track,
    kToFTopo_FGD2ECAL_LAStartFgd_Shower,
    kToFTopo_FGD2ECAL_LAEndFgd_Track,
    kToFTopo_FGD2ECAL_LAEndFgd_Shower,
    kToFTopo_FGD2ECAL_HAStartFgd_Track,
    kToFTopo_FGD2ECAL_HAStartFgd_Shower,
    kToFTopo_FGD2ECAL_HAEndFgd_Track,
    kToFTopo_FGD2ECAL_HAEndFgd_Shower,
    kToFTopo_FGD2DSECAL_LAStartFgd_Track,
    kToFTopo_FGD2DSECAL_LAStartFgd_Shower,
    kToFTopo_FGD1FGD2_NoStopFGD1, 
    kToFInvalid,  // will use it for array counter...
  };

  ToFSenseCorrector();

  virtual ~ToFSenseCorrector(){}

  /// Check whether a track is forward going
  static bool IsForward(const AnaTrackB& track);

  /// Check whether a track is forward going
  static bool IsForward(const AnaTrueParticleB& track);

  /// Force a track to be forward going (if needed)
  static void ForceForward(AnaTrackB& track);

  /// Force a collection of tracks to be forward going (if needed)
  static void ForceForward(AnaTrackB* Tracks[], int nTracks);

  /// Check whether a direction(sense) matches ToF
  bool CheckNeedApplyToFBasedFlip(const AnaTrackB& track, ToFTopology topo) const;

  /// Get the relevant ToF topologies that should be used later
  /// to apply any ToF based business to this track
  static Int_t GetToFTopologies(const AnaTrackB& track, ToFSenseCorrector::ToFTopology* topo);

  /// Check whether a given track has ECAL segment, if so only BarrelECAL 
  static bool IsBarrelECAL(const AnaTrackB& track);
  
    /// Check whether a given track has ECAL segment, if so only DSEcal
  static bool IsDSECAL(const AnaTrackB& track);

  /// Setters and getters
  Float_t GetCutValue(ToFSenseCorrector::ToFTopology cut) const{
    if (cut == ToFSenseCorrector::kToFInvalid){
      std::cout << " ToFSenseCorrector::GetCutValue() is called for wrong index " << std::endl; 
      return 0XDEADBEEF;
    }
    return ToFCutValues[cut];
  }

  void SetCutValue(ToFSenseCorrector::ToFTopology cut, Float_t value){
    if (cut == ToFSenseCorrector::kToFInvalid){
      std::cout << " ToFSenseCorrector::SetCutValue() is called for wrong index " << std::endl; 
      return;
    }
    ToFCutValues[cut] = value;
  }



private:

  Float_t ToFCutValues[kToFInvalid];

};

#endif
