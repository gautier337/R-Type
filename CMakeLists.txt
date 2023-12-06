    cmake_minimum_required(VERSION 3.12)
    project(RTypeGameEngine)

    set(CMAKE_CXX_STANDARD 17)

    # Add your source files here
    set(SOURCES
    
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
