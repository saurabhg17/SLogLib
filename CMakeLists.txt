
cmake_minimum_required(VERSION 3.10)


project(SLogLib 
        LANGUAGES    CXX
		VERSION      1.2.0
		DESCRIPTION  "SLogLib is a c++ logging library")


# Set the directories where the output files will be generated. To make it easy all files are
# generated in the bin directory under the root of the build directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if(MSVC_IDE OR CMAKE_GENERATOR MATCHES Xcode)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif()


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Various parameters used for configuring SLogLib.
set(SLOGLIB_DEBUG_POSTFIX     d     CACHE STRING "Add a suffix for debug builds")
set(SLOGLIB_BUILD_EXAMPLES    TRUE  CACHE BOOL   "Build examples")
set(SLOGLIB_BUILD_QT_EXAMPLES FALSE CACHE BOOL   "Build examples depending on Qt")
set(SLOGLIB_BUILD_SHARED_LIBS TRUE  CACHE BOOL   "Build shared library")


if(SLOGLIB_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX ${SLOGLIB_DEBUG_POSTFIX})
endif()

if(SLOGLIB_BUILD_SHARED_LIBS)
	set(BUILD_SHARED_LIBS TRUE)
else()
	set(BUILD_SHARED_LIBS FALSE)
endif()


add_subdirectory (SLogLib)

if(SLOGLIB_BUILD_EXAMPLES)
	add_subdirectory(Examples)
endif()


