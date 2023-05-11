#!/bin/bash 
 set -e 
ND280_SYSTEM=`nd280-system` 
export ND280_NJOBS=${ND280_NJOBS:=1}
  if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheROOT.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheCore_3.51/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheCore_3.51/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheCore.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheEventModel_3.47/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheEventModel_3.47/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheEventModel.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheUtils_3.36/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheUtils_3.36/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheUtils.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheND280Utils.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheIO.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSelections_3.60/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSelections_3.60/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheSelections.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSystematics_3.62/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSystematics_3.62/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheSystematics.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSteering_3.46/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSteering_3.46/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheSteering.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheMaster_3.85/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheMaster_3.85/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheMaster.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCore_2.46/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCore_2.46/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandCore.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackageoaAnalysisReader.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandEventModel.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandTools_2.32/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandTools_2.32/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandTools.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandUtils_2.46/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandUtils_2.46/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandUtils.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCorrections_2.33/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCorrections_2.33/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandCorrections.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandIO_2.53/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandIO_2.53/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandIO.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandSystematics_2.13/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandSystematics_2.13/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandSystematics.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseAnalysis_2.36/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseAnalysis_2.36/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagebaseAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseTrackerAnalysis_2.26/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseTrackerAnalysis_2.26/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagebaseTrackerAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCAnalysis_2.22/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCAnalysis_2.22/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagenumuCCAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCMultiPiAnalysis_2.32/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCMultiPiAnalysis_2.32/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagenumuCCMultiPiAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCC4piMultiPiAnalysis_2.1/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCC4piMultiPiAnalysis_2.1/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagenumuCC4piMultiPiAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/antiNumuCCAnalysis_2.7/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/antiNumuCCAnalysis_2.7/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackageantiNumuCCAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/antiNumuCCMultiPiAnalysis_2.12/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/antiNumuCCMultiPiAnalysis_2.12/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackageantiNumuCCMultiPiAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuBkgInAntiNuModeAnalysis_2.12/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuBkgInAntiNuModeAnalysis_2.12/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagenumuBkgInAntiNuModeAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/nueCCAnalysis_2.30/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/nueCCAnalysis_2.30/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagenueCCAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/antiNueCCAnalysis_2.18/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/antiNueCCAnalysis_2.18/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackageantiNueCCAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/gammaAnalysis_2.19/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/gammaAnalysis_2.19/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagegammaAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCZeroPiAnalysis_2.14/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCZeroPiAnalysis_2.14/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagenumuCCZeroPiAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/p0dNumuCCAnalysis_2.17/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/p0dNumuCCAnalysis_2.17/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagep0dNumuCCAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseP0DAnalysis_2.7/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseP0DAnalysis_2.7/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagebaseP0DAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/tutorialAnalysis_2.24/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/tutorialAnalysis_2.24/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagetutorialAnalysis.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandValidation_2.19/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandValidation_2.19/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighlandValidation.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highland2Master_2.89/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highland2Master_2.89/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagehighland2Master.sh 
  fi 
  find ../bin -name 'cmakePackage*.sh' -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1" "$2"  
