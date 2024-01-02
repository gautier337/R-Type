#!/bin/sh

# Create build directory
mkdir -p server/build
cd server/build && cmake .. && make && mv r-type_server ../../

cd ../../client && make && mv r-type_client ../
