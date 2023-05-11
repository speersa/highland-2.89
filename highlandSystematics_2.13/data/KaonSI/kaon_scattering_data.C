/// A simple macro to add TGraph(s) with kaon scattering data into a given file
/// Two data sources:
/// Total cross-sections on C:
/// Bugg. et al. 1968. PhysRev.168.1466
/// Friedman et al. 1997 (re-analysis of BNL AGS data from 90s) PhysRevC.55.1304
/// Inelastic cross-sections on C:
/// Friedman et al


void fill_data(const std::string& outfile){

  TFile* file = new TFile(outfile.c_str(), "RECREATE");

  /// Kaon plus on C,  total

  unsigned int total_nPoints = 14;

  Double_t total_mom_kaonPlus_Carbon[14] = {
    488, // Friedman
    531, // Friedman
    656, // Friedman
    714, // Bugg/Friedman 
    824, // Bugg 
    905, // Bugg 
    969, // Bugg 
    1084, // Bugg 
    1190, // Bugg 
    1293, // Bugg 
    1408, // Bugg 
    1564, // Bugg 
    2062, // Bugg 
    2554, // Bugg 
  };

  Double_t total_xsec_kaonPlus_Carbon[14] = {
    162.4, // Friedman
    166.6, // Friedman
    174.9, // Friedman
    175.6, // Friedman (Bugg value is 171.6+/-4.7, consistent)
    177.9, // Bugg 
    187.1, // Bugg 
    188.4, // Bugg 
    195.4, // Bugg 
    201.8, // Bugg 
    202.2, // Bugg 
    202.6, // Bugg 
    202.7, // Bugg 
    195.6, // Bugg 
    188.0  // Bugg 
  };

  Double_t total_xsec_err_kaonPlus_Carbon[14] = {
    1.9, // Friedman
    1.3, // Friedman
    0.8, // Friedman
    0.9, // Friedman
    4.3, // Bugg 
    4.2, // Bugg 
    4.0, // Bugg 
    3.8, // Bugg 
    3.7, // Bugg 
    3.8, // Bugg 
    3.6, // Bugg 
    3.4, // Bugg 
    3.2, // Bugg 
    3.3  // Bugg 
  };

  TGraphErrors total_graph = TGraphErrors(
      total_nPoints, 
      total_mom_kaonPlus_Carbon, 
      total_xsec_kaonPlus_Carbon, 
      NULL, 
      total_xsec_err_kaonPlus_Carbon
      );

  total_graph.SetName("total_kaon_plus_Carbon");
  total_graph.SetTitle("total_kaon_plus_Carbon");

  total_graph.SetMarkerColor(3);
  total_graph.SetLineColor(3);
  
  total_graph.Write();
  
  /// Inelastic cross sections
  
  unsigned int inelastic_nPoints = 4;

  Double_t inelastic_mom_kaonPlus_Carbon[4] = {
    488, // Friedman
    531, // Friedman
    656, // Friedman
    714  // Friedman 
  };

  Double_t inelastic_xsec_kaonPlus_Carbon[4] = {
    120.4, // Friedman
    129.3, // Friedman
    141.8, // Friedman
    149.3, // Friedman 
  };

  Double_t inelastic_xsec_err_kaonPlus_Carbon[4] = {
    2.3, // Friedman
    1.4, // Friedman
    1.5, // Friedman
    1.5, // Friedman
  };

  TGraphErrors inelastic_graph = TGraphErrors(
      inelastic_nPoints, 
      inelastic_mom_kaonPlus_Carbon, 
      inelastic_xsec_kaonPlus_Carbon, 
      NULL, 
      total_xsec_err_kaonPlus_Carbon
      );

  inelastic_graph.SetName("inelastic_kaon_plus_Carbon");
  inelastic_graph.SetTitle("inelastic_kaon_plus_Carbon");

  inelastic_graph.SetMarkerColor(4);
  inelastic_graph.SetLineColor(4);
  
  inelastic_graph.Write(); 

  file->Close();

}
