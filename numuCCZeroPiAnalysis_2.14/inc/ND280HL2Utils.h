#include "NeutrinoUtils.h"
#include "NuDirUtils.hxx"

class ND280HL2Utils
{
 public:
  static void SaveInfo(const Int_t nu_truereac, const Int_t nu_parentpdg, const Int_t nu_pdg, const Int_t ntpctracks);

  static void SetNeutrinoSim(const Float_t nu_truedir[], const Float_t nu_trueE);
  static void SetNeutrinoRec(const Float_t vertex_pos[]);
  static void SetNeutrinoGuess(const Float_t nu_truedir[]);
  static void SetMuonGuess();

  //== independent of NeutrinoUtils
  static TChain * IniIO(const TString flist, const TString tn);
  static Int_t SetParticleSim(const TLorentzVector * nusim, T2KParticle * ftrueptr, const Double_t truemass, const Float_t true_truedir[], const Float_t true_truemom, const Int_t particle);
  static Int_t SetParticleRec(const TLorentzVector * nurec, T2KParticle * selptr, const Double_t selmass, const Float_t sel_dir[], const Float_t sel_mom, const Float_t vertex_pos[], const Float_t sel_endpos[], const Float_t sel_Chi2, const Float_t sel_NDOF, const Int_t sel_ntpcs, const Int_t sel_nfgds, const Int_t sel_tpc_nhits[], const Float_t sel_tpc_charge[]);
  static Int_t SetProtonToy(const Bool_t kstaticN, T2KParticle * neutronToy, const TLorentzVector * nuSim, const TLorentzVector * muonSim, T2KParticle * protonToy, const Int_t murecpdg );

  static const TVector3 * GetNuDirRec(const Float_t vertex_pos[]);


 private:
  static const TVector3 * GetNuDirSim(const Float_t nu_NuParentDecPoint[], const Float_t vertex_truepos[]);


  //== independent of NeutrinoUtils
  //static void SetNeutrinoParentDecPointRec(TVector3 *vec){ vec->SetXYZ(-0.1388, -1.729, 34.55); }
  static void SetNeutrinoParentDecPointRec(TVector3 *vec){ vec->SetXYZ(anaUtils::NeutrinoParentDecay[0], 
      anaUtils::NeutrinoParentDecay[1], anaUtils::NeutrinoParentDecay[2]); }
  //static void SetNeutrinoParentDecPointRec(TVector3 *vec){ vec = new TVector3(DetDef::nd280NeutrinoParentDecay);}

  static const TVector3 * CalcNuDir(const TVector3 * nup0Global, const TVector3 * nup1Local);
  static void SetNeutronToy(T2KParticle *ntoy, const Bool_t kstatic);
  static TLorentzVector *GetFakeProton(const TLorentzVector * neutrinosim,  const TLorentzVector * ntoy, const TLorentzVector * muonsim);
};


void ND280HL2Utils::SetNeutrinoSim(const Float_t nu_truedir[], const Float_t nu_trueE)
{
  delete NeutrinoUtils::fNeutrinoSim;
  NeutrinoUtils::fNeutrinoSim = 0x0;

  TVector3 nup3(nu_truedir[0],nu_truedir[1],nu_truedir[2]);

  if(nu_trueE > EPSILON && nup3.Mag() > EPSILON){
    nup3 *= nu_trueE * 1e-3 / nup3.Mag(); //in GeV/c
    
    const Double_t nuE = nup3.Mag();
    NeutrinoUtils::fNeutrinoSim = new TLorentzVector(nup3, nuE);
  }
}



const TVector3 * ND280HL2Utils::GetNuDirSim(const Float_t nu_NuParentDecPoint[], const Float_t vertex_truepos[])
{
  //-------- nup0 
  //in m
  TVector3 nup0Global(nu_NuParentDecPoint);
  nup0Global *= 0.01; //default cm
  
  //shows a distribution with mean in m: ( -0.1388, -1.729, 34.55 )
  NeutrinoUtils::fNeutrinoParentDecPointSim = new TVector3(nup0Global);

  //------ nup1
  //in m
  TVector3 nup1Local(vertex_truepos);
  nup1Local *= 0.001; //default mm

  const TVector3 * dirsim = CalcNuDir(&nup0Global, &nup1Local);

// //test ->
// TVector3 nuDirTrue(nu_truedir);
// nuDirTrue *= 1./nuDirTrue.Mag();
// 
// const TVector3 ddir=(*dirsim)-nuDirTrue;
// //pass 1E-7, fail at 1E-8
// if(ddir.Mag()>1e-7){
//   printf("test bad!! \n");
//   ddir.Print();
//   dirsim->Print();
//   nuDirTrue.Print();
//   exit(1);
// }
// //test <-

  return dirsim;
}

