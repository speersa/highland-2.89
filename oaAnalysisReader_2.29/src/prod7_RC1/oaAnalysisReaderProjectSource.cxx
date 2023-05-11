#include "oaAnalysisReaderProjectHeaders.h"

#include "oaAnalysisReaderLinkDef.h"

#include "oaAnalysisReaderProjectDict.cxx"

struct DeleteObjectFunctor {
   template <typename T>
   void operator()(const T *ptr) const {
      delete ptr;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q> &) const {
      // Do nothing
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q*> &ptr) const {
      delete ptr.second;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q> &ptr) const {
      delete ptr.first;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q*> &ptr) const {
      delete ptr.first;
      delete ptr.second;
   }
};

#ifndef ND__TND280Event__Header_cxx
#define ND__TND280Event__Header_cxx
ND::TND280Event::Header::Header() {
}
ND::TND280Event::Header::Header(const Header & rhs)
   : fRecordType(const_cast<Header &>( rhs ).fRecordType)
   , fTimeStamp(const_cast<Header &>( rhs ).fTimeStamp)
   , fRunType(const_cast<Header &>( rhs ).fRunType)
   , fErrorCode(const_cast<Header &>( rhs ).fErrorCode)
   , fTriggerWord(const_cast<Header &>( rhs ).fTriggerWord)
   , fMCMSecond(const_cast<Header &>( rhs ).fMCMSecond)
   , fMCMSubSecond(const_cast<Header &>( rhs ).fMCMSubSecond)
   , fMCMTimeSinceBusy(const_cast<Header &>( rhs ).fMCMTimeSinceBusy)
   , fP0DSecond(const_cast<Header &>( rhs ).fP0DSecond)
   , fP0DSubSecond(const_cast<Header &>( rhs ).fP0DSubSecond)
   , fP0DTimeSinceBusy(const_cast<Header &>( rhs ).fP0DTimeSinceBusy)
   , fTPCSecond(const_cast<Header &>( rhs ).fTPCSecond)
   , fTPCSubSecond(const_cast<Header &>( rhs ).fTPCSubSecond)
   , fTPCTimeSinceBusy(const_cast<Header &>( rhs ).fTPCTimeSinceBusy)
   , fFGDSecond(const_cast<Header &>( rhs ).fFGDSecond)
   , fFGDSubSecond(const_cast<Header &>( rhs ).fFGDSubSecond)
   , fFGDTimeSinceBusy(const_cast<Header &>( rhs ).fFGDTimeSinceBusy)
   , fECalSecond(const_cast<Header &>( rhs ).fECalSecond)
   , fECalSubSecond(const_cast<Header &>( rhs ).fECalSubSecond)
   , fECalTimeSinceBusy(const_cast<Header &>( rhs ).fECalTimeSinceBusy)
   , fSMRDSecond(const_cast<Header &>( rhs ).fSMRDSecond)
   , fSMRDSubSecond(const_cast<Header &>( rhs ).fSMRDSubSecond)
   , fSMRDTimeSinceBusy(const_cast<Header &>( rhs ).fSMRDTimeSinceBusy)
   , fINGRIDSecond(const_cast<Header &>( rhs ).fINGRIDSecond)
   , fINGRIDSubSecond(const_cast<Header &>( rhs ).fINGRIDSubSecond)
   , fINGRIDTimeSinceBusy(const_cast<Header &>( rhs ).fINGRIDTimeSinceBusy)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<3;i++) fCTMTriggerPattern[i] = rhs.fCTMTriggerPattern[i];
   for (Int_t i=0;i<3;i++) fFGDCTMTriggerPattern[i] = rhs.fFGDCTMTriggerPattern[i];
}
ND::TND280Event::Header::~Header() {
}
#endif // ND__TND280Event__Header_cxx

#ifndef ND__TND280Event_cxx
#define ND__TND280Event_cxx
ND::TND280Event::TND280Event() {
}
ND::TND280Event::TND280Event(const TND280Event & rhs)
   : ND::TDataVector(const_cast<TND280Event &>( rhs ))
   , fContext(const_cast<TND280Event &>( rhs ).fContext)
   , fGeometryHash(const_cast<TND280Event &>( rhs ).fGeometryHash)
   , fAlignmentId(const_cast<TND280Event &>( rhs ).fAlignmentId)
   , fHeader(const_cast<TND280Event &>( rhs ).fHeader)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TND280Event::~TND280Event() {
}
#endif // ND__TND280Event_cxx

#ifndef ND__TDataVector_cxx
#define ND__TDataVector_cxx
ND::TDataVector::TDataVector() {
}
ND::TDataVector::TDataVector(const TDataVector & rhs)
   : ND::TData(const_cast<TDataVector &>( rhs ))
   , fVector(const_cast<TDataVector &>( rhs ).fVector)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TDataVector &modrhs = const_cast<TDataVector &>( rhs );
   modrhs.fVector.clear();
}
ND::TDataVector::~TDataVector() {
}
#endif // ND__TDataVector_cxx

#ifndef ND__TData_cxx
#define ND__TData_cxx
ND::TData::TData() {
}
ND::TData::TData(const TData & rhs)
   : ND::TDatum(const_cast<TData &>( rhs ))
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TData::~TData() {
}
#endif // ND__TData_cxx

#ifndef ND__TDatum_cxx
#define ND__TDatum_cxx
ND::TDatum::TDatum() {
   fParent = 0;
}
ND::TDatum::TDatum(const TDatum & rhs)
   : TNamed(const_cast<TDatum &>( rhs ))
   , fParent(const_cast<TDatum &>( rhs ).fParent)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TDatum &modrhs = const_cast<TDatum &>( rhs );
   modrhs.fParent = 0;
}
ND::TDatum::~TDatum() {
   delete fParent;   fParent = 0;
}
#endif // ND__TDatum_cxx

#ifndef ND__TND280Context_cxx
#define ND__TND280Context_cxx
ND::TND280Context::TND280Context() {
}
ND::TND280Context::TND280Context(const TND280Context & rhs)
   : fPartition(const_cast<TND280Context &>( rhs ).fPartition)
   , fRun(const_cast<TND280Context &>( rhs ).fRun)
   , fSubRun(const_cast<TND280Context &>( rhs ).fSubRun)
   , fEvent(const_cast<TND280Context &>( rhs ).fEvent)
   , fSpill(const_cast<TND280Context &>( rhs ).fSpill)
   , fTimeStamp(const_cast<TND280Context &>( rhs ).fTimeStamp)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TND280Context::~TND280Context() {
}
#endif // ND__TND280Context_cxx

#ifndef ND__TSHAHashValue_cxx
#define ND__TSHAHashValue_cxx
ND::TSHAHashValue::TSHAHashValue() {
}
ND::TSHAHashValue::TSHAHashValue(const TSHAHashValue & rhs)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<5;i++) fHash[i] = rhs.fHash[i];
}
ND::TSHAHashValue::~TSHAHashValue() {
}
#endif // ND__TSHAHashValue_cxx

#ifndef ND__TAlignmentId_cxx
#define ND__TAlignmentId_cxx
ND::TAlignmentId::TAlignmentId() {
}
ND::TAlignmentId::TAlignmentId(const TAlignmentId & rhs)
   : ND::TSHAHashValue(const_cast<TAlignmentId &>( rhs ))
   , fDocString(const_cast<TAlignmentId &>( rhs ).fDocString)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TAlignmentId &modrhs = const_cast<TAlignmentId &>( rhs );
   modrhs.fDocString.clear();
}
ND::TAlignmentId::~TAlignmentId() {
}
#endif // ND__TAlignmentId_cxx

#ifndef ND__NRooTrackerVtx_cxx
#define ND__NRooTrackerVtx_cxx
ND::NRooTrackerVtx::NRooTrackerVtx() {
   EvtCode = 0;
   StdHepPdg = 0;
   StdHepStatus = 0;
   StdHepFd = 0;
   StdHepLd = 0;
   StdHepFm = 0;
   StdHepLm = 0;
   NEipvc = 0;
   NEiorgvc = 0;
   NEiflgvc = 0;
   NEicrnvc = 0;
   NEiflgvert = 0;
   NEabspvert = 0;
   NEabstpvert = 0;
   NEipvert = 0;
   NEiverti = 0;
   NEivertf = 0;
   NFiflag = 0;
   NFx = 0;
   NFy = 0;
   NFz = 0;
   NFpx = 0;
   NFpy = 0;
   NFpz = 0;
   NFe = 0;
   NFfirststep = 0;
   NFecms2 = 0;
   GeomPath = 0;
   GeneratorName = 0;
   OrigFileName = 0;
   OrigTreeName = 0;
}
ND::NRooTrackerVtx::NRooTrackerVtx(const NRooTrackerVtx & rhs)
   : ND::JNuBeamFlux(const_cast<NRooTrackerVtx &>( rhs ))
   , EvtCode(const_cast<NRooTrackerVtx &>( rhs ).EvtCode)
   , EvtNum(const_cast<NRooTrackerVtx &>( rhs ).EvtNum)
   , EvtXSec(const_cast<NRooTrackerVtx &>( rhs ).EvtXSec)
   , EvtDXSec(const_cast<NRooTrackerVtx &>( rhs ).EvtDXSec)
   , EvtWght(const_cast<NRooTrackerVtx &>( rhs ).EvtWght)
   , EvtProb(const_cast<NRooTrackerVtx &>( rhs ).EvtProb)
   , StdHepN(const_cast<NRooTrackerVtx &>( rhs ).StdHepN)
   , StdHepPdg(const_cast<NRooTrackerVtx &>( rhs ).StdHepPdg)
   , StdHepStatus(const_cast<NRooTrackerVtx &>( rhs ).StdHepStatus)
   , StdHepFd(const_cast<NRooTrackerVtx &>( rhs ).StdHepFd)
   , StdHepLd(const_cast<NRooTrackerVtx &>( rhs ).StdHepLd)
   , StdHepFm(const_cast<NRooTrackerVtx &>( rhs ).StdHepFm)
   , StdHepLm(const_cast<NRooTrackerVtx &>( rhs ).StdHepLm)
   , NEnvc(const_cast<NRooTrackerVtx &>( rhs ).NEnvc)
   , NEipvc(const_cast<NRooTrackerVtx &>( rhs ).NEipvc)
   , NEiorgvc(const_cast<NRooTrackerVtx &>( rhs ).NEiorgvc)
   , NEiflgvc(const_cast<NRooTrackerVtx &>( rhs ).NEiflgvc)
   , NEicrnvc(const_cast<NRooTrackerVtx &>( rhs ).NEicrnvc)
   , NEcrsx(const_cast<NRooTrackerVtx &>( rhs ).NEcrsx)
   , NEcrsy(const_cast<NRooTrackerVtx &>( rhs ).NEcrsy)
   , NEcrsz(const_cast<NRooTrackerVtx &>( rhs ).NEcrsz)
   , NEcrsphi(const_cast<NRooTrackerVtx &>( rhs ).NEcrsphi)
   , NEnvert(const_cast<NRooTrackerVtx &>( rhs ).NEnvert)
   , NEiflgvert(const_cast<NRooTrackerVtx &>( rhs ).NEiflgvert)
   , NEnvcvert(const_cast<NRooTrackerVtx &>( rhs ).NEnvcvert)
   , NEabspvert(const_cast<NRooTrackerVtx &>( rhs ).NEabspvert)
   , NEabstpvert(const_cast<NRooTrackerVtx &>( rhs ).NEabstpvert)
   , NEipvert(const_cast<NRooTrackerVtx &>( rhs ).NEipvert)
   , NEiverti(const_cast<NRooTrackerVtx &>( rhs ).NEiverti)
   , NEivertf(const_cast<NRooTrackerVtx &>( rhs ).NEivertf)
   , NFnvert(const_cast<NRooTrackerVtx &>( rhs ).NFnvert)
   , NFiflag(const_cast<NRooTrackerVtx &>( rhs ).NFiflag)
   , NFx(const_cast<NRooTrackerVtx &>( rhs ).NFx)
   , NFy(const_cast<NRooTrackerVtx &>( rhs ).NFy)
   , NFz(const_cast<NRooTrackerVtx &>( rhs ).NFz)
   , NFpx(const_cast<NRooTrackerVtx &>( rhs ).NFpx)
   , NFpy(const_cast<NRooTrackerVtx &>( rhs ).NFpy)
   , NFpz(const_cast<NRooTrackerVtx &>( rhs ).NFpz)
   , NFe(const_cast<NRooTrackerVtx &>( rhs ).NFe)
   , NFfirststep(const_cast<NRooTrackerVtx &>( rhs ).NFfirststep)
   , NFnstep(const_cast<NRooTrackerVtx &>( rhs ).NFnstep)
   , NFecms2(const_cast<NRooTrackerVtx &>( rhs ).NFecms2)
   , GeomPath(const_cast<NRooTrackerVtx &>( rhs ).GeomPath)
   , GeneratorName(const_cast<NRooTrackerVtx &>( rhs ).GeneratorName)
   , OrigFileName(const_cast<NRooTrackerVtx &>( rhs ).OrigFileName)
   , OrigTreeName(const_cast<NRooTrackerVtx &>( rhs ).OrigTreeName)
   , OrigEvtNum(const_cast<NRooTrackerVtx &>( rhs ).OrigEvtNum)
   , OrigTreeEntries(const_cast<NRooTrackerVtx &>( rhs ).OrigTreeEntries)
   , OrigTreePOT(const_cast<NRooTrackerVtx &>( rhs ).OrigTreePOT)
   , TimeInSpill(const_cast<NRooTrackerVtx &>( rhs ).TimeInSpill)
   , TruthVertexID(const_cast<NRooTrackerVtx &>( rhs ).TruthVertexID)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   NRooTrackerVtx &modrhs = const_cast<NRooTrackerVtx &>( rhs );
   modrhs.EvtCode = 0;
   for (Int_t i=0;i<4;i++) EvtVtx[i] = rhs.EvtVtx[i];
   modrhs.StdHepPdg = 0;
   modrhs.StdHepStatus = 0;
   for (Int_t i=0;i<400;i++) (&(StdHepX4[0][0]))[i] = (&(rhs.StdHepX4[0][0]))[i];
   for (Int_t i=0;i<400;i++) (&(StdHepP4[0][0]))[i] = (&(rhs.StdHepP4[0][0]))[i];
   for (Int_t i=0;i<300;i++) (&(StdHepPolz[0][0]))[i] = (&(rhs.StdHepPolz[0][0]))[i];
   modrhs.StdHepFd = 0;
   modrhs.StdHepLd = 0;
   modrhs.StdHepFm = 0;
   modrhs.StdHepLm = 0;
   modrhs.NEipvc = 0;
   for (Int_t i=0;i<300;i++) (&(NEpvc[0][0]))[i] = (&(rhs.NEpvc[0][0]))[i];
   modrhs.NEiorgvc = 0;
   modrhs.NEiflgvc = 0;
   modrhs.NEicrnvc = 0;
   for (Int_t i=0;i<300;i++) (&(NEposvert[0][0]))[i] = (&(rhs.NEposvert[0][0]))[i];
   modrhs.NEiflgvert = 0;
   for (Int_t i=0;i<900;i++) (&(NEdirvert[0][0]))[i] = (&(rhs.NEdirvert[0][0]))[i];
   modrhs.NEabspvert = 0;
   modrhs.NEabstpvert = 0;
   modrhs.NEipvert = 0;
   modrhs.NEiverti = 0;
   modrhs.NEivertf = 0;
   modrhs.NFiflag = 0;
   modrhs.NFx = 0;
   modrhs.NFy = 0;
   modrhs.NFz = 0;
   modrhs.NFpx = 0;
   modrhs.NFpy = 0;
   modrhs.NFpz = 0;
   modrhs.NFe = 0;
   modrhs.NFfirststep = 0;
   modrhs.NFecms2 = 0;
   modrhs.GeomPath = 0;
   modrhs.GeneratorName = 0;
   modrhs.OrigFileName = 0;
   modrhs.OrigTreeName = 0;
}
ND::NRooTrackerVtx::~NRooTrackerVtx() {
   delete EvtCode;   EvtCode = 0;
   delete [] StdHepPdg;   StdHepPdg = 0;
   delete [] StdHepStatus;   StdHepStatus = 0;
   delete [] StdHepFd;   StdHepFd = 0;
   delete [] StdHepLd;   StdHepLd = 0;
   delete [] StdHepFm;   StdHepFm = 0;
   delete [] StdHepLm;   StdHepLm = 0;
   delete [] NEipvc;   NEipvc = 0;
   delete [] NEiorgvc;   NEiorgvc = 0;
   delete [] NEiflgvc;   NEiflgvc = 0;
   delete [] NEicrnvc;   NEicrnvc = 0;
   delete [] NEiflgvert;   NEiflgvert = 0;
   delete [] NEabspvert;   NEabspvert = 0;
   delete [] NEabstpvert;   NEabstpvert = 0;
   delete [] NEipvert;   NEipvert = 0;
   delete [] NEiverti;   NEiverti = 0;
   delete [] NEivertf;   NEivertf = 0;
   delete [] NFiflag;   NFiflag = 0;
   delete [] NFx;   NFx = 0;
   delete [] NFy;   NFy = 0;
   delete [] NFz;   NFz = 0;
   delete [] NFpx;   NFpx = 0;
   delete [] NFpy;   NFpy = 0;
   delete [] NFpz;   NFpz = 0;
   delete [] NFe;   NFe = 0;
   delete [] NFfirststep;   NFfirststep = 0;
   delete [] NFecms2;   NFecms2 = 0;
   delete GeomPath;   GeomPath = 0;
   delete GeneratorName;   GeneratorName = 0;
   delete OrigFileName;   OrigFileName = 0;
   delete OrigTreeName;   OrigTreeName = 0;
}
#endif // ND__NRooTrackerVtx_cxx

#ifndef ND__JNuBeamFlux_cxx
#define ND__JNuBeamFlux_cxx
ND::JNuBeamFlux::JNuBeamFlux() {
   NuFileName = 0;
}
ND::JNuBeamFlux::JNuBeamFlux(const JNuBeamFlux & rhs)
   : ND::RooTrackerVtxBase(const_cast<JNuBeamFlux &>( rhs ))
   , NuFluxEntry(const_cast<JNuBeamFlux &>( rhs ).NuFluxEntry)
   , NuFileName(const_cast<JNuBeamFlux &>( rhs ).NuFileName)
   , NuParentPdg(const_cast<JNuBeamFlux &>( rhs ).NuParentPdg)
   , NuParentDecMode(const_cast<JNuBeamFlux &>( rhs ).NuParentDecMode)
   , NuCospibm(const_cast<JNuBeamFlux &>( rhs ).NuCospibm)
   , NuNorm(const_cast<JNuBeamFlux &>( rhs ).NuNorm)
   , NuCospi0bm(const_cast<JNuBeamFlux &>( rhs ).NuCospi0bm)
   , NuRnu(const_cast<JNuBeamFlux &>( rhs ).NuRnu)
   , NuIdfd(const_cast<JNuBeamFlux &>( rhs ).NuIdfd)
   , NuGipart(const_cast<JNuBeamFlux &>( rhs ).NuGipart)
   , NuGamom0(const_cast<JNuBeamFlux &>( rhs ).NuGamom0)
   , NuNg(const_cast<JNuBeamFlux &>( rhs ).NuNg)
   , NuEnusk(const_cast<JNuBeamFlux &>( rhs ).NuEnusk)
   , NuNormsk(const_cast<JNuBeamFlux &>( rhs ).NuNormsk)
   , NuAnorm(const_cast<JNuBeamFlux &>( rhs ).NuAnorm)
   , NuVersion(const_cast<JNuBeamFlux &>( rhs ).NuVersion)
   , NuTuneid(const_cast<JNuBeamFlux &>( rhs ).NuTuneid)
   , NuNtrig(const_cast<JNuBeamFlux &>( rhs ).NuNtrig)
   , NuPint(const_cast<JNuBeamFlux &>( rhs ).NuPint)
   , NuRand(const_cast<JNuBeamFlux &>( rhs ).NuRand)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   JNuBeamFlux &modrhs = const_cast<JNuBeamFlux &>( rhs );
   modrhs.NuFileName = 0;
   for (Int_t i=0;i<4;i++) NuParentDecP4[i] = rhs.NuParentDecP4[i];
   for (Int_t i=0;i<4;i++) NuParentDecX4[i] = rhs.NuParentDecX4[i];
   for (Int_t i=0;i<4;i++) NuParentProP4[i] = rhs.NuParentProP4[i];
   for (Int_t i=0;i<4;i++) NuParentProX4[i] = rhs.NuParentProX4[i];
   for (Int_t i=0;i<2;i++) NuXnu[i] = rhs.NuXnu[i];
   for (Int_t i=0;i<3;i++) NuGpos0[i] = rhs.NuGpos0[i];
   for (Int_t i=0;i<3;i++) NuGvec0[i] = rhs.NuGvec0[i];
   for (Int_t i=0;i<36;i++) (&(NuGp[0][0]))[i] = (&(rhs.NuGp[0][0]))[i];
   for (Int_t i=0;i<12;i++) NuGcosbm[i] = rhs.NuGcosbm[i];
   for (Int_t i=0;i<36;i++) (&(NuGv[0][0]))[i] = (&(rhs.NuGv[0][0]))[i];
   for (Int_t i=0;i<12;i++) NuGpid[i] = rhs.NuGpid[i];
   for (Int_t i=0;i<12;i++) NuGmec[i] = rhs.NuGmec[i];
   for (Int_t i=0;i<12;i++) NuGmat[i] = rhs.NuGmat[i];
   for (Int_t i=0;i<12;i++) NuGdistc[i] = rhs.NuGdistc[i];
   for (Int_t i=0;i<12;i++) NuGdistal[i] = rhs.NuGdistal[i];
   for (Int_t i=0;i<12;i++) NuGdistti[i] = rhs.NuGdistti[i];
   for (Int_t i=0;i<12;i++) NuGdistfe[i] = rhs.NuGdistfe[i];
   for (Int_t i=0;i<2;i++) NuBpos[i] = rhs.NuBpos[i];
   for (Int_t i=0;i<2;i++) NuBtilt[i] = rhs.NuBtilt[i];
   for (Int_t i=0;i<2;i++) NuBrms[i] = rhs.NuBrms[i];
   for (Int_t i=0;i<2;i++) NuEmit[i] = rhs.NuEmit[i];
   for (Int_t i=0;i<2;i++) NuAlpha[i] = rhs.NuAlpha[i];
   for (Int_t i=0;i<3;i++) NuHcur[i] = rhs.NuHcur[i];
}
ND::JNuBeamFlux::~JNuBeamFlux() {
   delete NuFileName;   NuFileName = 0;
}
#endif // ND__JNuBeamFlux_cxx

