#ifndef __REGIONS_MATCHING_EXPERIMENT_H_INCLUDED__
#define __REGIONS_MATCHING_EXPERIMENT_H_INCLUDED__

#include "AbstractExperiment.h"
#include "../maps_merger/MapsMerger.h"

using namespace std;

namespace MapsMerge {
	class RegionsMatchingExperiment : public MapsMerge::AbstractExperiment, public MapsMerge::MapsMerger {

	private: 
		double getRelativeCorrectness(vector<Rect> originalRegions, vector<Rect> matchedRegions);

	public:
		void run();
	};
}

#endif
