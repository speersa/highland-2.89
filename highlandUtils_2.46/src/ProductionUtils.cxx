#include "ProductionUtils.hxx"

//********************************************************************
void anaUtils::AddStandardProductions(){
//********************************************************************

  // Add the different productions
  ND::versioning().AddProduction(ProdId::PROD5D,   "PROD5D",   "v10r11",    "v5r11");
  ND::versioning().AddProduction(ProdId::PROD5E,   "PROD5E",   "v10r11p17", "v5r15p1");
  ND::versioning().AddProduction(ProdId::PROD5F,   "PROD5F",   "v10r11p19", "v5r15p3");
  ND::versioning().AddProduction(ProdId::PROD5G,   "PROD5G",   "v10r11p27", "v5r15p3");
  ND::versioning().AddProduction(ProdId::PROD6PRE, "PROD6PRE", "v11r17",    "v11r28"); //TODO
  ND::versioning().AddProduction(ProdId::PROD6A,   "PROD6A",   "v11r29",    "v5r29p17");
  ND::versioning().AddProduction(ProdId::PROD6B,   "PROD6B",   "v11r31",    "v5r29p19");
  ND::versioning().AddProduction(ProdId::PROD6C,   "PROD6C",   "v11r31",    "v5r29p19");
  ND::versioning().AddProduction(ProdId::PROD6D,   "PROD6D",   "v11r31",    "v5r29p19");
  ND::versioning().AddProduction(ProdId::PROD6E,   "PROD6E",   "v11r31p5",  "v5r29p21");
  ND::versioning().AddProduction(ProdId::PROD6F,   "PROD6F",   "v11r31",    "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6G,   "PROD6G",   "v11r31p7",  "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6H,   "PROD6H",   "v11r31p9",  "v5r31p9");
  ND::versioning().AddProduction(ProdId::PROD6I,   "PROD6I",   "v11r37",    "v5r31p9");
  ND::versioning().AddProduction(ProdId::PROD6J,   "PROD6J",   "v11r31p11", "v5r29p19");
  ND::versioning().AddProduction(ProdId::PROD6K,   "PROD6K",   "v11r31p5",  "v5r29p21");
  ND::versioning().AddProduction(ProdId::PROD6L,   "PROD6L",   "v11r31p27", "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6M,   "PROD6M",   "v11r31p5",  "v5r29p21");
  ND::versioning().AddProduction(ProdId::PROD6N,   "PROD6N",   "v11r31p27", "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6O,   "PROD6O",   "v11r31p27", "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6P,   "PROD6P",   "v11r31p29", "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6Q,   "PROD6Q",   "v11r31p37", "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6R,   "PROD6R",   "v11r31p35", "v5r29p29");
  ND::versioning().AddProduction(ProdId::PROD6S,   "PROD6S",   "v11r31p41", "v5r29p25");
  ND::versioning().AddProduction(ProdId::PROD6T,   "PROD6T",   "v11r31p43", "v5r29p31");
  ND::versioning().AddProduction(ProdId::PROD6U,   "PROD6U",   "v11r31p43", "v5r29p31");
  ND::versioning().AddProduction(ProdId::PROD6V,   "PROD6V",   "v11r31p45", "v5r29p31");
  ND::versioning().AddProduction(ProdId::PROD6W,   "PROD6W",   "v11r31p57", "v5r29p33");
  ND::versioning().AddProduction(ProdId::PROD6W,   "PROD6W",   "v11r31p57", "v5r29p33");
  ND::versioning().AddProduction(ProdId::PROD6X,   "PROD6X",   "v11r31p51", "v5r29p33");
  ND::versioning().AddProduction(ProdId::PROD6Y,   "PROD6Y",   "v11r31p61", "v5r29p35");
  ND::versioning().AddProduction(ProdId::PROD6Z,   "PROD6Z",   "v11r31p63", "v5r29p35");
  ND::versioning().AddProduction(ProdId::PROD6AA,  "PROD6AA",  "v11r31p67", "v5r29p37");
  
  //May change when production evolves
  ND::versioning().AddProduction(ProdId::PROD7RC1, "PROD7RC1", "v12r5",  "v6r1");
  ND::versioning().AddProduction(ProdId::PROD7A,   "PROD7A",   "v12r9",  "v6r3");
  ND::versioning().AddProduction(ProdId::PROD7B1,  "PROD7B1",  "v12r15", "v6r3");
  ND::versioning().AddProduction(ProdId::PROD7B2,  "PROD7B2",  "v12r19", "v6r7");
  ND::versioning().AddProduction(ProdId::PROD7V01, "PROD7V01", "13.7",   "6.14");
  ND::versioning().AddProduction(ProdId::PROD7V02, "PROD7V02", "13.9",   "6.14");
  ND::versioning().AddProduction(ProdId::PROD7V03, "PROD7V03", "13.9",   "6.14");
  ND::versioning().AddProduction(ProdId::PROD7V06, "PROD7V06", "13.14",  "6.17");
  ND::versioning().AddProduction(ProdId::PROD7V07, "PROD7V07", "13.15",  "7.2");
  ND::versioning().AddProduction(ProdId::PROD7V09, "PROD7V09", "13.16",  "7.3");
  ND::versioning().AddProduction(ProdId::PROD7V12, "PROD7V12", "13.21",  "7.4");
}

//********************************************************************
ProdId_h anaUtils::GetProductionIdFromoaAnalysisReader(){
//********************************************************************

  ProdId_h prodId=UNKNOWN_PRODUCTION;

  // Add here only software versions having a reader in oaAnalysisReader package, which correspond to different versions of oaAnalysis

  // ---- Production 5 ----
#if   EQUALS_ANATOOLS_FILE(10,11,0)
  prodId=ProdId::PROD5D;  
#elif EQUALS_ANATOOLS_FILE(10,11,17)
  prodId=ProdId::PROD5E;
#elif EQUALS_ANATOOLS_FILE(10,11,19)
  prodId=ProdId::PROD5F;

  // ---- Production 6 ----
#elif (!BEFORE_ANATOOLS_FILE(11,17,0) && BEFORE_ANATOOLS_FILE(11,29,0))
  prodId=ProdId::PROD6PRE;  
#elif EQUALS_ANATOOLS_FILE(11,31,0)
  prodId=ProdId::PROD6B;  
#elif EQUALS_ANATOOLS_FILE(11,31,5)
  prodId=ProdId::PROD6E;
#elif EQUALS_ANATOOLS_FILE(11,31,7)
  prodId=ProdId::PROD6G;
#elif EQUALS_ANATOOLS_FILE(11,31,9)  // TREx version
  prodId=ProdId::PROD6H;
#elif EQUALS_ANATOOLS_FILE(11,31,35)
  prodId=ProdId::PROD6R;
#elif EQUALS_ANATOOLS_FILE(11,31,43)
  prodId=ProdId::PROD6T;
#elif EQUALS_ANATOOLS_FILE(11,31,51)
  prodId=ProdId::PROD6X;
#elif EQUALS_ANATOOLS_FILE(11,31,61)
  prodId=ProdId::PROD6Y;
#elif EQUALS_ANATOOLS_FILE(11,31,63)
  prodId=ProdId::PROD6Z;
#elif EQUALS_ANATOOLS_FILE(11,31,67) 
  prodId=ProdId::PROD6AA;
  
  // ---- Production 7 ----
#elif EQUALS_ANATOOLS_FILE(12,5,0)
  prodId=ProdId::PROD7RC1;
#elif EQUALS_ANATOOLS_FILE(12,15,0)
  prodId=ProdId::PROD7B1;
#elif EQUALS_ANATOOLS_FILE(12,19,0)
  prodId=ProdId::PROD7B2;
#elif EQUALS_ANATOOLS_FILE(13,9,0)
  prodId=ProdId::PROD7V02; 
#elif EQUALS_ANATOOLS_FILE(13, 14, 0)
  prodId=ProdId::PROD7V06;
#elif EQUALS_ANATOOLS_FILE(13, 15, 0)
  prodId=ProdId::PROD7V07;
#elif EQUALS_ANATOOLS_FILE(13, 16, 0)
  prodId=ProdId::PROD7V09;
#elif EQUALS_ANATOOLS_FILE(13, 21, 0)
  prodId=ProdId::PROD7V12;
#elif !BEFORE_ANATOOLS_FILE(13,21, 0)
  prodId=ProdId::PROD7DEVEL;
#endif
  return prodId;

}
