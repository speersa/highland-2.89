#!/bin/bash 
#! This file was autogenerated by ND280_END_PROJECT 
 [  -z "$1" ] && set -e 
 ND280_NJOBS="${ND280_NJOBS:=1}" 
  
export ND280_NJOBS=${ND280_NJOBS}
function shout {
  echo "+=======================================+" 
 echo "+                                       +" 
 echo "   Build of package psycheIO_3.40 in  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40  FAILED   ( Level = 1 )       " 
 echo "+                                       +" 
 echo "+=======================================+" 
 exit 1 
 } 
 trap shout ERR 
  echo "" ; echo " Building psycheIO_3.40  ( package number " 6 " out of " 6 " at level 1 ) " ; echo "" 
   makeTarget=$1 
  if [ "$1" == "documentation" ] ; then makeTarget=psycheIO_$1 ; fi 
   cd  /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40 
 SYS_DIR=`nd280-system` 
  [ -d ${SYS_DIR} ] || mkdir ${SYS_DIR} 
  cd  ${SYS_DIR} 
  [ -d inc ] || mkdir inc 
  [ -d bin ] || mkdir bin 
  [ -d lib ] || mkdir lib 
  cmake ../cmake $2 
 [ -f ../bin/setup.sh ] && . ../bin/setup.sh 
  make -j ${ND280_NJOBS}  ${makeTarget} ;
