//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Sep  4 09:00:22 2018 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../../../../Files/Prod7/7B_new_iteration/oa_nt_beam_90400000-0000_jrvqx3jehzgh_anal_000_prod6amagnet201011airc-bsdv01_2.root
//////////////////////////////////////////////////////////


#ifndef ND__TBeamSummaryDataModule__TBeamSummaryData_h
#define ND__TBeamSummaryDataModule__TBeamSummaryData_h
namespace ND {
namespace TBeamSummaryDataModule {
class TBeamSummaryData;
} // end of namespace.
} // end of namespace.

#include "TObject.h"
#include <TString.h>
#include "ND__TBeamSummaryDataModule__TBeamSummaryData.h"

namespace ND {
namespace TBeamSummaryDataModule {
class TBeamSummaryData : public TObject {

public:
// Nested classes forward declaration.
class TOtherData;

public:
// Nested classes declaration.
class TOtherData : public TObject {

public:
// Nested classes declaration.

public:
// Data Members.
   Int_t       MidasEvent;    ///< MIDAS Event number in BSD root file. not for nd280analysis.
   Int_t       BeamRunNumber;    ///< Beam Run Number in Neutrino beamline.
   Int_t       SpillNumber;      ///< Spill Number in 32 bit
   Int_t       MRRunNumber;      ///< Main Ring Run Number.
   Int_t       GPSStatus[2];     ///< Status of GPS. [0] = GPS1, [1] = GPS2.
   Int_t       TriggerTime[3];    ///< Trigger Time (Unix Time in sec), [0] = GPS1,[1] = GPS2, [2] = Rb clock system.
   Int_t       TriggerTimeNanoSecond[3];    ///< Trigger Time for sub-second (in nanosec), [0] = GPS1, [1] = GPS2, [2] = Rbclock system.
   Double_t    ProtonsPerSpill[5];          ///< Number of Protons in the SPILL countedby CTs, [0] = CT1,..[4] = CT5.
   Double_t    ProtonsPerBunch[5][9];       ///< Number of Protons in the BUNCHcounted by CTs, [0-4] = CT1-CT5, [0-8]= Whole of bunches, 1st bunch, ... 8thbunch.
   Double_t    BeamTiming[5];               ///< Timing of Proton beam measured by CTs. [0-4]= CT1-CT5. Time 0 is Trigger Time. [micro sec]
   Double_t    BeamBunchTiming[5][9];       ///< Timing of Proton beam BUNCH measuredby CTs. [0-4] = CT1-CT5, [0-8] = Wholeof bunches, 1st bunch, ... 8th bunch.Time 0 is Trigger Time. [micro sec]
   Double_t    BeamFlag[5];                 ///< Flag describing that the Proton Beam isdetected by CTs or not. 1 = extracted, 0 = notextracted.
   Double_t    BeamBunchFlag[5][9];         ///< Flag describing that the Proton Beamis detected by CTs or not in the BUNCH(1st-8th). 1 = extracted, 0 = notextracted.
   Double_t    HornCurrent[3];              ///< Horn Current. [0-3] = Horn1 - Horn3. [kA]
   Double_t    HornBusBarCurrent[3][5];     ///< Horn Current for each busbar.[0..3][] = Horn1..Horn3. [][0..4] =individual ch. [kA]
   Double_t    BeamPositionOnTarget[2];     ///< Beam Position on the target.[0..1] = [x and y]. [mm]
   Double_t    BeamDirectionOnTarget[2];    ///< Beam Direction on the target.[0..1] = [x and y]. [mm]
   Double_t    BeamSizeOnTarget[2];         ///< Beam Size on the target. [0..1] = [xand y]. [mm]
   Double_t    MumonSiTotalQ;               ///< MUMON Total Charge measured by the Si detectors.
   Double_t    MumonSiPeak;                 ///< MUMON Si Peak
   Double_t    MumonSiX;                    ///< Beam X Position on MUMON measured by the Sidetectors. [mm]
   Double_t    MumonSiwX;                   ///< Beam X Width on MUMON measured by the Sidetectors. [mm]
   Double_t    MumonSiY;                    ///< Beam Y Position on MUMON measured by the Sidetectors. [mm]
   Double_t    MumonSiwY;                   ///< Beam Y Width on MUMON measured by the Sidetectors. [mm]
   Double_t    MumonICTotalQ;               ///< MUMON Total Charge measured by theionization chambers.
   Double_t    MumonICPeak;                 ///< MUMON Peak measured by the ionization chambers.
   Double_t    MumonICX;                    ///< Beam X Position on MUMON measured by theionization chambers [mm]
   Double_t    MumonICwX;                   ///< Beam X Width on MUMON measured by the ionizationchambers [mm]
   Double_t    MumonICY;                    ///< Beam Y Position on MUMON measured by theionization chambers [mm]
   Double_t    MumonICwY;                   ///< Beam Y Width on MUMON measured by the ionizationchambers [mm]
   Double_t    OTRLightYield;               ///< Light Yield of OTR
   Double_t    OTRX;                        ///< Beam X Position measured by the OTR. [mm]
   Double_t    OTRwX;                       ///< Beam X Width measured by the OTR. [mm]
   Double_t    OTRY;                        ///< Beam Y Position measured by the OTR. [mm]
   Double_t    OTRwY;                       ///< Beam Y Width measured by the OTR. [mm]
   Double_t    OTRXError;                   ///< Error of OTRX [mm]
   Double_t    OTRwXError;                  ///< Error of OTRwX [mm]
   Double_t    OTRYError;                   ///< Error of OTRY [mm]
   Double_t    OTRwYError;                  ///< Error of OTRwY [mm]
   Int_t       GoodGPSFlag;                 ///< Status Flag of GPSs. 1 = GOOD. 0 = BAD.
   Int_t       TriggerFlag;                 ///< Status Flag of Beam Trrigger. 1 = GOOD. 0 = BAD.
   Int_t       SpillFlag;                   ///< Status Flag of Spill. 1 = GOOD. 0 = BAD.
   Int_t       GoodSpillFlag;               ///< Status Flag of Spill. This Flag contains allinformation above and should be used to defindethe flag is suitable for physics analysis or not.0 = BAD.  Any others starts depending on runconditions.
   Double_t    TargetEfficiency[3];         ///< Efficiency of the Trager.

