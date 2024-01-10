cmake_minimum_required(VERSION 3.10)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)

# Include directories for header files
include_directories(include)

# If you have installed Asio in a custom directory, replace this with your Asio include path
include_directories(/usr/local/include)

# Add definitions
add_definitions(-DASIO_STANDALONE)

# Add executable target with new source files
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
)

# Link necessary libraries (Threads library for Asio)
find_package(Threads REQUIRED)
target_link_libraries(r-type_server PRIVATE Threads::Threads)
