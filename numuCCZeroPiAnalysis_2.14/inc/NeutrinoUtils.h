#include "T2KParticle.h"

class NeutrinoUtils
{
 public:
  enum NeutrinoParent{
    kNull = -999,
    kBad = -2,
    kLost = -1,
    kOther=0,
    kPion,
    kKaon,
    kMuon
  };
  
  static void IniCC();
  static void IniCCQE();

  //--- Reconstruction related
  static const TLorentzVector * fNeutrinoRec;
  static T2KParticle * fMuonRec; 
  static T2KParticle * fProtonRec; 
  static TVector3 * fDeltaRecPt;
  static Double_t * fDeltaRecPhi_t;
  static TVector3 * fRecKmu_t;
  static TVector3 * fRecKp_t;
  static Double_t * fReconRecNuEnergy;
  static Double_t * fReconRecTgtMass;


  static const TLorentzVector * fNeutrinoGuess;
  static T2KParticle * fMuonGuess;

  //--- Simulation related
  static const TLorentzVector * fNeutrinoSim;
  static T2KParticle * fMuonSim;
  static T2KParticle * fProtonSim;
  static T2KParticle * fNeutronToy;
  static T2KParticle * fProtonToy;
  static T2KParticle * fProtonDet;
  static TVector3 * fDeltaSimPt;
  static TVector3 * fDeltaToyPt;
  static TVector3 * fDeltaDetPt;
  static TVector3 * fSimKmu_t;
  static TVector3 * fToyKmu_t;
  static TVector3 * fDetKmu_t;
  static TVector3 * fSimKp_t;
  static TVector3 * fToyKp_t;
  static TVector3 * fDetKp_t;
  static Double_t * fDeltaSimPhi_t;
  static Double_t * fDeltaToyPhi_t;
  static Double_t * fDeltaDetPhi_t;
  static Double_t * fReconSimNuEnergy;
  static Double_t * fReconSimTgtMass;  
  static Double_t * fReconDetNuEnergy;
  static Double_t * fReconDetTgtMass; 
  static Double_t * fReconToyNuEnergy;
  static Double_t * fReconToyTgtMass;
  
  static const TVector3 * fNeutrinoParentDecPointSim;
  
  static Double_t fOsciMuMuProb;
  static Int_t fkOsciMuSurvive;
  static Int_t fNeutrinoParentPDG;
  static Int_t fNeutrinoParentType;
  static Int_t fNeutrinoType;
  static Int_t fNeutMode;

  static void SetMuonNRec(const Int_t var){ fMuonNRec = var; }
  static Int_t GetMuonNRec(){return fMuonNRec;}
  static void SetMuonNSim(const Int_t var){ fMuonNSim = var; }
  static Int_t GetMuonNSim(){return fMuonNSim;}
  
  static void SetProtonNRec(const Int_t var){ fProtonNRec = var; }
  static Int_t GetProtonNRec(){return fProtonNRec;}
  static void SetProtonNSim(const Int_t var){ fProtonNSim = var; }
  static Int_t GetProtonNSim(){return fProtonNSim;}

  static void SetMultiplicity(const Int_t mul){fMultiplicity = mul;}
  static Int_t GetMultiplicity(){return fMultiplicity;}
  
  //only rec. meaningful; phi angle in the transver plane w.r.t. beam direction, -180 ~ 180, by definition muon at (-)180.
  static Double_t fBetaRec[10];  
  static Double_t fGammaRec[10];
  
  //-------- Calculations ---------
  static void SetDeltaPt();
  static void SetReconTgtMass();

