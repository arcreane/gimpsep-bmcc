#include "Controller.h"
#include "../tinyfiledialogs.h"
#include <iostream>

Controller::Controller() : view(model), lowThreshold(100), highThreshold(200), kernelSize(3)
{
    view.setMouseCallback([this](int event, int x, int y, int flags, void *userdata)
                          { this->handleMouseEvent(event, x, y, flags, userdata); });
    updateView();
}

void Controller::handleMouseEvent(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::cout << "Mouse clicked at (" << x << ", " << y << ")" << std::endl;
        const auto& buttonRects = view.getButtonRects();
        if (buttonRects.size() > 0 && buttonRects[0].contains(cv::Point(x, y)))
        {
            loadImage();
        }
        else if (buttonRects.size() > 1 && buttonRects[1].contains(cv::Point(x, y)))
        {
            saveImage();
        }
        else if (buttonRects.size() > 2 && buttonRects[2].contains(cv::Point(x, y)))
        {
            toggleGrayMode();
        }
        else if (buttonRects.size() > 3 && buttonRects[3].contains(cv::Point(x, y)))
        {
            applyLighten();
        }
        else if (buttonRects.size() > 4 && buttonRects[4].contains(cv::Point(x, y)))
        {
            applyDarken();
        }
        else if (buttonRects.size() > 5 && buttonRects[5].contains(cv::Point(x, y)))
        {
            increaseImageSize();
        }
        else if (buttonRects.size() > 6 && buttonRects[6].contains(cv::Point(x, y)))
        {
            decreaseImageSize();
        }
        else if (buttonRects.size() > 7 && buttonRects[7].contains(cv::Point(x, y)))
        {
            erodeOrDilate(true);
        }
        else if (buttonRects.size() > 8 && buttonRects[8].contains(cv::Point(x, y)))
        {
            erodeOrDilate(false);
        }
        else if (buttonRects.size() > 9 && buttonRects[9].contains(cv::Point(x, y)))
        {
            applyCanny();
        }
    }
}

void Controller::loadImage()
{
    const char *filterPatterns[] = {"*.jpg", "*.png"};
    const char *imagePath = tinyfd_openFileDialog("Open Image", "", 2, filterPatterns, NULL, 0);
    if (imagePath)
    {
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
    if (!image.empty())
    {
        cv::Mat grayImage;
        if (image.channels() == 3)
        {
            cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
        }
        else
        {
            grayImage = image.clone();
        }

        if (!grayImage.empty())
        {
            model.setImage(grayImage);
            cv::cvtColor(model.getImage(), grayImage, cv::COLOR_GRAY2BGR);
            model.setImage(grayImage);
            updateView();
        }
        else
        {
            std::cerr << "Error: grayImage is empty after conversion" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Original image is empty" << std::endl;
    }
}

void Controller::increaseImageSize()
{
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        double scaleFactor = 1.1f;
        cv::Mat resizedImage;
        cv::resize(image, resizedImage, cv::Size(), scaleFactor, scaleFactor);
        model.setImage(resizedImage);
        if (!model.isResizeMode())
        {
            model.toggleResizeMode();
        }
        updateView();
    }
}

void Controller::decreaseImageSize()
{
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        double scaleFactor = 0.9f;
        cv::Mat resizedImage;
        cv::resize(image, resizedImage, cv::Size(), scaleFactor, scaleFactor);
        model.setImage(resizedImage);
        if (!model.isResizeMode())
        {
            model.toggleResizeMode();
        }
        updateView();
    }
}

void Controller::applyLighten()
{
    cv::Mat lightenedImage = model.getImage();
    lightenedImage.convertTo(lightenedImage, -1, 1, 50);
    model.setImage(lightenedImage);
    updateView();
}

void Controller::applyDarken()
{
    cv::Mat darkenImage = model.getImage();
    darkenImage.convertTo(darkenImage, -1, 1, -50);
    model.setImage(darkenImage);
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

    if (model.getImage().channels() == 3)
    {
        cv::cvtColor(model.getImage(), grayImage, cv::COLOR_BGR2GRAY);
    }
    else
    {
        grayImage = model.getImage();
    }

    cv::Canny(grayImage, edges, lowThreshold, highThreshold, kernelSize);
    cv::cvtColor(edges, model.getImage(), cv::COLOR_GRAY2BGR);
    updateView();
}

void Controller::erodeOrDilate(bool isErosion)
{
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        cv::Mat result;
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(model.getErosionSize(), model.getErosionSize()));

        if (isErosion)
        {
            cv::erode(image, result, kernel);
        }
        else
        {
            cv::dilate(image, result, kernel);
        }
        model.setImage(result);
        updateView();
    }
}
