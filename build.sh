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

check_libraries() {
    echo "Checking if Boost and SFML are installed in the Conan local cache..."

    # Checking Boost library
    echo "Checking Boost..."
    is_conan_installed "boost/1.83.0" || return 1

    # Checking SFML library
    echo "Checking SFML..."
    is_conan_installed "sfml/2.6.1" || return 1
}

build() {
    mkdir build
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build .
}

if command_exists conan; then
    echo "Conan is already installed."
else
    echo "Conan is not installed. Installing..."

    if command_exists pip; then
        echo "pip found. Installing Conan using pip..."
        sudo pip install -y conan
    elif command_exists pip3; then
        echo "pip3 found. Installing Conan using pip3..."
        pip3 install conan
    else
        echo "pip is not installed. Please install pip or install Conan manually."
        exit 1
    fi

    if command_exists conan; then
        echo "Conan installed successfully!"
    else
        echo "Conan installation failed. Please check your environment."
        exit 1
    fi
fi

if check_libraries; then
    echo "All required libraries are installed."
    build
    exit 0
fi

conan profile detect --force
conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install
build