  //--- Reconstruction related
  Double_t CalcBetaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2);
  Double_t CalcGammaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2);
 
  static void SetRecGuessKinematics(const Bool_t kdummy=kFALSE);

  //---Simulation related
  static void MuonNSimSanityCheck();

  static void SetSimKinematics();

  //-------- IO ---------
  static TTree * GetTree();
  static TList * GetHistList();

  static Int_t FillCount(TList *lin, const Int_t var){ return NeutrinoTools::FillTH1I(lin, kcount, var);}

 private:
  //==========================================================
  //Variables and setters
  //==========================================================
  //--- Reconstruction related
  static Double_t fdNeutrinoGuessNeutrinoSim;
  static Double_t fdNeutrinoGuessMuonRec;
  static const Int_t fCutNR;
  static Double_t fGuessCorrection;
  static void SetdNeutrinoGuessNeutrinoSim(); 
  static void SetdNeutrinoGuessMuonRec();

  static Int_t fMuonNRec;
  static Int_t fProtonNRec;
  
  static Int_t fMultiplicity; 
  static Double_t fMeanBetaRec; 
  static void SetMeanBetaRec(const Bool_t kdummy = kFALSE);
  static Double_t fMeanGammaRec;//use Mean instead of sum to get rid of multiplicity
  static void SetMeanGammaRec(const Bool_t kdummy = kFALSE);

  ///---Simulation related
  static Bool_t IsCC(){ return TMath::Abs(fNeutMode)<30;}

  static Int_t fMuonNSim;
  static Int_t fProtonNSim;
 
  enum histID{
    kcount,
    kDUMMY
  };

};

//__________________________________________________________

const TLorentzVector * NeutrinoUtils::fNeutrinoRec = 0x0;
T2KParticle *NeutrinoUtils::fMuonRec=0x0; 
T2KParticle *NeutrinoUtils::fProtonRec=0x0; 
TVector3 * NeutrinoUtils::fDeltaRecPt = 0x0;
Double_t * NeutrinoUtils::fDeltaRecPhi_t = 0x0;
TVector3 * NeutrinoUtils::fRecKmu_t = 0x0;
TVector3 * NeutrinoUtils::fRecKp_t = 0x0;
Double_t * NeutrinoUtils::fReconRecNuEnergy = 0x0;
Double_t * NeutrinoUtils::fReconRecTgtMass = 0x0;
const TLorentzVector * NeutrinoUtils::fNeutrinoGuess = 0x0;
T2KParticle *NeutrinoUtils::fMuonGuess=0x0; 
const TLorentzVector * NeutrinoUtils::fNeutrinoSim = 0x0;
T2KParticle *NeutrinoUtils::fMuonSim=0x0; 
T2KParticle *NeutrinoUtils::fProtonSim=0x0; 
T2KParticle *NeutrinoUtils::fNeutronToy=0x0; 
T2KParticle *NeutrinoUtils::fProtonToy=0x0; 
T2KParticle *NeutrinoUtils::fProtonDet=0x0; 
TVector3 * NeutrinoUtils::fDeltaSimPt = 0x0;
TVector3 * NeutrinoUtils::fDeltaToyPt = 0x0;
TVector3 * NeutrinoUtils::fDeltaDetPt = 0x0;
Double_t * NeutrinoUtils::fDeltaSimPhi_t = 0x0;
Double_t * NeutrinoUtils::fDeltaToyPhi_t = 0x0;
Double_t * NeutrinoUtils::fDeltaDetPhi_t = 0x0;
TVector3 * NeutrinoUtils::fSimKmu_t = 0x0;
TVector3 * NeutrinoUtils::fToyKmu_t = 0x0;
TVector3 * NeutrinoUtils::fDetKmu_t = 0x0;
TVector3 * NeutrinoUtils::fSimKp_t = 0x0;
TVector3 * NeutrinoUtils::fToyKp_t = 0x0;
TVector3 * NeutrinoUtils::fDetKp_t = 0x0;
Double_t * NeutrinoUtils::fReconSimNuEnergy = 0x0;
Double_t * NeutrinoUtils::fReconSimTgtMass = 0x0;
Double_t * NeutrinoUtils::fReconDetNuEnergy = 0x0;
Double_t * NeutrinoUtils::fReconDetTgtMass = 0x0;
Double_t * NeutrinoUtils::fReconToyNuEnergy = 0x0;
Double_t * NeutrinoUtils::fReconToyTgtMass = 0x0;


