#include "../../image_matches/ImagesMatches.h"
#include "ManualRegionsSelector.h"

Point MapsMerge::ManualRegionsSelector::P1;
Point MapsMerge::ManualRegionsSelector::P2;
Rect MapsMerge::ManualRegionsSelector::cropRect;
bool MapsMerge::ManualRegionsSelector::clicked;
string MapsMerge::ManualRegionsSelector::winName1;
string MapsMerge::ManualRegionsSelector::winName2;
Mat MapsMerge::ManualRegionsSelector::img1;
Mat MapsMerge::ManualRegionsSelector::img2;

void MapsMerge::ManualRegionsSelector::checkBoundary(Rect &cropRect, Mat &img) {
	if (cropRect.width > img.cols - cropRect.x) {
		cropRect.width = img.cols - cropRect.x;
	}
	if (cropRect.height > img.rows - cropRect.y) {
		cropRect.height = img.rows - cropRect.y;
	}
}

void MapsMerge::ManualRegionsSelector::showImage(Mat img, string winName, Rect cropRect = Rect(0,0,0,0)) {
	Mat copyImg = img.clone();
	checkBoundary(cropRect, copyImg);
	rectangle(copyImg, cropRect, Scalar(0, 255, 0), 5, 8, 0);
	imshow(winName, copyImg);
}

void MapsMerge::ManualRegionsSelector::onMouse(int event, int x, int y, int f, void* numWindow) {
	switch (event) {
		case CV_EVENT_LBUTTONDOWN : 
			clicked = true;
			P1.x = x;
			P1.y = y;
			P2.x = x;
			P2.y = y;
			break;
		case CV_EVENT_LBUTTONUP :
			P2.x = x;
			P2.y = y;
			clicked = false;
			break;
		case CV_EVENT_MOUSEMOVE :
			if (clicked) {
				P2.x = x;
				P2.y = y;
			}
			break;
		default:
			break;
	}

	if (clicked) {
		if (P1.x > P2.x) {
			cropRect.x = P2.x;
			cropRect.width = P1.x - P2.x;
		} else {
			cropRect.x = P1.x;
			cropRect.width = P2.x - P1.x;
		}

		if (P1.y > P2.y) {
			cropRect.y = P2.y;
			cropRect.height = P1.y - P2.y;
		} else {
			cropRect.y = P1.y;
			cropRect.height = P2.y - P1.y;
		}
	}

	if ((int) numWindow == 1) {
		showImage(img1, winName1, cropRect);
	} else {
		showImage(img2, winName2, cropRect);
	}

}

void MapsMerge::ManualRegionsSelector::selectRegions(ImagesMatches& imgsMatches) {
	winName1 = "Select regions: Photo";
	winName2 = "Select regions: Map";

	img1 = imgsMatches.imgFeatures1.img.clone();
	img2 = imgsMatches.imgFeatures2.img.clone();

	namedWindow(winName1, WINDOW_NORMAL);
	namedWindow(winName2, WINDOW_NORMAL);

	setMouseCallback(winName1, onMouse, (void*) 1);
	setMouseCallback(winName2, onMouse, (void*) 2);

	drawKeypoints(imgsMatches.imgFeatures1.img, imgsMatches.imgFeatures1.keypoints, img1);
	drawKeypoints(imgsMatches.imgFeatures2.img, imgsMatches.imgFeatures2.keypoints, img2);
	
	imshow(winName1, img1);
	imshow(winName2, img2);

	bool isWindow1Active = true;
	while (true) {
		char c = waitKey();
		if (c == 's') {
			if (isWindow1Active) {		
				imgsMatches.imgFeatures1.regions.push_back(cropRect);
				rectangle(img1, cropRect, Scalar(0, 0, 255), 5, 8, 0);
			} else  {
				imgsMatches.imgFeatures2.regions.push_back(cropRect);
				rectangle(img2, cropRect, Scalar(0, 0, 255), 5, 8, 0);
			}
			cropRect = Rect(0,0,0,0);
			isWindow1Active = !isWindow1Active;
		}
		if (c == 27) break;
		showImage(img1, winName1);
		showImage(img2, winName2);
	}
}

vector<DMatch> MapsMerge::ManualRegionsSelector::leaveRegionsMatches(ImagesMatches& imgsMatches,
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
