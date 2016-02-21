#ifndef __MAPSMERGER_H_INCLUDED__
#define __MAPSMERGER_H_INCLUDED__

#include "ImagesMatches.h"

#include "KeypointsDescriptorsExtractor.h"
#include "DescriptorsMatcher.h"
#include "RegionsSelector.h"

using namespace std;

namespace MapsMerge {
	class MapsMerger {

	private:
		ImagesMatches imagesMatches;
		KeypointsDescriptorsExtractor* keypointsDescriptorsExtractor;
		DescriptorsMatcher* descriptorsMatcher;
		RegionsSelector* regionsSelector;
		//MapsMerge::ImageTransformer imageTransformer;
		//MapsMerge::ImagesMerger imagesMerger;
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

	};
}

#endif
