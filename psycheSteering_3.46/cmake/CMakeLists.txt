# CMakeLists.txt for psycheSteering package. It creates a library with dictionary and a main program

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND)
   message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(psycheSteeringPackageVersion.cmake)
ND280_PROJECT(psycheSteering ${PACKAGE_VERSION} NOVERSION)
include(psycheSteeringND280_USE.cmake)


ND280_STANDARD_LIBRARY()

ND280_EXECUTABLE(RunSyst RunSyst.cxx)
ND280_EXECUTABLE(RunSyst_New RunSyst_New.cxx)
ND280_EXECUTABLE(RunSystBinCorr RunSyst_BinCorr.cxx)
ND280_EXECUTABLE(RunExample RunExample.cxx)
ND280_EXECUTABLE(Make1SigmaVar Make1SigmaVar.cxx)
ND280_EXECUTABLE(RunPreloadExample RunPreloadExample.cxx)
ND280_EXECUTABLE(RunExpPreloadExample RunExpPreloadExample.cxx)
ND280_EXECUTABLE(MakeBANFFEventHistograms MakeBANFFEventHistograms.cxx)
ND280_EXECUTABLE(TestCorrelationMatrix TestCorrelationMatrix.cxx)

ND280_END_PROJECT()
