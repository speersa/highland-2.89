#include "ToyVariations.hxx"

//*************************************************************************
ToyVariations::ToyVariations(Int_t npar){
  //*************************************************************************

  nWeights    = npar;
  nVariations = npar;
  Variations  = new Float_t[npar];
  Weights     = new Float_t[npar];

}

//*************************************************************************
ToyVariations::~ToyVariations(){
  //*************************************************************************
  delete [] Variations;
  delete [] Weights;
}

//******************************************************************
ToyVariations::ToyVariations(const ToyVariations& vars){
  //******************************************************************

  nWeights    = vars.nWeights;
  nVariations = vars.nVariations;
  Variations  = new Float_t[nVariations];
  Weights     = new Float_t[nWeights];
 
  // Copy the weights 
  for (Int_t i = 0; i < nWeights; i++)
    Weights[i] = vars.Weights[i];
  
  // Copy the variations
  for (Int_t i = 0; i < nVariations; i++)
    Variations[i] = vars.Variations[i];
}


//*************************************************************************
Double_t ToyVariations::GetWeight() const{
  //*************************************************************************
  Double_t total_weight=1;
  for (Int_t i=0;i<nWeights;i++)
    total_weight *= Weights[i];
  return total_weight;
}

//*************************************************************************
Double_t ToyVariations::GetWeight(const Int_t* bins, int nBins) const{
  //*************************************************************************

  if (nBins==0) return GetWeight();

  Double_t total_weight=1;
  for (Int_t i=0;i<nBins;i++){
    total_weight *= Weights[bins[i]];
  }
  return total_weight;
}

//*************************************************************************
void ToyVariations::Dump() const{
//*************************************************************************

  for(int i = 0; i < nVariations; i++){
    std::cout << "    Variation[" << i << "] = " << Variations[i] << std::endl;
  }
  
  for(int i = 0; i < nWeights; i++){
    std::cout << "    Variation weight[" << i << "] = " << Weights[i] << std::endl;
  }

}
