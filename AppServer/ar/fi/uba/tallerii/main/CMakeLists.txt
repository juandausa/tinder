cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unused-variable")

# Locate all .h files in include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Locate all .cpp files in this src folder
FILE(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)

add_executable(AppServer_main main.cpp ${SOURCE_FILES})

#copy files folder to build destination
file(COPY ../files DESTINATION ..)
