#!/bin/bash

command_exists () {
    command -v "$1" >/dev/null 2>&1
}

if command_exists conan; then
    echo "Conan is already installed."
else
    echo "Conan is not installed. Installing..."

    if command_exists pip; then
        echo "pip found. Installing Conan using pip..."
        pip install --user conan
    elif command_exists pip3; then
        echo "pip3 found. Installing Conan using pip3..."
        pip3 install --user conan
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

conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
