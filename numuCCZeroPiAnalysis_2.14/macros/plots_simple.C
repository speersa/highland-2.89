void plots_simple(int mode, const std::string& data_file, const std::string& mc_file, std::string prefix = ""){

  DataSample    data(data_file);
  DataSample    mc(mc_file);

  DrawingTools  draw(mc_file);

  // define kinematics bins,  remove for the moment since have some problems plotting
  //double pbins[15]            = {0, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1250, 1500, 2000, 3000, 5000}; 
  //double theta_bins[12]       = {0, 0.142, 0.200, 0.284, 0.348, 0.403, 0.451, 0.555, 0.644, 0.795, 0.927, 3.142};

  double  mom_max   = 3000.;
  double  mom_min   = 0.;
  int     mom_bins  = 30; 
 
  double  mom_range_max   = 1500.;
  double  mom_range_min   = 0.;
  int     mom_range_bins  = 15; 
 
  double  theta_max   = 3.142.;
  double  theta_min   = 0.;
  int     theta_bins  = 10; 
 


  
  
  if(mode==0){ 
    // --- Kinematic plots for muon ---
    // Momentum 
    draw.SetTitleX("muon momentum,  MeV");
    // topo0
    draw.Draw(data, mc, "selmu_mom",              mom_bins,       mom_min,      mom_max, "topology",  "accum_level[][0]>7");
    c1->Print((prefix+"topo0_data_mc_muon_mom.png").c_str());
    // topo1
    draw.Draw(data, mc, "selmu_mom",              mom_bins,       mom_min,      mom_max, "topology",  "accum_level[][1]>10");
    c1->Print((prefix+"topo1_data_mc_muon_mom.png").c_str());
    // topo2
    draw.Draw(data, mc, "selmu_mom",              mom_bins,       mom_min,      mom_max, "topology",  "accum_level[][2]>11");
    c1->Print((prefix+"topo2_data_mc_muon_mom.png").c_str());
    //topo3
    draw.Draw(data, mc, "selmu_mom_range_vertex", mom_range_bins, mom_range_min, mom_range_max, "topology",  "accum_level[][3]>11");
    c1->Print((prefix+"topo3_data_mc_muon_mom.png").c_str());

    // Theta 
    draw.SetTitleX("muon theta (rad))");
    // topo0
    draw.Draw(data, mc, "selmu_theta",                theta_bins, theta_min, theta_max, "topology",  "accum_level[][0]>7");
    c1->Print((prefix+"topo0_data_mc_muon_theta.png").c_str());
    // topo1
    draw.Draw(data, mc, "selmu_theta",                theta_bins, theta_min, theta_max, "topology",  "accum_level[][1]>10");
    c1->Print((prefix+"topo1_data_mc_muon_theta.png").c_str());
    // topo2
    draw.Draw(data, mc, "selmu_theta",                theta_bins, theta_min, theta_max, "topology",  "accum_level[][2]>11");
    c1->Print((prefix+"topo2_data_mc_muon_theta.png").c_str());
    //topo3
    draw.Draw(data, mc, "selmu_theta",                theta_bins, theta_min, theta_max, "topology",  "accum_level[][3]>11");
    c1->Print((prefix+"topo3_data_mc_muon_theta.png").c_str());
  }
    

  if(mode==1){
    // --- Kinematic plots for proton ---
    // Proton 
    draw.SetTitleX("proton momentum,  MeV");
    // topo1
    draw.Draw(data, mc, "selp_amom",                          mom_bins,       mom_min, mom_max,             "topology",  "accum_level[][1]>10");
    c1->Print((prefix+"topo1_data_mc_proton_mom.png").c_str());
    // topo2
    draw.Draw(data, mc, "selp_mom_range_vertex",              mom_range_bins, mom_range_min, mom_range_max, "topology",  "accum_level[][2]>11");
    c1->Print((prefix+"topo2_data_mc_proton_mom.png").c_str());
    //topo3
    draw.Draw(data, mc, "selp_amom",                          mom_bins,       mom_min, mom_max,             "topology",  "accum_level[][3]>11");
    c1->Print((prefix+"topo3_data_mc_proton_mom.png").c_str());

    // Theta 
    draw.SetTitleX("proton theta (rad))");
    // topo1
    draw.Draw(data, mc, "selp_theta",                 theta_bins, theta_min, theta_max, "topology",  "accum_level[][1]>10");
    c1->Print((prefix+"topo1_data_mc_proton_theta.png").c_str());
    // topo2
    draw.Draw(data, mc, "selp_theta",                 theta_bins, theta_min, theta_max, "topology",  "accum_level[][2]>11");
    c1->Print((prefix+"topo2_data_mc_proton_theta.png").c_str());
    //topo3
    draw.Draw(data, mc, "selp_theta",                 theta_bins, theta_min, theta_max, "topology",  "accum_level[][3]>11");
    c1->Print((prefix+"topo3_data_mc_proton_theta.png").c_str());
  }

  //Eff + purities
  if(mode==10){ 
    // topo0
    draw.DrawEffPurVSCut(mc, 0, "topology==0", "", 1);
    c1->Print((prefix+"topo0_eff_pur_cut.png").c_str());
    // topo1
    draw.DrawEffPurVSCut(mc, 1, "topology==0", "", 1);
    c1->Print((prefix+"topo1_eff_pur_cut.png").c_str());
    // topo2
    draw.DrawEffPurVSCut(mc, 2, "topology==0", "", 1);
    c1->Print((prefix+"topo2_eff_pur_cut.png").c_str());
    //topo3
    draw.DrawEffPurVSCut(mc, 3, "topology==0", "", 1);
    c1->Print((prefix+"topo3_eff_pur_cut.png").c_str());
  }
 

}

