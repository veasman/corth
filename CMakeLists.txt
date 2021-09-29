cmake_minimum_required(VERSION 3.21.2)
project(corth VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

add_executable(corth "src/main.cpp" "src/lexer.cpp" "src/position.cpp")
