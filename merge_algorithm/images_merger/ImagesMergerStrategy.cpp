#include "../../image_matches/ImagesMatches.h"
#include "ImagesMergerStrategy.h"

void MapsMerge::ImagesMergerStrategy::mergeImages(ImagesMatches& imgsMatches) {
	addWeighted(imgsMatches.imgFeatures2.img, 0.5, imgsMatches.transformedImage, 1, 0.0, imgsMatches.mergedImages);
}
