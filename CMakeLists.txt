cmake_minimum_required(VERSION 3.3)
project(roborally)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    set(SOURCE_FILES example.c dijkstra.c dijkstra.h graph.c board.h board.c)
    #set_property(PROPERTY C_STANDARD 99)
    set(CMAKE_C_FLAGS "-std=c99")
    add_executable(roborally ${SOURCE_FILES})