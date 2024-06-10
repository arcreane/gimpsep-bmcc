cmake_minimum_required(VERSION 3.10)
project(gimpsep-bmcc)

set(CMAKE_CXX_STANDARD 11)

# Ajoutez ici les répertoires contenant vos fichiers d'en-tête
include_directories(
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/view
    ${CMAKE_SOURCE_DIR}/controller
)

# Ajoutez les fichiers sources
add_executable(gimpsep-bmcc
    main.cpp
    controller/Controller.cpp
    view/View.cpp
    model/ImageModel.cpp
    tinyfiledialogs.c

)

# Trouver et lier OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(gimpsep-bmcc ${OpenCV_LIBS})
