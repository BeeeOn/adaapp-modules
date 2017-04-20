# Top level build configuration
# TN, 2015

cmake_minimum_required (VERSION 2.8)

project (iodaemon)

include (CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else ()
        message (SEND_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif ()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -pedantic -Wextra")

set (IODAEMON_SOURCES
	src/BeeeOnInterface/IOMessage.cpp
	src/BeeeOnInterface/MsgParser.cpp
	src/BeeeOnInterface/Receiver.cpp
	src/BeeeOnInterface/Sender.cpp
	src/HWInterface/HWInterface.cpp
	src/HWInterface/Leds.cpp
	src/logic/main.cpp
	src/logic/logic.cpp
	)

include_directories(
	src/BeeeOnInterface
	src/HWInterface
	src/logic
	)

add_executable (${PROJECT_NAME} ${IODAEMON_SOURCES})

find_package (Threads)
find_library (POCO_FOUNDATION PocoFoundation)
find_library (POCO_JSON PocoJSON)
find_library (POCO_NET PocoNet)
find_library (POCO_UTIL PocoUtil)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${POCO_FOUNDATION} ${POCO_NET} ${POCO_JSON} ${POCO_UTIL})

install (
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION usr/bin
)

install (
	DIRECTORY etc/
	DESTINATION etc/beeeon/
)

install (
	FILES service/beeeon-iodaemon.service
	DESTINATION lib/systemd/system
)
