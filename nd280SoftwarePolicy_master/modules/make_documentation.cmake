## pragma once
if(_MAKE_DOCUMENTATION_CMAKE_INCLUDED_)
  return()
endif()
set(_MAKE_DOCUMENTATION_CMAKE_INCLUDED_ true)

cmake_minimum_required(VERSION 2.8)

include(${CMAKE_ROOT}/Modules/CMakeParseArguments.cmake)

## HOW TO DOCUMENT YOUR CMAKE FILES :
## 1- Use CMAKE_DOCUMENTATION_START <name> flag to start your documentation
## 2- Document your cmake file like you want (you can use doxygen syntax)
## 3- Use CMAKE_DOCUMENTATION_END flag to finish your documentation
##
## The parser will generate a documentation section foreach filenames parsed with a section foreach macros/functions under the file parsed.
## <name> could be :
##	* a fileName : 
##		In this case, the parser will add the doxygen documentation of the filename.
##  * a simple name (function/macro) name : 
##		In this case, the parser will add a section under the filename one.
##
## Example:
##    ## <CMAKE_DOC_START_FLAG> FindMySDK.cmake
##    ##
##    ## Try to find MySDK.
##    ## Once done this will define :
##    ##  \\li MYSDK_FOUND - system has MYSDK
##    ##  \\li MYSDK_INCLUDE_DIR - the MYSDK include directory
##    ##  \\li MYSDK_LIBRARIES - The libraries provided by MYSDK
##    ##
##    ## You can use the MYSDK_DIR environment variable
##    ##
##    ## <CMAKE_DOC_END_FLAG>
##
## This file is used to generated cmake documentation
## It allow to create cmakedoc custom_target (see docs/CMakeLists.txt)~
##
## In your CMakeLists.txt, just include this file.
## Or call subsequently :
## 	PARSE_CMAKE_DOCUMENTATION()
##	WRITE_CMAKE_DOCUMENTATION( "${CMAKE_SOURCE_DIR}/cmake/cmake.dox" SORTED )
##
## Then the standard Doxygen application will be able to parse your cmake.dox documentation to be include.

## SEE THE REAL COMMAND AT THE END OF THIS FILE !

## ###########################################################################
## #####################   INTERNAL USE   ####################################
## ###########################################################################

