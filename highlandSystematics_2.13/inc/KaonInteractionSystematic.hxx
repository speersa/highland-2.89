#ifndef KaonInteractionSystematic_h
#define KaonInteractionSystematic_h

#include "SecondaryInteractionSystematic.hxx"
#include "Parameters.hxx"
#include "TGraph.h" 
#include <cassert>
#include "ParticleId.hxx"

/// This exception is thrown when a graph is not found
class NoTGraphFound: public std::runtime_error {
  public:
    NoTGraphFound(const std::string& name) :
      std::runtime_error("No TGraph: " + name + " found ") {
    }
};



namespace kaon_si{

  
  
  

  /// Cross section data storage,  probably TGraph is the lightest object (+flexibility, e.g. spline interpolation,  if needed) 
  typedef std::map<ParticleId::PdgEnum, std::map<si_syst::InteractionType, std::map<si_syst::MaterialEnum, TGraph* > > >                 XSecDataFull;
  typedef std::map<ParticleId::PdgEnum, std::map<si_syst::InteractionType, std::map<si_syst::MaterialEnum, TGraph* > > >::iterator       XSecDataFull_iter;
  typedef std::map<ParticleId::PdgEnum, std::map<si_syst::InteractionType, std::map<si_syst::MaterialEnum, TGraph* > > >::const_iterator XSecDataFull_const_iter;
 
  typedef std::map<si_syst::InteractionType, std::map<si_syst::MaterialEnum, TGraph* > >                 XSecDataIntType;
  typedef std::map<si_syst::InteractionType, std::map<si_syst::MaterialEnum, TGraph* > >::iterator       XSecDataIntType_iter;
  typedef std::map<si_syst::InteractionType, std::map<si_syst::MaterialEnum, TGraph* > >::const_iterator XSecDataIntType_const_iter;
 
  typedef std::map<si_syst::MaterialEnum, TGraph* >                 XSecDataMaterial;
  typedef std::map<si_syst::MaterialEnum, TGraph* >::iterator       XSecDataMaterial_iter;
  typedef std::map<si_syst::MaterialEnum, TGraph* >::const_iterator XSecDataMaterial_const_iter;
 

    
  /// A structure to store cross section data
  /// Particle, Material, InterationType
  /// Also has an ability to store reference data that will be used to normalize the input 
  class CrossSectionData{
  
  public:
    
    CrossSectionData(){}
    
    virtual ~CrossSectionData(){
      ClearData();
    }
    
    /// Add the tgraph cross-section data, clone so that the object owns it
    void AddCrossSectionData(const ParticleId::PdgEnum& pdg,  
        const si_syst::InteractionType& type, 
        const si_syst::MaterialEnum& material,
        TGraph* data){
     
      if (!data) return;
      
     
      if (GetCrossSectionData(pdg, type, material)){
        delete _CrossSections[pdg][type][material];
         _CrossSections[pdg][type][material] = NULL;
      }
      
      _CrossSections[pdg][type][material] = (TGraph*)data->Clone();
        
    }
    
    /// Get the requested cross section data
    TGraph* GetCrossSectionData(const ParticleId::PdgEnum& pdg, 
        const si_syst::InteractionType& type, 
        const si_syst::MaterialEnum& material) const{
      
      XSecDataFull_const_iter     iter1;
      XSecDataIntType_const_iter  iter2;
      XSecDataMaterial_const_iter iter3;
      
      // PDG
      iter1 = _CrossSections.find(pdg);
      if (iter1 == _CrossSections.end()) return NULL;
      
      // Interaction
      iter2 = (iter1->second).find(type);
      if (iter2 == (iter1->second).end()) return NULL;
      
      // Material
      iter3 = (iter2->second).find(material);
      if (iter3 == (iter2->second).end()) return NULL;
      
      return iter3->second;

    }
    
    /// Add composit cross-section data,  one adds the pdg, interaction type, and 
    /// also the list of elements and molar fractions, the elements should be already familiar 
    /// to the class so for this to work
    void AddCompositeCrossSectionData(
        const ParticleId::PdgEnum& pdg,
        const si_syst::InteractionType& type,  
        const si_syst::MaterialEnum& material, 
        const std::vector<std::pair< si_syst::MaterialEnum, Float_t> >& input){
        
      AddCrossSectionData(
          pdg, 
          type,
          material, 
          CreateCompositeCrossSectionData(pdg, type, input)
          ); 
    }
    
    const XSecDataFull& GetCrossSectionData() const{
      return _CrossSections;
    }
    

  protected:
    
    TGraph* CreateCompositeCrossSectionData(
          const ParticleId::PdgEnum&, 
          const si_syst::InteractionType&, 
          const std::vector<std::pair< si_syst::MaterialEnum, Float_t> >&) const; 

    
    /// Clear the data
    void ClearData(){
     
      XSecDataFull_iter     iter1;
      XSecDataIntType_iter  iter2;
      XSecDataMaterial_iter iter3;
      
      for (iter1 = _CrossSections.begin(); iter1 != _CrossSections.end(); iter1++){
        for (iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++){
          for (iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++){
            if (iter3->second) delete iter3->second;
            iter3->second = NULL; 
          }
          iter2->second.clear();
        }
        iter1->second.clear();
      }
      
      _CrossSections.clear();
    }
     
