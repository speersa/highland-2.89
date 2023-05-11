# CMakeLists.txt for highlandValidation package. It creates a library with dictionary and a main program

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND)
   message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(highlandValidationPackageVersion.cmake)
ND280_PROJECT(highlandValidation ${PACKAGE_VERSION} NOVERSION)
include(highlandValidationND280_USE.cmake)


ND280_NO_LIBRARY(highlandValidation)


ND280_END_PROJECT()
