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

void MapsMerge::ImagesMatches::showRegions(string winName1, string winName2) {
	imgFeatures1.showRegions(winName1);
	imgFeatures2.showRegions(winName2);
}

void MapsMerge::ImagesMatches::showMatches(string winName) {
	Mat imgMatches;
	drawMatches(
		imgFeatures1.img, imgFeatures1.keypoints,
		imgFeatures2.img, imgFeatures2.keypoints,
		matches, imgMatches,
		Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	namedWindow(winName, WINDOW_NORMAL);
	imshow(winName, imgMatches);
	waitKey(0);
}

void MapsMerge::ImagesMatches::showTransformedImage(string windowName) {
	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, transformedImage);
	waitKey(0);
}

void MapsMerge::ImagesMatches::showMergedImage(string windowName) {
	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, mergedImages);
	waitKey(0);
}
