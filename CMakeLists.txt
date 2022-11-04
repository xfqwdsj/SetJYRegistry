cmake_minimum_required(VERSION 3.24)
project(SetRegistry)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(SetRegistry main.cpp)

target_sources(SetRegistry PRIVATE app.rc)
