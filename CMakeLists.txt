cmake_minimum_required(VERSION 3.5)
set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ------------------- CLIENT -------------------
set(CLIENT r-type_client)
project(${CLIENT} LANGUAGES CXX)
set(CLIENT_SRC_PATH "Client/src")
set(CLIENT_INCLUDE_PATH "Client/include")

set(SRC_CLIENT
    ${CLIENT_SRC_PATH}/main.cpp
    ${CLIENT_SRC_PATH}/Image.cpp
    ${CLIENT_SRC_PATH}/Button.cpp
    ${CLIENT_SRC_PATH}/Window.cpp
    ${CLIENT_SRC_PATH}/Game.cpp
    ${CLIENT_SRC_PATH}/Timer.cpp
    ${CLIENT_SRC_PATH}/TextField.cpp
    ${CLIENT_SRC_PATH}/Background.cpp
    ${CLIENT_SRC_PATH}/Paralax.cpp
    ${CLIENT_SRC_PATH}/Music.cpp
    ${CLIENT_SRC_PATH}/Network/UDPClient.cpp
    ${CLIENT_SRC_PATH}/Network/StreamBuffer/AStreamBuffer.cpp
    ${CLIENT_SRC_PATH}/Network/StreamBuffer/UDPClientStreamBuffer.cpp
    ${CLIENT_SRC_PATH}/Network/StreamBuffer/UDPServerStreamBuffer.cpp
)

set(HPP_CLIENT
    ${CLIENT_INCLUDE_PATH}/Window.hpp
    ${CLIENT_INCLUDE_PATH}/Button.hpp
    ${CLIENT_INCLUDE_PATH}/Image.hpp
    ${CLIENT_INCLUDE_PATH}/Game.hpp
    ${CLIENT_INCLUDE_PATH}/TextField.hpp
    ${CLIENT_INCLUDE_PATH}/Timer.hpp
    ${CLIENT_INCLUDE_PATH}/Background.hpp
    ${CLIENT_INCLUDE_PATH}/Paralax.hpp
    ${CLIENT_INCLUDE_PATH}/Music.hpp
    ${CLIENT_INCLUDE_PATH}/Constants/constants.hpp
    ${CLIENT_INCLUDE_PATH}/Network/UDPClient.hpp
    ${CLIENT_INCLUDE_PATH}/Network/StreamBuffer/AStreamBuffer.hpp
    ${CLIENT_INCLUDE_PATH}/Network/StreamBuffer/UDPClientStreamBuffer.hpp
    ${CLIENT_INCLUDE_PATH}/Network/StreamBuffer/UDPServerStreamBuffer.hpp
    ${CLIENT_INCLUDE_PATH}/IoServiceWork.hpp
    ${CLIENT_INCLUDE_PATH}/SafeQueue.hpp
)

add_executable(${CLIENT} ${SRC_CLIENT} ${HPP_CLIENT})
target_link_libraries(${CLIENT} PRIVATE CONAN_PKG::boost CONAN_PKG::sfml)
target_include_directories(${CLIENT} PUBLIC ${CONAN_INCLUDE_DIRS_BOOST} ${CONAN_INCLUDE_DIRS_SFML} ${CLIENT_INCLUDE_PATH})

# ------------------- SERVER -------------------
set(SERVER r-type_server)
project(${SERVER} LANGUAGES CXX)
set(SERVER_SRC_PATH "Server/src")
set(SERVER_INCLUDE_PATH "Server/include")

set(SRC_SERVER
    ${SERVER_SRC_PATH}/main.cpp
    ${SERVER_SRC_PATH}/GameLoop.cpp
    ${SERVER_SRC_PATH}/Timer.cpp
    ${SERVER_SRC_PATH}/Ecs/Entity.cpp
    ${SERVER_SRC_PATH}/Ecs/EntityManager.cpp
    ${SERVER_SRC_PATH}/Ecs/HitboxSystem.cpp
    ${SERVER_SRC_PATH}/Ecs/FrameSendingSystem.cpp
    ${SERVER_SRC_PATH}/Ecs/AISystem.cpp
    ${SERVER_SRC_PATH}/Ecs/PlayerSystem.cpp
    ${SERVER_SRC_PATH}/Ecs/WeaponSystem.cpp
    ${SERVER_SRC_PATH}/Ecs/Components/Health.cpp
    ${SERVER_SRC_PATH}/Ecs/Components/Position.cpp
    ${SERVER_SRC_PATH}/Ecs/Components/Acceleration.cpp
    ${SERVER_SRC_PATH}/Ecs/Components/Damages.cpp
    ${SERVER_SRC_PATH}/Ecs/Components/HitBox.cpp
    ${SERVER_SRC_PATH}/Ecs/Components/Drawable.cpp
    ${SERVER_SRC_PATH}/Network/AServer.cpp
    ${SERVER_SRC_PATH}/Network/TCPServer.cpp
    ${SERVER_SRC_PATH}/Network/TCPServerRoutine.cpp
    ${SERVER_SRC_PATH}/Network/UDPServer.cpp
    ${SERVER_SRC_PATH}/Network/Components/AServerComponent.cpp
    ${SERVER_SRC_PATH}/Network/Components/ConnectComponent.cpp
    ${SERVER_SRC_PATH}/Network/Components/MoveComponent.cpp
    ${SERVER_SRC_PATH}/Network/StreamBuffer/AStreamBuffer.cpp
    ${SERVER_SRC_PATH}/Network/StreamBuffer/TCPStreamBuffer.cpp
    ${SERVER_SRC_PATH}/Network/StreamBuffer/UDPServerStreamBuffer.cpp
    ${SERVER_SRC_PATH}/Network/StreamBuffer/UDPClientStreamBuffer.cpp
)

