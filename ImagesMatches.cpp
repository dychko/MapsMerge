#include "ImagesMatches.h"

void MapsMerge::ImagesMatches::readImages(string imgPath1, string imgPath2) {
	imgFeatures1.readImage(imgPath1);
	imgFeatures2.readImage(imgPath2);
}

void MapsMerge::ImagesMatches::showImages() {
	imgFeatures1.showImage("Image 1");
	imgFeatures2.showImage("Image 2");
}

void MapsMerge::ImagesMatches::showKeypoints() {
	imgFeatures1.showKeypoints("Image 1 keypoints");
	imgFeatures2.showKeypoints("Image 2 keypoints");
}
