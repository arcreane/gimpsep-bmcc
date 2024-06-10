#include "View.h"
#include <opencv2/opencv.hpp>
#include <iostream>

View::View(ImageModel& model) : model(model), buttonText("Gris"), winName("GIMProvise"), scaleFactor(1.0f)
{
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Erosion Size", winName, &erosionSize, 15, onErosionSizeChange, this);
    createGUI();
}

void View::setMouseCallback(std::function<void(int, int, int, int, void*)> callback)
{
    mouseCallback = callback;                     // Store the callback
    cv::setMouseCallback(winName, onMouse, this); // Pass 'this' pointer as userdata
}

void View::onMouse(int event, int x, int y, int flags, void* userdata)
{
    View* self = static_cast<View*>(userdata);
    if (self->mouseCallback)
    {
        self->mouseCallback(event, x, y, flags, userdata);
    }

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        int buttonSize = 30;
        int buttonSpacing = 10;
        cv::Rect increaseButtonRect(buttonSize + 2 * buttonSpacing, 0, buttonSize, buttonSize);
    }
}


void View::update()
{
    createGUI();
    cv::imshow(winName, canvas);
    cv::waitKey(1); // Ensure the window is updated
}

void View::drawButtons(const std::vector<std::string>& buttonNames) {
    int buttonSize = 70;
    int buttonSpacing = 10; // Space between buttons
    buttonRects.clear(); // Clear previous button positions

    for (size_t i = 0; i < buttonNames.size(); ++i) {
        int x = (i % 2) * (buttonSize + buttonSpacing);
        int y = (i / 2) * (buttonSize / 2 + buttonSpacing);
        cv::Rect buttonRect(x, y, buttonSize, buttonSize / 2);
        buttonRects.push_back(buttonRect); // Store button position
        cv::rectangle(canvas, buttonRect, cv::Scalar(200, 200, 200), cv::FILLED);
        cv::putText(canvas, buttonNames[i], cv::Point(x + buttonSize * 0.1, y + buttonSize / 2 * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));
    }
}

void View::createGUI()
{
    int buttonSize = 70;
    int buttonSpacing = 10; // Space between buttons
    int canvasWidth = 1400;
    int canvasHeight = 1000;
    canvas = cv::Mat3b(canvasHeight, canvasWidth, cv::Vec3b(0, 0, 0));


    std::vector<std::string> buttonNames = {"File"};

    // Display image if loaded
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        buttonNames.push_back("Save");
        buttonNames.push_back("Gris");
        buttonNames.push_back("Lighten");
        buttonNames.push_back("Darken");
        buttonNames.push_back("Size+");
        buttonNames.push_back("Size-");
        buttonNames.push_back("erode");
        buttonNames.push_back("dilate");
        if (!model.isGrayMode()) {
            buttonNames.push_back("+Canny");
        }
        drawButtons(buttonNames);

        cv::Mat resizedImage;
        double aspectRatio = static_cast<double>(image.cols) / image.rows;
        int newWidth = static_cast<int>(image.cols);
        int newHeight = static_cast<int>(image.rows);
        if (!model.isResizeMode()) {
            std::cout << "new Width : " << newWidth << std::endl;
            // Adjust new width and height to maintain aspect ratio
            if (canvasWidth - 200 < (canvasHeight - 200) * aspectRatio)
            {
                newWidth = canvasWidth - 200;
                newHeight = static_cast<int>(newWidth / aspectRatio);
            }
            else
            {
                newHeight = canvasHeight - 200;
                newWidth = static_cast<int>(newHeight * aspectRatio);
            }

            cv::resize(image, resizedImage, cv::Size(newWidth, newHeight));

            // Center the resized image on the canvas
            int offsetX = (canvasWidth - resizedImage.cols) / 2;
            int offsetY = (canvasHeight - resizedImage.rows) / 2;

            // Ensure the offset values are non-negative
            offsetX = std::max(0, offsetX);
            offsetY = std::max(0, offsetY);

            std::cout << "Image type" << resizedImage.type() << std::endl;
            std::cout << "Canvas type" << canvas.type() << std::endl;
            // Ensure the types match before copying
            if (resizedImage.type() == canvas.type()) {
                resizedImage.copyTo(canvas(cv::Rect(offsetX, offsetY, resizedImage.cols, resizedImage.rows)));
            }
            else {
                std::cerr << "Type mismatch between resizedImage and canvas" << std::endl;
            }
        }

        int offsetX = (canvasWidth - image.cols) / 2;
        int offsetY = (canvasHeight - image.rows) / 2;

        offsetX = std::max(0, offsetX);
        offsetY = std::max(0, offsetY);

        std::cout << "Image type" << image.type() << std::endl;
        std::cout << "Canvas type" << canvas.type() << std::endl;
        if (image.type() == canvas.type()) {
            image.copyTo(canvas(cv::Rect(offsetX, offsetY, image.cols, image.rows)));
        }
        else {
            std::cerr << "Type mismatch between resizedImage and canvas" << std::endl;
        }
    } else {
        drawButtons(buttonNames);
    }
}

void View::onErosionSizeChange(int, void* userdata)
{
    View* self = static_cast<View*>(userdata);
    self->erosionSize = std::max(1, self->erosionSize); // Ensure size is at least 1
    self->model.setErosionSize(self->erosionSize);
}
