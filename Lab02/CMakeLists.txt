cmake_minimum_required(VERSION 3.12.1)
project(App)

set(CMAKE_CXX_STANDARD 17)

add_compile_options( -Ofast
#        -pedantic -MMD -MP -Wall -g -Wextra
#        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
#        -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion
#        -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond
#        -Wduplicated-branches -Wlogical-op -Wuseless-cast
        )

add_executable(App lab02.cpp Menu.h window.h circle.h colors.h slider.h)

target_link_libraries(App sfml-graphics sfml-window sfml-system)
