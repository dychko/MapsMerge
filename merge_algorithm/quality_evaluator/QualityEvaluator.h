#ifndef __QUALITYEVALUATOR_H_INCLUDED__
#define __QUALITYEVALUATOR_H_INCLUDED__

class ImagesMatches;

namespace MapsMerge {
	class QualityEvaluator {

	public:
		virtual void evaluateQuality(ImagesMatches& imgsMatches) = 0;
	};
}

#endif