void ND280HL2Utils::SetNeutrinoRec(const Float_t vertex_pos[])
{
  delete NeutrinoUtils::fNeutrinoRec;
  const TVector3 * nudir = GetNuDirRec(vertex_pos);
  NeutrinoUtils::fNeutrinoRec = new TLorentzVector(*nudir,1);
  delete nudir;
}



void ND280HL2Utils::SetNeutrinoGuess(const Float_t nu_truedir[])
{
  delete NeutrinoUtils::fNeutrinoGuess;
  NeutrinoUtils::fNeutrinoGuess = 0x0;

  //
  //  NeutrinoUtils::fNeutrinoGuess = new TVector3(0,0,1);

  //fast access to true, but not really needed
  TVector3 nup3(nu_truedir[0],nu_truedir[1],nu_truedir[2]);
  
  if(nup3.Mag()>EPSILON){
    //use true beam direciton for Guess so that the pt resolution with true beam dir can be got from pt guess
    //can happen that fNeutrinoSim is bad because at this stage SetNeutrinoSim is not called!!
    NeutrinoUtils::fNeutrinoGuess = new TLorentzVector(nup3.Unit(),1);
  }
}

void ND280HL2Utils::SetMuonGuess()
{
  NeutrinoUtils::fMuonGuess->Reset();

  if(NeutrinoUtils::GetMuonNRec()>0){
    //should call SetParticleRec first!
    NeutrinoUtils::fMuonGuess->fLorentzVec = new TLorentzVector(*(NeutrinoUtils::fMuonRec->fLorentzVec));
    
    //should call SetNeutrinoGuess first
    NeutrinoUtils::fMuonGuess->SetNeutrino(NeutrinoUtils::fNeutrinoGuess);
    
    NeutrinoUtils::fMuonGuess->SetKinematics();
  }
}

void ND280HL2Utils::SaveInfo(const Int_t nu_truereac, const Int_t nu_parentpdg, const Int_t nu_pdg, const Int_t ntpctracks)
{
  NeutrinoUtils::fNeutMode = nu_truereac;
  NeutrinoUtils::fNeutrinoParentPDG = nu_parentpdg;
  NeutrinoUtils::fNeutrinoParentType = NeutrinoTools::PDGToType(NeutrinoUtils::fNeutrinoParentPDG);
  NeutrinoUtils::fNeutrinoType = nu_pdg;
  NeutrinoUtils::fkOsciMuSurvive = 1;

  //use TPC for multiplicity; has to be confirmed; test; 
  NeutrinoUtils::SetMultiplicity(ntpctracks);
}



//================================================================================================
//independent of NeutrinoUtils
//================================================================================================
TChain * ND280HL2Utils::IniIO(const TString flist, const TString tn)
{
  printf("ND280HL2Utils::IniIO flist %s %s\n", flist.Data(), tn.Data());

  return NeutrinoTools::InputFiles(flist, tn);
}

Int_t ND280HL2Utils::SetParticleSim(const TLorentzVector * nusim, T2KParticle * ftrueptr, const Double_t truemass, const Float_t true_truedir[], const Float_t true_truemom, const Int_t particle)
{
  ftrueptr->Reset();

  Int_t nfound = 0;
  //negative mom is -999 due to NC
  TVector3 parp3(true_truedir[0], true_truedir[1], true_truedir[2]);
 // if(true_truemom>EPSILON && parp3.Mag() > EPSILON){
  if(nusim && true_truemom>EPSILON && parp3.Mag() > EPSILON){
    parp3 *= true_truemom * 1e-3 / parp3.Mag();
    
    const Double_t parE = TMath::Sqrt(truemass*truemass+parp3.Mag2());
    //checked by ploting ->M(), confirmed to be 0.1057
    ftrueptr->fLorentzVec = new TLorentzVector(parp3, parE);

    //should SetNeitrinoSim first!!
    ftrueptr->SetNeutrino(nusim);

    ftrueptr->SetKinematics();

    ftrueptr->fPDG = particle;

    ftrueptr->fType =  NeutrinoTools::PDGToType(particle);

    //std::cout << "Verify simulated particle:" << endl;

    //std::cout << ftrueptr->fLorentzVec->E() << std::endl << ftrueptr->fLorentzVec->Z() << std::endl ;

    nfound = 1;
  }
  return nfound;
}

