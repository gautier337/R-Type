#!/usr/bin/bash

# Function to test exit status of a command
function testExitStatus() {
    if [ $1 -ne 0 ]; then
        echo "$2 failed"
        exit 1
    else
        echo "$2 succeeded"
    fi
}

# Create build directory
mkdir -p build
testExitStatus $? "mkdir"

# Change to build directory
cd build
testExitStatus $? "cd"

# Install Conan dependencies
conan install .. --build=missing -s compiler.libcxx=libstdc++11 -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
testExitStatus $? "conan install dependencies"

# Configure and build with CMake
cmake -DCMAKE_BUILD_TYPE=Debug ..
testExitStatus $? "cmake config"
cmake --build . -- -j
testExitStatus $? "cmake build"

