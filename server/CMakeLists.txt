cmake_minimum_required(VERSION 3.10)
project(RTypeServer)

set(CMAKE_CXX_STANDARD 17)

# Include directories for header files
include_directories(include)

# If you have installed Asio in a custom directory, replace this with your Asio include path
include_directories(/usr/include)

# Add definitions
add_definitions(-DASIO_STANDALONE)

# Add executable target
add_executable(RTypeServer src/main.cpp src/server.cpp)

# Link necessary libraries (Threads library for Asio)
find_package(Threads REQUIRED)
target_link_libraries(RTypeServer PRIVATE Threads::Threads)
