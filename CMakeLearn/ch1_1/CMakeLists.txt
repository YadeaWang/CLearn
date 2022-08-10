cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(CMAKELEARN LANGUAGES CXX)

# chapter 1.7
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C flags, Debug configuration: ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "C flags, Release configuration: ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "C flags, Release configuration with Debug info: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "C flags, minimal Release configuration: ${CMAKE_C_FLAGS_MINSIZEREL}")
message(STATUS "C++ flags, Debug configuration: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ flags, Release configuration: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "C++ flags, Release configuration with Debug info: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "C++ flags, minimal Release configuration: ${CMAKE_CXX_FLAGS_MINSIZEREL}")

# chapter 1.6
message(STATUS "Is the C++ compiler loaded? ${CMAKE_CXX_COMPILER_LOADED}")
if(CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "The C++ compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "Is the C++ from GNU? ${CMAKE_COMPILER_IS_GNUCXX}")
    message(STATUS "The C++ compiler version is: ${CMAKE_CXX_COMPILER_VERSION}")
endif()

message(STATUS "Is the C compiler loaded? ${CMAKE_C_COMPILER_LOADED}")
if(CMAKE_C_COMPILER_LOADED)
    message(STATUS "The C compiler ID is: ${CMAKE_C_COMPILER_ID}")
    message(STATUS "Is the C from GNU? ${CMAKE_COMPILER_IS_GNUCC}")
    message(STATUS "The C compiler version is: ${CMAKE_C_COMPILER_VERSION}")
endif()

# chapter 1.5
include(CMakeDependentOption)

cmake_dependent_option(
    MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
    "USE_LIBRARY" ON
)

cmake_dependent_option(
    MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
    "USE_LIBRARY" ON
)

# chapter 1.4
# option(USE_LIBRARY "Compile sources into a library?" OFF)

# message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

# set(BUILD_SHARED_LIBS OFF)

# list(APPEND _sources message.hpp message.cpp)

# if(USE_LIBRARY)
#     # add_library will create a static library
#     # since BUILD_SHARED_LIBS is OFF
#     add_library(message ${_sources})
#     add_executable(hello-world helloworld.cpp)
#     target_link_libraries(hello-world message)
# else()
#     add_executable(hello-world helloworld.cpp ${_sources})
# endif()

# chapter 1.3
add_library(message-objs
    OBJECT
        message.cpp
        message.hpp
)

set_target_properties(message-objs
    PROPERTIES
        POSITION_INDEPENDENT_CODE 1
)

add_library(message-shared
    SHARED
        $<TARGET_OBJECTS:message-objs>
)

set_target_properties(message-shared
    PROPERTIES
        OUTPUT_NAME "message"
)

add_library(message-static
    STATIC
        $<TARGET_OBJECTS:message-objs>
)

set_target_properties(message-static
    PROPERTIES
        OUTPUT_NAME "message"
)

add_executable(hello-world helloworld.cpp)
target_link_libraries(hello-world message-static)
