cmake_minimum_required(VERSION 3.0.0)
project(Hex VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

add_executable(Hex main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ts2_input.txt
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
