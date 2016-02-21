#include "ImagesMatches.h"
#include "RegionsSelector.h"

void MapsMerge::RegionsSelector::leaveRegionsMatches(ImagesMatches& imgsMatches) {

	vector<KeyPoint> keypoints1 = imgsMatches.imgFeatures1.keypoints;
	vector<KeyPoint> keypoints2 = imgsMatches.imgFeatures2.keypoints;
	vector<Rect> regions1 = imgsMatches.imgFeatures1.regions;
	vector<Rect> regions2 = imgsMatches.imgFeatures2.regions;
	vector<DMatch> matches = imgsMatches.matches;

	for(int iRect = 0; iRect < imgsMatches.imgFeatures1.regions.size(); iRect++) {		
		for(int iKeyPoint = 0; iKeyPoint < imgsMatches.imgFeatures1.keypoints.size(); iKeyPoint++) {
		
			// If key point is inside region
			if (keypoints1[iKeyPoint].pt.x >= regions1[iRect].x &&
				keypoints1[iKeyPoint].pt.x <= regions1[iRect].x + regions1[iRect].width &&
				keypoints1[iKeyPoint].pt.y >= regions1[iRect].y &&
				keypoints1[iKeyPoint].pt.y <= regions1[iRect].y + regions1[iRect].height) {
					
					// If matched key point is inside matched region
					if (keypoints2[matches[iKeyPoint].trainIdx].pt.x >= regions2[iRect].x &&
						keypoints2[matches[iKeyPoint].trainIdx].pt.x <= regions2[iRect].x + regions2[iRect].width &&
						keypoints2[matches[iKeyPoint].trainIdx].pt.y >= regions2[iRect].y &&
						keypoints2[matches[iKeyPoint].trainIdx].pt.y <= regions2[iRect].y + regions2[iRect].height) {

							imgsMatches.goodMatches.push_back(matches[iKeyPoint]);
					}
			}
		}
	}
}
