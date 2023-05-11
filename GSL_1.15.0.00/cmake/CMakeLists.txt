# CMakeLists.txt for GSL package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(ND280_NJOBS $ENV{ND280_NJOBS})
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND) 
  message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

set(PACKAGE GSL)
include(GSLPackageVersion.cmake)

set(TAG ${PACKAGE_VERSION} )

string(REPLACE _ .  VERSION ${TAG})


# GSL version does not have the final patch and `tweak' numbers
# so remove it - needed when constructing file name for tar file later
#
string(FIND ${PACKAGE_VERSION} \. dotpos REVERSE)
string(SUBSTRING ${PACKAGE_VERSION} 0 ${dotpos} NOTWEAK)
string(FIND ${NOTWEAK} \. dotpos REVERSE)
string(SUBSTRING ${NOTWEAK} 0 ${dotpos} SHORTTAG)

message("PACKAGE_VERSION = ${PACKAGE_VERSION} ")
message("SHORTTAG = ${SHORTTAG}")
string(REPLACE _ .  VERSION ${TAG})
machineDependentOutput(OutputDirectory)

set(TOPLEVEL ${CMAKE_CURRENT_SOURCE_DIR}/../${OutputDirectory}/ )

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

message("PROCESS ${PACKAGE}  VERSION : ${VERSION}")

#DOWNLOAD_COMMAND  ${TOPLEVEL}/bin/untar.sh; 

ExternalProject_Add(${PACKAGE}
PREFIX              ${TOPLEVEL} 
SOURCE_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/../src
STAMP_DIR           ${TOPLEVEL}/stamps
TMP_DIR             ${TOPLEVEL}/tmp
BINARY_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/../src
INSTALL_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/setup_script
URL                 $ENV{ND280_DOWNLOADS}/gsl-${SHORTTAG}.tar.gz
DOWNLOAD_NO_PROGRESS TRUE
CONFIGURE_COMMAND   ./configure --prefix=${TOPLEVEL}  --exec-prefix=${TOPLEVEL} 
BUILD_COMMAND       ${CMAKE_CURRENT_SOURCE_DIR}/../bin/make.sh
INSTALL_COMMAND     make install
)


