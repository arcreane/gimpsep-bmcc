#ifndef VIEW_H
#define VIEW_H

#include <opencv2/opencv.hpp>
#include <functional>
#include "../model/ImageModel.h"

class View
{
public:
    View(ImageModel &model);
    void setMouseCallback(std::function<void(int, int, int, int, void *)> callback);
    void update();
    void drawButtons(const std::vector<std::string>& buttonNames);

private:
    ImageModel &model;
    cv::Mat canvas;
    std::string buttonText;
    std::string winName;
    std::function<void(int, int, int, int, void *)> mouseCallback; // Store the callback
    void createGUI();
    static void onMouse(int event, int x, int y, int flags, void *userdata); // Static function for OpenCV callback
};

#endif // VIEW_H
