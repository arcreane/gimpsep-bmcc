void View::createGUI()
{
    int buttonSize = 30;
    int buttonSpacing = 10; // Space between buttons
    int canvasWidth = 1400;
    int canvasHeight = 1000;
    canvas = cv::Mat3b(canvasHeight, canvasWidth, cv::Vec3b(0, 0, 0));

    // Draw buttons
    cv::Rect fileButtonRect(0, 0, buttonSize, buttonSize);
    cv::rectangle(canvas, fileButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "File", cv::Point(buttonSize * 0.1, buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    cv::Rect saveButtonRect(buttonSize + buttonSpacing, 0, buttonSize, buttonSize);
    cv::rectangle(canvas, saveButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "Save", cv::Point((buttonSize + buttonSpacing) + buttonSize * 0.1, buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    cv::Rect grayButtonRect(0, buttonSize + buttonSpacing, buttonSize, buttonSize);
    cv::rectangle(canvas, grayButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "Gris", cv::Point(buttonSize * 0.1, (buttonSize + buttonSpacing) + buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    // Draw dilate and erode buttons
    cv::Rect dilateButtonRect(40, buttonSize + buttonSpacing, buttonSize, buttonSize);
    cv::rectangle(canvas, dilateButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "Dilate", cv::Point(40 + buttonSize * 0.1, (buttonSize + buttonSpacing) + buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    cv::Rect erodeButtonRect(80, buttonSize + buttonSpacing, buttonSize, buttonSize);
    cv::rectangle(canvas, erodeButtonRect, cv::Scalar(200, 200, 200), cv::FILLED);
    cv::putText(canvas, "Erode", cv::Point(80 + buttonSize * 0.1, (buttonSize + buttonSpacing) + buttonSize * 0.7), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0, 0, 0));

    // Display image if loaded
    cv::Mat image = model.getImage();
    if (!image.empty())
    {
        cv::Mat resizedImage;
        double aspectRatio = static_cast<double>(image.cols) / image.rows;
        int newWidth, newHeight;

        // Adjust new width and height to maintain aspect ratio
        if (canvasWidth - 200 < (canvasHeight - 200) * aspectRatio)
        {
            newWidth = canvasWidth - 200;
            newHeight = static_cast<int>(newWidth / aspectRatio);
        }
        else
        {
            newHeight = canvasHeight - 200;
            newWidth = static_cast<int>(newHeight * aspectRatio);
        }

        cv::resize(image, resizedImage, cv::Size(newWidth, newHeight));
        if (model.isGrayMode())
        {
            cv::cvtColor(resizedImage, resizedImage, cv::COLOR_GRAY2BGR);
        }

        // Center the resized image on the canvas
        int offsetX = (canvasWidth - resizedImage.cols) / 2;
        int offsetY = (canvasHeight - resizedImage.rows) / 2;

        // Ensure the offset values are non-negative
        offsetX = std::max(0, offsetX);
        offsetY = std::max(0, offsetY);

        resizedImage.copyTo(canvas(cv::Rect(offsetX, offsetY, resizedImage.cols, resizedImage.rows)));
    }
}
