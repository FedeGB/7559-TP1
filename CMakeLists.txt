cmake_minimum_required(VERSION 3.2)
project(TP1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PlatoComida.cpp PlatoComida.h Menu.cpp Menu.h Logger.cpp Logger.h)
add_executable(TP1 ${SOURCE_FILES})