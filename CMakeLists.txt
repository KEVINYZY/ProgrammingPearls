cmake_minimum_required(VERSION 3.12)
project(ProgrammingPearls)

set(CMAKE_CXX_STANDARD 14)

include_directories(catch tools)

add_executable(dist_sort chapter01/disk_sort.cpp tools/Tools.cpp)