const TVector3 * NeutrinoUtils::fNeutrinoParentDecPointSim = 0x0;

Double_t NeutrinoUtils::fOsciMuMuProb = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fkOsciMuSurvive = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fNeutrinoParentPDG = NeutrinoUtils::kNull;
Int_t NeutrinoUtils::fNeutrinoParentType = NeutrinoUtils::kNull;
Int_t NeutrinoUtils::fNeutrinoType = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fNeutMode = NeutrinoTools::kIniValue;

Int_t NeutrinoUtils::fMuonNRec = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fMuonNSim = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fProtonNRec = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fProtonNSim = NeutrinoTools::kIniValue;

Int_t NeutrinoUtils::fMultiplicity = NeutrinoTools::kIniValue;

Double_t NeutrinoUtils::fBetaRec[10]={NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue};
Double_t NeutrinoUtils::fMeanBetaRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fGammaRec[10]={NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue};
Double_t NeutrinoUtils::fMeanGammaRec = NeutrinoTools::kIniValue;

Double_t NeutrinoUtils::fdNeutrinoGuessNeutrinoSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fdNeutrinoGuessMuonRec = NeutrinoTools::kIniValue;

Double_t NeutrinoUtils::fGuessCorrection = 1;
const Int_t NeutrinoUtils::fCutNR = 1;

//_______________________________________________________________________________________________
//_______________________________________________________________________________________________
void NeutrinoUtils::IniCC()
{
  delete NeutrinoUtils::fMuonSim; NeutrinoUtils::fMuonSim= new T2KParticle;
  delete NeutrinoUtils::fMuonRec; NeutrinoUtils::fMuonRec= new T2KParticle;
  delete NeutrinoUtils::fMuonGuess; NeutrinoUtils::fMuonGuess= new T2KParticle;
}

void NeutrinoUtils::IniCCQE()
{
  IniCC();
  delete NeutrinoUtils::fProtonSim; NeutrinoUtils::fProtonSim= new T2KParticle;
  delete NeutrinoUtils::fNeutronToy; NeutrinoUtils::fNeutronToy= new T2KParticle;
  delete NeutrinoUtils::fProtonToy; NeutrinoUtils::fProtonToy= new T2KParticle;
  delete NeutrinoUtils::fProtonDet; NeutrinoUtils::fProtonDet= new T2KParticle;
  delete NeutrinoUtils::fProtonRec; NeutrinoUtils::fProtonRec= new T2KParticle;
  delete NeutrinoUtils::fDeltaRecPt; NeutrinoUtils::fDeltaRecPt=new TVector3;
  delete NeutrinoUtils::fDeltaSimPt; NeutrinoUtils::fDeltaSimPt=new TVector3;
  delete NeutrinoUtils::fDeltaToyPt; NeutrinoUtils::fDeltaToyPt=new TVector3;
  delete NeutrinoUtils::fDeltaDetPt; NeutrinoUtils::fDeltaDetPt=new TVector3;
  delete NeutrinoUtils::fDeltaRecPhi_t; NeutrinoUtils::fDeltaRecPhi_t=new Double_t;
  delete NeutrinoUtils::fDeltaSimPhi_t; NeutrinoUtils::fDeltaSimPhi_t=new Double_t;
  delete NeutrinoUtils::fDeltaToyPhi_t; NeutrinoUtils::fDeltaToyPhi_t=new Double_t;
  delete NeutrinoUtils::fDeltaDetPhi_t; NeutrinoUtils::fDeltaDetPhi_t=new Double_t;
  delete NeutrinoUtils::fRecKmu_t; NeutrinoUtils::fRecKmu_t=new TVector3;
  delete NeutrinoUtils::fSimKmu_t; NeutrinoUtils::fSimKmu_t=new TVector3;
  delete NeutrinoUtils::fToyKmu_t; NeutrinoUtils::fToyKmu_t=new TVector3;
  delete NeutrinoUtils::fDetKmu_t; NeutrinoUtils::fDetKmu_t=new TVector3;
  delete NeutrinoUtils::fRecKp_t; NeutrinoUtils::fRecKp_t=new TVector3;
  delete NeutrinoUtils::fSimKp_t; NeutrinoUtils::fSimKp_t=new TVector3;
  delete NeutrinoUtils::fToyKp_t; NeutrinoUtils::fToyKp_t=new TVector3;
  delete NeutrinoUtils::fDetKp_t; NeutrinoUtils::fDetKp_t=new TVector3;
  delete NeutrinoUtils::fReconRecNuEnergy; NeutrinoUtils::fReconRecNuEnergy=new Double_t;
  delete NeutrinoUtils::fReconRecTgtMass;  NeutrinoUtils::fReconRecTgtMass=new  Double_t;
  delete NeutrinoUtils::fReconSimNuEnergy; NeutrinoUtils::fReconSimNuEnergy=new Double_t;
  delete NeutrinoUtils::fReconSimTgtMass;  NeutrinoUtils::fReconSimTgtMass=new  Double_t;
  delete NeutrinoUtils::fReconDetNuEnergy; NeutrinoUtils::fReconDetNuEnergy=new Double_t;
  delete NeutrinoUtils::fReconDetTgtMass;  NeutrinoUtils::fReconDetTgtMass=new  Double_t;
  delete NeutrinoUtils::fReconToyNuEnergy; NeutrinoUtils::fReconToyNuEnergy=new Double_t;
  delete NeutrinoUtils::fReconToyTgtMass;  NeutrinoUtils::fReconToyTgtMass=new  Double_t;
}

