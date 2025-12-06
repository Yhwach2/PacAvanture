cmake_minimum_required(VERSION 3.10)
project(PacAvanture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(PacAvanture
        src/main.cpp
        src/Game.cpp
        src/Map.cpp
        src/Enemy.cpp
        src/Player.cpp
        include/Game.h
        include/Map.h
        include/Player.h
        include/Enemy.h
        include/InputHandler.h
)
