#include "ToFCorrection.hxx"
#include "VersioningUtils.hxx"
#include "ND280AnalysisUtils.hxx"
#include "TRandom3.h"
#include "Parameters.hxx"
#include <assert.h> 
 
#include "VersioningUtils.hxx"

//#define DEBUG

#define Fill(x) FillFromMap(x, #x)

//********************************************************************
ToFCorrection::ToFCorrection() : CorrectionBase(){
  //********************************************************************
  _RandomGenerator = NULL;

  InitializeRandomGenerator();

  _params_vect.clear();
  _params_vect.resize(kRunIndexCounter);
  _params_map.clear();
  _topo_names.resize(kCorrTopoCounter);
  
  size_t index = kFHC; 
  std::string filename = ND::params().GetParameterS("highlandCorrections.ToF.Smear.File.FHC.Run2_4");
  FillTopoParams(index, filename, versionUtils::ExtensionCorr());
  
  index = kRHC;
  filename = ND::params().GetParameterS("highlandCorrections.ToF.Smear.File.RHC.Run5_9");
  FillTopoParams(index, filename, versionUtils::ExtensionCorr());
  
  index = kFHCRun8;
  filename = ND::params().GetParameterS("highlandCorrections.ToF.Smear.File.FHC.Run8");
  FillTopoParams(index, filename, versionUtils::ExtensionCorr());
   
}

//********************************************************************
ToFCorrection::~ToFCorrection() {
  //********************************************************************
  if (_RandomGenerator)
    delete _RandomGenerator;
}

//********************************************************************
void ToFCorrection::InitializeRandomGenerator(){
  //********************************************************************
  if (!_RandomGenerator){
    _RandomGenerator = new TRandom3();
    SetRandomSeed(ND::params().GetParameterI("highlandCorrections.ToF.RandomSeed"));

  }
}

//********************************************************************
UInt_t ToFCorrection::GetRandomSeed() const{
  //********************************************************************
  if (_RandomGenerator)
    return _RandomGenerator->GetSeed();
  return 0XDEADBEEF;
}

//******************************************************************** 
void ToFCorrection::SetRandomSeed(UInt_t seed){
  //********************************************************************
  if (_RandomGenerator)
    _RandomGenerator->SetSeed(seed); 
}


//********************************************************************
void ToFCorrection::Apply(AnaSpillC& spillBB){
  //********************************************************************

  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);

  // Data or MC
  bool isMC     = spill.GetIsMC();
  bool isSandMC = spill.GetIsSandMC();

  if (!isMC && !isSandMC) return;
  
  SetTopoVector(spill);

  for (UInt_t i = 0; i < spill.Bunches.size(); i++) {
    AnaBunch* bunch = static_cast<AnaBunch*>(spill.Bunches[i]);
    for (UInt_t j = 0; j < bunch->Particles.size(); j++) {
      AnaTrack* track = static_cast<AnaTrack*>(bunch->Particles[j]);
      
      if (!track) continue;


      ToFSenseCorrector::ToFTopology topologies[ToFSenseCorrector::kToFInvalid];

      Int_t count = ToFSenseCorrector::GetToFTopologies(*track, topologies);

      for (Int_t j = 0; j < count; j++){

        ToFSenseCorrector::ToFTopology topo = topologies[j];

        ApplyToFSmear(*track, topo, isSandMC);
      }
    }

  }

}

