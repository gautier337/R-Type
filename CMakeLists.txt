    cmake_minimum_required(VERSION 3.12)
    project(RTypeGameEngine)

    set(CMAKE_CXX_STANDARD 17)

    # Add your source files here
    set(SOURCES
        Engine/includes/Entity.hpp
        Engine/includes/Component.hpp
        Engine/includes/System.hpp
        Engine/includes/ECSManager.hpp
        Engine/src/ECSManager.cpp
        Engine/src/Entity.cpp
        Engine/src/System.cpp
        Engine/src/Component.cpp
        Engine/main.cpp  # Add your main source file here
    )

    add_executable(RTypeGameEngine ${SOURCES})

    # Find and link necessary libraries (e.g., if you use SFML, OpenGL, etc.)
    # target_link_libraries(RTypeGameEngine PRIVATE sfml-graphics sfml-window sfml-system)

    # Customize the build process based on the operating system
    if (WIN32)
        # Add Windows-specific configurations
        # target_link_libraries(RTypeGameEngine PRIVATE some_windows_library)
    else ()
        # Add Linux-specific configurations
        # target_link_libraries(RTypeGameEngine PRIVATE some_linux_library)
    endif ()
