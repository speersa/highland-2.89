# CMakeLists.txt for externalsMaster package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

find_package(nd280SoftwarePolicy 3.2)
if( NOT nd280SoftwarePolicy_FOUND) 
  message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(externalsMasterPackageVersion.cmake)
ND280_PROJECT(externalsMaster ${PACKAGE_VERSION})
include(externalsMasterND280_USE.cmake)


ND280_END_PROJECT()

