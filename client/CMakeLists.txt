cmake_minimum_required(VERSION 3.10)
project(r-type_client VERSION 2023 LANGUAGES CXX)

set(SRC
    src/Client.cpp
    src/Game.cpp
    src/Main.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)

# Détecter le système d'exploitation
if(WIN32)
    # Utiliser FetchContent pour télécharger SFML sous Windows
    include(FetchContent)
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1 # Spécifiez la version de SFML que vous souhaitez
    )
    FetchContent_MakeAvailable(sfml)

    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
else()
    # Sous Linux, utiliser find_package
    find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio pthread)
endif()

# Debug configuration
set(CMAKE_BUILD_TYPE Debug)
