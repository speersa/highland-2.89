#! /bin/bash
path_remove ()  { export PATH=`echo -n $PATH | awk -v RS=: -v ORS=: '$0 != "'$1'"' | sed 's/:$//'`; } 
path_prepend ()  { path_remove $1; export PATH="$1:$PATH" ;} 

LOCATION=${ND280_ROOT}
if [ ! -z ${ND280PILOT_ROOT+x} ]; then 
	LOCATION=${ND280PILOT_ROOT}
fi

source $LOCATION/nd280SoftwarePilot/nd280SoftwarePilot.profile

path_prepend $ND280_ROOT/highland2SoftwarePilot/scripts


