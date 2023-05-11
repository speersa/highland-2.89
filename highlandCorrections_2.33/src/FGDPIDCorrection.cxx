#include <stdio.h>
#include "TMath.h"
#include "FGDPIDCorrection.hxx"
#include "HighlandAnalysisUtils.hxx"
#include "VersioningUtils.hxx"
#include "DetectorDefinition.hxx" 
#include "IntersectionUtils.hxx"

//#define DEBUG


//********************************************************************
FGDPIDCorrection::FGDPIDCorrection(){
  //********************************************************************

  // Define name of particle candidates
  _particle_names[ParticleId::kProton]   = "Proton";
  _particle_names[ParticleId::kPiPos]    = "Pion";
  _particle_names[ParticleId::kMuon]     = "Muon";
  _particle_names[ParticleId::kElectron] = "Electron";


  _pulls_mode = 0;

  if ((bool)ND::params().GetParameterI("highlandCorrections.FGDPIDCorrection.UseP7Pulls")){
    _pulls_mode = 1;
  }

  _apply_corr_missing_water = (bool)ND::params().GetParameterI("highlandCorrections.FGDPIDCorrection.ApplyCorrMissingWaterLayer");

  _xfactor = ND::params().GetParameterD("highlandCorrections.FGDPIDCorrection.CorrMissingWaterLayer.XFactor");
  
  bool loaded_pid_file = true;

  for (std::map<ParticleId::ParticleEnum, TString>::iterator part = _particle_names.begin(); part != _particle_names.end(); part++){
    
    // Fill array of particle types, bins, means and sigmas use in PID calculation by Anezka
    // Do this now so that we only load these once, rather than on every event.
    loaded_pid_file = (loaded_pid_file && ReadFile((part->second).Data(), 1, _pid_map[part->first].FGD1_Binned_PDF));
    loaded_pid_file = (loaded_pid_file && ReadFile((part->second).Data(), 2, _pid_map[part->first].FGD2_Binned_PDF));
    loaded_pid_file = (loaded_pid_file && ReadFitPars((part->second).Data(), 1, _pid_map[part->first].FGD1_PDF_Pars));
    loaded_pid_file = (loaded_pid_file && ReadFitPars((part->second).Data(), 2, _pid_map[part->first].FGD2_PDF_Pars));
    
    if (!loaded_pid_file && _pulls_mode == 1){
      std::cout << "FGDPIDCorrection: FGD PID file not found - FGD PIDs will not be correct!" << std::endl;
    }
    
    if (part->first == ParticleId::kElectron)
      continue;
    
    _pull_EvsX_FGD1[part->first] = ReadPull(part->second,"EvsX",1);
    _pull_EvsX_FGD2[part->first] = ReadPull(part->second,"EvsX",2);    
  }


}


//********************************************************************
void FGDPIDCorrection::Apply(AnaSpillC& spillBB){
  //********************************************************************

  AnaSpill& spill = *static_cast<AnaSpill*>(&spillBB);

#ifdef DEBUG 
  std::cout << " FGDPIDCorrection::Apply() " << std::endl;  
#endif



  // Loop over all bunches
  for (unsigned int i = 0; i < spill.Bunches.size(); i++) {

    AnaBunch* bunch = static_cast<AnaBunch*>(spill.Bunches[i]);
    AnaTrackB* allFgdTracks[NMAXPARTICLES];

    // Get all the tracks in the FGD
    int nFGD = anaUtils::GetAllTracksUsingDet(*bunch, SubDetId::kFGD, allFgdTracks);

    for (Int_t j = 0; j < nFGD; j++){
      if (!allFgdTracks[j])
        continue;

      ApplyCorrection(spill, *allFgdTracks[j]);
    }

  }


#ifdef DEBUG 
  std::cout << "FGDPIDCorrection::Apply() end " << std::endl;  
#endif

}

//********************************************************************
void FGDPIDCorrection::ApplyCorrection(const AnaSpill& spill, AnaTrackB& track){
  //********************************************************************

  for (int i = 0; i < track.nFGDSegments; i++){
    if (!track.FGDSegments[i])
      continue;

    if (_pulls_mode == 1){
      ApplyFgdPullCorrectionP7(spill, *(static_cast<AnaFGDParticle*>(track.FGDSegments[i])));
    }
    else{
      ApplyFgdPullCorrectionP6(spill, *(static_cast<AnaFGDParticle*>(track.FGDSegments[i])));
    }
  }
}

