#include "View.h"
#include <opencv2/opencv.hpp>
#include <iostream>

View::View(ImageModel &model) : model(model), buttonText("Gris"), winName("GIMProvise")
{
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    createGUI();
}

void View::setMouseCallback(std::function<void(int, int, int, int, void *)> callback)
{
    mouseCallback = callback;                  
    cv::setMouseCallback(winName, onMouse, this); 
}

void View::onMouse(int event, int x, int y, int flags, void *userdata)
{
    View *self = static_cast<View *>(userdata);
    if (self->mouseCallback)
    {
        self->mouseCallback(event, x, y, flags, userdata);
    }
}

void View::update()
{
    createGUI();
    cv::imshow(winName, canvas);
    cv::waitKey(1); 
}

void View::createGUI()
{
    int buttonSize = 30;
    int buttonSpacing = 10;
    int canvasWidth = 1400;
    int canvasHeight = 1000;
    canvas = cv::Mat3b(canvasHeight, canvasWidth, cv::Vec3b(0, 0, 0));

    // Draw buttons
    cv::Rect fileButtonRect(0, 0, buttonSize, buttonSize);
    cv::rectangle(canvas, fileButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "File", cv::Point(buttonSize * 0.1, buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    cv::Rect saveButtonRect(buttonSize + buttonSpacing, 0, buttonSize, buttonSize);
    cv::rectangle(canvas, saveButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "Save", cv::Point((buttonSize + buttonSpacing) + buttonSize * 0.1, buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    cv::Rect grayButtonRect(0, buttonSize + buttonSpacing, buttonSize, buttonSize);
    cv::rectangle(canvas, grayButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "Gris", cv::Point(buttonSize * 0.1, (buttonSize + buttonSpacing) + buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        cv::Mat resizedImage;
        double aspectRatio = static_cast<double>(image.cols) / image.rows;
        int newWidth, newHeight;

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

        int offsetX = (canvasWidth - resizedImage.cols) / 2;
        int offsetY = (canvasHeight - resizedImage.rows) / 2;

        offsetX = std::max(0, offsetX);
        offsetY = std::max(0, offsetY);

        resizedImage.copyTo(canvas(cv::Rect(offsetX, offsetY, resizedImage.cols, resizedImage.rows)));
    }
}
