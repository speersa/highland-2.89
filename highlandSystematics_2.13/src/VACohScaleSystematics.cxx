#include "VACohScaleSystematics.hxx"
#include "AnalysisUtils.hxx"
#include "BasicUtils.hxx"
#include "DataClasses.hxx"
#include "CategoriesUtils.hxx"
#include "ConstituentsUtils.hxx"
#include "EventBoxTracker.hxx"
#include "ND280AnalysisUtils.hxx"

//#define DEBUG
// Read the parameters:
// 1st and 2nd lines: FGD1 (5x5) fit results
// 3rd and 4th lines: FGD2 (5x5) fit results
// 1st and 3rd lines: MC
// 2nd and 4th ;ines: data

//********************************************************************
VACohScaleSystematics::VACohScaleSystematics():EventVariationBase(1),BinnedParams(
    std::string(getenv("HIGHLANDSYSTEMATICSROOT")) + "/data", 
    "VACohScale", 
    k1D_SYMMETRIC,
    versionUtils::ExtensionSyst()

    ){
//********************************************************************

#ifdef DEBUG
    std::cout <<"Nbins: "<<GetNBins();
    for (int i = 0 ; i < GetNBins(); i++){
        Float_t mean,err_mean; 
        GetParametersForBin(i,mean,err_mean);
        std::cout<<"Mean, err mean = "<<mean<<" "<<err_mean<<std::endl;
    }
#endif   
}

//********************************************************************
void VACohScaleSystematics::Apply(const ToyExperiment& toy, AnaEventC& event){
//********************************************************************
    (void)event;

    // Get the SystBox for this event
    SystBoxB* box = GetSystBox(event);

    // loop over the relevant tracks for this systematic
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
            std::cout <<" VACohScaleSystematics::Apply(): nodes = " << fgdTrack->NNodes << std::endl;       
#endif     

            // Get the correct FGD to apply the correct shift
            bool inFGD1 = anaUtils::InDetVolume(SubDetId::kFGD1, fgdTrack->PositionStart);
            bool inFGD2 = anaUtils::InDetVolume(SubDetId::kFGD2, fgdTrack->PositionStart);
            // Read parameters from data file
            Float_t mean_MC, err_mean_MC, mean_data, err_mean_data;
            if(inFGD1){
                if(!GetBinValues(1.0, mean_MC, err_mean_MC))      continue;
                if(!GetBinValues(2.0, mean_data, err_mean_data))  continue;
            }
            else if(inFGD2){
                if(!GetBinValues(3.0, mean_MC, err_mean_MC))      continue;
                if(!GetBinValues(4.0, mean_data, err_mean_data))  continue;
            }
            else continue;

#ifdef DEBUG
            if (inFGD1) std::cout << "VACohScaleSystematics::Apply(): FGD1 params = "<<mean_MC<<" , "<<err_mean_MC<<" , " <<mean_data<<" , "<<err_mean_data<<std::endl;     
            if (inFGD2) std::cout << "VACohScaleSystematics::Apply(): FGD2 params = "<<mean_MC<<" , "<<err_mean_MC<<" , " <<mean_data<<" , "<<err_mean_data<<std::endl;     
#endif
            Float_t diffdataMC=1.00*(mean_data-mean_MC); // in MeV
            Float_t error=sqrt( pow(fabs(diffdataMC),2) + pow(err_mean_MC,2)+pow(err_mean_data,2)); //in MeV
            Float_t& VA_55 = fgdTrack->Vertex5x5;
            Float_t& VA_27 = fgdTrack->Vertex5x5;
            // Apply the variation
            if (inFGD1){
                VA_55 =  fgdTrack->Vertex5x5 + 21.7*diffdataMC + 21.7*error*toy.GetToyVariations(_index)->Variations[0]; 
            }
            else if (inFGD2){
                VA_27 =  fgdTrack->Vertex5x5 + 21.7*diffdataMC + 21.7*error*toy.GetToyVariations(_index)->Variations[0]; 
            }
            else continue;

#ifdef DEBUG
            Float_t VA_5x5_original = original->Vertex5x5;
            std::cout << "VACohScaleSystematics::Apply(): Results: " << std::endl;  
            if(inFGD1) std::cout << "SCALE - FGD1 5x5 " << VA_5x5_original << " --> " <<  fgdTrack->Vertex5x5 << std::endl;
            if(inFGD2) std::cout << "SCALE - FGD2 5x5 " << VA_5x5_original << " --> " <<  fgdTrack->Vertex5x5 << std::endl;
#endif
        }
    }
}

//********************************************************************
bool VACohScaleSystematics::UndoSystematic(AnaEventC& event){
//********************************************************************
    // Get the SystBox for this event
    SystBoxB* box = GetSystBox(event);
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

//********************************************************************
Int_t VACohScaleSystematics::GetRelevantRecObjectGroups(const SelectionBase& sel, Int_t* IDs) const{
//********************************************************************
    Int_t ngroups=0;
    for (UInt_t b=0; b<sel.GetNBranches(); b++){
        SubDetId_h det = sel.GetDetectorFV(b);
        if (det == SubDetId::kFGD1 || det == SubDetId::kFGD){
            IDs[ngroups++] = EventBoxTracker::kTracksWithTPCInFGD1FV;
        }
        if (det == SubDetId::kFGD2 || det == SubDetId::kFGD){
            IDs[ngroups++] = EventBoxTracker::kTracksWithTPCInFGD2FV;
        }
    }
    return ngroups;
}
