#include "numuCC4piMultiPiAnalysis.hxx"
#include "AnalysisLoop.hxx"

int main(int argc, char *argv[]){
  numuCC4piMultiPiAnalysis* ana = new numuCC4piMultiPiAnalysis();
  AnalysisLoop loop(ana, argc, argv); 
  loop.Execute();
}
