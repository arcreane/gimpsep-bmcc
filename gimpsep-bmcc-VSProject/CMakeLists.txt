cmake_minimum_required(VERSION 3.0)
project(gimpsep-bmcc)

find_package(OpenCV REQUIRED)

add_executable(gimpsep-bmcc 
    main.cpp 
    controller/Controller.cpp 
    model/ImageModel.cpp 
    view/View.cpp
    tinyfiledialogs.c
)
target_link_libraries(gimpsep-bmcc ${OpenCV_LIBS})