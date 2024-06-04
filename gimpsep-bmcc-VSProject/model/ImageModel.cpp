#include "ImageModel.h"

ImageModel::ImageModel() : grayMode(false) {}

void ImageModel::loadImage(const std::string &path)
{
    colorImage = cv::imread(path);
    if (!colorImage.empty())
    {
        cv::cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);
    }
}

void ImageModel::toggleGrayMode()
{
    grayMode = !grayMode;
}

bool ImageModel::isGrayMode() const
{
    return grayMode;
}

cv::Mat ImageModel::getImage() const
{
    if (grayMode && !grayImage.empty())
    {
        return grayImage;
    }
    return colorImage;
}
