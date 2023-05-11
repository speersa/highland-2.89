#ifndef FgdBwdMigrationWeightSystematicsCCZeroPi_h
#define FgdBwdMigrationWeightSystematicsCCZeroPi_h

#include "FgdBwdMigrationWeightSystematics.hxx"

class FgdBwdMigrationWeightSystematicsCCZeroPi: public FgdBwdMigrationWeightSystematics{
public:

  FgdBwdMigrationWeightSystematicsCCZeroPi(bool apply_corr = false): FgdBwdMigrationWeightSystematics(std::string(getenv("NUMUCCZEROPIANALYSISROOT")) + "/data", 
      "FgdBwdMigrationWeightSystematicsCCZeroPi"){
    _apply_corr = apply_corr;
  }
  
  
  virtual ~FgdBwdMigrationWeightSystematicsCCZeroPi() {}
  
  /// A function to get which value to use to select bin: e.g. topology or
  /// something more
  virtual Float_t GetSystBinValue(const AnaEventC& event, const ToyBoxB& boxB, const SelectionBase& sel) const;
  
  /// Correlations
  Int_t ApplyCorrelation(Int_t index) const; 
  
private:
  bool _apply_corr;
  

};

#endif
