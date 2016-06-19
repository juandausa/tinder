cmake_minimum_required(VERSION 2.8)
project(Tinder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror --coverage -o0 -Wno-unknown-pragmas")

include(cmake-modules/FindGlog.cmake)
include(cmake-modules/Findrocksdb.cmake)
# Flags for rocks db
SET(GCC_ROCKSDB_LINK_FLAGS "-lz -lpthread -lrt")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_ROCKSDB_LINK_FLAGS}" )

set(NOMBRE_LIBS rocksdb z snappy bz2 pthread rt gtest glog curl jsoncpp)
foreach(LIB ${NOMBRE_LIBS})
    find_library(LIBRERIA${LIB} NAMES ${LIB} )
    if (LIBRERIA${LIB}) #False si es 0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, vacio, o si termina en "-NOTFOUND". Caso contrario es TRUE.
        message(STATUS "Librería |${LIB}| encontrada en |${LIBRERIA${LIB}}|")
    else (LIBRERIA${LIB})
        message(FATAL_ERROR "No se encontró la librería |${LIB}|. Verificar existencia.")
    endif (LIBRERIA${LIB})
endforeach(LIB ${NOMBRE_LIBS})

add_subdirectory(ar/fi/uba/tallerii/src)
add_subdirectory(ar/fi/uba/tallerii/main)
add_subdirectory(ar/fi/uba/tallerii/dbaccess)
add_subdirectory(ar/fi/uba/tallerii/test)