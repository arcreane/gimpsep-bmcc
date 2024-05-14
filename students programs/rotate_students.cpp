#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
Mat source, M, result;

// Reading the image
...

Point2f center(source.cols/2, source.rows/2);
double rotationAngle=30;
double scale=1;

// Getting the matrix which will define the rotation
...

// Rotating the source and storing in result
...
    
// Create windows for display
...

// Display images
...

}
