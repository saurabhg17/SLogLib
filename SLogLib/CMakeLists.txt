
SET(HDRS AddToCallStack.h
         CallInfo.h
         Config.h
         LoggingManager.h
         Message.h
         SLogLib.h
         SysUtils.h
         Types.h
         Devices/AbstractLoggingDevice.h
         Devices/ConsoleLogger.h
         Devices/FileLogger.h
         Devices/MemoryLogger.h
         Formatters/AbstractFormatter.h
         Formatters/DetailedFormatter.h
         Formatters/ErrorFormatter.h
         Formatters/HtmlFormatter.h
         Formatters/InfoFormatter.h
         Formatters/NullFormatter.h)

SET(SRCS AddToCallStack.cpp
         LoggingManager.cpp
         SLogLib.cpp
         SysUtils.cpp
         Devices/AbstractLoggingDevice.cpp
         Devices/FileLogger.cpp
         Devices/MemoryLogger.cpp)

set(RELEASE_MANGLED_NAME "SLogLib-${SLOGLIB_VERSION_MAJOR}.${SLOGLIB_VERSION_MINOR}")
set(DEBUG_MANGLED_NAME   "SLogLib${SLOGLIB_DEBUG_POSTFIX}-${SLOGLIB_VERSION_MAJOR}.${SLOGLIB_VERSION_MINOR}")

if(WIN32)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Platform/version.rc.in ${CMAKE_CURRENT_BINARY_DIR}/version.rc @ONLY)
	set(rcFile ${SRCS} ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
	add_definitions(-DSLOGLIB_EXPORTS)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
else()
    set(rcFile)
endif()

add_library(SLogLib SHARED ${SRCS} ${HDRS} ${rcFile})

# Set the name of targets based on configurations.
set_target_properties(SLogLib PROPERTIES 
                        OUTPUT_NAME_DEBUG          "${DEBUG_MANGLED_NAME}" 
						OUTPUT_NAME_RELEASE        "${RELEASE_MANGLED_NAME}" 
						OUTPUT_NAME_MINSIZEREL     "${RELEASE_MANGLED_NAME}" 
						OUTPUT_NAME_RELWITHDEBINFO "${RELEASE_MANGLED_NAME}")

# Set the version and soversion for Linux.
if(SLOGLIB_VERSION AND SLOGLIB_SOVERSION)
	set_target_properties(SLogLib PROPERTIES 
                            VERSION   "${SLOGLIB_VERSION}" 
							SOVERSION "${SLOGLIB_SOVERSION}")
endif()

# Install the target (DLL and LIB files for windows and SO file for Linux)
install(TARGETS SLogLib
          RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
          LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
          ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# For MSVC install PDB files as well.
if(MSVC)
	install(FILES ${CMAKE_BINARY_DIR}/Bin/Debug/${DEBUG_MANGLED_NAME}.pdb DESTINATION ${CMAKE_INSTALL_PREFIX}/bin CONFIGURATIONS DEBUG)
	install(FILES ${CMAKE_BINARY_DIR}/Bin/RelWithDebInfo/${RELEASE_MANGLED_NAME}.pdb DESTINATION ${CMAKE_INSTALL_PREFIX}/bin CONFIGURATIONS RELWITHDEBINFO)
endif(MSVC)

# Install the header files.
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}/include 
        FILES_MATCHING 
			PATTERN "*.h"
			PATTERN "SLogLib"
			PATTERN "Platform" EXCLUDE)

