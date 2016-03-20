cmake_minimum_required(VERSION 2.8)
project(ConcuPort2_2015)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -O0 -coverage")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -W -coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-Wall -Werror -g -O0 -coverage")

add_subdirectory(ar/fi/uba/concurrentes/src)
add_subdirectory(ar/fi/uba/concurrentes/main)
add_subdirectory(ar/fi/uba/concurrentes/test)
