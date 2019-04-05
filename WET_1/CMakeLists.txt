cmake_minimum_required(VERSION 3.6)
project(DataSructures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic-errors ")

set(SOURCE_FILES splayTree.h gladiator.cpp trainer.cpp colosseum.cpp library1.cpp main1.cpp)

add_executable(DS ${SOURCE_FILES})
