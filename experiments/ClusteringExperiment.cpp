#include "ClusteringExperiment.h"

#include "../maps_merger/MapsMerger.h"

#include "../merge_algorithm/keypoints_descriptors_extractor/SurfStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/SiftStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/AsiftStrategy.h"
#include "../merge_algorithm/descriptors_matcher/FlannMatcherStrategy.h"
#include "../merge_algorithm/regions_selector/DbscanRegionsSelector.h"
#include "../merge_algorithm/image_transformer/ImageTransformerStrategy.h"
#include "../merge_algorithm/images_merger/ImagesMergerStrategy.h"
#include "../merge_algorithm/quality_evaluator/MSSIM.h"
#include "../utils/Utils.h"

void MapsMerge::ClusteringExperiment::run() {

	string imgPath1 = "imgs/ap-GOPR9460.jpg";
	string imgPath2 = "imgs/from-google-cut.jpg";

	MapsMerger mapsMerger;
	mapsMerger.readImages(imgPath1, imgPath2);
	//mapsMerger.showImages("Image 1", "Image 2");

	mapsMerger.setKeypointsDescriptorsExtractor(new SurfStrategy());
	mapsMerger.detectAndCompute();
	//mapsMerger.showKeypoints("Image 1 with keypoints", "Image 2 with keypoints");

	mapsMerger.setDescriptorMatcher(new FlannMatcherStrategy());
	mapsMerger.matchDescriptors();
	//mapsMerger.showMatches("Matches");

	//double eps1 = 0.010;
	double eps1 = 0.05;
	size_t minElements1 = 5;

	//double eps2 = 0.008;
	double eps2 = 0.05;
	size_t minElements2 = 15;

	//cout << "Num keypoints1: " << mapsMerger.imagesMatches.imgFeatures1.keypoints.size() << endl;
	//cout << "Num keypoints2: " << mapsMerger.imagesMatches.imgFeatures2.keypoints.size() << endl;

	//         5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
	//       ---+---+---+---+---+---+---+--+---+---+---+
	//0.010 [ 50, 43, 50, 43, 42, 38, 31, 37, 27, 26, 26 ]
	//0.015 [ 10,  8, 10, 12, 15, 18, 18, 20, 22, 24, 21 ]
	//0.020 [  9,  8,  6,  4,  5,  6,  7,  7,  7,  6,  6 ]
	//0.025 [  3,  3,  4,  5,  2,  2,  2,  2,  2,  2,  3 ]

	mapsMerger.setRegionsSelector(new DbscanRegionsSelector(eps1, minElements1, eps2, minElements2));

	mapsMerger.selectRegions();

	//mapsMerger.showClusters("Clusters1", "Clustes2");

	mapsMerger.leaveRegionsMatches();
	
	//mapsMerger.showGoodMatches("Good Matches");


	//mapsMerger.setImageTransformer(new ImageTransformerStrategy());
	//mapsMerger.transformImage();

	//mapsMerger.showTransformedImage("Transformed image");

	//mapsMerger.setImagesMerger(new ImagesMergerStrategy());
	//mapsMerger.mergeImages();
	//mapsMerger.showMergedImage("Merge result");

	//mapsMerger.setQualityEvaluator(new MSSIM());
	//mapsMerger.evaluateQuality();

}
