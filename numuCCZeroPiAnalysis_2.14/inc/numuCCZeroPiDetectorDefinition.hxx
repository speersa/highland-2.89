#ifndef numuCCZeroPiDetectorDefinition_h
#define numuCCZeroPiDetectorDefinition_h

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <typeinfo>
#include "TVector3.h"

namespace numuCCZeroPiDetDef{

  /// ----- Reduced Detector volume definitions ---

  /// reduced FGD1 FV 
  const   Float_t FVdefminFGD1[3] = {57.66, 57.66, 0};
  const   Float_t FVdefmaxFGD1[3] = {57.66, 57.66, 0};

  /// reduced FGD2 FV 
  const   Float_t FVdefminFGD2[3] = {57.66, 57.66, 0};
  const   Float_t FVdefmaxFGD2[3] = {57.66, 57.66, 0};

  //BarrelECal FV for stopping point cut 
  const   Float_t FVdefminTECALLeft[3]    = {0.0,   40.0,   40.0};
  const   Float_t FVdefmaxTECALLeft[3]    = {10.0,  40.0,   40.0};

  const   Float_t FVdefminTECALRight[3]   = {10,    40.0,   40.0};
  const   Float_t FVdefmaxTECALRight[3]   = {0.0,   40.0,   40.0};

  const   Float_t FVdefminTECALTop[3]     = {40.0,  0.0,    40.0};
  const   Float_t FVdefmaxTECALTop[3]     = {40.0,  10.0,   40.0};

  const   Float_t FVdefminTECALBottom[3]  = {40.0,  10.0,   40.0};
  const   Float_t FVdefmaxTECALBottom[3]  = {40.0,  0.0,    40.0};

  //SMRD FV for stopping point cut 
  const   Float_t FVdefminSMRDLeft[3]     = {0.0,   0.0,    125.0};
  const   Float_t FVdefmaxSMRDLeft[3]     = {60.0,  0.0,    125.0};

  const   Float_t FVdefminSMRDRight[3]    = {60.0,  0.0,    125.0};
  const   Float_t FVdefmaxSMRDRight[3]    = {0.0,   0.0,    125.0};

  const   Float_t FVdefminSMRDTop[3]      = {0.0,   0.0,    125.0};
  const   Float_t FVdefmaxSMRDTop[3]      = {0.0,   60.0,   125.0};

  const   Float_t FVdefminSMRDBottom[3]   = {0.0,   60.0,   125.0};
  const   Float_t FVdefmaxSMRDBottom[3]   = {0.0,   0.0,    125.0};

}
#endif
