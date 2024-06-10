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
            std::cout << "Size + mode button clicked" << std::endl;
            decreaseImageSize();
            break;
        case 3:
            std::cout << "Size - mode button clicked" << std::endl;
            increaseImageSize();
            break;
        case 4:
            std::cout << "Toggle gray mode button clicked" << std::endl;
            toggleGrayMode();
            break;
        case 5:
            std::cout << "Erode threshold button clicked" << std::endl;
            erodeOrDilate(true, 10);
            break;
        case 6:
            std::cout << "dilate threshold button clicked" << std::endl;
            erodeOrDilate(false, 10);
            break;
        case 7:
            std::cout << "Undo button clicked" << std::endl;
            undo();
            break;
        case 8:
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

    cv::Mat image = model.getImage();
    if (!image.empty()) {
        cv::Mat grayImage;
        // Convert to grayscale if the image is not already in grayscale
        if (image.channels() == 3) {
            cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
            std::cout << "image" << image<< std::endl;
            model.setImage(grayImage);
        }
        else {
            grayImage = model.getImage();
        }
        updateView();
    }
}

void Controller::increaseImageSize()
{
    cv::Mat image = model.getImage();
    if (!image.empty()) {
        model.saveState(); // Save the current state before modifying
        double scaleFactor = 1.1f;
        cv::Mat resizedImage;
        cv::resize(image, resizedImage, cv::Size(), scaleFactor, scaleFactor);
        model.setImage(resizedImage);
        if (!model.isResizeMode()) {
            model.toggleResizeMode();
        }
        updateView();
    }
}

void Controller::decreaseImageSize()
{
    cv::Mat image = model.getImage();
    if (!image.empty()) {
        model.saveState(); // Save the current state before modifying
        double scaleFactor = 0.9f;
        cv::Mat resizedImage;
        cv::resize(image, resizedImage, cv::Size(), scaleFactor, scaleFactor);
        model.setImage(resizedImage);
        if (!model.isResizeMode()) {
            model.toggleResizeMode();
        }
        updateView();
    }
}

void Controller::applyCanny()
{
    cv::Mat grayImage, edges;
    if (model.getImage().channels() == 3) {
        cv::cvtColor(model.getImage(), grayImage, cv::COLOR_BGR2GRAY);
    } else {
        grayImage = model.getImage();
    }
    model.saveState(); // Save the current state before modifying
    cv::Canny(grayImage, edges, lowThreshold, highThreshold, kernelSize);
    cv::cvtColor(edges, model.getImage(), cv::COLOR_GRAY2BGR);
    updateView();
}

void Controller::erodeOrDilate(bool isErosion, int size)
{
    cv::Mat image = model.getImage();
    if (!image.empty()) {
        model.saveState(); // Save the current state before modifying
        cv::Mat result;
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size));
        if (isErosion) {
            cv::erode(image, result, kernel);
        } else {
            cv::dilate(image, result, kernel);
        }
        model.setImage(result);
        updateView();
    }
}

void Controller::undo()
{
    model.undo();
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
