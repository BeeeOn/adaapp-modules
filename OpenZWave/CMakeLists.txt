cmake_minimum_required (VERSION 2.8)

project (beeeon-openzwave)

include (CheckCXXCompilerFlag)

set (CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -g -pedantic -Wall -Wno-unknown-pragmas")
add_definitions(-std=c++11)

set (SOURCE
	BeeeOnMessage.cpp
	Main.cpp
	NotificationProcessor.cpp
	OpenZWaveModule.cpp
	PocoLoggerAdapter.cpp
	Startup.cpp
	ZWaveMessage.cpp
	)

include_directories (
		PATHS
			/usr/include/openzwave
			/usr/local/include/openzwave
)

include_directories(${CMAKE_SOURCE_DIR})

find_library (POCO_FOUNDATION PocoFoundation)
find_library (POCO_UTIL PocoUtil)
find_library (POCO_JSON PocoJSON)
find_library (MOSQUITTO_CPP mosquittopp)
find_library (OPENZWAVE openzwave
		PATHS
			/usr/lib
			/usr/lib64
			/usr/local/lib
			/usr/local/lib64
)

add_executable (${PROJECT_NAME} ${SOURCE})

target_link_libraries (
	${PROJECT_NAME}
	${POCO_FOUNDATION}
	${POCO_UTIL}
	${OPENZWAVE}
	${POCO_JSON}
	${MOSQUITTO_CPP}
	)
