cmake_minimum_required(VERSION 3.26)
project(Atividade_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Atividade_3 main.cpp
        SuperGraph.cpp
        SuperGraph.h
        GSet.cpp
        GSet.h
        Karger.cpp
        Karger.h
        Naive.cpp
        Naive.h
        IO.cpp
        IO.h
)
