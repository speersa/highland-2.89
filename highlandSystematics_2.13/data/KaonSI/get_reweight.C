/// This is to re-weight inelastic cross-section: -- match MC:inelastic+elastic with data (total) but re-weighting inelastic
TGraph* ReweightInelastic(TGraph* inelastic_mc, TGraph* elastic_mc, TGraph* data_total){
 
  if (!inelastic_mc || !elastic_mc || !data_total) return NULL;
  
  TGraph* graph_out = new TGraph();

  // Loop through the points of the inelastic MC
  for (int i = 0; i < inelastic_mc->GetN(); i++){
    
    // Estimate the weight
    Double_t pointX, pointY;
    if (inelastic_mc->GetPoint(i, pointX, pointY) < 0) continue;
     
    Double_t nom = data_total->Eval(pointX) - elastic_mc->Eval(pointX);
    
    if (nom < 0)  nom = 0.;
    
    Double_t weight = 0.;
    if (pointY != 0) weight = nom / pointY;
    
    graph_out->SetPoint(graph_out->GetN(), pointX, pointY * weight);

  }
   
  return graph_out; 
  
}


/// Sum up two graphs
TGraph* GetTotal(TGraph* inelastic_mc, TGraph* elastic_mc){
  
 
  if (!inelastic_mc || !elastic_mc) return NULL;
  
  TGraph* graph_out = new TGraph();

  // Loop through the points of the inelastic MC
  for (int i = 0; i < inelastic_mc->GetN(); i++){
    
    // Estimate the weight
    Double_t pointX, pointY;
    if (inelastic_mc->GetPoint(i, pointX, pointY) < 0) continue;
    
    graph_out->SetPoint(graph_out->GetN(), pointX, pointY + elastic_mc->Eval(pointX));

  }
  
  return graph_out; 
  
}


//  Scale factor for the elastic cross-section in MC
std::pair<Double_t, Double_t> GetScaleFactors(TGraph* inelastic_mc, TGraph* elastic_mc, TGraph* inelastic_data){
  
  std::pair<Double_t, Double_t>  factors(1., 1.);
  
  if (!inelastic_mc || !elastic_mc || !inelastic_data) return factors;
  
  
  Int_t count = 0;
   
  std::pair<Double_t, Double_t>  factor_count(0., 0.); // elastic, inelastic

 
  // Loop through the points of the inelastic data
  for (int i = 0; i < inelastic_data->GetN(); i++){
    
     Double_t pointX, pointY;
     
     if (inelastic_data->GetPoint(i, pointX, pointY) < 0) continue;
     
     // Get the difference between data and MC
     // and use it as a scaling factor for the elastic MC   
    Double_t diff = pointY - inelastic_mc->Eval(pointX); 
    
    if (elastic_mc->Eval(pointX) <= 0 || inelastic_mc->Eval(pointX) <= 0) continue;
     
    factor_count.first += (elastic_mc->Eval(pointX) - diff) / elastic_mc->Eval(pointX);
     
    factor_count.second += (inelastic_mc->Eval(pointX) + diff) / inelastic_mc->Eval(pointX);
    
    count++;
  }
  

  if (count == 0) return factors;
  
  factors.first *= (Double_t)factor_count.first/(Double_t)(count);
   
  factors.second *= (Double_t)factor_count.second/(Double_t)(count); 
  
  return factors;   
}

void ScaleGraph(TGraph* graph, Double_t factor){
  if (!graph) return;
  
  for (int i = 0; i < graph->GetN(); i++) graph->GetY()[i] *= factor;
}

void SmoothLowEnd(TGraph* graph, double limit){
  if (!graph) return;
  
  int ibin1, bin2;
  for (int i = 0; i < graph->GetN(); i++) {
    if (graph->GetX()[i] < limit) ibin1 = i;
    else if (graph->GetX()[i] < 2 * limit) ibin2 = i;
    else break;
  }
  
  double m = (graph->GetY()[ibin2]-graph->GetY()[ibin1])
           / (graph->GetX()[ibin2]-graph->GetX()[ibin1]);
  double q = graph->GetY()[ibin1] - m*graph->GetX()[ibin1];
  
  for (int i = 0; i < graph->GetN(); i++) {
    if (graph->GetX()[i] < 0) continue;
    else if (graph->GetX()[i] < limit)
      graph->GetY()[i] = m * graph->GetX()[i] + q;
    else break;
  }
}


