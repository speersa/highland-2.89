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
  find ../bin -name 'cmakePackage*.sh' -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1" "$2"  
