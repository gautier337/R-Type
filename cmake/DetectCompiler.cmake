# Detect the compiler and set the variable COMPILER_TYPE accordingly
if (CMAKE_COMPILER_IS_GNUCXX)
  set(COMPILER_TYPE "gcc")
  
  # Add the flags for the compilation
  add_compile_options(
    "-Wall" "-Wextra" "-Werror" "-pedantic" "-Wpointer-arith" "-fpic"
  )

  # Optional: If you have specific compiler flags for your architecture, set them here
  # Example: add_compile_options("-march=native")

  # Enable or disable testing with the option at cmake command line
  option(TESTING "Build the project with test coverage options" OFF)
  if (TESTING)
    enable_testing()
    add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    add_link_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    
    # Ensure the tests directory is present and has CMakeLists.txt
    add_subdirectory(tests)
  endif()

elseif (MSVC)
  set(COMPILER_TYPE "msvc")
  # Set to export all symbols when building shared libraries on Windows
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  # Define minimum supported Windows version and iterator debug level
  add_compile_options("-D_WIN32_WINNT=0x0601")
  add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
  # Make sure to use the proper runtime library flags if needed
  set(CMAKE_MSVC_RUNTIME_LIBRARY "")

else ()
  # Handle unknown compiler
  set(COMPILER_TYPE "unknown")
  message(WARNING "Unknown compiler type, compilation may not work as expected")
endif()

# Optionally, you might want to add here any architecture-specific configuration
# For instance, setup different flags or configurations for x86 vs x64

