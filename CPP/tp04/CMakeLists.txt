cmake_minimum_required(VERSION 3.30)
project(tp04)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(tp04 main.cpp)
