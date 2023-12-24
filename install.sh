#!/bin/sh

# Create build directory
mkdir -p build
cd build

# Install dependencies with Conan
conan install .. --build=missing -s compiler.libcxx=libstdc++

# Generate CMake files
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build . -- -j 3

# Copy executables to the parent  directory
cp ./RTypeClient ..
cp ./RTypeServer ..

# Return to the parent directory
cd ..
