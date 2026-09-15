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

# Тесты на GoogleTest (подключаются через FetchContent).
option(LAB4_BUILD_TESTS "Собирать тесты (GoogleTest)" ON)
if (LAB4_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    )
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(lab4_tests
        tests/test_stack.cpp
        tests/test_queue.cpp
        tests/test_binary_tree.cpp
    )
    target_link_libraries(lab4_tests PRIVATE lab4_structures GTest::gtest_main)

    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(lab4_tests)
endif()
