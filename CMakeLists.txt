cmake_minimum_required(VERSION 3.10)
project(lemon)

set(CMAKE_C_STANDARD 11)

find_package(SQLite3 REQUIRED)

add_executable(Lemon main.c)

target_link_libraries(Lemon SQLite::SQLite3)