//********************************************************************
void FGDPIDCorrection::ApplyFgdPullCorrectionP6(const AnaSpill& spill, AnaFGDParticle& track){
  //********************************************************************

  ResetPulls(track);

  Int_t fgdno = SubDetId::TrackUsesOnlyDet(track.Detector, SubDetId::kFGD1) ? 1 : 2;


  Float_t E = track.E;

  Float_t x = GetCorrectedX(spill, track);


#ifdef DEBUG
  std::cout << " FGDPIDCorrection::ApplyFgdPullCorrectionP6(): fgd: " << fgdno << " X: " << x << " E: " << E << std::endl;  
#endif



  if(x <= 0 || E <= 0){
    return;
  }

  for(std::map<ParticleId::ParticleEnum, TString>::iterator part = _particle_names.begin();
      part != _particle_names.end(); part++){
    
    
    if (part->first == ParticleId::kElectron)
      continue;


    if(fgdno == 1){
      Int_t bin = _pull_EvsX_FGD1[part->first].FindBin(x);
      Int_t nbins = _pull_EvsX_FGD1[part->first].GetNbinsX();
      if(bin <= 0 || bin > nbins){
        ResetPulls(track);
        return;
      }

      Float_t E_exp = _pull_EvsX_FGD1[part->first].GetBinContent(bin);
      Float_t error = _pull_EvsX_FGD1[part->first].GetBinError(bin);


      if (error <= 0 || E_exp <= 0){
        ResetPulls(track);  
        return;
      }

      double pull = (E - E_exp)/error;

#ifdef DEBUG
      std::cout << " FGDPIDCorrection::ApplyFgdPullCorrectionP6(): particle: " << part->second << " pull: " << pull << std::endl;  
#endif
      WritePullInfo(part->first, track, pull);
    }
    else if(fgdno == 2){

      Int_t bin = _pull_EvsX_FGD2[part->first].FindBin(x);
      Int_t nbins = _pull_EvsX_FGD2[part->first].GetNbinsX();

      if (bin <= 0 || bin > nbins){
        ResetPulls(track);
        return;
      }

      Float_t E_exp = _pull_EvsX_FGD2[part->first].GetBinContent(bin);
      Float_t error = _pull_EvsX_FGD2[part->first].GetBinError(bin);


      if(error <= 0 || E_exp <= 0){ // error,E_mc not available in the pull file
        ResetPulls(track);
        return;
      }

      double pull = (E - E_exp)/error;

#ifdef DEBUG
      std::cout << " FGDPIDCorrection::ApplyFgdPullCorrectionP6(): particle: " << part->second << " pull: " << pull << std::endl;  
#endif
      WritePullInfo(part->first, track, pull);
    }

  }

  return;


}

//********************************************************************
void FGDPIDCorrection::ApplyFgdPullCorrectionP7(const AnaSpill& spill, AnaFGDParticle& track){
  //********************************************************************

  ResetPulls(track);

  Int_t fgdno = SubDetId::TrackUsesOnlyDet(track.Detector, SubDetId::kFGD1) ? 1 : 2;

  Float_t E = track.E;

  Float_t x = GetCorrectedX(spill, track);


#ifdef DEBUG
  std::cout << " FGDPIDCorrection::ApplyFgdPullCorrectionP7(): fgd: " << fgdno << " X: " << x << " E: " << E << std::endl;  
#endif


  //Get bin number
  int xbin = (int)x/10;

  if (x <= 0 || E <= 0){
    return;
  }

  double energy, sigma;
  std::map<int, std::pair<double, double> >::iterator it;
  bool found = false;
  double pull = 0;

  for (std::map<ParticleId::ParticleEnum, TString>::iterator part = _particle_names.begin(); part != _particle_names.end(); part++){


    std::map<int, std::pair<double, double> > map = _pid_map[part->first].Get_Binned_PDF(fgdno);

    //If there is a value in the PDF corresponding to the desired bin, use it to calculate pull

    found = false;
    it = map.find(xbin);
    if (it != map.end()) found = true;
    if(found){
      energy = it->second.first;
      sigma = it->second.second;
      pull = (E - energy)/(sigma);
    }
    else{
      std::vector<double> pars = _pid_map[part->first].Get_PDF_Pars(1);
      pull = (E-(pars[0]*TMath::Power(x,pars[1])+pars[2]*x))/(pars[3]*x+pars[4]);
    }


#ifdef DEBUG
    std::cout << " FGDPIDCorrection::ApplyFgdPullCorrectionP7(): particle: " << part->second << " pull: " << pull << std::endl;  
#endif

    WritePullInfo(part->first, track, pull);

  } // end loop over particle hypothesis

  return;
}


