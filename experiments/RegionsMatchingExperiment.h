#ifndef __REGIONS_MATCHING_EXPERIMENT_H_INCLUDED__
#define __REGIONS_MATCHING_EXPERIMENT_H_INCLUDED__

#include "AbstractExperiment.h"
#include "../maps_merger/MapsMerger.h"

using namespace std;

namespace MapsMerge {
	class RegionsMatchingExperiment : public MapsMerge::AbstractExperiment, public MapsMerge::MapsMerger {

	public:
		void run();
	};
}

#endif
