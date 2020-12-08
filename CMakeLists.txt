cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks-1 C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c
        library/commonUtils/stack.c
        library/commonUtils/cyclical_list.c
        library/commonUtils/list.c
        library/commonUtils/avl.c
        library/commonUtils/bst.c
        library/commonUtils/graph.c
)

add_library(library ${SOURCE_LIB})
add_library(complex library/commonUtils/complex.c)

add_executable(sol1_1 Homeworks_1/1sol.c)
target_link_libraries(sol1_1 library)
add_executable(sol1_2 Homeworks_1/2sol.c)
target_link_libraries(sol1_2 library)
add_executable(sol1_3 Homeworks_1/3sol.c)
add_executable(sol1_4 Homeworks_1/4sol.c)
add_executable(sol1_5 Homeworks_1/5sol.c)
target_link_libraries(sol1_5 library)

add_executable(sol2_1 Homeworks_2/1sol.c)
add_executable(sol2_2 Homeworks_2/2_2sol.c)
add_executable(sol2_3 Homeworks_2/2_3sol.c)
add_executable(sol2_4 Homeworks_2/2_4sol.c)
add_executable(sol2_5 Homeworks_2/2_5sol_recursion_version.c)
add_executable(sol2_5_1 Homeworks_2/2_5sol_iteration_version.c)

add_executable(sol3_2 Homeworks_3/3_2sol.c)
target_link_libraries(sol3_2 library)
add_executable(sol3_1 Homeworks_3/3_1sol.c)
target_link_libraries(sol3_1 library)

add_executable(sol4_1 Homeworks_4/4_1sol.c)
target_link_libraries(sol4_1 library)
add_executable(sol4_2 Homeworks_4/4_2sol.c)
add_executable(sol4_3 Homeworks_4/3sol.c)

add_executable(sol5_2 Homeworks_5/5_2sol.c)
target_link_libraries(sol5_2 library)
add_executable(sol5_1 Homeworks_5/5_1sol.c)
target_link_libraries(sol5_1 library)

add_executable(test1.1 test1/test1.1.c)
add_executable(test1.2 test1/test1.2.c)
target_link_libraries(test1.2 complex)

add_executable(sol7_1 Homeworks_7/7.1sol.c)
target_link_libraries(sol7_1 library)

add_executable(test2.1 test2/2.1test.c)
add_executable(test2.2 test2/2.2sol.c)
add_executable(test2.3 test2/2.3sol.c)
target_link_libraries(test2.3 library)

add_executable(7.2sol Homeworks_7/7.2sol.c)
target_link_libraries(7.2sol library)
