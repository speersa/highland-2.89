#include "SIPionSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "MultiThread.hxx"
#include "SystId.hxx"
#include "Parameters.hxx"
#include "VersioningUtils.hxx"

//#define DEBUG

//********************************************************************
SIPionSystematics::SIPionSystematics():EventWeightBase(1),BinnedParams("SIPion",k1D_SYMMETRIC, versionUtils::ExtensionSyst()){
  //********************************************************************
  CtrInitialize(); 
}

//********************************************************************
SIPionSystematics::SIPionSystematics(PionSIManager* manager):EventWeightBase(1),BinnedParams("SIPion",k1D_SYMMETRIC, versionUtils::ExtensionSyst()){
  //********************************************************************
  CtrInitialize();
  if (!_pionSIManager && manager)
    _pionSIManager = manager;

}

//********************************************************************
void SIPionSystematics::CtrInitialize(){
  //********************************************************************
  char inputFileName[256];

  char inputFileNameMC[256];

  char inputFileNameExclude[256];


#define JMDEBUGFIXMATERIAL 1
#if JMDEBUGFIXMATERIAL == 0
  sprintf(inputFileName,"%s/data/PionSI/SIPionXsec.dat",getenv("PSYCHESYSTEMATICSROOT"));
#else
  sprintf(inputFileName,"%s/data/PionSI/SIPionXsecFixG10.dat",getenv("PSYCHESYSTEMATICSROOT"));
#endif

  if ((bool)ND::params().GetParameterI("psycheND280Utils.PionSI.UseNEUTCascade") || 
      (bool)ND::params().GetParameterI("psycheND280Utils.PionSI.UseNEUTCascadeProd6TFix")){
    sprintf(inputFileName,"%s/data/PionSI/SIPionXsec_NEUTCascade.dat",getenv("PSYCHESYSTEMATICSROOT"));
    
#ifdef DEBUG

  std::cout << " SIPionSystematics: use NEUTCascade xsec for data " << std::endl;

#endif

  
  }
  
  anaUtils::LoadPionCrossSections(inputFileName, _xsec_data, _err_data);

  _useMCtoDataOnTheFly = false;

  if ((bool)ND::params().GetParameterI("psycheSystematics.PionSI.UseMCtoDataOnTheFly")){

    _useMCtoDataOnTheFly = true;

#define JMDEBUGFIXMATERIAL 1
#if JMDEBUGFIXMATERIAL == 0

  sprintf(inputFileNameMC,"%s/data/PionSI/SIPionXsecMCto8GeV.dat",getenv("PSYCHEND280UTILSROOT"));
#else

  sprintf(inputFileNameMC,"%s/data/PionSI/SIPionXsecMCto8GeVFixG10.dat",getenv("PSYCHEND280UTILSROOT"));
#endif

    if ((bool)ND::params().GetParameterI("psycheND280Utils.PionSI.UseNEUTCascade")){
      sprintf(inputFileNameMC,"%s/data/PionSI/SIPionXsecMCto8GeV_NEUTCascade.dat",getenv("PSYCHEND280UTILSROOT"));
    }
    if ((bool)ND::params().GetParameterI("psycheND280Utils.PionSI.UseNEUTCascadeProd6TFix")){
      sprintf(inputFileNameMC,"%s/data/PionSI/SIPionXsecMCto8GeV_NEUTCascade_p6Tfix.dat",getenv("PSYCHEND280UTILSROOT"));

    }

    anaUtils::LoadPionCrossSections(inputFileNameMC, _xsec_mc, _err_mc);

    /// Fill the vector of the weights to exclude
    sprintf(inputFileNameExclude,"%s/data/PionSI/PionSIExcludedWeights.dat",getenv("PSYCHESYSTEMATICSROOT"));

    std::ifstream file(inputFileNameExclude);
    if (file.is_open()){
      std::string line;
      while(getline(file, line)){
        ExcludedWeights excWeights;
        std::istringstream iss(line);
        iss >> excWeights.IntBin;
        unsigned int momBin;
        while (iss >> momBin){
          excWeights.momBins.insert(momBin);  
        }
        _excludedWeights.push_back(excWeights);
      }
      file.close();
    } 

  }

#ifdef DEBUG

  PrintExcludedWeights();

#endif

  SetNParameters(GetNBins());

  _useToyBasedPionSI = (bool)ND::params().GetParameterI("psycheSystematics.PionSI.UseToyBasedPionSI");

  // Interaction types
  _interactionID[0]=0;  // Abs
  _interactionID[1]=1;  // CEX
  _interactionID[2]=4;  // QE

  _pionWeightInfo = NULL;
  _pionSIManager  = NULL;

  _initialized   = false;

  _pionWeightInfoToy = NULL;


}
//********************************************************************
void SIPionSystematics::Initialize(){
  //********************************************************************

  if (_initialized) return;

  if (!_pionSIManager)
    _pionSIManager = new PionSIManager();

  _initialized   = true;

}

