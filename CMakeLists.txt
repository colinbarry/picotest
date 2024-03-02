cmake_minimum_required(VERSION 3.8)
project(picotest)

add_library(picotest INTERFACE ./include/picotest/picotest.h)
target_include_directories(picotest INTERFACE include)

option(PICOTEST_BUILD_SAMPLE "Build a sample test system and test runner" OFF)
if (PICOTEST_BUILD_SAMPLE AND PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    add_subdirectory(sample)
endif()
