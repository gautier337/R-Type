cmake_minimum_required(VERSION 3.12)
project(RTypeGameEngine)

set(CMAKE_CXX_STANDARD 17)

# Add your source files here
set(SOURCES
    ECS/src/components/Shoot.cpp
    ECS/SystemManager/Entity.cpp
    ECS/SystemManager/EntityManager.cpp
    ECS/SystemManager/HitboxSystem.cpp
    ECS/SystemManager/PlayerSystem.cpp
    ECS/SystemManager/ShootSystem.cpp
    # Add other source files as needed
)

# Include directories
include_directories(ECS/include)

add_executable(RTypeGameEngine ${SOURCES})

# Find and link necessary libraries (e.g., if you use SFML, OpenGL, etc.)
# target_link_libraries(RTypeGameEngine PRIVATE sfml-graphics sfml-window sfml-system)

# Customize the build process based on the operating system
if (WIN32)
    # Copy the run script to the build directory
    configure_file(run_game.bat ${CMAKE_BINARY_DIR}/run_game.bat COPYONLY)
else ()
    # Add Linux-specific configurations
    # target_link_libraries(RTypeGameEngine PRIVATE some_linux_library)
endif ()
