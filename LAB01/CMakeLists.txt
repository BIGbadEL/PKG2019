cmake_minimum_required(VERSION 3.13)
project(App)

set(CMAKE_CXX_STANDARD 17)

add_executable(App lab01.cpp menu.h window.h "draw_shapes.h")

target_link_libraries(App sfml-graphics sfml-window sfml-system)