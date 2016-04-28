#ifndef __MAPSMERGER_H_INCLUDED__
#define __MAPSMERGER_H_INCLUDED__

#include "../image_matches/ImagesMatches.h"

#include "../merge_algorithm/keypoints_descriptors_extractor/KeypointsDescriptorsExtractor.h"
#include "../merge_algorithm/descriptors_matcher/DescriptorsMatcher.h"
#include "../merge_algorithm/regions_selector/RegionsSelector.h"
#include "../merge_algorithm/regions_matcher/RegionsMatcher.h"
#include "../merge_algorithm/image_transformer/ImageTransformer.h"
#include "../merge_algorithm/images_merger/ImagesMerger.h"
#include "../merge_algorithm/quality_evaluator/QualityEvaluator.h"

using namespace std;

namespace MapsMerge {
	class MapsMerger {

	public:
		ImagesMatches imagesMatches; // TODO: Maybe change it back
	protected:
		KeypointsDescriptorsExtractor* keypointsDescriptorsExtractor;
		DescriptorsMatcher* descriptorsMatcher;
		RegionsSelector* regionsSelector;
		RegionsMatcher* regionsMatcher;
		ImageTransformer* imageTransformer;
		ImagesMerger* imagesMerger;
		QualityEvaluator* qualityEvaluator;
	public:
		void readImages(std::string imgPath1, std::string imgPath2);
		void showImages(string winName1, string winName2);
		void showKeypoints(string winName1, string winName2);
		void showMatches(string winName);
		void showGoodMatches(string winName);
		void showRegions(string winName1, string winName2);
		void showClusters(string winName1, string winName2);
		void writeRegions(string fileName1, string fileName2);

		void setKeypointsDescriptorsExtractor(KeypointsDescriptorsExtractor* e);
		void detectAndCompute();
		string getExtractorAlgName();

		void setDescriptorMatcher(DescriptorsMatcher* d);
		void matchDescriptors();

		void setRegionsSelector(RegionsSelector* s);
		void selectRegions();
		void leaveRegionsMatches();

		int getNumRegions();

		void setRegionsMatcher(RegionsMatcher* m);
		void shuffleRegions();
		void matchRegions();

		void setImageTransformer(ImageTransformer* t);
		void transformImage();
		void showTransformedImage(string winName);

		void setImagesMerger(ImagesMerger* m);
		void mergeImages();
		void showMergedImage(string winName);
		void writeMergedImage(string fileName);

		void setQualityEvaluator(QualityEvaluator* e);
		void evaluateQuality();

		void setRegionsByIndexes(vector<Rect>& regions1, vector<Rect>& regions2, vector<int>& regionsIndexes);

	};
}

#endif
