#include "../../image_matches/ImagesMatches.h"
#include "SiftStrategy.h"

void MapsMerge::SiftStrategy::detectAndCompute(ImagesMatches& imgsMatches) {

	SiftFeatureDetector detector;

	detector.detect(
		imgsMatches.imgFeatures1.img, 
		imgsMatches.imgFeatures1.keypoints);

	detector.detect(
		imgsMatches.imgFeatures2.img,
		imgsMatches.imgFeatures2.keypoints);

	SiftDescriptorExtractor extractor;

	extractor.compute(
		imgsMatches.imgFeatures1.img,
		imgsMatches.imgFeatures1.keypoints,
		imgsMatches.imgFeatures1.descriptors);

	extractor.compute(
		imgsMatches.imgFeatures2.img,
		imgsMatches.imgFeatures2.keypoints,
		imgsMatches.imgFeatures2.descriptors);

}