//********************************************************************
SIPionSystematics::~SIPionSystematics(){
  //********************************************************************

  std::map<Int_t, std::pair<TGraphErrors*,TGraph*> > xsecs = PiXSec::AllXSecs;
  std::map<Int_t, std::pair<TGraphErrors*,TGraph*> >::iterator it;

  for (it = xsecs.begin(); it != xsecs.end(); it++) {
    delete it->second.first;
    delete it->second.second;
  }

  if (_pionSIManager)
    delete _pionSIManager;

  _pionSIManager = NULL;

  if (_pionWeightInfo){
    delete [] _pionWeightInfo;
  }

  ClearPionWeightInfoToy();

}

//********************************************************************
PionInteractionSystematic* SIPionSystematics::GetPionWeightInfo(const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel){ 
  //********************************************************************

  ClearPionWeightInfoToy();

  Int_t uniqueID = 0;

#ifdef MULTITHREAD
  uniqueID = event.UniqueID;
#else
  (void)event;
#endif

  if (!_useToyBasedPionSI){
    return  _pionWeightInfo[uniqueID];
  }

  const AnaEventB& eventB = *static_cast<const AnaEventB*>(&event); 

  _pionWeightInfoToy = _pionSIManager->ComputePionWeightInfo(eventB, sel, box.SuccessfulBranch);

  return _pionWeightInfoToy;

}


