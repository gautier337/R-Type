#!/bin/sh

# Créez un nom de dossier .zip avec la date d'aujourd'hui
current_date=$(date +"%Y-%m-%d")
zip_folder_name="r_type_$current_date"

# Create build directory
mkdir -p server/build
cd server/build && cmake .. && make && mv r-type_server ../../

mkdir -p ../../client/build
cd ../../client/build && cmake .. && make && mv r-type_client ../../

# Créez l'archive .zip en spécifiant le chemin complet des fichiers
cd ../.. && zip -r "$zip_folder_name.zip" r-type_client r-type_server assets