#ifndef ND__RooTrackerVtxBase_cxx
#define ND__RooTrackerVtxBase_cxx
ND::RooTrackerVtxBase::RooTrackerVtxBase() {
}
ND::RooTrackerVtxBase::RooTrackerVtxBase(const RooTrackerVtxBase & rhs)
   : TObject(const_cast<RooTrackerVtxBase &>( rhs ))
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::RooTrackerVtxBase::~RooTrackerVtxBase() {
}
#endif // ND__RooTrackerVtxBase_cxx

#ifndef ND__GRooTrackerVtx_cxx
#define ND__GRooTrackerVtx_cxx
ND::GRooTrackerVtx::GRooTrackerVtx() {
   EvtCode = 0;
   StdHepPdg = 0;
   StdHepRescat = 0;
   StdHepStatus = 0;
   StdHepFd = 0;
   StdHepLd = 0;
   StdHepFm = 0;
   StdHepLm = 0;
   GeomPath = 0;
   GeneratorName = 0;
   OrigFileName = 0;
   OrigTreeName = 0;
}
ND::GRooTrackerVtx::GRooTrackerVtx(const GRooTrackerVtx & rhs)
   : ND::JNuBeamFlux(const_cast<GRooTrackerVtx &>( rhs ))
   , EvtCode(const_cast<GRooTrackerVtx &>( rhs ).EvtCode)
   , EvtNum(const_cast<GRooTrackerVtx &>( rhs ).EvtNum)
   , EvtXSec(const_cast<GRooTrackerVtx &>( rhs ).EvtXSec)
   , EvtDXSec(const_cast<GRooTrackerVtx &>( rhs ).EvtDXSec)
   , EvtWght(const_cast<GRooTrackerVtx &>( rhs ).EvtWght)
   , EvtProb(const_cast<GRooTrackerVtx &>( rhs ).EvtProb)
   , StdHepN(const_cast<GRooTrackerVtx &>( rhs ).StdHepN)
   , StdHepPdg(const_cast<GRooTrackerVtx &>( rhs ).StdHepPdg)
   , StdHepRescat(const_cast<GRooTrackerVtx &>( rhs ).StdHepRescat)
   , StdHepStatus(const_cast<GRooTrackerVtx &>( rhs ).StdHepStatus)
   , StdHepFd(const_cast<GRooTrackerVtx &>( rhs ).StdHepFd)
   , StdHepLd(const_cast<GRooTrackerVtx &>( rhs ).StdHepLd)
   , StdHepFm(const_cast<GRooTrackerVtx &>( rhs ).StdHepFm)
   , StdHepLm(const_cast<GRooTrackerVtx &>( rhs ).StdHepLm)
   , G2NeutEvtCode(const_cast<GRooTrackerVtx &>( rhs ).G2NeutEvtCode)
   , GeomPath(const_cast<GRooTrackerVtx &>( rhs ).GeomPath)
   , GeneratorName(const_cast<GRooTrackerVtx &>( rhs ).GeneratorName)
   , OrigFileName(const_cast<GRooTrackerVtx &>( rhs ).OrigFileName)
   , OrigTreeName(const_cast<GRooTrackerVtx &>( rhs ).OrigTreeName)
   , OrigEvtNum(const_cast<GRooTrackerVtx &>( rhs ).OrigEvtNum)
   , OrigTreeEntries(const_cast<GRooTrackerVtx &>( rhs ).OrigTreeEntries)
   , OrigTreePOT(const_cast<GRooTrackerVtx &>( rhs ).OrigTreePOT)
   , TimeInSpill(const_cast<GRooTrackerVtx &>( rhs ).TimeInSpill)
   , TruthVertexID(const_cast<GRooTrackerVtx &>( rhs ).TruthVertexID)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   GRooTrackerVtx &modrhs = const_cast<GRooTrackerVtx &>( rhs );
   modrhs.EvtCode = 0;
   for (Int_t i=0;i<4;i++) EvtVtx[i] = rhs.EvtVtx[i];
   modrhs.StdHepPdg = 0;
   modrhs.StdHepRescat = 0;
   modrhs.StdHepStatus = 0;
   for (Int_t i=0;i<1400;i++) (&(StdHepX4[0][0]))[i] = (&(rhs.StdHepX4[0][0]))[i];
   for (Int_t i=0;i<1400;i++) (&(StdHepP4[0][0]))[i] = (&(rhs.StdHepP4[0][0]))[i];
   for (Int_t i=0;i<1050;i++) (&(StdHepPolz[0][0]))[i] = (&(rhs.StdHepPolz[0][0]))[i];
   modrhs.StdHepFd = 0;
   modrhs.StdHepLd = 0;
   modrhs.StdHepFm = 0;
   modrhs.StdHepLm = 0;
   modrhs.GeomPath = 0;
   modrhs.GeneratorName = 0;
   modrhs.OrigFileName = 0;
   modrhs.OrigTreeName = 0;
}
ND::GRooTrackerVtx::~GRooTrackerVtx() {
   delete EvtCode;   EvtCode = 0;
   delete [] StdHepPdg;   StdHepPdg = 0;
   delete [] StdHepRescat;   StdHepRescat = 0;
   delete [] StdHepStatus;   StdHepStatus = 0;
   delete [] StdHepFd;   StdHepFd = 0;
   delete [] StdHepLd;   StdHepLd = 0;
   delete [] StdHepFm;   StdHepFm = 0;
   delete [] StdHepLm;   StdHepLm = 0;
   delete GeomPath;   GeomPath = 0;
   delete GeneratorName;   GeneratorName = 0;
   delete OrigFileName;   OrigFileName = 0;
   delete OrigTreeName;   OrigTreeName = 0;
}
#endif // ND__GRooTrackerVtx_cxx

#ifndef ND__TTRExReconModule__TTPCAnaPattern_cxx
#define ND__TTRExReconModule__TTPCAnaPattern_cxx
ND::TTRExReconModule::TTPCAnaPattern::TTPCAnaPattern() {
   Junctions = 0;
   Paths = 0;
}
ND::TTRExReconModule::TTPCAnaPattern::TTPCAnaPattern(const TTPCAnaPattern & rhs)
   : TObject(const_cast<TTPCAnaPattern &>( rhs ))
   , S1Sflag(const_cast<TTPCAnaPattern &>( rhs ).S1Sflag)
   , PatternID(const_cast<TTPCAnaPattern &>( rhs ).PatternID)
   , NJunctions(const_cast<TTPCAnaPattern &>( rhs ).NJunctions)
   , Junctions(const_cast<TTPCAnaPattern &>( rhs ).Junctions)
   , NPaths(const_cast<TTPCAnaPattern &>( rhs ).NPaths)
   , Paths(const_cast<TTPCAnaPattern &>( rhs ).Paths)
   , TPC(const_cast<TTPCAnaPattern &>( rhs ).TPC)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTPCAnaPattern &modrhs = const_cast<TTPCAnaPattern &>( rhs );
   modrhs.Junctions = 0;
   modrhs.Paths = 0;
}
ND::TTRExReconModule::TTPCAnaPattern::~TTPCAnaPattern() {
   delete Junctions;   Junctions = 0;
   delete Paths;   Paths = 0;
}
#endif // ND__TTRExReconModule__TTPCAnaPattern_cxx

#ifndef ND__TTRExReconModule__TTPCAnaPath_cxx
#define ND__TTRExReconModule__TTPCAnaPath_cxx
ND::TTRExReconModule::TTPCAnaPath::TTPCAnaPath() {
   JunctionIDs = 0;
   MatchingPathIDs = 0;
   PathMatchingLikelihood = 0;
   MatchingPatternIDs = 0;
   MatchingPatternPathIDs = 0;
   PatternMatchingLikelihood = 0;
}
ND::TTRExReconModule::TTPCAnaPath::TTPCAnaPath(const TTPCAnaPath & rhs)
   : TObject(const_cast<TTPCAnaPath &>( rhs ))
   , PathID(const_cast<TTPCAnaPath &>( rhs ).PathID)
   , G4ID(const_cast<TTPCAnaPath &>( rhs ).G4ID)
   , PathMatchingID(const_cast<TTPCAnaPath &>( rhs ).PathMatchingID)
   , FirstPosition(const_cast<TTPCAnaPath &>( rhs ).FirstPosition)
   , LastPosition(const_cast<TTPCAnaPath &>( rhs ).LastPosition)
   , Time(const_cast<TTPCAnaPath &>( rhs ).Time)
   , Length(const_cast<TTPCAnaPath &>( rhs ).Length)
   , Momentum(const_cast<TTPCAnaPath &>( rhs ).Momentum)
   , MomentumError(const_cast<TTPCAnaPath &>( rhs ).MomentumError)
   , Direction(const_cast<TTPCAnaPath &>( rhs ).Direction)
   , IsContained(const_cast<TTPCAnaPath &>( rhs ).IsContained)
   , LikFit(const_cast<TTPCAnaPath &>( rhs ).LikFit)
   , Success(const_cast<TTPCAnaPath &>( rhs ).Success)
   , FitLikelihood(const_cast<TTPCAnaPath &>( rhs ).FitLikelihood)
   , T0Source(const_cast<TTPCAnaPath &>( rhs ).T0Source)
   , NClusters(const_cast<TTPCAnaPath &>( rhs ).NClusters)
   , Charge(const_cast<TTPCAnaPath &>( rhs ).Charge)
   , ElePull(const_cast<TTPCAnaPath &>( rhs ).ElePull)
   , EleExp(const_cast<TTPCAnaPath &>( rhs ).EleExp)
   , EleSigma(const_cast<TTPCAnaPath &>( rhs ).EleSigma)
   , MuonPull(const_cast<TTPCAnaPath &>( rhs ).MuonPull)
   , MuonExp(const_cast<TTPCAnaPath &>( rhs ).MuonExp)
   , MuonSigma(const_cast<TTPCAnaPath &>( rhs ).MuonSigma)
   , PionPull(const_cast<TTPCAnaPath &>( rhs ).PionPull)
   , PionExp(const_cast<TTPCAnaPath &>( rhs ).PionExp)
   , PionSigma(const_cast<TTPCAnaPath &>( rhs ).PionSigma)
   , ProtonPull(const_cast<TTPCAnaPath &>( rhs ).ProtonPull)
   , ProtonExp(const_cast<TTPCAnaPath &>( rhs ).ProtonExp)
   , ProtonSigma(const_cast<TTPCAnaPath &>( rhs ).ProtonSigma)
   , KaonPull(const_cast<TTPCAnaPath &>( rhs ).KaonPull)
   , KaonExp(const_cast<TTPCAnaPath &>( rhs ).KaonExp)
   , KaonSigma(const_cast<TTPCAnaPath &>( rhs ).KaonSigma)
   , PDist(const_cast<TTPCAnaPath &>( rhs ).PDist)
   , PEField(const_cast<TTPCAnaPath &>( rhs ).PEField)
   , PID(const_cast<TTPCAnaPath &>( rhs ).PID)
   , NetCharge(const_cast<TTPCAnaPath &>( rhs ).NetCharge)
   , NJunctions(const_cast<TTPCAnaPath &>( rhs ).NJunctions)
   , JunctionIDs(const_cast<TTPCAnaPath &>( rhs ).JunctionIDs)
   , NMatchingPaths(const_cast<TTPCAnaPath &>( rhs ).NMatchingPaths)
   , MatchingPathIDs(const_cast<TTPCAnaPath &>( rhs ).MatchingPathIDs)
   , PathMatchingLikelihood(const_cast<TTPCAnaPath &>( rhs ).PathMatchingLikelihood)
   , NMatchingPatterns(const_cast<TTPCAnaPath &>( rhs ).NMatchingPatterns)
   , MatchingPatternIDs(const_cast<TTPCAnaPath &>( rhs ).MatchingPatternIDs)
   , MatchingPatternPathIDs(const_cast<TTPCAnaPath &>( rhs ).MatchingPatternPathIDs)
   , PatternMatchingLikelihood(const_cast<TTPCAnaPath &>( rhs ).PatternMatchingLikelihood)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<2;i++) T0Range[i] = rhs.T0Range[i];
   for (Int_t i=0;i<2;i++) T0RangeDeltaX[i] = rhs.T0RangeDeltaX[i];
   TTPCAnaPath &modrhs = const_cast<TTPCAnaPath &>( rhs );
   modrhs.JunctionIDs = 0;
   modrhs.MatchingPathIDs = 0;
   modrhs.PathMatchingLikelihood = 0;
   modrhs.MatchingPatternIDs = 0;
   modrhs.MatchingPatternPathIDs = 0;
   modrhs.PatternMatchingLikelihood = 0;
}
ND::TTRExReconModule::TTPCAnaPath::~TTPCAnaPath() {
   delete [] JunctionIDs;   JunctionIDs = 0;
   delete [] MatchingPathIDs;   MatchingPathIDs = 0;
   delete [] PathMatchingLikelihood;   PathMatchingLikelihood = 0;
   delete [] MatchingPatternIDs;   MatchingPatternIDs = 0;
   delete [] MatchingPatternPathIDs;   MatchingPatternPathIDs = 0;
   delete [] PatternMatchingLikelihood;   PatternMatchingLikelihood = 0;
}
#endif // ND__TTRExReconModule__TTPCAnaPath_cxx

#ifndef ND__TTRExReconModule__TTPCAnaJunction_cxx
#define ND__TTRExReconModule__TTPCAnaJunction_cxx
ND::TTRExReconModule::TTPCAnaJunction::TTPCAnaJunction() {
   PathIDs = 0;
}
ND::TTRExReconModule::TTPCAnaJunction::TTPCAnaJunction(const TTPCAnaJunction & rhs)
   : TObject(const_cast<TTPCAnaJunction &>( rhs ))
   , JunctionID(const_cast<TTPCAnaJunction &>( rhs ).JunctionID)
   , JunctionMatchingID(const_cast<TTPCAnaJunction &>( rhs ).JunctionMatchingID)
   , Position(const_cast<TTPCAnaJunction &>( rhs ).Position)
   , NPaths(const_cast<TTPCAnaJunction &>( rhs ).NPaths)
   , PathIDs(const_cast<TTPCAnaJunction &>( rhs ).PathIDs)
   , MaximumCoordinates(const_cast<TTPCAnaJunction &>( rhs ).MaximumCoordinates)
   , MinimumCoordinates(const_cast<TTPCAnaJunction &>( rhs ).MinimumCoordinates)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTPCAnaJunction &modrhs = const_cast<TTPCAnaJunction &>( rhs );
   modrhs.PathIDs = 0;
}
ND::TTRExReconModule::TTPCAnaJunction::~TTPCAnaJunction() {
   delete [] PathIDs;   PathIDs = 0;
}
#endif // ND__TTRExReconModule__TTPCAnaJunction_cxx

#ifndef ND__TGeometrySummaryModule__TDetectorBoundingBox_cxx
#define ND__TGeometrySummaryModule__TDetectorBoundingBox_cxx
ND::TGeometrySummaryModule::TDetectorBoundingBox::TDetectorBoundingBox() {
}
ND::TGeometrySummaryModule::TDetectorBoundingBox::TDetectorBoundingBox(const TDetectorBoundingBox & rhs)
   : TObject(const_cast<TDetectorBoundingBox &>( rhs ))
   , Minimum(const_cast<TDetectorBoundingBox &>( rhs ).Minimum)
   , Maximum(const_cast<TDetectorBoundingBox &>( rhs ).Maximum)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGeometrySummaryModule::TDetectorBoundingBox::~TDetectorBoundingBox() {
}
#endif // ND__TGeometrySummaryModule__TDetectorBoundingBox_cxx

#ifndef ND__TGeometrySummaryModule__TTPCMicroMegasVolumes_cxx
#define ND__TGeometrySummaryModule__TTPCMicroMegasVolumes_cxx
ND::TGeometrySummaryModule::TTPCMicroMegasVolumes::TTPCMicroMegasVolumes() {
}
ND::TGeometrySummaryModule::TTPCMicroMegasVolumes::TTPCMicroMegasVolumes(const TTPCMicroMegasVolumes & rhs)
   : TObject(const_cast<TTPCMicroMegasVolumes &>( rhs ))
   , MMvolumes(const_cast<TTPCMicroMegasVolumes &>( rhs ).MMvolumes)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTPCMicroMegasVolumes &modrhs = const_cast<TTPCMicroMegasVolumes &>( rhs );
   modrhs.MMvolumes.clear();
}
ND::TGeometrySummaryModule::TTPCMicroMegasVolumes::~TTPCMicroMegasVolumes() {
}
#endif // ND__TGeometrySummaryModule__TTPCMicroMegasVolumes_cxx

#ifndef ND__TBeamSummaryDataModule__TBeamSummaryData__TOtherData_cxx
#define ND__TBeamSummaryDataModule__TBeamSummaryData__TOtherData_cxx
ND::TBeamSummaryDataModule::TBeamSummaryData::TOtherData::TOtherData() {
}
ND::TBeamSummaryDataModule::TBeamSummaryData::TOtherData::TOtherData(const TOtherData & rhs)
   : TObject(const_cast<TOtherData &>( rhs ))
   , MidasEvent(const_cast<TOtherData &>( rhs ).MidasEvent)
   , BeamRunNumber(const_cast<TOtherData &>( rhs ).BeamRunNumber)
   , SpillNumber(const_cast<TOtherData &>( rhs ).SpillNumber)
   , MRRunNumber(const_cast<TOtherData &>( rhs ).MRRunNumber)
   , MumonSiTotalQ(const_cast<TOtherData &>( rhs ).MumonSiTotalQ)
   , MumonSiPeak(const_cast<TOtherData &>( rhs ).MumonSiPeak)
   , MumonSiX(const_cast<TOtherData &>( rhs ).MumonSiX)
   , MumonSiwX(const_cast<TOtherData &>( rhs ).MumonSiwX)
   , MumonSiY(const_cast<TOtherData &>( rhs ).MumonSiY)
   , MumonSiwY(const_cast<TOtherData &>( rhs ).MumonSiwY)
   , MumonICTotalQ(const_cast<TOtherData &>( rhs ).MumonICTotalQ)
   , MumonICPeak(const_cast<TOtherData &>( rhs ).MumonICPeak)
   , MumonICX(const_cast<TOtherData &>( rhs ).MumonICX)
   , MumonICwX(const_cast<TOtherData &>( rhs ).MumonICwX)
   , MumonICY(const_cast<TOtherData &>( rhs ).MumonICY)
   , MumonICwY(const_cast<TOtherData &>( rhs ).MumonICwY)
   , OTRLightYield(const_cast<TOtherData &>( rhs ).OTRLightYield)
   , OTRX(const_cast<TOtherData &>( rhs ).OTRX)
   , OTRwX(const_cast<TOtherData &>( rhs ).OTRwX)
   , OTRY(const_cast<TOtherData &>( rhs ).OTRY)
   , OTRwY(const_cast<TOtherData &>( rhs ).OTRwY)
   , OTRXError(const_cast<TOtherData &>( rhs ).OTRXError)
   , OTRwXError(const_cast<TOtherData &>( rhs ).OTRwXError)
   , OTRYError(const_cast<TOtherData &>( rhs ).OTRYError)
   , OTRwYError(const_cast<TOtherData &>( rhs ).OTRwYError)
   , GoodGPSFlag(const_cast<TOtherData &>( rhs ).GoodGPSFlag)
   , TriggerFlag(const_cast<TOtherData &>( rhs ).TriggerFlag)
   , SpillFlag(const_cast<TOtherData &>( rhs ).SpillFlag)
   , GoodSpillFlag(const_cast<TOtherData &>( rhs ).GoodSpillFlag)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<2;i++) GPSStatus[i] = rhs.GPSStatus[i];
   for (Int_t i=0;i<3;i++) TriggerTime[i] = rhs.TriggerTime[i];
   for (Int_t i=0;i<3;i++) TriggerTimeNanoSecond[i] = rhs.TriggerTimeNanoSecond[i];
   for (Int_t i=0;i<5;i++) ProtonsPerSpill[i] = rhs.ProtonsPerSpill[i];
   for (Int_t i=0;i<45;i++) (&(ProtonsPerBunch[0][0]))[i] = (&(rhs.ProtonsPerBunch[0][0]))[i];
   for (Int_t i=0;i<5;i++) BeamTiming[i] = rhs.BeamTiming[i];
   for (Int_t i=0;i<45;i++) (&(BeamBunchTiming[0][0]))[i] = (&(rhs.BeamBunchTiming[0][0]))[i];
   for (Int_t i=0;i<5;i++) BeamFlag[i] = rhs.BeamFlag[i];
   for (Int_t i=0;i<45;i++) (&(BeamBunchFlag[0][0]))[i] = (&(rhs.BeamBunchFlag[0][0]))[i];
   for (Int_t i=0;i<3;i++) HornCurrent[i] = rhs.HornCurrent[i];
   for (Int_t i=0;i<15;i++) (&(HornBusBarCurrent[0][0]))[i] = (&(rhs.HornBusBarCurrent[0][0]))[i];
   for (Int_t i=0;i<2;i++) BeamPositionOnTarget[i] = rhs.BeamPositionOnTarget[i];
   for (Int_t i=0;i<2;i++) BeamDirectionOnTarget[i] = rhs.BeamDirectionOnTarget[i];
   for (Int_t i=0;i<2;i++) BeamSizeOnTarget[i] = rhs.BeamSizeOnTarget[i];
   for (Int_t i=0;i<3;i++) TargetEfficiency[i] = rhs.TargetEfficiency[i];
}
ND::TBeamSummaryDataModule::TBeamSummaryData::TOtherData::~TOtherData() {
}
#endif // ND__TBeamSummaryDataModule__TBeamSummaryData__TOtherData_cxx

