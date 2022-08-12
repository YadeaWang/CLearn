set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

add_library(sum sum.cpp)

add_executable(sum_up main.cpp)

target_link_libraries(sum_up sum)