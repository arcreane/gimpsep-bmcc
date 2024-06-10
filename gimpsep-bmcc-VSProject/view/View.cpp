#include "View.h"
#include <opencv2/opencv.hpp>
#include <iostream>

View::View(ImageModel& model) : model(model), buttonText("Gris"), winName("GIMProvise"), scaleFactor(1.0f)
{
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
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

    for (size_t i = 0; i < buttonNames.size(); ++i) {
        int x = (i % 2) * (buttonSize + buttonSpacing);
        int y = (i / 2) * (buttonSize / 2 + buttonSpacing);
        cv::Rect buttonRect(x, y, buttonSize, buttonSize / 2);
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

    std::vector<std::string> buttonNames = {"File", "Save", "Size+", "Size-", "Gris" , "erode", "dilate"};
    if (!model.isGrayMode()) {
        buttonNames.push_back("+Canny");
    }
    drawButtons(buttonNames);

    // Display image if loaded
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        cv::Mat resizedImage;
        double aspectRatio = static_cast<double>(image.cols) / image.rows;
        int newWidth = static_cast<int>(image.cols);
        int newHeight = static_cast<int>(image.rows);
        
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
        if (model.isGrayMode())
        {
            cv::cvtColor(resizedImage, resizedImage, cv::COLOR_GRAY2BGR);
        }

        // Center the resized image on the canvas
        int offsetX = (canvasWidth - resizedImage.cols) / 2;
        int offsetY = (canvasHeight - resizedImage.rows) / 2;

        // Ensure the offset values are non-negative
        offsetX = std::max(0, offsetX);
        offsetY = std::max(0, offsetY);

        // Ensure the types match before copying
        if (resizedImage.type() == canvas.type()) {
            resizedImage.copyTo(canvas(cv::Rect(offsetX, offsetY, resizedImage.cols, resizedImage.rows)));
        } else {
            std::cerr << "Type mismatch between resizedImage and canvas" << std::endl;
        }
    }
}
