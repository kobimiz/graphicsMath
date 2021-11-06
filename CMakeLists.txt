cmake_minimum_required(VERSION 3.1)

project(graphicsMath VERSION 1.0)

add_library(graphicsMath SHARED
    src/matrix.cpp
    src/vec3.cpp)