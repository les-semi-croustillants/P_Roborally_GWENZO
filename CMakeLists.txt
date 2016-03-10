cmake_minimum_required(VERSION 3.3)
project(roborally)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} c99")
set_property(TARGET  PROPERTY C_STANDARD 99)

set(SOURCE_FILES example.c dijkstra.c dijkstra.h graph.c graph.h board.h board.c)
set_property(TARGET PROPERTY C_STANDARD 99)
add_executable(roborally ${SOURCE_FILES})