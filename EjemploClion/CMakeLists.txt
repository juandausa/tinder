cmake_minimum_required(VERSION 2.8)
project(ConcuPort2_2015)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_subdirectory(ar/fi/uba/concurrentes/src)
add_subdirectory(ar/fi/uba/concurrentes/main)
add_subdirectory(ar/fi/uba/concurrentes/test)