//********************************************************************
Weight_h SIPionSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel){
  //********************************************************************

  Weight_h eventWeight;

  PionInteractionSystematic& pionSI = *GetPionWeightInfo(event, box, sel); 

#ifdef DEBUG
  std::cout << "nPions = " << pionSI.nPions << std::endl;
#endif

  // Only bother doing anything if there is at least one pion in the event.
  if(pionSI.nPions == 0) return eventWeight;

  // Correction part,  available from the beginning: scales MC cross-sections to data
  if (!_useMCtoDataOnTheFly){
    eventWeight.Correction = pionSI.weightMCToData;
  }

  if (!TMath::Finite(eventWeight.Correction) || eventWeight.Correction != eventWeight.Correction){
    return Weight_h(1);
  }

  //Start by defining the number density of carbon in FGD Scintillator.
  Float_t nC = 4.6487939E22;

  //Loop over all the saved steps.
  //For adding up what is computed in each step, to feed to the final exponential.
  Float_t weightExp[3] = {0,0,0};

  Float_t weightExpCorr[3] = {0,0,0};

  bool exclude = false;

  int stepsConsidered = 0;

  //The weight we will be calculating for the event.
  Float_t siUncWeight[3] = {1,1,1};

  Float_t siUncWeightCorr[3] = {1,1,1};

  //Loop over the pions.
  for(int ns = 0; ns < pionSI.nPions; ns++){

    // For example, for inclusive selection only when the lepton candidate is a true pion (or its ancestor) should be considered. Other tracks contribute at second order
    if (!sel.IsRelevantTrueObjectForSystematicInToy(event,box,pionSI.TrueParticles[ns],SystId::kSIPion,box.SuccessfulBranch)) continue;

#ifdef DEBUG
    std::cout << "nSteps = " << pionSI.nSteps[ns] << std::endl;          
#endif
    //Loop over only the steps belonging to that pion in the stepLengths array.
    //Note: totalSteps is necessarily the sum over nSteps[nPions]
    for(unsigned int ts = stepsConsidered; ts < (unsigned int)(stepsConsidered + pionSI.nSteps[ns]); ts++){

#ifdef DEBUG
      std::cout << "ts = " << ts << std::endl;          
#endif
      //baseAnalysis puts a limit of 128 on ts.  So, enforce that limit here.
      if (ts >= 128) break;

      //Steps are taken at 10 MeV/c momentum intervals.  Use this to compute the kinetic
      //energy of a step using the initial momentum of the pion and the number of steps
      Float_t pStep = pionSI.initMom[ns] - 10.0*((Float_t)(ts - stepsConsidered));
#ifdef DEBUG
      std::cout << "pStep = " << pStep << std::endl;          
#endif
      //Now, the pStep needs to be converted to the correct bin number to take the cross
      //section from.  We're probably better off rounding properly, so divide pStep by 10.0, add
      //0.5, then cast to int.
      int unsigned momBin = (int)((pStep*0.1) + 0.5);
#ifdef DEBUG
      std::cout << "momBin = " << momBin << std::endl;          
#endif
      //If the bin number is larger than the maximum (i.e. the momentum is larger
      //than 2000 MeV/c) use the information in the last bin.
      if (momBin > NMAXMOMBINS-1) momBin = NMAXMOMBINS-1;

      //Now compute the nominal and varied cross section multiplied by the step length.
      //Remember to convert the cross section to cm^2  (multiply by 1E-27)
      //and step length to cm (multiply by 0.1) to match the
      //number density of Carbon (particles/cm^3).
      //If the pion was travelling through a material other than FGD Scintillator,
      //the contribution to the step length was pre-scaled to an FGD scintillator equivalent
      //length so could just use the properties of FGD scintillator , and the
      //cross section on Carbon while stepping.

      //Note: Stepping is ostensibly for computing survival probability, but we're really
      //interested in P_(data + unc)/P_(data).  Exp(data+unc)/Exp(data) = Exp(unc),
      //so we would only need to use the uncertainties while stepping.  However, since some
      //of the extrapolated uncertainties are so large that the data+unc*sigmafraction would be
      //less than zero (non-physical), so have to add the cross section to the fraction
      //sigma (which could be positive or negative), use zero if it is negative, then subtract the
      //data cross section.

      //Use the pi+ data for pi+ (offset=0)
      //If it's not a pi+, it's a pi-, for which we use the pi- data (offset=100)
      int pim_offset = 0;
      if(pionSI.pionType[ns] != 1) pim_offset = 100;

      for (Int_t mech=0;mech<3;mech++){
        // No CEX systematic for CCOther when the pion is negative. Charge exchange 
        //              if (mech==1 && box.SuccessfulBranch==2 && pionSI.pionType[ns] == 0) continue;
        //              if (mech==0 && box.SuccessfulBranch==0 && toy.Variations[mech]>0) continue;
        //              if (mech==0 && box.SuccessfulBranch==2 && toy.Variations[mech]<0) continue;

        if (!_useMCtoDataOnTheFly){
          weightExp[mech] += (std::max((Float_t)(_xsec_data[_interactionID[mech]+pim_offset][momBin] + _err_data[_interactionID[mech]+pim_offset][momBin] * 
                  toy.GetToyVariations(_index)->Variations[mech]),(Float_t)0.0) 
              - ( _xsec_data[_interactionID[mech]+pim_offset][momBin]))*(1E-27)*(0.1)*pionSI.stepLengths[ts];
        }
        else{

          // First check whether the weights are not the ones to be excluded
          exclude = CheckIsExcludedWeight(_interactionID[mech]+pim_offset, momBin);


          if (exclude){
#ifdef DEBUG
            std::cout << " Excluded weight!!! survival - #int, mech, intType, momBin, xsec, xsec_err, throw  " << "\t" << mech << "\t" << _interactionID[mech] + pim_offset << "\t" << momBin << "\t" << _xsec_data[_interactionID[mech] + pim_offset][momBin]  << "\t" <<  _err_data[_interactionID[mech]+ pim_offset][momBin]  << "\t"  << toy.GetToyVariations(_index)->Variations[mech] << std::endl;
            std::cout << " - #int, mech, intType, momBin, xsec_mc, xsec_err_mc " << "\t" << mech << "\t" << _interactionID[mech] + pim_offset << "\t" << momBin << "\t" << _xsec_mc[_interactionID[mech] + pim_offset][momBin]  << "\t" <<  _err_mc[_interactionID[mech] + pim_offset][momBin] <<  std::endl;
#endif
            weightExp[mech] += (std::max((Float_t)(_xsec_data[_interactionID[mech]+pim_offset][momBin] + _err_data[_interactionID[mech]+pim_offset][momBin] * 
                    toy.GetToyVariations(_index)->Variations[mech]),(Float_t)0.0) 
                - ( _xsec_data[_interactionID[mech]+pim_offset][momBin]))*(1E-27)*(0.1)*pionSI.stepLengths[ts];
            
            weightExpCorr[mech] += 0.; // no re-weight


          }
          else {

            weightExp[mech] += (std::max((Float_t)(_xsec_data[_interactionID[mech]+pim_offset][momBin] + _err_data[_interactionID[mech]+pim_offset][momBin] * 
                    toy.GetToyVariations(_index)->Variations[mech]),(Float_t)0.0) 
                - ( _xsec_mc[_interactionID[mech]+pim_offset][momBin]))*(1E-27)*(0.1)*pionSI.stepLengths[ts];

            weightExpCorr[mech] += (std::max((Float_t)(_xsec_data[_interactionID[mech]+pim_offset][momBin]),(Float_t)0.0) 
                - ( _xsec_mc[_interactionID[mech]+pim_offset][momBin]))*(1E-27)*(0.1)*pionSI.stepLengths[ts];
          }
        }
        
       
        
        
#ifdef DEBUG
      std::cout << _interactionID[mech] + pim_offset << " " <<   _xsec_data[_interactionID[mech] + pim_offset][momBin] << " " << _err_data[_interactionID[mech] + pim_offset][momBin] << " " << pionSI.stepLengths[ts]   << std::endl; 
      if (_useMCtoDataOnTheFly && !exclude){
        std::cout << _interactionID[mech] + pim_offset << " " <<  _xsec_mc[_interactionID[mech] + pim_offset][momBin] << " " << _err_mc[_interactionID[mech] + pim_offset][momBin] << " " << pionSI.stepLengths[ts]   << std::endl; 
      }

      std::cout << " int,  weightExp, weightExpCorr = " << _interactionID[mech]+pim_offset << " " << weightExp[mech] << " " << weightExpCorr[mech] << std::endl;          
#endif


      }

#ifdef DEBUG 
      std::cout << " step finalized,  weightExp, weightExpCorr = " << ts << " " << weightExp[0] << " " << weightExp[1] << " " << weightExp[2] << " " << weightExpCorr[0] << " " << weightExpCorr[1] << " " << weightExpCorr[2] << std::endl;          
#endif
    }//Close loop over this pion's steps.

    //Having considered this pion's steps,
    //add the number of steps taken by this pion to the stepsConsidered counter.
    stepsConsidered += pionSI.nSteps[ns];

  }//Close loop over pions.

  //Multiply weightExp by the number density of Carbon, and compute the portion of the weight
  //that is due to the survival probability.
  for (int mech=0;mech<3;mech++){
    siUncWeight[mech] = exp(-nC*weightExp[mech]);
    siUncWeightCorr[mech] = exp(-nC*weightExpCorr[mech]);



#ifdef DEBUG
    std::cout << "siUncWeight[mech]  mech " << mech << " " << siUncWeight[mech] << std::endl;          

    std::cout << "siUncWeightCorr[mech]  mech " << mech << " " << siUncWeightCorr[mech] << std::endl;          

#endif

  }

#ifdef DEBUG
  std::cout << "nInteractions = " << pionSI.nInteractions << std::endl; 


#endif

  //With the survival probability portion of the weight calculated, apply the correct interaction cross section factors.
  //Loop over the interactions 
  for(int ii = 0; ii < pionSI.nInteractions; ii++){

    // only consider the interactions corresponding to relevant pions
    if (!sel.IsRelevantTrueObjectForSystematicInToy(event,box,pionSI.InteractionTrueParticles[ii],SystId::kSIPion,box.SuccessfulBranch)) continue;

    //Convert the momentum of the interaction to a bin number.
    unsigned int momBin = (int)((pionSI.pInteraction[ii]*0.1) + 0.5);

    //If the bin number is larger than the maximum (i.e. the momentum is larger
    //than 2000 MeV/c) use the information in the last bin.
    // if (momBin > NMAXMOMBINS-1) momBin = NMAXMOMBINS-1;
    if (momBin > NMAXMOMBINS) momBin = NMAXMOMBINS;

    int intType = pionSI.typeInteraction[ii];      

    //Interactions: 4, 0, 1.
    //Materials: 0, 20, 60, 70, 80, 10, 30, 40, 50
    //Due to pi- being non-insignificant, go back and forth
    //between pi+ and pi- (add 100 for pi-)
    //Also, only apply the weight if the data cross section is
    //non-zero. (The data value is rarely 0.0.  This only happens when the extrapolation
    //encounters a MC cross section of 0.0.  There may be a more correct way of handling this,
    //but since it affects a small number of points, this should suffice.)
    //Additionally, do not apply a negative weight.

    if(_xsec_data[intType][momBin] != 0.0){
      int mech;
      if      (intType%10 == _interactionID[0]) mech = 0;
      else if (intType%10 == _interactionID[1]) mech = 1;
      else if (intType%10 == _interactionID[2]) mech = 2;
      else break;

      //            if (mech==0 && box.SuccessfulBranch==0 && toy.Variations[mech]>0) continue;
      //            if (mech==0 && box.SuccessfulBranch==2 && toy.Variations[mech]<0) continue;
      if (!_useMCtoDataOnTheFly){

        siUncWeight[mech] *= (std::max((Float_t)(_xsec_data[intType][momBin] 
                + _err_data[intType][momBin] * toy.GetToyVariations(_index)->Variations[mech]),(Float_t)0.0)
            /_xsec_data[intType][momBin]);  
      }
      else{

        // First check whether the weights are not the ones to be excluded
        exclude = CheckIsExcludedWeight(intType, momBin);

        // Do only data systematic
        // And do not apply the correction
        if (exclude){

#ifdef DEBUG
          std::cout << " Excluded weight!!! interaction  - #mech, intType, momBin, xsec, xsec_err, throw  " << "\t" << mech << "\t" << intType << "\t" << momBin << "\t" << _xsec_data[intType][momBin]  << "\t" <<  _err_data[intType][momBin]  << "\t"  << toy.GetToyVariations(_index)->Variations[mech] << std::endl;
          std::cout << " - #mech, intType, momBin, xsec_mc, xsec_err_mc " << "\t" << mech << "\t" << intType << "\t" << momBin << "\t" << _xsec_mc[intType][momBin]  << "\t" <<  _err_mc[intType][momBin] <<  std::endl;
#endif


          siUncWeight[mech] *= (std::max((Float_t)(_xsec_data[intType][momBin] 
                  + _err_data[intType][momBin] * toy.GetToyVariations(_index)->Variations[mech]),(Float_t)0.0)
              /_xsec_data[intType][momBin]); 

          siUncWeightCorr[mech] *= 1.;
        }
        else{
          if(_xsec_mc[intType][momBin] != 0.0){

            siUncWeight[mech] *= (std::max((Float_t)(_xsec_data[intType][momBin] 
                    + _err_data[intType][momBin] * toy.GetToyVariations(_index)->Variations[mech]),(Float_t)0.0)
                /_xsec_mc[intType][momBin]); 

            siUncWeightCorr[mech] *= (std::max((Float_t)(_xsec_data[intType][momBin]),(Float_t)0.0)
                /_xsec_mc[intType][momBin]); 
          }
          else{
#ifdef DEBUG
            std::cout << " - #WARNING! zero MC xsec:  mech, intType, momBin, xsec_mc, xsec_err_mc " << "\t" << mech << "\t" << intType << "\t" << momBin << "\t" << _xsec_mc[intType][momBin]  << "\t" <<  _err_mc[intType][momBin] <<  std::endl;
#endif
          }
        }
      }

#ifdef DEBUG
      std::cout << " - #mech, intType, momBin, xsec, xsec_err, throw  " << "\t" << mech << "\t" << intType << "\t" << momBin << "\t" << _xsec_data[intType][momBin]  << "\t" <<  _err_data[intType][momBin]  << "\t"  << toy.GetToyVariations(_index)->Variations[mech] << std::endl;
      if (_useMCtoDataOnTheFly && !exclude){
        std::cout << " - #mech, intType, momBin, xsec_mc, xsec_err_mc " << "\t" << mech << "\t" << intType << "\t" << momBin << "\t" << _xsec_mc[intType][momBin]  << "\t" <<  _err_mc[intType][momBin] <<  std::endl;
      }
#endif
    }

  }//Close loop over the interactions.

  //With all the interactions looped over, all additional weights should be applied.
  //Apply this weight and the MC to data weight.
  Float_t siUncWeightTotal = 1.;
  Float_t siUncWeightTotalCorr = 1.;
  for (int mech=0;mech<3;mech++){
    siUncWeightTotal *= siUncWeight[mech];
    siUncWeightTotalCorr *= siUncWeightCorr[mech];

#ifdef DEBUG
    std::cout << mech << " siUncWeight[mech]="     << siUncWeight[mech]     << std::endl;
    std::cout << mech << " siUncWeightCorr[mech]=" << siUncWeightCorr[mech] << std::endl;    
#endif
  }


  if (!_useMCtoDataOnTheFly){
    eventWeight.Systematic = eventWeight.Correction * siUncWeightTotal;
  }
  else{
    eventWeight.Systematic = siUncWeightTotal;
    eventWeight.Correction = siUncWeightTotalCorr;
  }


#ifdef DEBUG
  const AnaEventB& eventB = *static_cast<const AnaEventB*>(&event);
  std::cout << "evt, subrun, run, nPions, nInteractions= " << eventB.EventInfo.Event << " " << eventB.EventInfo.SubRun << " " << eventB.EventInfo.Run << " " << pionSI.nPions << " " << pionSI.nInteractions << " weight = " << eventWeight << std::endl;
#endif  

  if (!TMath::Finite(eventWeight.Systematic) || eventWeight.Systematic != eventWeight.Systematic){

#ifdef DEBUG
    std::cout << "inifinite or NaN: " << eventB.EventInfo.Event << " " << eventB.EventInfo.SubRun << " " << eventB.EventInfo.Run << " " << pionSI.nPions << " " << pionSI.nInteractions << " " << eventWeight << std::endl;

    for (int mech=0;mech<3;mech++)
      std::cout << mech << " " << siUncWeight[mech] << " " << toy.GetToyVariations(_index)->Variations[mech] << " " << pionSI.weightMCToData << std::endl;
#endif  
    // Fall back to correction only  
    eventWeight.Systematic = eventWeight.Correction;
  }

  return eventWeight;
}

