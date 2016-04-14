#ifndef __GALE_SHAPLEY_MATCHER_STRATEGY_H_INCLUDED__
#define __GALE_SHAPLEY_MATCHER_STRATEGY_H_INCLUDED__

#include "RegionsMatcher.h"

class ImagesMatches;

using namespace std;

namespace MapsMerge {
	class GaleShapleyMatcherStrategy : public MapsMerge::RegionsMatcher {
	
	private:
		vector<int> findPreferences(const vector<int> numMatches);
		bool prefers(vector<vector<int>> matrix2, int w, int m, int m1);
		vector<int> algGaleShapley(vector<vector<int>> matrix1, vector<vector<int>> matrix2);
	
	public:
		void matchRegions(ImagesMatches& imgsMatches);

		void testGaleShapleyAlgorithm();

	};
}

#endif
