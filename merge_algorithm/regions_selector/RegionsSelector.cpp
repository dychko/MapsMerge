#include "../../image_matches/ImagesMatches.h"
#include "RegionsSelector.h"

vector<DMatch> MapsMerge::RegionsSelector::leaveRegionsMatches(ImagesMatches& imgsMatches,
															   vector<Rect> regions1,
															   vector<Rect> regions2) {

	vector<KeyPoint> keypoints1 = imgsMatches.imgFeatures1.keypoints;
	vector<KeyPoint> keypoints2 = imgsMatches.imgFeatures2.keypoints;
	//vector<Rect> regions1 = imgsMatches.imgFeatures1.regions;
	//vector<Rect> regions2 = imgsMatches.imgFeatures2.regions;
	vector<DMatch> matches = imgsMatches.matches;
	vector<DMatch> goodMatches;

	for(int iRect = 0; iRect < imgsMatches.imgFeatures1.regions.size(); iRect++) {		
		for(int iKeyPoint = 0; iKeyPoint < imgsMatches.imgFeatures1.keypoints.size(); iKeyPoint++) {		
			
			// If key point is inside region
			if (regions1[iRect].contains(keypoints1[iKeyPoint].pt)) {					
				
				// If matched key point is inside matched region
				if (regions2[iRect].contains(keypoints2[matches[iKeyPoint].trainIdx].pt)) {
					goodMatches.push_back(matches[iKeyPoint]);
				}
			}
		}
	}

	return goodMatches;
}
