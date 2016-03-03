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
		void showMatches(string winName);
		void showTransformedImage(string winName);
		void showMergedImage(string winName);
	};
}

#endif
