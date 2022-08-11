cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ch3-1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 检测Python解释器
find_package(PythonInterp REQUIRED)

execute_process(
    COMMAND
        ${PYTHON_EXECUTABLE} "-c" "print('hello world')"

    RESULT_VARIABLE _status
    OUTPUT_VARIABLE _hello_world
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "RESULT_VARIABLE is : ${_status}")
message(STATUS "OUTPUT_VARIABLE is : ${_hello_world}")

# 检测Boost
# set(Boost_DEBUG ON)

find_package(Boost 1.54 REQUIRED COMPONENTS filesystem)
# include_directories(${Boost_INCLUDE_DIRS})

add_executable(path-info path-info.cpp)

target_link_libraries(path-info
    PUBLIC
        Boost::filesystem
)
