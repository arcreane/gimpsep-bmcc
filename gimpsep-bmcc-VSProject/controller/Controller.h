#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../view/View.h"
#include "../model/ImageModel.h"

class Controller
{
public:
    Controller();

private:
    void handleMouseEvent(int event, int x, int y, int flags, void *userdata);
    void loadImage();
    void toggleGrayMode();
    void saveImage();
    void updateView();
    void applyCanny();
    void erodeOrDilate(bool isErosion);
    void increaseImageSize();
    void decreaseImageSize();
    void applyLighten();
    void applyDarken();
    void addImageToRight();
    void undo();

    ImageModel model;
    View view;

    // New Canny threshold variables
    int kernelSize;
    int lowThreshold = 100;
    int highThreshold = 200;
};

#endif // CONTROLLER_H
