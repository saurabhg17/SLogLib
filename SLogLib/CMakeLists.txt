
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #
# Add headers and sources.

set(HEADERS_CORE
	AddToCallStack.h
	CallInfo.h
	Config.h
	DisableCopy.h
	DisableCopyMove.h
	LoggingManager.h
	Message.h
	SLogLib.h
	SysUtils.h
	Types.h)

set(HEADERS_DEVICES
	Devices/AbstractLoggingDevice.h
	Devices/ConsoleLogger.h
	Devices/FileLogger.h
	Devices/MemoryLogger.h)

set(HEADERS_FORMATTERS
	Formatters/AbstractFormatter.h
	Formatters/DetailedFormatter.h
	Formatters/ErrorFormatter.h
	Formatters/FullFormatter.h
	Formatters/HtmlFormatter.h
	Formatters/InfoFormatter.h
	Formatters/NullFormatter.h)

set(SOURCES_CORE
	AddToCallStack.cpp
	LoggingManager.cpp
	SLogLib.cpp
	SysUtils.cpp
	Types.cpp)

set(SOURCES_DEVICES
	Devices/AbstractLoggingDevice.cpp
	Devices/FileLogger.cpp
	Devices/MemoryLogger.cpp)

if(MSVC)
	set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Platform/version.rc)
	if(BUILD_SHARED_LIBS)
		add_compile_definitions(SLOGLIB_BUILD_DLL)
		add_compile_definitions(SLOGLIB_EXPORTS)
	endif()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in ${CMAKE_CURRENT_BINARY_DIR}/Version.h @ONLY)

set(SOURCES ${HEADERS_CORE} 
            ${HEADERS_DEVICES}
			${HEADERS_FORMATTERS}
			${SOURCES_CORE}
			${SOURCES_DEVICES}
			${RESOURCES}
			${CMAKE_CURRENT_BINARY_DIR}/Version.h)
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #



# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #
# Build SLogLib library.

set(LIB_NAME SLogLib)

add_library(${LIB_NAME} ${SOURCES})


if(MSVC_IDE OR CMAKE_GENERATOR MATCHES Xcode)
	source_group(Core       FILES ${SOURCES_CORE} ${HEADERS_CORE} ${CMAKE_CURRENT_BINARY_DIR}/Version.h)
	source_group(Devices    FILES ${SOURCES_DEVICES} ${HEADERS_DEVICES})
	source_group(Formatters FILES ${HEADERS_FORMATTERS})
	source_group(Resources  FILES ${RESOURCES})
endif()

target_compile_options(${LIB_NAME} PRIVATE
						$<$<CXX_COMPILER_ID:MSVC>:/W4>
						$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)

target_include_directories(${LIB_NAME} 
							PUBLIC ${CMAKE_SOURCE_DIR}
							PUBLIC ${CMAKE_BINARY_DIR})

if(UNIX)
	set_target_properties(${LIB_NAME} PROPERTIES 
							VERSION   ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
							SOVERSION ${PROJECT_VERSION_MAJOR})
elseif(MSVC AND NOT SLOGLIB_BUILD_SHARED_LIBS)
	set_target_properties(${LIB_NAME} PROPERTIES
							COMPILE_PDB_NAME_DEBUG          ${LIB_NAME}${CMAKE_DEBUG_POSTFIX}
							COMPILE_PDB_NAME_RELWITHDEBINFO ${LIB_NAME})
endif()
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #



# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #
# Install the target (DLL and LIB files for windows and SO file for Linux)
install(TARGETS ${LIB_NAME}
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)

# For MSVC install PDB files as well.
if(MSVC)
	if(SLOGLIB_BUILD_SHARED_LIBS)
		install(FILES $<TARGET_PDB_FILE:${LIB_NAME}> 
				DESTINATION bin OPTIONAL)
	else()
		install(DIRECTORY $<TARGET_FILE_DIR:${LIB_NAME}>/ DESTINATION lib
				FILES_MATCHING PATTERN "${LIB_NAME}*.pdb") 
	endif()
endif()

# Install the header files.
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include 
			FILES_MATCHING 
			PATTERN "*.h"
			PATTERN "SLogLib"
			PATTERN "Platform" EXCLUDE)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Version.h DESTINATION include/SLogLib)
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #
