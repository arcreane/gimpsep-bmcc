#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
Mat source, scaleD, scaleU;

// Read source image
source = ...;

// Scaling factors
double scaleX = 0.6;
double scaleY = 0.6;

// Scaling down the image 0.6 times
...
// Scaling up the image 1.8 times
...



//Cropped image
Mat crop = source(...);



//Display windows and show for all four images
....

}
