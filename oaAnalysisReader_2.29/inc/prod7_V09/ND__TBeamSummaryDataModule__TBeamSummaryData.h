//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Wed Jan 11 14:09:41 2023 by ROOT version 5.34/34)
//      from the StreamerInfo in file ../../oa_nt_beam_80710119-0055_df7igapcoooo_anal_000_nu-bsdv01_2.root
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
   int         MidasEvent;    //MIDAS Event number in BSD root file. not for nd280analysis.
   int         BeamRunNumber;    //Beam Run Number in Neutrino beamline.
   int         SpillNumber;      //Spill Number in 32 bit
   int         MRRunNumber;      //Main Ring Run Number.
   int         GPSStatus[2];     //Status of GPS. [0] = GPS1, [1] = GPS2.
   int         TriggerTime[3];    //Trigger Time (Unix Time in sec), [0] = GPS1,[1] = GPS2, [2] = Rb clock system.
   int         TriggerTimeNanoSecond[3];    //Trigger Time for sub-second (in nanosec), [0] = GPS1, [1] = GPS2, [2] = Rbclock system.
   double      ProtonsPerSpill[5];          //Number of Protons in the SPILL countedby CTs, [0] = CT1,..[4] = CT5.
   double      ProtonsPerBunch[5][9];       //Number of Protons in the BUNCHcounted by CTs, [0-4] = CT1-CT5, [0-8]= Whole of bunches, 1st bunch, ... 8thbunch.
   double      BeamTiming[5];               //Timing of Proton beam measured by CTs. [0-4]= CT1-CT5. Time 0 is Trigger Time. [micro sec]
   double      BeamBunchTiming[5][9];       //Timing of Proton beam BUNCH measuredby CTs. [0-4] = CT1-CT5, [0-8] = Wholeof bunches, 1st bunch, ... 8th bunch.Time 0 is Trigger Time. [micro sec]
   double      BeamFlag[5];                 //Flag describing that the Proton Beam isdetected by CTs or not. 1 = extracted, 0 = notextracted.
   double      BeamBunchFlag[5][9];         //Flag describing that the Proton Beamis detected by CTs or not in the BUNCH(1st-8th). 1 = extracted, 0 = notextracted.
   double      HornCurrent[3];              //Horn Current. [0-3] = Horn1 - Horn3. [kA]
   double      HornBusBarCurrent[3][5];     //Horn Current for each busbar.[0..3][] = Horn1..Horn3. [][0..4] =individual ch. [kA]
   double      BeamPositionOnTarget[2];     //Beam Position on the target.[0..1] = [x and y]. [mm]
   double      BeamDirectionOnTarget[2];    //Beam Direction on the target.[0..1] = [x and y]. [mm]
   double      BeamSizeOnTarget[2];         //Beam Size on the target. [0..1] = [xand y]. [mm]
   double      MumonSiTotalQ;               //MUMON Total Charge measured by the Si detectors.
   double      MumonSiPeak;                 //MUMON Si Peak
   double      MumonSiX;                    //Beam X Position on MUMON measured by the Sidetectors. [mm]
   double      MumonSiwX;                   //Beam X Width on MUMON measured by the Sidetectors. [mm]
   double      MumonSiY;                    //Beam Y Position on MUMON measured by the Sidetectors. [mm]
   double      MumonSiwY;                   //Beam Y Width on MUMON measured by the Sidetectors. [mm]
   double      MumonICTotalQ;               //MUMON Total Charge measured by the ionization chambers.
   double      MumonICPeak;                 //MUMON Peak measured by the ionization chambers.
   double      MumonICX;                    //Beam X Position on MUMON measured by thei onization chambers [mm]
   double      MumonICwX;                   //Beam X Width on MUMON measured by the ionizationchambers [mm]
   double      MumonICY;                    //Beam Y Position on MUMON measured by   chambers [mm]
   double      MumonICwY;                   //Beam Y Width on MUMON measured by the ionization chambers [mm]
   double      OTRLightYield;               //Light Yield of OTR
   double      OTRX;                        //Beam X Position measured by the OTR. [mm]
   double      OTRwX;                       //Beam X Width measured by the OTR. [mm]
   double      OTRY;                        //Beam Y Position measured by the OTR. [mm]
   double      OTRwY;                       //Beam Y Width measured by the OTR. [mm]
   double      OTRXError;                   //Error of OTRX [mm]
   double      OTRwXError;                  //Error of OTRwX [mm]
   double      OTRYError;                   //Error of OTRY [mm]
   double      OTRwYError;                  //Error of OTRwY [mm]
   int         GoodGPSFlag;                 //Status Flag of GPSs. 1 = GOOD. 0 = BAD.
   int         TriggerFlag;                 //Status Flag of Beam Trrigger. 1 = GOOD. 0 = BAD.
   int         SpillFlag;                   //Status Flag of Spill. 1 = GOOD. 0 = BAD.
   int         GoodSpillFlag;               //Status Flag of Spill. This Flag contains all information in GoodGPSFlag TriggerFlag and SpillFlag. It should be used to define if the spill is suitable for physics analysis or not. 0 = BAD.  Any others starts depending on runconditions.
   double      TargetEfficiency[3];         //Efficiency of the Trager.

   TOtherData();
   TOtherData(const TOtherData & );
   virtual ~TOtherData();

   ClassDef(TOtherData,2); // Generated by MakeProject.
};

