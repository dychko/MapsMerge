#include "../../image_matches/ImagesMatches.h"
#include "RegionsMatcher.h"
#include "SimpleMatcherStrategy.h"
#include "../../utils/Utils.h"

void MapsMerge::SimpleMatcherStrategy::matchRegions(ImagesMatches& imgsMatches) {
	int numRegions = imgsMatches.imgFeatures1.regions.size();
	vector<vector<vector<int>>> numMatchesMatrices = createNumMatchesMatrices(imgsMatches);

	vector<vector<int>> regionsMatches = Utils::sumMatrices(numMatchesMatrices[0], Utils::transpose(numMatchesMatrices[1]));
	regionsMatches = Utils::transpose(regionsMatches);

	vector<Rect> copyRects1(imgsMatches.imgFeatures1.regions);

	for (int i = 0; i < numRegions; i++) {
		int idx1 = distance(regionsMatches[i].begin(), max_element(regionsMatches[i].begin(), regionsMatches[i].end()));
		imgsMatches.imgFeatures1.regions[i] = copyRects1[idx1];

		for (int row = 0; row < numRegions; row++) {
			regionsMatches[row][idx1] = -1;
		}
	}
}
