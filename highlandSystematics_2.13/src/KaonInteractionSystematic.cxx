#include "KaonInteractionSystematic.hxx"
#include "TFile.h"

//#define DEBUG
//#define DDEBUG
//#define DDDEBUG

//********************************************************************
TGraph* kaon_si::CrossSectionData::CreateCompositeCrossSectionData(
    const ParticleId::PdgEnum& pdg,
    const si_syst::InteractionType& type, 
    const std::vector<std::pair< si_syst::MaterialEnum, Float_t> >& input
    ) const{
  //********************************************************************
  
  std::vector<std::pair< si_syst::MaterialEnum, Float_t> >::const_iterator iter = input.begin();
 
  // Note! adding of graphs does no exist in ROOT,  have to do it ourselves
  
  
  HASSERT(input.size() != 0);
  
  // Use first input graph to define the graph`s X axis
  // may substitute with the one having wider/smaller ? range in momentum
  TGraph* graph1 = GetCrossSectionData(pdg, type, iter->first);
  
  HASSERT(graph1);
 
  Int_t nArray        = graph1->GetN(); 
  Double_t* momArray  = graph1->GetX();
  Double_t* xsecArray = new Double_t[nArray](); // value initialized
  
  
  // Make sure that the fractions sum-up to one
  Double_t totalMolFrac = 0.;
  for (; iter != input.end(); iter++)
    totalMolFrac += iter->second;


  HASSERT(totalMolFrac != 0.);
   
  
  for (; iter != input.end(); iter++){
    
    // Get cross-section data
    TGraph* graph_tmp = GetCrossSectionData(pdg, type, iter->first);
    
    HASSERT(graph_tmp);
   
    // Since not require all graphs to be of the same bins, need to loop and interpolate here, will take a while
    for (int i = 0; i < nArray; i++){
      // Xsection value scaled by the molar fraction 
      xsecArray[i] += (iter->second / totalMolFrac) * (graph_tmp->Eval(momArray[i])); // linear interpolation used
    
    }
  }
  
  TGraph* graph_out = new TGraph(nArray, momArray, xsecArray);
  
  delete [] xsecArray;
  
  return graph_out;
  
}


 
//********************************************************************
void kaon_si::KaonSIPropagator::InitializeCrossSectionData(){
//********************************************************************
  
#ifdef DEBUG
  std::cout << " ======= " << std::endl;
  std::cout << " kaon_si::KaonSIPropagator::InitializeCrossSectionData " << std::endl;
#endif 
  
  // Read the cross-sections
  char inputFileName[256];
  sprintf(inputFileName, "%s/data/KaonSI/kaon_plus_cross_sections.root", getenv("HIGHLANDSYSTEMATICSROOT"));

  
  // Open the root file with the cross sections
  TFile* file = new TFile(inputFileName);
  HASSERT(file);
   
  // Start getting the cross-section data: for the moment exact names can make
  std::string materials[] = {"Carbon", "Oxygen", "Aluminium", "Iron"}; 
  
  size_t count = sizeof(materials)/sizeof(materials[0]);
  
  for (size_t i = 0; i < count; i++){
    
    si_syst::MaterialEnum material = si_syst::GetMaterialEnum(materials[i]);
    
    // Inelastic 
    std::string name = "inelastic_kaon_plus_" + materials[i];
    TGraph* graph = (TGraph*)file->Get(name.c_str());
    HASSERT(graph); 
    
    // Add data
    AddCrossSectionData(ParticleId::kKPosPDG, si_syst::kInelastic, material, graph);
   
    // Eelastic 
    name = "elastic_kaon_plus_" + materials[i];
    graph = (TGraph*)file->Get(name.c_str());
    HASSERT(graph); 
    
    // Add data
    AddCrossSectionData(ParticleId::kKPosPDG, si_syst::kElastic, material, graph);
  }
  
  // So at this moment should have the cross-section filled for the "basic" elements, now 
  // do the composite materials
  // Have to be explicit here
  // Data from pion SI,  will be moved to Secondary interactions or similar
  
  std::vector<std::pair<si_syst::MaterialEnum, Float_t> > material_data;
  
  //****************
  //AlG10
  //----------------
  // 1 0.386397
  // 5 0.0128006
  // 6 0.192469
  // 8 0.120531
  // 11 0.00601091
  // 13 0.232802
  // 14 0.0489891
 
  //Ignore H
  //Use B and C as C
  material_data.push_back(std::make_pair(si_syst::kCarbon, 0.0128006 + 0.192469));

  //Use O for O.
  material_data.push_back(std::make_pair(si_syst::kOxygen, 0.120531));

  //Ignore Na
  //Use Al for Al and Si
  material_data.push_back(std::make_pair(si_syst::kAluminium, 0.232802 + 0.0489891));

  // Calculate and fill the composite cross-sections
  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kElastic,
      si_syst::kAlG10, 
      material_data
      );
 
  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kInelastic,
      si_syst::kAlG10, 
      material_data
      );
  

  
  //***************
  //WaterSystem
  //---------------
  // 1 0.283046
  // 6 0.17602
  // 8 0.463356
  // 26 0.0714256
  // 27 0.00615247
  //***************
  
  material_data.clear();
  
  //Ignore H.
  //Use C for C
  material_data.push_back(std::make_pair(si_syst::kCarbon, 0.17602));

  //Use O for O
  material_data.push_back(std::make_pair(si_syst::kOxygen, 0.463356));
  
  //Use Fe for Fe and Co
  material_data.push_back(std::make_pair(si_syst::kIron, 0.0714256 + 0.00615247));
  
  // Calculate and fill the composite cross-sections

  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kElastic,
      si_syst::kWaterSystem, 
      material_data
      );
 
  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kInelastic,
      si_syst::kWaterSystem, 
      material_data
      );

  //***************
  //G10FGD1, G10
  //(Only differ by density)
  //---------------
  // 1 0.503647
  // 5 0.0166849
  // 6 0.250872
  // 8 0.157106
  // 11 0.00783488
  // 14 0.0638545
  //***************
  
  material_data.clear();
  
  //Ignore H
  //Use C for B and C
  material_data.push_back(std::make_pair(si_syst::kCarbon, 0.0166849 + 0.250872));

  //Use O for O
  material_data.push_back(std::make_pair(si_syst::kOxygen, 0.157106));
  
  //Ignore Na
  //Use Al for Si
  material_data.push_back(std::make_pair(si_syst::kAluminium, 0.0638545));

  // Calculate and fill the composite cross-sections

  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kElastic,
      si_syst::kG10, 
      material_data
      );
 
  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kInelastic, 
      si_syst::kG10, 
      material_data
      );
  
  //***************
  //FGDGlue
  //---------------
  // 1 0.568911
  // 6 0.158577
  // 7 0.00584825
  // 8 0.266664
  //***************
  
  material_data.clear();
 
  //Ignore H
  //Use C for C and N
  material_data.push_back(std::make_pair(si_syst::kCarbon, 0.158577 + 0.00584825));

  //Use O for O
  material_data.push_back(std::make_pair(si_syst::kOxygen, 0.266664));
 
  // Calculate and fill the composite cross-sections

  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kElastic,
      si_syst::kFGDGlue, 
      material_data
      );
 
  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kInelastic,
      si_syst::kFGDGlue, 
      material_data
      );
  
  //***************
  //G10Roha
  //-------------
  // 1 0.498217
  // 5 0.0126443
  // 6 0.262956
  // 8 0.148193
  // 11 0.00593749
  // 14 0.0483907
  // 29 0.0236613
  //***************
  
  material_data.clear();
  
  //Ignore H
  //Use C for B and C.
  material_data.push_back(std::make_pair(si_syst::kCarbon, 0.0126443 + 0.262956));

  //Use O for O.
  material_data.push_back(std::make_pair(si_syst::kOxygen, 0.148193));

  //Ignore Na.
  //Use Al for Si.
  material_data.push_back(std::make_pair(si_syst::kAluminium, 0.0483907));

  //Use Fe for Cu.
  material_data.push_back(std::make_pair(si_syst::kIron, 0.0236613));

  // Calculate and fill the composite cross-sections

  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kElastic,
      si_syst::kG10Roha, 
      material_data
      );
 
  AddCompositeCrossSectionData(
      ParticleId::kKPosPDG,
      si_syst::kInelastic,
      si_syst::kG10Roha, 
      material_data
      );
  
  
  
  // Estimate the weights
  // This is basically the values needed to multiply the inelsatic cross-section to match data
  // Estimated from the carbon data
 
  // Get the carbon cross-section
  const TGraph* inelastic_carbon_geant4 = GetCrossSectionData(ParticleId::kKPosPDG, si_syst::kInelastic, si_syst::kCarbon);
  HASSERT(inelastic_carbon_geant4);
  
  TGraph* inelastic_carbon_reweight = (TGraph*)file->Get("inelastic_kaon_plus_Carbon_reweight");
  HASSERT(inelastic_carbon_reweight);
 
  if (_inelastic_weights) delete _inelastic_weights;
  
  _inelastic_weights = new TGraph();
  
  Double_t pointX, pointY;
  for (int i =0; i < inelastic_carbon_geant4->GetN(); i++){
    
    if (inelastic_carbon_geant4->GetPoint(i, pointX, pointY) < 0) continue;
    
    if (pointY <= 0) continue;
      
    _inelastic_weights->SetPoint(_inelastic_weights->GetN(), pointX, inelastic_carbon_reweight->Eval(pointX) / pointY);
  }
  
    
