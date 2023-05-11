#include "ToFSenseCorrector.hxx"
#include "Parameters.hxx"
#include "BasicUtils.hxx"
#include "DetectorDefinition.hxx"
#include "ND280AnalysisUtils.hxx"
#include "CutUtils.hxx"
// #define DEBUG


//********************************************************************
ToFSenseCorrector::ToFSenseCorrector(){
  //********************************************************************

  // Read various parameters
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1FGD2]                     = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1FGD2"                     );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1P0D_Track]                = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1P0D_Track"                );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1P0D_Shower]               = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1P0D_Shower"               );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track]    = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_LAStartFgd_Track"    );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower]   = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_LAStartFgd_Shower"   );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track]      = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_LAEndFgd_Track"      );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower]     = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_LAEndFgd_Shower"     );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track]    = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_HAStartFgd_Track"    );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower]   = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_HAStartFgd_Shower"   );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track]      = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_HAEndFgd_Track"      );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower]     = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1ECAL_HAEndFgd_Shower"     );
   
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track]    = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_LAStartFgd_Track"    );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower]   = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_LAStartFgd_Shower"   );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track]      = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_LAEndFgd_Track"      );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower]     = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_LAEndFgd_Shower"     );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track]    = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_HAStartFgd_Track"    );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower]   = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_HAStartFgd_Shower"   );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track]      = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_HAEndFgd_Track"      );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower]     = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2ECAL_HAEndFgd_Shower"     );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track]  = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2DSECAL_LAStartFgd_Track"  );
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower] = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD2DSECAL_LAStartFgd_Shower" );
  
  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1]          = (Float_t)ND::params().GetParameterD("psycheND280Utils.ToF.FGD1FGD2_NoStopFGD1"          );
  


}

//********************************************************************
bool ToFSenseCorrector::IsForward(const AnaTrackB& track){
  //********************************************************************

  // check if a track is forward (in Z) going
  // need something fancier?

  return track.PositionStart[2] < track.PositionEnd[2];  
}


//********************************************************************
bool ToFSenseCorrector::IsForward(const AnaTrueParticleB& track){
  //********************************************************************

  // check if a track is forward (in Z) going
  // need something fancier?

  return track.Position[2] < track.PositionEnd[2];  
}


//********************************************************************
void ToFSenseCorrector::ForceForward(AnaTrackB& track){
  //********************************************************************

  if (!IsForward(track)) track.Flip();  
}


//********************************************************************
void ToFSenseCorrector::ForceForward(AnaTrackB* Tracks[], int nTracks){
  //********************************************************************
  for (int i=0; i<nTracks; i++){
    if (!Tracks[i]) continue;
    ForceForward(*Tracks[i]);
  }    
}


//********************************************************************
bool ToFSenseCorrector::CheckNeedApplyToFBasedFlip(const AnaTrackB& track, ToFSenseCorrector::ToFTopology topo) const{
  //********************************************************************
#ifdef DEBUG    
  for (int i =0;i < 21; i++){
    std::cout << "ToFCutValues[i]: " << i << " " << ToFCutValues[i] << std::endl;
  }
#endif

  /* The ToF cuts were studied to select Bwd going tracks in case of FGD1-FGD2/P0D/ECal ToF(1) that end in an FGD and
   * those that start from FGD for FGD-ECal ToF (2) cases. So here the following checks are done:
   * TOF value ToF.Det1_Det2 is t_det1 - t_det2
   * all topologies were initially studied by forcing tracks to be forward (in Z) going
   * then we have cases: tracks starts in an FGD and track ends in an FGD
   * track should be reverese in case:
   * track ends in an FGD,  e.g. P0D-FGD1 -- tP0D - tFGD1
   * isForward but ToF1 > cut
   * isBackward but ToF1 < cut
   * track starts in an FGD,  e.g. ECAL-FGD1 -- tECAL - tFGD1
   * isForward but TOF2 < cut
   * isBackward but TOF2 > cut
   * if not one of the above or not valid ToF --> do not reverse
   */

  bool isForward = IsForward(track);

  //FGD1-FGD2
  if (topo == kToFTopo_FGD1FGD2) {
#ifdef DEBUG    
    std::cout << "track.ToF.FGD1_FGD2: " << track.ToF.FGD1_FGD2 << std::endl;
#endif
    if ((track.ToF.FGD1_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1FGD2] && !isForward) ||
        (track.ToF.FGD1_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1FGD2] &&  isForward)) return true;
  }

  // P0D-FGD1 
  if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Track) {
#ifdef DEBUG    
        std::cout << "kToFTopo_FGD1P0D_Track" << std::endl;
        std::cout << "track.ToF.P0D_FGD1: " << track.ToF.P0D_FGD1 << std::endl;
#endif
    if ((track.ToF.P0D_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1P0D_Track] && !isForward) ||
        (track.ToF.P0D_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1P0D_Track] &&  isForward)) return true;
  }
  
  if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1P0D_Shower" << std::endl;
