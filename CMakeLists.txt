# requiring cmake version 2.8 will be deprecated
cmake_minimum_required(VERSION 3.12)
project(MM1)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Werror)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MACOSX_RPATH 1)


add_subdirectory(src)

