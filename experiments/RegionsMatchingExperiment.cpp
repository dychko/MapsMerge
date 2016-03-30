#include "RegionsMatchingExperiment.h"
#include <iostream>

#include "../maps_merger/MapsMerger.h"

#include "../merge_algorithm/keypoints_descriptors_extractor/SurfStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/SiftStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/AsiftStrategy.h"
#include "../merge_algorithm/descriptors_matcher/FlannMatcherStrategy.h"
#include "../merge_algorithm/regions_selector/ManualRegionsSelector.h"
#include "../merge_algorithm/regions_matcher/GaleShapleyMatcherStrategy.h"
#include "../merge_algorithm/image_transformer/ImageTransformerStrategy.h"
#include "../merge_algorithm/images_merger/ImagesMergerStrategy.h"
#include "../merge_algorithm/quality_evaluator/MSSIM.h"

void MapsMerge::RegionsMatchingExperiment::run() {

	string imgPath1 = "imgs/ap-GOPR9460.jpg";
	string imgPath2 = "imgs/from-google-cut.jpg";

	MapsMerger mapsMerger;
	//mapsMerger.readImages(imgPath1, imgPath2);
	//mapsMerger.showImages("Image 1", "Image 2");

	//mapsMerger.setKeypointsDescriptorsExtractor(new SurfStrategy());
	//mapsMerger.detectAndCompute();
	//mapsMerger.showKeypoints("Image 1 with keypoints", "Image 2 with keypoints");

	//mapsMerger.setDescriptorMatcher(new FlannMatcherStrategy());
	//mapsMerger.matchDescriptors();
	//mapsMerger.showMatches("Matches");

	//mapsMerger.setRegionsSelector(new ManualRegionsSelector());

	//mapsMerger.selectRegions();



	mapsMerger.setRegionsMatcher(new GaleShapleyMatcherStrategy());
	mapsMerger.testAlg();


	// TODO: Shuffle regions

	// TODO: Create matrix of preferences

	// TODO: Match regions by Gale-Shapley algorithm

	// TODO: Show matched regions

	// TODO: Add loop

	// TODO: Save statistics


	// TODO: Remove the following method call
	// mapsMerger.leaveRegionsMatches();



	//mapsMerger.setImageTransformer(new ImageTransformerStrategy());
	//mapsMerger.transformImage();

	//mapsMerger.showTransformedImage("Transformed image");

	//mapsMerger.setImagesMerger(new ImagesMergerStrategy());
	//mapsMerger.mergeImages();
	//mapsMerger.showMergedImage("Merge result");

	//mapsMerger.setQualityEvaluator(new MSSIM());
	//mapsMerger.evaluateQuality();

	
	
	//mapsMerger.setRegionsSelector(new ManualRegionsSelector());
	//mapsMerger.testAlg();


}
