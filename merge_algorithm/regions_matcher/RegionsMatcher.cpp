#include "../../image_matches/ImagesMatches.h"
#include "RegionsMatcher.h"
#include "../regions_selector/RegionsSelector.h"

void MapsMerge::RegionsMatcher::shuffleRegions(ImagesMatches& imgsMatches) {
	imgsMatches.imgFeatures1.shuffeRegions();
}

vector<vector<vector<int>>> MapsMerge::RegionsMatcher::createNumMatchesMatrices(ImagesMatches& imgsMatches) {
	vector<vector<vector<int>>> numMatchesMatrices;

	// Build matrices with matches quantity

	const int numRegions1 = imgsMatches.imgFeatures1.regions.size();
	const int numRegions2 = imgsMatches.imgFeatures2.regions.size();

	vector<vector<int>> numMatchesRegions12(numRegions1, vector<int>(numRegions2));
	vector<vector<int>> numMatchesRegions21(numRegions2, vector<int>(numRegions1));

	for (int i = 0; i < numRegions1; i++) {
		vector<Rect> oneRegion1(1, imgsMatches.imgFeatures1.regions[i]);
		for (int j = 0; j  < numRegions2; j ++) {
			vector<Rect> oneRegion2(1, imgsMatches.imgFeatures2.regions[j]);
			numMatchesRegions12[i][j] = RegionsSelector::leaveRegionsMatches(imgsMatches, oneRegion1, oneRegion2).size();
			numMatchesRegions21[i][j] = RegionsSelector::leaveRegionsMatches(imgsMatches, oneRegion2, oneRegion1).size();			
		}
	}

	numMatchesMatrices.push_back(numMatchesRegions12);
	numMatchesMatrices.push_back(numMatchesRegions21);

	return numMatchesMatrices;
}
