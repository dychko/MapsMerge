#include "../../image_matches/ImagesMatches.h"
#include "FlannMatcherStrategy.h"

void MapsMerge::FlannMatcherStrategy::matchDescriptors(ImagesMatches& imgsMatches) {

	matcher.match(
		imgsMatches.imgFeatures1.descriptors,
		imgsMatches.imgFeatures2.descriptors,
		imgsMatches.matches);
}
