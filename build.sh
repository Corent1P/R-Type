#!/bin/bash

command_exists () {
    command -v "$1" >/dev/null 2>&1
}

is_conan_installed() {
    if [ -z "$1" ]; then
        echo "Error: No package name provided."
        return 1
    fi

    result=$(conan search "$1" 2>&1)

    if echo "$result" | grep -q  $1; then
        echo "Package '$1' is installed in the local cache."
        return 0
    else
        echo "Package '$1' is NOT installed in the local cache."
        return 1
    fi
}

check_first_compilation() {
    echo "Checking if Boost and SFML are installed in the Conan local cache..."

    echo "Checking Boost..."
    is_conan_installed "boost/1.83.0" || return 1

    echo "Checking SFML..."
    is_conan_installed "sfml/2.6.1" || return 1

    echo "Checking for build/ directory..."
    if [ -d "build" ]; then
        echo "build/ directory exists."
        return 0
    else
        echo "build/ directory does not exist."
        return 1
    fi
}

if command_exists conan; then
    echo "Conan is already installed."
else
    echo "Conan is not installed. Please install it to run this project"
    exit 1
fi

if check_first_compilation; then
    echo "All required libraries are installed."
else
    echo "Some required libraries are not installed. Installing..."
    conan profile detect --force
    conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install
fi

mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
