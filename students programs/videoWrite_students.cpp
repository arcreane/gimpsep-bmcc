#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object and use camera to capture the video
  ...
    
  // Check if camera opened successfully
...

  // Default resolutions of the frame are obtained.The default resolutions are system dependent.
  int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
  VideoWriter ...;

  while(1){

    Mat frame;

    // Capture frame-by-frame
    ...
      
      
    // If the frame is empty, break immediately
    ...
      

    // Write the frame into the file 'outcpp.avi'
    ...

    // Display the resulting frame
    ...

    // Press  ESC on keyboard to  exit
   ...

      
  }

  // When everything done, release the video capture and write object
 ....

  // Closes all the frames
  ...
    
  return 0;
}
