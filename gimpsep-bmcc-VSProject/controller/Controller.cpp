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
        int buttonSize = 70;
        int buttonSpacing = 10;
        
        // Calculate button index based on x and y coordinates
        int col = x / (buttonSize + buttonSpacing);
        int row = y / (buttonSize / 2 + buttonSpacing);
        int buttonIndex = row * 2 + col;

        switch (buttonIndex)
        {
        case 0:
            std::cout << "Load image button clicked" << std::endl;
            loadImage();
            break;
        case 1:
            std::cout << "Save image button clicked" << std::endl;
            saveImage();
            break;
        case 2:
            std::cout << "Toggle gray mode button clicked" << std::endl;
            toggleGrayMode();
            break;
        case 3:
            std::cout << "Increase Canny threshold button clicked" << std::endl;
            applyCanny();
            break;
        default:
            break;
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

