cmake_minimum_required(VERSION 3.27)
project(libbitstream VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

add_library(bitstream bitstream.h bitstream.cpp)