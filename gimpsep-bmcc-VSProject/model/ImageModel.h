#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <opencv2/opencv.hpp>
#include <string>


class ImageModel
{
public:
    ImageModel();
    void loadImage(const std::string& path);
    void toggleGrayMode();
    bool isGrayMode() const;
    cv::Mat getImage() const;
    void dilateImage();
    void erodeImage();  

private:
    cv::Mat colorImage;
    cv::Mat grayImage;
    bool grayMode;
};

#endif // IMAGEMODEL_H
