#ifndef __SURFSTRATEGY_H_INCLUDED__
#define __SURFSTRATEGY_H_INCLUDED__

#include "KeypointsDescriptorsExtractor.h"
#include "opencv2/nonfree/features2d.hpp"

class ImagesMatches;

using namespace cv;
using namespace std;

namespace MapsMerge {
	class SurfStrategy : public MapsMerge::KeypointsDescriptorsExtractor {

	public:
		void detectAndCompute(ImagesMatches& imgsMatches);
		string getAlgName();
	
	};
}

#endif