#ifndef ND__TBeamSummaryDataModule__TBeamSummaryData_cxx
#define ND__TBeamSummaryDataModule__TBeamSummaryData_cxx
ND::TBeamSummaryDataModule::TBeamSummaryData::TBeamSummaryData() {
}
ND::TBeamSummaryDataModule::TBeamSummaryData::TBeamSummaryData(const TBeamSummaryData & rhs)
   : TObject(const_cast<TBeamSummaryData &>( rhs ))
   , BeamRunNumber(const_cast<TBeamSummaryData &>( rhs ).BeamRunNumber)
   , SpillNumber(const_cast<TBeamSummaryData &>( rhs ).SpillNumber)
   , GPS1TriggerTime(const_cast<TBeamSummaryData &>( rhs ).GPS1TriggerTime)
   , GPS1TriggerTimeNanoSecond(const_cast<TBeamSummaryData &>( rhs ).GPS1TriggerTimeNanoSecond)
   , CT5ProtonsPerSpill(const_cast<TBeamSummaryData &>( rhs ).CT5ProtonsPerSpill)
   , OfficialProtonsPerSpill(const_cast<TBeamSummaryData &>( rhs ).OfficialProtonsPerSpill)
   , OfficialCTNumber(const_cast<TBeamSummaryData &>( rhs ).OfficialCTNumber)
   , OfficialBeamFlag(const_cast<TBeamSummaryData &>( rhs ).OfficialBeamFlag)
   , Horn1CurrentSum(const_cast<TBeamSummaryData &>( rhs ).Horn1CurrentSum)
   , Horn2CurrentSum(const_cast<TBeamSummaryData &>( rhs ).Horn2CurrentSum)
   , Horn3CurrentSum(const_cast<TBeamSummaryData &>( rhs ).Horn3CurrentSum)
   , GoodSpillFlag(const_cast<TBeamSummaryData &>( rhs ).GoodSpillFlag)
   , BSDVersion(const_cast<TBeamSummaryData &>( rhs ).BSDVersion)
   , OtherData(const_cast<TBeamSummaryData &>( rhs ).OtherData)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<8;i++) CT5ProtonsPerBunch[i] = rhs.CT5ProtonsPerBunch[i];
   for (Int_t i=0;i<8;i++) CT5BeamBunchTiming[i] = rhs.CT5BeamBunchTiming[i];
   for (Int_t i=0;i<8;i++) CT5BeamBunchFlag[i] = rhs.CT5BeamBunchFlag[i];
   for (Int_t i=0;i<8;i++) OfficialProtonsPerBunch[i] = rhs.OfficialProtonsPerBunch[i];
   for (Int_t i=0;i<8;i++) OfficialBeamBunchTiming[i] = rhs.OfficialBeamBunchTiming[i];
   for (Int_t i=0;i<8;i++) OfficialBeamBunchFlag[i] = rhs.OfficialBeamBunchFlag[i];
}
ND::TBeamSummaryDataModule::TBeamSummaryData::~TBeamSummaryData() {
}
#endif // ND__TBeamSummaryDataModule__TBeamSummaryData_cxx

#ifndef ND__TFgdOnlyModule__TFgd2DIsoTrack_cxx
#define ND__TFgdOnlyModule__TFgd2DIsoTrack_cxx
ND::TFgdOnlyModule::TFgd2DIsoTrack::TFgd2DIsoTrack() {
}
ND::TFgdOnlyModule::TFgd2DIsoTrack::TFgd2DIsoTrack(const TFgd2DIsoTrack & rhs)
   : TObject(const_cast<TFgd2DIsoTrack &>( rhs ))
   , AlgorithmName(const_cast<TFgd2DIsoTrack &>( rhs ).AlgorithmName)
   , NHits(const_cast<TFgd2DIsoTrack &>( rhs ).NHits)
   , Angle(const_cast<TFgd2DIsoTrack &>( rhs ).Angle)
   , SumCharge(const_cast<TFgd2DIsoTrack &>( rhs ).SumCharge)
   , Range(const_cast<TFgd2DIsoTrack &>( rhs ).Range)
   , Origin(const_cast<TFgd2DIsoTrack &>( rhs ).Origin)
   , OriginVariance(const_cast<TFgd2DIsoTrack &>( rhs ).OriginVariance)
   , Direction(const_cast<TFgd2DIsoTrack &>( rhs ).Direction)
   , HitPositions(const_cast<TFgd2DIsoTrack &>( rhs ).HitPositions)
   , TrajId(const_cast<TFgd2DIsoTrack &>( rhs ).TrajId)
   , Completeness(const_cast<TFgd2DIsoTrack &>( rhs ).Completeness)
   , Cleanliness(const_cast<TFgd2DIsoTrack &>( rhs ).Cleanliness)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TFgd2DIsoTrack &modrhs = const_cast<TFgd2DIsoTrack &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.HitPositions.clear();
}
ND::TFgdOnlyModule::TFgd2DIsoTrack::~TFgd2DIsoTrack() {
}
#endif // ND__TFgdOnlyModule__TFgd2DIsoTrack_cxx

#ifndef ND__TFgdOnlyModule__TFgd3DIsoTrack_cxx
#define ND__TFgdOnlyModule__TFgd3DIsoTrack_cxx
ND::TFgdOnlyModule::TFgd3DIsoTrack::TFgd3DIsoTrack() {
}
ND::TFgdOnlyModule::TFgd3DIsoTrack::TFgd3DIsoTrack(const TFgd3DIsoTrack & rhs)
   : TObject(const_cast<TFgd3DIsoTrack &>( rhs ))
   , AlgorithmName(const_cast<TFgd3DIsoTrack &>( rhs ).AlgorithmName)
   , NHits(const_cast<TFgd3DIsoTrack &>( rhs ).NHits)
   , SumCharge(const_cast<TFgd3DIsoTrack &>( rhs ).SumCharge)
   , Range(const_cast<TFgd3DIsoTrack &>( rhs ).Range)
   , Origin(const_cast<TFgd3DIsoTrack &>( rhs ).Origin)
   , OriginVariance(const_cast<TFgd3DIsoTrack &>( rhs ).OriginVariance)
   , Direction(const_cast<TFgd3DIsoTrack &>( rhs ).Direction)
   , muonPull(const_cast<TFgd3DIsoTrack &>( rhs ).muonPull)
   , pionPull(const_cast<TFgd3DIsoTrack &>( rhs ).pionPull)
   , protonPull(const_cast<TFgd3DIsoTrack &>( rhs ).protonPull)
   , XZHitPositions(const_cast<TFgd3DIsoTrack &>( rhs ).XZHitPositions)
   , YZHitPositions(const_cast<TFgd3DIsoTrack &>( rhs ).YZHitPositions)
   , TrajId(const_cast<TFgd3DIsoTrack &>( rhs ).TrajId)
   , Completeness(const_cast<TFgd3DIsoTrack &>( rhs ).Completeness)
   , Cleanliness(const_cast<TFgd3DIsoTrack &>( rhs ).Cleanliness)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TFgd3DIsoTrack &modrhs = const_cast<TFgd3DIsoTrack &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.XZHitPositions.clear();
   modrhs.YZHitPositions.clear();
}
ND::TFgdOnlyModule::TFgd3DIsoTrack::~TFgd3DIsoTrack() {
}
#endif // ND__TFgdOnlyModule__TFgd3DIsoTrack_cxx

#ifndef ND__TFgdOnlyModule__TFgd3DShowerPID_cxx
#define ND__TFgdOnlyModule__TFgd3DShowerPID_cxx
ND::TFgdOnlyModule::TFgd3DShowerPID::TFgd3DShowerPID() {
}
ND::TFgdOnlyModule::TFgd3DShowerPID::TFgd3DShowerPID(const TFgd3DShowerPID & rhs)
   : TObject(const_cast<TFgd3DShowerPID &>( rhs ))
   , Hyp1(const_cast<TFgd3DShowerPID &>( rhs ).Hyp1)
   , Hyp2(const_cast<TFgd3DShowerPID &>( rhs ).Hyp2)
   , PCAEigenValues(const_cast<TFgd3DShowerPID &>( rhs ).PCAEigenValues)
   , NumHits(const_cast<TFgd3DShowerPID &>( rhs ).NumHits)
   , MatchingLikelihood3D(const_cast<TFgd3DShowerPID &>( rhs ).MatchingLikelihood3D)
   , Circularity(const_cast<TFgd3DShowerPID &>( rhs ).Circularity)
   , Trajectories(const_cast<TFgd3DShowerPID &>( rhs ).Trajectories)
   , NDOF(const_cast<TFgd3DShowerPID &>( rhs ).NDOF)
   , Quality(const_cast<TFgd3DShowerPID &>( rhs ).Quality)
   , Status(const_cast<TFgd3DShowerPID &>( rhs ).Status)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TFgd3DShowerPID &modrhs = const_cast<TFgd3DShowerPID &>( rhs );
   modrhs.Trajectories.clear();
}
ND::TFgdOnlyModule::TFgd3DShowerPID::~TFgd3DShowerPID() {
}
#endif // ND__TFgdOnlyModule__TFgd3DShowerPID_cxx

#ifndef ND__TFgdOnlyModule__TFgd3DShowerHyp_cxx
#define ND__TFgdOnlyModule__TFgd3DShowerHyp_cxx
ND::TFgdOnlyModule::TFgd3DShowerHyp::TFgd3DShowerHyp() {
}
ND::TFgdOnlyModule::TFgd3DShowerHyp::TFgd3DShowerHyp(const TFgd3DShowerHyp & rhs)
   : TObject(const_cast<TFgd3DShowerHyp &>( rhs ))
   , Position(const_cast<TFgd3DShowerHyp &>( rhs ).Position)
   , PositionVar(const_cast<TFgd3DShowerHyp &>( rhs ).PositionVar)
   , Direction(const_cast<TFgd3DShowerHyp &>( rhs ).Direction)
   , DirectionVar(const_cast<TFgd3DShowerHyp &>( rhs ).DirectionVar)
   , ConeAngle(const_cast<TFgd3DShowerHyp &>( rhs ).ConeAngle)
   , ConeAngleVar(const_cast<TFgd3DShowerHyp &>( rhs ).ConeAngleVar)
   , EDeposit(const_cast<TFgd3DShowerHyp &>( rhs ).EDeposit)
   , QAvgInThirds(const_cast<TFgd3DShowerHyp &>( rhs ).QAvgInThirds)
   , SpreadInThirds(const_cast<TFgd3DShowerHyp &>( rhs ).SpreadInThirds)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TFgdOnlyModule::TFgd3DShowerHyp::~TFgd3DShowerHyp() {
}
#endif // ND__TFgdOnlyModule__TFgd3DShowerHyp_cxx

#ifndef ND__TFgdOnlyModule__TFgd2DCluster_cxx
#define ND__TFgdOnlyModule__TFgd2DCluster_cxx
ND::TFgdOnlyModule::TFgd2DCluster::TFgd2DCluster() {
}
ND::TFgdOnlyModule::TFgd2DCluster::TFgd2DCluster(const TFgd2DCluster & rhs)
   : TObject(const_cast<TFgd2DCluster &>( rhs ))
   , AlgorithmName(const_cast<TFgd2DCluster &>( rhs ).AlgorithmName)
   , Position(const_cast<TFgd2DCluster &>( rhs ).Position)
   , PCADirection(const_cast<TFgd2DCluster &>( rhs ).PCADirection)
   , StartPosition(const_cast<TFgd2DCluster &>( rhs ).StartPosition)
   , EndPosition(const_cast<TFgd2DCluster &>( rhs ).EndPosition)
   , Range(const_cast<TFgd2DCluster &>( rhs ).Range)
   , AvgHitTime(const_cast<TFgd2DCluster &>( rhs ).AvgHitTime)
   , EDeposit(const_cast<TFgd2DCluster &>( rhs ).EDeposit)
   , NumHits(const_cast<TFgd2DCluster &>( rhs ).NumHits)
   , Trajectories(const_cast<TFgd2DCluster &>( rhs ).Trajectories)
   , NDOF(const_cast<TFgd2DCluster &>( rhs ).NDOF)
   , Quality(const_cast<TFgd2DCluster &>( rhs ).Quality)
   , Status(const_cast<TFgd2DCluster &>( rhs ).Status)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TFgd2DCluster &modrhs = const_cast<TFgd2DCluster &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Trajectories.clear();
}
ND::TFgdOnlyModule::TFgd2DCluster::~TFgd2DCluster() {
}
#endif // ND__TFgdOnlyModule__TFgd2DCluster_cxx

#ifndef ND__TSmrdReconModule__TSmrdReconHit_cxx
#define ND__TSmrdReconModule__TSmrdReconHit_cxx
ND::TSmrdReconModule::TSmrdReconHit::TSmrdReconHit() {
}
ND::TSmrdReconModule::TSmrdReconHit::TSmrdReconHit(const TSmrdReconHit & rhs)
   : TObject(const_cast<TSmrdReconHit &>( rhs ))
   , Position(const_cast<TSmrdReconHit &>( rhs ).Position)
   , PositionUncertainty(const_cast<TSmrdReconHit &>( rhs ).PositionUncertainty)
   , Charge(const_cast<TSmrdReconHit &>( rhs ).Charge)
   , dZ(const_cast<TSmrdReconHit &>( rhs ).dZ)
   , dT(const_cast<TSmrdReconHit &>( rhs ).dT)
   , Wall(const_cast<TSmrdReconHit &>( rhs ).Wall)
   , Yoke(const_cast<TSmrdReconHit &>( rhs ).Yoke)
   , Layer(const_cast<TSmrdReconHit &>( rhs ).Layer)
   , Tower(const_cast<TSmrdReconHit &>( rhs ).Tower)
   , Counter(const_cast<TSmrdReconHit &>( rhs ).Counter)
   , RMM(const_cast<TSmrdReconHit &>( rhs ).RMM)
   , TFB(const_cast<TSmrdReconHit &>( rhs ).TFB)
   , IsInnerMatched(const_cast<TSmrdReconHit &>( rhs ).IsInnerMatched)
   , IsUsed(const_cast<TSmrdReconHit &>( rhs ).IsUsed)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<2;i++) ContribCharge[i] = rhs.ContribCharge[i];
}
ND::TSmrdReconModule::TSmrdReconHit::~TSmrdReconHit() {
}
#endif // ND__TSmrdReconModule__TSmrdReconHit_cxx

#ifndef ND__TSmrdReconModule__TSmrdIsoTrack_cxx
#define ND__TSmrdReconModule__TSmrdIsoTrack_cxx
ND::TSmrdReconModule::TSmrdIsoTrack::TSmrdIsoTrack() {
}
ND::TSmrdReconModule::TSmrdIsoTrack::TSmrdIsoTrack(const TSmrdIsoTrack & rhs)
   : TObject(const_cast<TSmrdIsoTrack &>( rhs ))
   , UniqueID(const_cast<TSmrdIsoTrack &>( rhs ).UniqueID)
   , AlgorithmName(const_cast<TSmrdIsoTrack &>( rhs ).AlgorithmName)
   , FrontPos(const_cast<TSmrdIsoTrack &>( rhs ).FrontPos)
   , FrontPosVariance(const_cast<TSmrdIsoTrack &>( rhs ).FrontPosVariance)
   , BackPos(const_cast<TSmrdIsoTrack &>( rhs ).BackPos)
   , BackPosVariance(const_cast<TSmrdIsoTrack &>( rhs ).BackPosVariance)
   , Direction(const_cast<TSmrdIsoTrack &>( rhs ).Direction)
   , DirectionVariance(const_cast<TSmrdIsoTrack &>( rhs ).DirectionVariance)
   , NHits(const_cast<TSmrdIsoTrack &>( rhs ).NHits)
   , NNodes(const_cast<TSmrdIsoTrack &>( rhs ).NNodes)
   , Status(const_cast<TSmrdIsoTrack &>( rhs ).Status)
   , KalmanStatus(const_cast<TSmrdIsoTrack &>( rhs ).KalmanStatus)
   , NDOF(const_cast<TSmrdIsoTrack &>( rhs ).NDOF)
   , EDeposit(const_cast<TSmrdIsoTrack &>( rhs ).EDeposit)
   , avgtime(const_cast<TSmrdIsoTrack &>( rhs ).avgtime)
   , Range(const_cast<TSmrdIsoTrack &>( rhs ).Range)
   , Chi2(const_cast<TSmrdIsoTrack &>( rhs ).Chi2)
   , ThetaAngle(const_cast<TSmrdIsoTrack &>( rhs ).ThetaAngle)
   , PhiAngle(const_cast<TSmrdIsoTrack &>( rhs ).PhiAngle)
   , TrueInitPos(const_cast<TSmrdIsoTrack &>( rhs ).TrueInitPos)
   , TrueInitDet(const_cast<TSmrdIsoTrack &>( rhs ).TrueInitDet)
   , TrueFinalPos(const_cast<TSmrdIsoTrack &>( rhs ).TrueFinalPos)
   , TrueFinalDet(const_cast<TSmrdIsoTrack &>( rhs ).TrueFinalDet)
   , TrueInitMom(const_cast<TSmrdIsoTrack &>( rhs ).TrueInitMom)
   , TrueId(const_cast<TSmrdIsoTrack &>( rhs ).TrueId)
   , TruePDG(const_cast<TSmrdIsoTrack &>( rhs ).TruePDG)
   , TrueParentId(const_cast<TSmrdIsoTrack &>( rhs ).TrueParentId)
   , TrueHitPurity(const_cast<TSmrdIsoTrack &>( rhs ).TrueHitPurity)
   , TrueHitEff(const_cast<TSmrdIsoTrack &>( rhs ).TrueHitEff)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TSmrdIsoTrack &modrhs = const_cast<TSmrdIsoTrack &>( rhs );
   modrhs.AlgorithmName.clear();
}
ND::TSmrdReconModule::TSmrdIsoTrack::~TSmrdIsoTrack() {
}
#endif // ND__TSmrdReconModule__TSmrdIsoTrack_cxx

#ifndef ND__TTrackerReconModule__TTrackerVertex_cxx
#define ND__TTrackerReconModule__TTrackerVertex_cxx
ND::TTrackerReconModule::TTrackerVertex::TTrackerVertex() {
}
ND::TTrackerReconModule::TTrackerVertex::TTrackerVertex(const TTrackerVertex & rhs)
   : TObject(const_cast<TTrackerVertex &>( rhs ))
   , AlgorithmName(const_cast<TTrackerVertex &>( rhs ).AlgorithmName)
   , Status(const_cast<TTrackerVertex &>( rhs ).Status)
   , Quality(const_cast<TTrackerVertex &>( rhs ).Quality)
   , NDOF(const_cast<TTrackerVertex &>( rhs ).NDOF)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTrackerVertex &modrhs = const_cast<TTrackerVertex &>( rhs );
   modrhs.AlgorithmName.clear();
}
ND::TTrackerReconModule::TTrackerVertex::~TTrackerVertex() {
}
#endif // ND__TTrackerReconModule__TTrackerVertex_cxx

#ifndef ND__TTrackerReconModule__TTrackerResult_cxx
#define ND__TTrackerReconModule__TTrackerResult_cxx
ND::TTrackerReconModule::TTrackerResult::TTrackerResult() {
   Constituents = 0;
   TPC = 0;
   FGD = 0;
   Nodes = 0;
}
ND::TTrackerReconModule::TTrackerResult::TTrackerResult(const TTrackerResult & rhs)
   : TObject(const_cast<TTrackerResult &>( rhs ))
   , UniqueID(const_cast<TTrackerResult &>( rhs ).UniqueID)
   , AlgorithmName(const_cast<TTrackerResult &>( rhs ).AlgorithmName)
   , Detectors(const_cast<TTrackerResult &>( rhs ).Detectors)
   , Status(const_cast<TTrackerResult &>( rhs ).Status)
   , Quality(const_cast<TTrackerResult &>( rhs ).Quality)
   , NDOF(const_cast<TTrackerResult &>( rhs ).NDOF)
   , Chi2(const_cast<TTrackerResult &>( rhs ).Chi2)
   , NHits(const_cast<TTrackerResult &>( rhs ).NHits)
   , NConstituents(const_cast<TTrackerResult &>( rhs ).NConstituents)
   , NTotalConstituents(const_cast<TTrackerResult &>( rhs ).NTotalConstituents)
   , Constituents(const_cast<TTrackerResult &>( rhs ).Constituents)
   , isForward(const_cast<TTrackerResult &>( rhs ).isForward)
   , Charge(const_cast<TTrackerResult &>( rhs ).Charge)
   , EDeposit(const_cast<TTrackerResult &>( rhs ).EDeposit)
   , Length(const_cast<TTrackerResult &>( rhs ).Length)
   , matchingFailure_flag(const_cast<TTrackerResult &>( rhs ).matchingFailure_flag)
   , Likelihoods(const_cast<TTrackerResult &>( rhs ).Likelihoods)
   , Pids(const_cast<TTrackerResult &>( rhs ).Pids)
   , Position(const_cast<TTrackerResult &>( rhs ).Position)
   , Variance(const_cast<TTrackerResult &>( rhs ).Variance)
   , Direction(const_cast<TTrackerResult &>( rhs ).Direction)
   , DirectionVariance(const_cast<TTrackerResult &>( rhs ).DirectionVariance)
   , Momentum(const_cast<TTrackerResult &>( rhs ).Momentum)
   , MomentumError(const_cast<TTrackerResult &>( rhs ).MomentumError)
   , TrueParticle(const_cast<TTrackerResult &>( rhs ).TrueParticle)
   , NTPCs(const_cast<TTrackerResult &>( rhs ).NTPCs)
   , TPC(const_cast<TTrackerResult &>( rhs ).TPC)
   , NFGDs(const_cast<TTrackerResult &>( rhs ).NFGDs)
   , FGD(const_cast<TTrackerResult &>( rhs ).FGD)
   , NNodes(const_cast<TTrackerResult &>( rhs ).NNodes)
   , Nodes(const_cast<TTrackerResult &>( rhs ).Nodes)
   , hackConstituentsObject(const_cast<TTrackerResult &>( rhs ).hackConstituentsObject)
   , hackTPCTrack(const_cast<TTrackerResult &>( rhs ).hackTPCTrack)
   , hackFGDTrack(const_cast<TTrackerResult &>( rhs ).hackFGDTrack)
   , hackNodes(const_cast<TTrackerResult &>( rhs ).hackNodes)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTrackerResult &modrhs = const_cast<TTrackerResult &>( rhs );
   modrhs.AlgorithmName.clear();
   for (Int_t i=0;i<2;i++) ConstitIdx[i] = rhs.ConstitIdx[i];
   modrhs.Constituents = 0;
   modrhs.Likelihoods.clear();
   modrhs.Pids.clear();
   modrhs.TPC = 0;
   modrhs.FGD = 0;
   modrhs.Nodes = 0;
}
ND::TTrackerReconModule::TTrackerResult::~TTrackerResult() {
   delete Constituents;   Constituents = 0;
   delete TPC;   TPC = 0;
   delete FGD;   FGD = 0;
   delete Nodes;   Nodes = 0;
}
#endif // ND__TTrackerReconModule__TTrackerResult_cxx

#ifndef ND__TTrackerReconModule__TTrueParticle_cxx
#define ND__TTrackerReconModule__TTrueParticle_cxx
ND::TTrackerReconModule::TTrueParticle::TTrueParticle() {
}
ND::TTrackerReconModule::TTrueParticle::TTrueParticle(const TTrueParticle & rhs)
   : TObject(const_cast<TTrueParticle &>( rhs ))
   , ID(const_cast<TTrueParticle &>( rhs ).ID)
   , Pur(const_cast<TTrueParticle &>( rhs ).Pur)
   , Eff(const_cast<TTrueParticle &>( rhs ).Eff)
   , Vertex(const_cast<TTrueParticle &>( rhs ).Vertex)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerReconModule::TTrueParticle::~TTrueParticle() {
}
#endif // ND__TTrackerReconModule__TTrueParticle_cxx

