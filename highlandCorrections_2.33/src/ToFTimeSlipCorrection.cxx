#include "ToFTimeSlipCorrection.hxx"
#include "VersioningUtils.hxx"
#include "ND280AnalysisUtils.hxx"
#include "TRandom3.h"
#include "Parameters.hxx"
#include <assert.h> 

// #define DEBUG

#define Fill(x) FillFromMap(x, #x)

//********************************************************************
ToFTimeSlipCorrection::ToFTimeSlipCorrection() : CorrectionBase(){
  //********************************************************************
  _RandomGenerator = NULL;

  InitializeRandomGenerator();

  _params_vect.clear();
  _params_vect.resize(kRunIndexCounter);
  _params_map.clear();
  _topo_names.resize(ToFSenseCorrector::kToFInvalid);
  
  _rndm_inputs.clear();
  _rndm_inputs.resize(ToFSenseCorrector::kToFInvalid);
  
  size_t index = kFHC;
  
  std::string filename = ND::params().GetParameterS("highlandCorrections.ToF.TimeSlips.File.FHC.Run2_4");
  
  FillTopoParams(index, filename, versionUtils::ExtensionCorr());
  
  index = kRHC;
  filename = ND::params().GetParameterS("highlandCorrections.ToF.TimeSlips.File.RHC.Run5_9");
  
  FillTopoParams(index, filename, versionUtils::ExtensionCorr());
  
  index = kFHCRun8;
  filename = ND::params().GetParameterS("highlandCorrections.ToF.TimeSlips.File.FHC.Run8");
  FillTopoParams(index, filename, versionUtils::ExtensionCorr());
  
#ifdef DEBUG 
  Print();
#endif


  
}

//********************************************************************
ToFTimeSlipCorrection::~ToFTimeSlipCorrection() {
  //********************************************************************
  if (_RandomGenerator)
    delete _RandomGenerator;
}

//********************************************************************
void ToFTimeSlipCorrection::InitializeRandomGenerator(){
  //********************************************************************
  if (!_RandomGenerator){
    _RandomGenerator = new TRandom3();
    SetRandomSeed(ND::params().GetParameterI("highlandCorrections.ToF.RandomSeed"));

  }
}

//********************************************************************
UInt_t ToFTimeSlipCorrection::GetRandomSeed() const{
  //********************************************************************
  if (_RandomGenerator)
    return _RandomGenerator->GetSeed();
  return 0XDEADBEEF;
}

//******************************************************************** 
void ToFTimeSlipCorrection::SetRandomSeed(UInt_t seed){
  //********************************************************************
  if (_RandomGenerator)
    _RandomGenerator->SetSeed(seed); 
}


//********************************************************************
void ToFTimeSlipCorrection::Apply(AnaSpillC& spillBB){
  //********************************************************************

#ifdef DEBUG 
  std::cout << "FGDPIDCorrection::Apply() start " << std::endl;  
#endif


  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);

  // Data or MC
  bool isMC     = spill.GetIsMC();
  bool isSandMC = spill.GetIsSandMC();

  if (!isMC && !isSandMC) return;
  
  // Set random values per topology
  SetRandomValues();
  
  SetTopoVector(spill);

  for (UInt_t i = 0; i < spill.Bunches.size(); i++) {
    AnaBunch* bunch = static_cast<AnaBunch*>(spill.Bunches[i]);
    for (UInt_t j = 0; j < bunch->Particles.size(); j++) {
      AnaTrack* track = static_cast<AnaTrack*>(bunch->Particles[j]);
      
      if (!track) continue;

#ifdef DEBUG
      std::cout << " === Track before === " << std::endl;
      track->ToF.Print();
#endif
  
      ToFSenseCorrector::ToFTopology topologies[ToFSenseCorrector::kToFInvalid];

      Int_t count = ToFSenseCorrector::GetToFTopologies(*track, topologies);

      for (Int_t j = 0; j < count; j++){

        ToFSenseCorrector::ToFTopology topo = topologies[j];

        ApplyToFTimeSlip(*track, topo);
      }
    
#ifdef DEBUG
      std::cout << " === Track after === " << std::endl;
      track->ToF.Print();
#endif
  
    }

  }
  

#ifdef DEBUG 
  std::cout << "FGDPIDCorrection::Apply() end " << std::endl;  
#endif


}

//********************************************************************
void ToFTimeSlipCorrection::ApplyToFTimeSlip(AnaTrack& track, ToFSenseCorrector::ToFTopology topo) const {
  //******************************************************************** 

  // should have a corresponding true track
  AnaTrueParticleB* trueTrack = track.GetTrueParticle();
  if (!trueTrack) return;

  //Apply for topologies
  switch (topo){
    case ToFSenseCorrector::kToFTopo_FGD1FGD2:
    case ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1: 
      ApplyCorrection(track.ToF.FGD1_FGD2, track.ToF.Flag_FGD1_FGD2, topo);
      break;
    
   case ToFSenseCorrector::kToFTopo_FGD1P0D_Track: 
   case ToFSenseCorrector::kToFTopo_FGD1P0D_Shower:
      ApplyCorrection(track.ToF.P0D_FGD1, track.ToF.Flag_P0D_FGD1, topo);
      break;
      
     
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track: 
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower:
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track: 
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower: 
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track: 
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower: 
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track: 
   case ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower:
      ApplyCorrection(track.ToF.ECal_FGD1, track.ToF.Flag_ECal_FGD1, topo);
      break;

    case ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track:
    case ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower:
    case ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track:
    case ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower:
    case ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track:
    case ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower:
    case ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track:
    case ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower:
      ApplyCorrection(track.ToF.ECal_FGD2, track.ToF.Flag_ECal_FGD2, topo);
      break;
    case ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track:
    case ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower:
      ApplyCorrection(track.ToF.DSECal_FGD2, track.ToF.Flag_DSECal_FGD2, topo);
      break;
    default:
      break;
  } 
}


