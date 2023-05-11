# clean-all.cmake

set(cmake_generated ${CMAKE_BINARY_DIR}/CMakeCache.txt
	${CMAKE_BINARY_DIR}/cmake_install.cmake
	${CMAKE_BINARY_DIR}/Makefile
	${CMAKE_BINARY_DIR}/CMakeFiles
	)

foreach(file ${cmake_generated})
	if (EXISTS ${file})
		message(" removing ${file} ")
		file(REMOVE_RECURSE ${file})
	endif()
endforeach(file)

file(GLOB nd280_files ../bin/Level*.sh ../bin/makeAll.sh ../bin/cmakeAll.sh setup.sh  ${CMAKE_BINARY_DIR}/*.dependencies)

foreach(file ${nd280_files})
	if (EXISTS ${file})
		message(" removing ${file}")
		file(REMOVE ${file})
	endif()
endforeach()


