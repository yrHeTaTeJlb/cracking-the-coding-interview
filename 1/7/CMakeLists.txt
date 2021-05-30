cmake_minimum_required(VERSION 3.16)
project(task_1_7 LANGUAGES CXX)

include(GoogleTest)

add_executable("${PROJECT_NAME}" main.cpp "${ASTYLE_CONFIG}")
target_link_libraries("${PROJECT_NAME}" PRIVATE gtest_main)

gtest_discover_tests("${PROJECT_NAME}")
