cmake_minimum_required(VERSION 3.8)
project(main)

set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Plugins)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -header-filter=.;
  -checks=*,modernize-*,-*,boost-*;)

# set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")

# if (CMAKE_SYSTEM MATCHES MacOSX)
#     include_directories(${"/opt/homebrew/lib"})
# endif()

add_subdirectory(src/ecs)
add_subdirectory(src/protocolHandler)

find_package(Boost REQUIRED)
find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)

add_subdirectory(src/client)
add_subdirectory(src/server)
