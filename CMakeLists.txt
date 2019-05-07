cmake_minimum_required(VERSION 3.13)
project(internship)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

add_executable(internship main.cpp enron.cpp enron.h Jaccard.cpp Jaccard.h App.cpp App.h)