cmake_minimum_required(VERSION 3.27)
project(BitXDR)

set(CMAKE_CXX_STANDARD 20)

add_executable(BitXDR main.cpp
        constants.h
        InputItems.cpp
        InputItems.h
        JsonEntities/PC.cpp
        JsonEntities/PC.h
        JsonEntities/User.cpp
        JsonEntities/User.h
        JsonEntities/Alert.cpp
        JsonEntities/Alert.h
        Output.cpp
        Output.h
        JsonEntities/Transition.cpp
        JsonEntities/Transition.h
        PathGraph.cpp
        PathGraph.h
)
