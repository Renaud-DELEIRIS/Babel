cmake_minimum_required(VERSION 3.14.5)

set(CMAKE_CXX_STANDARD 17)

project(babel_client)
project(babel_server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set compiler arguments
if (NOT WIN32)
	if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE Debug)
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -Wno-unused")
	# add_compile_options(-Wall -Wextra -g3)
	set(CMAKE_CXX_FLAGS_DEBUG "-g3")
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SERVER_PATH "${CMAKE_SOURCE_DIR}/src/server")
set(CLIENT_PATH "${CMAKE_SOURCE_DIR}/src/client/")
set(SECURITY_PATH "${CMAKE_SOURCE_DIR}/src/")

# Include headers
include_directories(include/)
include_directories(build/include/)
include_directories(src/client/GUI/)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

file(GLOB_RECURSE BABEL_SERVER RELATIVE ${CMAKE_SOURCE_DIR} "${SERVER_PATH}*/*.cpp" "${SERVER_PATH}*.cpp" "${SECURITY_PATH}security.cpp")
file(GLOB_RECURSE BABEL_CLIENT RELATIVE ${CMAKE_SOURCE_DIR} "${CLIENT_PATH}*/*.cpp" "${CLIENT_PATH}*.cpp" "${SECURITY_PATH}security.cpp")

add_executable(babel_server ${BABEL_SERVER})
add_executable(babel_client ${BABEL_CLIENT})

find_package(asio)
find_package(portaudio)
find_package(Opus)
find_package(SQLite3)
find_package(Boost REQUIRED COMPONENTS thread)
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)



# target_link_libraries(babel_server asio::asio SQLite::SQLite3 Boost::thread)
# target_link_libraries(babel_client portaudio::portaudio Opus::opus Qt5::Widgets)
target_link_libraries(babel_client ${CONAN_LIBS})
target_link_libraries(babel_server ${CONAN_LIBS} Boost::thread)
