# Locate all .h files in include folder
include_directories(include/server)
include_directories(include/server/Controllers)
include_directories(include/server/Services)
include_directories(include/database)
include_directories(include/resources)
include_directories(include/utils)
include_directories(test/include)


add_subdirectory(src)
add_subdirectory(main)
add_subdirectory(test)
