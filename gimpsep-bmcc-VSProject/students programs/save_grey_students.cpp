#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char **argv)
{
  char *imageName = argv[1];
  Mat image;
  image = ...;
  if (argc != 2 || !image.data)
  {
    printf(" No image data \n ");
    return -1;
  }
  Mat gray_image;
  ............

      return 0;
}