//********************************************************************
void ToFTimeSlipCorrection::FillFromMap(ToFSenseCorrector::ToFTopology  topo, std::string name){
  //********************************************************************

  assert(_params_map.find(name) != _params_map.end());
  
  assert(_params);

  assert(topo != ToFSenseCorrector::kToFInvalid);

  (*_params)[topo].Corr1  = _params_map[name].Corr1;
  (*_params)[topo].Corr2 = _params_map[name].Corr2;
  

  _topo_names[topo] = name;

}

//********************************************************************
void ToFTimeSlipCorrection::SetRandomValues(){
  //********************************************************************
  
  _rndm_inputs.clear();
  _rndm_inputs.resize(ToFSenseCorrector::kToFInvalid);
  
  for (int i = 0; i < ToFSenseCorrector::kToFInvalid; i++){
    _rndm_inputs[i].Corr1 = _RandomGenerator->Uniform(1.);
    _rndm_inputs[i].Corr2 = _RandomGenerator->Uniform(1.);
  }
  
}



//********************************************************************
void ToFTimeSlipCorrection::ApplyCorrection(Float_t& tof_value,
    Int_t& flag, 
    ToFSenseCorrector::ToFTopology topo) const{
  //********************************************************************
 
  assert(_params);
 
  flag = AnaToF::kValidNoSlip;
  
  // Whether to apply a slip 
  // At least one of the Up (Corr1) or Down (Corr2) prob is > 0
  if ((*_params)[topo].Corr1 + (*_params)[topo].Corr2 == 0){
    return;
  }
   
  // No slip rndm throw check for any slip:  > total slip prob
  if (_rndm_inputs[topo].Corr1 > (*_params)[topo].Corr1 + (*_params)[topo].Corr2){
    return;
  }
  
  // Probabilty to have an up flip: in case a slip happened
  Float_t probUp = (*_params)[topo].Corr1 / ((*_params)[topo].Corr1 + (*_params)[topo].Corr2);
  
  // Up or down slip
  if (probUp < _rndm_inputs[topo].Corr2){
  
    tof_value += 10.; //ns
    flag = AnaToF::kValidUpSlip;
  }
  else{ // Down
    tof_value += -10.; //ns
    flag = AnaToF::kValidDownSlip;
  } 

}

//********************************************************************
void ToFTimeSlipCorrection::Print(Option_t *option) const{
//********************************************************************
  (void)option;
  
  //Dump the params 
  std::cout << " ********** ToFTimeSlipCorrection: parameters ********** " << std::endl; 
  
  Int_t i = 0;
  std::vector<std::vector<CorrParams> >::const_iterator it = _params_vect.begin();
  
  for (; it != _params_vect.end(); it++, i++){
    std::cout << " *****  Index: \t " << i << std::endl;
 
    std::cout << " Topology \t " << " Corr1 \t " << " Corr2 \t " << std::endl;
    
    std::vector<CorrParams>::const_iterator it1 = (*it).begin();
    
    Int_t j = 0;
    for (; it1 != (*it).end(); it1++, j++){
      
      std::cout << _topo_names[j] << " \t " << it1->Corr1 << " \t " << it1->Corr2 << std::endl;
    }
  }
  
  std::cout << " ********** " << std::endl; 
  

}


//********************************************************************
void ToFTimeSlipCorrection::FillTopoParams(const size_t& index, const std::string& filename, 
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
  
  _params->resize(ToFSenseCorrector::kToFInvalid);
  
  _params_map.clear();
  
  std::string topo;
  Float_t par1, par2;

  while (getline(file, data)){
    std::stringstream input(data);

    input >> topo >> par1 >> par2;

    // Fill the map
    _params_map[topo] = CorrParams(par1, par2); 
    std::cout << topo << " " << par1 << " " << par2 << std::endl;
  }

  file.close();
  
  // Fill the vector of corrections
  Fill(ToFSenseCorrector::kToFTopo_FGD1FGD2); 
  Fill(ToFSenseCorrector::kToFTopo_FGD1P0D_Track);
  Fill(ToFSenseCorrector::kToFTopo_FGD1P0D_Shower); 
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Track); 
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_LAStartFgd_Shower); 
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Track);
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_LAEndFgd_Shower);
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Track); 
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_HAStartFgd_Shower); 
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Track); 
  Fill(ToFSenseCorrector::kToFTopo_FGD1ECAL_HAEndFgd_Shower);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Track);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_LAStartFgd_Shower);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Track);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_LAEndFgd_Shower);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Track);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_HAStartFgd_Shower);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Track);
  Fill(ToFSenseCorrector::kToFTopo_FGD2ECAL_HAEndFgd_Shower);
  Fill(ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Track);
  Fill(ToFSenseCorrector::kToFTopo_FGD2DSECAL_LAStartFgd_Shower);
  Fill(ToFSenseCorrector::kToFTopo_FGD1FGD2_NoStopFGD1);
  
}


//********************************************************************
void ToFTimeSlipCorrection::SetTopoVector(AnaSpillC& spillBB){
//********************************************************************

  size_t index = GetRunIndex(spillBB);
  
  SetTopoVector(index);
}


//********************************************************************
size_t ToFTimeSlipCorrection::GetRunIndex(AnaSpillC& spillBB) const{
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
void ToFTimeSlipCorrection::SetTopoVector(const size_t& index){
//********************************************************************

  assert(index < _params_vect.size());
  
  _params = &_params_vect[index];
  
}
  
