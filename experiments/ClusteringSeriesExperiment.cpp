#include "ClusteringSeriesExperiment.h"

#include "../maps_merger/MapsMerger.h"

#include "../merge_algorithm/keypoints_descriptors_extractor/SurfStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/SiftStrategy.h"
#include "../merge_algorithm/keypoints_descriptors_extractor/AsiftStrategy.h"
#include "../merge_algorithm/descriptors_matcher/FlannMatcherStrategy.h"
#include "../merge_algorithm/regions_selector/DbscanRegionsSelector.h"
#include "../merge_algorithm/image_transformer/ImageTransformerStrategy.h"
#include "../merge_algorithm/images_merger/ImagesMergerStrategy.h"
#include "../merge_algorithm/quality_evaluator/MSSIM.h"
#include "../utils/Utils.h"
#include "../utils/Statistics.h"

void MapsMerge::ClusteringSeriesExperiment::run() {

	string imgPath1 = "imgs/ap-GOPR9460.jpg";
	string imgPath2 = "imgs/from-google-cut.jpg";

	MapsMerger mapsMerger;
	mapsMerger.readImages(imgPath1, imgPath2);
	//mapsMerger.showImages("Image 1", "Image 2");

	mapsMerger.setKeypointsDescriptorsExtractor(new SurfStrategy());
	mapsMerger.detectAndCompute();
	//mapsMerger.showKeypoints("Image 1 with keypoints", "Image 2 with keypoints");

	mapsMerger.setDescriptorMatcher(new FlannMatcherStrategy());
	mapsMerger.matchDescriptors();
	//mapsMerger.showMatches("Matches");

	int minElements = 3;
	int maxElements = 20; /*
	int numStatsColumns = maxElements - minElements + 1;

	Statistics stats("experiments_results/clustering_series_experiment_" + Utils::getTimeStr() + ".csv", numStatsColumns);
	stats.addField("eps \\ minElements");
	for (int iMinElements = minElements; iMinElements < maxElements; iMinElements++) {
		stats.addField(iMinElements);
	}

	for (double eps = 0.005; eps < 0.03; eps += 0.005) {
		stats.addField(eps);

		for (int iMinElements = minElements; iMinElements < maxElements; iMinElements++) {
			mapsMerger.setRegionsSelector(new DbscanRegionsSelector(eps, iMinElements));

			mapsMerger.selectRegions();

			int numClusters1 = Utils::maxElement(mapsMerger.imagesMatches.imgFeatures1.keypointsClusters);
			int numClusters2 = Utils::maxElement(mapsMerger.imagesMatches.imgFeatures2.keypointsClusters);

			stats.addField(to_string(numClusters1) + " | " + to_string(numClusters2));
		}
	}

	stats.closeFile();

	*/


	// An attempt to find eps1, eps2, minElements1, minElements2 for non-zero quality merge
	Statistics statsQ("experiments_results/clustering_merge_quality_experiment2_" + Utils::getTimeStr() + ".csv", 5);

	statsQ.addField("eps1")
		.addField("minElements1")
		.addField("eps2")
		.addField("minElements2")
		.addField("Quality");

	for (double eps1 = 0.01; eps1 < 0.025; eps1 += 0.005) {	
		for (int iMinElements1 = minElements; iMinElements1 < maxElements; iMinElements1++) {
				
			for (double eps2 = 0.01; eps2 < 0.025; eps2 += 0.005) {	
				for (int iMinElements2 = minElements; iMinElements2 < maxElements; iMinElements2++) {

					mapsMerger.setRegionsSelector(new DbscanRegionsSelector(eps1, iMinElements1, eps2, iMinElements2));

					mapsMerger.selectRegions();
				
					mapsMerger.leaveRegionsMatches();
	
					mapsMerger.setImageTransformer(new ImageTransformerStrategy());
					mapsMerger.transformImage();

					mapsMerger.setImagesMerger(new ImagesMergerStrategy());
					mapsMerger.mergeImages();

					mapsMerger.setQualityEvaluator(new MSSIM());
					mapsMerger.evaluateQuality();

					if (mapsMerger.imagesMatches.quality > 0) {
						statsQ.addField(eps1)
							.addField(iMinElements1)
							.addField(eps2)
							.addField(iMinElements2)
							.addField(mapsMerger.imagesMatches.quality);
					}
				}
			}
		}
	}

	statsQ.closeFile();

}
