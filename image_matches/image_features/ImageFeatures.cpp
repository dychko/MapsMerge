#include "ImageFeatures.h"

void MapsMerge::ImageFeatures::readImage(string imgPath) {
	img = imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
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

void MapsMerge::ImageFeatures::showRegions(string windowName) {
	Mat imgWithRegions = img.clone();
	for (int i = 0; i < regions.size(); i++) {
		rectangle(imgWithRegions, regions[i], Scalar(0, 0, 255), 5, 8, 0);
		putText(imgWithRegions, to_string(i + 1), regions[i].tl() + Point(-5, -5), 0, 5, Scalar(0, 0, 255), 5);
	}
	namedWindow(windowName, WINDOW_NORMAL);
	imshow(windowName, imgWithRegions);
	waitKey(0);
}

void MapsMerge::ImageFeatures::shuffeRegions() {
	random_shuffle(regions.begin(), regions.end());
}
