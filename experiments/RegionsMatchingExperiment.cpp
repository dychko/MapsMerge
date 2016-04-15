#include "RegionsMatchingExperiment.h"
#include <iostream>
#include <ctime>

#include "../maps_merger/MapsMerger.h"

#include "../merge_algorithm/keypoints_descriptors_extractor/SurfStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/SiftStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/AsiftStrategy.h"
#include "../merge_algorithm/descriptors_matcher/FlannMatcherStrategy.h"
#include "../merge_algorithm/regions_selector/ManualRegionsSelector.h"
#include "../merge_algorithm/regions_matcher/GaleShapleyMatcherStrategy.h"
#include "../merge_algorithm/regions_matcher/SimpleMatcherStrategy.h"
#include "../merge_algorithm/image_transformer/ImageTransformerStrategy.h"
#include "../merge_algorithm/images_merger/ImagesMergerStrategy.h"
#include "../merge_algorithm/quality_evaluator/MSSIM.h"

#include "../utils/Utils.h"
#include "../utils/Statistics.h"

double MapsMerge::RegionsMatchingExperiment::getRelativeCorrectness(vector<Rect> originalRegions, vector<Rect> matchedRegions) {
	int numCorrectRegionsMatches = 0;
	for (int i = 0; i < originalRegions.size(); i++) {
		if (originalRegions[i] == matchedRegions[i]) {
			numCorrectRegionsMatches++;
		}
	}
	double regionsMatchesCorrectness = (double)numCorrectRegionsMatches / originalRegions.size();
	return regionsMatchesCorrectness;
}

void MapsMerge::RegionsMatchingExperiment::run() {
	
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
	
	// Experiments

	vector<vector<int>> regionsIndexes = Utils::getTuples4Vector(this->getNumRegions());

	vector<Rect> allSavedRegions1 = this->imagesMatches.imgFeatures1.regions;
	vector<Rect> allSavedRegions2 = this->imagesMatches.imgFeatures2.regions;
	
	Statistics stats("experiments_results/regions_matching_experiment_" + Utils::getTimeStr() + ".csv", 3);
	stats.addField("Id")
		 .addField("Regions matches correctness 1")
		 .addField("Regions matches correctness 2");

	int experimentId = 0;
	double averageCorrectness1 = 0;
	double averageCorrectness2 = 0;
	for(int iRegionsBatch = 0; iRegionsBatch < regionsIndexes.size(); iRegionsBatch++) {
		experimentId++;
		vector<int> regionsBatchIndexes = regionsIndexes[iRegionsBatch];
		
		// Set batch of regions
		this->setRegionsByIndexes(allSavedRegions1, allSavedRegions2, regionsBatchIndexes);
		vector<Rect> copyRegions(this->imagesMatches.imgFeatures1.regions);

		// Shuffle and create copy of regions
		this->imagesMatches.imgFeatures1.shuffeRegions();
		vector<Rect> copyShuffledRegions(this->imagesMatches.imgFeatures1.regions);

		// Match regions with Gale-Shapley
		this->setRegionsMatcher(new GaleShapleyMatcherStrategy());
		this->matchRegions();

		// Check correctness
		double regionsMatchesCorrectness1 = getRelativeCorrectness(copyRegions, this->imagesMatches.imgFeatures1.regions);

		// Restore shuffled regions configuration
		this->imagesMatches.imgFeatures1.regions = copyShuffledRegions;

		// Match regions with Simple algorithm
		this->setRegionsMatcher(new SimpleMatcherStrategy());
		this->matchRegions();

		// Check correctness
		double regionsMatchesCorrectness2 = getRelativeCorrectness(copyRegions, this->imagesMatches.imgFeatures1.regions);

		// Compute average	
		averageCorrectness1 += regionsMatchesCorrectness1 / regionsIndexes.size();
		averageCorrectness2 += regionsMatchesCorrectness2 / regionsIndexes.size();

		// Save results
		stats.addField(experimentId)
			 .addField(regionsMatchesCorrectness1)
			 .addField(regionsMatchesCorrectness2);
	}

	// Save results
	stats.addField("Average correctness:")
		 .addField(averageCorrectness1)
		 .addField(averageCorrectness2);

	stats.closeFile();

}
