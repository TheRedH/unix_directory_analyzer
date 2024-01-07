cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
project(unix_directory_analyzer VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(unix_directory_analyzer main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
