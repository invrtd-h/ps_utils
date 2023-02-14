cmake_minimum_required(VERSION 3.22)
project(ps_utils)

set(CMAKE_CXX_STANDARD 20)

add_library(ps_utils math/fft.h math/modulo.h math/sieve.h datastructures/mo.h math/fraction.h)
