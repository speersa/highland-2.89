#ifndef CategUtilsFgdTimeBins_hxx
#define CategUtilsFgdTimeBins_hxx

#include "BasicUtils.hxx"
#include "CategoriesUtils.hxx"

namespace fgd_tbins_categs{


 //int GetPDGFromG4ID(const AnaTrueVertex& vtx, int G4ID);
   
 void FillCategories(AnaEventB* event,       AnaTrack* track,    AnaFgdTimeBin* bin, 
     const std::string& prefix, const SubDetId::SubDetEnum det=SubDetId::kFGD1, bool useCATSAND = true);

 void AddCategories(const std::string& prefix = "");


};



#endif


