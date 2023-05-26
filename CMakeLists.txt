cmake_minimum_required (VERSION 3.10)
project (LLDBExample)

set(CMAKE_CXX_STANDARD 17)

set(LLDB_VERSION "" CACHE STRING "The LLDB version to build/link against.")
if (NOT LLDB_VERSION STREQUAL "")
    set(LLDB_VERSION_SUFFIX "-${LLDB_VERSION}")
else()
    set(LLDB_VERSION_SUFFIX "")
endif()

set(BINARY_NAME ${CMAKE_PROJECT_NAME})
enable_testing()

add_subdirectory (src)
add_subdirectory (test)
