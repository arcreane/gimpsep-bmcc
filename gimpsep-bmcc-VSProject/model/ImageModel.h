#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <opencv2/opencv.hpp>
#include <string>

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

private:
    cv::Mat colorImage;
    cv::Mat grayImage;
    bool grayMode;
    bool resizeMode;
};

#endif // IMAGEMODEL_H