void NeutrinoUtils::SetRecGuessKinematics(const Bool_t kdummy)
{ 
  SetdNeutrinoGuessMuonRec();
  SetMeanBetaRec(kdummy);
  SetMeanGammaRec(kdummy);
}

void NeutrinoUtils::SetSimKinematics()
{ 
  SetdNeutrinoGuessNeutrinoSim();
}

void NeutrinoUtils::SetDeltaPt()
// For each 'type' of reconstrcuted particle pair (recon, Sim(truth), Toy, Det (truth) )
// Fill the value of fDelta*Pt using the Muon and Proton fPt. 
{
  delete fDeltaRecPt; fDeltaRecPt = new TVector3;
  delete fDeltaSimPt; fDeltaSimPt = new TVector3;
  delete fDeltaToyPt; fDeltaToyPt = new TVector3;
  delete fDeltaDetPt; fDeltaDetPt = new TVector3;
 
  delete fDeltaRecPhi_t; fDeltaRecPhi_t = new Double_t;
  delete fDeltaSimPhi_t; fDeltaSimPhi_t = new Double_t;
  delete fDeltaToyPhi_t; fDeltaToyPhi_t = new Double_t;
  delete fDeltaDetPhi_t; fDeltaDetPhi_t = new Double_t;
  
  delete NeutrinoUtils::fRecKmu_t; NeutrinoUtils::fRecKmu_t=new TVector3;
  delete NeutrinoUtils::fSimKmu_t; NeutrinoUtils::fSimKmu_t=new TVector3;
  delete NeutrinoUtils::fToyKmu_t; NeutrinoUtils::fToyKmu_t=new TVector3;
  delete NeutrinoUtils::fDetKmu_t; NeutrinoUtils::fDetKmu_t=new TVector3;
  
  delete NeutrinoUtils::fRecKp_t; NeutrinoUtils::fRecKp_t=new TVector3;
  delete NeutrinoUtils::fSimKp_t; NeutrinoUtils::fSimKp_t=new TVector3;
  delete NeutrinoUtils::fToyKp_t; NeutrinoUtils::fToyKp_t=new TVector3;
  delete NeutrinoUtils::fDetKp_t; NeutrinoUtils::fDetKp_t=new TVector3;
  
  if(fMuonRec->fPt && fProtonRec->fPt){
    //has to be ordered: muon, then proto
    NeutrinoTools::SetDeltaPt(fDeltaRecPt, fMuonRec->fPt, fProtonRec->fPt);
    NeutrinoTools::SetDeltaPhi_t(fDeltaRecPhi_t, fMuonRec->fPt, fProtonRec->fPt);
    NeutrinoTools::SetK_t(fRecKmu_t, fDeltaRecPhi_t, fMuonRec->fPt);
    NeutrinoTools::SetK_t(fRecKp_t, fDeltaRecPhi_t, fProtonRec->fPt);

    //std::cout<<"deltaRecphi_t in Utils is "<<*fDeltaRecPhi_t<<std::endl;


//    //test z001->
//    TVector3 badmuon = fMuonRec->fLorentzVec->Vect();
//    badmuon.SetZ(0.);
//    TVector3 badproton = fProtonRec->fLorentzVec->Vect();
//    badproton.SetZ(0.);
//    NeutrinoTools::SetDeltaPt(fDeltaRecPt, &badmuon, &badproton);
//    //<-
  }

  if(fMuonSim->fPt && fProtonSim->fPt){
    NeutrinoTools::SetDeltaPt(fDeltaSimPt, fMuonSim->fPt, fProtonSim->fPt);
    NeutrinoTools::SetDeltaPhi_t(fDeltaSimPhi_t, fMuonSim->fPt, fProtonSim->fPt);
    NeutrinoTools::SetK_t(fSimKmu_t, fDeltaSimPhi_t, fMuonSim->fPt);
    NeutrinoTools::SetK_t(fSimKp_t, fDeltaSimPhi_t, fProtonSim->fPt);


    /*
    //test->
    fMuonSim->fPt->Print();
    fProtonSim->fPt->Print();
    fDeltaSimPt->Print();
    exit(1);
    //<-
    */
  }

  if(fMuonSim->fPt && fProtonToy->fPt){
    NeutrinoTools::SetDeltaPt(fDeltaToyPt,  fMuonSim->fPt, fProtonToy->fPt);
    NeutrinoTools::SetDeltaPhi_t(fDeltaToyPhi_t,  fMuonSim->fPt, fProtonToy->fPt);
    NeutrinoTools::SetK_t(fToyKmu_t, fDeltaToyPhi_t, fMuonSim->fPt);
    //NeutrinoTools::SetK_t(fToyKp_t, fDeltaToyPhi_t, fProtonSim->fPt);

  }

  if(fMuonSim->fPt && fProtonDet->fPt){
    NeutrinoTools::SetDeltaPt(fDeltaDetPt,  fMuonSim->fPt, fProtonDet->fPt);
    NeutrinoTools::SetDeltaPhi_t(fDeltaDetPhi_t,  fMuonSim->fPt, fProtonDet->fPt);
    NeutrinoTools::SetK_t(fDetKmu_t, fDeltaDetPhi_t, fMuonSim->fPt);
    //NeutrinoTools::SetK_t(fDetKp_t, fDeltaDetPhi_t, fProtonDet->fPt);

  }
}

