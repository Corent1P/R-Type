cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0091 NEW)

project(main)

set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Plugins)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0601)
endif()

if(NOT MSVC)
#     add_compile_options(/W4 /WX)
# else()
    add_compile_options(-Wall -Wextra -Werror -g)
endif()

# set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")

# if (CMAKE_SYSTEM MATCHES MacOSX)
#     include_directories(${"/opt/homebrew/lib"})
# endif()

find_package(Boost REQUIRED)
find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)

add_subdirectory(src/ecs)
add_subdirectory(src/protocolHandler)

add_subdirectory(src/client)
add_subdirectory(src/server)

target_link_libraries(r-type_client PUBLIC boost::boost sfml::sfml)
target_link_libraries(r-type_server PUBLIC boost::boost sfml::sfml)
