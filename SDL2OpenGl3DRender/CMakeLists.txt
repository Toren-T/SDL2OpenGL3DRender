cmake_minimum_required(VERSION 3.5)

project(SDL2OpenGl3DRender LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

