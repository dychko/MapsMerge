#include "../../image_matches/ImagesMatches.h"
#include "AsiftStrategy.h"

void MapsMerge::AsiftStrategy::detectAndCompute(ImagesMatches& imgsMatches) {
	
	vector<KeyPoint>().swap(imgsMatches.imgFeatures1.keypoints);
	vector<KeyPoint>().swap(imgsMatches.imgFeatures2.keypoints);	
	imgsMatches.imgFeatures1.descriptors.release();
	imgsMatches.imgFeatures2.descriptors.release();

	ASiftDetector detector;

	detector.detectAndCompute(
		imgsMatches.imgFeatures1.img,
		imgsMatches.imgFeatures1.keypoints,
		imgsMatches.imgFeatures1.descriptors);

	detector.detectAndCompute(
		imgsMatches.imgFeatures2.img,
		imgsMatches.imgFeatures2.keypoints,
		imgsMatches.imgFeatures2.descriptors);

}