#endif
    if ((track.ToF.P0D_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1P0D_Shower] && !isForward) ||
        (track.ToF.P0D_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1P0D_Shower] &&  isForward)) return true;
  }

  // ECal-FGD1 -> We apply the flip for both track&shower like cases
  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_LAStartFgd_Track" << std::endl;
#endif
    if ((track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track] &&  isForward)) return true;
  }
  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_LAStartFgd_Shower" << std::endl;
#endif
    if ((track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower] &&  isForward)) return true;
  }

  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_LAEndFgd_Track" << std::endl;
#endif
    if ((track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track] &&  isForward)) return true;
  }
  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_LAEndFgd_Track" <<std::endl;
#endif
    if ((track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower] &&  isForward)) return true;
  } 

  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_HAStartFgd_Track" << std::endl;
#endif
    if ((track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track] &&  isForward)) return true;
  }  
  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_HAStartFgd_Shower" << std::endl;
#endif
    if ((track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower] &&  isForward)) return true;
  }  

  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_HAEndFgd_Track" << std::endl;
#endif
    if ((track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track] &&  isForward)) return true;
  }    
  if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD1ECAL_HAEndFgd_Shower" << std::endl;
#endif
    if ((track.ToF.ECal_FGD1 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD1 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower] &&  isForward)) return true;
  }  


  // ECal-FGD2 -> We apply the flip for both track&shower like cases
  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_LAStartFgd_Track" << std::endl;
#endif
    if ((track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track] &&  isForward)) return true;
  }
  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_LAStartFgd_Shower" << std::endl;
#endif
    if ((track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower] &&  isForward)) return true;
  }

  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_LAEndFgd_Track" << std::endl;
#endif
    if ((track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track] &&  isForward)) return true;
  }
  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_LAEndFgd_Shower" << std::endl;
#endif
    if ((track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower] &&  isForward)) return true;
  }

  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_HAStartFgd_Track" << std::endl;
#endif

    if ((track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track] &&  isForward)) return true;
  }
  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_HAStartFgd_Shower" << std::endl;
#endif

    if ((track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower] &&  isForward)) return true;
  }

  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_HAEndFgd_Track: " << track.ToF.ECal_FGD2 << " " << ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track] << std::endl;
#endif
    // std::cout << "kToFTopo_FGD2ECAL_HAEndFgd_Track: " << track.ToF.ECal_FGD2 << " " << ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track] << std::endl;

    if ((track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track] && !isForward) ||
        (track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track] &&  isForward)) return true;
  }
  if (topo==ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2ECAL_HAEndFgd_Shower" << std::endl;
#endif
    // std::cout << "kToFTopo_FGD2ECAL_HAEndFgd_Shower: " << track.ToF.ECal_FGD2 << " " << ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower] << std::endl;

    if ((track.ToF.ECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower] && !isForward) ||
        (track.ToF.ECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower] &&  isForward)) return true;
  }

  // DSECal-FGD2 -> We apply the flip for both track&shower like cases
  if (topo==ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2DSECAL_LAStartFgd_Track: " << track.ToF.DSECal_FGD2 << std::endl;
#endif
    if ((track.ToF.DSECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track] && !isForward) ||
        (track.ToF.DSECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track] &&  isForward)) return true;
  }
  if (topo==ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower) {
#ifdef DEBUG    
    std::cout << "kToFTopo_FGD2DSECAL_LAStartFgd_Shower" << std::endl;
#endif
    if ((track.ToF.DSECal_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower] && !isForward) ||
        (track.ToF.DSECal_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower] &&  isForward)) return true;
  }

  //FGD1-FGD2 special topo
  if (topo==kToFTopo_FGD1FGD2_NoStopFGD1) {
    if ((track.ToF.FGD1_FGD2 <= ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1] && !isForward) ||
        (track.ToF.FGD1_FGD2 >  ToFCutValues[ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1] &&  isForward)) return true;
  }

  // Everything is fine or cannot say that any flipping is needed
  return false;

}

