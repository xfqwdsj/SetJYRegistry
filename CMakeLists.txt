cmake_minimum_required(VERSION 3.24)
project(RegistryHelper)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(RegistryHelper main.cpp)

target_sources(RegistryHelper PRIVATE app.rc)