#ifndef ND__TTrueVertex_cxx
#define ND__TTrueVertex_cxx
ND::TTrueVertex::TTrueVertex() {
}
ND::TTrueVertex::TTrueVertex(const TTrueVertex & rhs)
   : TObject(const_cast<TTrueVertex &>( rhs ))
   , Position(const_cast<TTrueVertex &>( rhs ).Position)
   , ID(const_cast<TTrueVertex &>( rhs ).ID)
   , Pur(const_cast<TTrueVertex &>( rhs ).Pur)
   , Eff(const_cast<TTrueVertex &>( rhs ).Eff)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrueVertex::~TTrueVertex() {
}
#endif // ND__TTrueVertex_cxx

#ifndef ND__TTrackerReconModule__TTrackerConstituent_cxx
#define ND__TTrackerReconModule__TTrackerConstituent_cxx
ND::TTrackerReconModule::TTrackerConstituent::TTrackerConstituent() {
}
ND::TTrackerReconModule::TTrackerConstituent::TTrackerConstituent(const TTrackerConstituent & rhs)
   : TObject(const_cast<TTrackerConstituent &>( rhs ))
   , AlgorithmName(const_cast<TTrackerConstituent &>( rhs ).AlgorithmName)
   , Detectors(const_cast<TTrackerConstituent &>( rhs ).Detectors)
   , Status(const_cast<TTrackerConstituent &>( rhs ).Status)
   , Quality(const_cast<TTrackerConstituent &>( rhs ).Quality)
   , NDOF(const_cast<TTrackerConstituent &>( rhs ).NDOF)
   , Chi2(const_cast<TTrackerConstituent &>( rhs ).Chi2)
   , NNodes(const_cast<TTrackerConstituent &>( rhs ).NNodes)
   , NHits(const_cast<TTrackerConstituent &>( rhs ).NHits)
   , NConstituents(const_cast<TTrackerConstituent &>( rhs ).NConstituents)
   , isForward(const_cast<TTrackerConstituent &>( rhs ).isForward)
   , Charge(const_cast<TTrackerConstituent &>( rhs ).Charge)
   , EDeposit(const_cast<TTrackerConstituent &>( rhs ).EDeposit)
   , FrontPosition(const_cast<TTrackerConstituent &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TTrackerConstituent &>( rhs ).BackPosition)
   , FrontVariance(const_cast<TTrackerConstituent &>( rhs ).FrontVariance)
   , BackVariance(const_cast<TTrackerConstituent &>( rhs ).BackVariance)
   , FrontDirection(const_cast<TTrackerConstituent &>( rhs ).FrontDirection)
   , BackDirection(const_cast<TTrackerConstituent &>( rhs ).BackDirection)
   , FrontMomentum(const_cast<TTrackerConstituent &>( rhs ).FrontMomentum)
   , BackMomentum(const_cast<TTrackerConstituent &>( rhs ).BackMomentum)
   , Position(const_cast<TTrackerConstituent &>( rhs ).Position)
   , Variance(const_cast<TTrackerConstituent &>( rhs ).Variance)
   , Direction(const_cast<TTrackerConstituent &>( rhs ).Direction)
   , DirectionVariance(const_cast<TTrackerConstituent &>( rhs ).DirectionVariance)
   , Momentum(const_cast<TTrackerConstituent &>( rhs ).Momentum)
   , MomentumError(const_cast<TTrackerConstituent &>( rhs ).MomentumError)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTrackerConstituent &modrhs = const_cast<TTrackerConstituent &>( rhs );
   modrhs.AlgorithmName.clear();
   for (Int_t i=0;i<2;i++) ConstitIdx[i] = rhs.ConstitIdx[i];
}
ND::TTrackerReconModule::TTrackerConstituent::~TTrackerConstituent() {
}
#endif // ND__TTrackerReconModule__TTrackerConstituent_cxx

#ifndef ND__TTrackerReconModule__TTPCTrack_cxx
#define ND__TTrackerReconModule__TTPCTrack_cxx
ND::TTrackerReconModule::TTPCTrack::TTPCTrack() {
}
ND::TTrackerReconModule::TTPCTrack::TTPCTrack(const TTPCTrack & rhs)
   : TObject(const_cast<TTPCTrack &>( rhs ))
   , UniqueID(const_cast<TTPCTrack &>( rhs ).UniqueID)
   , Detector(const_cast<TTPCTrack &>( rhs ).Detector)
   , Ndof(const_cast<TTPCTrack &>( rhs ).Ndof)
   , Chi2(const_cast<TTPCTrack &>( rhs ).Chi2)
   , NHits(const_cast<TTPCTrack &>( rhs ).NHits)
   , Momentum(const_cast<TTPCTrack &>( rhs ).Momentum)
   , MomentumError(const_cast<TTPCTrack &>( rhs ).MomentumError)
   , Charge(const_cast<TTPCTrack &>( rhs ).Charge)
   , Position(const_cast<TTPCTrack &>( rhs ).Position)
   , PositionVariance(const_cast<TTPCTrack &>( rhs ).PositionVariance)
   , Direction(const_cast<TTPCTrack &>( rhs ).Direction)
   , DirectionVariance(const_cast<TTPCTrack &>( rhs ).DirectionVariance)
   , NTrun(const_cast<TTPCTrack &>( rhs ).NTrun)
   , Ccorr(const_cast<TTPCTrack &>( rhs ).Ccorr)
   , PullEle(const_cast<TTPCTrack &>( rhs ).PullEle)
   , PullMuon(const_cast<TTPCTrack &>( rhs ).PullMuon)
   , PullPion(const_cast<TTPCTrack &>( rhs ).PullPion)
   , PullKaon(const_cast<TTPCTrack &>( rhs ).PullKaon)
   , PullProton(const_cast<TTPCTrack &>( rhs ).PullProton)
   , dEdxexpEle(const_cast<TTPCTrack &>( rhs ).dEdxexpEle)
   , dEdxexpMuon(const_cast<TTPCTrack &>( rhs ).dEdxexpMuon)
   , dEdxexpPion(const_cast<TTPCTrack &>( rhs ).dEdxexpPion)
   , dEdxexpKaon(const_cast<TTPCTrack &>( rhs ).dEdxexpKaon)
   , dEdxexpProton(const_cast<TTPCTrack &>( rhs ).dEdxexpProton)
   , SigmaEle(const_cast<TTPCTrack &>( rhs ).SigmaEle)
   , SigmaMuon(const_cast<TTPCTrack &>( rhs ).SigmaMuon)
   , SigmaPion(const_cast<TTPCTrack &>( rhs ).SigmaPion)
   , SigmaKaon(const_cast<TTPCTrack &>( rhs ).SigmaKaon)
   , SigmaProton(const_cast<TTPCTrack &>( rhs ).SigmaProton)
   , Sigma0(const_cast<TTPCTrack &>( rhs ).Sigma0)
   , Sigma1(const_cast<TTPCTrack &>( rhs ).Sigma1)
   , Sigma2(const_cast<TTPCTrack &>( rhs ).Sigma2)
   , MeanDrift(const_cast<TTPCTrack &>( rhs ).MeanDrift)
   , NConstituents(const_cast<TTPCTrack &>( rhs ).NConstituents)
   , TrDirection(const_cast<TTPCTrack &>( rhs ).TrDirection)
   , TrDirectionVar(const_cast<TTPCTrack &>( rhs ).TrDirectionVar)
   , TrCurvature(const_cast<TTPCTrack &>( rhs ).TrCurvature)
   , TrCurvatureVar(const_cast<TTPCTrack &>( rhs ).TrCurvatureVar)
   , HasExtrapolation(const_cast<TTPCTrack &>( rhs ).HasExtrapolation)
   , ExtrapolatedVertexXX(const_cast<TTPCTrack &>( rhs ).ExtrapolatedVertexXX)
   , ExtrapolatedVertexZX(const_cast<TTPCTrack &>( rhs ).ExtrapolatedVertexZX)
   , ExtrapolatedVertexYY(const_cast<TTPCTrack &>( rhs ).ExtrapolatedVertexYY)
   , ExtrapolatedVertexZY(const_cast<TTPCTrack &>( rhs ).ExtrapolatedVertexZY)
   , EnteringFGD(const_cast<TTPCTrack &>( rhs ).EnteringFGD)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerReconModule::TTPCTrack::~TTPCTrack() {
}
#endif // ND__TTrackerReconModule__TTPCTrack_cxx

#ifndef ND__TTrackerReconModule__TFGDTrack_cxx
#define ND__TTrackerReconModule__TFGDTrack_cxx
ND::TTrackerReconModule::TFGDTrack::TFGDTrack() {
}
ND::TTrackerReconModule::TFGDTrack::TFGDTrack(const TFGDTrack & rhs)
   : TObject(const_cast<TFGDTrack &>( rhs ))
   , UniqueID(const_cast<TFGDTrack &>( rhs ).UniqueID)
   , Detector(const_cast<TFGDTrack &>( rhs ).Detector)
   , Ndof(const_cast<TFGDTrack &>( rhs ).Ndof)
   , Chi2(const_cast<TFGDTrack &>( rhs ).Chi2)
   , Position(const_cast<TFGDTrack &>( rhs ).Position)
   , Direction(const_cast<TFGDTrack &>( rhs ).Direction)
   , EDeposit(const_cast<TFGDTrack &>( rhs ).EDeposit)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerReconModule::TFGDTrack::~TFGDTrack() {
}
#endif // ND__TTrackerReconModule__TFGDTrack_cxx

#ifndef ND__TTrackerReconModule__TTrackerNode_cxx
#define ND__TTrackerReconModule__TTrackerNode_cxx
ND::TTrackerReconModule::TTrackerNode::TTrackerNode() {
}
ND::TTrackerReconModule::TTrackerNode::TTrackerNode(const TTrackerNode & rhs)
   : TObject(const_cast<TTrackerNode &>( rhs ))
   , Charge(const_cast<TTrackerNode &>( rhs ).Charge)
   , EDeposit(const_cast<TTrackerNode &>( rhs ).EDeposit)
   , Position(const_cast<TTrackerNode &>( rhs ).Position)
   , Variance(const_cast<TTrackerNode &>( rhs ).Variance)
   , Direction(const_cast<TTrackerNode &>( rhs ).Direction)
   , DirectionVariance(const_cast<TTrackerNode &>( rhs ).DirectionVariance)
   , Momentum(const_cast<TTrackerNode &>( rhs ).Momentum)
   , MomentumError(const_cast<TTrackerNode &>( rhs ).MomentumError)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerReconModule::TTrackerNode::~TTrackerNode() {
}
#endif // ND__TTrackerReconModule__TTrackerNode_cxx

#ifndef ND__TTrackerReconModule__TTrackOther_cxx
#define ND__TTrackerReconModule__TTrackOther_cxx
ND::TTrackerReconModule::TTrackOther::TTrackOther() {
   Hits = 0;
}
ND::TTrackerReconModule::TTrackOther::TTrackOther(const TTrackOther & rhs)
   : TObject(const_cast<TTrackOther &>( rhs ))
   , AlgorithmName(const_cast<TTrackOther &>( rhs ).AlgorithmName)
   , Detector(const_cast<TTrackOther &>( rhs ).Detector)
   , NHits(const_cast<TTrackOther &>( rhs ).NHits)
   , Hits(const_cast<TTrackOther &>( rhs ).Hits)
   , EDeposit(const_cast<TTrackOther &>( rhs ).EDeposit)
   , FrontPosition(const_cast<TTrackOther &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TTrackOther &>( rhs ).BackPosition)
   , hackHits(const_cast<TTrackOther &>( rhs ).hackHits)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTrackOther &modrhs = const_cast<TTrackOther &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Hits = 0;
}
ND::TTrackerReconModule::TTrackOther::~TTrackOther() {
   delete Hits;   Hits = 0;
}
#endif // ND__TTrackerReconModule__TTrackOther_cxx

#ifndef ND__TTrackerReconModule__TUnusedHit_cxx
#define ND__TTrackerReconModule__TUnusedHit_cxx
ND::TTrackerReconModule::TUnusedHit::TUnusedHit() {
}
ND::TTrackerReconModule::TUnusedHit::TUnusedHit(const TUnusedHit & rhs)
   : TObject(const_cast<TUnusedHit &>( rhs ))
   , TotalCharge(const_cast<TUnusedHit &>( rhs ).TotalCharge)
   , Position(const_cast<TUnusedHit &>( rhs ).Position)
   , Variance(const_cast<TUnusedHit &>( rhs ).Variance)
   , Time(const_cast<TUnusedHit &>( rhs ).Time)
   , TimeUnc(const_cast<TUnusedHit &>( rhs ).TimeUnc)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerReconModule::TUnusedHit::~TUnusedHit() {
}
#endif // ND__TTrackerReconModule__TUnusedHit_cxx

#ifndef ND__TGlobalReconModule__TTpcPID_cxx
#define ND__TGlobalReconModule__TTpcPID_cxx
ND::TGlobalReconModule::TTpcPID::TTpcPID() {
}
ND::TGlobalReconModule::TTpcPID::TTpcPID(const TTpcPID & rhs)
   : TObject(const_cast<TTpcPID &>( rhs ))
   , AlgorithmName(const_cast<TTpcPID &>( rhs ).AlgorithmName)
   , Detectors(const_cast<TTpcPID &>( rhs ).Detectors)
   , Status(const_cast<TTpcPID &>( rhs ).Status)
   , NDOF(const_cast<TTpcPID &>( rhs ).NDOF)
   , Chi2(const_cast<TTpcPID &>( rhs ).Chi2)
   , NNodes(const_cast<TTpcPID &>( rhs ).NNodes)
   , NHits(const_cast<TTpcPID &>( rhs ).NHits)
   , NConstituents(const_cast<TTpcPID &>( rhs ).NConstituents)
   , isForward(const_cast<TTpcPID &>( rhs ).isForward)
   , Charge(const_cast<TTpcPID &>( rhs ).Charge)
   , EDeposit(const_cast<TTpcPID &>( rhs ).EDeposit)
   , Cone(const_cast<TTpcPID &>( rhs ).Cone)
   , Width(const_cast<TTpcPID &>( rhs ).Width)
   , Length(const_cast<TTpcPID &>( rhs ).Length)
   , Likelihoods(const_cast<TTpcPID &>( rhs ).Likelihoods)
   , FrontPosition(const_cast<TTpcPID &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TTpcPID &>( rhs ).BackPosition)
   , FrontPositionVar(const_cast<TTpcPID &>( rhs ).FrontPositionVar)
   , BackPositionVar(const_cast<TTpcPID &>( rhs ).BackPositionVar)
   , FrontDirection(const_cast<TTpcPID &>( rhs ).FrontDirection)
   , BackDirection(const_cast<TTpcPID &>( rhs ).BackDirection)
   , FrontDirectionVar(const_cast<TTpcPID &>( rhs ).FrontDirectionVar)
   , BackDirectionVar(const_cast<TTpcPID &>( rhs ).BackDirectionVar)
   , FrontMomentum(const_cast<TTpcPID &>( rhs ).FrontMomentum)
   , BackMomentum(const_cast<TTpcPID &>( rhs ).BackMomentum)
   , FrontMomentumError(const_cast<TTpcPID &>( rhs ).FrontMomentumError)
   , BackMomentumError(const_cast<TTpcPID &>( rhs ).BackMomentumError)
   , PositionAtTrueVertex(const_cast<TTpcPID &>( rhs ).PositionAtTrueVertex)
   , PositionVarAtTrueVertex(const_cast<TTpcPID &>( rhs ).PositionVarAtTrueVertex)
   , DirectionAtTrueVertex(const_cast<TTpcPID &>( rhs ).DirectionAtTrueVertex)
   , DirectionVarAtTrueVertex(const_cast<TTpcPID &>( rhs ).DirectionVarAtTrueVertex)
   , MomentumAtTrueVertex(const_cast<TTpcPID &>( rhs ).MomentumAtTrueVertex)
   , MomentumErrorAtTrueVertex(const_cast<TTpcPID &>( rhs ).MomentumErrorAtTrueVertex)
   , EntrancePosition(const_cast<TTpcPID &>( rhs ).EntrancePosition)
   , ExitPosition(const_cast<TTpcPID &>( rhs ).ExitPosition)
   , TrueParticle(const_cast<TTpcPID &>( rhs ).TrueParticle)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTpcPID &modrhs = const_cast<TTpcPID &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Likelihoods.clear();
   modrhs.EntrancePosition.clear();
   modrhs.ExitPosition.clear();
}
ND::TGlobalReconModule::TTpcPID::~TTpcPID() {
}
#endif // ND__TGlobalReconModule__TTpcPID_cxx

#ifndef ND__TTrueParticle_cxx
#define ND__TTrueParticle_cxx
ND::TTrueParticle::TTrueParticle() {
}
ND::TTrueParticle::TTrueParticle(const TTrueParticle & rhs)
   : TObject(const_cast<TTrueParticle &>( rhs ))
   , ID(const_cast<TTrueParticle &>( rhs ).ID)
   , Pur(const_cast<TTrueParticle &>( rhs ).Pur)
   , Eff(const_cast<TTrueParticle &>( rhs ).Eff)
   , Vertex(const_cast<TTrueParticle &>( rhs ).Vertex)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrueParticle::~TTrueParticle() {
}
#endif // ND__TTrueParticle_cxx

#ifndef ND__TGlobalReconModule__TGlobalVertex_cxx
#define ND__TGlobalReconModule__TGlobalVertex_cxx
ND::TGlobalReconModule::TGlobalVertex::TGlobalVertex() {
   TrueVertices = 0;
   Constituents = 0;
}
ND::TGlobalReconModule::TGlobalVertex::TGlobalVertex(const TGlobalVertex & rhs)
   : TObject(const_cast<TGlobalVertex &>( rhs ))
   , PrimaryIndex(const_cast<TGlobalVertex &>( rhs ).PrimaryIndex)
   , AlgorithmName(const_cast<TGlobalVertex &>( rhs ).AlgorithmName)
   , Status(const_cast<TGlobalVertex &>( rhs ).Status)
   , Quality(const_cast<TGlobalVertex &>( rhs ).Quality)
   , NDOF(const_cast<TGlobalVertex &>( rhs ).NDOF)
   , Position(const_cast<TGlobalVertex &>( rhs ).Position)
   , Variance(const_cast<TGlobalVertex &>( rhs ).Variance)
   , NTrueVertices(const_cast<TGlobalVertex &>( rhs ).NTrueVertices)
   , TrueVertices(const_cast<TGlobalVertex &>( rhs ).TrueVertices)
   , NConstituents(const_cast<TGlobalVertex &>( rhs ).NConstituents)
   , Constituents(const_cast<TGlobalVertex &>( rhs ).Constituents)
   , hackTrueVertexObject(const_cast<TGlobalVertex &>( rhs ).hackTrueVertexObject)
   , hackVertexConstituentObject(const_cast<TGlobalVertex &>( rhs ).hackVertexConstituentObject)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TGlobalVertex &modrhs = const_cast<TGlobalVertex &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.TrueVertices = 0;
   modrhs.Constituents = 0;
}
ND::TGlobalReconModule::TGlobalVertex::~TGlobalVertex() {
   delete TrueVertices;   TrueVertices = 0;
   delete Constituents;   Constituents = 0;
}
#endif // ND__TGlobalReconModule__TGlobalVertex_cxx

#ifndef ND__TGlobalReconModule__TVertexConstituent_cxx
#define ND__TGlobalReconModule__TVertexConstituent_cxx
ND::TGlobalReconModule::TVertexConstituent::TVertexConstituent() {
}
ND::TGlobalReconModule::TVertexConstituent::TVertexConstituent(const TVertexConstituent & rhs)
   : TObject(const_cast<TVertexConstituent &>( rhs ))
   , Charge(const_cast<TVertexConstituent &>( rhs ).Charge)
   , Quality(const_cast<TVertexConstituent &>( rhs ).Quality)
   , Momentum(const_cast<TVertexConstituent &>( rhs ).Momentum)
   , PID(const_cast<TVertexConstituent &>( rhs ).PID)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TVertexConstituent::~TVertexConstituent() {
}
#endif // ND__TGlobalReconModule__TVertexConstituent_cxx

#ifndef ND__TGlobalReconModule__TFgdTimeBin_cxx
#define ND__TGlobalReconModule__TFgdTimeBin_cxx
ND::TGlobalReconModule::TFgdTimeBin::TFgdTimeBin() {
   FGD1Unused = 0;
   FGD2Unused = 0;
}
ND::TGlobalReconModule::TFgdTimeBin::TFgdTimeBin(const TFgdTimeBin & rhs)
   : TObject(const_cast<TFgdTimeBin &>( rhs ))
   , minTime(const_cast<TFgdTimeBin &>( rhs ).minTime)
   , maxTime(const_cast<TFgdTimeBin &>( rhs ).maxTime)
   , FGD1OutermostHits(const_cast<TFgdTimeBin &>( rhs ).FGD1OutermostHits)
   , FGD2OutermostHits(const_cast<TFgdTimeBin &>( rhs ).FGD2OutermostHits)
   , FGD1HitLayer(const_cast<TFgdTimeBin &>( rhs ).FGD1HitLayer)
   , FGD1HitPosition(const_cast<TFgdTimeBin &>( rhs ).FGD1HitPosition)
   , FGD1HitQ(const_cast<TFgdTimeBin &>( rhs ).FGD1HitQ)
   , FGD1HitT(const_cast<TFgdTimeBin &>( rhs ).FGD1HitT)
   , FGD1HitTrajID(const_cast<TFgdTimeBin &>( rhs ).FGD1HitTrajID)
   , FGD2HitLayer(const_cast<TFgdTimeBin &>( rhs ).FGD2HitLayer)
   , FGD2HitPosition(const_cast<TFgdTimeBin &>( rhs ).FGD2HitPosition)
   , FGD2HitQ(const_cast<TFgdTimeBin &>( rhs ).FGD2HitQ)
   , FGD2HitT(const_cast<TFgdTimeBin &>( rhs ).FGD2HitT)
   , FGD2HitTrajID(const_cast<TFgdTimeBin &>( rhs ).FGD2HitTrajID)
   , NFGD1Unused(const_cast<TFgdTimeBin &>( rhs ).NFGD1Unused)
   , FGD1Unused(const_cast<TFgdTimeBin &>( rhs ).FGD1Unused)
   , NFGD2Unused(const_cast<TFgdTimeBin &>( rhs ).NFGD2Unused)
   , FGD2Unused(const_cast<TFgdTimeBin &>( rhs ).FGD2Unused)
   , g4ID(const_cast<TFgdTimeBin &>( rhs ).g4ID)
   , hackFGDUnused(const_cast<TFgdTimeBin &>( rhs ).hackFGDUnused)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<2;i++) nHits[i] = rhs.nHits[i];
   for (Int_t i=0;i<2;i++) rawChargeSum[i] = rhs.rawChargeSum[i];
   for (Int_t i=0;i<60;i++) (&(chargePerLayer[0][0]))[i] = (&(rhs.chargePerLayer[0][0]))[i];
   for (Int_t i=0;i<2;i++) chargeWeightedPos[i] = rhs.chargeWeightedPos[i];
   TFgdTimeBin &modrhs = const_cast<TFgdTimeBin &>( rhs );
   modrhs.FGD1HitLayer.clear();
   modrhs.FGD1HitPosition.clear();
   modrhs.FGD1HitQ.clear();
   modrhs.FGD1HitT.clear();
   modrhs.FGD1HitTrajID.clear();
   modrhs.FGD2HitLayer.clear();
   modrhs.FGD2HitPosition.clear();
   modrhs.FGD2HitQ.clear();
   modrhs.FGD2HitT.clear();
   modrhs.FGD2HitTrajID.clear();
   modrhs.FGD1Unused = 0;
   modrhs.FGD2Unused = 0;
}
ND::TGlobalReconModule::TFgdTimeBin::~TFgdTimeBin() {
   delete FGD1Unused;   FGD1Unused = 0;
   delete FGD2Unused;   FGD2Unused = 0;
}
#endif // ND__TGlobalReconModule__TFgdTimeBin_cxx

