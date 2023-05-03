cmake_minimum_required(VERSION 3.24)
project(akna_pp)

set(CMAKE_CXX_STANDARD 11)

if(MEMTRACE)
    add_definitions(-DMEMTRACE=1)
endif(MEMTRACE)

add_executable(akna_pp main.cpp Game.cpp Game.h Field.cpp Field.h Mine.cpp Mine.h Tile.cpp Tile.h VektorTable.cpp VektorTable.h econio.cpp econio.h Control.cpp Control.h memtrace.h memtrace.cpp)
