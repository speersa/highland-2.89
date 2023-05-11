#!/bin/bash 
#! This file was autogenerated by ND280_END_PROJECT 
 [  -z "$1" ] && set -e 
 ND280_NJOBS="${ND280_NJOBS:=1}" 
  
export ND280_NJOBS=${ND280_NJOBS}
function shout {
  echo "+=====================================================================+" 
 echo "+                                                                     +" 
 echo "+  nd280 Build Is Incomplete, Please Check Stdout/Stderr for Errors   +" 
 echo "+                                                                     +" 
 echo "+=====================================================================+" 
 exit 1 
  } 
 [  "$1" != "documentation" ] && trap shout ERR 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 15              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level15make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 14              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level14make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 13              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level13make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 12              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level12make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 11              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level11make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 10              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level10make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 9              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level9make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 8              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level8make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 7              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level7make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 6              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level6make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 5              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level5make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 4              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level4make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 3              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level3make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 2              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level2make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
echo "============================================"
echo "                                            "
echo "                                            "
echo "                                            "
echo "        Process level 1              "
echo "                                            "
echo "                                            "
echo "                                            "
echo "                                            "
echo "============================================"
find ../bin -name "Level1make*.sh" -print0 | xargs -0 -I NAME -P ${ND280_NJOBS} /bin/bash NAME "$1"  "$2" 
 echo ""
 echo " All packages built succesfully. " 
 echo ""
 