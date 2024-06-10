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
            std::cout << "Lighten button clicked" << std::endl;
            applyLighten();
        }
        else if (buttonRects.size() > 4 && buttonRects[4].contains(cv::Point(x, y)))
        {
            std::cout << "Darken button clicked" << std::endl;
            applyDarken();
        }
        else if (buttonRects.size() > 5 && buttonRects[5].contains(cv::Point(x, y)))
        {
            std::cout << "Size + mode button clicked" << std::endl;
            increaseImageSize();
        }
        else if (buttonRects.size() > 6 && buttonRects[6].contains(cv::Point(x, y)))
        {
            std::cout << "Size - mode button clicked" << std::endl;
                decreaseImageSize();
        }
        else if (buttonRects.size() > 7 && buttonRects[7].contains(cv::Point(x, y)))
        {
            std::cout << "Erode threshold button clicked" << std::endl;
                erodeOrDilate(true);
        }
        else if (buttonRects.size() > 8 && buttonRects[8].contains(cv::Point(x, y)))
        {
            std::cout << "Dilate threshold button clicked" << std::endl;
            erodeOrDilate(false);
        }
        else if (buttonRects.size() > 9 && buttonRects[9].contains(cv::Point(x, y)))
        {
            std::cout << "Create a Panorama" << std::endl;
            addImageToRight();
        }
        else if (buttonRects.size() > 10 && buttonRects[10].contains(cv::Point(x, y)))
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
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        cv::Mat grayImage;
        // Convert to grayscale if the image is not already in grayscale
        // deprecated, because the image is always passed on BGR after the operation to be printed on the canvas
        if (image.channels() == 3)
        {
            cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
            std::cout << "Converted to grayscale, channels: " << grayImage.channels() << std::endl;
        }
        else
        {
            grayImage = image.clone();  // Ensure we have a proper clone of the grayscale image
            std::cout << "Image is already grayscale, channels: " << grayImage.channels() << std::endl;
        }

        if (!grayImage.empty())
        {
            model.setImage(grayImage);
            // To give image the same type as canvas to print it
            cv::cvtColor(model.getImage(), grayImage, cv::COLOR_GRAY2BGR);
            model.setImage(grayImage);
            std::cout << "Image type after gray conversion: " << model.getImage().type() << std::endl;
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
    if (!image.empty()) {
        // Diminue la taille de l'image par exemple en divisant la largeur et la hauteur par un facteur
        double scaleFactor = 1.1f; // Facteur de réduction par exemple
        cv::Mat resizedImage;
        cv::resize(image, resizedImage, cv::Size(), scaleFactor, scaleFactor);
        image = resizedImage;
        model.setImage(resizedImage);
        if (!model.isResizeMode()) {
            model.toggleResizeMode();
        }
        updateView(); // Met à jour la vue avec la nouvelle image
    }
}

void Controller::decreaseImageSize() {
    cv::Mat image = model.getImage();
    if (!image.empty()) {
        // Diminue la taille de l'image par exemple en divisant la largeur et la hauteur par un facteur
        double scaleFactor = 0.9f; // Facteur de réduction par exemple
        cv::Mat resizedImage;
        cv::resize(image, resizedImage, cv::Size(), scaleFactor, scaleFactor);
        image = resizedImage;
        std::cout << "Image type after resize" << resizedImage.type() << std::endl;
        model.setImage(resizedImage);
        std::cout << "Image type after save" << model.getImage().type() << std::endl;
        if (!model.isResizeMode()) {
            model.toggleResizeMode();
        }
        std::cout << "new Width : " << static_cast<int>(model.getImage().cols) << std::endl;
        updateView(); // Met à jour la vue avec la nouvelle image
    }
}

void Controller::applyLighten()
{
    cv::Mat lightenedImage = model.getImage();
    lightenedImage.convertTo(lightenedImage, -1, 1, 50); // Increase brightness
    updateView();
}

void Controller::applyDarken()
{
    cv::Mat darkenImage = model.getImage();
    darkenImage.convertTo(darkenImage, -1, 1, - 50); // Increase brightness
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

void Controller::addImageToRight()
{
    const char* filterPatterns[] = { "*.jpg", "*.png" };                                           // Séparez les filtres par des virgules
    const char* imagePath = tinyfd_openFileDialog("Open Image", "", 2, filterPatterns, NULL, 0); // Le 2 indique le nombre de motifs de filtre
    if (imagePath)
    {
        std::cout << "Image loaded for panorama: " << imagePath << std::endl;
        cv::Mat newImage = cv::imread(imagePath);
        if (newImage.empty())
        {
            std::cout << "Error loading image" << std::endl;
            return;
        }

        cv::Mat existingImage = model.getImage();
        if (existingImage.empty())
        {
            std::cout << "No existing image to append to" << std::endl;
            return;
        }

        // Assure que les deux images ont la même hauteur
        if (existingImage.rows != newImage.rows)
        {
            cv::resize(newImage, newImage, cv::Size(newImage.cols, existingImage.rows));
        }

        cv::Mat combinedImage(cv::Size(existingImage.cols + newImage.cols, existingImage.rows), existingImage.type());
        existingImage.copyTo(combinedImage(cv::Rect(0, 0, existingImage.cols, existingImage.rows)));
        newImage.copyTo(combinedImage(cv::Rect(existingImage.cols, 0, newImage.cols, newImage.rows)));

        model.setImage(combinedImage);
        updateView();
    }
    else
    {
        std::cout << "No image selected for panorama" << std::endl;
    }
}

