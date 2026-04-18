cmake_minimum_required(VERSION 3.12)
project(TotalWar2D)

set(CMAKE_CXX_STANDARD 20)

add_executable(TotalWar2D main.cpp
        Components.cpp
        Components.h
        State.cpp
        State.h
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h)

set(ASSETS_SRC_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_BINARY_DIR ${CMAKE_BINARY_DIR}/assets)
add_custom_target(
        assets ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${ASSETS_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SRC_DIR} ${ASSETS_BINARY_DIR}
        COMMENT "Clearing and copying game assets into the binary directory."
)
target_link_libraries(TotalWar2D PRIVATE SDL3 SDL3_image SDL3_ttf sqlite3 SDL3_mixer)

add_dependencies(${PROJECT_NAME} assets)