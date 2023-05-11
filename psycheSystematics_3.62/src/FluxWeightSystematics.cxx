#include "FluxWeightSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "ToyBoxND280.hxx"
#include "TDecompChol.h"
#include "Parameters.hxx"

//#define DEBUG

//********************************************************************
FluxWeightSystematics::FluxWeightSystematics(const std::string& file, bool apply_syst, FluxWeighting::Plane plane):
  _ndplane(plane), _file(file), _apply_syst(apply_syst){
  //********************************************************************

  InitializeSystematics();

}

//********************************************************************
FluxWeightSystematics::FluxWeightSystematics(bool apply_syst, FluxWeighting::Plane plane):_ndplane(plane), _apply_syst(apply_syst){
  //********************************************************************

  
  std::string cov_file_name = ND::params().GetParameterS("psycheSystematics.FluxCov.File");
  

  _file = std::string(getenv("PSYCHESYSTEMATICSROOT")) + cov_file_name;

  InitializeSystematics();

}

//********************************************************************
void FluxWeightSystematics::InitializeSystematics(){
  //********************************************************************

  _params     = NULL;
  _root_file  = NULL;

  std::cout << " \n******************************************************************** " << std::endl;
  std::cout << " FluxWeightSystematics: start initialization" << std::endl;

  std::cout << "Create FluxWeight in FluxWeightSystematics: " << std::endl;
  _flux = new FluxWeighting();  

  std::cout << " Read covariance matrix from file: " << _file << std::endl;

  // Do not fill if the systeamtic wont` be called
  if (!_apply_syst){
    std::cout << " FluxWeightSystematics:: running with no systematics applied - weight only " << std::endl;
    return;
  }
  
  // Open the TFile

  _root_file = TFile::Open(_file.c_str(), "READ");

  if (_root_file->IsZombie()){
    std::cerr << "Cannot open input file '" << _file << "'. Exit!" << std::endl;
    exit(1);
  }

  // Start reading and filling the bins

  std::cout << " \nStart filling bins "        << std::endl;
  FillBins();
  std::cout << " Finished filling bins\n "     << std::endl;

  std::cout << " \nStart filling matrices "    << std::endl;
  FillMatrices();
  std::cout << " Finished filling matrices\n " << std::endl;


  std::cout << " FluxWeightSystematics: finished initialization" << std::endl;
  std::cout << " ********************************************************************\n " << std::endl;


}

//********************************************************************
void FluxWeightSystematics::FillBins(){
  //********************************************************************

  // Available bins definition
  // This also corresponds to the order used in cov matrix
  const  BinDef bins[8] = {
    BinDef("nd5_numode_numu_bins",    14,  15, 0, 1),
    BinDef("nd5_numode_numub_bins",  -14, -13, 0, 1),
    BinDef("nd5_numode_nue_bins",     12,  13, 0, 1),
    BinDef("nd5_numode_nueb_bins",   -12, -11, 0, 1),
    BinDef("nd5_anumode_numu_bins",   14,  15, 1, 2),
    BinDef("nd5_anumode_numub_bins", -14, -13, 1, 2),
    BinDef("nd5_anumode_nue_bins",    12,  13, 1, 2),
    BinDef("nd5_anumode_nueb_bins",  -12, -13, 1, 2)
  };

  const TArrayD* flux_bins_array;
  TAxis* axis;

  // Initialize params
  _params = new BinnedParams();
  _params->SetName("FluxSyst");
  _params->SetType(BinnedParams::k3D_DATA);

  for (int i = 0; i < 8; i++){

    _root_file->GetObject(bins[i].Name.c_str(), axis); 

    if (!axis){
      std::cout << "FluxWeightSystematics::FillBins: cannot read bin definitions for " << bins[i].Name << std::endl; 
      exit(1);
    }

    flux_bins_array = axis->GetXbins();

    Int_t size = flux_bins_array->GetSize(); 

    if (size < 2){
      std::cout << "FluxWeightSystematics::FillBins: no bins found for " << bins[i].Name << std::endl; 
      exit(1);
    }

    // Start adding the bins
    for (int j = 0; j < size - 1; j++){
      // Add bins
      _params->AddBin(
          bins[i].ModeMin,
          bins[i].ModeMax,
          bins[i].TypeMin,
          bins[i].TypeMax,
          flux_bins_array->GetAt(j) * 1000.,
          flux_bins_array->GetAt(j+1) * 1000., 
          // we do not need the numbers just indexing
          0, 
          0
          );
    }
  }
   
  SetNParameters(_params->GetNBins());

}

