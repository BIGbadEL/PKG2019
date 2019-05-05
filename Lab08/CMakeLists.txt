cmake_minimum_required(VERSION 3.14)
project(Lab08)

set(CMAKE_CXX_STANDARD 17)
find_package(wxWidgets 3.0.4 REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(Lab08 main.cpp CImg.h GUIMyFrame1.h GUIMyFrame1.cpp GUI.h GUI.cpp FreeImage.h)

target_link_libraries(Lab08 ${wxWidgets_LIBRARIES} X11 freeimage)
