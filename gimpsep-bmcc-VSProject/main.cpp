#include "controller/Controller.h"

int main()
{
    try
    {
        Controller controller;
        cv::waitKey();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}