   TOtherData();
   TOtherData(const TOtherData & );
   virtual ~TOtherData();

   ClassDef(TOtherData,2); // Generated by MakeProject.
};

public:
// Data Members.
   Int_t       BeamRunNumber;    ///< Beam Run Number in neutrino beamline.
   Int_t       SpillNumber;      ///< Spill Number in 32 bit.
   Int_t       GPS1TriggerTime;    ///< GPS1 Trigger Time (Unix Time in sec)
   Int_t       GPS1TriggerTimeNanoSecond;    ///< GPS1 Trigger Time for sub-second (innano sec)
   Double_t    CT5ProtonsPerSpill;           ///< Number of Protons in the SPILL counted byCT5, which is the most downstream chargetransferer. [POT]
   Double_t    CT5ProtonsPerBunch[8];        ///< Number of Protons in the BUNCH(1st-8th) counted by CT5, which is themost downstream charge transferer. [POT]
   Double_t    CT5BeamBunchTiming[8];        ///< Timing of Proton beam BUNCH (1st-8th)measured by CT5, which is the mostdownstream charge transferer. Time 0 isTrigger Time. [micro sec]
   Int_t       CT5BeamBunchFlag[8];          ///< Flag describing that the Proton Beam isdetected by CT5 or not in the BUNCH(1st-8th). 1 = extracted, 0 = not extracted.
   Double_t    OfficialProtonsPerSpill;      ///< Number of Protons in the SPILL forthe official analysis, normally CT5.[POT]
   Double_t    OfficialCTNumber;             ///< Gives the CT used for the POT calculation.Usually CT5.
   Double_t    OfficialProtonsPerBunch[8];    ///< Number of Protons in the BUNCH(1st-8th) counted in the officialanalysis, normally from CT5. [POT]
   Double_t    OfficialBeamBunchTiming[8];    ///< Timing of Proton beam BUNCH(1st-8th) in the official analysis,usually CT5. Time 0 is TriggerTime. [micro sec]
   Int_t       OfficialBeamBunchFlag[8];      ///< Flag describing that the Proton Beamis detected or not in the BUNCH(1st-8th) for the official CT for agiven spill. 1 = extracted, 0 = notextracted.
   Int_t       OfficialBeamFlag;              ///< Flag describing that the Proton Beam isdetected or not for the official CT for a givenspill. 1 = extracted, 0 = not extracted.
   Double_t    Horn1CurrentSum;               ///< Horn1 Current. [kA]
   Double_t    Horn2CurrentSum;               ///< Horn2 Current. [kA]
   Double_t    Horn3CurrentSum;               ///< Horn3 Current. [kA]
   Int_t       GoodSpillFlag;                 ///< Good Spill Flag. Values >=1 = Good Spill, with 1being at 250 kA, 2 at 200 kA, 100 at 0 kA, etc..Suitable for analysis., 0 = Bad Spill. Improper forphysics analysis., Flag == 99 is applied forHorn-off run in early Run 3 (early 2012) (need tocheck if this is still valid).
   TString     BSDVersion;                    ///< BSD version information. Currently "v01" is thenewest.
   ND::TBeamSummaryDataModule::TBeamSummaryData::TOtherData OtherData;                     //

   TBeamSummaryData();
   TBeamSummaryData(const TBeamSummaryData & );
   virtual ~TBeamSummaryData();

   ClassDef(TBeamSummaryData,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
