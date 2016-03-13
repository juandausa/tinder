cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Locate all .h files in include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Locate all .cpp files in this folder
FILE(GLOB SOURCE_FILES ./*.cpp)

#add_executable(ConcuPort2_2015_main ${SOURCE_FILES})


