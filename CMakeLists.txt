cmake_minimum_required(VERSION 3.8)
project(main)

set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Plugins)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(Boost REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_subdirectory(tests)
add_subdirectory(src/client)
add_subdirectory(src/server)
