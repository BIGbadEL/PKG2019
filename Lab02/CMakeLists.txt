cmake_minimum_required(VERSION 3.13)
project(App)

set(CMAKE_CXX_STANDARD 17)

add_executable(App lab02.cpp Menu.h window.h circle.h)

target_link_libraries(App sfml-graphics sfml-window sfml-system)
