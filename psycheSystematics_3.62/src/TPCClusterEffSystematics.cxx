#include "TPCClusterEffSystematics.hxx"
#include "ND280AnalysisUtils.hxx"
#include "CutUtils.hxx"
#include "SystematicUtils.hxx"
#include "SystId.hxx"

//********************************************************************
TPCClusterEffSystematics::TPCClusterEffSystematics():BinnedParams("TPCClusterEff",k1D_EFF_SYMMETRIC, versionUtils::ExtensionSyst()){
//********************************************************************

    // Get the TPC cluster extra inefficiency
    //GetParametersForBin(0, _extraIneff, _extraIneffError);
    //GetParametersForBin(0, _params);
    SetNParameters(2*GetNBins());
}

//********************************************************************
Weight_h TPCClusterEffSystematics::ComputeWeight(const ToyExperiment& toy, const AnaEventC& event, const ToyBoxB& box, const SelectionBase& sel){
//********************************************************************

    // Get the SystBox for this event, and the appropriate selection and branch
    SystBoxB* SystBox = GetSystBox(event,box.SelectionEnabledIndex,box.SuccessfulBranch);


    Weight_h eventWeight = 1.0;

    // loop over reconstructed tracks in the TPC
    for (Int_t irec=0;irec<(int) SystBox->nRelevantRecObjects;irec++){
      AnaTrackB* track = static_cast<AnaTrackB*>(SystBox->RelevantRecObjects[irec]);
      
      if (!track) continue;
      
      // For example in numuCC inclusive selection, only the Candidate is important at first order
      if (!sel.IsRelevantRecObjectForSystematicInToy(event, box, track, SystId::kTpcClusterEff, box.SuccessfulBranch)) continue;
                   
      //SubDetId::SubDetEnum tpc=anaUtils::GetClosestTPC(*track);
      //AnaTPCParticleB *tpcTrack=static_cast<AnaTPCParticleB*> (anaUtils::GetSegmentInDet(*track,tpc));

      //      AnaTPCParticleB* tpcTrack = static_cast<AnaTPCParticleB*>(track->TPCSegments[0]);

      // Use the TPC segment with more nodes in closest TPC to the start position of the track
      AnaTPCParticleB* tpcTrack = static_cast<AnaTPCParticleB*>(anaUtils::GetSegmentWithMostNodesInClosestTpc(*track));      
      if (!tpcTrack)continue;
      float dir=fabs(tpcTrack->DirectionStart[2]);
  
      BinnedParamsParams params;
      int index;
      if(!GetBinValues(dir, params, index)) continue;

      int nn = tpcTrack->NNodes;           
     
     
      // Assume efficiency for MC control and analysis samples is 1
      // The numbers used for propagation are
      
      // meanDATA  <=> effdata/effmc
      // meanMC    <=> 1
      // meanMCANA <=> 1
      // sigmaMC   <=> 0
      // sigmaDATA <=> ratio error


      // Since there is no inefficiency for MC to apply the systematic one
      // should associate a weight to a track with certain number of nodes with the
      // probability to get these number (i.e. not loosing any):
      // which will so be (effdata/effmc)^nn => (meanData)^nn
      
      // weight = effvarWeight^nn
      
      // Given the high efficiencies in both MC and data it is "enough" to apply
      // the systematic for tracks with the nnodes just above the quality
      // threshold

      // See here
      // www.t2k.org/nd280/physics/SyetematicsAndSelection/Meetings/2018/ssv200218/tpccluster 
      
#if useNewWeights 
      Weight_h eff_w= systUtils::ComputeEffLikeWeight(true, toy.GetToyVariations(_index)->Variations[0], params);//new way with data-mc error included
#else
      Weight_h eff_w= systUtils::ComputeEffLikeWeight(true, toy.GetToyVariations(_index)->Variations[0], toy.GetToyVariations(_index)->Variations[1], params);
#endif

      Weight_h weight(TMath::Power(eff_w.Correction,(Float_t)nn),
                      TMath::Power(eff_w.Systematic,(Float_t)nn));
      
      eventWeight *= weight; 
    }

   
  return eventWeight;
    
}
