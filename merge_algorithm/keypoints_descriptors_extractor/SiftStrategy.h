#ifndef __SIFTSTRATEGY_H_INCLUDED__
#define __SIFTSTRATEGY_H_INCLUDED__

#include "KeypointsDescriptorsExtractor.h"
#include "opencv2/nonfree/features2d.hpp"

class ImagesMatches;

namespace MapsMerge {
	class SiftStrategy : public MapsMerge::KeypointsDescriptorsExtractor {

	public:
		void detectAndCompute(ImagesMatches& imgsMatches);
		string getAlgName();

	};
}

#endif
