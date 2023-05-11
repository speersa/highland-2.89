#ifndef SelTopoId_hxx
#define SelTopoId_hxx

#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>

/// Topo sample - whether e.g.  a pion/proton particle is reconstructed in TPC/FGD or even ME activity

namespace SelTopoId{

  enum SelTopoPionEnum{
    kPionUnassigned,
    // Pion in TPC
    kTPCPion,
    // FGD contained
    kFGDPion, 
    // Identified by ME
    kMEPion
  };
  
  
  enum SelTopoProtonEnum{
    kProtonUnassigned,
    // Proton in TPC
    kTPCProton,
    // FGD contained
    kFGDProton, 
    kTPCAndFgdProtons
  };


};

#endif

