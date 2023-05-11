# CMakeLists.txt for MYSQL
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(ND280_NJOBS $ENV{ND280_NJOBS})
find_package(nd280SoftwarePolicy 3.1)
if(NOT nd280SoftwarePolicy_FOUND)
  message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

set(externalName ROOT)
include(ROOTPackageVersion.cmake)
#
# ROOT version does not have the final `tweak' number so remove it - needed when
# constructing file name for tar file later
#
string(FIND ${PACKAGE_VERSION} \. dotpos REVERSE)
string(SUBSTRING ${PACKAGE_VERSION}
                 0
                 ${dotpos}
                 ROOTVERSION)
#
# find mysql root...
#
include(ROOTND280_USE.cmake)
if("${MYSQLROOT}" STREQUAL "")
  message(
    FATAL_ERROR " ROOT CONFIGURATION FAILED TO FIND MYSQL, CAN NOT CONTINUE ")
endif()
#
# find GSL root...
#
if("${GSLROOT}" STREQUAL "")
  message(
    FATAL_ERROR " ROOT CONFIGURATION FAILED TO FIND GSL, CAN NOT CONTINUE ")
endif()

string(TOLOWER ${externalName} lowerName)

machinedependentoutput(OutputDirectory)
# message(" OutputDirectory = ${OutputDirectory}") message(" ND280_SYSTEM =
# ${ND280_SYSTEM} ")
set(TOPLEVEL ${CMAKE_CURRENT_SOURCE_DIR}/../${OutputDirectory}/)
message("PROCESS ${externalName} VERSION : ${PACKAGE_VERSION}")
message("Top level for build process is ${TOPLEVEL}")
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
#
# Allow user to override ROOT setting fail-on-missing which we default to ON
#
set(ROOT_FAIL_ON_MISSING_ARG ON)
if( DEFINED ROOT_FAIL_ON_MISSING)
 if(NOT ROOT_FAIL_ON_MISSING)
  set(ROOT_FAIL_ON_MISSING_ARG OFF)
 endif()
endif()
if("${ROOT_FAIL_ON_MISSING_ARG}" STREQUAL "ON")
  message("")
  message(" ROOT build will fail if any required packages are missing.")
  message(" This is the recommended default behaviour, however if you wish to")
  message(
    " override this, add the option -DROOT_FAIL_ON_MISSING=False to the cmake command "
    )
  message("")
endif()
if("${ROOT_FAIL_ON_MISSING_ARG}" STREQUAL "OFF")
  message("")
  message(
    " ROOT build will carry on, even if any required packages are missing.")
  message(" Later builds may fail however.")
  message("")
endif()
unset(ROOT_FAIL_ON_MISSING CACHE)
#
# This clever little thing does all the rest!
#
ExternalProject_Add(
  root
  INSTALL_DIR ${TOPLEVEL}
  URL $ENV{ND280_DOWNLOADS}/${lowerName}_v${ROOTVERSION}.source.tar.gz
  PATCH_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../src/root && patch -f -p2 < ../../tar/${lowerName}_v${ROOTVERSION}.patch
  STAMP_DIR ${TOPLEVEL}/stamps
  TMP_DIR ${TOPLEVEL}/tmp
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/root
  BINARY_DIR ${TOPLEVEL}/tmp_build
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${TOPLEVEL}
    -DMYSQL_DIR=${MYSQLROOT}/${OutputDirectory}
    -DMYSQL_CONFIG_EXECUTABLE=${MYSQLROOT}/${OutputDirectory}/bin/mysql_config
    -DGSL_DIR=${GSLROOT}/${OutputDirectory}
    -DGSL_CONFIG_EXECUTABLE=${GSLROOT}/${OutputDirectory}/bin/gsl-config
    -Dfail-on-missing=${ROOT_FAIL_ON_MISSING_ARG}
    -Droofit=ON
    -Dmysql=ON
    -Dbonjour=OFF
    -Dcastor=OFF
    -Drfio=OFF
    -Doracle=OFF
    -Dodbc=OFF
    -Dpgsql=OFF
    -Dsqlite=OFF
    -Dpythia6=OFF
    -Dpythia8=OFF
    -Dfftw3=OFF
    -Dgfal=OFF
    -Dbuiltin_xrootd=ON
    -Ddcache=OFF
    -Dldap=OFF
    -Dgviz=OFF
    -Dminuit2=ON
    BUILD_COMMAND make -j${ND280_NJOBS}
    # INSTALL_COMMAND make install
  )
ExternalProject_Add_Step(root PostConfigure 
COMMAND ${CMAKE_COMMAND} -E create_symlink ${TOPLEVEL} ${TOPLEVEL}/root 
)
#COMMAND cd ${TOPLEVEL} ; rm root ; ln -sf . root
#)
# OR!
#ADD_CUSTOM_TARGET( addlink   COMMAND ${CMAKE_COMMAND} -E create_symlink ${TOPLEVEL} ${TOPLEVEL}/root DEPENDS root)
# ExternalProject_Add_Step(root PostConfigure COMMAND
# ${CMAKE_CURRENT_SOURCE_DIR}/../bin/edit_ROOTConfig.sh ${TOPLEVEL}
# ${CMAKE_CURRENT_SOURCE_DIR} COMMENT        "Modify ROOTConfig.cmake to point
# to the correct location" DEPENDEES      install ) INSTALL_COMMAND cp
# ${TOPLEVEL}/cmake/ROOTConfig*.cmake ${CMAKE_CURRENT_SOURCE_DIR}/
set_property(DIRECTORY
             APPEND
             PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
                      "${TOPLEVEL}/src"
                      "${TOPLEVEL}/include"
                      ${TOPLEVEL}/aclocal
                      ${TOPLEVEL}/bin
                      ${TOPLEVEL}/cmake
                      ${TOPLEVEL}/cint
                      ${TOPLEVEL}/config
                      ${TOPLEVEL}/emacs
                      ${TOPLEVEL}/etc
                      ${TOPLEVEL}/fonts
                      ${TOPLEVEL}/geom
                      ${TOPLEVEL}/icons
                      ${TOPLEVEL}/inc
                      ${TOPLEVEL}/lib
                      ${TOPLEVEL}/install
                      ${TOPLEVEL}/LICENSE
                      ${TOPLEVEL}/macros
                      ${TOPLEVEL}/man
                      ${TOPLEVEL}/README
                      ${TOPLEVEL}/root
                      ${TOPLEVEL}/SRC
                      ${TOPLEVEL}/test
                      ${TOPLEVEL}/tmp
                      ${TOPLEVEL}/tmva
                      ${TOPLEVEL}/tutorials)
# For informaton, this is the original set of configurations settings from the
# CMT version: -Dgminimal=ON -Dasimage=ON -Dastiff=ON -Dcintex=OFF -Dcxx11=ON
# -Dgdml=ON -Dmathmore=ON -Dgsl_shared=ON -Dbuiltin_gsl=OFF -Dmysql=ON
# -Dminuit2=ON -Dopengl=ON -Dpython=ON -Dreflex=OFF -Droofit=ON -Drpath=OFF
# -Dshared=ON -Dsoversion=ON -Dsqlite=ON -Dtmva=ON -Dunuran=ON -Dx11=ON -Dxml=ON
