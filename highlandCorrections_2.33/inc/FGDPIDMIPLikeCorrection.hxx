#ifndef FGDPIDMIPLikeCorrection_h
#define FGDPIDMIPLikeCorrection_h

#include "CorrectionBase.hxx"

// A simple correction that fills FGD E/X variable that is used in some analyses
class FGDPIDMIPLikeCorrection: public CorrectionBase {
public:

  /// Constructor which accepts as an argument the hypothesis to use when
  /// updating the Momentum and MomentumError members of each track.
  FGDPIDMIPLikeCorrection();

  virtual ~FGDPIDMIPLikeCorrection() {}

  /// Apply the variation to all tracks with TPC info.
  void Apply(AnaSpillC& spill);

};

#endif
