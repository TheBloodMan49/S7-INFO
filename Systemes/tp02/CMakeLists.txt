cmake_minimum_required(VERSION 3.30)
project(tp02 C)

set(CMAKE_C_STANDARD 11)

add_executable(deroutement
        deroutement.c)

add_executable(signal
        signal.c)

add_executable(boucle
        boucle.c)
add_executable(update update.c)

add_executable(update2 update2.c)
add_executable(sendsignals sendsignals.c)