//********************************************************************
void ToFCorrection::ApplyToFSmear(AnaTrack& track, ToFSenseCorrector::ToFTopology topo, bool IsSandMC) const {
  //******************************************************************** 

  // should have a corresponding true track
  AnaTrueParticleB* trueTrack = track.GetTrueParticle();
  if (!trueTrack) return;

  // apply the smearing
  if (!IsSandMC){

    //  fwd or bwd track
    bool TrueIsFwd = ToFSenseCorrector::IsForward(*trueTrack);

    // FGD1-FGD2
    if (topo == ToFSenseCorrector::kToFTopo_FGD1FGD2){
      TrueIsFwd ? ApplyCorrection(track.ToF.FGD1_FGD2, kFGD1_FGD2_ToF_MC_TrueFwd) : ApplyCorrection(track.ToF.FGD1_FGD2, kFGD1_FGD2_ToF_MC_TrueBwd);
    }
    // P0D-FGD1 
    if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Track){
      TrueIsFwd ? ApplyCorrection(track.ToF.P0D_FGD1, kP0D_FGD1_ToF_MC_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.P0D_FGD1, kP0D_FGD1_ToF_MC_TrueBwd_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Shower){
      TrueIsFwd ? ApplyCorrection(track.ToF.P0D_FGD1, kP0D_FGD1_ToF_MC_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.P0D_FGD1, kP0D_FGD1_ToF_MC_TrueBwd_Shower);
    }
 
    // ECal-FGD1,  LA
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAStartFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAStartFgd_TrueBwd_Track);
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAStartFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAStartFgd_TrueBwd_Shower);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAEndFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAEndFgd_TrueBwd_Track);
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAEndFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAEndFgd_TrueBwd_Shower);
    }
    
    //ECal-FGD1,  HA
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAStartFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAStartFgd_TrueBwd_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAStartFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAStartFgd_TrueBwd_Shower);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAEndFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAEndFgd_TrueBwd_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAEndFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAEndFgd_TrueBwd_Shower);
    }
    
    // ECal-FGD2,  LA
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Track);
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Shower);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAEndFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAEndFgd_TrueBwd_Track);
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAEndFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAEndFgd_TrueBwd_Shower);
    }
    
    // ECal-FGD2,  HA
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAStartFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAStartFgd_TrueBwd_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAStartFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAStartFgd_TrueBwd_Shower);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAEndFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAEndFgd_TrueBwd_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAEndFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAEndFgd_TrueBwd_Shower);
    }
    
    // DSECal-FGD2, LA
    if (topo == ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.DSECal_FGD2, kDSECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Track) : 
        ApplyCorrection(track.ToF.DSECal_FGD2, kDSECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Track);
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower) { 
      TrueIsFwd ? ApplyCorrection(track.ToF.DSECal_FGD2, kDSECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Shower) : 
        ApplyCorrection(track.ToF.DSECal_FGD2, kDSECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Shower);
    }
    
    // FGD1-FGD2, no stop in FGD1
    if (topo == ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1){
      TrueIsFwd ? ApplyCorrection(track.ToF.FGD1_FGD2, kFGD1_FGD2_ToF_MC_NoStopFGD1_TrueFwd) : 
        ApplyCorrection(track.ToF.FGD1_FGD2, kFGD1_FGD2_ToF_MC_NoStopFGD1_TrueBwd);
    }


  }
  
  // Sand
  else {
       
    // FGD1-FGD2
    if (topo == ToFSenseCorrector::kToFTopo_FGD1FGD2){
      ApplyCorrection(track.ToF.FGD1_FGD2, kFGD1_FGD2_ToF_MC_Sand);
    }
    
    // P0D-FGD1 
    if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Track){
      ApplyCorrection(track.ToF.P0D_FGD1, kP0D_FGD1_ToF_MC_Sand_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1P0D_Shower){
      ApplyCorrection(track.ToF.P0D_FGD1, kP0D_FGD1_ToF_MC_Sand_Shower);
    }
 
    // ECal-FGD1 -> only apply smearing for cases in which we have enough statistic to compute the correction factors
    // ECal-FGD1,  LA
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track) { 
      ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAStartFgd_Sand_Track); 
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower) { 
      ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_LAStartFgd_Sand_Shower);
    }
    
    //ECal-FGD1,  HA
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track) { 
      ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAStartFgd_Sand_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower) { 
      ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAStartFgd_Sand_Shower);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track) { 
      ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAEndFgd_Sand_Track);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower) { 
      ApplyCorrection(track.ToF.ECal_FGD1, kECal_FGD1_ToF_MC_HAEndFgd_Sand_Shower); 
    }
    
    //ECal-FGD2,  LA
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track) { 
      ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAStartFgd_Sand_Track); 
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower) { 
      ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAStartFgd_Sand_Shower);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track) { 
      ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAEndFgd_Sand_Track); 
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower) { 
      ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_LAEndFgd_Sand_Shower);
    }

    //ECal-FGD2,  HA
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track) { 
      ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAStartFgd_Sand_Track); 
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower) { 
      ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAStartFgd_Sand_Shower);
    }
    
    if (topo == ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track) { 
      ApplyCorrection(track.ToF.ECal_FGD2, kECal_FGD2_ToF_MC_HAEndFgd_Sand_Track); 
    }

    // DSECal-FGD2,  LA
    if (topo == ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track) { 
      ApplyCorrection(track.ToF.DSECal_FGD2, kDSECal_FGD2_ToF_MC_LAStartFgd_Sand_Track); 
    }
    
    if(topo == ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower) { 
      ApplyCorrection(track.ToF.DSECal_FGD2, kDSECal_FGD2_ToF_MC_LAStartFgd_Sand_Shower);
    }

    // FGD1-FGD2
    if (topo == ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1){
      ApplyCorrection(track.ToF.FGD1_FGD2,  kFGD1_FGD2_ToF_MC_NoStopFGD1_Sand);
    }

  }

}


