#!/bin/bash 
 set -e 
ND280_SYSTEM=`nd280-system` 
export ND280_NJOBS=${ND280_NJOBS:=1}
  if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackagepsycheROOT.sh 
  fi 
    if [ -f /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/cmake/CMakeLists.txt ] ; then
  echo " cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/${ND280_SYSTEM}/ ;cmake ../cmake ; " >../bin/cmakePackageoaAnalysisReader.sh 
  fi 
  find ../bin -name 'cmakePackage*.sh' -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1" "$2"  
