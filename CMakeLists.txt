cmake_minimum_required(VERSION 3.5)

project(07.homework)

include_directories(headers)

add_executable(my_containers
main.cpp)
set_target_properties(my_containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)