class Controller
{
public:
    Controller();
    void handleMouseEvent(int event, int x, int y, int flags, void* userdata);
    void loadImage();
    void toggleGrayMode();
    void saveImage();
    void dilateImage(); // Add this line
    void erodeImage();  // Add this line

private:
    ImageModel model;
    View view;
    void updateView();
};
