# CMakeLists.txt for MYSQL
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND) 
  message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

set(externalName MYSQL)

include(${externalName}PackageVersion.cmake)

string(TOLOWER ${externalName} lowerName)
set(TAG ${PACKAGE_VERSION})
# MYSQL version does not have the final `tweak' number
# so remove it - needed when constructing file name for tar file later
#
string(FIND ${PACKAGE_VERSION} \. dotpos REVERSE)
string(SUBSTRING ${PACKAGE_VERSION} 0 ${dotpos} MYSQLVERSION)
string(REPLACE _ .  VERSION ${TAG})
machineDependentOutput(OutputDirectory)

set(TOPLEVEL ${CMAKE_CURRENT_SOURCE_DIR}/../${OutputDirectory}/)
set(MYSQL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../src/${lowerName}-${MYSQLVERSION})

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(TAR_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../tar/${lowerName}-${MYSQLVERSION}.tar.gz)
set(PATCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../tar/${lowerName}-${MYSQLVERSION}.patch)
#DOWNLOAD_COMMAND tar -C ${MYSQL_SRC}/.. -xzf ${TAR_FILE}

message(" ${externalName} VERSION : ${VERSION}")
ExternalProject_Add(${externalName}
PREFIX      ${TOPLEVEL}
INSTALL_DIR ${TOPLEVEL}
SOURCE_DIR  ${MYSQL_SRC}
STAMP_DIR   ${TOPLEVEL}/stamps
TMP_DIR     ${TOPLEVEL}/tmp
BINARY_DIR  ${TOPLEVEL}/tmp_build
URL         $ENV{ND280_DOWNLOADS}/${lowerName}-${MYSQLVERSION}.tar.gz
PATCH_COMMAND cd ${MYSQL_SRC} && patch -N -p1 < ${PATCH_FILE} && true
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${TOPLEVEL} -DWITH_UNIT_TESTS=OFF -DINSTALL_SQLBENCHDIR=
BUILD_COMMAND "" 
INSTALL_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../bin/make.sh ${MYSQL_SRC}
)
##
