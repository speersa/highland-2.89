#ifndef FGDChargeUtils_h
#define FGDChargeUtils_h

#include "DataClasses.hxx"


namespace anaUtils{

  class FGDChargeCorrector{


  public:
    /// Constructor
    FGDChargeCorrector();


    /// Destructor
    virtual ~FGDChargeCorrector(){}

    /// Get energy given a charge
    Float_t GetEnergy(const Float_t& charge) const;

    /// Get energy given a hit
    Float_t GetEnergy(const AnaHit& hit) const;

    /// Get Birks correction for a visible charge given an energy deposit and dX
    Float_t GetBirksCorrection(const Float_t& dE, const Float_t& dX) const;

    /// Get Birks correction for a visible charge given an energy deposit and dX and the cutoff stopping power
    Float_t GetBirksCorrection(const Float_t& dE, const Float_t& dX, const Float_t& cutoff) const;

    /// Get attenuation inside a WLS fiber given a path length
    Float_t GetAttenuation(const Float_t& pathlength) const;

    /// Get attenuation correction given a path length 
    Float_t GetAttenuationCorrection(const Float_t& pathlength) const;

    /// Get path length in fiber given a pos and an FGD hit type: kXZ or kYZ
    /// A position is need to retrieve an unknown coordinate
    Float_t GetPathLengthInFiber(const Float_t* pos, const AnaHit::TypeEnum& type) const;

    /// Get path length in fiber given a hit and a  position
    /// A position is need to retrieve an unknown coordinate
    Float_t GetPathLengthInFiber(const AnaHit& hit, const Float_t* pos) const;

    /// Get energy corrected for attenuation in fiber 
    /// given a charge, a pos and an FGD hit type: kXZ or kYZ
    /// A position is need to retrieve an unknown coordinate
    Float_t GetFiberCorrectedEnergy(const Float_t& charge, const Float_t* pos, const AnaHit::TypeEnum& type) const; 

    /// Get energy corrected for attenuation in fiber 
    /// given a hit and  a pos
    /// A position is need to retrieve an unknown coordinate
    Float_t GetFiberCorrectedEnergy(const AnaHit& hit, const Float_t* pos) const;

    /// Get fully calibrated energy: corrected for fiber attenuation and Birks effect 
    /// Given a charge, a pos, range, and an FGD hit type: kXZ or kYZ
    /// A position is need to retrieve an unknown coordinate
    Float_t GetCalibratedEDeposit(const Float_t& charge, const Float_t* pos,
        const Float_t& dX, const AnaHit::TypeEnum& type) const;

    /// Get fully calibrated energy: corrected for fiber attenuation and Birks effect 
    /// Given a charge, a pos, range, and an FGD hit type: kXZ or kYZ, and the cutoff stopping power
    /// A position is need to retrieve an unknown coordinate
    Float_t GetCalibratedEDeposit(const Float_t& charge, const Float_t* pos,
        const Float_t& dX, const AnaHit::TypeEnum& type, const Float_t& cutoff) const;


    /// Get fully calibrated energy: corrected for fiber attenuation and Birks effect 
    /// Given a hit, a pos and range
    /// A position is need to retrieve an unknown coordinate
    Float_t GetCalibratedEDeposit(const AnaHit& hit, const Float_t* pos, const Float_t& dX) const;

    /// Get fully calibrated energy: corrected for fiber attenuation and Birks effect 
    /// Given a hit, a pos, range, and the cutoff stopping power
    /// A position is need to retrieve an unknown coordinate
    Float_t GetCalibratedEDeposit(const AnaHit& hit, const Float_t* pos, const Float_t& dX, const Float_t& cutoff) const;

    /// Check whether a given type is a valid FGD type: FGD has kXZ or kYZ bars
    bool IsValidHitType(const AnaHit::TypeEnum& type) const;

    /// Getters
    Float_t GetExtraFiberLength() const{
      return _extraFiberLength;
    }

    Float_t GetBarLength() const{
      return _barLength;
    }

    void GetAttParams(Float_t* params) const{
      for (int i=0; i<6; i++){
        params[i] = _attParams[i];
      } 
    }

    Float_t GetBirksC() const{
      return _birksC;
    }

    Float_t GetPeuMeV() const{
      return _peuMeV;
    }

  private:
    Float_t _extraFiberLength;
    Float_t _barLength;
    Float_t _birksC;
    Float_t _peuMeV;

    Float_t _attParams[6];
  };


};




#endif
