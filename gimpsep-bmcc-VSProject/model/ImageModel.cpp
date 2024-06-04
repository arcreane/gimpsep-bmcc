void ImageModel::dilateImage()
{
    if (!colorImage.empty())
    {
        cv::dilate(colorImage, colorImage, cv::Mat());
        if (grayMode)
        {
            cv::dilate(grayImage, grayImage, cv::Mat());
        }
    }
}

void ImageModel::erodeImage()
{
    if (!colorImage.empty())
    {
        cv::erode(colorImage, colorImage, cv::Mat());
        if (grayMode)
        {
            cv::erode(grayImage, grayImage, cv::Mat());
        }
    }
}
