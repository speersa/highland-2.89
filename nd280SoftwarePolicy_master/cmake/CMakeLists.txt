cmake_minimum_required(VERSION 3.8)
include(../modules/make_documentation.cmake)
find_package(Doxygen)
  if (DOXYGEN_FOUND)
   include(nd280SoftwarePolicyPackageVersion.cmake)

   set(DOXYGEN_PROJECT_NAME nd280SoftwarePolicy)
   set(DOXYGEN_PROJECT_NUMBER "${PACKAGE_VERSION}" )
   set(DOXYGEN_HTML_OUTPUT ../dox)
   set(DOXYGEN_LATEX_OUTPUT ../dox)
   set(DOXYGEN_QUIET YES)
   set(DOXYGEN_INLINE_INHERITED_MEMB YES)
   set(DOXYGEN_FULL_PATH_NAMES NO)
   set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
   set(DOXYGEN_EXTRACT_ALL YES)
   set(DOXYGEN_EXTRACT_PRIVATE YES)
   set(DOXYGEN_EXTRACT_STATIC  NO)
   set(DOXYGEN_HIDE_UNDOC_MEMBERS YES)
   set(DOXYGEN_INTERNAL_DOCS     YES)
   set(DOXYGEN_INLINE_INFO     NO)
   set(DOXYGEN_SORT_BRIEF_DOCS YES)
   set(DOXYGEN_SORT_BY_SCOPE_NAME YES)
   set(DOXYGEN_SORT_MEMBERS_CTORS_1ST YES)
   set(DOXYGEN_FILE_PATTERNS *.cmake *.dox)
   set(DOXYGEN_EXTENSION_MAPPING  cmake=C++)
   set(DOXYGEN_SOURCE_BROWSER NO)
   set(DOXYGEN_IMAGE_PATH ../doc)
   set(DOXYGEN_STRIP_CODE_COMMENTS NO)
   set(DOXGHEN_IGNORE_PREFIX ND280)
   set(DOXYGEN_ALPHABETICAL_INDEX   YES)
   set(DOXYGEN_COLS_IN_ALPHA_INDEX    2)
   set(DOXYGEN_REFERENCED_BY_RELATION YES)
   set(DOXYGEN_REFERENCES_RELATION     YES)
   set(DOXYGEN_HTML_HEADER            ../doxygen/header.html)
   set(DOXYGEN_HTML_FOOTER          ../doc/footer.html)
   set(DOXYGEN_HTML_EXTRA_STYLESHEET ../doxygen/doxygenND280_extra.css)
   set(DOXYGEN_HTML_DYNAMIC_SECTIONS YES)
   set(DOXYGEN_PAPER_TYPE a4)
   set(DOXYGEN_MACRO_EXPANSION NO)
   set(DOXYGEN_EXTERNAL_GROUPS YES)
   set(DOXYGEN_QT_AUTOBRIEF YES)
   set(DOXYGEN_EXCLUDE_SYMLINKS YES)
   set(DOXYGEN_TOC_EXPAND YES)
   set(DOXYGEN_GENERATE_TREEVIEW YES)
   set(DOXYGEN_USE_MATHJAX YES)
   set(DOXYGEN_GENERATE_LATEX NO)
   set(DOXYGEN_HIDE_UNDOC_RELATIONS NO)
   set(DOXYGEN_HAVE_DOT YES)
   set(DOXYGEN_IMAGE_FORMAT svg)
   set(DOXYGEN_INTERACTIVE_SVG YES)
   set(DOXYGEN_GRAPH_MAX_NODES 1000)
   set(DOXYGEN_DOT_TRANSPARENT YES)
   set(DOXYGEN_DOT_MULTI_TARGETS YES)
   set(DOXYGEN_PROJECT_LOGO ../doxygen/logo.jpg)
   set(DOXYGEN_LAYOUT_FILE   ../doxygen/DoxygenLayout.xml)
 
  
  #message("nd280SoftwarePolicyROOT = ${nd280SoftwarePolicyROOT}")
   set(PROJECT_NAME "nd280SoftwarePolicy")
   set(nd280SoftwarePolicy_VERSION ${PACKAGE_VERSION})
   configure_file(../doxygen/footer.html.frag1 ../doc/footer.html)
   file(READ ../doxygen/footer.html.frag2 content)
   file(APPEND  ../doc/footer.html ${content})
   doxygen_add_docs(nd280SoftwarePolicy_documentation
      ../doc  )
   message(" To build the documentation do \n \n make nd280SoftwarePolicy_documentation \n ")
   
  else (DOXYGEN_FOUND)
   message("Doxygen needs to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)