//********************************************************************
Float_t FGDPIDCorrection::GetCorrectedX(const AnaSpill& spill, const AnaFGDParticle& track) const{
//********************************************************************

  (void)spill;
  
  Float_t XCorr = track.X;
  
  if (!_apply_corr_missing_water){
   return XCorr; 
  } 
  
  // Only for FGD2
  if (SubDetId::TrackUsesOnlyDet(track.Detector, SubDetId::kFGD1)){
    return XCorr;
  }
  
  // Only for tracks crossing the first empty (Run7 onwards)
  bool cross = (track.PositionStart[2] < DetDef::fgd2WaterCenter[0] && DetDef::fgd2WaterCenter[0] < track.PositionEnd[2]) ||
    (track.PositionEnd[2] < DetDef::fgd2WaterCenter[0] && DetDef::fgd2WaterCenter[0] < track.PositionStart[2]);

  if (!cross){
    return XCorr;
  }
  
  // Apply a scaling factor

  XCorr *= _xfactor; 
  
  return XCorr;

}

//********************************************************************
void FGDPIDCorrection::WritePullInfo(ParticleId::ParticleEnum part, AnaFGDParticle& track, Float_t pull) const{
  //********************************************************************

  switch (part) {
    case ParticleId::kMuon:
      track.Pullmu = pull;
      track.Pullno = 0;
      break;

    case ParticleId::kElectron:
      track.Pulle = pull;
      track.Pullno = 0;
      break;

    case ParticleId::kPiPos:
      track.Pullpi = pull;
      track.Pullno = 0;
      break;

    case ParticleId::kProton:
      track.Pullp = pull;
      track.Pullno = 0;
      break;
    default:
      break;

  }

}

//********************************************************************
bool FGDPIDCorrection::ReadFile(const char partName[], int fgd, std::map<int, std::pair<double, double> >& pid_map){
  //********************************************************************

  ifstream inputFile;

  inputFile.open(Form("%s/data/FGDPID/pdf_fgd%i_%s.dat", getenv("HIGHLANDCORRECTIONSROOT"), fgd, partName));

  // If input file doesn't exist.
  if (!inputFile){
    std::cout << Form("FGD PID - File %s not found", Form("%s/data/FGDPID/pdf_fgd%i_%s.dat", getenv("HIGHLANDCORRECTIONSROOT"), fgd, partName)) << std::endl;
    return false;
  }

  inputFile.clear();
  inputFile.seekg(0, ios::beg);

  char name[180], bin[10], energy[20], ene_err[20], sigma[20], sig_err[20];

  while(inputFile.good()){
    inputFile.getline(name, 180);
    inputFile >> bin >> energy >> ene_err >> sigma >> sig_err;
    int nbin = atoi(bin);
    if(nbin < 1) break;
    double ene=atof(energy);
    double sig=atof(sigma);
    std::pair<double, double> ene_sig(ene, sig);
    pid_map[nbin] = ene_sig;
  }

  if(inputFile.is_open()) inputFile.close();

  return true;
}


//********************************************************************
bool FGDPIDCorrection::ReadFitPars(const char partName[],int fgdno, std::vector<double>& pid_vec){
  //********************************************************************
  ifstream inputFile;

  inputFile.open(Form("%s/data/FGDPID/pdf_fitting_fgd%i.dat", getenv("HIGHLANDCORRECTIONSROOT"), fgdno));

  // If input file doesn't exist.
  if (!inputFile){
    std::cout << Form("FGD PID fitting %s file doesn't exist", Form("%s/data/FGDPID/pdf_fitting_fgd%i.dat", getenv("HIGHLANDCORRECTIONSROOT"), fgdno)) << std::endl;
    return false;
  }

  inputFile.clear();
  inputFile.seekg(0, ios::beg);

  
  char particle[20];
  int toProcess=20;
  if (strlen(partName)<20) toProcess = strlen(partName);
  toProcess++;
  for (int i=0; i<toProcess; i++){
    particle[i]=toupper(partName[i]);    	
  }  
  bool find =true;
 
  char name[40];

  while (find){
    inputFile.getline(name, 40);
    if (inputFile.eof()){
      std::cout << " FGDPIDCorrection::ReadFitPars(): particle "<<
    	    	particle << " not found in "<<
    	    	Form(" file %s/data/FGDPID/pdf_fitting_fgd%i.dat", getenv("HIGHLANDCORRECTIONSROOT"), fgdno) << std::endl;
      exit(1);	
    }
    if (strcmp(name, particle)==0)
    	    find=false;
    }
  
  inputFile.getline(name, 40);

  char par[4], value[20], div[4], err[20];

  inputFile >> par >> value >> div >> err;
  pid_vec.push_back(atof(value));
  inputFile >> par >> value >> div >> err;
  pid_vec.push_back(atof(value));
  inputFile >> par >> value >> div >> err;
  pid_vec.push_back(atof(value));

  inputFile >> par >> value >> div >> err;

  inputFile >> name;

  inputFile >> par >> value >> div >> err;
  pid_vec.push_back(atof(value));
  inputFile >> par >> value >> div >> err;
  pid_vec.push_back(atof(value));

  if(inputFile.is_open()) inputFile.close();

  return true;
}

