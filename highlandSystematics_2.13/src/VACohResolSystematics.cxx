#include "VACohResolSystematics.hxx"
#include "AnalysisUtils.hxx"
#include "BasicUtils.hxx"
#include "DataClasses.hxx"
#include "CategoriesUtils.hxx"
#include "ConstituentsUtils.hxx"
#include "EventBoxTracker.hxx"
#include "ND280AnalysisUtils.hxx"


//#define DEBUG
// Read the parameters for proton as the errors are the biggest (conservative):
// 1st  line: FGD1 (5x5) MC
// 2nd  line: FGD1 (5x5) data
// 3rd  line: FGD2 (2x7) MC
// 4th  line: FGD2 (2x7) data

//********************************************************************
VACohResolSystematics::VACohResolSystematics():EventVariationBase(1),BinnedParams(
    std::string(getenv("HIGHLANDSYSTEMATICSROOT")) + "/data", 
    "VACohResol", 
    k1D_SYMMETRIC,
    versionUtils::ExtensionSyst()
    ){
//********************************************************************

#ifdef DEBUG
    std::cout <<"Nbins: "<<GetNBins();
    for (int i = 0 ; i < GetNBins(); i++){
        Float_t sigma,err_sigma; 
        GetParametersForBin(i,sigma,err_sigma);
        std::cout<<"Sigma, err sigma = "<<sigma<<" "<<err_sigma<<std::endl;
    }
#endif   
}  

//********************************************************************
void VACohResolSystematics::Apply(const ToyExperiment& toy, AnaEventC& event){
//********************************************************************
  //(void)event;

    // Get the SystBox for this event
    SystBoxB* box = GetSystBox(event);
 
#ifdef DEBUG
    std::cout << "VACohResolSystematics::Apply(): track size " << box->nRelevantRecObjects << std::endl;
#endif

    // Loop over relevant tracks for this systematic
    // Could be only the HMN track
    //cout<<box->nRelevantRecObjects<<endl;
   for (Int_t itrk=0;itrk<box->nRelevantRecObjects;itrk++){
        AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);
        for (Int_t subdet = 0; subdet<2; subdet++) {
            AnaFGDParticle* fgdTrack =static_cast<AnaFGDParticle*>( anaUtils::GetSegmentInDet(*track,static_cast<SubDetId::SubDetEnum >(subdet)));
            if(!fgdTrack) continue;
            // The original (corrected) FGD track 
            const AnaFGDParticle* original = static_cast<const AnaFGDParticle*>(fgdTrack->Original);
            // The original should exist
            if (!original)   continue;   

#ifdef DEBUG
            std::cout <<" VACohResolSystematics::Apply(): nodes = " << fgdTrack->NNodes << std::endl;       
#endif   

            bool inFGD1 = anaUtils::InDetVolume(SubDetId::kFGD1, fgdTrack->PositionStart);
            bool inFGD2 = anaUtils::InDetVolume(SubDetId::kFGD2, fgdTrack->PositionStart);
            Float_t sigma_MC, err_sigma_MC, sigma_data, err_sigma_data;
            if(inFGD1){
                if(!GetBinValues(1.0, sigma_MC, err_sigma_MC))      continue;
                if(!GetBinValues(2.0, sigma_data, err_sigma_data))  continue;
            }
            else if(inFGD2){
                if(!GetBinValues(3.0, sigma_MC, err_sigma_MC))        continue;
                if(!GetBinValues(4.0, sigma_data, err_sigma_data))    continue;
            }
            else continue;

#ifdef DEBUG
            if (inFGD1) std::cout << "VACohResolSystematics::Apply(): FGD1 params = "<<sigma_MC<<" , "<<err_sigma_MC<<" , " <<sigma_data<<" , "<<err_sigma_data<<std::endl;     
            if (inFGD2) std::cout << "VACohResolSystematics::Apply(): FGD2 params = "<<sigma_MC<<" , "<<err_sigma_MC<<" , " <<sigma_data<<" , "<<err_sigma_data<<std::endl;     
#endif

            // The unit here doesn't matter as we always deal with ratios.
            Float_t ratiodataMC=sigma_data/sigma_MC;
            Float_t error= ratiodataMC*fabs(err_sigma_data/sigma_data - err_sigma_MC/sigma_MC);
            Float_t& VA_55 = fgdTrack->Vertex5x5;
            Float_t& VA_27 = fgdTrack->Vertex5x5;
            // Apply the variation
            if (inFGD1){
                VA_55 =  fgdTrack->Vertex5x5 *(ratiodataMC + error*toy.GetToyVariations(_index)->Variations[0]); 
            }
            else if (inFGD2){
                VA_27 =  fgdTrack->Vertex5x5 *(ratiodataMC + error*toy.GetToyVariations(_index)->Variations[0]); 
            }
            else continue;

#ifdef DEBUG
            std::cout << "VACohResolSystematics::Apply(): Results: " << std::endl;  
            if(inFGD1) std::cout << "VA RESOL - FGD1 5x5 " << original->Vertex5x5 << " --> " <<  VA_55 << std::endl;
            if(inFGD2) std::cout << "VA RESOL - FGD2 5x5 " << original->Vertex5x5 << " --> " <<  VA_27 << std::endl;
#endif
        }
    }
}

//********************************************************************
bool VACohResolSystematics::UndoSystematic(AnaEventC& event){
//********************************************************************
    // Get the SystBox for this event
    SystBoxB* box = GetSystBox(event);
    
    AnaRecObjectC** recObjs = box->RelevantRecObjects;

    for (Int_t itrk=0;itrk<box->nRelevantRecObjects;itrk++){
        AnaTrackB* track = static_cast<AnaTrackB*>(box->RelevantRecObjects[itrk]);
        for (Int_t subdet = 0; subdet<2; subdet++) {
            AnaFGDParticle* fgdTrack =static_cast<AnaFGDParticle*>( anaUtils::GetSegmentInDet(*track,static_cast<SubDetId::SubDetEnum >(subdet)));
            if (!fgdTrack)   continue;
            // The original (corrected) fgd track
            const AnaFGDParticle* original = static_cast<const AnaFGDParticle*>(fgdTrack->Original);
            // The original should exist
            if (!original)   continue;
            bool inFGD1 = anaUtils::InDetVolume(SubDetId::kFGD1, fgdTrack->PositionStart);
            bool inFGD2 = anaUtils::InDetVolume(SubDetId::kFGD2, fgdTrack->PositionStart);
            // revert to initial pulls
            if (inFGD1) fgdTrack->Vertex5x5 = original->Vertex5x5;
            if (inFGD2) fgdTrack->Vertex5x5 = original->Vertex5x5;
        }
    }
    // Don't reset the spill to corrected
    return false;
}


