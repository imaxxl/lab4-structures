cmake_minimum_required(VERSION 3.16)
project(lab4_structures VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека со структурами данных (стек, очередь, дерево).
add_library(lab4_structures
    src/stack.cpp
    src/queue.cpp
    src/binary_tree.cpp
)
target_include_directories(lab4_structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Консольное приложение (собирается в один исполняемый файл).
add_executable(lab4_app src/main.cpp)
target_link_libraries(lab4_app PRIVATE lab4_structures)