//********************************************************************
Int_t ToFSenseCorrector::GetToFTopologies(const AnaTrackB& track, ToFSenseCorrector::ToFTopology* topo){
  //********************************************************************
  // std::cout << "ToFSenseCorrector::GetToFTopologies(const AnaTrackB& track, ToFSenseCorrector::ToFTopology* topo)" << std::endl;
  // This function returns which type of ToF check/cut (there may be several involved since a 
  // track can cross several sub-detectors and the check/cut can also depend on the type of track, 
  // e.g. track/shower for the same topology)

  // The current values (Sept 2016,  details in TN-245) used were retrieved using the track being forced to be forward going in Z 
  // hence the relevant type should be checked based on the position of the upstream/downstream (in Z) ends,  no matter their correspondence 
  // to an actual start/end point

  // For the moment (April 2017), only one topology is relevant since this was
  // the way how the numbers were obtained for TN-245
  Int_t count = 0;

  const Float_t* pos_upstream;
  const Float_t* pos_downstream;
  bool forward = IsForward(track);
  pos_upstream   = forward ? track.PositionStart : track.PositionEnd;
  pos_downstream = forward ? track.PositionEnd   : track.PositionStart;

  // Four different topologies -> Fwd, HAFwd, Bwd, HABwd
  // Studied with FWD sample
  if (anaUtils::InDetVolume(SubDetId::kFGD1, pos_upstream)) {
    // FWD LA sample
    if (cutUtils::TrackQualityCut(track)) {
      if (track.ToF.Flag_FGD1_FGD2){
        topo[count++] = kToFTopo_FGD1FGD2;
      }
      if (track.ToF.Flag_ECal_FGD1) {
        if (ToFSenseCorrector::IsBarrelECAL(track)) {
          if (track.ECALSegments[0]->NNodes == 1){ 
            topo[count++] = kToFTopo_FGD1ECAL_LAStartFgd_Shower;
          }
          if (track.ECALSegments[0]->NNodes >  1){ 
            topo[count++] = kToFTopo_FGD1ECAL_LAStartFgd_Track;
          }
        }
      }
    }
    // FWD HA sample
    else {
      if (cutUtils::StoppingBrECALorSMRDCut(pos_downstream)!=-1) {
      if (true) {

        if (track.ToF.Flag_ECal_FGD1) {
          if (ToFSenseCorrector::IsBarrelECAL(track)) {

            if (track.ECALSegments[0]->NNodes == 1){
              topo[count++] = kToFTopo_FGD1ECAL_HAStartFgd_Shower;
            }
            if (track.ECALSegments[0]->NNodes >  1){
              topo[count++] = kToFTopo_FGD1ECAL_HAStartFgd_Track;
            }
          }
        }
      }
    }
    }
  }
  //Studied with BWD sample
  else if (anaUtils::InDetVolume(SubDetId::kFGD1, pos_downstream)) {
    // BWD LA sample
    if (cutUtils::TrackQualityCut(track)) {
      if (track.ToF.Flag_P0D_FGD1) {
        if (track.nP0DSegments > 0) {
          if (track.P0DSegments[0]) {
            if (track.P0DSegments[0]->NNodes ==  1){
              topo[count++] = kToFTopo_FGD1P0D_Shower; 
            }
            if (track.P0DSegments[0]->NNodes >  1){
              topo[count++] = kToFTopo_FGD1P0D_Track; 
            }
          }
        }
      }
      else if (track.ToF.Flag_ECal_FGD1) {
        if (ToFSenseCorrector::IsBarrelECAL(track)) {
          if (track.ECALSegments[0]->NNodes == 1){
            topo[count++] = kToFTopo_FGD1ECAL_LAEndFgd_Shower;
          }
          if (track.ECALSegments[0]->NNodes >  1){
            topo[count++] = kToFTopo_FGD1ECAL_LAEndFgd_Track;
          };
        }
      }
    }
    // BWD HA sample
    else {
      // std::cout << "cutUtils::StoppingBrECALorSMRDCut(pos_upstream) == " << pos_upstream[0]<< pos_upstream[1]<< pos_upstream[2]  << " " << cutUtils::StoppingBrECALorSMRDCut(pos_upstream) << std::endl; 
      if (cutUtils::StoppingBrECALorSMRDCut(pos_upstream)!=-1) {
        if (track.ToF.Flag_ECal_FGD1) {
          if (ToFSenseCorrector::IsBarrelECAL(track)) {
            if (track.ECALSegments[0]->NNodes == 1){ 
              topo[count++] = kToFTopo_FGD1ECAL_HAEndFgd_Shower;
            }
            if (track.ECALSegments[0]->NNodes >  1){ 
              topo[count++] = kToFTopo_FGD1ECAL_HAEndFgd_Track;
            }
          }
        }
      }
    }
  }
  else if (anaUtils::InDetVolume(SubDetId::kFGD2, pos_upstream)) {
    if (cutUtils::TrackQualityCut(track)) {
      if (track.ToF.Flag_ECal_FGD2) {
        if (ToFSenseCorrector::IsBarrelECAL(track)) {
          if (track.ECALSegments[0]->NNodes == 1) topo[count++] = kToFTopo_FGD2ECAL_LAStartFgd_Shower;
          if (track.ECALSegments[0]->NNodes >  1) topo[count++] = kToFTopo_FGD2ECAL_LAStartFgd_Track;
        }
      }
      else if (track.ToF.Flag_DSECal_FGD2) {
        if (ToFSenseCorrector::IsDSECAL(track)) {
          if (track.ECALSegments[0]->NNodes == 1) topo[count++] = kToFTopo_FGD2DSECAL_LAStartFgd_Shower;
          if (track.ECALSegments[0]->NNodes >  1) topo[count++] = kToFTopo_FGD2DSECAL_LAStartFgd_Track;
        }
      }
    }
    else {
      if (cutUtils::StoppingBrECALorSMRDCut(pos_downstream)!=-1) {
        if (track.ToF.Flag_ECal_FGD2) {
          if (ToFSenseCorrector::IsBarrelECAL(track)) {
            if (track.ECALSegments[0]->NNodes == 1) topo[count++] = kToFTopo_FGD2ECAL_HAStartFgd_Shower;
            if (track.ECALSegments[0]->NNodes >  1) topo[count++] = kToFTopo_FGD2ECAL_HAStartFgd_Track;
          }
        }
      }
    }
  }
  else if (anaUtils::InDetVolume(SubDetId::kFGD2, pos_downstream)) {
    if (cutUtils::TrackQualityCut(track)) {
      if (track.ToF.Flag_FGD1_FGD2 && !anaUtils::InDetVolume(SubDetId::kFGD1, pos_upstream)) topo[count++] = kToFTopo_FGD1FGD2_NoStopFGD1;
      if (track.ToF.Flag_ECal_FGD2) {
        if (ToFSenseCorrector::IsBarrelECAL(track)) {
          if (track.ECALSegments[0]->NNodes == 1) topo[count++] = kToFTopo_FGD2ECAL_LAEndFgd_Shower;
          if (track.ECALSegments[0]->NNodes >  1) topo[count++] = kToFTopo_FGD2ECAL_LAEndFgd_Track;
        }
      }
    }
    else {
      if (cutUtils::StoppingBrECALorSMRDCut(pos_upstream)!=-1) {
        if (track.ToF.Flag_ECal_FGD2) {
          if (ToFSenseCorrector::IsBarrelECAL(track)) {
            if (track.ECALSegments[0]->NNodes == 1) topo[count++] = kToFTopo_FGD2ECAL_HAEndFgd_Shower;
            if (track.ECALSegments[0]->NNodes >  1) topo[count++] = kToFTopo_FGD2ECAL_HAEndFgd_Track;
          }
        }
      }
    }
  }

  return count;

}

//********************************************************************
bool ToFSenseCorrector::IsBarrelECAL(const AnaTrackB& track){
  //********************************************************************

  if (track.nECALSegments < 1) return false; 

  int count = (int)(anaUtils::TrackUsesDet(track, SubDetId::kTopTECAL)) + 
    (int)(anaUtils::TrackUsesDet(track, SubDetId::kBottomTECAL))      + 
    (int)(anaUtils::TrackUsesDet(track, SubDetId::kLeftTECAL))        + 
    (int)(anaUtils::TrackUsesDet(track, SubDetId::kRightTECAL));
  if (count != 1) return false;

  return track.ECALSegments[0];

}

//********************************************************************
bool ToFSenseCorrector::IsDSECAL(const AnaTrackB& track){
  //********************************************************************

  if (track.nECALSegments < 1) return false;

  if (!anaUtils::TrackUsesDet(track, SubDetId::kDSECAL)) return false;

  return track.ECALSegments[0];

}
