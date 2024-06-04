#include "Controller.h"
#include "../tinyfiledialogs.h"
#include <iostream>

Controller::Controller() : view(model)
{
    view.setMouseCallback([this](int event, int x, int y, int flags, void* userdata)
        { this->handleMouseEvent(event, x, y, flags, userdata); });
    updateView(); 
}
void Controller::handleMouseEvent(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        if (x >= 0 && x < 30 && y >= 0 && y < 30)
        {
            std::cout << "Load image button clicked" << std::endl;
            loadImage();
        }
        else if (x >= 40 && x < 70 && y >= 0 && y < 30)
        {
            std::cout << "Save image button clicked" << std::endl;
            saveImage();
        }
        else if (x >= 0 && x < 30 && y >= 40 && y < 70)
        {
            std::cout << "Toggle gray mode button clicked" << std::endl;
            toggleGrayMode();
        }
        else if (x >= 40 && x < 70 && y >= 40 && y < 70)
        {
            std::cout << "Dilate button clicked" << std::endl;
            dilateImage();
        }
        else if (x >= 80 && x < 110 && y >= 40 && y < 70)
        {
            std::cout << "Erode button clicked" << std::endl;
            erodeImage();
        }
    }
}

void Controller::dilateImage()
{
    model.dilateImage();
    updateView();
}

void Controller::erodeImage()
{
    model.erodeImage();
    updateView();
}
