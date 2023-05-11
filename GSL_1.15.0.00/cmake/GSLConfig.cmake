####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was MYSQLConfig.cmake.in                            ########

macro(set_and_check _var _file)
  set(CHECK "OK")
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    set(CHECK "NOTOK")
    ND280_DEBUG("File or directory ${_file} referenced by variable ${_var} does not exist (yet) !")
  endif()
endmacro()


####################################################################################
# define the variable GSL_LIBRARIES for later use when linking exectutables
get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)
set(PACKAGE_PREFIX_DIR ${PACKAGE_PREFIX_DIR}/${GSLCONFIG})

set_and_check(GSL_BINARY_DIR "${PACKAGE_PREFIX_DIR}/bin")
if(${CHECK} STREQUAL "OK" )
#message("e xecute_process(COMMAND  ${GSL_BINARY_DIR}/gsl-config --libs ")
execute_process(COMMAND  ${GSL_BINARY_DIR}/gsl-config --libs
OUTPUT_VARIABLE GSL_LIBRARIES
OUTPUT_STRIP_TRAILING_WHITESPACE
) 
#message(" the command ${GSL_BINARY_DIR}/gsl-config --libs returned ${GSL_LIBRARIES}")
include_directories(${PACKAGE_PREFIX_DIR}/include)

else()
ND280_DEBUG(" GSL_BINARY_DIR - ${PACKAGE_PREFIX_DIR}/bin NOT FOUND ")
endif()