    XSecDataFull _CrossSections;
  
  };
  
 
  
  class KaonSIPropagator:  public si_syst::ParticleSIPropagator{
    
  public:
    KaonSIPropagator(){
      // For the moment read the uncertainty from the param file
      _uncertainty = (Float_t)ND::params().GetParameterD("highlandSystematics.KaonSI.XSec.Uncertainty");
      
      // For the elastic cross-section a simple scaling 
      _elastic_scale = (Float_t)ND::params().GetParameterD("highlandSystematics.KaonSI.XSec.ElasticScale");
        
      _inelastic_weights = NULL;
      
    }
   
    virtual ~KaonSIPropagator(){
      delete _inelastic_weights;
    }
    
    
    virtual Double_t GetCrossSection(const si_syst::InteractionType&, const Float_t&, const Int_t&, TGeoNode*) const;
    
    /// If one wants to re-weight to a given cross-section
    virtual Double_t GetReferenceCrossSection(const si_syst::InteractionType&, const Float_t&, const Int_t&, TGeoNode*) const;
    
    /// Same but given the state
    Double_t GetReferenceCrossSection(const si_syst::InteractionType& type, const si_syst::ParticleState& state, const Int_t& PDG){

      TGeoNode *node = ND::hgman().GeoManager()->FindNode(state.Pos.X(), state.Pos.Y(), state.Pos.Z());

      return GetReferenceCrossSection(type, state.Momentum, PDG, node);
    }
    
    virtual Double_t GetCrossSectionError(const si_syst::InteractionType& type, const Float_t&, const Int_t&, TGeoNode*) const{
      if (type != si_syst::kInelastic && type != si_syst::kElastic) return 0.; 
      return _uncertainty;
    }
   
    /// Whether a track is in VOI given a position and detector
    virtual Bool_t InVOI(const TVector3&) const;
    
    
  protected:
  
    
    
    void SetParameters(){
      
      // Read from the param files
      _lengthStepSize = (Float_t)ND::params().GetParameterD("highlandSystematics.KaonSI.StepSize");
      _momStepSize    = (Float_t)ND::params().GetParameterD("highlandSystematics.KaonSI.StepMom");

      
      // Set interaction types here
      AddInteractionType(si_syst::kInelastic);  
     
      // Set relevant PDGs
      AddParticlePDG(ParticleId::kKPosPDG);
      
      
      // Here for the moment,  will be moved to base class
      InitializeCrossSectionData();
       
      // Here for the moment,  will be moved to base class
      HASSERT(CheckCrossSectionData()); 
 
     }

    
        
     /// Initialize cross-section data, will be moved to base class
     void InitializeCrossSectionData();
     
     
     /// Check on whether the cross-section data was correctly initialzed
     /// Will be moved to base class
     bool CheckCrossSectionData() const{
       
      // Check that the size of the registered particles corresponds to the cross-section data
      if (GetParticlePDGs().size() != _xsecData.GetCrossSectionData().size()) return false;
      
      // Check that all registered particles and interactions have the corresponding cross-sections filled
      
      XSecDataFull_const_iter     iter1;
      XSecDataIntType_const_iter  iter2;
      
      std::set<ParticleId::PdgEnum>::const_iterator it_pdg  = _particlePDGs.begin();
      std::set<si_syst::InteractionType>::const_iterator it_type; 

      for (; it_pdg != _particlePDGs.end(); it_pdg++){
        
        iter1 = _xsecData.GetCrossSectionData().find(*it_pdg);
        if ( iter1 == _xsecData.GetCrossSectionData().end())
          return false;
        
        
        // Check all the interactions are present 
        for (it_type = _intTypes.begin(); it_type != _intTypes.end(); it_type++){
          iter2 = iter1->second.find(*it_type);
          
          if (iter2 == iter1->second.end())
            return false;
          
        }   

      } 
       
      return true; 
     }
    
          
      /// Add the tgraph cross-section data, clone so that the object owns it
      void AddCrossSectionData(const ParticleId::PdgEnum& pdg,
        const si_syst::InteractionType& type, 
        const si_syst::MaterialEnum& material, 
        TGraph* data){
        
        _xsecData.AddCrossSectionData(pdg, type, material, data);
      }
      
      void AddCompositeCrossSectionData(
        const ParticleId::PdgEnum& pdg,  
        const si_syst::InteractionType& type,
        const si_syst::MaterialEnum& material, 
        const std::vector<std::pair< si_syst::MaterialEnum, Float_t> >& input){
        
        _xsecData.AddCompositeCrossSectionData(pdg, type, material, input);
      }
      
      /// Get the requested cross section data
      TGraph* GetCrossSectionData(const ParticleId::PdgEnum& pdg,
          const si_syst::InteractionType& type, 
          const si_syst::MaterialEnum& material) const{ 
        return _xsecData.GetCrossSectionData(pdg, type, material);
      }
     
     
      /// Build a graph for the cross-sections for the composite material
      /// Requires a list of materials and their molar fractions
    
      /// Cross-section data
      kaon_si::CrossSectionData _xsecData;
      
            
  private:
    
    Float_t _uncertainty; // cross-section uncertainty
    Float_t _elastic_scale; // scaling factor for the elastic cross-section
    
    TGraph* _inelastic_weights; // weights for the inelastic cross-section
     
  };
  

  
}

#endif
