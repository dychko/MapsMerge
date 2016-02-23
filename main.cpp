#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include "MapsMerger.h"

#include "SurfStrategy.h"
#include "SiftStrategy.h"
#include "AsiftStrategy.h"
#include "FlannMatcherStrategy.h"
#include "ManualRegionsSelector.h"
#include "ImageTransformerStrategy.h"
#include "ImagesMergerStrategy.h"


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
	mapsMerger.showKeypoints("Image 1 with keypoints", "Image 2 with keypoints");

	mapsMerger.setDescriptorMatcher(new FlannMatcherStrategy());
	mapsMerger.matchDescriptors();
	mapsMerger.showMatches("Matches");

	mapsMerger.setRegionsSelector(new ManualRegionsSelector());

	mapsMerger.selectRegions();
	mapsMerger.leaveRegionsMatches();

	mapsMerger.setImageTransformer(new ImageTransformerStrategy());
	mapsMerger.transformImage();

	mapsMerger.showTransformedImage("Transformed image");

	mapsMerger.setImagesMerger(new ImagesMergerStrategy());
	mapsMerger.mergeImages();
	mapsMerger.showMergedImage("Merge result");

    
    return 0;
}
