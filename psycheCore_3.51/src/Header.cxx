#include "Header.hxx"
#include "CoreUtils.hxx"
#include <stdio.h>
#include <iostream>
#include <assert.h>

//********************************************************************
Header::Header(POTDef def){
  //********************************************************************
  
  SetPOTDef(def); 
  
  Reset();
}

//********************************************************************
void Header::Reset() {
  //********************************************************************

  _POT_CountedPerFile      = 0;
  _POT_NoCut               = 0;
  _POT_BadBeam             = 0;
  _POT_BadND280            = 0;
  _POT_GoodBeamGoodND280   = 0;
  _POT_0KA                 = 0;
  _POT_200KA               = 0;
  _POT_250KA               = 0;
  _POT_m250KA              = 0;
  _POT_OtherKA             = 0;
  _Spill_NoCut             = 0;
  _Spill_BadBeam           = 0;
  _Spill_BadND280          = 0;
  _Spill_GoodBeamGoodND280 = 0;

  _pot_def_counter = kPOTDefCounter;
  _spill_def_counter = kSpillDefCounter;

  for (int i = 0; i < _pot_def_counter; i++){
    _POTInfo[i] = 0;
  }
  
  for (int i = 0; i < _spill_def_counter; i++){
    _SpillInfo[i] = 0;
  } 

  _SoftwareVersion="";
  _IsMC = false;
  _isFirstFile=true;
}

//********************************************************************
bool Header::AddHeader(TTree* tree, bool bySpillPOT){
  //********************************************************************

  if (!tree) return false;

  if (tree->FindBranch("POTInfo_v2")){
    Header *header=0;
    anaUtils::ConfigureTreeBranch(tree, "POTInfo_v2", &header);

    // There can be multiple entries in the "header" tree if the analyser has
    // used hadd to merge multiple output trees. We sum the total POT in all
    // entries
    HASSERT(header->GetPOTDefCounter()   == _pot_def_counter);
    HASSERT(header->GetSpillDefCounter() == _spill_def_counter);
    for (int i = 0; i < tree->GetEntries(); i++) {
      tree->GetEntry(i);      
      if (!SetIsMC(header->GetIsMC())) return false;
      if (!SetSoftwareVersion(header->GetSoftwareVersion())) return false;

      _POT_CountedPerFile += header->GetPOTCountedPerFile();
      if (!bySpillPOT){
        for (int i = 0; i < header->GetPOTDefCounter(); i++){
          _POTInfo[i] += header->GetPOTInfo()[i];
        }
       
        for (int i = 0; i < header->GetSpillDefCounter(); i++){
          _SpillInfo[i] += header->GetSpillInfo()[i];
        }
 
      }
    }
  }
  else if (tree->FindBranch("POTInfo")){
    Header *header=0;
    anaUtils::ConfigureTreeBranch(tree, "POTInfo", &header);

    // There can be multiple entries in the "header" tree if the analyser has
    // used hadd to merge multiple output trees. We sum the total POT in all
    // entries.
    for (int i = 0; i < tree->GetEntries(); i++) {
      tree->GetEntry(i);      
      if (!SetIsMC(header->GetIsMC())) return false;
      if (!SetSoftwareVersion(header->GetSoftwareVersion())) return false;

      _POT_CountedPerFile      += header->GetPOTCountedPerFile();

      if (!bySpillPOT){
        _POTInfo[kNoCut]             += header->_POT_NoCut;
        _POTInfo[kBadBeam]           += header->_POT_BadBeam;
        _POTInfo[kBadND280]          += header->_POT_BadND280;
        _POTInfo[kGoodBeamGoodND280] += header->_POT_GoodBeamGoodND280;
        _POTInfo[k0KA]               += header->_POT_0KA;
        _POTInfo[k200KA]             += header->_POT_200KA;
        _POTInfo[k250KA]             += header->_POT_250KA;
        _POTInfo[km250KA]            += header->_POT_m250KA;
        _POTInfo[kOtherKA]           += header->_POT_OtherKA;
        
        _SpillInfo[kSpillNoCut]                 += header->_Spill_NoCut;
        _SpillInfo[kSpillBadBeam]               += header->_Spill_BadBeam;
        _SpillInfo[kSpillBadND280]              += header->_Spill_BadND280;
        _SpillInfo[kSpillGoodBeamGoodND280]     += header->_Spill_GoodBeamGoodND280;
      }
    }   
  }

  return true;
}

