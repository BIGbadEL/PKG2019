cmake_minimum_required(VERSION 3.12)
project(lab04)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets 3.0.4 REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(lab04 main.cpp
        GUI.cpp GUI.h
        GUIMyFrame1.cpp GUIMyFrame1.h
        image.h
        )

target_link_libraries(lab04 ${wxWidgets_LIBRARIES})

configure_file(mask.png  mask.png COPYONLY)
configure_file(test.jpg  test.jpg COPYONLY)
