cmake_minimum_required(VERSION 3.16)

project(DungeonEscapeOOP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(dungeon_escape src/main.cpp)
target_include_directories(dungeon_escape PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(dungeon_escape PRIVATE -Wall -Wextra -Wpedantic)
