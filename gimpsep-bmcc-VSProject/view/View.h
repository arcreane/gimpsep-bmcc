#ifndef VIEW_H
#define VIEW_H

#include <opencv2/opencv.hpp>
#include <functional>
#include <vector>
#include "../model/ImageModel.h"

class View {
public:
    View(ImageModel& model);
    void setMouseCallback(std::function<void(int, int, int, int, void*)> callback);
    void update();
    const std::vector<cv::Rect>& getButtonRects() const { return buttonRects; }

private:
    static void onMouse(int event, int x, int y, int flags, void* userdata);
    static void onErosionSizeChange(int, void* userdata);
    void drawButtons(const std::vector<std::string>& buttonNames);
    void createGUI();

    ImageModel& model;
    std::string winName;
    std::string buttonText;
    float scaleFactor;
    int erosionSize = 1;
    std::vector<cv::Rect> buttonRects;
    cv::Mat3b canvas;
    std::function<void(int, int, int, int, void*)> mouseCallback;
};

#endif // VIEW_H
