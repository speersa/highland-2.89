#!/bin/bash 
#! This file was autogenerated by ND280_END_PROJECT 
 [  -z "$1" ] && set -e 
 ND280_NJOBS="${ND280_NJOBS:=1}" 
  
export ND280_NJOBS=${ND280_NJOBS}
function shout {
  echo "+=======================================+" 
 echo "+                                       +" 
 echo "   Build of package baseP0DAnalysis_2.7 in  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseP0DAnalysis_2.7  FAILED   ( Level = 2 )       " 
 echo "+                                       +" 
 echo "+=======================================+" 
 exit 1 
 } 
 trap shout ERR 
  echo "" ; echo " Building baseP0DAnalysis_2.7  ( package number " 27 " out of " 28 " at level 2 ) " ; echo "" 
   makeTarget=$1 
  if [ "$1" == "documentation" ] ; then makeTarget=baseP0DAnalysis_$1 ; fi 
   cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseP0DAnalysis_2.7 
 SYS_DIR=`nd280-system` 
  [ -d ${SYS_DIR} ] || mkdir ${SYS_DIR} 
  cd  ${SYS_DIR} 
  [ -d inc ] || mkdir inc 
  [ -d bin ] || mkdir bin 
  [ -d lib ] || mkdir lib 
  cmake ../cmake $2 
 [ -f ../bin/setup.sh ] && . ../bin/setup.sh 
  make -j ${ND280_NJOBS}  ${makeTarget} ;
