#include "Controller.h"
#include "../tinyfiledialogs.h"
#include <iostream>

Controller::Controller() : view(model)
{
    // Set the mouse callback
    view.setMouseCallback([this](int event, int x, int y, int flags, void *userdata)
                          { this->handleMouseEvent(event, x, y, flags, userdata); });
    updateView(); // Initial update
}

void Controller::handleMouseEvent(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (x < 30 && y < 30)
        {
            std::cout << "Toggle gray mode button clicked" << std::endl;
            toggleGrayMode();
        }
        else if (x < 60 && y < 30)
        {
            std::cout << "Load image button clicked" << std::endl;
            loadImage();
        }
    }
}

void Controller::loadImage()
{
    const char *filterPatterns[] = {"*.jpg", "*.png"};                                           // Séparez les filtres par des virgules
    const char *imagePath = tinyfd_openFileDialog("Open Image", "", 2, filterPatterns, NULL, 0); // Le 2 indique le nombre de motifs de filtre
    if (imagePath)
    {
        std::cout << "Image loaded: " << imagePath << std::endl;
        model.loadImage(imagePath);
        updateView();
    }
    else
    {
        std::cout << "No image selected" << std::endl;
    }
}

void Controller::toggleGrayMode()
{
    model.toggleGrayMode();
    updateView();
}

void Controller::updateView()
{
    view.update();
}
