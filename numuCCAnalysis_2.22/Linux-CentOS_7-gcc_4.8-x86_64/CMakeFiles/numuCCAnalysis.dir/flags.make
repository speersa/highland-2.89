# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# compile CXX with /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/nd280SoftwarePilot/scripts/c++
CXX_FLAGS = -DND280SOFTWAREPOLICY_CXXFLAGS -pipe -fPIC -pthread  -Wall -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -m64  -DND280SOFTWAREPOLICY_RELEASE -DNDEBUG -g -O2  -fPIC   -fcommon -std=c++11

CXX_DEFINES = -DND280_CMAKE_BUILD -DND280_baseAnalysis_INCLUDED=\"2.36\" -DND280_baseTrackerAnalysis_INCLUDED=\"2.26\" -DND280_highlandCore_INCLUDED=\"2.46\" -DND280_highlandCorrections_INCLUDED=\"2.33\" -DND280_highlandEventModel_INCLUDED=\"2.43\" -DND280_highlandIO_INCLUDED=\"2.53\" -DND280_highlandTools_INCLUDED=\"2.32\" -DND280_highlandUtils_INCLUDED=\"2.46\" -DND280_oaAnalysisReader_INCLUDED=\"2.29\" -DND280_psycheCore_INCLUDED=\"3.51\" -DND280_psycheEventModel_INCLUDED=\"3.47\" -DND280_psycheIO_INCLUDED=\"3.40\" -DND280_psycheND280Utils_INCLUDED=\"3.73\" -DND280_psycheROOT_INCLUDED=\"3.10\" -DND280_psycheSelections_INCLUDED=\"3.60\" -DND280_psycheSystematics_INCLUDED=\"3.62\" -DND280_psycheUtils_INCLUDED=\"3.36\" -DnumuCCAnalysis_EXPORTS

CXX_INCLUDES = -I/t2k/Software/v12r25/ROOT/v5r34p34n00/Linux-x86_64/include/root -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheCore_3.51/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheEventModel_3.47/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheUtils_3.36/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheND280Utils_3.73/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheIO_3.40/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCore_2.46/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod5D -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod5F -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6AA -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6B -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6E -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6G -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6R -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6T -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6TREx -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6X -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod6Y -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7B -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7_RC1 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7_RC2 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7_V02 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7_V06 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7_V07 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7_V09 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/oaAnalysisReader_2.29/inc/prod7_V12 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandUtils_2.46/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandUtils_2.46/inc/EventDisplay -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSelections_3.60/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/psycheSystematics_3.62/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandCorrections_2.33/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandIO_2.53/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandTools_2.32/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseAnalysis_2.36/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseAnalysis_2.36/inc/EventDisplayND280 -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/baseTrackerAnalysis_2.26/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCAnalysis_2.22/Linux-CentOS_7-gcc_4.8-x86_64/inc -I/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/numuCCAnalysis_2.22/inc 

