cmake_minimum_required(VERSION 3.12)
project(ProgrammingPearls)

set(CMAKE_CXX_STANDARD 14)

include_directories(catch tools)

add_executable(dist_sort chapter01/disk_sort.cpp tools/Tools.cpp)
add_executable(find_unexisted chapter02/find_unexisted.cpp tools/Tools.cpp)
add_executable(anagrams chapter02/anagrams.cpp)
add_executable(rotate chapter02/rotate.cpp tools/Tools.cpp)