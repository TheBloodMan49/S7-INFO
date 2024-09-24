cmake_minimum_required(VERSION 3.30)#baisser en 3.0 si cmake trop vieux sur la machine

set(project string) #nom du projet
project(${project} VERSION 0.1.0) #version de l'executable
set(CMAKE_CXX_STANDARD 14) #oncompile en c++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${project} test.cpp string.cpp ) #liste des fichiers cpp à compiler

target_compile_options(${project} PUBLIC -Wall -Wextra -O2) #ajout de paramètre de compilation: active tous les warnings + les optimisations de code niveau 2

