cmake_minimum_required(VERSION 3.27)
project(BitXDR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(BitXDR main.cpp
        constants.h
        InputItems.cpp
        InputItems.h
        JsonEntities/PC.h
        JsonEntities/User.h
        JsonEntities/Alert.h
        Output.cpp
        Output.h
        JsonEntities/Transition.cpp
        JsonEntities/Transition.h
        PathGraph.cpp
        PathGraph.h
)
