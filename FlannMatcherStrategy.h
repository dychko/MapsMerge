#ifndef __FLANNMATCHER_H_INCLUDED__
#define __FLANNMATCHER_H_INCLUDED__

#include "DescriptorsMatcher.h"
#include "opencv2/features2d/features2d.hpp"

class ImagesMatches;

using namespace cv;
using namespace std;

namespace MapsMerge {
	class FlannMatcherStrategy : public MapsMerge::DescriptorsMatcher {
	private:
		FlannBasedMatcher matcher;

	public:
		void matchDescriptors(ImagesMatches& imgsMatches);
	};
}

#endif
