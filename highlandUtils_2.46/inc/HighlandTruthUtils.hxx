#ifndef HighlandTruthUtils_h
#define HighlandTruthUtils_h

#include "DataClasses.hxx"

/// This namespace contains useful functions for analyses. Functions include
/// those related to fiducial volumes, accessing tracks with specific
/// characteristics, and more.
namespace anaUtils{

    /// Check whether a true object has a relation to second true one, 
    /// The corresponding generation (0 is direct contributor) will be returned
    /// as well
    bool CheckTrueCausesHitFull(const AnaEventB& event, const AnaTrueParticleB& trueTrack, 
        const AnaHit& hit, std::vector<int>& gen);
  
}

  
#endif
