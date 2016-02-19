#include "MapsMerger.h"

void MapsMerge::MapsMerger::readImages(string imgPath1, string imgPath2) {
	imagesMatches.readImages(imgPath1, imgPath2);
}

void MapsMerge::MapsMerger::showImages() {
	imagesMatches.showImages();
}

void MapsMerge::MapsMerger::setKeypointsDescriptorsExtractor(KeypointsDescriptorsExtractor* e) {
	keypointsDescriptorsExtractor = e;
}

void MapsMerge::MapsMerger::detectAndCompute(ImagesMatches& imagesMatches) {
	keypointsDescriptorsExtractor->detectAndCompute(imagesMatches);
}
