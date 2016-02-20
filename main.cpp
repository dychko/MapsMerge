#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include "MapsMerger.h"

#include "SurfStrategy.h"


using namespace cv;
using namespace std;
using namespace MapsMerge;

int testOpenCV(int, char**);

int main(int argc, char** argv) {

	string imgPath1 = "imgs/ap-GOPR9460.jpg";
	string imgPath2 = "imgs/from-google-cut.jpg";

	MapsMerger mapsMerger;

	mapsMerger.readImages(imgPath1, imgPath2);
	mapsMerger.showImages();
	mapsMerger.setKeypointsDescriptorsExtractor(new SurfStrategy());
	mapsMerger.detectAndCompute();
	mapsMerger.showKeypoints();
    
    return 0;
}

int testOpenCV(int argc, char** argv) {
	if(argc != 2) {
     std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
     return -1;
    }

	cv::Mat image;
    image = cv::imread(argv[1], cv::IMREAD_COLOR); // Read the file

     // Check for invalid input
	if(!image.data) {
        std::cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE ); // Create a window for display.
    cv::imshow( "Display window", image ); // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}