//********************************************************************
void Header::SetPOTDef(POTDef def){
  //********************************************************************
  HASSERT(def < kPOTDefCounter);
  _pot_def = def;
   
  _spill_def = kSpillGoodBeamGoodND280;
 
  // Depending on pot def set the spill one
  switch (_pot_def){
    case  kNoCut:
      _spill_def = kSpillNoCut;
      break;
    case kBadBeam:
      _spill_def = kSpillBadBeam;
      break;
    case kBadND280:
      _spill_def = kSpillBadND280;
      break;
    case kBadND280Time:
      _spill_def = kSpillBadND280Time;
      break;
    case kGoodBeamGoodND280Time:
      _spill_def = kSpillGoodBeamGoodND280Time;
      break;
    default:
      break;
  }
  
}


//********************************************************************
Double_t Header::GetPOT(POTDef def){
  //********************************************************************
  HASSERT(def < kPOTDefCounter);
  return _POTInfo[def];
}


//********************************************************************
Int_t Header::GetNSpills(SpillDef def){
  //********************************************************************
  HASSERT(def < kSpillDefCounter);
  return _SpillInfo[def];
}

//********************************************************************
void Header::ReadHeader(TTree* tree){
  //********************************************************************

  if (!tree) return;
  Reset();
  AddHeader(tree);
}

//********************************************************************
bool Header::AddHeader(const std::string& file, bool bySpillPOT){
  //********************************************************************

  TChain chain("header");
  chain.AddFile(file.c_str());
  return AddHeader(&chain, bySpillPOT);
}

//********************************************************************
void Header::ReadHeader(const std::string& file){
  //********************************************************************

  TChain chain("header");
  chain.AddFile(file.c_str());
  ReadHeader(&chain);
}

//********************************************************************
void Header::IncrementPOTByFile(Double_t pot, bool bySpillPOT) {
  //********************************************************************

  _POT_CountedPerFile += pot;

  // When no POT information by spill exists (prod5 MC) POT counting is done by file 
  if (!bySpillPOT){
    _POT_NoCut += pot;
    _POT_GoodBeamGoodND280 += pot;
  }
}

//********************************************************************
void Header::IncrementPOTBySpill(const AnaSpillC& spill) {
  //********************************************************************

  (void)spill;
  /*
     const AnaBeamB& beam = *spill.Beam;
     const AnaEventInfoB& info = *spill.EventInfo;

     if (beam.POTSincePreviousSavedSpill > 1e+16) {
     std::cout << "WARNING: POT is suspiciously large for run " << info.Run << ", subrun " << info.SubRun << ", event " << info.Event << ": " << beam.POTSincePreviousSavedSpill << ". POT will not be counted for this event." << std::endl;
     return;
     }

     if (beam.POTSincePreviousSavedSpill < 0) {
     std::cout << "WARNING: POT is negative for run " << info.Run << ", subrun " << info.SubRun << ", event " << info.Event << ": " << beam.POTSincePreviousSavedSpill << ". POT will not be counted for this event." << std::endl;
     return;
     }

  // For real data
  if (!spill.GetIsMC()) {

  _POT_NoCut   += beam.POTSincePreviousSavedSpill;
  _Spill_NoCut += beam.SpillsSincePreviousSavedSpill;

  if (beam.GoodSpill == 0) {
  _POT_BadBeam   += beam.POTSincePreviousSavedSpill;
  _Spill_BadBeam += beam.SpillsSincePreviousSavedSpill;
  return;
  }

  if (!spill.DataQuality->GoodDaq) {
  _POT_BadND280   += beam.POTSincePreviousSavedSpill;
  _Spill_BadND280 += beam.SpillsSincePreviousSavedSpill;
  return;
  }

  if (beam.GoodSpill == 100) {
  _POT_0KA += beam.POTSincePreviousSavedSpill;
  } else if (beam.GoodSpill == 1) {
  _POT_250KA += beam.POTSincePreviousSavedSpill;
  } else if (beam.GoodSpill == 2) {
  _POT_200KA += beam.POTSincePreviousSavedSpill;
  } else if (beam.GoodSpill == -1) {
  _POT_m250KA += beam.POTSincePreviousSavedSpill;
  } else {
  _POT_OtherKA += beam.POTSincePreviousSavedSpill;
  }

  _POT_GoodBeamGoodND280   += beam.POTSincePreviousSavedSpill;
  _Spill_GoodBeamGoodND280 += beam.SpillsSincePreviousSavedSpill;
  }
  else{
  // For MC there is no information about magnet current, Spill and DQ are always good
  _Spill_NoCut             += beam.SpillsSincePreviousSavedSpill;
  _Spill_GoodBeamGoodND280 += beam.SpillsSincePreviousSavedSpill;

  _POT_NoCut             += beam.POTSincePreviousSavedSpill;
  _POT_GoodBeamGoodND280 += beam.POTSincePreviousSavedSpill;
  }
  */
}

