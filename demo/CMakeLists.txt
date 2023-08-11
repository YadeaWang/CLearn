cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(demo LANGUAGES CXX)

# <<< General set up >>>
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBS_DIR "../../project/_libs" CACHE STRING "directory of dependencies libs")
include_directories(${LIBS_DIR}/ciccficcquantlib_gcc10/include)
link_directories(${LIBS_DIR}/ciccficcquantlib_gcc10/lib)

add_executable(coupon coupon.cpp)

target_link_libraries(coupon CiccFiccQuantLib QuantLib)