public:
// Data Members.
   int         BeamRunNumber;    //Beam Run Number in neutrino beamline.
   int         SpillNumber;      //Spill Number in 32 bit.
   int         GPS1TriggerTime;    //GPS1 Trigger Time (Unix Time in sec)
   int         GPS1TriggerTimeNanoSecond;    //GPS1 Trigger Time for sub-second (innano sec)
   double      CT5ProtonsPerSpill;           //Number of Protons in the SPILL counted byCT5, which is the most downstream chargetransferer. [POT]
   double      CT5ProtonsPerBunch[8];        //Number of Protons in the BUNCH(1st-8th) counted by CT5, which is themost downstream charge transferer. [POT]
   double      CT5BeamBunchTiming[8];        //Timing of Proton beam BUNCH (1st-8th)measured by CT5, which is the mostdownstream charge transferer. Time 0 isTrigger Time. [micro sec]
   int         CT5BeamBunchFlag[8];          //Flag describing that the Proton Beam isdetected by CT5 or not in the BUNCH(1st-8th). 1 = extracted, 0 = not extracted.
   double      OfficialProtonsPerSpill;      //Number of Protons in the SPILL forthe official analysis, normally CT5.[POT]
   double      OfficialCTNumber;             //Gives the CT used for the POT calculation.Usually CT5.
   double      OfficialProtonsPerBunch[8];    //Number of Protons in the BUNCH(1st-8th) counted in the officialanalysis, normally from CT5. [POT]
   double      OfficialBeamBunchTiming[8];    //Timing of Proton beam BUNCH(1st-8th) in the official analysis,usually CT5. Time 0 is TriggerTime. [micro sec]
   int         OfficialBeamBunchFlag[8];      //Flag describing that the Proton Beamis detected or not in the BUNCH(1st-8th) for the official CT for agiven spill. 1 = extracted, 0 = notextracted.
   int         OfficialBeamFlag;              //Flag describing that the Proton Beam isdetected or not for the official CT for a givenspill. 1 = extracted, 0 = not extracted.
   double      Horn1CurrentSum;               //Horn1 Current. [kA]
   double      Horn2CurrentSum;               //Horn2 Current. [kA]
   double      Horn3CurrentSum;               //Horn3 Current. [kA]
   int         GoodSpillFlag;                 //Good Spill Flag. Values >=1 = Good Spill, with 1being at 250 kA, 2 at 200 kA, 100 at 0 kA, etc..Suitable for analysis., 0 = Bad Spill. Improper forphysics analysis., Flag == 99 is applied forHorn-off run in early Run 3 (early 2012) (need tocheck if this is still valid).
   TString     BSDVersion;                    //BSD version information. Currently "v01" is thenewest.
   ND::TBeamSummaryDataModule::TBeamSummaryData::TOtherData OtherData;                     //

   TBeamSummaryData();
   TBeamSummaryData(const TBeamSummaryData & );
   virtual ~TBeamSummaryData();

   ClassDef(TBeamSummaryData,2); // Generated by MakeProject.
};
} // namespace
} // namespace
#endif
