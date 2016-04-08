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

#include "../utils/Utils.h"

void MapsMerge::RegionsMatchingExperiment::run() {

	// Getting needed data
	
	string imgPath1 = "imgs/ap-GOPR9460.jpg";
	string imgPath2 = "imgs/from-google-cut.jpg";
		
	this->readImages(imgPath1, imgPath2);
	this->showImages("Image 1", "Image 2");

	this->setKeypointsDescriptorsExtractor(new SurfStrategy());
	this->detectAndCompute();
	this->showKeypoints("Image 1 with keypoints", "Image 2 with keypoints");

	this->setDescriptorMatcher(new FlannMatcherStrategy());
	this->matchDescriptors();
	this->showMatches("Matches");

	this->setRegionsSelector(new ManualRegionsSelector());
	this->selectRegions();

	// TODO: Maybe use it later
	//this->setRegionsMatcher(new GaleShapleyMatcherStrategy());
	//this->testAlg();

	//this->shuffleRegions();
	//this->showRegions("Shuffled regions 1", "Shuffled regions 2");

	//this->matchRegions();
	//this->showRegions("Regions 1", "Regions 2");
	//
	
	// Experiments

	vector<vector<int>> regionsIndexes = Utils::getTuples4Vector(this->getNumRegions());

	vector<Rect> allSavedRegions1 = this->imagesMatches.imgFeatures1.regions;
	vector<Rect> allSavedRegions2 = this->imagesMatches.imgFeatures2.regions;
	
	
	int experimentId = 1;
	double averageCorrectness = 0;
	for(int iRegionsBatch = 0; iRegionsBatch < regionsIndexes.size(); iRegionsBatch++) {
		// Set batches of regions

			// TODO: This may need refactoring
			// E.g. create function setRegionsByIndexes
		this->imagesMatches.imgFeatures1.regions.clear();
		this->imagesMatches.imgFeatures2.regions.clear();
		for (int i = 0; i < regionsIndexes[iRegionsBatch].size(); i++) {
			this->imagesMatches.imgFeatures1.regions.push_back(allSavedRegions1[regionsIndexes[iRegionsBatch][i]]);
			this->imagesMatches.imgFeatures2.regions.push_back(allSavedRegions2[regionsIndexes[iRegionsBatch][i]]);
		}

		// Shuffle regions

		this->imagesMatches.imgFeatures1.shuffeRegions();

		// Match regions

		this->setRegionsMatcher(new GaleShapleyMatcherStrategy());
		this->matchRegions();

			// Use second algorithm

		// Save results
		// Check correctness		
		int numCorrectRegionsMatches = 0;
		int numAllRegionsMatches = regionsIndexes[iRegionsBatch].size();

		for (int i = 0; i < numAllRegionsMatches; i++) {
			if (this->imagesMatches.imgFeatures1.regions[i] == allSavedRegions1[regionsIndexes[iRegionsBatch][i]]) {
				numCorrectRegionsMatches++;
			}
		}

		double regionsMatchesCorrectness = (double)numCorrectRegionsMatches / numAllRegionsMatches;

		cout << experimentId << ". Correctness: " << regionsMatchesCorrectness << " %" << endl;

		experimentId++;

		averageCorrectness += regionsMatchesCorrectness / regionsIndexes.size();

	}

	cout << "Average correctness: " << averageCorrectness << endl;
		
	
	//mapsMerger.matchRegions();
	//mapsMerger.showRegions("Regions 1", "Regions 2");

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
