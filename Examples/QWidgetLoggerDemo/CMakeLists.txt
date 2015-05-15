
# This policy enabled auto-linking of QtMain.
# It was introduced in CMake version 2.8.11.
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the Qt library
if(SLOGLIB_USE_QT_VERSION STREQUAL Qt5)
	find_package(Qt5Widgets)
elseif(SLOGLIB_USE_QT_VERSION STREQUAL Qt4)
	find_package(Qt4 4.0.0 REQUIRED QtCore QtGui)
	include(${QT_USE_FILE})
endif()

if(WIN32)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
endif()

add_executable(QWidgetLoggerDemo QWidgetLogger.h QWidgetLogger.cpp Main.cpp)

if(SLOGLIB_USE_QT_VERSION STREQUAL Qt5)
	target_link_libraries(QWidgetLoggerDemo SLogLib Qt5::Widgets)
elseif(SLOGLIB_USE_QT_VERSION STREQUAL Qt4)
	target_link_libraries(QWidgetLoggerDemo SLogLib ${QT_LIBRARIES})
endif()