set(HPP_SERVER
    ${SERVER_INCLUDE_PATH}/Constants.hpp
    ${SERVER_INCLUDE_PATH}/GameLoop.hpp
    ${SERVER_INCLUDE_PATH}/Entity.hpp
    ${SERVER_INCLUDE_PATH}/EntityManager.hpp
    ${SERVER_INCLUDE_PATH}/ISystem.hpp
    ${SERVER_INCLUDE_PATH}/ASystem.hpp
    ${SERVER_INCLUDE_PATH}/HitboxSystem.hpp
    ${SERVER_INCLUDE_PATH}/FrameSendingSystem.hpp
    ${SERVER_INCLUDE_PATH}/AISystem.hpp
    ${SERVER_INCLUDE_PATH}/PlayerSystem.hpp
    ${SERVER_INCLUDE_PATH}/WeaponSystem.hpp
    ${SERVER_INCLUDE_PATH}/IoServiceWork.hpp
    ${SERVER_INCLUDE_PATH}/SafeQueue.hpp
    ${SERVER_INCLUDE_PATH}/Timer.hpp
    ${SERVER_INCLUDE_PATH}/Components/IComponent.hpp
    ${SERVER_INCLUDE_PATH}/Components/AComponent.hpp
    ${SERVER_INCLUDE_PATH}/Components/Health.hpp
    ${SERVER_INCLUDE_PATH}/Components/Position.hpp
    ${SERVER_INCLUDE_PATH}/Components/Acceleration.hpp
    ${SERVER_INCLUDE_PATH}/Components/Damages.hpp
    ${SERVER_INCLUDE_PATH}/Components/HitBox.hpp
    ${SERVER_INCLUDE_PATH}/Components/AI.hpp
    ${SERVER_INCLUDE_PATH}/Components/Weapon.hpp
    ${SERVER_INCLUDE_PATH}/Components/Drawable.hpp
    ${SERVER_INCLUDE_PATH}/Network/AServer.hpp
    ${SERVER_INCLUDE_PATH}/Network/TCPServer.hpp
    ${SERVER_INCLUDE_PATH}/Network/TCPServerRoutine.hpp
    ${SERVER_INCLUDE_PATH}/Network/UDPServer.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/IServerComponent.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/AServerComponent.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/ConnectComponent.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/MoveComponent.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/ConnectComponent.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/Actions.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/Directions.hpp
    ${SERVER_INCLUDE_PATH}/Network/Components/Events.hpp
    ${SERVER_INCLUDE_PATH}/Network/DataStruct/Lobby.hpp
    ${SERVER_INCLUDE_PATH}/Network/DataStruct/Player.hpp
    ${SERVER_INCLUDE_PATH}/Network/StreamBuffer/AStreamBuffer.hpp
    ${SERVER_INCLUDE_PATH}/Network/StreamBuffer/TCPStreamBuffer.hpp
    ${SERVER_INCLUDE_PATH}/Network/StreamBuffer/UDPServerStreamBuffer.hpp
    ${SERVER_INCLUDE_PATH}/Network/StreamBuffer/UDPClientStreamBuffer.hpp
)

add_executable(${SERVER} ${SRC_SERVER} ${HPP_SERVER})
target_link_libraries(${SERVER} PRIVATE CONAN_PKG::boost)
target_include_directories(${SERVER} PUBLIC ${CONAN_INCLUDE_DIRS_BOOST} ${SERVER_INCLUDE_PATH})

# ------------------- CONAN SETUP -------------------
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# ------------------- UNIT_TEST -------------------
add_subdirectory(Server/tests)

# -------------------- MISC --------------------
# Set default compile flags for  GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    target_compile_options(${CLIENT} PRIVATE -std=c++14 -W -Wall -Wextra)
    target_compile_options(${SERVER} PRIVATE -std=c++14 -W -Wall -Wextra)
endif(CMAKE_COMPILER_IS_GNUCXX)

# Set default compile flags for MSVC
if(MSVC)
    message(STATUS "MSVC detected, adding compile flags")
    target_compile_options(${CLIENT} PRIVATE /std:c++14)
    target_compile_options(${SERVER} PRIVATE /std:c++14)
endif(MSVC)
