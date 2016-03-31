cmake_minimum_required(VERSION 2.8)
project(Tinder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include(cmake-modules/FindGlog.cmake)
include(cmake-modules/Findrocksdb.cmake)
# Flags for rocks db
SET(GCC_ROCKSDB_LINK_FLAGS "-lz -lpthread -lrt")
SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_ROCKSDB_LINK_FLAGS}" )

add_subdirectory(ar/fi/uba/tallerii/src)
add_subdirectory(ar/fi/uba/tallerii/main)
add_subdirectory(ar/fi/uba/tallerii/test)
