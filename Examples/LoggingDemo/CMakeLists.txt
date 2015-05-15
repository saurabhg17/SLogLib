
if(WIN32)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
endif()

add_executable(LoggingDemo LoggingDemo.cpp)
target_link_libraries (LoggingDemo SLogLib)