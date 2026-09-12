cmake_minimum_required(VERSION 3.16)
project(lab4_structures VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека со структурами данных (стек, очередь, дерево).
add_library(lab4_structures
    src/stack.cpp
)
target_include_directories(lab4_structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