// Do the thing
void Process(const std::string& in_mc, const std::string& in_data,  const std::string& out){

    TFile* file_mc = new TFile(in_mc.c_str());
   
    TFile* file_data = new TFile(in_data.c_str());

    if (!file_mc) return;
    if (!file_data) return;
   
    
    // Initial histograms from MC
    TGraph* inelastic_mc = (TGraph*)file_mc->Get("inelastic_kaon_plus_Carbon")->Clone();
    TGraph* elastic_mc   = (TGraph*)file_mc->Get("elastic_kaon_plus_Carbon")->Clone();
   
    
    // Initial histograms from data
    TGraph* data_total      = (TGraph*)file_data->Get("total_kaon_plus_Carbon")->Clone();
    data_total->SetTitle("total_kaon_plus_Carbon_data");
    data_total->SetName("total_kaon_plus_Carbon_data");
    
    TGraph* data_inelastic  = (TGraph*)file_data->Get("inelastic_kaon_plus_Carbon")->Clone();
    data_inelastic->SetTitle("inelastic_kaon_plus_Carbon_data");
    data_inelastic->SetName("inelastic_kaon_plus_Carbon_data");
    
    TFile* file_out = new TFile(out.c_str(), "RECREATE");
  
    
    // Write basic histos
    inelastic_mc->SetMarkerColor(6);
    inelastic_mc->SetLineColor(6);

    inelastic_mc->Write();
    elastic_mc->Write();
    data_total->Write();
    data_inelastic->Write();
    
    // Reweighted inelastic, first interation
    TGraph* inelastic_mc_reweight_first = ReweightInelastic(inelastic_mc, elastic_mc, data_total);
    
    if (!inelastic_mc_reweight_first) return;
    
    inelastic_mc_reweight_first->SetTitle("inelastic_mc_reweight_first_Carbon");
    inelastic_mc_reweight_first->SetName("inelastic_mc_reweight_first_Carbon");
    inelastic_mc_reweight_first->Write();
  
    
    // Total GEANT4 
    TGraph* total_mc_geant4 = GetTotal(inelastic_mc, elastic_mc);
    
    total_mc_geant4->SetTitle("total_mc_geant4_Carbon");
    total_mc_geant4->SetName("total_mc_geant4_Carbon");
    total_mc_geant4->Write();  
   
    
    // Total reweighted, first iteration
    TGraph* total_mc_reweight_first = GetTotal(inelastic_mc_reweight_first, elastic_mc);
    
    total_mc_reweight_first->SetTitle("total_mc_reweight_first_Carbon");
    total_mc_reweight_first->SetName("total_mc_reweight_first_Carbon");
    total_mc_reweight_first->Write();

    
    // Get the scale factors for elastic and inelastic (the second one is for checks)
    std::pair<Double_t, Double_t> factors = GetScaleFactors(inelastic_mc_reweight_first, elastic_mc, data_inelastic);
    
    // Dump the factor
    std::cout << "Elastic MC scaling factor \t"   << factors.first  << std::endl;
    std::cout << "Inelastic MC scaling factor \t" << factors.second << std::endl;
     
      
    // Apply the scaling for elastic
    TGraph* elastic_mc_reweight   = elastic_mc->Clone();
    ScaleGraph(elastic_mc_reweight, factors.first);
   
    elastic_mc_reweight->SetTitle("elastic_mc_reweight_Carbon");
    elastic_mc_reweight->SetName("elastic_mc_reweight_Carbon");
    elastic_mc_reweight->Write();
    
    
    // Reweighted inelastic, second interation 
    TGraph* inelastic_mc_reweight = ReweightInelastic(inelastic_mc, elastic_mc_reweight, data_total);
    
    // Smooth the lowest end of the inelastic xsec, so there is no peak
    SmoothLowEnd(inelastic_mc_reweight, 100.);
    
    if (!inelastic_mc_reweight) return;
    inelastic_mc_reweight->SetTitle("inelastic_mc_reweight_Carbon");
    inelastic_mc_reweight->SetName("inelastic_mc_reweight_Carbon");
    inelastic_mc_reweight->SetMarkerColor(6);
    inelastic_mc_reweight->SetLineColor(6);
    inelastic_mc_reweight->Write();
    
    // Total reweighted, second iteration
    TGraph* total_mc_reweight = GetTotal(inelastic_mc_reweight, elastic_mc_reweight);
    
    total_mc_reweight->SetTitle("total_mc_reweight_Carbon");
    total_mc_reweight->SetName("total_mc_reweight_Carbon");
    total_mc_reweight->Write();
   
    TCanvas *c0 = new TCanvas("xsec_final", "xsec_final", 600, 400); 
    
    TMultiGraph* mg_reweight = new TMultiGraph("xsec_final", "K^{+} on C");
    
    total_mc_reweight->SetFillColor(0);
    data_total->SetFillColor(0);
    data_inelastic->SetFillColor(0);
    inelastic_mc_reweight->SetFillColor(0);
    elastic_mc_reweight->SetFillColor(0);
    
    mg_reweight->Add(total_mc_reweight);
    mg_reweight->Add(data_total);
    mg_reweight->Add(data_inelastic);
    mg_reweight->Add(inelastic_mc_reweight);
    mg_reweight->Add(elastic_mc_reweight);
   
    mg_reweight->Draw("ALP");
    
    TLegend* l0 = c0->BuildLegend();
    l0->SetHeader("K^{+} on Carbon");
    l0->SetFillColor(0);

    mg_reweight->GetXaxis()->SetTitle("K^{+} Momentum, MeV");
    mg_reweight->GetYaxis()->SetTitle("#sigma, mbarn");
    c0->Modified();
    c0->Update();
    c0->Print("xsec_final_reweight.png");
    
    
    // Raw GEANT4
    TCanvas *c1 = new TCanvas("xsec_GEANT4", "xsec_GEANT4", 600, 400); 
    
    TMultiGraph* mg_geant4 = new TMultiGraph("xsec_GEANT4", "K^{+} on C");
    
    total_mc_geant4->SetFillColor(0);
    data_total->SetFillColor(0);
    data_inelastic->SetFillColor(0);
    inelastic_mc->SetFillColor(0);
    elastic_mc->SetFillColor(0);
    
    mg_geant4->Add(total_mc_geant4);
    mg_geant4->Add(data_total);
    mg_geant4->Add(data_inelastic);
    mg_geant4->Add(inelastic_mc);
    mg_geant4->Add(elastic_mc);
   
    mg_geant4->Draw("ALP");
    
    TLegend* l1 = c1->BuildLegend();
    l1->SetHeader("K^{+} on Carbon");
    l1->SetFillColor(0);
    
    mg_geant4->GetXaxis()->SetTitle("K^{+} Momentum, MeV");
    mg_geant4->GetYaxis()->SetTitle("#sigma, mbarn");
    c1->Modified();
    c1->Update();
    c1->Print("xsec_final_geant4.png");
 
    file_out->Close();
}

