
# Top level CMakeLists.txt for SLogLib.
# The name of our project is "SLogLib". CMakeLists files in this 
# project can refer to the root source directory of the project 
# as ${CMAKE_SOURCE_DIR} and to the root binary directory of the 
# project as ${CMAKE_BINARY_DIR}.
project("SLogLib")

# Minimal version of CMake required:
cmake_minimum_required(VERSION 2.8.11)

# The version of SLogLib is defined as Major.Minor.BugFix
# The rules for deciding the version are:
#    If the binary interface of the library do not change from the previous release as in the case
#      of bugfixes, increase SLOGLIB_VERSION_BUGFIX.
#    If the binary interface is changed, but remains compatible with the previous release then 
#      increase SLOGLIB_VERSION_MINOR and set SLOGLIB_VERSION_BUGFIX to 0.
#    If the binary interface is changed in an incompatible way to the previous release, then 
#      increase the SLOGLIB_VERSION_MAJOR, and set the two other numbers to 0.
set(SLOGLIB_VERSION_MAJOR 1)
set(SLOGLIB_VERSION_MINOR 0)
set(SLOGLIB_VERSION_BUGFIX 0)

# SO verions are used in linux.
set(SLOGLIB_VERSION   ${SLOGLIB_VERSION_MAJOR}.${SLOGLIB_VERSION_MINOR})
set(SLOGLIB_SOVERSION ${SLOGLIB_VERSION_MAJOR})

# Set the directories where the output files will be generated. To make it easy all files are
# generated in the bin directory under the root of the build directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SlogLib uses relative path to the include the header files and so does all the examples.
# Hence, we define the include directory as the root of the source directory where SLogLib directory
# resides with all the source and header files.
include_directories(${CMAKE_SOURCE_DIR})

# Various parameters used for configuring.
set(SLOGLIB_DEBUG_POSTFIX     d     CACHE STRING "Add a suffix for debug builds")
set(SLOGLIB_BUILD_EXAMPLES    TRUE  CACHE BOOL   "Build examples")
set(SLOGLIB_BUILD_QT_EXAMPLES FALSE CACHE BOOL   "Build examples depending on Qt")
set(SLOGLIB_USE_QT_VERSION "Qt5" CACHE STRING "Qt version chosen by the user at CMake configure time")
set_property(CACHE SLOGLIB_USE_QT_VERSION PROPERTY STRINGS Qt5 Qt4)

# Don't use CMake defined suffix; otherwise CMake adds an extra suffix at the end.
set(CMAKE_DEBUG_POSTFIX)

#set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install)

# First build the SLogLib and then all examples.
add_subdirectory (SLogLib)

if(SLOGLIB_BUILD_EXAMPLES)
	add_subdirectory(Examples)
endif()