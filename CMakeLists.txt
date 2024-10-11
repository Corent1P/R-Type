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

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -g)
endif()

# set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")

# if (CMAKE_SYSTEM MATCHES MacOSX)
#     include_directories(${"/opt/homebrew/lib"})
# endif()

add_subdirectory(src/ecs)
add_subdirectory(src/protocolHandler)

find_package(Boost REQUIRED)
find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
# include_directories(${SFML_INCLUDE_DIRS})

add_subdirectory(src/client)
add_subdirectory(src/server)

# target_include_directories(r-type_client PRIVATE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS})
# target_include_directories(r-type_server PRIVATE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS})
target_link_libraries(r-type_client PUBLIC boost::boost sfml::sfml)
target_link_libraries(r-type_server PUBLIC boost::boost sfml::sfml)