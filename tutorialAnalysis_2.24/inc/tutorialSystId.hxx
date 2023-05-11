#ifndef tutorialSystId_hxx_seen
#define tutorialSystId_hxx_seen

#include "SystId.hxx"


namespace tutorialSystId{
// Here we create an enum with all systematics we want to add starting at the last systematic it was added by used analyses or base analyses, 
  enum tutorialSystEnum{
    kTutorialWeight = SystId::SystEnumLast_SystId+1,
    kTutorialVariation,
    tutorialSystEnumLast_SystId
  };
};


#endif
