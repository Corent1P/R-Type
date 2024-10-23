@echo off

@REM type ressources\logoASCII.txt

where vcpkg >nul 2>nul
if %errorlevel% neq 0 (
    echo vcpkg is not installed. Please install vcpkg manually:
    echo 1. Visit https://vcpkg.io/
    echo 2. Download and run the installer for your system
    echo 3. Restart this script after installation
    pause
    exit
)

where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo CMake is not installed. Please install CMake manually:
    echo 1. Visit https://cmake.org/download/
    echo 2. Download and run the installer for your system
    echo 3. Ensure to add CMake to the system PATH during installation
    echo 4. Restart this script after installation
    pause
    exit
)

echo Running CMake and Vcpkg...

vcpkg x-update-baseline --add-initial-baseline
cmake --preset=windows
cmake -G "Visual Studio 17 2022" build
if %errorlevel% neq 0 (
    echo CMake configuration failed. Please check the error messages above.
    pause
    exit
)

echo Build process completed.

pause
