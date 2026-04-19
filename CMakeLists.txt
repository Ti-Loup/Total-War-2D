cmake_minimum_required(VERSION 3.12)
project(TotalWar2D)

set(CMAKE_CXX_STANDARD 20)

# --- CONFIGURATION SDL3_MIXER (Version Libs) ---
# On définit le chemin vers ton dossier extrait (ajuste le nom du dossier si besoin)
set(MIXER_PATH "${CMAKE_SOURCE_DIR}/libs/SDL3_mixer-3.2.0/x86_64-w64-mingw32")

add_executable(TotalWar2D main.cpp
        Components.cpp
        Components.h
        State.cpp
        State.h
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h
)

# 1. Indiquer où trouver SDL3_mixer/SDL_mixer.h
target_include_directories(TotalWar2D PRIVATE "${MIXER_PATH}/include")

# 2. Trouver le fichier .a pour le lien
find_library(MIXER_LIBRARY NAMES SDL3_mixer PATHS "${MIXER_PATH}/lib" NO_DEFAULT_PATH)

# --- LIENS ---
# On ajoute MIXER_LIBRARY à la liste
target_link_libraries(TotalWar2D PRIVATE
        SDL3
        SDL3_image
        SDL3_ttf
        sqlite3
        ${MIXER_LIBRARY}
)

# --- ASSETS ---
set(ASSETS_SRC_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_BINARY_DIR ${CMAKE_BINARY_DIR}/assets)
add_custom_target(
        assets ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${ASSETS_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SRC_DIR} ${ASSETS_BINARY_DIR}
        COMMENT "Clearing and copying game assets into the binary directory."
)
add_dependencies(${PROJECT_NAME} assets)

# --- COPIE DE LA DLL (Post-Build) ---
# Pour que le .exe puisse se lancer sans erreur "SDL3_mixer.dll introuvable"
add_custom_command(TARGET TotalWar2D POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MIXER_PATH}/bin/SDL3_mixer.dll"
        $<TARGET_FILE_DIR:TotalWar2D>
)