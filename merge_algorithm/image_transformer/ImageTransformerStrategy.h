#ifndef __IMAGETRANSFORMERSTRATEGY_H_INCLUDED__
#define __IMAGETRANSFORMERSTRATEGY_H_INCLUDED__

#include "ImageTransformer.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ImagesMatches;

namespace MapsMerge {
	class ImageTransformerStrategy : public MapsMerge::ImageTransformer {

	public:
		void transformImage(ImagesMatches& imgsMatches);
	};
}

#endif
