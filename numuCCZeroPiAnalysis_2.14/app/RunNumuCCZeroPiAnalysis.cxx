#include "numuCCZeroPiAnalysis.hxx"
#include "AnalysisLoop.hxx"

int main(int argc, char *argv[]){
  numuCCZeroPiAnalysis* ana = new numuCCZeroPiAnalysis();
  AnalysisLoop loop(ana, argc, argv); 
  loop.Execute();
}
