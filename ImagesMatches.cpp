#include "ImagesMatches.h"

void MapsMerge::ImagesMatches::readImages(string imgPath1, string imgPath2) {
	imgFeatures1.readImage(imgPath1);
	imgFeatures2.readImage(imgPath2);
}

void MapsMerge::ImagesMatches::showImages(string winName1, string winName2) {
	imgFeatures1.showImage(winName1);
	imgFeatures2.showImage(winName2);
}

void MapsMerge::ImagesMatches::showKeypoints(string winName1, string winName2) {
	imgFeatures1.showKeypoints(winName1);
	imgFeatures2.showKeypoints(winName2);
}
