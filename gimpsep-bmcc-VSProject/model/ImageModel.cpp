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
        @@ - 29, 38 + 17, 27 @@ void Controller::handleMouseEvent(int event, int x, int y, int flags, void* user
            std::cout << "Toggle gray mode button clicked" << std::endl;
    toggleGrayMode();
}
    }
}

void Controller::loadImage()
{
    const char* filterPatterns[] = { "*.jpg", "*.png" };                                           
    const char* imagePath = tinyfd_openFileDialog("Open Image", "", 2, filterPatterns, NULL, 0); 
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

void Controller::saveImage()
{
    cv::Mat image = model.getImage();
    imwrite("output.jpg", image);
}

void Controller::updateView()
{
    view.update();
}

void Controller::dilateImage()
{
    if (!colorImage.empty())
    {
        cv::dilate(colorImage, colorImage, cv::Mat());
        if (grayMode)
        {
            cv::dilate(grayImage, grayImage, cv::Mat());
        }
    }
}

void Controller::erodeImage()
{
    if (!colorImage.empty())
    {
        cv::erode(colorImage, colorImage, cv::Mat());
        if (grayMode)
        {
            cv::erode(grayImage, grayImage, cv::Mat());
        }
    }
}
