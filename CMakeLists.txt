cmake_minimum_required(VERSION 3.16)

project(CtCi)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ASTYLE_CONFIG "${CMAKE_CURRENT_LIST_DIR}/.astylerc")

FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "release-1.10.0"
)

FetchContent_MakeAvailable(googletest)

add_subdirectory("1")
