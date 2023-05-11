#include "SampleId.hxx"


//*********************************************************
std::string SampleId::ConvertSample(SampleEnum sample){
  //*********************************************************

  std::string ssample="";
  // FGD1 numu
  if      (sample == kUnassigned)                       ssample = "Unassigned";
  else if (sample == kFGD1NuMuCC)                       ssample = "FGD1 numuCC inclusive";
  else if (sample == kFGD1NuMuCCQE)                     ssample = "FGD1 numuCC QE";
  
  else if (sample == kFGD1NuMuCC0Pi)                    ssample = "FGD1 numuCC 0pi";
  
  else if (sample == kFGD1NuMuCC0PiNoPhoton)            ssample = "FGD1 numuCC 0pi no photon";
 
  else if (sample == kFGD1NuMuCC0Pi0Protons)            ssample = "FGD1 numuCC 0pi 0 protons";
  else if (sample == kFGD1NuMuCC0PiNProtons)            ssample = "FGD1 numuCC 0pi N protons";
  
  else if (sample == kFGD1NuMuCC0Pi0ProtonsNoPhoton)    ssample = "FGD1 numuCC 0pi 0 protons no photon";
  else if (sample == kFGD1NuMuCC0PiNProtonsNoPhoton)    ssample = "FGD1 numuCC 0pi N protons no photon";

  else if (sample == kFGD1NuMuCC1Pi)                    ssample = "FGD1 numuCC 1pi";
  
  else if (sample == kFGD1NuMuCC1PiNoPhoton)            ssample = "FGD1 numuCC 1pi no photon";

  else if (sample == kFGD1NuMuCCOther)                  ssample = "FGD1 numuCC other";
  
  else if (sample == kFGD1NuMuCCOtherNoPhoton)          ssample = "FGD1 numuCC other no photon";

  else if (sample == kFGD1NuMuCCPhoton)                 ssample = "FGD1 numuCC photon";

  // FGD2 numu
  else if (sample == kFGD2NuMuCC)                       ssample = "FGD2 numuCC inclusive";
  
  else if (sample == kFGD2NuMuCC0Pi)                    ssample = "FGD2 numuCC 0pi";

  else if (sample == kFGD2NuMuCC0PiNoPhoton)            ssample = "FGD2 numuCC 0pi no photon";
  
  
  else if (sample == kFGD2NuMuCC0Pi0Protons)            ssample = "FGD2 numuCC 0pi 0 protons";
  else if (sample == kFGD2NuMuCC0PiNProtons)            ssample = "FGD2 numuCC 0pi N protons";
  
  
  else if (sample == kFGD2NuMuCC0Pi0ProtonsNoPhoton)    ssample = "FGD2 numuCC 0pi 0 protons no photon";
  else if (sample == kFGD2NuMuCC0PiNProtonsNoPhoton)    ssample = "FGD2 numuCC 0pi N protons no photon";
  

  else if (sample == kFGD2NuMuCC1Pi)                    ssample = "FGD2 numuCC 1pi";
  
  else if (sample == kFGD2NuMuCC1PiNoPhoton)            ssample = "FGD2 numuCC 1pi no photon";
  
  else if (sample == kFGD2NuMuCCOther)                  ssample = "FGD2 numuCC other";
  
  else if (sample == kFGD2NuMuCCOtherNoPhoton)          ssample = "FGD2 numuCC other no photon";

  else if (sample == kFGD2NuMuCCPhoton)                 ssample = "FGD2 numuCC photon";
  

  else if (sample == kFGD1NuECC)                        ssample = "FGD1 nueCC inclusive";
  else if (sample == kFGD1NuECC0Pi)                     ssample = "FGD1 nueCC 0pi";
  else if (sample == kFGD1NuECCOther)                   ssample = "FGD1 nueCC other";

  else if (sample == kFGD2NuECC)                        ssample = "FGD2 nueCC inclusive";
  else if (sample == kFGD2NuECC0Pi)                     ssample = "FGD2 nueCC 0pi";
  else if (sample == kFGD2NuECCOther)                   ssample = "FGD2 nueCC other";

  else if (sample == kFGD1AntiNuMuCC)                   ssample = "FGD1 anti-numuCC inclusive";
  else if (sample == kFGD1AntiNuMuCC1Track)             ssample = "FGD1 anti-numuCC QE";
  else if (sample == kFGD1AntiNuMuCCNTracks)            ssample = "FGD1 anti-numuCC nQE";
  else if (sample == kFGD1AntiNuMuCC0Pi)                ssample = "FGD1 anti-numuCC 0pi";
  else if (sample == kFGD1AntiNuMuCC1Pi)                ssample = "FGD1 anti-numuCC 1pi";
  else if (sample == kFGD1AntiNuMuCCOther)              ssample = "FGD1 anti-numuCC other";

  else if (sample == kFGD2AntiNuMuCC)                   ssample = "FGD2 anti-numuCC inclusive";
  else if (sample == kFGD2AntiNuMuCC1Track)             ssample = "FGD2 anti-numuCC 1 track";
  else if (sample == kFGD2AntiNuMuCCNTracks)            ssample = "FGD2 anti-numuCC N tracks";
  else if (sample == kFGD2AntiNuMuCC0Pi)                ssample = "FGD2 anti-numuCC 0pi";
  else if (sample == kFGD2AntiNuMuCC1Pi)                ssample = "FGD2 anti-numuCC 1pi";
  else if (sample == kFGD2AntiNuMuCCOther)              ssample = "FGD2 anti-numuCC other";

  else if (sample == kFGD1NuMuBkgInAntiNuModeCC)        ssample = "FGD1 NuMuBkg CC inclusive in AntiNu Mode";
  else if (sample == kFGD1NuMuBkgInAntiNuModeCC1Track)  ssample = "FGD1 NuMuBkg CCQE in AntiNu Mode";
  else if (sample == kFGD1NuMuBkgInAntiNuModeCCNTracks) ssample = "FGD1 NuMuBkg CCnQE in AntiNu Mode";
  else if (sample == kFGD1NuMuBkgInAntiNuModeCC0Pi)     ssample = "FGD1 NuMuBkg CC0pi in AntiNu Mode";
  else if (sample == kFGD1NuMuBkgInAntiNuModeCC1Pi)     ssample = "FGD1 NuMuBkg CC1pi in AntiNu Mode";
  else if (sample == kFGD1NuMuBkgInAntiNuModeCCOther)   ssample = "FGD1 NuMuBkg CCother in AntiNu Mode";

  else if (sample == kFGD2NuMuBkgInAntiNuModeCC)        ssample = "FGD2 NuMuBkg CC inclusive in AntiNu Mode";
  else if (sample == kFGD2NuMuBkgInAntiNuModeCC1Track)  ssample = "FGD2 NuMuBkg CCQE in AntiNu Mode";
  else if (sample == kFGD2NuMuBkgInAntiNuModeCCNTracks) ssample = "FGD2 NuMuBkg CCnQE in AntiNu Mode";
  else if (sample == kFGD2NuMuBkgInAntiNuModeCC0Pi)     ssample = "FGD2 NuMuBkg CC0pi in AntiNu Mode";
  else if (sample == kFGD2NuMuBkgInAntiNuModeCC1Pi)     ssample = "FGD2 NuMuBkg CC1pi in AntiNu Mode";
  else if (sample == kFGD2NuMuBkgInAntiNuModeCCOther)   ssample = "FGD2 NuMuBkg CCother in AntiNu Mode";

  else if (sample == kFGD1AntiNuECC)                    ssample = "FGD1 anti-nueCC inclusive";
  else if (sample == kFGD1AntiNuECC0Pi)                 ssample = "FGD1 anti-nueCC 0pi";
  else if (sample == kFGD1AntiNuECCOther)               ssample = "FGD1 anti-nueCC other";

  else if (sample == kFGD2AntiNuECC)                    ssample = "FGD2 anti-nueCC inclusive";
  else if (sample == kFGD2AntiNuECC0Pi)                 ssample = "FGD2 anti-nueCC 0pi";
  else if (sample == kFGD2AntiNuECCOther)               ssample = "FGD2 anti-nueCC other";

  else if (sample == kFGD1Gamma)                        ssample = "FGD1 gamma FHC";
  else if (sample == kFGD2Gamma)                        ssample = "FGD2 gamma FHC";

  else if (sample == kFGD1GammaInAntiNuMode)            ssample = "FGD1 gamma RHC";
  else if (sample == kFGD2GammaInAntiNuMode)            ssample = "FGD2 gamma RHC";
  else if (sample == kFGD1AntiNuEBkgInNuModeCC)         ssample = "FGD1 Anti-NuE Bkg In NuMode CC";
  else if (sample == kFGD1AntiNuEBkgInNuModeCC0Pi)      ssample = "FGD1 Anti-NuE Bkg In NuMode CC0Pi";
  else if (sample == kFGD1AntiNuEBkgInNuModeCCOther)    ssample = "FGD1 Anti-NuE Bkg In NuMode CCOther";
  else if (sample == kFGD2AntiNuEBkgInNuModeCC)         ssample = "FGD2 Anti-NuE Bkg In NuMode CC";
  else if (sample == kFGD2AntiNuEBkgInNuModeCC0Pi)      ssample = "FGD2 Anti-NuE Bkg In NuMode CC0Pi";
  else if (sample == kFGD2AntiNuEBkgInNuModeCCOther)    ssample = "FGD2 Anti-NuE Bkg In NuMode CCOther";
  else if (sample == kFGD1NuEBkgInAntiNuModeCC)         ssample = "FGD1 NuE Bkg In Anti NuMode CC";
  else if (sample == kFGD1NuEBkgInAntiNuModeCC0Pi)      ssample = "FGD1 NuE Bkg In Anti NuMode CC0Pi";
  else if (sample == kFGD1NuEBkgInAntiNuModeCCOther)    ssample = "FGD1 NuE Bkg In Anti NuMode CCOther";
  else if (sample == kFGD2NuEBkgInAntiNuModeCC)         ssample = "FGD2 NuE Bkg In Anti NuMode CC";
  else if (sample == kFGD2NuEBkgInAntiNuModeCC0Pi)      ssample = "FGD2 NuE Bkg In Anti NuMode CC0Pi";
  else if (sample == kFGD2NuEBkgInAntiNuModeCCOther)    ssample = "FGD2 NuE Bkg In Anti NuMode CCOther";

  else if (sample == kFGD1NuMuCC0PiFwd)                    ssample = "FGD1 numuCC 0pi Fwd";
  else if (sample == kFGD1NuMuCC0PiBwd)                    ssample = "FGD1 numuCC 0pi Bwd";
  else if (sample == kFGD1NuMuCC0PiHAFwd)                    ssample = "FGD1 numuCC 0pi HAFwd";
  else if (sample == kFGD1NuMuCC0PiHABwd)                    ssample = "FGD1 numuCC 0pi HABwd";
  else if (sample == kFGD1NuMuCC1PiFwd)                    ssample = "FGD1 numuCC 1Pi Fwd";
  else if (sample == kFGD1NuMuCC1PiBwd)                    ssample = "FGD1 numuCC 1Pi Bwd";
  else if (sample == kFGD1NuMuCC1PiHAFwd)                    ssample = "FGD1 numuCC 1Pi HAFwd";
  else if (sample == kFGD1NuMuCC1PiHABwd)                    ssample = "FGD1 numuCC 1Pi HABwd";
  else if (sample == kFGD1NuMuCCOtherFwd)                    ssample = "FGD1 numuCC Other Fwd";
  else if (sample == kFGD1NuMuCCOtherBwd)                    ssample = "FGD1 numuCC Other Bwd";
  else if (sample == kFGD1NuMuCCOtherHAFwd)                    ssample = "FGD1 numuCC Other HAFwd";
  else if (sample == kFGD1NuMuCCOtherHABwd)                    ssample = "FGD1 numuCC Other HABwd";


  else if (sample == kFGD1NuMuCC0PiFwdNoPhoton)                    ssample = "FGD1 numuCC 0pi Fwd NoPhoton";
  else if (sample == kFGD1NuMuCC0PiBwdNoPhoton)                    ssample = "FGD1 numuCC 0pi Bwd NoPhoton";
  else if (sample == kFGD1NuMuCC0PiHAFwdNoPhoton)                    ssample = "FGD1 numuCC 0pi HAFwd NoPhoton";
  else if (sample == kFGD1NuMuCC0PiHABwdNoPhoton)                    ssample = "FGD1 numuCC 0pi HABwd NoPhoton";
  else if (sample == kFGD1NuMuCC1PiFwdNoPhoton)                    ssample = "FGD1 numuCC 1Pi Fwd NoPhoton";
  else if (sample == kFGD1NuMuCC1PiBwdNoPhoton)                    ssample = "FGD1 numuCC 1Pi Bwd NoPhoton";
  else if (sample == kFGD1NuMuCC1PiHAFwdNoPhoton)                    ssample = "FGD1 numuCC 1Pi HAFwd NoPhoton";
  else if (sample == kFGD1NuMuCC1PiHABwdNoPhoton)                    ssample = "FGD1 numuCC 1Pi HABwd NoPhoton";
  else if (sample == kFGD1NuMuCCOtherFwdNoPhoton)                    ssample = "FGD1 numuCC Other Fwd NoPhoton";
  else if (sample == kFGD1NuMuCCOtherBwdNoPhoton)                    ssample = "FGD1 numuCC Other Bwd NoPhoton";
  else if (sample == kFGD1NuMuCCOtherHAFwdNoPhoton)                    ssample = "FGD1 numuCC Other HAFwd NoPhoton";
  else if (sample == kFGD1NuMuCCOtherHABwdNoPhoton)                    ssample = "FGD1 numuCC Other HABwd ";

  else if (sample == kFGD1NuMuCCPhotonFwd)                    ssample = "FGD1 numuCC Photon Fwd";
  else if (sample == kFGD1NuMuCCPhotonBwd)                    ssample = "FGD1 numuCC Photon Bwd";
  else if (sample == kFGD1NuMuCCPhotonHAFwd)                    ssample = "FGD1 numuCC Photon HAFwd";
  else if (sample == kFGD1NuMuCCPhotonHABwd)                    ssample = "FGD1 numuCC Photon HABwd";

  else if (sample == kFGD1NuMuCC0PiFwd0ProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi Fwd NoPhoton No Protons";
  else if (sample == kFGD1NuMuCC0PiFwdNProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi Fwd NoPhoton N Protons";

  else if (sample == kFGD1NuMuCC0PiBwd0ProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi Bwd NoPhoton No Protons";
  else if (sample == kFGD1NuMuCC0PiBwdNProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi Bwd NoPhoton N Protons";

  else if (sample == kFGD1NuMuCC0PiHAFwd0ProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi HAFwd NoPhoton No Protons";
  else if (sample == kFGD1NuMuCC0PiHAFwdNProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi HAFwd NoPhoton N Protons";

  else if (sample == kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi HABwd NoPhoton No Protons";
  else if (sample == kFGD1NuMuCC0PiHABwdNProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi HABwd NoPhoton N Protons";


  else if (sample == kFGD1NuMuCC0PiHA0ProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi HA NoPhoton No Protons";
  else if (sample == kFGD1NuMuCC0PiHANProtonsNoPhoton)                    ssample = "FGD1 numuCC 0pi HA NoPhoton N Protons";


  else if (sample == kFGD2NuMuCC0PiFwdNoPhoton)                    ssample = "FGD2 numuCC 0pi Fwd NoPhoton";
  else if (sample == kFGD2NuMuCC0PiBwdNoPhoton)                    ssample = "FGD2 numuCC 0pi Bwd NoPhoton";
  else if (sample == kFGD2NuMuCC0PiHAFwdNoPhoton)                    ssample = "FGD2 numuCC 0pi HAFwd NoPhoton";
  else if (sample == kFGD2NuMuCC0PiHABwdNoPhoton)                    ssample = "FGD2 numuCC 0pi HABwd NoPhoton";
  else if (sample == kFGD2NuMuCC1PiFwdNoPhoton)                    ssample = "FGD2 numuCC 1Pi Fwd NoPhoton";
  else if (sample == kFGD2NuMuCC1PiBwdNoPhoton)                    ssample = "FGD2 numuCC 1Pi Bwd NoPhoton";
  else if (sample == kFGD2NuMuCC1PiHAFwdNoPhoton)                    ssample = "FGD2 numuCC 1Pi HAFwd NoPhoton";
  else if (sample == kFGD2NuMuCC1PiHABwdNoPhoton)                    ssample = "FGD2 numuCC 1Pi HABwd NoPhoton";
  else if (sample == kFGD2NuMuCCOtherFwdNoPhoton)                    ssample = "FGD2 numuCC Other Fwd NoPhoton";
  else if (sample == kFGD2NuMuCCOtherBwdNoPhoton)                    ssample = "FGD2 numuCC Other Bwd NoPhoton";
  else if (sample == kFGD2NuMuCCOtherHAFwdNoPhoton)                    ssample = "FGD2 numuCC Other HAFwd NoPhoton";
  else if (sample == kFGD2NuMuCCOtherHABwdNoPhoton)                    ssample = "FGD2 numuCC Other HABwd ";

  else if (sample == kFGD2NuMuCCPhotonFwd)                    ssample = "FGD2 numuCC Photon Fwd";
  else if (sample == kFGD2NuMuCCPhotonBwd)                    ssample = "FGD2 numuCC Photon Bwd";
  else if (sample == kFGD2NuMuCCPhotonHAFwd)                    ssample = "FGD2 numuCC Photon HAFwd";
  else if (sample == kFGD2NuMuCCPhotonHABwd)                    ssample = "FGD2 numuCC Photon HABwd";

  else if (sample == kFGD2NuMuCC0PiFwd0ProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi Fwd NoPhoton No Protons";
  else if (sample == kFGD2NuMuCC0PiFwdNProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi Fwd NoPhoton N Protons";

  else if (sample == kFGD2NuMuCC0PiBwd0ProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi Bwd NoPhoton No Protons";
  else if (sample == kFGD2NuMuCC0PiBwdNProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi Bwd NoPhoton N Protons";

  else if (sample == kFGD2NuMuCC0PiHAFwd0ProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi HAFwd NoPhoton No Protons";
  else if (sample == kFGD2NuMuCC0PiHAFwdNProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi HAFwd NoPhoton N Protons";

  else if (sample == kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi HABwd NoPhoton No Protons";
  else if (sample == kFGD2NuMuCC0PiHABwdNProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi HABwd NoPhoton N Protons";

  else if (sample == kFGD2NuMuCC0PiHA0ProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi HA NoPhoton No Protons";
  else if (sample == kFGD2NuMuCC0PiHANProtonsNoPhoton)                    ssample = "FGD2 numuCC 0pi HA NoPhoton N Protons";


  else                                                  ssample = "Unassigned";

  return ssample;
}


//*********************************************************
std::set<std::string> SampleId::ConvertSampleToSelection(SampleEnum sample){
  //*********************************************************

  //These should be the same as what is used to initialize selection names in
  //AnalysisManager. Some of them are made up right now. -ACK

  std::set<std::string> ssample;

  // FGD1
  if      (sample == kUnassigned)                       ssample.insert("Unassigned");
  else if (sample == kFGD1NuMuCC)                       ssample.insert("kTrackerNumuCC");
  else if (sample == kFGD1NuMuCCQE)                     ssample.insert("kTrackerNumuCCQE");
  else if (sample == kFGD1NuMuCC0Pi)                    ssample.insert("kTrackerNumuCCMultiPi");
  else if (sample == kFGD1NuMuCC0PiNoPhoton)            ssample.insert("kTrackerNumuCCMultiPiPhoton");  
  else if (sample == kFGD1NuMuCC0Pi0Protons)            ssample.insert("kTrackerNumuCCMultiPiProton");
  else if (sample == kFGD1NuMuCC0PiNProtons)            ssample.insert("kTrackerNumuCCMultiPiProton");
  
  else if (sample == kFGD1NuMuCC0Pi0ProtonsNoPhoton)    ssample.insert("kTrackerNumuCCMultiPiPhotonProton");
  else if (sample == kFGD1NuMuCC0PiNProtonsNoPhoton)    ssample.insert("kTrackerNumuCCMultiPiPhotonProton");
  
  else if (sample == kFGD1NuMuCC1Pi){
                                                        ssample.insert("kTrackerNumuCCMultiPi");
                                                        ssample.insert("kTrackerNumuCCMultiPiProton");
  }
  else if (sample == kFGD1NuMuCC1PiNoPhoton){            
    
                                                        ssample.insert("kTrackerNumuCCMultiPiPhoton");
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonProton");
                                                        
  }
  else if (sample == kFGD1NuMuCCOther){
                                                        ssample.insert("kTrackerNumuCCMultiPi");
                                                        ssample.insert("kTrackerNumuCCMultiPiProton");
  }
  else if (sample == kFGD1NuMuCCOtherNoPhoton){          
                                                        ssample.insert("kTrackerNumuCCMultiPiPhoton");
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonProton");
  }
  else if (sample == kFGD1NuMuCCPhoton){                
                                                        ssample.insert("kTrackerNumuCCMultiPiPhoton");
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonProton");
  }
  // FGD2
  else if (sample == kFGD2NuMuCC)                       ssample.insert("kTrackerNumuCCFGD2");
  else if (sample == kFGD2NuMuCC0Pi)                    ssample.insert("kTrackerNumuCCMultiPiFGD2");
  else if (sample == kFGD2NuMuCC0PiNoPhoton)            ssample.insert("kTrackerNumuCCMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0Pi0Protons)            ssample.insert("kTrackerNumuCCMultiPiProtonFGD2");
  else if (sample == kFGD2NuMuCC0PiNProtons)            ssample.insert("kTrackerNumuCCMultiPiProtonFGD2");
  
  else if (sample == kFGD2NuMuCC0Pi0ProtonsNoPhoton)    ssample.insert("kTrackerNumuCCMultiPiPhotonProtonFGD2");
  else if (sample == kFGD2NuMuCC0PiNProtonsNoPhoton)    ssample.insert("kTrackerNumuCCMultiPiPhotonProtonFGD2");
  
  else if (sample == kFGD2NuMuCC1Pi){
                                                        ssample.insert("kTrackerNumuCCMultiPiFGD2");
                                                        ssample.insert("kTrackerNumuCCMultiPiProtonFGD2");
  }
  else if (sample == kFGD2NuMuCC1PiNoPhoton){            
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonFGD2");
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonProtonFGD2");
  }
  else if (sample == kFGD2NuMuCCOther){
                                                        ssample.insert("kTrackerNumuCCMultiPiFGD2");
                                                        ssample.insert("kTrackerNumuCCMultiPiProtonFGD2");
  }
  else if (sample == kFGD2NuMuCCOtherNoPhoton){          
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonFGD2");
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonProtonFGD2");
  }
  
  else if (sample == kFGD2NuMuCCPhoton){                 
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonFGD2");
                                                        ssample.insert("kTrackerNumuCCMultiPiPhotonProtonFGD2");
  } 
  else if (sample == kFGD1NuECC)                        ssample.insert("kTrackerNueCC");
  else if (sample == kFGD1NuECC0Pi)                     ssample.insert("kTrackerNueCCMultiPi");
  else if (sample == kFGD1NuECCOther)                   ssample.insert("kTrackerNueCCMultiPi");
  else if (sample == kFGD2NuECC)                        ssample.insert("kTrackerNueCCFGD2");
  else if (sample == kFGD2NuECC0Pi)                     ssample.insert("kTrackerNueCCMultiPiFGD2");
  else if (sample == kFGD2NuECCOther)                   ssample.insert("kTrackerNueCCMultiPiFGD2");

  else if (sample == kFGD1AntiNuMuCC)                   ssample.insert("kTrackerAntiNumuCC");

  // To be renamed
  else if (sample == kFGD1AntiNuMuCC1Track)             ssample.insert("kTrackerAntiNumuCCMultiTrack");
  else if (sample == kFGD1AntiNuMuCCNTracks)            ssample.insert("kTrackerAntiNumuCCMultiTrack");

  else if (sample == kFGD1AntiNuMuCC0Pi)                ssample.insert("kTrackerAntiNumuCCMultiPi");
  else if (sample == kFGD1AntiNuMuCC1Pi)                ssample.insert("kTrackerAntiNumuCCMultiPi");
  else if (sample == kFGD1AntiNuMuCCOther)              ssample.insert("kTrackerAntiNumuCCMultiPi");


  // To be renamed
  else if (sample == kFGD2AntiNuMuCC)                   ssample.insert("kTrackerAntiNumuCCFGD2");
  else if (sample == kFGD2AntiNuMuCC1Track)             ssample.insert("kTrackerAntiNumuCCMultiTrackFGD2");
  else if (sample == kFGD2AntiNuMuCCNTracks)            ssample.insert("kTrackerAntiNumuCCMultiTrackFGD2");

  else if (sample == kFGD2AntiNuMuCC0Pi)                ssample.insert("kTrackerAntiNumuCCMultiPiFGD2");
  else if (sample == kFGD2AntiNuMuCC1Pi)                ssample.insert("kTrackerAntiNumuCCMultiPiFGD2");
  else if (sample == kFGD2AntiNuMuCCOther)              ssample.insert("kTrackerAntiNumuCCMultiPiFGD2");

  else if (sample == kFGD1NuMuBkgInAntiNuModeCC)        ssample.insert("kTrackerNumuInAntiNuModeCC");
  else if (sample == kFGD1NuMuBkgInAntiNuModeCC1Track)  ssample.insert("kTrackerNumuInAntiNuModeCCMultiTrack");
  else if (sample == kFGD1NuMuBkgInAntiNuModeCCNTracks) ssample.insert("kTrackerNumuInAntiNuModeCCMultiTrack");

  else if (sample == kFGD1NuMuBkgInAntiNuModeCC0Pi)     ssample.insert("kTrackerNumuInAntiNuModeCCMultiPi");
  else if (sample == kFGD1NuMuBkgInAntiNuModeCC1Pi)     ssample.insert("kTrackerNumuInAntiNuModeCCMultiPi");
  else if (sample == kFGD1NuMuBkgInAntiNuModeCCOther)   ssample.insert("kTrackerNumuInAntiNuModeCCMultiPi");

  else if (sample == kFGD2NuMuBkgInAntiNuModeCC)        ssample.insert("kTrackerNumuInAntiNuModeCCFGD2");
  else if (sample == kFGD2NuMuBkgInAntiNuModeCC1Track)  ssample.insert("kTrackerNumuInAntiNuModeCCMultiTrackFGD2");
  else if (sample == kFGD2NuMuBkgInAntiNuModeCCNTracks) ssample.insert("kTrackerNumuInAntiNuModeCCMultiTrackFGD2");

  else if (sample == kFGD2NuMuBkgInAntiNuModeCC0Pi)     ssample.insert("kTrackerNumuInAntiNuModeCCMultiPiFGD2");
  else if (sample == kFGD2NuMuBkgInAntiNuModeCC1Pi)     ssample.insert("kTrackerNumuInAntiNuModeCCMultiPiFGD2");
  else if (sample == kFGD2NuMuBkgInAntiNuModeCCOther)   ssample.insert("kTrackerNumuInAntiNuModeCCMultiPiFGD2");


  else if (sample == kFGD1AntiNuECC)                    ssample.insert("kTrackerAntiNueCC");
  else if (sample == kFGD1AntiNuECC0Pi)                 ssample.insert("kTrackerAntiNueCCMultiPi");
  else if (sample == kFGD1AntiNuECCOther)               ssample.insert("kTrackerAntiNueCCMultiPi");

  else if (sample == kFGD2AntiNuECC)                    ssample.insert("kTrackerAntiNueCCFGD2");
  else if (sample == kFGD2AntiNuECC0Pi)                 ssample.insert("kTrackerAntiNueCCMultiPiFGD2");
  else if (sample == kFGD2AntiNuECCOther)               ssample.insert("kTrackerAntiNueCCMultiPiFGD2");

  else if (sample == kFGD1Gamma)                        ssample.insert("kTrackerGamma");
  else if (sample == kFGD2Gamma)                        ssample.insert("kTrackerGammaFGD2");

  else if (sample == kFGD1NuMuCC0PiFwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCC0PiBwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCC0PiHAFwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCC0PiHABwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCC1PiFwd)                   ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCC1PiBwd)                   ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCC1PiHAFwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCC1PiHABwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCCOtherFwd)                   ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCCOtherBwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCCOtherHAFwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");
  else if (sample == kFGD1NuMuCCOtherHABwd)                    ssample.insert("kTrackerNumuCC4piMultiPi");


  else if (sample == kFGD1NuMuCC0PiFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiBwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiHAFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiHABwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC1PiFwdNoPhoton)                   ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC1PiBwdNoPhoton)                   ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC1PiHAFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC1PiHABwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCOtherFwdNoPhoton)                   ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCOtherBwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCOtherHAFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCOtherHABwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCPhotonFwd)                   ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCPhotonBwd)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCPhotonHAFwd)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCCPhotonHABwd)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");

  else if (sample == kFGD1NuMuCC0PiFwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiFwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");

  else if (sample == kFGD1NuMuCC0PiBwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiBwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");

  else if (sample == kFGD1NuMuCC0PiHAFwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiHAFwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");

  else if (sample == kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiHABwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");


  else if (sample == kFGD1NuMuCC0PiHA0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");
  else if (sample == kFGD1NuMuCC0PiHANProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhoton");


  else if (sample == kFGD2NuMuCC0PiFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiBwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiHAFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiHABwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC1PiFwdNoPhoton)                   ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC1PiBwdNoPhoton)                   ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC1PiHAFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC1PiHABwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCOtherFwdNoPhoton)                   ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCOtherBwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCOtherHAFwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCOtherHABwdNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCPhotonFwd)                   ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCPhotonBwd)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCPhotonHAFwd)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCCPhotonHABwd)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");

  else if (sample == kFGD2NuMuCC0PiFwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiFwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");

  else if (sample == kFGD2NuMuCC0PiBwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiBwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");

  else if (sample == kFGD2NuMuCC0PiHAFwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiHAFwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");

  else if (sample == kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiHABwdNProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");


  else if (sample == kFGD2NuMuCC0PiHA0ProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");
  else if (sample == kFGD2NuMuCC0PiHANProtonsNoPhoton)                    ssample.insert("kTrackerNumuCC4piMultiPiPhotonFGD2");

  else                                                  ssample.insert("Unassigned");

  return ssample;
}

std::map<std::string, SampleId::SampleEnum> SampleId::SampleNameToEnumMap = {
 {"kUnassigned", kUnassigned,},
 {"kFGD1NuMuCC", kFGD1NuMuCC,},
 {"kFGD1NuMuCCQE", kFGD1NuMuCCQE,},
 {"kFGD1NuMuCC0Pi", kFGD1NuMuCC0Pi,},
 {"kFGD1NuMuCC0PiNoPhoton", kFGD1NuMuCC0PiNoPhoton,},
 {"kFGD1NuMuCC0Pi0Protons", kFGD1NuMuCC0Pi0Protons,},
 {"kFGD1NuMuCC0PiNProtons", kFGD1NuMuCC0PiNProtons,},
 {"kFGD1NuMuCC0Pi0ProtonsNoPhoton", kFGD1NuMuCC0Pi0ProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiNProtonsNoPhoton", kFGD1NuMuCC0PiNProtonsNoPhoton,},
 {"kFGD1NuMuCC1Pi", kFGD1NuMuCC1Pi,},
 {"kFGD1NuMuCC1PiNoPhoton", kFGD1NuMuCC1PiNoPhoton,},
 {"kFGD1NuMuCCOther", kFGD1NuMuCCOther,},
 {"kFGD1NuMuCCOtherNoPhoton", kFGD1NuMuCCOtherNoPhoton,},
 {"kFGD1NuMuCCPhoton", kFGD1NuMuCCPhoton,},
 {"kFGD1NuMuCC0PiFwd", kFGD1NuMuCC0PiFwd,},
 {"kFGD1NuMuCC1PiFwd", kFGD1NuMuCC1PiFwd,},
 {"kFGD1NuMuCCOtherFwd", kFGD1NuMuCCOtherFwd,},
 {"kFGD1NuMuCC0PiBwd", kFGD1NuMuCC0PiBwd,},
 {"kFGD1NuMuCC1PiBwd", kFGD1NuMuCC1PiBwd,},
 {"kFGD1NuMuCCOtherBwd", kFGD1NuMuCCOtherBwd,},
 {"kFGD1NuMuCC0PiHAFwd", kFGD1NuMuCC0PiHAFwd,},
 {"kFGD1NuMuCC1PiHAFwd", kFGD1NuMuCC1PiHAFwd,},
 {"kFGD1NuMuCCOtherHAFwd", kFGD1NuMuCCOtherHAFwd,},
 {"kFGD1NuMuCC0PiHABwd", kFGD1NuMuCC0PiHABwd,},
 {"kFGD1NuMuCC1PiHABwd", kFGD1NuMuCC1PiHABwd,},
 {"kFGD1NuMuCCOtherHABwd", kFGD1NuMuCCOtherHABwd,},
 {"kFGD2NuMuCC", kFGD2NuMuCC,},
 {"kFGD2NuMuCC0Pi", kFGD2NuMuCC0Pi,},
 {"kFGD2NuMuCC0PiNoPhoton", kFGD2NuMuCC0PiNoPhoton,},
 {"kFGD2NuMuCC0Pi0Protons", kFGD2NuMuCC0Pi0Protons,},
 {"kFGD2NuMuCC0PiNProtons", kFGD2NuMuCC0PiNProtons,},
 {"kFGD2NuMuCC0Pi0ProtonsNoPhoton", kFGD2NuMuCC0Pi0ProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiNProtonsNoPhoton", kFGD2NuMuCC0PiNProtonsNoPhoton,},
 {"kFGD2NuMuCC1Pi", kFGD2NuMuCC1Pi,},
 {"kFGD2NuMuCC1PiNoPhoton", kFGD2NuMuCC1PiNoPhoton,},
 {"kFGD2NuMuCCOther", kFGD2NuMuCCOther,},
 {"kFGD2NuMuCCOtherNoPhoton", kFGD2NuMuCCOtherNoPhoton,},
 {"kFGD2NuMuCCPhoton", kFGD2NuMuCCPhoton,},
 {"kFGD2NuMuCC0PiFwd", kFGD2NuMuCC0PiFwd,},
 {"kFGD2NuMuCC1PiFwd", kFGD2NuMuCC1PiFwd,},
 {"kFGD2NuMuCCOtherFwd", kFGD2NuMuCCOtherFwd,},
 {"kFGD2NuMuCC0PiBwd", kFGD2NuMuCC0PiBwd,},
 {"kFGD2NuMuCC1PiBwd", kFGD2NuMuCC1PiBwd,},
 {"kFGD2NuMuCCOtherBwd", kFGD2NuMuCCOtherBwd,},
 {"kFGD2NuMuCC0PiHAFwd", kFGD2NuMuCC0PiHAFwd,},
 {"kFGD2NuMuCC1PiHAFwd", kFGD2NuMuCC1PiHAFwd,},
 {"kFGD2NuMuCCOtherHAFwd", kFGD2NuMuCCOtherHAFwd,},
 {"kFGD2NuMuCC0PiHABwd", kFGD2NuMuCC0PiHABwd,},
 {"kFGD2NuMuCC1PiHABwd", kFGD2NuMuCC1PiHABwd,},
 {"kFGD2NuMuCCOtherHABwd", kFGD2NuMuCCOtherHABwd,},
 {"kFGD1NuECC", kFGD1NuECC,},
 {"kFGD1NuECC0Pi", kFGD1NuECC0Pi,},
 {"kFGD1NuECCOther", kFGD1NuECCOther,},
 {"kFGD2NuECC", kFGD2NuECC,},
 {"kFGD2NuECC0Pi", kFGD2NuECC0Pi,},
 {"kFGD2NuECCOther", kFGD2NuECCOther,},
 {"kFGD1AntiNuMuCC", kFGD1AntiNuMuCC,},
 {"kFGD1AntiNuMuCC1Track", kFGD1AntiNuMuCC1Track,},
 {"kFGD1AntiNuMuCCNTracks", kFGD1AntiNuMuCCNTracks,},
 {"kFGD1AntiNuMuCC0Pi", kFGD1AntiNuMuCC0Pi,},
 {"kFGD1AntiNuMuCC1Pi", kFGD1AntiNuMuCC1Pi,},
 {"kFGD1AntiNuMuCCOther", kFGD1AntiNuMuCCOther,},
 {"kFGD2AntiNuMuCC", kFGD2AntiNuMuCC,},
 {"kFGD2AntiNuMuCC1Track", kFGD2AntiNuMuCC1Track,},
 {"kFGD2AntiNuMuCCNTracks", kFGD2AntiNuMuCCNTracks,},
 {"kFGD2AntiNuMuCC0Pi", kFGD2AntiNuMuCC0Pi,},
 {"kFGD2AntiNuMuCC1Pi", kFGD2AntiNuMuCC1Pi,},
 {"kFGD2AntiNuMuCCOther", kFGD2AntiNuMuCCOther,},
 {"kFGD1NuMuBkgInAntiNuModeCC", kFGD1NuMuBkgInAntiNuModeCC,},
 {"kFGD1NuMuBkgInAntiNuModeCC1Track", kFGD1NuMuBkgInAntiNuModeCC1Track,},
 {"kFGD1NuMuBkgInAntiNuModeCCNTracks", kFGD1NuMuBkgInAntiNuModeCCNTracks,},
 {"kFGD1NuMuBkgInAntiNuModeCC0Pi", kFGD1NuMuBkgInAntiNuModeCC0Pi,},
 {"kFGD1NuMuBkgInAntiNuModeCC1Pi", kFGD1NuMuBkgInAntiNuModeCC1Pi,},
 {"kFGD1NuMuBkgInAntiNuModeCCOther", kFGD1NuMuBkgInAntiNuModeCCOther,},
 {"kFGD2NuMuBkgInAntiNuModeCC", kFGD2NuMuBkgInAntiNuModeCC,},
 {"kFGD2NuMuBkgInAntiNuModeCC1Track", kFGD2NuMuBkgInAntiNuModeCC1Track,},
 {"kFGD2NuMuBkgInAntiNuModeCCNTracks", kFGD2NuMuBkgInAntiNuModeCCNTracks,},
 {"kFGD2NuMuBkgInAntiNuModeCC0Pi", kFGD2NuMuBkgInAntiNuModeCC0Pi,},
 {"kFGD2NuMuBkgInAntiNuModeCC1Pi", kFGD2NuMuBkgInAntiNuModeCC1Pi,},
 {"kFGD2NuMuBkgInAntiNuModeCCOther", kFGD2NuMuBkgInAntiNuModeCCOther,},
 {"kFGD1NuMuCCBwd", kFGD1NuMuCCBwd,},
 {"kFGD2NuMuCCBwd", kFGD2NuMuCCBwd,},
 {"kFGD1AntiNuECC", kFGD1AntiNuECC,},
 {"kFGD1AntiNuECC0Pi", kFGD1AntiNuECC0Pi,},
 {"kFGD1AntiNuECCOther", kFGD1AntiNuECCOther,},
 {"kFGD2AntiNuECC", kFGD2AntiNuECC,},
 {"kFGD2AntiNuECC0Pi", kFGD2AntiNuECC0Pi,},
 {"kFGD2AntiNuECCOther", kFGD2AntiNuECCOther,},
 {"kFGD1AntiNuEBkgInNuModeCC", kFGD1AntiNuEBkgInNuModeCC,},
 {"kFGD1AntiNuEBkgInNuModeCC0Pi", kFGD1AntiNuEBkgInNuModeCC0Pi,},
 {"kFGD1AntiNuEBkgInNuModeCCOther", kFGD1AntiNuEBkgInNuModeCCOther,},
 {"kFGD2AntiNuEBkgInNuModeCC", kFGD2AntiNuEBkgInNuModeCC,},
 {"kFGD2AntiNuEBkgInNuModeCC0Pi", kFGD2AntiNuEBkgInNuModeCC0Pi,},
 {"kFGD2AntiNuEBkgInNuModeCCOther", kFGD2AntiNuEBkgInNuModeCCOther,},
 {"kFGD1NuEBkgInAntiNuModeCC", kFGD1NuEBkgInAntiNuModeCC,},
 {"kFGD1NuEBkgInAntiNuModeCC0Pi", kFGD1NuEBkgInAntiNuModeCC0Pi,},
 {"kFGD1NuEBkgInAntiNuModeCCOther", kFGD1NuEBkgInAntiNuModeCCOther,},
 {"kFGD2NuEBkgInAntiNuModeCC", kFGD2NuEBkgInAntiNuModeCC,},
 {"kFGD2NuEBkgInAntiNuModeCC0Pi", kFGD2NuEBkgInAntiNuModeCC0Pi,},
 {"kFGD2NuEBkgInAntiNuModeCCOther", kFGD2NuEBkgInAntiNuModeCCOther,},
 {"kFGD1Gamma", kFGD1Gamma,},
 {"kFGD2Gamma", kFGD2Gamma,},
 {"kFGD1GammaInAntiNuMode", kFGD1GammaInAntiNuMode,},
 {"kFGD2GammaInAntiNuMode", kFGD2GammaInAntiNuMode,},
 {"kP0DNuMuCC", kP0DNuMuCC,},
 {"kFGD1NuMuCC0PiFwdNoPhoton", kFGD1NuMuCC0PiFwdNoPhoton,},
 {"kFGD1NuMuCC1PiFwdNoPhoton", kFGD1NuMuCC1PiFwdNoPhoton,},
 {"kFGD1NuMuCCOtherFwdNoPhoton", kFGD1NuMuCCOtherFwdNoPhoton,},
 {"kFGD1NuMuCC0PiBwdNoPhoton", kFGD1NuMuCC0PiBwdNoPhoton,},
 {"kFGD1NuMuCC1PiBwdNoPhoton", kFGD1NuMuCC1PiBwdNoPhoton,},
 {"kFGD1NuMuCCOtherBwdNoPhoton", kFGD1NuMuCCOtherBwdNoPhoton,},
 {"kFGD1NuMuCC0PiHAFwdNoPhoton", kFGD1NuMuCC0PiHAFwdNoPhoton,},
 {"kFGD1NuMuCC1PiHAFwdNoPhoton", kFGD1NuMuCC1PiHAFwdNoPhoton,},
 {"kFGD1NuMuCCOtherHAFwdNoPhoton", kFGD1NuMuCCOtherHAFwdNoPhoton,},
 {"kFGD1NuMuCC0PiHABwdNoPhoton", kFGD1NuMuCC0PiHABwdNoPhoton,},
 {"kFGD1NuMuCC1PiHABwdNoPhoton", kFGD1NuMuCC1PiHABwdNoPhoton,},
 {"kFGD1NuMuCCOtherHABwdNoPhoton", kFGD1NuMuCCOtherHABwdNoPhoton,},
 {"kFGD1NuMuCCPhotonFwd", kFGD1NuMuCCPhotonFwd,},
 {"kFGD1NuMuCCPhotonBwd", kFGD1NuMuCCPhotonBwd,},
 {"kFGD1NuMuCCPhotonHAFwd", kFGD1NuMuCCPhotonHAFwd,},
 {"kFGD1NuMuCCPhotonHABwd", kFGD1NuMuCCPhotonHABwd,},

 {"kFGD1NuMuCC0PiFwd0ProtonsNoPhoton", kFGD1NuMuCC0PiFwd0ProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiFwdNProtonsNoPhoton", kFGD1NuMuCC0PiFwdNProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiBwd0ProtonsNoPhoton", kFGD1NuMuCC0PiBwd0ProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiBwdNProtonsNoPhoton", kFGD1NuMuCC0PiBwdNProtonsNoPhoton,},

 {"kFGD1NuMuCC0PiHAFwd0ProtonsNoPhoton", kFGD1NuMuCC0PiHAFwd0ProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiHAFwdNProtonsNoPhoton", kFGD1NuMuCC0PiHAFwdNProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton", kFGD1NuMuCC0PiHABwd0ProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiHABwdNProtonsNoPhoton", kFGD1NuMuCC0PiHABwdNProtonsNoPhoton,},


 {"kFGD1NuMuCC0PiHA0ProtonsNoPhoton", kFGD1NuMuCC0PiHA0ProtonsNoPhoton,},
 {"kFGD1NuMuCC0PiHANProtonsNoPhoton", kFGD1NuMuCC0PiHANProtonsNoPhoton,},


{"kFGD2NuMuCC0PiFwdNoPhoton", kFGD2NuMuCC0PiFwdNoPhoton,},
 {"kFGD2NuMuCC1PiFwdNoPhoton", kFGD2NuMuCC1PiFwdNoPhoton,},
 {"kFGD2NuMuCCOtherFwdNoPhoton", kFGD2NuMuCCOtherFwdNoPhoton,},
 {"kFGD2NuMuCC0PiBwdNoPhoton", kFGD2NuMuCC0PiBwdNoPhoton,},
 {"kFGD2NuMuCC1PiBwdNoPhoton", kFGD2NuMuCC1PiBwdNoPhoton,},
 {"kFGD2NuMuCCOtherBwdNoPhoton", kFGD2NuMuCCOtherBwdNoPhoton,},
 {"kFGD2NuMuCC0PiHAFwdNoPhoton", kFGD2NuMuCC0PiHAFwdNoPhoton,},
 {"kFGD2NuMuCC1PiHAFwdNoPhoton", kFGD2NuMuCC1PiHAFwdNoPhoton,},
 {"kFGD2NuMuCCOtherHAFwdNoPhoton", kFGD2NuMuCCOtherHAFwdNoPhoton,},
 {"kFGD2NuMuCC0PiHABwdNoPhoton", kFGD2NuMuCC0PiHABwdNoPhoton,},
 {"kFGD2NuMuCC1PiHABwdNoPhoton", kFGD2NuMuCC1PiHABwdNoPhoton,},
 {"kFGD2NuMuCCOtherHABwdNoPhoton", kFGD2NuMuCCOtherHABwdNoPhoton,},
 {"kFGD2NuMuCCPhotonFwd", kFGD2NuMuCCPhotonFwd,},
 {"kFGD2NuMuCCPhotonBwd", kFGD2NuMuCCPhotonBwd,},
 {"kFGD2NuMuCCPhotonHAFwd", kFGD2NuMuCCPhotonHAFwd,},
 {"kFGD2NuMuCCPhotonHABwd", kFGD2NuMuCCPhotonHABwd,},

 {"kFGD2NuMuCC0PiFwd0ProtonsNoPhoton", kFGD2NuMuCC0PiFwd0ProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiFwdNProtonsNoPhoton", kFGD2NuMuCC0PiFwdNProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiBwd0ProtonsNoPhoton", kFGD2NuMuCC0PiBwd0ProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiBwdNProtonsNoPhoton", kFGD2NuMuCC0PiBwdNProtonsNoPhoton,},

 {"kFGD2NuMuCC0PiHAFwd0ProtonsNoPhoton", kFGD2NuMuCC0PiHAFwd0ProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiHAFwdNProtonsNoPhoton", kFGD2NuMuCC0PiHAFwdNProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton", kFGD2NuMuCC0PiHABwd0ProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiHABwdNProtonsNoPhoton", kFGD2NuMuCC0PiHABwdNProtonsNoPhoton,},


 {"kFGD2NuMuCC0PiHA0ProtonsNoPhoton", kFGD2NuMuCC0PiHA0ProtonsNoPhoton,},
 {"kFGD2NuMuCC0PiHANProtonsNoPhoton", kFGD2NuMuCC0PiHANProtonsNoPhoton,},


 {"kNSample", kNSamples},
 };


