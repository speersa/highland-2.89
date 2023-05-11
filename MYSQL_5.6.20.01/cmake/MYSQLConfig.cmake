#
#
macro(set_and_check _var _file)
  set(CHECK "OK")
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    set(CHECK "NOTOK")
    ND280_DEBUG("File or directory ${_file} referenced by variable ${_var} does not exist (yet) !")
  endif()
endmacro()
#
###################################################################################
get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)
set(PACKAGE_PREFIX_DIR ${PACKAGE_PREFIX_DIR}/${MYSQLCONFIG})
#
# define the variables MYSQL_LIBRARIES amd MYSQL_INCLUDE_DIRS for later use when compiling
# andlinking exectutables
#
set_and_check(MYSQL_BINARY_DIR "${PACKAGE_PREFIX_DIR}/bin")
if(${CHECK} STREQUAL "OK" )
execute_process(COMMAND  ${MYSQL_BINARY_DIR}/mysql_config --libs
                OUTPUT_VARIABLE MYSQL_LIBRARIES
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ) 
execute_process(COMMAND  ${MYSQL_BINARY_DIR}/mysql_config --include
                OUTPUT_VARIABLE MYSQL_INCLUDE_DIRS
                 OUTPUT_STRIP_TRAILING_WHITESPACE
                ) 
# We only need the directory so remove the -I from the front of the variabe MYSQL_INCLUDE_DIRS
#
string(REPLACE "-I" "" MYSQL_INCLUDE_DIRS ${MYSQL_INCLUDE_DIRS})
  ND280_DEBUG("MYSQL_INCLUDE_DIRS =   ${MYSQL_INCLUDE_DIRS}")
   ND280_DEBUG(" MYSQL_LIBRARIES = ${MYSQL_LIBRARIES} ")

else()
  ND280_DEBUG(" MYSQL_BINARY_DIR - ${PACKAGE_PREFIX_DIR}/bin NOT FOUND ")
endif()
