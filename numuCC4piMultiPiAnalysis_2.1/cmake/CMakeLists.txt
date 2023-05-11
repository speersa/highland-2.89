# CMakeLists.txt for numuCC4piMultiPiAnalysis package. It creates a library with dictionary and a main program

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND)
   message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(numuCC4piMultiPiAnalysisPackageVersion.cmake)
ND280_PROJECT(numuCC4piMultiPiAnalysis ${PACKAGE_VERSION} NOVERSION)
include(numuCC4piMultiPiAnalysisND280_USE.cmake)


ND280_STANDARD_LIBRARY()

ND280_EXECUTABLE(RunNumuCC4piMultiPiAnalysis RunNumuCC4piMultiPiAnalysis.cxx)

ND280_END_PROJECT()
