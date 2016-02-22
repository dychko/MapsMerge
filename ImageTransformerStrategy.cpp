#include "ImagesMatches.h"
#include "ImageTransformerStrategy.h"
#include "InteriorRect.h"

void MapsMerge::ImageTransformerStrategy::transformImage(ImagesMatches& imgsMatches) {

	// Localize the object from img1 in img2

	vector<Point2f> obj;
	vector<Point2f> scene;

	for(size_t i = 0; i < imgsMatches.goodMatches.size(); i++) {
		obj.push_back(imgsMatches.imgFeatures1.keypoints[imgsMatches.goodMatches[i].queryIdx].pt);
		scene.push_back(imgsMatches.imgFeatures2.keypoints[imgsMatches.goodMatches[i].trainIdx].pt);
	}

	Mat H = findHomography(obj, scene, CV_RANSAC);

	// Get the corners from the img1 ( the object to be "detected" )

	vector<Point2f> objCorners(4);
	objCorners[0] = Point(0,0);
	objCorners[1] = Point(imgsMatches.imgFeatures1.img.cols, 0);
	objCorners[2] = Point(imgsMatches.imgFeatures1.img.cols, imgsMatches.imgFeatures1.img.rows);
	objCorners[3] = Point(0, imgsMatches.imgFeatures1.img.rows);

	// Transform image

	vector<Point2f> sceneCorners(4);
	perspectiveTransform(objCorners, sceneCorners, H);

	imgsMatches.transformedImage = Mat(imgsMatches.imgFeatures2.img.rows, imgsMatches.imgFeatures2.img.cols, CV_8UC3);
	warpPerspective(imgsMatches.imgFeatures1.img, imgsMatches.transformedImage, H, imgsMatches.transformedImage.size());


	// Get rectangular area from transformed image

	if (sceneCorners[0].x > sceneCorners[1].x || sceneCorners[3].x > sceneCorners[2].x ||
		sceneCorners[0].y > sceneCorners[3].y || sceneCorners[1].y > sceneCorners[2].y) {
		imgsMatches.interiorRect = Rect(0, 0, 0, 0);
	} else {
		imgsMatches.interiorRect = cropRectCustom(sceneCorners, Rect(0, 0, imgsMatches.imgFeatures2.img.cols, imgsMatches.imgFeatures2.img.rows));
	}

}
