cmake_minimum_required(VERSION 3.20)
project(MDNF VERSION 1.0.0 LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
qt_add_executable(MDNF
    source/main.cpp
    source/Back.hpp
    source/Back.cpp
    source/Front.hpp
    source/Front.cpp
)
target_link_libraries(MDNF PRIVATE Qt6::Widgets)