#ifndef ND280BeamBunching_h
#define ND280BeamBunching_h

#include "BeamBunching.hxx"

const UInt_t NBUNCHES = 8;

class ND280BeamBunching: public BeamBunching {

public:
  
  static ND280BeamBunching& Instance(){
    static ND280BeamBunching instance; 
    return instance;
  }
  

private:
  
  ND280BeamBunching();
  
  virtual ~ND280BeamBunching(){}
  
  ND280BeamBunching(ND280BeamBunching const&);
  void operator=(ND280BeamBunching const&); 
  

  
  
};

#endif
