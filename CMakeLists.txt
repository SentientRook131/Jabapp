cmake_minimum_required(VERSION 3.24)
project(Jabapp CXX)

include_directories(
    include
)

file(GLOB_RECURSE interpret_src
    src/interpret/*.cpp
)

file(GLOB_RECURSE runtime
    src/runtime/*.cpp
)

add_library(JabappRuntime SHARED
    ${runtime}
)


add_executable(Jabapp
    ${interpret_src}
)
target_link_libraries(Jabapp
    PUBLIC JabappRuntime
)