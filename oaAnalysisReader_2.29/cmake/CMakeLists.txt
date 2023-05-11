# CMakeLists.txt for oaAnalysisReader package. It creates a library with dictionary and a main program

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
find_package(nd280SoftwarePolicy 3.1)
if( NOT nd280SoftwarePolicy_FOUND)
   message(FATAL_ERROR " nd280SoftwarePolicy not found - abort ")
endif()

include(oaAnalysisReaderPackageVersion.cmake)
ND280_PROJECT(oaAnalysisReader ${PACKAGE_VERSION} NOVERSION)
include(oaAnalysisReaderND280_USE.cmake)


# The list below shows the correspondence between a given production,
# the oaAnalysis version used for that production
# and the oaAnalysisReader subfolder to be used
# (to be set below in the PRODUCTIONDIR variable)
#
# productions                           oa/eventAnalysis  oaAnalysisReader
#--------------------------------------------------------------------------
# 5D                                    v5r11                prod5D   
# 5E                                    v5r15p1               
# 5F, 5G                                v5r15p3              prod5F
# 
# -----
# 6B-6D, 6J                             v5r29p19             prod6B 
# 6E, 6K, 6M                            v5r29p21             prod6E
# 6F, 6G, 6L, 6N, 6O, 6P, 6Q, 6S        v5r29p25             prod6G
# 6H-6I                                 v5r31p9  (TREX)      prod6TREx 
# 6R                                    v5r29p29             prod6R  
# 6T, 6U, 6V                            v5r29p31             prod6T  
# 6W, 6X                                v5r29p33             prod6X
# 6Y, 6Z                                v5r29p35             prod6Y
# 6AA                                   v5r29p37             prod6AA
# -----                                 v6r1     (P7 RC1)    prod7_RC1
# 7A, 7B (v12r15)                       v6r3                 prod7_RC2
# 7B (v12r19)                           v6r7                 prod7B
# 7_V(1, 2, 3)                          6.14                 prod7_V02
# 7_V06                                 6.17                 prod7_V06
# 7_V07                                 7.2                  prod7_V07
# 7_V09                                 7.3                  prod7_V09
# 7_V12                                 7.4                  prod7_V12

# the production to be used
set(PRODUCTIONDIR prod7_V12)


# Create all proper make and setup scripts
ND280_END_PROJECT()

machineDependentOutput(OutputDirectory)

file(MAKE_DIRECTORY   ${${PROJECT_NAME}_CMAKE_DIR}/${ND280_SYSTEM}/lib)


add_custom_target(RunOaAnalysisReaderBuild ALL
  COMMAND . ${${PROJECT_NAME}_CMAKE_DIR}/src/${PRODUCTIONDIR}/compile_reader
  DEPENDS ${${PROJECT_NAME}_CMAKE_DIR}/bin/setup.sh
  COMMENT " Build oaAnalysisReader in ${PRODUCTIONDIR} ")


