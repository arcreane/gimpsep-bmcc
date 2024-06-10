#include "ImageModel.h"

ImageModel::ImageModel() : grayMode(false), resizeMode(false) {}

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

void ImageModel::toggleResizeMode()
{
    resizeMode = !resizeMode;
}

bool ImageModel::isGrayMode() const
{
    return grayMode;
}

bool ImageModel::isResizeMode() const
{
    return resizeMode;
}

cv::Mat ImageModel::getImage() const
{
    if (grayMode && !grayImage.empty())
    {
        return grayImage;
    }
    return colorImage;
}

void ImageModel::setImage(const cv::Mat& image)
{
    colorImage = image;
}

void ImageModel::saveState()
{
    imageHistory.push(colorImage.clone());
}

void ImageModel::undo()
{
    if (!imageHistory.empty())
    {
        colorImage = imageHistory.top();
        imageHistory.pop();
    }
}

int ImageModel::getStackSize() const
{
    return imageHistory.size();
}

