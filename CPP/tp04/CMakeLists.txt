cmake_minimum_required(VERSION 3.30)
project(tp04)

set(CMAKE_CXX_STANDARD 20)

add_executable(tp04 main.cpp)
target_compile_options(tp04 PRIVATE -Wall -O2 -Wextra -Wpedantic)
