#ifndef __IMAGEMATCHES_H_INCLUDED__
#define __IMAGEMATCHES_H_INCLUDED__

#include "image_features\ImageFeatures.h"

namespace MapsMerge {
	class ImagesMatches {

	public:
		MapsMerge::ImageFeatures imgFeatures1;
		MapsMerge::ImageFeatures imgFeatures2;

		vector<DMatch> matches;
		vector<DMatch> goodMatches;

		Mat transformedImage;

		Mat mergedImages;
		
		// For quality measurement
		Rect interiorRect;

		double quality;

		void readImages(string imgPath1, string imgPath2);
		void showImages(string winName1, string winName2);
		void showKeypoints(string winName1, string winName2);
		void showRegions(string winName1, string winName2);
		void showClusters(string winName1, string winName2);
		void writeRegions(string fileName1, string fileName2);
		void showMatches(string winName);
		void showGoodMatches(string winName);
		void showTransformedImage(string winName);
		void showMergedImage(string winName);
		void writeMergedImage(string fileName);
	};
}

#endif