Int_t ND280HL2Utils::SetParticleRec(const TLorentzVector * nurec, T2KParticle * selptr, const Double_t selmass, const Float_t sel_dir[], const Float_t sel_mom, const Float_t vertex_pos[], const Float_t sel_endpos[], const Float_t sel_Chi2, const Float_t sel_NDOF, const Int_t sel_ntpcs, const Int_t sel_nfgds, const Int_t sel_tpc_nhits[], const Float_t sel_tpc_charge[])
{
  //T2KParticle selptr_s = *selptr;
  selptr->Reset();
 
  TVector3 parp3(sel_dir[0],sel_dir[1],sel_dir[2]);
  const Double_t momvar = sel_mom;
  Int_t nrec = 0;
  if(momvar > EPSILON && parp3.Mag()>EPSILON){
    parp3 *= momvar * 1e-3 / parp3.Mag();
    const Double_t parE = TMath::Sqrt(selmass*selmass+parp3.Mag2());
    
    selptr->fLorentzVec = new TLorentzVector(parp3, parE); 
    
    //should call SetNeutrinoRec first!!
    selptr->SetNeutrino(nurec);

    selptr->SetKinematics();
    
    const TVector3 tmpvertex(vertex_pos);
    selptr->fVertex = new TVector3(tmpvertex * 0.001); //default in mm

    const TVector3 tmpendpos(sel_endpos);
    selptr->fEndPos = new TVector3(tmpendpos * 0.001); //default in mm

    selptr->fFlightPath = new TVector3( (tmpendpos-tmpvertex)*0.001 ); //default mm

    selptr->fChi2 = sel_Chi2;
    selptr->fNDOF = sel_NDOF;

    //nhits = sel_tpc_nnodes
    //safe for muon, not for proton due to unknown accmu_level
    if(sel_ntpcs<1){
      //printf("ND280HL2Utils::SetParticleRec bad sel_ntpcs %d\n", sel_ntpcs); exit(1);
    }
    selptr->fNdets[0] = sel_ntpcs;
    selptr->fNdets[1] = sel_nfgds;
    
    for(Int_t itpc=0; itpc<sel_ntpcs; itpc++){
      selptr->fNhits[itpc] = sel_tpc_nhits[itpc];
      selptr->fCharge[itpc] = sel_tpc_charge[itpc];
    }
    nrec = 1;
  }

  return nrec;
}

const TVector3 * ND280HL2Utils::CalcNuDir(const TVector3 * nup0Global, const TVector3 * nup1Local)
{
  if( nup0Global->Mag()<EPSILON || nup1Local->Mag()<EPSILON ){
    return 0x0;
  }

  //in m
  const Double_t nd280x= -3.221999;
  const Double_t nd280y= -8.14599;
  const Double_t nd280z= 280.10;
  const TVector3 nd280Global(nd280x, nd280y, nd280z);

  //in m 
  const TVector3 nup0Local = (*nup0Global) - nd280Global;

  TVector3 *nuDirCalc = new TVector3( (*nup1Local) - nup0Local );
  (*nuDirCalc) *= 1./nuDirCalc->Mag();

  return nuDirCalc;
}


const TVector3 * ND280HL2Utils::GetNuDirRec(const Float_t vertex_pos[])
{
  //=======================================
  //dirRaw001;
  //return (new TVector3(0,0,1));

  //======================================
  //dirSim
  //return GetNuDirSim(nu_NuParentDecPoint, vertex_truepos);

  //========================================
  //dir_p0Sim_p1Rec
  //TVector3 nup0Global(nu_NuParentDecPoint);
  //nup0Global *= 0.01;

  //========================================
  //dir_p0Rec_p1Rec

  //-------- nup0 
  //in m, mean of the distribution, 6B neutrino flux
  TVector3 nup0Global;
  SetNeutrinoParentDecPointRec(&nup0Global);
  //cout << "Set Nu PDP as: " << endl;
  //nup0Global.Print();
  
  //------ nup1
  //in m
  TVector3 nup1Local(vertex_pos);
  nup1Local *= 0.001; //default mm

  return CalcNuDir(&nup0Global, &nup1Local);
}


