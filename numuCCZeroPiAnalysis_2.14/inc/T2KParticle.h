#include "NeutrinoTools.h"

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TTree.h"

class T2KParticle
{
 public:
  T2KParticle();

  void SetKinematics(){
    SetPt(); 
    SetAlpha(); 
    SetQ2();
  }

  void SetNeutrino(const TLorentzVector * neu)
  {
    fNeutrino = neu;
    //printf("11.1.1\n");
    //std::cout << "fNeutrino: " << fNeutrino->E() << ", " << fNeutrino->X() << std::endl;
    //printf("11.2\n");
    if(fNeutrino)fNuDir = new TVector3(fNeutrino->Vect());
    else fNuDir = new TVector3(999.,999.,999.);
   // printf("11.3\n");
  }

  void Reset();

  void SetTree(TString tag, TTree * tout, const Int_t spl);
  //-----------

  const TLorentzVector * fLorentzVec; 
  const TVector3 * fPt;
  Double_t fPtMag;
  Double_t fAlpha;
  Double_t fQ2;//only make sense for muon in sim

  TVector3 * fVertex;
  TVector3 * fEndPos;
  TVector3 * fFlightPath;

  Double_t fChi2;
  Int_t    fNDOF;
  Int_t fNdets[2];
  Int_t fNhits[3];
  Int_t fCharge[3];

  Int_t fID;

  //sim
  Int_t fPDG;
  Int_t fType;

  const TVector3 * fNuDir;

 private:
  const TLorentzVector * fNeutrino;

  void SetPt();
  void SetAlpha();
  void SetQ2();
};

T2KParticle::T2KParticle():
   fLorentzVec(0x0)
  ,fPt(0x0)
  ,fVertex(0x0)
  ,fEndPos(0x0)
  ,fFlightPath(0x0)
  ,fNuDir(0x0)
  ,fNeutrino(0x0)
{
  //printf("T2KParticle::T2KParticle default constructor called!!\n");
  Reset();
}

void T2KParticle::Reset()
{
  
  delete fLorentzVec; fLorentzVec=0x0;
  delete fPt; fPt=0x0;
  fPtMag = NeutrinoTools::kIniValue;
  fAlpha=NeutrinoTools::kIniValue;
  fQ2=NeutrinoTools::kIniValue;
  
  delete fVertex; fVertex=0x0;
  delete fEndPos; fEndPos=0x0;
  delete fFlightPath; fFlightPath=0x0;
    
  fChi2=NeutrinoTools::kIniValue;
  fNDOF=NeutrinoTools::kIniValue;
  
  fNdets[0]=fNdets[1]=NeutrinoTools::kIniValue;
  fNhits[0]=fNhits[1]=fNhits[2]=NeutrinoTools::kIniValue;
  fCharge[0]=fCharge[1]=fCharge[2]=NeutrinoTools::kIniValue;

  fID=NeutrinoTools::kIniValue;
 
  fPDG=NeutrinoTools::kIniValue;
  fType=NeutrinoTools::kIniValue;

  delete fNuDir; fNuDir = 0x0;

  //external, should not delete
  fNeutrino=0x0;
}

void T2KParticle::SetQ2()
{
  if(fQ2!=NeutrinoTools::kIniValue){
    printf("T2KParticle::SetQ2 fQ2 exist! %f\n", fQ2); exit(1);
  }

  if(!fNeutrino || !fLorentzVec){
    fQ2 = NeutrinoTools::kNullPointer;
  }
  else{
    const TLorentzVector dq = (*fLorentzVec) - (*fNeutrino);
    fQ2 = -dq.Mag2();

    //allow <0 for rec where neutrino energy set to 1
//    if(fQ2<0){
//      printf("T2KParticle::SetQ2 fQ2<0 %e\n", fQ2);
//      exit(1);
//    }
  }
}


void T2KParticle::SetAlpha()
{
  if(fAlpha!=NeutrinoTools::kIniValue){
    printf("T2KParticle::SetAlpha fAlpha exist! %f\n", fAlpha); exit(1);
  }

  if(!fNeutrino || !fLorentzVec){
    fAlpha = NeutrinoTools::kNullPointer;
  }
  else{
    fAlpha = NeutrinoTools::CalcAlpha(fNeutrino, fLorentzVec);
  }
}

void T2KParticle::SetPt()
{
  if(fPt){
    printf("T2KParticle::SetPt fPt exists!\n"); exit(1);
  }
  
  if(fNeutrino && fLorentzVec){
    fPt = NeutrinoTools::GetVecT(fNeutrino, fLorentzVec->Px(), fLorentzVec->Py(), fLorentzVec->Pz() );
    fPtMag = fPt->Mag();
  }

//      //pass 1e-10
//      //test->
//      const Double_t fastpt = fLorentzVec->Pt(*fNeutrinoRec);
//      if( fabs((fPtRec->Mag()/fastpt)-1)>1E-10 ){
//        printf("T2KParticle::SetMuonPtRec fast %f slow %f ratio %f\n", fastpt, fPtRec->Mag(), fPtRec->Mag()/fastpt);
//      }
//      //test <-
  
}

void T2KParticle::SetTree(TString tag, TTree * tout, const Int_t spl)
{
  tout->Branch(tag+".","TLorentzVector", &(fLorentzVec), 128000, spl);
  tout->Branch(tag+"Pt.", "TVector3", &(fPt), 128000, spl);
  tout->Branch(tag+"PtMag", &(fPtMag), tag+"PtMag/D");
  tout->Branch(tag+"Alpha", &(fAlpha), tag+"Alpha/D");
  tout->Branch(tag+"Q2", &(fQ2), tag+"Q2/D");

  tout->Branch(tag+"Vertex.", "TVector3", &(fVertex), 128000, spl);
  tout->Branch(tag+"EndPos.", "TVector3", &(fEndPos), 128000, spl);
  tout->Branch(tag+"FlightPath.", "TVector3", &(fFlightPath), 128000, spl);

  tout->Branch(tag+"Chi2", &(fChi2), tag+"Chi2/D");
  tout->Branch(tag+"NDOF", &(fNDOF), tag+"NDOF/I");

  tout->Branch(tag+"Ndets",&(fNdets),tag+"Ndets[2]/I");
  tout->Branch(tag+"Nhits",&(fNhits),tag+"Nhits[3]/I");
  tout->Branch(tag+"Charge",&(fCharge),tag+"Charge[3]/I");

  tout->Branch(tag+"ID",&(fID),tag+"ID/I");

  tout->Branch(tag+"PDG",&(fPDG),tag+"PDG/I");
  tout->Branch(tag+"Type",&(fType),tag+"Type/I");
}
