#ifndef __ASIFTSTRATEGY_H_INCLUDED__
#define __ASIFTSTRATEGY_H_INCLUDED__

#include "KeypointsDescriptorsExtractor.h"
#include "ASIFT/ASiftDetector.h"

class ImagesMatches;

namespace MapsMerge {
	class AsiftStrategy : public MapsMerge::KeypointsDescriptorsExtractor {

	public:
		void detectAndCompute(ImagesMatches& imgsMatches);
		string getAlgName();

	};
}

#endif
