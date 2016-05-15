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

	//string imgPath1 = "imgs/GOPR9339.jpg";
	//string imgPath2 = "imgs/GGL9339.jpg";

	MapsMerger mapsMerger;
	mapsMerger.readImages(imgPath1, imgPath2);
	//mapsMerger.showImages("Image 1", "Image 2");

	mapsMerger.setKeypointsDescriptorsExtractor(new SurfStrategy());
	mapsMerger.detectAndCompute();
	//mapsMerger.showKeypoints("Image 1 with keypoints", "Image 2 with keypoints");

	mapsMerger.setDescriptorMatcher(new FlannMatcherStrategy());
	mapsMerger.matchDescriptors();
	//mapsMerger.showMatches("Matches");

	//double eps1 = 0.005;
	//size_t minElements1 = 30;
	double eps1 = 0.010;
	size_t minElements1 = 5;

	double eps2 = 0.005;
	size_t minElements2 = 5;
	//double eps2 = 0.005;
	//size_t minElements2 = 5;

	mapsMerger.setRegionsSelector(new DbscanRegionsSelector(eps1, minElements1, eps2, minElements2));
	//mapsMerger.setRegionsSelector(new DbscanRegionsSelector(eps1, minElements1));

	mapsMerger.selectRegions();

	mapsMerger.showClusters("Clusters1", "Clusters2");

	mapsMerger.leaveRegionsMatches();
	
	mapsMerger.showGoodMatches("Good Matches");


	mapsMerger.setImageTransformer(new ImageTransformerStrategy());
	mapsMerger.transformImage();

	mapsMerger.showTransformedImage("Transformed image");

	mapsMerger.setImagesMerger(new ImagesMergerStrategy());
	mapsMerger.mergeImages();
	mapsMerger.showMergedImage("Merge result");

	mapsMerger.setQualityEvaluator(new MSSIM());
	mapsMerger.evaluateQuality();

}
