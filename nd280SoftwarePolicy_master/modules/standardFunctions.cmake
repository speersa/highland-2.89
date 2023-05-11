## CMAKE_DOCUMENTATION_START file standardFunctions.cmake
##
##  The file standardFunctions contains a number of functions used to build nd280 software.
##
##  Each package has a cmake directory containing the following files
##
##   \\li <B> CMakeLists.txt </B> Main control file used by CMAKE.
##   \\li <B>\\<packageName\\>Version.cmake </b>  Unique location that the version number is defined.
##   \\li <B>\\<packageName\\>ND280_USE.cmake  </b> Contains lines of the form ND280_USE(<package>  ) which specify which packages this package requires.
##   \\li <B>\\<packageName\\>ConfigVersion.cmake </b> Standard template for checking the version number. It includes \\<packageName\\>Version.cmake to actually set the version number
##   \\li <B> \\<packageName\\>Config.cmake  </b> Processed by CMAKE's find_project() when a package higher in the tree requests this one. Includes \\<packageName\\>ND280_USE.cmake
## which triggers the construction of the entire hierarchy of packages upon which this one depends.
##
##
##  The following functions may be called from CMakeLists:
##
##  \\li  <b> ND280_PROJECT </b> Initialise  a new project.
##  \\li  <b>  ND280_STANDARD_LIBRARY </b>  Generate targets for a shared object library with the same name as the project.
##   \\li  <b> ND280_EXECUTABLE </b> Add a target to build an executable program.
##    \\li  <b>  ND280_TEST </b> Add a target to build an executable test program.
##   \\li  <b>  ND280_ADD_LIBRARY </b> Add non standard libraries to the list.
##   \\li  <b>  ND280_ADD_SCRIPT</b>  Add a soft link to an interpreted script.
##   \\li  <b>  ND280_INSTALL</b>  Copy application into the directory where binaries are stored.
##    \\li  <b>  ND280_NO_LIBRARY</b>  Flag that this project does not create a library
##   \\li   <b> ND280_PATH_APPEND</b>  Add a directory to the PATH environment variable in setup.sh.
##   \\li   <b> ND280_SCRIPT</b> Install a  program.
##   \\li   <b> ND280_PYTHON_LIBRARY</b> Install one or more python modules.
##   \\li  <b> ND280_END_PROJECT</b> Create the shell scripts required to build this project and its subordinates in the correct order.
##
## The function <B>ND280_USE</B> is called by a package's <B> <packageName>ND280_USE.cmake </B> which is included by its
## <B> <packageName>Config.cmake </B> which is processed by find_project when a superior package requests this one. In this way
## the entire hierarchy of packages is constructed.
##
##
## CMAKE_DOCUMENTATION_END
#
# include the file which provides the git_describe command
#
set(ND280SOFTWAREPOLICYROOT ${CMAKE_CURRENT_LIST_DIR}/.. )
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_MODULE_PATH})
include(GetGitRevisionDescription)
##
## CMAKE_DOCUMENTATION_START function ND280_GLOB_FILES()
##  <B> ND280_GLOB_FILES (var [RECURSE] [RELATIVE path ] [FILTER regexp] <sources> ) </B>
## \\brief Create a list of files.
## \\param RECURSE search is recursive
## \\param RELATIVE <path> Start search from path
## \\param  FILTER   <regexp>   Any items matching the regular expression are removed from the list.
## \\return The list of files is returned in  var.
##
## This is a wrapper around the CMAKE function file() \\n
## <b> Example of usage: </b> \n
## \\code
##  ND280_GLOB_FILES(_sources FILTER ".*.hxx .*.hh" RELATIVE \${\${PROJECT_NAME}_CMAKE_DIR}/inc  \${\${PROJECT_NAME}_CMAKE_DIR}/inc/&#47;&#42;.h )
## \\endcode
## CMAKE_DOCUMENTATION_END
function(ND280_GLOB_FILES variable)
  CMAKE_PARSE_ARGUMENTS(ARG "RECURSE" "RELATIVE;FILTER" "" ${ARGN})
  set(_possibly_recurse "")
  if (ARG_RECURSE)
    set(_possibly_recurse "_RECURSE")
  endif()
  if(ARG_RELATIVE)
    file(GLOB${_possibly_recurse} _sources RELATIVE ${ARG_RELATIVE} ${ARG_UNPARSED_ARGUMENTS})
  else()
    file(GLOB${_possibly_recurse} _sources ${ARG_UNPARSED_ARGUMENTS})
  endif()
  if(ARG_FILTER)
    foreach(s ${_sources})
      if(s MATCHES ${ARG_FILTER})
        list(REMOVE_ITEM _sources ${s})
      endif()
    endforeach()
  endif()
  set(${variable} ${_sources} PARENT_SCOPE)
endfunction()
## CMAKE_DOCUMENTATION_START function ND280_GLOB_SOURCES()
##  <B> ND280_GLOB_SOURCES (var [SOURCELIST sources] ) </B>
## \\brief Create a list of  source files files.
## \\param SOURCELIST is a list of sources.
## \\return The list of files is returned in  var.
##
## Calls ND280_GLOB_FILES specifically to find source files. If the SOURCELIST parameter is
## present it looks in \${\${PROJECT_NAME}_CMAKE_DIR}/src  for files listed in \${ND280_GLOB_SOURCES_SOURCELIST}.
## Otherwise it looks in \${\${PROJECT_NAME}_CMAKE_DIR}/src for files: \\n
##  \${\${PROJECT_NAME}_CMAKE_DIR}/src&#47;&#42;.cxx  \\n
## \${\${PROJECT_NAME}_CMAKE_DIR}/src&#47;&#42;.cc       \\n
##  \${\${PROJECT_NAME}_CMAKE_DIR}/src&#47;&#42;.cpp   \\n
##  \${\${PROJECT_NAME}_CMAKE_DIR}/src&#47;&#42;.F     \\n
##  \${\${PROJECT_NAME}_CMAKE_DIR}/dict        \\n
## <b> Example of usage: </b> \\n
## \\code
##  ND280_GLOB_SOURCES(_sources )
## \\endcode
## CMAKE_DOCUMENTATION_END
function(ND280_GLOB_SOURCES variable)
  cmake_parse_arguments(ND280_GLOB_SOURCES "" "" "SOURCELIST" ${ARGN})
  if(DEFINED  ND280_GLOB_SOURCES_SOURCELIST)
    ND280_GLOB_FILES(_sources RECURSE RELATIVE  ${${PROJECT_NAME}_CMAKE_DIR}/src ${ND280_GLOB_SOURCES_SOURCELIST} )
  else()
    #ND280_DEBUG("    ND280_GLOB_FILES(_sources  RECURSE RELATIVE  \${\${PROJECT_NAME}_CMAKE_DIR}/src \${\${PROJECT_NAME}_CMAKE_DIR}/src/*.cxx \${\${PROJECT_NAME}_CMAKE_DIR}/src/*.cc \${\${PROJECT_NAME}_CMAKE_DIR}/src/*.cpp \${\${PROJECT_NAME}_CMAKE_DIR}/src/*.F \${\${PROJECT_NAME}_CMAKE_DIR}/dict)")
    ND280_GLOB_FILES(_sources  RECURSE RELATIVE  ${${PROJECT_NAME}_CMAKE_DIR}/src ${${PROJECT_NAME}_CMAKE_DIR}/src/*.cxx ${${PROJECT_NAME}_CMAKE_DIR}/src/*.cc ${${PROJECT_NAME}_CMAKE_DIR}/src/*.cpp ${${PROJECT_NAME}_CMAKE_DIR}/src/*.F ${${PROJECT_NAME}_CMAKE_DIR}/dict)
  endif()
  set(local "")
  foreach(s ${_sources})
    set(local ${local}  ${${PROJECT_NAME}_CMAKE_DIR}/src/${s} )
  endforeach()
  set(${variable} ${local} PARENT_SCOPE)
endfunction(ND280_GLOB_SOURCES)
## CMAKE_DOCUMENTATION_START function ND280_GENERATE_DICTIONARIES()
## <B> ND280_GENERATE_DICTIONARIES(variable)</B>
## \\brief Create rule to generate ROOT dictionary files.
## \\return The list of dictionary files which will be created  is returned in  variable.
##
## Searches for files called something_Linkdef.h in the \${\${PROJECT_NAME}_CMAKE_DIR}/inc directory.
## For each file found call ND280_GENERATE_DICTIONARY to create the rule to create the dictionary.
## CMAKE_DOCUMENTATION_END
function(ND280_GENERATE_DICTIONARIES variable)
  #
  # find all_LinkDef.h files in the /inc directory
  #
  ND280_GLOB_FILES(_sources FILTER ".*.hxx" RELATIVE ${${PROJECT_NAME}_CMAKE_DIR}/inc  ${${PROJECT_NAME}_CMAKE_DIR}/inc/*_LinkDef.h  ${${PROJECT_NAME}_CMAKE_DIR}/inc/*/*_LinkDef.h)
  set(local "")
  foreach(t ${_sources})
    get_filename_component(dictname ${t} NAME)
    # extract the part of the string before _LinkDef.h
    string(REPLACE "_LinkDef.h" "" nameOnly ${dictname})
    string(REPLACE "_LinkDef.h" "" nameAndSubDir ${t})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../${ND280_SYSTEM}/dict")
    #machineDependentOutput(OutputDirectory)
    set(CMAKE_INSTALL_LIBDIR "../${ND280_SYSTEM}/lib" )
    ND280_GENERATE_DICTIONARY("G_" ${nameOnly} ${nameAndSubDir}.hxx LINKDEF ${nameAndSubDir}_LinkDef.h)
    set(local ${local}  ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/G_${nameOnly}.cxx  )
  endforeach()
  set(${variable} ${local} PARENT_SCOPE)
