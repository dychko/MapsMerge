#include "../../image_matches/ImagesMatches.h"
#include "RegionsMatcher.h"

void MapsMerge::RegionsMatcher::shuffleRegions(ImagesMatches& imgsMatches) {
	random_shuffle(imgsMatches.imgFeatures1.regions.begin(), imgsMatches.imgFeatures1.regions.end());
	random_shuffle(imgsMatches.imgFeatures2.regions.begin(), imgsMatches.imgFeatures2.regions.end());
}
