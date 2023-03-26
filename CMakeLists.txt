cmake_minimum_required(VERSION 3.22)
project(ps_utils)

set(CMAKE_CXX_STANDARD 20)

add_executable(ps_utils main.cpp)

add_compile_options(-Wall -lm -static -DONLINE_JUDGE -DBOJ)