//********************************************************************
void ToFCorrection::FillFromMap(CorrTopology topo, std::string name){
  //********************************************************************

  assert(_params_map.find(name) != _params_map.end());
  
  assert(_params);

  assert(topo != kCorrTopoCounter);

  (*_params)[topo].Mean  = _params_map[name].Mean;
  (*_params)[topo].Sigma = _params_map[name].Sigma;
  

  _topo_names[topo] = name;

}

//********************************************************************
void ToFCorrection::ApplyCorrection(Float_t& tof_value, CorrTopology topo) const{
  //********************************************************************
 
  assert(_params);
  
  tof_value += _RandomGenerator->Gaus((*_params)[topo].Mean, (*_params)[topo].Sigma); 

}

//********************************************************************
void ToFCorrection::Print(Option_t *option) const{
//********************************************************************
  (void)option;
  
  //Dump the params 
  std::cout << " ********** ToFCorrection: parameters ********** " << std::endl; 
  
  Int_t i = 0;
  std::vector<std::vector<CorrParams> >::const_iterator it = _params_vect.begin();
  
  for (; it != _params_vect.end(); it++, i++){
    std::cout << " *****  Index: \t " << i << std::endl;
 
    std::cout << " Topology \t " << " Mean \t " << " Sigma \t " << std::endl;
    
    std::vector<CorrParams>::const_iterator it1 = (*it).begin();
    
    Int_t j = 0;
    for (; it1 != (*it).end(); it1++, j++){
      
      std::cout << _topo_names[j] << " \t " << it1->Mean << " \t " << it1->Sigma << std::endl;
    }
  }
  
  std::cout << " ********** " << std::endl; 
  

}


