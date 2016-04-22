#ifndef __DBSCAN_REGIONS_SELECTOR_H_INCLUDED__
#define __DBSCAN_REGIONS_SELECTOR_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class DbscanRegionsSelector {
	private:
		double eps;
		size_t minElements;
		int numThreads;

		vector<int> findClusters(vector<KeyPoint> keypoints);

	public:
		virtual void selectRegions(ImagesMatches& imgMatches) = 0;		

		DbscanRegionsSelector(double eps, size_t minElements, int numThreads = 4);

	};
}

#endif
