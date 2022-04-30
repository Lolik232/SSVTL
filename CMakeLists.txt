cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME "SSVTL")

project(${PROJECT_NAME} VERSION "0.0.1" LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(ssvtl)
add_subdirectory(ssvtl_tests)
