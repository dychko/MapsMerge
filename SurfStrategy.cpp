#include "ImagesMatches.h"
#include "SurfStrategy.h"

void MapsMerge::SurfStrategy::detectAndCompute(ImagesMatches& imgsMatches) {
	int minHessian = 400;

	SurfFeatureDetector detector(minHessian);

	detector.detect(
		imgsMatches.imgFeatures1.img, 
		imgsMatches.imgFeatures1.keypoints);

	detector.detect(
		imgsMatches.imgFeatures2.img,
		imgsMatches.imgFeatures2.keypoints);

	SurfDescriptorExtractor extractor;

	extractor.compute(
		imgsMatches.imgFeatures1.img,
		imgsMatches.imgFeatures1.keypoints,
		imgsMatches.imgFeatures1.descriptors);

	extractor.compute(
		imgsMatches.imgFeatures2.img,
		imgsMatches.imgFeatures2.keypoints,
		imgsMatches.imgFeatures2.descriptors);

}
