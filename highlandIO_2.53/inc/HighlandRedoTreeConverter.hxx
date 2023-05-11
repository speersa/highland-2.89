/*
 A converter to test the redo tree converter from psycheIO used for BANFF
*/


#ifndef HighlandRedoTreeConverter_h
#define HighlandRedoTreeConverter_h

#include "RedoTreeConverter.hxx"
#include "DataClassesIO.hxx"
#include "P0DDataClasses.hxx"
#include "InputConverter.hxx"
#include <TClonesArray.h>
#include "oaAnalysisReaderProjectHeaders.h"


class HighlandRedoTreeConverter: public RedoTreeConverter{

 public:
  
  HighlandRedoTreeConverter(){};
  virtual ~HighlandRedoTreeConverter(){};

  virtual AnaSpillB*         MakeSpill        () { return new AnaSpill        (); }
  virtual AnaBunchB*         MakeBunch        () { return new AnaBunch        (); }
  virtual AnaBeamB*          MakeBeam         () { return new AnaBeam         (); }
  virtual AnaDataQualityB*   MakeDataQuality  () { return new AnaDataQuality  (); }
  virtual AnaEventInfoB*     MakeEventInfo    () { return new AnaEventInfo    (); }
  virtual AnaTrigger*        MakeTrigger      () { return new AnaTrigger      (); }
  virtual AnaVertexB*        MakeVertex       () { return new AnaVertex       (); }
  virtual AnaTrueParticleB*  MakeTrueParticle () { return new AnaTrueParticle (); }
  virtual AnaTrueVertexB*    MakeTrueVertex   () { return new AnaTrueVertex   (); }
  virtual AnaTrackB*         MakeTrack        () { return new AnaTrack        (); }
  virtual AnaTPCParticleB*   MakeTpcTrack     () { return new AnaTPCParticle  (); }
  virtual AnaTrackerTrackB*  MakeTrackerTrack () { return new AnaTrackerTrack (); }
  virtual AnaFGDParticleB*   MakeFgdTrack     () { return new AnaFGDParticle  (); }
  virtual AnaP0DParticleB*   MakeP0dTrack     () { return new AnaP0DParticle  (); }
  virtual AnaECALParticleB*  MakeEcalTrack    () { return new AnaECALParticle (); }
  virtual AnaSMRDParticleB*  MakeSmrdTrack    () { return new AnaSMRDParticle (); }
  virtual AnaFgdTimeBinB*    MakeFgdTimeBin   () { return new AnaFgdTimeBin   (); }

};

#endif