//********************************************************************
TH1F FGDPIDCorrection::ReadPull(TString partName,TString method,int fgdno,double units){
  //********************************************************************
  TH1F pull;

  TString initName = (fgdno == 1 || fgdno == 2) ? Form("pulls_%s_FGD%d",method.Data(),fgdno) : Form("pulls_%s",method.Data());
  TString dirName = getenv("HIGHLANDCORRECTIONSROOT") + TString("/data/FGDPID");
  TString fullFileName(Form("%s/%s.dat",dirName.Data(),initName.Data()));

  ifstream inputFile(fullFileName.Data(), std::ios::in);

  // If input file doesn't exist.
  if (!inputFile){
    //Throw exception.
    std::cout << " FGDPIDCorrection: ReadPull() - Cannot open input file " << fullFileName.Data() << std::endl;
    exit(1);
  }

  std::string inputString;
  int inputState = -1;
  TString histoName, histoTitle;
  int histoNbins = 0;
  double histoXmin = 0, histoXmax = 0;
  int binNo = -1;
  double binContent = -1;

  TString curPartName = partName;

  while(inputFile >> inputString){

    if(inputString == "-")
      inputState = 0;
    else if(inputState == 0 && inputString == "Particle")
      inputState = 1;
    else if(inputState == 1){
      curPartName = inputString;
      inputState = 2;
    }

    if(curPartName != partName)
      continue;        

    if(inputState == 2 && inputString == "Name")
      inputState = 3;
    else if(inputState == 3){
      histoName = inputString;
      inputState = 4;
    }
    else if(inputState == 4 && inputString == "Title")
      inputState = 5;
    else if(inputState == 5){
      histoTitle = inputString;
      inputState = 6;
      pull.SetNameTitle(histoName.Data(),histoTitle.Data());
    }
    else if(inputState == 6 && inputString == "Nbins")
      inputState = 7;
    else if(inputState == 7){
      histoNbins = atoi(inputString.c_str());
      inputState = 8;
    }
    else if(inputState == 8 && inputString == "Range")
      inputState = 9;
    else if(inputState == 9){
      histoXmin = atof(inputString.c_str())*units;
      inputState = 10;
    }
    else if(inputState == 10){
      histoXmax = atof(inputString.c_str())*units;
      inputState = 11;
      pull.SetBins(histoNbins,histoXmin,histoXmax);               
    }
    else if(inputState == 11 && inputString == "Entries")
      inputState = 12;
    else if(inputState == 12){
      int histoEntries = atoi(inputString.c_str());
      inputState = 13;
      pull.SetEntries(histoEntries);
    }
    else if(inputState == 13 && inputString == "Bin")
      inputState = 14;
    else if(inputState == 14){
      binNo = atoi(inputString.c_str());
      inputState = 15;
    }
    else if(inputState == 15){
      binContent = atof(inputString.c_str());
      inputState = 16;
    }
    else if(inputState == 16 && binNo >= 0 && binContent >= 0){
      double binError = atof(inputString.c_str());
      inputState = 13;
      pull.SetBinContent(binNo,binContent);
      pull.SetBinError(binNo,binError);
    }

  }

  if (inputState < 2) {
    std::cout << " FGDPIDCorrection: ReadPulls() Input file " << fullFileName.Data() << " last input state " << inputState << "\n" << std::endl;
    exit(1);
  } 

  if(inputFile.is_open())
    inputFile.close();

  return pull;
}

