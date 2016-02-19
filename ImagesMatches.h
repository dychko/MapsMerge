#ifndef __IMAGEMATCHES_H_INCLUDED__
#define __IMAGEMATCHES_H_INCLUDED__

#include "ImageFeatures.h"

namespace MapsMerge {
	class ImagesMatches {

	private:
		int matches;
		int goodMatches;

	public:
		MapsMerge::ImageFeatures imgFeatures1;
		MapsMerge::ImageFeatures imgFeatures2;

		void readImages(string imgPath1, string imgPath2);
		void showImages();
	};
}

#endif
