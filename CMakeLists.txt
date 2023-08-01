cmake_minimum_required(VERSION 3.13)

project(RANSAC_TEST)

# set(CMAKE_CXX_STANDARD 14)

find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})

add_executable(RANSAC_TEST ransac_test.cpp)

target_link_libraries(RANSAC_TEST ${PCL_LIBRARIES})
