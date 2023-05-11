
doFit(const std::string& file, const std::string& cut, std::string out_file = "result.pdf"){

  DataSample mc(file);

  TH1D* htime = new TH1D("htime", "", 5000, 2000, 8000);

  std::string cut_total = "(selmu_pos[3]>0 && " + cut + ")";

  std::cout << cut_total << std::endl;


  gStyle->SetOptStat("");

  mc.GetTree("default")->Draw("selmu_pos[3] >> htime", cut_total.c_str());

  Double_t par[24];
  TF1 *g1    = new TF1("g1","gaus",2600, 3150);
  TF1 *g2    = new TF1("g2","gaus",3200, 3700);
  TF1 *g3    = new TF1("g3","gaus",3800, 4300);
  TF1 *g4    = new TF1("g4","gaus",4400, 4900);
  TF1 *g5    = new TF1("g5","gaus",4950, 5450);
  TF1 *g6    = new TF1("g6","gaus",5550, 6100);
  TF1 *g7    = new TF1("g7","gaus",6150, 6650);
  TF1 *g8    = new TF1("g8","gaus",6700, 7300);



  TF1 *total = new TF1("total","gaus(0) + gaus(3) + gaus(6) + gaus(9) + gaus(12) + gaus(15) + gaus(18) + gaus(21)", 
      2000, 8000);

  total->SetLineColor(2);
  htime->Fit(g1,"R");
  htime->Fit(g2,"R+");
  htime->Fit(g3,"R+");
  htime->Fit(g4,"R+");
  htime->Fit(g5,"R+");
  htime->Fit(g6,"R+");
  htime->Fit(g7,"R+");
  htime->Fit(g8,"R+"); 


  g1->GetParameters(&par[0]);
  g2->GetParameters(&par[3]);
  g3->GetParameters(&par[6]);
  g4->GetParameters(&par[9]);
  g5->GetParameters(&par[12]);
  g6->GetParameters(&par[15]);
  g7->GetParameters(&par[18]);
  g8->GetParameters(&par[21]);


  total->SetParameters(par);
  htime->Fit(total,"NR+");


  total->GetParameters(&par[0]);



  htime->Draw();
  htime->GetXaxis()->SetTitle("Time,  ns");
  gPad->Update();

  // draw text
  TLatex l;
  l.SetTextSize(0.02);
  
 
  TString s1 = cut;
  
  TString s2 = Form(" %g - %g - %g - %g - %g - %g - %g - %g", 
      par[1], par[4], par[7], par[10], par[13], par[16], par[19], par[22]);

   
  TString s3 = Form(" %g - %g - %g - %g - %g - %g - %g - %g", 
      par[2], par[5], par[8], par[11], par[14], par[17], par[20], par[23]);
  
  std::cout << " Result: " << s1 << std::endl;
  std::cout << " Result: " << s2 << std::endl;
  std::cout << " Result: " << s3 << std::endl;
  
  l.DrawLatexNDC(0.05, 0.98,s1);
  
  l.DrawLatexNDC(0.05, 0.95,s2);
  
  l.DrawLatexNDC(0.05, 0.92,s3);


  gPad->Update();


  c1->SaveAs(out_file.c_str());

}


