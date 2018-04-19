cmake_minimum_required(VERSION 3.9)
project(forest)

set(CMAKE_CXX_STANDARD 11)

add_executable(forest main.cpp avl_tree.h red_black_tree.h bs_tree.h trie.cpp trie.h)