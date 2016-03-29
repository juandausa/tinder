cmake_minimum_required(VERSION 2.8)
project(Tinder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include(cmake-modules/FindGlog.cmake)
add_subdirectory(ar/fi/uba/tallerii/src)
add_subdirectory(ar/fi/uba/tallerii/main)
add_subdirectory(ar/fi/uba/tallerii/test)