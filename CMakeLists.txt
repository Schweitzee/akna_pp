cmake_minimum_required(VERSION 3.22)
project(akna_pp)

set(CMAKE_CXX_STANDARD 11)

#add_compile_definitions(MEMTRACE)

#add_compile_definitions(CPORTA)

#if(MEMTRACE)
#    add_definitions(-DMEMTRACE=1)
#endif(MEMTRACE)

add_executable(akna_pp main.cpp
        Game.cpp Game.h
        Field.cpp Field.h
        Mine.cpp Mine.h
        Tile.h
        VektorTable.cpp VektorTable.h
        econio.cpp econio.h
#        memtrace.h memtrace.cpp
        gtest_lite.h)
