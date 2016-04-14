#ifndef __SIMPLE_MATCHER_STRATEGY_H_INCLUDED__
#define __SIMPLE_MATCHER_STRATEGY_H_INCLUDED__

#include "SimpleMatcherStrategy.h"

class ImagesMatches;

using namespace std;

namespace MapsMerge {
	class SimpleMatcherStrategy : public MapsMerge::RegionsMatcher {
	
	public:
		void matchRegions(ImagesMatches& imgsMatches);

	};
}

#endif
