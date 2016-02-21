#include "MapsMerger.h"

void MapsMerge::MapsMerger::readImages(string imgPath1, string imgPath2) {
	imagesMatches.readImages(imgPath1, imgPath2);
}

void MapsMerge::MapsMerger::showImages(string winName1, string winName2) {
	imagesMatches.showImages(winName1, winName2);
}

void MapsMerge::MapsMerger::showKeypoints(string winName1, string winName2) {
	imagesMatches.showKeypoints(winName1, winName2);
}

void MapsMerge::MapsMerger::setKeypointsDescriptorsExtractor(KeypointsDescriptorsExtractor* e) {
	keypointsDescriptorsExtractor = e;
}

void MapsMerge::MapsMerger::detectAndCompute() {
	keypointsDescriptorsExtractor->detectAndCompute(imagesMatches);
}