## Parse for a list of cmake files in order to recover documentation notes.
##
## PARSE_CMAKE_DOCUMENTATION(
##      [INCLUDES   includeFilePathPattern] ## default ${CMAKE_SOURCE_DIR}/*.cmake*
##      [EXCLUDES   excludeFilePathPattern] ## default this file (avoiding conflicts)
##      [START_FLAG matchingStartFlag]		## CMAKE_DOCUMENTATION_START
##      [END_FLAG   matchingEndFlag]		## CMAKE_DOCUMENTATION_END
##)
##
MACRO(PARSE_CMAKE_DOCUMENTATION )

    ##params: "PREFIX" "optionsArgs" "oneValueArgs" "multiValueArgs"
    cmake_parse_arguments(PARSE_CMAKE_DOCUMENTATION "" "START_FLAG;END_FLAG" "INCLUDES;EXCLUDES" ${ARGN} )
    
    # INCLUDES cmake file to the list files
    if(NOT DEFINED PARSE_CMAKE_DOCUMENTATION_INCLUDES)
        set(PARSE_CMAKE_DOCUMENTATION_INCLUDES "${CMAKE_SOURCE_DIR}/*.cmake*") # all *.cmake* by default
    endif()
    set(cmake_files_list)
    foreach(includeFilePathPattern ${PARSE_CMAKE_DOCUMENTATION_INCLUDES})
        file(GLOB_RECURSE cmake_files "${includeFilePathPattern}")
        list(APPEND cmake_files_list ${cmake_files}) 
    endforeach()

    # EXCLUDES cmake file to the list files
    if(NOT DEFINED PARSE_CMAKE_DOCUMENTATION_EXCLUDES)
        set(PARSE_CMAKE_DOCUMENTATION_EXCLUDES
                "${CMAKE_SOURCE_DIR}/*make_documentation.cmake*") # mutual exclude by default
    endif()
    if( NOT  ${PARSE_CMAKE_DOCUMENTATION_EXCLUDES} STREQUAL "")
    foreach(excludeFilePathPattern ${PARSE_CMAKE_DOCUMENTATION_EXCLUDES})
        file(GLOB_RECURSE cmake_files_exclude "${excludeFilePathPattern}")
         if( NOT  ${cmake_files_exclude} STREQUAL "")
        list(REMOVE_ITEM cmake_files_list ${cmake_files_exclude})
        endif()
        #message("remove file from cmake documentation files list : ${cmake_files_exclude}")
    endforeach()
    endif()

    # default START_FLAG
    if(NOT DEFINED PARSE_CMAKE_DOCUMENTATION_START_FLAG)
        set(PARSE_CMAKE_DOCUMENTATION_START_FLAG "CMAKE_DOCUMENTATION_START")
    endif()
    
    # default END_FLAG
    if(NOT DEFINED PARSE_CMAKE_DOCUMENTATION_END_FLAG)
        set(PARSE_CMAKE_DOCUMENTATION_END_FLAG "CMAKE_DOCUMENTATION_END")
    endif()
    
    # Process for each file of the list
    foreach(cmake_file ${cmake_files_list})
        file(READ ${cmake_file} cmake_file_content)
        message(STATUS "Generate cmake doc for : ${cmake_file}")
 
        ## check pair tags for cmake doc
        string(REGEX MATCHALL "${PARSE_CMAKE_DOCUMENTATION_START_FLAG}" matches_start ${cmake_file_content})
        list(LENGTH matches_start matches_start_count)
        string(REGEX MATCHALL "${PARSE_CMAKE_DOCUMENTATION_END_FLAG}" matches_end ${cmake_file_content})
        list(LENGTH matches_end matches_end_count)
        if(NOT matches_start_count EQUAL matches_end_count)
            message("WARNING: You forgot a tag for cmake documentation generation.
                    Matches ${PARSE_CMAKE_DOCUMENTATION_START_FLAG} = ${matches_start_count}.
                    Matches ${PARSE_CMAKE_DOCUMENTATION_END_FLAG} = ${matches_end_count}.
                    The cmake file ${cmake_file} will not be parse for cmake doc generation.")
            set(cmake_file_content "") # to skip the parsing
        endif()

        ## Parse the cmake file
        string(REGEX REPLACE "\r?\n" ";" cmake_file_content "${cmake_file_content}")
        set(docSectionContent "")
        set(fileStarted false)
        foreach(line ${cmake_file_content})
            ## find the start balise
            string(REGEX MATCH "##.*${PARSE_CMAKE_DOCUMENTATION_START_FLAG}.*" matchStart ${line})            
            #
            # look for special start section for files
            #
            if( matchStart )   
             #message(${line})
            #string(REGEX MATCHALL "[a-zA-Z_\\.()]+\ |[a-zA-Z_\\.()]+$" TOKEN_LIST "${line}")
            string(REGEX MATCHALL "[^ \t\r\n]+[ \t\r\n]|[^ \t\r\n]+$" TOKEN_LIST "${line}")
             list(LENGTH TOKEN_LIST len)
             
             if( len GREATER 3 )           
              list(GET TOKEN_LIST 2 KEY )
              list(GET TOKEN_LIST 3 VALUE )
              
               if( KEY STREQUAL "file " )
                 set(DOXYFILE ${VALUE})
                 set(fileStarted true)
                 list(APPEND docSectionContent "/**")
                 list(APPEND docSectionContent " * @file ${DOXYFILE}")
                 list(APPEND docSectionContent " * ")
               endif()
               
               if( KEY STREQUAL "function ")
                 list(REMOVE_AT TOKEN_LIST 0 1 2)
                 set(functionDescription "${TOKEN_LIST}")
                 string(REGEX REPLACE ";" " " functionDescription "${functionDescription}")  
                
                 list(APPEND docSectionContent "/**")
                 set(functionStarted true)
                 #message("${docSectionContent}")
               endif()
               if( KEY STREQUAL "macro ")
                 list(REMOVE_AT TOKEN_LIST 0 1 2 )
                 set(functionDescription "${TOKEN_LIST}")
                 string(REGEX REPLACE ";" " " functionDescription "${functionDescription}")  
                 list(APPEND docSectionContent "/**")
                 set(functionStarted true)
                 #message("${docSectionContent}")
               endif()
             endif()
            endif()
            ## find the end balise
            string(REGEX MATCH "##.*${PARSE_CMAKE_DOCUMENTATION_END_FLAG}" matchEnd ${line})
            if(fileStarted OR functionStarted)
             if( matchEnd)
                list(APPEND docSectionContent " */" )
                 list(APPEND docSectionContent ${functionDescription})
                 list(APPEND docSectionContent "&SemiColon")
                string(REGEX REPLACE ";" "\n" docSectionContent "${docSectionContent}") ## to remove ; at each line 
                #message(" docSectionContent = ${docSectionContent}")
                ###########################
                process_cmake_documentation( "${cmake_file}" "${docSection}" "${docSectionContent}" )
                ###########################
                set(ligneComment "")
                set(docSectionContent "")
                set(fileStarted false)
                set(functionStarted false)
             endif()
            endif()
            
            ## Extract comment between balises, just strip off any #symbols
            string(REGEX MATCH "#.*" matchComment ${line})
            if(fileStarted OR functionStarted)
             if( matchComment AND NOT matchStart AND NOT matchEnd)
                string(REGEX REPLACE "#" "" ligneComment ${matchComment})
                list(APPEND docSectionContent " *${ligneComment}")
             endif()
            endif()

        endforeach()
        
    endforeach()
ENDMACRO()


## This macro define some global cmake variables to be used when generate the .dox file
## Internal used only
MACRO(PROCESS_CMAKE_DOCUMENTATION cmakeFile sectionName sectionContent)
      list(APPEND gPROCESS_CMAKE_DOCUMENTATION_FUNCTIONS_DESCRIPTIONS ${sectionContent}   )
ENDMACRO()


## Generate the .dox file using globale variables set by previous macro

FUNCTION(WRITE_CMAKE_DOCUMENTATION outputPathFileName )
    string(REGEX REPLACE ";" "\n" gPROCESS_CMAKE_DOCUMENTATION_FUNCTIONS_DESCRIPTIONS "${gPROCESS_CMAKE_DOCUMENTATION_FUNCTIONS_DESCRIPTIONS}")
    string(REGEX REPLACE "\n&SemiColon" ";" gPROCESS_CMAKE_DOCUMENTATION_FUNCTIONS_DESCRIPTIONS "${gPROCESS_CMAKE_DOCUMENTATION_FUNCTIONS_DESCRIPTIONS}")
    file(WRITE  "${outputPathFileName}" "${gPROCESS_CMAKE_DOCUMENTATION_FUNCTIONS_DESCRIPTIONS}")   
ENDFUNCTION()


## ###########################################################################
## #####################   WHAT WE DO   ######################################
## ###########################################################################

PARSE_CMAKE_DOCUMENTATION( INCLUDES ${CMAKE_SOURCE_DIR}/../modules/standardFunctions.cmake )
WRITE_CMAKE_DOCUMENTATION( "${CMAKE_SOURCE_DIR}/../doc/standardFunctions.cmake" )