//********************************************************************
void Header::DumpPOT() {
  //********************************************************************
  std::cout << "Initial POT (per File).. " << _POT_CountedPerFile << std::endl;
  std::cout << "Initial POT............. " << _POTInfo[kNoCut] << " Spills " << _SpillInfo[kSpillNoCut]  << std::endl;
  std::cout << "|-- Bad Beam............ " << _POTInfo[kBadBeam] << " Spills " << _SpillInfo[kSpillBadBeam]  << std::endl;
  std::cout << "|-- Bad ND280........... " << _POTInfo[kBadND280] << " Spills " << _SpillInfo[kSpillBadND280]  << std::endl;
  std::cout << "|-- Bad ND280 Time...... " << _POTInfo[kBadND280Time] << " Spills " << _SpillInfo[kSpillBadND280Time]  << std::endl;
  std::cout << "|-- Total Good POT...... " << _POTInfo[kGoodBeamGoodND280] << " Spills " << _SpillInfo[kSpillGoodBeamGoodND280]  << std::endl;
  std::cout << "|-- Total Good POT Time. " << _POTInfo[kGoodBeamGoodND280Time] << " Spills " << _SpillInfo[kSpillGoodBeamGoodND280Time]  << std::endl;
  std::cout << "  |-- @  0KA............ " << _POTInfo[k0KA] << std::endl;
  std::cout << "  |-- @  200KA.......... " << _POTInfo[k200KA] << std::endl;
  std::cout << "  |-- @  250KA.......... " << _POTInfo[k250KA] << std::endl;
  std::cout << "  |-- @ -250KA.......... " << _POTInfo[km250KA] << std::endl;
  std::cout << "  |-- @  250KA Time..... " << _POTInfo[k250KA_ND280Time] << std::endl;
  std::cout << "  |-- @ -250KA Time..... " << _POTInfo[km250KA_ND280Time] << std::endl;
  std::cout << "  |-- @  Other power.... " << _POTInfo[kOtherKA] << std::endl;
}


//********************************************************************
bool Header::SetIsMC(bool IsMC){
  //********************************************************************

  if (!_isFirstFile && _IsMC != IsMC){
    std::cout << "Header::SetIsMC(). New file with IsMC=" << IsMC << " differs from previous with IsMC=" << _IsMC << ". You cannot mix DATA and MC files !!!" << std::endl;
    return false;
  }

  _isFirstFile = false;
  _IsMC = IsMC;

  return true;
}

//********************************************************************
bool Header::SetSoftwareVersion(const std::string& ver){
  //********************************************************************

  if (_SoftwareVersion!="" && ver != _SoftwareVersion){
    std::cout << "Header::SetSoftwareVersion(). New version " << ver << " differs from previous " << _SoftwareVersion << std::endl;
    return false;
  }
  _SoftwareVersion = ver;
  return true;
}
