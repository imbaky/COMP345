cmake_minimum_required(VERSION 3.8)
project(Risk)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Assets/Maploader.cpp Assets/Maploader.h)
add_executable(Risk ${SOURCE_FILES})