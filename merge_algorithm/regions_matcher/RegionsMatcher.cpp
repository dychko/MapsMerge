#include "../../image_matches/ImagesMatches.h"
#include "RegionsMatcher.h"

void MapsMerge::RegionsMatcher::shuffleRegions(ImagesMatches& imgsMatches) {
	imgsMatches.imgFeatures1.shuffeRegions();
}
