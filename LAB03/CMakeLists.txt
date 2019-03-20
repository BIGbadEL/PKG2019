cmake_minimum_required(VERSION 3.13)
project(LAB03)

set(CMAKE_CXX_STANDARD 17)

add_executable(LAB03 main.cpp app.h frame.h)

add_definitions(-D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__)
target_link_libraries(LAB03 pthread
        wx_gtk2u_xrc-3.0 wx_gtk2u_qa-3.0
        wx_gtk2u_html-3.0 wx_gtk2u_adv-3.0
        wx_gtk2u_core-3.0 wx_baseu_xml-3.0
        wx_baseu_net-3.0 wx_baseu-3.0
        )

link_directories(
        /usr/lib/x86_64-linux-gnu/wx/include/gtk2-unicode-3.0
        /usr/include/wx-3.0
        /usr/lib/x86_64-linux-gnu
        )