//********************************************************************
void SIPionSystematics::FillSystBox(const AnaEventC& eventC, const SelectionBase& sel, Int_t ibranch){
  //********************************************************************

  (void)sel;
  (void)ibranch;

  Int_t uniqueID = 0;    
#ifdef MULTITHREAD
  uniqueID = eventC.UniqueID;
#endif

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventC); 

  // Compute Pion weight info needed by PionSISystematics (TODO, only when this systematic is enabled)
  if (!_useToyBasedPionSI){
    _pionWeightInfo[uniqueID] = _pionSIManager->ComputePionWeightInfo(event, sel, ibranch);
  }
}

//********************************************************************
void SIPionSystematics::InitializeSystBoxes(Int_t nsel, Int_t isel, Int_t nbranches, Int_t nevents){
  //********************************************************************

  Initialize();

  //  TODO: This is a temporary solution to make this work with multithreading. Instead we would need a derived SystBox

  // Although the SystBox is actually not used we need to create it because SystematicBase::InitializeEvent uses it
  EventWeightBase::InitializeSystBoxes(nsel,isel,nbranches,nevents);

  // Since this is called for several selections use for the moment a single one for all selections
  if (_pionWeightInfo) return;

#ifndef MULTITHREAD
  nevents=1;
#endif

  _pionWeightInfo = new PionInteractionSystematic*[nevents];
  for (Int_t k= 0;k<nevents;k++)
    _pionWeightInfo[k]=NULL;
}


