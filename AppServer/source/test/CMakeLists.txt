cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -g -Wall")

execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/files)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/files)

file(GLOB TXTS
        "${CMAKE_CURRENT_SOURCE_DIR}/../files/*.ini" "${CMAKE_CURRENT_SOURCE_DIR}/files/*.txt"
)

file(GLOB MAINTXTS
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

file( COPY ${TXTS}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/files
)

file( COPY ${MAINTXTS}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Locate all .cpp files in test folder
FILE(GLOB CPP_SOURCE_TEST *.cpp)

# Locate all .h in test/include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Locate all .h files in src/include folder
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Locate all .cpp files in src folder
# FILE(GLOB CPP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)
FILE(GLOB CPP_SOURCE "../src/server/*.cpp" 
						"../src/server/Controllers/*.cpp" 
						"../src/server/Services/*.cpp" 
						"../src/database/*.cpp"
						"../src/resources/*.cpp"
						"../src/utils/*.cpp")


# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${CPP_SOURCE_TEST} ${CPP_SOURCE})
target_link_libraries(runTests ${NOMBRE_LIBS} pthread ${CMAKE_INCLUDE_PATH} )