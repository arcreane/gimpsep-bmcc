#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat3b canvas;
string buttonText("Gris");
string winName = "GIMProvise";

Rect button;
Mat colorImage;
Mat grayImage;
bool grayMode = false;

void createGUI()
{
    int buttonSize = 30;
    int canvasWidth = 1400;
    canvas = Mat3b(1000, canvasWidth, Vec3b(0, 0, 0));

    Mat resizedColorImage;
    resize(colorImage, resizedColorImage, Size(800, 800));

    if (grayMode)
    {
        Mat resizedGrayImage;
        resize(grayImage, resizedGrayImage, Size(800, 800));
        cvtColor(resizedGrayImage, canvas(Rect((canvasWidth - resizedGrayImage.cols) / 2, (canvas.rows - resizedGrayImage.rows) / 2, resizedGrayImage.cols, resizedGrayImage.rows)), COLOR_GRAY2BGR);
    }
    else
    {
        resizedColorImage.copyTo(canvas(Rect((canvasWidth - resizedColorImage.cols) / 2, (canvas.rows - resizedColorImage.rows) / 2, resizedColorImage.cols, resizedColorImage.rows)));
    }

    Rect buttonRect(0, 0, buttonSize, buttonSize);
    rectangle(canvas, buttonRect, Scalar(200, 200, 200), FILLED);
    putText(canvas, buttonText, Point(buttonSize * 0.1, buttonSize * 0.7), FONT_HERSHEY_PLAIN, 0.8, Scalar(0, 0, 0));

    imshow(winName, canvas);
}

void callBackFunc(int event, int x, int y, int flags, void *userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        if (x < 30 && y < 30)
        {
            grayMode = !grayMode;
            createGUI();
        }
    }
}

int main()
{
    char *imageName = "./HappyFish.jpg";
    colorImage = imread(imageName);
    if (!colorImage.data)
    {
        cout << "No image data" << endl;
        return -1;
    }

    cvtColor(colorImage, grayImage, COLOR_BGR2GRAY);

    namedWindow(winName);
    setMouseCallback(winName, callBackFunc);

    createGUI();

    waitKey();

    return 0;
}
