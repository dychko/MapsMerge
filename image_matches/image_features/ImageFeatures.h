#ifndef __IMAGEFEATURES_H_INCLUDED__
#define __IMAGEFEATURES_H_INCLUDED__

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace MapsMerge {
	class ImageFeatures {

	private:

	public:
		Mat img;
		vector<KeyPoint> keypoints;
		vector<int> keypointsClusters;
		Mat descriptors;

		vector<Rect> regions;

		void readImage(string imgPath);
		void showImage(string windowName);
		void showKeypoints(string windowName);
		void showRegions(string windowName);
		void showClusters(string windowName);
		void writeRegions(string fileName);

		void shuffeRegions();

	};
}

#endif
