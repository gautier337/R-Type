@echo off
set SRC_DIR=%~dp0
set ECS_DIR=%SRC_DIR%ECS
set EXECUTABLE=%SRC_DIR%RTypeGameEngine.exe

:: Setup any environment variables if needed

:: Run the executable
%EXECUTABLE%
