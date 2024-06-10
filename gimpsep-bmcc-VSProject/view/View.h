#ifndef VIEW_H
#define VIEW_H

#include <opencv2/opencv.hpp>
#include <functional>
#include <vector>
#include "../model/ImageModel.h"

class View
{
public:
    View(ImageModel &model);
    void setMouseCallback(std::function<void(int, int, int, int, void *)> callback);
    void update();
    void drawButtons(const std::vector<std::string>& buttonNames);
    const std::vector<cv::Rect>& getButtonRects() const { return buttonRects; } // Getter for buttonRects

private:
    ImageModel &model;
    cv::Mat canvas;
    std::float_t scaleFactor;
    std::string buttonText;
    std::string winName;
    std::function<void(int, int, int, int, void *)> mouseCallback; // Store the callback
    std::vector<cv::Rect> buttonRects; // Store button positions
    void createGUI();
    static void onMouse(int event, int x, int y, int flags, void *userdata); // Static function for OpenCV callback
};

#endif // VIEW_H
