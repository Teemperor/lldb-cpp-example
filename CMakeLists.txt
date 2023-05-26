cmake_minimum_required (VERSION 3.10)
project (LLDBExample)

set(CMAKE_CXX_STANDARD 17)

set(BINARY_NAME ${CMAKE_PROJECT_NAME})
enable_testing()

add_subdirectory (src)
add_subdirectory (test)
