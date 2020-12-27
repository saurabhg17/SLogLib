
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(QWidgetLoggerDemo
				../../Contrib/QWidgetLogger/QWidgetLogger.h
				../../Contrib/QWidgetLogger/QWidgetLogger.cpp
				Main.cpp)

set_target_properties(QWidgetLoggerDemo
						PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_include_directories(QWidgetLoggerDemo
							PRIVATE ../../Contrib/QWidgetLogger)

target_link_libraries(QWidgetLoggerDemo SLogLib Qt5::Widgets)

target_compile_options(LoggingDemo PRIVATE
						$<$<CXX_COMPILER_ID:MSVC>:/W4>
						$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)

install(TARGETS QWidgetLoggerDemo
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

if(MSVC)
	install(FILES $<TARGET_PDB_FILE:QWidgetLoggerDemo> DESTINATION bin OPTIONAL)
endif()
