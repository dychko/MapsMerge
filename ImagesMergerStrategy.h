#ifndef __IMAGESMERGERSTRATEGY_H_INCLUDED__
#define __IMAGESMERGERSTRATEGY_H_INCLUDED__

#include "images_merger\ImagesMerger.h"
#include "opencv2\core\core.hpp"

class ImagesMatches;

using namespace cv;

namespace MapsMerge {
	class ImagesMergerStrategy : public MapsMerge::ImagesMerger {

	public:
		void mergeImages(ImagesMatches& imgsMatches);
	};
}

#endif
