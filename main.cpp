#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include "MapsMerger.h"

#include "SurfStrategy.h"
#include "SiftStrategy.h"
#include "AsiftStrategy.h"


using namespace cv;
using namespace std;
using namespace MapsMerge;

int main(int argc, char** argv) {

	string imgPath1 = "imgs/ap-GOPR9460.jpg";
	string imgPath2 = "imgs/from-google-cut.jpg";

	MapsMerger mapsMerger;

	mapsMerger.readImages(imgPath1, imgPath2);
	mapsMerger.showImages("Image 1", "Image 2");

	mapsMerger.setKeypointsDescriptorsExtractor(new SurfStrategy());
	mapsMerger.detectAndCompute();
	mapsMerger.showKeypoints("Surf image 1", "Surf image 2");

	mapsMerger.setKeypointsDescriptorsExtractor(new SiftStrategy());
	mapsMerger.detectAndCompute();
	mapsMerger.showKeypoints("Sift keypoints 1", "Sift keypoints 2");	

	mapsMerger.setKeypointsDescriptorsExtractor(new AsiftStrategy());
	mapsMerger.detectAndCompute();
	mapsMerger.showKeypoints("Asift keypoints 1", "Asift keypoints 2");
    
    return 0;
}
