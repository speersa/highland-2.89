#include "ToyExperiment.hxx"
#include <assert.h>

//******************************************************************
ToyExperiment::ToyExperiment(){
//******************************************************************

  _nToyVariations=0;

  for(UInt_t i = 0; i < NMAXSYSTEMATICS; ++i){
      _toyVariations[i] = NULL;
  }
  
  _index = -1;

}

//******************************************************************
ToyExperiment::ToyExperiment(const ToyExperiment& toy){
//******************************************************************

  _nToyVariations       = toy.GetNToyVariations();
  
  for(UInt_t i = 0; i < NMAXSYSTEMATICS; ++i){ 
    if(toy.GetToyVariations(i))
      _toyVariations[i] = new ToyVariations(*toy.GetToyVariations(i));
    else
      _toyVariations[i] = NULL;
  }
}

//******************************************************************
ToyExperiment::~ToyExperiment(){
//******************************************************************
  
  for(UInt_t i = 0; i < NMAXSYSTEMATICS; ++i){
    if (_toyVariations[i]) delete _toyVariations[i];
  }

}

//******************************************************************
void ToyExperiment::AddToyVariation(Int_t index, UInt_t npar){
//******************************************************************

  ToyVariations* toyVar = new ToyVariations(npar);
  _toyVariations[index] = toyVar;
  _nToyVariations++;
}



//******************************************************************
void ToyExperiment::Dump() const{
//******************************************************************


  std::cout << "*********************" << std::endl; 
  std::cout << "Dumping ToyExperiment" << std::endl; 
  for(UInt_t i = 0; i < NMAXSYSTEMATICS; ++i){ 
    if(_toyVariations[i]){
      std::cout << " - ToyVariation[" << i << "] Activated" << std::endl;
      _toyVariations[i]->Dump();
    }else{
      std::cout << " - ToyVariation[" << i << "] Not activated" << std::endl;
    }
  }
  std::cout << "*********************" << std::endl; 
}


//******************************************************************
void ToyExperiment::SetToyIndex(Int_t index){
//******************************************************************
  
  HASSERT(index >= 0);
  
  _index = index;

}


