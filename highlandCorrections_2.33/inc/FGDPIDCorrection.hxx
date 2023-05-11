#ifndef FGDPIDCorrection_h
#define FGDPIDCorrection_h

#include "CorrectionBase.hxx"
#include "ParticleId.hxx"
#include <map>
#include "DataClasses.hxx"
#include "TH1F.h"
#include "Parameters.hxx" 

// Set of maps matching the track length bin to the appropriate mean and sigma energy deposits
// Form a struct with separate maps for FGD1 and FGD2
struct fgd_pid_map{
  // For binned PDFs - pair.first is the energy deposit for a given track length, pair.second the sigma
  std::map<int, std::pair<double, double> > FGD1_Binned_PDF;
  std::map<int, std::pair<double, double> > FGD2_Binned_PDF;

  // Vector of parameters to calculate PDF -a, b, c, sa, sb
  std::vector<double> FGD1_PDF_Pars;
  std::vector<double> FGD2_PDF_Pars;

  std::map<int, std::pair<double, double> > Get_Binned_PDF(int i) {
    if(i == 1) return FGD1_Binned_PDF;
    else if(i == 2) return FGD2_Binned_PDF;
    else{
      std::cout << "FGDPIDCorrection: Trying to access binned PID map that does not exist." << std::endl;
      exit(1);
    }
  }

  std::vector<double> Get_PDF_Pars(int i) {
    if(i == 1) return FGD1_PDF_Pars;
    else if(i == 2) return FGD2_PDF_Pars;
    else{
      std::cout << "FGDPIDCorrection: Trying to access PID parameter vector that does not exist." << std::endl;
      exit(1);
    }
  }
};


/// This class defines a correction that affects the pulls of FGD iso objects 

class FGDPIDCorrection: public CorrectionBase {

public:

  FGDPIDCorrection();

  virtual ~FGDPIDCorrection(){}

  /// Apply the correction to all the relevant objects: FGD constituent of an AnaTrack 
  void Apply(AnaSpillC& spill);


protected:

  void ApplyCorrection(const AnaSpill& spill, AnaTrackB& track);
  
  /// Check whether a track is relevant to apply the correction: e.g. momentum resolution was studied for tracker objects only 
  /// Probably should be moved to a base class
  bool IsRelevantObject(const AnaRecObjectC* object) {(void)object; return true;} // all considered for the moment

   
private:
  /// Distribution maps from fgdRecon
  /// pulls for tracks' E vs X
  std::map<ParticleId::ParticleEnum, TH1F> _pull_EvsX_FGD1;
  std::map<ParticleId::ParticleEnum, TH1F> _pull_EvsX_FGD2;

  std::map<ParticleId::ParticleEnum, fgd_pid_map > _pid_map;

  
  /// Particle lists and names
  std::map<ParticleId::ParticleEnum, TString> _particle_names;
  
  void WritePullInfo(ParticleId::ParticleEnum part, AnaFGDParticle& track, Float_t pull) const;

  /// Apply P6B-like
  void ApplyFgdPullCorrectionP6(const AnaSpill& spill, AnaFGDParticle& track);
  
  
  /// Apply P6L/P7-like
  void ApplyFgdPullCorrectionP7(const AnaSpill& spill, AnaFGDParticle& track);

  /// Get corrected length
  /// If an additional correction for Run7 onwards (missing first FGD2 water
  /// layer) is ON then the X value will be corrected accordingly to subtract a
  /// path in one water if the first one is crossed by the track
  /// TODO: should be reviewed if fixed already on pdf generations level e.g.
  /// for prod7 
  
  Float_t GetCorrectedX(const AnaSpill& spill, const AnaFGDParticle& track) const;
 
   
  /// Unset pulls
  void ResetPulls(AnaFGDParticle& track) const{
    
    track.Pullmu = -999;

    track.Pullp  = -999;

    track.Pullpi = -999;

    track.Pulle  = -999;
  
    track.Pullno = 1;
  }
  
   
  /// Function to read the .dat files containing the PDFs
  bool ReadFile(const char partName[], int fgd, std::map<int, std::pair<double, double> >& pid_map);

  /// Function to read the .dat file with the fitting parameters from the PDFs
  bool ReadFitPars(const char partName[],int fgdno, std::vector<double>& pid_vec);
  
  
  /// Old,  prod6B-like pulls 
  TH1F ReadPull(TString partName, TString criteria,int fgdno = -1, double units = 1.);
  
  /// A parameter to control which pull maps to use: 0 - default - p6B-like,
  /// else - new p7-like 
  Int_t _pulls_mode; 
  
  /// A parameter to check whether to apply additional correction for a missing
  /// layer in Run7 onwards
  bool _apply_corr_missing_water;
 
  
  /// Scaling factor for the X range to account for missing water layer in Run7
  /// onwards
  Float_t _xfactor;
  
};

#endif