#ifndef ND__TGlobalReconModule__TOutermostHits_cxx
#define ND__TGlobalReconModule__TOutermostHits_cxx
ND::TGlobalReconModule::TOutermostHits::TOutermostHits() {
}
ND::TGlobalReconModule::TOutermostHits::TOutermostHits(const TOutermostHits & rhs)
   : TObject(const_cast<TOutermostHits &>( rhs ))
   , hitMinX(const_cast<TOutermostHits &>( rhs ).hitMinX)
   , hitMaxX(const_cast<TOutermostHits &>( rhs ).hitMaxX)
   , hitMinY(const_cast<TOutermostHits &>( rhs ).hitMinY)
   , hitMaxY(const_cast<TOutermostHits &>( rhs ).hitMaxY)
   , hitMinZ(const_cast<TOutermostHits &>( rhs ).hitMinZ)
   , hitMaxZ(const_cast<TOutermostHits &>( rhs ).hitMaxZ)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TOutermostHits::~TOutermostHits() {
}
#endif // ND__TGlobalReconModule__TOutermostHits_cxx

#ifndef ND__TGlobalReconModule__TGlobalHit_cxx
#define ND__TGlobalReconModule__TGlobalHit_cxx
ND::TGlobalReconModule::TGlobalHit::TGlobalHit() {
}
ND::TGlobalReconModule::TGlobalHit::TGlobalHit(const TGlobalHit & rhs)
   : TObject(const_cast<TGlobalHit &>( rhs ))
   , Charge(const_cast<TGlobalHit &>( rhs ).Charge)
   , Time(const_cast<TGlobalHit &>( rhs ).Time)
   , Position(const_cast<TGlobalHit &>( rhs ).Position)
   , PositionError(const_cast<TGlobalHit &>( rhs ).PositionError)
   , Type(const_cast<TGlobalHit &>( rhs ).Type)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TGlobalHit::~TGlobalHit() {
}
#endif // ND__TGlobalReconModule__TGlobalHit_cxx

#ifndef ND__TGlobalReconModule__TGlobalPID_cxx
#define ND__TGlobalReconModule__TGlobalPID_cxx
ND::TGlobalReconModule::TGlobalPID::TGlobalPID() {
   HitsSaved = 0;
   TRACKER = 0;
   TPC = 0;
   FGD = 0;
   ECAL = 0;
   P0DECAL = 0;
   P0D = 0;
   SMRD = 0;
   Alternates = 0;
}
ND::TGlobalReconModule::TGlobalPID::TGlobalPID(const TGlobalPID & rhs)
   : TObject(const_cast<TGlobalPID &>( rhs ))
   , UniqueID(const_cast<TGlobalPID &>( rhs ).UniqueID)
   , BrokenUniqueIDs(const_cast<TGlobalPID &>( rhs ).BrokenUniqueIDs)
   , AlgorithmName(const_cast<TGlobalPID &>( rhs ).AlgorithmName)
   , Detectors(const_cast<TGlobalPID &>( rhs ).Detectors)
   , Status(const_cast<TGlobalPID &>( rhs ).Status)
   , NDOF(const_cast<TGlobalPID &>( rhs ).NDOF)
   , Chi2(const_cast<TGlobalPID &>( rhs ).Chi2)
   , NNodes(const_cast<TGlobalPID &>( rhs ).NNodes)
   , NHits(const_cast<TGlobalPID &>( rhs ).NHits)
   , NConstituents(const_cast<TGlobalPID &>( rhs ).NConstituents)
   , isForward(const_cast<TGlobalPID &>( rhs ).isForward)
   , SenseOK(const_cast<TGlobalPID &>( rhs ).SenseOK)
   , IsCurvBack(const_cast<TGlobalPID &>( rhs ).IsCurvBack)
   , IsFgdECalIncremental(const_cast<TGlobalPID &>( rhs ).IsFgdECalIncremental)
   , Charge(const_cast<TGlobalPID &>( rhs ).Charge)
   , EDeposit(const_cast<TGlobalPID &>( rhs ).EDeposit)
   , Cone(const_cast<TGlobalPID &>( rhs ).Cone)
   , Width(const_cast<TGlobalPID &>( rhs ).Width)
   , Length(const_cast<TGlobalPID &>( rhs ).Length)
   , ParticleIds(const_cast<TGlobalPID &>( rhs ).ParticleIds)
   , PIDWeights(const_cast<TGlobalPID &>( rhs ).PIDWeights)
   , FrontPosition(const_cast<TGlobalPID &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TGlobalPID &>( rhs ).BackPosition)
   , FrontDirection(const_cast<TGlobalPID &>( rhs ).FrontDirection)
   , BackDirection(const_cast<TGlobalPID &>( rhs ).BackDirection)
   , FrontMomentum(const_cast<TGlobalPID &>( rhs ).FrontMomentum)
   , FrontCharge(const_cast<TGlobalPID &>( rhs ).FrontCharge)
   , BackMomentum(const_cast<TGlobalPID &>( rhs ).BackMomentum)
   , BackCharge(const_cast<TGlobalPID &>( rhs ).BackCharge)
   , FrontMomentumError(const_cast<TGlobalPID &>( rhs ).FrontMomentumError)
   , BackMomentumError(const_cast<TGlobalPID &>( rhs ).BackMomentumError)
   , RangeMomentumMuon(const_cast<TGlobalPID &>( rhs ).RangeMomentumMuon)
   , RangeMomentumMuonFlip(const_cast<TGlobalPID &>( rhs ).RangeMomentumMuonFlip)
   , RangeMomentumElectron(const_cast<TGlobalPID &>( rhs ).RangeMomentumElectron)
   , RangeMomentumElectronFlip(const_cast<TGlobalPID &>( rhs ).RangeMomentumElectronFlip)
   , RangeMomentumProton(const_cast<TGlobalPID &>( rhs ).RangeMomentumProton)
   , RangeMomentumProtonFlip(const_cast<TGlobalPID &>( rhs ).RangeMomentumProtonFlip)
   , NodeTimes(const_cast<TGlobalPID &>( rhs ).NodeTimes)
   , PositionAtTrueVertex(const_cast<TGlobalPID &>( rhs ).PositionAtTrueVertex)
   , DirectionAtTrueVertex(const_cast<TGlobalPID &>( rhs ).DirectionAtTrueVertex)
   , MomentumAtTrueVertex(const_cast<TGlobalPID &>( rhs ).MomentumAtTrueVertex)
   , MomentumErrorAtTrueVertex(const_cast<TGlobalPID &>( rhs ).MomentumErrorAtTrueVertex)
   , ChargeAtTrueVertex(const_cast<TGlobalPID &>( rhs ).ChargeAtTrueVertex)
   , NHitsSaved(const_cast<TGlobalPID &>( rhs ).NHitsSaved)
   , HitsSaved(const_cast<TGlobalPID &>( rhs ).HitsSaved)
   , TrueParticle(const_cast<TGlobalPID &>( rhs ).TrueParticle)
   , NTRACKERs(const_cast<TGlobalPID &>( rhs ).NTRACKERs)
   , TRACKER(const_cast<TGlobalPID &>( rhs ).TRACKER)
   , NTPCs(const_cast<TGlobalPID &>( rhs ).NTPCs)
   , TPC(const_cast<TGlobalPID &>( rhs ).TPC)
   , NFGDs(const_cast<TGlobalPID &>( rhs ).NFGDs)
   , FGD(const_cast<TGlobalPID &>( rhs ).FGD)
   , NECALs(const_cast<TGlobalPID &>( rhs ).NECALs)
   , NDsECALs(const_cast<TGlobalPID &>( rhs ).NDsECALs)
   , NTrECALs(const_cast<TGlobalPID &>( rhs ).NTrECALs)
   , ECAL(const_cast<TGlobalPID &>( rhs ).ECAL)
   , NP0DECALs(const_cast<TGlobalPID &>( rhs ).NP0DECALs)
   , P0DECAL(const_cast<TGlobalPID &>( rhs ).P0DECAL)
   , NP0Ds(const_cast<TGlobalPID &>( rhs ).NP0Ds)
   , P0D(const_cast<TGlobalPID &>( rhs ).P0D)
   , NSMRDs(const_cast<TGlobalPID &>( rhs ).NSMRDs)
   , SMRD(const_cast<TGlobalPID &>( rhs ).SMRD)
   , NAlternates(const_cast<TGlobalPID &>( rhs ).NAlternates)
   , Alternates(const_cast<TGlobalPID &>( rhs ).Alternates)
   , TPCGasPatternIDs(const_cast<TGlobalPID &>( rhs ).TPCGasPatternIDs)
   , TPCGasPathIDs(const_cast<TGlobalPID &>( rhs ).TPCGasPathIDs)
   , TPCGasJunctionIDs(const_cast<TGlobalPID &>( rhs ).TPCGasJunctionIDs)
   , hackTPCObject(const_cast<TGlobalPID &>( rhs ).hackTPCObject)
   , hackFGDObject(const_cast<TGlobalPID &>( rhs ).hackFGDObject)
   , hackECALObject(const_cast<TGlobalPID &>( rhs ).hackECALObject)
   , hackP0DObject(const_cast<TGlobalPID &>( rhs ).hackP0DObject)
   , hackSMRDObject(const_cast<TGlobalPID &>( rhs ).hackSMRDObject)
   , hackTrackerObject(const_cast<TGlobalPID &>( rhs ).hackTrackerObject)
   , hackGlobalPIDAlternate(const_cast<TGlobalPID &>( rhs ).hackGlobalPIDAlternate)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TGlobalPID &modrhs = const_cast<TGlobalPID &>( rhs );
   modrhs.BrokenUniqueIDs.clear();
   modrhs.AlgorithmName.clear();
   for (Int_t i=0;i<19;i++) DetectorUsed[i] = rhs.DetectorUsed[i];
   modrhs.ParticleIds.clear();
   modrhs.PIDWeights.clear();
   for (Int_t i=0;i<49;i++) (&(FrontStateCov[0][0]))[i] = (&(rhs.FrontStateCov[0][0]))[i];
   for (Int_t i=0;i<49;i++) (&(BackStateCov[0][0]))[i] = (&(rhs.BackStateCov[0][0]))[i];
   modrhs.NodeTimes.clear();
   for (Int_t i=0;i<49;i++) (&(StateCovAtTrueVertex[0][0]))[i] = (&(rhs.StateCovAtTrueVertex[0][0]))[i];
   for (Int_t i=0;i<25;i++) EntranceOK[i] = rhs.EntranceOK[i];
   for (Int_t i=0;i<25;i++) ExitOK[i] = rhs.ExitOK[i];
   for (Int_t i=0;i<25;i++) EntrancePosition[i] = rhs.EntrancePosition[i];
   for (Int_t i=0;i<25;i++) ExitPosition[i] = rhs.ExitPosition[i];
   for (Int_t i=0;i<25;i++) EntranceDirection[i] = rhs.EntranceDirection[i];
   for (Int_t i=0;i<25;i++) ExitDirection[i] = rhs.ExitDirection[i];
   for (Int_t i=0;i<25;i++) EntranceMomentum[i] = rhs.EntranceMomentum[i];
   for (Int_t i=0;i<25;i++) ExitMomentum[i] = rhs.ExitMomentum[i];
   for (Int_t i=0;i<25;i++) EntrancePositionErr[i] = rhs.EntrancePositionErr[i];
   for (Int_t i=0;i<25;i++) ExitPositionErr[i] = rhs.ExitPositionErr[i];
   for (Int_t i=0;i<25;i++) EntranceDirectionErr[i] = rhs.EntranceDirectionErr[i];
   for (Int_t i=0;i<25;i++) ExitDirectionErr[i] = rhs.ExitDirectionErr[i];
   for (Int_t i=0;i<25;i++) EntranceMomentumErr[i] = rhs.EntranceMomentumErr[i];
   for (Int_t i=0;i<25;i++) ExitMomentumErr[i] = rhs.ExitMomentumErr[i];
   modrhs.HitsSaved = 0;
   modrhs.TRACKER = 0;
   modrhs.TPC = 0;
   modrhs.FGD = 0;
   modrhs.ECAL = 0;
   modrhs.P0DECAL = 0;
   modrhs.P0D = 0;
   modrhs.SMRD = 0;
   modrhs.Alternates = 0;
   modrhs.TPCGasPatternIDs.clear();
   modrhs.TPCGasPathIDs.clear();
   modrhs.TPCGasJunctionIDs.clear();
}
ND::TGlobalReconModule::TGlobalPID::~TGlobalPID() {
   delete HitsSaved;   HitsSaved = 0;
   delete TRACKER;   TRACKER = 0;
   delete TPC;   TPC = 0;
   delete FGD;   FGD = 0;
   delete ECAL;   ECAL = 0;
   delete P0DECAL;   P0DECAL = 0;
   delete P0D;   P0D = 0;
   delete SMRD;   SMRD = 0;
   delete Alternates;   Alternates = 0;
}
#endif // ND__TGlobalReconModule__TGlobalPID_cxx

#ifndef ND__TGlobalReconModule__TTPCObject_cxx
#define ND__TGlobalReconModule__TTPCObject_cxx
ND::TGlobalReconModule::TTPCObject::TTPCObject() {
}
ND::TGlobalReconModule::TTPCObject::TTPCObject(const TTPCObject & rhs)
   : ND::TSubBaseObject(const_cast<TTPCObject &>( rhs ))
   , Charge(const_cast<TTPCObject &>( rhs ).Charge)
   , NTrun(const_cast<TTPCObject &>( rhs ).NTrun)
   , Ccorr(const_cast<TTPCObject &>( rhs ).Ccorr)
   , PullEle(const_cast<TTPCObject &>( rhs ).PullEle)
   , PullMuon(const_cast<TTPCObject &>( rhs ).PullMuon)
   , PullPion(const_cast<TTPCObject &>( rhs ).PullPion)
   , PullKaon(const_cast<TTPCObject &>( rhs ).PullKaon)
   , PullProton(const_cast<TTPCObject &>( rhs ).PullProton)
   , dEdxexpEle(const_cast<TTPCObject &>( rhs ).dEdxexpEle)
   , dEdxexpMuon(const_cast<TTPCObject &>( rhs ).dEdxexpMuon)
   , dEdxexpPion(const_cast<TTPCObject &>( rhs ).dEdxexpPion)
   , dEdxexpKaon(const_cast<TTPCObject &>( rhs ).dEdxexpKaon)
   , dEdxexpProton(const_cast<TTPCObject &>( rhs ).dEdxexpProton)
   , SigmaEle(const_cast<TTPCObject &>( rhs ).SigmaEle)
   , SigmaMuon(const_cast<TTPCObject &>( rhs ).SigmaMuon)
   , SigmaPion(const_cast<TTPCObject &>( rhs ).SigmaPion)
   , SigmaKaon(const_cast<TTPCObject &>( rhs ).SigmaKaon)
   , SigmaProton(const_cast<TTPCObject &>( rhs ).SigmaProton)
   , T0Source(const_cast<TTPCObject &>( rhs ).T0Source)
   , NHorRows(const_cast<TTPCObject &>( rhs ).NHorRows)
   , NVerRows(const_cast<TTPCObject &>( rhs ).NVerRows)
   , NbFittedVerticalClusters(const_cast<TTPCObject &>( rhs ).NbFittedVerticalClusters)
   , NbFittedHorizontalClusters(const_cast<TTPCObject &>( rhs ).NbFittedHorizontalClusters)
   , PDist(const_cast<TTPCObject &>( rhs ).PDist)
   , PEField(const_cast<TTPCObject &>( rhs ).PEField)
   , TPCLength(const_cast<TTPCObject &>( rhs ).TPCLength)
   , TrackType(const_cast<TTPCObject &>( rhs ).TrackType)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTPCObject &modrhs = const_cast<TTPCObject &>( rhs );
   modrhs.T0Source.clear();
   modrhs.NHorRows.clear();
   modrhs.NVerRows.clear();
}
ND::TGlobalReconModule::TTPCObject::~TTPCObject() {
}
#endif // ND__TGlobalReconModule__TTPCObject_cxx

#ifndef ND__TSubBaseObject_cxx
#define ND__TSubBaseObject_cxx
ND::TSubBaseObject::TSubBaseObject() {
}
ND::TSubBaseObject::TSubBaseObject(const TSubBaseObject & rhs)
   : TObject(const_cast<TSubBaseObject &>( rhs ))
   , UniqueID(const_cast<TSubBaseObject &>( rhs ).UniqueID)
   , Status(const_cast<TSubBaseObject &>( rhs ).Status)
   , Detector(const_cast<TSubBaseObject &>( rhs ).Detector)
   , NHits(const_cast<TSubBaseObject &>( rhs ).NHits)
   , NNodes(const_cast<TSubBaseObject &>( rhs ).NNodes)
   , NDOF(const_cast<TSubBaseObject &>( rhs ).NDOF)
   , Chi2(const_cast<TSubBaseObject &>( rhs ).Chi2)
   , EDeposit(const_cast<TSubBaseObject &>( rhs ).EDeposit)
   , NConstituents(const_cast<TSubBaseObject &>( rhs ).NConstituents)
   , Length(const_cast<TSubBaseObject &>( rhs ).Length)
   , FrontPosition(const_cast<TSubBaseObject &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TSubBaseObject &>( rhs ).BackPosition)
   , FrontPositionVar(const_cast<TSubBaseObject &>( rhs ).FrontPositionVar)
   , BackPositionVar(const_cast<TSubBaseObject &>( rhs ).BackPositionVar)
   , FrontDirection(const_cast<TSubBaseObject &>( rhs ).FrontDirection)
   , BackDirection(const_cast<TSubBaseObject &>( rhs ).BackDirection)
   , FrontDirectionVar(const_cast<TSubBaseObject &>( rhs ).FrontDirectionVar)
   , BackDirectionVar(const_cast<TSubBaseObject &>( rhs ).BackDirectionVar)
   , FrontMomentum(const_cast<TSubBaseObject &>( rhs ).FrontMomentum)
   , BackMomentum(const_cast<TSubBaseObject &>( rhs ).BackMomentum)
   , FrontMomentumError(const_cast<TSubBaseObject &>( rhs ).FrontMomentumError)
   , BackMomentumError(const_cast<TSubBaseObject &>( rhs ).BackMomentumError)
   , TrueParticle(const_cast<TSubBaseObject &>( rhs ).TrueParticle)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TSubBaseObject::~TSubBaseObject() {
}
#endif // ND__TSubBaseObject_cxx

