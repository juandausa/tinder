cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

target_link_libraries(RequestParser.h)
# Locate all .h files in include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Locate all .cpp files in this folder
FILE(GLOB SOURCE_FILES ./*.cpp)

