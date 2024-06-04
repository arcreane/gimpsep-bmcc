class ImageModel
{
public:
    ImageModel();
    void loadImage(const std::string& path);
    void toggleGrayMode();
    bool isGrayMode() const;
    cv::Mat getImage() const;
    void dilateImage(); // Add this line
    void erodeImage();  // Add this line

private:
    cv::Mat colorImage;
    cv::Mat grayImage;
    bool grayMode;
};
