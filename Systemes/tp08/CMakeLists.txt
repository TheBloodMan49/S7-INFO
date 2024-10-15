cmake_minimum_required(VERSION 3.30)
project(tp08 C)

set(CMAKE_C_STANDARD 11)

add_executable(pair-ser pair-ser.c
        vb-util.c)
add_executable(pair-cli pair-cli.c
        vb-util.c)
add_executable(scrutpair-cli scrutpair-cli.c
        vb-util.c)
add_executable(scrutpair-ser scrutpair-ser.c
        vb-util.c)
