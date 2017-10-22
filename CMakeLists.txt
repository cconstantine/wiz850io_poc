
cmake_minimum_required(VERSION 3.0)
project(wiz850io_poc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(main main.cpp )
target_link_libraries(main pthread )


