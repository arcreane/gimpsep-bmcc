cmake_minimum_required(VERSION 3.0)
project(gimpsep-bmcc)

find_package(OpenCV REQUIRED)

add_executable(gimpsep-bmcc main.cpp)
target_link_libraries(gimpsep-bmcc ${OpenCV_LIBS})