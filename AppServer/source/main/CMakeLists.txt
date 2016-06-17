cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unused-variable")

# Locate all .cpp files in this src folder
FILE(GLOB SOURCE_FILES "../src/server/*.cpp" 
						"../src/server/Controllers/*.cpp" 
						"../src/server/Services/*.cpp" 
						"../src/database/*.cpp"
						"../src/utils/*.cpp")

add_executable(Tinder_main main.cpp ${SOURCE_FILES})

#copy files folder to build destination
file(COPY ../files DESTINATION ..)
target_link_libraries(Tinder_main ${NOMBRE_LIBS} pthread ${CMAKE_INCLUDE_PATH} curl jsoncpp)