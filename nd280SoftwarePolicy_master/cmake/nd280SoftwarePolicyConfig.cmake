get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
#message( "PACKAGE_PREFIX_DIR: ${PACKAGE_PREFIX_DIR}")
macro(set_and_check _var _file)
	set(${_var} "${_file}")
	if(NOT EXISTS "${_file}")
		message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
	endif()
endmacro()
####################################################################################
#---Define location of version and modules directories
set_and_check(ND280SOFTWAREPOLICY_VERSION_FRAGMENT "${PACKAGE_PREFIX_DIR}/version")
set_and_check(ND280SOFTWAREPOLICY_MODULES          "${PACKAGE_PREFIX_DIR}/modules")
#
#---Define standard ND280 functions
include(${ND280SOFTWAREPOLICY_MODULES}/standardFunctions.cmake)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
#
#---Extend existing CXX flags
set(CMAKE_CXX_FLAGS "-DND280SOFTWAREPOLICY_CXXFLAGS -pipe -fPIC -pthread  -Wall -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual")

if(NOT "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "aarch64")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
endif()

#
# Add compiler version specific flags
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # Explicitly set expectations for unspecified loader behavior.
  # These are behaviours that are common, but for which there is not
  # standard.
  #
  #   -fcommon : means that multiply defined globals (like fortran
  #        common blocks) go in the right ELF segment.  Loader
  #        behaviour is taken from the first object file.
  #
  #   --no-as-needed : means the libraries don't need to be in the
  #        right order
  #
  add_compile_options("-fcommon")
  add_link_options("-Wl,--no-as-needed")
endif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#
# override default optimisations for release builds
# 
set(CMAKE_CXX_FLAGS_RELEASE " -DND280SOFTWAREPOLICY_RELEASE -DNDEBUG -g -O2 " CACHE STRING "C++ compilation Release build flags" FORCE )
set(CMAKE_CXX_FLAGS_DEBUG   " -DND280SOFTWAREPOLICY_DEBUG  -g -Og " CACHE STRING "C++ compilation Debug build flags"   FORCE )
#
# Now make the default build type RELEASE if it is not already specified
#
#
set(nd280SoftwarePolicyROOT ${PACKAGE_PREFIX_DIR}  CACHE PATH "nd280SoftwarePolicyROOT for CMT compatability" FORCE )
#
# set ND280JOBS 
#
if( "$ENV{ND280JOBS}" STREQUAL "")
	set(ND280JOBS 1 )
else()
	set(ND280JOBS $ENV{ND280JOBS} )
endif()
#
set_property(GLOBAL PROPERTY  nd280SoftwarePolicy_NOLIBRARY "TRUE")
#
#DEBUG
