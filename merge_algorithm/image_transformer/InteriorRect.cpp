/*
http://stackoverflow.com/questions/21410449/how-do-i-crop-to-largest-interior-bounding-box-in-opencv?lq=1
*/

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "interiorrect.h"

using namespace std;
using namespace cv;

bool sortXcust(Point a, Point b) {
	return a.x < b.x;
}

bool sortYcust(Point a, Point b) {
	return a.y < b.y;
}

bool checkInteriorExteriorCustom(const Mat& img, const Rect& interiorRect, int& top, int& bottom, int& left, int& right)
{
	// return true if the rectangle is fine as it is!
	bool returnVal = true;

	Mat sub = img(interiorRect);

	unsigned int x = 0;
	unsigned int y = 0;

	// count how many exterior pixels are at the
	double cTop=0; // top row
	double cBottom=0; // bottom row
	double cLeft=0; // left column
	double cRight=0; // right column
	// and choose that side for reduction where mose exterior pixels occured (that's the heuristic)
	     
	for(y=0, x=0 ; x<sub.cols; ++x) {
		// if there is an exterior part in the interior we have to move the top side of the rect a bit to the bottom
		if(sub.at<unsigned char>(y,x) == 0) {
			returnVal = false;
			++cTop;
		}
	}

	cTop /= sub.cols;

	for(y=sub.rows-1, x=0; x<sub.cols; ++x) {
		// if there is an exterior part in the interior we have to move the bottom side of the rect a bit to the top
		if(sub.at<unsigned char>(y,x) == 0) {
			returnVal = false;
			++cBottom;
		}
	}

	cBottom /= sub.cols;

	for(y=0, x=0 ; y<sub.rows; ++y) {
		// if there is an exterior part in the interior
		if(sub.at<unsigned char>(y,x) == 0) {
			returnVal = false;
			++cLeft;
		}
	}

	cLeft /= sub.rows;

	for(x=sub.cols-1, y=0; y<sub.rows; ++y) {
		// if there is an exterior part in the interior
		if(sub.at<unsigned char>(y,x) == 0) {
			returnVal = false;
			++cRight;
		}
	}

	cRight /= sub.rows;

	
	// that part is ugly and maybe not correct, didn't check whether all possible combinations are handled. Check that one please. The idea is to set `top = 1` iff it's better to reduce the rect at the top than anywhere else.
	if(cTop > cBottom) {
		if(cTop > cLeft)
			if(cTop > cRight)
				top = 1;
	}
	else
		if(cBottom > cLeft)
			if(cBottom > cRight)
				bottom = 1;

	if(cLeft >= cRight) {
		if(cLeft >= cBottom)
			if(cLeft >= cTop)
				left = 1;
	}
	else
		if(cRight >= cTop)
			if(cRight >= cBottom)
				right = 1;

	return returnVal;
}


Rect cropRectCustom(const vector<Point2f> points, const Rect rect) {

	// Drawing polygon
	Mat imgPoly = Mat::zeros(rect.size(), CV_8UC1);
	Point polyPoints[1][4];
	polyPoints[0][0] = points[0];
	polyPoints[0][1] = points[1];
	polyPoints[0][2] = points[2];
	polyPoints[0][3] = points[3];

	const Point* ppt[1] = {polyPoints[0]};
	int npt[] = {4};

	fillPoly(imgPoly, ppt, npt, 1, Scalar(255), 8);
	// End of drawing polygon

	vector<Point2f> pointsSortedX = points;
	sort(pointsSortedX.begin(), pointsSortedX.end(), sortXcust);

	vector<Point2f> pointsSortedY = points;
	sort(pointsSortedY.begin(), pointsSortedY.end(), sortYcust);

	int minXid = 0;
	int maxXid = pointsSortedX.size() - 1;

	int minYid = 0;
	int maxYid = pointsSortedY.size() - 1;

	// test
	minXid = max(pointsSortedX[minXid].x, float(0));
	maxXid = min(pointsSortedX[maxXid].x, float(rect.width));

	minYid = max(pointsSortedY[minYid].y, float(0));
	maxYid = min(pointsSortedY[maxYid].y, float(rect.height));
	// end
	
	Rect interiorRect;
	
	int i = 0;
	
	while ((minXid < maxXid) && (minYid < maxYid)) {
		Point minPoint(minXid, minYid);
		Point maxPoint(maxXid, maxYid);

		interiorRect = Rect(minPoint.x, minPoint.y, maxPoint.x - minPoint.x, maxPoint.y - minPoint.y);
		// out-codes: if one of them is set, the rectangle size has to be reduced at that border
		int ocTop = 0;
		int ocBottom = 0;
		int ocLeft = 0;
		int ocRight = 0;

		bool finished = checkInteriorExteriorCustom(imgPoly, interiorRect, ocTop, ocBottom, ocLeft, ocRight);
		if (finished) {
			break;
		}

		// reduce rectangle at border if necessary
		if (ocLeft) {
			++minXid;
		}
		if (ocRight) {
			--maxXid;
		}
		if (ocTop) {
			++minYid;
		}
		if (ocBottom) {
			--maxYid;
		}		
	}

	return interiorRect;
}
