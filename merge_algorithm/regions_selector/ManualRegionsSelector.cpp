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

bool MapsMerge::ManualRegionsSelector::prefers(vector<vector<int>> matrix2, int w, int m, int m1) {
	for (int i = 0; i < matrix2[0].size(); i++) {
		if (matrix2[w][i] == m1)
			return true;
		
		if (matrix2[w][i] == m)
			return false;
	}
}

vector<int> MapsMerge::ManualRegionsSelector::algGaleShapley(vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
	if (matrix1.size() != matrix2.size()) {
		cerr << "Incompatible dimensions of matrices" << endl;
		return vector<int>(0, 0);
	}

	int N = matrix1.size();
	vector<int> wMatch(N, -1);
	vector<bool> mMatched(N, false);
	int freeCount = N;

	while (freeCount > 0) {
		int m;
		for (m = 0; m < N; m++)
			if (mMatched[m] == false)
				break;
		for (int i = 0; i < N && !mMatched[m]; i++) {
			int w = matrix1[m][i];

			if (wMatch[w] == -1) {
				wMatch[w] = m;
				mMatched[m] = true;
				freeCount--;
			} else {
				int m1 = wMatch[w];

				if (!prefers(matrix2, w, m, m1)) {
					wMatch[w] = m;
					mMatched[m] = true;
					mMatched[m1] = false;
				}
			}
		}
	}

	// Returns a vector with values corresponding to matrix1 and indices - to matrix2

	return wMatch;
}

void MapsMerge::ManualRegionsSelector::testGaleShapleyAlgorithm() {

	// Initialization
	const int dimension = 4;
	    int prefer[2 * dimension][dimension] = { 
		{7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
    
		{0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
	vector<vector<int>> matrix1(dimension, vector<int>(dimension));
	vector<vector<int>> matrix2(dimension, vector<int>(dimension));
	
	cout << "Before initialization" << endl;

	//for (int i = 0; i < dimension; i++) {
	//	matrix1[i].assign(&prefer[i][0], &prefer[i][dimension]);
	//	matrix1[i + dimension].assign(&prefer[i + dimension][0], &prefer[i + dimension][dimension]);
	//}

	matrix1[0][0] = 3; matrix1[0][1] = 1; matrix1[0][2] = 2; matrix1[0][3] = 0;
	matrix1[1][0] = 1; matrix1[1][1] = 0; matrix1[1][2] = 2; matrix1[1][3] = 3;
	matrix1[2][0] = 0; matrix1[2][1] = 1; matrix1[2][2] = 2; matrix1[2][3] = 3;
	matrix1[3][0] = 0; matrix1[3][1] = 1; matrix1[3][2] = 2; matrix1[3][3] = 3;
	matrix2[0][0] = 0; matrix2[0][1] = 1; matrix2[0][2] = 2; matrix2[0][3] = 3;
	matrix2[1][0] = 0; matrix2[1][1] = 1; matrix2[1][2] = 2; matrix2[1][3] = 3;
	matrix2[2][0] = 0; matrix2[2][1] = 1; matrix2[2][2] = 2; matrix2[2][3] = 3;
	matrix2[3][0] = 0; matrix2[3][1] = 1; matrix2[3][2] = 2; matrix2[3][3] = 3;

	cout << "Matrix 1" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "[ ";
		for (int j = 0; j < 4; j++) {
			cout << matrix1[i][j] << ((j!=3)?(", "):(""));
		}
		cout << " ]\n";
	}

	cout << "Matrix 2" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "[ ";
		for (int j = 0; j < 4; j++) {
			cout << matrix2[i][j] << ((j!=3)?(", "):(""));
		}
		cout << " ]\n";
	}

	cout << "After initialization" << endl;
	
	// Algorithm
	vector<int> result = algGaleShapley(matrix1, matrix2);

	cout << "After algorithm" << endl;

	// Print results
	cout << "Results: " << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << ", ";
	}
}

void MapsMerge::ManualRegionsSelector::matchRegionsAuto(ImagesMatches& imgsMatches) {
	// TODO: Needs implementation
}