void NeutrinoUtils::SetReconTgtMass()
{
  
    delete NeutrinoUtils::fReconRecNuEnergy; NeutrinoUtils::fReconRecNuEnergy=new Double_t;
    delete NeutrinoUtils::fReconRecTgtMass;  NeutrinoUtils::fReconRecTgtMass=new  Double_t;
    delete NeutrinoUtils::fReconSimNuEnergy; NeutrinoUtils::fReconSimNuEnergy=new Double_t;
    delete NeutrinoUtils::fReconSimTgtMass;  NeutrinoUtils::fReconSimTgtMass=new  Double_t;
    delete NeutrinoUtils::fReconDetNuEnergy; NeutrinoUtils::fReconDetNuEnergy=new Double_t;
    delete NeutrinoUtils::fReconDetTgtMass;  NeutrinoUtils::fReconDetTgtMass=new  Double_t;
    delete NeutrinoUtils::fReconToyNuEnergy; NeutrinoUtils::fReconToyNuEnergy=new Double_t;
    delete NeutrinoUtils::fReconToyTgtMass;  NeutrinoUtils::fReconToyTgtMass=new  Double_t;
  
    
    if(fMuonRec->fNuDir && fMuonRec->fLorentzVec && fProtonRec->fLorentzVec){    
      *fReconRecNuEnergy = NeutrinoTools::SetReconNuEnergy(fMuonRec->fNuDir ,fMuonRec->fLorentzVec, fProtonRec->fLorentzVec);  
      *fReconRecTgtMass = NeutrinoTools::SetReconTgtMass(fReconRecNuEnergy, fMuonRec->fLorentzVec, fProtonRec->fLorentzVec); 
    }
    if(fMuonSim->fNuDir && fMuonSim->fLorentzVec && fProtonSim->fLorentzVec){          
      *fReconSimNuEnergy = NeutrinoTools::SetReconNuEnergy(fMuonSim->fNuDir ,fMuonSim->fLorentzVec, fProtonSim->fLorentzVec);  
      *fReconSimTgtMass = NeutrinoTools::SetReconTgtMass(fReconSimNuEnergy, fMuonSim->fLorentzVec, fProtonSim->fLorentzVec); 
    }
}

