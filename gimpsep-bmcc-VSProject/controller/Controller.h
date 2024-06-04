#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <opencv2/opencv.hpp>
#include "../model/ImageModel.h"
#include "../view/View.h"

class Controller
{
public:
    Controller();
    void handleMouseEvent(int event, int x, int y, int flags, void *userdata);
    void loadImage();
    void toggleGrayMode();
    void saveImage();

private:
    ImageModel model;
    View view;
    void updateView();
};

#endif // CONTROLLER_H
