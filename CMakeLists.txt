cmake_minimum_required(VERSION 3.10)
project(PacAvanture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
        src/main.cpp
        src/Map.cpp
        src/Player.cpp
)

add_executable(PacAvanture ${SOURCES})

# test
enable_testing()

add_executable(test_map
        tests/test_map.cpp
        src/Map.cpp
        src/Player.cpp
)

add_test(NAME MapTests COMMAND test_map)