void NeutrinoUtils::SetdNeutrinoGuessNeutrinoSim()
{
  //flat in cos, not tha angle
  //tested with = fNeutrinoRec; should be 0; confirmed
  if(!fNeutrinoGuess){
    fdNeutrinoGuessNeutrinoSim = NeutrinoTools::kNullPointer;
  }
  else{
    const Double_t tmpcos= NeutrinoTools::GetCos(fNeutrinoGuess, fNeutrinoSim, "NeutrinoUtils::SetdNeutrinoGuessNeutrinoSimGetCos");
    if(tmpcos== NeutrinoTools::kZeroDivider){
      fdNeutrinoGuessNeutrinoSim = NeutrinoTools::kZeroDivider;
    }
    else{
      fdNeutrinoGuessNeutrinoSim =  tmpcos - 1;
    }
  }
}

void NeutrinoUtils::SetdNeutrinoGuessMuonRec()
{
  //flat in cos, not tha angle

  //calculation confirmed by
  //tree->Draw("fdNeutrinoGuessMuonRec","fMultiplicity==1") //should = 1
  
  //tested with = &(fMuonRec->Vect())// should be 0; confirmed
  if(!fMuonRec->fLorentzVec || !fNeutrinoGuess){
    fdNeutrinoGuessMuonRec = NeutrinoTools::kNullPointer;
  }
  else{
    const Double_t tmpcos = NeutrinoTools::GetCos(fNeutrinoGuess, fMuonRec->fLorentzVec, "NeutrinoUtils::SetdNeutrinoGuessMuonRecGetCos");
    if(tmpcos== NeutrinoTools::kZeroDivider){
      fdNeutrinoGuessMuonRec = NeutrinoTools::kZeroDivider;
    }
    else{
      fdNeutrinoGuessMuonRec = tmpcos - 1;
    }
  }
}

void NeutrinoUtils::SetMeanBetaRec(const Bool_t kdummy)
{
  if(kdummy){
    fMeanBetaRec = NeutrinoTools::kIniValue;
    return;
  }

  fMeanBetaRec = 0;
  for(Int_t ipar=0; ipar<fMultiplicity; ipar++){
    //remove muon contribution
    if(ipar == fMuonRec->fID){
      continue;
    }

    fMeanBetaRec += fBetaRec[ipar];
  }

  if(fMultiplicity==1){
    fMeanBetaRec=NeutrinoTools::kZeroDivider;
  }
  else{//multiplicity >= 2
    fMeanBetaRec /= (fMultiplicity-1);
  }
}

