cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks-1 C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        )
set(SOURCE_LIB1
        library/commonUtils/arrayOperations.c
        )
add_library(library ${SOURCE_LIB})
add_library(library1 ${SOURCE_LIB1})
add_executable(2sol Homeworks_1/2sol.c)
target_link_libraries(2sol library)

add_executable(sol3 Homeworks_1/3sol.c)

add_executable(sol1 Homeworks_1/1sol.c)
target_link_libraries(sol1 library1)