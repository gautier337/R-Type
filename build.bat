@echo off
REM Create build directory if it doesn't exist
IF NOT EXIST build (mkdir build)

REM Move to build directory, install dependencies, and build
cd build && conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True && cd ..
cmake -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build -j

REM Copy executables to the root of the project directory
copy .\build\bin\r-type_client.exe . 
copy .\build\bin\r-type_server.exe .
copy .\build\bin\r-type_room.exe .
copy .\build\bin\r-type_admin_panel.exe .
