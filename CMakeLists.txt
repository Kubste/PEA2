cmake_minimum_required(VERSION 3.28)
project(PEAProjekt2)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEAProjekt2
        TSP.hpp
        TSP.cpp
        File_manager.hpp
        File_manager.cpp
        Main.hpp
        Main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")