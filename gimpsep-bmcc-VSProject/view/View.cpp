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
    mouseCallback = callback;                     // Store the callback
    cv::setMouseCallback(winName, onMouse, this); // Pass 'this' pointer as userdata
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
    cv::waitKey(1); // Ensure the window is updated
}

void View::createGUI()
{
    int buttonSize = 30;
    int canvasWidth = 1400;
    canvas = cv::Mat3b(1000, canvasWidth, cv::Vec3b(0, 0, 0));

    // Draw buttons
    cv::Rect buttonRect(0, 0, buttonSize, buttonSize);
    cv::rectangle(canvas, buttonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, buttonText, cv::Point(buttonSize * 0.1, buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    cv::Rect fileButtonRect(30, 0, buttonSize, buttonSize);
    cv::rectangle(canvas, fileButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "File", cv::Point(30 + buttonSize * 0.1, buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    // Display image if loaded
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        cv::Mat resizedImage;
        cv::resize(image, resizedImage, cv::Size(800, 800));
        if (model.isGrayMode())
        {
            cv::cvtColor(resizedImage, resizedImage, cv::COLOR_GRAY2BGR);
        }
        resizedImage.copyTo(canvas(cv::Rect((canvasWidth - resizedImage.cols) / 2, (canvas.rows - resizedImage.rows) / 2, resizedImage.cols, resizedImage.rows)));
    }
}