void ND280HL2Utils::SetNeutronToy(T2KParticle *ntoy, const Bool_t kstatic)
{
  ntoy->Reset();

  if(!kstatic){
    TVector3 fermiP;
    NeutrinoTools::SampleUnityIsotropicVector(&fermiP);
    fermiP *= NeutrinoTools::SampleFermiMomentum();
    
    const Double_t nE = TMath::Sqrt(fermiP.Mag2()+NeutrinoTools::NeutronMass()*NeutrinoTools::NeutronMass());
    ntoy->fLorentzVec = new TLorentzVector(fermiP, nE);
  }
  else{
    ntoy->fLorentzVec = new TLorentzVector(0,0,0, NeutrinoTools::NeutronMass());
  }
}

TLorentzVector *ND280HL2Utils::GetFakeProton(const TLorentzVector * neutrinosim,  const TLorentzVector * ntoy, const TLorentzVector * muonsim)
{
  TLorentzVector * fakep = 0x0;
  if(neutrinosim && muonsim){
    fakep = new TLorentzVector((*neutrinosim)+(*ntoy)-(*muonsim));
  }
  return fakep;
}

Int_t ND280HL2Utils::SetProtonToy(const Bool_t kstaticN, T2KParticle * neutronToy, const TLorentzVector * nuSim, const TLorentzVector * muonSim, T2KParticle * protonToy, const Int_t murecpdg )
{
  protonToy->Reset();
  Int_t ntoy = 0;

  //kstaticN
  //kTRUE:  test with static Neutron to validate the codes
  //kFALSE: fermi motion of neutron
  /*
  //to test
  tree->Draw("fNeutronToy->M()","fMuonNSim>0")
  //all M: ~0-RMS
  
  tree->Draw("fNeutronToy->P()","fMuonNSim>0")
  tree->Draw("fNeutronToy->Theta()","fMuonNSim>0")
  tree->Draw("fNeutronToy->Phi()","fMuonNSim>0")
  
  //static: P, theta, phi: 0
  //non static: P: fermi momentum GEANT4 max~0.17, theta: sin(theta), phi: flat
  
  tree->Draw("fDeltaToyPt->Mag()","fMuonNSim>0")
  tree->Draw("fDeltaToyPt->Theta()","fMuonNSim>0")
  tree->Draw("fDeltaToyPt->Phi()","fMuonNSim>0")
  
  //static: delta pt: ~0, theta(=alpha): not defined (unless for FSIfactor!=1), phi: 0
  */

  SetNeutronToy(neutronToy, kstaticN);

  TLorentzVector * fakeP1 = GetFakeProton(nuSim, neutronToy->fLorentzVec, muonSim);

  if(fakeP1){

    //static void RutherfordTransport(TLorentzVector * v0, const Int_t nstep, const Double_t regtheta, const Double_t regde);
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 0, 0, 0);//no move
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 0, 0, 1e-1);//only de active. dpT small away from 0, dalpha small away from pi, dphi 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 1, 0, 0);//only phi active. dpT nearly 0, dalpha undefined (corresponding to 0 dpT), dphiT 0 --> good. When no polar angle change, azimuth should not change
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 1, 1E-6, 0);//only phi, theta active (phi has to be active!! otherwise only scatter in theta). regtheta=1 too big, dpt mean 0.311 GeV/c. regtheta 1E-6, dpt mean 0.0016 : dpT small away from 0, dalpha big range between 0-pi and mild bump at pi/2, deflection makes the pT projection bigger! dphi small away from 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 1, 1E-6, 1E-1);//all active, one step. dpT small away from 0, dalpha sharp peak at pi, long tail to 0, dip at pi/2! dphi small away from 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 10, 1, 1E-6, 1E-1);//all active, 10 steps. dpt landau, dalpha all pulled to pi (dedx too large), dphi small away from 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 10, 1, 1E-6, 1E-3);//all active, 10 steps. dpt narrow landau, dalpha partial pull and no peak at 0, dphi small away from 0.
    
    //conclusion: not to transport at the moment since too many parameters and no clear way to handle. 
    
    Float_t fakeV[]={ static_cast<Float_t>(fakeP1->X()),  
      static_cast<Float_t>(fakeP1->Y()),
       static_cast<Float_t>(fakeP1->Z())};
    //FSIfactor > 1, accelerated, alpha=0
    //FSIfactor < 1, decelearted, alpha=pi
    const Double_t FSIfactor = 1; //0.1;//2;

    //momentum should be in MeV
    ND280HL2Utils::SetParticleSim(nuSim, protonToy, NeutrinoTools::ProtonMass(), fakeV,   fakeP1->P()*1e3*FSIfactor,   murecpdg);

    ntoy = 1;
  }

  return ntoy;
}