//******************************************************************** 
void FluxWeightSystematics::Print(Option_t *option) const{
  //******************************************************************** 
  (void)option;

  std::cout << " \n***** Bins for the FluxWeightSystematics **** " << std::endl;

  if (_params) _params->Print();
  
  std::cout << "\n" << std::endl;
  
  if (_cov_matrix) _cov_matrix->Print();
    
  std::cout << " *********\n " << std::endl;

}  


//********************************************************************
void FluxWeightSystematics::FillMatrices(){
  //********************************************************************

  // Get the matrix from the file
  TMatrixD* matrix;

  _root_file->GetObject("total_flux_cov", matrix); 

  if (!matrix){
    std::cout << "FluxWeightSystematics::FillBins: cannot read matix total_flux_cov " << std::endl; 
    exit(1);
  }

  // Get the number of bins to be considered
  Int_t nbins = _params->GetNBins();
 
  // Check the matrix corresponds to the number of bins: should be larger since
  // has sk
  if (matrix->GetNcols() < nbins || matrix->GetNrows() < nbins){
    std::cout << " FluxWeightSystematics::FillMatrices: input matrix has less bins than needed " << std::endl;
    exit(1);
  }
  
  // Retrieve the part we need
  _cov_matrix = new TMatrixD(matrix->GetSub(0, nbins - 1, 0, nbins - 1)); 
 
  // Do the Cholesky decomposition to get the L matrix
  TDecompChol *chdcmp = new TDecompChol(*_cov_matrix);
  
  if (!chdcmp->Decompose()){
    std::cout << " FluxWeightSystematics::FillMatrices: cannot decompose matrix " << std::endl;
    delete chdcmp;
    exit(1);
  }
  
  // Get the upper matrix
  _L_cov_matrix = new TMatrixD(chdcmp->GetU());
  
  // Get the lower matrix
  _L_cov_matrix->Transpose(*_L_cov_matrix);
 
  delete chdcmp;
  
  if (_L_cov_matrix->GetNcols() != _cov_matrix->GetNcols()){
    std::cout << " FluxWeightSystematics::FillMatrices: problem getting lower matrix " << std::endl;
    exit(1);
  }
  

}


//********************************************************************
Weight_h FluxWeightSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& eventBB, const ToyBoxB& boxB){
  //********************************************************************

  const AnaEventB& event = *static_cast<const AnaEventB*>(&eventBB); 

  // Cast the ToyBox to the appropriate type
  const ToyBoxND280& box = *static_cast<const ToyBoxND280*>(&boxB); 

  Weight_h eventWeight = 1;
  
  if (!box.TrueVertex){
    return eventWeight; // True vertex associated to the recon vertex should exist 
  }
  // In case of sand-muons use ND13 plane
  FluxWeighting::Plane ndplane = _ndplane;

  if (event.GetIsSandMC()) ndplane = FluxWeighting::kND13;

  // Actual mean from FluxWeighting class
  Float_t mean =  _flux->GetWeight(box.TrueVertex, anaUtils::GetRunPeriod(event.EventInfo.Run), ndplane);
  
  // Set both,  corr and systematic
  eventWeight = 1 + (mean - 1);
  
  // Apply systematic only if it is requested
  if (!_apply_syst){
    return eventWeight;
  }
  
  // Do the systematic
  
  // Get the true neutrino energy
  Float_t enu  = box.TrueVertex->NuEnergy;
  int     type = box.TrueVertex->NuPDG;

  int mode = 0;
  if (anaUtils::IsRHC(anaUtils::GetRunPeriod(event.EventInfo.Run)))
    mode = 1;
  
  //// Get the flux error values for this energy
  Float_t syst_val;
  Int_t index;
  if (!_params || !_params->GetBinMeanValue(mode, type, enu, syst_val, index)) return eventWeight;

  // Compute the weight
  eventWeight.Systematic = mean * (1 + toy.GetToyVariations(_index)->Variations[index]);

#ifdef DEBUG
std::cout << "Run: " << event.EventInfo.Run 
<< " mode: "  << mode
<< " type: "  << type
<< " Enu: "   << enu  
<< " index "  << index        << " variation " << toy.GetToyVariations(_index)->Variations[index] 
<< " weight " << eventWeight  << std::endl;
#endif

  return eventWeight;

}

