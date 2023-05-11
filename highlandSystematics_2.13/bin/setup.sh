# Setup the PATH and LD_LIBRARY_PATH environment variables 
# and run all setup scripts
HERE=`pwd` 
export ND280_SYSTEM=`nd280-system` 
unset -f path_remove 
unset -f path_append 
unset -f ld_remove 
unset -f ld_append 
path_remove ()  { export PATH=`echo -n $PATH | awk -v RS=: -v ORS=: '$0 != "'$1'"' | sed 's/:$//'`; } 
path_append ()  { path_remove $1; export PATH="$PATH:$1" ;} 
ld_remove ()  { export LD_LIBRARY_PATH=`echo -n $LD_LIBRARY_PATH | awk -v RS=: -v ORS=: '$0 != "'$1'"' | sed 's/:$//'`; } 
ld_append ()  { ld_remove $1; export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$1" ;} 
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandSystematics_2.13/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandSystematics_2.13/${ND280_SYSTEM}/lib 
export ND280SOFTWAREPOLICYROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/nd280SoftwarePolicy_master/modules/.. 
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10/${ND280_SYSTEM}/lib 
export PSYCHEROOTROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10 
export PSYCHEROOTCONFIG=${ND280_SYSTEM}  
for file in /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheROOT_3.10/setup_script/*.sh ; do [ -f $file ] && . $file ; done
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheCore_3.51/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheCore_3.51/${ND280_SYSTEM}/lib 
export PSYCHECOREROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheCore_3.51 
export PSYCHECORECONFIG=${ND280_SYSTEM}  
for file in /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheCore_3.51/setup_script/*.sh ; do [ -f $file ] && . $file ; done
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCore_2.46/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCore_2.46/${ND280_SYSTEM}/lib 
export HIGHLANDCOREROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCore_2.46 
export HIGHLANDCORECONFIG=${ND280_SYSTEM}  
for file in /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCore_2.46/setup_script/*.sh ; do [ -f $file ] && . $file ; done
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheEventModel_3.47/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheEventModel_3.47/${ND280_SYSTEM}/lib 
export PSYCHEEVENTMODELROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheEventModel_3.47 
export PSYCHEEVENTMODELCONFIG=${ND280_SYSTEM}  
for file in /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheEventModel_3.47/setup_script/*.sh ; do [ -f $file ] && . $file ; done
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/${ND280_SYSTEM}/lib 
export OAANALYSISREADERROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29 
export OAANALYSISREADERCONFIG=${ND280_SYSTEM}  
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/${ND280_SYSTEM}/lib 
export HIGHLANDEVENTMODELROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43 
export HIGHLANDEVENTMODELCONFIG=${ND280_SYSTEM}  
for file in /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/setup_script/*.sh ; do [ -f $file ] && . $file ; done
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheUtils_3.36/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheUtils_3.36/${ND280_SYSTEM}/lib 
export PSYCHEUTILSROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheUtils_3.36 
export PSYCHEUTILSCONFIG=${ND280_SYSTEM}  
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/${ND280_SYSTEM}/lib 
export PSYCHEND280UTILSROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73 
export PSYCHEND280UTILSCONFIG=${ND280_SYSTEM}  
for file in /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/setup_script/*.sh ; do [ -f $file ] && . $file ; done
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandUtils_2.46/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandUtils_2.46/${ND280_SYSTEM}/lib 
export HIGHLANDUTILSROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandUtils_2.46 
export HIGHLANDUTILSCONFIG=${ND280_SYSTEM}  
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40/${ND280_SYSTEM}/lib 
export PSYCHEIOROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40 
export PSYCHEIOCONFIG=${ND280_SYSTEM}  
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSelections_3.60/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSelections_3.60/${ND280_SYSTEM}/lib 
export PSYCHESELECTIONSROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSelections_3.60 
export PSYCHESELECTIONSCONFIG=${ND280_SYSTEM}  
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSystematics_3.62/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSystematics_3.62/${ND280_SYSTEM}/lib 
export PSYCHESYSTEMATICSROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSystematics_3.62 
export PSYCHESYSTEMATICSCONFIG=${ND280_SYSTEM}  
path_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandSystematics_2.13/${ND280_SYSTEM}/bin 
ld_append /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandSystematics_2.13/${ND280_SYSTEM}/lib 
export HIGHLANDSYSTEMATICSROOT=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandSystematics_2.13 
export HIGHLANDSYSTEMATICSCONFIG=${ND280_SYSTEM}  
export LD_LIBRARY_PATH=`echo $LD_LIBRARY_PATH | sed 's/^://g'`
cd $HERE 
