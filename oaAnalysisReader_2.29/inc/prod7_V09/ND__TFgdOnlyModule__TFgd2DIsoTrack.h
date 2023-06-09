//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:09:41 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710119-0055_df7igapcoooo_anal_000_nu-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TFgdOnlyModule__TFgd2DIsoTrack_h
#define ND__TFgdOnlyModule__TFgd2DIsoTrack_h
namespace ND {
namespace TFgdOnlyModule {
class TFgd2DIsoTrack;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include "Riostream.h"
#include <string>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <vector>

namespace ND {
namespace TFgdOnlyModule {
class TFgd2DIsoTrack : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   string      AlgorithmName;    //
   int         NHits;            //
   double      Angle;            //
   double      SumCharge;        //
   double      Range;            //
   TLorentzVector Origin;           //
   TLorentzVector OriginVariance;    //
   TVector3       Direction;         //
   vector<TVector3*> HitPositions;      //
   int               TrajId;            //
   double            Completeness;      //
   double            Cleanliness;       //

   TFgd2DIsoTrack();
   TFgd2DIsoTrack(const TFgd2DIsoTrack & );
   virtual ~TFgd2DIsoTrack();

   ClassDef(TFgd2DIsoTrack,3); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
