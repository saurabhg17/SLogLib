
add_executable(LoggingDemo LoggingDemo.cpp)

set_target_properties(LoggingDemo
						PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(LoggingDemo SLogLib)

target_compile_options(LoggingDemo PRIVATE
						$<$<CXX_COMPILER_ID:MSVC>:/W4>
						$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)
						
install(TARGETS LoggingDemo RUNTIME DESTINATION bin)

if(MSVC)
	install(FILES $<TARGET_PDB_FILE:LoggingDemo> DESTINATION bin OPTIONAL)
endif()