#ifndef ND__TGlobalReconModule__TFGDObject_cxx
#define ND__TGlobalReconModule__TFGDObject_cxx
ND::TGlobalReconModule::TFGDObject::TFGDObject() {
}
ND::TGlobalReconModule::TFGDObject::TFGDObject(const TFGDObject & rhs)
   : ND::TSubBaseObject(const_cast<TFGDObject &>( rhs ))
   , avgtime(const_cast<TFGDObject &>( rhs ).avgtime)
   , fgdContainment(const_cast<TFGDObject &>( rhs ).fgdContainment)
   , E(const_cast<TFGDObject &>( rhs ).E)
   , x(const_cast<TFGDObject &>( rhs ).x)
   , E_exp_muon(const_cast<TFGDObject &>( rhs ).E_exp_muon)
   , E_exp_pion(const_cast<TFGDObject &>( rhs ).E_exp_pion)
   , E_exp_proton(const_cast<TFGDObject &>( rhs ).E_exp_proton)
   , E_exp_electron(const_cast<TFGDObject &>( rhs ).E_exp_electron)
   , sigmaE_muon(const_cast<TFGDObject &>( rhs ).sigmaE_muon)
   , sigmaE_pion(const_cast<TFGDObject &>( rhs ).sigmaE_pion)
   , sigmaE_proton(const_cast<TFGDObject &>( rhs ).sigmaE_proton)
   , sigmaE_electron(const_cast<TFGDObject &>( rhs ).sigmaE_electron)
   , PullMuon(const_cast<TFGDObject &>( rhs ).PullMuon)
   , PullPion(const_cast<TFGDObject &>( rhs ).PullPion)
   , PullProton(const_cast<TFGDObject &>( rhs ).PullProton)
   , PullElectron(const_cast<TFGDObject &>( rhs ).PullElectron)
   , PullNotSet(const_cast<TFGDObject &>( rhs ).PullNotSet)
   , isFgdVA(const_cast<TFGDObject &>( rhs ).isFgdVA)
   , isFgdVA_flag(const_cast<TFGDObject &>( rhs ).isFgdVA_flag)
   , globpassVA_flag(const_cast<TFGDObject &>( rhs ).globpassVA_flag)
   , fgdVA_upMinZ(const_cast<TFGDObject &>( rhs ).fgdVA_upMinZ)
   , fgdVA_downMaxZ(const_cast<TFGDObject &>( rhs ).fgdVA_downMaxZ)
   , fgdVA_upCosTheta(const_cast<TFGDObject &>( rhs ).fgdVA_upCosTheta)
   , fgdVA_downCosTheta(const_cast<TFGDObject &>( rhs ).fgdVA_downCosTheta)
   , fgdVA_otherUpQ(const_cast<TFGDObject &>( rhs ).fgdVA_otherUpQ)
   , fgdVA_otherDownQ(const_cast<TFGDObject &>( rhs ).fgdVA_otherDownQ)
   , fgdVA_verQ(const_cast<TFGDObject &>( rhs ).fgdVA_verQ)
   , fgdVA_verLayQ(const_cast<TFGDObject &>( rhs ).fgdVA_verLayQ)
   , fgdVA_verNearQ(const_cast<TFGDObject &>( rhs ).fgdVA_verNearQ)
   , fgdVA_verNextNearQ(const_cast<TFGDObject &>( rhs ).fgdVA_verNextNearQ)
   , fgdVA_verNextNextNearQ(const_cast<TFGDObject &>( rhs ).fgdVA_verNextNextNearQ)
   , fgdVA_verNearQ_rect(const_cast<TFGDObject &>( rhs ).fgdVA_verNearQ_rect)
   , fgdVA_verNextNearQ_rect(const_cast<TFGDObject &>( rhs ).fgdVA_verNextNearQ_rect)
   , fgdVA_verNextNextNearQ_rect(const_cast<TFGDObject &>( rhs ).fgdVA_verNextNextNearQ_rect)
   , fgdVA_totalQ(const_cast<TFGDObject &>( rhs ).fgdVA_totalQ)
   , fgdVA_totalCorrE(const_cast<TFGDObject &>( rhs ).fgdVA_totalCorrE)
   , isFgdEA(const_cast<TFGDObject &>( rhs ).isFgdEA)
   , isFgdEA_flag(const_cast<TFGDObject &>( rhs ).isFgdEA_flag)
   , globpassEA_flag(const_cast<TFGDObject &>( rhs ).globpassEA_flag)
   , fgdEA_otherUpQ(const_cast<TFGDObject &>( rhs ).fgdEA_otherUpQ)
   , fgdEA_otherDownQ(const_cast<TFGDObject &>( rhs ).fgdEA_otherDownQ)
   , fgdEA_verQ(const_cast<TFGDObject &>( rhs ).fgdEA_verQ)
   , fgdEA_verLayQ(const_cast<TFGDObject &>( rhs ).fgdEA_verLayQ)
   , fgdEA_verNearQ(const_cast<TFGDObject &>( rhs ).fgdEA_verNearQ)
   , fgdEA_verNextNearQ(const_cast<TFGDObject &>( rhs ).fgdEA_verNextNearQ)
   , fgdEA_verNextNextNearQ(const_cast<TFGDObject &>( rhs ).fgdEA_verNextNextNearQ)
   , fgdEA_verNearQ_rect(const_cast<TFGDObject &>( rhs ).fgdEA_verNearQ_rect)
   , fgdEA_verNextNearQ_rect(const_cast<TFGDObject &>( rhs ).fgdEA_verNextNearQ_rect)
   , fgdEA_verNextNextNearQ_rect(const_cast<TFGDObject &>( rhs ).fgdEA_verNextNextNearQ_rect)
   , fgdhits_Layer(const_cast<TFGDObject &>( rhs ).fgdhits_Layer)
   , fgdhits_Position(const_cast<TFGDObject &>( rhs ).fgdhits_Position)
   , fgdhits_Time(const_cast<TFGDObject &>( rhs ).fgdhits_Time)
   , fgdhits_Charge(const_cast<TFGDObject &>( rhs ).fgdhits_Charge)
   , fgdhits_TrajID(const_cast<TFGDObject &>( rhs ).fgdhits_TrajID)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<30;i++) chargePerLayer[i] = rhs.chargePerLayer[i];
   for (Int_t i=0;i<30;i++) chargePerLayerAttenCorr[i] = rhs.chargePerLayerAttenCorr[i];
   TFGDObject &modrhs = const_cast<TFGDObject &>( rhs );
   modrhs.fgdhits_Layer.clear();
   modrhs.fgdhits_Position.clear();
   modrhs.fgdhits_Time.clear();
   modrhs.fgdhits_Charge.clear();
   modrhs.fgdhits_TrajID.clear();
}
ND::TGlobalReconModule::TFGDObject::~TFGDObject() {
}
#endif // ND__TGlobalReconModule__TFGDObject_cxx

#ifndef ND__TGlobalReconModule__TECALObject_cxx
#define ND__TGlobalReconModule__TECALObject_cxx
ND::TGlobalReconModule::TECALObject::TECALObject() {
}
ND::TGlobalReconModule::TECALObject::TECALObject(const TECALObject & rhs)
   : ND::TSubBaseShowerObject(const_cast<TECALObject &>( rhs ))
   , LLR_MIP_EM(const_cast<TECALObject &>( rhs ).LLR_MIP_EM)
   , LLR_MIP_Pion(const_cast<TECALObject &>( rhs ).LLR_MIP_Pion)
   , LLR_EM_HIP(const_cast<TECALObject &>( rhs ).LLR_EM_HIP)
   , LLR_MIP_EM_LowMomentum(const_cast<TECALObject &>( rhs ).LLR_MIP_EM_LowMomentum)
   , LLR_MIP_HIP_VACut(const_cast<TECALObject &>( rhs ).LLR_MIP_HIP_VACut)
   , AverageHitTime(const_cast<TECALObject &>( rhs ).AverageHitTime)
   , AverageZPosition(const_cast<TECALObject &>( rhs ).AverageZPosition)
   , EMEnergyFit_Result(const_cast<TECALObject &>( rhs ).EMEnergyFit_Result)
   , EMEnergyFit_Uncertainty(const_cast<TECALObject &>( rhs ).EMEnergyFit_Uncertainty)
   , FilledAsType(const_cast<TECALObject &>( rhs ).FilledAsType)
   , PID_Circularity(const_cast<TECALObject &>( rhs ).PID_Circularity)
   , PID_Angle(const_cast<TECALObject &>( rhs ).PID_Angle)
   , PID_ShowerAngle(const_cast<TECALObject &>( rhs ).PID_ShowerAngle)
   , PID_Asymmetry(const_cast<TECALObject &>( rhs ).PID_Asymmetry)
   , PID_TruncatedMaxRatio(const_cast<TECALObject &>( rhs ).PID_TruncatedMaxRatio)
   , PID_TransverseChargeRatio(const_cast<TECALObject &>( rhs ).PID_TransverseChargeRatio)
   , PID_FrontBackRatio(const_cast<TECALObject &>( rhs ).PID_FrontBackRatio)
   , Containment(const_cast<TECALObject &>( rhs ).Containment)
   , Thrust(const_cast<TECALObject &>( rhs ).Thrust)
   , ThrustOrigin(const_cast<TECALObject &>( rhs ).ThrustOrigin)
   , ThrustAxis(const_cast<TECALObject &>( rhs ).ThrustAxis)
   , InnerMostLayerHit(const_cast<TECALObject &>( rhs ).InnerMostLayerHit)
   , OuterMostLayerHit(const_cast<TECALObject &>( rhs ).OuterMostLayerHit)
   , Width(const_cast<TECALObject &>( rhs ).Width)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TECALObject::~TECALObject() {
}
#endif // ND__TGlobalReconModule__TECALObject_cxx

#ifndef ND__TSubBaseShowerObject_cxx
#define ND__TSubBaseShowerObject_cxx
ND::TSubBaseShowerObject::TSubBaseShowerObject() {
}
ND::TSubBaseShowerObject::TSubBaseShowerObject(const TSubBaseShowerObject & rhs)
   : ND::TSubBaseObject(const_cast<TSubBaseShowerObject &>( rhs ))
   , Cone(const_cast<TSubBaseShowerObject &>( rhs ).Cone)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TSubBaseShowerObject::~TSubBaseShowerObject() {
}
#endif // ND__TSubBaseShowerObject_cxx

#ifndef ND__TGlobalReconModule__TP0DObject_cxx
#define ND__TGlobalReconModule__TP0DObject_cxx
ND::TGlobalReconModule::TP0DObject::TP0DObject() {
}
ND::TGlobalReconModule::TP0DObject::TP0DObject(const TP0DObject & rhs)
   : ND::TSubBaseShowerObject(const_cast<TP0DObject &>( rhs ))
   , Width(const_cast<TP0DObject &>( rhs ).Width)
   , avgtime(const_cast<TP0DObject &>( rhs ).avgtime)
   , ParticleId(const_cast<TP0DObject &>( rhs ).ParticleId)
   , PIDWeight(const_cast<TP0DObject &>( rhs ).PIDWeight)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DObject &modrhs = const_cast<TP0DObject &>( rhs );
   modrhs.ParticleId.clear();
   modrhs.PIDWeight.clear();
}
ND::TGlobalReconModule::TP0DObject::~TP0DObject() {
}
#endif // ND__TGlobalReconModule__TP0DObject_cxx

#ifndef ND__TGlobalReconModule__TSMRDObject_cxx
#define ND__TGlobalReconModule__TSMRDObject_cxx
ND::TGlobalReconModule::TSMRDObject::TSMRDObject() {
}
ND::TGlobalReconModule::TSMRDObject::TSMRDObject(const TSMRDObject & rhs)
   : ND::TSubBaseObject(const_cast<TSMRDObject &>( rhs ))
   , avgtime(const_cast<TSMRDObject &>( rhs ).avgtime)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TSMRDObject::~TSMRDObject() {
}
#endif // ND__TGlobalReconModule__TSMRDObject_cxx

#ifndef ND__TGlobalReconModule__TTrackerObject_cxx
#define ND__TGlobalReconModule__TTrackerObject_cxx
ND::TGlobalReconModule::TTrackerObject::TTrackerObject() {
}
ND::TGlobalReconModule::TTrackerObject::TTrackerObject(const TTrackerObject & rhs)
   : ND::TSubBaseObject(const_cast<TTrackerObject &>( rhs ))
   , Charge(const_cast<TTrackerObject &>( rhs ).Charge)
   , matchingFailure_flag(const_cast<TTrackerObject &>( rhs ).matchingFailure_flag)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TTrackerObject::~TTrackerObject() {
}
#endif // ND__TGlobalReconModule__TTrackerObject_cxx

#ifndef ND__TGlobalReconModule__TGlobalPIDAlternate_cxx
#define ND__TGlobalReconModule__TGlobalPIDAlternate_cxx
ND::TGlobalReconModule::TGlobalPIDAlternate::TGlobalPIDAlternate() {
}
ND::TGlobalReconModule::TGlobalPIDAlternate::TGlobalPIDAlternate(const TGlobalPIDAlternate & rhs)
   : TObject(const_cast<TGlobalPIDAlternate &>( rhs ))
   , Detectors(const_cast<TGlobalPIDAlternate &>( rhs ).Detectors)
   , Status(const_cast<TGlobalPIDAlternate &>( rhs ).Status)
   , NDOF(const_cast<TGlobalPIDAlternate &>( rhs ).NDOF)
   , Chi2(const_cast<TGlobalPIDAlternate &>( rhs ).Chi2)
   , Charge(const_cast<TGlobalPIDAlternate &>( rhs ).Charge)
   , Length(const_cast<TGlobalPIDAlternate &>( rhs ).Length)
   , ParticleId(const_cast<TGlobalPIDAlternate &>( rhs ).ParticleId)
   , PIDWeight(const_cast<TGlobalPIDAlternate &>( rhs ).PIDWeight)
   , FrontPosition(const_cast<TGlobalPIDAlternate &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TGlobalPIDAlternate &>( rhs ).BackPosition)
   , FrontPositionVar(const_cast<TGlobalPIDAlternate &>( rhs ).FrontPositionVar)
   , BackPositionVar(const_cast<TGlobalPIDAlternate &>( rhs ).BackPositionVar)
   , FrontDirection(const_cast<TGlobalPIDAlternate &>( rhs ).FrontDirection)
   , BackDirection(const_cast<TGlobalPIDAlternate &>( rhs ).BackDirection)
   , FrontDirectionVar(const_cast<TGlobalPIDAlternate &>( rhs ).FrontDirectionVar)
   , BackDirectionVar(const_cast<TGlobalPIDAlternate &>( rhs ).BackDirectionVar)
   , FrontMomentum(const_cast<TGlobalPIDAlternate &>( rhs ).FrontMomentum)
   , BackMomentum(const_cast<TGlobalPIDAlternate &>( rhs ).BackMomentum)
   , FrontMomentumError(const_cast<TGlobalPIDAlternate &>( rhs ).FrontMomentumError)
   , BackMomentumError(const_cast<TGlobalPIDAlternate &>( rhs ).BackMomentumError)
   , PositionAtTrueVertex(const_cast<TGlobalPIDAlternate &>( rhs ).PositionAtTrueVertex)
   , PositionVarAtTrueVertex(const_cast<TGlobalPIDAlternate &>( rhs ).PositionVarAtTrueVertex)
   , DirectionAtTrueVertex(const_cast<TGlobalPIDAlternate &>( rhs ).DirectionAtTrueVertex)
   , DirectionVarAtTrueVertex(const_cast<TGlobalPIDAlternate &>( rhs ).DirectionVarAtTrueVertex)
   , MomentumAtTrueVertex(const_cast<TGlobalPIDAlternate &>( rhs ).MomentumAtTrueVertex)
   , MomentumErrorAtTrueVertex(const_cast<TGlobalPIDAlternate &>( rhs ).MomentumErrorAtTrueVertex)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<19;i++) DetectorUsed[i] = rhs.DetectorUsed[i];
}
ND::TGlobalReconModule::TGlobalPIDAlternate::~TGlobalPIDAlternate() {
}
#endif // ND__TGlobalReconModule__TGlobalPIDAlternate_cxx

#ifndef ND__TGlobalReconModule__TTPCOtherObject_cxx
#define ND__TGlobalReconModule__TTPCOtherObject_cxx
ND::TGlobalReconModule::TTPCOtherObject::TTPCOtherObject() {
}
ND::TGlobalReconModule::TTPCOtherObject::TTPCOtherObject(const TTPCOtherObject & rhs)
   : TObject(const_cast<TTPCOtherObject &>( rhs ))
   , Charge(const_cast<TTPCOtherObject &>( rhs ).Charge)
   , Detector(const_cast<TTPCOtherObject &>( rhs ).Detector)
   , NHits(const_cast<TTPCOtherObject &>( rhs ).NHits)
   , Chi2(const_cast<TTPCOtherObject &>( rhs ).Chi2)
   , EDeposit(const_cast<TTPCOtherObject &>( rhs ).EDeposit)
   , FrontPosition(const_cast<TTPCOtherObject &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TTPCOtherObject &>( rhs ).BackPosition)
   , FrontDirection(const_cast<TTPCOtherObject &>( rhs ).FrontDirection)
   , BackDirection(const_cast<TTPCOtherObject &>( rhs ).BackDirection)
   , Momentum(const_cast<TTPCOtherObject &>( rhs ).Momentum)
   , TrueParticle(const_cast<TTPCOtherObject &>( rhs ).TrueParticle)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TTPCOtherObject::~TTPCOtherObject() {
}
#endif // ND__TGlobalReconModule__TTPCOtherObject_cxx

#ifndef ND__TGlobalReconModule__TSMRDHit_cxx
#define ND__TGlobalReconModule__TSMRDHit_cxx
ND::TGlobalReconModule::TSMRDHit::TSMRDHit() {
}
ND::TGlobalReconModule::TSMRDHit::TSMRDHit(const TSMRDHit & rhs)
   : TObject(const_cast<TSMRDHit &>( rhs ))
   , Wall(const_cast<TSMRDHit &>( rhs ).Wall)
   , Yoke(const_cast<TSMRDHit &>( rhs ).Yoke)
   , Layer(const_cast<TSMRDHit &>( rhs ).Layer)
   , Tower(const_cast<TSMRDHit &>( rhs ).Tower)
   , Counter(const_cast<TSMRDHit &>( rhs ).Counter)
   , Charge(const_cast<TSMRDHit &>( rhs ).Charge)
   , Time(const_cast<TSMRDHit &>( rhs ).Time)
   , Position(const_cast<TSMRDHit &>( rhs ).Position)
   , PositionError(const_cast<TSMRDHit &>( rhs ).PositionError)
   , Type(const_cast<TSMRDHit &>( rhs ).Type)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TGlobalReconModule::TSMRDHit::~TSMRDHit() {
}
#endif // ND__TGlobalReconModule__TSMRDHit_cxx

#ifndef ND__TTrackerECALReconModule__TECALReconObject_cxx
#define ND__TTrackerECALReconModule__TECALReconObject_cxx
ND::TTrackerECALReconModule::TECALReconObject::TECALReconObject() {
}
ND::TTrackerECALReconModule::TECALReconObject::TECALReconObject(const TECALReconObject & rhs)
   : TObject(const_cast<TECALReconObject &>( rhs ))
   , FilledAsTrack(const_cast<TECALReconObject &>( rhs ).FilledAsTrack)
   , FilledAsShower(const_cast<TECALReconObject &>( rhs ).FilledAsShower)
   , Track(const_cast<TECALReconObject &>( rhs ).Track)
   , Shower(const_cast<TECALReconObject &>( rhs ).Shower)
   , Cluster(const_cast<TECALReconObject &>( rhs ).Cluster)
   , UniqueID(const_cast<TECALReconObject &>( rhs ).UniqueID)
   , G4ID(const_cast<TECALReconObject &>( rhs ).G4ID)
   , G4ID_Primary(const_cast<TECALReconObject &>( rhs ).G4ID_Primary)
   , Completeness_Primary(const_cast<TECALReconObject &>( rhs ).Completeness_Primary)
   , Cleanliness_Primary(const_cast<TECALReconObject &>( rhs ).Cleanliness_Primary)
   , G4ID_Recursive(const_cast<TECALReconObject &>( rhs ).G4ID_Recursive)
   , G4ID_Recursive2(const_cast<TECALReconObject &>( rhs ).G4ID_Recursive2)
   , G4ID_Recursive3(const_cast<TECALReconObject &>( rhs ).G4ID_Recursive3)
   , G4ID_Recursive4(const_cast<TECALReconObject &>( rhs ).G4ID_Recursive4)
   , Completeness_Recursive(const_cast<TECALReconObject &>( rhs ).Completeness_Recursive)
   , Cleanliness_Recursive(const_cast<TECALReconObject &>( rhs ).Cleanliness_Recursive)
   , G4ID_Single(const_cast<TECALReconObject &>( rhs ).G4ID_Single)
   , Completeness_Single(const_cast<TECALReconObject &>( rhs ).Completeness_Single)
   , Cleanliness_Single(const_cast<TECALReconObject &>( rhs ).Cleanliness_Single)
   , NHits(const_cast<TECALReconObject &>( rhs ).NHits)
   , NIsXHits(const_cast<TECALReconObject &>( rhs ).NIsXHits)
   , NIsYHits(const_cast<TECALReconObject &>( rhs ).NIsYHits)
   , NIsZHits(const_cast<TECALReconObject &>( rhs ).NIsZHits)
   , NLayersHit(const_cast<TECALReconObject &>( rhs ).NLayersHit)
   , MaxPerpBarHit(const_cast<TECALReconObject &>( rhs ).MaxPerpBarHit)
   , MaxParaBarHit(const_cast<TECALReconObject &>( rhs ).MaxParaBarHit)
   , MinBarHit(const_cast<TECALReconObject &>( rhs ).MinBarHit)
   , MostUpStreamLayerHit(const_cast<TECALReconObject &>( rhs ).MostUpStreamLayerHit)
   , MostDownStreamLayerHit(const_cast<TECALReconObject &>( rhs ).MostDownStreamLayerHit)
   , TotalHitCharge(const_cast<TECALReconObject &>( rhs ).TotalHitCharge)
   , AverageHitTime(const_cast<TECALReconObject &>( rhs ).AverageHitTime)
   , Module(const_cast<TECALReconObject &>( rhs ).Module)
   , ObjectLength(const_cast<TECALReconObject &>( rhs ).ObjectLength)
   , PID_Circularity(const_cast<TECALReconObject &>( rhs ).PID_Circularity)
   , PID_Angle(const_cast<TECALReconObject &>( rhs ).PID_Angle)
   , PID_ShowerAngle(const_cast<TECALReconObject &>( rhs ).PID_ShowerAngle)
   , PID_Asymmetry(const_cast<TECALReconObject &>( rhs ).PID_Asymmetry)
   , PID_TruncatedMaxRatio(const_cast<TECALReconObject &>( rhs ).PID_TruncatedMaxRatio)
   , PID_TransverseChargeRatio(const_cast<TECALReconObject &>( rhs ).PID_TransverseChargeRatio)
   , PID_FrontBackRatio(const_cast<TECALReconObject &>( rhs ).PID_FrontBackRatio)
   , Containment(const_cast<TECALReconObject &>( rhs ).Containment)
   , PID_LLR_MIP_EM(const_cast<TECALReconObject &>( rhs ).PID_LLR_MIP_EM)
   , PID_LLR_MIP_Pion(const_cast<TECALReconObject &>( rhs ).PID_LLR_MIP_Pion)
   , PID_LLR_EM_HIP(const_cast<TECALReconObject &>( rhs ).PID_LLR_EM_HIP)
   , PID_LLR_MIP_EM_LowMomentum(const_cast<TECALReconObject &>( rhs ).PID_LLR_MIP_EM_LowMomentum)
   , AverageZPosition(const_cast<TECALReconObject &>( rhs ).AverageZPosition)
   , EMEnergyFit_Result(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Result)
   , EMEnergyFit_Uncertainty(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Uncertainty)
   , EMEnergyFit_Likelihood_energyGrad(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Likelihood_energyGrad)
   , EMEnergyFit_Likelihood_energy_qsumGrad(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Likelihood_energy_qsumGrad)
   , EMEnergyFit_Likelihood_qsum_like(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Likelihood_qsum_like)
   , EMEnergyFit_Para_QSum(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Para_QSum)
   , EMEnergyFit_Para_QMean(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Para_QMean)
   , EMEnergyFit_Para_QRMS(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Para_QRMS)
   , EMEnergyFit_Para_QSkew(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Para_QSkew)
   , EMEnergyFit_Para_QMax(const_cast<TECALReconObject &>( rhs ).EMEnergyFit_Para_QMax)
   , Thrust(const_cast<TECALReconObject &>( rhs ).Thrust)
   , ThrustOrigin(const_cast<TECALReconObject &>( rhs ).ThrustOrigin)
   , ThrustAxis(const_cast<TECALReconObject &>( rhs ).ThrustAxis)
   , MatchingLikelihood(const_cast<TECALReconObject &>( rhs ).MatchingLikelihood)
   , NHitsAtLayersWithManyHits(const_cast<TECALReconObject &>( rhs ).NHitsAtLayersWithManyHits)
   , NLayersTwoHits(const_cast<TECALReconObject &>( rhs ).NLayersTwoHits)
   , NLayersThreeHits(const_cast<TECALReconObject &>( rhs ).NLayersThreeHits)
   , FirstLayerManyHits(const_cast<TECALReconObject &>( rhs ).FirstLayerManyHits)
   , LastLayerManyHits(const_cast<TECALReconObject &>( rhs ).LastLayerManyHits)
   , MaxHitsInALayer(const_cast<TECALReconObject &>( rhs ).MaxHitsInALayer)
   , MaxHitChargeLayer(const_cast<TECALReconObject &>( rhs ).MaxHitChargeLayer)
   , Clustering_3DSeedType(const_cast<TECALReconObject &>( rhs ).Clustering_3DSeedType)
   , Pointing(const_cast<TECALReconObject &>( rhs ).Pointing)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TECALReconObject &modrhs = const_cast<TECALReconObject &>( rhs );
   modrhs.Module.clear();
}
ND::TTrackerECALReconModule::TECALReconObject::~TECALReconObject() {
}
#endif // ND__TTrackerECALReconModule__TECALReconObject_cxx

