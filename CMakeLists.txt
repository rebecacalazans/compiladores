# Minimum CMake version required to generate
cmake_minimum_required(VERSION 2.8)
include_directories(include)
project("my first compiler")

add_definitions(-std=c++14)

add_executable(compiler.out analisador_lexico.cpp)
