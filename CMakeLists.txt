cmake_minimum_required(VERSION 3.1.0)
project(main)
include_directories(${CMAKE_SOURCE_DIR}/include)
#find_package(GTest)
add_subdirectory(src)

add_executable(main test.cpp)

target_link_libraries(main filter gtest)