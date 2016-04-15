#include "TransformationQualityExperiment.h"

#include <iostream>
#include <ctime>

#include "../maps_merger/MapsMerger.h"

#include "../merge_algorithm/keypoints_descriptors_extractor/SurfStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/SiftStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/AsiftStrategy.h"
#include "../merge_algorithm/descriptors_matcher/FlannMatcherStrategy.h"
#include "../merge_algorithm/regions_selector/ManualRegionsSelector.h"
#include "../merge_algorithm/regions_matcher/GaleShapleyMatcherStrategy.h"
#include "../merge_algorithm/regions_matcher/SimpleMatcherStrategy.h"
#include "../merge_algorithm/image_transformer/ImageTransformerStrategy.h"
#include "../merge_algorithm/images_merger/ImagesMergerStrategy.h"
#include "../merge_algorithm/quality_evaluator/MSSIM.h"

#include "../utils/Utils.h"
#include "../utils/Statistics.h"

/*
  Create name for image in experiments by given template
  E.g.: "alg=asift_regions=3_id=12_type=merge"
 */
string MapsMerge::TransformationQualityExperiment::createImgName(string rootPath,
				     string algName,			// Name of the algorithm
					 int numRegions,			// Number of regions selected for merge
					 int id,					// id of the experiment
					 string type,				// Type of the image (image with regions - "1regions", "2regions", merged images - "merge")
					 string extension = "jpg"	// Extension of image to write
					 ) {

	return rootPath + 
		   "alg=" + algName + "_" + 
		   "regions=" + to_string(numRegions) + "_" +
		   "id=" + to_string(id) + "_" +
		   "type=" + type +
		   "." + extension;
}

void MapsMerge::TransformationQualityExperiment::run() {

	string imgPath1 = "imgs/ap-GOPR9460.jpg";
	string imgPath2 = "imgs/from-google-cut.jpg";

	string resPath = "E:/Diploma/Results/merge/with regions/hq_new/";

	MapsMerger mapsMerger;
	mapsMerger.readImages(imgPath1, imgPath2);

	mapsMerger.setRegionsSelector(new ManualRegionsSelector());
	mapsMerger.selectRegions();
	
	vector<vector<int>> regionsIndexes = Utils::getTuples4Vector(mapsMerger.getNumRegions());

	vector<Rect> allSavedRegions1 = mapsMerger.imagesMatches.imgFeatures1.regions;
	vector<Rect> allSavedRegions2 = mapsMerger.imagesMatches.imgFeatures2.regions;
		
	vector<KeypointsDescriptorsExtractor*> keypointsAlgs;
	keypointsAlgs.push_back(new SurfStrategy());
	keypointsAlgs.push_back(new AsiftStrategy());
	keypointsAlgs.push_back(new SiftStrategy());
	
	Statistics stats(resPath + "/transformation_quality_experiment_" + Utils::getTimeStr() + ".csv", 8);
	stats.addField("Src img name")
		 .addField("Src img resolution")
		 .addField("Dst img name")
		 .addField("Dst img resolution")
		 .addField("Algorithm")
		 .addField("Regions qtty")
		 .addField("id")
		 .addField("MSSIM");

	for(int iAlg = 0; iAlg < keypointsAlgs.size(); iAlg++) {
		int experimentId = 0;
		mapsMerger.setKeypointsDescriptorsExtractor(keypointsAlgs[iAlg]);		
		mapsMerger.detectAndCompute();
		mapsMerger.setDescriptorMatcher(new FlannMatcherStrategy());
		mapsMerger.matchDescriptors();

		for(int iRegionsBatch = 0; iRegionsBatch < regionsIndexes.size(); iRegionsBatch++) {
			experimentId++;
			vector<int> regionsBatchIndexes = regionsIndexes[iRegionsBatch];		
			mapsMerger.setRegionsByIndexes(allSavedRegions1, allSavedRegions2, regionsBatchIndexes);
			mapsMerger.writeRegions(
				createImgName(resPath, mapsMerger.getExtractorAlgName(), (int)regionsBatchIndexes.size(), experimentId, "1regions"),
				createImgName(resPath, mapsMerger.getExtractorAlgName(), (int)regionsBatchIndexes.size(), experimentId, "2regions"));			

			mapsMerger.leaveRegionsMatches();

			mapsMerger.setImageTransformer(new ImageTransformerStrategy());
			mapsMerger.transformImage();

			mapsMerger.setImagesMerger(new ImagesMergerStrategy());
			mapsMerger.mergeImages();
			mapsMerger.writeMergedImage(createImgName(resPath, mapsMerger.getExtractorAlgName(), regionsBatchIndexes.size(), experimentId, "merge"));

			mapsMerger.setQualityEvaluator(new MSSIM());
			mapsMerger.evaluateQuality();
			
			stats.addField(imgPath1)
				 .addField(to_string(mapsMerger.imagesMatches.imgFeatures1.img.cols) + "x" + to_string(mapsMerger.imagesMatches.imgFeatures1.img.rows))
				 .addField(imgPath2)
				 .addField(to_string(mapsMerger.imagesMatches.imgFeatures2.img.cols) + "x" + to_string(mapsMerger.imagesMatches.imgFeatures2.img.rows))
				 .addField(mapsMerger.getExtractorAlgName())
				 .addField((int)regionsBatchIndexes.size())
				 .addField(experimentId)
				 .addField(mapsMerger.imagesMatches.quality);
		}
	}

	stats.closeFile();

}
