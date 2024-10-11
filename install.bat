@echo off

@REM type ressources\logoASCII.txt

where conan >nul 2>nul
if %errorlevel% neq 0 (
    echo Conan is not installed. Please install Conan manually:
    echo 1. Visit https://conan.io/downloads
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

echo Running Conan and CMake...
conan profile detect --force
if not exist "build" mkdir build
cd build

for /f "tokens=*" %%i in ('conan profile path default') do set "profile_path=%%i"

findstr /C:"compiler.cppstd=20" "%profile_path%" >nul
if %errorlevel% neq 0 (
    echo Setting Conan profile to use C++20...
    echo compiler.cppstd=20 >> "%profile_path%"
    echo Updated Conan profile to use C++20.
) else (
    echo Conan profile already set to use C++20.
)
echo Updated Conan profile:
conan profile show

conan install .. --output-folder=. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
cmake .. -DCMAKE_TOOLCHAIN_FILE=build\generators\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo CMake configuration failed. Please check the error messages above.
    pause
    exit
)
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Build process failed. Please check the error messages above.
    pause
    exit
)

echo Build process completed.

pause
