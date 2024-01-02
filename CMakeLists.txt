cmake_minimum_required(VERSION 3.10)
project(R-Type LANGUAGES CXX)

# Set the C++ standard and make it required for the project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Append custom modules to CMake's module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Include custom CMake files or scripts if necessary
include(DetectCompiler)

# Include subdirectories that contain CMakeLists.txt for modular project management
add_subdirectory(ECS)
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Room)
add_subdirectory(AdminPanel)

# Setup and include Conan for dependency management
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Specify where to install project assets
install(DIRECTORY ./assets/ DESTINATION bin/assets/)

# Include CPack for packaging the project if necessary
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${RTYPE_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${RTYPE_MINOR_VERSION}")
set(CPACK_BUNDLE_NAME "R-Type")
include(CPack)
