@echo off
SET current_date=%date:~-4,4%-%date:~-7,2%-%date:~-10,2%
SET zip_folder_name=r_type_%current_date%

:: Créer le répertoire de build
mkdir server\build
cd server\build

:: Générer et compiler le projet
cmake .. -G "MinGW Makefiles" && mingw32-make

:: Déplacer les exécutables
move r-type_server.exe ..\..\

cd ..\..\client
@REM mingw32-make
@REM move r-type_client ..

:: Créer l'archive .zip
cd ..
@REM zip -r "%zip_folder_name%.zip" r-type_client.exe r-type_server.exe assets
tar -a -c -f "%zip_folder_name%.zip" r-type_server.exe config_game.txt assets
