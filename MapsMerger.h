#ifndef __MAPSMERGER_H_INCLUDED__
#define __MAPSMERGER_H_INCLUDED__

#include "ImagesMatches.h"

#include "KeypointsDescriptorsExtractor.h"
#include "DescriptorsMatcher.h"
#include "RegionsSelector.h"
#include "ImageTransformer.h"
#include "images_merger\ImagesMerger.h"

using namespace std;

namespace MapsMerge {
	class MapsMerger {

	private:
		ImagesMatches imagesMatches;
		KeypointsDescriptorsExtractor* keypointsDescriptorsExtractor;
		DescriptorsMatcher* descriptorsMatcher;
		RegionsSelector* regionsSelector;
		ImageTransformer* imageTransformer;
		ImagesMerger* imagesMerger;
		//MapsMerge::QualityEvaluator qualityEvaluator;
	public:
		void readImages(std::string imgPath1, std::string imgPath2);
		void showImages(string winName1, string winName2);
		void showKeypoints(string winName1, string winName2);
		void showMatches(string winName);

		void setKeypointsDescriptorsExtractor(KeypointsDescriptorsExtractor* e);
		void detectAndCompute();

		void setDescriptorMatcher(DescriptorsMatcher* d);
		void matchDescriptors();

		void setRegionsSelector(RegionsSelector* s);
		void selectRegions();
		void leaveRegionsMatches();		

		void setImageTransformer(ImageTransformer* t);
		void transformImage();
		void showTransformedImage(string winName);

		void setImagesMerger(ImagesMerger* m);
		void mergeImages();
		void showMergedImage(string winName);

	};
}

#endif
