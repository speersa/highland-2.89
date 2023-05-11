# CMakeLists.txt for psycheROOT package. It creates a library with dictionary and a main program

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND)
   message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(psycheROOTPackageVersion.cmake)
ND280_PROJECT(psycheROOT ${PACKAGE_VERSION} NOVERSION)

ND280_NO_LIBRARY(psycheROOT)

ND280_END_PROJECT()
ND280_CREATE_EMPTY_DEPENDENCY_FILE("psycheROOT")
