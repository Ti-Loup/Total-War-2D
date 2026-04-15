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


target_link_libraries(TotalWar2D PRIVATE SDL3 SDL3_image SDL3_ttf sqlite3 SDL3_mixer)