#ifndef __MSSIM_H_INCLUDED__
#define __MMSIM_H_INCLUDED__

#include "QualityEvaluator.h"

namespace MapsMerge {
	class MSSIM : public MapsMerge::QualityEvaluator {

	public:
		Scalar getMSSIM(const Mat& i1, const Mat& i2);
		void evaluateQuality(ImagesMatches& imgsMatches);
	};
}

#endif
