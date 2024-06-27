cmake_minimum_required(VERSION 3.0.0)
project(MyLibraryManagementSQL VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")
# Add executable target
add_executable(MyLibraryManagementSQL ${SOURCES})