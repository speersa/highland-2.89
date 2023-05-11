#include "HighlandTruthUtils.hxx"
#include "TruthUtils.hxx"


//**************************************************
bool anaUtils::CheckTrueCausesHitFull(const AnaEventB& event, const AnaTrueParticleB& trueTrack, 
    const AnaHit& hit, std::vector<int>& gen)
//**************************************************
{
  gen.resize(hit.TrueG4IDs.size());
  
  bool ok = false;
  
  // Loop over all associted true tracks
  int count = 0;
  for  (std::set<int>::const_iterator it = hit.TrueG4IDs.begin(); it != hit.TrueG4IDs.end(); it++ ){
    
    int gen_tmp = -1;
    
    AnaTrueParticleB* trueCandidate = anaUtils::GetTrueParticleByID(event, *it);
    
    if (trueCandidate){
      if (anaUtils::CheckTrueCausesTrueFull(event, trueTrack, *trueCandidate, gen_tmp)){
        ok = true;
      }
      
    }
    
    gen[count++] = gen_tmp;
  
  } 
  
  return ok;
  
}
