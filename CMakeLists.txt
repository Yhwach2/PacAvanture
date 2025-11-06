cmake_minimum_required(VERSION 3.10)
project(PacAvanture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(PagcAvanture
        src/main.cpp
        src/Game.cpp
        src/Player.cpp
        src/Enemy.cpp
        src/Map.cpp
        src/InputHandler.cpp
)