void NeutrinoUtils::SetMeanGammaRec(const Bool_t kdummy)
{
  if(kdummy){
    fMeanGammaRec = NeutrinoTools::kIniValue;
    return;
  }

  fMeanGammaRec = 0;
  for(Int_t ipar=0; ipar<fMultiplicity; ipar++){
    //remove muon contribution
    if(ipar == fMuonRec->fID){
      continue;
    }
    fMeanGammaRec += fGammaRec[ipar];
  }

  if(fMultiplicity==1){
    fMeanGammaRec = NeutrinoTools::kZeroDivider;
  }
  else{
    fMeanGammaRec /= (fMultiplicity-1);
  }
}

void NeutrinoUtils::MuonNSimSanityCheck()
{
  //sanity check -1
  if(fMuonNSim==0 && IsCC()){
    printf("MuonNSimSanityCheck wrong fMuonNSim CC %d %d\n", fMuonNSim, fNeutMode); exit(1);
  }
  //sanity check -2
  if(fMuonNSim>0 && !IsCC()){
    printf("MuonNSimSanityCheck wrong fMuonNSim NC %d %d\n", fMuonNSim, fNeutMode); exit(1);
  }
}

Double_t NeutrinoUtils::CalcBetaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2)
{
  //
  //magnitude does not magger
  //w.r.t. beam direction (z-axis) and muon opposite direction  (x-axis)
  //-180 ~ 180
  //
  if(!fMuonRec->fPt){
    return NeutrinoTools::kNullPointer;
  }

  const TVector3 *vt = NeutrinoTools::GetVecT(fNeutrinoRec, dir0, dir1, dir2);

  //muon pt direction := -180 deg, i.e. -x axis
  const TVector3 xaxis = (*fMuonRec->fPt)*(-1);

  //0 ~ 180

  
  Double_t beta = NeutrinoTools::GetAngle(&xaxis, vt, "NeutrinoUtils::CalcBetaRec");

  if( (fNeutrinoRec->Vect()).Dot(xaxis.Cross(*vt)) < 0 )
    beta *= -1;

  if(beta<-180 + 1e-3){
    beta+= 360;
  }

  delete vt;
  return beta;
}

Double_t NeutrinoUtils::CalcGammaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2)
{
  const TVector3 vec(dir0, dir1, dir2);

  const TVector3 refdir=fNeutrinoRec->Vect();
  return NeutrinoTools::GetAngle(&vec, &refdir, "NeutrinoUtils::CalcGammaRec");
}

//___________________________________________________________________________________

//___________________________________________________________________________________________________

