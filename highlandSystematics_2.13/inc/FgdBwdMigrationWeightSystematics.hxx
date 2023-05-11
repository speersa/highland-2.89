#ifndef FgdBwdMigrationWeightSystematics_h
#define FgdBwdMigrationWeightSystematics_h

#include "EventWeightBase.hxx"
#include "BinnedParams.hxx"

class FgdBwdMigrationWeightSystematics: public EventWeightBase, public BinnedParams {
public:

  FgdBwdMigrationWeightSystematics(const std::string& folder = std::string(getenv("HIGHLANDSYSTEMATICSROOT")) + "/data", 
      const std::string& name = "FgdBwdMigrationWeightSystematics");
  
  
  virtual ~FgdBwdMigrationWeightSystematics() {}

  
  /// Apply the systematic
  Weight_h ComputeWeight(const ToyExperiment&, const AnaEventC&, const ToyBoxB&){return 1;}
  
  Weight_h ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel);
  
  /// A function to get which value to use to select bin: e.g. topology or
  /// something more
  virtual Float_t GetSystBinValue(const AnaEventC& event, const ToyBoxB& boxB, const SelectionBase& sel) const;

  /// This is the function to implement correlation based on given index,
  /// returns a new index: no correlation by default
  virtual Int_t ApplyCorrelation(Int_t index) const{
    return index;
  }
  
protected:
  /// Set fraction to 0 or 1 if it is outside the limits
  Float_t CorrectFraction(Float_t) const;
  

};

#endif
