cmake_minimum_required(VERSION 3.14)
project(Lab07)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets 3.0.4 REQUIRED)
include(${wxWidgets_USE_FILE})


add_executable(Lab07
        draw_map.cpp
        GUI.cpp
        GUI.h
        GUIMyFrame1.cpp
        GUIMyFrame1.h
        main.cpp)

target_link_libraries(Lab07 ${wxWidgets_LIBRARIES})