#ifdef DEBUG
  std::cout << " ======= " << std::endl;
#endif 
  
}

//********************************************************************
Double_t kaon_si::KaonSIPropagator::GetCrossSection(const si_syst::InteractionType& type, const Float_t& mom, const Int_t& pdg, TGeoNode* node) const{
//********************************************************************
 
  if (type != si_syst::kInelastic && type != si_syst::kElastic) return 0.; 
 
  // Only kaon plus for the moment
  if (pdg != ParticleId::kKPosPDG) return 0.; 
   
  TGeoVolume *volume        = node->GetVolume();
  TGeoMaterial *material    = volume->GetMaterial();
 
  // Get the cross-section graph
  TGraph* data = _xsecData.GetCrossSectionData(
      static_cast<ParticleId::PdgEnum>(pdg), // bit dangerous 
      type, 
      si_syst::GetMaterialEnum(material->GetName())
      );
  
  HASSERT(data);
  
  return data->Eval(mom) * units::millibarn; // linear interpolation
  
}

//********************************************************************
Double_t kaon_si::KaonSIPropagator::GetReferenceCrossSection(const si_syst::InteractionType& type, const Float_t& mom, const Int_t& pdg, TGeoNode* node) const{
//********************************************************************
 
  if (type != si_syst::kInelastic && type != si_syst::kElastic) return 0.; 
 
  // Only kaon plus for the moment
  if (pdg != ParticleId::kKPosPDG) return 0.; 
   
  TGeoVolume *volume        = node->GetVolume();
  TGeoMaterial *material    = volume->GetMaterial();
 
  // Get the cross-section graph:
  TGraph* data = _xsecData.GetCrossSectionData(
      static_cast<ParticleId::PdgEnum>(pdg), // bit dangerous 
      type, 
      si_syst::GetMaterialEnum(material->GetName())
      );
  
  HASSERT(data);
  HASSERT(_inelastic_weights);
  
  // Elastic
  if (type == si_syst::kElastic) return data->Eval(mom) * _elastic_scale * units::millibarn;
 
  // Inelastic
  return data->Eval(mom) * _inelastic_weights->Eval(mom) * units::millibarn; // linear interpolation
  
}


//********************************************************************
Bool_t kaon_si::KaonSIPropagator::InVOI(const TVector3& pos) const{
  //********************************************************************
  
  if (_det == SubDetId::kFGD1){
    // This is the edges of the FGD1 volume, plus all the way out to TPCGasMixture in downstream z.
    // (Rounded to the next integer value that includes the value from the geometry in its range).
    Bool_t xOK = -1150.0 < pos.X() && pos.X() < 1150.0;
    Bool_t yOK = -1170.0 < pos.Y() && pos.Y() < 1230.0;
    Bool_t zOK = 98.0 < pos.Z() && pos.Z() < 576.0;

    return xOK && yOK && zOK;
  }
  else if (_det == SubDetId::kFGD2){
    // This is from the TPCGasMixture in upstream z through FGD2 all the way out to TPCGasMixture in downstream z.
    // (Rounded to the next integer value that includes the value from the geometry in its range).
    Bool_t xOK = -1150.0 < pos.X() && pos.X() < 1150.0;
    Bool_t yOK = -1170.0 < pos.Y() && pos.Y() < 1230.0;
    Bool_t zOK = 1347.0 < pos.Z() && pos.Z() < 1934.0;
    return xOK && yOK && zOK;
  }
  return false;

}


