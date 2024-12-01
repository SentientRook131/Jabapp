cmake_minimum_required(VERSION 3.24)
project(Jabapp CXX)
set(CMAKE_CXX_STANDARD 23)

include_directories(
    include
)

file(GLOB_RECURSE src
    src/*.cpp
)

add_executable(Jabapp
    ${src}
        include/Parser.h
        src/lib/Parser.cpp
)
