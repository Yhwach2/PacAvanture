cmake_minimum_required(VERSION 4.0)
project(PacAvanture)

set(CMAKE_CXX_STANDARD 20)

add_executable(PacAvanture cmake-build-debug/src/main.cpp
        src/Game.h
        src/Player.h
        src/Enemy.h
        src/Map.h
        src/InputHandler.h)
