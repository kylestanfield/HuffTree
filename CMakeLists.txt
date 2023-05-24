cmake_minimum_required(VERSION 3.14)
project(Huffman_Tree)

#Google Test needs C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(Tree HuffTree.cpp)
add_executable(compress compress.cpp)
target_link_libraries(compress PUBLIC Tree)
target_link_libraries(compress PRIVATE "stdc++fs")
