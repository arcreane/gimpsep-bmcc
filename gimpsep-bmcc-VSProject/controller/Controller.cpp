#include "Controller.h"
#include "../tinyfiledialogs.h"
#include <iostream>

Controller::Controller() : view(model), lowThreshold(100), highThreshold(200), kernelSize(3)
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
        std::cout << "Mouse clicked at (" << x << ", " << y << ")" << std::endl;
        const auto& buttonRects = view.getButtonRects();
        if (buttonRects.size() > 0 && buttonRects[0].contains(cv::Point(x, y)))
        {
            std::cout << "Load image button clicked" << std::endl;
            loadImage();
        }
        else if (buttonRects.size() > 1 && buttonRects[1].contains(cv::Point(x, y)))
        {
            std::cout << "Save image button clicked" << std::endl;
            saveImage();
        }
        else if (buttonRects.size() > 2 && buttonRects[2].contains(cv::Point(x, y)))
        {
            std::cout << "Toggle gray mode button clicked" << std::endl;
            toggleGrayMode();
        }
        else if (buttonRects.size() > 3 && buttonRects[3].contains(cv::Point(x, y)))
        {
            std::cout << "Increase Canny threshold button clicked" << std::endl;
            applyCanny();
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

void Controller::saveImage()
{
    cv::Mat image = model.getImage();
    imwrite("output.jpg", image);
}

void Controller::updateView()
{
    view.update();
}

void Controller::applyCanny()
{
    cv::Mat grayImage, edges;

    // Convert to grayscale if the image is not already in grayscale
    if (model.getImage().channels() == 3) {
        cv::cvtColor(model.getImage(), grayImage, cv::COLOR_BGR2GRAY);
    } else {
        grayImage = model.getImage();
    }

    // Apply Canny edge detection
    cv::Canny(grayImage, edges, lowThreshold, highThreshold, kernelSize);

    // Convert edges to BGR format to display in color image
    cv::cvtColor(edges, model.getImage(), cv::COLOR_GRAY2BGR);
    updateView();
}
