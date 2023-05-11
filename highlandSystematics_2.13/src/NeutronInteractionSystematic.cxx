#include "NeutronInteractionSystematic.hxx"
#include <cmath>

//#define DEBUG
//#define DDEBUG


const Float_t neutron_si::NeutronSIPropagator::_maxEnergy = 19.9 * units::GeV;
const Float_t neutron_si::NeutronSIPropagator::_minEnergy = 19.9 * units::MeV;

//##########################################################
//Neutron inelastic cross-section parametrization,  GEANT4
//##########################################################
// scattering cross section for nuclei using the Wellisch-Laidlaw\n"
// parameterization between 19.9 MeV and 19.9 GeV.  Above 19.9 GeV\n"
// the cross section is assumed to be constant 

//********************************************************************
Double_t neutron_si::NeutronSIPropagator::GetNeutronInelasticCrossSection(const Double_t& momentum, const Double_t& Z, const Double_t& A) const{
  //********************************************************************

  Double_t anEnergy = anaUtils::ComputeKineticEnergy(momentum, units::mass_neutron); 

  if (anEnergy <= 0.) { return 0.; }

  if (A < Z) { return 0.; }
  
  if (Z < 2) { return 0.;} //! from G4
  

  if (anEnergy > _maxEnergy) { anEnergy = _maxEnergy; }
  Double_t cross_section = 0.0;
  
  if (anEnergy < units::keV) { return cross_section; }
  
  //Set it to min for small energies???
  if (anEnergy < _minEnergy) { anEnergy = _minEnergy;}
  
   
  Double_t A13 = std::pow(A,-0.3333333333);
  
  
  Double_t elog = std::log10(anEnergy/units::MeV);
  
  Int_t nOfNeutrons = A - Z;
  
  Double_t atomicNumber = Double_t(A);
  
  const Double_t p1 = 1.3773;
  
  Double_t p2 = 1. + 10./atomicNumber   - 0.0006*atomicNumber;
  Double_t p3 = 0.6+ 13./atomicNumber   - 0.0005*atomicNumber;
  Double_t p4 = 7.2449 - 0.018242*atomicNumber;
  Double_t p5 = 1.64 - 1.8/atomicNumber - 0.0005*atomicNumber;
  Double_t p6 = 1. + 200./atomicNumber + 0.02*atomicNumber;
  Double_t p7 = (atomicNumber-70.)*(atomicNumber-200.)/11000.;

  Double_t logN  = std::log(nOfNeutrons);
  Double_t part1 = M_PI*p1*p1*logN;
  Double_t part2 = 1.+ A13 - p2*(1.-1./A13);

  Double_t firstexp = -p4*(elog-p5);
  Double_t first    = 1. + std::exp(firstexp);
  Double_t corr     = 1. + p3*(1.-1./first); 

  Double_t secondexp= -p6*(elog-p7);
  Double_t secondv   = 1.+std::exp(secondexp);
  Double_t corr2    = 1./secondv;

  Double_t xsec = corr*corr2*part1*part2*10.*units::millibarn;

  if (xsec < 0.0) { xsec = 0.0; }
  
  return xsec;

}


//********************************************************************
Double_t neutron_si::NeutronSIPropagator::GetCrossSection(const si_syst::InteractionType& type, const Float_t& mom, const Int_t& pdg, TGeoNode* node) const{
//********************************************************************
 
 // Only work with inelastic at the moment
 if (type != si_syst::kInelastic) return 0.; 
 
 (void)pdg;
  
 TGeoVolume *volume        = node->GetVolume();
 TGeoMaterial *material    = volume->GetMaterial();
 TGeoMixture *mixture      = (TGeoMixture*)material;

 return GetNeutronInelasticCrossSection(mom, mixture->GetZ(), mixture->GetA());
 
}

//********************************************************************
Bool_t neutron_si::NeutronSIPropagator::InVOI(const TVector3& pos) const{
  //********************************************************************
  
  if (_det == SubDetId::kFGD1){
    // This is the edges of the FGD1 volume, plus all the way out to TPCGasMixture in downstream z.
    // (Rounded to the next integer value that includes the value from the geometry in its range).
    Bool_t xOK = -1150.0 < pos.X() && pos.X() < 1150.0;
    Bool_t yOK = -1170.0 < pos.Y() && pos.Y() < 1230.0;
    Bool_t zOK = 98.0 < pos.Z() && pos.Z() < 576.0;

    return xOK && yOK && zOK;
  }
  else if (_det == SubDetId::kFGD2){
    // This is from the TPCGasMixture in upstream z through FGD2 all the way out to TPCGasMixture in downstream z.
    // (Rounded to the next integer value that includes the value from the geometry in its range).
    Bool_t xOK = -1150.0 < pos.X() && pos.X() < 1150.0;
    Bool_t yOK = -1170.0 < pos.Y() && pos.Y() < 1230.0;
    Bool_t zOK = 1347.0 < pos.Z() && pos.Z() < 1934.0;
    return xOK && yOK && zOK;
  }
  return false;

}
