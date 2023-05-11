# Include the version of ROOTConfig.cmake from the build directory
get_filename_component(_currentDirectory "${CMAKE_CURRENT_LIST_FILE}" PATH)
if (EXISTS ${_currentDirectory}/../${ND280_SYSTEM}/cmake/ROOTConfig.cmake ) 
  include("${_currentDirectory}/../${ND280_SYSTEM}/cmake/ROOTConfig.cmake")
endif()
if (EXISTS ${_currentDirectory}/../cmake/ROOTND280_USE.cmake)
  include("${_currentDirectory}/../cmake/ROOTND280_USE.cmake")
endif()
