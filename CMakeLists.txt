cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
set(SOURCE_LIB
        library/commonUtils/arrayOperations.c
        )
add_library(library ${SOURCE_LIB})
add_executable(5sol Homeworks_1/5sol.c)
target_link_libraries(5sol library)