cmake_minimum_required(VERSION 3.14)
project(Huffman_Tree)

#Google Test needs C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set debugging symbols for gdb
set(CMAKE_BUILD_TYPE Debug)

#include google test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(Tree HuffTree.cpp)
add_library(Heap Minheap.cpp)

add_executable(compress compress.cpp)
add_executable(decompress decompress.cpp)

target_link_libraries(compress PUBLIC Tree)
target_link_libraries(compress PRIVATE "stdc++fs")
target_link_libraries(compress PUBLIC Heap)

target_link_libraries(decompress PUBLIC Tree)
target_link_libraries(decompress PRIVATE "stdc++fs")
target_link_libraries(decompress PUBLIC Heap)