//********************************************************************
void ToFCorrection::FillTopoParams(const size_t& index, const std::string& filename, 
    const std::string& extension){
//********************************************************************

  // Read from file and fill the map
  std::string data;
  std::ifstream file;
  std::string file_ext = extension;
  if (file_ext.length() > 0){
    file_ext = "_" + extension;
  }
  std::string fullpath = std::string(getenv("HIGHLANDCORRECTIONSROOT")) 
    + "/data/" + extension + "/" + filename + file_ext +  ".dat"; // assume .dat files
  
  file.open(fullpath.c_str()); 

  assert(file.is_open());
  
  assert(index < _params_vect.size());
  
  SetTopoVector(index);
  
  _params->resize(kCorrTopoCounter);
  
  _params_map.clear();
  
  std::string topo;
  Float_t mean, sigma;

  while (getline(file, data)){
    std::stringstream input(data);

    input >> topo >> mean >> sigma;

    // Fill the map
    _params_map[topo] = CorrParams(mean, sigma); 
  }

  file.close();
  
  // Fill the vector of corrections
  Fill(kP0D_FGD1_ToF_MC_TrueFwd_Track);
  Fill(kP0D_FGD1_ToF_MC_TrueBwd_Track);
  Fill(kP0D_FGD1_ToF_MC_Sand_Track);
  
  Fill(kP0D_FGD1_ToF_MC_TrueFwd_Shower);
  Fill(kP0D_FGD1_ToF_MC_TrueBwd_Shower);
  Fill(kP0D_FGD1_ToF_MC_Sand_Shower);

  Fill(kFGD1_FGD2_ToF_MC_TrueFwd);
  Fill(kFGD1_FGD2_ToF_MC_TrueBwd);
  Fill(kFGD1_FGD2_ToF_MC_Sand);

  Fill(kECal_FGD1_ToF_MC_LAStartFgd_TrueFwd_Shower);
  Fill(kECal_FGD1_ToF_MC_LAStartFgd_TrueBwd_Shower);
  Fill(kECal_FGD1_ToF_MC_LAStartFgd_TrueFwd_Track);
  Fill(kECal_FGD1_ToF_MC_LAStartFgd_TrueBwd_Track);
  Fill(kECal_FGD1_ToF_MC_LAStartFgd_Sand_Shower);
  Fill(kECal_FGD1_ToF_MC_LAStartFgd_Sand_Track);

  Fill(kECal_FGD1_ToF_MC_LAEndFgd_TrueFwd_Shower);
  Fill(kECal_FGD1_ToF_MC_LAEndFgd_TrueBwd_Shower);
  Fill(kECal_FGD1_ToF_MC_LAEndFgd_TrueFwd_Track);
  Fill(kECal_FGD1_ToF_MC_LAEndFgd_TrueBwd_Track);

  Fill(kECal_FGD1_ToF_MC_HAStartFgd_TrueFwd_Shower);
  Fill(kECal_FGD1_ToF_MC_HAStartFgd_TrueBwd_Shower);
  Fill(kECal_FGD1_ToF_MC_HAStartFgd_TrueFwd_Track);
  Fill(kECal_FGD1_ToF_MC_HAStartFgd_TrueBwd_Track);
  Fill(kECal_FGD1_ToF_MC_HAStartFgd_Sand_Shower);
  Fill(kECal_FGD1_ToF_MC_HAStartFgd_Sand_Track);

  Fill(kECal_FGD1_ToF_MC_HAEndFgd_TrueFwd_Shower);
  Fill(kECal_FGD1_ToF_MC_HAEndFgd_TrueBwd_Shower);
  Fill(kECal_FGD1_ToF_MC_HAEndFgd_TrueFwd_Track);
  Fill(kECal_FGD1_ToF_MC_HAEndFgd_TrueBwd_Track);
  Fill(kECal_FGD1_ToF_MC_HAEndFgd_Sand_Shower);
  Fill(kECal_FGD1_ToF_MC_HAEndFgd_Sand_Track);

  
  Fill(kECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Track);
  Fill(kECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Track);
  Fill(kECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Shower);
  Fill(kECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Shower);
  Fill(kECal_FGD2_ToF_MC_LAStartFgd_Sand_Track);        
  Fill(kECal_FGD2_ToF_MC_LAStartFgd_Sand_Shower);


  Fill(kECal_FGD2_ToF_MC_LAEndFgd_TrueFwd_Track);
  Fill(kECal_FGD2_ToF_MC_LAEndFgd_TrueBwd_Track);
  Fill(kECal_FGD2_ToF_MC_LAEndFgd_TrueFwd_Shower);
  Fill(kECal_FGD2_ToF_MC_LAEndFgd_TrueBwd_Shower);
  Fill(kECal_FGD2_ToF_MC_LAEndFgd_Sand_Track);         
  Fill(kECal_FGD2_ToF_MC_LAEndFgd_Sand_Shower);
  
  Fill(kECal_FGD2_ToF_MC_HAStartFgd_TrueFwd_Track);
  Fill(kECal_FGD2_ToF_MC_HAStartFgd_TrueBwd_Track);
  Fill(kECal_FGD2_ToF_MC_HAStartFgd_TrueFwd_Shower);
  Fill(kECal_FGD2_ToF_MC_HAStartFgd_TrueBwd_Shower);
  Fill(kECal_FGD2_ToF_MC_HAStartFgd_Sand_Track);     
  Fill(kECal_FGD2_ToF_MC_HAStartFgd_Sand_Shower); 
  
  Fill(kECal_FGD2_ToF_MC_HAEndFgd_TrueFwd_Track);
  Fill(kECal_FGD2_ToF_MC_HAEndFgd_TrueBwd_Track);
  Fill(kECal_FGD2_ToF_MC_HAEndFgd_TrueFwd_Shower);
  Fill(kECal_FGD2_ToF_MC_HAEndFgd_TrueBwd_Shower);
  Fill(kECal_FGD2_ToF_MC_HAEndFgd_Sand_Track);

  Fill(kDSECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Track);
  Fill(kDSECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Track);
  Fill(kDSECal_FGD2_ToF_MC_LAStartFgd_TrueFwd_Shower);
  Fill(kDSECal_FGD2_ToF_MC_LAStartFgd_TrueBwd_Shower);
  Fill(kDSECal_FGD2_ToF_MC_LAStartFgd_Sand_Track);    
  Fill(kDSECal_FGD2_ToF_MC_LAStartFgd_Sand_Shower);
  
  Fill(kFGD1_FGD2_ToF_MC_NoStopFGD1_TrueFwd);
  Fill(kFGD1_FGD2_ToF_MC_NoStopFGD1_TrueBwd); 
  Fill(kFGD1_FGD2_ToF_MC_NoStopFGD1_Sand);
  
}


//********************************************************************
void ToFCorrection::SetTopoVector(AnaSpillC& spillBB){
//********************************************************************

  size_t index = GetRunIndex(spillBB);
  
  SetTopoVector(index);
}


//********************************************************************
size_t ToFCorrection::GetRunIndex(AnaSpillC& spillBB) const{
//********************************************************************

  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);
  
  assert(spill.EventInfo);
  
  //FHC
  size_t index = kFHC;
  
  
  //RHC 
  if (anaUtils::IsRHC(spill.EventInfo->Run)){
    index = kRHC;
  
  }
  
  int run_period = anaUtils::GetRunPeriod(spill.EventInfo->Run);
  
  //Run8
  if (run_period == 17 || run_period == 18){
    index = kFHCRun8;
  }
  
  return index;
  
}


//********************************************************************
void ToFCorrection::SetTopoVector(const size_t& index){
//********************************************************************

  assert(index < _params_vect.size());
  
  _params = &_params_vect[index];
  
}
  
