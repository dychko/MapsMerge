#ifndef __REGIONS_MATCHER_H_INCLUDED__
#define __REGIONS_MATCHER_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class RegionsMatcher {

	public:
		virtual void matchRegions(ImagesMatches& imgsMatches) = 0;
		
		void shuffleRegions(ImagesMatches& imgsMatches);
		vector<vector<vector<int>>> createNumMatchesMatrices(ImagesMatches& imgsMatches);
	};
}

#endif
