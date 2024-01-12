cmake_minimum_required(VERSION 3.10)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)

# Include directories for header files
include_directories(include)

# Include FetchContent module
include(FetchContent)

# Fetch and include Asio
FetchContent_Declare(
    Asio
    URL https://github.com/chriskohlhoff/asio/archive/asio-1-18-1.tar.gz # Example URL, replace with the desired version
)
FetchContent_MakeAvailable(Asio)
include_directories(${asio_SOURCE_DIR}/asio/include)

# Add definitions
add_definitions(-DASIO_STANDALONE)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00) # For Windows 10, adjust according to your target
endif()

# Add executable target with source files
add_executable(r-type_server
    src/main.cpp
    src/server.cpp
    ../ECS/src/SystemManager/Entity.cpp
    ../ECS/src/components/Health.cpp
    ../ECS/src/components/Damages.cpp
    ../ECS/src/SystemManager/EntityManager.cpp
    ../ECS/src/components/Position.cpp
    ../ECS/src/components/Speed.cpp
    ../ECS/src/components/HitBox.cpp
    ../ECS/src/components/ShootCooldown.cpp
    ../ECS/src/SystemManager/HitboxSystem.cpp
    ../ECS/src/SystemManager/EntitySystem.cpp
    ../ECS/src/SystemManager/MissileSystem.cpp
    ../ECS/src/SystemManager/MonsterSystem.cpp
    ../ECS/src/SystemManager/PlayerSystem.cpp
    # Ajoutez ici d'autres fichiers source selon vos besoins
)

if (WIN32)
    target_link_libraries(r-type_server PRIVATE Ws2_32)
endif()

# Link necessary libraries
find_package(Threads REQUIRED)
target_link_libraries(r-type_server PRIVATE Threads::Threads)

# Additional specifications for Windows
if(WIN32)
    # Link specific libraries for Windows if necessary
endif()
