cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

# example library
add_library(sum_integers sum.cpp)

# main code
add_executable(sum_up main.cpp)
target_link_libraries(sum_up sum_integers)

###### Ctest的测试方案
# testing binary
# add_executable(cpp_test test.cpp)
# target_link_libraries(cpp_test sum_integers)

# enable_testing()

# add_test(
#     NAME bash_test
#     COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh $<TARGET_FILE:sum_up>
#     )
# add_test(
#     NAME cpp_test
#     COMMAND $<TARGET_FILE:cpp_test>
#     )
# add_test(
#     NAME python_test_long
#     COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py --executable $<TARGET_FILE:sum_up>
#     )
# add_test(
#     NAME python_test_short
#     COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py --short --executable $<TARGET_FILE:sum_up>
#     )
    

###### Boost Test的测试方案
find_package(Boost 1.54 REQUIRED COMPONENTS unit_test_framework)

add_executable(cpp_test test.cpp)

target_link_libraries(cpp_test
    PRIVATE
        sum_integers
        Boost::unit_test_framework
)

target_compile_definitions(cpp_test
    PRIVATE
        BOOST_TEST_DYN_LINK
)

enable_testing()

add_test(
    NAME boost_test
    COMMAND $<TARGET_FILE:cpp_test>
)