endfunction(ND280_GENERATE_DICTIONARIES)
#---------------------------------------------------------------------------------------------------
#---ND280_GENERATE_DICTIONARY( precursor dictionary headerfiles MODULE module DEPENDENCIES dep1 dep2
#                                                    BUILTINS dep1 dep2
#                                                    STAGE1 LINKDEF linkdef OPTIONS opt1 opt2 ...)
#---------------------------------------------------------------------------------------------------
## CMAKE_DOCUMENTATION_START function ND280_GENERATE_DICTIONARY()
##
## <B> ND280_GENERATE_DICTIONARY( precursor dictionary headerfiles MODULE module DEPENDENCIES dep1 dep2 BUILTINS dep1 dep2 STAGE1 LINKDEF linkdef OPTIONS opt1 opt2 ...) </B>
##
## \\brief Creates the rules to create dictionary files from a list of headerfiles and LinkDef files.
##
## Based on ROOT's code to do the same thing.
## It also creates the DATESTAMP rule which puts the date of compilation
## of T\${PROJECT_NAME}_version into
## ../\${ND280_SYSTEM}/inc/\${PROJECT_NAME}_make_date.hxx
## CMAKE_DOCUMENTATION_END
function(ND280_GENERATE_DICTIONARY precursor nameOnly)
  set(dictionary ${precursor}${nameOnly})
  CMAKE_PARSE_ARGUMENTS(ARG "" "" "LINKDEF" ${ARGN})
  #---Get the list of include directories------------------
  get_directory_property(incdirs INCLUDE_DIRECTORIES)
  #ND280_DEBUG(" Getting the directory property INCLUDE_DIRECTORIES = ${incdirs}")
  if(EXISTS ${${PROJECT_NAME}_CMAKE_DIR}/inc)
    set(localinclude ${${PROJECT_NAME}_CMAKE_DIR}/inc)
  else()
    set(localinclude ${${PROJECT_NAME}_CMAKE_DIR})
  endif()
  #---Get the list of header files-------------------------
  set(headerfiles)
  set(_list_of_header_dependencies)
  #ND280_DEBUG(" ND280_GENERATE_DICTIONARY is forming the list of headerfiles ")
  get_property( ROOT_VERSION_MAJOR  GLOBAL PROPERTY ROOT_VERSION_MAJOR)
  #ND280_DEBUG(" ROOT major version is ${ROOT_VERSION_MAJOR}")
  foreach(fp ${ARG_UNPARSED_ARGUMENTS})
    #ND280_DEBUG("  consider ${fp}")
    if(${fp} MATCHES "[*?]") 
      # Is this header a globbing expression?
      file(GLOB files inc/${fp} ${fp})
      foreach(f ${files})
        if(NOT f MATCHES LinkDef) 
          # skip LinkDefs from globbing result
          list(APPEND headerfiles ${f})
          list(APPEND _list_of_header_dependencies ${f})
        endif()
      endforeach()
    elseif(IS_ABSOLUTE ${fp})
      list(APPEND headerfiles ${fp})
      list(APPEND _list_of_header_dependencies ${fp})
    else()
      find_file(headerFile ${fp} HINTS ${localinclude} ${incdirs} NO_DEFAULT_PATH)
      find_file(headerFile ${fp} NO_SYSTEM_ENVIRONMENT_PATH)
      if(headerFile)
        list(APPEND headerfiles ${headerFile})
        list(APPEND _list_of_header_dependencies ${headerFile})
      else()
        list(APPEND headerfiles ${fp})
      endif()
      unset(headerFile CACHE)
    endif()
  endforeach()
  #
  #construct the includedirs variable
  #
  if(EXISTS ${${PROJECT_NAME}_CMAKE_DIR}/inc)
    set(includedirs -I${${PROJECT_NAME}_CMAKE_DIR}/inc)
  endif()
  #
  # add include directories to the list for rootcint, unless the
  # environment variable <dirname>_NOTFORROOTCINT exists and has the value "TRUE"
  #
  foreach( d ${incdirs})
    if(NOT "$ENV{${d}_NOTFORROOTCINT}" STREQUAL "TRUE"  )
      set(includedirs ${includedirs} -I${d})
    endif()
  endforeach()
  list(REMOVE_DUPLICATES includedirs)
  set(includedirs ${includedirs} -I${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/inc)
  #---Get LinkDef.h file------------------------------------
  foreach( f ${ARG_LINKDEF})
    if( IS_ABSOLUTE ${f})
      set(_linkdef ${_linkdef} ${f})
    else()
      if(EXISTS ${${PROJECT_NAME}_CMAKE_DIR}/inc/${f})
        set(_linkdef ${_linkdef} ${${PROJECT_NAME}_CMAKE_DIR}/inc/${f})
      else()
        set(_linkdef ${_linkdef} ${${PROJECT_NAME}_CMAKE_DIR}/${f})
      endif()
    endif()
  endforeach()
  #---Build the names for library, pcm and rootmap file ----
  get_filename_component(dict_base_name ${dictionary} NAME_WE)
  if(dict_base_name MATCHES "^G__")
    string(SUBSTRING ${dictionary} 3 -1 deduced_arg_module)
  else()
    set(deduced_arg_module ${dict_base_name})
  endif()
  #---Set the library output directory-----------------------
  if(DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY AND NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY STREQUAL "")
    set(library_output_dir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  else()
    set(library_output_dir ${CMAKE_CURRENT_BINARY_DIR})
  endif()
  if(DEFINED CMAKE_LIBRARY_INSTALL_DIRECTORY AND NOT CMAKE_LIBRARY_INSTALL_DIRECTORY STREQUAL "")
    set(library_install_dir ${CMAKE_LIBRARY_INSTALL_DIRECTORY})
  else()
    set(library_install_dir ${CMAKE_CURRENT_BINARY_DIR}/${ND280_SYSTEM}/lib)
  endif()
  set(library_name ${libprefix}${deduced_arg_module}${libsuffix})
  set(newargs -s ${library_output_dir}/${library_name})
  set(pcm_name ${library_output_dir}/${libprefix}${deduced_arg_module}_rdict.pcm)
  set(rootmap_name ${library_output_dir}/${libprefix}${deduced_arg_module}.rootmap)
  set(command ${CMAKE_COMMAND} -E env "${runtime_cxxmodules_env}" rootcint)
  if( ${nameOnly} STREQUAL T${PROJECT_NAME}_version )
    add_custom_target(DATESTAMP
      echo -n  '\#define ${PROJECT_NAME}_COMPILE_DATE \"'  > ../${ND280_SYSTEM}/inc/${PROJECT_NAME}_make_date.hxx
      COMMAND echo  -n `date`  >> ../${ND280_SYSTEM}/inc/${PROJECT_NAME}_make_date.hxx
      COMMAND echo   '\" ' >> ../${ND280_SYSTEM}/inc/${PROJECT_NAME}_make_date.hxx
      COMMENT "Set the build date for ${PROJECT_NAME} version information")
    #---create rootcint target------------------------------------------
    # this is the ROOT 6 version
    if(  ${ROOT_VERSION_MAJOR} STREQUAL "6" )
      add_custom_command(OUTPUT ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx
        COMMAND ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint -v2 -f  ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx ${newargs} ${excludepathsargs}
        ${ARG_OPTIONS} ${definitions} ${includedirs} ${headerfiles} ${_linkdef}
        IMPLICIT_DEPENDS ${_implicitdeps}
        DEPENDS DATESTAMP ${_list_of_header_dependencies} ${_linkdef} ${ROOTCINTDEP} ${ARG_DEPENDENCIES} 
        COMMENT "Use ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint to generate the dictionary files ${dictionary}.cxx and ${dictionary}.h " )
    else()
      # ROOT 5 version
      add_custom_command(OUTPUT ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.h
        COMMAND ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint  -f  ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx
        -c -p -g -pipe -O -Wall -ansi -Wctor-dtor-privacy -Wnon-virtual-dtor -fpic -Woverloaded-virtual  ${includedirs} ${headerfiles} ${_linkdef}
        DEPENDS ${headerfiles} ${_linkdef}   DATESTAMP
        COMMENT "Use ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint to generate the dictionary files ${dictionary}.cxx and ${dictionary}.h " )
    endif()
    FILE(TOUCH ../${ND280_SYSTEM}/inc/${PROJECT_NAME}_make_date.hxx)
  else()
    if(  ${ROOT_VERSION_MAJOR} STREQUAL "6" )

      add_custom_command(OUTPUT ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx
        COMMAND ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint -v2 -f  ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx ${newargs} ${excludepathsargs}
        ${ARG_OPTIONS} ${definitions} ${includedirs} ${headerfiles} ${_linkdef}
        IMPLICIT_DEPENDS ${_implicitdeps}
        DEPENDS ${_list_of_header_dependencies} ${_linkdef} ${ROOTCINTDEP} ${ARG_DEPENDENCIES}
        COMMENT "Use ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint to generate the dictionary files ${dictionary}.cxx and ${dictionary}.h " )
    else()
      add_custom_command(OUTPUT ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.h
        COMMAND ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint    -f  ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict/${dictionary}.cxx
        -c -p -g -pipe -O -Wall -ansi -Wctor-dtor-privacy -Wnon-virtual-dtor -fpic -Woverloaded-virtual ${includedirs} ${headerfiles} ${_linkdef}
        DEPENDS ${headerfiles} ${_linkdef}
        COMMENT "Use ${ROOTROOT}/${ROOTCONFIG}/bin/rootcint to generate the dictionary files ${dictionary}.cxx and ${dictionary}.h   " )
    endif()
  endif()
  if(cpp_module)
    ROOT_CXXMODULES_APPEND_TO_MODULEMAP("${cpp_module}" "${headerfiles}")
  endif()
endfunction(ND280_GENERATE_DICTIONARY)
## CMAKE_DOCUMENTATION_START function ND280_STRIP_PACKAGE()
##<B> ND280_STRIP_PACKAGE(package string)</B>
## \\param string The text to be processed.
## \\return The new string is returned in the variable <package>
## \\brief Removes everything after the last _ from a string.
## If string is package_version, this is the name of the package.
## CMAKE_DOCUMENTATION_END
function(ND280_STRIP_PACKAGE package string)
  string(FIND ${string} "_" position REVERSE)
  string(SUBSTRING ${string} 0 ${position} result)
  set ( ${package} ${result} PARENT_SCOPE)
endfunction(ND280_STRIP_PACKAGE)
## CMAKE_DOCUMENTATION_START function ND280_STRIP_VERSION()
## <B> ND280_STRIP_VERSION(version string) </B>
## \\brief Removes everything before the first _ from a string.
## If string is package_version, this is the name of the package.
## \\param string The text to be processed.
## \\return The new string is returned in the variable <version>
## \\brief Removes everything after the last _ from a string.
## If string is package_version, this is the name of the package.
## CMAKE_DOCUMENTATION_END
function(ND280_STRIP_VERSION version string)
  string(FIND ${string} "_" position)
  math(EXPR position "${position}+1")
  string(SUBSTRING ${string}  ${position} -1 result)
  set( ${version} ${result} PARENT_SCOPE)
endfunction(ND280_STRIP_VERSION)
## CMAKE_DOCUMENTATION_START function ND280_CHECK_VERSION()
##
## <B> ND280_CHECK_VERSION(result package version) </B>
##
## \\param package package name
## \\param version version number
## \\return result is returned as true or false
##remove_leading_whitespace
##
## \\brief Find out if the package is in the existing list of nd280_PROJECTS.
##
## If it is not in the list return false.
## If it is in the list and the version does not match, return false
## Otherwiser return true.
## CMAKE_DOCUMENTATION_END
function(ND280_CHECK_VERSION result package version)
  get_property(ND280_PROJECTS GLOBAL PROPERTY ND280_PROJECTS)
  foreach(p ${ND280_PROJECTS})
    ND280_STRIP_PACKAGE(packageAlreadyProcessed ${p})
    if( ${packageAlreadyProcessed} STREQUAL ${p} )
      ND280_STRIP_VERSION(v ${p})
      if (${version} STREQUAL ${v})
        set (${result} "TRUE" PARENT_SCOPE)
        return()
      else()
        message(" ND280_CHECK_VERSION failed as requested version ${version} does not match existing version ${v}")
        set (${result} "FALSE" PARENT_SCOPE)
        return()
      endif()
    endif()
  endforeach()
  set (${result} "TRUE" PARENT_SCOPE)
endfunction(ND280_CHECK_VERSION)
## CMAKE_DOCUMENTATION_START function machineDependentOutput()
## <B> machineDependentOutput(result) </B>
## \\return The result is returned in <result>
## \\brief Find the name to use for directory where output is stored.
## Finds the machine and compiler dependent name which defines
## directory where all binaries and executables are stored.
## It is defined by the variable ND280_SYSTEM which is
## set by running the command nd280-system.
## CMAKE_DOCUMENTATION_END
function(machineDependentOutput ret)
  if(ND280_SYSTEM)
    if(NOT "${ND280_SYSTEM}" STREQUAL "")
      ND280_DEBUG(" ND280_SYSTEM = ${ND280_SYSTEM}")
      set(${ret} ${ND280_SYSTEM} PARENT_SCOPE)
      ND280_DEBUG(" machinedependentOutput returning ${ret} as  preexisting value of:  ${ND280_SYSTEM}")
      return()
    endif()
  endif()
  # set(${ret} "../lib" PARENT_SCOPE)
  execute_process(COMMAND nd280-system
    OUTPUT_VARIABLE nd280-system
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
 
  set(${ret} ${nd280-system} PARENT_SCOPE)
  set(ND280_SYSTEM ${nd280-system} CACHE STRING "Directory name to be used for building the software" FORCE)
  ND280_DEBUG(" SET VALUE OF ND280_SYSTEM TO  ${OutputDirectory} IN THE CACHE ")
  if (NOT nd280-system )
    message(FATAL_ERROR
      "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
      "Cannot determine system type (missing nd280-system command)."
      " Probably need to source nd280SoftwarePilot.profile in"
      " nd280SoftwarePilot or use nd280-setup."
      "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
      )
  endif()
 

  ND280_DEBUG(" machinedependentOutput returning value calculated by nd280-system command of ${ret}")
endfunction(machineDependentOutput)
## CMAKE_DOCUMENTATION_START function ND280_STANDARD_LIBRARY()
## \\brief Create a standard library with the same name as the package.
##
##<B> ND280_STANDARD_LIBRARY() </B>
##
## Generate a target for a shared object library with the same name
## as the project.
## Include directories are defined to be
## /inc and any subdirectories thereof.
## The \${ND280_SYSTEM}/lib directory is added to the list of
## places to look for shared libaries.
## ROOT dictionary file targets are created.
## A new library target is created which depends on the source files and header files.
## Add a target, which is dependent on the library, to run ../bin/setup.sh if it exists.
## Once library is built, copy all pcm files from dict/ to lib/
## NB pcm are a ROOT 6 feature.
## CMAKE_DOCUMENTATION_END
function(ND280_STANDARD_LIBRARY)
  ND280_DEBUG(" ND280_STANDARD_LIBRARY called ")
  ND280_DEBUG(" Libraries and Executables will be stored under the directory ${ND280_SYSTEM}/" )
  set(multiValueArgs SOURCELIST)
  set(options NODICTIONARY STATIC)
  cmake_parse_arguments(ND280_STANDARD_LIBRARY "${options}" "" "${multiValueArgs}" ${ARGN} )
  add_definitions(-DND280_CMAKE_BUILD)
  ND280_debug("Add standard library for project ${PROJECT_NAME}")
  # add our inc directory to the list of include directories
  ND280_debug("Add include directory: ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/inc")
  ND280_debug("Add include directory: ${${PROJECT_NAME}_CMAKE_DIR}/inc")

  include_directories(${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/inc)
  include_directories(${${PROJECT_NAME}_CMAKE_DIR}/inc)
  # and any subdirectories
  file(GLOB_RECURSE directories LIST_DIRECTORIES true RELATIVE  ${${PROJECT_NAME}_CMAKE_DIR}/inc ${${PROJECT_NAME}_CMAKE_DIR}/inc/* )
  FOREACH(child ${directories})
    # message(" looking in ${child}")
    if(IS_DIRECTORY   ${${PROJECT_NAME}_CMAKE_DIR}/inc/${child} )
      if(NOT ${child} MATCHES ".*/CVS*" AND NOT ${child} MATCHES ".*/.svn*")
        include_directories(${${PROJECT_NAME}_CMAKE_DIR}/inc/${child})
      endif()
    endif()
  endforeach()
  # add our  directory to the list of  directories containing shared object libraries to link to
  link_directories(${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/lib)
  # Create the necessary instructions to create dictionary files
  ND280_DEBUG(" Create a list of sources using a sourcelist of |${ND280_STANDARD_LIBRARY_SOURCELIST}|")
  ND280_GLOB_SOURCES(sources SOURCELIST ${ND280_STANDARD_LIBRARY_SOURCELIST} )
  file(MAKE_DIRECTORY   ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict)
  if( ND280_STANDARD_LIBRARY_NODICTIONARY STREQUAL "FALSE" )
    ND280_DEBUG(" generate dictionaries ")
    # create the directory where dict will go ( now done elsewhere )
    # add_custom_command(OUTPUT ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict
    #COMMAND ${CMAKE_COMMAND} -E make_directory ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict
    #COMMENT "Create the directory where ROOT dictionaries will be stored.")
    ND280_GENERATE_DICTIONARIES(dictionaries)
  endif()
  #---Create a shared library with generated dictionary
  if( ND280_STANDARD_LIBRARY_STATIC STREQUAL "TRUE" )
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/lib)
    add_library(${PROJECT_NAME}  STATIC ${sources} ${dictionaries} ../inc/${ND280_SYSTEM}/${PROJECT_NAME}_make_date.hxx)
  else()
    FILE(TOUCH ../${ND280_SYSTEM}/inc/${PROJECT_NAME}_make_date.hxx)
    add_library(${PROJECT_NAME}  SHARED ${sources} ${dictionaries} ../${ND280_SYSTEM}/inc/${PROJECT_NAME}_make_date.hxx )
    add_custom_target(RunSetup ALL
      COMMAND . ../bin/setup.sh | tee setup.log
      DEPENDS ../bin/setup.sh
      COMMENT " Source bin/setup.sh to initialise environment etc.")
    ADD_DEPENDENCIES (${PROJECT_NAME} RunSetup)
  endif()
  # create the directory where dict will go
  add_custom_command(TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict
    COMMENT "Create the directory where ROOT dictionaries will be stored.")
  #
  #-- Store library in the lib directory
  #--
  set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/lib )
  #
  #
  # once library is built, copy all pcm files from dict/ to lib/, but don't fail if there are none!
  # (alternatively this could be included in ND280_GENERATE_DICTIONARIES on a  per dictionary basis)
  # N.B. pcm files are a ROOT 6 feature
  #
  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${nd280SoftwarePolicyROOT}/modules/Copypcmfiles.sh ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/dict ../lib/
    COMMENT "Copy pcm files to ${ND280_SYSTEM}/lib directory"
    )
endfunction(ND280_STANDARD_LIBRARY)
## CMAKE_DOCUMENTATION_START function ND280_SCRIPT()
## <B> ND280_SCRIPT(filename) </B>
##
## \\param filename Name of a file to be installed.
##
## \\brief Copies a file to the standard location for executable programs.
##
## The file is assumed to be in the app directory: \${CMAKE_CURRENT_SOURCE_DIR}/../app/. If it exists
## it is installed in the
## bin directory:  \${CMAKE_CURRENT_BINARY_DIR}/../\${ND280_SYSTEM}/bin
## Note it is run at cmake time so is assumed to exist already, it is not
## built during the make process.
## CMAKE_DOCUMENTATION_END
#
function(ND280_SCRIPT filename )
  #  ND280_debug("add_executable(${filename} ${CMAKE_CURRENT_SOURCE_DIR}/../app/${filename})")#
  #machineDependentOutput(OutputDirectory)
  #add_custom_target( ${filename} ALL
  #  COMMAND install -t ${CMAKE_CURRENT_BINARY_DIR}/../${ND280_SYSTEM}/bin  ${CMAKE_CURRENT_SOURCE_DIR}/../app/${filename}
  #  SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/../app/${filename} )
  execute_process(COMMAND install -t ${CMAKE_CURRENT_BINARY_DIR}/../${ND280_SYSTEM}/bin  ${CMAKE_CURRENT_SOURCE_DIR}/../app/${filename})
endfunction(ND280_SCRIPT)
## CMAKE_DOCUMENTATION_START function ND280_PYTHON_LIBRARY()
## <B> ND280_PYTHON_LIBRARY(filenameglob) </B>
##
## \\param filename Name of a file to be installed.
##
## \\brief Creates a target to install python files.
##
## The filenameglob should include the path relative to the package directory:
## \${CMAKE_CURRENT_SOURCE_DIR}/. Files that match the glob are installed in the
## lib directory:  \${CMAKE_CURRENT_BINARY_DIR}/../\${ND280_SYSTEM}/lib
## CMAKE_DOCUMENTATION_END
#
function(ND280_PYTHON_LIBRARY filenameglob )
  ND280_GLOB_FILES( files ${CMAKE_CURRENT_SOURCE_DIR}/../${filenameglob} )
  foreach( f ${files} )
    get_filename_component(fname ${f} NAME)
    if(IS_DIRECTORY ${f})
      execute_process(
        COMMAND cp -pr ${f} ${CMAKE_CURRENT_BINARY_DIR}/../${ND280_SYSTEM}/lib
        )
    else()
      execute_process(
        COMMAND install -D --mode=0644 -t ${CMAKE_CURRENT_BINARY_DIR}/../${ND280_SYSTEM}/lib ${f}
        )
    endif()
  endforeach(f)
endfunction(ND280_PYTHON_LIBRARY)
## CMAKE_DOCUMENTATION_START function ND280_EXECUTABLE()
##
## <B>ND280_EXECUTABLE( name filename)</B>
##
## \\param  name    Name for the executable.
## \\param filename Name of source file containing main routine.
##
## \\brief Add a target to build an excutable program.
##
## Add the /app directory as a source of include files.
## Link to the shared library in this package, if there is one.
## Also link to the list of shared libraries from other packages, stored in
## ND280_PROJECTS.
## Non standard libraries (e.g. ROOT and Geant4) libraries are obtained from
## EXTERNAL_LINK_COMMANDS and as a special case, CERNLIB is from CERNLIB_LIBRARIES
## CMAKE_DOCUMENTATION_END
function(ND280_EXECUTABLE name filename)
  ND280_APPLICATION(${name} ${filename})
endfunction(ND280_EXECUTABLE)
## CMAKE_DOCUMENTATION_START function ND280_TEST()
##
## \\brief Add a target to build an excutable test program.
##
## \\param  name    Name for the executable.
## \\param filename1 Name of source file containing main routine.
## \\param filename2  Optional second file to be included.
## \\param filename3  Optional third file to be included.
##
## <B> ND280_TEST( name filename1   [filename2]   [filename3] ) </B>
##
##  Add a target to build an excutable test program.
## Add the /test directory as a source of include files.
## Link to the shared library in this package, if there is one.
## Also link to the list of shared libraries from other packages, stored in
## ND280_PROJECTS
## Non standard libraries (e.g. ROOT and Geant4) libraries are obtained from
## EXTERNAL_LINK_COMMANDS and as a special case, CERNLIB is from CERNLIB_LIBRARIES.
## We make a  "test" target depend on this target, so to get  tests to be built you must do "make test",
## they will not build by default. Example:
## \\code
## ND280_TEST(oaChanInfoTUT ../test/oaChanInfoTUT.cxx  ../test/func*.cxx ../test/tut*.cxx )
## \\endcode
## CMAKE_DOCUMENTATION_END
function(ND280_TEST name filename)
  ND280_APPLICATION(${name} ${filename} "TEST" ${ARGN})
endfunction(ND280_TEST)
## CMAKE_DOCUMENTATION_START function ND280_APPLICATION()
##
##  \\brief Add a target to build an application, normal or test.
##
## <B> ND280_APPLICATION( name filename1 [TEST] [filename2] [filename3] ) </B>
##
## \\param  name    Name for the executable.
## \\param filename Name of source file containing main routine.
## \\param TEST If present indeicates that a test application is being built.
## \\param filename2  Optional second file or pathname to be included for test programs.
## \\param filename3  Optional third file or pathname to be included for test programs.
##
##
## Add a target to build an excutable program. Special action is taken if the program is a test program.
## Add the /app directory as a source of include files if it is a test program otherwise
## add the /test directory as a source of include files.
## Link to the shared library in this package, if there is one.
## Also link to the list of shared libraries from other packages, stored in
## ND280_PROJECTS
## Non standard libraries (e.g. ROOT and Geant4) libraries are obtained from
## EXTERNAL_LINK_COMMANDS and as a special case, CERNLIB is from CERNLIB_LIBRARIES.
## We make a  "test" target depend on this target, so to get  tests to be built you must do "make test",
## they will not build by default. Example:
## \\code
## ND280_TEST(oaChanInfoTUT ../test/oaChanInfoTUT.cxx  ../test/func*.cxx ../test/tut*.cxx )
## \\endcode
## CMAKE_DOCUMENTATION_END
function(ND280_APPLICATION name filename1)
  cmake_parse_arguments(ND280_APPLICATION "TEST" "" "" ${ARGN})
  set(name ${name}.exe)
  #---Create  a main program using the library with input from the test directory
  if(ND280_APPLICATION_TEST)
    set(extraFiles "")
    if (${ARGC} GREATER 2 )
      file(GLOB extraFiles ${ARGV2})
      if (${ARGC} GREATER 3 )
        file(GLOB extraFiles2 ${ARGV3})
        set(extraFiles ${extraFiles} ${extraFiles2})
      endif()
    endif()
    ND280_debug("ND280_TEST: ${name} EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/../test/${filename1} ${extraFiles} ")
    add_executable(${name} EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/../test/${filename1} ${extraFiles})
    #
    # make the "test" target depend on this target,so to make tests you must do "make test"
    #
    add_dependencies(test ${name})
  else()
    ND280_debug("add_executable(${name} ${CMAKE_CURRENT_SOURCE_DIR}/../app/${filename})")
    add_executable(${name} ${CMAKE_CURRENT_SOURCE_DIR}/../app/${filename})
    target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../app)
  endif()
  #
  # assume we want to link to our own project shared object library, which will not be in
  # ND280_PROJECTS list at this point
  get_property(${PROJECT_NAME}_NOLIBRARY GLOBAL PROPERTY ${PROJECT_NAME}_NOLIBRARY)
  if(DEFINED ${PROJECT_NAME}_NOLIBRARY)
    ND280_debug(" The package ${PROJECT_NAME} has declared that it will not create a library ")
  else()
    target_link_libraries(${name} ${PROJECT_NAME})
  endif()
  #
  # and link to everything in ND280_PROJECTS
  #
  get_property(ND280_PROJECTS GLOBAL PROPERTY ND280_PROJECTS)
  foreach(p ${ND280_PROJECTS})
    ND280_STRIP_PACKAGE(package ${p})
    if(TARGET ${package})
      target_link_libraries(${name} ${package})
    endif()
  endforeach()
  #-- add to external libraries like ROOT MYSQL etc.
  get_property(EXTERNAL_LINK_COMMANDS GLOBAL PROPERTY EXTERNAL_LINK_COMMANDS)
  get_property(CERNLIB_LIBRARIES GLOBAL PROPERTY CERNLIB_LIBRARIES)
  #
  # We make a special case for the CERNLIB_LIBRARIES as they are the only statically linked libraries.
  # Could have made a more general solution, but decided to just fudge it for this one case. If in the future we obtain more
  # special cases then may have to find a better solution.
  #
  string(COMPARE EQUAL "${CERNLIB_LIBRARIES}" "" _cmpCL)
  if ( NOT _cmpCL )
    set(EXTERNAL_LINK_COMMANDS ${EXTERNAL_LINK_COMMANDS} ${CERNLIB_LIBRARIES})
  endif()
  string(COMPARE EQUAL "${EXTERNAL_LINK_COMMANDS}" "" _cmp)
  if ( NOT _cmp )
    nd280_debug(" adding external link commands: ${EXTERNAL_LINK_COMMANDS} for executable ${name} ")
    target_link_libraries(${name}  ${EXTERNAL_LINK_COMMANDS})
  endif()
  # and define that we will store the executable in  the /bin directory underneath our configureed OutputDirectory
  set_target_properties(${name}  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/bin )
endfunction(ND280_APPLICATION)
## CMAKE_DOCUMENTATION_START function ND280_USE()
## \\brief Use find_project() to configure a project required by this one.
##
## <B> ND280_USE(package [version|*] [CONFIGURE] [CONFIGURE_ADD] [configuration]) </B>
##
## \\param package Name of package we require.
## \\param version Exact version number  required. If absent or * then take the highest version found.
##  \\param [CONFIGURE] Treat following arguments as additional CMAKE configuration to be passed to the package
##  \\param [CONFIGURE_ADD] Treat following arguments as additional CMAKE configuration to be added to the configuration to be passed to the package
##
##  The first time a package is requested call find_package() to find it. The next time it is called we change its position in the
## hierarchy so that it is at the deepest point necessary so that it is built before any packages that need it.
## CMAKE_DOCUMENTATION_END
function(ND280_USE package)
  #
  # Set the indent value so that nd280_debug output it pretty
  #
  get_property(INDENT GLOBAL PROPERTY INDENT )
  math(EXPR INDENT "${INDENT}+2" )
  set_property(GLOBAL PROPERTY INDENT ${INDENT} )
  ND280_debug(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
  ND280_debug("ND280_USE called for ${ARGV} ")
  #
  # parse the arguments
  #
  CMAKE_PARSE_ARGUMENTS(ARG "" "" "CONFIGURE;CONFIGURE_ADD" ${ARGN})
  #
  # set the ND280_SYSTEM global variable, if it has not already been set
  #
  if(NOT ND280_SYSTEM)
    machineDependentOutput(OutputDirectory)

  endif()
  #
  # Increment the depth global variable
  #
  get_property(DEPTH GLOBAL PROPERTY DEPTH )
  math(EXPR DEPTH "${DEPTH}+1" )
  set_property(GLOBAL PROPERTY DEPTH ${DEPTH} )
  #
  # See if this package has already been called.
  # If it has, the variable ${package}DEPTH will have been set
  #
  get_property(check GLOBAL PROPERTY ${package}DEPTH  SET)
  #
  #
  #
  set(DELTA 0)
  if ( NOT ${check} )
    #
    # Must be the first time for this package
    #
    ND280_debug("${package}DEPTH not defined, setting it to ${DEPTH}")
    set_property(GLOBAL PROPERTY ${package}DEPTH ${DEPTH} )
  else()
    #
    # package seen before so change the depth value to how deep we are now, if we are deeper than last
    # time it was seen
    #
    get_property(${package}DEPTH GLOBAL PROPERTY   ${package}DEPTH )
    if(DEPTH GREATER ${${package}DEPTH} )
      set_property(GLOBAL PROPERTY ${package}DEPTH ${DEPTH} )
      math(EXPR DELTA "${DEPTH} - ${${package}DEPTH}")
    endif()
  endif()
  get_property(${package}DEPTH GLOBAL PROPERTY   ${package}DEPTH )
  ND280_debug("  GLOBAL PROPERTY  ${package}DEPTH currently set  to: ${${package}DEPTH} ")
  #
  # Create the list of argument which will be passed to find_project
  #
  set(REQUESTED_VERSION "NONE")
  set(FIND_ARGUMENTS ${package})
  if(${ARGC} GREATER 1 AND NOT ${ARGV1} STREQUAL "*")
    #
    # Check that if a version has been requested it is not different to a version we have already found
    #
    ND280_CHECK_VERSION(result ${package} ${ARGV1} )
    if( NOT ${result} )
      message(FATAL_ERROR " requested version ${version} of ${package} does not match version already loaded ")
    endif()
    #
    # If a version is specified then we require it to be found exactly
    if(${ARGC} EQUAL 2)
      set(REQUESTED_VERSION ${ARGV1})
      ND280_CMTLIKE(${ARGV0} ${REQUESTED_VERSION} )
      IF(${ND280_COMPATIBILITY_MODE})
        ND280_debug(" there are 2 arguments, second ${REQUESTED_VERSION} must be version ")
        ND280_debug(" ND280_COMPATIBILITY_MODE option has been chosen  so require a compatible version to be found")
        set(FIND_ARGUMENTS ${package}  ${REQUESTED_VERSION} REQUIRED CONFIG)
      else()
        ND280_debug(" there are 2 arguments, second ${REQUESTED_VERSION} must be version, so require it to be found exactly ")
        set(FIND_ARGUMENTS ${package}  ${REQUESTED_VERSION} EXACT REQUIRED CONFIG)
      endif()
      set(VERSION_SPECIFIED "TRUE")
    else()
      ND280_debug(" No  version specified ")
      set(FIND_ARGUMENTS ${ARGV})
    endif()
  else()
    ND280_CMTLIKE(${ARGV0})
  endif()
  #
  # If the requested package is already in the ND280_PROJECTS list
  # do no more, but move it to here in the list
  #
  #  get the list of all projects
  #
  get_property(ND280_PROJECTS GLOBAL PROPERTY ND280_PROJECTS)
  if ( DELTA GREATER 0 )
    #
    # We are deeper than before by an ammount DELTA
    #
    # Make all packages except this one deeper by an ammount DELTA
    #
    foreach( p ${ND280_PROJECTS})
      ND280_STRIP_PACKAGE(packageAlreadyProcessed ${p})
      if(NOT ${packageAlreadyProcessed} STREQUAL ${package})
        get_property(oldDepth GLOBAL PROPERTY ${packageAlreadyProcessed}DEPTH )
        math(EXPR NewDepth "${oldDepth} + ${DELTA}")
        set_property(GLOBAL PROPERTY ${packageAlreadyProcessed}DEPTH ${NewDepth})
      endif()
    endforeach()
  endif()
  #
  #
  # Loop through  ND280_PROJECTS looking for this package
  # When its found remove it and put it at the end.
  # Normally return, unless additonal configuration has been requested.
  #
  foreach( p ${ND280_PROJECTS})
    ND280_STRIP_PACKAGE(packageAlreadyProcessed ${p})
    if( packageAlreadyProcessed STREQUAL package)
      list(REMOVE_ITEM ND280_PROJECTS ${package})
      list(APPEND ND280_PROJECTS ${package})
      #   if we find a package that requests additional configuration in we must call it wherever it appears
      #   so we do not return at this point
      if(ARG_CONFIGURE_ADD)
        ND280_debug("ND280_USE: As CONFIGURE_ADD option has been passed, we will repeat the find_package steps")
        break()
      endif()
      math(EXPR DEPTH "${DEPTH}-1" )
      set_property(GLOBAL PROPERTY DEPTH ${DEPTH} )
      ND280_debug("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
      math(EXPR INDENT "${INDENT}-2" )
      set_property(GLOBAL PROPERTY INDENT ${INDENT} )
      return()
    endif()
  endforeach()
  #
  #
  # Set option that says in the case of multiple matching packages, find the highest one
  #
  SET(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
  SET(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
  #
  # store in the cache the location of where the package binarie etc. are stored
  #
  set(${package}CONFIG ${ND280_SYSTEM} CACHE PATH "${package}CONFIG build location" FORCE )
  set(${package}CONFIG ${ND280_SYSTEM})
  cmake_policy(SET CMP0074 NEW)
  ND280_debug("find_package(${FIND_ARGUMENTS})")
  ND280_DEBUG(" ${package}CONFIG SET TO ${${package}CONFIG}")
  #
  # THIS IS THE IMPORTANT PART!>>>>
  #
  ND280_debug(" Searching in $ENV{CMAKE_PREFIX_PATH} for ${FIND_ARGUMENTS}")
  find_package(${FIND_ARGUMENTS} NO_SYSTEM_ENVIRONMENT_PATH )
  ND280_debug(" Version for ${package} found by find_package is  ${${package}_VERSION}")
  set_property(GLOBAL PROPERTY ${package}_VERSION_MAJOR  ${${package}_VERSION_MAJOR})
  ND280_debug(" Remember  that ${package}_VERSION_MAJOR is ${${package}_VERSION_MAJOR} ")
  ND280_debug(" CONFIG  for ${package} found by find_package is  ${${package}_CONFIG}")
  #
  # now look for a file next to the CONFIG file with additional default options
  # if it exists, include it then rerun find_project with the additional arguments
  # e.g.
  # set(ROOTND280_EXTRACONFIG  EXACT REQUIRED COMPONENTS RIO Net Geom EG XMLIO XMLParser Minuit Gui TMVA Hist Spectrum RooFit )
  #
  # We have to do it this way (i.e. twice) as the first find_package call gives us the location of the configuration file
  # Defining it within the package ensures all users of a given package get the same configuration.
  #
  #message("get_filename_component(pathname ${${package}_CONFIG} DIRECTORY)")
  get_filename_component(pathname ${${package}_CONFIG} DIRECTORY)
  ND280_debug(" pathname to config file is ${pathname} ")
  # I wrote this but now I don't understand it
  # In what circumstances is ${ND280_SYSTEM} part of ${${package}_CONFIG} ?
  # Alex Finch
  string(REPLACE ${ND280_SYSTEM}/ "" cmakeDirectory ${pathname})
  ND280_debug(" pathname to cmake directory is ${cmakeDirectory}")
  set (ND280_EXTRACONFIGFILE ${cmakeDirectory}/${package}ND280_EXTRACONFIG.cmake)
  ND280_debug(" search for ${ND280_EXTRACONFIGFILE}")
  if(EXISTS ${ND280_EXTRACONFIGFILE})
    ND280_debug("${ND280_EXTRACONFIGFILE} exists, so include it ")
    include(${ND280_EXTRACONFIGFILE})
    set_property(GLOBAL PROPERTY ${package}ND280_EXTRACONFIG ${${package}ND280_EXTRACONFIG})
  endif()
  if(ARG_CONFIGURE)
    ND280_debug(" Overriding configuration with values ${ARG_CONFIGURE} passed as argument to nd280_use")
    set(${package}ND280_EXTRACONFIG ${ARG_CONFIGURE})
    set_property(GLOBAL PROPERTY ${package}ND280_EXTRACONFIG ${${package}ND280_EXTRACONFIG})
  endif()
  if(ARG_CONFIGURE_ADD)
    ND280_debug(" Updating configuration with additional values <${ARG_CONFIGURE_ADD}> passed as argument to nd280_use")
    get_property(${package}ND280_EXTRACONFIG GLOBAL PROPERTY ${package}ND280_EXTRACONFIG)
    set(${package}ND280_EXTRACONFIG  ${${package}ND280_EXTRACONFIG} ${ARG_CONFIGURE_ADD})
  endif()
  #ND280_debug(" ${package}ND280_EXTRACONFIG is defined as ${${package}ND280_EXTRACONFIG}")
  if(DEFINED ${package}ND280_EXTRACONFIG)
    set(FIND_ARGUMENTS ${package}  ${${package}_VERSION} ${${package}ND280_EXTRACONFIG})
    ND280_debug(" second call to find_package ${package} with arguments ${FIND_ARGUMENTS}")
    find_package(${FIND_ARGUMENTS})
    set_property(GLOBAL PROPERTY ${package}ND280_EXTRACONFIG ${${package}ND280_EXTRACONFIG})
  endif()
  #
  # set ${package}ROOT to the correct location of the package found
  # This is emulating CMT's naming scheme and is required later.
  #
  #  get_filename_component(pathname ${${package}_CONFIG} DIRECTORY)
  get_filename_component(${package}_CONFIG_DIR "${${package}_CONFIG}" DIRECTORY)
  nd280_debug(" ${package}_CONFIG_DIR =  ${${package}_CONFIG} extracted from ${${package}_CONFIG}")
  # if( ${package} STREQUAL Geant4 )
  #  get_filename_component(${package}ROOT "${${package}_CONFIG_DIR}/../.." ABSOLUTE)
  #  ND280_DEBUG(" (Geant4 special) SETTING ${package}ROOT  to ${${package}ROOT}  FROM ${${package}_CONFIG_DIR}/../..")
  #  set(${package}ROOT ${${package}ROOT} CACHE PATH "${package}ROOT for CMT compatability" FORCE )
  # else()
  ND280_DEBUG(" SETTING ${package}ROOT  to ${${package}ROOT}  FROM ${${package}_CONFIG_DIR}/..")
  get_filename_component(${package}ROOT "${${package}_CONFIG_DIR}/.." ABSOLUTE)
  #  if( ${package} STREQUAL "Geant4" )
  #     get_filename_component(${package}ROOT "${${package}_CONFIG_DIR}/../.." ABSOLUTE)
  #  endif()
  # One subtlety with root 6 is that thisroot.sh prepends to CMAKE_PREFIX_PATH
  # This means that cmake finds the root config file directly, not via our placeholder file.
  # This in turn means that ROOTROOT gets changed from what we were expecting.
  # Its value depends on whether the user has run ../bin/setup.sh before issuing make
  #  but after deleting the cache!
  # IF she has then there is an additional ${ND280_SYSTEM} appended to ROOTROOT
  #
  # However, this should also be defeated by patching thisroot.sh in ROOT 6!
  #
  if( ${package} STREQUAL "ROOT" )
    ND280_DEBUG(" Change ROOTROOT to workaround thisroot.sh interference in ROOT 6")
    string(REGEX REPLACE  "${ND280_SYSTEM}$" "" ROOTROOT ${ROOTROOT} )
    ND280_DEBUG(" ROOTROOT now set to ${ROOTROOT}")
  endif()
  set(${package}ROOT ${${package}ROOT} CACHE PATH "${package}ROOT for CMT compatability" FORCE )
  #
  #
  # Now perform a consistency check.
  # Normally the version of the packet occurs in the directory name and matches the git tag
  #
  SANITY_CHECK_VERSION(${package} ${${package}_CONFIG_DIR} ${${package}_VERSION} ${REQUESTED_VERSION})
  set(VERSION ${package}_VERSION)
  get_property(ND280_PROJECTS GLOBAL PROPERTY ND280_PROJECTS)
  #
  # if project is not already in ND280_PROJECTS, add it
  #
  set(packageAlreadyProcessed )
  foreach( p ${ND280_PROJECTS})
    ND280_STRIP_PACKAGE(previous ${p})
    if( ${previous} STREQUAL ${package} )
      set(packageAlreadyProcessed True)
      break()
    endif()
  endforeach()
  if(NOT packageAlreadyProcessed)
    ND280_debug(" adding to ND280_PROJECTS ${package}_${package}_VERSION  (${package}_${${package}_VERSION}) ")
    SET(${package}_VERSION ${package}_${${package}_VERSION} PARENT_SCOPE)
    set_property(GLOBAL  APPEND PROPERTY ND280_PROJECTS ${package}_${${package}_VERSION} )
  endif()
  get_property(ND280_PROJECTS GLOBAL PROPERTY ND280_PROJECTS)
  #
  # Look for additional postprocessing command to run after find_package
  # For use with external packages which create their own configuration files
  #
  # message(" looking for post process file in  ${pathname}/${package}ND280_PostProcess.cmake")
  set (ND280_POSTPROCESS ${pathname}/${package}ND280_PostProcess.cmake)
  if(EXISTS ${ND280_POSTPROCESS})
    include(${ND280_POSTPROCESS})
  endif()
  #
  # add the  inc directory, and any subdirectores to the list of include directories
  #
  # ND280_DEBUG(" checking ${package}_INCLUDE_DIRS_NOTFORROOTCINT - it is ${${package}_INCLUDE_DIRS_NOTFORROOTCINT}")
  # if(DEFINED ${package}_INCLUDE_DIRS_NOTFORROOTCINT)
  #   ND280_DEBUG(" the include directories ${package}_INCLUDE_DIRS are not to be used in rootcint ")
  # else()
  if(DEFINED ${package}_INCLUDE_DIRS )
    if( NOT "${${package}_INCLUDE_DIRS}" STREQUAL "" )

      ND280_DEBUG(" as ${package}_INCLUDE_DIRS exists , add it to the list of directories to search for include files ")
        string(SUBSTRING  "${${package}_INCLUDE_DIRS}" 0 2 firstTwoChars)
        if( firstTwoChars STREQUAL "-I" )
          string(SUBSTRING  ${${package}_INCLUDE_DIRS} 2 -1 ${package}_INCLUDE_DIRS)
        endif()
      ND280_DEBUG(" it is |${${package}_INCLUDE_DIRS}|")
      
      include_directories( ${${package}_INCLUDE_DIRS} )
    endif()
  else()
    ND280_DEBUG(" as ${package}_INCLUDE_DIRS does not exist look for standard include files in ${${package}ROOT} /inc and /include ")
    foreach(INCDIR ${${package}ROOT}/inc ${${package}ROOT}/include)
      file(GLOB RESULT ${INCDIR})
      list(LENGTH RESULT RES_LEN)
      if(NOT RES_LEN EQUAL 0)
        ND280_DEBUG(" add to include_directories: ${INCDIR}")
        include_directories(${INCDIR})
        file(GLOB_RECURSE directories LIST_DIRECTORIES true ${INCDIR}/* )
        foreach(child ${directories})
          if(IS_DIRECTORY ${child} )
            if(NOT ${child} MATCHES ".*/CVS*" AND NOT ${child} MATCHES ".*/.svn*")
              ND280_DEBUG(" add to include_directories: ${child}")
              include_directories( ${child})
            endif()
          endif()
        endforeach(child)
      endif()
    endforeach(INCDIR)
  endif()
  #ND280_ListIncludeDirectories()
  add_definitions(-DND280_${package}_INCLUDED="${${package}_VERSION}")
  ND280_DEBUG(" ND280_USE: calling ND280_ADD_LIBRARY(${package})")
  ND280_ADD_LIBRARY(${package})
  ND280_DEBUG(" ND280_USE: setting  ${package}_CMAKE_DIR equal to  ${package}ROOT (${${package}ROOT})  in the cache")
  set(${package}_CMAKE_DIR ${${package}ROOT} CACHE STRING "${PACKAGE} CMAKE DIRECTORY" FORCE)

  ND280_debug("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
  math(EXPR INDENT "${INDENT}-2" )
  set_property(GLOBAL PROPERTY INDENT ${INDENT} )
  math(EXPR DEPTH "${DEPTH}-1" )
  set_property(GLOBAL PROPERTY DEPTH ${DEPTH}  )

endfunction(ND280_USE)
# CMAKE_DOCUMENTATION_START function SANITY_CHECK_VERSION()
##
## <B> SANITY_CHECK_VERSION(package directory version requested_version ) </B>
##
## \\param package    The package to check
## \\param directory  The directory containing the configuration files.
## \\param version    The project version number as used by cmake.
## \\param requested_version    The project version number requested .
## \\brief Check cmake, git versions and compare to directory name. Warn of inconsistency.
## CMAKE_DOCUMENTATION_END
function(SANITY_CHECK_VERSION package directory version requested_version)
  ND280_debug(" perform sanity check on ${directory} ${version} ${requested_version} ")
  #
  # (1) Compare CMAKE version requested and actually used.
  #      These can be different in COMPATABILITY mode
  #
  if( NOT ${requested_version} STREQUAL "NONE")
    if( NOT ${version} VERSION_EQUAL ${requested_version} )
      if( NOT DEFINED ${ND280_CMT_LIKE} )
        message("\n WARNING: The version  of ${package} being used (${version}) is not the same as the one requested (${requested_version})  \n")
      endif()
    endif()
  endif()
  #
  # (2) Look at version number in the directory and compare it to the version number
  #
  get_filename_component(a_dir ${directory} PATH)
  get_filename_component(Package_Directory_Name ${a_dir} NAME)
  string(REGEX  MATCHALL "[a-zA-Z0-9]+_[0-9]+\.[0-9]+(\.[0-9]+)*"   components ${Package_Directory_Name} )
  ND280_DEBUG("version number: ${components} ")
  ND280_DEBUG("found in package config directory: ${Package_Directory_Name}")
  if (NOT ${components})
    ND280_DEBUG("Found a version number in the directory name")
    list(GET components -1 last_item)
    string(REGEX MATCH "_[0-9]+\.[0-9]+(\.[0-9]+)*" directoryVersion ${last_item})
    string(REGEX REPLACE "_" "" directoryVersion ${directoryVersion} )
    # Remove trailing .00 and leading 0 before numbers in directory and cmake  versions before performing comparison
    # ND280_DEBUG("Remove trailing .00 and leading 0 before numbers in directory and cmake  versions before performing comparison")
    string(REGEX REPLACE "\.0([1-9])+" "\.\\1" directoryVersion ${directoryVersion} )
    string(REGEX REPLACE "\.00$" ""  directoryVersion ${directoryVersion} )
    string(REGEX REPLACE "\.0([1-9])+" "\.\\1"  version   ${version}    )
    string(REGEX REPLACE "\.00$"  ""  version   ${version}    )
    if(NOT ${version} STREQUAL ${directoryVersion} )
      message(" ")
      message(" Warning, the version of ${package}  found by CMAKE (${version}) does not match the version in the directory name (${directoryVersion}) ")
      message(" ")
    endif()
  else()
    ND280_DEBUG("No version number in directory name,  is it ${package}_master ?")
    if(${Package_Directory_Name} STREQUAL "${package}_master" )
      if(NOT DEFINED ND280_CMT_LIKE)
        message(" TAKE CARE, you appear to be using the master version of ${package}, proceed with caution")
      endif()
      # set the version to make it clear that the versions do not match
      #  set(VERSION "master" PARENT_SCOPE)
      ND280_DEBUG("Package version: ${VERSION} ")
    else()
      message(" Warning, the directory name ${Package_Directory_Name} is not of the form <package>_<version> or <package>_master. This could indicate something is wrong.")
    endif()
  endif(NOT ${components})
  #
  # (3) Compare the git version to the cmake version
  #
  git_describe(${directory}   GITVERSION --tags)
  #
  # Remove trailing .00 and leading 0 before numbers in git version and cmake  version before performing comparison
  #
  string(REGEX REPLACE "\.0([1-9])+" "\.\\1"  version   ${version}    )
  string(REGEX REPLACE "\.00$"  ""  version   ${version}    )
  string(REGEX REPLACE "\.0([1-9])+" "\.\\1" GITVERSION ${GITVERSION} )
  string(REGEX REPLACE "\.00$" ""            GITVERSION ${GITVERSION} )
  #
  #
  if(NOT ${GITVERSION} STREQUAL ${version} )
    IF(NOT DEFINED ND280_CMT_LIKE)
      message(" Warning, the version of ${package}  found by CMAKE (${version}) does not match the GIT tag   (${GITVERSION}) ")
    ENDIF()
  endif()
  #
  # (4) check if the code has been modified locally
  #
  git_local_changes(${directory} status)
  if(status STREQUAL "DIRTY")
    message(" Warning, the source of ${package} has been modified. ")
  endif()
  #
  # Set the version number to match the git version tag. This is what appears in the summary at the end
  # saying "use package version location level"
  #
  set(VERSION ${GITVERSION} PARENT_SCOPE)
endfunction(SANITY_CHECK_VERSION)
## CMAKE_DOCUMENTATION_START function ND280_MESSAGE()
##
## <B> ND280_message(message) </B>
##
## \\param message The message to be written.
## \\brief Write a message indented by the current value of INDENT
## CMAKE_DOCUMENTATION_END
function(ND280_message message)
  set(index 0)
  while(index LESS INDENT)
    MATH(EXPR index "${index}+1")
    #string(CONCAT message " " "${message}")
    set(message " ${message}")
  endwhile(index LESS INDENT)
  message("${message}")
endfunction(ND280_message)
## CMAKE_DOCUMENTATION_START function ND280_ADD_LIBRARY()
##
## <B> ND280_ADD_LIBRARY( package ) </B>
##
## \\param package The name of the package.
##
## \\brief Add non standard linkage commands.
## If the package has set its own <package>_LIBRARIES variable
## add it to the EXTERNAL_LINK_COMMANDS global variable so it is included when
## linking executables.
##
## CMAKE_DOCUMENTATION_END
function(ND280_ADD_LIBRARY package)
  # check to see whether the package has set its own package_LIBRARIES variable
  # if so, add it to the EXTERNAL_LINK_COMMANDS global
  ND280_debug(" Check for existence of ${package}_LIBRARIES ")
  if(DEFINED ${package}_LIBRARIES )
    ND280_debug(" Add contents of  ${package}_LIBRARIES to external_link_commands")
    set_property(GLOBAL  APPEND PROPERTY EXTERNAL_LINK_COMMANDS ${${package}_LIBRARIES})
    ND280_debug("${package}_LIBRARIES : ")
    ND280_debug("${${package}_LIBRARIES}")
    get_property(EXTERNAL_LINK_COMMANDS GLOBAL PROPERTY EXTERNAL_LINK_COMMANDS)
    # make a global variable aka property for all external link commands
    #if(${package} STREQUAL CERNLIB)
    set_property(GLOBAL PROPERTY ${package}_LIBRARIES ${${package}_LIBRARIES})
    
    if(APPLE)
      ## [AI 03.10.2020] -- adding for apple but should be probably generalised
      ## add libraries to use when linking any targets created later: add_executable() or add_library()
      ## although target_link_libraries should be preferred, the target is not known when calling this
      ND280_debug(" APPLE Add LIBRARIES ")
      ND280_debug(" APPLE LIBRARIES: ${${package}_LIBRARIES}")
      link_libraries(${${package}_LIBRARIES})
    endif()
    
    #ND280_DEBUG(" SET SPECIAL GLOBAL PROPERTY ${package}_LIBRARIES  TO  ${${package}_LIBRARIES}")
    #  endif()
  else()
    # otherwise add the /lib  directory to the list of  directories containing shared object libraries to link to
    #machineDependentOutput(OutputDirectory)
    ##  [AI 03.10.2020] -- not sure is needed since we later set the exact paths 
    link_directories(${${package}ROOT}/${ND280_SYSTEM}/lib)
    
    # and add the shared object library for later use, provided it has not already been added
    # or it has declared that it will not create one
    #
    get_property(${package}_NOLIBRARY GLOBAL PROPERTY ${package}_NOLIBRARY)
    if(DEFINED ${package}_NOLIBRARY)
      ND280_debug(" The package ${package} has declared that it will not create a library ")
    else()
      if(NOT TARGET ${package})
        
        add_library(${package} SHARED IMPORTED)
           
       
        ## [AI 03.10.2020] -- add for apple
        if(APPLE)
          
          set_property(TARGET ${package} PROPERTY IMPORTED_LOCATION "${${package}ROOT}/${ND280_SYSTEM}/lib/lib${package}.dylib")
           
          find_library(${package}_LIBRARY ${package} HINTS ${${package}ROOT}/${ND280_SYSTEM}/lib)
          
          if (${package}_LIBRARY)
            ND280_debug(" APPLE Add LIBRARIES ")
            ND280_debug(" APPLE LIBRARIES: ${${package}_LIBRARY}")
            link_libraries(${${package}_LIBRARY})
          endif()
            
        else()
          set_property(TARGET ${package} PROPERTY IMPORTED_LOCATION "${${package}ROOT}/${ND280_SYSTEM}/lib/lib${package}.so") 
        endif()
        
        
        # ADD_DEPENDENCIES (${package} timestamp)
      endif()
    endif()
  endif()
endfunction(ND280_ADD_LIBRARY)
## CMAKE_DOCUMENTATION_START function ND280_NO_LIBRARY()
## \\brief Sets the flag which indicates that this project does not create a library.
##
## <B> ND280_NO_LIBRARY( package ) </B>
##
## \\param package The name of the package
## CMAKE_DOCUMENTATION_END
function(ND280_NO_LIBRARY package)
  set_property(GLOBAL PROPERTY ${package}_NOLIBRARY "TRUE")
endfunction(ND280_NO_LIBRARY)
## CMAKE_DOCUMENTATION_START function ND280_NO_CONFIG()
## \\brief Sets the flag that inidicates that this package does not store its generated output in a directory
##  named for the machine type and compiler version.
##
## <B> ND280_NO_CONFIG( package ) </B>
##
##
## \\param package The name of the package
## CMAKE_DOCUMENTATION_END
function(ND280_NO_CONFIG package)
  set_property(GLOBAL PROPERTY ${package}_NOCONFIG "TRUE")
endfunction(ND280_NO_CONFIG)
## CMAKE_DOCUMENTATION_START function ND280_CMTLIKE()
##
## <B> ND280_CMTLIKE() </B>
##
## \\brief Ensure the output from cmake looks as close as possible to that
##   from CMT.
##
## If the variable ND280_CMT_LIKE has the value YES the output is
## produced to mimic that produced by cmt.
##
## cmake -DND280_CMT_LIKE=YEs
##
## CMAKE_DOCUMENTATION_END
function(ND280_CMTLIKE p )
  if( ${ND280_CMT_LIKE} MATCHES "YES" )
    set(index 4)
    set(m "# ")
    while(index LESS INDENT)
      MATH(EXPR index "${index}+1")
      set(m  "${m} ")
    endwhile(index LESS INDENT)
    set(v "*")
    if(${ARGC} GREATER 1)
      set(v ${ARGV1})
    endif()
    message("${m}use ${p} ${v}")
  endif()
endfunction(ND280_CMTLIKE)
## CMAKE_DOCUMENTATION_START function ND280_DEBUG()
##
## <B> ND280_DEBUG() </B>
##
## \\brief Output debug information.
##
## Debug information is output provided the variable ND280_DEBUG_MODE has the value DEBUG.
## To see debug information when running cmake, issue the command
##
## cmake -DND280_DEBUG_MODE=DEBUG
##
## CMAKE_DOCUMENTATION_END
function(ND280_debug m)
  IF(${ND280_DEBUG_MODE} MATCHES "DEBUG")
    set(index 0)
    set(m "DEBUG: ${m}")
    while(index LESS INDENT)
      MATH(EXPR index "${index}+1")
      #string(CONCAT message " " "${message}")
      set(m  " ${m}")
    endwhile(index LESS INDENT)
    message("${m}")
  endif()
endfunction(ND280_debug)
## CMAKE_DOCUMENTATION_START macro setup_package_version_variables()
## \\brief Extract major, minor, patch and tweak numbers from the variable <package>_VERSION.
##
## <B> (macro) setup_package_version_variables (packageName) </B>
##
## \\param packageName The name of the package.
##
## Looks for a variable called \${\${packageName}_VERSION} and creates variables
## \${_packageName}_VERSION_MAJOR \${_packageName}_VERSION_MINOR \${_packageName}_VERSION_PATCH \${_packageName}_VERSION_TWEAK
## from it with the correct numbers.
## CMAKE_DOCUMENTATION_END
macro (setup_package_version_variables _packageName)
  if (DEFINED ${_packageName}_VERSION)
    string (REGEX MATCHALL "[0-9]+" _versionComponents "${${_packageName}_VERSION}")
    list (LENGTH _versionComponents _len)
    if (${_len} GREATER 0)
      list(GET _versionComponents 0 ${_packageName}_VERSION_MAJOR)
    endif()
    if (${_len} GREATER 1)
      list(GET _versionComponents 1 ${_packageName}_VERSION_MINOR)
    endif()
    if (${_len} GREATER 2)
      list(GET _versionComponents 2 ${_packageName}_VERSION_PATCH)
    else()
      set(${_packageName}_VERSION_PATCH 0)
    endif()
    if (${_len} GREATER 3)
      list(GET _versionComponents 3 ${_packageName}_VERSION_TWEAK)
    else()
      set(${_packageName}_VERSION_TWEAK 0)
    endif()
    set (${_packageName}_VERSION_COUNT ${_len})
  else()
    set (${_packageName}_VERSION_COUNT 0)
    set (${_packageName}_VERSION "")
  endif()
endmacro()
## CMAKE_DOCUMENTATION_START function ND280_PROJECT()
## \\brief Define a new ND280 Project.
##
## <b> ND280_PROJECT(  project VERSION [NOVERSION]) </b>
##
## \\param project Name of the project
## \\param version Version number of the project
## \\param [NOVERSION] Do not create the special code for storing the version number in the library.
##
##
## Sets things up to create a new project. Defines C++11 standard to use. Prepares the special code
## which stores the version number in the library, unless instructed not to. Create the "test" target.
## CMAKE_DOCUMENTATION_END
function(ND280_PROJECT project VERSION)
  cmake_parse_arguments(ND280_PROJECT "NOVERSION" "" "" ${ARGN})
  #
  # A few sanity checks first...
  #
  # Call machineDependentOutput to set the cache variable ND280_SYSTEM. This specifies the directory
  # in which the software will be built.
  #
  machineDependentOutput(OutputDirectory)
 

  get_filename_component(name ${CMAKE_CURRENT_BINARY_DIR} NAME)
  if( NOT ${name} STREQUAL ${ND280_SYSTEM})
    message(FATAL_ERROR " Please build this project in the ${ND280_SYSTEM} directory, we are in ${name} ")
  endif()
  #
  # make sure we have the necessary subdirectories in place
  #
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/inc )
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin )
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib )
  
  #
  # initialise the global property ND280_PROJECTS which tracks all the different packages we link to
  #
  set_property(GLOBAL PROPERTY  ND280_PROJECTS "" )
  get_property(ND280_PROJECTS GLOBAL PROPERTY ND280_PROJECTS)
  set_property(GLOBAL PROPERTY INDENT 1 )
  set_property(GLOBAL PROPERTY DEPTH 1)
  set_property(GLOBAL PROPERTY  ${project}DEPTH  1 )
  ND280_DEBUG(" GLOBAL PROPERTY DEPTH SET TO 1")
  ND280_DEBUG(" GLOBAL PROPERTY ${project}DEPTH SET TO 1")
  #
  # Globally define the C++  version, and insist it is used, and disallow extensions
  #
  set(CMAKE_CXX_STANDARD 11 PARENT_SCOPE )
  set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE )
  set(CMAKE_CXX_EXTENSIONS OFF PARENT_SCOPE)
  

  # initialise the collection of link commands , mainly from external projects, which need to be included
  # when linking exectuables
  #
  set_property(GLOBAL PROPERTY  EXTERNAL_LINK_COMMANDS "" )
  get_property(EXTERNAL_LINK_COMMANDS GLOBAL PROPERTY EXTERNAL_LINK_COMMANDS)
  if(NOT DEFINED ND280_CMT_LIKE )
    message("\n ND280_PROJECT ${project} version ${VERSION} . \n ")
    IF(${ND280_COMPATIBILITY_MODE})
      message("\n WARNING: Running in COMPATIBILITY_MODE. \n Packages are accepted with compatible version numbers, not exact matches \n")
    endif()
  endif()
  #
  # Occasionally need to call project command before call to nd280_project,
  #  so avoid doing it twice
  #
  if( NOT DEFINED PROJECT_DEFINED)
    ND280_DEBUG(" project(${project}  VERSION ${VERSION})")
    project(${project}  VERSION ${VERSION})
    set(PROJECT_NAME ${PROJECT_NAME} PARENT_SCOPE)
  endif()
  get_filename_component(path ${CMAKE_CURRENT_BINARY_DIR} PATH)
  SANITY_CHECK_VERSION(${PROJECT_NAME} "${path}/cmake" ${VERSION} "NONE")
  set(${PROJECT_NAME}_VERSION ${VERSION}  PARENT_SCOPE)
  #
  # Prepare version.hxx version.cxx etc. , unless instructed not to
  #
  if(NOT ND280_PROJECT_NOVERSION)
    execute_process(COMMAND uname -n
      OUTPUT_VARIABLE PROJECT_COMPILE_HOST
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
    execute_process(COMMAND uname -a
      OUTPUT_VARIABLE PROJECT_COMPILE_UNAME
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
    set(${project}_VERSION ${VERSION})
    setup_package_version_variables(${project})
    configure_file(${ND280SOFTWAREPOLICY_VERSION_FRAGMENT}/version.h.in ${CMAKE_HOME_DIRECTORY}/../inc/${PROJECT_NAME}_version.h)
    configure_file(${ND280SOFTWAREPOLICY_VERSION_FRAGMENT}/Tpackage_version.hxx.in  ${CMAKE_HOME_DIRECTORY}/../inc/T${PROJECT_NAME}_version.hxx)
    configure_file(${ND280SOFTWAREPOLICY_VERSION_FRAGMENT}/Tpackage_version.cxx.in ${CMAKE_HOME_DIRECTORY}/../src/T${PROJECT_NAME}_version.cxx)
    configure_file(${ND280SOFTWAREPOLICY_VERSION_FRAGMENT}/Tpackage_version_LinkDef.in ${CMAKE_HOME_DIRECTORY}/../inc/T${PROJECT_NAME}_version_LinkDef.h)
    include_directories(${ND280SOFTWAREPOLICY_VERSION_FRAGMENT})
    nd280_debug(" add to include_directories : ${ND280SOFTWAREPOLICY_VERSION_FRAGMENT}")
    # execute_process(COMMAND echo "#define ${PROJECT_NAME}_COMPILE_DATE \"`date`\" " OUTPUT_FILE ../inc/${PROJECT_NAME}_make_date.hxx)
  endif()
  #
  #
  get_filename_component(${PROJECT_NAME}_CMAKE_DIR ${CMAKE_CURRENT_LIST_FILE}/../.. ABSOLUTE)
  set(${PROJECT_NAME}_CMAKE_DIR ${${PROJECT_NAME}_CMAKE_DIR} PARENT_SCOPE)
  #
  # set our ROOT variable for later inclusion in setup.sh
  #
  set(${PROJECT_NAME}ROOT      ${${PROJECT_NAME}_CMAKE_DIR}   CACHE PATH "${PROJECT_NAME}ROOT for CMT compatability" FORCE )
  #
  # Add files to the list to be cleaned up
  #
  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${${PROJECT_NAME}ROOT}/${ND280_SYSTEM}/inc/${PROJECT_NAME}_make_date.hxx" )
  add_custom_target(test)
  #
  # create a target that allows the cmake files to be cleaned out
  #
  add_custom_target(clean-cmake-files
    COMMAND ${CMAKE_COMMAND} -P ${ND280SOFTWAREPOLICYROOT}/modules/clean-all.cmake
    COMMENT "Removing all cmake generated files. You need to do cmake ../cmake to recreate them."
    )
  add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} -P ${ND280SOFTWAREPOLICYROOT}/modules/clean-all.cmake
    COMMENT "Completely cleaning up."
    )
endfunction(ND280_PROJECT)
## CMAKE_DOCUMENTATION_START function ND280_ListIncludeDirectories()
##
## <B> ND280_ListIncludeDirectories </B>
##
## \\brief Print out the current list of directories to be searched when looking for include files.
## Used when debugging.
## CMAKE_DOCUMENTATION_END
function(ND280_ListIncludeDirectories)
  message(" current contents of INCLUDE_DIRECTORIES")
  get_directory_property(incdirs INCLUDE_DIRECTORIES)
  foreach( d ${incdirs})
    message(${d})
  endforeach()
endfunction()
## CMAKE_DOCUMENTATION_START function ND280_ADD_SCRIPT()
##
## <B> ND280_ADD_SCRIPT(name [directory] ) </B>
##
##\\param name The name of the script to add
##\\param directory The name of the directory which contains the scripts. Defaults to bin.
##
## \\brief Create soft link to an interpreted script
##
## Add a soft link from the /bin directory which lives under the configuration directory
## to a program in the /bin directory at the top level of a package.
## This is for scripts ( Python/bash etc.)  which are not recompiled but just need to be linked to.
##
## The optional second argument allows one to specify a different location where the scripts are stored.
##
## CMAKE_DOCUMENTATION_END
function(ND280_ADD_SCRIPT name )
  set(destination "bin")
  if(${ARGC} GREATER 1)
    set(destination ${ARGV1})
  endif()
  file( MAKE_DIRECTORY ../${ND280_SYSTEM}/bin)
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND}  -E create_symlink ../../${destination}/${name} ../${ND280_SYSTEM}/bin/${name}
    OUTPUT_VARIABLE output
    ERROR_VARIABLE  output
    )
  ND280_DEBUG("${CMAKE_COMMAND}                  -E create_symlink ../../${destination}/${name} ../${ND280_SYSTEM}/bin/${name}")
  ND280_DEBUG("${output}")
endfunction(ND280_ADD_SCRIPT)
## CMAKE_DOCUMENTATION_START function ND280_CREATE_EMPTY_DEPENDENCY_FILE()
##
## <B>  ND280_CREATE_EMPTY_DEPENDENCY_FILE(PROJECT_NAME) </B>
##
## \\brief Create an empty dependency file called <PROJECT_NAME>.dependencies in the config directory.
##
## For use by EXTERNAL packages.
##
## CMAKE_DOCUMENTATION_END
function(ND280_CREATE_EMPTY_DEPENDENCY_FILE PROJECT_NAME)
  file(REMOVE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.dependencies")
  file(TOUCH "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.dependencies" )
endfunction(ND280_CREATE_EMPTY_DEPENDENCY_FILE)
## CMAKE_DOCUMENTATION_START function ND280_ADD_TO_DEPENDENCY_FILE()
##
## <B>  ND280_ADD_TO_DEPENDENCY_FILE(PROJECT_NAME DEPENDENT DEPENDENT_ROOT) </B>
##
## \\brief Append to the dependency file the ROOT directory of a package on which this one depends
##
## For use by EXTERNAL packages which don't use ND280_PROJECT.
## CMAKE_DOCUMENTATION_END
function(ND280_ADD_TO_DEPENDENCY_FILE PROJECT_NAME  DEPENDENT_ROOT )
 file(APPEND "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.dependencies" "${DEPENDENT_ROOT}/${ND280_SYSTEM}\n")
endfunction(ND280_ADD_TO_DEPENDENCY_FILE)
## CMAKE_DOCUMENTATION_START function ND280_END_PROJECT()
##
## <B>  ND280_END_PROJECT() </B>
##
## \\brief Create all the scripts required to build this package and all its subordinates.
##
##Once we have finished creating the project, we know all the projects which this one calls,
## so we can generate scripts etc. which need this information.
##
## We create cmakeAll.sh, makeAll.sh, setup.sh and the doxygen generation rule.
## We also fill the .dependencies file.
##
## CMAKE_DOCUMENTATION_END
function(ND280_END_PROJECT)
  CMAKE_PARSE_ARGUMENTS(ND280_END_PROJECT "NOCONFIG" "" "" ${ARGN} )
  if(NOT DEFINED ND280_CMT_LIKE)
    message(" ND280_END_PROJECT for ${PROJECT_NAME} version ${${PROJECT_NAME}_VERSION} " )
    message("")
  endif()
  set_property(GLOBAL  APPEND PROPERTY ND280_PROJECTS ${PROJECT_NAME}_${${PROJECT_NAME}_VERSION} )
  get_property(ND280_PROJECTS GLOBAL PROPERTY ND280_PROJECTS)
  #
  # create the script "makeAll.sh which runs make for all subordinate packages and this one
  #
  #machineDependentOutput(OutputDirectory)
  set(build_directory ${ND280_SYSTEM})
  list(REMOVE_DUPLICATES  ND280_PROJECTS)
  file(GLOB oldFiles ../bin/Level*.sh)
  if(NOT "${oldFiles}" STREQUAL "" )
    file(REMOVE ${oldFiles})
  endif()
  file(GLOB oldFiles ../bin/Level*.sh)
  if(NOT "${oldFiles}" STREQUAL "" )
    file(REMOVE ${oldFiles})
  endif()
  set(scriptName ../${build_directory}/makeAll.sh)
  file(WRITE  ${scriptName} "#!/bin/bash \n#! This file was autogenerated by ND280_END_PROJECT \n [  -z \"$1\" ] && set -e \n ND280_NJOBS=\"\$\{ND280_NJOBS:=1\}\" \n  \n")
  file(APPEND ${scriptName} "export ND280_NJOBS=\$\{ND280_NJOBS\}\n")
  file(APPEND ${scriptName} "function shout {\n " )  
  file(APPEND ${scriptName} " echo \"+=====================================================================+\" \n")
  file(APPEND ${scriptName} " echo \"+                                                                     +\" \n")
  file(APPEND ${scriptName} " echo \"+  nd280 Build Is Incomplete, Please Check Stdout/Stderr for Errors   +\" \n")
  file(APPEND ${scriptName} " echo \"+                                                                     +\" \n")
  file(APPEND ${scriptName} " echo \"+=====================================================================+\" \n")
  file(APPEND ${scriptName} " exit 1 \n  } \n")
  file(APPEND ${scriptName} " [  \"$1\" != \"documentation\" ] && trap shout ERR \n")

  list(LENGTH ND280_PROJECTS length)
  set(index 0)
  #
  # This is a FUDGE for a few special cases!
  #
  # Because the ROOTConfig.cmake file does not use ND280_USE, MYSQL ends up on the same level as ROOT, which
  # then will not be able to find MYSQL when it compiles, so force MYSQL to be one level lower than root
  # DITTO FOR GSL
  # DITTO for GEANT->CLHEP
  get_property(isSet GLOBAL PROPERTY ROOTDEPTH SET)
  if(isSet)
    get_property(ROOTDEPTH GLOBAL PROPERTY ROOTDEPTH )
    if ( NOT ${ROOTDEPTH} STREQUAL "" )
      math(EXPR newDepth "${ROOTDEPTH}+1" )
      set_property(GLOBAL PROPERTY MYSQLDEPTH ${newDepth})
      set_property(GLOBAL PROPERTY GSLDEPTH ${newDepth})
    endif()
  endif()
  get_property(check GLOBAL PROPERTY  Geant4DEPTH SET)
  if(check)
    get_property(Geant4DEPTH GLOBAL PROPERTY Geant4DEPTH )
    math(EXPR newDepth "${Geant4DEPTH}+1" )
    set_property(GLOBAL PROPERTY CLHEPDEPTH ${newDepth})
  endif()
  #
  # sort projects into levels
  #
  set(maxlevel 0)
  #message(" ND280_PROJECTS ${ND280_PROJECTS}")
  foreach(p ${ND280_PROJECTS})
    ND280_STRIP_PACKAGE(package ${p})
    get_property(${package}DEPTH GLOBAL PROPERTY ${package}DEPTH)
    #message("package: ${package} level: ${${package}DEPTH}  ")
    if(${${package}DEPTH} GREATER maxlevel)
      set( maxlevel ${${package}DEPTH})
    endif()
  endforeach(p)
  math(EXPR  range "${maxlevel} - 1 ")
  foreach ( lup RANGE ${range} )
    math(EXPR level "${maxlevel} - ${lup}" )
    # Find every package at this level
    SET(FoundOne)
    foreach(p ${ND280_PROJECTS})
      ND280_STRIP_PACKAGE(package ${p})
      if ( ${package}DEPTH EQUAL ${level} )
        #ND280_DEBUG(" package ${package} has level ${${package}DEPTH}")
        SET(FoundOne TRUE)
        set(V0 ${${package}_CMAKE_DIR})
        string(REPLACE ${ND280_SYSTEM} "" V ${V0})
        MATH(EXPR index "${index}+1")
        set(scriptName "../${build_directory}/Level${level}make${package}.sh")
        file(WRITE ${scriptName} "#!/bin/bash \n#! This file was autogenerated by ND280_END_PROJECT \n [  -z \"$1\" ] && set -e \n ND280_NJOBS=\"\$\{ND280_NJOBS:=1\}\" \n  \n")
        file(APPEND ${scriptName} "export ND280_NJOBS=\$\{ND280_NJOBS\}\n")
        file(APPEND ${scriptName} "function shout {\n " )
        file(APPEND ${scriptName} " echo \"+=======================================+\" \n")
        file(APPEND ${scriptName} " echo \"+                                       +\" \n")
        file(APPEND ${scriptName} " echo \"   Build of package ${p} in  ${V}  FAILED   ( Level = ${level} )       \" \n")
        file(APPEND ${scriptName} " echo \"+                                       +\" \n")
        file(APPEND ${scriptName} " echo \"+=======================================+\" \n")
        file(APPEND ${scriptName} " exit 1 \n } \n")
        file(APPEND ${scriptName} " trap shout ERR \n")
        file(APPEND ${scriptName} "  echo \"\" ; echo \" Building ${p}  ( package number \" ${index} \" out of \" ${length} \" at level ${level} ) \" ; echo \"\" \n ")
        file(APPEND ${scriptName} "  makeTarget=$1 \n ")
        file(APPEND ${scriptName} " if [ \"$1\" == \"documentation\" ] ; then makeTarget=${package}_\$1 ; fi \n ")
        file(APPEND ${scriptName} "  cd  ${V} \n")
        file(APPEND ${scriptName} " SYS_DIR=`nd280-system` \n  [ -d \$\{SYS_DIR\} ] || mkdir \$\{SYS_DIR\} \n  cd  \$\{SYS_DIR\} \n ")
        file(APPEND ${scriptName} " [ -d inc ] || mkdir inc \n ")
        file(APPEND ${scriptName} " [ -d bin ] || mkdir bin \n ")
        file(APPEND ${scriptName} " [ -d lib ] || mkdir lib \n ")
        file(APPEND ${scriptName} " cmake ../cmake $2 \n [ -f ../bin/setup.sh ] && . ../bin/setup.sh \n")
        if(${package} STREQUAL CLHEP )
          file(APPEND ${scriptName} " make \$\{makeTarget\} ;\n")
        else()
          file(APPEND ${scriptName} "  make -j \$\{ND280_NJOBS\}  \$\{makeTarget\} ;\n")
        endif()
        file(COPY ${scriptName}  DESTINATION ../bin FILE_PERMISSIONS OWNER_READ  OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE )
      endif()
    endforeach(p)
    # if at least one package existed at this level...
    if(FoundOne)
      file(APPEND ../${build_directory}/makeAll.sh "echo \"============================================\"\n")
      file(APPEND ../${build_directory}/makeAll.sh "echo \"                                            \"\n") 
      file(APPEND ../${build_directory}/makeAll.sh "echo \"                                            \"\n") 
      file(APPEND ../${build_directory}/makeAll.sh "echo \"                                            \"\n") 
      file(APPEND ../${build_directory}/makeAll.sh "echo \"        Process level ${level}              \"\n")
      file(APPEND ../${build_directory}/makeAll.sh "echo \"                                            \"\n") 
      file(APPEND ../${build_directory}/makeAll.sh "echo \"                                            \"\n") 
      file(APPEND ../${build_directory}/makeAll.sh "echo \"                                            \"\n") 
      file(APPEND ../${build_directory}/makeAll.sh "echo \"                                            \"\n")
      file(APPEND ../${build_directory}/makeAll.sh "echo \"============================================\"\n")
      file(APPEND ../${build_directory}/makeAll.sh "find ../bin -name \"Level${level}make*.sh\" -print0 | xargs -0 -I NAME -P \$\{ND280_NJOBS\} /bin/bash NAME \"$1\"  \"$2\" \n")
    endif()
  endforeach(lup)
  file(APPEND ../${build_directory}/makeAll.sh " echo \"\"\n echo \" All packages built succesfully. \" \n echo \"\"\n ")
  file(COPY ../${build_directory}/makeAll.sh DESTINATION ../bin FILE_PERMISSIONS OWNER_READ  OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE )
  file(GLOB oldFiles ../${build_directory}/Level*.sh)
  file(REMOVE ${oldFiles})
  file(REMOVE ../${build_directory}/makeAll.sh)
  #
  #
  #---Generate doxygen documentation
  # first we can indicate the documentation build as an option and set it to ON by default
  #
  option(BUILD_DOC "Build documentation" ON)
  # check if Doxygen is installed, if it is generate the rules to build it
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
    get_property(${PROJECT_NAME}_NODOCUMENTATION  GLOBAL PROPERTY ${PROJECT_NAME}_NODOCUMENTATION)
    if(DEFINED ${PROJECT_NAME}_NODOCUMENTATION)
      ND280_debug(" The package ${PROJECT_NAME} has declared that default documentation should not be built.")
    else()
      set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
      set(DOXYGEN_PROJECT_NUMBER ${${PROJECT_NAME}_VERSION} )
      set(DOXYGEN_HTML_OUTPUT ../dox)
      set(DOXYGEN_LATEX_OUTPUT ../dox)
      set(DOXYGEN_QUIET YES)
      set(DOXYGEN_INLINE_INHERITED_MEMB YES)
      set(DOXYGEN_FULL_PATH_NAMES NO)
      set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
      set(DOXYGEN_EXTRACT_ALL YES)
      set(DOXYGEN_EXTRACT_PRIVATE YES)
      set(DOXYGEN_EXTRACT_STATIC  NO)
      set(DOXYGEN_HIDE_UNDOC_MEMBERS YES)
      set(DOXYGEN_INTERNAL_DOCS     YES)
      set(DOXYGEN_INLINE_INFO     NO)
      set(DOXYGEN_SORT_BRIEF_DOCS YES)
      set(DOXYGEN_SORT_BY_SCOPE_NAME YES)
      set(DOXYGEN_SORT_MEMBERS_CTORS_1ST YES)
      set(DOXYGEN_FILE_PATTERNS *.dox *.cxx *.hxx *.cc *.hh *.h *.py *.F *.H)
      set(DOXYGEN_RECURSIVE YES)
      set(DOXYGEN_EXCLUDE_PATTERNS *~ */.* tut* test* orig.* purge.* *Dict.cxx *Dict.h *LinkDef.h )
      set(DOXYGEN_EXAMPLE_PATH ../ )
      set(DOXYGEN_EXAMPLE_RECURSIVE    YES)
      set(DOXYGEN_SOURCE_BROWSER YES)
      set(DOXYGEN_IMAGE_PATH ../doc)
      set(DOXYGEN_INLINE_SOURCES NO)
      set(DOXYGEN_STRIP_CODE_COMMENTS NO)
      set(DOXYGEN_ALPHABETICAL_INDEX   YES)
      set(DOXYGEN_COLS_IN_ALPHA_INDEX    2)
      set(DOXYGEN_REFERENCED_BY_RELATION YES)
      set(DOXYGEN_REFERENCES_RELATION     YES)
      set(DOXYGEN_IGNORE_PREFIX          T E )
      set(DOXYGEN_HTML_HEADER          ${nd280SoftwarePolicyROOT}/doxygen/header.html)
      set(DOXYGEN_HTML_FOOTER          ../doc/footer.html)
      set(DOXYGEN_HTML_EXTRA_STYLESHEET ${nd280SoftwarePolicyROOT}/doxygen/doxygenND280_extra.css)
      set(DOXYGEN_HTML_DYNAMIC_SECTIONS YES)
      set(DOXYGEN_PAPER_TYPE a4wide)
      set(DOXYGEN_MACRO_EXPANSION NO)
      set(DOXYGEN_INCLUDE_FILE_PATTERNS *.h *.hxx *.hh )
      set(DOXYGEN_PREDEFINED "ClassDef(N,V) = ClassDef(N,V); /**< ROOT macro: See Rtypes.h*/")
      set(DOXYGEN_EXPAND_AS_DEFINED OA_EXCEPTION )
      set(DOXYGEN_EXTERNAL_GROUPS YES)
      set(DOXYGEN_QT_AUTOBRIEF YES)
      set(DOXYGEN_EXCLUDE_SYMLINKS YES)
      set(DOXYGEN_TOC_EXPAND YES)
      set(DOXYGEN_GENERATE_TREEVIEW YES)
      set(DOXYGEN_USE_MATHJAX YES)
      set(DOXYGEN_GENERATE_LATEX NO)
      set(DOXYGEN_HIDE_UNDOC_RELATIONS NO)
      set(DOXYGEN_HAVE_DOT YES)
      set(DOXYGEN_IMAGE_FORMAT svg)
      set(DOXYGEN_INTERACTIVE_SVG YES)
      set(DOXYGEN_GRAPH_MAX_NODES 1000)
      set(DOXYGEN_DOT_TRANSPARENT YES)
      set(DOXYGEN_DOT_MULTI_TARGETS YES)
      set(DOXYGEN_DOT_GRAPH_MAX_NODES  100)
      set(DOXYGEN_UML_LOOK YES)
      set(DOXYGEN_UML_LIMIT_NUM_FIELDS  50)
      set(DOXYGEN_PROJECT_LOGO ${nd280SoftwarePolicyROOT}/doxygen/logo.jpg)
      set(DOXYGEN_LAYOUT_FILE ${nd280SoftwarePolicyROOT}/doxygen/DoxygenLayout.xml)
      SET(DOXYGEN_EXPAND_AS_DEFINED OA_EXCEPTION)
      #SET(DOXYGEN_ALIASES "footnote{1}=""\\latexonly\\footnote\{1\}\\endlatexonly\\htmlonly<sup title=\1\>*</sup>\\endhtmlonly""  ")
      SET(DOXYGEN_DOCSET_BUNDLE_ID     "org.t2k" )
      SET(DOXYGEN_DOCSET_FEEDNAME       "Doxygen generated ND280 docs")
      SET(DOXYGEN_EXTRACT_STATIC         YES)
      SET(DOXYGEN_HIDE_UNDOC_MEMBERS     NO)
      SET(DOXYGEN_TEMPLATE_RELATIONS      YES)
      SET(DOXYGEN_JAVADOC_AUTOBRIEF YES)
      #  set(DOXYGEN_ALIASES footnote{1}=\"\latexonly\footnote\{\1\}\endlatexonly\htmlonly<sup title=\\"\1\\">*</sup>\endhtmlonly\")
      # set(DOXYGEN_WARNINGS NO)
      set(DOXYGEN_TAGFILES)
      foreach(p ${ND280_PROJECTS})
        ND280_STRIP_PACKAGE(package ${p})
        if ( NOT ${package} STREQUAL ${PROJECT_NAME} )
          ND280_STRIP_VERSION(version ${p})
          set(DOXYGEN_TAGFILES ${DOXYGEN_TAGFILES} ../../${p}/dox/${package}_${version}.tag=../../${p}/dox)
        endif()
      endforeach()
      set(DOXYGEN_GENERATE_TAGFILE ../dox/${PROJECT_NAME}_${${PROJECT_NAME}_VERSION}.tag)
      IF(DEFINED ENV{ND280_ADDITIONAL_DOXYGEN})
        INCLUDE($ENV{ND280_ADDITIONAL_DOXYGEN})
    ENDIF()
    #message("nd280SoftwarePolicyROOT = ${nd280SoftwarePolicyROOT}")
    configure_file(${nd280SoftwarePolicyROOT}/doxygen/footer.html.frag1 ../doc/footer.html)
    file(READ ${nd280SoftwarePolicyROOT}/doxygen/footer.html.frag2 content)
    file(APPEND  ../doc/footer.html ${content})
    doxygen_add_docs(documentation
      ../doc ../src ../inc
      )
      doxygen_add_docs(${PROJECT_NAME}_documentation
      ../doc ../src ../inc
      )
  ENDIF()
  else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
  #
  #
  # create the script "cmakeAll.sh which runs cmake for all subordinate packages and this one
  #
  file(WRITE ../${build_directory}/cmakeAll.sh "#!/bin/bash \n set -e \n")
  file(APPEND ../${build_directory}/cmakeAll.sh "ND280_SYSTEM=`nd280-system` \n")
  file(APPEND ../${build_directory}/cmakeAll.sh "export ND280_NJOBS=\$\{ND280_NJOBS:=1\}\n" )


  foreach(p ${ND280_PROJECTS})
     ND280_STRIP_PACKAGE(package ${p})
     set(V ${${package}_CMAKE_DIR})
#    file(APPEND ../${build_directory}/cmakeAll.sh "  if [ -f ${V}/cmake/CMakeLists.txt ] ; then\n  cd  ${V}/${build_directory} ; rm  CMakeCache.txt || true ;cmake ../cmake ;\n fi \n")
     file(APPEND ../${build_directory}/cmakeAll.sh "  if [ -f ${V}/cmake/CMakeLists.txt ] ; then\n  echo \" cd  ${V}/\$\{ND280_SYSTEM\}/ ;cmake ../cmake ; \" >../bin/cmakePackage${package}.sh \n  fi \n  ")

  endforeach()
  file(APPEND ../${build_directory}/cmakeAll.sh "find ../bin -name 'cmakePackage*.sh' -print0 | xargs -0 -I NAME -P \$\{ND280_NJOBS\} /bin/bash NAME \"$1\" \"$2\"  \n")
  file(COPY ../${build_directory}/cmakeAll.sh DESTINATION ../bin FILE_PERMISSIONS OWNER_READ  OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE )
  file(REMOVE ../${build_directory}/cmakeAll.sh)
  #
  # create a setup script which sets up:
  #
  # Environment variables...
  # PATH
  # LD_LIBRARY_PATH
  # <package_name>ROOT
  #
  # and runs any package specific setup scripts found in /setup_script
  #
  #machineDependentOutput(OutputDirectory)
  file(WRITE ../${build_directory}/setup.sh "# Setup the PATH and LD_LIBRARY_PATH environment variables \n# and run all setup scripts\n")
  string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_IN_UPPERCASE)
  file(APPEND ../${build_directory}/setup.sh "HERE=`pwd` \n")
  file(APPEND ../${build_directory}/setup.sh "export ND280_SYSTEM=`nd280-system` \n")
  file(APPEND ../${build_directory}/setup.sh "unset -f path_remove \n")
  file(APPEND ../${build_directory}/setup.sh "unset -f path_append \n")
  file(APPEND ../${build_directory}/setup.sh "unset -f ld_remove \n")
  file(APPEND ../${build_directory}/setup.sh "unset -f ld_append \n")
  file(APPEND ../${build_directory}/setup.sh "path_remove ()  { export PATH=`echo -n $PATH | awk -v RS=: -v ORS=: '$0 != \"'$1'\"' | sed 's/:$//'`; } \n")
  file(APPEND ../${build_directory}/setup.sh "path_append ()  { path_remove $1; export PATH=\"$PATH:$1\" ;} \n")
  file(APPEND ../${build_directory}/setup.sh  "ld_remove ()  { export LD_LIBRARY_PATH=`echo -n $LD_LIBRARY_PATH | awk -v RS=: -v ORS=: '$0 != \"'$1'\"' | sed 's/:$//'`; } \n")
  file(APPEND ../${build_directory}/setup.sh "ld_append ()  { ld_remove $1; export LD_LIBRARY_PATH=\"$LD_LIBRARY_PATH:$1\" ;} \n")
  if(ND280_END_PROJECT_NOCONFIG)
    ND280_debug(" The package ${PROJECT_NAME} has declared that it does not have a CONFIG directory")
    file(APPEND ../${build_directory}/setup.sh "path_append ${${PROJECT_NAME}_CMAKE_DIR}/bin \n")
  else()
    file(APPEND ../${build_directory}/setup.sh "path_append ${${PROJECT_NAME}_CMAKE_DIR}/$\{ND280_SYSTEM\}/bin \n")
  endif()
  file(APPEND ../${build_directory}/setup.sh "ld_append ${${PROJECT_NAME}_CMAKE_DIR}/\$\{ND280_SYSTEM\}/lib \n")
  file(REMOVE "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.dependencies")
  file(APPEND ../${build_directory}/setup.sh "export ND280SOFTWAREPOLICYROOT=${ND280SOFTWAREPOLICYROOT} \n")

  foreach(p ${ND280_PROJECTS})
    ND280_STRIP_PACKAGE(package ${p})
    ND280_STRIP_VERSION(version ${p})
    if(DEFINED ND280_CMT_LIKE)
      ND280_message("use  ${package} ${version}   (${${package}_CMAKE_DIR})" )
    else()
      ND280_message("use  ${package} ${version}   (${${package}_CMAKE_DIR}) (Level: ${${package}DEPTH} )" )
    endif()
    # Add name of all packages this one depends on to the file ${PROJECT_NAME}.dependencies
    if ( NOT ${package} STREQUAL ${PROJECT_NAME})
     file(APPEND "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.dependencies"
       "${${package}_CMAKE_DIR}/${ND280_SYSTEM}\n" )
    endif()
    get_property(${package}_NOCONFIG GLOBAL PROPERTY ${package}_NOCONFIG)
    if(DEFINED ${package}_NOCONFIG)
      ND280_debug(" The package ${package} has declared that it does not have a CONFIG directory")
      file(APPEND ../${build_directory}/setup.sh "path_append ${${package}_CMAKE_DIR}/bin \n")
    else()
      file(APPEND ../${build_directory}/setup.sh "path_append ${${package}_CMAKE_DIR}/\$\{ND280_SYSTEM\}/bin \n")
    endif()


    file(APPEND ../${build_directory}/setup.sh "ld_append ${${package}_CMAKE_DIR}/$\{ND280_SYSTEM\}/lib \n")
    string(TOUPPER ${package} PACKAGE_NAME_IN_UPPERCASE)
    file(APPEND ../${build_directory}/setup.sh "export ${PACKAGE_NAME_IN_UPPERCASE}ROOT=${${package}ROOT} \n")
    file(APPEND ../${build_directory}/setup.sh "export ${PACKAGE_NAME_IN_UPPERCASE}CONFIG=\$\{ND280_SYSTEM\}  \n")
# run the local setup script of any subordinate packages
    if(EXISTS ${${package}_CMAKE_DIR}/setup_script/ )
      file(APPEND ../${build_directory}/setup.sh "for file in ${${package}_CMAKE_DIR}/setup_script/*.sh ; do [ -f $file ] && . $file ; done\n")
    endif()
  endforeach()
  file(APPEND ../${build_directory}/setup.sh "export LD_LIBRARY_PATH=`echo $LD_LIBRARY_PATH | sed 's/^://g'`\n")
  
  if (APPLE)
    file(APPEND ../${build_directory}/setup.sh "export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH \n")
  endif()
    
  file(APPEND ../${build_directory}/setup.sh "cd $HERE \n")
  file(REMOVE ../bin/setup.sh)
  file(COPY ../${build_directory}/setup.sh DESTINATION ../bin FILE_PERMISSIONS OWNER_READ  OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE )
  
  unset(ND280_SYSTEM  CACHE )
  unset(ND280_DEBUG_MODE CACHE )
  unset(ND280_COMPATIBILITY_MODE CACHE)
  unset(ND280_CMT_LIKE CACHE)
endfunction(ND280_END_PROJECT)
## CMAKE_DOCUMENTATION_START function ND280_PATH_APPEND()
##
## <B> ND280_PATH_APPEND ( directory) </B>
##
## \\brief Add directory to the PATH environment variable in setup.sh
##
## \\param directory Name of directory to be added to PATH
##
## Add to the setup.sh script the commands to add a path to the PATH environment variable.
## CMAKE_DOCUMENTATION_END
function(ND280_PATH_APPEND directory)
  # NB normally no debug messages appear after ND280_END_PROJECT has been called
  ND280_DEBUG(" ADDING ${directory} to PATH setting in ../bin/setup.sh")
  machineDependentOutput(build_directory)
  if(EXISTS "../bin/setup.sh")
    file(APPEND ../bin/setup.sh "path_append ${${PROJECT_NAME}ROOT}/${directory} \n")
  else()
    message(FATAL_ERROR " ND280_PATH_APPEND is trying to append to ../bin/setup.sh but that file does not exist")
  endif()
endfunction(ND280_PATH_APPEND)
## CMAKE_DOCUMENTATION_START function ND280_PYTHON_PATH_APPEND()
##
## \\brief Add directory to the PYTHON_PATH environment variable in setup.sh
##
## <B> ND280_PYTHON_PATH_APPEND  directory) </B>
##
## \\param directory Name of directory to be added to PYTHON_PATH
##
## Add to the setup.sh script the commands to add a path to the PYTHON_PATH environment variable.
##
## CMAKE_DOCUMENTATION_END
function(ND280_PYTHON_PATH_APPEND  directory)
  machineDependentOutput(build_directory)
  # NB normally  no debug messages appear after ND280_END_PROJECT has been called
  ND280_DEBUG(" ADDING PYTHON SETUP TO ../bin/setup.sh")
  if(EXISTS "../bin/setup.sh")
    file(APPEND ../bin/setup.sh "unset -f python_path_remove \n")
    file(APPEND ../bin/setup.sh "unset -f path_append \n")
    file(APPEND ../bin/setup.sh "python_path_remove ()  { export PYTHONPATH=`echo -n $PYTHONPATH | awk -v RS=: -v ORS=: '$0 != \"'$1'\"' | sed 's/:$//'`; } \n")
    file(APPEND ../bin/setup.sh "python_path_append ()  { python_path_remove $1; export PYTHONPATH=`echo $PYTHONPATH:$1  | sed s/^:// | sed s/:$// `;} \n")
    file(APPEND ../bin/setup.sh "python_path_append ${${PROJECT_NAME}ROOT}/${directory} \n")
  else()
    message(FATAL_ERROR " ND280_PYTHON_PATH_APPEND is trying to append to ../bin/setup.sh but that file does not exist")
  endif()
endfunction(ND280_PYTHON_PATH_APPEND)
## CMAKE_DOCUMENTATION_START function ND280_INSTALL()
##
## \\brief Copy application into the directory where binaries are stored.
##
## <b> ND280_INSTALL( app) </b>
##
## \\param app Name of application to be installed
##
##
## CMAKE_DOCUMENTATION_END
function(ND280_INSTALL app)
  machineDependentOutput(build_directory)
  file(COPY ${app} DESTINATION ../${build_directory}/bin/ FILE_PERMISSIONS OWNER_READ  OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE )
endfunction(ND280_INSTALL)
