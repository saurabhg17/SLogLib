
if(WIN32)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
endif()

set(RELEASE_MANGLED_NAME "LoggingDemo")
set(DEBUG_MANGLED_NAME   "LoggingDemo${SLOGLIB_DEBUG_POSTFIX}")

add_executable(LoggingDemo LoggingDemo.cpp)
target_link_libraries(LoggingDemo SLogLib)

# Set the name of targets based on configurations.
set_target_properties(LoggingDemo PROPERTIES 
                        OUTPUT_NAME_DEBUG          "${DEBUG_MANGLED_NAME}" 
						OUTPUT_NAME_RELEASE        "${RELEASE_MANGLED_NAME}" 
						OUTPUT_NAME_MINSIZEREL     "${RELEASE_MANGLED_NAME}" 
						OUTPUT_NAME_RELWITHDEBINFO "${RELEASE_MANGLED_NAME}")
						
install(TARGETS LoggingDemo
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)