//********************************************************************
void SIPionSystematics::FinalizeEvent(const AnaEventC& event){
  //********************************************************************

  ClearPionWeightInfoToy();

  //  TODO: This is a temporary solution to make this work with multithreading. Instead we would need a derived SystBox

  // Although the SystBox is actually not used we need to create it because SystematicBase::FinalizeEvent uses it
  EventWeightBase::FinalizeEvent(event);

  Int_t uniqueID = 0;
#ifdef MULTITHREAD
  uniqueID = event.UniqueID;
#endif

  if (_pionWeightInfo[uniqueID])
    delete _pionWeightInfo[uniqueID];
  _pionWeightInfo[uniqueID]=NULL;

}




//********************************************************************
bool SIPionSystematics::CheckIsExcludedWeight(int intType, unsigned int momBin){
  //********************************************************************

  bool exclude = false;


  std::vector<ExcludedWeights>::const_iterator it = _excludedWeights.begin();

  for(; it != _excludedWeights.end(); it++){
    // First check the interaction 
    if (intType == (*it).IntBin){
      if ((*it).momBins.find(momBin) != (*it).momBins.end()){
        exclude = true;
        return exclude;
      }   
    }
  }
  return exclude;
}

//********************************************************************
void SIPionSystematics::PrintExcludedWeights(){
  //********************************************************************

  std::cout << " ***** Pion SI excluded weights ***** " << std::endl;

  std::vector<ExcludedWeights>::const_iterator it = _excludedWeights.begin();
  std::set<unsigned int>::const_iterator it1;

  for(; it != _excludedWeights.end(); it++){
    std::cout << " Interaction\t " << (*it).IntBin << std::endl;
    for (it1 = (*it).momBins.begin(); it1 != (*it).momBins.end(); it1++){
      std::cout << " MomBin\t " << (*it1) << std::endl;
    }
  }

  std::cout << " *****  ***** " << std::endl;

}
