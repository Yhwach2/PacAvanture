cmake_minimum_required(VERSION 3.10)
project(PacAvanture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Main game
add_executable(PacAvanture
    src/main.cpp
    src/Game.cpp
    src/Map.cpp
    src/Player.cpp
    src/Enemy.cpp
)

# Simple tests - don't fail build if tests fail
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    add_executable(test_map
        tests/test_map.cpp
        src/Map.cpp
        src/Player.cpp
    )
    
    add_executable(test_powerups
        tests/test_powerups.cpp
        src/Player.cpp
        src/Enemy.cpp
    )
endif()
