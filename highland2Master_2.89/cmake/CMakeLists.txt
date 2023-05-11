# CMakeLists.txt for highland2Master package. It creates a library with dictionary and a main program

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND)
   message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(highland2MasterPackageVersion.cmake)
ND280_PROJECT(highland2Master ${PACKAGE_VERSION} NOVERSION)
include(highland2MasterND280_USE.cmake)


ND280_NO_LIBRARY(highland2Master)


ND280_END_PROJECT()
