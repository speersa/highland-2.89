# thisroot.sh has to be run so that all ROOT env settings are set

# comment this out in case want to use local ROOT version
#return()

if (NOT EXISTS $ENV{ROOTSYS}) 
  message(FATAL_ERROR
    "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
    "psycheROOT: $ROOTSYS is not set."
    " Probably need to source thisroot.sh"
    "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
    )
endif()

## Set ROOT related vars for later usage in standardFunctions.cmake
set(ROOTROOT $ENV{ROOTSYS} CACHE PATH "ROOTROOT" FORCE)
set(ROOTCONFIG "" CACHE PATH "ROOTCONFIG" FORCE)


set (root_cmd "root-config")
set (root_cmd_ver_arg "--version")
set (root_cmd_inc_arg "--incdir")
set (root_cmd_lib_arg "--ldflags" "--glibs" )

message(STATUS "root cmd: ${root_cmd}")

# Version of ROOT
execute_process(COMMAND ${root_cmd} ${root_cmd_ver_arg} OUTPUT_VARIABLE psycheROOT_USED_ROOT_VERSION)

string (REGEX MATCHALL "[0-9]+" _versionComponents "${psycheROOT_USED_ROOT_VERSION}")
list (LENGTH _versionComponents _len)
if (${_len} GREATER 0)
  list(GET _versionComponents 0 psycheROOT_ROOTVERSION_MAJOR)
  set(ROOT_VERSION_MAJOR ${psycheROOT_ROOTVERSION_MAJOR} CACHE PATH "ROOT version major" FORCE)
  
endif()


# Includes
execute_process(COMMAND ${root_cmd} ${root_cmd_inc_arg} OUTPUT_VARIABLE psycheROOT_INCLUDE_DIRS OUTPUT_STRIP_TRAILING_WHITESPACE)

set(psycheROOT_INCLUDE_DIRS ${psycheROOT_INCLUDE_DIRS} CACHE PATH "path to ROOT include" FORCE)


# Libraries
execute_process(COMMAND ${root_cmd} ${root_cmd_lib_arg} OUTPUT_VARIABLE psycheROOT_LIBRARIES OUTPUT_STRIP_TRAILING_WHITESPACE)

# ROOT libs for highland/psyche
string(APPEND psycheROOT_LIBRARIES " -lEG -lGeom -lMinuit -lFumili -lXMLIO -lRooFit -lRooFitCore")

set(psycheROOT_LIBRARIES ${psycheROOT_LIBRARIES} CACHE PATH "path to ROOT libraries" FORCE)



