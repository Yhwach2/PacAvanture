cmake_minimum_required(VERSION 3.10)
project(PacAvanture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(PacAvanture
        src/main.cpp
        src/Map.cpp
        src/Player.cpp
        src/Enemy.cpp
        src/Game.cpp
        src/FileHandler.cpp
)

enable_testing()

add_executable(test_map tests/test_map.cpp src/Map.cpp src/Player.cpp)
add_test(NAME MapTests COMMAND test_map)

add_executable(test_powerups tests/test_powerups.cpp src/Player.cpp src/Enemy.cpp)
add_test(NAME PowerUpTests COMMAND test_powerups)

add_executable(test_final tests/test_final.cpp src/Map.cpp src/Player.cpp src/FileHandler.cpp)
add_test(NAME FinalTests COMMAND test_final)