TTree * NeutrinoUtils::GetTree()
{
  TTree * tout = new TTree("tree","tree");

  const Int_t spl = 99;

  fMuonRec->SetTree("fMuonRec",tout,spl);
  fMuonSim->SetTree("fMuonSim",tout,spl);

  if(fProtonRec && fProtonSim){
    fProtonRec->SetTree("fProtonRec",tout,spl);
    fProtonSim->SetTree("fProtonSim",tout,spl);
  }

  if(fDeltaRecPt && fDeltaSimPt){
    tout->Branch("fDeltaRecPt.", "TVector3", &(fDeltaRecPt), 128000, spl);
    tout->Branch("fDeltaSimPt.", "TVector3", &(fDeltaSimPt), 128000, spl);
  }
  
  if(fDeltaRecPhi_t && fDeltaSimPhi_t){
    //tout->Branch("fDeltaRecPhi_t", "Double_t", &(fDeltaRecPhi_t), 128000, spl);
    tout->Branch("fDeltaRecPhi_t",  fDeltaRecPhi_t, "fDeltaRecPhi_t/D");
    tout->Branch("fDeltaSimPhi_t",  fDeltaSimPhi_t, "fDeltaSimPhi_t/D");
  }
  
  if(fRecKmu_t && fSimKmu_t){
    tout->Branch("fRecKmu_t.", "TVector3", &(fRecKmu_t), 128000, spl);
    tout->Branch("fSimKmu_t.", "TVector3", &(fSimKmu_t), 128000, spl);
  }
  if(fRecKp_t && fSimKp_t){
    tout->Branch("fRecKp_t.", "TVector3", &(fRecKp_t), 128000, spl);
    tout->Branch("fSimKp_t.", "TVector3", &(fSimKp_t), 128000, spl);
  }    
  if(fReconRecNuEnergy && fReconSimNuEnergy){
    tout->Branch("fReconRecNuEnergy",  fReconRecNuEnergy, "fReconRecNuEnergy/D");
    tout->Branch("fReconSimNuEnergy",  fReconSimNuEnergy, "fReconSimNuEnergy/D");
    tout->Branch("fReconRecTgtMass",  fReconRecTgtMass, "fReconRecTgtMass/D");
    tout->Branch("fReconSimTgtMass",  fReconSimTgtMass, "fReconSimTgtMass/D");
  }

  if(fProtonToy && fDeltaToyPt){
    fNeutronToy->SetTree("fNeutronToy",tout,spl);
    fProtonToy->SetTree("fProtonToy",tout,spl);
    tout->Branch("fDeltaToyPt.", "TVector3", &(fDeltaToyPt), 128000, spl);
  }

  if(fProtonDet && fDeltaDetPt){
    fProtonDet->SetTree("fProtonDet",tout,spl);
    tout->Branch("fDeltaDetPt.", "TVector3", &(fDeltaDetPt), 128000, spl);
  }

  tout->Branch("fNeutrinoSim.","TLorentzVector", &fNeutrinoSim, 128000, spl);
  //tout->Branch("fNeutrinoRec.", "TVector3", &(fMuonRec->fNuDir), 128000, spl);
  tout->Branch("fNeutrinoRec.", "TVector3", &(fMuonRec->fNuDir), 128000, spl);
  tout->Branch("fNeutrinoGuess.", "TVector3", &(fMuonGuess->fNuDir), 128000, spl);
  
  tout->Branch("fdNeutrinoGuessNeutrinoSim", &fdNeutrinoGuessNeutrinoSim, "fdNeutrinoGuessNeutrinoSim/D");
  tout->Branch("fdNeutrinoGuessMuonRec", &fdNeutrinoGuessMuonRec, "fdNeutrinoGuessMuonRec/D");

  tout->Branch("fGuessCorrection", &fGuessCorrection, "fGuessCorrection/D");
  tout->Branch("fMuonPtGuess", &(fMuonGuess->fPtMag), "fMuonPtGuess/D");

  tout->Branch("fOsciMuMuProb",&fOsciMuMuProb,"fOsciMuMuProb/D");
  tout->Branch("fkOsciMuSurvive",&fkOsciMuSurvive,"fkOsciMuSurvive/I");
  tout->Branch("fNeutrinoParentPDG",&fNeutrinoParentPDG,"fNeutrinoParentPDG/I");
  tout->Branch("fNeutrinoParentType",&fNeutrinoParentType,"fNeutrinoParentType/I");
  tout->Branch("fNeutrinoType",&fNeutrinoType,"fNeutrinoType/I");
  tout->Branch("fNeutMode",&fNeutMode,"fNeutMode/I");
  tout->Branch("fNeutrinoParentDecPointSim.", "TVector3", &fNeutrinoParentDecPointSim, 128000, spl);

  tout->Branch("fMultiplicity",&fMultiplicity,"fMultiplicity/I");

  tout->Branch("fMuonNSim",&fMuonNSim,"fMuonNSim/I");
  tout->Branch("fMuonNRec",&fMuonNRec,"fMuonNRec/I");
  tout->Branch("fProtonNSim",&fProtonNSim,"fProtonNSim/I");
  tout->Branch("fProtonNRec",&fProtonNRec,"fProtonNRec/I");

  tout->Branch("fMeanBetaRec", &fMeanBetaRec, "fMeanBetaRec/D");
  tout->Branch("fMeanGammaRec", &fMeanGammaRec, "fMeanGammaRec/D");

  return tout;
}

TList * NeutrinoUtils::GetHistList()
{
  TList *lout=new TList;
  lout->SetName("lout");
  
  TH1D * hcount = new TH1D("count","",30, -0.5, 29.5); lout->AddAt(hcount,kcount);  
  return lout;
}
