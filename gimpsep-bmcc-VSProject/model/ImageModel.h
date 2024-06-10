#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <opencv2/opencv.hpp>
#include <stack>

class ImageModel
{
public:
    ImageModel();
    void loadImage(const std::string &path);
    void toggleGrayMode();
    void toggleResizeMode();
    bool isGrayMode() const;
    bool isResizeMode() const;
    cv::Mat getImage() const;
    void setImage(const cv::Mat& image);
    void saveState();
    void undo();
    int getStackSize() const;
    int getErosionSize() const;
    void setErosionSize(int size);

private:
    cv::Mat colorImage;
    cv::Mat grayImage;
    bool grayMode;
    bool resizeMode;
    std::stack<cv::Mat> imageHistory; 
    int erosionSize;
};

#endif // IMAGEMODEL_H
