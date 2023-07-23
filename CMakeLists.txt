cmake_minimum_required(VERSION 3.5)

project(07.homework)

find_package(GTest)

include_directories(headers test)

add_executable(my_containers
main.cpp)

set_target_properties(my_containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(container_tests
test/container_tests.cpp
)

target_include_directories(container_tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(container_tests ${GTEST_BOTH_LIBRARIES})
target_include_directories(container_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/headers")

message(STATUS ${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_BOTH_LIBRARIES})


set_target_properties(container_tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)