#ifndef ND__TTrackerECALReconModule__TECALReconTrack_cxx
#define ND__TTrackerECALReconModule__TECALReconTrack_cxx
ND::TTrackerECALReconModule::TECALReconTrack::TECALReconTrack() {
}
ND::TTrackerECALReconModule::TECALReconTrack::TECALReconTrack(const TECALReconTrack & rhs)
   : TObject(const_cast<TECALReconTrack &>( rhs ))
   , Direction(const_cast<TECALReconTrack &>( rhs ).Direction)
   , EDeposit(const_cast<TECALReconTrack &>( rhs ).EDeposit)
   , Position(const_cast<TECALReconTrack &>( rhs ).Position)
   , PositionVar(const_cast<TECALReconTrack &>( rhs ).PositionVar)
   , BackPosition(const_cast<TECALReconTrack &>( rhs ).BackPosition)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerECALReconModule::TECALReconTrack::~TECALReconTrack() {
}
#endif // ND__TTrackerECALReconModule__TECALReconTrack_cxx

#ifndef ND__TTrackerECALReconModule__TECALReconShower_cxx
#define ND__TTrackerECALReconModule__TECALReconShower_cxx
ND::TTrackerECALReconModule::TECALReconShower::TECALReconShower() {
}
ND::TTrackerECALReconModule::TECALReconShower::TECALReconShower(const TECALReconShower & rhs)
   : TObject(const_cast<TECALReconShower &>( rhs ))
   , ConeAngle(const_cast<TECALReconShower &>( rhs ).ConeAngle)
   , Direction(const_cast<TECALReconShower &>( rhs ).Direction)
   , EDeposit(const_cast<TECALReconShower &>( rhs ).EDeposit)
   , Position(const_cast<TECALReconShower &>( rhs ).Position)
   , PositionVar(const_cast<TECALReconShower &>( rhs ).PositionVar)
   , BackPosition(const_cast<TECALReconShower &>( rhs ).BackPosition)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerECALReconModule::TECALReconShower::~TECALReconShower() {
}
#endif // ND__TTrackerECALReconModule__TECALReconShower_cxx

#ifndef ND__TTrackerECALReconModule__TECALReconCluster_cxx
#define ND__TTrackerECALReconModule__TECALReconCluster_cxx
ND::TTrackerECALReconModule::TECALReconCluster::TECALReconCluster() {
}
ND::TTrackerECALReconModule::TECALReconCluster::TECALReconCluster(const TECALReconCluster & rhs)
   : TObject(const_cast<TECALReconCluster &>( rhs ))
   , Position(const_cast<TECALReconCluster &>( rhs ).Position)
   , PositionVar(const_cast<TECALReconCluster &>( rhs ).PositionVar)
   , NDOF(const_cast<TECALReconCluster &>( rhs ).NDOF)
   , EDeposit(const_cast<TECALReconCluster &>( rhs ).EDeposit)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerECALReconModule::TECALReconCluster::~TECALReconCluster() {
}
#endif // ND__TTrackerECALReconModule__TECALReconCluster_cxx

#ifndef ND__TTrackerECALReconModule__TECALReconUnmatchedObject_cxx
#define ND__TTrackerECALReconModule__TECALReconUnmatchedObject_cxx
ND::TTrackerECALReconModule::TECALReconUnmatchedObject::TECALReconUnmatchedObject() {
}
ND::TTrackerECALReconModule::TECALReconUnmatchedObject::TECALReconUnmatchedObject(const TECALReconUnmatchedObject & rhs)
   : TObject(const_cast<TECALReconUnmatchedObject &>( rhs ))
   , NHits(const_cast<TECALReconUnmatchedObject &>( rhs ).NHits)
   , View(const_cast<TECALReconUnmatchedObject &>( rhs ).View)
   , TotalHitCharge(const_cast<TECALReconUnmatchedObject &>( rhs ).TotalHitCharge)
   , AverageHitTime(const_cast<TECALReconUnmatchedObject &>( rhs ).AverageHitTime)
   , FrontPosition(const_cast<TECALReconUnmatchedObject &>( rhs ).FrontPosition)
   , BackPosition(const_cast<TECALReconUnmatchedObject &>( rhs ).BackPosition)
   , MostUpStreamLayerHit(const_cast<TECALReconUnmatchedObject &>( rhs ).MostUpStreamLayerHit)
   , MostDownStreamLayerHit(const_cast<TECALReconUnmatchedObject &>( rhs ).MostDownStreamLayerHit)
   , G4ID(const_cast<TECALReconUnmatchedObject &>( rhs ).G4ID)
   , G4ID_Primary(const_cast<TECALReconUnmatchedObject &>( rhs ).G4ID_Primary)
   , G4ID_Recursive(const_cast<TECALReconUnmatchedObject &>( rhs ).G4ID_Recursive)
   , G4ID_Single(const_cast<TECALReconUnmatchedObject &>( rhs ).G4ID_Single)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerECALReconModule::TECALReconUnmatchedObject::~TECALReconUnmatchedObject() {
}
#endif // ND__TTrackerECALReconModule__TECALReconUnmatchedObject_cxx

#ifndef ND__TTrackerECALReconModule__TECALReconVertexCandidate_cxx
#define ND__TTrackerECALReconModule__TECALReconVertexCandidate_cxx
ND::TTrackerECALReconModule::TECALReconVertexCandidate::TECALReconVertexCandidate() {
   TrackUIDs = 0;
}
ND::TTrackerECALReconModule::TECALReconVertexCandidate::TECALReconVertexCandidate(const TECALReconVertexCandidate & rhs)
   : TObject(const_cast<TECALReconVertexCandidate &>( rhs ))
   , VertexClusterUID(const_cast<TECALReconVertexCandidate &>( rhs ).VertexClusterUID)
   , Position(const_cast<TECALReconVertexCandidate &>( rhs ).Position)
   , ECalModule(const_cast<TECALReconVertexCandidate &>( rhs ).ECalModule)
   , NTracks(const_cast<TECALReconVertexCandidate &>( rhs ).NTracks)
   , NHits(const_cast<TECALReconVertexCandidate &>( rhs ).NHits)
   , G4IDSingle(const_cast<TECALReconVertexCandidate &>( rhs ).G4IDSingle)
   , CompletenessSingle(const_cast<TECALReconVertexCandidate &>( rhs ).CompletenessSingle)
   , CleanlinessSingle(const_cast<TECALReconVertexCandidate &>( rhs ).CleanlinessSingle)
   , G4IDPrimary(const_cast<TECALReconVertexCandidate &>( rhs ).G4IDPrimary)
   , CompletenessPrimary(const_cast<TECALReconVertexCandidate &>( rhs ).CompletenessPrimary)
   , CleanlinessPrimary(const_cast<TECALReconVertexCandidate &>( rhs ).CleanlinessPrimary)
   , G4IDRecursive(const_cast<TECALReconVertexCandidate &>( rhs ).G4IDRecursive)
   , CompletenessRecursive(const_cast<TECALReconVertexCandidate &>( rhs ).CompletenessRecursive)
   , CleanlinessRecursive(const_cast<TECALReconVertexCandidate &>( rhs ).CleanlinessRecursive)
   , TrackUIDs(const_cast<TECALReconVertexCandidate &>( rhs ).TrackUIDs)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TECALReconVertexCandidate &modrhs = const_cast<TECALReconVertexCandidate &>( rhs );
   modrhs.ECalModule.clear();
   modrhs.TrackUIDs = 0;
}
ND::TTrackerECALReconModule::TECALReconVertexCandidate::~TECALReconVertexCandidate() {
   delete [] TrackUIDs;   TrackUIDs = 0;
}
#endif // ND__TTrackerECALReconModule__TECALReconVertexCandidate_cxx

#ifndef ND__TTrackerECALReconModule__TECALReconVertexTrack_cxx
#define ND__TTrackerECALReconModule__TECALReconVertexTrack_cxx
ND::TTrackerECALReconModule::TECALReconVertexTrack::TECALReconVertexTrack() {
}
ND::TTrackerECALReconModule::TECALReconVertexTrack::TECALReconVertexTrack(const TECALReconVertexTrack & rhs)
   : TObject(const_cast<TECALReconVertexTrack &>( rhs ))
   , Status(const_cast<TECALReconVertexTrack &>( rhs ).Status)
   , UniqueID(const_cast<TECALReconVertexTrack &>( rhs ).UniqueID)
   , NHits(const_cast<TECALReconVertexTrack &>( rhs ).NHits)
   , MatchingLikelihood(const_cast<TECALReconVertexTrack &>( rhs ).MatchingLikelihood)
   , FrontPosition(const_cast<TECALReconVertexTrack &>( rhs ).FrontPosition)
   , FrontDirection(const_cast<TECALReconVertexTrack &>( rhs ).FrontDirection)
   , FrontLayerNumber(const_cast<TECALReconVertexTrack &>( rhs ).FrontLayerNumber)
   , BackPosition(const_cast<TECALReconVertexTrack &>( rhs ).BackPosition)
   , BackDirection(const_cast<TECALReconVertexTrack &>( rhs ).BackDirection)
   , BackLayerNumber(const_cast<TECALReconVertexTrack &>( rhs ).BackLayerNumber)
   , TotalCharge(const_cast<TECALReconVertexTrack &>( rhs ).TotalCharge)
   , StraightTrackLength(const_cast<TECALReconVertexTrack &>( rhs ).StraightTrackLength)
   , NodeTrackLength(const_cast<TECALReconVertexTrack &>( rhs ).NodeTrackLength)
   , AverageHitTime(const_cast<TECALReconVertexTrack &>( rhs ).AverageHitTime)
   , G4IDSingle(const_cast<TECALReconVertexTrack &>( rhs ).G4IDSingle)
   , PID_LLR_MIP_EM(const_cast<TECALReconVertexTrack &>( rhs ).PID_LLR_MIP_EM)
   , PID_LLR_EM_HIP(const_cast<TECALReconVertexTrack &>( rhs ).PID_LLR_EM_HIP)
   , PID_LLR_MIP_HIP(const_cast<TECALReconVertexTrack &>( rhs ).PID_LLR_MIP_HIP)
   , PID_LLR_MIP_HIP_VACut(const_cast<TECALReconVertexTrack &>( rhs ).PID_LLR_MIP_HIP_VACut)
   , Containment(const_cast<TECALReconVertexTrack &>( rhs ).Containment)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTrackerECALReconModule::TECALReconVertexTrack::~TECALReconVertexTrack() {
}
#endif // ND__TTrackerECALReconModule__TECALReconVertexTrack_cxx


#ifndef ND__TP0DECALReconModule__TP0DECALReconTrack_cxx
#define ND__TP0DECALReconModule__TP0DECALReconTrack_cxx
ND::TP0DECALReconModule::TP0DECALReconTrack::TP0DECALReconTrack() {
}
ND::TP0DECALReconModule::TP0DECALReconTrack::TP0DECALReconTrack(const TP0DECALReconTrack & rhs)
   : TObject(const_cast<TP0DECALReconTrack &>( rhs ))
   , UniqueID(const_cast<TP0DECALReconTrack &>( rhs ).UniqueID)
   , Curvature(const_cast<TP0DECALReconTrack &>( rhs ).Curvature)
   , Direction(const_cast<TP0DECALReconTrack &>( rhs ).Direction)
   , EDeposit(const_cast<TP0DECALReconTrack &>( rhs ).EDeposit)
   , NDOF(const_cast<TP0DECALReconTrack &>( rhs ).NDOF)
   , Position(const_cast<TP0DECALReconTrack &>( rhs ).Position)
   , Quality(const_cast<TP0DECALReconTrack &>( rhs ).Quality)
   , Width(const_cast<TP0DECALReconTrack &>( rhs ).Width)
   , AMR(const_cast<TP0DECALReconTrack &>( rhs ).AMR)
   , CWTrackWidth(const_cast<TP0DECALReconTrack &>( rhs ).CWTrackWidth)
   , Max_Ratio(const_cast<TP0DECALReconTrack &>( rhs ).Max_Ratio)
   , NormChargeSD(const_cast<TP0DECALReconTrack &>( rhs ).NormChargeSD)
   , PathChargeRatio(const_cast<TP0DECALReconTrack &>( rhs ).PathChargeRatio)
   , TrShval(const_cast<TP0DECALReconTrack &>( rhs ).TrShval)
   , NHits(const_cast<TP0DECALReconTrack &>( rhs ).NHits)
   , BenCWPosition(const_cast<TP0DECALReconTrack &>( rhs ).BenCWPosition)
   , StackNo(const_cast<TP0DECALReconTrack &>( rhs ).StackNo)
   , Module(const_cast<TP0DECALReconTrack &>( rhs ).Module)
   , TrueID(const_cast<TP0DECALReconTrack &>( rhs ).TrueID)
   , TruePDG(const_cast<TP0DECALReconTrack &>( rhs ).TruePDG)
   , TrueParentID(const_cast<TP0DECALReconTrack &>( rhs ).TrueParentID)
   , TrueHitPurity(const_cast<TP0DECALReconTrack &>( rhs ).TrueHitPurity)
   , TrueHitEfficiency(const_cast<TP0DECALReconTrack &>( rhs ).TrueHitEfficiency)
   , TrueInitPos(const_cast<TP0DECALReconTrack &>( rhs ).TrueInitPos)
   , TrueFinalPos(const_cast<TP0DECALReconTrack &>( rhs ).TrueFinalPos)
   , TrueInitMom(const_cast<TP0DECALReconTrack &>( rhs ).TrueInitMom)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DECALReconTrack &modrhs = const_cast<TP0DECALReconTrack &>( rhs );
   modrhs.Module.clear();
}
ND::TP0DECALReconModule::TP0DECALReconTrack::~TP0DECALReconTrack() {
}
#endif // ND__TP0DECALReconModule__TP0DECALReconTrack_cxx

#ifndef ND__TP0DECALReconModule__TP0DECALReconShower_cxx
#define ND__TP0DECALReconModule__TP0DECALReconShower_cxx
ND::TP0DECALReconModule::TP0DECALReconShower::TP0DECALReconShower() {
}
ND::TP0DECALReconModule::TP0DECALReconShower::TP0DECALReconShower(const TP0DECALReconShower & rhs)
   : TObject(const_cast<TP0DECALReconShower &>( rhs ))
   , UniqueID(const_cast<TP0DECALReconShower &>( rhs ).UniqueID)
   , ConeAngle(const_cast<TP0DECALReconShower &>( rhs ).ConeAngle)
   , Direction(const_cast<TP0DECALReconShower &>( rhs ).Direction)
   , EDeposit(const_cast<TP0DECALReconShower &>( rhs ).EDeposit)
   , NDOF(const_cast<TP0DECALReconShower &>( rhs ).NDOF)
   , Position(const_cast<TP0DECALReconShower &>( rhs ).Position)
   , Quality(const_cast<TP0DECALReconShower &>( rhs ).Quality)
   , AMR(const_cast<TP0DECALReconShower &>( rhs ).AMR)
   , CWTrackWidth(const_cast<TP0DECALReconShower &>( rhs ).CWTrackWidth)
   , Max_Ratio(const_cast<TP0DECALReconShower &>( rhs ).Max_Ratio)
   , NormChargeSD(const_cast<TP0DECALReconShower &>( rhs ).NormChargeSD)
   , PathChargeRatio(const_cast<TP0DECALReconShower &>( rhs ).PathChargeRatio)
   , TrShval(const_cast<TP0DECALReconShower &>( rhs ).TrShval)
   , NHits(const_cast<TP0DECALReconShower &>( rhs ).NHits)
   , BenCWPosition(const_cast<TP0DECALReconShower &>( rhs ).BenCWPosition)
   , StackNo(const_cast<TP0DECALReconShower &>( rhs ).StackNo)
   , TrueID(const_cast<TP0DECALReconShower &>( rhs ).TrueID)
   , Module(const_cast<TP0DECALReconShower &>( rhs ).Module)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DECALReconShower &modrhs = const_cast<TP0DECALReconShower &>( rhs );
   modrhs.Module.clear();
}
ND::TP0DECALReconModule::TP0DECALReconShower::~TP0DECALReconShower() {
}
#endif // ND__TP0DECALReconModule__TP0DECALReconShower_cxx

#ifndef ND__TP0DECALReconModule__TP0DECALLayerCharge_cxx
#define ND__TP0DECALReconModule__TP0DECALLayerCharge_cxx
ND::TP0DECALReconModule::TP0DECALLayerCharge::TP0DECALLayerCharge() {
}
ND::TP0DECALReconModule::TP0DECALLayerCharge::TP0DECALLayerCharge(const TP0DECALLayerCharge & rhs)
   : TObject(const_cast<TP0DECALLayerCharge &>( rhs ))
   , FirstTime(const_cast<TP0DECALLayerCharge &>( rhs ).FirstTime)
   , LastTime(const_cast<TP0DECALLayerCharge &>( rhs ).LastTime)
   , module_name(const_cast<TP0DECALLayerCharge &>( rhs ).module_name)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   for (Int_t i=0;i<6;i++) Charge[i] = rhs.Charge[i];
}
ND::TP0DECALReconModule::TP0DECALLayerCharge::~TP0DECALLayerCharge() {
}
#endif // ND__TP0DECALReconModule__TP0DECALLayerCharge_cxx

#ifndef ND__TP0DReconModule__TP0DAlgoRes_cxx
#define ND__TP0DReconModule__TP0DAlgoRes_cxx
ND::TP0DReconModule::TP0DAlgoRes::TP0DAlgoRes() {
}
ND::TP0DReconModule::TP0DAlgoRes::TP0DAlgoRes(const TP0DAlgoRes & rhs)
   : TObject(const_cast<TP0DAlgoRes &>( rhs ))
   , AlgorithmName(const_cast<TP0DAlgoRes &>( rhs ).AlgorithmName)
   , Cycle(const_cast<TP0DAlgoRes &>( rhs ).Cycle)
   , Vertices(const_cast<TP0DAlgoRes &>( rhs ).Vertices)
   , Particles(const_cast<TP0DAlgoRes &>( rhs ).Particles)
   , Tracks(const_cast<TP0DAlgoRes &>( rhs ).Tracks)
   , Showers(const_cast<TP0DAlgoRes &>( rhs ).Showers)
   , Clusters(const_cast<TP0DAlgoRes &>( rhs ).Clusters)
   , Nodes(const_cast<TP0DAlgoRes &>( rhs ).Nodes)
   , Hits(const_cast<TP0DAlgoRes &>( rhs ).Hits)
   , NHits(const_cast<TP0DAlgoRes &>( rhs ).NHits)
   , UniqueID(const_cast<TP0DAlgoRes &>( rhs ).UniqueID)
   , FullName(const_cast<TP0DAlgoRes &>( rhs ).FullName)
   , AlgoResults(const_cast<TP0DAlgoRes &>( rhs ).AlgoResults)
   , Parent(const_cast<TP0DAlgoRes &>( rhs ).Parent)
   , UsedHitCluster(const_cast<TP0DAlgoRes &>( rhs ).UsedHitCluster)
   , UnusedHitCluster(const_cast<TP0DAlgoRes &>( rhs ).UnusedHitCluster)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DAlgoRes &modrhs = const_cast<TP0DAlgoRes &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Vertices.clear();
   modrhs.Particles.clear();
   modrhs.Tracks.clear();
   modrhs.Showers.clear();
   modrhs.Clusters.clear();
   modrhs.Nodes.clear();
   modrhs.Hits.clear();
   modrhs.FullName.clear();
   modrhs.AlgoResults.clear();
}
ND::TP0DReconModule::TP0DAlgoRes::~TP0DAlgoRes() {
}
#endif // ND__TP0DReconModule__TP0DAlgoRes_cxx

#ifndef ND__TP0DReconModule__TP0DVertex_cxx
#define ND__TP0DReconModule__TP0DVertex_cxx
ND::TP0DReconModule::TP0DVertex::TP0DVertex() {
}
ND::TP0DReconModule::TP0DVertex::TP0DVertex(const TP0DVertex & rhs)
   : TObject(const_cast<TP0DVertex &>( rhs ))
   , AlgorithmName(const_cast<TP0DVertex &>( rhs ).AlgorithmName)
   , Cycle(const_cast<TP0DVertex &>( rhs ).Cycle)
   , Vertices(const_cast<TP0DVertex &>( rhs ).Vertices)
   , Particles(const_cast<TP0DVertex &>( rhs ).Particles)
   , Tracks(const_cast<TP0DVertex &>( rhs ).Tracks)
   , Showers(const_cast<TP0DVertex &>( rhs ).Showers)
   , Clusters(const_cast<TP0DVertex &>( rhs ).Clusters)
   , Nodes(const_cast<TP0DVertex &>( rhs ).Nodes)
   , Hits(const_cast<TP0DVertex &>( rhs ).Hits)
   , NHits(const_cast<TP0DVertex &>( rhs ).NHits)
   , UniqueID(const_cast<TP0DVertex &>( rhs ).UniqueID)
   , Status(const_cast<TP0DVertex &>( rhs ).Status)
   , Quality(const_cast<TP0DVertex &>( rhs ).Quality)
   , NDOF(const_cast<TP0DVertex &>( rhs ).NDOF)
   , Truth_PrimaryTrajIDs(const_cast<TP0DVertex &>( rhs ).Truth_PrimaryTrajIDs)
   , Truth_TrajIDs(const_cast<TP0DVertex &>( rhs ).Truth_TrajIDs)
   , Truth_HitCount(const_cast<TP0DVertex &>( rhs ).Truth_HitCount)
   , Truth_ChargeShare(const_cast<TP0DVertex &>( rhs ).Truth_ChargeShare)
   , Position(const_cast<TP0DVertex &>( rhs ).Position)
   , PosVariance(const_cast<TP0DVertex &>( rhs ).PosVariance)
   , ValidDimensions(const_cast<TP0DVertex &>( rhs ).ValidDimensions)
   , Fiducial(const_cast<TP0DVertex &>( rhs ).Fiducial)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DVertex &modrhs = const_cast<TP0DVertex &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Vertices.clear();
   modrhs.Particles.clear();
   modrhs.Tracks.clear();
   modrhs.Showers.clear();
   modrhs.Clusters.clear();
   modrhs.Nodes.clear();
   modrhs.Hits.clear();
   modrhs.Truth_PrimaryTrajIDs.clear();
   modrhs.Truth_TrajIDs.clear();
   modrhs.Truth_HitCount.clear();
   modrhs.Truth_ChargeShare.clear();
}
ND::TP0DReconModule::TP0DVertex::~TP0DVertex() {
}
#endif // ND__TP0DReconModule__TP0DVertex_cxx

