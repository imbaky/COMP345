cmake_minimum_required(VERSION 3.8)
project(Risk)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES maploader/main.cpp maploader/Maploader.cpp maploader/Maploader.h)
add_executable(Risk ${SOURCE_FILES})