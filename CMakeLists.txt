cmake_minimum_required(VERSION 3.7..3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(cracking-coding-problems
  VERSION 1.0
  DESCRIPTION "cpp solutions for Cracking the Coding Interview book"
  LANGUAGES CXX)

set(default_build_type "Release")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(data-structures-cpp)

add_subdirectory(ch1)
add_subdirectory(ch2)
add_subdirectory(ch3)
add_subdirectory(ch4)
