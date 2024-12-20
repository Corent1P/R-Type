cmake_minimum_required(VERSION 3.25)
project(R-Type)

cmake_policy(SET CMP0091 NEW)
add_definitions(-D_WIN32_WINNT=0x0601)


set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Plugins)
set(Boost_INCLUDE_DIR "./vcpkg_installed/x64-windows/include/boost")
set(jsoncpp_INCLUDE_DIR "${WORKING_DIRECTORY}/build/vcpkg_installed/x64-linux/include/json")
set(SFML_DIR "./vcpkg_installed/x64-windows/share/sfml")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0601)
endif()

if(NOT MSVC)
    if (APPLE)
        add_compile_options(-Wall -Wextra -Werror)
    else()
        add_compile_options(-Wall -Wextra -Werror -ljsoncpp)
    endif()
else()
    # add_compile_options(/W4 /WX)
endif()
if (!APPLE)
    set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=.;
    -checks=*,modernize-*,-*,boost-*;)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory(src/protocolHandler)

find_package(Lua REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(SFML 2.6.1 COMPONENTS system window graphics audio REQUIRED)

add_subdirectory(src/ecs)
add_subdirectory(src/client)
add_subdirectory(src/server)

