# CMakeLists.txt for baseAnalysis package. It creates a library with dictionary and a main program

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND)
   message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(baseAnalysisPackageVersion.cmake)
ND280_PROJECT(baseAnalysis ${PACKAGE_VERSION} NOVERSION)
include(baseAnalysisND280_USE.cmake)


ND280_STANDARD_LIBRARY()

ND280_EXECUTABLE(RunRooTrackerVtxExample RunRooTrackerVtxExample.cxx)
ND280_EXECUTABLE(EventDisplayND280 EventDisplayND280.cxx)

ND280_END_PROJECT()
