cmake_minimum_required(VERSION 3.6)
project(DataSructures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic-errors ")

set(SOURCE_FILES  gladiators.cpp rankSplayTree.cpp trainingGroup.cpp
        colosseum.cpp library2.cpp main2.cpp)

add_executable(DS ${SOURCE_FILES})
