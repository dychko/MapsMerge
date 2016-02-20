#include "ImageFeatures.h"


void MapsMerge::ImageFeatures::readImage(string imgPath) {
	img = imread(imgPath, CV_LOAD_IMAGE_COLOR);
	if (!img.data) {
		cerr << "Could not read an image: " + imgPath << endl;
		throw "imread exception";
	}
}

void MapsMerge::ImageFeatures::showImage(string windowName) {
	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, img);
	waitKey(0);
}

void MapsMerge::ImageFeatures::showKeypoints(string windowName) {
	Mat imgWithKeypoints;
	drawKeypoints(img, keypoints, imgWithKeypoints);
	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, imgWithKeypoints);
	waitKey(0);
	imgWithKeypoints.release();
}