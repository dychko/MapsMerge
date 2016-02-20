#ifndef __MAPSMERGER_H_INCLUDED__
#define __MAPSMERGER_H_INCLUDED__

#include "ImagesMatches.h"

#include "KeypointsDescriptorsExtractor.h"

using namespace std;

namespace MapsMerge {
	class MapsMerger {

	private:
		ImagesMatches imagesMatches;
		KeypointsDescriptorsExtractor* keypointsDescriptorsExtractor;
		//MapsMerge::DescriptorsMatcher descriptorMatcher;
		//MapsMerge::RegionsSelector regionsSelector;
		//MapsMerge::ImageTransformer imageTransformer;
		//MapsMerge::ImagesMerger imagesMerger;
		//MapsMerge::QualityEvaluator qualityEvaluator;
	public:
		void readImages(std::string imgPath1, std::string imgPath2);
		void showImages();
		void showKeypoints();

		void setKeypointsDescriptorsExtractor(KeypointsDescriptorsExtractor* e);
		void detectAndCompute();
	};
}

#endif