#ifndef ND__TP0DReconModule__TP0DParticle_cxx
#define ND__TP0DReconModule__TP0DParticle_cxx
ND::TP0DReconModule::TP0DParticle::TP0DParticle() {
}
ND::TP0DReconModule::TP0DParticle::TP0DParticle(const TP0DParticle & rhs)
   : TObject(const_cast<TP0DParticle &>( rhs ))
   , AlgorithmName(const_cast<TP0DParticle &>( rhs ).AlgorithmName)
   , Cycle(const_cast<TP0DParticle &>( rhs ).Cycle)
   , Vertices(const_cast<TP0DParticle &>( rhs ).Vertices)
   , Particles(const_cast<TP0DParticle &>( rhs ).Particles)
   , Tracks(const_cast<TP0DParticle &>( rhs ).Tracks)
   , Showers(const_cast<TP0DParticle &>( rhs ).Showers)
   , Clusters(const_cast<TP0DParticle &>( rhs ).Clusters)
   , Nodes(const_cast<TP0DParticle &>( rhs ).Nodes)
   , Hits(const_cast<TP0DParticle &>( rhs ).Hits)
   , NHits(const_cast<TP0DParticle &>( rhs ).NHits)
   , UniqueID(const_cast<TP0DParticle &>( rhs ).UniqueID)
   , Status(const_cast<TP0DParticle &>( rhs ).Status)
   , Quality(const_cast<TP0DParticle &>( rhs ).Quality)
   , NDOF(const_cast<TP0DParticle &>( rhs ).NDOF)
   , Truth_PrimaryTrajIDs(const_cast<TP0DParticle &>( rhs ).Truth_PrimaryTrajIDs)
   , Truth_TrajIDs(const_cast<TP0DParticle &>( rhs ).Truth_TrajIDs)
   , Truth_HitCount(const_cast<TP0DParticle &>( rhs ).Truth_HitCount)
   , Truth_ChargeShare(const_cast<TP0DParticle &>( rhs ).Truth_ChargeShare)
   , SideDeposit(const_cast<TP0DParticle &>( rhs ).SideDeposit)
   , EndDeposit(const_cast<TP0DParticle &>( rhs ).EndDeposit)
   , Position(const_cast<TP0DParticle &>( rhs ).Position)
   , PosVariance(const_cast<TP0DParticle &>( rhs ).PosVariance)
   , ValidDimensions(const_cast<TP0DParticle &>( rhs ).ValidDimensions)
   , Direction(const_cast<TP0DParticle &>( rhs ).Direction)
   , DirVariance(const_cast<TP0DParticle &>( rhs ).DirVariance)
   , Momentum(const_cast<TP0DParticle &>( rhs ).Momentum)
   , Charge(const_cast<TP0DParticle &>( rhs ).Charge)
   , realPIDNames(const_cast<TP0DParticle &>( rhs ).realPIDNames)
   , realPIDValues(const_cast<TP0DParticle &>( rhs ).realPIDValues)
   , integerPIDNames(const_cast<TP0DParticle &>( rhs ).integerPIDNames)
   , integerPIDValues(const_cast<TP0DParticle &>( rhs ).integerPIDValues)
   , PID(const_cast<TP0DParticle &>( rhs ).PID)
   , PID_weight(const_cast<TP0DParticle &>( rhs ).PID_weight)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DParticle &modrhs = const_cast<TP0DParticle &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Vertices.clear();
   modrhs.Particles.clear();
   modrhs.Tracks.clear();
   modrhs.Showers.clear();
   modrhs.Clusters.clear();
   modrhs.Nodes.clear();
   modrhs.Hits.clear();
   modrhs.Truth_PrimaryTrajIDs.clear();
   modrhs.Truth_TrajIDs.clear();
   modrhs.Truth_HitCount.clear();
   modrhs.Truth_ChargeShare.clear();
   modrhs.realPIDNames.clear();
   modrhs.realPIDValues.clear();
   modrhs.integerPIDNames.clear();
   modrhs.integerPIDValues.clear();
   modrhs.PID.clear();
   modrhs.PID_weight.clear();
}
ND::TP0DReconModule::TP0DParticle::~TP0DParticle() {
}
#endif // ND__TP0DReconModule__TP0DParticle_cxx

#ifndef ND__TP0DReconModule__TP0DShower_cxx
#define ND__TP0DReconModule__TP0DShower_cxx
ND::TP0DReconModule::TP0DShower::TP0DShower() {
}
ND::TP0DReconModule::TP0DShower::TP0DShower(const TP0DShower & rhs)
   : TObject(const_cast<TP0DShower &>( rhs ))
   , AlgorithmName(const_cast<TP0DShower &>( rhs ).AlgorithmName)
   , Cycle(const_cast<TP0DShower &>( rhs ).Cycle)
   , Vertices(const_cast<TP0DShower &>( rhs ).Vertices)
   , Particles(const_cast<TP0DShower &>( rhs ).Particles)
   , Tracks(const_cast<TP0DShower &>( rhs ).Tracks)
   , Showers(const_cast<TP0DShower &>( rhs ).Showers)
   , Clusters(const_cast<TP0DShower &>( rhs ).Clusters)
   , Nodes(const_cast<TP0DShower &>( rhs ).Nodes)
   , Hits(const_cast<TP0DShower &>( rhs ).Hits)
   , NHits(const_cast<TP0DShower &>( rhs ).NHits)
   , UniqueID(const_cast<TP0DShower &>( rhs ).UniqueID)
   , Status(const_cast<TP0DShower &>( rhs ).Status)
   , Quality(const_cast<TP0DShower &>( rhs ).Quality)
   , NDOF(const_cast<TP0DShower &>( rhs ).NDOF)
   , Truth_PrimaryTrajIDs(const_cast<TP0DShower &>( rhs ).Truth_PrimaryTrajIDs)
   , Truth_TrajIDs(const_cast<TP0DShower &>( rhs ).Truth_TrajIDs)
   , Truth_HitCount(const_cast<TP0DShower &>( rhs ).Truth_HitCount)
   , Truth_ChargeShare(const_cast<TP0DShower &>( rhs ).Truth_ChargeShare)
   , EDeposit(const_cast<TP0DShower &>( rhs ).EDeposit)
   , SideDeposit(const_cast<TP0DShower &>( rhs ).SideDeposit)
   , EndDeposit(const_cast<TP0DShower &>( rhs ).EndDeposit)
   , Position(const_cast<TP0DShower &>( rhs ).Position)
   , PosVariance(const_cast<TP0DShower &>( rhs ).PosVariance)
   , ValidDimensions(const_cast<TP0DShower &>( rhs ).ValidDimensions)
   , Direction(const_cast<TP0DShower &>( rhs ).Direction)
   , DirVariance(const_cast<TP0DShower &>( rhs ).DirVariance)
   , Cone(const_cast<TP0DShower &>( rhs ).Cone)
   , Width(const_cast<TP0DShower &>( rhs ).Width)
   , Length(const_cast<TP0DShower &>( rhs ).Length)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DShower &modrhs = const_cast<TP0DShower &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Vertices.clear();
   modrhs.Particles.clear();
   modrhs.Tracks.clear();
   modrhs.Showers.clear();
   modrhs.Clusters.clear();
   modrhs.Nodes.clear();
   modrhs.Hits.clear();
   modrhs.Truth_PrimaryTrajIDs.clear();
   modrhs.Truth_TrajIDs.clear();
   modrhs.Truth_HitCount.clear();
   modrhs.Truth_ChargeShare.clear();
}
ND::TP0DReconModule::TP0DShower::~TP0DShower() {
}
#endif // ND__TP0DReconModule__TP0DShower_cxx

#ifndef ND__TP0DReconModule__TP0DTrack_cxx
#define ND__TP0DReconModule__TP0DTrack_cxx
ND::TP0DReconModule::TP0DTrack::TP0DTrack() {
}
ND::TP0DReconModule::TP0DTrack::TP0DTrack(const TP0DTrack & rhs)
   : TObject(const_cast<TP0DTrack &>( rhs ))
   , AlgorithmName(const_cast<TP0DTrack &>( rhs ).AlgorithmName)
   , Cycle(const_cast<TP0DTrack &>( rhs ).Cycle)
   , Vertices(const_cast<TP0DTrack &>( rhs ).Vertices)
   , Particles(const_cast<TP0DTrack &>( rhs ).Particles)
   , Tracks(const_cast<TP0DTrack &>( rhs ).Tracks)
   , Showers(const_cast<TP0DTrack &>( rhs ).Showers)
   , Clusters(const_cast<TP0DTrack &>( rhs ).Clusters)
   , Nodes(const_cast<TP0DTrack &>( rhs ).Nodes)
   , Hits(const_cast<TP0DTrack &>( rhs ).Hits)
   , NHits(const_cast<TP0DTrack &>( rhs ).NHits)
   , UniqueID(const_cast<TP0DTrack &>( rhs ).UniqueID)
   , Status(const_cast<TP0DTrack &>( rhs ).Status)
   , Quality(const_cast<TP0DTrack &>( rhs ).Quality)
   , NDOF(const_cast<TP0DTrack &>( rhs ).NDOF)
   , Truth_PrimaryTrajIDs(const_cast<TP0DTrack &>( rhs ).Truth_PrimaryTrajIDs)
   , Truth_TrajIDs(const_cast<TP0DTrack &>( rhs ).Truth_TrajIDs)
   , Truth_HitCount(const_cast<TP0DTrack &>( rhs ).Truth_HitCount)
   , Truth_ChargeShare(const_cast<TP0DTrack &>( rhs ).Truth_ChargeShare)
   , EDeposit(const_cast<TP0DTrack &>( rhs ).EDeposit)
   , SideDeposit(const_cast<TP0DTrack &>( rhs ).SideDeposit)
   , EndDeposit(const_cast<TP0DTrack &>( rhs ).EndDeposit)
   , Position(const_cast<TP0DTrack &>( rhs ).Position)
   , PosVariance(const_cast<TP0DTrack &>( rhs ).PosVariance)
   , ValidDimensions(const_cast<TP0DTrack &>( rhs ).ValidDimensions)
   , Direction(const_cast<TP0DTrack &>( rhs ).Direction)
   , DirVariance(const_cast<TP0DTrack &>( rhs ).DirVariance)
   , Length(const_cast<TP0DTrack &>( rhs ).Length)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DTrack &modrhs = const_cast<TP0DTrack &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Vertices.clear();
   modrhs.Particles.clear();
   modrhs.Tracks.clear();
   modrhs.Showers.clear();
   modrhs.Clusters.clear();
   modrhs.Nodes.clear();
   modrhs.Hits.clear();
   modrhs.Truth_PrimaryTrajIDs.clear();
   modrhs.Truth_TrajIDs.clear();
   modrhs.Truth_HitCount.clear();
   modrhs.Truth_ChargeShare.clear();
}
ND::TP0DReconModule::TP0DTrack::~TP0DTrack() {
}
#endif // ND__TP0DReconModule__TP0DTrack_cxx

#ifndef ND__TP0DReconModule__TP0DNode_cxx
#define ND__TP0DReconModule__TP0DNode_cxx
ND::TP0DReconModule::TP0DNode::TP0DNode() {
}
ND::TP0DReconModule::TP0DNode::TP0DNode(const TP0DNode & rhs)
   : TObject(const_cast<TP0DNode &>( rhs ))
   , Hits(const_cast<TP0DNode &>( rhs ).Hits)
   , Truth_PrimaryTrajIDs(const_cast<TP0DNode &>( rhs ).Truth_PrimaryTrajIDs)
   , Truth_TrajIDs(const_cast<TP0DNode &>( rhs ).Truth_TrajIDs)
   , Truth_HitCount(const_cast<TP0DNode &>( rhs ).Truth_HitCount)
   , Truth_ChargeShare(const_cast<TP0DNode &>( rhs ).Truth_ChargeShare)
   , EDeposit(const_cast<TP0DNode &>( rhs ).EDeposit)
   , Position(const_cast<TP0DNode &>( rhs ).Position)
   , PosVariance(const_cast<TP0DNode &>( rhs ).PosVariance)
   , ValidDimensions(const_cast<TP0DNode &>( rhs ).ValidDimensions)
   , Direction(const_cast<TP0DNode &>( rhs ).Direction)
   , DirVariance(const_cast<TP0DNode &>( rhs ).DirVariance)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DNode &modrhs = const_cast<TP0DNode &>( rhs );
   modrhs.Hits.clear();
   modrhs.Truth_PrimaryTrajIDs.clear();
   modrhs.Truth_TrajIDs.clear();
   modrhs.Truth_HitCount.clear();
   modrhs.Truth_ChargeShare.clear();
}
ND::TP0DReconModule::TP0DNode::~TP0DNode() {
}
#endif // ND__TP0DReconModule__TP0DNode_cxx

#ifndef ND__TP0DReconModule__TP0DHit_cxx
#define ND__TP0DReconModule__TP0DHit_cxx
ND::TP0DReconModule::TP0DHit::TP0DHit() {
}
ND::TP0DReconModule::TP0DHit::TP0DHit(const TP0DHit & rhs)
   : TObject(const_cast<TP0DHit &>( rhs ))
   , GeomID(const_cast<TP0DHit &>( rhs ).GeomID)
   , ChanID(const_cast<TP0DHit &>( rhs ).ChanID)
   , Charge(const_cast<TP0DHit &>( rhs ).Charge)
   , Time(const_cast<TP0DHit &>( rhs ).Time)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TP0DReconModule::TP0DHit::~TP0DHit() {
}
#endif // ND__TP0DReconModule__TP0DHit_cxx

#ifndef ND__TP0DReconModule__TP0DCluster_cxx
#define ND__TP0DReconModule__TP0DCluster_cxx
ND::TP0DReconModule::TP0DCluster::TP0DCluster() {
}
ND::TP0DReconModule::TP0DCluster::TP0DCluster(const TP0DCluster & rhs)
   : TObject(const_cast<TP0DCluster &>( rhs ))
   , AlgorithmName(const_cast<TP0DCluster &>( rhs ).AlgorithmName)
   , Cycle(const_cast<TP0DCluster &>( rhs ).Cycle)
   , Vertices(const_cast<TP0DCluster &>( rhs ).Vertices)
   , Particles(const_cast<TP0DCluster &>( rhs ).Particles)
   , Tracks(const_cast<TP0DCluster &>( rhs ).Tracks)
   , Showers(const_cast<TP0DCluster &>( rhs ).Showers)
   , Clusters(const_cast<TP0DCluster &>( rhs ).Clusters)
   , Nodes(const_cast<TP0DCluster &>( rhs ).Nodes)
   , Hits(const_cast<TP0DCluster &>( rhs ).Hits)
   , NHits(const_cast<TP0DCluster &>( rhs ).NHits)
   , UniqueID(const_cast<TP0DCluster &>( rhs ).UniqueID)
   , Truth_PrimaryTrajIDs(const_cast<TP0DCluster &>( rhs ).Truth_PrimaryTrajIDs)
   , Truth_TrajIDs(const_cast<TP0DCluster &>( rhs ).Truth_TrajIDs)
   , Truth_HitCount(const_cast<TP0DCluster &>( rhs ).Truth_HitCount)
   , Truth_ChargeShare(const_cast<TP0DCluster &>( rhs ).Truth_ChargeShare)
   , NFiducialHits(const_cast<TP0DCluster &>( rhs ).NFiducialHits)
   , EDeposit(const_cast<TP0DCluster &>( rhs ).EDeposit)
   , Position(const_cast<TP0DCluster &>( rhs ).Position)
   , PosVariance(const_cast<TP0DCluster &>( rhs ).PosVariance)
   , ValidDimensions(const_cast<TP0DCluster &>( rhs ).ValidDimensions)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TP0DCluster &modrhs = const_cast<TP0DCluster &>( rhs );
   modrhs.AlgorithmName.clear();
   modrhs.Vertices.clear();
   modrhs.Particles.clear();
   modrhs.Tracks.clear();
   modrhs.Showers.clear();
   modrhs.Clusters.clear();
   modrhs.Nodes.clear();
   modrhs.Hits.clear();
   modrhs.Truth_PrimaryTrajIDs.clear();
   modrhs.Truth_TrajIDs.clear();
   modrhs.Truth_HitCount.clear();
   modrhs.Truth_ChargeShare.clear();
   for (Int_t i=0;i<9;i++) Moments[i] = rhs.Moments[i];
}
ND::TP0DReconModule::TP0DCluster::~TP0DCluster() {
}
#endif // ND__TP0DReconModule__TP0DCluster_cxx

#ifndef ND__TTruthVerticesModule__TTruthVertex_cxx
#define ND__TTruthVerticesModule__TTruthVertex_cxx
ND::TTruthVerticesModule::TTruthVertex::TTruthVertex() {
}
ND::TTruthVerticesModule::TTruthVertex::TTruthVertex(const TTruthVertex & rhs)
   : TObject(const_cast<TTruthVertex &>( rhs ))
   , ID(const_cast<TTruthVertex &>( rhs ).ID)
   , Position(const_cast<TTruthVertex &>( rhs ).Position)
   , Generator(const_cast<TTruthVertex &>( rhs ).Generator)
   , ReactionCode(const_cast<TTruthVertex &>( rhs ).ReactionCode)
   , Subdetector(const_cast<TTruthVertex &>( rhs ).Subdetector)
   , Fiducial(const_cast<TTruthVertex &>( rhs ).Fiducial)
   , NPrimaryTraj(const_cast<TTruthVertex &>( rhs ).NPrimaryTraj)
   , PrimaryTrajIDs(const_cast<TTruthVertex &>( rhs ).PrimaryTrajIDs)
   , NeutrinoPDG(const_cast<TTruthVertex &>( rhs ).NeutrinoPDG)
   , NeutrinoMomentum(const_cast<TTruthVertex &>( rhs ).NeutrinoMomentum)
   , TargetPDG(const_cast<TTruthVertex &>( rhs ).TargetPDG)
   , TargetMomentum(const_cast<TTruthVertex &>( rhs ).TargetMomentum)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTruthVertex &modrhs = const_cast<TTruthVertex &>( rhs );
   modrhs.Generator.clear();
   modrhs.ReactionCode.clear();
   modrhs.PrimaryTrajIDs.clear();
}
ND::TTruthVerticesModule::TTruthVertex::~TTruthVertex() {
}
#endif // ND__TTruthVerticesModule__TTruthVertex_cxx

#ifndef ND__TTruthTrajectoriesModule__TTruthTrajectory_cxx
#define ND__TTruthTrajectoriesModule__TTruthTrajectory_cxx
ND::TTruthTrajectoriesModule::TTruthTrajectory::TTruthTrajectory() {
}
ND::TTruthTrajectoriesModule::TTruthTrajectory::TTruthTrajectory(const TTruthTrajectory & rhs)
   : TObject(const_cast<TTruthTrajectory &>( rhs ))
   , ID(const_cast<TTruthTrajectory &>( rhs ).ID)
   , PDG(const_cast<TTruthTrajectory &>( rhs ).PDG)
   , Name(const_cast<TTruthTrajectory &>( rhs ).Name)
   , Category(const_cast<TTruthTrajectory &>( rhs ).Category)
   , InitMomentum(const_cast<TTruthTrajectory &>( rhs ).InitMomentum)
   , InitPosition(const_cast<TTruthTrajectory &>( rhs ).InitPosition)
   , FinalPosition(const_cast<TTruthTrajectory &>( rhs ).FinalPosition)
   , ParentID(const_cast<TTruthTrajectory &>( rhs ).ParentID)
   , PrimaryID(const_cast<TTruthTrajectory &>( rhs ).PrimaryID)
   , Mass(const_cast<TTruthTrajectory &>( rhs ).Mass)
   , Charge(const_cast<TTruthTrajectory &>( rhs ).Charge)
   , Points(const_cast<TTruthTrajectory &>( rhs ).Points)
   , TraceSubdetectors(const_cast<TTruthTrajectory &>( rhs ).TraceSubdetectors)
   , TraceInActive(const_cast<TTruthTrajectory &>( rhs ).TraceInActive)
   , TraceEntrancePosition(const_cast<TTruthTrajectory &>( rhs ).TraceEntrancePosition)
   , TraceExitPosition(const_cast<TTruthTrajectory &>( rhs ).TraceExitPosition)
   , TraceEntranceMomentum(const_cast<TTruthTrajectory &>( rhs ).TraceEntranceMomentum)
   , TraceExitMomentum(const_cast<TTruthTrajectory &>( rhs ).TraceExitMomentum)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
   TTruthTrajectory &modrhs = const_cast<TTruthTrajectory &>( rhs );
   modrhs.Name.clear();
   modrhs.Points.clear();
   modrhs.TraceSubdetectors.clear();
   modrhs.TraceInActive.clear();
   modrhs.TraceEntrancePosition.clear();
   modrhs.TraceExitPosition.clear();
   modrhs.TraceEntranceMomentum.clear();
   modrhs.TraceExitMomentum.clear();
}
ND::TTruthTrajectoriesModule::TTruthTrajectory::~TTruthTrajectory() {
}
#endif // ND__TTruthTrajectoriesModule__TTruthTrajectory_cxx

#ifndef ND__TTruthTrajectoriesModule__TTruthTrajectoryPoint_cxx
#define ND__TTruthTrajectoriesModule__TTruthTrajectoryPoint_cxx
ND::TTruthTrajectoriesModule::TTruthTrajectoryPoint::TTruthTrajectoryPoint() {
}
ND::TTruthTrajectoriesModule::TTruthTrajectoryPoint::TTruthTrajectoryPoint(const TTruthTrajectoryPoint & rhs)
   : TObject(const_cast<TTruthTrajectoryPoint &>( rhs ))
   , ProcessType(const_cast<TTruthTrajectoryPoint &>( rhs ).ProcessType)
   , PositionX(const_cast<TTruthTrajectoryPoint &>( rhs ).PositionX)
   , PositionY(const_cast<TTruthTrajectoryPoint &>( rhs ).PositionY)
   , PositionZ(const_cast<TTruthTrajectoryPoint &>( rhs ).PositionZ)
   , PositionT(const_cast<TTruthTrajectoryPoint &>( rhs ).PositionT)
   , MomentumX(const_cast<TTruthTrajectoryPoint &>( rhs ).MomentumX)
   , MomentumY(const_cast<TTruthTrajectoryPoint &>( rhs ).MomentumY)
   , MomentumZ(const_cast<TTruthTrajectoryPoint &>( rhs ).MomentumZ)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   if (&rhs) {} // avoid warning about unused parameter
}
ND::TTruthTrajectoriesModule::TTruthTrajectoryPoint::~TTruthTrajectoryPoint() {
}
#endif // ND__TTruthTrajectoriesModule__TTruthTrajectoryPoint_cxx

