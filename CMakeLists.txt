cmake_minimum_required(VERSION 3.16.3)
project(factory)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(factory
        CleverStrategy.cpp
        CleverStrategy.h
        DefaultStrategy.cpp
        DefaultStrategy.h
        Factory.cpp
        Factory.h
        IStrategy.h
        main.cpp
        SimpleStrategy.cpp
        SimpleStrategy.h
        SmartStrategy.cpp
        SmartStrategy.h
        SnitchStrategy.cpp
        SnitchStrategy.h
        MetaStrategy.h
        MetaStrategy.cpp
        Game.h
        Game.cpp
        func.h
        func.cpp
        Mode.h
        MoveResult.h
        )
