#ifndef __DBSCAN_REGIONS_SELECTOR_H_INCLUDED__
#define __DBSCAN_REGIONS_SELECTOR_H_INCLUDED__

#include "RegionsSelector.h"

class ImagesMatches;

namespace MapsMerge {
	class DbscanRegionsSelector : public RegionsSelector {
	private:
		double eps1, eps2;
		size_t minElements1, minElements2;
		int numThreads;

		vector<int> findClusters(vector<KeyPoint> keypoints, double eps, size_t numElements);

	public:
		DbscanRegionsSelector(double eps, size_t minElements, int numThreads = 4);
		DbscanRegionsSelector(double eps1, size_t minElements1, double eps2, size_t minElements2, int numThreads = 4);
		
		void selectRegions(ImagesMatches& imgMatches);
		
		vector<DMatch> leaveRegionsMatches(ImagesMatches&, vector<Rect>, vector<Rect>);

	};
}

#endif
