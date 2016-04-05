#ifndef __REGIONS_MATCHER_H_INCLUDED__
#define __REGIONS_MATCHER_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class RegionsMatcher {

	public:
		virtual void matchRegions(ImagesMatches& imgsMatches) = 0;
		
		void shuffleRegions(ImagesMatches& imgsMatches);

		virtual void testGaleShapleyAlgorithm() = 0; // TODO: Remove it later

	};
}

#endif
